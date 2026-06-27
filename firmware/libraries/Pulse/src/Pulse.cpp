// Pulse.cpp — TTN-RFC-0010 fleet pulse engine. See Pulse.h.
#include "Pulse.h"

namespace pulse {

void Engine::begin(uint32_t node_id, uint32_t now_ms) {
  node_id_ = node_id;
  boot_ms_ = now_ms;
  last_beacon_rx_ms_ = now_ms;
  have_chart_ = false;
  am_conductor_ = false;
  offset_ms_ = 0;
  last_beat_count_ = 0xFFFFFFFFu;
  last_step_count_ = 0xFFFFFFFFu;
  fastlock_ = false;
}

// A is strictly preferred over B: higher era wins; on a tie, lower conductor id.
bool Engine::better(const Chart& a, const Chart& b) {
  if (a.era != b.era) return a.era > b.era;
  return a.conductor_id < b.conductor_id;
}

void Engine::onBeacon(const Chart& c, uint64_t conductor_epoch, uint32_t recv_ms) {
  // Never re-adopt our own echo (e.g. relayed back): it would shift our clock by a
  // round trip. As conductor, ignore beacons carrying our id unless they out-era us.
  if (c.conductor_id == node_id_ && am_conductor_ && c.era <= chart_.era) return;

  const bool from_current = have_chart_ && c.conductor_id == chart_.conductor_id;
  bool adopt = false;
  if (!have_chart_) adopt = true;            // first chart heard: lock to it
  else if (from_current && c.era >= chart_.era) adopt = true;  // routine correction
  else if (better(c, chart_)) adopt = true;  // a better conductor: yield to it

  if (!adopt) return;
  chart_ = c;
  offset_ms_ = (int64_t)conductor_epoch - (int64_t)recv_ms;
  have_chart_ = true;
  last_beacon_rx_ms_ = recv_ms;
  am_conductor_ = (c.conductor_id == node_id_);
}

void Engine::noteNeighbor(uint32_t now_ms) {
  (void)now_ms;
  if (am_conductor_) fastlock_ = true;
}

void Engine::selfAppoint(uint32_t now_ms, bool takeover) {
  if (!takeover) {
    // Fresh start: our own millis() is the band epoch (offset 0); place the downbeat
    // at the next beat boundary so beat 0 starts cleanly in the near future.
    offset_ms_ = 0;
    chart_.beat_period_ms = PULSE_DEFAULT_BEAT_MS;
    chart_.meter_beats = PULSE_DEFAULT_METER;
    chart_.flags = 0;
    int64_t pn = (int64_t)now_ms;  // == pulseNow (offset 0)
    chart_.downbeat_epoch =
        (uint64_t)(pn - (pn % chart_.beat_period_ms) + chart_.beat_period_ms);
    chart_.era = 1;
    last_beat_count_ = 0xFFFFFFFFu;
  } else {
    // Handoff: keep the offset + downbeat + tempo so the beat does NOT lurch; only
    // the timekeeper changes. Bump era so every follower prefers us over the old one.
    chart_.era += 1;
  }
  chart_.conductor_id = node_id_;
  have_chart_ = true;
  am_conductor_ = true;
  next_beacon_tx_ms_ = now_ms;   // emit immediately on taking the baton
  last_beacon_rx_ms_ = now_ms;
}

bool Engine::update(uint32_t now_ms, Chart& out, uint64_t& out_conductor_epoch) {
  if (!have_chart_) {
    if (now_ms - boot_ms_ >= PULSE_LISTEN_WINDOW_MS) selfAppoint(now_ms, false);
    else return false;
  }

  // Conductor loss -> a follower takes over after a timeout staggered by id so the
  // lowest id grabs the baton first; higher-id candidates then adopt its era+1 beacon.
  if (!am_conductor_) {
    uint32_t timeout =
        PULSE_CONDUCTOR_TIMEOUT_MS + node_id_ * PULSE_TAKEOVER_STAGGER_MS;
    if (now_ms - last_beacon_rx_ms_ >= timeout) selfAppoint(now_ms, true);
  }

  if (am_conductor_ &&
      (fastlock_ || (int32_t)(now_ms - next_beacon_tx_ms_) >= 0)) {
    fastlock_ = false;
    next_beacon_tx_ms_ = now_ms + PULSE_RESYNC_PERIOD_MS;
    last_beacon_rx_ms_ = now_ms;     // our own beacon counts as "heard"
    out = chart_;
    out_conductor_epoch = (uint64_t)pulseNow(now_ms);
    return true;
  }
  return false;
}

bool Engine::tick(uint32_t now_ms, uint8_t& beat_in_bar, uint32_t& beat_count) {
  if (!have_chart_) return false;
  int64_t pn = pulseNow(now_ms);
  if (pn < (int64_t)chart_.downbeat_epoch) return false;  // before beat 0
  uint32_t bc =
      (uint32_t)((uint64_t)(pn - (int64_t)chart_.downbeat_epoch) / chart_.beat_period_ms);
  if (bc == last_beat_count_) return false;
  last_beat_count_ = bc;
  beat_count = bc;
  beat_in_bar = (uint8_t)(bc % chart_.meter_beats);
  return true;
}

bool Engine::phaseNow(uint32_t now_ms, uint8_t& beat_in_bar, uint16_t& phase_ms,
                      uint32_t& beat_count) const {
  if (!have_chart_) return false;
  int64_t pn = pulseNow(now_ms);
  if (pn < (int64_t)chart_.downbeat_epoch) return false;
  uint64_t ticks = (uint64_t)(pn - (int64_t)chart_.downbeat_epoch);
  beat_count = (uint32_t)(ticks / chart_.beat_period_ms);
  phase_ms = (uint16_t)(ticks % chart_.beat_period_ms);
  beat_in_bar = (uint8_t)(beat_count % chart_.meter_beats);
  return true;
}

bool Engine::stepTick(uint32_t now_ms, uint16_t phrase_steps,
                      uint16_t& step_in_phrase, uint32_t& step_count) {
  if (!have_chart_) return false;
  int64_t pn = pulseNow(now_ms);
  if (pn < (int64_t)chart_.downbeat_epoch) return false;
  uint32_t step_ms = chart_.beat_period_ms / PULSE_STEPS_PER_BEAT;
  if (step_ms == 0) step_ms = 1;
  uint32_t s = (uint32_t)((uint64_t)(pn - (int64_t)chart_.downbeat_epoch) / step_ms);
  if (s == last_step_count_) return false;
  last_step_count_ = s;
  step_count = s;
  step_in_phrase = phrase_steps ? (uint16_t)(s % phrase_steps) : 0;
  return true;
}

}  // namespace pulse
