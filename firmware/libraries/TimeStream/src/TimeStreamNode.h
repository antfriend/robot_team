// TimeStreamNode.h — the Arduino-side glue that puts a node on the team time stream.
//
// TimeStream.h is deliberately portable (no Arduino, native-testable, which is where
// the merge rule is proven). This header is the other half: the small amount of
// per-sketch wiring every node needs, written ONCE instead of six times.
//
// It exists because the wiring is not quite trivial, and getting it subtly wrong on
// one of six boards would be invisible — the node would simply keep its own timeline
// and look fine. Three things it gets right on every board:
//
//  1. **The recv callback never touches the Engine.** ESP-NOW receive runs in the WiFi
//     task; `Engine::mono()` MUTATES its 49.7-day wrap accounting, and a torn write to
//     that would move the node's clock by seven weeks. So the callback only queues,
//     and `service()` — called from loop() — is the sole mutator. STATUS / GPS /
//     TIME_RESP replies built in the callback read `clockOffsetMs()`, a plain scalar.
//  2. **Anchors queue in a RING, not one slot.** With four peers a single slot always
//     holds the LAST talker's anchor, and the stream that ought to win the merge may
//     never be the last to speak.
//  3. **One @LAT90 record per settled state**, not one per hop through it: the queue
//     is drained first, the record is written after.
//
// Wiring a sketch is five calls:
//     gTs.begin(kNodeId, &gDb, millis());              // setup()
//     gTs.service(now);                                // FIRST thing in loop()
//     gTs.onHello(t, millis());                        // in the HELLO case
//     gTs.onTimeSync(epoch_ms, recv_ms, t.src_node_id);// in the TIME_SYNC case
//     n = gTs.helloPayload(body, sizeof(body), now);   // at the HELLO emit
#pragma once
#include <Arduino.h>
#include <Toot.h>
#include <TTDB.h>
#include "TimeStream.h"

#ifndef TIMESTREAM_MAX_LANE
// The @LAT90 lane records TIMELINE CHANGES, not time. A settled fleet writes an ORIGIN
// or an ADOPTED and then nothing for hours, so this is a guard against a pathology
// (two nodes flapping between streams), not a routine ceiling like the percept lanes'.
// If it is ever reached, that IS the finding — do not raise it, go and look.
#define TIMESTREAM_MAX_LANE 16
#endif

#ifndef TIMESTREAM_ANCHOR_QUEUE
#define TIMESTREAM_ANCHOR_QUEUE 6
#endif

namespace timestream {

class Node {
 public:
  // `db` may be null on a node with no TTDB: the stream still runs and still stamps
  // toots, it just has nowhere to write its @LAT90 log. Better than refusing to
  // participate — the timeline is worth more than the record of how it was joined.
  void begin(uint32_t node_id, Ttdb* db, uint32_t now_ms) {
    node_id_ = node_id;
    db_ = db;
    begin_ms_ = now_ms;      // the listen window starts HERE, when the radio is up
    e_.begin(node_id, now_ms);
    head_ = tail_ = 0;
    owed_ = false;
    sync_pending_ = false;
    refresh(now_ms);
  }

  // From the radio/serial recv path, on any HELLO. Cheap: a copy and an index bump.
  void onHello(const toot::Toot& t, uint32_t recv_ms) {
    if (t.type != toot::HELLO || t.payload_len < ANCHOR_LEN) return;
    Anchor a;
    if (!parseAnchor(t.payload, t.payload_len, a)) return;
    const uint8_t h = head_;
    q_[h] = a;
    src_[h] = t.src_node_id;
    // Sampled HERE, not at drain time: the receiver adopts (stream_ms - recv_ms), so
    // any staleness in recv_ms lands directly in its clock as an error.
    recv_[h] = recv_ms;
    head_ = (uint8_t)((h + 1) % TIMESTREAM_ANCHOR_QUEUE);
  }

  // From the TIME_SYNC handler. The laptop supplies the DATE; it does not supply the
  // timeline, because the fleet already has one. Latched here, applied in service().
  void onTimeSync(uint64_t epoch_ms, uint32_t recv_ms, uint32_t from_node) {
    sync_epoch_ = epoch_ms;
    sync_recv_ = recv_ms;
    sync_from_ = from_node;
    sync_pending_ = true;
  }

  // Once per loop(), FIRST — before anything reads a clock. Drains the queue, starts a
  // stream if nobody else has one, refreshes the caches, writes at most one record.
  void service(uint32_t now_ms) {
    while (tail_ != head_) {
      const uint8_t i = tail_;
      Event ev = e_.onAnchor(q_[i], src_[i], recv_[i]);
      tail_ = (uint8_t)((i + 1) % TIMESTREAM_ANCHOR_QUEUE);
      if (ev != EV_NONE && ev != EV_SLEW) owed_ = true;
    }

    if (sync_pending_) {
      sync_pending_ = false;
      // esp_random() is what makes a REBOOT a new stream rather than a reused id with
      // a clock reset to 0 (TimeStream.h::origin) — it only bites when this is also
      // the call that starts the stream.
      Event ev = e_.anchorWall(sync_epoch_, sync_recv_, sync_from_, esp_random());
      if (ev != EV_NONE) owed_ = true;
    }

    // Heard nothing worth joining in TIMESTREAM_LISTEN_MS: start one and say so.
    //
    // ⚠ MEASURED FROM begin(), NOT FROM BOOT — and the difference is not cosmetic.
    // A first pass at this compared `now_ms` (i.e. millis()) against the window
    // directly, which silently assumes setup() is short. On the Cardputer setup()
    // takes OVER SIX SECONDS (BLE + WiFi + codec + display), so millis() was already
    // past the window on the very first loop pass: the node originated a stream
    // having never once listened with its radio up, then reconciled onto its peer's
    // a moment later — TWO @LAT90 records for a reboot that should have written
    // none. Observed on hardware 2026-08-03 (`[stream] origin` immediately followed
    // by `[stream] reconciled ... offset=3956818ms`).
    // pulse::Engine has always done it this way (`now_ms - boot_ms_`); this did not,
    // and that one difference is what turned a quiet rejoin into a fork-and-merge.
    if (!e_.have() && (uint32_t)(now_ms - begin_ms_) >= TIMESTREAM_LISTEN_MS) {
      if (e_.origin(now_ms, esp_random())) owed_ = true;
    }

    refresh(now_ms);

    if (owed_) {
      owed_ = false;
      writeRecord(now_ms);
    }

    // A held ORIGIN that has now earned its record — either it survived the settle
    // window, or something reached flash stamped with it. See originDue().
    if (origin_held_ && db_ &&
        originDue(origin_held_ms_, now_ms, origin_held_records_,
                  db_->recordCount())) {
      origin_held_ = false;
      Serial.printf("[stream] origin 0x%08lx kept (%s) — writing it now\n",
                    (unsigned long)held_.new_id,
                    db_->recordCount() > origin_held_records_
                        ? "a record was stamped with it" : "it settled");
      append(held_);
    }
  }

  // The HELLO payload. Sampled at call time on purpose — see onHello().
  size_t helloPayload(uint8_t* out, size_t cap, uint32_t now_ms) {
    Anchor a;
    if (!e_.fill(a, now_ms)) return 0;   // no stream: say nothing, don't claim id 0
    return buildAnchor(out, cap, a);
  }

  // --- what the rest of the sketch reads (all callback-safe scalars) ---------
  const Stamp& stamp() const { return stamp_; }      // the per-record time triplet
  uint32_t wallSec() const { return wall_sec_; }     // Unix seconds, 0 if no date
  bool wall() const { return wall_; }                // the old `gSynced`, honestly named
  int64_t clockOffsetMs() const { return clock_off_; }
  int64_t nowEpochMs() const { return (int64_t)millis() + clock_off_; }
  uint32_t streamId() const { return stamp_.stream_id; }
  Engine& engine() { return e_; }

 private:
  void refresh(uint32_t now_ms) {
    stamp_.t_ms = e_.nowMs(now_ms);
    stamp_.stream_id = e_.streamId();
    stamp_.wall = e_.wall();
    wall_ = e_.wall();
    wall_sec_ = e_.wallSec(now_ms);
    clock_off_ = wall_ ? (int64_t)e_.unixMs(now_ms) - (int64_t)now_ms : 0;
  }

  void writeRecord(uint32_t now_ms) {
    const Transition& tr = e_.last();
    if (tr.ev == EV_NONE || tr.ev == EV_SLEW) return;
    Serial.printf("[stream] %s stream=0x%08lx t_ms=%llu wall=%d from=0x%lx "
                  "offset=%lldms\n",
                  eventName(tr.ev), (unsigned long)tr.new_id,
                  (unsigned long long)tr.new_ms, tr.wall ? 1 : 0,
                  (unsigned long)tr.from_node, (long long)tr.offset_ms);
    if (tr.wall_conflict_ms)
      Serial.printf("[stream] ⚠ WALL ANCHORS DISAGREE by %lldms — two sources, or a "
                    "stale anchor carried across a merge\n",
                    (long long)tr.wall_conflict_ms);
    if (!db_) return;

    // --- the ORIGIN hold (TIMESTREAM_ORIGIN_SETTLE_MS) ------------------------
    // A brand-new stream has not proved it is a state rather than a hop, so its
    // record waits. Everything else is written as it always was.
    if (tr.ev == EV_ORIGIN) {
      held_ = tr;                       // COPY: e_.last() is overwritten by the next event
      origin_held_ = true;
      origin_held_ms_ = now_ms;
      origin_held_records_ = db_->recordCount();
      Serial.printf("[stream] origin 0x%08lx HELD — not written until it survives "
                    "%lums or something is stamped with it\n",
                    (unsigned long)tr.new_id,
                    (unsigned long)TIMESTREAM_ORIGIN_SETTLE_MS);
      return;
    }
    // Any other transition while an origin is held resolves it. Moving to a DIFFERENT
    // stream means the held one was abandoned before it was ever a settled state — the
    // defect this hold exists to stop — so it is dropped and never written. Nothing on
    // flash can reference it: had anything been stamped with it, service() would have
    // released the hold first (originDue's record-count arm).
    if (origin_held_) {
      if (tr.new_id != held_.new_id) {
        Serial.printf("[stream] origin 0x%08lx ABANDONED after %lums for stream "
                      "0x%08lx — never a settled state, so no record is written "
                      "(this is the @LAT%d growth fix, not a lost event)\n",
                      (unsigned long)held_.new_id,
                      (unsigned long)(now_ms - origin_held_ms_),
                      (unsigned long)tr.new_id, TIMESTREAM_LANE);
        origin_held_ = false;
      } else {
        // Same stream, new fact about it (an anchor arriving). The ORIGIN has to land
        // FIRST or the lane explains the anchor before the stream it anchors.
        origin_held_ = false;
        append(held_);
      }
    }

    append(tr);
  }

  // The write itself: dedup against the lane, respect the cap, append. Split out of
  // writeRecord() because a HELD origin is appended later, from service(), long after
  // its transition passed through — and it must go through exactly this path.
  void append(const Transition& tr) {
    if (!db_) return;

    // ONE pass over the lane answers both questions: how full is it, and has it already
    // explained this stream? Reading bodies is file I/O, but a stream event happens at
    // boot and at a merge — never per frame — so this is nowhere near the per-frame
    // read that cost 767 ms/repaint in the edgesAt defect.
    int n = 0;
    bool named = false, anchored = false;
    // A @LAT90 record's header line plus its verb line is ~180 B, and both ` stream:`
    // and ` wall:` sit on the verb line, so a prefix read is enough — the REMAP,
    // WALL and PROVENANCE lines below it carry nothing this decision needs.
    char body[320];
    for (int i = 0; i < db_->recordCount(); ++i) {
      if (db_->record(i).lat != TIMESTREAM_LANE) continue;
      ++n;
      size_t off = 0, len = 0;
      if (!db_->recordSpan(i, off, len)) continue;
      const size_t want = len < sizeof(body) ? len : sizeof(body);
      const size_t got = db_->readBytes(off, (uint8_t*)body, want);
      if (!recordNamesStream(body, got, tr.new_id)) continue;
      named = true;
      if (recordIsWallAnchored(body, got)) anchored = true;
    }

    // Say nothing new, write nothing — but SAY that on serial. A suppression nobody
    // prints is how this lane would start lying about what the node did.
    if (recordIsRedundant(tr, named, anchored)) {
      Serial.printf("[stream] %s adds nothing: @LAT%d already explains stream 0x%08lx "
                    "— no record written (the node still rejoined; only the log line "
                    "is deduped)\n",
                    eventName(tr.ev), TIMESTREAM_LANE, (unsigned long)tr.new_id);
      return;
    }

    if (n >= TIMESTREAM_MAX_LANE) {
      Serial.printf("[stream] @LAT%d lane FULL at %d — the timeline is flapping, not "
                    "settling. Go and look; do not raise the cap.\n",
                    TIMESTREAM_LANE, n);
      return;
    }
    char rec[TIMESTREAM_BUF];
    size_t m = buildStreamRecord(rec, sizeof(rec), n, tr, node_id_, wall_sec_);
    if (!m || !db_->appendRecord(rec, m))
      Serial.println("[stream] appendRecord FAILED");
  }

  Engine e_;
  Ttdb* db_ = nullptr;
  uint32_t node_id_ = 0;
  uint32_t begin_ms_ = 0;

  // The held ORIGIN (TIMESTREAM_ORIGIN_SETTLE_MS). `held_` is a COPY, not a reference
  // into the Engine: e_.last() is overwritten by the very next transition, which in
  // the abandonment case is the one that arrives moments later.
  Transition held_;
  bool origin_held_ = false;
  uint32_t origin_held_ms_ = 0;
  int origin_held_records_ = 0;

  Anchor q_[TIMESTREAM_ANCHOR_QUEUE];
  uint32_t src_[TIMESTREAM_ANCHOR_QUEUE] = {0};
  uint32_t recv_[TIMESTREAM_ANCHOR_QUEUE] = {0};
  volatile uint8_t head_ = 0;   // written by the recv callback
  volatile uint8_t tail_ = 0;   // read by loop()

  volatile bool sync_pending_ = false;
  uint64_t sync_epoch_ = 0;
  uint32_t sync_recv_ = 0;
  uint32_t sync_from_ = 0;

  bool owed_ = false;
  Stamp stamp_;
  bool wall_ = false;
  uint32_t wall_sec_ = 0;
  int64_t clock_off_ = 0;
};

}  // namespace timestream
