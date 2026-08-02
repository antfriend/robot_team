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

@LAT99LON0 | created:1785189513 | updated:1785189513 | relates:logs@LAT0LON0

**SYNC** id:6 t_ms:1785189513430 recv_ms:25971 offset_ms:1785189487459

---

@LAT99LON1 | created:1785190035 | updated:1785190035 | relates:logs@LAT0LON0

**SYNC** id:7 t_ms:1785190035995 recv_ms:81790 offset_ms:1785189954205

---


---


---


---


---


---


---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-70 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-78 rssi_med:-67 rssi_max:-60
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-56 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-72 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:24 rssi_min:-99 rssi_med:-90 rssi_max:-81
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-79 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-66 rssi_med:-61 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-50 rssi_med:-49 rssi_max:-47

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60000 synced:0 window_ms:60000 n:950
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:26 moving_ms:0

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60000 synced:0 window_ms:60000 blocks:3558 rate:8000
**ACOUSTIC** rms_mean:202 rms_max:2745 peak:8207 transients:12
**TRANSIENT** t_ms:9691 rms:2745 synced:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-79 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-73 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-68 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-71 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-62 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-50 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000011 proto:ble n:14 rssi_min:-98 rssi_med:-92 rssi_max:-91
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-58 rssi_med:-53 rssi_max:-51

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:120000 synced:0 window_ms:60000 n:994
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:120000 synced:0 window_ms:60000 blocks:3726 rate:8000
**ACOUSTIC** rms_mean:210 rms_max:11472 peak:12518 transients:11
**TRANSIENT** t_ms:89971 rms:11472 synced:0

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-82 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-68 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:11 rssi_min:-99 rssi_med:-92 rssi_max:-91
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-62 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-56 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-51 rssi_med:-49 rssi_max:-47

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:180000 synced:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:180000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:153 rms_max:893 peak:1815 transients:0

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-68 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-69 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-72 rssi_med:-71 rssi_max:-67
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-62 rssi_med:-61 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-50 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-68 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000011 proto:ble n:7 rssi_min:-96 rssi_med:-94 rssi_max:-93

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:240000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:240000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:155 rms_max:379 peak:768 transients:0

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-51 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-69 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-68 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000011 proto:ble n:6 rssi_min:-95 rssi_med:-93 rssi_max:-92
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-68 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-62 rssi_med:-61 rssi_max:-61
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-53 rssi_med:-53 rssi_max:-52

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:300000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:300000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:167 rms_max:425 peak:822 transients:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-50 rssi_med:-50 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-53 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-72 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-62 rssi_med:-61 rssi_max:-61
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:10 rssi_min:-98 rssi_med:-95 rssi_max:-92

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:360000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:360000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:164 rms_max:445 peak:1242 transients:0

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:12 rssi_min:-95 rssi_med:-94 rssi_max:-90
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-67 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-62 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-71 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-68 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-51 rssi_med:-49 rssi_max:-47

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:420000 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:17 moving_ms:0

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:420000 synced:0 window_ms:60000 blocks:3726 rate:8000
**ACOUSTIC** rms_mean:203 rms_max:12006 peak:13425 transients:8
**TRANSIENT** t_ms:391920 rms:12006 synced:0

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-80 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-71 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-50 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-58 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-68 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-62 rssi_med:-61 rssi_max:-61
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-71 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000011 proto:ble n:8 rssi_min:-94 rssi_med:-93 rssi_max:-91

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:480000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:17 moving_ms:0

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:480000 synced:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:191 rms_max:6331 peak:6977 transients:5
**TRANSIENT** t_ms:463097 rms:6331 synced:0

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-80 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-69 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-68 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-51 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-62 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-71 rssi_med:-70 rssi_max:-70
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:4 rssi_min:-94 rssi_med:-93 rssi_max:-92

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:540000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:19 moving_ms:0

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:540000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:229 rms_max:13944 peak:16765 transients:9
**TRANSIENT** t_ms:531119 rms:13944 synced:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-50 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-77 rssi_med:-69 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-71 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-64 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:42 rssi_min:-80 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:7 rssi_min:-62 rssi_med:-61 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000011 proto:ble n:8 rssi_min:-97 rssi_med:-95 rssi_max:-92

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:600000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:18 moving_ms:0

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:600000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:243 rms_max:4793 peak:5720 transients:12
**TRANSIENT** t_ms:571641 rms:4652 synced:0

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:611639 synced:0 window_ms:551639 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-83 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000012 proto:ble n:46 rssi_min:-79 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:17 rssi_min:-99 rssi_med:-93 rssi_max:-87
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-53 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-60 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-73 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-76 rssi_med:-67 rssi_max:-61
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-84 rssi_med:-61 rssi_max:-52

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:660000 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:17 moving_ms:0

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:660000 synced:0 window_ms:60000 blocks:3729 rate:8000
**ACOUSTIC** rms_mean:254 rms_max:11443 peak:12598 transients:17
**TRANSIENT** t_ms:645817 rms:5825 synced:0

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-75 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:17 rssi_min:-95 rssi_med:-92 rssi_max:-90
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-72 rssi_med:-66 rssi_max:-61
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-67 rssi_max:-61
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-73 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000001 proto:espnow n:1 rssi_min:-54 rssi_med:-54 rssi_max:-54
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-59 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-64 rssi_med:-61 rssi_max:-51

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:720000 synced:0 window_ms:60000 n:994
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:24 moving_ms:0

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:720000 synced:0 window_ms:60000 blocks:3726 rate:8000
**ACOUSTIC** rms_mean:204 rms_max:4287 peak:8847 transients:7
**TRANSIENT** t_ms:679435 rms:4287 synced:0

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:780000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-68 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-71 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-68 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:8 rssi_min:-97 rssi_med:-95 rssi_max:-90
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-55 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-52 rssi_med:-49 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-73 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-62 rssi_med:-60 rssi_max:-59

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:780000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:780000 synced:0 window_ms:60000 blocks:3738 rate:8000
**ACOUSTIC** rms_mean:173 rms_max:4870 peak:5588 transients:3
**TRANSIENT** t_ms:725577 rms:4585 synced:0

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:840000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-68 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-70 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-68 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-56 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-61 rssi_med:-60 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-52 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-73 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:2 rssi_min:-97 rssi_med:-97 rssi_max:-97

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:840000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:840000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:174 rms_max:4021 peak:4572 transients:3
**TRANSIENT** t_ms:836011 rms:3935 synced:0

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:900000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:19 rssi_min:-97 rssi_med:-92 rssi_max:-85
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-73 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-55 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-72 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-52 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-76 rssi_med:-73 rssi_max:-70
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-70 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-63 rssi_med:-56 rssi_max:-55

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:900000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:900000 synced:0 window_ms:60000 blocks:3732 rate:8000
**ACOUSTIC** rms_mean:161 rms_max:1254 peak:4035 transients:1
**TRANSIENT** t_ms:869159 rms:1254 synced:0

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:960000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-80 rssi_med:-67 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:32 rssi_min:-51 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-71 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-65 rssi_med:-62 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-75 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-65 rssi_med:-65 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-54 rssi_med:-52 rssi_max:-51

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:960000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:960000 synced:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:225 rms_max:5730 peak:6493 transients:4
**TRANSIENT** t_ms:941102 rms:4358 synced:0

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1020000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-51 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-70 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-68 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-55 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-74 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-63 rssi_med:-62 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:14 rssi_min:-96 rssi_med:-93 rssi_max:-85

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1020000 synced:0 window_ms:60000 n:994
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:17 moving_ms:0

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1020000 synced:0 window_ms:60000 blocks:3725 rate:8000
**ACOUSTIC** rms_mean:214 rms_max:8684 peak:9398 transients:4
**TRANSIENT** t_ms:980874 rms:4418 synced:0

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1080000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-52 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-73 rssi_med:-66 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-75 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-54 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-65 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-74 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:12 rssi_min:-94 rssi_med:-92 rssi_max:-83

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1080000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1080000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:164 rms_max:2412 peak:8634 transients:3
**TRANSIENT** t_ms:1039723 rms:2412 synced:0

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1140000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-80 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-51 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-71 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-55 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-78 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000011 proto:ble n:13 rssi_min:-95 rssi_med:-91 rssi_max:-78
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-61 rssi_med:-60 rssi_max:-59

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1140000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:17 moving_ms:0

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1140000 synced:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:203 rms_max:10426 peak:11528 transients:4
**TRANSIENT** t_ms:1124863 rms:6947 synced:0

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1200000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-70 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-51 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-66 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:6 rssi_min:-96 rssi_med:-90 rssi_max:-87
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-53 rssi_med:-52 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-73 rssi_med:-72 rssi_max:-72
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-80 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-61 rssi_med:-60 rssi_max:-60

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1200000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1200000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:156 rms_max:375 peak:728 transients:0

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1211640 synced:0 window_ms:600001 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1260000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-83 rssi_med:-66 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-72 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-55 rssi_med:-52 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-68 rssi_med:-60 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-70 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-74 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-51 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000011 proto:ble n:9 rssi_min:-96 rssi_med:-93 rssi_max:-83

---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1260000 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:20 moving_ms:0

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1260000 synced:0 window_ms:60000 blocks:3728 rate:8000
**ACOUSTIC** rms_mean:189 rms_max:5619 peak:6092 transients:3
**TRANSIENT** t_ms:1215020 rms:3427 synced:0

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-69 rssi_med:-51 rssi_max:-39
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-41 rssi_med:-31 rssi_max:-29

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60000 synced:0 window_ms:60000 n:960
**MOTION** state:still moving_permille:33 dev_mean_mg:14 dev_max_mg:402 moving_ms:2360

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60000 synced:0 window_ms:60000 blocks:3586 rate:8000
**ACOUSTIC** rms_mean:879 rms_max:24577 peak:32768 transients:13
**TRANSIENT** t_ms:26631 rms:24577 synced:0

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-49 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-38 rssi_med:-33 rssi_max:-29

---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:120000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:40 moving_ms:0

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:120000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:909 rms_max:16148 peak:32768 transients:3
**TRANSIENT** t_ms:105847 rms:16148 synced:0

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-38 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-61 rssi_med:-49 rssi_max:-42

---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:180000 synced:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:1 dev_mean_mg:10 dev_max_mg:118 moving_ms:60

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:180000 synced:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:913 rms_max:9830 peak:29461 transients:4
**TRANSIENT** t_ms:178400 rms:9830 synced:0

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-29 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-42 rssi_max:-37

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:240000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:5 dev_mean_mg:11 dev_max_mg:207 moving_ms:300

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:240000 synced:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:922 rms_max:18144 peak:32768 transients:5
**TRANSIENT** t_ms:195345 rms:18144 synced:0

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:69 rssi_min:-74 rssi_med:-68 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-56 rssi_med:-53 rssi_max:-25

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:300000 synced:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:42 moving_ms:0

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:300000 synced:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:898 rms_max:1895 peak:5952 transients:1
**TRANSIENT** t_ms:240188 rms:1230 synced:0

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-67 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-80 rssi_med:-69 rssi_max:-62

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:360000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:4 dev_mean_mg:11 dev_max_mg:95 moving_ms:240

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:360000 synced:0 window_ms:60000 blocks:3730 rate:8000
**ACOUSTIC** rms_mean:962 rms_max:17803 peak:32768 transients:3
**TRANSIENT** t_ms:315498 rms:17803 synced:0

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-52 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-78 rssi_med:-64 rssi_max:-60

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:420000 synced:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:27 moving_ms:0

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:420000 synced:0 window_ms:60000 blocks:3740 rate:8000
**ACOUSTIC** rms_mean:913 rms_max:1804 peak:4609 transients:0

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-67 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-51 rssi_med:-50 rssi_max:-49

---

@LAT95LON28 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:480000 synced:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:1 dev_mean_mg:10 dev_max_mg:100 moving_ms:60

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:480000 synced:0 window_ms:60000 blocks:3739 rate:8000
**ACOUSTIC** rms_mean:916 rms_max:5297 peak:11104 transients:1
**TRANSIENT** t_ms:423063 rms:5131 synced:0

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-53 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-69 rssi_med:-64 rssi_max:-61

---

@LAT95LON29 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:540000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:7 dev_mean_mg:11 dev_max_mg:107 moving_ms:420

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:540000 synced:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:964 rms_max:18125 peak:32768 transients:8
**TRANSIENT** t_ms:500896 rms:18125 synced:0

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-53 rssi_med:-51 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-69 rssi_med:-64 rssi_max:-63

---

@LAT95LON30 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:600000 synced:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:15 moving_ms:0

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:600000 synced:0 window_ms:60000 blocks:3742 rate:8000
**ACOUSTIC** rms_mean:883 rms_max:1918 peak:4519 transients:0

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:611159 synced:0 window_ms:551159 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-80 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-53 rssi_med:-51 rssi_max:-51

---

@LAT95LON31 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:660000 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:15 moving_ms:0

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:660000 synced:0 window_ms:60000 blocks:3728 rate:8000
**ACOUSTIC** rms_mean:895 rms_max:1882 peak:3724 transients:0

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-69 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000200 proto:espnow n:11 rssi_min:-52 rssi_med:-51 rssi_max:-50

---

@LAT95LON32 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:720000 synced:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:4 dev_mean_mg:11 dev_max_mg:111 moving_ms:240

---

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:720000 synced:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:954 rms_max:11415 peak:27290 transients:4
**TRANSIENT** t_ms:690200 rms:11415 synced:0

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91

---

@LAT95LON33 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60000 synced:0 window_ms:60000 n:955
**MOTION** state:still moving_permille:70 dev_mean_mg:20 dev_max_mg:587 moving_ms:4025

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60000 synced:0 window_ms:60000 blocks:3555 rate:8000
**ACOUSTIC** rms_mean:160 rms_max:19544 peak:32768 transients:13
**TRANSIENT** t_ms:29904 rms:19544 synced:0
