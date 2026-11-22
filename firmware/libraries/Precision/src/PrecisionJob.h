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

  // The write rule (design §4, incl. D7) for a READY job, then idle. `outcome` is
  // "yes" | "no" | "FAILED (<why>)"; `why` says what decided it. Returns true if it wrote.
  bool finish(Ttdb& db, char* scratch, size_t cap, uint32_t node, uint32_t t_sec,
              const char* stamp, const char*& outcome, char* why, size_t why_cap) {
    outcome = "no";
    snprintf(why, why_cap, "n=0");
    if (state_ != READY) { outcome = "FAILED (not ready)"; return false; }
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
    }
    if (f_.n() > 0) {
      if (!old.present)
        snprintf(why, why_cap, "none on flash");
      else if (!old.has_from || old.from != f_.from())
        snprintf(why, why_cap, "from moved %ld->%ld", (long)old.from, (long)f_.from());
      else
        snprintf(why, why_cap, "d=%d", (int)f_.prec() - (int)old.prec);
    }
    if (!shouldWrite(old, f_)) return false;
    const uint16_t rev = old.present ? (uint16_t)(old.rev + 1) : 0;
    const size_t m = render(scratch, cap, f_, node, rev, old.present ? old.created : 0, t_sec,
                            stamp ? stamp : "");
    if (m == 0) { outcome = "FAILED (render)"; return false; }
    if (existing < 0 && db.indexHeadroom() < 1) {
      outcome = "FAILED (index full)";        // ACT-III: never refused without saying so
      return false;
    }
    if (existing >= 0) {
      const TtdbCut cut = {PRECISION_LANE, (int16_t)chan, (int16_t)chan};
      if (!db.removeCuts(&cut, 1)) { outcome = "FAILED (removeCuts)"; return false; }
    }
    if (!db.appendRecord(scratch, m)) { outcome = "FAILED (append)"; return false; }
    outcome = "yes";
    return true;
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

}  // namespace precision
