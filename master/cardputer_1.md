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

**ENTWIN** t_ms:60010 synced:0 window_ms:60010 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60010 synced:0 window_ms:60010 blocks:2706 rate:8000
**ACOUSTIC** rms_mean:122 rms_max:300 peak:638 transients:0

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:63760 synced:0 window_ms:63760
**LINK** peer:0x00000010 proto:espnow n:1 rssi_min:-32 rssi_med:-32 rssi_max:-32

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60185 synced:0 window_ms:60185
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-36 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-73 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-73 rssi_med:-50 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-51 rssi_med:-47 rssi_max:-45

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60185 synced:0 window_ms:60185 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60185 synced:0 window_ms:60185 n:593
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:58 moving_ms:0

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60185 synced:0 window_ms:60185 blocks:2618 rate:8000
**ACOUSTIC** rms_mean:191 rms_max:6118 peak:19246 transients:1
**TRANSIENT** t_ms:41020 rms:6118 synced:0

---

@LAT99LON0 | created:1785189513 | updated:1785189513 | relates:logs@LAT0LON0

**SYNC** id:6 t_ms:1785189513430 recv_ms:25971 offset_ms:1785189487459

---

@LAT97LON2 | created:1785189547 | updated:1785189547 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1785189547469 synced:1 window_ms:60010
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-35 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-60 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-54 rssi_med:-50 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-80 rssi_med:-51 rssi_max:-50

---

@LAT96LON2 | created:1785189547 | updated:1785189547 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1785189547587 synced:1 window_ms:60010 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90

---

@LAT95LON1 | created:1785189547 | updated:1785189547 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1785189547727 synced:1 window_ms:60010 n:349
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:18 moving_ms:0

---

@LAT94LON2 | created:1785189547 | updated:1785189547 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1785189547877 synced:1 window_ms:60010 blocks:1516 rate:8000
**ACOUSTIC** rms_mean:158 rms_max:515 peak:1380 transients:0

---

@LAT97LON3 | created:1785189607 | updated:1785189607 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1785189607469 synced:1 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-57 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-70 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-37 rssi_med:-34 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-59 rssi_med:-49 rssi_max:-36

---

@LAT95LON2 | created:1785189607 | updated:1785189607 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1785189607654 synced:1 window_ms:60000 n:235
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:15 moving_ms:0

---

@LAT94LON3 | created:1785189607 | updated:1785189607 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1785189607865 synced:1 window_ms:60000 blocks:1112 rate:8000
**ACOUSTIC** rms_mean:140 rms_max:1516 peak:4502 transients:1
**TRANSIENT** t_ms:1785189570618 rms:1516 synced:1

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60130 synced:0 window_ms:60130
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-80 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-58 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-35 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-37 rssi_med:-34 rssi_max:-33

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60130 synced:0 window_ms:60130 entities:11
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60130 synced:0 window_ms:60130 n:183
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60130 synced:0 window_ms:60130 blocks:857 rate:8000
**ACOUSTIC** rms_mean:117 rms_max:2753 peak:4237 transients:1
**TRANSIENT** t_ms:6875 rms:2753 synced:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120246 synced:0 window_ms:60116
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-39 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-50 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-36 rssi_med:-34 rssi_max:-31

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:120246 synced:0 window_ms:60116 n:627
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:14 moving_ms:0

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:120246 synced:0 window_ms:60116 blocks:2766 rate:8000
**ACOUSTIC** rms_mean:119 rms_max:7043 peak:28369 transients:7
**TRANSIENT** t_ms:78904 rms:7043 synced:0

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180431 synced:0 window_ms:60185
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-55 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-52 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-37 rssi_med:-35 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-65 rssi_med:-39 rssi_max:-30

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:180431 synced:0 window_ms:60185 n:353
**MOTION** state:still moving_permille:19 dev_mean_mg:14 dev_max_mg:495 moving_ms:1209

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:180431 synced:0 window_ms:60185 blocks:1369 rate:8000
**ACOUSTIC** rms_mean:133 rms_max:2139 peak:7299 transients:7
**TRANSIENT** t_ms:145270 rms:2139 synced:0

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240697 synced:0 window_ms:60266
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-59 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-63 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-37 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-35 rssi_med:-33 rssi_max:-30
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-38 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-56 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-80 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-42 rssi_med:-38 rssi_max:-36

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:240697 synced:0 window_ms:60266 n:228
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:14 moving_ms:0

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:240697 synced:0 window_ms:60266 blocks:974 rate:8000
**ACOUSTIC** rms_mean:220 rms_max:3530 peak:10662 transients:6
**TRANSIENT** t_ms:192276 rms:2719 synced:0

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60010 synced:0 window_ms:60010
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-51 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-58 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-53 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-79 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-79 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-40 rssi_med:-38 rssi_max:-36
**LINK** peer:0x00000011 proto:espnow n:12 rssi_min:-45 rssi_med:-41 rssi_max:-37
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-37 rssi_med:-36 rssi_max:-36

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60010 synced:0 window_ms:60010 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60010 synced:0 window_ms:60010 n:865
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60010 synced:0 window_ms:60010 blocks:3506 rate:8000
**ACOUSTIC** rms_mean:122 rms_max:479 peak:1730 transients:0

---

@LAT99LON1 | created:1785190035 | updated:1785190035 | relates:logs@LAT0LON0

**SYNC** id:7 t_ms:1785190035995 recv_ms:81790 offset_ms:1785189954205

---

@LAT97LON9 | created:1785190074 | updated:1785190074 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1785190074215 synced:1 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-38 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-67 rssi_med:-56 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-59 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-82 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-49 rssi_med:-44 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-56 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-46 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-39 rssi_med:-36 rssi_max:-33

---

@LAT95LON8 | created:1785190074 | updated:1785190074 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1785190074395 synced:1 window_ms:60000 n:884
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:15 moving_ms:0

---

@LAT94LON9 | created:1785190074 | updated:1785190074 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1785190074588 synced:1 window_ms:60000 blocks:3628 rate:8000
**ACOUSTIC** rms_mean:125 rms_max:342 peak:854 transients:0

---

@LAT97LON10 | created:1785190136 | updated:1785190136 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1785190136215 synced:1 window_ms:62000
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-82 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:67 rssi_min:-81 rssi_med:-57 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-48 rssi_med:-44 rssi_max:-35
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-38 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-57 rssi_max:-49
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-59 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-45 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-38 rssi_med:-36 rssi_max:-35

---

@LAT95LON9 | created:1785190138 | updated:1785190138 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1785190138475 synced:1 window_ms:62000 n:905
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:29 moving_ms:0

---

@LAT94LON10 | created:1785190140 | updated:1785190140 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1785190140740 synced:1 window_ms:62000 blocks:3721 rate:8000
**ACOUSTIC** rms_mean:148 rms_max:1354 peak:1957 transients:4
**TRANSIENT** t_ms:1785190109794 rms:1354 synced:1

---

@LAT97LON11 | created:1785190196 | updated:1785190196 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1785190196215 synced:1 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-78 rssi_med:-56 rssi_max:-49
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-82 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-63 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-60 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-47 rssi_med:-40 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-52 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-38 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-38 rssi_med:-36 rssi_max:-35

---

@LAT95LON10 | created:1785190198 | updated:1785190198 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1785190198532 synced:1 window_ms:60000 n:743
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0

---

@LAT94LON11 | created:1785190200 | updated:1785190200 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1785190200867 synced:1 window_ms:60000 blocks:3075 rate:8000
**ACOUSTIC** rms_mean:128 rms_max:668 peak:4442 transients:0

---

@LAT97LON12 | created:1785190256 | updated:1785190256 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1785190256225 synced:1 window_ms:60010
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-50 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-57 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-45 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-79 rssi_med:-55 rssi_max:-48
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-41 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-57 rssi_max:-49
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-36 rssi_med:-34 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-45 rssi_med:-42 rssi_max:-40

---

@LAT95LON11 | created:1785190256 | updated:1785190256 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1785190256618 synced:1 window_ms:60010 n:765
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:17 moving_ms:0

---

@LAT94LON12 | created:1785190257 | updated:1785190257 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1785190257056 synced:1 window_ms:60010 blocks:3083 rate:8000
**ACOUSTIC** rms_mean:129 rms_max:470 peak:1523 transients:0
