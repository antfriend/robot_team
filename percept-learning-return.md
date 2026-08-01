# Return: `robot_team` → `toot-toot-engineering`

**Staged in `robot_team`; destined for `toot-toot-engineering`.**
Answers `percept-learning-handoff.md` Part 4. Authored against `robot_team` @
`fe8e47f` + this session's working tree and `toot-toot-engineering` @ `cdac8d4`,
both read at 2026-08-01.

**Read §0 before merging anything.** This is a *partial* return. The handoff asked
for five things back (Part 4.1 A–E); this delivers **D and E**, and explicitly
declines to deliver A, B and C because the run that would produce them has not
happened. Nothing here is projected, extrapolated, or assumed.

Throughout: `TTE` = `toot-toot-engineering`, `RT` = `robot_team`.

---

## 0. Status in one paragraph

`RT` pulled the five drifted spec files and merged the canonical feelings store into
both device globes, so the repo is in sync (Part 1 ①②). Stage A is **built**:
`MotionPercept` now emits a paired `@PERCEPT:before` → `@PERCEPT:after` record on a
motion verdict change, pinned by a new 48-check native test, and the Cardputer sketch
carrying it compiles at 41% flash. **It has never run on a device.** No ESP32 was
attached to the build machine this session — enumerating `Win32_PnPEntity` found only
two Bluetooth virtual COM ports, no `VID_303A&PID_1001`. So the transition form exists
as code and as a tested format, and **zero transition records exist in any store**.
Stages B–E were not started; **`+2/−16` and `K = 3` remain exactly as unrun as they
were in Draft 06.**

---

## 1. What does NOT come back yet — and why (Part 4.1 E)

`TTDB-RFC-0009` asks for the location of the block, because the location is the
measurement. Precisely:

| Part 4.1 asks for | Status |
|---|---|
| **A.** Stage C side-log records, verbatim | **Not delivered.** Stage C not started. There is no side log. |
| **B.** A reconciliation of `@LAT20LON3`, computed not asserted | **Not delivered.** Rules 3 and 4 never executed. There is no tally, so there is no `conf` movement — asserting one would be the exact failure mode B was written to prevent. |
| **C.** A verdict on the constants | **Not delivered.** `+2/−16` and `K = 3` were not exercised. Still zero evidence either way. |
| **D.** New records for what only hardware could show | **Partially delivered** — see §2. Two findings are properties of *implementing* the form in a fixed-RAM streaming writer and did not need a powered device; everything that needs a device (in-situ flash cost, lane pruning under real motion, clock stability across nodes) is not here. |
| **E.** Log where you got blocked | **This document.** |

**The block, exactly.** Not a design problem, not a store that could not choose a
repair path — simply no hardware on the end of a cable. Two consequences worth stating
because they are easy to gloss:

1. **Native verification is not the claim.** 48 checks pass against the real
   `MotionPercept.cpp`; they prove the *format* and the *state machine*. They say
   nothing about flash cost in situ, lane behaviour under real accelerometer noise, or
   whether the fleet clock can order transitions across nodes — which is live doubt,
   because `RT/CLAUDE.md` documents an unresolved **multi-second loop stall** that is
   in no sketch's loop body and would invalidate any timing-sensitive tier.
2. **Do not read Stage A as "the invitation is answered."** `@LAT98LON2` asks for a
   device *acting on sensor expectations*. Stage A materializes the difference; it does
   not predict, testify, or reconcile. The ESP32 half of the invitation is still open.

---

## 2. What DOES come back: two findings about the form itself (Part 4.1 D)

Both are implementation facts discovered by building `TTDB-RFC-0006 §5` on a
constrained streaming writer. Part 4.2 anticipated the first as a possible amendment;
the second was not anticipated by either repo.

### 2.1 §7.1 IS enforceable — but only if the pair is ONE record

§7.1 says implementations MUST enforce the pairing at write time and that orphans are
errors, not partial data. Part 4.2 asked whether that is actually enforceable in a
fixed-RAM streaming writer. **It is, and the constraint is sharper than "enforce it":**

`Ttdb::appendRecord` has no transaction. Writing `before` and `after` as two records
means power loss between the two appends leaves an orphaned `before` on flash — the
precise thing §7.1 forbids, produced by no bug, on a device that can lose power at any
instant. **A single atomic append is the only construction that keeps the promise.**
So both halves live in one record body, and §7.1 for constrained implementations is
better read as: *the pair must be written in one atomic operation*, not merely
*validated together*.

Cost of that choice, stated plainly: the pair is no longer two addressable nodes at the
TTDB record level. `RT` compensates by *also* writing `derived_from` edges to each
half's originating `@LAT95` record, so the pairing is traversable from the edge list —
but those edges can dangle once the percept lane wraps, which is why both state blocks
are duplicated inline. **The record is self-sufficient; the edges are a convenience.**
If §5.2's "storage SHOULD optimise for edge traversal" is meant to bind at the record
level rather than the claim level, that tension is worth an explicit sentence in the RFC.

### 2.2 ⚠ `@PERCEPT:` collides with `TTDB-RFC-0001 §3`

**This is the finding to merge first, because it silently corrupts stores.**

`TTDB-RFC-0001 §3` defines a record header as *a line whose first character is `@`*.
Every implementation in this corpus implements exactly that — `RT`'s reader is a
one-line scan (`TTDB.cpp:24`: `if (line_start && c == '@') ...`).

Therefore an unindented `@PERCEPT:before` inside a record body **is a record header**.
It is indexed, fails to parse as one, and becomes a phantom `(0,0)` record on the
device. The Locus namespace and the TTDB record syntax occupy the same lexical slot.

`RT` resolves it by indenting both `@PERCEPT:` lines two spaces, and the native test
asserts the indentation and asserts the whole pair scans as exactly **one** record
header. But the collision is a property of the two RFCs, not of `RT`, and any
implementation writing Locus percepts into a TTDB will hit it. **Suggested amendment:
TTDB-RFC-0006 §5 should state that `@PERCEPT:` markers appearing inside a record body
MUST NOT begin a line**, or TTDB-RFC-0001 §3 should carve out an escape.

Corroborating evidence that this is a live trap and not theoretical: `RT` already used
the namespace before this work — `master/gps-fixes.md` carries four `@PERCEPT:GPS`
markers **at line start**. That file happens never to be streamed through the reader,
so it has been harmless. It would not have been on a node.

### 2.3 A smaller one: silence is the dangerous failure mode

Two places in this work failed *quietly* and were caught only by a test:

- A pair that does not fit its buffer renders **0 bytes rather than a truncated
  `before`** (correct per §7.1 — an orphan is an error). A first pass sized the buffer
  at 512 B against a measured **589 B** pair, so every transition was silently dropped
  while the tier looked healthy. **A conformant §7.1 writer fails closed, which means
  an under-sized buffer is indistinguishable from a node that never changed state.**
  Implementations should log the refusal; `RT` now does.
- Same shape for a full lane: dropping transitions silently looks identical to a node
  that never moved, which is the *opposite* claim. Also logged now.

Neither is deep, but both argue that the transition form needs its writer to be loud,
because its natural failure is under-reporting, and under-reporting reads as evidence.

---

## 3. What `@LAT98LON6` should do (and should NOT do yet)

Part 4.2 anticipated that if the transition form shipped, `@LAT98LON6` would be
*"contradicted by observation"* and take `conf −16 / sal +8` as `@LAT98LON2` did.

**Not yet.** `@LAT98LON6`'s claim is a count of `@PERCEPT:` record headers **across
stores**, and that count in `RT` is still **zero**: the firmware can emit the form, but
no device has run it, so no store contains a pair. A capability is not an instance.
Applying `−16` now would be exactly the confirmation-bias-in-reverse that Rule 3's
asymmetry exists to prevent, and it would be applied by hand by an outside reader —
the caveat Draft 06 already carries.

Recommended instead, if you want the record to move at all:

- **`@LAT98LON6`: leave `conf:220` alone.** Optionally add a `rev 1` note that an
  implementation now exists and is pending first execution, naming this document. The
  count it asserts is still correct.
- **`@LAT20LON3`: unchanged at `conf:122 rev:1 sal:200`.** Rule 1 gained nothing here
  (Stage A carries no expectation); Rules 2–4 were not exercised. It remains the
  highest-EPS record in the store, which is the right answer — this session did not
  reduce the uncertainty that makes it so.
- A new belief in the lat-98 lane is defensible for §2.1/§2.2, since those *are*
  observations and they *are* about the form. Suggested shape, for you to weigh rather
  than paste:

```
@LAT98LON7 | relates:supports@LAT98LON6,refines@LAT20LON3
conf:200 sal:60

**The transition form is implementable on a constrained device — and collides
with the record syntax.** An ESP32 fleet built @PERCEPT:before/after on a
fixed-RAM streaming writer (robot_team, MotionPercept @LAT93, 2026-08-01).
Two results, neither needing the device to be powered: §7.1's write-time
pairing is enforceable ONLY as a single atomic append, because a two-append
pair orphans on power loss; and an unindented @PERCEPT: line inside a body is
a record header under TTDB-RFC-0001 §3, so the two namespaces collide and the
form silently produces phantom records. conf 200, not higher: verified by
native test and by compilation, NOT by a device — the store has not yet been
written to by hardware.
```

Note the deliberate `conf:200`. Draft 06's own scale reads 240 = proven on hardware,
210 = stable and exercised, 195 = first instance live. This is a first instance that is
*not* live, so it sits below 210 and below the value a hardware run would earn.

---

## 4. What changes in `TTE` when the hardware run DOES happen

Unchanged from the handoff's Part 4.2, with one addition: the run should report
**whether `@LAT93` records survive a `CMD_CLEAR_PERCEPTS`**. `RT` deliberately put the
transition lane *outside* the 94–97 block that command drops, on the reasoning that a
percept window is cheap raw evidence while a transition is the thing the node learns
from. If TTE's model of the Dream Cycle expects derived records to be prunable with
their sources, that is a disagreement worth settling before Stage D relies on the lane
being there.

`README.md`'s closing section should **not** be rewritten yet. Its claim is that what
is missing is *"one loop that writes the difference down."* A loop that has never run
does not answer it. When it runs, that sentence is answerable in one line with a
number attached — and if the constants come back wrong in an interesting way, Part
4.2's routing to `research/` is the right destination, not an RFC.

---

*Authored from `robot_team`. Every count, path, and line number above was verified
against the working tree, not recalled. Where something was not run, this document says
so rather than estimating it.*
