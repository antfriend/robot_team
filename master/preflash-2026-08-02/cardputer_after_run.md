# Cardputer Fleet Map TTDB (semantic positioning SP6)

The mesh-facing globe: one record per fleet node at its believed position, the map the
mesh draws of itself. The four POSITION records below are real beliefs, carried over
from the fleet's last embedding (companion.py positions -> fleetmap). The Cardputer's
own record is **not** a belief — it has no proximity evidence yet, and says so.

Regenerate this file from live beliefs with:

    python orchestrator/companion.py fleetmap --out firmware/cardputer_console/data/ttdb.md

then flash it with `scripts/Upload-Cardputer-FS.ps1`.

```mmpdb
db_id: cardputer-console-001
db_name: Cardputer ADV Console - Fleet Map
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: cardputer-console
  role: handheld-console-sense-organ
  perspective: operator
  scope: fleet-command
  senses:
    - "link rssi (esp-now + ble) -> @LAT97"
    - "wifi entity co-occurrence -> @LAT96"
    - "motion, from a BMI270 accelerometer -> @LAT95"
    - "sound, from an ES8311 codec + MEMS microphone -> @LAT94"
  globe:
    frame: mesh-topology
    origin: "@LAT0LON0"
    mapping: "each record is a fleet node at its believed position; the map the mesh draws of itself (companion.py fleetmap from positions.md + proximity.md)"
typed_edges:
  enabled: true
  syntax: "type@LATxLONy"
librarian:
  enabled: false
  primitive_queries: []
```

```cursor
lat: 0
lon: 0
```

---

@LAT0LON16 | created:1750000000 | updated:1750000000 | relates:espnow@LAT0LON0,espnow@LAT35LON7,espnow@LAT32LON34

**POSITION** node:k10_1
name: K10
x_m: 16.25  y_m: -0.00
sigma_m: 51.28   conf: 0.58
link V4-A: espnow 16.3m conf 0.80
link V4-B: espnow 34.1m conf 0.80
link T-Deck: espnow 38.4m conf 0.80

---

@LAT32LON34 | created:1750000000 | updated:1750000000 | relates:espnow@LAT0LON0,espnow@LAT35LON7,espnow@LAT0LON16

**POSITION** node:tdeck_1
name: T-Deck
x_m: 33.61  y_m: 31.87
sigma_m: 61.96   conf: 0.55
link V4-A: espnow 41.8m conf 0.75
link V4-B: espnow 27.2m conf 0.78
link K10: espnow 38.4m conf 0.80

---

@LAT0LON0 | created:1750000000 | updated:1750000000 | relates:espnow@LAT35LON7,espnow@LAT0LON16,espnow@LAT32LON34

**POSITION** node:v4a_bridge
name: V4-A
x_m: 0.00  y_m: -0.00
sigma_m: 57.72   conf: 0.55
link V4-B: espnow 37.1m conf 0.78
link K10: espnow 16.3m conf 0.80
link T-Deck: espnow 41.8m conf 0.75

---

@LAT35LON7 | created:1750000000 | updated:1750000000 | relates:espnow@LAT0LON0,espnow@LAT0LON16,espnow@LAT32LON34

**POSITION** node:v4b_relay
name: V4-B
x_m: 6.83  y_m: 34.78
sigma_m: 53.15   conf: 0.56
link V4-A: espnow 37.1m conf 0.78
link K10: espnow 34.1m conf 0.80
link T-Deck: espnow 27.2m conf 0.78

---

@LAT-20LON-20 | created:1750000000 | updated:1750000000 | relates:espnow@LAT0LON0

**POSITION-UNKNOWN** node:cardputer_1
name: Card
conf: 0.00
This node has just joined the fleet and has no position belief. It has not yet appeared
in a proximity fuse, so it has no x_m/y_m and no sigma. The coordinate above is a
PARKING SPOT so the record is navigable on the globe — it is not a claim about where
this node is. It becomes a real POSITION record the first time the fleet runs
`proximity` -> `positions` -> `fleetmap` with this node's @LAT97 windows in the pull.

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60000 synced:0 window_ms:60000 n:959
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60000 synced:0 window_ms:60000 blocks:3594 rate:8000
**ACOUSTIC** rms_mean:80 rms_max:320 peak:712 transients:0

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:120000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:120000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:78 rms_max:182 peak:434 transients:0

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:180000 synced:0 window_ms:60000 n:999
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:180000 synced:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:76 rms_max:836 peak:2397 transients:0

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:240010 synced:0 window_ms:60010 n:1000
**MOTION** state:still moving_permille:52 dev_mean_mg:22 dev_max_mg:739 moving_ms:3128

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:240010 synced:0 window_ms:60010 blocks:3718 rate:8000
**ACOUSTIC** rms_mean:192 rms_max:27498 peak:32767 transients:8
**TRANSIENT** t_ms:231372 rms:27498 synced:0

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:300010 synced:0 window_ms:60000 n:999
**MOTION** state:moving moving_permille:735 dev_mean_mg:227 dev_max_mg:1359 moving_ms:44107

---

@LAT93LON0 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON3,derived_from@LAT95LON4

**TRANSITION** t_ms:300010 synced:0 node:0x300 from:still to:moving dt_ms:60000
  @PERCEPT:before state:still t_ms:240010 window_ms:60010 n:1000 moving_permille:52 dev_mean_mg:22 dev_max_mg:739 moving_ms:3128 lane:@LAT95LON3
  @PERCEPT:after state:moving t_ms:300010 window_ms:60000 n:999 moving_permille:735 dev_mean_mg:227 dev_max_mg:1359 moving_ms:44107 lane:@LAT95LON4
**DELTA** edge:became d_permille:683 d_dev_mean_mg:205 d_dev_max_mg:620

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:300010 synced:0 window_ms:60000 blocks:3356 rate:8000
**ACOUSTIC** rms_mean:267 rms_max:5912 peak:29012 transients:19
**TRANSIENT** t_ms:295400 rms:5912 synced:0

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:360010 synced:0 window_ms:60000 n:999
**MOTION** state:moving moving_permille:775 dev_mean_mg:281 dev_max_mg:1947 moving_ms:46547

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:360010 synced:0 window_ms:60000 blocks:3094 rate:8000
**ACOUSTIC** rms_mean:307 rms_max:2722 peak:9919 transients:15
**TRANSIENT** t_ms:307232 rms:2722 synced:0

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:420012 synced:0 window_ms:60002 n:999
**MOTION** state:moving moving_permille:129 dev_mean_mg:34 dev_max_mg:809 moving_ms:7757

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:420012 synced:0 window_ms:60002 blocks:3660 rate:8000
**ACOUSTIC** rms_mean:336 rms_max:29828 peak:32768 transients:21
**TRANSIENT** t_ms:376854 rms:29828 synced:0

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:480012 synced:0 window_ms:60000 n:999
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0

---

@LAT93LON1 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON6,derived_from@LAT95LON7

**TRANSITION** t_ms:480012 synced:0 node:0x300 from:moving to:still dt_ms:60000
  @PERCEPT:before state:moving t_ms:420012 window_ms:60002 n:999 moving_permille:129 dev_mean_mg:34 dev_max_mg:809 moving_ms:7757 lane:@LAT95LON6
  @PERCEPT:after state:still t_ms:480012 window_ms:60000 n:999 moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0 lane:@LAT95LON7
**DELTA** edge:became d_permille:-129 d_dev_mean_mg:-25 d_dev_max_mg:-797

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:480012 synced:0 window_ms:60000 blocks:3742 rate:8000
**ACOUSTIC** rms_mean:72 rms_max:134 peak:355 transients:0

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:542012 synced:0 window_ms:62000 n:964
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:542012 synced:0 window_ms:62000 blocks:3610 rate:8000
**ACOUSTIC** rms_mean:83 rms_max:610 peak:774 transients:0
