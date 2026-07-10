# Fleet GPS Fixes (semantic positioning SP2 ground truth)

Authored by `companion.py gps --at <node>`: each record is a T-Deck GPS
fix taken beside a static node. `companion.py anchor` fits the relative
@BELIEF:POSITION map to these absolute tie points (GPS is the verifier +
anchor, never an inference input). >=3 non-collinear ties resolve the mirror.

---

@PERCEPT:GPS @at(tdeck_1)
lat_deg: 43.6525363
lon_deg: -116.3365368
alt_m: 817.9
quality: 2
sats: 12
hdop: 0.6
source_node: tdeck_1
node_epoch_ms: 0
touched: 2026-07-10T17:49:52Z

---

@PERCEPT:GPS @at(v4b_relay)
lat_deg: 43.6524050
lon_deg: -116.3365342
alt_m: 810.8
quality: 2
sats: 12
hdop: 0.6
source_node: tdeck_1
node_epoch_ms: 0
touched: 2026-07-10T17:52:43Z

---

@PERCEPT:GPS @at(k10_1)
lat_deg: 43.6525062
lon_deg: -116.3363758
alt_m: 813.3
quality: 2
sats: 12
hdop: 0.7
source_node: tdeck_1
node_epoch_ms: 0
touched: 2026-07-10T17:56:16Z

---

@PERCEPT:GPS @at(v4a_bridge)
lat_deg: 43.6525070
lon_deg: -116.3364750
alt_m: 802.5
quality: 2
sats: 12
hdop: 0.6
source_node: tdeck_1
node_epoch_ms: 0
touched: 2026-07-10T18:00:35Z
