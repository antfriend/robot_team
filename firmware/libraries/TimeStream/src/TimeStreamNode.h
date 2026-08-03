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
    if (!e_.have() && now_ms >= TIMESTREAM_LISTEN_MS) {
      if (e_.origin(now_ms, esp_random())) owed_ = true;
    }

    refresh(now_ms);

    if (owed_) {
      owed_ = false;
      writeRecord();
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

  void writeRecord() {
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
    int n = 0;
    for (int i = 0; i < db_->recordCount(); ++i)
      if (db_->record(i).lat == TIMESTREAM_LANE) ++n;
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
