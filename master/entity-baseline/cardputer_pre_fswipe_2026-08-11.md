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

@LAT92LON8 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:110192 stream:0xe334a7e1 wall:0 node:0x300 acting:@LAT95LON0+0 observed_in:@LAT97LON1 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-57 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-44 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

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

@LAT92LON10 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON4,senses@LAT0LON0

**OUTCOME** t_ms:290192 stream:0xe334a7e1 wall:0 node:0x300 acting:@LAT95LON0+3 observed_in:@LAT97LON4 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-35 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-35 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-19 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-20 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

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

@LAT93LON0 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON19,derived_from@LAT95LON20

**TRANSITION** t_ms:7594286 stream:0xbe8a1293 wall:0 node:0x300 from:still to:moving dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:still t_ms:7534286 window_ms:60000 n:999 moving_permille:0 dev_mean_mg:9 dev_max_mg:27 moving_ms:0 lane:@LAT95LON19+0
  @PERCEPT:after state:moving t_ms:7594286 window_ms:60000 n:997 moving_permille:172 dev_mean_mg:40 dev_max_mg:1261 moving_ms:10339 lane:@LAT95LON20+0
**DELTA** edge:became d_permille:172 d_dev_mean_mg:31 d_dev_max_mg:1234

---

@LAT100LON18 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:5 removed:48 last_lon:47 t_ms:318020 stream:0xf796e624 wall:0 node:0x00000300

---

@LAT100LON19 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:5 removed:38 last_lon:37 t_ms:318020 stream:0xf796e624 wall:0 node:0x00000300

---

@LAT100LON20 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:4 removed:48 last_lon:47 t_ms:318020 stream:0xf796e624 wall:0 node:0x00000300

---

@LAT100LON21 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:5 removed:48 last_lon:47 t_ms:318020 stream:0xf796e624 wall:0 node:0x00000300

---

@LAT100LON22 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:3 removed:11 last_lon:10 t_ms:0 stream:0x00000000 wall:0 node:0x00000300
**STREAMS-EXPLAINED** n:8 0xe334a7e1 0xbe8a1293 0xa1dd036e 0xe61efa15 0x569630d1 0x41877b36 0x9929f0cc 0xf796e624

---

@LAT92LON12 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:107859 stream:0xc8a01245 wall:0 node:0x300 acting:@LAT95LON0+0 observed_in:@LAT97LON1 band_dbm:6 met:0 violated:2 unobserved:0 streak:1
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-44 delta:9 verdict:violated
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-35 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-25 delta:10 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT93LON1 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON0,derived_from@LAT95LON1

**TRANSITION** t_ms:107859 stream:0xc8a01245 wall:0 node:0x300 from:still to:moving dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:still t_ms:47859 window_ms:60000 n:453 moving_permille:90 dev_mean_mg:27 dev_max_mg:411 moving_ms:2460 lane:@LAT95LON0+0
  @PERCEPT:after state:moving t_ms:107859 window_ms:60000 n:996 moving_permille:143 dev_mean_mg:40 dev_max_mg:774 moving_ms:8750 lane:@LAT95LON1+0
**DELTA** edge:became d_permille:53 d_dev_mean_mg:13 d_dev_max_mg:363

---

@LAT93LON2 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON1,derived_from@LAT95LON2

**TRANSITION** t_ms:167859 stream:0xc8a01245 wall:0 node:0x300 from:moving to:still dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:moving t_ms:107859 window_ms:60000 n:996 moving_permille:143 dev_mean_mg:40 dev_max_mg:774 moving_ms:8750 lane:@LAT95LON1+0
  @PERCEPT:after state:still t_ms:167859 window_ms:60000 n:995 moving_permille:0 dev_mean_mg:9 dev_max_mg:16 moving_ms:0 lane:@LAT95LON2+0
**DELTA** edge:became d_permille:-143 d_dev_mean_mg:-31 d_dev_max_mg:-758

---

@LAT92LON13 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON3,senses@LAT0LON0

**OUTCOME** t_ms:227863 stream:0xc8a01245 wall:0 node:0x300 acting:@LAT95LON2+0 observed_in:@LAT97LON3 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-40 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-40 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-24 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-24 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON14 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON33,senses@LAT0LON0

**OUTCOME** t_ms:2027876 stream:0xc8a01245 wall:0 node:0x300 acting:@LAT95LON3+0 observed_in:@LAT97LON33 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED-SPAN** windows:29 first_t_ms:287863 last_t_ms:1967863 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000010 proto:ble verdict:met windows:29 observed_min:-44 observed_max:-38
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:29 observed_min:-24 observed_max:-23
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-38 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-38 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-23 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-23 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON15 | created:0 | updated:0 | relates:testifies_about@LAT95LON4,derived_from@LAT97LON37,senses@LAT0LON0

**OUTCOME** t_ms:2280666 stream:0xc8a01245 wall:0 node:0x300 acting:@LAT95LON4+0 observed_in:@LAT97LON37 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-23 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-23 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-38 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-38 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT93LON3 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON28,derived_from@LAT95LON29

**TRANSITION** t_ms:16686578 stream:0xe6a101ec wall:0 node:0x300 from:still to:moving dt_ms:62000 dt_across_merge:0
  @PERCEPT:before state:still t_ms:16624578 window_ms:60000 n:999 moving_permille:0 dev_mean_mg:9 dev_max_mg:18 moving_ms:0 lane:@LAT95LON28+3
  @PERCEPT:after state:moving t_ms:16686578 window_ms:62000 n:1001 moving_permille:119 dev_mean_mg:33 dev_max_mg:690 moving_ms:7200 lane:@LAT95LON29+0
**DELTA** edge:became d_permille:119 d_dev_mean_mg:24 d_dev_max_mg:672

---

@LAT100LON23 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:6 removed:48 last_lon:47 t_ms:16707848 stream:0xe6a101ec wall:0 node:0x00000300

---

@LAT100LON24 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:6 removed:30 last_lon:29 t_ms:16707848 stream:0xe6a101ec wall:0 node:0x00000300

---

@LAT100LON25 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:5 removed:48 last_lon:47 t_ms:16707848 stream:0xe6a101ec wall:0 node:0x00000300

---

@LAT100LON26 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:6 removed:48 last_lon:47 t_ms:16707848 stream:0xe6a101ec wall:0 node:0x00000300

---

@LAT100LON27 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:4 removed:6 last_lon:5 t_ms:16721065 stream:0xe6a101ec wall:0 node:0x00000300
**STREAMS-EXPLAINED** n:2 0xc8a01245 0xe6a101ec

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xe6a101ec wall:0 t_ms:16729479 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---


---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:16796247 stream:0xe6a101ec wall:0 window_ms:62001
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-70 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-64 rssi_med:-56 rssi_max:-50

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:16796247 stream:0xe6a101ec wall:0 window_ms:62001 blocks:1721 rate:8000
**ACOUSTIC** rms_mean:429 rms_max:7942 peak:17874 transients:28
**TRANSIENT** t_ms:16768368 stream:0xe6a101ec wall:0 rms:7942

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:16872443 stream:0xe6a101ec wall:0 window_ms:62000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-63 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-80 rssi_med:-72 rssi_max:-57

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:16872443 stream:0xe6a101ec wall:0 window_ms:62000 blocks:1689 rate:8000
**ACOUSTIC** rms_mean:105 rms_max:582 peak:1255 transients:0

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:16932443 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-79 rssi_med:-66 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-65 rssi_med:-61 rssi_max:-48

---

@LAT92LON16 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON2,senses@LAT0LON0

**OUTCOME** t_ms:16932443 stream:0xe6a101ec wall:0 node:0x300 acting:@LAT95LON1+0 observed_in:@LAT97LON2 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-61 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-61 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-72 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-66 delta:6 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:16932443 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2848 rate:8000
**ACOUSTIC** rms_mean:173 rms_max:5445 peak:19106 transients:9
**TRANSIENT** t_ms:16915491 stream:0xe6a101ec wall:0 rms:5445

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:16992443 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-53 rssi_med:-50 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-79 rssi_med:-64 rssi_max:-57

---

@LAT92LON17 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON3,senses@LAT0LON0

**OUTCOME** t_ms:16992443 stream:0xe6a101ec wall:0 node:0x300 acting:@LAT95LON1+1 observed_in:@LAT97LON3 band_dbm:6 met:1 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-66 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-64 delta:2 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-61 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-50 delta:11 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:16992443 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2985 rate:8000
**ACOUSTIC** rms_mean:179 rms_max:6076 peak:6725 transients:7
**TRANSIENT** t_ms:16968969 stream:0xe6a101ec wall:0 rms:4424

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17052443 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-66 rssi_med:-64 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-52 rssi_med:-50 rssi_max:-49

---

@LAT92LON18 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON4,senses@LAT0LON0

**OUTCOME** t_ms:17052443 stream:0xe6a101ec wall:0 node:0x300 acting:@LAT95LON1+2 observed_in:@LAT97LON4 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-50 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-50 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-64 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-64 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17052443 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2310 rate:8000
**ACOUSTIC** rms_mean:135 rms_max:627 peak:1174 transients:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17112450 stream:0xe6a101ec wall:0 window_ms:60007
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-52 rssi_med:-50 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-66 rssi_med:-64 rssi_max:-57

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17112450 stream:0xe6a101ec wall:0 window_ms:60007 blocks:2981 rate:8000
**ACOUSTIC** rms_mean:153 rms_max:1624 peak:1909 transients:1
**TRANSIENT** t_ms:17099734 stream:0xe6a101ec wall:0 rms:1470

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17172450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-64 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-52 rssi_med:-50 rssi_max:-49

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17172450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2985 rate:8000
**ACOUSTIC** rms_mean:140 rms_max:725 peak:1450 transients:0

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17232450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-66 rssi_med:-64 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-53 rssi_med:-51 rssi_max:-50

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17232450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2432 rate:8000
**ACOUSTIC** rms_mean:147 rms_max:1872 peak:2865 transients:5
**TRANSIENT** t_ms:17229828 stream:0xe6a101ec wall:0 rms:1872

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17292450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-53 rssi_med:-50 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-81 rssi_med:-64 rssi_max:-57

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17292450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3111 rate:8000
**ACOUSTIC** rms_mean:142 rms_max:651 peak:1274 transients:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17352450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-53 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-79 rssi_med:-64 rssi_max:-57

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17352450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3107 rate:8000
**ACOUSTIC** rms_mean:286 rms_max:14385 peak:32768 transients:16
**TRANSIENT** t_ms:17333942 stream:0xe6a101ec wall:0 rms:14385

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17412450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-53 rssi_med:-50 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-63 rssi_max:-57

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17412450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2987 rate:8000
**ACOUSTIC** rms_mean:250 rms_max:12188 peak:32768 transients:14
**TRANSIENT** t_ms:17394205 stream:0xe6a101ec wall:0 rms:12188

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17472450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17472450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2863 rate:8000
**ACOUSTIC** rms_mean:183 rms_max:3588 peak:18073 transients:3
**TRANSIENT** t_ms:17472432 stream:0xe6a101ec wall:0 rms:3118

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17532450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-52 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-79 rssi_med:-62 rssi_max:-58

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17532450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2990 rate:8000
**ACOUSTIC** rms_mean:216 rms_max:7241 peak:8034 transients:5
**TRANSIENT** t_ms:17502476 stream:0xe6a101ec wall:0 rms:7241

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17592450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17592450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2980 rate:8000
**ACOUSTIC** rms_mean:98 rms_max:239 peak:509 transients:0

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17652450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17652450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3112 rate:8000
**ACOUSTIC** rms_mean:91 rms_max:308 peak:647 transients:0

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17712450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-83 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-52 rssi_med:-49 rssi_max:-48

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17712450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3116 rate:8000
**ACOUSTIC** rms_mean:100 rms_max:293 peak:960 transients:0

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17772450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-52 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:48 rssi_min:-66 rssi_med:-62 rssi_max:-58

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17772450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2980 rate:8000
**ACOUSTIC** rms_mean:97 rms_max:230 peak:492 transients:0

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17832450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17832450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3107 rate:8000
**ACOUSTIC** rms_mean:97 rms_max:231 peak:450 transients:0

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17892450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-52 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-82 rssi_med:-62 rssi_max:-58

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17892450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2987 rate:8000
**ACOUSTIC** rms_mean:98 rms_max:400 peak:848 transients:0

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17952450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-80 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:17952450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2983 rate:8000
**ACOUSTIC** rms_mean:100 rms_max:550 peak:1185 transients:0

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18012450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18012450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3112 rate:8000
**ACOUSTIC** rms_mean:99 rms_max:276 peak:570 transients:0

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18072450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18072450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2858 rate:8000
**ACOUSTIC** rms_mean:125 rms_max:1586 peak:5438 transients:4
**TRANSIENT** t_ms:18053069 stream:0xe6a101ec wall:0 rms:1586

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18132450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-52 rssi_med:-49 rssi_max:-48

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18132450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2979 rate:8000
**ACOUSTIC** rms_mean:123 rms_max:678 peak:2220 transients:0

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18192450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-52 rssi_med:-49 rssi_max:-48

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18192450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3114 rate:8000
**ACOUSTIC** rms_mean:113 rms_max:816 peak:1375 transients:0

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18252450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-52 rssi_med:-49 rssi_max:-48

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18252450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2978 rate:8000
**ACOUSTIC** rms_mean:105 rms_max:582 peak:1013 transients:0

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18312450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-52 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-62 rssi_max:-58

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18312450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2985 rate:8000
**ACOUSTIC** rms_mean:129 rms_max:1356 peak:1965 transients:2
**TRANSIENT** t_ms:18284769 stream:0xe6a101ec wall:0 rms:1356

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18372450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-51 rssi_med:-50 rssi_max:-48

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18372450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3111 rate:8000
**ACOUSTIC** rms_mean:115 rms_max:969 peak:1435 transients:1
**TRANSIENT** t_ms:18323419 stream:0xe6a101ec wall:0 rms:969

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18432450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-52 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-69 rssi_med:-62 rssi_max:-58

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18432450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3116 rate:8000
**ACOUSTIC** rms_mean:110 rms_max:1160 peak:1673 transients:0

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18492450 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18492450 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2979 rate:8000
**ACOUSTIC** rms_mean:129 rms_max:3447 peak:3822 transients:3
**TRANSIENT** t_ms:18453130 stream:0xe6a101ec wall:0 rms:3447

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18552451 stream:0xe6a101ec wall:0 window_ms:60001
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18552451 stream:0xe6a101ec wall:0 window_ms:60001 blocks:3113 rate:8000
**ACOUSTIC** rms_mean:133 rms_max:1114 peak:2036 transients:1
**TRANSIENT** t_ms:18513491 stream:0xe6a101ec wall:0 rms:1114

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18612459 stream:0xe6a101ec wall:0 window_ms:60008
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-79 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-51 rssi_med:-49 rssi_max:-48

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18612459 stream:0xe6a101ec wall:0 window_ms:60008 blocks:2988 rate:8000
**ACOUSTIC** rms_mean:149 rms_max:5482 peak:6542 transients:11
**TRANSIENT** t_ms:18596408 stream:0xe6a101ec wall:0 rms:5482

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18672459 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18672459 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2721 rate:8000
**ACOUSTIC** rms_mean:115 rms_max:831 peak:1482 transients:0

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18732459 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18732459 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2976 rate:8000
**ACOUSTIC** rms_mean:100 rms_max:832 peak:1214 transients:0

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18792459 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-51 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-80 rssi_med:-62 rssi_max:-57

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18792459 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3114 rate:8000
**ACOUSTIC** rms_mean:104 rms_max:532 peak:849 transients:0

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18852476 stream:0xe6a101ec wall:0 window_ms:60017
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-52 rssi_med:-49 rssi_max:-48

---

@LAT92LON19 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON34,senses@LAT0LON0

**OUTCOME** t_ms:18852476 stream:0xe6a101ec wall:0 node:0x300 acting:@LAT95LON2+2 observed_in:@LAT97LON34 band_dbm:6 met:2 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED-SPAN** windows:29 first_t_ms:17112450 last_t_ms:18792459 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000010 proto:ble verdict:met windows:29 observed_min:-64 observed_max:-62
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:29 observed_min:-51 observed_max:-49
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-50 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-49 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-62 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-62 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON34 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18852476 stream:0xe6a101ec wall:0 window_ms:60017 blocks:2974 rate:8000
**ACOUSTIC** rms_mean:115 rms_max:784 peak:1138 transients:0

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18912565 stream:0xe6a101ec wall:0 window_ms:60089
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-52 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-80 rssi_med:-62 rssi_max:-58

---

@LAT94LON35 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18912565 stream:0xe6a101ec wall:0 window_ms:60089 blocks:2919 rate:8000
**ACOUSTIC** rms_mean:97 rms_max:524 peak:985 transients:0

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18972565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-52 rssi_med:-51 rssi_max:-48

---

@LAT94LON36 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18972565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2903 rate:8000
**ACOUSTIC** rms_mean:129 rms_max:1090 peak:1591 transients:1
**TRANSIENT** t_ms:18935284 stream:0xe6a101ec wall:0 rms:1090

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19032565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-52 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-62 rssi_max:-58

---

@LAT94LON37 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19032565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2246 rate:8000
**ACOUSTIC** rms_mean:126 rms_max:545 peak:826 transients:0

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19092565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-52 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-66 rssi_med:-62 rssi_max:-58

---

@LAT94LON38 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19092565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3002 rate:8000
**ACOUSTIC** rms_mean:98 rms_max:304 peak:600 transients:0

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19152565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-51 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-66 rssi_med:-62 rssi_max:-58

---

@LAT94LON39 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19152565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3013 rate:8000
**ACOUSTIC** rms_mean:83 rms_max:188 peak:397 transients:0

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19212565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON40 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19212565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2876 rate:8000
**ACOUSTIC** rms_mean:86 rms_max:192 peak:435 transients:0

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19272565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-52 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-66 rssi_med:-62 rssi_max:-57

---

@LAT94LON41 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19272565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2764 rate:8000
**ACOUSTIC** rms_mean:84 rms_max:197 peak:429 transients:0

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19332565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-66 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT94LON42 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19332565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2908 rate:8000
**ACOUSTIC** rms_mean:89 rms_max:261 peak:484 transients:0

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19392565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-52 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-66 rssi_med:-62 rssi_max:-58

---

@LAT94LON43 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19392565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2854 rate:8000
**ACOUSTIC** rms_mean:85 rms_max:249 peak:431 transients:0

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19452565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-52 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-80 rssi_med:-62 rssi_max:-58

---

@LAT94LON44 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19452565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3019 rate:8000
**ACOUSTIC** rms_mean:88 rms_max:213 peak:412 transients:0

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19512565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-52 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-66 rssi_med:-62 rssi_max:-58

---

@LAT94LON45 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19512565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3020 rate:8000
**ACOUSTIC** rms_mean:84 rms_max:230 peak:437 transients:0

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19572565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-52 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-79 rssi_med:-62 rssi_max:-58

---

@LAT94LON46 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19572565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:2869 rate:8000
**ACOUSTIC** rms_mean:79 rms_max:188 peak:385 transients:0

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19632565 stream:0xe6a101ec wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-52 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-66 rssi_med:-62 rssi_max:-58

---

@LAT94LON47 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19632565 stream:0xe6a101ec wall:0 window_ms:60000 blocks:3017 rate:8000
**ACOUSTIC** rms_mean:83 rms_max:195 peak:450 transients:0

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xe6a101ec wall:0 t_ms:19859709 node:0x300 from:0x10
**REMAP** prev_stream:0xfd1fc95c prev_t_ms:4880 offset_ms:19854829 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x7945c57c wall:0 t_ms:61217 node:0x300 from:0x10
**REMAP** prev_stream:0x0fba7f03 prev_t_ms:4951 offset_ms:56266 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x5c68cae2 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xb94644d8 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x50956f00 wall:0 t_ms:345208 node:0x300 from:0x10
**REMAP** prev_stream:0xec3ac72c prev_t_ms:5990 offset_ms:339218 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x50956f00 wall:0 t_ms:11306664 node:0x300 from:0x200
**REMAP** prev_stream:0x081bdfd9 prev_t_ms:17670 offset_ms:11288994 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xc537a0b6 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x8cc27853 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbbc96f7f wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT93LON4 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON35,derived_from@LAT95LON36

**TRANSITION** t_ms:112078 stream:0xbbc96f7f wall:0 node:0x300 from:still to:moving dt_ms:60016 dt_across_merge:0
  @PERCEPT:before state:still t_ms:52062 window_ms:60000 n:934 moving_permille:61 dev_mean_mg:25 dev_max_mg:255 moving_ms:3425 lane:@LAT95LON35+0
  @PERCEPT:after state:moving t_ms:112078 window_ms:60016 n:996 moving_permille:132 dev_mean_mg:34 dev_max_mg:504 moving_ms:7967 lane:@LAT95LON36+0
**DELTA** edge:became d_permille:71 d_dev_mean_mg:9 d_dev_max_mg:249

---

@LAT93LON5 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON36,derived_from@LAT95LON37

**TRANSITION** t_ms:232078 stream:0xbbc96f7f wall:0 node:0x300 from:moving to:still dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:moving t_ms:172078 window_ms:60000 n:996 moving_permille:126 dev_mean_mg:33 dev_max_mg:389 moving_ms:7565 lane:@LAT95LON36+1
  @PERCEPT:after state:still t_ms:232078 window_ms:60000 n:1000 moving_permille:25 dev_mean_mg:21 dev_max_mg:367 moving_ms:1501 lane:@LAT95LON37+0
**DELTA** edge:became d_permille:-101 d_dev_mean_mg:-12 d_dev_max_mg:-22

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x1d96fb5c wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbea21365 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x66486d22 wall:0 t_ms:4188016 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x58783c1d wall:0 t_ms:11096 node:0x300 from:0x200
**REMAP** prev_stream:0x35fa5866 prev_t_ms:6438 offset_ms:4658 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x9cf79991 wall:0 t_ms:6708 node:0x300 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x9cf79991 wall:0 t_ms:1645119 node:0x300 from:0x200
**REMAP** prev_stream:0x00449474 prev_t_ms:1835 offset_ms:1643284 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT100LON28 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:6 removed:48 last_lon:47 t_ms:4868390 stream:0x95cc309e wall:0 node:0x00000300

---

@LAT100LON29 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:7 removed:48 last_lon:47 t_ms:0 stream:0x00000000 wall:0 node:0x00000300

---


---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4946561 stream:0x95cc309e wall:0 window_ms:60000 n:74
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4948619 stream:0x95cc309e wall:0 window_ms:62058 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60300 stream:0xb4347c09 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60300 stream:0xb4347c09 wall:0 window_ms:60000 n:949
**MOTION** state:still moving_permille:6 dev_mean_mg:8 dev_max_mg:472 moving_ms:831
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:612142 stream:0xb4347c09 wall:0 window_ms:551842 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1212140 stream:0xb4347c09 wall:0 window_ms:599998 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,18a5ffbae2d6

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1758934 stream:0xb4347c09 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1758934 stream:0xb4347c09 wall:0 window_ms:60000 n:938
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2311491 stream:0xb4347c09 wall:0 window_ms:552557 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2911538 stream:0xb4347c09 wall:0 window_ms:600047 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,64677217947d,0283cce0e689,bc102f237ace,18a5ffbae2d6,e6b32d2cea8b

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3381996 stream:0xb4347c09 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3381996 stream:0xb4347c09 wall:0 window_ms:60000 n:944
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3934139 stream:0xb4347c09 wall:0 window_ms:552143 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4534132 stream:0xb4347c09 wall:0 window_ms:599993 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,64677217947d,0283cce0e689,84a329c78fec,bc102f237ace,18a5ffbae2d6,e6b32d2cea8b

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5182657 stream:0xb4347c09 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5182657 stream:0xb4347c09 wall:0 window_ms:60000 n:933
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5735460 stream:0xb4347c09 wall:0 window_ms:552803 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6335457 stream:0xb4347c09 wall:0 window_ms:599997 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,64677217947d,e6b32d2cea8b,0283cce0e689,18a5ffbae2d6,bc102f237ace,84a329c78fec

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7000379 stream:0xb4347c09 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7000379 stream:0xb4347c09 wall:0 window_ms:60000 n:941
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7552734 stream:0xb4347c09 wall:0 window_ms:552355 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8152730 stream:0xb4347c09 wall:0 window_ms:599996 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,64677217947d,18a5ffbae2d6,e6b32d2cea8b,84a329c78fec

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:8806340 stream:0xb4347c09 wall:0 window_ms:60000 n:977
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28763 window_ms:1745961 moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0 first_t_ms:7060379 last_t_ms:8746340 covered_by:@LAT95LON5

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9021063 stream:0xb4347c09 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:9021063 stream:0xb4347c09 wall:0 window_ms:60000 n:937
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9573606 stream:0xb4347c09 wall:0 window_ms:552543 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10173606 stream:0xb4347c09 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,64677217947d,0283cce0e689,84a329c78fec,18a5ffbae2d6,e6b32d2cea8b

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10806618 stream:0xb4347c09 wall:0 window_ms:60001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:10806618 stream:0xb4347c09 wall:0 window_ms:60001 n:944
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11358791 stream:0xb4347c09 wall:0 window_ms:552173 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11958790 stream:0xb4347c09 wall:0 window_ms:599999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,64677217947d,18a5ffbae2d6,e6b32d2cea8b,84a329c78fec,bc102f237ace

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12619451 stream:0xb4347c09 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:12619451 stream:0xb4347c09 wall:0 window_ms:60000 n:932
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13172340 stream:0xb4347c09 wall:0 window_ms:552889 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13772339 stream:0xb4347c09 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689,bc102f237ace,64677217947d

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13882706 stream:0xb4347c09 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:13882706 stream:0xb4347c09 wall:0 window_ms:60000 n:938
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:14435221 stream:0xb4347c09 wall:0 window_ms:552515 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:15035220 stream:0xb4347c09 wall:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,84a329c78fec,bc102f237ace,0283cce0e689,64677217947d

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:15709777 stream:0xb4347c09 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:15709777 stream:0xb4347c09 wall:0 window_ms:60000 n:930
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:16262776 stream:0xb4347c09 wall:0 window_ms:552999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:16862774 stream:0xb4347c09 wall:0 window_ms:599998 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,64677217947d,bc102f237ace,0283cce0e689,84a329c78fec,18a5ffbae2d6,e6b32d2cea8b

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:17465360 stream:0xb4347c09 wall:0 window_ms:602586 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:4
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,0283cce0e689,64677217947d,bc102f237ace,18a5ffbae2d6,84a329c78fec,e6b32d2cea8b

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:17509778 stream:0xb4347c09 wall:0 window_ms:60001 n:870
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28910 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0 first_t_ms:15769777 last_t_ms:17449777 covered_by:@LAT95LON11

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:18126034 stream:0xb4347c09 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:18126034 stream:0xb4347c09 wall:0 window_ms:60000 n:940
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:18678437 stream:0xb4347c09 wall:0 window_ms:552403 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:19278435 stream:0xb4347c09 wall:0 window_ms:599998 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,0283cce0e689,84a329c78fec,64677217947d,bc102f237ace,18a5ffbae2d6,e6b32d2cea8b

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:19881991 stream:0xb4347c09 wall:0 window_ms:603556 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:4
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,0283cce0e689,64677217947d,84a329c78fec,bc102f237ace,18a5ffbae2d6,e6b32d2cea8b

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:19933211 stream:0xb4347c09 wall:0 window_ms:60000 n:979
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28838 window_ms:1747177 moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0 first_t_ms:18186034 last_t_ms:19873211 covered_by:@LAT95LON13

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:188106 stream:0xc49e1cd4 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:188106 stream:0xc49e1cd4 wall:0 window_ms:60000 n:935
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:740734 stream:0xc49e1cd4 wall:0 window_ms:552628 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1340733 stream:0xc49e1cd4 wall:0 window_ms:599999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,84a329c78fec,64677217947d,18a5ffbae2d6,0283cce0e689,e6b32d2cea8b

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2048770 stream:0xc49e1cd4 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2048770 stream:0xc49e1cd4 wall:0 window_ms:60000 n:941
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2601104 stream:0xc49e1cd4 wall:0 window_ms:552334 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3201102 stream:0xc49e1cd4 wall:0 window_ms:599998 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,0283cce0e689,64677217947d,e6b32d2cea8b,18a5ffbae2d6

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3491390 stream:0xc49e1cd4 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3491390 stream:0xc49e1cd4 wall:0 window_ms:60000 n:932
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4044310 stream:0xc49e1cd4 wall:0 window_ms:552920 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4644305 stream:0xc49e1cd4 wall:0 window_ms:599995 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,64677217947d,18a5ffbae2d6,e6b32d2cea8b

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5186321 stream:0xc49e1cd4 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5186321 stream:0xc49e1cd4 wall:0 window_ms:60000 n:936
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5738923 stream:0xc49e1cd4 wall:0 window_ms:552602 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6338921 stream:0xc49e1cd4 wall:0 window_ms:599998 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,0283cce0e689,64677217947d,84a329c78fec,bc102f237ace,e6b32d2cea8b,18a5ffbae2d6

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:6986321 stream:0xc49e1cd4 wall:0 window_ms:60000 n:842
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28824 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:14 moving_ms:0 first_t_ms:5246321 last_t_ms:6926321 covered_by:@LAT95LON18

---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7603596 stream:0xc49e1cd4 wall:0 window_ms:60000 n:932
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:9411532 stream:0xc49e1cd4 wall:0 window_ms:60000 n:974
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28863 window_ms:1747936 moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0 first_t_ms:7663596 last_t_ms:9351532 covered_by:@LAT95LON20

---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:9952187 stream:0xc49e1cd4 wall:0 window_ms:60000 n:933
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:11753918 stream:0xc49e1cd4 wall:0 window_ms:60000 n:926
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:13554571 stream:0xc49e1cd4 wall:0 window_ms:60000 n:935
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:15354571 stream:0xc49e1cd4 wall:0 window_ms:60000 n:849
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28854 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0 first_t_ms:13614571 last_t_ms:15294571 covered_by:@LAT95LON24

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:15714571 stream:0xc49e1cd4 wall:0 window_ms:60000 n:981
**MOTION** state:moving moving_permille:267 dev_mean_mg:60 dev_max_mg:1387 moving_ms:16293
**RUN** windows_since_last:6 reason:changed max_run:30
**COVERED** state:still windows:5 n:4935 window_ms:300000 moving_permille:0 dev_mean_mg:9 dev_max_mg:22 moving_ms:0 first_t_ms:15414571 last_t_ms:15654571 covered_by:@LAT95LON25

---

@LAT93LON6 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON25,derived_from@LAT95LON26

**TRANSITION** t_ms:15714571 stream:0xc49e1cd4 wall:0 node:0x300 from:still to:moving dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:still t_ms:15654571 window_ms:60000 n:989 moving_permille:0 dev_mean_mg:9 dev_max_mg:22 moving_ms:0 lane:@LAT95LON25+5
  @PERCEPT:after state:moving t_ms:15714571 window_ms:60000 n:981 moving_permille:267 dev_mean_mg:60 dev_max_mg:1387 moving_ms:16293 lane:@LAT95LON26+0
**DELTA** edge:became d_permille:267 d_dev_mean_mg:51 d_dev_max_mg:1365

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:15813868 stream:0xc49e1cd4 wall:0 window_ms:60000 n:934
**MOTION** state:still moving_permille:34 dev_mean_mg:15 dev_max_mg:407 moving_ms:1926
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON28 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:15877250 stream:0xc49e1cd4 wall:0 window_ms:63382 n:239
**MOTION** state:moving moving_permille:192 dev_mean_mg:37 dev_max_mg:379 moving_ms:2760
**RUN** windows_since_last:1 reason:changed max_run:30

---

@LAT93LON7 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON27,derived_from@LAT95LON28

**TRANSITION** t_ms:15877250 stream:0xc49e1cd4 wall:0 node:0x300 from:still to:moving dt_ms:63382 dt_across_merge:0
  @PERCEPT:before state:still t_ms:15813868 window_ms:60000 n:934 moving_permille:34 dev_mean_mg:15 dev_max_mg:407 moving_ms:1926 lane:@LAT95LON27+0
  @PERCEPT:after state:moving t_ms:15877250 window_ms:63382 n:239 moving_permille:192 dev_mean_mg:37 dev_max_mg:379 moving_ms:2760 lane:@LAT95LON28+0
**DELTA** edge:became d_permille:158 d_dev_mean_mg:22 d_dev_max_mg:-28

---

@LAT95LON29 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:15974880 stream:0xc49e1cd4 wall:0 window_ms:60000 n:57
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:27 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON30 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:999264 stream:0x516c169d wall:0 window_ms:60000 n:932
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON31 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51883 stream:0x6ceb85ae wall:0 window_ms:60000 n:927
**MOTION** state:still moving_permille:0 dev_mean_mg:6 dev_max_mg:21 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---


---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:339067 stream:0x6ceb85ae wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:254 half_life_ms:600000 reinforced:1 last_ms:339677
t_ms:339067 stream:0x6ceb85ae wall:0

---

@LAT101LON2 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:339067 stream:0x6ceb85ae wall:0

---

@LAT101LON3 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:46 half_life_ms:600000 reinforced:0 last_ms:2117
t_ms:339067 stream:0x6ceb85ae wall:0

---

@LAT101LON4 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:339067 stream:0x6ceb85ae wall:0

---

@LAT95LON32 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:658835 stream:0x5def950e wall:0 window_ms:60000 n:921
**MOTION** state:still moving_permille:1 dev_mean_mg:8 dev_max_mg:84 moving_ms:60
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON33 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:817591 stream:0x5def950e wall:0 window_ms:61414 n:54
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:51 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON34 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51778 stream:0x0870722b wall:0 window_ms:60000 n:924
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:19 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON35 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1203616 stream:0x0870722b wall:0 window_ms:60000 n:238
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT91LON0 | sid:ab8f77ba | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:206
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000100 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:39 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:20 method:sequential_fold_from_baseline

---

@LAT91LON1 | sid:ca9b482d | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:255
rev:1
sal:24
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:136 violated:3 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:20 method:sequential_fold_from_baseline

---

@LAT91LON2 | sid:2b4da8c8 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:255
rev:1
sal:24
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:132 violated:3 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:20 method:sequential_fold_from_baseline

---

@LAT95LON36 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1303915 stream:0x0870722b wall:0 window_ms:60000 n:927
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30
