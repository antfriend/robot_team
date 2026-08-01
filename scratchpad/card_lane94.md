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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-84 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-60 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-80 rssi_med:-65 rssi_max:-60
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-50 rssi_med:-50 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-69 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-74 rssi_med:-73 rssi_max:-71

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:360000 synced:0 window_ms:60000 n:984
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-77 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-60 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-74 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-85 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-55 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-74 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000010 proto:espnow n:35 rssi_min:-52 rssi_med:-50 rssi_max:-46

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:420000 synced:0 window_ms:60000 n:994
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-53 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-85 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-75 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-82 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-81 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-49 rssi_med:-47 rssi_max:-47

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:480000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-70 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-86 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-52 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-69 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-71 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:132 rssi_min:-55 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-74 rssi_med:-73 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-60 rssi_med:-53 rssi_max:-51

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:540000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-77 rssi_med:-66 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-79 rssi_med:-68 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-75 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-86 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-55 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-61 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-55 rssi_med:-53 rssi_max:-53

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:600000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:611255 synced:0 window_ms:551255 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-68 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-80 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-55 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-56 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-74 rssi_med:-73 rssi_max:-72
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-84 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-81 rssi_med:-67 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-63 rssi_med:-55 rssi_max:-54

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:660000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-85 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-75 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-51 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-69 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-80 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-55 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-54 rssi_med:-53 rssi_max:-52

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:720000 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:780000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-85 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-74 rssi_med:-73 rssi_max:-70
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-47 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-69 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-53 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-56 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-79 rssi_med:-64 rssi_max:-61

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:780000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:840000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-82 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-70 rssi_med:-61 rssi_max:-56
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-60 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-87 rssi_med:-81 rssi_max:-78
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-75 rssi_med:-73 rssi_max:-72
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-51 rssi_med:-45 rssi_max:-44

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:840000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:18 moving_ms:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:900000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-80 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-74 rssi_med:-73 rssi_max:-72
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-56 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-84 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-82 rssi_med:-60 rssi_max:-56

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:900000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:960000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-68 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-45 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-55 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-84 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-60 rssi_max:-56
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-74 rssi_med:-72 rssi_max:-71

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:960000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1020000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-69 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-74 rssi_med:-73 rssi_max:-72
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-83 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-56 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-84 rssi_med:-80 rssi_max:-78

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1020000 synced:0 window_ms:60000 n:994
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1080000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-61 rssi_max:-57
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-70 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-57 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-84 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-74 rssi_med:-72 rssi_max:-71

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1080000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:19 moving_ms:0

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1140000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-80 rssi_med:-66 rssi_max:-58
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-74 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-54 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-83 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-85 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000001 proto:espnow n:13 rssi_min:-52 rssi_med:-48 rssi_max:-47

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1140000 synced:0 window_ms:60000 n:973
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1200000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-73 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:10 rssi_min:-52 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-85 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-66 rssi_max:-57
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-71 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-54 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-56 rssi_med:-53 rssi_max:-48

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1200000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1211255 synced:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1260001 synced:0 window_ms:60001
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-66 rssi_max:-61
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-74 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-55 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:10 rssi_min:-53 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-70 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-85 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-64 rssi_max:-59
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-54 rssi_med:-51 rssi_max:-48

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1260001 synced:0 window_ms:60001 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:16 moving_ms:0

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1320001 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-60 rssi_max:-58
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-72 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-85 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-45 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-67 rssi_max:-66
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-55 rssi_med:-53 rssi_max:-52

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1320001 synced:0 window_ms:60000 n:993
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1380001 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-80 rssi_med:-60 rssi_max:-58
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-84 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-72 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-80 rssi_med:-67 rssi_max:-66
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-45 rssi_med:-44 rssi_max:-44

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1380001 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1440001 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:80 rssi_min:-81 rssi_med:-67 rssi_max:-66
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-62 rssi_med:-60 rssi_max:-58
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-84 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-69 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-73 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-56 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:11 rssi_min:-44 rssi_med:-44 rssi_max:-44

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1440001 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1500001 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-85 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-66 rssi_max:-58
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-76 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-60 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-90 rssi_med:-66 rssi_max:-61
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-69 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-55 rssi_med:-49 rssi_max:-44

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1500001 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:16 moving_ms:0

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1560001 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-73 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-72 rssi_med:-65 rssi_max:-60
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-70 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-85 rssi_med:-79 rssi_max:-78
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-58 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-79 rssi_med:-63 rssi_max:-59
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-50 rssi_med:-47 rssi_max:-46

---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1560001 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1620001 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-67 rssi_max:-61
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-69 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-73 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-51 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-86 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-76 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-56 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-50 rssi_med:-48 rssi_max:-47

---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1620001 synced:0 window_ms:60000 n:994
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1680002 synced:0 window_ms:60001
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-68 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-54 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-85 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-70 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-73 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-56 rssi_med:-51 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-55 rssi_med:-49 rssi_max:-48

---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1680002 synced:0 window_ms:60001 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1740002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-74 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-81 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-64 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-86 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000012 proto:ble n:49 rssi_min:-79 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-56 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-54 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-57 rssi_med:-51 rssi_max:-49

---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1740002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1800002 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-64 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-85 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-77 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-57 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-50 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-69 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-83 rssi_med:-66 rssi_max:-63

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1800002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1811256 synced:0 window_ms:600001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1860002 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-50 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-74 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-54 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-81 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-53 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:50 rssi_min:-81 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-86 rssi_med:-80 rssi_max:-78

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1860002 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1920002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-86 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-58 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-69 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-73 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-50 rssi_med:-46 rssi_max:-45

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1920002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1980002 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-88 rssi_med:-68 rssi_max:-64
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-68 rssi_max:-62
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-87 rssi_med:-81 rssi_max:-79
**LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-56 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-65 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-54 rssi_med:-49 rssi_max:-47

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1980002 synced:0 window_ms:60000 n:993
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2040002 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-88 rssi_med:-69 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-73 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-86 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-59 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:10 rssi_min:-53 rssi_med:-50 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:46 rssi_min:-76 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-82 rssi_med:-66 rssi_max:-63

---

@LAT95LON28 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2040002 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2100002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-86 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-89 rssi_med:-68 rssi_max:-64
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-74 rssi_med:-65 rssi_max:-59
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-57 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-73 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-53 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-82 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-59 rssi_med:-50 rssi_max:-47

---

@LAT95LON29 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2100002 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2160002 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-81 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000200 proto:ble n:47 rssi_min:-76 rssi_med:-69 rssi_max:-65
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-73 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-69 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-55 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-62 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-86 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-56 rssi_med:-49 rssi_max:-47

---

@LAT95LON30 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2160002 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2220002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-74 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-87 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-56 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-50 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:44 rssi_min:-82 rssi_med:-68 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:8 rssi_min:-57 rssi_med:-54 rssi_max:-52

---

@LAT95LON31 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2220002 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2280002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-75 rssi_med:-73 rssi_max:-69
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-55 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-56 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-85 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-68 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-48 rssi_med:-48 rssi_max:-48

---

@LAT95LON32 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2280002 synced:0 window_ms:60000 n:994
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2340002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-85 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-65 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-73 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-68 rssi_max:-64
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-54 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-48 rssi_med:-48 rssi_max:-48

---

@LAT95LON33 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2340002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:16 moving_ms:0

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2400002 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-69 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-65 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-72 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-54 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-85 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-48 rssi_med:-48 rssi_max:-48
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-56 rssi_med:-53 rssi_max:-52

---

@LAT95LON34 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2400002 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2411255 synced:0 window_ms:599999 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2460002 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-49 rssi_med:-48 rssi_max:-48
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-85 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-73 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-68 rssi_med:-68 rssi_max:-64
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-54 rssi_med:-53 rssi_max:-53

---

@LAT95LON35 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2460002 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2520002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-85 rssi_med:-84 rssi_max:-79
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-73 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-55 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-64 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-59 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-52 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-70 rssi_med:-66 rssi_max:-64

---

@LAT95LON36 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2520002 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:20 moving_ms:0

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2580002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:48 rssi_min:-92 rssi_med:-81 rssi_max:-79
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-78 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:11 rssi_min:-53 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-55 rssi_med:-53 rssi_max:-51

---

@LAT95LON37 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2580002 synced:0 window_ms:60000 n:993
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:19 moving_ms:0

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2640002 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-77 rssi_med:-68 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-75 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-88 rssi_med:-69 rssi_max:-59
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-64 rssi_med:-51 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-56 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-57 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-62 rssi_med:-51 rssi_max:-48

---

@LAT95LON38 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2640002 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:19 moving_ms:0

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2700002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:13 rssi_min:-54 rssi_med:-51 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-81 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000012 proto:ble n:50 rssi_min:-69 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-68 rssi_max:-64
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-56 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-81 rssi_med:-68 rssi_max:-64
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-54 rssi_med:-51 rssi_max:-49

---

@LAT95LON39 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2700002 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:16 moving_ms:0

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2760002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:41 rssi_min:-73 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:7 rssi_min:-60 rssi_med:-51 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-90 rssi_med:-68 rssi_max:-65
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-58 rssi_med:-52 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-80 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-56 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-82 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-59 rssi_med:-53 rssi_max:-50

---

@LAT95LON40 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2760002 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:21 moving_ms:0

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2820002 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-51 rssi_med:-49 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-58 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-82 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-72 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-56 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-49 rssi_med:-48 rssi_max:-46

---

@LAT95LON41 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2820002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:17 moving_ms:0

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2880002 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-71 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:67 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-55 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-68 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-52 rssi_med:-49 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-48 rssi_med:-48 rssi_max:-47

---

@LAT95LON42 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2880002 synced:0 window_ms:60000 n:993
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2940002 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-68 rssi_med:-66 rssi_max:-61
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-79 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-54 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-55 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-49 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-51 rssi_med:-49 rssi_max:-48

---

@LAT95LON43 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2940002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3000002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:71 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-68 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-79 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-80 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-54 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-52 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-48 rssi_med:-48 rssi_max:-48

---

@LAT95LON44 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3000002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3011255 synced:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3060002 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-68 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-71 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-56 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-51 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-82 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-48 rssi_med:-48 rssi_max:-48

---

@LAT95LON45 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3060002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3120002 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-68 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-80 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-57 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-55 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-49 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-74 rssi_med:-68 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-51 rssi_med:-50 rssi_max:-48

---

@LAT95LON46 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3120002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3180002 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-68 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-71 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-55 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-51 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:47 rssi_min:-68 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-48 rssi_med:-48 rssi_max:-47

---

@LAT95LON47 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3180002 synced:0 window_ms:60000 n:993
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:18 moving_ms:0

---

