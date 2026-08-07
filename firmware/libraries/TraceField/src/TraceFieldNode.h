// TraceFieldNode.h — the Arduino glue for a TraceField. ONE copy, both handhelds.
//
// Same shape as TimeStreamNode.h and LaneGenNode.h, and for the same reason: the portable
// arithmetic lives in TraceField.cpp where a native test can reach it, and everything that
// needs `Serial` or a radio callback lives here.
//
// ⚠ THE RECV CALLBACK MUST NEVER TOUCH `Field`. `merge()` mutates 16 strengths and 16
// timestamps; a HELLO arriving mid-`buildDigest` would ship a half-merged field, and a
// deposit racing a merge can lose either. So the callback only COPIES 18 bytes into a
// ring, and `service()` — called from loop() — is the sole mutator. This is exactly the
// rule `TimeStreamNode` follows for anchors, where a torn write moved a node's clock by
// seven weeks; here it would only cost a wrong note, but the rule is cheaper to keep than
// to reason about each time.
//
// WHERE THE CELL COMES FROM, AND WHY IT IS THE POINT: the sketch deposits at the pulse's
// CURRENT STEP. So a sound at step 6 raises cell 6, which is voiced at step 6 of every
// later bar — the field records the RHYTHM of what happened, on the grid the whole fleet
// already agrees on, and then plays it back until it fades. Tap a pattern and the fleet
// keeps it for a half-life. That is the deposit-medium-readback loop with nothing in the
// middle addressing anybody.
#pragma once
#include <Arduino.h>
#include "TraceField.h"

#ifndef TRACEFIELD_QUEUE
#define TRACEFIELD_QUEUE 6
#endif

class TraceFieldNode {
 public:
  explicit TraceFieldNode(uint32_t half_life_ms = TRACEFIELD_HALF_LIFE_MS)
      : f_(half_life_ms) {}

  // ---- callback side: copy only, never merge -------------------------------------
  // Safe to call from an ESP-NOW recv callback. `p` points at the digest (the sketch
  // does the offset arithmetic past the time-stream anchor, so this library needs no
  // dependency on TimeStream).
  void queueDigest(const uint8_t* p, size_t n) {
    if (!p || n < tracefield::DIGEST_LEN) return;
    if (p[0] != tracefield::DIGEST_MAGIC) return;      // cheap reject before the copy
    const uint8_t h = head_;
    for (size_t i = 0; i < tracefield::DIGEST_LEN; ++i) q_[h][i] = p[i];
    head_ = (uint8_t)((h + 1) % TRACEFIELD_QUEUE);
    if (head_ == tail_) tail_ = (uint8_t)((tail_ + 1) % TRACEFIELD_QUEUE);  // drop oldest
  }

  // ---- loop side: the only mutator ------------------------------------------------
  // Drains the queue. Returns cells raised this pass (0 = nothing new, the normal case).
  uint8_t service(uint32_t now_ms) {
    uint8_t raised = 0;
    while (tail_ != head_) {
      raised = (uint8_t)(raised + f_.merge(q_[tail_], tracefield::DIGEST_LEN, now_ms));
      tail_ = (uint8_t)((tail_ + 1) % TRACEFIELD_QUEUE);
    }
    if (raised) {
      // Change-only logging. A digest arrives every 2 s per peer and says nothing new
      // almost every time; printing each one would bury the interesting event and cost
      // more CDC time than the merge itself.
      Serial.printf("[field] merged peer trace: %u cell(s) raised, energy %u\n",
                    raised, f_.energy(now_ms));
    }
    return raised;
  }

  // Deposit at the pulse step where it happened.
  void depositAt(uint8_t step, uint8_t amount, uint32_t now_ms) {
    f_.deposit((uint8_t)(step % tracefield::CELLS), amount, now_ms);
  }

  // Append our field to a HELLO body already holding the anchor. Returns bytes added.
  size_t helloAppend(uint8_t* p, size_t cap, uint32_t now_ms) const {
    return f_.buildDigest(p, cap, now_ms);
  }

  // What to sound at `step`, or 0 for silence. `amp_out` is 0..255 scaled from strength.
  uint16_t voiceAt(uint8_t step, uint32_t now_ms, uint8_t& amp_out) const {
    const uint8_t s = f_.strengthAt((uint8_t)(step % tracefield::CELLS), now_ms);
    if (s < TRACEFIELD_VOICE_FLOOR) { amp_out = 0; return 0; }
    amp_out = s;
    return tracefield::pitchFor((uint8_t)(step % tracefield::CELLS));
  }

  const tracefield::Field& field() const { return f_; }
  tracefield::Field& field() { return f_; }

 private:
  tracefield::Field f_;
  uint8_t q_[TRACEFIELD_QUEUE][tracefield::DIGEST_LEN] = {{0}};
  uint8_t head_ = 0, tail_ = 0;
};
