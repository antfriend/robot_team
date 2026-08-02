# Return: `robot_team` → `toot-toot-engineering`

**Staged in `robot_team`; destined for `toot-toot-engineering`.**
Answers `percept-learning-handoff.md` Part 4. Authored against `robot_team` @
`fe8e47f` + this session's working tree and `toot-toot-engineering` @ `cdac8d4`.
Spec sync read 2026-08-01; **the hardware run is 2026-08-02**.

**Read §0 before merging anything.** This is a *partial* return, and the partition is
sharp: **Stage A ran on a device and Part 4.1 D is delivered with real numbers.
Stages B–E did not run, so A, B and C are not delivered and are not estimated.**

Throughout: `TTE` = `toot-toot-engineering`, `RT` = `robot_team`.

---

## 0c. STAGE D RUNS — and TTE Draft 06's standing caveat is discharged

**The store reconciles itself.** The Cardputer's Dream Cycle re-reads its own `@LAT92`
outcome lane off flash, folds every claim through Rule 3 from a fixed baseline, and
rewrites an `@LAT91` belief lane. Device-written, 2026-08-02:

```
@LAT91LON1 | ... relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:140
rev:1
sal:16
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:espnow node:0x300
**TALLY** met:22 violated:2 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92
              lane_records:24 method:sequential_fold_from_baseline
```

plus `@LAT91LON0` for ble: **`conf:122 sal:24`, met 21 / violated 3, `contradiction:1`**.

**These are the first records on this fleet to carry a TBEW `[ew]` block at all** — before
today the node's store had none, which is itself the finding in §2.7a.

### The verification that makes it a reconciliation and not a number

The 24 `@LAT92` records were re-folded **independently on the laptop**, in lane order, from
the same baseline:

| proto | laptop conf/sal | device conf/sal | met/violated | match |
|---|---|---|---|---|
| ble | 122 / 24 | 122 / 24 | 21 / 3 | **yes** |
| espnow | 140 / 16 | 140 / 16 | 22 / 2 | **yes** |

Exact agreement, derived twice by different code from the same evidence. That is the
property the design was built for: **the belief is a pure function of the outcome lane**,
recomputed from baseline every cycle rather than accumulated. A running total would have
produced these same two numbers and proven nothing — it would have been the node
*remembering*. Re-reading makes it the store *reconciling*, and it means any third party
holding the `@LAT92` records can check the node's arithmetic. Draft 06's caveat — *"the
reconciliation was performed BY HAND, by an outside reader"* — no longer holds: it was
performed by the node, and the outside reader now merely audits it.

Two consequences worth carrying into the spec:

- **Pruning the outcome lane resets the belief toward baseline.** Not a bug: the belief is
  exactly as strong as the evidence still retained. But it means Rule 3's `conf` is a
  statement about *retained testimony*, not about history, and a store that prunes is a
  store that forgets what it concluded. Rule 2's side log therefore has a retention policy
  whether or not it declares one.
- **Order matters and a clamp does not commute with a sum.** `+2` saturates at 255 and
  `−16` floors at 0, so a belief that hit the ceiling and then fell is not the same as one
  that never rose. Folding must be sequential; tallying met/violated and applying the
  arithmetic once is subtly wrong over long runs. Rule 3 should say so.

---

## 0a. Update — 2026-08-02 later the same day: Stages B and C also run

**The node now makes falsifiable predictions and testifies to the result.** New portable
lib `firmware/libraries/PerceptLearn/` (39 native checks) writes an `@LAT92` outcome lane
on the Cardputer. Rule 1: a `still` motion window is a positive claim of anchoring, so it
arms an expectation that each peer's median RSSI holds within a band next window. Rule 2:
the verdict is **appended** and nothing in the live loop touches any `[ew]`. Verified over
two hardware runs — **8 outcome records, 16 claims, ~683 B each**, cycling
arm → score → testify → re-arm every 60 s.

Three things this adds to what TTE asked for:

1. **The band is the first constant in this system with an empirical basis.** 6 dBm is the
   **p90 of consecutive-window median drift over 33 link windows the node had already
   written while all 34 motion windows read `still`** — derived from the node's own flash,
   not guessed the way `+2/−16` and `K = 3` were.
2. **Rule 3's asymmetry has a computable break-even: 1/9.** Expected drift per window is
   `(1-p)(+2) + p(-16) = 2 - 18p`, zero at **p = 11.1%**. So `+2/−16` encodes *"a claim
   must hold at least 8 times in 9 to be worth keeping."* That is derivable without running
   anything, and it means **the band choice, not the constants, sets whether Rule 3 looks
   good** — which is why the band was fixed at p90 (~10%, just inside break-even) rather
   than somewhere comfortable. ⚠ A wider band would flatter Rule 3 and prove nothing.
3. **Stage D is blocked on two structural facts, and they are findings in their own right.**
   See §2.7.

## 0b. THE CONSTANTS — Part 4.1.C, answered

A second run put the Cardputer flat and untouched on a desk and carried the T-Deck to
another room and back over ~10 minutes. **7 outcomes, 14 claims, 9 met / 5 violated.**

```
      espnow                       ble
LON17 -41  d= -1  met        LON17 -55  d=  0  met      <- both on the desk
LON18 -45  d= -4  met        LON18 -56  d= -1  met
LON19 -83  d=-38  VIOLATED   LON19 -93  d=-37  VIOLATED <- being carried away
LON20 -83  d=  0  met        LON20 -92  d=  1  met      <- PARKED far away
LON21 -82  d=  1  met        LON21 -86  d=  6  met      <- still parked (d=6 = band edge)
LON22 -54  d= 28  VIOLATED   LON22 -69  d= 17  VIOLATED <- being carried back
LON23 -50  d=  4  met        LON23 -59  d= 10  VIOLATED <- settling
```

**First: the expectation measures what it claims to.** The windows where the T-Deck sat
parked in another room at **−83 / −93 dBm** were **MET**. A far but stationary link is a
stable link, and the prediction was not fooled by a 40 dB gap — only by *change*. This is
the design working, and it is worth stating because it is what makes the violations below
trustworthy rather than noise.

**Rule 3, computed by hand from these records** (start `conf:128`; met +2 saturating,
violated −16 floor 0 / sal +8):

| belief | conf | sal | max streak | contradiction |
|---|---|---|---|---|
| link-stable espnow | 128 → **106** (−22) | 16 | 1 | no |
| link-stable ble | 128 → **88** (−40) | 24 | 2 | **raised** |
| pooled | 128 → **66** | — | — | — |

Violation rate **35.7%** — **3.2× the 1/9 break-even**, so Rule 3 drives confidence hard
down.

### ⚠ Verdict on `+2/−16`: the asymmetry assumes violations are EXCEPTIONAL. Here they are ROUTINE.

The 1:8 ratio is a good guard against confirmation bias *for a claim that should almost
always hold*. "This link is stable" does not almost always hold in a fleet that contains a
designated roamer — and recovery costs **8 met windows per violated one**, so a peer that
moves even once an hour keeps every link belief permanently depressed. That behaviour is
not *self-regulating*; it is **self-extinguishing**.

And note *why* the framing is suspect: **the node is penalised for its peer's behaviour.**
The Cardputer never moved. RSSI cannot say which end of a pair moved, so an agent that did
exactly what it claimed — held still — lost 22–40 confidence for someone else's walk. A
belief the agent cannot act on is a strange thing to punish it for.

So the honest answer to "did `+2/−16` behave as designed?" is: **yes, and that is the
problem.** It did precisely what the numbers specify, and the result is a belief that
decays whenever the world behaves normally. Either the constants need to be domain-scaled,
or Rule 3 needs to distinguish "my model was wrong" from "the world legitimately changed" —
which the current formulation cannot, because a violated expectation reports only that the
prediction failed, never why.

### ⚠ Verdict on `K = 3`: it would NOT have fired — on a complete relocation

Device-reported consecutive-violation streaks across the run: `0, 0, 1, 0, 0, 1, 2`.
**Max 2, one short of K.** A peer physically relocating to another room and back never
tripped the abort.

The reason is structural: at 60 s windows, `K = 3` demands **three continuous minutes of
changing geometry**, and ordinary movement between two places does not last that long — the
roamer arrives and stops, and the very next window is `met` because the new position is
also stable. **On this observable K=3 can essentially never fire**, so Stage E would keep
asserting a stale distance straight through a relocation.

**`K` and the window length are not independent knobs**, and no statement of `K` is
meaningful without the window it counts. Either K drops to 2, or the window shortens, or
Rule 4 needs a trigger other than consecutive-window counting. This is, as far as either
repo knows, the first evidence about `K` from any domain.

---

### 2.7 What Stage D actually requires (discovered by trying to build it)

**a. The node's own TTDB carries ZERO `[ew]` blocks.** Rule 3 moves `conf`/`sal`, and
there is nothing in this node's store that has either. The two globes that do
(`rfc.ttdb.md` 36, `feelings.ttdb.md` 46) are read-only reference corpora in separate
files. **Stage D must first create the thing it reconciles.** This is not a `RT` quirk:
Rule 3 silently assumes the acting agent's store already carries epistemic weight on the
belief being tested, and a percept-writing device has no reason to have written one.

**b. `Ttdb` has no in-place update** — only `appendRecord`, `removeLane`,
`removeLaneRange`. Moving a `conf` means rewriting a whole lane, i.e. a Dream-Cycle-scale
flash operation rather than a per-window one. That is *consistent* with Rule 2 (the live
loop must not mutate) but it means reconciliation cannot be a cheap running total.

**c. And it should not be one anyway.** To answer the question Draft 06 actually leaves
open — *"the reconciliation was performed by hand, by an outside reader"* — Stage D must
recompute its tally **by reading the `@LAT92` records back off flash**, the way an outside
reader would. A RAM counter kept during scoring would be cheaper, would produce the same
numbers, and **would not prove the thing**: it would be the node remembering, not the
store reconciling.

---

## 0. Status in one paragraph

`RT` pulled the five drifted spec files and merged the canonical feelings store into
both device globes. **`MotionPercept` now emits a paired `@PERCEPT:before` →
`@PERCEPT:after` record on a motion verdict change, and on 2026-08-02 an M5Stack
Cardputer ADV (node `0x300`) wrote two of them to its own flash** — one in each
direction — from nine 60 s accelerometer windows while it was left still, carried, and
set down. **The transition form is instantiated. `@LAT98LON6`'s count is no longer
zero.** What has *not* happened: the node made no prediction, kept no outcome log, and
ran no reconciliation. **`+2/−16` and `K = 3` remain exactly as unrun as in Draft 06.**

---

## 1. Part 4.1, item by item

| Part 4.1 asks for | Status |
|---|---|
| **A.** Stage C side-log records, verbatim | **Not delivered.** Stage C not started; there is no side log. |
| **B.** A reconciliation of `@LAT20LON3`, computed not asserted | **Not delivered.** Rules 3 and 4 never executed. No tally exists, so no `conf` movement exists. Asserting one is the failure mode B was written to prevent. |
| **C.** A verdict on the constants | **Not delivered.** Zero evidence either way, still. |
| **D.** New records for what only hardware could show | **Delivered — §2.** Four findings, three of which only a powered device could produce. |
| **E.** Log where you got blocked | **§4.** Narrower than it was: the T-Deck was not on the cable, and Stages B–E were not begun. |

**Do not read Stage A as "the invitation is answered."** `@LAT98LON2` asks for a device
*acting on sensor expectations*. This device notices and records change. It does not
yet expect anything, so nothing it does can be wrong, so there is still nothing to
reconcile. The ESP32 half of the invitation is **advanced, not closed**.

---

## 2. What comes back (Part 4.1 D)

### 2.1 The gap was real on this fleet, and it is measured, not argued

Before the change, the Cardputer's TTDB was pulled off flash intact (41400 B, 114
records, kept at `master/preflash-2026-08-02/cardputer_ttdb.md`):

> **34 `@LAT95` motion-state records. Zero `@PERCEPT:` markers.**

Thirty-four windows of a device noticing its own motion, and not one recorded
difference. `@LAT98LON6`'s conclusion — *the gap is representational, not a missing
feature* — is exactly right, and this is a second independent instance of it in a
domain (embedded sensing) far from LOCUS's.

A related datum, because it shows how the failure hides: `RT` was *already* using the
Locus namespace. `master/gps-fixes.md` carries four `@PERCEPT:GPS` records. They are
unpaired state snapshots — precisely §5.2's *"modeling isolated facts"* — so using the
namespace bought nothing. **The form is not the marker; the form is the pairing.**

### 2.2 It runs. Here is the record the device wrote

Two transitions from nine windows, both directions, written by the node to its own
flash with no laptop involvement:

```
[  246.7s] [motion] still -> moving TRANSITION -> @LAT93LON0 (559B, TTDB 6226B)

@LAT93LON0 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON3,derived_from@LAT95LON4

**TRANSITION** t_ms:300010 synced:0 node:0x300 from:still to:moving dt_ms:60000
  @PERCEPT:before state:still  t_ms:240010 window_ms:60010 n:1000 moving_permille:52  dev_mean_mg:22  dev_max_mg:739  moving_ms:3128  lane:@LAT95LON3
  @PERCEPT:after  state:moving t_ms:300010 window_ms:60000 n:999  moving_permille:735 dev_mean_mg:227 dev_max_mg:1359 moving_ms:44107 lane:@LAT95LON4
**DELTA** edge:became d_permille:683 d_dev_mean_mg:205 d_dev_max_mg:620
```

and `@LAT93LON1`, `from:moving to:still`, `derived_from@LAT95LON6,@LAT95LON7`.

**Cost, measured:** **559 B per pair** on flash — *identical* to the native test's
figure, so the format is pinned end to end. TTDB grew 3267 → 8773 B across the run;
the two pairs are 1118 B of that. At `MOTIONPERCEPT_MAX_TRANSITION_LANE 32` the lane's
ceiling is ~18 KB. Transitions are bounded by how often the node changes state, not by
uptime: a node on a shelf writes **none**.

`synced:0` and `created:0` throughout — the node was alone with no fleet clock, so the
pairs carry local `millis()` and correctly decline to claim cross-node orderability.

### 2.3 ⚠ `@PERCEPT:` collides with `TTDB-RFC-0001 §3` — confirmed on device

**Merge this one first; it silently corrupts stores.**

`TTDB-RFC-0001 §3` defines a record header as *a line whose first character is `@`*,
and every reader in this corpus implements exactly that (`RT`: `TTDB.cpp:24`). An
unindented `@PERCEPT:before` inside a record body **is a record header**. It is
indexed, fails to parse, and becomes a phantom `(0,0)` record.

`RT` indents both `@PERCEPT:` lines two spaces. Verified on the device, not just in
the test — the node's own boot scan reports:

```
TTDB loaded: 8773 bytes, 26 records
```

and the pulled file contains exactly **26** lines beginning with `@`, all of them
`@LAT`: **zero phantoms from four `@PERCEPT:` markers.** Unindented, that count would
have been 30, and the store would have carried four unparseable records that every
consumer would have had to skip.

**Suggested amendment: TTDB-RFC-0006 §5 should state that `@PERCEPT:` markers inside a
record body MUST NOT begin a line** (or TTDB-RFC-0001 §3 should carve out an escape).
This will bite every implementation that writes Locus percepts into a TTDB.

### 2.4 §7.1 IS enforceable — but only as a single atomic append

Part 4.2 asked whether write-time pairing is enforceable in a fixed-RAM streaming
writer. **It is, and the constraint is sharper than "enforce it."**

`Ttdb::appendRecord` has no transaction. Writing `before` and `after` as two records
means power loss between the appends leaves an orphaned `before` on flash — the exact
thing §7.1 forbids, produced by no bug, on a device that can lose power at any instant.
**One atomic append is the only construction that keeps the promise**, so both halves
live in one record body.

The cost is that the pair is no longer two addressable nodes at the TTDB record level.
`RT` compensates by *also* writing `derived_from` edges to each half's originating
`@LAT95` record, so the pairing is traversable from the edge list — but those can
dangle once the percept lane wraps, which is why both state blocks are duplicated
inline. **The record is self-sufficient; the edges are a convenience.** If §5.2's
"optimise for edge traversal" is meant to bind at the record level rather than the
claim level, that tension deserves an explicit sentence.

### 2.5 ⚠ NEW, and only hardware could show it: **the transition is quantized to the window**

The device was set down partway through window `@LAT95LON6`. That window still scored
**129 permille** — just over the 100 threshold — so it was judged `moving`, and the
`moving → still` edge did not fire until the *next* window closed, 60 s later.

**A transition's timestamp is therefore accurate to ±1 window, not to the physical
event.** The verdict threshold is applied to a whole window, so the edge lands on a
window boundary rather than on the change.

This is fine for Stage B/C, where the question is *whether* the expectation held. It is
a real problem for anything that wants to order transitions finely across nodes — and
it **compounds with, rather than replaces, the unresolved multi-second loop stall**
documented in `RT/CLAUDE.md`. (Worst loop pass over this 7-minute run was a benign
200 ms; per `RT`'s own `lp` lesson, a clean window proves nothing about the stall's
absence.) Anything Phase-3/TDoA-shaped needs a sub-window transition timestamp first.

### 2.6 A conformant §7.1 writer fails *closed*, which is dangerous

A pair that does not fit its buffer renders **0 bytes rather than a truncated
`before`** — correct per §7.1, since an orphan is an error rather than partial data.
But a first pass sized the buffer at 512 B against a 589 B pair, so **every transition
was silently dropped while the tier looked perfectly healthy.** Same shape for a full
lane. Under-reporting reads as evidence of a node that never changed state, which is
the *opposite* claim. **Implementations of §7.1 should be required to log the refusal.**
`RT` now does; only the native test caught the original.

---

## 3. What `@LAT98LON6` should now do

Part 4.2 predicted that if the transition form shipped, `@LAT98LON6` would be
*"contradicted by observation"* and should take its own medicine as `@LAT98LON2` did.
**That condition is now met, and it is met by execution, not by compilation.** The
form is instantiated; records exist on flash; they were pulled back and read.

Applying `@LAT20LON3` Rule 3 to it, by hand, from outside — with the same caveat Draft
06 already carries:

- **`@LAT98LON6`: `conf 220 → 204` (−16), `sal 40 → 48` (+8), `rev 0 → 1`.** Note
  should say plainly that its "zero instances" count was correct when written and was
  overtaken on 2026-08-02 by an ESP32 fleet, naming this document.
- **`@LAT20LON3`: unchanged at `conf:122 rev:1 sal:200`.** Stage A carries no
  expectation, so Rule 1 gained nothing here, and Rules 2–4 were not exercised. It
  remains the highest-EPS record in the store — correctly, because this session did not
  reduce the uncertainty that makes it so. **Resist the pull to reward it for adjacent
  progress.**
- New belief for the hardware result, edged `supports@LAT20LON3`:

```
@LAT98LON7 | relates:contradicts@LAT98LON6,supports@LAT20LON3,refines@LAT98LON2
conf:240 sal:70

**The transition form runs on a constrained device.** An ESP32 (M5Stack
Cardputer ADV, node 0x300, robot_team @LAT93) wrote paired
@PERCEPT:before/after records to its own flash from accelerometer windows,
2026-08-02: two transitions from nine 60 s windows, both directions, 559 B
each. Before the change the same node held 34 motion-STATE records and zero
@PERCEPT: markers — the gap of @LAT98LON6, measured rather than argued.
Three implementation results: §7.1's write-time pairing is enforceable ONLY
as a single atomic append (a two-append pair orphans on power loss); an
unindented @PERCEPT: line inside a body is a record header under
TTDB-RFC-0001 §3, so the namespaces collide and the form silently produces
phantom records; and the transition is quantized to the window, so its
timestamp is accurate to ±1 window, not to the event. conf 240 = proven on
hardware, per this store's own scale. It does NOT corroborate Rules 2-4:
the node testifies to nothing and reconciles nothing.
```

`conf:240` is deliberate, and is Draft 06's own scale (240 = proven on hardware). The
last clause is the load-bearing one: this record must not be read as evidence for the
part that is still unevidenced.

---

## 4. Where it stopped (Part 4.1 E)

1. **The T-Deck was not on the cable**, so its FS is not reflashed and that console is
   still displaying a **v1.0 spec globe** with no §7 `opposes`. One command when it is
   next plugged in.
2. **Stages B–E were not begun.** Stage A materializes the difference; B (expectation),
   C (side log), D (asymmetric reconcile) and E (`K = 3` abort) are untouched. **D is
   the actual experiment** — the handoff's own warning against letting A become the
   deliverable stands, and this document is not a claim to have run it.
3. **Only the Cardputer has an IMU**, so the tier is single-node. Multi-node transition
   ordering is unexercised and, per §2.5, needs a sub-window timestamp before it would
   mean anything.
4. Draft 06's standing caveat is **not** discharged. The reconciliation proposed in §3
   is still performed *by hand, by an outside reader*. A node running Stage D in its own
   Dream Cycle is what closes that, and that has not happened.

---

## 5. What changes in `TTE` when this lands

- **`agent-memory-system_ttdb.md`** — §3's three edits; bump the `agent_note` draft.
- **`RFCs/TTDB-RFC-0006`** — the §5 line-start prohibition (§2.3); optionally the §7.1
  atomicity reading (§2.4) and the fail-closed logging requirement (§2.6).
- **`README.md`** — the closing section's claim is that what's missing is *"one loop
  that writes the difference down."* **That sentence is now answered by a fleet of
  ESP32s**, and can say so with 559 B and two records attached. It should say in the
  same breath that the loop still does not *predict*, so the interesting half is open.
- **`RFCs/ARC-RFC-0001`** — still no second-domain evidence for `K`; unchanged.
- **`RFCs/TTN-RFC-0011`** — the §2.5 debt from the handoff is still unsettled, and
  §2.5 here adds to it: window quantization is a timing-integrity fact that any
  amplitude-or-timing tier inherits.
- **`research/`** — nothing yet. The constants have still not been run, so there is no
  result to route there, wrong or otherwise.

---

*Authored from `robot_team`. Every number above was read off the device or its pulled
TTDB. Where something was not run, this document says so rather than estimating it.*
