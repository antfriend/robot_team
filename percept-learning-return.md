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
