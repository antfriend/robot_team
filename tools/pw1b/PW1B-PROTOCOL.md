# PW-1b — pre-registered protocol (TTDB-RFC-0011 open question 6)

2026-11-22. Committed with `pw1b_constants.py` **before any PW-1b code exists or reads
`master/`**. Nothing here may change after the run.

## 1. Question

PW-1 (§8.1) folded acoustic, motion and link to median `π` 255, 255 and 250, so the
precision filter cannot give those three different gains. RFC §11 Q6 asks whether they
are **quiet**, or whether PW-1's `pe_span` (acoustic 32 767, motion 16 000 mg, link
100 dB) was so wide that `pe = |Δ| × 255 / span` rounds every real change down to almost
nothing. Stage 3 writes `π` on a device, so its span constants must be settled first.

PW-1b re-runs PW-1 with spans set by the rule below and **nothing else changed**. It is
its own result (RFC §8.4). §8.1 is not edited.

## 2. The rule (decided before looking at residuals)

For each scalar channel, `pe_span` is:

- **R1** — the smallest firmware constant at which the firmware treats the logged
  quantity as having **changed state or registered an event**, provided that constant's
  value was **not derived from records in `master/`**;
- **R2** — otherwise, the full domain the firmware clamps the logged quantity to.

R1 measures error against the scale the channel's own firmware already acts on. A
full-scale span (PW-1's choice) makes saturation **true by construction** for any
quantity whose window-to-window change is a small fraction of full scale. So a rerun with
a different full-scale figure could not answer Q6, and full scale is kept only as the
fallback.

| channel | logged quantity | rule | `pe_span` | source |
|---|---|---|---|---|
| acoustic | `rms_mean` (int16 RMS) | R1 | **900** | `ACOUSTICPERCEPT_TRANSIENT_FLOOR`, AcousticPercept.h:45 (`bddb399`, 2026-07-27): the smallest block RMS ever counted as a transient |
| motion | `dev_mean_mg` | R1 | **60 mg** | `MOTIONPERCEPT_MOVING_MG`, MotionPercept.h:209: \|a\| − 1 g above which a sample is moving. Value from published figures (hand tremor 20–40 mg, stride in the hundreds); a later 48-window check against the Cardputer kept it. Same constant on the K10 (samples scaled so rest = 1000 mg) |
| link | `rssi_med` per peer | **R2** | **90 dB** | `LinkPercept.h:35-37`, RSSI clamped to [−100, −10] dBm |
| entity | BSSID set | — | unchanged | Jaccard distance × 255 |

⚠ **Link fails R1, and that is recorded rather than worked around.** The R1 candidate is
`PERCEPTLEARN_RSSI_BAND 6` (the met/violated band), but PerceptLearn.h:46-64 derives it
as the **p90 of consecutive-window |Δ `rssi_med`|** on
`master/preflash-2026-08-02/cardputer_ttdb.md`. That is PW-1's own link residual, measured
on a file in this archive. Using it would put the data's own spread into the denominator.

Caveats, recorded:
- The acoustic floor is a **level**, not a change. The firmware's change rule (3× the
  running ambient) is relative and data-dependent at runtime, so it is not a constant.
  The floor is the nearest constant on the same int16 RMS scale.
- The motion threshold applies to **samples**, and `dev_mean_mg` is a window mean, so
  the same threshold reads more strictly on a mean.

## 3. Everything else is PW-1's, unchanged

The archive scope (all `master/**/*.md`, lanes 94–97), dedup key, series and segment
rules, run expansion, `MIN_RESIDUALS` 30, `PI_ALPHA` 4, `PI_SCALE` 8192 with robustness
at 4096/16384, the separation and stability thresholds, and the decision that the
**runs-expanded** computation gives the verdict. The code imports
`tools/pw1/pw1_fold.py` **unmodified** and replaces only its three module-level span
constants in memory.

`PI_SCALE` is **not** re-derived. Changing it alongside the spans would turn two knobs
at once, and only the spans were authorised for this run.

## 4. Outputs and decision rules

1. **PW-1b verdict** by PW-1's rule: PASS, FALSIFIED or INCONCLUSIVE.
2. **Q6, per channel** (acoustic, motion, link): **saturated** iff its median `π`
   (expanded, `PI_SCALE` 8192) is ≥ **247** = 255 − `prec_write_delta`. At or above
   that, stage 3 could not tell the channel from the ceiling by its own rewrite rule.
   - saturated → *quiet at its declared scale*: PW-1's saturation was not caused by span
     width alone;
   - not saturated → *PW-1's span was too wide for this channel*.
3. **Distinguishability** (descriptive): which pairs of those three channels have
   medians differing by more than 24.
4. Every exclusion, as PW-1 logs them.

**Consequence fixed in advance:** stage 3 uses PW-1b's spans **whatever the outcome**,
because choosing spans by their result would be the tuning the brief forbids. PW-1
(§8.1) remains the stage-2 gate; PW-1b decides constants and answers Q6. It does not
reopen the gate.

## 5. What was already known before the run (disclosed, not hidden)

The run is not blind, and what I knew is listed here:
- PW-1's results: medians acoustic 255, motion 255, link 250, entity 132.
- MotionPercept.h:167-168 (firmware comment, 2026-08-03): over 48 still Cardputer
  windows, `dev_mean_mg` min 8, p50 8, p90 8, max 9.
- In this session's repo review I saw one `@LAT103` motion episode
  (`cardputer_run11_2026-10-06.md`) with `dev_mean_mg:12`. `@LAT103` is outside PW-1's
  scope.
- PerceptLearn.h:52-61: on the Cardputer, consecutive-window |Δ `rssi_med`| has a median of
  0–2 dB and a p90 of ≤ 6 dB per peer.
- No `rms_mean` value has been seen.

**Predictions written down now:**
- **motion stays saturated:** a still window's mean moves by about 0–1 mg, which is
  `pe` 0–4 at span 60;
- **link stays saturated:** 90 dB is barely narrower than 100;
- **acoustic: no prediction.**

So the run can only really answer Q6 for acoustic. For motion and link it is close to a
confirmation, and should be reported that way.

## 6. Limitations

- R1 spans are **decision scales**, not datasheet ranges, which departs from the brief's
  "physical range". §2 gives the reason.
- PW-1's scope excludes `@LAT103`, so the Cardputer contributes nothing after
  2026-10-02. That is PW-1's scope, kept unchanged for comparability, and it is the reason
  stage 3's gate needs its own episode reader.
- Run expansion inserts zero residuals for covered windows, which pushes `π` up. That is
  PW-1's convention, kept.
