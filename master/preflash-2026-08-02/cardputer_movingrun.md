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

@LAT93LON0 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON3,derived_from@LAT95LON4

**TRANSITION** t_ms:300010 synced:0 node:0x300 from:still to:moving dt_ms:60000
  @PERCEPT:before state:still t_ms:240010 window_ms:60010 n:1000 moving_permille:52 dev_mean_mg:22 dev_max_mg:739 moving_ms:3128 lane:@LAT95LON3
  @PERCEPT:after state:moving t_ms:300010 window_ms:60000 n:999 moving_permille:735 dev_mean_mg:227 dev_max_mg:1359 moving_ms:44107 lane:@LAT95LON4
**DELTA** edge:became d_permille:683 d_dev_mean_mg:205 d_dev_max_mg:620

---

@LAT93LON1 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON6,derived_from@LAT95LON7

**TRANSITION** t_ms:480012 synced:0 node:0x300 from:moving to:still dt_ms:60000
  @PERCEPT:before state:moving t_ms:420012 window_ms:60002 n:999 moving_permille:129 dev_mean_mg:34 dev_max_mg:809 moving_ms:7757 lane:@LAT95LON6
  @PERCEPT:after state:still t_ms:480012 window_ms:60000 n:999 moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0 lane:@LAT95LON7
**DELTA** edge:became d_permille:-129 d_dev_mean_mg:-25 d_dev_max_mg:-797

---

@LAT93LON2 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON33,derived_from@LAT95LON34

**TRANSITION** t_ms:422010 synced:0 node:0x300 from:still to:moving dt_ms:60010
  @PERCEPT:before state:still t_ms:362000 window_ms:60000 n:999 moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0 lane:@LAT95LON33
  @PERCEPT:after state:moving t_ms:422010 window_ms:60010 n:866 moving_permille:147 dev_mean_mg:35 dev_max_mg:652 moving_ms:7679 lane:@LAT95LON34
**DELTA** edge:became d_permille:147 d_dev_mean_mg:26 d_dev_max_mg:639

---

@LAT93LON3 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON34,derived_from@LAT95LON35

**TRANSITION** t_ms:482010 synced:0 node:0x300 from:moving to:still dt_ms:60000
  @PERCEPT:before state:moving t_ms:422010 window_ms:60010 n:866 moving_permille:147 dev_mean_mg:35 dev_max_mg:652 moving_ms:7679 lane:@LAT95LON34
  @PERCEPT:after state:still t_ms:482010 window_ms:60000 n:799 moving_permille:0 dev_mean_mg:15 dev_max_mg:18 moving_ms:0 lane:@LAT95LON35
**DELTA** edge:became d_permille:-147 d_dev_mean_mg:-20 d_dev_max_mg:-634

---

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON44,derived_from@LAT97LON28,senses@LAT0LON0

**OUTCOME** t_ms:122007 synced:0 node:0x300 acting:@LAT95LON44 observed_in:@LAT97LON28 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-37 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON1 | created:0 | updated:0 | relates:testifies_about@LAT95LON45,derived_from@LAT97LON29,senses@LAT0LON0

**OUTCOME** t_ms:182007 synced:0 node:0x300 acting:@LAT95LON45 observed_in:@LAT97LON29 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-37 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-53 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON2 | created:0 | updated:0 | relates:testifies_about@LAT95LON46,derived_from@LAT97LON30,senses@LAT0LON0

**OUTCOME** t_ms:242007 synced:0 node:0x300 acting:@LAT95LON46 observed_in:@LAT97LON30 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-37 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-53 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON3 | created:0 | updated:0 | relates:testifies_about@LAT95LON47,derived_from@LAT97LON31,senses@LAT0LON0

**OUTCOME** t_ms:302007 synced:0 node:0x300 acting:@LAT95LON47 observed_in:@LAT97LON31 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-37 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---


---

@LAT92LON4 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:120000 synced:0 node:0x300 acting:@LAT95LON0 observed_in:@LAT97LON1 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-37 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON5 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON2,senses@LAT0LON0

**OUTCOME** t_ms:180000 synced:0 node:0x300 acting:@LAT95LON1 observed_in:@LAT97LON2 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-37 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON6 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON3,senses@LAT0LON0

**OUTCOME** t_ms:240000 synced:0 node:0x300 acting:@LAT95LON2 observed_in:@LAT97LON3 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-41 delta:-4 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-56 delta:-3 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON7 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON4,senses@LAT0LON0

**OUTCOME** t_ms:300000 synced:0 node:0x300 acting:@LAT95LON3 observed_in:@LAT97LON4 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-41 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON8 | created:0 | updated:0 | relates:testifies_about@LAT95LON4,derived_from@LAT97LON5,senses@LAT0LON0

**OUTCOME** t_ms:360000 synced:0 node:0x300 acting:@LAT95LON4 observed_in:@LAT97LON5 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-42 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-56 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON9 | created:0 | updated:0 | relates:testifies_about@LAT95LON5,derived_from@LAT97LON6,senses@LAT0LON0

**OUTCOME** t_ms:422000 synced:0 node:0x300 acting:@LAT95LON5 observed_in:@LAT97LON6 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-42 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON10 | created:0 | updated:0 | relates:testifies_about@LAT95LON6,derived_from@LAT97LON7,senses@LAT0LON0

**OUTCOME** t_ms:482000 synced:0 node:0x300 acting:@LAT95LON6 observed_in:@LAT97LON7 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-43 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON11 | created:0 | updated:0 | relates:testifies_about@LAT95LON7,derived_from@LAT97LON8,senses@LAT0LON0

**OUTCOME** t_ms:542000 synced:0 node:0x300 acting:@LAT95LON7 observed_in:@LAT97LON8 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-44 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON12 | created:0 | updated:0 | relates:testifies_about@LAT95LON8,derived_from@LAT97LON9,senses@LAT0LON0

**OUTCOME** t_ms:602000 synced:0 node:0x300 acting:@LAT95LON8 observed_in:@LAT97LON9 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-44 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-43 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON13 | created:0 | updated:0 | relates:testifies_about@LAT95LON9,derived_from@LAT97LON10,senses@LAT0LON0

**OUTCOME** t_ms:662000 synced:0 node:0x300 acting:@LAT95LON9 observed_in:@LAT97LON10 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-42 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON14 | created:0 | updated:0 | relates:testifies_about@LAT95LON10,derived_from@LAT97LON11,senses@LAT0LON0

**OUTCOME** t_ms:722000 synced:0 node:0x300 acting:@LAT95LON10 observed_in:@LAT97LON11 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-44 delta:-2 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-56 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON15 | created:0 | updated:0 | relates:testifies_about@LAT95LON11,derived_from@LAT97LON12,senses@LAT0LON0

**OUTCOME** t_ms:782000 synced:0 node:0x300 acting:@LAT95LON11 observed_in:@LAT97LON12 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-44 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-43 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON16 | created:0 | updated:0 | relates:testifies_about@LAT95LON12,derived_from@LAT97LON13,senses@LAT0LON0

**OUTCOME** t_ms:842000 synced:0 node:0x300 acting:@LAT95LON12 observed_in:@LAT97LON13 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-40 delta:3 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---


---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-42 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-58 rssi_med:-55 rssi_max:-52

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60000 synced:0 window_ms:60000 n:824
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60000 synced:0 window_ms:60000 blocks:3086 rate:8000
**ACOUSTIC** rms_mean:93 rms_max:406 peak:1170 transients:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-59 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-42 rssi_med:-41 rssi_max:-39

---

@LAT92LON17 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:120000 synced:0 node:0x300 acting:@LAT95LON0 observed_in:@LAT97LON1 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-41 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:120000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:120000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:93 rms_max:350 peak:714 transients:0

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-90 rssi_med:-45 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:42 rssi_min:-95 rssi_med:-56 rssi_max:-53

---

@LAT92LON18 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON2,senses@LAT0LON0

**OUTCOME** t_ms:180000 synced:0 node:0x300 acting:@LAT95LON1 observed_in:@LAT97LON2 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-56 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-45 delta:-4 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:180000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:17 moving_ms:0

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:180000 synced:0 window_ms:60000 blocks:3731 rate:8000
**ACOUSTIC** rms_mean:155 rms_max:5341 peak:9586 transients:11
**TRANSIENT** t_ms:163276 rms:5341 synced:0

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-85 rssi_med:-83 rssi_max:-78
**LINK** peer:0x00000200 proto:ble n:14 rssi_min:-94 rssi_med:-93 rssi_max:-90

---

@LAT92LON19 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON3,senses@LAT0LON0

**OUTCOME** t_ms:240000 synced:0 node:0x300 acting:@LAT95LON2 observed_in:@LAT97LON3 band_dbm:6 met:0 violated:2 unobserved:0 streak:1
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-45 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-83 delta:-38 verdict:violated
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-93 delta:-37 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:240000 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:240000 synced:0 window_ms:60000 blocks:3726 rate:8000
**ACOUSTIC** rms_mean:85 rms_max:506 peak:1192 transients:0

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:11 rssi_min:-95 rssi_med:-92 rssi_max:-90
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-84 rssi_med:-83 rssi_max:-79

---

@LAT92LON20 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON4,senses@LAT0LON0

**OUTCOME** t_ms:300000 synced:0 node:0x300 acting:@LAT95LON3 observed_in:@LAT97LON4 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-83 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-83 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-93 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-92 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:300000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:300000 synced:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:84 rms_max:448 peak:750 transients:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-90 rssi_med:-82 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:17 rssi_min:-95 rssi_med:-86 rssi_max:-76

---

@LAT92LON21 | created:0 | updated:0 | relates:testifies_about@LAT95LON4,derived_from@LAT97LON5,senses@LAT0LON0

**OUTCOME** t_ms:360000 synced:0 node:0x300 acting:@LAT95LON4 observed_in:@LAT97LON5 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-92 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-86 delta:6 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-83 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-82 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:360000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:360000 synced:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:90 rms_max:1070 peak:1589 transients:0

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-85 rssi_med:-69 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-66 rssi_med:-54 rssi_max:-52

---

@LAT92LON22 | created:0 | updated:0 | relates:testifies_about@LAT95LON5,derived_from@LAT97LON6,senses@LAT0LON0

**OUTCOME** t_ms:420000 synced:0 node:0x300 acting:@LAT95LON5 observed_in:@LAT97LON6 band_dbm:6 met:0 violated:2 unobserved:0 streak:1
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-82 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-54 delta:28 verdict:violated
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-86 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-69 delta:17 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:420000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:420000 synced:0 window_ms:60000 blocks:3729 rate:8000
**ACOUSTIC** rms_mean:127 rms_max:3545 peak:12488 transients:4
**TRANSIENT** t_ms:385211 rms:3545 synced:0

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-78 rssi_med:-59 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-54 rssi_med:-50 rssi_max:-41

---

@LAT92LON23 | created:0 | updated:0 | relates:testifies_about@LAT95LON6,derived_from@LAT97LON7,senses@LAT0LON0

**OUTCOME** t_ms:480000 synced:0 node:0x300 acting:@LAT95LON6 observed_in:@LAT97LON7 band_dbm:6 met:1 violated:1 unobserved:0 streak:2
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-69 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-59 delta:10 verdict:violated
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-54 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-50 delta:4 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:480000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:480000 synced:0 window_ms:60000 blocks:3726 rate:8000
**ACOUSTIC** rms_mean:96 rms_max:945 peak:3272 transients:1
**TRANSIENT** t_ms:443524 rms:945 synced:0

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-62 rssi_med:-56 rssi_max:-51

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:540000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:540000 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:113 rms_max:2058 peak:2234 transients:3
**TRANSIENT** t_ms:514421 rms:1109 synced:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-62 rssi_med:-56 rssi_max:-51

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:600000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:600000 synced:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:94 rms_max:1510 peak:1687 transients:2
**TRANSIENT** t_ms:595152 rms:1510 synced:0

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:619373 synced:0 window_ms:559373 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-63 rssi_med:-56 rssi_max:-51

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:660000 synced:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:660000 synced:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:91 rms_max:409 peak:673 transients:0
