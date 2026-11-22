# Handoff brief: TTDB-RFC-0011 stages 1, 3 and 4, and EXP-01

2026-11-22 · from the `toot-toot-engineering` session

## Where things stand

TTDB-RFC-0011 (*Precision Weighting and the Ignition Filter*) is at **v0.1.7** in
`c:\git\toot-toot-engineering\RFCs\TTDB-RFC-0011-Precision-Weighting-and-the-Ignition-Filter.md`.
Read §3 (arithmetic), §4 (PRECISION lane), §8 (falsifiers and results) and §9.2 (staging)
before starting.

Stage 2, the offline replay, is done. The code is in `tools/pw1/`, `tools/pw2/` and
`tools/pw3/` here, and each one was pre-registered before it read `master/`:

| Falsifier | Verdict | What it means for the next stages |
|---|---|---|
| PW-1 learned `π` separates channels | PASS | Only entity separates. Acoustic, motion and link sit at `π` ≈ 250–255 (see open question 6) |
| PW-2 gain protects settled beliefs | PASS | 139 rewrites vs 8 217. It is protection, not immunity, and genuine change is followed a little less often |
| PW-4 an empty workspace changes no answer | PASS | Tested on the reference implementation only |
| PW-3 broadcast gate | **FALSIFIED** | 38.1 % of beliefs go stale. **Stage 5 is blocked and §6.3 must not be built** |
| PW-5 fusion, PW-6 ignition signature | not run | PW-5 waits on EXP-01 |

Lanes: `@LAT108` PRECISION (EVIDENCE, KEY) and `@LAT109` WORKSPACE (FIELD, KEY), both still
unwritten. `@LAT103`–`@LAT106` were already taken here, which is why the RFC uses these. SALIENT
is toot type `15`, provisional (`14` is `EPISODE`). The RFC's §9.1 YAML still lists
`103`/`104` under `lane_classes`. Fix that in the RFC when you next write it back.

## Working rules (carried over; Dan has agreed to all of them)

- **Pre-register.** Before any experiment reads `master/` or runs on hardware, commit its
  protocol and constants with their sources. Never change a threshold after seeing data.
- **Verdicts are PASS, FALSIFIED or INCONCLUSIVE.** Not "KILL".
- **Write every result back to the RFC**, including failures. Use a §8.x section, the Status
  line and a changelog row with a version bump, and update the `INDEX.md` and `rfc.ttdb.md`
  entries in `toot-toot-engineering`.
- **Never write to `master/`** or to any archived TTDB.
- **Log every exclusion, and report surprises** as candidate `lat 98` divergence beliefs.
  Don't edit the RFC to match the code.
- **Work on a branch, commit locally, and push only when Dan says so.** Flashing and anything
  that touches a board needs Dan at the bench. Ask before each flash.
- This repo's `CLAUDE.md` takes precedence over this brief wherever they disagree.

## Task 1: Stage 1, readers (no behaviour change)

The RFC says: "Add `prec` to `TtdbParse` and `companion.py` field tables and test writer
against reader."

Two facts the RFC got wrong, which I found during stage 2:
- **There is no `companion.py`.** The laptop parsers are in `orchestrator/fleet.py`.
- **`TtdbParse` has no `[ew]` reader.** `firmware/libraries/TTDB/src/TtdbParse.h` parses headers,
  edges and `sid:`. Only `PerceptLearn` writes `[ew]` blocks, for `@LAT91`, and only
  `tests/test_perceptlearn.cpp` and `tests/test_citation.cpp` touch them. Stage 1 is therefore
  "a reader for `[ew]` that accepts `prec`", not "add a field to an existing table". Confirm
  this, then propose the smallest change.

Steps:
1. Find every reader and writer of `[ew]` and of `conf`/`touched` on both sides. Note that
   `fleet.py` writes belief fields as `conf: 0.75`, which is a different shape from TBEW's
   `conf:96`. Report the shapes you find before changing anything.
2. Add `prec` (0–255, default 128 when absent, `prec:0` meaning *ignore*, per RFC §3.1) to the
   readers. An unknown field must still be ignored (TTDB-RFC-0005 §4.1).
3. Test writer against reader, in C++ and Python, using the same vectors (TTDB-RFC-0010 §7.2's
   lesson). Cases: `prec` absent, `prec:0`, `prec:255`, malformed, and a pre-RFC record.
4. Stop and show Dan the diff. No firmware is flashed at this stage.

## Task 2: Settle open question 6 before stage 3 (offline)

Acoustic and motion `π` saturate at ≈ 255, probably because `pe_span` (32 767 for
`rms_mean`, 16 000 mg for `dev_mean_mg`) is far wider than the real residuals. Stage 3
writes `π` on a device, so settle this first.

- Pre-register a rule for deriving `pe_span` from the *physical* range a channel actually
  uses, such as the sensor's observed operating range or a datasheet figure for the quantity
  logged, and commit it before looking at residuals. **Do not choose `pe_span` by re-running
  PW-1 until the channels separate.** That would be tuning against PW-1.
- Re-run PW-1 with the new constants as a *new* pre-registered run, and record it as its own
  result. Don't overwrite §8.1.
- If no defensible physical range exists, say so. "These channels are genuinely quiet" is an
  acceptable answer.

## Task 3: Stage 3, one PRECISION lane on the Cardputer

`@LAT108` on the Cardputer, folded in the Dream Cycle's Replay phase (RFC §4.3; never in
Projection). §3.4 stays off: `π` is observed, not used.

- Record format and fold: RFC §4.2–4.3. The key is `node:0x%08lx|chan:%s`. Rewrite only
  when `π` moves by more than `prec_write_delta` (8). `conf` follows `n`.
- Integer arithmetic must match `tools/pw1/pw1_fold.py` exactly. Port its 5-residual
  hand-worked test (`var` 4090, `π` 170) to C++ and assert the same numbers.
- `>>` on a negative `int32` must be an arithmetic shift, which is GCC's behaviour on the
  ESP32. Add a test that would catch a logical shift.
- Respect the lane discipline in TTDB-RFC-0010 and this repo's `CLAUDE.md`: quotas, the record
  index headroom, and no new static buffers without checking the boot-loop history in
  `docs/log/2026-10.md`.
- Gate: pull the Cardputer's TTDB after a Dream Cycle. Its `@LAT108` `π` must agree with
  `pw1_fold.py` run over the same pulled residuals.

## Task 4: Stage 4, gain on one node (PW-2 on hardware)

Only after stage 3 passes. Enable §3.4 on the Cardputer for one channel. Pre-register a
hardware PW-2 (cohort, injection method, thresholds) before flashing. A noisy twin on hardware
could be a deliberately mis-gained second reader of the same sensor. Compare against the
`+2`/`−16` fixed steps in `PerceptLearn.h:386-390`.

## Task 5: EXP-01 on the V4 triad (unblocks PW-5)

TTDB-RFC-0009 §5.3: an identical-sensor triad (three Heltec V4s, same firmware, same
modalities) against the heterogeneous triad of §5.4, sweeping the ESP-NOW sync interval.
Measure residual EPS topology, not accuracy. It is a precondition for PW-5 and for
TTDB-RFC-0009 §6.

Two open points for PW-5 were left undecided, so raise them with Dan when you get there:
- **Arms:** run only the identical-umwelt arm, or wait for EXP-01 to supply gate-passing pairs.
- **§3.6 saturation:** §3.6 sums `π` on the 0–255 scale, which saturates at 255, meaning a
  predicted variance of 0. A literal test can never falsify it. Decide whether to test the
  inverse-variance claim instead and report the saturation as a finding.

## Out of scope

- Stage 5 (broadcast gate). It is blocked until a refresh mechanism is specified and replayed
  (RFC §11 Q7).
- Stages 6–7.
- Any change to the stage-2 tools or their reports, beyond running them.

## Prompt to paste into Claude Code (started in `c:\git\robot_team`)

```
Read BRIEF-RFC-0011-STAGES.md and follow it in order, one task at a time.

Start with Task 1 (stage 1 readers). Before changing anything, report every
reader and writer of [ew] / conf / touched in firmware and orchestrator/fleet.py
and the shapes you find, and propose the smallest change. Work on a branch,
commit locally, don't push, don't flash.

Stop and ask me before each flash, before reading master/ for a new experiment
(pre-register first), and whenever the brief and CLAUDE.md disagree.
```
