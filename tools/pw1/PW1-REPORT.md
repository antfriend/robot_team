PW-1: PASS — separation 123 (pass > 32), stability 75.0% (pass >= 70%), robustness PASS

Verdict is from the runs-expanded computation (fixed in advance). Runs-unexpanded verdict: **INCONCLUSIVE** — separation 139 (pass > 32), stability 66.7% (pass >= 70%), robustness PASS. **The two disagree.**

## Pre-registered constants (committed in 055364d before any archive read)

| constant | value | source |
|---|---|---|
| pe_span acoustic | 32767 | `AcousticPercept.h:76` — int16 samples |
| pe_span motion | 16000 mg | BMI270 ±8 g datasheet default; firmware sets no range (`cardputer_console.ino` ~3874); confirmed by Dan Ray |
| pe_span link | 100 dB | brief: −120 to −20 dBm |
| pe entity | Jaccard × 255 | already 0–1 |
| PI_SCALE | 8192 (robustness (4096, 8192, 16384)) | brief |
| thresholds | sep >32 / ≤16; stab ≥70% / <50%, tol 24; min n 30 | brief |

## Scope

- Files under `master/` (`**/*.md`): **187** (the RFC assumed 78; the archive has grown). Deduplicated on (node, lane, stream, t_ms, body digest).
- Distinct records kept: @LAT94 734, @LAT95 617, @LAT96 1387, @LAT97 1679
- Duplicate records dropped: 6611, across 86 files.
- Lanes 94–97 only; `@LAT101` is never parsed.
- Node = filename prefix before the first `_` (records carry no node id).
- Primary scalars used: acoustic `rms_mean`; motion `dev_mean_mg`; link `rssi_med` per (peer, proto), pooled per node; entity = set of `ENTITY id`.

## Checks — runs expanded (verdict)

| check | value | result |
|---|---|---|
| Separation (range of per-channel median π, PI_SCALE=8192) | 123 | PASS |
| Stability (split-half within 24; 12 of 16 series) | 75.0% | PASS |
| Robustness (rank order at 4096/8192/16384) | 4096: entity<link<acoustic<motion | 8192: entity<link<acoustic<motion | 16384: entity<link<acoustic<motion | PASS |

Per-channel median π: @4096 acoustic 255, entity 89, link 247, motion 255; @8192 acoustic 255, entity 132, link 250, motion 255; @16384 acoustic 255, entity 174, link 252, motion 255
Tied medians at PI_SCALE [4096, 8192, 16384] (ties broken by channel name).

## Checks — runs not expanded

| check | value | result |
|---|---|---|
| Separation (range of per-channel median π, PI_SCALE=8192) | 139 | PASS |
| Stability (split-half within 24; 10 of 15 series) | 66.7% | MID |
| Robustness (rank order at 4096/8192/16384) | 4096: entity<link<acoustic<motion | 8192: entity<link<acoustic<motion | 16384: entity<link<acoustic<motion | PASS |

Per-channel median π: @4096 acoustic 255, entity 75, link 247, motion 255; @8192 acoustic 255, entity 116, link 250, motion 255; @16384 acoustic 255, entity 159, link 252, motion 255
Tied medians at PI_SCALE [4096, 8192, 16384] (ties broken by channel name).

## Series — runs expanded

| node | channel | n | π (EWMA) | π (mean) | π₁ | π₂ | drift |
|---|---|---|---|---|---|---|---|
| cardputer | acoustic | 605 | 255 | 254 | 255 | 255 |  |
| cardputer | entity | 428 | 116 | 164 | 185 | 116 | DRIFT |
| cardputer | link | 2705 | 254 | 252 | 255 | 254 |  |
| cardputer | motion | 1952 | 255 | 255 | 255 | 255 |  |
| k10 | acoustic | 90 | 255 | 255 | 255 | 255 |  |
| k10 | entity | 126 | 148 | 152 | 185 | 149 |  |
| k10 | motion | 963 | 255 | 255 | 255 | 255 |  |
| tdeck | entity | 199 | 137 | 150 | 170 | 137 |  |
| tdeck | link | 1390 | 255 | 253 | 251 | 255 |  |
| v4a | entity | 297 | 115 | 175 | 150 | 115 | DRIFT |
| v4a | link | 1066 | 230 | 251 | 253 | 230 |  |
| v4b | entity | 95 | 130 | 129 | 111 | 135 |  |
| v4b | link | 1133 | 247 | 253 | 254 | 247 |  |
| v4c | entity | 120 | 134 | 129 | 126 | 136 |  |
| v4c | link | 1155 | 255 | 254 | 254 | 255 |  |
| walk | link | 99 | 232 | 243 | 249 | 232 |  |

## Series — runs not expanded

| node | channel | n | π (EWMA) | π (mean) | π₁ | π₂ | drift |
|---|---|---|---|---|---|---|---|
| cardputer | acoustic | 605 | 255 | 254 | 255 | 255 |  |
| cardputer | entity | 405 | 116 | 161 | 174 | 116 | DRIFT |
| cardputer | link | 2705 | 254 | 252 | 255 | 254 |  |
| cardputer | motion | 459 | 255 | 255 | 255 | 255 |  |
| k10 | acoustic | 90 | 255 | 255 | 255 | 255 |  |
| k10 | entity | 70 | 102 | 115 | 144 | 105 |  |
| k10 | motion | 35 | 255 | 255 | - | - |  |
| tdeck | entity | 184 | 132 | 145 | 160 | 132 |  |
| tdeck | link | 1390 | 255 | 253 | 251 | 255 |  |
| v4a | entity | 247 | 115 | 164 | 142 | 115 | DRIFT |
| v4a | link | 1066 | 230 | 251 | 253 | 230 |  |
| v4b | entity | 95 | 130 | 129 | 111 | 135 |  |
| v4b | link | 1133 | 247 | 253 | 254 | 247 |  |
| v4c | entity | 114 | 116 | 126 | 147 | 117 |  |
| v4c | link | 1155 | 255 | 254 | 254 | 255 |  |
| walk | link | 99 | 232 | 243 | 249 | 232 |  |

## Reading the result (descriptive; no threshold was changed)

- Channels whose median π is >= 250 (saturated near the 255 ceiling): acoustic, link, motion. Of the 4 channels, the separation figure is the gap between the lowest median (entity, 132) and the highest (motion, 255).
- Saturated channels are mutually indistinguishable at this resolution, and the robustness check ties on them; the rank order among them rests on name tie-breaking. The pre-registered rule is met as written, but a pass resting on one channel separating from the rest is weaker evidence for per-channel gain than separation spread across all four.
- Series flagged DRIFT (EWMA vs mean π differ by > 24): cardputer/entity, v4a/entity.

## Exclusions and notes

- Series below 30 residuals (excluded): none
- Series dropped from stability (a half < 30): none
- Files with no lane 94–97 records: anchored.md, belief.md, calibration.md, cardputer_2026-10-03.md, cardputer_c4gate_2026-10-03.md, cardputer_c4s2gate_2026-10-03.md, cardputer_c4s2rerun_2026-10-03.md, cardputer_c4s2run3_2026-10-03.md, cardputer_c4s2run4_2026-10-03.md, cardputer_c4s2run5_2026-10-04.md, cardputer_c4s2run6_2026-10-04.md, cardputer_c4s2run7_2026-10-04.md, cardputer_c4s2run8_2026-10-05.md, cardputer_pre_c3_wired_2026-10-02.md, cardputer_pre_lat90_lat93_2026-10-02.md, cardputer_pre_saidline_2026-10-02.md, cardputer_run10_2026-10-05.md, cardputer_run11_2026-10-06.md, consolidated.md, gps-fixes.md, k10.md, k10_c4s2fix_2026-10-04.md, k10_c4s2run5_2026-10-04.md, k10_c4s2run6_2026-10-04.md, k10_run11_2026-10-06.md, k10_via_bridge.md, orchestrator-sync.md, positions.md, proximity-ble.md, proximity.md, prune-2026-08-03\v4a_after.md, prune-2026-08-04\cardputer_pruned.md, tdeck.md, tdeck_bridged.md, tdeck_sp0_check.md, ui\cardputer_prerun_night2.md, ui\tdeck_postflash.md, ui\tdeck_postprune_2026-08-13.md, ui\v4a_postprune_2026-08-13.md, ui\v4b_postprune_2026-08-13_pm.md, v4a.md, v4a_c4gate_2026-10-03.md, v4a_c4s2run7_2026-10-04.md, v4a_c4s2run8_2026-10-05.md, v4a_postclear.md, v4a_pre_repartition_2026-10-04.md, v4a_run10_2026-10-05.md, v4a_run11_2026-10-06.md, v4a_sp0_check.md, v4b_c4s2run7_2026-10-04.md, v4b_c4s2run8_2026-10-04.md, v4b_c4s2run8_2026-10-05.md, v4b_relay_belief_pre_repartition_2026-10-04.md, v4b_relay_pre_repartition_2026-10-04.md, v4b_run10_2026-10-05.md, v4b_run10_mid_2026-10-05.md, v4b_run11_2026-10-06.md, v4b_sp0_check.md
- Unparseable / non-window records (not guessed at): 9
  - `belief-log.md` @LAT97: 9 × no t_ms
- Stream-less t_ms resets treated as segment breaks: cardputer @LAT94 ×12, cardputer @LAT95 ×11, cardputer @LAT96 ×20, cardputer @LAT97 ×9, k10 @LAT96 ×18, tdeck @LAT96 ×15, tdeck @LAT97 ×4, v4a @LAT96 ×7, v4a @LAT97 ×3, v4b @LAT96 ×28, v4b @LAT97 ×1, v4c @LAT96 ×22, v4c @LAT97 ×1, walk @LAT97 ×4
- Link peers absent from the previous window (no residual): 141
- Duplicates dropped per file:
  - `cardputer_pre_acoustic_episode_2026-10-01.md`: 2
  - `cardputer_pre_entity_episode_2026-10-01.md`: 135
  - `cardputer_pre_episode_2026-10-01.md`: 105
  - `cardputer_pre_link_episode_2026-10-02.md`: 48
  - `cardputer_pre_motion_episode_2026-10-02.md`: 96
  - `entity-baseline\cardputer_check2.md`: 166
  - `entity-baseline\cardputer_night2_cancelled.md`: 96
  - `entity-baseline\cardputer_postprune_2026-08-13_pm.md`: 30
  - `entity-baseline\cardputer_pre_fswipe_2026-08-11.md`: 173
  - `entity-baseline\cardputer_pre_prune_2026-08-13.md`: 172
  - `entity-baseline\cardputer_preflash_2026-08-13_pm.md`: 58
  - `entity-baseline\v4a_pre_prune_2026-08-13.md`: 67
  - `gate-2026-08-02\cardputer_preflash.md`: 2
  - `k10_1.md`: 13
  - `k10_1_null_2026-08-12.md`: 34
  - `k10_1_postflash_2026-08-12.md`: 51
  - `k10_1_postprune_2026-08-12.md`: 49
  - `k10_1_postprune_2026-08-13.md`: 4
  - `k10_1_preflash_2026-08-12.md`: 48
  - `k10_1_preflash_2026-08-13.md`: 95
  - `k10_1_preprune_2026-08-12.md`: 98
  - `k10_pre_episode_2026-10-02.md`: 58
  - `preflash-2026-08-02\cardputer_movingrun.md`: 34
  - `preflash-2026-08-02\cardputer_staged.md`: 93
  - `prune-2026-08-03\cardputer_after.md`: 49
  - `prune-2026-08-03\cardputer_before.md`: 124
  - `prune-2026-08-03\cardputer_motion_gen1.md`: 96
  - `prune-2026-08-03\cardputer_motion_gen2.md`: 12
  - `prune-2026-08-03\cardputer_timeline_pruned.md`: 163
  - `prune-2026-08-03\v4c_before.md`: 6
  - `prune-2026-08-04\cardputer_battery.md`: 92
  - `prune-2026-08-04\cardputer_hour.md`: 13
  - `prune-2026-08-04\cardputer_post.md`: 173
  - `prune-2026-08-04\cardputer_pre.md`: 192
  - `prune-2026-08-04\cardputer_prebattery.md`: 109
  - `tdeck_1.md`: 1
  - `tdeck_c4s2rerun_2026-10-03.md`: 2
  - `tdeck_c4s2run3_2026-10-03.md`: 2
  - `tdeck_c4s2run4_2026-10-03.md`: 2
  - `tdeck_c4s2run5_2026-10-04.md`: 2
  - `tdeck_c4s2run6_2026-10-04.md`: 2
  - `tdeck_c4s2run7_2026-10-04.md`: 2
  - `tdeck_c4s2run8_2026-10-05.md`: 2
  - `tdeck_run10_2026-10-05.md`: 2
  - `tdeck_run11_2026-10-06.md`: 2
  - `timestream-2026-08-03\cardputer_dedup.md`: 192
  - `timestream-2026-08-03\cardputer_final.md`: 190
  - `timestream-2026-08-03\cardputer_postflash.md`: 180
  - `timestream-2026-08-03\cardputer_preflash.md`: 178
  - `timestream-2026-08-03\cardputer_synced.md`: 187
  - `timestream-2026-08-03\tdeck_dedup_1.md`: 96
  - `timestream-2026-08-03\tdeck_dedup_2.md`: 96
  - `timestream-2026-08-03\tdeck_final.md`: 96
  - `timestream-2026-08-03\v4a_after.md`: 68
  - `timestream-2026-08-03\v4c_after.md`: 30
  - `ui\cardputer_1.md`: 165
  - `ui\cardputer_2026-08-13.md`: 173
  - `ui\cardputer_check1.md`: 174
  - `ui\cardputer_check2.md`: 178
  - `ui\cardputer_check3.md`: 179
  - `ui\cardputer_check4.md`: 182
  - `ui\cardputer_final2_2026-08-13.md`: 41
  - `ui\cardputer_final_2026-08-13.md`: 137
  - `ui\cardputer_night3_ready.md`: 96
  - `ui\cardputer_prerun_night3.md`: 162
  - `ui\cardputer_prewalk.md`: 176
  - `ui\k10_check90.md`: 99
  - `ui\k10_recheck_a.md`: 50
  - `ui\tdeck_1.md`: 48
  - `ui\tdeck_part2_check.md`: 50
  - `ui\tdeck_postprune_2026-08-13_pm.md`: 18
  - `ui\tdeck_preflash_2026-08-13_pm.md`: 14
  - `ui\v4a_2026-08-13.md`: 96
  - `ui\v4a_bridge.md`: 48
  - `ui\v4a_fold_check.md`: 49
  - `ui\v4a_pm_2026-08-13.md`: 63
  - `ui\v4a_postflash_2026-08-13.md`: 66
  - `ui\v4a_postprune.md`: 69
  - `ui\v4b_relay.md`: 96
  - `v4a_bridge.md`: 8
  - `v4a_pre_episode_2026-10-02.md`: 81
  - `v4c_c4s2run8_2026-10-04.md`: 1
  - `v4c_c4s2run8_2026-10-05.md`: 1
  - `v4c_edge_pre_repartition_2026-10-04.md`: 1
  - `v4c_run10_2026-10-05.md`: 1
  - `v4c_run11_2026-10-06.md`: 1

## Limitations (not corrected, only recorded)

- "Chronological" split-half = segment encounter order (file-name sorted, then t_ms); t_ms restarts at each boot and records carry no wall time, so this is only as chronological as the file names.
- Missing windows (gaps in t_ms) are not detected for @LAT94/@LAT97: the previous record is taken as the previous window.
- `rms_mean` is RMS, so the int16 full-scale span makes acoustic residuals small by construction; this affects π for that channel and is part of what PW-1 measures.
