# Fleet Anchored Position Beliefs (semantic positioning SP2)

Authored by `companion.py anchor`: the relative @BELIEF:POSITION map
(positions.md) fitted onto the T-Deck GPS tie points (gps-fixes.md) by
a 2D similarity (scale+rotation+translation, reflection allowed). GPS is
the verifier + anchor, never an inference input. flip_resolved is true
only with >=3 non-collinear ties (2 leave the mirror ambiguous).

fit: ties=4 ['tdeck_1', 'v4b_relay', 'k10_1', 'v4a_bridge']  scale=0.4122  <-- WARN: far from 1.0  reflected=True  tie_rmse=6.71 m  flip_resolved=True

---

@BELIEF:POSITION @node(k10_1)
frame: geo   # absolute, GPS-anchored
lat_deg: 43.6524795
lon_deg: -116.3364419
x_m: 21.23
y_m: 0.00   # relative frame
sigma_m: 3.37
anchor_chain: [v4a_bridge, gps]
is_tie: yes
flip_resolved: true
tie_rmse_m: 6.71
touched: 2026-07-13T22:32:17Z

---

@BELIEF:POSITION @node(tdeck_1)
frame: geo   # absolute, GPS-anchored
lat_deg: 43.6524884
lon_deg: -116.3364657
x_m: 16.05
y_m: 0.67   # relative frame
sigma_m: 18.42
anchor_chain: [v4a_bridge, gps]
is_tie: yes
flip_resolved: true
tie_rmse_m: 6.71
touched: 2026-07-13T22:32:17Z

---

@BELIEF:POSITION @node(v4a_bridge)
frame: geo   # absolute, GPS-anchored
lat_deg: 43.6525244
lon_deg: -116.3365311
x_m: 0.00
y_m: 0.00   # relative frame
sigma_m: 253.45
anchor_chain: [v4a_bridge, gps]
is_tie: yes
flip_resolved: true
tie_rmse_m: 6.71
touched: 2026-07-13T22:32:17Z

---

@BELIEF:POSITION @node(v4b_relay)
frame: geo   # absolute, GPS-anchored
lat_deg: 43.6524622
lon_deg: -116.3364831
x_m: 17.30
y_m: 8.43   # relative frame
sigma_m: 283.04
anchor_chain: [v4a_bridge, gps]
is_tie: yes
flip_resolved: true
tie_rmse_m: 6.71
touched: 2026-07-13T22:32:17Z
