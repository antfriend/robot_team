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
// portable (no Arduino dependency) so the stats and the record format are pinned by
// tests/test_motionpercept.cpp. (Until 2026-08-01 that test did not exist and this tier
// had only ever been verified on hardware — companion.md §6, 2026-07-27.)
// The sketch supplies the IMU read and the Ttdb::appendRecord.
//
// ---------------------------------------------------------------------------
// THE TRANSITION FORM (@LAT93) — TTDB-RFC-0006 §5, added 2026-08-01
// ---------------------------------------------------------------------------
// A window verdict written on its own is a STATE. TTDB-RFC-0006 §5 makes the paired
// `@PERCEPT:before` -> `@PERCEPT:after` node "formal and non-negotiable": the unit of
// perceptual knowledge is not a node but the EDGE between two of them (§5.2). Until
// now nothing in this project — or in any store the spec side has examined — had ever
// instantiated that form: every loop overwrote state, and the difference, which is the
// datum, was never materialized. There was therefore nothing to compute prediction
// error over, which is why Learning from Action has stayed untestable.
//
// This tier is the cheapest true instance of the form available anywhere in the fleet:
// it already computes both sides of a `still -> moving` edge and used to throw the
// pairing away. Now, when a window closes with a verdict DIFFERENT from the window
// before it, it emits one @LAT93 record carrying both halves and the typed edge.
//
// Three decisions worth knowing before you change the format:
//
//  1. ONE record, not two. §7.1 says implementations MUST enforce the pairing at write
//     time and that orphans are errors. `Ttdb::appendRecord` has no transaction: two
//     appends means power loss between them leaves an orphaned `before`, which §7.1
//     forbids. A single atomic append is the only way a fixed-RAM streaming writer can
//     actually keep that promise, so both halves live in one record body.
//
//  2. The `@PERCEPT:` lines are INDENTED BY TWO SPACES, and must stay that way.
//     TTDB-RFC-0001 §3 defines a record header as a line whose first character is '@',
//     and Ttdb::begin()'s pass-1 scan implements exactly that. An unindented
//     `@PERCEPT:before` in a body is therefore indexed as a record header, fails to
//     parse, and becomes a phantom (0,0) record on the device. The Locus namespace and
//     the TTDB record syntax collide, and indentation is the resolution.
//
//  3. The pair is ALSO written as real edges (`derived_from` to each half's @LAT95
//     record), because §5.2 asks storage to optimise for edge traversal — and because
//     the same lesson TTDB-RFC-0003 v1.1 §7.3 draws about polarity applies here: what
//     is encoded only positionally is invisible to a consumer reading the edge list,
//     which is what implementations in this corpus actually traverse. Those edges CAN
//     dangle once the @LAT95 lane is pruned or wraps, which is why the state blocks are
//     duplicated into the body: the transition stays self-sufficient without them.
//
// Stage A only. This writes the difference down; it does not yet predict, testify, or
// reconcile (percept-learning-handoff.md Stages B-E).
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <TimeStream.h>   // the shared time stamp every record carries

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
#ifndef MOTIONPERCEPT_TRANSITION_LANE
// The transition lane. Deliberately OUTSIDE the 94..97 percept block that
// CMD_CLEAR_PERCEPTS drops (TTDB.h TTDB_PERCEPT_LANE_LO/HI): a percept window is
// raw evidence and cheap to re-gather, whereas a transition is the thing this node
// learns from and there are far fewer of them. Widen the prune range deliberately
// if you ever want them dropped — do not let it happen by adjacency.
#define MOTIONPERCEPT_TRANSITION_LANE 93
#endif
#ifndef MOTIONPERCEPT_MAX_TRANSITION_LANE
// Own cap, own budget. A transition only exists on a verdict CHANGE, so at one 60 s
// window per minute this is bounded by how often the node actually starts and stops
// moving, not by uptime — a still node on a shelf writes none at all.
#define MOTIONPERCEPT_MAX_TRANSITION_LANE 32
#endif
#ifndef MOTIONPERCEPT_TRANSITION_BUF
// Buffer buildTransition() needs: two state blocks plus the header. A measured pair is
// 589 B (tests/test_motionpercept.cpp), so this is ~30% headroom for wider lane numbers
// and permille/dev fields. Do NOT trim it to fit the measurement: buildTransition
// writes NOTHING when the record does not fit rather than truncating (§7.1 — an orphan
// is an error, not partial data), so an under-sized buffer silently loses transitions.
// That is exactly what a first pass at 512 did, and only the test caught it.
#define MOTIONPERCEPT_TRANSITION_BUF 768
#endif

namespace motionpercept {

// One closed window, reduced to the numbers a transition needs. Fixed size, no
// allocation — two of these are the entire cost of remembering the previous window.
struct Window {
  bool     moving;        // the window's verdict (permille >= 100)
  // WHEN, and on WHICH shared timeline. `stamp.stream_id == 0` says t_ms is local
  // millis() and is comparable with nothing but this node's own records — what the
  // old `synced:0` meant, except this one also NAMES the clock when there is one.
  timestream::Stamp stamp;
  int16_t  lane;          // the @LAT95 lane this window was written to
  int32_t  n;             // samples
  int32_t  permille;
  int32_t  dev_mean_mg;
  int32_t  dev_max_mg;
  uint32_t moving_ms;
  uint32_t window_ms;
  uint32_t t_sec;
};

class Log {
 public:
  Log() { reset(0); prev_valid_ = false; pending_ = false; }

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
  //   \n\n**MOTIONWIN** t_ms:.. stream:0x<id> wall:<0|1> window_ms:.. n:..
  //   \n**MOTION** state:<still|moving> moving_permille:.. dev_mean_mg:..
  //     dev_max_mg:.. moving_ms:..
  // Returns bytes written, or 0 if the window was empty (still resets).
  //
  // Also closes the transition chain: the window just rendered becomes the candidate
  // `after` half, and if the window BEFORE it carried the opposite verdict a paired
  // record is now pending (see transitionPending()).
  size_t buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                     const timestream::Stamp& ts, uint32_t now_ms);

  // True when the two most recently closed windows disagree, i.e. a state change
  // happened and has not been written down yet. Cleared by buildTransition(), or by
  // any reset() — a discarded window breaks the chain rather than pairing across the
  // gap and claiming a transition that skipped a window nobody measured.
  bool transitionPending() const { return pending_; }

  // Render the paired @PERCEPT:before -> @PERCEPT:after record for that change and
  // clear the pending flag. Call it right after the buildRecord() that set the flag
  // and before the next one, which would overwrite the `after` half.
  //
  // `node_id` is the agent anchor TTDB-RFC-0006 §7.3 makes mandatory: a perceptual
  // transition without a perceiving subject is propositional, not experiential.
  // Needs a buffer of MOTIONPERCEPT_TRANSITION_BUF. Returns bytes written, or 0 if
  // nothing was pending or the record did not fit (the flag clears either way — a
  // truncated pair is exactly the orphan §7.1 forbids).
  size_t buildTransition(char* out, size_t cap, int lane_n, uint32_t node_id);

  // The last window closed by buildRecord(), and the one before it while a transition
  // is pending. Exposed for the native test and for Stage B, which has to re-derive an
  // expectation from the current state rather than from a precomputed route.
  const Window& lastWindow() const { return prev_; }
  const Window& pendingBefore() const { return before_; }

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

  // --- the transition chain (survives reset() only through buildRecord) ---
  Window prev_;           // last closed window = the `after` half while pending
  Window before_;         // the one before it = the `before` half
  bool   prev_valid_;
  bool   pending_;
};

}  // namespace motionpercept
