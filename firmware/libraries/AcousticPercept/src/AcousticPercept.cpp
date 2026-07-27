// AcousticPercept.cpp — see AcousticPercept.h. Portable; native-testable.
#include "AcousticPercept.h"
#include <stdio.h>
#include <string.h>

namespace acousticpercept {
namespace {

// Integer sqrt of a 64-bit value (no libm — see MotionPercept for the same reason).
uint32_t isqrt64(uint64_t sq) {
  if (sq == 0) return 0;
  uint64_t r = sq, prev = 0;
  while (r > 0xFFFFFFFFULL) r >>= 1;
  if (r == 0) r = 1;
  for (int i = 0; i < 32 && r != prev; ++i) {
    prev = r;
    r = (r + sq / r) / 2;
  }
  return (uint32_t)r;
}

}  // namespace

void Log::reset(uint32_t now_ms) {
  blocks_ = 0;
  rms_sum_ = 0;
  rms_max_ = 0;
  peak_ = 0;
  transients_ = 0;
  ambient_ = 0;
  loudest_t_ms_ = 0;
  loudest_rms_ = 0;
  window_start_ms_ = now_ms;
}

void Log::addBlock(const int16_t* samples, size_t n, uint64_t t_ms,
                   uint32_t now_ms) {
  (void)now_ms;
  if (!samples || n == 0) return;

  uint64_t sq = 0;
  int32_t pk = 0;
  for (size_t i = 0; i < n; ++i) {
    int32_t s = samples[i];
    sq += (uint64_t)((int64_t)s * s);
    int32_t a = s < 0 ? -s : s;
    if (a > pk) pk = a;
  }
  int32_t rms = (int32_t)isqrt64(sq / (uint64_t)n);

  blocks_++;
  rms_sum_ += (uint64_t)rms;
  if (rms > rms_max_) rms_max_ = rms;
  if (pk > peak_) peak_ = pk;

  // Transient test against the running ambient baseline — but only once the baseline
  // has settled, so the first blocks after boot can't all read as events.
  if (blocks_ > 4) {
    int32_t threshold = (int32_t)(((int64_t)ambient_ * ACOUSTICPERCEPT_TRANSIENT_MULT) / 8);
    if (threshold < ACOUSTICPERCEPT_TRANSIENT_FLOOR)
      threshold = ACOUSTICPERCEPT_TRANSIENT_FLOOR;
    if (rms > threshold) {
      transients_++;
      if (rms > loudest_rms_) {
        loudest_rms_ = rms;
        loudest_t_ms_ = t_ms;   // the TDoA datum: WHEN, on the fleet clock
      }
    }
  }

  // Exponential baseline (1/8 new). Deliberately slow so a bang lifts it barely at
  // all and a room's real ambient level is what the next block is judged against.
  ambient_ = ambient_ + (rms - ambient_) / 8;
}

bool Log::due(uint32_t now_ms) const {
  if (blocks_ == 0) return false;
  return (uint32_t)(now_ms - window_start_ms_) >= (uint32_t)ACOUSTICPERCEPT_FLUSH_MS;
}

int32_t Log::rmsMean() const {
  if (blocks_ == 0) return 0;
  return (int32_t)(rms_sum_ / (uint64_t)blocks_);
}

size_t Log::buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                        uint64_t t_ms, bool synced, uint32_t now_ms,
                        uint32_t sample_rate) {
  if (blocks_ == 0) {
    reset(now_ms);
    return 0;
  }
  uint32_t window_ms = now_ms - window_start_ms_;
  size_t w = 0;
  int m = snprintf(out + w, cap - w,
                   "\n---\n\n@LAT94LON%d | created:%lu | updated:%lu | "
                   "relates:hears@LAT0LON0\n\n"
                   "**ACOUSTICWIN** t_ms:%llu synced:%d window_ms:%lu blocks:%ld "
                   "rate:%lu\n"
                   "**ACOUSTIC** rms_mean:%ld rms_max:%ld peak:%ld transients:%ld\n",
                   lane_n, (unsigned long)t_sec, (unsigned long)t_sec,
                   (unsigned long long)t_ms, synced ? 1 : 0,
                   (unsigned long)window_ms, (long)blocks_,
                   (unsigned long)sample_rate, (long)rmsMean(), (long)rms_max_,
                   (long)peak_, (long)transients_);
  if (m < 0 || (size_t)m >= cap - w) {
    reset(now_ms);
    return 0;
  }
  w += (size_t)m;

  // The transient line is the whole point of the tier, so it is emitted separately
  // and only when there is one — an empty line would read as a heard event.
  if (transients_ > 0) {
    m = snprintf(out + w, cap - w, "**TRANSIENT** t_ms:%llu rms:%ld synced:%d\n",
                 (unsigned long long)loudest_t_ms_, (long)loudest_rms_,
                 synced ? 1 : 0);
    if (m > 0 && (size_t)m < cap - w) w += (size_t)m;
  }
  reset(now_ms);
  return w;
}

}  // namespace acousticpercept
