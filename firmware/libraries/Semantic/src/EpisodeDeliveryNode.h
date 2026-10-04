// EpisodeDeliveryNode.h — the Arduino glue for C4 stage 2 (docs/design/episode-order.md §7):
// serve this node's LINK episodes to peers that WANT them, fetch theirs into @LAT105, and
// print the BAR VIEW once per bar line and keep it as a @LAT106 BAR record (so the view a
// node computed survives without a cable listening). The portable half is EpisodeDelivery.h.
//
// ⚠ Header-only and NOT in the native test build (<Arduino.h>, TTDB.h). What could be wrong in
// a way a test could catch lives in EpisodeDelivery.cpp; this is plumbing, kept small.
//
// ORDER OF CALLS (sketch):
//   gDelivery.attach(gEpisodes);                    BEFORE gEpisodes.begin(): boot lines -> SeqMap
//   gEpisodes.begin(gDb);
//   gDelivery.begin(gDb, gEpisodes, gOrder, kNodeId, sendFn);   still before the radios: boot cut
//   recv callback:  gDelivery.onToot(t.src_node_id, payload, len)  for every EPISODE toot
//                   but a VECTOR (the toot's src is who a WANT came from)
//   loop():         gDelivery.service(now, have_frame, frame, pulse_now)
//
// ⚠ THE RECV CALLBACK ONLY COPIES (the TimeStream rule): a WANT goes into one slot, DATA and
// DONE into the Inflight buffer loop() armed. Every flash read/write, every send and every
// allocation happens in service(), from loop().
#pragma once
#include <Arduino.h>
#include <TTDB.h>
#include <new>
#include "EpisodeDelivery.h"
#include "EpisodeNode.h"

namespace episodedelivery {

typedef void (*SendFn)(const uint8_t* body, uint8_t n);

#ifndef EPISODEDELIVERY_SLICE_GAP_MS
#define EPISODEDELIVERY_SLICE_GAP_MS 12     // ESP-NOW burst pacing between DATA slices
#endif
#ifndef EPISODEDELIVERY_CUT_RETRY_MS
#define EPISODEDELIVERY_CUT_RETRY_MS 300000UL
#endif

struct Stats {
  uint32_t wants_sent = 0, fetched = 0, duplicate = 0, refused = 0, broken = 0,
           unanswered = 0, empty = 0, append_failed = 0, nomem = 0, resumed = 0;
  uint32_t wants_heard = 0, served = 0, served_empty = 0, cuts = 0, cut_failed = 0;
  uint32_t bars_written = 0, bar_fail = 0, cut_early = 0;
};

class Node {
 public:
  // This board's ceiling for held copies (its share of the 288-slot index). Before begin().
  void setHeldHardMax(uint16_t n) { hard_max_ = n; }

  void attach(episodenode::Node& ep) {
    ep.attachBootSink(&Node::bootLine, this);
  }

  void begin(Ttdb& db, episodenode::Node& ep, semantic::VectorClock& vc, uint32_t self,
             SendFn send) {
    db_ = &db; ep_ = &ep; vc_ = &vc; self_ = self; send_ = send;
    fetch_.begin(self);
    held_.reset();
    for (int i = 0; i < db.recordCount(); ++i)          // file order = age order
      if (db.record(i).lat == EPISODEDELIVERY_HELD_LANE)
        episodenode::streamRecord(db, i, held_, long_lines_);
    held_.finish();
    bars_.reset();
    for (int i = 0; i < db.recordCount(); ++i)
      if (db.record(i).lat == EPISODEDELIVERY_BAR_LANE)
        episodenode::streamRecord(db, i, bars_, long_lines_);
    for (uint16_t i = 0; i < held_.count(); ++i)
      fetch_.seed(held_.agentAt(i), held_.maxSeq(held_.agentAt(i)));
    link_gen_seen_ = ep.linkAppends();
    cut(true);                                          // boot: radios down, heap free
    cutBars(true);
  }

  // --- recv callback: copy only -------------------------------------------------------
  // Takes EVERY EPISODE toot, VECTOR included: its src is a peer that is on (heard_src_, one
  // slot; vectors repeat every <= 10 s, so an overwrite only delays). VECTOR stops there.
  void onToot(uint32_t src, const uint8_t* p, size_t len) {
    if (src && src != self_) heard_src_ = src;
    if (!p || !len) return;
    if (p[0] == EPISODEORDER_SUBOP_WANT) {
      semantic::Want w;
      if (semantic::decodeWant(p, len, w) && w.to == self_ && w.agent == self_ && src &&
          src != self_)
        wants_.push(src, w);
    } else if (p[0] == EPISODEORDER_SUBOP_DATA) {
      semantic::DataHdr h;
      const uint8_t* b;
      size_t n;
      if (semantic::decodeData(p, len, h, &b, &n)) in_.onData(h, b, n);
    } else if (p[0] == EPISODEDELIVERY_SUBOP_DONE) {
      semantic::Done d;
      if (semantic::decodeDone(p, len, d)) in_.onDone(d);
    }
  }

  // --- loop() -------------------------------------------------------------------------
  void service(uint32_t now, bool have_frame, uint64_t frame, int64_t pulse_now) {
    if (!db_) return;
    // Own link appends -> the author's lon -> seq map.
    if (ep_->linkAppends() != link_gen_seen_) {
      link_gen_seen_ = ep_->linkAppends();
      seqs_.add(ep_->lastLinkOrdinal(), ep_->lastLinkSeq());
    }
    const uint32_t h = heard_src_;
    if (h) {
      heard_src_ = 0;
      fetch_.heard(h, now);
    }
    serve(now);
    fetch(now);
    if (held_.count() >= EPISODEDELIVERY_HELD_QUOTA + EPISODEDELIVERY_HELD_SLACK &&
        (cut_fail_ms_ == 0 || now - cut_fail_ms_ >= EPISODEDELIVERY_CUT_RETRY_MS)) {
      if (!cut(false)) cut_fail_ms_ = now ? now : 1;
      else cut_fail_ms_ = 0;
    }
    if (have_frame) bar(frame, pulse_now);
  }

  void print(Print& out) const {
    out.printf("[deliver] held %u | fetched %lu dup %lu refused %lu broken %lu resumed %lu "
               "unanswered %lu empty %lu nomem %lu appendfail %lu | served %lu (empty %lu) of %lu want(s) | "
               "own link map %u | cuts %lu (fail %lu, early %lu, cap %u) | bars %u on flash, "
               "%lu written (fail %lu) | wantq drop %lu superseded %lu\n",
               (unsigned)held_.count(), (unsigned long)st_.fetched,
               (unsigned long)st_.duplicate, (unsigned long)st_.refused,
               (unsigned long)st_.broken, (unsigned long)st_.resumed,
               (unsigned long)st_.unanswered,
               (unsigned long)st_.empty, (unsigned long)st_.nomem,
               (unsigned long)st_.append_failed, (unsigned long)st_.served,
               (unsigned long)st_.served_empty, (unsigned long)st_.wants_heard,
               (unsigned)seqs_.count(), (unsigned long)st_.cuts,
               (unsigned long)st_.cut_failed, (unsigned long)st_.cut_early,
               (unsigned)semantic::heldHardCap(held_.authors(), hard_max_),
               (unsigned)bars_.count(), (unsigned long)st_.bars_written,
               (unsigned long)st_.bar_fail, (unsigned long)wants_.dropped(),
               (unsigned long)wants_.superseded());
  }
  const Stats& stats() const { return st_; }

 private:
  static void bootLine(void* ctx, const char* l) { ((Node*)ctx)->seqs_.line(l); }

  void sendWire(const uint8_t* b, size_t n) {
    if (send_ && n) send_(b, (uint8_t)n);
  }

  int findRecord(int16_t lat, int16_t lon) const {
    for (int i = 0; i < db_->recordCount(); ++i)
      if (db_->record(i).lat == lat && db_->record(i).lon == lon) return i;
    return -1;
  }

  // ---- the author ----
  void serve(uint32_t now) {
    if (serving_) {
      if (now - last_tx_ < EPISODEDELIVERY_SLICE_GAP_MS) return;
      last_tx_ = now;
      if (sent_ < total_) {
        uint8_t slice[EPISODEDELIVERY_SLICE];
        const size_t n = total_ - sent_ < EPISODEDELIVERY_SLICE ? total_ - sent_
                                                                : EPISODEDELIVERY_SLICE;
        if (db_->readBytes(span_off_ + sent_, slice, n) != n) { serving_ = false; return; }
        uint8_t b[208];
        const size_t m = semantic::encodeData(
            semantic::DataHdr{to_, self_, seq_, (uint16_t)total_, (uint16_t)sent_}, slice, n,
            b, sizeof(b));
        sendWire(b, m);
        sent_ += n;
        return;
      }
      uint8_t b[EPISODEDELIVERY_DONE_LEN];
      sendWire(b, semantic::encodeDone(semantic::Done{to_, self_, seq_, (uint16_t)total_}, b, sizeof(b)));
      ++st_.served;
      serving_ = false;
      return;
    }
    semantic::Want w;
    uint32_t who;
    if (!wants_.pop(&who, &w)) return;
    ++st_.wants_heard;
    if (w.tier != semantic::TIER_LINK) return;
    // The first own link episode in range that is STILL on flash (a fold may have cut it).
    uint32_t from = w.from_seq;
    for (int tries = 0; tries < 8; ++tries) {
      uint32_t seq;
      int16_t lon;
      if (!seqs_.firstInRange(from, w.to_seq, &seq, &lon)) break;
      if (w.off && seq != w.from_seq) break;            // the resumed episode is gone
      const int i = findRecord(SEMANTIC_EPISODE_LANE, lon);
      size_t off = 0, len = 0;
      if (i < 0 || !db_->recordSpan(i, off, len) || len == 0 || len > 0xFFFF) {
        seqs_.remove(lon);
        from = seq + 1;
        continue;
      }
      serving_ = true;
      to_ = who;
      seq_ = seq;
      span_off_ = off;
      total_ = len;
      sent_ = w.off < len ? w.off : 0;                  // a resume starts mid-episode
      last_tx_ = now - EPISODEDELIVERY_SLICE_GAP_MS;    // first slice on the next pass
      return;
    }
    // Nothing held in range (folded, or not a link seq): say so, so the cursor moves.
    uint8_t b[EPISODEDELIVERY_DONE_LEN];
    sendWire(b, semantic::encodeDone(semantic::Done{who, self_, w.to_seq ? w.to_seq : from},
                                     b, sizeof(b)));
    ++st_.served_empty;
  }

  // ---- the receiver ----
  void fetch(uint32_t now) {
    const semantic::Inflight::State s = in_.state();
    if (s == semantic::Inflight::IDLE) {
      semantic::Want w;
      if (!fetch_.next(*vc_, now, w)) return;
      buf_ = (uint8_t*)malloc(EPISODEDELIVERY_MAX_EPISODE);
      if (!buf_) { ++st_.nomem; fetch_.retry(w.agent, now); return; }
      in_.arm(self_, w.agent, buf_, EPISODEDELIVERY_MAX_EPISODE);
      uint8_t b[EPISODEDELIVERY_WANT_LEN];
      sendWire(b, semantic::encodeWant(w, b, sizeof(b)));   // to = agent = the author
      want_at_ = now;
      ++st_.wants_sent;
      return;
    }
    if (s == semantic::Inflight::WAITING) {
      if (now - want_at_ < EPISODEDELIVERY_TIMEOUT_MS) return;
      if (in_.started()) {                              // data came, the DONE did not
        resume(now);
        return;
      }
      ++st_.unanswered;
      fetch_.unanswered(in_.agent(), now);
      release();
      return;
    }
    if (s == semantic::Inflight::PARTIAL) {
      resume(now);
      return;
    }
    const uint32_t agent = in_.agent();
    if (s == semantic::Inflight::EMPTY) {
      ++st_.empty;
      fetch_.answered(agent, in_.through(), now);
    } else if (s == semantic::Inflight::BROKEN) {
      ++st_.broken;
      fetch_.retry(agent, now);
    } else {                                            // COMPLETE
      const uint32_t seq = in_.seq();
      if (held_.has(agent, seq)) {
        ++st_.duplicate;
        fetch_.answered(agent, seq, now);
      } else {
        const int16_t ord = held_.nextOrdinal();
        const size_t m = semantic::renderHeld((const char*)in_.bytes(), in_.length(), agent,
                                              seq, ord, ep_->scratch(), ep_->scratchCap());
        if (!m) {
          ++st_.refused;
          fetch_.answered(agent, seq, now);             // skip it: it will never check
        } else if (!db_->appendRecord(ep_->scratch(), m)) {
          ++st_.append_failed;
          fetch_.retry(agent, now);
        } else {
          held_.feed(ep_->scratch(), m);                // agent, seq, lon AND its bar
          ++st_.fetched;
          fetch_.answered(agent, seq, now);
        }
      }
    }
    release();
  }

  // Ask the author for the rest of the episode in flight, from the first missing byte.
  // Abandoned (cursor unmoved, retried later from scratch) after STALLED_RESUMES in a row
  // that brought nothing new.
  void resume(uint32_t now) {
    if (in_.length() > resume_got_) stalled_ = 0;
    else if (++stalled_ > EPISODEDELIVERY_STALLED_RESUMES) {
      ++st_.broken;
      fetch_.retry(in_.agent(), now);
      release();
      return;
    }
    resume_got_ = in_.length();
    const uint32_t agent = in_.agent(), seq = in_.seq();
    in_.resume();
    semantic::Want w{agent, agent, seq, seq, semantic::TIER_LINK, (uint16_t)resume_got_};
    uint8_t b[EPISODEDELIVERY_WANT_LEN];
    sendWire(b, semantic::encodeWant(w, b, sizeof(b)));
    want_at_ = now;
    ++st_.wants_sent;
    ++st_.resumed;
  }

  void release() {
    stalled_ = 0;
    resume_got_ = 0;
    in_.disarm();
    free(buf_);
    buf_ = nullptr;
  }

  bool cut(bool boot) {
    semantic::Cut cs[4];
    uint16_t covers = 0, early = 0;
    const uint8_t n = held_.cuts(cs, 4, boot, &covers, &bars_, &early,
                                 semantic::heldHardCap(held_.authors(), hard_max_));
    if (!n) return true;
    TtdbCut tc[4];
    for (uint8_t i = 0; i < n; ++i) tc[i] = TtdbCut{cs[i].lat, cs[i].lon_lo, cs[i].lon_hi};
    db_->clearRewriteErr();
    if (!db_->removeCuts(tc, n)) { ++st_.cut_failed; return false; }
    held_.cutDone(covers);
    st_.cut_early += early;
    ++st_.cuts;
    return true;
  }

  // The BAR lane's ring: QUOTA records, the oldest cut once SLACK more have landed.
  bool cutBars(bool boot) {
    semantic::Cut cs;
    uint16_t covers = 0;
    if (!bars_.cut(&cs, boot, &covers)) return true;
    TtdbCut tc{cs.lat, cs.lon_lo, cs.lon_hi};
    db_->clearRewriteErr();
    if (!db_->removeCuts(&tc, 1)) { ++st_.cut_failed; return false; }
    bars_.cutDone(covers);
    ++st_.cuts;
    return true;
  }

  // ---- the bar view ----
  // Bars n and n-1 are printed once per new bar; each is WRITTEN once, the first time it is
  // computed (a bar the node missed while off is written at its next boot, settled_ms says
  // how late).
  void bar(uint64_t frame, int64_t pulse_now) {
    const int64_t n = semantic::completeBar(pulse_now, frame, EPISODEDELIVERY_BAR_MS,
                                            EPISODEDELIVERY_BAR_SETTLE_MS);
    if (n < 1 || (n == last_bar_ && frame == last_frame_)) return;
    last_bar_ = n;
    last_frame_ = frame;
    for (int64_t k = n; k >= 1 && k >= n - 1; --k) printBar(frame, k, pulse_now);
    if (bars_.count() >= EPISODEDELIVERY_BAR_QUOTA + EPISODEDELIVERY_BAR_SLACK) cutBars(false);
  }

  void printBar(uint64_t frame, int64_t n, int64_t pulse_now) {
    semantic::Consolidator* c = new (std::nothrow) semantic::Consolidator();
    if (!c) { Serial.println("[bar] nomem"); return; }
    c->begin();
    semantic::BarView v(*c, frame, semantic::barLine(frame, EPISODEDELIVERY_BAR_MS, n - 1),
                        semantic::barLine(frame, EPISODEDELIVERY_BAR_MS, n), self_);
    for (int i = 0; i < db_->recordCount(); ++i) {
      const int16_t lat = db_->record(i).lat;
      if (lat == SEMANTIC_EPISODE_LANE || lat == EPISODEDELIVERY_HELD_LANE)
        episodenode::streamRecord(*db_, i, v, long_lines_);
    }
    v.finish();
    const semantic::BarDigest d = semantic::barDigest(*c);
    Serial.printf("[bar] frame %llu bar %lld: %u episode(s) (own %u, held %u) %u term(s) "
                  "digest 0x%08lx\n",
                  (unsigned long long)frame, (long long)n, (unsigned)(v.own() + v.held()),
                  (unsigned)v.own(), (unsigned)v.held(), (unsigned)d.terms,
                  (unsigned long)d.sum);
    if (!bars_.has(frame, n)) {
      const int16_t ord = bars_.nextOrdinal();
      const int64_t late = pulse_now - semantic::barLine(frame, EPISODEDELIVERY_BAR_MS, n);
      const size_t m = semantic::renderBar(ep_->scratch(), ep_->scratchCap(), ord, frame, n,
                                           v, d, late);
      if (m && db_->appendRecord(ep_->scratch(), m)) {
        bars_.appended(frame, n, ord);
        ++st_.bars_written;
      } else {
        ++st_.bar_fail;
      }
    }
    delete c;
  }

  Ttdb* db_ = nullptr;
  episodenode::Node* ep_ = nullptr;
  semantic::VectorClock* vc_ = nullptr;
  uint32_t self_ = 0;
  SendFn send_ = nullptr;

  semantic::SeqMap seqs_;
  semantic::HeldIndex held_;
  semantic::BarIndex bars_;
  semantic::Fetcher fetch_;
  semantic::Inflight in_;
  uint8_t* buf_ = nullptr;
  uint32_t want_at_ = 0;
  size_t resume_got_ = 0;
  uint8_t stalled_ = 0;

  semantic::WantQueue wants_;
  volatile uint32_t heard_src_ = 0;
  uint16_t hard_max_ = EPISODEDELIVERY_HELD_HARD_MAX;

  bool serving_ = false;
  uint32_t to_ = 0, seq_ = 0, last_tx_ = 0;
  size_t span_off_ = 0, total_ = 0, sent_ = 0;

  uint32_t link_gen_seen_ = 0, cut_fail_ms_ = 0, long_lines_ = 0;
  int64_t last_bar_ = -1;
  uint64_t last_frame_ = 0;
  Stats st_;
};

}  // namespace episodedelivery
