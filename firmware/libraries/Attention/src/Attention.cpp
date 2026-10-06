// Attention.cpp — see Attention.h. Portable: no Arduino dependency.
#include "Attention.h"
#include <math.h>

namespace attention {

const char* modalityName(uint8_t m) {
  switch (m) {
    case MOD_MOTION:    return "motion";
    case MOD_SOUND:     return "sound";
    case MOD_NEIGHBOUR: return "neighbour";
    case MOD_IDLE:      return "idle";
    default:            return "?";
  }
}

uint8_t decayed(uint8_t v, uint32_t t0_ms, uint32_t now_ms, uint32_t half_life_ms) {
  if (!v || !half_life_ms) return 0;
  const uint32_t dt = now_ms - t0_ms;          // unsigned: a "future" t0 is a huge dt
  const uint32_t whole = dt / half_life_ms;
  if (whole >= 8) return 0;
  const uint32_t frac = dt % half_life_ms;
  const uint32_t base = (uint32_t)v >> whole;
  return (uint8_t)(base - (base * frac) / (2u * half_life_ms));
}

// ---- Arbiter ---------------------------------------------------------------------

uint8_t Arbiter::epsAt(uint8_t m, uint32_t now_ms) const {
  if (m >= MOD_COUNT) return 0;
  return decayed(s_[m].eps, s_[m].t, now_ms, ATTENTION_HALF_LIFE_MS);
}

bool Arbiter::observe(uint8_t m, uint8_t sal, uint8_t conf, uint32_t now_ms,
                      uint32_t detail) {
  if (m >= MOD_COUNT) return false;
  const uint8_t e = eps(sal, conf);
  if (e == 0 || e < epsAt(m, now_ms)) return false;
  Slot& s = s_[m];
  s.eps = e; s.sal = sal; s.conf = conf; s.t = now_ms; s.detail = detail;
  return true;
}

uint16_t Arbiter::total(uint32_t now_ms) const {
  uint16_t t = 0;
  for (uint8_t m = 0; m < MOD_COUNT; ++m) t = (uint16_t)(t + epsAt(m, now_ms));
  return t;
}

bool Arbiter::tick(uint32_t now_ms) {
  uint8_t e[MOD_COUNT];
  uint8_t best = 0;
  for (uint8_t m = 0; m < MOD_COUNT; ++m) {
    e[m] = epsAt(m, now_ms);
    if (e[m] > e[best]) best = m;              // strict: ties go to the lower index
  }
  const bool bestActive = e[best] >= ATTENTION_IDLE_EPS;

  uint8_t next = winner_;
  if (winner_ == MOD_IDLE) {
    if (bestActive) next = best;               // idle never dwells: the face yields at once
  } else if (now_ms - since_ms_ >= ATTENTION_DWELL_MS) {
    const uint8_t inc = e[winner_];
    if (inc < ATTENTION_IDLE_EPS) {
      next = bestActive ? best : MOD_IDLE;     // the incumbent faded: no margin owed to it
    } else if (best != winner_ &&
               (uint32_t)e[best] * 100u > (uint32_t)inc * (100u + ATTENTION_MARGIN_PCT)) {
      next = best;
    }
  }
  if (next == winner_) return false;
  winner_ = next;
  since_ms_ = now_ms;
  return true;
}

// ---- Novelty ---------------------------------------------------------------------

uint32_t Novelty::lateAfter(uint32_t typ) const {
  const uint32_t t = typ * ATTENTION_LATE_MULT;
  return t > ATTENTION_LATE_MIN_MS ? t : ATTENTION_LATE_MIN_MS;
}

uint32_t Novelty::typicalGap(uint32_t peer) const {
  for (const Peer& q : p_) if (q.used && q.node == peer) return q.typ;
  return 0;
}

uint8_t Novelty::heard(uint32_t peer, uint32_t now_ms, Event& ev, uint32_t& gap_ms) {
  ev = EV_NONE; gap_ms = 0;
  if (!peer) return 0;
  Peer* slot = nullptr;
  for (Peer& q : p_) if (q.used && q.node == peer) { slot = &q; break; }
  if (!slot) {
    // A new neighbour. Take a free slot, else evict the longest-unheard (the same rule
    // Social's table uses: nothing is evicted for age, only for space).
    for (Peer& q : p_) if (!q.used) { slot = &q; break; }
    if (!slot) {
      slot = &p_[0];
      for (Peer& q : p_) if (now_ms - q.last > now_ms - slot->last) slot = &q;
    }
    *slot = Peer();
    slot->used = true; slot->node = peer; slot->last = now_ms;
    slot->typ = 2000;                          // a HELLO period until it teaches us better
    ev = EV_NEW;
    return ATTENTION_SAL_NEW;
  }
  const uint32_t gap = now_ms - slot->last;
  const uint32_t late = lateAfter(slot->typ);
  slot->last = now_ms;
  if (slot->late || gap > late) {
    // It came back. Salience grows with how long it was gone, measured in its own
    // threshold: just past late = 128, three thresholds or more = 255.
    slot->late = false;
    ev = EV_RETURNED; gap_ms = gap;
    const uint32_t over = gap > late ? gap - late : 0;
    uint32_t s = 128u + (127u * over) / (2u * late);
    return (uint8_t)(s > 255u ? 255u : s);
  }
  // Routine. But only an ON-TIME arrival (within 2x) teaches the baseline: a gap just
  // under `late` taught it too in the first cut, and two dropped HELLOs moved the
  // threshold far enough that the next 7 s reboot read as routine (native test, §5).
  if (gap > 2u * slot->typ) return 0;
  int32_t typ = (int32_t)slot->typ + ((int32_t)gap - (int32_t)slot->typ) / 8;
  if (typ < 100) typ = 100;
  slot->typ = (uint32_t)typ;
  return 0;
}

uint8_t Novelty::quiet(uint32_t now_ms, uint32_t& peer, uint32_t& gap_ms) {
  for (Peer& q : p_) {
    if (!q.used || q.late) continue;
    const uint32_t gap = now_ms - q.last;
    if (gap > lateAfter(q.typ)) {
      q.late = true;
      peer = q.node; gap_ms = gap;
      return ATTENTION_SAL_QUIET;
    }
  }
  return 0;
}

// ---- MotionSalience --------------------------------------------------------------

static uint8_t ramp(int v, int floor, int span) {
  if (v <= floor) return 0;
  const int s = ((v - floor) * 255) / span;
  return (uint8_t)(s > 255 ? 255 : s);
}

uint8_t MotionSalience::feed(int ax, int ay, int az) {
  const float x = (float)ax, y = (float)ay, z = (float)az;
  if (!primed_) {                              // boot pose is the baseline, not news
    primed_ = true;
    fx_ = sx_ = x; fy_ = sy_ = y; fz_ = sz_ = z;
  }
  fx_ += (x - fx_) * 0.10f; fy_ += (y - fy_) * 0.10f; fz_ += (z - fz_) * 0.10f;
  sx_ += (fx_ - sx_) * 0.02f; sy_ += (fy_ - sy_) * 0.02f; sz_ += (fz_ - sz_) * 0.02f;
  const float dx = fx_ - sx_, dy = fy_ - sy_, dz = fz_ - sz_;
  tilt_mg_ = (int)sqrtf(dx * dx + dy * dy + dz * dz);
  shake_mg_ = (int)fabsf(sqrtf(x * x + y * y + z * z) - 1000.0f);
  const uint8_t a = ramp(tilt_mg_, ATTENTION_TILT_FLOOR_MG, ATTENTION_TILT_SPAN_MG);
  const uint8_t b = ramp(shake_mg_, ATTENTION_SHAKE_FLOOR_MG, ATTENTION_SHAKE_SPAN_MG);
  return a > b ? a : b;
}

}  // namespace attention
