// MotionPercept.cpp — see MotionPercept.h. Portable; native-testable.
#include "MotionPercept.h"
#include <stdio.h>
#include <string.h>

namespace motionpercept {
namespace {

// Integer magnitude of a 3-vector, in the same units as the inputs. Uses a 64-bit
// sum (a 16 g sample squares to ~2.6e8 per axis) and an integer Newton sqrt so the
// library stays free of libm — it runs on nodes where float printf is a luxury.
uint32_t magnitude(int32_t x, int32_t y, int32_t z) {
  uint64_t sq = (uint64_t)((int64_t)x * x + (int64_t)y * y + (int64_t)z * z);
  if (sq == 0) return 0;
  uint64_t r = sq, prev = 0;
  // Seed near the answer, then iterate; converges in a handful of rounds.
  while (r > 0xFFFFFFFFULL) r >>= 1;
  if (r == 0) r = 1;
  for (int i = 0; i < 24 && r != prev; ++i) {
    prev = r;
    r = (r + sq / r) / 2;
  }
  return (uint32_t)r;
}

const int32_t ONE_G_MG = 1000;

}  // namespace

void Log::reset(uint32_t now_ms) {
  n_ = 0;
  n_moving_ = 0;
  dev_sum_mg_ = 0;
  dev_max_mg_ = 0;
  moving_ms_ = 0;
  last_sample_ms_ = now_ms;
  last_moving_ms_ = 0;
  window_start_ms_ = now_ms;
}

void Log::add(int ax_mg, int ay_mg, int az_mg, uint32_t now_ms) {
  int32_t mag = (int32_t)magnitude(ax_mg, ay_mg, az_mg);
  int32_t dev = mag - ONE_G_MG;
  if (dev < 0) dev = -dev;

  // Time since the previous sample is charged to moving or still. Guard against a
  // long gap (a blocked loop, a reset window) so one stall can't dominate a window.
  uint32_t dt = now_ms - last_sample_ms_;
  if (dt > 500) dt = 500;
  last_sample_ms_ = now_ms;

  n_++;
  dev_sum_mg_ += (uint32_t)dev;
  if (dev > dev_max_mg_) dev_max_mg_ = dev;
  if (dev >= MOTIONPERCEPT_MOVING_MG) {
    n_moving_++;
    moving_ms_ += dt;
    last_moving_ms_ = now_ms ? now_ms : 1;   // 0 is the "never" sentinel
  }
}

bool Log::due(uint32_t now_ms) const {
  if (n_ == 0) return false;
  return (uint32_t)(now_ms - window_start_ms_) >= (uint32_t)MOTIONPERCEPT_FLUSH_MS;
}

int Log::movingPermille() const {
  if (n_ == 0) return 0;
  return (int)((int64_t)n_moving_ * 1000 / n_);
}

int Log::devMeanMg() const {
  if (n_ == 0) return 0;
  return (int)(dev_sum_mg_ / (uint32_t)n_);
}

bool Log::moving(uint32_t now_ms, uint32_t recent_ms) const {
  if (last_moving_ms_ == 0) return false;
  return (uint32_t)(now_ms - last_moving_ms_) <= recent_ms;
}

size_t Log::buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                        uint64_t t_ms, bool synced, uint32_t now_ms) {
  if (n_ == 0) {
    reset(now_ms);
    return 0;
  }
  uint32_t window_ms = now_ms - window_start_ms_;
  int permille = movingPermille();
  // The window's verdict. A handful of stray samples is noise, not a journey: the
  // window is only called `moving` when motion held for a tenth of it or more.
  const char* state = permille >= 100 ? "moving" : "still";
  int m = snprintf(out, cap,
                   "\n---\n\n@LAT95LON%d | created:%lu | updated:%lu | "
                   "relates:senses@LAT0LON0\n\n"
                   "**MOTIONWIN** t_ms:%llu synced:%d window_ms:%lu n:%ld\n"
                   "**MOTION** state:%s moving_permille:%d dev_mean_mg:%d "
                   "dev_max_mg:%ld moving_ms:%lu\n",
                   lane_n, (unsigned long)t_sec, (unsigned long)t_sec,
                   (unsigned long long)t_ms, synced ? 1 : 0,
                   (unsigned long)window_ms, (long)n_, state, permille,
                   devMeanMg(), (long)dev_max_mg_, (unsigned long)moving_ms_);
  if (m < 0 || (size_t)m >= cap) {
    reset(now_ms);
    return 0;
  }
  reset(now_ms);
  return (size_t)m;
}

}  // namespace motionpercept
