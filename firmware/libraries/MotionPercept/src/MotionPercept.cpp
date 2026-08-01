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

  // reset() is "throw this window away" — the sketch calls it when the lane is full
  // or the IMU drops out. Whatever closes next is NOT adjacent to whatever closed
  // last, so the chain breaks here. Pairing across the gap would assert a transition
  // over a window nobody measured. buildRecord() re-arms the chain deliberately,
  // after calling this.
  prev_valid_ = false;
  pending_ = false;
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

  // Reduce the window we just wrote to the numbers a transition needs, BEFORE reset()
  // clears the chain, then re-arm the chain with it as the new `after` candidate.
  Window cur;
  cur.moving = (permille >= 100);
  cur.synced = synced;
  cur.lane = (int16_t)lane_n;
  cur.n = n_;
  cur.permille = permille;
  cur.dev_mean_mg = devMeanMg();
  cur.dev_max_mg = dev_max_mg_;
  cur.moving_ms = moving_ms_;
  cur.window_ms = window_ms;
  cur.t_sec = t_sec;
  cur.t_ms = t_ms;

  const Window prev = prev_;
  const bool had_prev = prev_valid_;

  reset(now_ms);  // clears prev_valid_/pending_ — re-armed on the next three lines

  prev_ = cur;
  prev_valid_ = true;
  // The claim exists only where the two verdicts disagree. Equal verdicts are not a
  // transition, and writing one anyway would bury the real changes in noise.
  if (had_prev && prev.moving != cur.moving) {
    before_ = prev;
    pending_ = true;
  }
  return (size_t)m;
}

size_t Log::buildTransition(char* out, size_t cap, int lane_n, uint32_t node_id) {
  if (!pending_) return 0;
  pending_ = false;  // one write per change, success or not: never a second attempt

  const Window& b = before_;
  const Window& a = prev_;
  // Elapsed between the two windows' close stamps. Both come from the same clock on
  // the same node, so this is a real duration even when the fleet clock is unsynced —
  // `synced` on each half says whether it is comparable with another node's.
  const uint64_t dt_ms = (a.t_ms > b.t_ms) ? (a.t_ms - b.t_ms) : 0;

  // NOTE: the two `@PERCEPT:` lines are indented by two spaces ON PURPOSE. See the
  // header — an unindented '@' at line start IS a record header to Ttdb::begin(), and
  // this pair would index as two phantom (0,0) records.
  int m = snprintf(
      out, cap,
      "\n---\n\n@LAT%dLON%d | created:%lu | updated:%lu | "
      "relates:senses@LAT0LON0,derived_from@LAT95LON%d,derived_from@LAT95LON%d\n\n"
      "**TRANSITION** t_ms:%llu synced:%d node:0x%lx from:%s to:%s dt_ms:%llu\n"
      "  @PERCEPT:before state:%s t_ms:%llu window_ms:%lu n:%ld moving_permille:%ld "
      "dev_mean_mg:%ld dev_max_mg:%ld moving_ms:%lu lane:@LAT95LON%d\n"
      "  @PERCEPT:after state:%s t_ms:%llu window_ms:%lu n:%ld moving_permille:%ld "
      "dev_mean_mg:%ld dev_max_mg:%ld moving_ms:%lu lane:@LAT95LON%d\n"
      "**DELTA** edge:became d_permille:%ld d_dev_mean_mg:%ld d_dev_max_mg:%ld\n",
      MOTIONPERCEPT_TRANSITION_LANE, lane_n,
      (unsigned long)a.t_sec, (unsigned long)a.t_sec, (int)b.lane, (int)a.lane,
      (unsigned long long)a.t_ms, a.synced ? 1 : 0, (unsigned long)node_id,
      b.moving ? "moving" : "still", a.moving ? "moving" : "still",
      (unsigned long long)dt_ms,
      b.moving ? "moving" : "still", (unsigned long long)b.t_ms,
      (unsigned long)b.window_ms, (long)b.n, (long)b.permille,
      (long)b.dev_mean_mg, (long)b.dev_max_mg, (unsigned long)b.moving_ms, (int)b.lane,
      a.moving ? "moving" : "still", (unsigned long long)a.t_ms,
      (unsigned long)a.window_ms, (long)a.n, (long)a.permille,
      (long)a.dev_mean_mg, (long)a.dev_max_mg, (unsigned long)a.moving_ms, (int)a.lane,
      (long)(a.permille - b.permille), (long)(a.dev_mean_mg - b.dev_mean_mg),
      (long)(a.dev_max_mg - b.dev_max_mg));

  // A truncated pair is an orphan, which TTDB-RFC-0006 §7.1 calls an error rather than
  // partial data. Write nothing at all instead.
  if (m < 0 || (size_t)m >= cap) return 0;
  return (size_t)m;
}

}  // namespace motionpercept
