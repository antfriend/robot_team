# Handoff: spec sync + percept-learning focus → `robot_team`

**Staged in `toot-toot-engineering`; destined for `robot_team`.**
Copy this file into the `robot_team` repo root (suggested name:
`percept-learning-handoff.md`) and work it from there. It was authored against
`toot-toot-engineering` @ `cdac8d4` and `robot_team` @ `fe8e47f`, both read at
2026-08-01.

Two repos, one system: `toot-toot-engineering` is the spec, `robot_team` is the
reference implementation. This document does three things, in order:

1. **Part 1 — Pull.** Which files have drifted, which direction they go, and
   which of them are flashed onto hardware.
2. **Part 2 — Merge.** The findings from the spec side that change what
   `robot_team` should build next.
3. **Part 3 — Build.** A staged percept-learning experiment that `robot_team`
   is uniquely positioned to run.
4. **Part 4 — Conclusion.** What comes *back* here when it runs, in the exact
   form the spec store requires.

Throughout: `TTE` = `toot-toot-engineering`, `RT` = `robot_team`.

---

## Part 1 — Files to pull

`RT/replicate/RFCs/` is a fork of `TTE/RFCs/` (moved to `replicate/` on
2026-07-31). **26 of 31 files are byte-identical.** Five have drifted, and
**TTE is the newer side on all five** — verified by content, not by timestamp.

### 1.1 The five drifted files

| File | TTE (pull FROM) | RT (currently) |
|---|---|---|
| `RFCs/TTDB-RFC-0003-Typed-Edges.md` | **v1.1** — adds §7 symmetric types + `opposes` | v1.0, §7 absent |
| `RFCs/TTN-RFC-0002-Typed-Edges.md` | **v1.1** — adds the semantic-polarity group | v1.0 |
| `RFCs/INDEX.md` | reflects both v1.1 bumps | stale entries |
| `RFCs/TTDB-RFC-0006-Experiential-Perception-as-Synthetic-Model.md` | §5/§8 point at `feelings_ttdb.md` | points at `emotions.md` — **a file that does not exist in either repo** |
| `RFCs/rfc.ttdb.md` | `@LAT10LON3` `rev:1 sal:140 touched:1785542400` | `rev:0 sal:130 touched:1774396800` |

`RFCs/TTN-RFC-0011-Semantic-Positioning.md` — the primary hypothesis — is
**byte-identical** in both. Nothing to pull; see §2.5 for why that is itself a
finding.

### 1.2 Copy plan

Straight copies into `RT/replicate/RFCs/`:

```bash
# from the RT repo root, with TTE checked out alongside
TTE=../toot-toot-engineering
for f in INDEX.md \
         TTDB-RFC-0003-Typed-Edges.md \
         TTDB-RFC-0006-Experiential-Perception-as-Synthetic-Model.md \
         TTN-RFC-0002-Typed-Edges.md \
         rfc.ttdb.md ; do
  cp "$TTE/RFCs/$f" "replicate/RFCs/$f"
done

# verify: this should print nothing at all
for f in $TTE/RFCs/*.md; do
  cmp -s "$f" "replicate/RFCs/$(basename $f)" || echo "STILL DIFFERS: $(basename $f)"
done
```

Also check `RT/replicate/agent-memory-system_ttdb.md` against
`TTE/agent-memory-system_ttdb.md` — they differ, and TTE is Draft 06
(2026-08-01), which carries the findings in Part 2. Pull it the same way.

### 1.3 ⚠ The on-device copies are NOT straight copies

`RT` carries the corpus on hardware in two places, and they follow different
rules:

| Path | Rule |
|---|---|
| `firmware/tdeck_console/data/rfc.ttdb.md` | **Straight copy** of `replicate/RFCs/rfc.ttdb.md`. Overwrite it. |
| `firmware/cardputer_console/data/rfc.ttdb.md` | Same. Overwrite it. |
| `firmware/tdeck_console/data/feelings.ttdb.md` | **MERGE, do not overwrite.** |
| `firmware/cardputer_console/data/feelings.ttdb.md` | **MERGE, do not overwrite.** |

The feelings globes are deliberate node-local *supersets*. The canonical
`TTE/feelings_ttdb.md` has 43 `@LAT` records; the T-Deck's has 44 and the
Cardputer's has 45, and the extras are `type:band` overlay records
(`@LAT14LON-6` V4-A timekeeper, `@LAT-6LON-8` V4-B ally, `@LAT6LON8` V4-C edge)
that place the band members on the affective field for the hero's-arc song.
Those are `RT` content and must survive. The two device copies have also drifted
from *each other*, which is its own small problem worth resolving while you're
in there.

Merge procedure: take the canonical 43 records from TTE as the base, re-apply
the `type:band` records and the T-Deck-specific header paragraph, and diff the
result against both device copies before flashing.

### 1.4 Reflash — the sync is not done until this runs

The RFC corpus is *displayed on the handhelds*. Until the filesystem images are
rewritten, both consoles show a v1.0 spec globe — including a Typed Edges RFC
with no `opposes`, which is the very finding Part 2 turns on. Per `RT/CLAUDE.md`:

```powershell
scripts/Upload-Tdeck-FS.ps1     -Node tdeck_console     -Port <COMx>
scripts/Upload-Cardputer-FS.ps1 -Node cardputer_console -Port <COMx>
```

⚠ Use the per-node script, never `Upload-V4-FS.ps1` — huge_app puts LittleFS at
`0x310000`, the V4 script writes `0x290000`, and flashing at the wrong offset
fails *silently* (empty globe, app otherwise fine). ⚠ The T-Deck needs manual
bootloader entry (hold trackball-click/GPIO0 + tap RST); the Cardputer's
auto-reset works.

Confirm on-device by walking the RFC globe to the Typed Edges record and looking
for §7. If `opposes` isn't there, the image didn't land.

---

## Part 2 — Findings to merge

### 2.1 `opposes` — semantic polarity is now a typed edge (TTDB-RFC-0003 §7, v1.1)

A new edge type, **symmetric**, asserting that two endpoints sit at opposite
ends of one dimension. It is explicitly *not* `contradicts`:

| | `contradicts` | `opposes` |
|---|---|---|
| Kind | Epistemic | Semantic |
| Asserts | These two claims cannot both hold | These two concepts are antonyms |
| Endpoint truth | At most one is true | **Both may be true simultaneously** |

Symmetry is a property of the *type*, not an exception to traversal:
implementations MUST NOT infer the reverse edge, so an author asserting
`opposes` writes it on **both** records. Every existing parser stays correct
unmodified.

**Why `RT` should care.** The rationale section (§7.3) is about stores exactly
like `RT`'s: *"Stores may encode polarity positionally — for example a
coordinate mapping in which latitude carries valence. Position is not available
to a consumer reading the edge list, which is what implementations in this
corpus actually traverse."* The feelings globe encodes Joy/Grief polarity in
latitude. The T-Deck's renderer walks edges. Without `opposes`, the hero's-arc
song's most load-bearing relation — the grief the band holds for the returning
T-Deck, against the joy it resolves into — is invisible to the thing drawing it.

**Concrete work in `RT`:** add `opposes` edges to the opposed pairs in both
device `feelings.ttdb.md` copies (both directions, per §7.1), and decide whether
the T-Deck's globe renderer draws a polarity axis. A validator that reports
one-directional symmetric edges is a natural native test.

### 2.2 The transition-form gap — the central finding

`TTDB-RFC-0006 §5` makes the `@PERCEPT:before` → `@PERCEPT:after` paired node
**"formal and non-negotiable… the binding contract of any system claiming
conformance to Locus."** §5.2: *the unit of perceptual knowledge is not a node
but an edge — the nodes are addressed; the edge is the claim.* §7.1:
implementations MUST enforce the pairing at write time; orphaned percepts are
errors.

`TTE/agent-memory-system_ttdb.md` `@LAT98LON6` (conf 220, new in Draft 06)
reports the count of `@PERCEPT:` record headers across every store examined:
**zero.** Including LOCUS, the ARC-AGI-3 agent whose own umwelt instructs it to
"model game learning as transitions." It records state updates; `@BELIEF:` is
instantiated 130 times there.

**I verified this holds in `RT` too, and it does.** `@PERCEPT:before`/`after`
appears in `RT` only as *spec text carried on the handhelds*
(`firmware/tdeck_console/data/rfc.ttdb.md:178,264` and the Cardputer's copy).
Zero instances in any firmware or in `orchestrator/companion.py`.

The conclusion `@LAT98LON6` draws is the one to carry over: **the gap is
representational, not a missing feature.** A loop that overwrites state never
materializes the difference, and the difference is the datum — there is nothing
to compute prediction error over.

### 2.3 Learning from Action — the four rules and their untested constants

`@LAT20LON3` (conf 122, sal 200) is the spec store's highest-EPS record: the
newest, least-proven, most-relied-upon idea in the system. Verbatim rules:

- **Rule 1** — every action carries an *expectation*: a predicted transition
  re-derived from current state, never a precomputed route. An action without
  one is a reflex — it executes but cannot teach.
- **Rule 2** — outcomes are **appended to a side log** (acting record, edge,
  expectation, observed, verdict, provenance). The live loop *testifies, never
  mutates.*
- **Rule 3** — reconciliation folds outcomes into weights **asymmetrically**:
  expectation met `conf +2` saturating; violated `conf −16` floor 0, `sal +8`;
  repeated violation raises a contradiction flag. The ~1:8 asymmetry guards
  against confirmation bias and makes EPS self-regulating.
- **Rule 4** — **K consecutive expectation failures (K = 3)** abort the plan
  back to baseline exploration. Plans are hypotheses; failing hypotheses lose
  control.

Status as of Draft 06: **Rule 1 corroborated** by LOCUS (39 sessions, +2
awarded). **Rule 2 violated** by it (revises in place instead of appending).
**Rules 3 and 4 never exercised by anything.** The `+2/−16` constants and `K =
3` are still guesses.

### 2.4 `RT` is the body the invitation asks for

`@LAT98LON2`: *"An ESP32 acting on sensor expectations, or an LLM harness acting
on predicted tool results, either will do."* The LLM-harness half is answered
and answered incompletely. **The ESP32 half is untouched, and `RT` is the only
ESP32 fleet in the project.**

`RT` already has, on verified hardware, every part except the loop: four percept
tiers writing real records (`@LAT97` link, `@LAT96` entity, `@LAT95` motion,
`@LAT94` acoustic), an `[ew]`-bearing TTDB per node, `Ttdb::appendRecord`,
belief push-back, a Dream Cycle, and a fleet clock to stamp transitions with.

### 2.5 What flows the other way: TTN-RFC-0011 has not been updated from the field

`TTN-RFC-0011-Semantic-Positioning.md` is byte-identical across both repos,
meaning **no field result from `RT` has ever been folded back into the spec of
the hypothesis it is testing.** At minimum these are unrecorded:

- `AcousticPercept`'s `@LAT94` fleet-clock timestamp of the loudest transient —
  explicit Phase-3 TDoA groundwork, an evidence tier RFC-0011 anticipates but
  does not yet describe as implemented.
- `MotionPercept` existing at all: it makes "the observer held still" checkable
  rather than assumed, which is a stated precondition of every amplitude tier.
- The **multi-second loop stall** documented in `RT/CLAUDE.md` — not in any
  sketch's loop body, loop task descheduled between iterations, async WiFi scan
  exonerated. This is a timing-integrity problem that would invalidate any TDoA
  tier, and RFC-0011 says nothing about it.

Treat that as a standing debt, not part of this handoff's critical path.

---

## Part 3 — The build: percept learning on `RT`

The gap in §2.2 and the constants in §2.3 point at one experiment, and `RT`
already contains the cheapest possible entry point.

### 3.0 Why `MotionPercept` is the place to start

`firmware/libraries/MotionPercept/` is **one step away from instantiating the
transition form.**

Today (`MotionPercept.cpp:92`, `MotionPercept.h:70-77`) it computes per window:

```c
const char* state = permille >= 100 ? "moving" : "still";
// appends: @LAT95LON<lane> ... **MOTION** state:<still|moving>
//          moving_permille:.. dev_mean_mg:.. dev_max_mg:.. moving_ms:..
```

One `@LAT95` record per 60 s window (`MOTIONPERCEPT_FLUSH_MS`), driven from
`cardputer_console.ino:3076` on the Cardputer's BMI270 at 20 Hz.

It writes each window's **state** and discards the **pairing**. It already holds
`last_moving_ms_` and knows the window it is closing; the object that knows the
previous window's verdict is the same object. A `still → moving` edge is the
smallest true `@PERCEPT:before` → `@PERCEPT:after` pair available anywhere in
the project, on a node (CARD-1) already on-device verified.

It is also the *right* datum, not just the cheapest: the header comment says
this tier exists because the 2026-07-07 walking range test proved a node carried
between stations fuses four places into one distance. The moment of transition
is exactly the thing that invalidates the other tiers' windows.

### Stage A — materialize the difference (satisfies §2.2, no learning yet)

Emit a paired record when the window verdict changes, per TTDB-RFC-0006 §5:

- `@PERCEPT:before` — the closing window's state block.
- `@PERCEPT:after` — the opening window's state block.
- The **edge between them is the claim**; both nodes addressed, neither orphaned
  (§7.1 forbids an `after` without a `before`).
- Stamp with the fleet clock (`synced` is already a `buildRecord` parameter) so
  transitions are orderable across nodes.

Constraints that already govern this library apply unchanged: fixed RAM, integer
math, no per-sample flash write, no Arduino dependency. **Write the native test
this time** — `MotionPercept.h:22-24` admits the tier has only ever been
verified on hardware, and `tests/` exists precisely for pinning record formats.

Stage A alone discharges `@LAT98LON6` and is worth doing on its own merits.

### Stage B — give the action an expectation (Rule 1)

An expectation must be *re-derived from current state*, never precomputed. The
natural pairing on this fleet:

> A `state:still` window is a positive claim that the node was anchored. If it
> was anchored, the next `@LAT97` link-percept window should show RSSI to a
> given peer within some band of the previous window's. Predict that before the
> window closes; record what actually happened.

This is a genuine prediction about the world made by a device, not a
bookkeeping exercise — and it is falsifiable within 60 s. `LinkPercept` already
produces the observable.

### Stage C — testify, do not mutate (Rule 2)

The rule LOCUS broke, and the one `RT` is structurally best placed to keep,
because `Ttdb::appendRecord` is already append-only and the percept lanes are
already side lanes. Add an outcome lane carrying the full tuple the rule
specifies: **acting record, edge, expectation, observed, verdict, provenance**.
Do not touch the `[ew]` block at this stage. Note the lane cap
(`MOTIONPERCEPT_MAX_LANE 48`, mirrored at `@LAT96`/`@LAT97`) and that `RT`'s
CLAUDE.md already flags unpruned percept lanes growing V4-B's TTDB to 54 KB —
decide the outcome lane's pruning policy up front.

### Stage D — reconcile asymmetrically (Rule 3) — **the actual experiment**

A pre-phase of the existing Dream Cycle, running over the Stage C log:
expectation met `conf +2` saturating; violated `conf −16` floor 0, `sal +8`;
repeated violation raises a contradiction flag.

**This is the untested part.** Everything before it is scaffolding. Run it long
enough that the constants are exercised rather than merely coded, then report
whether the 1:8 asymmetry actually makes EPS self-regulating on real sensor
noise — whether knowledge that works goes quiet and knowledge that fails gets
loud, or whether 60 s windows of accelerometer data flap fast enough to drive
confidence to the floor.

**A store reconciling itself is the whole point.** Draft 06's standing caveat is
that its only reconciliation was performed *by hand, by an outside reader*. A
node that runs Stage D in its own Dream Cycle closes that gap; the same work
done in `companion.py` does not.

### Stage E — abort (Rule 4)

`K = 3` consecutive expectation failures abort back to baseline. On `RT` the
natural plan to abort is a positioning belief: three consecutive violated RSSI
expectations drop the proximity belief back to baseline exploration rather than
continuing to assert a distance. This connects the learning loop directly to the
primary hypothesis — and `K = 3` is as unrun as the `+2/−16`.

### Recommended order

Stage A is worth shipping alone. A→C is the honest floor. **D is the
experiment**; do not let A–C become the deliverable.

---

## Part 4 — Conclusion: merging the findings back here

The loop is not closed by building it. `TTE`'s `@LAT98LON2` requires the result
to come back as records, with provenance, in the form the store specifies.

### 4.1 What `RT` sends back

**A. Outcome records, verbatim.** Not a summary. Copies of the Stage C side-log
records — expectation, observed, verdict, provenance — so the reconciliation
here can be recomputed by a third party rather than trusted.

**B. A reconciliation of `@LAT20LON3`, computed not asserted.** State the tally
(N met, N violated), the resulting `conf` movement under its own Rule 3, and
whether the movement was applied *by the node* or by hand. The distinction is
the finding. Current value to move from: `conf:122 rev:1 sal:200`.

**C. A verdict on the constants — the thing nobody has.** Did `+2/−16` behave as
designed on real sensor noise, or did it need different values? Did `K = 3`
abort too eagerly or too late? **A number that had to be changed is a better
result than one that happened to work**, and it is the first evidence either
constant has ever had.

**D. New records for what only hardware could show.** Anything about running the
transition form on a constrained device — flash cost of paired records, lane
pruning against `MOTIONPERCEPT_MAX_LANE`, whether the fleet clock is stable
enough to order transitions across nodes given the unresolved loop stall (§2.5).

**E. Log where you got blocked, and do not route around it.**
`TTDB-RFC-0009` asks for exactly this, because *the location of the block is the
measurement.* If Stage D cannot run because the store cannot choose a repair
path, commit to it, and decide to stop — say so, and say precisely where. That
is a result, not a failure to deliver one.

### 4.2 What changes here when it lands

- **`agent-memory-system_ttdb.md`** — `@LAT20LON3` reconciled per (B), with a
  `rev 2` note naming the run. New `@LAT98LON7` belief for the hardware result,
  edged `supports@LAT20LON3`. If the transition form ships, **`@LAT98LON6` is
  contradicted by observation** and takes its own medicine exactly as
  `@LAT98LON2` did in Draft 06: `conf −16`, `sal +8`, and an honest `rev 1` note
  saying its "zero instances" count was overtaken by the run. Bump the
  `agent_note` draft number.
- **`README.md`** — the closing section (["Where it stands,
  2026-08-01"](README.md#L205-L235)) rewrites. Its current claim is that what's
  missing is *"one loop that writes the difference down."* If `RT` writes it
  down, that sentence is answered by a fleet of ESP32s and should say so, with
  what the run cost and what it left open.
- **`RFCs/TTDB-RFC-0006`** — §7.1 mandates enforcing the pairing at write time.
  A real implementation on constrained hardware will surface whether that is
  actually enforceable in a fixed-RAM streaming writer; if it is not, that is an
  amendment, not a bug in `RT`.
- **`RFCs/ARC-RFC-0001`** — the nearest formal expansion of Learning from Action
  and still `Proposed`. Evidence for `K` from a second, non-game domain is
  directly relevant to it.
- **`RFCs/TTN-RFC-0011`** — settle the §2.5 debt in the same pass.
- **`research/`** — if the constants come back wrong in an interesting way, that
  is research-line material before it is spec, on the pattern
  `research/valence/` already sets: results first, including where the method or
  its author was wrong, and no RFC until the test that would settle it has run.

### 4.3 The one-line version

`RT` should pull five drifted RFC files and reflash both handhelds so the fleet
stops displaying a v1.0 spec; then take `MotionPercept` — which already computes
both sides of a `still → moving` edge and throws the pairing away — and write
the difference down. Everything the project has been unable to test for two
drafts sits behind that one change.

---

*Authored from `toot-toot-engineering` against a read-only inspection of
`robot_team`. No files in either repo were modified. Every count, path, line
number, and file-difference above was verified against both working trees on
2026-08-01, not recalled.*
