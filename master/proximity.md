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
rssi_est_dbm: -35.5
rssi_ab_dbm: -38   # v4a_bridge hears v4b_relay (n:70)
rssi_ba_dbm: -33.0   # v4b_relay hears v4a_bridge (n:54)
asym_db: 5.0
dist_est_m: 4.01
dist_sigma_m: 0.67
n_obs: 124
windows: 5
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.52
touched: 2026-07-07T22:32:07Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, k10_1)
proto: espnow
rssi_est_dbm: -30.0
rssi_ab_dbm: -30   # v4a_bridge hears k10_1 (n:305)
rssi_ba_dbm: None   # k10_1 hears v4a_bridge (n:0)
asym_db: 0.0
dist_est_m: 3.09
dist_sigma_m: 0.44
n_obs: 305
windows: 5
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-07T22:32:07Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, tdeck_1)
proto: espnow
rssi_est_dbm: -28.5
rssi_ab_dbm: -26   # v4a_bridge hears tdeck_1 (n:146)
rssi_ba_dbm: -31   # tdeck_1 hears v4a_bridge (n:84)
asym_db: 5
dist_est_m: 2.88
dist_sigma_m: 0.41
n_obs: 230
windows: 8
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.63
touched: 2026-07-07T22:32:07Z

---

@BELIEF:PROXIMITY @pair(v4b_relay, k10_1)
proto: espnow
rssi_est_dbm: -22.5
rssi_ab_dbm: -22.5   # v4b_relay hears k10_1 (n:119)
rssi_ba_dbm: None   # k10_1 hears v4b_relay (n:0)
asym_db: 0.0
dist_est_m: 2.16
dist_sigma_m: 0.31
n_obs: 119
windows: 2
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.68
touched: 2026-07-07T22:32:07Z

---

@BELIEF:PROXIMITY @pair(v4b_relay, tdeck_1)
proto: espnow
rssi_est_dbm: -29.2
rssi_ab_dbm: -26.5   # v4b_relay hears tdeck_1 (n:59)
rssi_ba_dbm: -32   # tdeck_1 hears v4b_relay (n:69)
asym_db: 5.5
dist_est_m: 2.98
dist_sigma_m: 0.43
n_obs: 128
windows: 5
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.51
touched: 2026-07-07T22:32:07Z

---

@BELIEF:PROXIMITY @pair(k10_1, tdeck_1)
proto: espnow
rssi_est_dbm: -35.0
rssi_ab_dbm: None   # k10_1 hears tdeck_1 (n:0)
rssi_ba_dbm: -35   # tdeck_1 hears k10_1 (n:179)
asym_db: 0.0
dist_est_m: 3.92
dist_sigma_m: 0.56
n_obs: 179
windows: 3
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.77
touched: 2026-07-07T22:32:07Z
