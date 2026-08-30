# Handoff: episodic sensing — record the dynamics, not the frames

**Work order for a fresh session.** Authored 2026-08-15 against `robot_team` @ `80f6a86`.
Read [companion.md](companion.md) §6 first — it is the source of truth. This document
sharpens a loose idea into a staged plan, and the first half of it is an argument about
where the loose idea is *wrong*, because two of those errors have already cost this fleet
a field run each.

---

## 0. The idea, restated precisely

> *Compress data collection by summarising an episodic block as parameters. A sensor
> reading 5 for 10 instances becomes one value with 10 steps. Ideally: a mic recognises a
> tone and the lane records "heard twice in 8 hours" in 2 slots. This is sensory **vector**
> collection rather than static data collection.*

Three separable claims are bundled here, and they need separating because they have
different truth values and different costs:

| | claim | verdict |
|---|---|---|
| **A** | Fold an unchanged run of windows into one parameterised record | ✅ **already built, three times** — this is not new, it is a fourth application |
| **B** | Put a *recognizer* in front of the sensor so only meaningful events consume slots | ⚠️ **right target, wrong accounting** — see §2.3 |
| **C** | This grounds the TTDB in relationships/vectors rather than static values | ✅ **right, and stronger than stated** — but §1 is not what delivers it |

---

## 1. Where you are right

**C is the most valuable part of the idea and you undersold it.** "Vector rather than
static" is exactly `TTDB-RFC-0006` §5's position: the unit of perceptual knowledge is not a
node but the **edge** between two of them. `MotionPercept.h:28-41` records that until
`@LAT93` was written, *nothing in this project — or in any store the spec side has examined
— had ever instantiated that form*: every loop overwrote state and the difference, which is
the datum, was never materialised. There was therefore nothing to compute prediction error
over. `@LAT93` is still the only instance in the corpus. Your instinct that this is a
"virtuous recursion" is correct, and §4 below is how to get a second instance.

**And B targets the right lane.** `@LAT94` (acoustic) is the **last periodic percept lane
on the fleet**. It writes one record per 60 s window unconditionally, so it fills its
48-slot cap in **48 minutes** and then refuses writes. Grep companion.md for `@LAT94` and
it reads `48/48` on nearly every pull for months — including the entry that names the cost
plainly: *"was 48/48 FULL — the fleet's SECOND EAR was discarding"* (companion.md:6452).
Meanwhile its siblings were fixed long ago:

| lane | before | after | mechanism |
|---|---|---|---|
| `@LAT95` motion | 48 min | ~24 h | run-length, 2026-08-04 (**15.5×** measured) |
| `@LAT92` outcomes | 24 min | — | run-length, 2026-08-04 (**6.0×** measured) |
| `@LAT96` entity | 8 h | 48 h | stable-core trigger, 2026-08-10 (**4.56×** simulated) |
| `@LAT94` acoustic | **48 min** | **— nothing** | ← **this document** |

So the plan is not "invent episodic sensing". It is **"@LAT94 is the fourth lane, and it is
the hard one, because it has two consumers that want incompatible things."** That framing
is worth more than the general idea, because it is the framing that can be finished.

---

## 2. Where you are wrong

### 2.1 "Folding the timestream" is the wrong object, and the error has teeth

The **time stream** is timeline *identity* — `@LAT90`, `stream:0x…`/`wall:0|1`. Folding
*it* is a different and dangerous operation (its cap policy is a live open question; see
[MEMORY: @LAT90 saturation](file:///C:/Users/antfr/.claude/projects/c--git-robot-team/memory/lat90-saturation-is-next.md)).
What you mean is folding the **window series**, which the time stream merely stamps.

That is not pedantry, because of this, from CLAUDE.md:

> A stream's clock is **elapsed-since-its-own-origin** … Consequence: the clock is a
> **ratchet** (fastest crystal heard wins) — fine for ordering/recency, **wrong for
> measuring a duration**.

An 8-hour episode is a duration, and its endpoints can straddle a ratchet event. So:

> 🛑 **`last_t_ms - first_t_ms` IS NOT THE EPISODE'S LENGTH AND MUST NEVER BE READ AS ONE.**
> An episode record must carry an explicitly accumulated `window_ms`, summed from local
> `millis()` deltas. `MotionPercept` already does exactly this (`cov_window_ms_`); copy
> that shape, and state it in the record so a reader cannot make the subtraction.

### 2.2 "5 for 10 instances" is lossless only because your example is exactly constant

Real sensor series are never exactly constant. The instant you allow *"close enough to 5"*
you have introduced a threshold — and this fleet has **measured** that a threshold's loss
does not transfer between environments. From `EntityPercept.h:52-53`:

> a fixed Jaccard threshold's **LOSS DOES NOT TRANSFER** — the same node on the same bench
> dropped 10% of its AP union one night and **36%** the next.

The repo's answer was not a better threshold. It was a different contract, and it is
already the governing rule at `ttn-semantic-positioning.md:316`:

> **Any new positioning lane must state its consumer and its losslessness argument before
> it is written.**

So the primitive is not *"same value ⇒ fold"*. It is:

> **The covering record must carry whatever the lane's consumer computes, so that the fold
> is lossless *for that consumer* by construction.**

`@LAT92`'s consumer computes a tally → fold the count. `@LAT96`'s consumer computes a union
→ the covering record carries the union (`**COVERED-ENTITY**`), and a window whose entities
would not fit **ends the run** rather than being dropped. That inversion — the record's
capacity bounds the run, not the other way round — is the whole trick, and §3 applies it.

### 2.3 "Heard twice in 8 hours, using 2 slots" — this is the error that has already cost a run

Two records means the lane says **nothing whatsoever about the other 7 h 59 m**. Three
things break at once:

1. **Silence is evidence here, not the absence of it.** `AcousticPercept.h:21-22`: *"Ambient
   level is useful on its own as a second entity-style tier: rooms have sound signatures,
   and two nodes in the same room hear the same machine hum."* An event-only lane throws
   away the room signature — a positioning input — to save slots.
2. **A dead mic and a quiet room become byte-identical.** This is a lesson the fleet has
   already written down in a *different* subsystem and then had to learn again:
   companion.md:4458 — *"A transient rejected as too quiet flashes `quiet`, because
   otherwise a deliberately deaf setting and a dead microphone look identical."*
3. **It has the exact shape of the entity-survey failure.** From CLAUDE.md:

   > A folded lane writes ~1 record per hour while a node stands still — and **standing
   > still is what a node does at a station** — so folding deletes the walker's entire
   > per-station contribution … the survey it feeds just comes back nearly empty and
   > **reads as a bad site**.

   Substitute *quiet* for *still* and the sentence still holds. An event-only acoustic lane
   returns a nearly-empty lane for a quiet site and for a broken mic, and nothing in it
   distinguishes them.

✅ **The fix is cheap and it is a third record, not a redesign.** Keep a **coverage
heartbeat**: a record that states how many windows were listened through, the accumulated
`window_ms`, the ambient floor over them, and the detector threshold in force. Then
"heard twice in 8 hours" costs **~3 slots instead of 2** — 480 windows → 3 records is still
**160×**, against a 240× that is unfalsifiable. You are trading 0.6% of the compression for
the difference between a measurement and an anecdote.

### 2.4 Run-length is not "dynamics" — it is deduplicated statics

A run of `still` is a *static assertion with a length attached*. It compresses beautifully
and it is not a vector. The derivative of a state series exists only at the change points —
which is precisely where a change-triggered lane writes, so the machinery is already
sitting on top of the datum you want and currently discards it for the acoustic tier.

If you want claim **C** delivered, folding alone will not do it. You need the `@LAT93` form
applied to `@LAT94`: a paired `before → after` record at every acoustic state change. §4.

### 2.5 A recognizer is a new *instrument*, not a compression scheme — ship it separately

Compression is a **lane** change and is argued against a consumer. Detection is a
**front-end** change that redefines what a percept *is*. If both land in one commit and the
lane comes back near-empty, you cannot tell whether the mic is deaf, the detector is
mistuned, or the room was quiet. That is the §2.3 failure again, one layer up.

> 🛑 **And do not "improve" the existing transient threshold while you are in there.**
> companion.md:4450 already refused this once: *"that lane is evidence, and redefining what
> it calls a transient would silently redefine a percept."* A tone detector is an
> **additional channel**, layered the way the trace field's stricter gate was.

---

## 3. Stage 1 — `@LAT94` becomes change-triggered

**State the consumer and the losslessness argument first** (`ttn-semantic-positioning.md:316`).
`@LAT94` is the hard case because it has **two consumers with incompatible needs**, and
recognising that is the design:

| consumer | what it reads | fold is lossless if… |
|---|---|---|
| **A. Room signature** (entity-style proximity bound) | ambient *level*, as a distribution | the covering record carries the run's aggregate — mean over **blocks** (not a mean of means), min, max, block count |
| **B. TDoA** (`ttn-semantic-positioning.md` Phase 3) | the **individual instant** of a transient on the fleet clock | 🛑 **impossible** — a dropped window drops its `loudest_t_ms` irrecoverably |

The resolution follows `EntityPercept`'s `union_full` exactly — **make the incompressible
thing end the run**:

> ### The rule
> **A window containing a transient is NEVER folded.** It always writes. Silence folds;
> events never do. `reason:transient` joins `first|changed|heartbeat` as a run-ender.

This is your idea made honest, and note what falls out: *"the tone was heard twice in 8
hours in 2 slots"* is now **true by construction** — the two event windows are structurally
unfoldable — and the silence between them costs one heartbeat record that says how long it
listened. Loss for consumer B is **zero, by construction, not by tuning**.

**The fold trigger for the silent stretches** should be a **band, not a threshold on
drift** — the `@LAT96` lesson: prefer a counting rule over recorded values to a constant
fitted to a continuous quantity. Quantise ambient RMS onto a fixed coarse ladder and fold
while the bucket is unchanged; the record states the ladder in a `**BAND**` line so it is
self-describing, and `**COVERED**` carries the real min/mean/max so a reader recomputes
rather than trusts.

⚠ **Do not upgrade the wording to "verifiable."** As `EntityPercept.h:69-74` says of the
stable core: a reader holding only what was written cannot recompute the trigger over
dropped windows. Self-describing is the strongest honest claim available at any compression.

### Record shape

```
@LAT94LON<n> | created:<t_sec> | ... | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:.. stream:0x.. wall:.. window_ms:.. blocks:.. rate:..
**ACOUSTIC**   rms_mean:.. rms_max:.. peak:.. transients:..
**TRANSIENT**  t_ms:.. stream:0x.. wall:.. rms:..          (only when one was heard)
**BAND**       bucket:<k> edges:<r0>,<r1>,...              ← NEW: the fold's own claim
**RUN**        windows_since_last:<N> reason:<first|changed|heartbeat|transient> max_run:<M>
**COVERED**    windows:<N-1> blocks:.. window_ms:.. rms_mean:.. rms_min:.. rms_max:..
               transients:0 first_t_ms:.. last_t_ms:.. covered_by:@LAT94LON<n>
```

`transients:0` on the **COVERED** line is not redundant — it is the assertion that makes the
fold safe for consumer B, written where a reader will see it.

### Implementation notes, each of which is a trap already sprung elsewhere

- 🛑 **Add a `Close` enum and branch on `lastClose()`, NEVER on the byte count.** This has
  bitten twice (`MotionPercept.h:265-268`, `EntityPercept.h:181-184`). `buildRecord`
  returning 0 currently means "empty window"; after this change it means "covered", which
  is the *normal* case for a quiet node.
- 🛑 **`ACOUSTICPERCEPT_RECORD_BUF` must live in the header, sized by a native test.**
  Fourth-undersized-buffer rule
  ([MEMORY](file:///C:/Users/antfr/.claude/projects/c--git-robot-team/memory/render-buffers-belong-in-libraries.md)):
  a native test cannot call into a `.ino`, so the header is the only place a size can be
  pinned — and pin it in *both* directions (fits the new form, does **not** fit the old).
  `buildRecord` must write nothing rather than truncate.
- ⚠ **`AcousticPercept` has no native test at all** (`AcousticPercept.h:26-27`) — it has
  only ever been verified on hardware. Write `tests/test_acousticpercept.cpp` **in this
  stage**, before the fold. `@LAT95`'s run-length silently did nothing while looking
  correct, and only the native test caught it.
- ⚠ **The K10 and the Cardputer have different microphones.** Any level constant measured
  on the ES8311 does **not** transfer to the K10's I2S mic — this is `MOTIONPERCEPT_MOVING_MG`
  all over again (`MotionPercept.h:192-209`: the K10's accelerometer made a picture frame on
  a desk read `state:moving moving_permille:1000`). **Give the second board a null and scale
  in the sketch; do not move the shared constant.**

### Prune before you measure

`@LAT94` is at 48/48 on both ears and a full lane **refuses writes**, so a run started now
collects nothing. Prune with `cmd --op clear-percepts --lane 94` — ⚠ **name the lane;
`--lane 0` drops 94–97 including `@LAT96`**, whose Jaccard baseline is needed elsewhere.
And [MEMORY: runbook counts expire](file:///C:/Users/antfr/.claude/projects/c--git-robot-team/memory/runbook-counts-expire.md):
prune *immediately* before the run, never in advance.

---

## 4. Stage 2 — the acoustic transition (this is where claim C is delivered)

Mirror `@LAT93` exactly. When a window closes with a band verdict differing from the one
before it, emit **one atomic record** carrying both halves and the typed edge:

1. **One record, not two** — `Ttdb::appendRecord` has no transaction, and `RFC-0006` §7.1
   says an orphaned `before` is an error.
2. **`@PERCEPT:` lines indented by two spaces** — an unindented `@` in a body is indexed as
   a record header and becomes a phantom `(0,0)` record.
3. **Write the pairing as real `derived_from` edges too**, and duplicate the state blocks
   into the body so the transition survives the `@LAT94` lane being pruned.
4. **Cite windows as `(covering record, offset)`** — `@LAT94LON7+3`, never a bare ordinal.
   Under folding the `before` half is usually a *suppressed* window; citing the last-written
   record instead would attribute the edge to a different window. `derived_from` edges stay
   plain ordinals with no `+k` — an edge must resolve to a record that exists.

**Lane number — take `@LAT93` with a `kind:` discriminator, do not open a new lane.**

- 🛑 **`@LAT89` is forbidden.** `isNodeRecord()` is `lat > -90 && lat < 90` on both consoles
  (`LaneGen.h:40`), so an `@LAT89` record is navigated to as a *node* on the globes.
- `@LAT102` is already reserved for stage-3 attributed testimony.
- The index is a **whole-file budget of 288 that the per-lane caps already oversubscribe**
  (Cardputer measured 265/288). Reusing `@LAT93` — already outside the 94–97 prune range,
  already capped at 32, already named "transition" — costs nothing new.
- ⚠ Then the needle discipline applies: `**MOTION**` vs a new `**ACOUSTIC**` block, and a
  reader must never fold one as the other. Same family as `prev_stream:` and
  `**COVERED-SPAN**`.

---

## 5. Stage 3 — the recognizer, and the thing you did not ask for

A tone detector is an integer **Goertzel** over a handful of fixed bins: portable, no float,
fixed RAM — the same discipline as every tier here, and natively testable against synthesised
input. It adds a `**TONE**` line and a tone-presence vector that becomes a fold trigger
alongside the band.

**But choose the bins from `Score.h`, because the fleet emits tones of known frequency at
known instants.** The pulse, duets, and the hero's arc are a scheduled emitter the
conductor already knows the timetable of. Three consequences:

- 🎯 **The detector gets ground truth.** False-positive and false-negative rates become
  *measurable* rather than asserted — which is the standard `ttn-semantic-positioning.md:523-529`
  already sets for the RSSI movement detector.
- 🎤 **The fleet now has two ears** (Cardputer + K10, 2026-08-12), which closes what the
  hypothesis doc calls *"the single largest hardware gap on the hypothesis path"* — its
  line 510, *"Only the Cardputer has a microphone"*, is **stale and should be corrected**.
  Two ears + a known emitter + a known schedule is the acoustic TDoA leg.
- ♻️ **It converts a known live bug into the calibration signal.** companion.md:1587 records
  that phase S0 *"still owes the same gate to the `@LAT94` transient log — that is a live
  data-quality bug in the acoustic tier"*: nodes hear their own singing and log it as
  transients. A detector that knows the fleet's note frequencies can *label* self-noise
  instead of merely suppressing it.

🛑 **Two hard constraints on the TDoA use:**
- **The clock is the PULSE, not the time stream.** A ratchet is correct for ordering and
  wrong for a cross-node duration (`ttn-semantic-positioning.md:485-491`).
- **The resolution floor is ~1.9 m** and it is already measured (residual band skew, per-run
  mean removed, conductor excluded). **State it before running the experiment, not after.**

---

## 6. Order, and the one thing that must not be skipped

```
Stage 0  measure offline  ← DO NOT SKIP
Stage 1  @LAT94 folds  (+ native test, + record buf in the header)
Stage 2  @LAT93 gains kind:acoustic          ← claim C is delivered here
Stage 3  Goertzel recognizer, shipped alone
Stage 4  two-ear TDoA against a known emitter
```

**Stage 0 is a laptop-only job and it is the precedent that made `@LAT96` work.** Before
any firmware, pull the current `@LAT94` lanes off both ears and simulate the candidate
triggers offline, exactly as `scratchpad/lat96_trigger_sim.py` did over a gate-validated
segment. Deliverable: a compression ratio **and a loss figure per consumer** for each
candidate ladder. Without it you are fitting a constant to one bench and one room, which is
precisely the dependency §2.2 exists to avoid.

⚠ And prune the lane before collecting, then leave the node **untouched** — every
`companion.py` call resets the board.
[MEMORY: verify before believing](file:///C:/Users/antfr/.claude/projects/c--git-robot-team/memory/verify-before-believing.md):
deriving a threshold from windows labelled by that threshold was wrong by 2.75×. The lane's
own label is not evidence.

---

## 7. One-line summary

> Not *"compress the timestream"* but **"`@LAT94` is the last periodic lane; fold its
> silence, never its events, and write down what the silence covered."** The compression
> falls out; the vector you actually want is the `@LAT93` edge, applied to a second sense
> for the first time.
