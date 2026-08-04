# Handoff: Part B proper — change-triggered logging

**Work order for a fresh session.** Authored 2026-08-03 against `robot_team` @ `c353568`.
Read [companion.md](companion.md) §6 first — it is the source of truth, and its last eight
entries are the work this document continues.

This supersedes [semantic-logging-handoff.md](semantic-logging-handoff.md), whose **Part A
is done** and whose **Part B is opened but not finished**. What is left is the substance:
making `@LAT95` change-triggered without breaking the two things that depend on it being
periodic.

---

## Part 0 — Where things stand

**All five nodes carry the same firmware and share one timeline.** Stream `0xe7384824`,
originated by V4-A and adopted by everyone else, laptop in none of the paths.

| node | id | `@LAT90` | notes |
|---|---|---|---|
| V4-A bridge | `0x10` | 3 | originated `0xbdc62024` **and** `0xe7384824` |
| V4-B relay | `0x11` | 3 | |
| V4-C edge | `0x12` | 3 | reachable but **not pullable over the air** — use its cable |
| T-Deck | `0x200` | 11 | the only GPS |
| Cardputer | `0x300` | **1** | the only IMU + mic; hit the 16/16 cap and was repaired |
| K10 | — | — | v1 firmware, off the roster, still the last non-participant |

Tests: native **453 checks, rc=0** (`bash scratchpad/t.sh`; portable zig at
`c:/tmp/toolchain/`, there is no host g++ or make). Python **230 checks across 8 files**
(run each `tests/test_*_py.py` directly).

**Landed this session** (all hardware-verified, detail in companion.md §6):
`proximity --since` with the fleet-clock reference · the `@LAT97`/`@LAT96` prune on all
five nodes · **lane generations** (`@LAT100`, `firmware/libraries/LaneGen`) · **B.3's
measurement** — `MOTIONPERCEPT_MOVING_MG 60` confirmed at 5.0× the measured noise floor ·
the **origin hold** (`TIMESTREAM_ORIGIN_SETTLE_MS`) · the **`@LAT90` prune** that carries
its stream ids forward.

---

## Part 1 — `@LAT95` CHANGE-TRIGGERED (the remaining substance)

`MOTIONPERCEPT_MAX_LANE 48` ([MotionPercept.h:79](firmware/libraries/MotionPercept/src/MotionPercept.h#L79))
with `MOTIONPERCEPT_FLUSH_MS 60000` ([:76](firmware/libraries/MotionPercept/src/MotionPercept.h#L76))
fills the lane in 48 minutes of uptime whether or not anything happened. **Measured three
times on 2026-08-03: every lane on every node refilled to its cap within one afternoon of
being emptied.** Pruning is a treadmill; this is the fix.

### 1.1 ⚠ The record is a CITATION — solve this first or not at all

`PerceptLearn::arm(int motion_lane)`
([PerceptLearn.h:159](firmware/libraries/PerceptLearn/src/PerceptLearn.h#L159)) stores it as
`acting_lane_` — *"the @LAT95 record whose `still` claim armed this"*
([:196](firmware/libraries/PerceptLearn/src/PerceptLearn.h#L196)) — and the sketch arms
from the record it has just written: `int lane = laneCount(95)`
([cardputer_console.ino:3476](firmware/cardputer_console/cardputer_console.ino#L3476)) then
`gLearn.arm(lane)` ([:3516](firmware/cardputer_console/cardputer_console.ino#L3516)).

So an expectation is **provenanced to a specific record**. Change-trigger the lane naively
and a `still` window matching its predecessor writes nothing — leaving nothing to cite.
Arming against the last-written lane instead would cite a record describing a *different*
window: testimony with false provenance, which `@LAT92`'s tally then inherits. That is
worse than not arming.

**The resolution is explicit run-length: `windows_since_last:N`**, so one record honestly
covers N windows and remains a valid citation for all of them.

### 1.2 ⚠ `@LAT92` is a TALLY and shares the same fix

`met_ / violated_ / unobserved_`
([PerceptLearn.h:200](firmware/libraries/PerceptLearn/src/PerceptLearn.h#L200)) feed `conf`.
A state series can be compressed by keeping transitions; **a tally cannot** — dropping
unchanged windows removes the denominator and `conf` becomes systematically
over-confident. Either leave `@LAT92` periodic or give it the same run-length form. Decide
both together; they are one decision.

### 1.3 What B.3 already settled, and what it did not

- **The threshold is confirmed.** p90 of `dev_max_mg` = 12 mg over 48 known-quiet windows,
  so 60 mg is 5.0× the floor and 3× the worst excursion in 50 minutes. Derivation table is
  in the header beside the constant.
- **Rest-state flapping is a non-issue on this board**: `moving_permille` was **0** in all
  48 windows, not merely under the 100 verdict gate. So hysteresis is not needed to stop a
  stationary node flapping.
- ⚠ **The EDGE of real motion is unmeasured.** A walk-and-stop run is what would show
  whether hysteresis or a minimum dwell is needed there. Derive it; do not pick it.
- 📎 `@LAT93` (transitions) is **already** change-triggered with its own budget
  (`MOTIONPERCEPT_MAX_TRANSITION_LANE 32`,
  [MotionPercept.h:135](firmware/libraries/MotionPercept/src/MotionPercept.h#L135)).
  **Generalize that shape; do not invent a new one.**

---

## Part 2 — `@LAT96` CHANGE-TRIGGERED

Same cap and window (`ENTITYPERCEPT_MAX_LANE 48`
[EntityPercept.h:36](firmware/libraries/EntityPercept/src/EntityPercept.h#L36),
`ENTITYPERCEPT_FLUSH_MS 60000` [:31](firmware/libraries/EntityPercept/src/EntityPercept.h#L31)).
The change signal is **Jaccard drift between consecutive windows**, and its threshold has
to be measured, not chosen — the same standard B.3 met.

✅ **The collection clock has been running since 2026-08-03**: every node's `@LAT96` lane
was pruned that afternoon, so the accumulating windows are a clean baseline. ⚠ The AP set
is not stationary the way an accelerometer's floor is — neighbours' APs come and go on
their own schedule, so the quiet baseline includes churn the node did not cause. Measure
long enough to see it, and expect a looser threshold than intuition suggests.

---

## Part 3 — Closeouts

- **`TIMESTREAM_MAX_LANE 16`'s full-policy is still "refuse and print"** — but it is now
  survivable rather than terminal, because `cmd --lane 90` can prune the lane and carry its
  stream ids into the boundary. Whether refusing is still the right behaviour when a prune
  path exists is worth one paragraph of thought.
- **`LANEGEN_MAX_LANE 32`'s full-policy IS decided** (refuse the prune, say why) with the
  cost stated in the header. Nothing to do unless it is ever reached — if it is, that is
  the finding.
- **The K10.** Compiles at 20%, wire-compatible, sends 0-byte HELLOs. One flash when it
  next appears.
- **`percept-learning-return.md` is still cleared and unsent to TTE.** Part E of the old
  handoff lists what to add; this session adds two more claims worth carrying: *a citation
  is an ordinal, so a prune re-points it unless the boundary is written down*, and *a
  constant that survives its own measurement is worth more than one that was reasoned
  about* (B.3 confirmed 60 mg; the first attempt at measuring it was wrong by 2.75×).

---

## Traps carried forward (every one cost real time on this fleet)

- **A lane's own label is not evidence.** Deriving the motion threshold from the windows
  already on flash gave p90 = 33 mg; a run with the node deliberately untouched gave
  **12 mg**. Those windows said `state:still` — a verdict computed *with the threshold
  being measured* — and the node had been handled. **Prune, then collect yourself.**
- **Identify a board by reading its app image**, never from a mesh reply or a USB instance
  path (that names a *socket*, not a board). `esptool read-flash 0x10000 0x100000` then
  grep the sketch's own banner literal. `esp_app_desc_t.project_name` reads
  `arduino-lib-builder` on every arduino-cli build. ⚠ The full-length read failed three
  times this session near the tail — retry at `--baud 460800`, or read `0x100000`.
- **`companion.py` resets the cabled node on most invocations, and that hides collection.**
  V4-A wrote no percept window for minutes while it was being used as the bridge, because
  every call restarted its 60 s window. A node under measurement must be left alone.
  (⚠ A V4 does *not* reset on port open; the handhelds do. Check reported uptime.)
- **A no-ACK "NOT applied" is often a false negative.** A lane clear rewrites the whole
  TTDB and outruns the default RTO ladder — `ping` to prove the link, then retry with
  `--attempts 6+`. The op is idempotent.
- **A bridged pull is unreliable and a node can be commandable but un-pullable** (V4-C:
  `ping`, `clear-percepts` and a 21-byte INTERO all fine, TTDB pull empty twice — then
  25558 B first try on its own cable). **Never clear a lane you could not pull first**
  unless that lane is full.
- **n=1 and n=3 timing samples on this fleet are noise.** n≥9, and observe the mechanism
  with a serial print rather than chaining hypotheses off indirect timing.

---

*Every file path, line number, constant and count above was verified against the working
tree at `c353568`, not recalled. The archived run data referenced by Part 1 lives in
`master/prune-2026-08-03/` — `cardputer_motion_gen1.md` is the contaminated sample and
`cardputer_motion_gen2.md` the clean 48-window run, which is the pair that makes the
"a lane's own label is not evidence" trap reproducible rather than anecdotal.*
