// PrecisionJob.h — the D3b fold job (docs/design/rfc0011-stage3.md §5.1). Portable: it
// drives a real `Ttdb` but needs no Arduino API of its own, so tests/test_precision_job.cpp
// runs it through tests/shim/ against the real store, with cuts and appends injected
// mid-job. PrecisionNode.h is the Arduino glue (clock, stamp, serial line).
//
// Why a job: the synchronous fold measured 141–288 ms on the Cardputer (run 1, §9), over
// D3's 100 ms budget. A job folds at most PRECISION_JOB_STEP episodes per loop pass.
//
// ⚠ POSITION IS RE-FOUND EVERY PASS, BY THE LON OF THE LAST FOLDED EPISODE — never held as
// an index. Cuts and appends between passes re-index the Ttdb, so a remembered index can
// point anywhere. The search is over the in-RAM index (≤ TTDB_MAX_RECORDS entries) and
// costs microseconds. It is sound because episodes are never rewritten in place (appends
// go to the end, rewrites keep order, delivered episodes live in @LAT105): an episode found
// after the last folded one has not been folded. If the last folded one is gone, the job
// ABORTS rather than guessing.
#pragma once
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "TTDB.h"
#include "Precision.h"

#ifndef PRECISION_JOB_STEP
#define PRECISION_JOB_STEP 2   // episodes per loop pass (design §5.1)
#endif

namespace precision {

class Job {
 public:
  enum Status : uint8_t { IDLE = 0, FOLDING, READY, ABORTED };

  // false (and nothing changes) if a job is already running — the caller prints `busy`
  // and does not advance its rotation.
  bool start(uint8_t chan) {
    if (state_ == FOLDING || state_ == READY) return false;
    f_.reset(chan);
    last_lon_ = -1;
    state_ = FOLDING;
    abort_why_ = "";
    passes_ = 0;
    return true;
  }
  bool running() const { return state_ == FOLDING || state_ == READY; }
  const Fold& fold() const { return f_; }
  const char* abortWhy() const { return abort_why_; }
  uint32_t passes() const { return passes_; }
  uint32_t aborts() const { return aborts_; }

  // One loop pass: fold up to PRECISION_JOB_STEP more episodes. Returns FOLDING while there
  // is more, READY when the fold is complete (call finish() next), ABORTED when it gave up
  // (abortWhy() says why; the job is idle again), IDLE when nothing is running.
  Status step(Ttdb& db, char* scratch, size_t cap) {
    if (state_ != FOLDING) return state_ == READY ? READY : IDLE;
    ++passes_;
    int i = 0;
    if (last_lon_ >= 0) {
      const int at = findEpisode(db, last_lon_);
      if (at < 0) return abort("episode cut mid-fold");
      i = at + 1;
    }
    int folded = 0;
    for (; i < db.recordCount(); ++i) {
      const TtdbRecord& r = db.record(i);
      if (r.lat != PRECISION_EPISODE_LANE || chanOfLon(r.lon) != (int)f_.chan()) continue;
      if (folded == PRECISION_JOB_STEP) return FOLDING;   // more remain: next pass
      size_t off = 0, len = 0;
      if (!db.recordSpan(i, off, len) || len + 1 > cap ||
          db.readBytes(off, (uint8_t*)scratch, len) != len) {
        f_.skip(r.lon);          // counted and written down; the gate FAILs on any skip
      } else {
        scratch[len] = 0;
        f_.add(scratch, len, r.lon);
      }
      last_lon_ = r.lon;
      ++folded;
    }
    // End of the index. A record whose first episode is already gone would be
    // UNVERIFIABLE at birth (design §5.1), so do not write one.
    if (f_.episodes() > 0 && findEpisode(db, f_.from()) < 0) return abort("from cut mid-fold");
    state_ = READY;
    return READY;
  }

  // Outcome of finish(): what the write rule (design §11 D8) did.
  enum Outcome : uint8_t { NO_WRITE = 0, WROTE, DEFERRED, FAILED };
  struct Carry {             // rev/created of a record a rider cut deleted (D8)
    bool has = false;
    uint16_t rev = 0;        // the rev the NEXT write takes (old + 1)
    uint32_t created = 0;
  };

  // The write rule (design §11 D8) for a READY job, then idle. It NEVER rewrites: with no
  // record on flash and n > 0 it APPENDS (rev/created from `carry` when a rider cut deleted
  // the old one); with a record on flash and |Δπ| > 8 or a moved `from` it returns DEFERRED
  // — the caller marks the channel stale and the next episode cut deletes the record.
  // `outcome` is "yes" | "no" | "deferred to next cut" | "FAILED (<why>)"; `why` says what
  // decided it.
  Outcome finish(Ttdb& db, char* scratch, size_t cap, uint32_t node, uint32_t t_sec,
                 const char* stamp, const Carry& carry, const char*& outcome, char* why,
                 size_t why_cap) {
    outcome = "no";
    snprintf(why, why_cap, "n=0");
    if (state_ != READY) { outcome = "FAILED (not ready)"; return FAILED; }
    state_ = IDLE;
    const uint8_t chan = f_.chan();
    int existing = -1;
    for (int i = 0; i < db.recordCount(); ++i)
      if (db.record(i).lat == PRECISION_LANE && db.record(i).lon == chan) existing = i;
    OnFlash old;
    if (existing >= 0) {
      size_t off = 0, len = 0;
      if (db.recordSpan(existing, off, len) && len + 1 <= cap &&
          db.readBytes(off, (uint8_t*)scratch, len) == len) {
        scratch[len] = 0;
        readOnFlash(scratch, len, old);
      }
      old.present = true;      // there IS a record; an unreadable one counts as moved
    }
    if (f_.n() > 0) {
      if (existing < 0)
        snprintf(why, why_cap, carry.has ? "deleted by cut, rev %u" : "none on flash",
                 (unsigned)carry.rev);
      else if (!old.has_from || old.from != f_.from())
        snprintf(why, why_cap, "from moved %ld->%ld (invariant)", (long)old.from,
                 (long)f_.from());
      else
        snprintf(why, why_cap, "d=%d", (int)f_.prec() - (int)old.prec);
    }
    if (f_.n() == 0) return NO_WRITE;
    if (existing >= 0) {
      if (!shouldWrite(old, f_)) return NO_WRITE;
      outcome = "deferred to next cut";
      return DEFERRED;
    }
    const uint16_t rev = carry.has ? carry.rev : 0;
    const size_t m = render(scratch, cap, f_, node, rev, carry.has ? carry.created : 0, t_sec,
                            stamp ? stamp : "");
    if (m == 0) { outcome = "FAILED (render)"; return FAILED; }
    if (db.indexHeadroom() < 1) {
      outcome = "FAILED (index full)";        // ACT-III: never refused without saying so
      return FAILED;
    }
    if (!db.appendRecord(scratch, m)) { outcome = "FAILED (append)"; return FAILED; }
    outcome = "yes";
    return WROTE;
  }

 private:
  static int findEpisode(Ttdb& db, int32_t lon) {
    for (int i = 0; i < db.recordCount(); ++i)
      if (db.record(i).lat == PRECISION_EPISODE_LANE && db.record(i).lon == lon) return i;
    return -1;
  }
  Status abort(const char* why) {
    abort_why_ = why;
    state_ = IDLE;
    ++aborts_;
    return ABORTED;
  }

  Fold f_;
  int32_t last_lon_ = -1;
  uint8_t state_ = IDLE;
  const char* abort_why_ = "";
  uint32_t passes_ = 0, aborts_ = 0;
};

// The whole lane on one node (design §2, §5.1, §11 D8): the rotation, the job, the stale and
// refold marks, the carry, and the cut-rider callbacks EpisodeNode calls. Portable: the
// Arduino glue (PrecisionNode.h) adds only the clock, the stamp and the serial line.
class Lane {
 public:
  void attach(Ttdb* db, char* scratch, size_t cap) {
    db_ = db;
    scratch_ = scratch;
    cap_ = cap;
  }

  // Stage D: start the next rotation channel. false = a job is running (`busy`); the
  // rotation does not move.
  bool startCycle() {
    if (job_.running()) return false;
    job_.start(next_);
    next_ = (uint8_t)((next_ + 1) % CH_COUNT);
    return true;
  }
  // Every loop pass, before step(): a channel a rider cut emptied refolds AHEAD of the
  // rotation (D8). True if it started one.
  bool startQueued() {
    if (job_.running() || !refold_) return false;
    for (uint8_t c = 0; c < CH_COUNT; ++c)
      if (refold_ & (1u << c)) {
        job_.start(c);
        return true;
      }
    return false;
  }
  Job::Status step() { return job_.step(*db_, scratch_, cap_); }
  // After step() returned READY: apply D8 and update the marks.
  Job::Outcome finish(uint32_t node, uint32_t t_sec, const char* stamp, const char*& outcome,
                      char* why, size_t why_cap) {
    const uint8_t c = job_.fold().chan();
    const Job::Outcome o = job_.finish(*db_, scratch_, cap_, node, t_sec, stamp, carry_[c],
                                       outcome, why, why_cap);
    if (o == Job::WROTE) carry_[c] = Job::Carry();
    if (o == Job::DEFERRED) stale_ |= (uint8_t)(1u << c);
    if (o != Job::FAILED) refold_ &= (uint8_t)~(1u << c);   // a FAILED append retries
    return o;
  }

  // ---- the cut rider (EpisodeNode::attachCutRider) --------------------------------------
  // Add {108, k, k} for every channel with a record on flash whose band this cut touches,
  // or that is stale, and carry its rev/created. ⚠ Reads the record into the scratch: the
  // episode tier calls this from cut(), where its scratch is not in use.
  uint8_t riderCuts(const TtdbCut* cuts, uint8_t n, TtdbCut* out, uint8_t cap) {
    pending_ = 0;
    uint8_t touched = stale_;
    for (uint8_t i = 0; i < n; ++i) {
      if (cuts[i].lat != PRECISION_EPISODE_LANE) continue;
      const int lo = chanOfLon(cuts[i].lon_lo), hi = chanOfLon(cuts[i].lon_hi);
      if (lo >= 0) touched |= (uint8_t)(1u << lo);
      if (hi >= 0) touched |= (uint8_t)(1u << hi);
    }
    uint8_t m = 0;
    for (int i = 0; i < db_->recordCount() && m < cap; ++i) {
      const TtdbRecord& r = db_->record(i);
      if (r.lat != PRECISION_LANE || r.lon < 0 || r.lon >= CH_COUNT) continue;
      const uint8_t c = (uint8_t)r.lon;
      if (!(touched & (1u << c)) || (pending_ & (1u << c))) continue;
      OnFlash old;
      size_t off = 0, len = 0;
      if (db_->recordSpan(i, off, len) && len + 1 <= cap_ &&
          db_->readBytes(off, (uint8_t*)scratch_, len) == len) {
        scratch_[len] = 0;
        readOnFlash(scratch_, len, old);
      }
      pend_carry_[c].has = true;
      pend_carry_[c].rev = old.present ? (uint16_t)(old.rev + 1) : 0;
      pend_carry_[c].created = old.present ? old.created : 0;
      out[m++] = TtdbCut{PRECISION_LANE, (int16_t)c, (int16_t)c};
      pending_ |= (uint8_t)(1u << c);
    }
    return m;
  }
  void cutDone(bool ok) {
    if (ok) {
      for (uint8_t c = 0; c < CH_COUNT; ++c)
        if (pending_ & (1u << c)) carry_[c] = pend_carry_[c];
      refold_ |= pending_;
      stale_ &= (uint8_t)~pending_;
      deleted_ += countBits(pending_);
    }
    pending_ = 0;   // a failed cut changed nothing on flash: drop the carry, keep stale
  }
  static uint8_t riderExtra(void* ctx, const TtdbCut* c, uint8_t n, TtdbCut* out, uint8_t cap) {
    return static_cast<Lane*>(ctx)->riderCuts(c, n, out, cap);
  }
  static void riderDone(void* ctx, bool ok) { static_cast<Lane*>(ctx)->cutDone(ok); }

  const Job& job() const { return job_; }
  uint8_t staleMask() const { return stale_; }
  uint8_t refoldMask() const { return refold_; }
  uint32_t deletedByCuts() const { return deleted_; }

 private:
  static uint8_t countBits(uint8_t v) {
    uint8_t n = 0;
    for (; v; v >>= 1) n += v & 1u;
    return n;
  }
  Ttdb* db_ = nullptr;
  char* scratch_ = nullptr;
  size_t cap_ = 0;
  Job job_;
  uint8_t next_ = CH_LINK;
  uint8_t stale_ = 0, refold_ = 0, pending_ = 0;
  uint32_t deleted_ = 0;
  Job::Carry carry_[CH_COUNT], pend_carry_[CH_COUNT];
};

}  // namespace precision
