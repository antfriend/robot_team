// PerceptLearn.h — Learning from Action, Rules 1 and 2 (Stages B and C).
//
// Stage A (MotionPercept @LAT93) made the node write DIFFERENCES down. A difference is
// not yet learning: nothing was ever at stake. This tier puts something at stake —
// the node makes a falsifiable prediction about the world before the world answers,
// and then records whether it was right, in a lane it never edits.
//
// The two rules this implements, from the spec store's highest-EPS record
// (agent-memory-system_ttdb.md @LAT20LON3, conf 122 — the least-proven, most-relied-on
// idea in the system):
//
//   Rule 1 — every action carries an EXPECTATION: a predicted transition re-derived
//            from current state, never a precomputed route. An action without one is a
//            reflex: it executes but cannot teach.
//   Rule 2 — outcomes are APPENDED TO A SIDE LOG (acting record, edge, expectation,
//            observed, verdict, provenance). The live loop TESTIFIES, NEVER MUTATES.
//
// Rules 3 (asymmetric reconciliation) and 4 (K-failure abort) are NOT here. This tier
// only produces the evidence they would consume. It deliberately does not touch any
// record's [ew] block — that is Stage D's job, and doing it here would be the exact
// violation Rule 2 names. LOCUS, the only other implementation to run Rule 1, broke
// Rule 2 by revising in place; `RT` is structurally placed to keep it because
// `Ttdb::appendRecord` is append-only.
//
// ---------------------------------------------------------------------------
// THE PREDICTION
// ---------------------------------------------------------------------------
// A `state:still` motion window (@LAT95) is not a passive observation — it is a
// positive claim that the node was ANCHORED for those 60 seconds. If that claim is
// true, then the geometry between this node and each peer it hears did not change, so
// the NEXT link window's median RSSI to that peer should land within a small band of
// the window just closed.
//
// That is falsifiable inside 60 s against an observable `LinkPercept` already
// produces, which is what makes it a real prediction about the world rather than
// bookkeeping.
//
// ⚠ **A violation does NOT mean "this node moved."** It means the pair's geometry
// changed, and RSSI cannot say which end moved — the T-Deck is the fleet's roamer, so
// the most likely cause of a violated expectation on the Cardputer is the OTHER node
// walking away. The claim under test is "this link was stable", and the node is one of
// two things that can break it. Do not read the outcome lane as a motion detector.
//
// ---------------------------------------------------------------------------
// THE BAND — the first constant in this system with an empirical basis
// ---------------------------------------------------------------------------
// `+2/−16` and `K = 3` arrived as guesses and are still unrun. This one is not a
// guess. It was derived from 33 link windows the Cardputer had already written to its
// own flash (`master/preflash-2026-08-02/cardputer_ttdb.md`), in which ALL 34 motion
// windows were `still` — i.e. the entire history is the anchored case:
//
//     peer/proto        n    median |delta|   p90   max
//     0x010 ble        20         0            1     1
//     0x012 ble        20         0            2     3
//     0x200 ble        32         0            5    26
//     0x011 espnow     20         1            1     1
//     0x010 espnow     20         0            6     6
//     0x200 espnow     30         0            6    27
//     0x011 ble        18         2            3     5
//     0x012 espnow     20         0            2     3
//
// A still node's consecutive-window median moves by 0-2 dBm typically and by <= 6 dBm
// at p90 for every peer. **6 dBm is that p90**, so under genuinely anchored conditions
// roughly 90% of windows should land inside the band.
//
// ⚠ That number was chosen knowing what it does to Rule 3, and the interaction is the
// whole experiment. Rule 3 awards `+2` when an expectation is met and `−16` when it is
// violated, so with violation rate p the expected drift per window is
// `(1-p)(+2) + p(-16) = 2 - 18p`, which is **zero at p = 1/9 ≈ 11.1%**. The 1:8
// asymmetry therefore encodes "a claim must hold at least 8 times in 9 to be worth
// keeping." Setting the band at p90 puts a perfectly anchored node at ~10% — just
// inside break-even — so confidence should creep UP when nothing moves and fall as
// soon as anything does. A wider band would make Rule 3 look good by construction and
// prove nothing. **If you widen it, say so when reporting the constants.**
//
// ---------------------------------------------------------------------------
// RUN-LENGTH (2026-08-04) — the SAME decision as @LAT95's, not a separate one
// ---------------------------------------------------------------------------
// @LAT95 became change-triggered because a periodic lane fills with uptime rather than
// with events (part-b-handoff.md Part 1). This lane has the same disease and a worse
// prognosis — an outcome is 573-1595 B against a percept window's ~200 B, and
// PERCEPTLEARN_MAX_LANE is 24, so it fills in 24 minutes.
//
// ⚠ BUT THIS LANE IS A TALLY, AND A TALLY CANNOT BE COMPRESSED THE WAY A STATE SERIES
// CAN. A state series survives keeping only its transitions: the value between two
// changes is implied. A tally does not — `conf` is driven by HOW MANY windows were met
// and violated, so dropping the unchanged ones removes the denominator and Rule 3's
// arithmetic reads systematically over-confident. Keeping only transitions here would
// not compress the evidence; it would falsify it.
//
// Run-length is the form that fixes both, and the reason is worth stating precisely:
// **it is LOSSLESS with respect to Rule 3.** Folding a verdict N times is arithmetically
// identical to folding it once per window — the +2 saturation and the -16 floor are
// order-sensitive but not batch-sensitive, and the covered windows precede this one in
// the record exactly as they did in time. So a compressed lane reconciles to the SAME
// conf, sal and streak as an uncompressed one, and `tests/test_perceptlearn.cpp` pins
// that equivalence directly rather than trusting the argument.
//
// The shape mirrors @LAT95's, deliberately (part-b-handoff.md §1.3: generalize the
// shape, do not invent a new one). A record is written when the VERDICT VECTOR changes,
// when PERCEPTLEARN_MAX_RUN windows have passed, or when it is the first — and it
// carries the windows it suppressed:
//
//   **OUTCOME** ... windows_since_last:<N> reason:<first|changed|heartbeat>
//   **COVERED** peer:0x.. proto:.. verdict:.. windows:<N-1> observed_min:.. observed_max:..
//
// ⚠ COVERED LINES ARE FOLDED FIRST AND `windows:` TIMES EACH. They are emitted BEFORE
// the record's own EXPECTED/OBSERVED pairs because that is the order the windows
// happened in, and Reconciler::foldRecord walks the record in document order for
// exactly that reason. Reordering them would change a belief that hit the ceiling and
// then fell into one that never rose.
//
// What is lost, stated rather than glossed: the per-window `predicted_med`/`observed_med`
// of a covered window. `observed_min`/`observed_max` keep the range, so "the link held
// within the band for 20 windows" stays checkable, but the individual series does not
// survive. Verdicts — the only thing Rule 3 consumes — survive exactly.
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <TimeStream.h>   // the shared time stamp every record carries

#ifndef PERCEPTLEARN_MAX_CLAIMS
// One per (peer, proto) slot, matching LINKPERCEPT_MAX_PEERS.
#define PERCEPTLEARN_MAX_CLAIMS 8
#endif
#ifndef PERCEPTLEARN_RSSI_BAND
// dBm. See the derivation above. This is the tuning knob of the whole experiment.
#define PERCEPTLEARN_RSSI_BAND 6
#endif
#ifndef PERCEPTLEARN_LANE
// The outcome side log. Outside the 94..97 percept block AND outside @LAT93: this is
// testimony, and Rule 2's whole point is that it is kept apart from the live loop.
#define PERCEPTLEARN_LANE 92
#endif
#ifndef PERCEPTLEARN_MAX_LANE
// ⚠ This lane is EXPENSIVE and needs its cap chosen with the arithmetic in front of
// you, not by copying the percept lanes' 48. An outcome carries two lines per claim,
// so it is far bigger than a percept window: **573 B at 1 claim, 719 B at 2 (the
// realistic fleet case: one peer over espnow + ble), 1595 B at the 8-claim ceiling**
// — and it is written once per LINK window, ~1/minute, which is much faster than
// @LAT93 transitions arrive.
//
// At 48 that is 34 KB typical / 76 KB worst case, on a node whose whole TTDB was
// 41 KB. CLAUDE.md already records unpruned percept lanes growing V4-B's TTDB to
// 54 KB and breaking the bridged pull. So: **24**, which is ~17 KB typical / 38 KB
// worst, and ~24 minutes of continuous testimony — long enough to exercise Rule 3
// (whose 1/9 break-even needs tens of windows to show), short enough to survive.
// Prune and re-run rather than raising this.
//
// 📎 Since run-length landed (2026-08-04) this cap is spent on CHANGES rather than on
// minutes: an anchored fleet with nothing moving now writes one record per
// PERCEPTLEARN_MAX_RUN windows instead of one per window, so 24 records is ~12 hours of
// testimony instead of ~24 minutes. The 34 KB / 76 KB arithmetic above is unchanged —
// it is the same 24 records — it just takes 30x longer to spend.
#define PERCEPTLEARN_MAX_LANE 24
#endif
#ifndef PERCEPTLEARN_MAX_RUN
// The heartbeat, in scored windows. Matched to MOTIONPERCEPT_MAX_RUN on purpose: the
// two lanes are written from the same 60 s cadence and a reader lining an outcome up
// against the motion window that armed it should not have to reconcile two budgets.
//
//   lane life, nothing changing = PERCEPTLEARN_MAX_LANE x MAX_RUN = 24 x 30 = 12 hours
//   worst-case loss on power cut = MAX_RUN - 1 = 29 windows of unchanged testimony
//
// ⚠ That loss is REAL and it is not symmetric with @LAT95's: a lost percept window is
// evidence that can be re-gathered by waiting, whereas a lost outcome is testimony
// about a prediction that has already been resolved and cannot be re-run. It is
// bounded, it only ever loses windows that AGREED with the record before them, and a
// violation always writes immediately — but do not raise it casually.
#define PERCEPTLEARN_MAX_RUN 30
#endif
#ifndef PERCEPTLEARN_BUF
// Measured: 1595 B for a full PERCEPTLEARN_MAX_CLAIMS house, and **2340 B once that
// house also carries a COVERED line per claim** (run-length, 2026-08-04). ~12% headroom
// over that for wider node ids and RSSI fields. buildOutcome writes NOTHING rather than
// truncating, so an under-sized buffer loses testimony SILENTLY — a first pass at 1024
// did exactly that and only the native test caught it, which is the second time that
// has happened on this pattern (see MOTIONPERCEPT_TRANSITION_BUF). It would have been
// the third here: 1792 fits the head and the OBSERVED pairs but not the COVERED block,
// so an under-sized buffer would have dropped precisely the records carrying a run.
//
// ⚠ Too big for the loop stack next to the other tiers' buffers — the sketch declares
// it `static`. Do not turn it into a local.
#define PERCEPTLEARN_BUF 2624
#endif

namespace perceptlearn {

enum Verdict : uint8_t {
  VERDICT_MET = 0,
  VERDICT_VIOLATED = 1,
  VERDICT_UNOBSERVED = 2,   // predicted a peer that was not heard at all next window
};
const char* verdictName(uint8_t v);

struct Claim {
  uint32_t peer;
  uint8_t  proto;
  int16_t  predicted;   // median this claim says the next window will land near
  int16_t  observed;    // what it actually was (valid once scored)
  uint8_t  verdict;
};

// One claim's worth of a suppressed run: the verdict that held, how many windows it
// held for, and the range the observed median moved through while it did. The verdict
// and the count are what Rule 3 folds; the range is what a reader needs to see that
// "met for 20 windows" was not 20 identical numbers.
struct Covered {
  uint32_t peer;
  uint8_t  proto;
  uint8_t  verdict;
  int32_t  windows;
  int16_t  observed_min;
  int16_t  observed_max;
};

class Loop {
 public:
  Loop() { reset(); }
  void reset();

  // --- per link window: stage the medians of the window that just closed ---------
  // Call stageBegin(), then stage() once per (peer, proto), BEFORE the link log is
  // reset by its buildRecord(). These medians do double duty: they SCORE the
  // outstanding expectation and they are the basis for the next one.
  void stageBegin(int link_lane);
  void stage(uint32_t peer, uint8_t proto, int median);

  // Score the armed expectation against what was just staged. Returns the number of
  // claims scored, or 0 if nothing was armed.
  //
  // ⚠ Scoring no longer implies a record. If this window's verdict vector matches the
  // last one written, it is folded into the run instead and outcomePending() stays
  // false — the window is still counted, and the record that eventually closes the run
  // carries it. Check outcomePending(), never the return value, to decide whether to
  // append. The return value says "an expectation was resolved", which is a different
  // question and still the right one for logging.
  int score(const timestream::Stamp& ts, uint32_t wall_sec);

  // --- Rule 1: arm the next expectation, ONLY on a positive anchoring claim -------
  // `motion_lane` is the @LAT95 record making that claim and `motion_offset` says which
  // window of that record's run it is — the acting record is a (record, offset) PAIR
  // since @LAT95 became change-triggered. A `still` window that matches the run before
  // it writes no record of its own, so `motion_lane` alone would provenance this
  // expectation to a record describing a DIFFERENT window. The outcome writes the pair
  // out as `acting:@LAT95LON<n>+<k>`, which is checkable against the lane.
  //
  // Re-derives entirely from what was staged this pass. Storing a per-peer "usual
  // RSSI" learned once and predicting THAT would be the precomputed route Rule 1
  // forbids; this deliberately reads the world again every window.
  bool arm(int motion_lane, int motion_offset = 0);

  // The node did not claim to be anchored (a `moving` window), or the window was
  // discarded. Any outstanding expectation is dropped UNSCORED — scoring it would
  // test a claim the node never made.
  void disarm();

  bool armed() const { return armed_; }
  bool outcomePending() const { return pending_; }
  // (peer, proto) observations dropped this window because staged_ was full. MUST be
  // surfaced by the caller: an overflowed peer scores as VERDICT_UNOBSERVED, so a cap
  // that is too small is indistinguishable from peers going quiet unless someone says
  // so. PERCEPTLEARN_MAX_CLAIMS is 8 and a 4-node fleet over espnow+ble needs exactly
  // 8, so this is at the boundary the moment the V4s are powered, not a distant limit.
  int  stagedOverflow() const { return staged_over_; }
  int  metCount() const { return met_; }
  int  violatedCount() const { return violated_; }
  // Consecutive windows in which at least one claim was violated. Rule 4 (Stage E)
  // aborts at K of these; this tier only counts them so the datum exists.
  int  violationStreak() const { return streak_; }
  // Windows folded into the run in progress but not yet written down (0 = the last
  // scoring produced a record). Surface it: this is testimony at risk from a power cut,
  // and a node that never writes an outcome again looks identical to one whose links
  // are perfectly stable unless someone says which it is.
  int  coveredWindows() const { return cov_windows_; }
  // Windows since the last record was written, counting the one just scored.
  int  windowsSinceLast() const { return cov_windows_ + 1; }

  // Render the outcome record and clear the pending flag. Carries the full tuple
  // Rule 2 specifies: acting record, edge, expectation, observed, verdict,
  // provenance. Returns bytes written, or 0 if nothing was pending or it did not fit.
  size_t buildOutcome(char* out, size_t cap, int lane_n, uint32_t node_id);

 private:
  int findStaged(uint32_t peer, uint8_t proto) const;
  // The rendering half of buildOutcome, split out so the run can be adopted on EVERY
  // exit path — including the ones where the record did not fit.
  size_t renderOutcome(char* out, size_t cap, int lane_n, uint32_t node_id);

  Claim staged_[PERCEPTLEARN_MAX_CLAIMS];
  int   staged_n_;
  int   staged_over_;      // dropped for want of a slot this window
  int   staged_lane_;      // the @LAT97 record the staged medians came from

  Claim claims_[PERCEPTLEARN_MAX_CLAIMS];   // the armed expectation
  int   claims_n_;
  bool  armed_;
  int   acting_lane_;      // the @LAT95 record whose `still` claim armed this
  int   acting_offset_;    // ...and which window of that record's run it was

  // scored results, awaiting buildOutcome
  bool  pending_;
  int   met_, violated_, unobserved_;
  int   scored_lane_;      // the @LAT97 record that answered
  timestream::Stamp scored_stamp_;
  uint32_t scored_wall_sec_;
  int   streak_;
  const char* reason_;     // why the pending record is being written

  // --- the run: windows scored since the last record, folded not dropped ---
  bool     run_open_;      // a record has been written and speaks for a run
  Claim    run_[PERCEPTLEARN_MAX_CLAIMS];   // its verdict vector
  int      run_n_;
  // ⚠ The verdict vector as SCORED, snapshotted at score() time. adoptRun() must not
  // read `claims_` instead: the sketch stages and scores in the link flush and re-arms
  // in the motion flush, and arm() overwrites claims_ with fresh UNOBSERVED slots. A
  // first cut adopted from claims_ and every window therefore compared as `changed`, so
  // run-length silently did nothing at all while looking exactly like it worked. Only
  // the native test caught it — the records were each individually correct.
  Claim    scored_vec_[PERCEPTLEARN_MAX_CLAIMS];
  int      scored_vec_n_;
  Covered  cov_[PERCEPTLEARN_MAX_CLAIMS];   // the suppressed windows, per claim
  int      cov_n_;
  int      cov_windows_;   // how many windows those are
  // ⚠ AND WHEN THEY WERE. `windows:` counts SCORED windows, not minutes: a node that
  // starts moving arms nothing, so no window is scored at all until it settles, and two
  // scorings folded into one run can be an hour apart. The span makes that visible
  // instead of letting a reader assume N windows means N contiguous minutes — the same
  // move @LAT93's `dt_across_merge` makes for the same class of unstated assumption.
  uint64_t cov_first_t_ms_;
  uint64_t cov_last_t_ms_;

  // True when `claims_` (as just scored) carries the same (peer, proto, verdict) set as
  // the run in progress. Set membership, not order: the staging order follows whichever
  // peers were heard first and is not a fact about the world.
  bool sameAsRun() const;
  void adoptRun();         // make the just-scored vector the run's, clearing covered
  void foldIntoRun();      // add the just-scored window to the covered accumulators
};

// ---------------------------------------------------------------------------
// STAGE D — Rule 3, asymmetric reconciliation. THE experiment.
// ---------------------------------------------------------------------------
// Rule 3 — reconciliation folds outcomes into weights ASYMMETRICALLY: expectation met
// `conf +2` saturating, violated `conf -16` floor 0 and `sal +8`; repeated violation
// raises a contradiction flag. The ~1:8 asymmetry guards against confirmation bias.
//
// Three things make this the part that was worth building rather than a counter:
//
//  1. It reconciles a belief that DID NOT EXIST until now. The node's own TTDB carried
//     **zero `[ew]` blocks** — Rule 3 moves `conf`/`sal` and there was nothing on the
//     device that had either. That is not a robot_team quirk: Rule 3 quietly assumes the
//     acting agent already carries epistemic weight on the belief under test, and a
//     percept-writing device has no reason to have written one. So Stage D introduces
//     `@LAT91` LINK-STABLE, one belief per (peer, proto), and it is the first record on
//     this fleet to carry a TBEW block at all.
//
//  2. It is a PURE FUNCTION of the outcome lane, recomputed from a fixed baseline over
//     the records in order — never an incremental running total. That costs a re-read of
//     the whole lane every cycle and buys the only property that matters here: a third
//     party reading the same @LAT92 records reaches the same number, so re-running is a
//     no-op and the reconciliation is auditable rather than trusted. A RAM counter would
//     be cheaper, would produce the same figures, and would prove nothing — it would be
//     the node REMEMBERING, not the store RECONCILING. TTE Draft 06's standing caveat is
//     that its only reconciliation was performed by hand by an outside reader; a running
//     total would not discharge it.
//     ⚠ Consequence, stated because it is a real property and not a bug: **pruning the
//     outcome lane resets the belief toward baseline.** The belief is exactly as strong
//     as the evidence still retained.
//
//  3. Order matters, so folding is sequential. The +2 saturates at 255 and the -16 floors
//     at 0, and a clamp is not commutative with a sum — a belief that hit the ceiling and
//     then fell is not the same as one that never rose. Summing met/violated and applying
//     the arithmetic once would be subtly wrong over long runs.
//
// MEASURED, 2026-08-02 (percept-learning-return.md §0b): over a run where the peer was
// carried to another room and back, 9 met / 5 violated drove espnow 128 -> 106 and ble
// 128 -> 88. tests/test_perceptlearn.cpp replays that exact verdict sequence and asserts
// those numbers, so the on-device result is checkable against the hand computation.
#ifndef PERCEPTLEARN_BELIEF_LANE
#define PERCEPTLEARN_BELIEF_LANE 91
#endif
#ifndef PERCEPTLEARN_BASELINE_CONF
// Mid-range on purpose. Movement is visible in BOTH directions from here: 64 met windows
// to saturate at +2, only 8 violated ones to floor at -16. Starting high would hide the
// decay behind the ceiling; starting low would floor on the first bad patch.
#define PERCEPTLEARN_BASELINE_CONF 128
#endif
#ifndef PERCEPTLEARN_CONF_MET
#define PERCEPTLEARN_CONF_MET 2
#endif
#ifndef PERCEPTLEARN_CONF_VIOLATED
#define PERCEPTLEARN_CONF_VIOLATED 16
#endif
#ifndef PERCEPTLEARN_SAL_VIOLATED
#define PERCEPTLEARN_SAL_VIOLATED 8
#endif
#ifndef PERCEPTLEARN_CONTRADICTION_STREAK
// "Repeated violation raises a contradiction flag" — repeated = 2 consecutive for the
// same (peer, proto). Distinct from Rule 4's K, which counts whole windows.
#define PERCEPTLEARN_CONTRADICTION_STREAK 2
#endif
#ifndef PERCEPTLEARN_MAX_BELIEFS
#define PERCEPTLEARN_MAX_BELIEFS PERCEPTLEARN_MAX_CLAIMS
#endif
#ifndef PERCEPTLEARN_BOUNDARY_BUF
// MEASURED, not estimated — see buildBoundary(). A full 8-belief house with realistic
// field values renders at **1095 B**: a 120 B head line plus 8 x ~122 B. 1536 is ~40%
// headroom, which is deliberate rather than tight: the belief line carries nine numeric
// fields and a wider node id or a four-digit tally would push a hand-fitted buffer over
// again. tests/test_perceptlearn.cpp pins the worst case against this constant AND
// against the 1024 that was too small, so shrinking it back fails the build.
#define PERCEPTLEARN_BOUNDARY_BUF 1536
#endif

struct Belief {
  uint32_t peer;
  uint8_t  proto;
  int32_t  met, violated, unobserved;
  int32_t  conf, sal;
  int32_t  streak, max_streak;
  bool     contradiction;
};

class Reconciler {
 public:
  Reconciler() { begin(); }

  // Clear all tallies. Every cycle starts from the baseline and re-reads the lane.
  void begin();

  // Fold ONE claim, in lane order. Applies Rule 3 immediately (see note 3 above).
  void fold(uint32_t peer, uint8_t proto, uint8_t verdict);

  // Parse one @LAT92 record body straight off flash and fold every claim it carries.
  // Returns the number folded. Tolerates a partial read: it only acts on complete
  // `**OBSERVED** ... verdict:<v>` lines, so a truncated tail is ignored rather than
  // guessed at.
  int foldRecord(const char* text, size_t len);

  int beliefCount() const { return n_; }
  const Belief& belief(int i) const { return b_[i]; }
  int recordsFolded() const { return records_; }
  // Claims discarded this cycle because every belief slot was taken. Unlike the staged
  // overflow above this one silently biases an ANSWER: the dropped (peer, proto)'s
  // testimony never reaches any belief, so conf is computed from a subset of the lane
  // while looking exactly like a complete fold.
  int claimsDropped() const { return dropped_; }

  // Render one @LAT91 belief — the first record on this fleet to carry an [ew] block.
  //
  // ⚠ THE RECENCY ANCHOR IS WRITTEN TWICE, ON PURPOSE, AND THAT IS A SPEC FINDING.
  // TTDB-RFC-0005 §4 defines `touched` as **Unix epoch seconds**, and §4's own decay
  // note ("entries untouched for long periods SHOULD have conf decremented") assumes
  // an agent that can read a wall clock. A fleet with no laptop in sight cannot:
  // `t_sec` is 0, so `touched:0`, so `sal` can never fade and EPS = sal x (255-conf)/255
  // has no time term at all. **The RFC's recency machinery is unusable on exactly the
  // class of device the RFC was written for.**
  //
  // So `touched:` stays spec-conformant (Unix seconds, 0 = unknown) and the **TOUCHED**
  // body line carries the same instant in the STREAM frame, which a node always has.
  // That is what a node decays against. Both are emitted every time; they are the same
  // moment in two frames, not two moments.
  size_t buildBelief(char* out, size_t cap, int i, int lon, uint32_t t_sec,
                     uint32_t node_id, int rev, const timestream::Stamp& ts) const;

  // Render the block a @LAT100 boundary carries when THIS lane is pruned: what the
  // ended generation held, and what it concluded. `records` is the caller's count of
  // @LAT92 records folded (a record is not a window since run-length, so both are
  // stated). Returns bytes written, or 0 if it did not fit — nothing rather than a
  // truncation, because a short list understates the evidence the boundary stands in
  // for, which is the failure it exists to prevent.
  //
  // ⚠ THIS LIVED IN THE SKETCH FOR ONE AFTERNOON AND THAT WAS THE DEFECT. Sized by eye
  // at "~100 B a line", it renders at 122, so a full 8-belief house came to 1095 B
  // against a 1024 B buffer and the prune correctly REFUSED — on hardware, after the
  // measurement window had already been spent. Every other buffer in this library is
  // pinned by a native test against its worst case; this one could not be, because a
  // native test cannot call into a .ino. Moving it here is the fix, not the raised
  // constant.
  //
  // ⚠ The line tokens are deliberately NOT `**OBSERVED**`/`**COVERED**`. Those are
  // foldRecord()'s needles, and a boundary carrying either would be folded as testimony
  // the next time the lane was read — the node re-learning from its own gravestone.
  size_t buildBoundary(char* out, size_t cap, int records) const;

 private:
  int slotFor(uint32_t peer, uint8_t proto);
  Belief b_[PERCEPTLEARN_MAX_BELIEFS];
  int n_;
  int records_;
  int dropped_;
};

}  // namespace perceptlearn
