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
rssi_est_dbm: -85.0
rssi_ab_dbm: -85   # v4a_bridge hears v4b_relay (n:691)
rssi_ba_dbm: None   # v4b_relay hears v4a_bridge (n:0)
asym_db: 0.0
dist_est_m: 19.95
dist_sigma_m: 14.06
n_obs: 691
windows: 17
sources: { rssi: 1.0 }
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.7
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, v4b_relay)
proto: espnow
rssi_est_dbm: -73.0
rssi_ab_dbm: -73   # v4a_bridge hears v4b_relay (n:654)
rssi_ba_dbm: None   # v4b_relay hears v4a_bridge (n:0)
asym_db: 0.0
dist_est_m: 23.88
dist_sigma_m: 8.7
n_obs: 654
windows: 17
sources: { rssi: 0.77, ble: 0.23 }
ble_bound_m: 34.01   # near-range BLE estimate
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, v4c_edge)
proto: ble
rssi_est_dbm: -75.0
rssi_ab_dbm: -75   # v4a_bridge hears v4c_edge (n:972)
rssi_ba_dbm: None   # v4c_edge hears v4a_bridge (n:0)
asym_db: 0.0
dist_est_m: 6.31
dist_sigma_m: 15.54
n_obs: 972
windows: 17
sources: { rssi: 0.77, entity_jaccard: 0.23 }
entity_jaccard: 0.75   # shared 12 AP(s), bound <= 47.5 m
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.7
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, v4c_edge)
proto: espnow
rssi_est_dbm: -62.0
rssi_ab_dbm: -62   # v4a_bridge hears v4c_edge (n:372)
rssi_ba_dbm: None   # v4c_edge hears v4a_bridge (n:0)
asym_db: 0.0
dist_est_m: 14.15
dist_sigma_m: 4.09
n_obs: 372
windows: 17
sources: { rssi: 0.62, entity_jaccard: 0.19, ble: 0.19 }
entity_jaccard: 0.75   # shared 12 AP(s), bound <= 47.5 m
ble_bound_m: 21.85   # near-range BLE estimate
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, tdeck_1)
proto: ble
rssi_est_dbm: -49.5
rssi_ab_dbm: -49   # v4a_bridge hears tdeck_1 (n:1062)
rssi_ba_dbm: -50   # tdeck_1 hears v4a_bridge (n:779)
asym_db: 1
dist_est_m: 0.33
dist_sigma_m: 0.45
n_obs: 1841
windows: 30
sources: { rssi: 0.87, entity_jaccard: 0.13 }
entity_jaccard: 0.36   # shared 12 AP(s), bound <= 74.55 m
ble_reflection_suspect: yes   # saturated/asymmetric BLE — NOT used as a tight bound (reflection guard, ttn-semantic-positioning.md §2.2)
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.7
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, tdeck_1)
proto: espnow
rssi_est_dbm: -34.5
rssi_ab_dbm: -36   # v4a_bridge hears tdeck_1 (n:472)
rssi_ba_dbm: -33   # tdeck_1 hears v4a_bridge (n:279)
asym_db: 3
dist_est_m: 3.83
dist_sigma_m: 1.3
n_obs: 751
windows: 30
sources: { rssi: 0.87, entity_jaccard: 0.13 }
entity_jaccard: 0.36   # shared 12 AP(s), bound <= 74.55 m
ble_reflection_suspect: yes   # saturated/asymmetric BLE — NOT used as a tight bound (reflection guard, ttn-semantic-positioning.md §2.2)
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.7
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, cardputer_1)
proto: ble
rssi_est_dbm: -59.0
rssi_ab_dbm: -59   # v4a_bridge hears cardputer_1 (n:1040)
rssi_ba_dbm: None   # cardputer_1 hears v4a_bridge (n:0)
asym_db: 0.0
dist_est_m: 1.0
dist_sigma_m: 0.95
n_obs: 1040
windows: 17
sources: { rssi: 1.0 }
ble_reflection_suspect: yes   # saturated/asymmetric BLE — NOT used as a tight bound (reflection guard, ttn-semantic-positioning.md §2.2)
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.7
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, cardputer_1)
proto: espnow
rssi_est_dbm: -49.0
rssi_ab_dbm: -49   # v4a_bridge hears cardputer_1 (n:737)
rssi_ba_dbm: None   # cardputer_1 hears v4a_bridge (n:0)
asym_db: 0.0
dist_est_m: 7.62
dist_sigma_m: 2.97
n_obs: 737
windows: 17
sources: { rssi: 1.0 }
ble_reflection_suspect: yes   # saturated/asymmetric BLE — NOT used as a tight bound (reflection guard, ttn-semantic-positioning.md §2.2)
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(v4b_relay, tdeck_1)
proto: ble
rssi_est_dbm: -87.0
rssi_ab_dbm: None   # v4b_relay hears tdeck_1 (n:0)
rssi_ba_dbm: -87   # tdeck_1 hears v4b_relay (n:606)
asym_db: 0.0
dist_est_m: 25.12
dist_sigma_m: 17.7
n_obs: 606
windows: 13
sources: { rssi: 1.0 }
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.7
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(v4b_relay, tdeck_1)
proto: espnow
rssi_est_dbm: -76.0
rssi_ab_dbm: None   # v4b_relay hears tdeck_1 (n:0)
rssi_ba_dbm: -76   # tdeck_1 hears v4b_relay (n:376)
asym_db: 0.0
dist_est_m: 27.55
dist_sigma_m: 7.97
n_obs: 376
windows: 13
sources: { rssi: 0.77, ble: 0.23 }
ble_bound_m: 42.82   # near-range BLE estimate
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(v4c_edge, tdeck_1)
proto: ble
rssi_est_dbm: -72.0
rssi_ab_dbm: None   # v4c_edge hears tdeck_1 (n:0)
rssi_ba_dbm: -72   # tdeck_1 hears v4c_edge (n:749)
asym_db: 0.0
dist_est_m: 4.47
dist_sigma_m: 3.15
n_obs: 749
windows: 13
sources: { rssi: 0.87, entity_jaccard: 0.13 }
entity_jaccard: 0.37   # shared 11 AP(s), bound <= 74.33 m
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.7
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(v4c_edge, tdeck_1)
proto: espnow
rssi_est_dbm: -60.0
rssi_ab_dbm: None   # v4c_edge hears tdeck_1 (n:0)
rssi_ba_dbm: -60   # tdeck_1 hears v4c_edge (n:300)
asym_db: 0.0
dist_est_m: 7.62
dist_sigma_m: 2.46
n_obs: 300
windows: 13
sources: { rssi: 0.69, entity_jaccard: 0.1, ble: 0.21 }
entity_jaccard: 0.37   # shared 11 AP(s), bound <= 74.33 m
ble_bound_m: 7.62   # near-range BLE estimate — CAPPED the RSSI estimate
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(tdeck_1, cardputer_1)
proto: ble
rssi_est_dbm: -59.0
rssi_ab_dbm: -59   # tdeck_1 hears cardputer_1 (n:766)
rssi_ba_dbm: None   # cardputer_1 hears tdeck_1 (n:0)
asym_db: 0.0
dist_est_m: 1.0
dist_sigma_m: 0.7
n_obs: 766
windows: 13
sources: { rssi: 1.0 }
ble_reflection_suspect: yes   # saturated/asymmetric BLE — NOT used as a tight bound (reflection guard, ttn-semantic-positioning.md §2.2)
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.7
touched: 2026-07-31T23:00:34Z

---

@BELIEF:PROXIMITY @pair(tdeck_1, cardputer_1)
proto: espnow
rssi_est_dbm: -48.0
rssi_ab_dbm: -48   # tdeck_1 hears cardputer_1 (n:559)
rssi_ba_dbm: None   # cardputer_1 hears tdeck_1 (n:0)
asym_db: 0.0
dist_est_m: 7.27
dist_sigma_m: 1.04
n_obs: 559
windows: 13
sources: { rssi: 1.0 }
ble_reflection_suspect: yes   # saturated/asymmetric BLE — NOT used as a tight bound (reflection guard, ttn-semantic-positioning.md §2.2)
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.8
touched: 2026-07-31T23:00:34Z
