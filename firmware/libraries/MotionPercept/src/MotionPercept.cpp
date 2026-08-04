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

  // Same argument, one level up: a discarded window means the next record is not
  // adjacent to the last, so the run it would have extended has a hole in it. Folding
  // across that hole would let `windows_since_last` claim coverage of a window nobody
  // measured — the run-length equivalent of pairing a transition across a gap.
  breakRun();
}

void Log::breakRun() {
  run_open_ = false;
  run_state_ = false;
  run_lane_ = -1;
  run_len_ = 0;
  cov_windows_ = 0;
  cov_n_ = 0;
  cov_n_moving_ = 0;
  cov_dev_sum_mg_ = 0;
  cov_dev_max_mg_ = 0;
  cov_moving_ms_ = 0;
  cov_window_ms_ = 0;
  cov_first_t_ms_ = 0;
  cov_last_t_ms_ = 0;
  close_ = CLOSE_EMPTY;
  cover_lane_ = -1;
  run_offset_ = 0;
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
                        const timestream::Stamp& ts, uint32_t now_ms) {
  if (n_ == 0) {
    reset(now_ms);
    close_ = CLOSE_EMPTY;
    return 0;
  }
  const uint32_t window_ms = now_ms - window_start_ms_;
  const int permille = movingPermille();
  // The window's verdict. A handful of stray samples is noise, not a journey: the
  // window is only called `moving` when motion held for a tenth of it or more.
  const bool moving_now = (permille >= 100);

  // ------------------------------------------------------------------------
  // Write, or fold into the run in progress?
  // ------------------------------------------------------------------------
  // A CHANGE is never deferred: the whole point of the tier is the moment the verdict
  // flips, and @LAT93's paired record is written off the back of this decision. The
  // heartbeat exists only so an unchanging state is re-asserted before the run's length
  // grows past what MOTIONPERCEPT_MAX_RUN's arithmetic budgeted for.
  const bool first     = !run_open_;
  const bool changed   = run_open_ && (moving_now != run_state_);
  const bool heartbeat = run_open_ && !changed && (run_len_ >= MOTIONPERCEPT_MAX_RUN);
  const bool write     = first || changed || heartbeat;

  // Reduce this window to the numbers a transition and a run need, BEFORE reset()
  // clears either chain.
  Window cur;
  cur.moving = moving_now;
  cur.stamp = ts;
  cur.n = n_;
  cur.permille = permille;
  cur.dev_mean_mg = devMeanMg();
  cur.dev_max_mg = dev_max_mg_;
  cur.moving_ms = moving_ms_;
  cur.window_ms = window_ms;
  cur.t_sec = t_sec;

  size_t wrote = 0;
  if (write) {
    char stamp[64];
    if (!timestream::buildStamp(stamp, sizeof(stamp), ts)) {
      reset(now_ms);
      close_ = CLOSE_EMPTY;
      return 0;
    }
    // `windows_since_last` counts THIS window plus every one suppressed since the last
    // record, so 1 means adjacent. On the first record of a run chain there is no
    // previous record to measure from and it is 1 by definition, flagged `reason:first`.
    const int since = run_open_ ? run_len_ : 1;
    const char* reason = first ? "first" : (changed ? "changed" : "heartbeat");
    int m = snprintf(out, cap,
                     "\n---\n\n@LAT95LON%d | created:%lu | updated:%lu | "
                     "relates:senses@LAT0LON0\n\n"
                     "**MOTIONWIN** %s window_ms:%lu n:%ld\n"
                     "**MOTION** state:%s moving_permille:%d dev_mean_mg:%d "
                     "dev_max_mg:%ld moving_ms:%lu\n"
                     "**RUN** windows_since_last:%d reason:%s max_run:%d\n",
                     lane_n, (unsigned long)t_sec, (unsigned long)t_sec,
                     stamp,
                     (unsigned long)window_ms, (long)n_,
                     moving_now ? "moving" : "still", permille,
                     devMeanMg(), (long)dev_max_mg_, (unsigned long)moving_ms_,
                     since, reason, MOTIONPERCEPT_MAX_RUN);
    if (m < 0 || (size_t)m >= cap) {
      reset(now_ms);
      close_ = CLOSE_EMPTY;
      return 0;
    }
    wrote = (size_t)m;

    // The windows this record's predecessor spoke for but never itemised. Emitted only
    // when there were any, and summed over SAMPLES so the block reads as one long
    // window rather than a mean of means. Without this the lane understates how long
    // the node held a state, which is the statistic the tier exists to report.
    if (cov_windows_ > 0) {
      const int cov_permille =
          cov_n_ > 0 ? (int)((int64_t)cov_n_moving_ * 1000 / cov_n_) : 0;
      const int cov_dev_mean =
          cov_n_ > 0 ? (int)(cov_dev_sum_mg_ / (uint32_t)cov_n_) : 0;
      m = snprintf(out + wrote, cap - wrote,
                   "**COVERED** state:%s windows:%ld n:%ld window_ms:%lu "
                   "moving_permille:%d dev_mean_mg:%d dev_max_mg:%ld moving_ms:%lu "
                   "first_t_ms:%llu last_t_ms:%llu covered_by:@LAT95LON%d\n",
                   run_state_ ? "moving" : "still", (long)cov_windows_, (long)cov_n_,
                   (unsigned long)cov_window_ms_, cov_permille, cov_dev_mean,
                   (long)cov_dev_max_mg_, (unsigned long)cov_moving_ms_,
                   (unsigned long long)cov_first_t_ms_,
                   (unsigned long long)cov_last_t_ms_, run_lane_);
      // A record missing its COVERED block would silently claim `windows_since_last:N`
      // with no accounting for the N-1, which is exactly the dishonesty the block was
      // added to prevent. Write nothing rather than the head alone.
      if (m < 0 || (size_t)m >= cap - wrote) {
        reset(now_ms);
        close_ = CLOSE_EMPTY;
        return 0;
      }
      wrote += (size_t)m;
    }
    cur.lane = (int16_t)lane_n;   // this record speaks for its own window
    cur.run_offset = 0;
  } else {
    cur.lane = (int16_t)run_lane_;      // the open run's record speaks for it
    cur.run_offset = (int16_t)run_len_;
  }

  // ------------------------------------------------------------------------
  // Advance both chains across reset(), which clears them by design.
  // ------------------------------------------------------------------------
  const Window prev = prev_;
  const bool had_prev = prev_valid_;

  // The two raw accumulators the COVERED aggregate needs. Taken from the window itself
  // rather than reconstructed from its rounded `moving_permille` / `dev_mean_mg`: a
  // 30-window run would compound that rounding into the very statistic the block
  // exists to keep honest.
  const int32_t  cur_n_moving = n_moving_;
  const uint32_t cur_dev_sum  = dev_sum_mg_;

  // Snapshot the run so reset()'s breakRun() does not eat it. Kept explicit rather than
  // teaching reset() about exceptions: reset() means "throw this window away", and the
  // ONE caller that legitimately continues afterwards is right here.
  const bool     s_open  = run_open_;
  const bool     s_state = run_state_;
  const int      s_lane  = run_lane_;
  const int      s_len   = run_len_;
  const int32_t  s_cw    = cov_windows_;
  const int32_t  s_cn    = cov_n_;
  const int32_t  s_cnm   = cov_n_moving_;
  const uint32_t s_cds   = cov_dev_sum_mg_;
  const int32_t  s_cdm   = cov_dev_max_mg_;
  const uint32_t s_cmms  = cov_moving_ms_;
  const uint32_t s_cwms  = cov_window_ms_;
  const uint64_t s_cft   = cov_first_t_ms_;

  reset(now_ms);  // clears prev_valid_/pending_ AND the run — both re-armed below

  prev_ = cur;
  prev_valid_ = true;
  // The claim exists only where the two verdicts disagree. Equal verdicts are not a
  // transition, and writing one anyway would bury the real changes in noise.
  if (had_prev && prev.moving != cur.moving) {
    before_ = prev;
    pending_ = true;
  }

  if (write) {
    // A fresh run, with the record just rendered speaking for it. Its covered
    // accumulators start empty — breakRun() already zeroed them.
    run_open_ = true;
    run_state_ = moving_now;
    run_lane_ = lane_n;
    run_len_ = 1;
  } else {
    run_open_ = s_open;
    run_state_ = s_state;
    run_lane_ = s_lane;
    run_len_ = s_len + 1;
    cov_windows_ = s_cw + 1;
    cov_n_ = s_cn + cur.n;
    cov_n_moving_ = s_cnm + cur_n_moving;
    cov_dev_sum_mg_ = s_cds + cur_dev_sum;
    cov_dev_max_mg_ = (cur.dev_max_mg > s_cdm) ? cur.dev_max_mg : s_cdm;
    cov_moving_ms_ = s_cmms + cur.moving_ms;
    cov_window_ms_ = s_cwms + cur.window_ms;
    cov_first_t_ms_ = (s_cw == 0) ? cur.stamp.t_ms : s_cft;
    cov_last_t_ms_ = cur.stamp.t_ms;
  }

  close_ = write ? CLOSE_WRITTEN : CLOSE_COVERED;
  cover_lane_ = cur.lane;
  run_offset_ = cur.run_offset;
  return wrote;
}

size_t Log::buildTransition(char* out, size_t cap, int lane_n, uint32_t node_id) {
  if (!pending_) return 0;
  pending_ = false;  // one write per change, success or not: never a second attempt

  const Window& b = before_;
  const Window& a = prev_;
  // Elapsed between the two windows' close stamps. Both come from the same node, so
  // this is a real duration — UNLESS the node changed timelines between them. A stream
  // merge moves the clock forward by the offset it adopted, and that offset would land
  // in this subtraction and read as elapsed time that never happened. It is not
  // detectable from the numbers (a minute-long gap looks like a minute-long gap), so
  // the record says so instead: `dt_across_merge:1` means do not trust `dt_ms`.
  //
  // It is recoverable rather than lost: a merge only ever moves the clock FORWARD, so
  // dt_ms is an over-estimate by exactly the offset the @LAT90 STREAM-RECONCILED record
  // wrote down. A reader with both records can subtract it back out.
  const uint64_t at = a.stamp.t_ms, bt = b.stamp.t_ms;
  const uint64_t dt_ms = (at > bt) ? (at - bt) : 0;
  const bool across_merge = (a.stamp.stream_id != b.stamp.stream_id);

  char stamp[64];
  if (!timestream::buildStamp(stamp, sizeof(stamp), a.stamp)) return 0;

  // NOTE: the two `@PERCEPT:` lines are indented by two spaces ON PURPOSE. See the
  // header — an unindented '@' at line start IS a record header to Ttdb::begin(), and
  // this pair would index as two phantom (0,0) records.
  //
  // The `lane:` fields carry `@LAT95LON<n>+<k>` since the lane became change-triggered.
  // The `before` half is now USUALLY a suppressed window — a run of `still` ends when
  // motion starts, and only the run's first window has a record of its own — so citing
  // `lane` alone would point at a record describing a different window. `+k` says which
  // window of that run this was; the run's length is written down when it closes.
  // The `derived_from` EDGES stay plain ordinals: an edge must resolve to a record that
  // exists, and the covering record does.
  int m = snprintf(
      out, cap,
      "\n---\n\n@LAT%dLON%d | created:%lu | updated:%lu | "
      "relates:senses@LAT0LON0,derived_from@LAT95LON%d,derived_from@LAT95LON%d\n\n"
      "**TRANSITION** %s node:0x%lx from:%s to:%s dt_ms:%llu dt_across_merge:%d\n"
      "  @PERCEPT:before state:%s t_ms:%llu window_ms:%lu n:%ld moving_permille:%ld "
      "dev_mean_mg:%ld dev_max_mg:%ld moving_ms:%lu lane:@LAT95LON%d+%d\n"
      "  @PERCEPT:after state:%s t_ms:%llu window_ms:%lu n:%ld moving_permille:%ld "
      "dev_mean_mg:%ld dev_max_mg:%ld moving_ms:%lu lane:@LAT95LON%d+%d\n"
      "**DELTA** edge:became d_permille:%ld d_dev_mean_mg:%ld d_dev_max_mg:%ld\n",
      MOTIONPERCEPT_TRANSITION_LANE, lane_n,
      (unsigned long)a.t_sec, (unsigned long)a.t_sec, (int)b.lane, (int)a.lane,
      stamp, (unsigned long)node_id,
      b.moving ? "moving" : "still", a.moving ? "moving" : "still",
      (unsigned long long)dt_ms, across_merge ? 1 : 0,
      b.moving ? "moving" : "still", (unsigned long long)bt,
      (unsigned long)b.window_ms, (long)b.n, (long)b.permille,
      (long)b.dev_mean_mg, (long)b.dev_max_mg, (unsigned long)b.moving_ms,
      (int)b.lane, (int)b.run_offset,
      a.moving ? "moving" : "still", (unsigned long long)at,
      (unsigned long)a.window_ms, (long)a.n, (long)a.permille,
      (long)a.dev_mean_mg, (long)a.dev_max_mg, (unsigned long)a.moving_ms,
      (int)a.lane, (int)a.run_offset,
      (long)(a.permille - b.permille), (long)(a.dev_mean_mg - b.dev_mean_mg),
      (long)(a.dev_max_mg - b.dev_max_mg));

  // A truncated pair is an orphan, which TTDB-RFC-0006 §7.1 calls an error rather than
  // partial data. Write nothing at all instead.
  if (m < 0 || (size_t)m >= cap) return 0;
  return (size_t)m;
}

}  // namespace motionpercept
