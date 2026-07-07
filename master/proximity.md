# Fleet Proximity Beliefs (semantic positioning SP1)

Authored by `companion.py proximity`: each node's @LAT97 link-percept windows
(SP0 evidence) fused into one @BELIEF:PROXIMITY record per node pair
(ttn-semantic-positioning.md §2.1). Estimator: median of per-window rssi_max
per direction (the strongest receptions sit nearest line-of-sight truth;
fading only subtracts), directions averaged; sigma from window spread +
direction asymmetry, widened while the path-loss model is uncalibrated.

---

@BELIEF:PROXIMITY @pair(v4a_bridge, v4b_relay)
proto: espnow
rssi_est_dbm: -32.5
rssi_ab_dbm: -33   # v4a_bridge hears v4b_relay (n:142)
rssi_ba_dbm: -32   # v4b_relay hears v4a_bridge (n:140)
asym_db: 1
dist_est_m: 0.34
dist_sigma_m: 0.18
n_obs: 282
windows: 10
sources: { rssi: 1.0 }
calibrated: no   # default path-loss {'rssi_d0': -45.0, 'd0_m': 1.0, 'n': 2.7} — run the SP1 calibration walk
conf: 0.7
touched: 2026-07-07T19:54:59Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, tdeck_1)
proto: espnow
rssi_est_dbm: -47.2
rssi_ab_dbm: -49   # v4a_bridge hears tdeck_1 (n:153)
rssi_ba_dbm: -45.5   # tdeck_1 hears v4a_bridge (n:150)
asym_db: 3.5
dist_est_m: 1.21
dist_sigma_m: 1.78
n_obs: 303
windows: 11
sources: { rssi: 1.0 }
calibrated: no   # default path-loss {'rssi_d0': -45.0, 'd0_m': 1.0, 'n': 2.7} — run the SP1 calibration walk
conf: 0.68
touched: 2026-07-07T19:54:59Z

---

@BELIEF:PROXIMITY @pair(v4b_relay, tdeck_1)
proto: espnow
rssi_est_dbm: -29.0
rssi_ab_dbm: -27   # v4b_relay hears tdeck_1 (n:176)
rssi_ba_dbm: -31   # tdeck_1 hears v4b_relay (n:176)
asym_db: 4
dist_est_m: 0.26
dist_sigma_m: 0.15
n_obs: 352
windows: 10
sources: { rssi: 1.0 }
calibrated: no   # default path-loss {'rssi_d0': -45.0, 'd0_m': 1.0, 'n': 2.7} — run the SP1 calibration walk
conf: 0.67
touched: 2026-07-07T19:54:59Z
