# Fleet Anchored Position Beliefs (semantic positioning SP2)

Authored by `companion.py anchor`: the relative @BELIEF:POSITION map
(positions.md) fitted onto the T-Deck GPS tie points (gps-fixes.md) by
a 2D similarity (scale+rotation+translation, reflection allowed). GPS is
the verifier + anchor, never an inference input. flip_resolved is true
only with >=3 non-collinear ties (2 leave the mirror ambiguous).

fit: ties=4 ['tdeck_1', 'v4b_relay', 'k10_1', 'v4a_bridge']  scale=0.2768  <-- WARN: far from 1.0  reflected=False  tie_rmse=4.98 m  flip_resolved=True

---

@BELIEF:POSITION @node(k10_1)
frame: geo   # absolute, GPS-anchored
lat_deg: 43.6525104
lon_deg: -116.3364312
x_m: 16.25
y_m: -0.00   # relative frame
sigma_m: 51.28
anchor_chain: [v4a_bridge, gps]
is_tie: yes
flip_resolved: true
tie_rmse_m: 4.98
touched: 2026-07-10T18:00:59Z

---

@BELIEF:POSITION @node(tdeck_1)
frame: geo   # absolute, GPS-anchored
lat_deg: 43.6525171
lon_deg: -116.3365556
x_m: 33.61
y_m: 31.87   # relative frame
sigma_m: 61.96
anchor_chain: [v4a_bridge, gps]
is_tie: yes
flip_resolved: true
tie_rmse_m: 4.98
touched: 2026-07-10T18:00:59Z

---

@BELIEF:POSITION @node(v4a_bridge)
frame: geo   # absolute, GPS-anchored
lat_deg: 43.6524736
lon_deg: -116.3364082
x_m: 0.00
y_m: -0.00   # relative frame
sigma_m: 57.72
anchor_chain: [v4a_bridge, gps]
is_tie: yes
flip_resolved: true
tie_rmse_m: 4.98
touched: 2026-07-10T18:00:59Z

---

@BELIEF:POSITION @node(v4b_relay)
frame: geo   # absolute, GPS-anchored
lat_deg: 43.6524534
lon_deg: -116.3365268
x_m: 6.83
y_m: 34.78   # relative frame
sigma_m: 53.15
anchor_chain: [v4a_bridge, gps]
is_tie: yes
flip_resolved: true
tie_rmse_m: 4.98
touched: 2026-07-10T18:00:59Z
