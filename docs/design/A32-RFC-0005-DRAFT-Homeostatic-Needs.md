# A32-RFC-0005 (proposed number): Homeostatic Needs — Interoception as Evidence, Reflexes as Actions

**Version:** 0.1 (draft)
**Status:** Draft. **Nothing in §§4–8 is implemented.** §3 classifies what exists; every
claim about existing code there cites the file it was read from on 2026-10-30. The number
is proposed, not assigned: on adoption this file moves to `replicate/RFCs/`, gains an
`INDEX.md` entry and an `rfc.ttdb.md` record, and both handhelds need an FS re-flash to
carry it (the three-way sync rule in `replicate/RFCs/INDEX.md`).
**Project:** robot_team (toot-toot-engineering corpus)
**Component:** A32 agent loop
**Depends on:** A32-RFC-0003 (Agent Loop), TTDB-RFC-0005 (TBEW / EPS),
TTDB-RFC-0010 (lane discipline), TTG-RFC-0002/-0003 (percepts, beliefs)
**Relates to:** `@LAT20LON3` Learning from Action (the spec store's four rules),
`docs/design/cardputer-sensorium.md` (the arbiter), ACT-III.md §2 (autonomous fleet)
**Plan:** [homeostasis.md](homeostasis.md) (phases, gates, and the review of the drafts this
replaces)
**Author:** antfriend
**Created:** 2026-10-30

---

## 1. Abstract

Every node in the fleet already measures its own body: battery, die temperature, heap and
loop latency (the 21-byte INTERO PERCEPT). Some nodes also run fixed reflexes that keep
that body viable, such as the BLE scan restart that bounds a measured heap leak. None of
it reaches the store. A node can report its battery to a console that asks, but it cannot
remember it, reason about it or learn from what it did about it.

This RFC makes three additive changes, in order:

1. **Interoception becomes evidence**: an `intero` episode tier in `@LAT103`, beside link,
   entity, motion and acoustic.
2. **Reflexes become actions**: each existing body-maintenance reflex declares an
   expectation before it fires and records an outcome after (Learning from Action Rules
   1–2), folded asymmetrically into a per-`(action, variable)` belief (Rule 3). Rule 4
   then aborts an action that keeps failing.
3. **Need selects among actions**: a node acts on the variable furthest outside its band,
   using the action its own beliefs rate most likely to help. Otherwise it rests.

It also gives the arbiter a fourth modality, so a body in trouble takes the screen
unprompted (ACT-III §2: the fleet "displays what it knows unprompted").

**Non-claim.** The vocabulary (need, valence, interoception) is borrowed from affective
neuroscience as a control structure. Nothing here claims that a node feels anything.

## 2. Motivation

- **`@LAT20LON3` is the spec store's highest-EPS record, and two of its four rules have
  never run.** Rules 1–3 run on the Cardputer over link expectations (`@LAT93` →
  `@LAT92` → `@LAT91`, gate passed 2026-08-02). Rule 4 (*K* = 3 consecutive failures abort
  the plan) has never executed, because the node has no plan to abort
  (`PerceptLearn.h:47`: "`+2/−16` and `K = 3` arrived as guesses and are still unrun").
  Body maintenance is the first domain on this fleet where the node chooses its own
  actions and the effect is quick enough to observe. That gives Rule 4 something to abort.
- **The fleet's reflexes cannot teach.** Rule 1: "an action without [an expectation] is a
  reflex — it executes but cannot teach." `blelink::loop()` restarts the BLE scan every
  60 s whether or not heap is falling. It works, and nothing records whether a given
  restart helped.
- **A capability that only works with a cable attached is not a fleet capability.** Today
  interoception is visible only through `fleet.py intero` or a console polling op 12. A
  cable also charges the pack, so battery behaviour seen through a cable is not battery
  behaviour.

## 3. What exists (classification, not proposal)

| Piece | Where | State |
|---|---|---|
| INTERO PERCEPT: `bat_mv`, `bat_pct`, `bat_trend`, `die_c_x10`, `maxalloc_kb`, `uptime_s`, `worst_loop_ms`, flags | `Toot.h:282-322`, op 12 | on all six boards, **answered on request, never written to the store** |
| Free heap (not in INTERO) | serial `[intero]`/heap prints | printed only; it is the number that revealed the ≈500 B/min BLE leak that `maxalloc` hid |
| Episode tiers + quotas, fold-and-cut, one shared scratch buffer | `Semantic/src/Episode.h` (`SEMANTIC_QUOTA_*`), `EpisodeNode::scratch()` | running, all boards (Phase C complete 2026-10-06) |
| Learning from Action Rules 1–3 (`**EXPECTED**`/`**OBSERVED**` → `**OUTCOME**` → `**TALLY** … rule:+2/-16`) | `PerceptLearn`, `Reconciler::foldRecord`, `@LAT92`/`@LAT91` | running on the Cardputer, link domain only |
| Rule 4 | — | **never executed** |
| Attention arbiter: `(sal, conf)` → EPS, decay, dwell, margin; modalities motion/sound/neighbour | `Attention/src/Attention.h` | running on the Cardputer; low-battery alert is named as a future modality but not built |
| Body reflexes: BLE scan restart every 60 s; T-Deck withholds `bat_pct` above 4.20 V | `blelink::loop()`; tdeck sketch | running; no expectation, no outcome |

**Known measurement limits that bind this RFC:**
- T-Deck battery reads **4.71 V**, above the Li-ion ceiling (`BAT_DIVIDER 2.0` unmetered).
  The V4's `BAT_DIVIDER 4.9` is also unmetered. **An absolute battery band on those boards
  would be invented.**
- Opening the port resets the handhelds (not the V4s), so `uptime` and `lp` read over a
  fresh connection describe the ~8 s after boot.
- The fleet's stream clock is a ratchet and is **wrong for durations**. Every rate in this
  RFC uses a local `millis()` delta, the way `MotionPercept`'s `dt_ms` does.
- The ~2 s `lp` stall is outside every loop section (descheduling). **No known action
  fixes it.**

## 4. Essential variables

### 4.1 Definition

An essential variable (EV, after Ashby 1960) `k` declares:

| Field | Meaning |
|---|---|
| `src` | the measurement (an INTERO field, or free heap) |
| `lo`, `hi` | viable band |
| `floor`, `ceil` | fault limits |
| `w` | weight, 0..255 |
| `bound:` | **`measured:<log ref>`** or **`declared`** (see §4.3) |

Need error, for `x` the current value (a fully open side is written `-` and contributes 0):

```
e = clamp( max( (lo − x)/(lo − floor),  (x − hi)/(ceil − hi),  0 ), 0, 1 )
```

`e = 0` inside the band, `1` at a fault limit. All arithmetic is integer on the node:
`e` is stored ×255 as `e8`.

### 4.2 Initial EV set (informative; every number below is a starting point, not a result)

| EV | `src` | Band | Bound provenance today | Has a candidate action? |
|---|---|---|---|---|
| `heap_free` | `ESP.getFreeHeap()` | keep above `lo` | Cardputer **measured**: 8.5–10.6 KB under real traffic, leak ≈ −500 B/min without restart (docs/log/2026-10.md) | yes: BLE scan restart |
| `heap_block` | `maxalloc_kb` | keep above `lo` | ~45 KB radios up (memory note, re-measure per board) | none known |
| `battery` | `bat_mv` + `bat_trend` | keep above `lo` | **declared** everywhere until a meter reads the pack on the JST lead; T-Deck and V4 dividers are unmetered | yes: backlight dim (handhelds) |
| `die_temp` | `die_c_x10` | keep below `hi` | **declared** | yes: defer one entity scan (§7.3 applies) |
| `loop_worst` | `worst_loop_ms` | keep below `hi` | measured, but the stall is unattributed | **none**: kept deliberately, see §8.3 |
| `neighbours` | Social roster / `Novelty` | keep above `lo` | observe-only | **none**: other nodes control it |

`sensor_age` and `radio_duty` (proposed in the earlier draft) are not EVs. Staleness is
what TBEW `conf` already expresses. No board counts airtime, so `radio_duty` would need an
instrument before it could be a variable.

### 4.3 Declared bounds may display but MUST NOT act

A band with `bound:declared` may raise `e` and may reach the arbiter (§6). It **MUST NOT**
drive action selection (§7). An action chosen from a guessed band teaches the action
model about the guess, and Rule 3 then folds the guess in as evidence. This applies
TTDB-RFC-0010 §6 ("no measured constant from a field") to bands. A bound becomes
`measured:` only by citing the log entry that measured it.

## 5. The `intero` episode tier (EVIDENCE)

One `@LAT103` episode per interoception window, `source: intero`, rendered through
`EpisodeNode::scratch()`. **A second static render buffer is forbidden**: one boot-looped
the Cardputer at +5.6 KB `.bss`. Bounded by a new `SEMANTIC_QUOTA_INTERO` and reclaimed by
the fold-and-cut like every other tier. **No new lane.**

Change-triggered with run-length, like `@LAT95`. A window whose per-EV `e8` bucket matches
the run in progress writes nothing. The closing record states what it suppressed, so
counting records under-reports calm, exactly as `@LAT95` does. A reader MUST sum covered
windows.

The window uses a local `millis()` duration. The episode's `at:` carries the fleet order
as every tier's does. See Appendix A.1.

## 6. Display: the `MOD_INTERO` arbiter modality

Append `MOD_INTERO` to `attention::Modality` after `MOD_NEIGHBOUR`. Order is the
tie-break, so appending keeps existing behaviour.

- `sal = max_k(e8_k · w_k / 255)`
- `conf` = how well the need is **explained**. A falling pack with `bat_trend = +1` is
  explained (it is charging). A heap dip within 10 s of a scheduled scan restart is
  explained. Otherwise `conf = 0`.

This is the arbiter's own rule (an explained stimulus can never win, however loud) applied
to the body. It needs no new math. **Done-condition, modelled on S3:** with a pack pulled
below `lo` the screen is seized **exactly once** per crossing, and released when charging
explains it.

The earlier draft multiplied `sal` by an arousal gain computed from `max(e)`. That was
dropped: it scaled the need's salience by the same need, which is circular. The
arbiter's `total()` is already the fleet's arousal figure.

## 7. Actions with expectations

### 7.1 An action declares, before it fires (Rule 1)

```
**EXPECTED** ev:heap_free action:ble_restart predicted_delta:+1800 within_ms:10000 band:600
```

Predictions come from the action-model belief (§7.4). With no belief yet, the action's
declared prior is used and the outcome's `**PROVENANCE**` says `basis:prior`.

### 7.2 The outcome is appended, never mutated (Rule 2)

After `within_ms`, the node appends one `source: action` episode carrying `**EXPECTED**`,
`**OBSERVED** ev:… observed_delta:… verdict:met|violated|unobserved` and
`**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3`. `unobserved` covers the
case where the variable could not be read, or the window was disturbed by the cable
(`bat_trend` flips to `+1` mid-window).

⚠ **Needle discipline.** These lines are keyed `ev:`, never `peer:0x`.
`Reconciler::foldRecord` folds every `**OBSERVED** peer:0x` / `**COVERED** peer:0x` it
finds, so a homeostatic outcome that matched would be folded into the link beliefs as
testimony about a radio. A native test MUST assert the non-match. This is the same family
as `prev_stream:` and `**COVERED-SPAN**`.

### 7.3 An action that changes perception MUST say so in that tier

Deferring an entity scan cools the die and also thins `@LAT96` evidence. This is the same
silent downgrade that a missing `-DENTITYPERCEPT_MAX_RUN=1` caused. Any action that alters
a percept tier's duty MUST stamp the affected tier's next episode with
`perturbed_by: action:<name>`, and the boot banner MUST list the actions a build can take.
A survey reader MUST be able to exclude perturbed windows.

### 7.4 The action model is a KEY belief folded by Rule 3

One belief record per `(action, ev)`, rewritten in place, never appended. That makes it
TTDB-RFC-0010's KEY class, bounded by the vocabulary. It carries TBEW `[ew]` with `conf`
from Rule 3: met `+2` (saturating), violated `−16` (floor 0) and `sal +8`. It also stores
the running median of `observed_delta`, which becomes the next prediction. The fold is
recomputable from the outcome episodes alone, and the laptop recomputing it to the same
`conf` is the verification (as it was for `@LAT91` on 2026-08-02). See Appendix A.3.

The earlier draft updated predictions by an exponential step and raised confidence by a
fixed `+0.05` on every execution, met or not. That breaks Rule 2 (it mutates instead of
testifying) and Rule 3 (confidence rises on failure). It is withdrawn.

### 7.5 Rule 4 aborts

*K* = 3 consecutive `violated` verdicts for `(action, ev)` suspend that action for that EV
until a `met` verdict is observed from some other cause or the operator re-arms it. The
suspension is itself a recorded outcome. *K* stays at 3 because that is the spec's value.
It is still a guess, and this domain is the first place it can be measured.

## 8. Selection

### 8.1 Rule

Each selection tick (proposed 10 s, local `millis()`):

```
eligible(a) = a not suspended (Rule 4), not in refractory, every EV it affects has bound:measured
gain(a)     = Σ_k  w_k · ( e_k − ê_k(a) ) · conf(a,k)/255
```

`ê_k(a)` is the need error predicted after applying the belief's median delta. The sum
runs over **every** EV the action touches, so a predicted worsening counts as negative
gain at its own confidence. Pick `argmax gain` if it is `≥ θ`; otherwise **rest**. Ties go
to the lower action index.

### 8.2 Hysteresis

Refractory per action ≥ its own `within_ms`, so an outcome is always observed before the
action can repeat. An EV is "satisfied" again only after `e = 0` for *H* consecutive
windows.

### 8.3 An EV with no effective action must produce rest, not thrash

`loop_worst` and `neighbours` are kept in the set precisely because nothing the node can do
fixes them. The correct behaviour is: they display (§6), they never select, and any action
tried against them is aborted by Rule 4 after *K* failures.

## 9. Valence (optional; a reading, not a control input)

`L = Σ_k w_k · e_k` (need load); valence `v = −ΔL/Δt` over a local-`millis()` window,
low-passed. Positive means improving. This follows Joffily & Coricelli (2013), who define
valence as the negative rate of change of free energy; need load is a crude engineering
stand-in for that quantity, not an equivalent.

**v is not derived from EPS.** The earlier draft used `v = −Δ Σ EPS`. A fresh trusted
reading has `conf = 255` and therefore EPS 0, so its valence was identically zero (its own
simulation printed `v = 0.0` on every one of 500 ticks). Need and uncertainty are
different axes. EPS ranks what to **look at**; `L` ranks what to **fix**.

Valence carries no weight in §8. Feeding it into the semantic valence field is out of
scope until the field question (`research/valence/`, other repo) is settled.

## 10. Budget

The intero tier and the selector MUST add no static buffer above 1 KB on the Cardputer
(BLE starvation at +5.6 KB `.bss`) and MUST hold its loop budget (≤ 40 ms worst pass
outside the known stall). Flash and RAM cost MUST be measured against a HEAD worktree and
stated, as every tier's has been.

## 11. Conformance

A conforming node MUST: write `intero` episodes (§5); refuse action selection on declared
bounds (§4.3); emit an `**EXPECTED**` before every selected action and an outcome episode
after it (§7.1–7.2); keep homeostatic lines off the link-fold needles (§7.2); stamp
perturbed tiers (§7.3); fold action models by Rule 3 recomputably (§7.4); apply Rule 4
(§7.5).
It SHOULD implement `MOD_INTERO` (§6). It MAY compute valence (§9).

## 12. Open questions

1. **Where do action-model beliefs live?** In `@LAT91` with a distinct verb
   (`**ACTION-MODEL**`), next to the link beliefs that `FACE_BELIEF` already reads, or in a
   new KEY lane at `@LAT107`? Recommendation: `@LAT91`, provided the native needle test of
   §7.2 also covers the verb.
2. Should `bat_trend = +1` (charging) mark the whole window `unobserved` for battery
   outcomes, or only those that span the flip?
3. Do fleet-level needs exist (e.g., "the band has no conductor")? Those belong to the
   default network (`Social`) and are out of scope here.
4. Should *K* scale with an action's prior `conf`?

## 13. References

- Ashby, W. R. (1960). *Design for a Brain* (2nd ed.). Chapman & Hall. (Essential
  variables, ultrastability.)
- Joffily, M. & Coricelli, G. (2013). Emotional valence and the free-energy principle.
  *PLoS Computational Biology*, 9(6), e1003094.
- Solms, M. & Friston, K. (2018). How and why consciousness arises: some considerations
  from physics and physiology. *Journal of Consciousness Studies*, 25(5–6), 202–238.
  (Motivation only: viability bounds and the primacy of interoception. No formula here is
  taken from it.)
- Hesp, C. et al. (2021). Deeply felt affect: the emergence of valence in deep active
  inference. *Neural Computation*, 33(2), 398–446. (Valence as a change in confidence in
  one's own action model; cf. §7.4.)
- Corpus: `@LAT20LON3`; A32-RFC-0003; TTDB-RFC-0005 §3.3; TTDB-RFC-0010 §§3, 6;
  `docs/design/cardputer-sensorium.md` §§3, 4.5.

⚠ The bibliographic details above are from memory and are checked as plan item H0.3
before this draft leaves `docs/design/`.

---

## Appendix A — record shapes (proposed; syntax copied from records on flash)

Headers and line shapes follow real records in `master/cardputer_*.md` (`@LAT103` episodes,
`@LAT91` beliefs). Field values are illustrative.

### A.1 Intero episode

````
@LAT103LON9000 | created:0 | updated:0

**intero window**

```ttdb-episode
source: intero
at: 31641581 ±21 frame:5500
seq: 1012
follows: 0x00000010:86 0x00000011:48
said: 1 | **INTEROWIN** window_ms:60000 node:0x300
said: 2 | **EV** name:heap_free x:9120 e8:0 bound:measured
said: 3 | **EV** name:battery x:3712 trend:-1 e8:41 bound:declared
said: 4 | **EV** name:loop_worst x:2009 e8:255 bound:measured
said: 5 | **RUN** windows_since_last:4 reason:changed max_run:30
```
````

### A.2 Action outcome episode

````
@LAT103LON9001 | created:0 | updated:0

**action outcome**

```ttdb-episode
source: action
at: 31652000 ±21 frame:5510
seq: 1013
said: 1 | **EXPECTED** ev:heap_free action:ble_restart predicted_delta:+1800 within_ms:10000 band:600
said: 2 | **OBSERVED** ev:heap_free observed_delta:+2140 verdict:met
said: 3 | **PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:belief
```
````

### A.3 Action-model belief (KEY, rewritten in place)

```
@LAT91LON20 | sid:<8 hex> | created:0 | updated:0 | relates:believes_about@LAT0LON0,derived_from@LAT103LON9001
[ew]
conf:132
rev:2
sal:0
touched:0
[/ew]

**ACTION-MODEL** action:ble_restart ev:heap_free median_delta:+2010 n:2 node:0x300
**TALLY** met:2 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 suspended:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT103/source:action method:sequential_fold_from_baseline
```
