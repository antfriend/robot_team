# Fleet Path-Loss Calibration (semantic positioning SP1)

Authored by `companion.py calibrate` from a measured calibration walk
(ttn-semantic-positioning.md Appendix B): per-station fused RSSI vs ground-truth
distance, least-squares fit of the log-distance model
RSSI(d) = rssi_d0 - 10*n*log10(d/d0). `proximity` reads this file and uses the
fitted model (and drops its uncalibrated-sigma penalty). The model is only
trustworthy inside valid_range_m — the rssi_d0 intercept is an extrapolation,
not a near-field measurement.

---

@BELIEF:CALIBRATION proto:espnow
rssi_d0_dbm: -6.3
d0_m: 1.0
n: 4.84
rmse_db: 1.4
valid_range_m: 3.75-37.5
stations: 3.75:-33.0, 9.0:-54.8, 19.5:-67.5, 37.5:-82.5
note: 2026-07-07 walking range test: V4-A fixed in workroom, V4-B walked. Stations (strides x0.75m): workroom far side 5, hall end 12, deck 26 (NLOS), front yard 50. RSSI = median of per-window rssi_max, both directions fused, from master/walk_v4a.md lanes 13-25 + master/walk_v4b.md lanes 31-47. Through-wall/home propagation, NOT open air.
conf: 0.75
touched: 2026-07-07T21:57:59Z
