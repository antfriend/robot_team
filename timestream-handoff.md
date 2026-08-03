# Handoff: team time stream, semantic logging, and the verification gate

**Work order for a fresh session.** Authored 2026-08-02 against `robot_team` @ `33a7a02`
with a clean tree. Read [companion.md](companion.md) §6 first — it is the source of truth
and its last five entries are this session's results.

This document does three things, and **the order is load-bearing**:

1. **Part 1 — The verification gate.** Everything built on 2026-08-02 that has NOT been
   proven on hardware. **`percept-learning-return.md` does not go back to
   `toot-toot-engineering` until this passes.**
2. **Part 2 — The team time stream.** A fleet-owned timeline that survives the laptop's
   absence. It unblocks TBEW recency, cross-node ordering, and TDoA.
3. **Part 3 — Semantic (change-triggered) logging.** Record meaning, not frames. **Depends
   on Part 2** and the dependency is not negotiable — see §3.0.

Throughout: `TTE` = `toot-toot-engineering`, `RT` = `robot_team`.

---

## Part 0 — Where things stand

Four stages of Learning from Action now run on the Cardputer (`0x300`), and the store
reconciles itself:

| lane | what | status |
|---|---|---|
| `@LAT93` | `@PERCEPT:before/after` transition pairs (Stage A) | on hardware |
| `@LAT92` | outcome side log — expectation, observed, verdict (Rules 1+2) | on hardware |
| `@LAT91` | LINK-STABLE belief with a TBEW `[ew]` block (Rule 3) | on hardware, independently verified |
| `@LAT90` | *proposed here* — stream origin/adoption | not built |

Native suite: **298 checks, 0 failures** (`cd tests && make`, or `scratchpad/t.sh <name>`
with portable zig — there is no host g++ on this machine).

**The two spec-level findings that already justify the work**, both in
`percept-learning-return.md`: `@PERCEPT:` collides with TTDB-RFC-0001 §3 (an unindented
`@` in a body is a record header, so the Locus form silently produces phantom records), and
§7.1's write-time pairing is enforceable **only as a single atomic append**.

---

## Part 1 — THE VERIFICATION GATE

Nothing below is a known bug. It is all *unverified*, which on this fleet has repeatedly
turned out to be the same thing. Three separate silent failures bit us in two days (a full
lane that logged nothing, a buffer that refused to write rather than truncate, an FS image
at the wrong offset), and each was invisible until something asserted on it.

### 1.1 ⚠ HIGHEST PRIORITY — the Dream Cycle's flash cost is UNMEASURED

`reconcileBeliefs()` (cardputer_console.ino) runs from `loop()` every
`DREAM_RECONCILE_MS` (3 min). On a change it calls **`gDb.removeLane(91)`, which rewrites
the ENTIRE TTDB** — currently ~46 KB — and then appends. **This has never been timed.**

The fleet already has an unexplained multi-second loop stall (CLAUDE.md), and this is a
plausible new source of one that would be indistinguishable from it.

- [x] Measure the worst loop pass across a Dream Cycle that **changes** a belief (not the
      no-op path, which is the only one observed so far). Use the sketch's own section
      profiler; `lp` is a 10-second-window number, so sample it *during* the rewrite.
      **DONE 2026-08-02: 150 ms @ 8.6 KB → 1757 ms @ 74 KB, ~10-13 µs/byte; crosses 1 s at
      ~53 KB.** ⚠ The section profiler **could not have answered this**: it skipped the
      FIRST loop pass, which is where the boot Dream Cycle runs. Fixed; the two instruments
      now agree to 8 ms. See companion.md §6.
- [ ] If it is seconds, move the rewrite off `loop()` or make the belief lane
      append-with-supersede instead of rewrite-in-place. **STILL OPEN — it IS seconds-class
      (1.76 s).** `removeLane` is O(file) and `appendRecord` is O(file) too, so a changing
      cycle is 1 rewrite + N appends = **9 full-file passes at 8 beliefs**. Decide before
      Part 2 adds more writers.
- [x] Record the number in companion.md either way. **"It seemed fine" is not a result.**

### 1.2 The constants verdict rests on n=1

`percept-learning-return.md` §0b reports verdicts on `+2/−16` and `K = 3`. Both come from
**a single walk-away-and-back**. This repo's own hard-won rule is that n=1 and n=3 samples
here are noise and n≥9 is the floor.

- [x] Repeat the moving run **at least 3 more times**, varying distance and dwell.
      **DONE — two further runs 2026-08-02** (one unlabelled but with a CONTROL GROUP, one
      operator-labelled), giving three independent runs total.
- [x] Confirm the shape holds: violations only in transit windows, `met` while parked at
      distance (this is the finding that makes the whole tier trustworthy — see §0b).
      **CONFIRMED:** −36 dB transit → VIOLATED, then **five consecutive parked-far windows
      all `met` to within 1 dBm**, then +17/+26 on the return → VIOLATED. Internal control:
      **stationary peers 1.4% violation (2/144) vs the roamer 32.4% (12/37) — a 23×
      separation** in the same windows with the same band.
- [x] Confirm `K = 3` still never fires. If a longer/slower walk *does* reach streak 3,
      the verdict changes and the return report must be rewritten before it is sent.
      **STILL NEVER FIRES — max streak 2 in all three runs**, including a full relocation
      and return. §0b stands unchanged.
- [x] Re-run the laptop-vs-device reconciliation cross-check after each run.
      **`scratchpad/refold.py`: 8 pairs × 7 fields, 0 mismatches** (the morning's check was
      2 pairs).
- ⚠ **Lesson for whoever runs the next one:** label ONLY what the operator actually
      labelled. The first analysis pass called the unlabelled pre-walk period "still",
      which manufactured a 7% baseline violation rate and nearly buried the real result —
      the roamer was being handled during it.

### 1.3 Multi-node — never exercised

Everything so far is the Cardputer with the T-Deck as its only peer. The V4s were off.

- [x] Power all three V4s. Confirm `@LAT97` shows 4+ peers and `@LAT91` grows a belief per
      (peer, proto). `PERCEPTLEARN_MAX_CLAIMS` is 8 — with 4 nodes × 2 protos that is
      **exactly at the cap**, so verify nothing is silently dropped. **DONE: 8 beliefs,
      nothing dropped.** ⚠ But hardware only *reached* the boundary, never crossed it —
      over-cap behaviour is still native-tested only (a 9th pair needs a 5th node).
      ⚠⚠ **Both caps were SILENT until this session.** An overflowed `stage()` scored the
      peer `VERDICT_UNOBSERVED` — indistinguishable from a peer that genuinely went quiet,
      i.e. a plausible wrong answer rather than a gap. Now counted and printed.
- [x] Exercise the `unobserved` verdict for real by powering a peer OFF mid-run. The code
      path is unit-tested but has never fired on hardware. It must NOT count as violated.
      **FIRED ON HARDWARE** (`unobs:1` on both T-Deck protos) by the roamer going out of
      range rather than powering off — the more realistic case — and it did **not** count
      as violated. 📎 Distinct from it: a peer heard in NO window gets **no claim armed at
      all**, which is invisible in the tally.
- [x] Verify a belief actually **moves between Dream Cycles** (`rev:2`+). Only `rev:1` and
      the no-op path have been seen. **Reached `rev:9`.**

### 1.4 Nodes still carrying old firmware

`STARTUP_TOOT 0` lives in the shared `RobotTeamConfig.h`, but only the two consoles were
flashed.

- [ ] Flash **v4a_bridge, v4b_relay, v4c_edge, k10_percept** — they still toot on boot.
- [ ] ⚠ The V4 sketches are at **94% of the default app partition**. If anything fails to
      fit, move them to `huge_app` before adding a single line.
- [ ] After flashing, **verify audio still works on each** (`CMD_BEEP`, the band, the
      duet). Boot-toot gating touched the audio init path, and every board's audio was
      hard-won differently. A silent boot and a silent *node* look identical.

### 1.5 Regression checks not re-run since the firmware changed

- [ ] `orchestrator/negchecks.py` — HMAC / wrong-key / tampered-toot rejection.
- [ ] `orchestrator/radio_replay.py` — radio-only dedup still drops an over-air duplicate.
- [ ] **Bridged pull** with the now-46 KB TTDB. This is already known-intermittent and
      CLAUDE.md implicates TTDB growth; the new lanes made the file bigger. Expect trouble,
      and **do not tune dwell or retries** — that is a documented dead end. A node's own
      cable is the trustworthy path.
- [ ] `companion.py band` / `intero` / `gps` still answer.

### 1.6 On-glass verification (never done visually)

- [ ] Walk the **RFC globe** to the Typed Edges record on **both** handhelds and confirm
      **§7 `opposes`** is present. If it is absent the FS image did not land. This is the
      finding the whole spec sync turned on and it has only ever been checked by byte count.
- [ ] Confirm the **feelings globe** still renders its band overlay after the merge
      (T-Deck 46 records, Cardputer 47).
- [ ] Check how `@LAT90/91/92/93` render on the T-Deck's record pane — four new lanes it
      has never been shown. Ugly is acceptable; a crash or a blank pane is not.

### 1.7 Only when all of the above passes

- [ ] Send `percept-learning-return.md` to TTE, updating §0b if 1.2 changed any verdict.

---

## Part 2 — The team time stream

> **STATUS 2026-08-03: BUILT, NATIVE-TESTED, ALL SIX SKETCHES COMPILE. NOT ON HARDWARE.**
> See companion.md §6. Two of the three hazards in §2.2 turned out to be **the same
> mechanism**: because a stream's clock reads elapsed-since-its-own-origin, "older
> stream wins" (§2.2.2) and "never move backward" (§2.2.3) are one rule, not two that
> must agree. §2.2.1 (`stream:` on every record) was built as specified.
> Two deviations from the sketch below, both deliberate and both explained in
> companion.md §6: the anchor rides on **HELLO, not PULSE** (only the conductor emits a
> PULSE, and the conductor is elected by id, so the oldest stream usually cannot speak);
> and `touched:` stays **Unix seconds per TTDB-RFC-0005** with the stream frame added
> beside it on a `**TOUCHED**` line, rather than having its unit redefined — the RFC
> defines that field in Unix seconds, and that is itself the spec finding (§4.1).
> **HARDWARE RUN DONE (Cardputer 0x300 + T-Deck 0x200, both flashed app-only so the
> existing TTDBs were preserved).** ORIGIN, ANCHORED, ADOPTED and **RECONCILED with its
> REMAP mapping** all fired on real flash; the merge did not even need staging (a
> booting node's radio is not up inside its own listen window, so it originates and then
> yields ~1.3 s later). Both nodes ended up stamping records with one shared stream id,
> and the Cardputer got its own timeline handed back by the T-Deck across a reset.
> ⚠ **One defect found and NOT fixed: `@LAT90` grows one record per reboot** and
> `companion.py` reboots the cabled node on every invocation — 0 → 7 records in a
> session against a cap of 16. A node that rejoins the stream it was already on has had
> no timeline change and should not write one. Fix candidate (persist the last stream id
> in NVS, write `ADOPTED` only on a genuine difference) is recorded in companion.md §6,
> deliberately not built blind.

### 2.1 The problem, stated precisely

Every record the Cardputer wrote on 2026-08-02 carries `synced:0`, `created:0`,
`touched:0`. Consequences, in order of severity:

1. **TBEW recency is inert.** RFC-0005 defines `touched` as a recency anchor and salience
   decays from it. With `touched:0` the `@LAT91` beliefs carry `sal:24` that will **never
   decay**, and EPS (`sal×(255−conf)/255`) has no time term. **The epistemic-weight
   machinery cannot function on-device without a clock.** This is the strongest argument
   for the feature and it is a spec-level gap, not merely an `RT` one — Rule 3 moves `sal`
   without saying what makes it fade.
2. **`@LAT94`'s acoustic timestamp is meaningless.** The tier records the fleet-clock time
   of the loudest transient as Phase-3 TDoA groundwork; unsynced it is local `millis()`.
3. **`@LAT93` transitions cannot be ordered across nodes** — flagged as open all day.

### 2.2 The design

**Do not build a new subsystem. `Pulse` already has most of it**: `conductor_id`, `era`,
`conductor_epoch`, `onBeacon()`, and an election, plus the property that killing the node
that is counting does not lose the fleet's place (TTN-RFC-0010). The stream is *era +
epoch offset*, and the conductor is already the phase reference.

**Split the one `synced` bit into two orthogonal facts.** This is the core modelling
change and it is what makes the user's original framing work:

| field | meaning |
|---|---|
| `stream:<u32>` | WHICH shared timeline this record belongs to |
| `wall:<0\|1>` | is that timeline anchored to real-world date, or only self-consistent |

A fleet with no laptop in sight still has a perfectly good shared timeline
(`wall:0`) — it just cannot name the date. Today's single `synced` bit conflates
"we agree with each other" and "we know what day it is", which is why a lone node
reports `synced:0` and throws its timestamps away.

**Lifecycle:**

- A node that boots and finds **no stream** starts one: `stream_id` derived from
  `(node_id, first_boot_ms)` so it is stable and comparable, and writes a
  **`@LAT90` STREAM-ORIGIN** record — the "logged signal that this begins a new stream".
- A node that **hears a stream** adopts it, carries it forward on its own counter, and
  writes **`@LAT90` STREAM-ADOPTED** with the offset it applied.
- The laptop supplies wall-clock date on connect/flash, flipping `wall:0 → 1` and writing
  **`@LAT90` STREAM-ANCHORED**. The existing `companion.py sync` already does the
  transport; it just needs to set the anchor rather than a bare bit.

**Three things the sketch above needs that are easy to miss:**

1. **`stream:<id>` must ride on EVERY record, not just at the boundary.** Two nodes that
   each boot alone each start a stream; when they meet, one loses, and every record written
   under the loser is stamped in a timeline that no longer exists. Without the id on each
   record you cannot tell retroactively which clock a timestamp belonged to.
2. **Merge rule: OLDER STREAM WINS** (largest elapsed), not lowest node id. It preserves
   more history. The loser writes `@LAT90` **STREAM-RECONCILED** carrying the offset
   mapping, so its earlier records stay interpretable instead of orphaned. (Pulse elects
   its *conductor* by lowest id — do not reuse that rule here; they are different jobs.)
3. **Monotonicity.** Adopting a stream can move the clock BACKWARD if the local counter ran
   ahead, putting already-written records out of order. Adopt via an offset the way
   TTN-RFC-0008 does; never assign the number directly.

### 2.3 The change surface — all of it

`synced:` appears in **7 record formats across 5 libraries**, and they must move together
or the corpus becomes half-parseable:

```
AcousticPercept.cpp   (x2)   EntityPercept.cpp   LinkPercept.cpp
MotionPercept.cpp     (x2 — MOTIONWIN and TRANSITION)
PerceptLearn.cpp      (OUTCOME)
```

Also:
- `tests/test_motionpercept.cpp` and `tests/test_perceptlearn.cpp` **assert on the
  `synced` field** and will fail loudly. Good — update them deliberately.
- `orchestrator/companion.py:1747` has a `**LINKWIN**` regex with `synced:([01])`, plus
  STATUS/INTERO flag decoding around lines 242 / 748 / 1342.
- `@LAT91` `buildBelief()` writes `touched:%lu` from `t_sec` — **this is the field that
  makes decay possible; wire it to stream time.**

**Migration:** old records must keep parsing. Accept `synced:` on read, emit
`stream:`/`wall:` on write, and say in companion.md which build changed it.

### 2.4 What this does NOT fix

State it up front so the effort is not oversold:

- **Not** the ±60 s transition quantization — that is window length, independent.
- **Not** the loop stall. It would make the stall *measurable across nodes*, which is a
  precondition for diagnosing it, but it is not a fix.

---

## Part 3 — Semantic (change-triggered) logging

### 3.0 ⚠ Why this comes second

Under periodic logging you can reconstruct approximate time from a record's *position* in a
regular series. **Under event logging you cannot** — each record must carry a trustworthy
timestamp, which is exactly what does not exist today. **Part 2 is a prerequisite, not an
enhancement.** Building Part 3 first produces a sparse log that nobody can place in time.

### 3.1 It is already proven in-tree on one tier

`@LAT93` writes a record only on a verdict **change** — a node on a shelf writes none at
all. The transition record is also the right *template*, because it carries both endpoints'
full state, so each entry is self-sufficient rather than needing its predecessor.

Generalize that shape. Do not invent a new one.

### 3.2 What it fixes

- **The failure that broke the 2026-08-02 experiment.** `@LAT95` hit 48/48 in 48 minutes
  and silently disarmed the learning loop. Change-triggered, that lane holds ~4 records.
- **TTDB growth**, which is implicated in the intermittent bridged pull (V4-B reached
  54 KB on unpruned percept lanes). This attacks the cause rather than pruning after.

### 3.3 Three rules it must follow

1. **HEARTBEAT OR CHANGE, whichever comes first.** Absence of a record must never be
   ambiguous. Zero records otherwise means "nothing changed" *or* "the sensor died" *or*
   "the node was off" — and silent ambiguity is this project's signature failure. A
   heartbeat every N windows keeps the stream proving liveness.
2. **Correct for STATE; WRONG for EVIDENCE.** Stage D computes `conf` by counting
   met/violated across `@LAT92`. Drop the unchanged windows and the tally loses its
   denominator, so confidence is computed from a biased sample. **You can compress a state
   series by keeping transitions; you cannot compress a tally that way.** Leave `@LAT92`
   periodic, or convert it to explicit run-length (`windows_since_last:N met:N`) — which is
   what this whole idea really is.
3. **DERIVE the thresholds; do not choose them.** The 6 dBm RSSI band in `PerceptLearn.h`
   is the **p90 of that node's own drift across 33 known-quiet windows**, and it is the
   only constant in this system with an empirical basis. Same method per tier: measure the
   signal's noise floor during a period known to be uneventful, set the threshold there,
   and write the derivation into the header the way `PerceptLearn.h` does.

### 3.4 Two traps

- **Flapping.** A signal sitting exactly at the threshold produces MORE records than
  periodic logging. We already saw `d=6` land exactly on the band. Needs hysteresis
  (different up/down thresholds) or a minimum dwell.
- **Record count stops being a time proxy.** `companion.py proximity --last N` is
  documented as a recency filter over "each node's newest N windows". Under event logging,
  N records is no longer N minutes. **Audit every consumer that counts records** before
  changing any tier.

### 3.5 Suggested order

`@LAT95` and `@LAT96` first — the state tiers, where the argument is unambiguous and where
the cap actually bit. Leave `@LAT92` alone until §3.3.2 is decided.

---

## Part 4 — What this unblocks for TTE

When Parts 1–3 land, `percept-learning-return.md` gains three things it cannot claim today:

1. **A `touched` that means something**, so Rule 3's `sal` can decay and EPS becomes
   computable on-device. Worth raising with TTE as a gap: **Rule 3 specifies how salience
   RISES and never says what makes it fall**, and a store with no clock cannot implement
   the difference.
2. **Cross-node transition ordering**, which is the precondition for the Phase-3 TDoA tier
   that `TTN-RFC-0011` anticipates — and settles part of the §2.5 debt (no field result has
   ever been folded back into RFC-0011).
3. **A retention story.** Stage D found that pruning the outcome lane resets the belief
   toward baseline: `conf` describes *retained testimony*, not history. Change-triggered
   logging changes what retention means, and TTE should hear both facts together.

**Do not send the return report before Part 1 passes.** Its §0b verdicts on `+2/−16` and
`K = 3` are currently n=1, and this project has a written rule about that.

---

*Every file path, line number, constant and count above was verified against the working
tree at `33a7a02` on 2026-08-02, not recalled.*
