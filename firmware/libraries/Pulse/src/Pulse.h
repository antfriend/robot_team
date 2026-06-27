// Pulse.h — TTN-RFC-0010 fleet pulse: shared time-base + conductor election.
//
// The band keeps time from a shared "pulse clock" (millis() + an adopted offset),
// not from a per-beat message. The first node up conducts; joiners adopt its chart
// and fall into phase; the lowest live id keeps the baton. Beacons are emitted
// rarely (drift-paced) plus on-join — never per beat. This engine is transport-
// agnostic: the sketch decodes/encodes PULSE toots (Toot.h) and renders the beat on
// whatever instrument the node has. See RFCs/TTN-RFC-0010-Fleet-Pulse.md.
#pragma once
#include <stdint.h>

namespace pulse {

#ifndef PULSE_DEFAULT_BEAT_MS
#define PULSE_DEFAULT_BEAT_MS 1000      // ~1 Hz heartbeat (60 BPM); the tempo
#endif
#ifndef PULSE_DEFAULT_METER
#define PULSE_DEFAULT_METER 4           // beats per bar
#endif
#ifndef PULSE_LISTEN_WINDOW_MS
#define PULSE_LISTEN_WINDOW_MS 3000     // cold-start: hear no PULSE this long -> conduct
#endif
#ifndef PULSE_RESYNC_PERIOD_MS
#define PULSE_RESYNC_PERIOD_MS 30000    // steady-state beacon cadence (§5 ceiling-safe)
#endif
#ifndef PULSE_CONDUCTOR_TIMEOUT_MS
#define PULSE_CONDUCTOR_TIMEOUT_MS 90000  // 3 missed beacons -> consider handoff
#endif
#ifndef PULSE_TAKEOVER_STAGGER_MS
#define PULSE_TAKEOVER_STAGGER_MS 10    // per-id extra wait at handoff so lowest id wins
#endif
#ifndef PULSE_STEPS_PER_BEAT
#define PULSE_STEPS_PER_BEAT 4          // sixteenth-note sequencer resolution (Score.h)
#endif

// The chart: the four numbers (plus owner/revision) that define the grid. Mirrors
// the PULSE payload (Toot.h buildPulse/parsePulse).
struct Chart {
  uint32_t conductor_id = 0;
  uint32_t era = 0;
  uint64_t downbeat_epoch = 0;          // band-epoch ms of beat 0
  uint16_t beat_period_ms = PULSE_DEFAULT_BEAT_MS;
  uint8_t  meter_beats = PULSE_DEFAULT_METER;
  uint8_t  flags = 0;
};

class Engine {
 public:
  // node_id is this node's logical id (lower id wins the baton). now_ms = millis().
  void begin(uint32_t node_id, uint32_t now_ms);

  // Evaluate a received PULSE. recv_ms = millis() sampled at receipt (the offset
  // adopted is conductor_epoch - recv_ms, so its residual is just the transit delay).
  void onBeacon(const Chart& c, uint64_t conductor_epoch, uint32_t recv_ms);

  // A new neighbor was heard (HELLO/first toot from a src). If we conduct, schedule
  // an immediate beacon so the joiner locks within a round trip (§4.2).
  void noteNeighbor(uint32_t now_ms);

  // Drive election + beacon scheduling. Returns true if a beacon should be emitted
  // now; fills `out` (chart) and `out_conductor_epoch` (= pulseNow) for the sketch
  // to encode with toot::buildPulse.
  bool update(uint32_t now_ms, Chart& out, uint64_t& out_conductor_epoch);

  // Beat-boundary detector. Returns true once per new beat; sets beat_in_bar
  // (0..meter-1, 0 = downbeat) and the monotonic beat_count. Call every loop().
  bool tick(uint32_t now_ms, uint8_t& beat_in_bar, uint32_t& beat_count);

  // Read the current phase WITHOUT advancing the tick detector (for telemetry):
  // beat_in_bar, ms-into-the-beat, and the monotonic beat_count. False if not yet
  // playing (no chart, or before beat 0).
  bool phaseNow(uint32_t now_ms, uint8_t& beat_in_bar, uint16_t& phase_ms,
                uint32_t& beat_count) const;

  // Sub-beat sequencer step detector (PULSE_STEPS_PER_BEAT per beat). Returns true once
  // per new step; sets step_in_phrase (0..phrase_steps-1, the loop position for a
  // Score::Phrase) and the absolute monotonic step_count. Call every loop() to drive a
  // part. Independent of tick() — a node may use either or both.
  bool stepTick(uint32_t now_ms, uint16_t phrase_steps, uint16_t& step_in_phrase,
                uint32_t& step_count);

  bool playing() const { return have_chart_; }
  bool conductor() const { return am_conductor_; }
  const Chart& chart() const { return chart_; }
  int64_t offsetMs() const { return offset_ms_; }
  int64_t pulseNow(uint32_t now_ms) const { return (int64_t)now_ms + offset_ms_; }

 private:
  static bool better(const Chart& a, const Chart& b);  // a strictly preferred over b
  void selfAppoint(uint32_t now_ms, bool takeover);

  uint32_t node_id_ = 0;
  Chart chart_;
  bool have_chart_ = false;
  bool am_conductor_ = false;
  int64_t offset_ms_ = 0;
  uint32_t boot_ms_ = 0;
  uint32_t last_beacon_rx_ms_ = 0;      // when we last heard our conductor (or beat)
  uint32_t next_beacon_tx_ms_ = 0;      // when (as conductor) to emit next
  uint32_t last_beat_count_ = 0xFFFFFFFFu;
  uint32_t last_step_count_ = 0xFFFFFFFFu;
  bool fastlock_ = false;               // pending on-join beacon
};

}  // namespace pulse
