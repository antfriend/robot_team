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
#pragma once
#include <stdint.h>
#include <stddef.h>

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
#define PERCEPTLEARN_MAX_LANE 24
#endif
#ifndef PERCEPTLEARN_BUF
// Measured: 1595 B for a full PERCEPTLEARN_MAX_CLAIMS house. ~12% headroom for wider
// node ids and RSSI fields. buildOutcome writes NOTHING rather than truncating, so an
// under-sized buffer loses testimony SILENTLY — a first pass at 1024 did exactly that
// and only the native test caught it, which is the second time that has happened on
// this pattern (see MOTIONPERCEPT_TRANSITION_BUF).
//
// ⚠ Too big for the loop stack next to the other tiers' buffers — the sketch declares
// it `static`. Do not turn it into a local.
#define PERCEPTLEARN_BUF 1792
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
  // claims scored, or 0 if nothing was armed. Sets outcomePending() on success.
  int score(uint64_t t_ms, bool synced);

  // --- Rule 1: arm the next expectation, ONLY on a positive anchoring claim -------
  // `motion_lane` is the @LAT95 record making that claim — the acting record.
  // Re-derives entirely from what was staged this pass. Storing a per-peer "usual
  // RSSI" learned once and predicting THAT would be the precomputed route Rule 1
  // forbids; this deliberately reads the world again every window.
  bool arm(int motion_lane);

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

  // Render the outcome record and clear the pending flag. Carries the full tuple
  // Rule 2 specifies: acting record, edge, expectation, observed, verdict,
  // provenance. Returns bytes written, or 0 if nothing was pending or it did not fit.
  size_t buildOutcome(char* out, size_t cap, int lane_n, uint32_t node_id);

 private:
  int findStaged(uint32_t peer, uint8_t proto) const;

  Claim staged_[PERCEPTLEARN_MAX_CLAIMS];
  int   staged_n_;
  int   staged_over_;      // dropped for want of a slot this window
  int   staged_lane_;      // the @LAT97 record the staged medians came from

  Claim claims_[PERCEPTLEARN_MAX_CLAIMS];   // the armed expectation
  int   claims_n_;
  bool  armed_;
  int   acting_lane_;      // the @LAT95 record whose `still` claim armed this

  // scored results, awaiting buildOutcome
  bool  pending_;
  int   met_, violated_, unobserved_;
  int   scored_lane_;      // the @LAT97 record that answered
  uint64_t scored_t_ms_;
  bool  scored_synced_;
  int   streak_;
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
  size_t buildBelief(char* out, size_t cap, int i, int lon, uint32_t t_sec,
                     uint32_t node_id, int rev) const;

 private:
  int slotFor(uint32_t peer, uint8_t proto);
  Belief b_[PERCEPTLEARN_MAX_BELIEFS];
  int n_;
  int records_;
  int dropped_;
};

}  // namespace perceptlearn
