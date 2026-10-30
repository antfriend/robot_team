# Homeostasis — build plan for A32-RFC-0005 (draft)

**Status:** proposal, 2026-10-30. Nothing built.
**Normative half:** [A32-RFC-0005-DRAFT-Homeostatic-Needs.md](A32-RFC-0005-DRAFT-Homeostatic-Needs.md)
(the same pairing as `stigmergy.md` ↔ TTDB-RFC-0010).
**Sequencing:** after ACT-III Phase D has started, or alongside it. H0–H2 touch only the
Cardputer and `fleet.py`. Nothing here may delay D.
**Replaces:** `RFC-HOMEOSTATIC-NEEDS.md`, `needs_golden_fragment.ttdb.md`,
`ttdb_needs.py` (untracked drafts at the repo root). The reasons are in Appendix R.

## The claim this plan tests

> A node can keep its own body in band **with no cable attached**, by acting on its own
> measured needs, and its record of *why* it acted and *whether that helped* is
> recomputable from its store alone.

Each phase has a **done-condition that is a measurement on a board**, plus the command or
artefact that shows it. A phase whose evidence is a simulation is not done.

## Ground rules (from what this fleet has already paid for)

- **Uncabled for every battery claim.** A cable charges the pack and resets the
  handhelds. Battery runs are on battery, read back afterwards with
  `fleet.py pull --port <own cable>`.
- **n ≥ 9 for any timing or effect claim**, with the uptime range stated, and nothing
  sampled during the boot stall.
- **Read the board's build from its boot banner** (`scratchpad/catchboot.py <PORT> 14`).
  Every phase adds a banner line declaring the actions this build can take.
- **Measure cost against a HEAD worktree** and state flash/RAM/`.bss` deltas. On the
  Cardputer, any new static buffer above 1 KB is a red flag (BLE starvation at +5.6 KB).
- **Recompute, don't trust.** Every number the node writes must be re-derivable on the
  laptop from the pulled store. A mismatch fails the gate.

## Phases

### H0 — Paper (no hardware)

1. Land the RFC draft and this plan in `docs/design/`. *(this commit)*
2. Decide RFC open question §12.1 (where action-model beliefs live). Recommendation:
   `@LAT91`, distinct verb.
3. Verify the four references in RFC §13 against the sources (authors, venue, volume,
   pages), and that §9's reading of Joffily & Coricelli (valence = −d(free energy)/dt) is
   what the paper says. Fix the RFC wherever it is wrong.
4. Native test, written first and failing: a homeostatic `**OBSERVED** ev:` line is **not**
   folded by `Reconciler::foldRecord`, and an `**ACTION-MODEL**` record is not mistaken for
   a `**LINK-STABLE**` belief.

**Done:** `bash tests/run-all` shows the new test compiling and failing for the right
reason. ⚠ Check that the test binary was actually rebuilt, not a stale `.exe` (the
2026-08-09 lesson).

### H1 — Interoception becomes evidence (Cardputer, then all six)

- `intero` episode tier in `@LAT103` via `EpisodeNode::scratch()`, `SEMANTIC_QUOTA_INTERO`,
  change-triggered with run-length. Add free heap; INTERO only carries `maxalloc`.
- `fleet.py`: `parse_intero_episodes` + an `intero` report that sums covered windows and
  reports `unaccounted`, as `motion` does.
- Boot banner: `[intero] tier: window:60s evs:<list> bounds:<measured|declared per ev>`.

**Done when:**
1. A Cardputer run of ≥ 2 h on battery, pulled afterwards, gives a laptop-recomputed `e8`
   per EV per window that matches the `e8` the node wrote, on every window.
2. Covered-window totals add up to wall time ±1 window.
3. The same check passes on the other five boards. On the T-Deck and V4s, `battery` shows
   `bound:declared`, which is the correct outcome there and not a failure.
4. Measured cost stated, with the loop budget held (worst pass ≤ 40 ms outside the known
   stall, ≥ 9 windows, uptime range stated).

### H2 — One reflex becomes an action (Cardputer, heap)

Convert the BLE scan restart from "every 60 s" to an **action with an expectation**, still
on the 60 s timer. Only the bookkeeping changes in this phase. Each restart writes
`**EXPECTED**` beforehand and an outcome episode after `within_ms`. The `(ble_restart,
heap_free)` belief is folded by Rule 3.

This is the cheapest true test: the effect is measured (≈ −500 B/min leak, bounded by the
restart), fast (seconds) and frequent (≈ 60 per hour).

**Done when:**
1. ≥ 9 outcomes on flash with verdicts. The laptop re-fold of `conf` from the outcome
   episodes alone matches the device's `[ew] conf` exactly.
2. Free-heap trend is no worse than the pre-H2 baseline over the same duration. The
   bookkeeping must not itself leak.
3. A deliberately wrong prior (predict `+20000`) produces `violated` verdicts and a
   falling `conf`. Rule 3's asymmetry is visible in the tally.

### H3 — Need chooses, against a fair baseline (Cardputer, heap)

Replace the 60 s timer with §8 selection over `heap_free` (measured band from H1).

**The baseline is the existing reflex**: same board, same build except
`-DHOMEOSTASIS_SELECT=0` (timer). It is not a strawman schedule.

**Done when, over ≥ 3 runs of ≥ 1 h per arm, alternating arms:**
- time with `heap_free` below `lo` under selection ≤ timer, **and**
- restarts per hour under selection < timer (each restart costs BLE near-range percepts),
  **and**
- zero resets (`rst:` reason on the next boot banner) in either arm.

**Stop condition:** if selection fails either of the first two criteria on 2 of 3 runs,
the timer was the better controller. Record that in `docs/log/` as the result and do not
proceed to H4 with selection.

### H4 — Rule 4 and the action that cannot help

Register a no-op candidate action against `loop_worst`, with a confident prior that it
helps. Nothing is known to fix the stall, so the expected result is *K* = 3 violated
verdicts followed by suspension.

**Done when:** across ≥ 3 boots the action executes **exactly *K* times** before
suspension, the suspension is a recorded outcome, and `loop_worst` never selects again in
that boot. This is the first execution of Rule 4 anywhere in the project. Record it
against `@LAT20LON3` as a computed tally, not an asserted one.

### H5 — The body takes the screen unprompted (Cardputer)

`MOD_INTERO` in the arbiter (RFC §6).

**Done when (operator-verified at the deck, ≥ 3 trials):** a pack below `lo` takes the
screen **exactly once** per crossing. Plugging in a cable (`bat_trend` → +1) explains it
and releases the screen. Calm EVs never win against a clap.

### H6 — A second action, and the perception it perturbs (optional)

`die_temp` via deferring one entity scan. **Gate:** every deferred scan's next `@LAT96`
episode carries `perturbed_by:`, and `fleet.py entity-survey` excludes it. Test that
exclusion on a measurement build.
Battery via backlight dim **only after** a meter has turned the Cardputer's battery band
into `bound:measured`.

## What is explicitly not in this plan

- Any claim that a node feels anything.
- Fleet-level needs (no conductor, split band). Those belong to `Social`.
- Feeding valence into a semantic valence field.
- Actions that touch the pulse, the band, radio protocol or the time stream.

---

## Appendix R — review of the drafts this replaces (2026-10-30)

The originals are kept outside the repo at
`C:\Users\antfr\AppData\Local\Temp\claude\c--git-robot-team\d1d6377b-074e-4fdd-af3a-45117ed527e2\scratchpad\original-needs-drafts\`.

### R.1 `ttdb_needs.py` — the self-test passes, but it does not test the claim

Instrumented with the drafts' own seed and world:

| Observation | Value |
|---|---|
| Distinct valence values over 500 ticks, either policy | **{0.0}** |
| Distinct total need-EPS values | **{0.0}** |
| Actions chosen by the need-driven policy | `read_sensor` ×62; `sleep` and `transmit` **never** |
| Battery at end, need-driven | **0.8 %** (floor 5): the policy runs the pack flat |
| Out-of-band EV-ticks: need-driven / drafts' fixed schedule | 578 / 939 (the self-test's "win") |
| Out-of-band EV-ticks: a trivial read/sleep/rest rotation | **50**, which beats the need-driven policy by 11× |
| Seeds 2–6 | 577 vs 937–939; the result does not depend on the seed |

Causes:
- `_drift` sets `age = 0` every tick, so `conf = 255`, every EPS is 0 and valence is
  identically 0. The oscillation and valence criteria (draft §11.2–11.3) were untestable.
- The "fixed" baseline spends a third of its actions on `transmit`, which has no benefit
  and only costs. The comparison is against a strawman.
- The out-of-band metric counts a dead battery the same as one 1 % below band.
- `sleep` *raises* the battery by 4 %/tick, which does not describe any board.
- `delta_conf += 0.05` on every execution, met or not, is the confirmation bias that Rule
  3's 1:8 asymmetry exists to prevent.

### R.2 `RFC-HOMEOSTATIC-NEEDS.md` — the right idea, but written without this repo

- **The action side already exists.** Learning from Action Rules 1–3 run on the Cardputer
  (`@LAT93`/`@LAT92`/`@LAT91`, gate passed 2026-08-02). The arbiter
  (`Attention.h`, 2026-10-06) is EPS-ranked selection over percepts. The draft proposed
  both as new.
- §8.4 updates the action model in place. That contradicts Rule 2 ("testify, never
  mutate") and replaces Rule 3's asymmetric fold.
- Valence was defined from Σ EPS. That makes a well-measured violated need contribute 0
  (shown numerically in R.1).
- Arousal scaled a need's `sal` by `max(e)` of the same needs, which is circular.
- EVs: `heap_free` used free heap only, but this fleet needs both free heap (leak) and
  `maxalloc` (allocation). `sensor_age` is TBEW `conf`, not a need. `radio_duty` has no
  instrument. Battery bands are not knowable on the T-Deck (reads 4.71 V) or the V4s
  (divider unmetered).
- Wrong cross-references: Dream Cycle is TTDB-RFC-0007, not "RFC-0002".
  `VALENCE_FIELD.md` is not in this repo. The project is robot_team, not "Locus".
- No lane discipline (TTDB-RFC-0010 requires each record's class). No mention of the
  `**OBSERVED** peer:0x` needle collision. No warning that an action changing scan duty
  silently degrades survey evidence. No uncabled requirement.
- The draft's own caveat ("formulas are proposed designs, not results from the cited
  paper") was correct. The valence-as-rate idea is better sourced to Joffily & Coricelli
  2013 than to Solms & Friston 2018.

### R.3 `needs_golden_fragment.ttdb.md` — syntax guessed, status overstated

- `@SELF:*` / `@ACT:*` / `@PERCEPT:before` is not this store's syntax. Records are
  `@LAT<n>LON<m> | …` headers with `[ew]` blocks and `**VERB**` lines, and since ACT-III C0
  every tier is a `@LAT103` episode. The replacement shapes in the RFC's Appendix A are
  copied from records on flash.
- It marks `@LAT20LON3` "implemented in ttdb_needs.py". A toy simulation is not an
  implementation. `@LAT20LON3` stays `conf:122 rev:1 sal:200` until a hardware tally moves
  it (H2/H4).
