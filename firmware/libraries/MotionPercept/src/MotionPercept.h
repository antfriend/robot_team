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
//
// ---------------------------------------------------------------------------
// CHANGE-TRIGGERED WITH EXPLICIT RUN-LENGTH (2026-08-04) — part-b-handoff.md Part 1
// ---------------------------------------------------------------------------
// Until now this lane was PERIODIC: one record per 60 s window whether or not anything
// happened, so `MOTIONPERCEPT_MAX_LANE 48` filled in 48 minutes of UPTIME. Measured
// three times on 2026-08-03: every percept lane on every node refilled to its cap
// within one afternoon of being emptied. Pruning that is a treadmill, not maintenance.
//
// So a window whose verdict matches the run in progress is no longer written on its own.
// The one thing that makes that honest instead of lossy is that the suppression is
// SAID OUT LOUD, in the lane, in two fields:
//
//   **RUN** windows_since_last:<N> reason:<first|changed|heartbeat> run_lane:<LON>
//   **COVERED** state:<s> windows:<N-1> n:.. window_ms:.. moving_permille:.. ...
//
// `windows_since_last:N` is the number of windows that elapsed between the previous
// @LAT95 record and this one, counting this one — 1 means adjacent, N>1 means N-1
// windows were suppressed. **COVERED** is those N-1 windows reduced to the same
// statistics a single window carries, so the lane still answers "how much of the last
// hour was this node still?" exactly. Without it the lane would UNDERSTATE stillness,
// and every downstream statistic computed from it — including the B.3 measurement that
// derived MOTIONPERCEPT_MOVING_MG — would silently weight a 30-window run the same as a
// 1-window one.
//
// ⚠ THE RECORD IS A CITATION, AND THAT IS WHY THIS IS NOT A ONE-LINE CHANGE.
// `PerceptLearn::arm()` provenances every expectation to "the @LAT95 record whose
// `still` claim armed this". Suppress a window and there is no new record to cite;
// citing the last-written one instead would attribute the expectation to a record
// describing a DIFFERENT window — testimony with false provenance, which @LAT92's tally
// then inherits. That is worse than not arming at all.
//
// The resolution: a window is identified by **(covering record, offset into its run)**,
// not by a record alone. `lastClose()` reports which of the two things just happened and
// `coveringLane()`/`runOffset()` name the window, so a citation reads
// `acting:@LAT95LON7+3` — "the 4th window of the run opened by @LAT95LON7". That is
// exact, and it is checkable against the lane: the run's length is written down when it
// closes. The same pair identifies the `before` half of an @LAT93 transition, whose
// window is usually suppressed now.
//
// ⚠ WHAT IS ACTUALLY LOST, stated rather than glossed: a suppressed window's INDIVIDUAL
// statistics. The run's aggregate survives; the per-window series does not. And a run
// that is still open when the node loses power was never written at all, so up to
// MOTIONPERCEPT_MAX_RUN - 1 windows of unchanged history go with it. No CHANGE is ever
// deferred — a verdict flip always writes immediately — so what is at risk is only the
// detail of a stretch in which nothing happened.
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
#ifndef MOTIONPERCEPT_MAX_RUN
// The heartbeat: how many consecutive windows of one verdict may be folded into a run
// before a record is written anyway. This is NOT a threshold on data and is not
// measured — it is a budget, and the arithmetic is the justification:
//
//   lane life at rest  = MOTIONPERCEPT_MAX_LANE x MAX_RUN windows
//                      = 48 x 30 x 60 s = 24 HOURS of uptime (was 48 minutes)
//   worst-case loss    = MAX_RUN - 1 = 29 windows of unchanged history, if the node
//                        loses power with a run open
//   worst-case latency = 0 for a CHANGE (always written immediately); 29 windows
//                        before an unchanging state is re-asserted in the lane
//
// 30 buys the treadmill fix by a factor of 30 while keeping the lane's freshest record
// no more than half an hour old, so "when did this node last say anything?" stays a
// meaningful question. Raise it and the loss window grows in exactly the same ratio.
#define MOTIONPERCEPT_MAX_RUN 30
#endif
#ifndef MOTIONPERCEPT_RECORD_BUF
// Buffer buildRecord() needs. A plain window is ~200 B; one carrying a **COVERED**
// block is ~330 B. 512 is ~55% headroom. Like buildTransition(), buildRecord() writes
// NOTHING rather than truncating, so an under-sized buffer loses windows SILENTLY —
// the sketch's old `char rec[320]` would have fitted the plain form and quietly dropped
// exactly the records that close a long run, which are the ones carrying the run length.
#define MOTIONPERCEPT_RECORD_BUF 512
#endif
#ifndef MOTIONPERCEPT_MOVING_MG
// Deviation of |acceleration| from 1 g, in milli-g, above which a sample counts as
// motion. Hand tremor on a held device is ~20-40 mg; a walking stride peaks in the
// hundreds. 60 mg keeps "held still in a hand" on the still side of the line.
//
// ✅ MEASURED AGAINST THIS BMI270 ON THIS BOARD, 2026-08-03 — and it survives.
// The reasoning above came from published figures and had never been checked against
// the part; every `still` claim the learning loop rests on rests on this line, so it
// was measured the way PERCEPTLEARN_RSSI_BAND 6 was (p90 of the node's own statistic
// across a known-quiet run, table written down rather than summarised).
//
//   Cardputer 0x300, @LAT95 lane pruned to empty first so the run IS the sample.
//   48 windows x 60 s, 298-997 samples each, node stationary and UNTOUCHED for
//   50 minutes (no companion.py call: every invocation resets the board and
//   restarts the window). Statistic: dev_max_mg, the largest |mag - 1g| in a window.
//
//     dev_max_mg    min 11   p50 12   p75 12   p90 12   p95 13   max 20
//     dev_mean_mg   min  8   p50  8   p90  8   max  9
//     moving_permille  0 in every window (max 0)
//     samples >= 60 mg: 0 of 48 windows
//
//   p90 = 12 mg, so 60 mg is 5.0x the noise floor and 3x the worst single excursion
//   in 50 minutes. The resting floor is a BIAS, not jitter: dev is |mag - 1 g| and
//   this part sits ~8 mg off 1 g at rest, so the usable margin above rest is ~52 mg,
//   not 60. Even so the verdict is comfortable, and it is comfortable in the
//   direction the design intends — 60 mg stays ABOVE hand tremor (20-40 mg), which is
//   what keeps a held-but-still device on the still side.
//
// ⚠ THE FIRST ATTEMPT AT THIS MEASUREMENT WAS WRONG BY 2.75x, AND THE WAY IT WAS
// WRONG IS THE LESSON. Reading the 48 windows the lane already held gave p90 = 33 mg
// and one window with an 80 mg sample. Those windows were labelled `state:still` — by
// this very threshold, which is circular — and the node had been picked up, plugged
// and unplugged during them. The lane's own label is not evidence that the node was
// still; only an operator keeping it still is. Prune, then collect.
//
// ⚠ Consequence for the flapping concern (a signal sitting ON the threshold produces
// MORE records than periodic logging): at rest this board is nowhere near the line —
// moving_permille was 0 in all 48 windows, not merely under the 100 verdict gate. So
// hysteresis is not needed to stop rest-state flapping. It may still be needed at the
// EDGE of real motion, which this run does not measure and a walk-and-stop run would.
// ⚠⚠ THIS NUMBER WAS MEASURED ON ONE CHIP AND DOES NOT TRANSFER TO ANOTHER (2026-08-12).
// It came off the Cardputer's BMI270. The K10's SC7A20H reads |a| = **1085 mg** at rest —
// 8.5% high, which is ordinary for the part and passes any "is the scale about right?"
// check — so `dev = | |a| - 1000 |` sits at a STATIC 87 mg, over this 60 mg line, forever.
// The first two windows that board ever wrote said, about a picture frame untouched on a
// desk:
//
//     **MOTION** state:moving moving_permille:1000 dev_mean_mg:87 dev_max_mg:99
//
// Reproduced identically across two boots, so it was systematic, not noise. That is the
// worst failure this tier has: not a missing verdict but a CONFIDENT FALSE one, in the
// lane whose whole job is to make "the observer held still" checkable instead of assumed.
//
// The fix belongs in the SKETCH, not here: k10_percept.ino measures what magnitude ITS
// board reads at rest and scales samples so that maps to 1000 mg, which restores the
// meaning this threshold was measured to have — a fraction of g, not a raw count. After
// it: `state:still moving_permille:1 dev_mean_mg:4`. Do NOT "fix" a third board by moving
// this constant; it would silently redefine both existing lanes. Give the new board a null.
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
  // WHICH RECORD SPEAKS FOR THIS WINDOW. Since the lane became change-triggered a
  // window is named by a pair: the @LAT95 record covering it, and how many windows
  // into that record's run it sat. `run_offset == 0` is the record's own window.
  // Citing `lane` alone would attribute this window to a record describing another one.
  int16_t  lane;          // the @LAT95 lane whose run covers this window
  int16_t  run_offset;    // windows into that run (0 = the covering record's own)
  int32_t  n;             // samples
  int32_t  permille;
  int32_t  dev_mean_mg;
  int32_t  dev_max_mg;
  uint32_t moving_ms;
  uint32_t window_ms;
  uint32_t t_sec;
};

// What buildRecord() did with the window it just closed. `WRITTEN` and `COVERED` are
// BOTH successful closes — a covered window is a real, counted observation that an
// existing record's run speaks for. Only `EMPTY` means there was nothing there.
//
// ⚠ The caller must branch on this, not on the returned byte count. Before the lane
// became change-triggered, `0 bytes` meant "no window", and the sketch disarmed the
// learning loop on it. Under run-length, 0 bytes is the NORMAL case for a still node,
// and disarming on it would silence Rule 1 for 29 windows out of every 30.
enum Close : uint8_t {
  CLOSE_EMPTY = 0,    // no samples, or the record did not fit: nothing happened
  CLOSE_WRITTEN,      // a record was rendered; it opens a new run
  CLOSE_COVERED,      // folded into the run in progress; no record, no loss
};

class Log {
 public:
  Log() { reset(0); prev_valid_ = false; pending_ = false; breakRun(); }

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

  // Close the current window. Renders a complete TTDB record block ONLY when the
  // window's verdict starts a run, changes it, or the run has reached
  // MOTIONPERCEPT_MAX_RUN; otherwise the window is folded into the run in progress and
  // nothing is written. Either way the window is counted and a new one starts.
  //
  //   \n---\n\n@LAT95LON<lane_n> | created:<t_sec> | ... | relates:senses@LAT0LON0
  //   \n\n**MOTIONWIN** t_ms:.. stream:0x<id> wall:<0|1> window_ms:.. n:..
  //   \n**MOTION** state:<still|moving> moving_permille:.. dev_mean_mg:..
  //     dev_max_mg:.. moving_ms:..
  //   \n**RUN** windows_since_last:<N> reason:<first|changed|heartbeat>
  //   \n**COVERED** state:<s> windows:<N-1> ...          (only when N > 1)
  //
  // Returns bytes written, or 0 when the window was covered or empty — ⚠ CHECK
  // lastClose(), NOT the byte count, to tell those two apart. `cap` should be
  // MOTIONPERCEPT_RECORD_BUF: a record that does not fit is written NOT AT ALL.
  //
  // Also closes the transition chain: the window just closed becomes the candidate
  // `after` half, and if the window BEFORE it carried the opposite verdict a paired
  // record is now pending (see transitionPending()).
  size_t buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                     const timestream::Stamp& ts, uint32_t now_ms);

  // What the last buildRecord() call did, and the (record, offset) pair naming the
  // window it closed — the citation any downstream claim about that window must carry.
  Close lastClose() const { return close_; }
  int   coveringLane() const { return cover_lane_; }
  int   runOffset() const { return run_offset_; }
  // Windows in the run in progress, including the covering record's own. 0 = no run.
  int   runLength() const { return run_open_ ? run_len_ : 0; }

  // Break the run without closing a window: whatever is written next opens a fresh run
  // and says `reason:first`. Called by reset() for the same reason it breaks the
  // transition chain — a discarded window means the next record is not adjacent to the
  // last, so folding across the gap would claim coverage of a window nobody measured.
  void breakRun();

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

  // --- the run (also survives reset() only through buildRecord) ---
  bool   run_open_;       // a record has been written and speaks for a run
  bool   run_state_;      // that run's verdict; a window disagreeing with it writes
  int    run_lane_;       // the @LAT95 lane of the record covering the run
  int    run_len_;        // windows in it so far, including the covering record's own

  // The suppressed windows, reduced to the same statistics one window carries. Summed
  // over SAMPLES, not over windows, so the aggregate is what the whole stretch would
  // have measured as a single long window rather than a mean of means.
  int32_t  cov_windows_;
  int32_t  cov_n_;
  int32_t  cov_n_moving_;
  uint32_t cov_dev_sum_mg_;
  int32_t  cov_dev_max_mg_;
  uint32_t cov_moving_ms_;
  uint32_t cov_window_ms_;
  uint64_t cov_first_t_ms_;
  uint64_t cov_last_t_ms_;

  // --- what the last close did ---
  Close  close_;
  int    cover_lane_;
  int    run_offset_;
};

}  // namespace motionpercept
