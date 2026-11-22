PW-3: KILL — belief disagreement 38.1% (kill > 5%), airtime fall 97.9% (kill < 30%), 63 beliefs

Protocol and constants: `PW3-PROTOCOL.md`, `pw3_constants.py` (committed f3eab94 before this code existed). Verdict uses θ_tx = 96.

## Result (θ_tx = 96)

- Series: 16; beliefs compared: 63; records: 4417, transmitted: 62 (1.4%).
- Bytes on air: ungated 2215839, gated 46076 (includes 53-byte SALIENT per transmitted record) → fall **97.9%**.
- Beliefs where the gated receiver disagrees with the ungated one (no belief, or pe ≥ 48): **24 of 63 = 38.1%**.

| channel | series | records | tx | beliefs | disagree | rate | airtime fall |
|---|---|---|---|---|---|---|---|
| acoustic | 2 | 734 | 2 | 2 | 0 | 0.0% | 99.7% |
| entity | 6 | 1387 | 36 | 6 | 6 | 100.0% | 96.9% |
| link | 6 | 1679 | 22 | 53 | 18 | 34.0% | 98.3% |
| motion | 2 | 617 | 2 | 2 | 0 | 0.0% | 99.7% |

## Reading the result (descriptive; nothing re-tuned)

- The airtime criterion is not the problem: the gate sends 1.4% of records and saves 97.9% of bytes. The disagreement criterion decides the verdict.
- Disagreement is concentrated in entity (6 of 6 beliefs) and link (18 of 53). Acoustic and motion, which are smooth, agree throughout.
- Entity BSSID sets and per-peer RSSI jitter window to window while the gate stays closed (π is low on these channels, §8.1, so ε stays under θ_tx). A receiver that hears from the sender only at its rare surprises holds a body that was right when sent and is stale at the end. No heartbeat or peer request is specified in §6.3, so none was modelled.
- The sweep shows disagreement rising as θ_tx rises (30.2%% → 52.4%%), so no θ_tx in the swept range meets the 5%% criterion with this gate and metric. A heartbeat or periodic refresh would be a different mechanism and a new pre-registered experiment, not a re-run of this one.

## θ_tx sweep (descriptive; no verdict, not used to choose θ_tx)

| θ_tx | tx share | disagreement | airtime fall |
|---|---|---|---|
| 64 | 7.3% | 30.2% | 89.5% |
| 96 | 1.4% | 38.1% | 97.9% |
| 128 | 0.6% | 52.4% | 99.1% |

## Exclusions and notes

- duplicate: 6611
- unparseable: no t_ms: 9
- Airtime is bytes on air, a proxy: LoRa time also depends on spreading factor and preamble, which are equal in both arms.
- The first record of each series is always transmitted; no peer request or heartbeat is modelled (neither is specified in §6.3).
- Run-length-elided windows were never records and appear in neither arm.
- The §6.4 trust cap on received precision is not modelled (one trusted sender per series).
- Disagreement is measured on final bodies at the end of the replay, not over time: a gated receiver that is stale mid-run but converges is counted as agreeing.
