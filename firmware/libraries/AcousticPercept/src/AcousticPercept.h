// AcousticPercept.h — SP0 ACOUSTIC tier: what the fleet HEARS (@LAT94).
//
// The fourth percept tier, and the first non-radio one. Every tier so far measures
// electromagnetic amplitude, and the 2026-07-10 garden run found that amplitude is
// the problem: outdoors, among ground-level nodes and vegetation, RSSI is
// shadowing-limited, not distance-limited, so it decorrelated from truth. Sound is a
// different physics with a different failure mode — it travels at 343 m/s, which is
// slow enough that a fleet synchronized to ~10 ms can, in principle, measure a TIME
// DIFFERENCE of arrival rather than an amplitude (ttn-semantic-positioning.md
// Phase 3). At 343 m/s, 10 ms of sync error is ~3.4 m of range error: coarse, but
// bounded by clock quality rather than by foliage, and it gets better exactly as the
// time-sync gets better instead of degrading with the environment.
//
// This log is the instrument, not the solver. The sketch feeds it blocks of PCM from
// the microphone; per window it renders one @LAT94 record: the ambient level, and —
// the part that matters for TDoA — the count of impulsive transients and the
// timestamp of the loudest one on the fleet-synced clock. Two nodes that log the same
// clap at different t_ms have measured something about their separation. Nothing on
// the node interprets that; consolidation is the companion's job, as ever.
//
// Ambient level is useful on its own as a second entity-style tier: rooms have sound
// signatures, and two nodes in the same room hear the same machine hum.
//
// Portable (no Arduino dependency), fixed RAM, integer math, no per-block flash
// write — the same discipline as LinkPercept / EntityPercept / MotionPercept. Like
// MotionPercept, its native test is **not written yet**: this tier has so far been
// verified only on hardware (FLEET.md §6, 2026-07-27).
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <TimeStream.h>   // the shared time stamp every record carries

#ifndef ACOUSTICPERCEPT_FLUSH_MS
#define ACOUSTICPERCEPT_FLUSH_MS 60000   // one window per link-percept window
#endif
#ifndef ACOUSTICPERCEPT_TRANSIENT_MULT
// A block counts as a transient when its RMS exceeds this multiple (in eighths) of
// the running ambient RMS — 24/8 = 3x. Relative, not absolute, so it adapts to a
// quiet room or a noisy yard without a per-site threshold.
#define ACOUSTICPERCEPT_TRANSIENT_MULT 24
#endif
#ifndef ACOUSTICPERCEPT_TRANSIENT_FLOOR
// ...but never fire below this absolute RMS (16-bit units), or a silent room makes
// every faint rustle a "transient".
#define ACOUSTICPERCEPT_TRANSIENT_FLOOR 900
#endif

#ifndef ACOUSTICPERCEPT_RECORD_BUF
// Buffer buildRecord() needs. Here, not in a sketch, because a native test cannot call
// into a .ino ([[render-buffers-belong-in-libraries]]); pinned by tests/test_episode.cpp
// against a record rendered with every field at its widest. ⚠ An undersized buffer does
// not fail the record: buildRecord DROPS the **TRANSIENT** line — the TDoA datum, the
// tier's whole point — and returns the rest as if nothing happened. Measured widest: 337 B
// (every counter at full width would add ~35 B more), so the sketch's old `char rec[400]`
// was adequate; 512 is headroom for a field added later, not a fix.
#define ACOUSTICPERCEPT_RECORD_BUF 512
#endif

namespace acousticpercept {

class Log {
 public:
  Log() { reset(0); }

  // Fold in one block of 16-bit mono PCM. `t_ms` is the block's timestamp on the
  // best clock the node has — the TEAM TIME STREAM's clock whenever the node is on a
  // stream, else local millis(). This is what makes a transient comparable ACROSS
  // nodes, so pass the stream value whenever there is one and make sure the same
  // stream id reaches buildRecord: an instant is worthless without the clock it was
  // read from. `now_ms` is local millis() for window bookkeeping.
  // `self` = the node's own speaker was sounding when this block was captured (Phase S0,
  // docs/design/cardputer-sensorium.md §7). Such a block is FULLY EXPLAINED: it is counted
  // (self_blocks) but is never a transient, never the loudest-transient datum, and never
  // feeds the ambient baseline, so a clap right after a beep is judged against the room,
  // not against the beep. Our own voice in the TDoA datum would correlate against itself.
  void addBlock(const int16_t* samples, size_t n, uint64_t t_ms, uint32_t now_ms,
                bool self = false);

  bool due(uint32_t now_ms) const;

  int32_t blocks() const { return blocks_; }
  int32_t rmsMean() const;
  int32_t rmsMax() const { return rms_max_; }
  int32_t peak() const { return peak_; }
  int32_t transients() const { return transients_; }
  int32_t selfBlocks() const { return self_blocks_; }
  // Diagnostics: the last HEARD block's RMS and the baseline it was judged against.
  int32_t lastRms() const { return last_rms_; }
  int32_t ambient() const { return ambient_; }
  // Timestamp + level of the loudest transient this window (0 if none) — the TDoA
  // datum: the same real-world event, timestamped independently by several nodes.
  uint64_t loudestTMs() const { return loudest_t_ms_; }
  int32_t loudestRms() const { return loudest_rms_; }

  // Render a complete TTDB record block and start a new window:
  //   \n---\n\n@LAT94LON<lane_n> | created:<t_sec> | ... | relates:hears@LAT0LON0
  //   \n\n**ACOUSTICWIN** t_ms:.. stream:0x<id> wall:<0|1> window_ms:.. blocks:.. rate:..
  //   \n**ACOUSTIC** rms_mean:.. rms_max:.. peak:.. transients:.. self_blocks:..
  //   (rms_*, peak, transients are over HEARD blocks; self_blocks were our own voice)
  //   \n**TRANSIENT** t_ms:.. stream:0x<id> wall:<0|1> rms:..   (only when one was heard)
  // Returns bytes written, or 0 if the window was empty (still resets).
  size_t buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                     const timestream::Stamp& ts, uint32_t now_ms,
                     uint32_t sample_rate);

  void reset(uint32_t now_ms);

 private:
  int32_t blocks_;
  uint64_t rms_sum_;      // sum of per-block RMS, for the mean
  int32_t rms_max_;
  int32_t peak_;          // largest |sample| seen
  int32_t transients_;
  int32_t self_blocks_;   // blocks captured while our own speaker sounded (not heard)
  int32_t last_rms_ = 0;  // diagnostics only (survives reset(); ambient_ does NOT)
  int32_t ambient_;      // slow-moving RMS baseline the transient test rides on
  uint64_t loudest_t_ms_;
  int32_t loudest_rms_;
  uint32_t window_start_ms_;
};

}  // namespace acousticpercept
