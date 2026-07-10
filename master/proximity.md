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
rssi_est_dbm: -82.2
rssi_ab_dbm: -82.5   # v4a_bridge hears v4b_relay (n:324)
rssi_ba_dbm: -82   # v4b_relay hears v4a_bridge (n:274)
asym_db: 0.5
dist_est_m: 37.09
dist_sigma_m: 58.5
n_obs: 598
windows: 23
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.78
touched: 2026-07-10T17:46:49Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, k10_1)
proto: espnow
rssi_est_dbm: -65.0
rssi_ab_dbm: -65.0   # v4a_bridge hears k10_1 (n:723)
rssi_ba_dbm: None   # k10_1 hears v4a_bridge (n:0)
asym_db: 0.0
dist_est_m: 16.32
dist_sigma_m: 13.16
n_obs: 723
windows: 12
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-10T17:46:49Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, tdeck_1)
proto: espnow
rssi_est_dbm: -84.8
rssi_ab_dbm: -85.5   # v4a_bridge hears tdeck_1 (n:303)
rssi_ba_dbm: -84   # tdeck_1 hears v4a_bridge (n:484)
asym_db: 1.5
dist_est_m: 41.77
dist_sigma_m: 79.85
n_obs: 787
windows: 33
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.75
touched: 2026-07-10T17:46:49Z

---

@BELIEF:PROXIMITY @pair(v4b_relay, k10_1)
proto: espnow
rssi_est_dbm: -80.5
rssi_ab_dbm: -80.5   # v4b_relay hears k10_1 (n:646)
rssi_ba_dbm: None   # k10_1 hears v4b_relay (n:0)
asym_db: 0.0
dist_est_m: 34.12
dist_sigma_m: 61.8
n_obs: 646
windows: 12
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-10T17:46:49Z

---

@BELIEF:PROXIMITY @pair(v4b_relay, tdeck_1)
proto: espnow
rssi_est_dbm: -75.8
rssi_ab_dbm: -75.5   # v4b_relay hears tdeck_1 (n:368)
rssi_ba_dbm: -76   # tdeck_1 hears v4b_relay (n:786)
asym_db: 0.5
dist_est_m: 27.22
dist_sigma_m: 35.03
n_obs: 1154
windows: 33
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.78
touched: 2026-07-10T17:46:49Z

---

@BELIEF:PROXIMITY @pair(k10_1, tdeck_1)
proto: espnow
rssi_est_dbm: -83.0
rssi_ab_dbm: None   # k10_1 hears tdeck_1 (n:0)
rssi_ba_dbm: -83   # tdeck_1 hears k10_1 (n:1052)
asym_db: 0.0
dist_est_m: 38.43
dist_sigma_m: 62.35
n_obs: 1052
windows: 21
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-10T17:46:49Z
