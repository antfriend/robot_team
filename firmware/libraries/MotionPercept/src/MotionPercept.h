// MotionPercept.h — SP0 MOTION tier: "was this node standing still?" (@LAT95).
//
// The third percept tier, and the first one that is about the OBSERVER rather than
// the observed. LinkPercept says how strongly two nodes hear each other;
// EntityPercept says what external things they both see. Both silently assume the
// node did not move while the window accumulated — and the 2026-07-07 walking range
// test proved that assumption can fail badly: a node carried between stations fuses
// four different places into one distance, which is exactly why `companion.py
// proximity` had to grow a `--last N` recency filter.
//
// This tier makes that assumption CHECKABLE instead of hoped-for. An accelerometer
// (the Cardputer ADV's BMI270) is sampled a few times a second; per window the log
// renders one @LAT95 record saying how much of the window the node spent in motion.
// A window marked `state:moving` is evidence about a node that was somewhere else
// for part of it — the consolidator can down-weight or drop it. A `state:still`
// window is a positive claim: this node was anchored while it listened.
//
// It is also the roaming instrument's own state: the fleet's handhelds are the nodes
// that move, so "moving" vs "anchored" is a first-class thing for them to report.
//
// Same discipline as its siblings: fixed RAM, integer math, no per-sample flash write,
// portable (no Arduino dependency) so the stats and the record format CAN be pinned by
// a native test the way LinkPercept's are — though that test is **not written yet**;
// this tier has so far been verified only on hardware (companion.md §6, 2026-07-27).
// The sketch supplies the IMU read and the Ttdb::appendRecord.
#pragma once
#include <stdint.h>
#include <stddef.h>

#ifndef MOTIONPERCEPT_FLUSH_MS
// Motion changes fast but the CLAIM is about a whole window, so it matches the
// link-percept window (60 s) — one @LAT95 record per @LAT97 record, pairable by time.
#define MOTIONPERCEPT_FLUSH_MS 60000
#endif
#ifndef MOTIONPERCEPT_MAX_LANE
#define MOTIONPERCEPT_MAX_LANE 48       // lane cap, like @LAT96/@LAT97
#endif
#ifndef MOTIONPERCEPT_MOVING_MG
// Deviation of |acceleration| from 1 g, in milli-g, above which a sample counts as
// motion. Hand tremor on a held device is ~20-40 mg; a walking stride peaks in the
// hundreds. 60 mg keeps "held still in a hand" on the still side of the line.
#define MOTIONPERCEPT_MOVING_MG 60
#endif

namespace motionpercept {

class Log {
 public:
  Log() { reset(0); }

  // Fold in one accelerometer sample, in milli-g per axis. The statistic is the
  // deviation of the vector magnitude from 1 g, which is gravity-invariant: it does
  // not care how the device is oriented, only whether it is being accelerated.
  // `now_ms` lets the log attribute elapsed time to moving vs still.
  void add(int ax_mg, int ay_mg, int az_mg, uint32_t now_ms);

  // True when the window elapsed and at least one sample landed in it.
  bool due(uint32_t now_ms) const;

  int samples() const { return n_; }
  // Tenths of a percent of samples that exceeded the motion threshold (0..1000).
  int movingPermille() const;
  int devMeanMg() const;
  int devMaxMg() const { return dev_max_mg_; }
  // Best current answer to "is this node anchored right now?" — true when no sample
  // has crossed the threshold recently. Cheap enough to read every loop (the sketch
  // reports it in STATUS so the fleet knows which nodes are holding still).
  bool moving(uint32_t now_ms, uint32_t recent_ms = 3000) const;

  // Render a complete TTDB record block and start a new window:
  //   \n---\n\n@LAT95LON<lane_n> | created:<t_sec> | ... | relates:senses@LAT0LON0
  //   \n\n**MOTIONWIN** t_ms:.. synced:<0|1> window_ms:.. n:..
  //   \n**MOTION** state:<still|moving> moving_permille:.. dev_mean_mg:..
  //     dev_max_mg:.. moving_ms:..
  // Returns bytes written, or 0 if the window was empty (still resets).
  size_t buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                     uint64_t t_ms, bool synced, uint32_t now_ms);

  void reset(uint32_t now_ms);

 private:
  int32_t n_;             // samples this window
  int32_t n_moving_;      // samples over the threshold
  uint32_t dev_sum_mg_;   // sum of |mag - 1g| for the mean
  int32_t dev_max_mg_;
  uint32_t moving_ms_;    // elapsed time attributed to motion
  uint32_t last_sample_ms_;
  uint32_t last_moving_ms_;   // when motion was last seen (0 = never this window)
  uint32_t window_start_ms_;
};

}  // namespace motionpercept
