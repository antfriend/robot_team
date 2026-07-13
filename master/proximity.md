# Fleet Proximity Beliefs (semantic positioning SP1)

Authored by `companion.py proximity`: each node's @LAT97 link-percept windows
(SP0 evidence) fused into one @BELIEF:PROXIMITY record per node pair
(ttn-semantic-positioning.md §2.1). Estimator: median of per-window rssi_max
per direction (the strongest receptions sit nearest line-of-sight truth;
fading only subtracts), directions averaged; sigma from window spread +
direction asymmetry, widened while the path-loss model is uncalibrated.

---

@BELIEF:PROXIMITY @pair(v4a_bridge, v4b_relay)
proto: ble
rssi_est_dbm: -89.5
rssi_ab_dbm: -89.5   # v4a_bridge hears v4b_relay (n:548)
rssi_ba_dbm: None   # v4b_relay hears v4a_bridge (n:0)
asym_db: 0.0
dist_est_m: 33.5
dist_sigma_m: 560.35
n_obs: 548
windows: 12
sources: { rssi: 0.81, entity_jaccard: 0.19 }
entity_jaccard: 0.57   # shared 13 AP(s), bound <= 60.43 m
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.7
touched: 2026-07-13T22:31:47Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, v4b_relay)
proto: espnow
rssi_est_dbm: -83.5
rssi_ab_dbm: -83.5   # v4a_bridge hears v4b_relay (n:200)
rssi_ba_dbm: None   # v4b_relay hears v4a_bridge (n:0)
asym_db: 0.0
dist_est_m: 39.36
dist_sigma_m: 73.24
n_obs: 200
windows: 12
sources: { rssi: 0.65, entity_jaccard: 0.15, ble: 0.2 }
entity_jaccard: 0.57   # shared 13 AP(s), bound <= 60.43 m
ble_bound_m: 593.85   # near-range BLE estimate
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-13T22:31:47Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, k10_1)
proto: espnow
rssi_est_dbm: -71.0
rssi_ab_dbm: -71.0   # v4a_bridge hears k10_1 (n:549)
rssi_ba_dbm: None   # k10_1 hears v4a_bridge (n:0)
asym_db: 0.0
dist_est_m: 21.72
dist_sigma_m: 4.68
n_obs: 549
windows: 12
sources: { rssi: 0.77, entity_jaccard: 0.23 }
entity_jaccard: 0.73   # shared 11 AP(s), bound <= 48.67 m
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-13T22:31:47Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, tdeck_1)
proto: ble
rssi_est_dbm: -68.0
rssi_ab_dbm: -78.0   # v4a_bridge hears tdeck_1 (n:538)
rssi_ba_dbm: -58   # tdeck_1 hears v4a_bridge (n:412)
asym_db: 20.0
dist_est_m: 2.82
dist_sigma_m: 27.9
n_obs: 950
windows: 19
sources: { rssi: 0.79, entity_jaccard: 0.21 }
entity_jaccard: 0.65   # shared 13 AP(s), bound <= 54.5 m
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.6
touched: 2026-07-13T22:31:47Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, tdeck_1)
proto: espnow
rssi_est_dbm: -59.0
rssi_ab_dbm: -73.0   # v4a_bridge hears tdeck_1 (n:255)
rssi_ba_dbm: -45   # tdeck_1 hears v4a_bridge (n:153)
asym_db: 28.0
dist_est_m: 12.27
dist_sigma_m: 15.32
n_obs: 408
windows: 19
sources: { rssi: 0.64, entity_jaccard: 0.17, ble: 0.19 }
entity_jaccard: 0.65   # shared 13 AP(s), bound <= 54.5 m
ble_bound_m: 30.72   # near-range BLE estimate
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.6
touched: 2026-07-13T22:31:47Z

---

@BELIEF:PROXIMITY @pair(v4b_relay, tdeck_1)
proto: ble
rssi_est_dbm: -65.0
rssi_ab_dbm: -80   # v4b_relay hears tdeck_1 (n:358)
rssi_ba_dbm: -50.0   # tdeck_1 hears v4b_relay (n:730)
asym_db: 30.0
dist_est_m: 2.0
dist_sigma_m: 16.55
n_obs: 1088
windows: 21
sources: { rssi: 0.82, entity_jaccard: 0.18 }
entity_jaccard: 0.56   # shared 14 AP(s), bound <= 60.8 m
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.6
touched: 2026-07-13T22:31:47Z

---

@BELIEF:PROXIMITY @pair(v4b_relay, tdeck_1)
proto: espnow
rssi_est_dbm: -55.5
rssi_ab_dbm: -71   # v4b_relay hears tdeck_1 (n:157)
rssi_ba_dbm: -40.0   # tdeck_1 hears v4b_relay (n:243)
asym_db: 31.0
dist_est_m: 10.39
dist_sigma_m: 13.37
n_obs: 400
windows: 23
sources: { rssi: 0.66, entity_jaccard: 0.15, ble: 0.2 }
entity_jaccard: 0.56   # shared 14 AP(s), bound <= 60.8 m
ble_bound_m: 18.55   # near-range BLE estimate
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.6
touched: 2026-07-13T22:31:47Z

---

@BELIEF:PROXIMITY @pair(k10_1, tdeck_1)
proto: espnow
rssi_est_dbm: -41.0
rssi_ab_dbm: None   # k10_1 hears tdeck_1 (n:0)
rssi_ba_dbm: -41   # tdeck_1 hears k10_1 (n:477)
asym_db: 0.0
dist_est_m: 5.21
dist_sigma_m: 0.75
n_obs: 477
windows: 11
sources: { rssi: 0.8, entity_jaccard: 0.2 }
entity_jaccard: 0.61   # shared 11 AP(s), bound <= 57.22 m
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-13T22:31:47Z
