PW-1b: INCONCLUSIVE — separation 119 (pass > 32), stability 68.8% (pass >= 70%), robustness PASS

Verdict from the runs-expanded computation (fixed in advance). Runs-unexpanded: **INCONCLUSIVE** — separation 133 (pass > 32), stability 53.3% (pass >= 70%), robustness PASS.

## Open question 6 (pre-registered: saturated iff median π ≥ 247)

| channel | PW-1 span | PW-1b span | PW-1 median π | PW-1b median π | saturated | reading |
|---|---|---|---|---|---|---|
| acoustic | 32767 | 900 | 255 | 241 | no | PW-1's span was too wide for this channel |
| motion | 16000 | 60 | 255 | 251 | yes | quiet at its declared scale |
| link | 100 | 90 | 250 | 249 | yes | quiet at its declared scale |

Distinguishability (descriptive, medians differ by > 24): acoustic/motion not distinct (Δ 10); acoustic/link not distinct (Δ 8); motion/link not distinct (Δ 2)

## Constants

| constant | value | rule / source |
|---|---|---|
| pe_span acoustic | 900 | R1 `ACOUSTICPERCEPT_TRANSIENT_FLOOR` |
| pe_span motion | 60 mg | R1 `MOTIONPERCEPT_MOVING_MG` |
| pe_span link | 90 dB | R2 LinkPercept clamp [−100, −10]; R1 `PERCEPTLEARN_RSSI_BAND` excluded (archive-derived) |
| everything else | PW-1 | `tools/pw1/pw1_constants.py`, unchanged |

## Scope

- Files: 187; distinct records: @LAT94 734, @LAT95 617, @LAT96 1387, @LAT97 1679; duplicates dropped: 6611.
- Same scope, dedup and series rules as PW-1 (lanes 94–97; `@LAT103` is outside it).

## Checks — runs expanded (verdict)

| check | value | result |
|---|---|---|
| Separation (range of per-channel median π, PI_SCALE=8192) | 119 | PASS |
| Stability (split-half within 24; 11 of 16 series) | 68.8% | MID |
| Robustness (rank order at 4096/8192/16384) | 4096: entity<acoustic<link<motion | 8192: entity<acoustic<link<motion | 16384: entity<acoustic<link<motion | PASS |

Per-channel median π: @4096 acoustic 230, entity 89, link 245, motion 248; @8192 acoustic 241, entity 132, link 249, motion 251; @16384 acoustic 247, entity 174, link 252, motion 253

## Checks — runs not expanded

| check | value | result |
|---|---|---|
| Separation (range of per-channel median π, PI_SCALE=8192) | 133 | PASS |
| Stability (split-half within 24; 8 of 15 series) | 53.3% | MID |
| Robustness (rank order at 4096/8192/16384) | 4096: entity<acoustic<motion<link | 8192: entity<acoustic<motion<link | 16384: entity<acoustic<motion<link | PASS |

Per-channel median π: @4096 acoustic 230, entity 75, link 245, motion 240; @8192 acoustic 241, entity 116, link 249, motion 247; @16384 acoustic 247, entity 159, link 252, motion 250

## Series — runs expanded

| node | channel | n | π (EWMA) | π (mean) | π₁ | π₂ | drift |
|---|---|---|---|---|---|---|---|
| cardputer | acoustic | 605 | 227 | 188 | 211 | 227 | DRIFT |
| cardputer | entity | 428 | 116 | 164 | 185 | 116 | DRIFT |
| cardputer | link | 2705 | 254 | 252 | 255 | 254 |  |
| cardputer | motion | 1952 | 249 | 247 | 254 | 249 |  |
| k10 | acoustic | 90 | 255 | 254 | 255 | 255 |  |
| k10 | entity | 126 | 148 | 152 | 185 | 149 |  |
| k10 | motion | 963 | 254 | 254 | 255 | 254 |  |
| tdeck | entity | 199 | 137 | 150 | 170 | 137 |  |
| tdeck | link | 1390 | 255 | 253 | 250 | 255 |  |
| v4a | entity | 297 | 115 | 175 | 150 | 115 | DRIFT |
| v4a | link | 1066 | 225 | 251 | 253 | 225 | DRIFT |
| v4b | entity | 95 | 130 | 129 | 111 | 135 |  |
| v4b | link | 1133 | 245 | 253 | 254 | 245 |  |
| v4c | entity | 120 | 134 | 129 | 126 | 136 |  |
| v4c | link | 1155 | 255 | 253 | 254 | 255 |  |
| walk | link | 99 | 227 | 240 | 247 | 227 |  |

## Series — runs not expanded

| node | channel | n | π (EWMA) | π (mean) | π₁ | π₂ | drift |
|---|---|---|---|---|---|---|---|
| cardputer | acoustic | 605 | 227 | 188 | 211 | 227 | DRIFT |
| cardputer | entity | 405 | 116 | 161 | 174 | 116 | DRIFT |
| cardputer | link | 2705 | 254 | 252 | 255 | 254 |  |
| cardputer | motion | 459 | 248 | 226 | 185 | 248 |  |
| k10 | acoustic | 90 | 255 | 254 | 255 | 255 |  |
| k10 | entity | 70 | 102 | 115 | 144 | 105 |  |
| k10 | motion | 35 | 246 | 246 | - | - |  |
| tdeck | entity | 184 | 132 | 145 | 160 | 132 |  |
| tdeck | link | 1390 | 255 | 253 | 250 | 255 |  |
| v4a | entity | 247 | 115 | 164 | 142 | 115 | DRIFT |
| v4a | link | 1066 | 225 | 251 | 253 | 225 | DRIFT |
| v4b | entity | 95 | 130 | 129 | 111 | 135 |  |
| v4b | link | 1133 | 245 | 253 | 254 | 245 |  |
| v4c | entity | 114 | 116 | 126 | 147 | 117 |  |
| v4c | link | 1155 | 255 | 253 | 254 | 255 |  |
| walk | link | 99 | 227 | 240 | 247 | 227 |  |

## Exclusions and notes

- Series below 30 residuals (excluded): none
- Series dropped from stability (a half < 30): none
- Unparseable / non-window records (not guessed at): 9
  - `belief-log.md` @LAT97: 9 × no t_ms
- Stream-less t_ms resets treated as segment breaks: cardputer @LAT94 ×12, cardputer @LAT95 ×11, cardputer @LAT96 ×20, cardputer @LAT97 ×9, k10 @LAT96 ×18, tdeck @LAT96 ×15, tdeck @LAT97 ×4, v4a @LAT96 ×7, v4a @LAT97 ×3, v4b @LAT96 ×28, v4b @LAT97 ×1, v4c @LAT96 ×22, v4c @LAT97 ×1, walk @LAT97 ×4
- Link peers absent from the previous window (no residual): 141
- Files with no lane 94–97 records: 58 (listed in PW1-REPORT.md; same archive)

## Reading the result (written after the run; nothing above was changed)

- **The verdict turns on one series.** PW-1b's stability is 11 of 16 = 68.8 % against
  PW-1's 12 of 16 = 75.0 %. The only series that changed side is `v4a/link`: its split
  halves are π₁ 253 / π₂ 225 (Δ 28), against PW-1's 253 / 230 (Δ 23), with the tolerance at
  24. Narrowing the link span 100 → 90 moved one boundary case across the line. Entity,
  which carries the separation, is unchanged from PW-1.
- **Open question 6, per the registered rule:** acoustic is **not** saturated (241); motion
  (251) and link (249) **are**. Both written predictions held: motion and link stayed
  saturated, and acoustic had no prediction.
- **The acoustic answer rests on the Cardputer alone.** `cardputer/acoustic` folds to 227
  (mean-π 188, flagged DRIFT), while `k10/acoustic` stays at 255 on only 90 residuals.
  The channel median, 241, is the average of the two. The K10's ear is quiet even at
  span 900.
- **No pair of acoustic, motion and link is distinguishable** (largest gap Δ 10). So
  "every channel earns its own gain" is still not shown; entity is still the only channel
  that separates.
- **Stage 3 takes these spans as registered** (acoustic 900, motion 60 mg, link 90 dB).
  That was fixed in advance, whatever the verdict.
