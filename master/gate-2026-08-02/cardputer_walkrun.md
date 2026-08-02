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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-65 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:47 rssi_min:-64 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-45 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-51 rssi_med:-47 rssi_max:-46

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60000 synced:0 window_ms:60000 n:704
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:18 moving_ms:0

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60000 synced:0 window_ms:60000 blocks:2632 rate:8000
**ACOUSTIC** rms_mean:212 rms_max:1611 peak:6984 transients:5
**TRANSIENT** t_ms:52349 rms:1463 synced:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-70 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-67 rssi_med:-60 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-51 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-52 rssi_med:-41 rssi_max:-33

---

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:120000 synced:0 node:0x300 acting:@LAT95LON0 observed_in:@LAT97LON1 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-56 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-60 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-60 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-41 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-48 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:120000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:26 moving_ms:0

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:120000 synced:0 window_ms:60000 blocks:3731 rate:8000
**ACOUSTIC** rms_mean:122 rms_max:1126 peak:6424 transients:2
**TRANSIENT** t_ms:113751 rms:1126 synced:0

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-67 rssi_med:-61 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-65 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-83 rssi_med:-77 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-50 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:1 rssi_min:-43 rssi_med:-43 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:5 rssi_min:-60 rssi_med:-56 rssi_max:-52

---

@LAT92LON1 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON2,senses@LAT0LON0

**OUTCOME** t_ms:180000 synced:0 node:0x300 acting:@LAT95LON1 observed_in:@LAT97LON2 band_dbm:6 met:2 violated:2 unobserved:0 streak:1
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-77 delta:-21 verdict:violated
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-60 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-61 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-49 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-56 delta:-15 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:180000 synced:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:18 moving_ms:0

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:180000 synced:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:109 rms_max:1242 peak:6283 transients:3
**TRANSIENT** t_ms:170591 rms:1222 synced:0

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:71 rssi_min:-63 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-58 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-68 rssi_med:-62 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-61 rssi_med:-50 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-43 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:48 rssi_min:-83 rssi_med:-77 rssi_max:-69
**LINK** peer:0x00000012 proto:ble n:25 rssi_min:-63 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:5 rssi_min:-50 rssi_med:-49 rssi_max:-49

---

@LAT92LON2 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON3,senses@LAT0LON0

**OUTCOME** t_ms:240000 synced:0 node:0x300 acting:@LAT95LON2 observed_in:@LAT97LON3 band_dbm:6 met:6 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-61 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-62 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-56 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-77 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-77 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-49 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-50 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-56 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:240000 synced:0 window_ms:60000 n:994
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:18 moving_ms:0

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:240000 synced:0 window_ms:60000 blocks:3728 rate:8000
**ACOUSTIC** rms_mean:101 rms_max:2556 peak:9086 transients:5
**TRANSIENT** t_ms:212829 rms:2556 synced:0

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-86 rssi_med:-71 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-74 rssi_med:-55 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-62 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-46 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-48 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-51 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-79 rssi_med:-61 rssi_max:-57
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-66 rssi_med:-57 rssi_max:-53

---

@LAT92LON3 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON4,senses@LAT0LON0

**OUTCOME** t_ms:300000 synced:0 node:0x300 acting:@LAT95LON3 observed_in:@LAT97LON4 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-56 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-62 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-61 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-50 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-49 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-77 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-71 delta:6 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-57 delta:2 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-49 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-46 delta:3 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:300000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:18 moving_ms:0

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:300000 synced:0 window_ms:60000 blocks:3729 rate:8000
**ACOUSTIC** rms_mean:102 rms_max:3681 peak:10772 transients:4
**TRANSIENT** t_ms:279371 rms:3681 synced:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:73 rssi_min:-81 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-44 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-50 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-71 rssi_med:-60 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-87 rssi_med:-69 rssi_max:-58
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-79 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-38 rssi_med:-36 rssi_max:-35

---

@LAT92LON4 | created:0 | updated:0 | relates:testifies_about@LAT95LON4,derived_from@LAT97LON5,senses@LAT0LON0

**OUTCOME** t_ms:360000 synced:0 node:0x300 acting:@LAT95LON4 observed_in:@LAT97LON5 band_dbm:6 met:4 violated:4 unobserved:0 streak:1
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-71 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-52 delta:19 verdict:violated
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-36 delta:19 verdict:violated
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-46 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-46 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-49 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-60 delta:-11 verdict:violated
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-61 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-69 delta:-8 verdict:violated
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-59 delta:-2 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:360000 synced:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:18 moving_ms:0

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:360000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:112 rms_max:843 peak:2556 transients:0

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-79 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-54 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-63 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-49 rssi_med:-44 rssi_max:-37
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-71 rssi_med:-68 rssi_max:-65
**LINK** peer:0x00000200 proto:ble n:48 rssi_min:-90 rssi_med:-81 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-47 rssi_med:-42 rssi_max:-37

---

@LAT92LON5 | created:0 | updated:0 | relates:testifies_about@LAT95LON5,derived_from@LAT97LON6,senses@LAT0LON0

**OUTCOME** t_ms:420000 synced:0 node:0x300 acting:@LAT95LON5 observed_in:@LAT97LON6 band_dbm:6 met:6 violated:2 unobserved:0 streak:2
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-52 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-52 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-58 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-46 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-44 delta:2 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-60 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-68 delta:-8 verdict:violated
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-69 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-81 delta:-12 verdict:violated
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-36 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-35 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:420000 synced:0 window_ms:60000 n:987
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:420000 synced:0 window_ms:60000 blocks:3699 rate:8000
**ACOUSTIC** rms_mean:136 rms_max:3308 peak:8995 transients:7
**TRANSIENT** t_ms:404048 rms:3308 synced:0

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-60 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-44 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-46 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-72 rssi_med:-66 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:48 rssi_min:-86 rssi_med:-75 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-38 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-74 rssi_med:-56 rssi_max:-51

---

@LAT92LON6 | created:0 | updated:0 | relates:testifies_about@LAT95LON6,derived_from@LAT97LON7,senses@LAT0LON0

**OUTCOME** t_ms:480000 synced:0 node:0x300 acting:@LAT95LON6 observed_in:@LAT97LON7 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:2 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-52 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-35 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-36 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-44 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-68 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-66 delta:2 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-81 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-75 delta:6 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:480000 synced:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:480000 synced:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:139 rms_max:676 peak:1094 transients:0

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-83 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-79 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-49 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-49 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-64 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-38 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-49 rssi_med:-43 rssi_max:-41

---

@LAT92LON7 | created:0 | updated:0 | relates:testifies_about@LAT95LON7,derived_from@LAT97LON8,senses@LAT0LON0

**OUTCOME** t_ms:540000 synced:0 node:0x300 acting:@LAT95LON7 observed_in:@LAT97LON8 band_dbm:6 met:6 violated:2 unobserved:0 streak:1
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-43 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-66 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-47 delta:19 verdict:violated
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-75 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-60 delta:15 verdict:violated
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-36 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-36 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-57 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:540000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:540000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:130 rms_max:1168 peak:4047 transients:2
**TRANSIENT** t_ms:525457 rms:1168 synced:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-68 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-55 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-80 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:49 rssi_min:-84 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-47 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-50 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-49 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-38 rssi_med:-37 rssi_max:-35

---

@LAT92LON8 | created:0 | updated:0 | relates:testifies_about@LAT95LON8,derived_from@LAT97LON9,senses@LAT0LON0

**OUTCOME** t_ms:600000 synced:0 node:0x300 acting:@LAT95LON8 observed_in:@LAT97LON9 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-60 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-59 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-46 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-52 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-36 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-37 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:600000 synced:0 window_ms:60000 n:985
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:18 moving_ms:0

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:600000 synced:0 window_ms:60000 blocks:3694 rate:8000
**ACOUSTIC** rms_mean:129 rms_max:1168 peak:5642 transients:2
**TRANSIENT** t_ms:592866 rms:1168 synced:0

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:620639 synced:0 window_ms:560639 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-79 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-56 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-92 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-39 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-51 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-52 rssi_med:-43 rssi_max:-37
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-84 rssi_med:-53 rssi_max:-42

---

@LAT92LON9 | created:0 | updated:0 | relates:testifies_about@LAT95LON9,derived_from@LAT97LON10,senses@LAT0LON0

**OUTCOME** t_ms:660000 synced:0 node:0x300 acting:@LAT95LON9 observed_in:@LAT97LON10 band_dbm:6 met:7 violated:1 unobserved:0 streak:1
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-52 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-62 delta:-3 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-46 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-53 delta:-7 verdict:violated
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-37 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:660000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:660000 synced:0 window_ms:60000 blocks:3729 rate:8000
**ACOUSTIC** rms_mean:147 rms_max:1993 peak:2210 transients:2
**TRANSIENT** t_ms:658077 rms:1154 synced:0

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-82 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-60 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-38 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-42 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-44 rssi_med:-43 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:2 rssi_min:-95 rssi_med:-95 rssi_max:-91
**LINK** peer:0x00000200 proto:espnow n:12 rssi_min:-92 rssi_med:-89 rssi_max:-82

---

@LAT92LON10 | created:0 | updated:0 | relates:testifies_about@LAT95LON10,derived_from@LAT97LON11,senses@LAT0LON0

**OUTCOME** t_ms:720000 synced:0 node:0x300 acting:@LAT95LON10 observed_in:@LAT97LON11 band_dbm:6 met:6 violated:2 unobserved:0 streak:2
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-56 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-62 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-95 delta:-33 verdict:violated
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-37 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-40 delta:2 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-53 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-89 delta:-36 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:720000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:720000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:131 rms_max:1060 peak:1321 transients:0

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:780000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-57 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-37 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-41 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-61 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-92 rssi_med:-90 rssi_max:-88
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-44 rssi_med:-43 rssi_max:-43

---

@LAT92LON11 | created:0 | updated:0 | relates:testifies_about@LAT95LON11,derived_from@LAT97LON12,senses@LAT0LON0

**OUTCOME** t_ms:780000 synced:0 node:0x300 acting:@LAT95LON11 observed_in:@LAT97LON12 band_dbm:6 met:7 violated:0 unobserved:1 streak:0
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-37 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-40 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-95 band:6
**OBSERVED** peer:0x00000200 proto:ble verdict:unobserved
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-89 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-90 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:780000 synced:0 window_ms:60000 n:983
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:780000 synced:0 window_ms:60000 blocks:3685 rate:8000
**ACOUSTIC** rms_mean:144 rms_max:373 peak:770 transients:0

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:840000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-79 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-80 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-38 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-92 rssi_med:-89 rssi_max:-78
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-41 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-43 rssi_med:-43 rssi_max:-43

---

@LAT92LON12 | created:0 | updated:0 | relates:testifies_about@LAT95LON12,derived_from@LAT97LON13,senses@LAT0LON0

**OUTCOME** t_ms:840000 synced:0 node:0x300 acting:@LAT95LON12 observed_in:@LAT97LON13 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-37 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-40 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-90 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-89 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:840000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:18 moving_ms:0

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:840000 synced:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:127 rms_max:271 peak:588 transients:0

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:900000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-70 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-56 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-39 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-46 rssi_med:-40 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-48 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-74 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-80 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:49 rssi_min:-89 rssi_med:-58 rssi_max:-54

---

@LAT92LON13 | created:0 | updated:0 | relates:testifies_about@LAT95LON13,derived_from@LAT97LON14,senses@LAT0LON0

**OUTCOME** t_ms:900000 synced:0 node:0x300 acting:@LAT95LON13 observed_in:@LAT97LON14 band_dbm:6 met:6 violated:1 unobserved:0 streak:1
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-36 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-89 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-44 delta:45 verdict:violated
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-40 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:900000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:18 moving_ms:0

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:900000 synced:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:171 rms_max:13181 peak:32768 transients:15
**TRANSIENT** t_ms:868875 rms:13181 synced:0

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:960000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-79 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-43 rssi_med:-40 rssi_max:-36
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-48 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-45 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-38 rssi_med:-37 rssi_max:-35

---

@LAT92LON14 | created:0 | updated:0 | relates:testifies_about@LAT95LON14,derived_from@LAT97LON15,senses@LAT0LON0

**OUTCOME** t_ms:960000 synced:0 node:0x300 acting:@LAT95LON14 observed_in:@LAT97LON15 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-36 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-37 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-40 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-44 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-43 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-57 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:960000 synced:0 window_ms:60000 n:981
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:18 moving_ms:0

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:960000 synced:0 window_ms:60000 blocks:3673 rate:8000
**ACOUSTIC** rms_mean:146 rms_max:475 peak:1142 transients:0

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1020000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-39 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-81 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-45 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-55 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-79 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-43 rssi_med:-41 rssi_max:-36
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-50 rssi_med:-43 rssi_max:-40

---

@LAT92LON15 | created:0 | updated:0 | relates:testifies_about@LAT95LON15,derived_from@LAT97LON16,senses@LAT0LON0

**OUTCOME** t_ms:1020000 synced:0 node:0x300 acting:@LAT95LON15 observed_in:@LAT97LON16 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-56 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-56 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-41 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-44 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-37 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1020000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1020000 synced:0 window_ms:60000 blocks:3729 rate:8000
**ACOUSTIC** rms_mean:195 rms_max:5855 peak:13485 transients:12
**TRANSIENT** t_ms:1003307 rms:5130 synced:0

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1080000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:49 rssi_min:-80 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-38 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-41 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-81 rssi_med:-71 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:47 rssi_min:-92 rssi_med:-79 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-57 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-54 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-44 rssi_med:-43 rssi_max:-42

---

@LAT92LON16 | created:0 | updated:0 | relates:testifies_about@LAT95LON16,derived_from@LAT97LON17,senses@LAT0LON0

**OUTCOME** t_ms:1080000 synced:0 node:0x300 acting:@LAT95LON16 observed_in:@LAT97LON17 band_dbm:6 met:6 violated:2 unobserved:0 streak:1
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-37 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-44 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-71 delta:-27 verdict:violated
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-79 delta:-23 verdict:violated
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-41 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1080000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1080000 synced:0 window_ms:60000 blocks:3732 rate:8000
**ACOUSTIC** rms_mean:236 rms_max:7610 peak:8277 transients:17
**TRANSIENT** t_ms:1078375 rms:5409 synced:0

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1140000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:70 rssi_min:-81 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-37 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-42 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:67 rssi_min:-57 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-82 rssi_med:-71 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:49 rssi_min:-87 rssi_med:-76 rssi_max:-64
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-59 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-43 rssi_med:-43 rssi_max:-42

---

@LAT92LON17 | created:0 | updated:0 | relates:testifies_about@LAT95LON17,derived_from@LAT97LON18,senses@LAT0LON0

**OUTCOME** t_ms:1140000 synced:0 node:0x300 acting:@LAT95LON17 observed_in:@LAT97LON18 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-37 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-41 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-71 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-71 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-79 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-76 delta:3 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-56 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1140000 synced:0 window_ms:60000 n:979
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1140000 synced:0 window_ms:60000 blocks:3665 rate:8000
**ACOUSTIC** rms_mean:136 rms_max:346 peak:711 transients:0

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1200001 synced:0 window_ms:60001
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-57 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:46 rssi_min:-91 rssi_med:-78 rssi_max:-71
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-41 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-43 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-87 rssi_med:-68 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-38 rssi_med:-37 rssi_max:-36

---

@LAT92LON18 | created:0 | updated:0 | relates:testifies_about@LAT95LON18,derived_from@LAT97LON19,senses@LAT0LON0

**OUTCOME** t_ms:1200001 synced:0 node:0x300 acting:@LAT95LON18 observed_in:@LAT97LON19 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-37 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-40 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-71 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-68 delta:3 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-76 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-78 delta:-2 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1200001 synced:0 window_ms:60001 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:18 moving_ms:0

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1200001 synced:0 window_ms:60001 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:161 rms_max:13097 peak:14916 transients:10
**TRANSIENT** t_ms:1145592 rms:12605 synced:0

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1220638 synced:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1260001 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-80 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-64 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-38 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-87 rssi_med:-71 rssi_max:-57
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-48 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-45 rssi_med:-40 rssi_max:-36

---

@LAT92LON19 | created:0 | updated:0 | relates:testifies_about@LAT95LON19,derived_from@LAT97LON20,senses@LAT0LON0

**OUTCOME** t_ms:1260001 synced:0 node:0x300 acting:@LAT95LON19 observed_in:@LAT97LON20 band_dbm:6 met:6 violated:1 unobserved:1 streak:1
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-56 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-78 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-71 delta:7 verdict:violated
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-40 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-68 band:6
**OBSERVED** peer:0x00000200 proto:espnow verdict:unobserved
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-37 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1260001 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1260001 synced:0 window_ms:60000 blocks:3730 rate:8000
**ACOUSTIC** rms_mean:147 rms_max:5915 peak:6991 transients:5
**TRANSIENT** t_ms:1224015 rms:3452 synced:0

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1320001 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-79 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-83 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-64 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-53 rssi_med:-41 rssi_max:-36
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-49 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-69 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-47 rssi_med:-36 rssi_max:-33

---

@LAT92LON20 | created:0 | updated:0 | relates:testifies_about@LAT95LON20,derived_from@LAT97LON21,senses@LAT0LON0

**OUTCOME** t_ms:1320001 synced:0 node:0x300 acting:@LAT95LON20 observed_in:@LAT97LON21 band_dbm:6 met:6 violated:1 unobserved:0 streak:2
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-36 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-71 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-58 delta:13 verdict:violated
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-41 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1320001 synced:0 window_ms:60000 n:974
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:47 moving_ms:0

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1320001 synced:0 window_ms:60000 blocks:3646 rate:8000
**ACOUSTIC** rms_mean:111 rms_max:1346 peak:5193 transients:5
**TRANSIENT** t_ms:1284367 rms:1346 synced:0

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1380001 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-63 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-51 rssi_med:-46 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-80 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-65 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-43 rssi_med:-40 rssi_max:-36

---

@LAT92LON21 | created:0 | updated:0 | relates:testifies_about@LAT95LON21,derived_from@LAT97LON22,senses@LAT0LON0

**OUTCOME** t_ms:1380001 synced:0 node:0x300 acting:@LAT95LON21 observed_in:@LAT97LON22 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-57 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-57 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-40 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-46 delta:-4 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-36 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-35 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1380001 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1380001 synced:0 window_ms:60000 blocks:3732 rate:8000
**ACOUSTIC** rms_mean:101 rms_max:422 peak:1435 transients:0

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1440001 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-57 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-71 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-72 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-65 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-37 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-49 rssi_med:-42 rssi_max:-36
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-47 rssi_med:-43 rssi_max:-41

---

@LAT92LON22 | created:0 | updated:0 | relates:testifies_about@LAT95LON22,derived_from@LAT97LON23,senses@LAT0LON0

**OUTCOME** t_ms:1440001 synced:0 node:0x300 acting:@LAT95LON22 observed_in:@LAT97LON23 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-35 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-34 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-46 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:3 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:-2 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1440001 synced:0 window_ms:60000 n:994
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1440001 synced:0 window_ms:60000 blocks:3727 rate:8000
**ACOUSTIC** rms_mean:90 rms_max:219 peak:1085 transients:0

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1500001 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-80 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-69 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-66 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-37 rssi_med:-34 rssi_max:-34
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-54 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-71 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-45 rssi_med:-42 rssi_max:-36

---

@LAT92LON23 | created:0 | updated:0 | relates:testifies_about@LAT95LON23,derived_from@LAT97LON24,senses@LAT0LON0

**OUTCOME** t_ms:1500001 synced:0 node:0x300 acting:@LAT95LON23 observed_in:@LAT97LON24 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-57 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-56 delta:2 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-57 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-34 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-34 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-44 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1500001 synced:0 window_ms:60000 n:968
**MOTION** state:still moving_permille:1 dev_mean_mg:14 dev_max_mg:63 moving_ms:60

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1500001 synced:0 window_ms:60000 blocks:3625 rate:8000
**ACOUSTIC** rms_mean:121 rms_max:3030 peak:9623 transients:4
**TRANSIENT** t_ms:1478003 rms:3030 synced:0

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1560001 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-67 rssi_med:-60 rssi_max:-56
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-43 rssi_med:-41 rssi_max:-39

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1560001 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:23 moving_ms:0

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1560001 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:108 rms_max:607 peak:2213 transients:0

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1620001 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-69 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-40 rssi_med:-38 rssi_max:-37
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-80 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-45 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-45 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-60 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-62 rssi_med:-54 rssi_max:-51

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1620001 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:22 moving_ms:0

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1620001 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:105 rms_max:469 peak:2012 transients:0

---

@LAT91LON0 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:140
rev:9
sal:16
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TALLY** met:22 violated:2 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON1 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:44
rev:9
sal:56
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:ble node:0x300
**TALLY** met:14 violated:7 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:2 contradiction:1
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON2 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:140
rev:9
sal:16
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TALLY** met:22 violated:2 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON3 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:40
rev:9
sal:56
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:espnow node:0x300
**TALLY** met:12 violated:7 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:2 contradiction:1
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON4 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:172
rev:9
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000011 proto:espnow node:0x300
**TALLY** met:22 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON5 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:172
rev:9
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000011 proto:ble node:0x300
**TALLY** met:22 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON6 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:170
rev:9
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000012 proto:ble node:0x300
**TALLY** met:21 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON7 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:170
rev:9
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000012 proto:espnow node:0x300
**TALLY** met:21 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1680001 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-59 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-39 rssi_med:-38 rssi_max:-37
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-80 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-46 rssi_med:-44 rssi_max:-39
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-47 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:68 rssi_min:-61 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-69 rssi_med:-58 rssi_max:-54

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1680001 synced:0 window_ms:60000 n:968
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:27 moving_ms:0

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1680001 synced:0 window_ms:60000 blocks:3624 rate:8000
**ACOUSTIC** rms_mean:129 rms_max:366 peak:1304 transients:0
