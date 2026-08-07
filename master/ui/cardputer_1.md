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

@LAT99LON0 | created:1785774270 | updated:1785774270 | relates:logs@LAT0LON0

**SYNC** id:8 t_ms:1785774270662 recv_ms:4040166 offset_ms:1785770230496

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:418673 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:1 removed:48 last_lon:47 t_ms:1683303 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:1 removed:48 last_lon:47 t_ms:1688500 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:1 removed:16 last_lon:15 t_ms:1438863 stream:0xe7384824 wall:0 node:0x00000300
**STREAMS-EXPLAINED** n:12 0x0ad62c42 0xfc36a38c 0x10578c80 0x26a1b82d 0x44574814 0x59fb8ce8 0x450f0e1c 0x2434b81f 0xbdc62024 0x1428c702 0xa315ec7d 0x9c462b30

---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:2 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON5 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:2 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON6 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON7 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:2 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---


---


---

@LAT100LON8 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:92 gen:1 removed:24 last_lon:23 t_ms:8137821 stream:0xbe6d9616 wall:0 node:0x00000300
**OUTCOMES-CARRIED** records:24 windows_max:24 beliefs:8 met:167 violated:14 unobserved:2 baseline_conf:128 rule:+2/-16
**BELIEF-AT-BOUNDARY** peer:0x00000010 proto:ble conf:176 sal:0 met:24 violated:0 unobserved:0 max_streak:0 contradiction:0
**BELIEF-AT-BOUNDARY** peer:0x00000012 proto:ble conf:176 sal:0 met:24 violated:0 unobserved:0 max_streak:0 contradiction:0
**BELIEF-AT-BOUNDARY** peer:0x00000011 proto:ble conf:176 sal:0 met:24 violated:0 unobserved:0 max_streak:0 contradiction:0
**BELIEF-AT-BOUNDARY** peer:0x00000011 proto:espnow conf:176 sal:0 met:24 violated:0 unobserved:0 max_streak:0 contradiction:0
**BELIEF-AT-BOUNDARY** peer:0x00000012 proto:espnow conf:158 sal:8 met:23 violated:1 unobserved:0 max_streak:1 contradiction:0
**BELIEF-AT-BOUNDARY** peer:0x00000200 proto:ble conf:64 sal:40 met:8 violated:5 unobserved:2 max_streak:2 contradiction:1
**BELIEF-AT-BOUNDARY** peer:0x00000200 proto:espnow conf:50 sal:56 met:17 violated:7 unobserved:0 max_streak:2 contradiction:1
**BELIEF-AT-BOUNDARY** peer:0x00000010 proto:espnow conf:158 sal:8 met:23 violated:1 unobserved:0 max_streak:1 contradiction:0

---

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON18,senses@LAT0LON0

**OUTCOME** t_ms:8260961 stream:0xbe6d9616 wall:0 node:0x300 acting:@LAT95LON2+0 observed_in:@LAT97LON18 band_dbm:6 met:3 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-37 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-56 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-38 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT100LON9 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:3 removed:48 last_lon:47 t_ms:18643636 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON10 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:3 removed:11 last_lon:10 t_ms:18643636 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON11 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:2 removed:23 last_lon:22 t_ms:18643636 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON12 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:3 removed:48 last_lon:47 t_ms:18643636 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT92LON1 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:18764845 stream:0xbe6d9616 wall:0 node:0x300 acting:@LAT95LON0+0 observed_in:@LAT97LON1 band_dbm:6 met:2 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-43 delta:-3 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-63 delta:-8 verdict:violated
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-45 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-48 delta:-3 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON2 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON2,senses@LAT0LON0

**OUTCOME** t_ms:18824845 stream:0xbe6d9616 wall:0 node:0x300 acting:@LAT95LON0+1 observed_in:@LAT97LON2 band_dbm:6 met:3 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-44 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-63 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-62 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-48 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON3 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON32,senses@LAT0LON0

**OUTCOME** t_ms:20624845 stream:0xbe6d9616 wall:0 node:0x300 acting:@LAT95LON1+1 observed_in:@LAT97LON32 band_dbm:6 met:3 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED-SPAN** windows:29 first_t_ms:18884845 last_t_ms:20564845 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000010 proto:ble verdict:met windows:29 observed_min:-64 observed_max:-61
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:29 observed_min:-49 observed_max:-47
**COVERED** peer:0x00000100 proto:espnow verdict:met windows:29 observed_min:-45 observed_max:-42
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-62 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-61 delta:1 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-44 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-47 delta:-3 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-47 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON4 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON34,senses@LAT0LON0

**OUTCOME** t_ms:20744845 stream:0xbe6d9616 wall:0 node:0x300 acting:@LAT95LON1+3 observed_in:@LAT97LON34 band_dbm:6 met:2 violated:0 unobserved:1 streak:0
**RUN** windows_since_last:2 reason:changed max_run:30
**COVERED-SPAN** windows:1 first_t_ms:20684845 last_t_ms:20684845 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000100 proto:espnow verdict:met windows:1 observed_min:-44 observed_max:-44
**COVERED** peer:0x00000010 proto:ble verdict:met windows:1 observed_min:-61 observed_max:-61
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:1 observed_min:-47 observed_max:-47
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-61 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-62 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000010 proto:espnow verdict:unobserved
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-44 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-44 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON5 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON35,senses@LAT0LON0

**OUTCOME** t_ms:20804845 stream:0xbe6d9616 wall:0 node:0x300 acting:@LAT95LON1+4 observed_in:@LAT97LON35 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-44 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-44 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-62 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-62 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON6 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON44,senses@LAT0LON0

**OUTCOME** t_ms:110132 stream:0x6a2120c2 wall:0 node:0x300 acting:@LAT95LON2+0 observed_in:@LAT97LON44 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-47 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON7 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON46,senses@LAT0LON0

**OUTCOME** t_ms:230146 stream:0x6a2120c2 wall:0 node:0x300 acting:@LAT95LON2+2 observed_in:@LAT97LON46 band_dbm:6 met:3 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:2 reason:changed max_run:30
**COVERED-SPAN** windows:1 first_t_ms:170140 last_t_ms:170140 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000100 proto:espnow verdict:met windows:1 observed_min:-49 observed_max:-49
**COVERED** peer:0x00000010 proto:ble verdict:met windows:1 observed_min:-54 observed_max:-54
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-54 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:1 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-49 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-45 delta:4 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-34 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-35 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT100LON13 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:4 removed:48 last_lon:47 t_ms:16016341 stream:0x946fea42 wall:0 node:0x00000300

---

@LAT100LON14 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:4 removed:21 last_lon:20 t_ms:16016341 stream:0x946fea42 wall:0 node:0x00000300

---

@LAT100LON15 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:3 removed:45 last_lon:44 t_ms:16016341 stream:0x946fea42 wall:0 node:0x00000300

---

@LAT100LON16 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:4 removed:48 last_lon:47 t_ms:16016341 stream:0x946fea42 wall:0 node:0x00000300

---

@LAT100LON17 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:2 removed:15 last_lon:14 t_ms:0 stream:0x00000000 wall:0 node:0x00000300
**STREAMS-EXPLAINED** n:12 0xe7384824 0xaf869fce 0x161e88ac 0x5f6eb232 0x41ba1242 0x67ec2883 0x3ab84e5a 0xbe6d9616 0x6a2120c2 0xdffbae31 0x185f5a4b 0x946fea42

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xe334a7e1 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:50187 stream:0xe334a7e1 wall:0 window_ms:62000
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-82 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-44 rssi_med:-43 rssi_max:-42

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:50187 stream:0xe334a7e1 wall:0 window_ms:62000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:50187 stream:0xe334a7e1 wall:0 window_ms:62000 n:430
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:50187 stream:0xe334a7e1 wall:0 window_ms:62000 blocks:1605 rate:8000
**ACOUSTIC** rms_mean:79 rms_max:187 peak:361 transients:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:110192 stream:0xe334a7e1 wall:0 window_ms:60005
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-57 rssi_med:-44 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-70 rssi_med:-57 rssi_max:-50

---

@LAT92LON8 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:110192 stream:0xe334a7e1 wall:0 node:0x300 acting:@LAT95LON0+0 observed_in:@LAT97LON1 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-57 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-44 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:110192 stream:0xe334a7e1 wall:0 window_ms:60005 blocks:2476 rate:8000
**ACOUSTIC** rms_mean:84 rms_max:671 peak:2362 transients:0

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:170192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-56 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-58 rssi_med:-40 rssi_max:-19

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:170192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3186 rate:8000
**ACOUSTIC** rms_mean:200 rms_max:19661 peak:32768 transients:28
**TRANSIENT** t_ms:145833 stream:0xe334a7e1 wall:0 rms:19661

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:230192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT92LON9 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON3,senses@LAT0LON0

**OUTCOME** t_ms:230192 stream:0xe334a7e1 wall:0 node:0x300 acting:@LAT95LON0+2 observed_in:@LAT97LON3 band_dbm:6 met:0 violated:2 unobserved:0 streak:1
**RUN** windows_since_last:2 reason:changed max_run:30
**COVERED-SPAN** windows:1 first_t_ms:170192 last_t_ms:170192 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:1 observed_min:-40 observed_max:-40
**COVERED** peer:0x00000010 proto:ble verdict:met windows:1 observed_min:-56 observed_max:-56
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-35 delta:21 verdict:violated
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-19 delta:21 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:230192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3705 rate:8000
**ACOUSTIC** rms_mean:90 rms_max:262 peak:962 transients:0

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:290192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-41 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-21 rssi_med:-20 rssi_max:-18

---

@LAT92LON10 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON4,senses@LAT0LON0

**OUTCOME** t_ms:290192 stream:0xe334a7e1 wall:0 node:0x300 acting:@LAT95LON0+3 observed_in:@LAT97LON4 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-35 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-35 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-19 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-20 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:290192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:89 rms_max:305 peak:590 transients:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:350192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-41 rssi_med:-35 rssi_max:-34

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:350192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:101 rms_max:1310 peak:4415 transients:2
**TRANSIENT** t_ms:338067 stream:0xe334a7e1 wall:0 rms:1310

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:410192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:410192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3700 rate:8000
**ACOUSTIC** rms_mean:99 rms_max:513 peak:1707 transients:0

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:470192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-20 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-41 rssi_med:-35 rssi_max:-33

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:470192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3736 rate:8000
**ACOUSTIC** rms_mean:87 rms_max:558 peak:1146 transients:0

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:530192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-35 rssi_max:-33

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:530192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:114 rms_max:1224 peak:4440 transients:4
**TRANSIENT** t_ms:486466 stream:0xe334a7e1 wall:0 rms:1224

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:590192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-41 rssi_med:-35 rssi_max:-33

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:590192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:109 rms_max:1305 peak:2372 transients:0

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:623286 stream:0xe334a7e1 wall:0 window_ms:573099 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:650192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:650192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3739 rate:8000
**ACOUSTIC** rms_mean:100 rms_max:306 peak:934 transients:0

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:710192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-35 rssi_max:-33

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:710192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:105 rms_max:300 peak:797 transients:0

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:770192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-41 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:770192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:100 rms_max:440 peak:1130 transients:0

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:830192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-21 rssi_med:-19 rssi_max:-18

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:830192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3739 rate:8000
**ACOUSTIC** rms_mean:169 rms_max:1949 peak:4197 transients:2
**TRANSIENT** t_ms:780207 stream:0xe334a7e1 wall:0 rms:1750

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:890192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-20 rssi_med:-20 rssi_max:-19

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:890192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:160 rms_max:315 peak:785 transients:0

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:950192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-21 rssi_med:-20 rssi_max:-19

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:950192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:159 rms_max:326 peak:737 transients:0

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1010192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-21 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-42 rssi_med:-35 rssi_max:-34

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1010192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3738 rate:8000
**ACOUSTIC** rms_mean:165 rms_max:316 peak:718 transients:0

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1070192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-21 rssi_med:-20 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-42 rssi_med:-35 rssi_max:-34

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1070192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3739 rate:8000
**ACOUSTIC** rms_mean:175 rms_max:592 peak:1121 transients:0

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1130192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-20 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-41 rssi_med:-35 rssi_max:-34

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1130192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3731 rate:8000
**ACOUSTIC** rms_mean:187 rms_max:3429 peak:3784 transients:5
**TRANSIENT** t_ms:1106274 stream:0xe334a7e1 wall:0 rms:2127

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1190192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-21 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-35 rssi_max:-34

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1190192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3732 rate:8000
**ACOUSTIC** rms_mean:200 rms_max:6238 peak:7165 transients:9
**TRANSIENT** t_ms:1161963 stream:0xe334a7e1 wall:0 rms:4793

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1223286 stream:0xe334a7e1 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1250192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-20 rssi_med:-19 rssi_max:-19

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1250192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:174 rms_max:1156 peak:1662 transients:1
**TRANSIENT** t_ms:1217713 stream:0xe334a7e1 wall:0 rms:995

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1310192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-79 rssi_med:-35 rssi_max:-33

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1310192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3738 rate:8000
**ACOUSTIC** rms_mean:260 rms_max:14915 peak:17503 transients:18
**TRANSIENT** t_ms:1296141 stream:0xe334a7e1 wall:0 rms:14526

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1370192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:70 rssi_min:-79 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1370192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:227 rms_max:12281 peak:13780 transients:12
**TRANSIENT** t_ms:1313227 stream:0xe334a7e1 wall:0 rms:10104

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1430192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-41 rssi_med:-35 rssi_max:-34

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1430192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3743 rate:8000
**ACOUSTIC** rms_mean:112 rms_max:1984 peak:3460 transients:3
**TRANSIENT** t_ms:1372293 stream:0xe334a7e1 wall:0 rms:1984

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1490192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-41 rssi_med:-35 rssi_max:-34

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1490192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3736 rate:8000
**ACOUSTIC** rms_mean:110 rms_max:1217 peak:2322 transients:2
**TRANSIENT** t_ms:1481375 stream:0xe334a7e1 wall:0 rms:1217

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1550192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1550192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:120 rms_max:1643 peak:2832 transients:1
**TRANSIENT** t_ms:1546525 stream:0xe334a7e1 wall:0 rms:926

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1610192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-41 rssi_med:-35 rssi_max:-34

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1610192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3729 rate:8000
**ACOUSTIC** rms_mean:146 rms_max:2355 peak:6618 transients:3
**TRANSIENT** t_ms:1587935 stream:0xe334a7e1 wall:0 rms:2355

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1670192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-35 rssi_max:-34

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1670192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:169 rms_max:1333 peak:3065 transients:4
**TRANSIENT** t_ms:1665347 stream:0xe334a7e1 wall:0 rms:1333

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1730192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1730192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3745 rate:8000
**ACOUSTIC** rms_mean:127 rms_max:2764 peak:8307 transients:4
**TRANSIENT** t_ms:1697668 stream:0xe334a7e1 wall:0 rms:2764

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1790192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-41 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1790192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3738 rate:8000
**ACOUSTIC** rms_mean:93 rms_max:508 peak:2131 transients:0

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1823286 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1850192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-21 rssi_med:-19 rssi_max:-18

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1850192 stream:0xe334a7e1 wall:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28430 window_ms:1740005 moving_permille:2 dev_mean_mg:9 dev_max_mg:547 moving_ms:4563 first_t_ms:110192 last_t_ms:1790192 covered_by:@LAT95LON0

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1850192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:104 rms_max:495 peak:939 transients:0

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1910192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-41 rssi_med:-35 rssi_max:-34

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1910192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:118 rms_max:2782 peak:6736 transients:3
**TRANSIENT** t_ms:1851367 stream:0xe334a7e1 wall:0 rms:2782

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1970192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-79 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1970192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:123 rms_max:1195 peak:2787 transients:6
**TRANSIENT** t_ms:1929542 stream:0xe334a7e1 wall:0 rms:1195

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2030192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-80 rssi_med:-35 rssi_max:-34

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2030192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3728 rate:8000
**ACOUSTIC** rms_mean:124 rms_max:453 peak:816 transients:0

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2090192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-80 rssi_med:-35 rssi_max:-33

---

@LAT92LON11 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON34,senses@LAT0LON0

**OUTCOME** t_ms:2090192 stream:0xe334a7e1 wall:0 node:0x300 acting:@LAT95LON1+3 observed_in:@LAT97LON34 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED-SPAN** windows:29 first_t_ms:350192 last_t_ms:2030192 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000010 proto:ble verdict:met windows:29 observed_min:-35 observed_max:-34
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:29 observed_min:-20 observed_max:-19
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-19 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-19 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-35 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-35 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON34 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2090192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3740 rate:8000
**ACOUSTIC** rms_mean:118 rms_max:449 peak:900 transients:0

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2150192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-41 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-21 rssi_med:-19 rssi_max:-18

---

@LAT94LON35 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2150192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3739 rate:8000
**ACOUSTIC** rms_mean:190 rms_max:8968 peak:9532 transients:14
**TRANSIENT** t_ms:2144376 stream:0xe334a7e1 wall:0 rms:5398

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2210192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-21 rssi_med:-19 rssi_max:-18

---

@LAT94LON36 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2210192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3583 rate:8000
**ACOUSTIC** rms_mean:154 rms_max:6004 peak:7171 transients:12
**TRANSIENT** t_ms:2194809 stream:0xe334a7e1 wall:0 rms:6004

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2270192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-35 rssi_max:-34

---

@LAT94LON37 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2270192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3671 rate:8000
**ACOUSTIC** rms_mean:110 rms_max:275 peak:545 transients:0

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2330192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-41 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-20 rssi_med:-19 rssi_max:-19

---

@LAT94LON38 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2330192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3644 rate:8000
**ACOUSTIC** rms_mean:203 rms_max:6934 peak:7949 transients:10
**TRANSIENT** t_ms:2328252 stream:0xe334a7e1 wall:0 rms:6934

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2390192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-41 rssi_med:-35 rssi_max:-34

---

@LAT94LON39 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2390192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3645 rate:8000
**ACOUSTIC** rms_mean:178 rms_max:4177 peak:6600 transients:24
**TRANSIENT** t_ms:2336573 stream:0xe334a7e1 wall:0 rms:4177

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2423285 stream:0xe334a7e1 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2450192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-41 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-21 rssi_med:-19 rssi_max:-18

---

@LAT94LON40 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2450192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3648 rate:8000
**ACOUSTIC** rms_mean:297 rms_max:5455 peak:11373 transients:3
**TRANSIENT** t_ms:2429311 stream:0xe334a7e1 wall:0 rms:3880

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2510192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-41 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON41 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2510192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3651 rate:8000
**ACOUSTIC** rms_mean:337 rms_max:2775 peak:3404 transients:5
**TRANSIENT** t_ms:2485921 stream:0xe334a7e1 wall:0 rms:1921

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2570192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON42 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2570192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3630 rate:8000
**ACOUSTIC** rms_mean:325 rms_max:2191 peak:3691 transients:6
**TRANSIENT** t_ms:2527002 stream:0xe334a7e1 wall:0 rms:2191

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2630192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON43 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2630192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3645 rate:8000
**ACOUSTIC** rms_mean:353 rms_max:8810 peak:10431 transients:7
**TRANSIENT** t_ms:2602143 stream:0xe334a7e1 wall:0 rms:8593

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2690192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-21 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-35 rssi_max:-33

---

@LAT94LON44 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2690192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3628 rate:8000
**ACOUSTIC** rms_mean:302 rms_max:682 peak:1247 transients:0

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2750192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-41 rssi_med:-35 rssi_max:-34

---

@LAT94LON45 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2750192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3594 rate:8000
**ACOUSTIC** rms_mean:204 rms_max:498 peak:959 transients:0

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2810192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-41 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON46 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2810192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3632 rate:8000
**ACOUSTIC** rms_mean:198 rms_max:949 peak:1763 transients:1
**TRANSIENT** t_ms:2771689 stream:0xe334a7e1 wall:0 rms:949

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2870192 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT94LON47 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2870192 stream:0xe334a7e1 wall:0 window_ms:60000 blocks:3636 rate:8000
**ACOUSTIC** rms_mean:197 rms_max:367 peak:870 transients:0

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3023284 stream:0xe334a7e1 wall:0 window_ms:599999 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3710811 stream:0xe334a7e1 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3710811 stream:0xe334a7e1 wall:0 window_ms:60000 n:948
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4262683 stream:0xe334a7e1 wall:0 window_ms:551872 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4862682 stream:0xe334a7e1 wall:0 window_ms:599999 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5462683 stream:0xe334a7e1 wall:0 window_ms:600001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5510812 stream:0xe334a7e1 wall:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:19 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28978 window_ms:1740001 moving_permille:0 dev_mean_mg:9 dev_max_mg:28 moving_ms:0 first_t_ms:3770811 last_t_ms:5450812 covered_by:@LAT95LON2

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6062681 stream:0xe334a7e1 wall:0 window_ms:599998 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6662682 stream:0xe334a7e1 wall:0 window_ms:600001 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7133588 stream:0xe334a7e1 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7133588 stream:0xe334a7e1 wall:0 window_ms:60000 n:949
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7685427 stream:0xe334a7e1 wall:0 window_ms:551839 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8285427 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8885425 stream:0xe334a7e1 wall:0 window_ms:599998 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:8933588 stream:0xe334a7e1 wall:0 window_ms:60000 n:986
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28943 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:15 moving_ms:0 first_t_ms:7193588 last_t_ms:8873588 covered_by:@LAT95LON4

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9485425 stream:0xe334a7e1 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xe334a7e1 wall:0 t_ms:9806368 node:0x300 from:0x10
**REMAP** prev_stream:0xa817d5d2 prev_t_ms:5064 offset_ms:9801304 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9853632 stream:0xe334a7e1 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:9853632 stream:0xe334a7e1 wall:0 window_ms:60000 n:951
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10405380 stream:0xe334a7e1 wall:0 window_ms:551748 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11005380 stream:0xe334a7e1 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11605379 stream:0xe334a7e1 wall:0 window_ms:599999 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:11653632 stream:0xe334a7e1 wall:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28968 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:33 moving_ms:0 first_t_ms:9913632 last_t_ms:11593632 covered_by:@LAT95LON6

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12205378 stream:0xe334a7e1 wall:0 window_ms:599999 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12805378 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13405379 stream:0xe334a7e1 wall:0 window_ms:600001 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13816134 stream:0xe334a7e1 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:13816134 stream:0xe334a7e1 wall:0 window_ms:60000 n:950
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:14367929 stream:0xe334a7e1 wall:0 window_ms:551795 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:14967928 stream:0xe334a7e1 wall:0 window_ms:599999 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:15567929 stream:0xe334a7e1 wall:0 window_ms:600001 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:15616135 stream:0xe334a7e1 wall:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28974 window_ms:1740001 moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0 first_t_ms:13876134 last_t_ms:15556135 covered_by:@LAT95LON8

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:16167927 stream:0xe334a7e1 wall:0 window_ms:599998 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:16767927 stream:0xe334a7e1 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:17287463 stream:0xe334a7e1 wall:0 window_ms:60000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:17287463 stream:0xe334a7e1 wall:0 window_ms:60000 n:952
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:17839167 stream:0xe334a7e1 wall:0 window_ms:551704 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:18439168 stream:0xe334a7e1 wall:0 window_ms:600001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:19039167 stream:0xe334a7e1 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:19087463 stream:0xe334a7e1 wall:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28979 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:18 moving_ms:0 first_t_ms:17347463 last_t_ms:19027463 covered_by:@LAT95LON10

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:19639167 stream:0xe334a7e1 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xe334a7e1 wall:0 t_ms:20274368 node:0x300 from:0x10
**REMAP** prev_stream:0x4bb5ccdb prev_t_ms:7515 offset_ms:20266853 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:20318710 stream:0xe334a7e1 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:20318710 stream:0xe334a7e1 wall:0 window_ms:60000 n:938
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:20871218 stream:0xe334a7e1 wall:0 window_ms:552508 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:21471218 stream:0xe334a7e1 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:22071218 stream:0xe334a7e1 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:22118710 stream:0xe334a7e1 wall:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28975 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:16 moving_ms:0 first_t_ms:20378710 last_t_ms:22058710 covered_by:@LAT95LON12

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:22671216 stream:0xe334a7e1 wall:0 window_ms:599998 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:23271217 stream:0xe334a7e1 wall:0 window_ms:600001 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbe8a1293 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:51885 stream:0xbe8a1293 wall:0 window_ms:60001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51885 stream:0xbe8a1293 wall:0 window_ms:60001 n:937
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:35 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:604420 stream:0xbe8a1293 wall:0 window_ms:552535 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1204420 stream:0xbe8a1293 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1804420 stream:0xbe8a1293 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1851887 stream:0xbe8a1293 wall:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28973 window_ms:1740002 moving_permille:0 dev_mean_mg:9 dev_max_mg:29 moving_ms:0 first_t_ms:111885 last_t_ms:1791887 covered_by:@LAT95LON14

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2404419 stream:0xbe8a1293 wall:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3031304 stream:0xbe8a1293 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3031304 stream:0xbe8a1293 wall:0 window_ms:60000 n:940
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:20 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3583693 stream:0xbe8a1293 wall:0 window_ms:552389 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4831305 stream:0xbe8a1293 wall:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28980 window_ms:1740001 moving_permille:0 dev_mean_mg:9 dev_max_mg:42 moving_ms:0 first_t_ms:3091304 last_t_ms:4771305 covered_by:@LAT95LON16

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbe8a1293 wall:0 t_ms:5687407 node:0x300 from:0x10
**REMAP** prev_stream:0xcabf8b87 prev_t_ms:5351 offset_ms:5682056 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5734286 stream:0xbe8a1293 wall:0 window_ms:60000 n:944
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7534286 stream:0xbe8a1293 wall:0 window_ms:60000 n:999
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:27 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28975 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:22 moving_ms:0 first_t_ms:5794286 last_t_ms:7474286 covered_by:@LAT95LON18

---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7594286 stream:0xbe8a1293 wall:0 window_ms:60000 n:997
**MOTION** state:moving moving_permille:172 dev_mean_mg:40 dev_max_mg:1261 moving_ms:10339
**RUN** windows_since_last:1 reason:changed max_run:30

---

@LAT93LON0 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON19,derived_from@LAT95LON20

**TRANSITION** t_ms:7594286 stream:0xbe8a1293 wall:0 node:0x300 from:still to:moving dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:still t_ms:7534286 window_ms:60000 n:999 moving                                                                                                                                                                                                           lane:@LAT95LON20+0
**DELTA** edge:became d_permille:172 d_dev_mean_mg:31 d_dev_max_mg:1234

---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7679097 stream:0xbe8a1293 wall:0 window_ms:60000 n:934
**MOTION** state:still moving_permille:3 dev_mean_mg:9 dev_max_mg:77 moving_ms:180
**RUN** windows_since_last:1 reason:first max_run:30

---


---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7808842 stream:0xbe8a1293 wall:0 window_ms:62000 n:438
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:19 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:8153414 stream:0xbe8a1293 wall:0 window_ms:60000 n:946
**MOTION** state:still moving_permille:41 dev_mean_mg:16 dev_max_mg:896 moving_ms:2341
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:9344247 stream:0xbe8a1293 wall:0 window_ms:62000 n:442
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:11144364 stream:0xbe8a1293 wall:0 window_ms:60000 n:852
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:26618 window_ms:1740117 moving_permille:0 dev_mean_mg:9 dev_max_mg:110 moving_ms:540 first_t_ms:9404248 last_t_ms:11084364 covered_by:@LAT95LON24

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:11335129 stream:0xbe8a1293 wall:0 window_ms:60000 n:932
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xa1dd036e wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51862 stream:0xa1dd036e wall:0 window_ms:60000 n:934
**MOTION** state:still moving_permille:48 dev_mean_mg:17 dev_max_mg:692 moving_ms:3140
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xe61efa15 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON28 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52218 stream:0xe61efa15 wall:0 window_ms:60000 n:942
**MOTION** state:still moving_permille:13 dev_mean_mg:13 dev_max_mg:505 moving_ms:788
**RUN** windows_since_last:1 reason:first max_                                                                                                                                                                                                          :9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28983 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:15 moving_ms:0 first_t_ms:112218 last_t_ms:1792218 covered_by:@LAT95LON28

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x569630d1 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON30 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51851 stream:0x569630d1 wall:0 window_ms:60000 n:932
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON31 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1851851 stream:0x569630d1 wall:0 window_ms:60000 n:999
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28977 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:16 moving_ms:0 first_t_ms:111851 last_t_ms:1791851 covered_by:@LAT95LON30

---

@LAT95LON32 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3651851 stream:0x569630d1 wall:0 window_ms:60000 n:983
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28800 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0 first_t_ms:1911851 last_t_ms:3591851 covered_by:@LAT95LON31

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x41877b36 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON33 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52128 stream:0x41877b36 wall:0 window_ms:60000 n:939
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON34 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1852128 stream:0x41877b36 wall:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:25 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28983 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:14 moving_ms:0 first_t_ms:112128 last_t_ms:1792128 covered_by:@LAT95LON33

---


---

@LAT91LON0 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:206
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000100 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:39 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON1 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:238
rev:1
sal:16
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:71 violated:2 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON2 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:248
rev:1
sal:8
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:68 violated:1 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x9929f0cc wall:0 t_ms:73211 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT95LON35 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:130469 stream:0x9929f0cc wall:0 window_ms:60000 n:941
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30
