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
rssi_est_dbm: -34.0
rssi_ab_dbm: None   # v4a_bridge hears v4b_relay (n:0)
rssi_ba_dbm: -34.0   # v4b_relay hears v4a_bridge (n:368)
asym_db: 0.0
dist_est_m: 0.06
dist_sigma_m: 0.04
n_obs: 368
windows: 6
sources: { rssi: 1.0 }
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.7
touched: 2026-07-10T22:16:31Z

---

@BELIEF:PROXIMITY @pair(v4a_bridge, v4b_relay)
proto: espnow
rssi_est_dbm: -21.5
rssi_ab_dbm: None   # v4a_bridge hears v4b_relay (n:0)
rssi_ba_dbm: -21.5   # v4b_relay hears v4a_bridge (n:132)
asym_db: 0.0
dist_est_m: 2.06
dist_sigma_m: 0.3
n_obs: 132
windows: 6
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.7
touched: 2026-07-10T22:16:31Z

---

@BELIEF:PROXIMITY @pair(v4b_relay, tdeck_1)
proto: ble
rssi_est_dbm: -60.0
rssi_ab_dbm: -60.0   # v4b_relay hears tdeck_1 (n:371)
rssi_ba_dbm: None   # tdeck_1 hears v4b_relay (n:0)
asym_db: 0.0
dist_est_m: 1.12
dist_sigma_m: 2.19
n_obs: 371
windows: 6
sources: { rssi: 1.0 }
calibrated: no   # default path-loss {'rssi_d0': -59.0, 'd0_m': 1.0, 'n': 2.0} — run the SP1 calibration walk
conf: 0.7
touched: 2026-07-10T22:16:31Z

---

@BELIEF:PROXIMITY @pair(v4b_relay, tdeck_1)
proto: espnow
rssi_est_dbm: -52.5
rssi_ab_dbm: -52.5   # v4b_relay hears tdeck_1 (n:127)
rssi_ba_dbm: None   # tdeck_1 hears v4b_relay (n:0)
asym_db: 0.0
dist_est_m: 9.01
dist_sigma_m: 4.69
n_obs: 127
windows: 6
sources: { rssi: 1.0 }
calibrated: yes   # master\calibration.md {'rssi_d0': -6.3, 'd0_m': 1.0, 'n': 4.84, 'rmse_db': 1.4}
conf: 0.69
touched: 2026-07-10T22:16:31Z
