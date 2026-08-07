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

@LAT91LON0 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:206
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000100 proto:espnow node:0x300
**TOUCHED** t_ms:16730975 stream:0xe6a101ec wall:0 unix_s:0
**TALLY** met:39 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:16 method:sequential_fold_from_baseline

---

@LAT91LON1 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:255
rev:1
sal:24
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:16730975 stream:0xe6a101ec wall:0 unix_s:0
**TALLY** met:103 violated:3 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:16 method:sequential_fold_from_baseline

---

@LAT91LON2 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:255
rev:1
sal:16
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TOUCHED** t_ms:16730975 stream:0xe6a101ec wall:0 unix_s:0
**TALLY** met:100 violated:2 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:16 method:sequential_fold_from_baseline
