# Handoff: recency in time, then semantic logging

**Work order for a fresh session.** Authored 2026-08-03 against `robot_team` @ `6abc919`
with a clean tree. Read [companion.md](companion.md) §6 first — it is the source of truth,
and its last four entries are the team-time-stream work this document builds on.

This continues [timestream-handoff.md](timestream-handoff.md), whose Part 1 (the
verification gate) and Part 2 (the team time stream) are both **done and hardware-verified**.
What is left of it is its Part 3, and the order below is a refinement of that plan made
after reading the code it touches.

**The order is load-bearing, and the first step is not the one the old handoff named.**

> **SUPERSEDED 2026-08-03 by [part-b-handoff.md](part-b-handoff.md)** — Part A is done,
> Part B is opened (lane generations + the B.3 measurement), and what remains of B and C
> is restated there against the current tree. Read that one; this stays for its reasoning.
>
> **STATUS 2026-08-03: Part A is DONE** (`--since`, the fleet-clock reference, and the
> A.1 entity-tier fix; `test_prox_py` 74 → 94 checks). Its first run on the real corpus
> found that **the `@LAT97` lane is at its 48-record cap on all five nodes with zero
> post-flash records** — see companion.md §6. **Prune it (`proximity --clear`) before
> starting Part C's collection**, or the window collects nothing. Next: Part B.

1. **Part A — recency becomes a TIME window** (`--last N` → `--since`). The old handoff
   filed this under "traps, audit before changing any tier". It is more than that: Part 2
   made it properly *fixable* for the first time, and it must land before any lane changes
   or the fusion silently starts weighting a biased sample.
2. **Part B — `@LAT95` change-triggered.** The lane whose cap silently disarmed the
   learning loop on 2026-08-02.
3. **Part C — `@LAT96` change-triggered.** Needs a measured threshold, which needs
   wall-clock time; start its data collection early.

Throughout: `TTE` = `toot-toot-engineering`, `RT` = `robot_team`.

---

## Part 0 — Where things stand

**Five nodes share one timeline.** Stream `0x59fb8ce8`, propagated Cardputer `0x300` →
T-Deck `0x200` → V4-A `0x10` / V4-B `0x11` → V4-C `0x12`, multi-hop, each node adopting
from whichever neighbour it heard first, with the laptop in none of the paths. Every
percept record now carries `t_ms:<ms> stream:0x<id> wall:<0|1>`.

| node | id | timestream | notes |
|---|---|---|---|
| Cardputer ADV | `0x300` | ✅ | the only IMU + mic; the only node that can author `@LAT91` |
| T-Deck | `0x200` | ✅ | the only GPS |
| V4-A / V4-B / V4-C | `0x10`/`0x11`/`0x12` | ✅ | all at **94%** flash, ~71–74 KB left |
| K10 | — | ❌ | v1 firmware, off the band roster; sends 0-byte HELLOs |

Native suite: **419 checks, 0 failures** (`bash scratchpad/t.sh`, rc=0 — there is no host
g++ or make on this machine; portable zig lives at `c:/tmp/toolchain/`). Counting
convention varies between suites, so that number is `grep -ciE "^\s*(pass|ok)[: ]"`.
Python suite: **7 files, all passing** (run each `tests/test_*_py.py` directly).

`percept-learning-return.md` has been **cleared for TTE since Part 1 passed** on
2026-08-02 and has not been sent. Part 2 adds three claims to it — see Part E.

---

## Part A — RECENCY BECOMES A TIME WINDOW

### A.0 Why this is first, and why it is not merely an audit

`companion.py proximity --last N` is documented as "use only each node's newest N windows —
the recency filter" ([companion.py:2244](orchestrator/companion.py#L2244)). It is
implemented as a **slice**: `wins = wins[-last:]`
([companion.py:2257](orchestrator/companion.py#L2257)) and
`windows = windows[-last:]` ([companion.py:1944](orchestrator/companion.py#L1944)).

Under periodic logging, N records ≈ N minutes, so the slice is a passable proxy for time.
**Under change-triggered logging it is not**, and the error is not random: a node that sat
still writes few records, so "its newest 6 windows" may reach back hours, while a node that
moved writes many and its newest 6 cover minutes. The filter would then be *strictest
exactly on the node with the most recent evidence* — backwards.

Before Part 2 the only honest response was the old handoff's: audit the consumers and be
careful. Now every window carries a comparable `t_ms` on a named stream, so recency can be
**stated in milliseconds instead of approximated by counting**. This is the first thing the
team time stream pays for, and it is a small change.

### A.1 ⚠ FINDING — `--last` is silently NOT applied to the entity tier

`consolidate_entity_jaccard(windows_by_node, last=None)` takes a `last` parameter
([companion.py:1962](orchestrator/companion.py#L1962)) and passes it to `_entity_set`.
**Its only call site does not supply one:**

```python
# companion.py:2391
entity_bounds = {frozenset(e["pair"]): e
                 for e in consolidate_entity_jaccard(entity_windows_by_node)}
```

So `proximity --last 6` narrows the RSSI evidence to six windows while the **entity cap
that bounds it from above is computed over the node's entire history**. A node that was
carried across the house keeps every AP it ever saw in its Jaccard set, so the pair looks
co-located and the bound stays tight — and the `--last` flag the operator passed to say
"that node moved, use recent evidence only" is exactly the case it fails on.

This is pre-existing, unrelated to Part 2, and has never been reported because a bound that
is too tight produces a plausible number rather than an error. **Fix it in the same change**
— it is the same concept and the same call.

### A.2 What to build

1. Add `--since <duration>` to `proximity` (and anywhere else the recency filter lands),
   parsed to milliseconds. Keep `--last N` working — it is in `companion.md` runbooks and
   in muscle memory — but have it **warn** when the corpus contains change-triggered lanes.
2. Filter on `w["t_ms"]` relative to the newest window **in that node's own stream**, not
   wall-clock: most records are `wall:0` and always will be in a garden.
3. ⚠ **Windows on a different stream than the node's newest are not comparable and must not
   be silently dropped or silently kept.** `stream:0x00000000` means "local `millis()`,
   comparable with nothing but this node's own records" and pre-2026-08-03 records read back
   as stream `None` ("some clock, unnameable"). Decide the policy explicitly and print a
   count of what was excluded. A silent subset is this project's signature failure.
4. Pass the same window into `consolidate_entity_jaccard` (A.1).

### A.3 Tests

Extend `tests/test_prox_py.py`. It already carries `TEXT_STREAM` fixtures in both record
formats and three `@LAT90` order-independence checks. Add:

- a node whose newest window is old, against one whose newest is fresh — assert the time
  filter keeps the right ones where `--last N` keeps the wrong ones;
- a mixed corpus where some windows carry `stream:None` (old `synced:1`) and assert the
  documented policy, with the exclusion count;
- an entity-cap case proving `--since` reaches `consolidate_entity_jaccard` (the A.1 bug,
  pinned so it cannot come back).

---

## Part B — `@LAT95` CHANGE-TRIGGERED

### B.0 ⚠⚠ READ THIS BEFORE TOUCHING THE LANE — the record is a CITATION

This is the coupling that will not be obvious from the old handoff, and it is the reason
this part is bigger than it looks.

`PerceptLearn::arm()` takes the @LAT95 lane number and stores it:

```
PerceptLearn.h:159   bool arm(int motion_lane);
PerceptLearn.h:196   int acting_lane_;   // the @LAT95 record whose `still` claim armed this
```

and the sketch arms **from the record it just wrote**:

```
cardputer_console.ino:3513   } else if (gLearn.arm(lane)) {
```

where `lane = laneCount(95)` — the count of existing @LAT95 records
([cardputer_console.ino:3473](firmware/cardputer_console/cardputer_console.ino#L3473),
`laneCount` at [:1149](firmware/cardputer_console/cardputer_console.ino#L1149)).

So Rule 1's expectation is **provenanced to a specific @LAT95 record**: the still-claim that
makes the prediction refutable. Under naive change-triggered logging a `still` window that
matches the previous one writes nothing — and then there is no record to cite. Arming
anyway would cite a record that describes a *different* window, which is worse than not
arming: it produces testimony with false provenance, and `@LAT92`'s tally would inherit it.

**Do not solve this by arming against the last-written lane.** The clean resolution is
§3.3.2 of the old handoff, which turns out to be the same idea as the heartbeat: convert
the window record to explicit **run-length** — `windows_since_last:N` — so a single record
honestly covers N windows and remains a valid citation for all of them. Then `arm()` can
cite it, and `conf`'s denominator (see B.2) stays intact.

### B.1 Why this lane first

It is the lane that broke the 2026-08-02 experiment, and the sketch says so in a comment
that should be preserved:

> `@LAT95` hit 48/48 after 48 minutes, four `@LAT92` outcomes had been written, and the loop
> then went quiet with no error anywhere. The motion lane fills ~2× faster than the link lane
> (motion flushes with no peers in range; link needs an observation), so it is always the
> first cap to bite.
> — [cardputer_console.ino:3478](firmware/cardputer_console/cardputer_console.ino#L3478)

`MOTIONPERCEPT_MAX_LANE 48` ([MotionPercept.h:79](firmware/libraries/MotionPercept/src/MotionPercept.h#L79))
with `MOTIONPERCEPT_FLUSH_MS 60000` = the lane fills in 48 minutes of uptime regardless of
whether anything happened. Change-triggered, a node on a shelf writes ~1.

The full-lane path is now loud (a throttled serial line every 5 min) but still **discards
the window and disarms the loop**. Loud is not fixed.

### B.2 The rule that must NOT be broken

`@LAT92` is a **tally**, not a state series: `met_ / violated_ / unobserved_`
([PerceptLearn.h:200](firmware/libraries/PerceptLearn/src/PerceptLearn.h#L200)) feed `conf`.
You can compress a state series by keeping only transitions. **You cannot compress a tally
that way** — dropping the unchanged windows removes the denominator and `conf` is then
computed from a biased sample that is systematically over-confident.

**Leave `@LAT92` periodic**, or convert it to explicit run-length (`windows_since_last:N
met:N`). Do not simply change-trigger it. This is the same mechanism as B.0 and they should
be decided together.

### B.3 ⚠ FINDING — the motion threshold is CHOSEN, not derived

The old handoff's §3.3.3 says *derive the thresholds, do not choose them*, and holds up
`PERCEPTLEARN_RSSI_BAND 6` as the model — correctly: it is the **p90 of that node's own
consecutive-window drift across 33 known-quiet link windows**, with the derivation table
written into the header
([PerceptLearn.h:48–71](firmware/libraries/PerceptLearn/src/PerceptLearn.h#L48)).

`MOTIONPERCEPT_MOVING_MG 60` is **not** derived that way:

> Hand tremor on a held device is ~20-40 mg; a walking stride peaks in the hundreds. 60 mg
> keeps "held still in a hand" on the still side of the line.
> — [MotionPercept.h:83](firmware/libraries/MotionPercept/src/MotionPercept.h#L83)

That is a reasoned choice from published figures, not a measurement of **this BMI270 on
this board**. It has never been checked against the Cardputer's own noise floor. Before
change-triggering the lane, measure it the way `PerceptLearn.h` did: log the deviation
statistic across a run where the node is known to be stationary, take the p90, and write the
table into the header. If 60 mg survives, say so — a confirmed constant is worth more than
an assumed one. If it does not, the `still` claims that the entire learning loop rests on
have been resting on the wrong line.

### B.4 The flapping trap is real here

A signal sitting exactly at the threshold produces **more** records than periodic logging.
`PerceptLearn`'s band already landed a `d=6` exactly on the line once. `@LAT95`'s verdict is
`permille >= 100` ([MotionPercept.h:116](firmware/libraries/MotionPercept/src/MotionPercept.h#L116)),
so a node at ~10% motion flaps every window. Needs hysteresis (different up/down thresholds)
or a minimum dwell. Derive that too — do not pick it.

Note the transition lane `@LAT93` is **already** change-triggered and already has its own
budget (`MOTIONPERCEPT_MAX_TRANSITION_LANE 32`), with a header comment explaining that a
still node writes none. That is the template. Generalize its shape; do not invent a new one.

---

## Part C — `@LAT96` CHANGE-TRIGGERED

Same cap (`ENTITYPERCEPT_MAX_LANE 48`), same window
(`ENTITYPERCEPT_FLUSH_MS 60000`), max 12 entities per window
([EntityPercept.h:26–37](firmware/libraries/EntityPercept/src/EntityPercept.h#L26)).

The change signal is **Jaccard drift between consecutive windows**, and its threshold has to
be measured, not chosen — the same standard as B.3. That measurement needs a stretch of
wall-clock time with the fleet powered and undisturbed, so **start collecting it on day one**
and do Parts A and B while it accumulates.

⚠ The AP set is not stationary the way an accelerometer's noise floor is: neighbours' APs
come and go on their own schedule, so the "quiet" baseline includes real churn the node did
not cause. Measure long enough to see that, and expect the threshold to be looser than
intuition suggests.

---

## Part D — Two closeouts from Part 2

### D.1 `TIMESTREAM_MAX_LANE 16` — the refusal-on-full policy

Deliberately left undecided until the accumulation rate could be measured. **It now can be,
and the data says the cap is generous:**

| node | `@LAT90` records | comment |
|---|---|---|
| T-Deck `0x200` | 9 | **all pre-fix churn** — 6 redundant ADOPTED + the ORIGIN the listen-window bug caused |
| V4-A / V4-B / V4-C | 1 each | after flashing, multiple resets, and full pulls |

Post-fix a reboot onto the stream the node is already on writes **nothing**. So 16 is not
close to binding and **should not be raised** (`TimeStreamNode.h:34–40` explains why: it is
a guard against a pathology, not a routine ceiling — if it is reached, that *is* the finding).

What is still undecided is only what happens **when** it fills. Today it prints and refuses
([TimeStreamNode.h:203](firmware/libraries/TimeStream/src/TimeStreamNode.h#L203)), which
means the next stream's records carry an id nothing in the lane explains — a silent
un-interpretable subset, exactly the failure class this project keeps finding. Decide
deliberately; "loud and refuse" may be right, but it should be a decision rather than a
default.

### D.2 The K10

The last non-participant. It compiles (20% flash) and is wire-compatible — a 0-byte HELLO
payload makes it a non-participant, not a parse error — but it is on v1 firmware and off the
band roster, and it was not plugged in when the rest of the fleet was flashed. One flash when
it next appears.

---

## Part E — What to send TTE

`percept-learning-return.md` is cleared and unsent. Part 2 gives it three claims it could not
make on 2026-08-02:

1. **A `touched` that means something.** Rule 3's `sal` can now decay, so EPS becomes
   computable on-device. ⚠ Carry the spec gap with it: `TTDB-RFC-0005` defines `touched` as
   **Unix epoch seconds**, which a laptop-less fleet cannot produce — so the recency
   machinery was inert exactly where it mattered. RT did **not** redefine the unit (that
   would have made the corpus half-parseable); it kept `touched:` spec-conformant and added
   a `**TOUCHED**` body line carrying the stream time. And **Rule 3 specifies how salience
   RISES and never says what makes it fall.**
2. **Cross-node transition ordering** — the precondition for the Phase-3 TDoA tier
   `TTN-RFC-0011` anticipates, and part of the §2.5 debt (no field result has ever been
   folded back into RFC-0011). ⚠ Only the Cardputer has a mic, so multi-node TDoA is still
   unexercised.
3. **A retention story.** Stage D found that pruning the outcome lane resets the belief
   toward baseline: `conf` describes *retained testimony*, not history. Change-triggered
   logging changes what retention means, and TTE should hear both facts together.

⚠ One more worth raising, found while flashing: **a record's field ORDER is part of its
contract unless every reader is written not to care.** RT's seven observation formats render
`t_ms: stream: wall:` through one function; the `@LAT90` lane leads with `stream:` because
there the stream is the subject of the sentence. Both are right, and the order-anchored
reader silently returned nothing for an entire lane. If the RFCs specify fields by example,
they are specifying an order by accident.

---

## Traps carried forward (all cost real time on this fleet)

- **Identify a board by reading its app image**, never from a mesh reply — `ping`/`intero`
  answers arrive over the air from battery-powered nodes, and COM numbers move.
  `esptool read-flash 0x10000 0x140000` then grep for the sketch's banner literal.
  `esp_app_desc_t.project_name` reads `arduino-lib-builder` on every arduino-cli build.
- **A V4 does not reset when its port is opened** and prints nothing on serial at any
  DTR/RTS setting. The handhelds do reset. Check reported uptime against plug-in time.
- **Asserting DTR *and* RTS together is esptool's bootloader-entry sequence**, not a reset:
  it drops the board into silent `boot:0x3 (DOWNLOAD)`. Recover with
  `esptool --after hard-reset chip-id`; to reset deliberately pulse **RTS only**.
- **`companion.py` resets the cabled node on most invocations**, so a shell loop probes a
  just-rebooted node. Hold one connection (`scratchpad/reach.py`, `open_serial_no_reset`).
- **n=1 and n=3 timing samples on this fleet are noise.** n≥9, and observe the mechanism
  with a serial print rather than chaining hypotheses off indirect timing.
- **Try the T-Deck's automatic bootloader entry first**; keep the trackball-click + RST
  dance as the fallback, and do not ask the operator to hold a button before trying.

---

*Every file path, line number, constant and count above was verified against the working
tree at `6abc919` on 2026-08-03, not recalled. The two findings marked ⚠ FINDING (A.1, B.3)
and the B.0 citation coupling were discovered while writing this document; they are also
recorded in `companion.md` §6, which stays the source of truth.*
