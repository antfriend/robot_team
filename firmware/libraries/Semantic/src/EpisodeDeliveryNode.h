// EpisodeDeliveryNode.h — the Arduino glue for C4 stage 2 (docs/design/episode-order.md §7):
// serve this node's LINK episodes to peers that WANT them, fetch theirs into @LAT105, and
// print the BAR VIEW once per bar line. The portable half is EpisodeDelivery.h.
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
           unanswered = 0, empty = 0, append_failed = 0, nomem = 0;
  uint32_t wants_heard = 0, served = 0, served_empty = 0, cuts = 0, cut_failed = 0;
};

class Node {
 public:
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
    for (uint16_t i = 0; i < held_.count(); ++i)
      fetch_.seed(held_.agentAt(i), held_.maxSeq(held_.agentAt(i)));
    link_gen_seen_ = ep.linkAppends();
    cut(true);                                          // boot: radios down, heap free
  }

  // --- recv callback: copy only -------------------------------------------------------
  void onToot(uint32_t src, const uint8_t* p, size_t len) {
    if (!p || !len) return;
    if (p[0] == EPISODEORDER_SUBOP_WANT) {
      semantic::Want w;
      if (semantic::decodeWant(p, len, w) && w.to == self_ && w.agent == self_ && src &&
          src != self_ && !want_pending_) {
        want_ = w;
        want_src_ = src;
        want_pending_ = true;                           // last: loop reads after this
      }
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
    out.printf("[deliver] held %u | fetched %lu dup %lu refused %lu broken %lu unanswered %lu "
               "empty %lu nomem %lu appendfail %lu | served %lu (empty %lu) of %lu want(s) | "
               "own link map %u | cuts %lu (fail %lu)\n",
               (unsigned)held_.count(), (unsigned long)st_.fetched,
               (unsigned long)st_.duplicate, (unsigned long)st_.refused,
               (unsigned long)st_.broken, (unsigned long)st_.unanswered,
               (unsigned long)st_.empty, (unsigned long)st_.nomem,
               (unsigned long)st_.append_failed, (unsigned long)st_.served,
               (unsigned long)st_.served_empty, (unsigned long)st_.wants_heard,
               (unsigned)seqs_.count(), (unsigned long)st_.cuts,
               (unsigned long)st_.cut_failed);
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
      sendWire(b, semantic::encodeDone(semantic::Done{to_, self_, seq_}, b, sizeof(b)));
      ++st_.served;
      serving_ = false;
      return;
    }
    if (!want_pending_) return;
    const semantic::Want w = want_;
    const uint32_t who = want_src_;
    want_pending_ = false;
    ++st_.wants_heard;
    if (w.tier != semantic::TIER_LINK) return;
    // The first own link episode in range that is STILL on flash (a fold may have cut it).
    uint32_t from = w.from_seq;
    for (int tries = 0; tries < 8; ++tries) {
      uint32_t seq;
      int16_t lon;
      if (!seqs_.firstInRange(from, w.to_seq, &seq, &lon)) break;
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
      sent_ = 0;
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
      ++st_.unanswered;
      fetch_.unanswered(in_.agent(), now);
      release();
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
          held_.appended(agent, seq, ord);
          ++st_.fetched;
          fetch_.answered(agent, seq, now);
        }
      }
    }
    release();
  }

  void release() {
    in_.disarm();
    free(buf_);
    buf_ = nullptr;
  }

  bool cut(bool boot) {
    semantic::Cut cs[4];
    uint16_t covers = 0;
    const uint8_t n = held_.cuts(cs, 4, boot, &covers);
    if (!n) return true;
    TtdbCut tc[4];
    for (uint8_t i = 0; i < n; ++i) tc[i] = TtdbCut{cs[i].lat, cs[i].lon_lo, cs[i].lon_hi};
    db_->clearRewriteErr();
    if (!db_->removeCuts(tc, n)) { ++st_.cut_failed; return false; }
    held_.cutDone(covers);
    ++st_.cuts;
    return true;
  }

  // ---- the bar view ----
  void bar(uint64_t frame, int64_t pulse_now) {
    const int64_t n = semantic::completeBar(pulse_now, frame, EPISODEDELIVERY_BAR_MS,
                                            EPISODEDELIVERY_BAR_SETTLE_MS);
    if (n < 1 || (n == last_bar_ && frame == last_frame_)) return;
    last_bar_ = n;
    last_frame_ = frame;
    for (int64_t k = n; k >= 1 && k >= n - 1; --k) printBar(frame, k);
  }

  void printBar(uint64_t frame, int64_t n) {
    semantic::Consolidator* c = new (std::nothrow) semantic::Consolidator();
    if (!c) { Serial.println("[bar] nomem"); return; }
    c->begin();
    semantic::BarView v(*c, frame, semantic::barLine(frame, EPISODEDELIVERY_BAR_MS, n - 1),
                        semantic::barLine(frame, EPISODEDELIVERY_BAR_MS, n));
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
    delete c;
  }

  Ttdb* db_ = nullptr;
  episodenode::Node* ep_ = nullptr;
  semantic::VectorClock* vc_ = nullptr;
  uint32_t self_ = 0;
  SendFn send_ = nullptr;

  semantic::SeqMap seqs_;
  semantic::HeldIndex held_;
  semantic::Fetcher fetch_;
  semantic::Inflight in_;
  uint8_t* buf_ = nullptr;
  uint32_t want_at_ = 0;

  volatile bool want_pending_ = false;
  semantic::Want want_ = {0, 0, 0, 0, 0};
  uint32_t want_src_ = 0;

  bool serving_ = false;
  uint32_t to_ = 0, seq_ = 0, last_tx_ = 0;
  size_t span_off_ = 0, total_ = 0, sent_ = 0;

  uint32_t link_gen_seen_ = 0, cut_fail_ms_ = 0, long_lines_ = 0;
  int64_t last_bar_ = -1;
  uint64_t last_frame_ = 0;
  Stats st_;
};

}  // namespace episodedelivery
