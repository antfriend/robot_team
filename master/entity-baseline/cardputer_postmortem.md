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

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xe7384824 wall:0 t_ms:1447466 node:0x300 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---


---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xaf869fce wall:0 t_ms:7185 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x161e88ac wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x5f6eb232 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x41ba1242 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x67ec2883 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x3ab84e5a wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---


---


---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbe6d9616 wall:0 t_ms:4001 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---


---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbe6d9616 wall:0 t_ms:5743568 node:0x300 from:0x10
**REMAP** prev_stream:0x9feeb581 prev_t_ms:7042 offset_ms:5736526 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

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

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbe6d9616 wall:0 t_ms:6944002 node:0x300 from:0x10
**REMAP** prev_stream:0x36d6dcee prev_t_ms:5710 offset_ms:6938292 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

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

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbe6d9616 wall:0 t_ms:15986373 node:0x300 from:0x10
**REMAP** prev_stream:0x9750d529 prev_t_ms:6268 offset_ms:15980105 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18704845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:29 rssi_min:-63 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-71 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-65 rssi_med:-45 rssi_max:-36

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:18704845 stream:0xbe6d9616 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:18704845 stream:0xbe6d9616 wall:0 window_ms:60000 n:497
**MOTION** state:still moving_permille:68 dev_mean_mg:20 dev_max_mg:466 moving_ms:2040
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18704845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:1833 rate:8000
**ACOUSTIC** rms_mean:253 rms_max:19763 peak:32768 transients:15
**TRANSIENT** t_ms:18682702 stream:0xbe6d9616 wall:0 rms:19763

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18764845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-46 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-80 rssi_med:-63 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:32 rssi_min:-51 rssi_med:-48 rssi_max:-46

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

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18764845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:95 rms_max:917 peak:3805 transients:1
**TRANSIENT** t_ms:18718861 stream:0xbe6d9616 wall:0 rms:917

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18824845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-67 rssi_med:-62 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-50 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-45 rssi_med:-44 rssi_max:-43

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

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18824845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:92 rms_max:183 peak:551 transients:0

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18884845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-45 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-66 rssi_med:-62 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-50 rssi_med:-47 rssi_max:-46

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18884845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3698 rate:8000
**ACOUSTIC** rms_mean:91 rms_max:177 peak:800 transients:0

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18944845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-50 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-68 rssi_med:-63 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-46 rssi_med:-44 rssi_max:-43

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:18944845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3739 rate:8000
**ACOUSTIC** rms_mean:98 rms_max:251 peak:502 transients:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19004845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-51 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-56

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19004845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3738 rate:8000
**ACOUSTIC** rms_mean:95 rms_max:499 peak:1524 transients:0

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19064845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-50 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-45 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-68 rssi_med:-63 rssi_max:-56

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19064845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:95 rms_max:219 peak:702 transients:0

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19124845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-45 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-49 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-62 rssi_max:-56

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19124845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:94 rms_max:326 peak:1014 transients:0

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19184845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-50 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-68 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-46 rssi_med:-44 rssi_max:-41

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19184845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:99 rms_max:231 peak:713 transients:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19244845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-62 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-52 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-46 rssi_med:-43 rssi_max:-42

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19244845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:132 rms_max:341 peak:933 transients:0

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:19279881 stream:0xbe6d9616 wall:0 window_ms:575036 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19304845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-47 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-49 rssi_med:-47 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-62 rssi_max:-57

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19304845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:170 rms_max:402 peak:871 transients:0

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19364845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-67 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-44 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-50 rssi_med:-48 rssi_max:-48

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19364845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3740 rate:8000
**ACOUSTIC** rms_mean:188 rms_max:496 peak:960 transients:0

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19424845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-84 rssi_med:-63 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-56 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-45 rssi_med:-43 rssi_max:-41

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19424845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3739 rate:8000
**ACOUSTIC** rms_mean:201 rms_max:462 peak:1277 transients:0

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19484845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-45 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-51 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-75 rssi_med:-62 rssi_max:-54

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19484845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:184 rms_max:509 peak:889 transients:0

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19544845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-50 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-64 rssi_max:-56

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19544845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:183 rms_max:458 peak:1323 transients:0

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19604845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-47 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-51 rssi_med:-49 rssi_max:-47

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19604845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3725 rate:8000
**ACOUSTIC** rms_mean:191 rms_max:571 peak:1221 transients:0

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19664845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-50 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-67 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-46 rssi_med:-44 rssi_max:-42

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19664845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3743 rate:8000
**ACOUSTIC** rms_mean:174 rms_max:433 peak:1007 transients:0

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19724845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-45 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-65 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-49 rssi_med:-48 rssi_max:-47

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19724845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3738 rate:8000
**ACOUSTIC** rms_mean:201 rms_max:429 peak:853 transients:0

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19784845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-50 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-66 rssi_med:-63 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-46 rssi_med:-44 rssi_max:-42

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19784845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:202 rms_max:536 peak:1398 transients:0

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19844845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-65 rssi_med:-62 rssi_max:-56
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-45 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-50 rssi_med:-48 rssi_max:-46

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19844845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:146 rms_max:455 peak:787 transients:0

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:19879881 stream:0xbe6d9616 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19904845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-64 rssi_med:-62 rssi_max:-56
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-49 rssi_med:-47 rssi_max:-47

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19904845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:96 rms_max:215 peak:603 transients:0

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:19964845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-45 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-65 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-48 rssi_med:-48 rssi_max:-46

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:19964845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:94 rms_max:183 peak:503 transients:0

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20024845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-63 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-49 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-46 rssi_med:-44 rssi_max:-44

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20024845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3729 rate:8000
**ACOUSTIC** rms_mean:95 rms_max:356 peak:1153 transients:0

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20084845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-45 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-80 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-50 rssi_med:-48 rssi_max:-46

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20084845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:101 rms_max:287 peak:787 transients:0

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20144845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-49 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-68 rssi_med:-62 rssi_max:-56

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20144845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3739 rate:8000
**ACOUSTIC** rms_mean:93 rms_max:294 peak:582 transients:0

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20204845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-71 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-50 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-45 rssi_med:-44 rssi_max:-42

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20204845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3742 rate:8000
**ACOUSTIC** rms_mean:95 rms_max:385 peak:661 transients:0

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20264845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-45 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-63 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-51 rssi_med:-49 rssi_max:-46

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20264845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:92 rms_max:439 peak:762 transients:0

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20324845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-50 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-65 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-47 rssi_med:-45 rssi_max:-43

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20324845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:95 rms_max:267 peak:773 transients:0

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20384845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-48 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-83 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-48 rssi_med:-47 rssi_max:-46

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20384845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3739 rate:8000
**ACOUSTIC** rms_mean:114 rms_max:1731 peak:2754 transients:1
**TRANSIENT** t_ms:20333878 stream:0xbe6d9616 wall:0 rms:1731

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20444845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-48 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-70 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-51 rssi_med:-48 rssi_max:-47

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20444845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:107 rms_max:923 peak:1655 transients:1
**TRANSIENT** t_ms:20391855 stream:0xbe6d9616 wall:0 rms:923

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:20479878 stream:0xbe6d9616 wall:0 window_ms:599997 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20504845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:29 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-48 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-81 rssi_med:-63 rssi_max:-56

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:20504845 stream:0xbe6d9616 wall:0 window_ms:60000 n:980
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28912 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:25 moving_ms:0 first_t_ms:18764845 last_t_ms:20444845 covered_by:@LAT95LON0

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20504845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3611 rate:8000
**ACOUSTIC** rms_mean:139 rms_max:3715 peak:8171 transients:16
**TRANSIENT** t_ms:20487198 stream:0xbe6d9616 wall:0 rms:3715

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20564845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-50 rssi_med:-47 rssi_max:-47

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20564845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3637 rate:8000
**ACOUSTIC** rms_mean:89 rms_max:215 peak:465 transients:0

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20624845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-48 rssi_med:-47 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-66 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-50 rssi_med:-47 rssi_max:-47

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

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20624845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3630 rate:8000
**ACOUSTIC** rms_mean:127 rms_max:987 peak:1719 transients:2
**TRANSIENT** t_ms:20598223 stream:0xbe6d9616 wall:0 rms:987

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20684845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-67 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:11 rssi_min:-48 rssi_med:-47 rssi_max:-47
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-48 rssi_med:-44 rssi_max:-43

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20684845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3559 rate:8000
**ACOUSTIC** rms_mean:100 rms_max:981 peak:1491 transients:0

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20744845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-46 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-68 rssi_med:-62 rssi_max:-56

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

@LAT94LON34 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20744845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3630 rate:8000
**ACOUSTIC** rms_mean:139 rms_max:4565 peak:19922 transients:4
**TRANSIENT** t_ms:20705967 stream:0xbe6d9616 wall:0 rms:2121

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20804845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-44 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-66 rssi_med:-62 rssi_max:-57

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

@LAT94LON35 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20804845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3639 rate:8000
**ACOUSTIC** rms_mean:136 rms_max:242 peak:635 transients:0

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20864845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-45 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-67 rssi_med:-62 rssi_max:-57

---

@LAT94LON36 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20864845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3582 rate:8000
**ACOUSTIC** rms_mean:174 rms_max:5996 peak:11714 transients:7
**TRANSIENT** t_ms:20859449 stream:0xbe6d9616 wall:0 rms:5996

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20924845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-44 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-66 rssi_med:-62 rssi_max:-57

---

@LAT94LON37 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20924845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3643 rate:8000
**ACOUSTIC** rms_mean:149 rms_max:1667 peak:2702 transients:2
**TRANSIENT** t_ms:20867016 stream:0xbe6d9616 wall:0 rms:1667

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:20984845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-66 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-45 rssi_med:-44 rssi_max:-43

---

@LAT94LON38 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:20984845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3632 rate:8000
**ACOUSTIC** rms_mean:137 rms_max:221 peak:603 transients:0

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:21044845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-45 rssi_med:-44 rssi_max:-43

---

@LAT94LON39 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:21044845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3626 rate:8000
**ACOUSTIC** rms_mean:149 rms_max:2788 peak:6299 transients:7
**TRANSIENT** t_ms:20997505 stream:0xbe6d9616 wall:0 rms:2788

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:21079879 stream:0xbe6d9616 wall:0 window_ms:600001 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:21104845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-45 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-66 rssi_med:-62 rssi_max:-58

---

@LAT94LON40 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:21104845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3619 rate:8000
**ACOUSTIC** rms_mean:135 rms_max:224 peak:705 transients:0

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:21164845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-45 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-66 rssi_med:-64 rssi_max:-57

---

@LAT94LON41 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:21164845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3637 rate:8000
**ACOUSTIC** rms_mean:138 rms_max:213 peak:607 transients:0

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:21224845 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-71 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-45 rssi_med:-44 rssi_max:-43

---

@LAT94LON42 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:21224845 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3628 rate:8000
**ACOUSTIC** rms_mean:140 rms_max:403 peak:739 transients:0

---


---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x6a2120c2 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:50131 stream:0x6a2120c2 wall:0 window_ms:62000
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-51 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-62 rssi_med:-55 rssi_max:-53

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:50131 stream:0x6a2120c2 wall:0 window_ms:62000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:50131 stream:0x6a2120c2 wall:0 window_ms:62000 n:421
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:18 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON43 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:50131 stream:0x6a2120c2 wall:0 window_ms:62000 blocks:1573 rate:8000
**ACOUSTIC** rms_mean:198 rms_max:8568 peak:23752 transients:4
**TRANSIENT** t_ms:29265 stream:0x6a2120c2 wall:0 rms:8568

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:110132 stream:0x6a2120c2 wall:0 window_ms:60001
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-67 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-65 rssi_med:-55 rssi_max:-53

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

@LAT94LON44 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:110132 stream:0x6a2120c2 wall:0 window_ms:60001 blocks:2855 rate:8000
**ACOUSTIC** rms_mean:143 rms_max:646 peak:1321 transients:0

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:170140 stream:0x6a2120c2 wall:0 window_ms:60008
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-79 rssi_med:-54 rssi_max:-48
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-55 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:3 rssi_min:-34 rssi_med:-34 rssi_max:-34

---

@LAT94LON45 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:170140 stream:0x6a2120c2 wall:0 window_ms:60008 blocks:2974 rate:8000
**ACOUSTIC** rms_mean:153 rms_max:767 peak:2314 transients:0

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:230146 stream:0x6a2120c2 wall:0 window_ms:60006
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-80 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-59 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-37 rssi_med:-35 rssi_max:-34

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

@LAT94LON46 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:230146 stream:0x6a2120c2 wall:0 window_ms:60006 blocks:2308 rate:8000
**ACOUSTIC** rms_mean:168 rms_max:1308 peak:2841 transients:1
**TRANSIENT** t_ms:207106 stream:0x6a2120c2 wall:0 rms:1308

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:290146 stream:0x6a2120c2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-47 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-39 rssi_med:-38 rssi_max:-36
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-61 rssi_med:-54 rssi_max:-51

---

@LAT94LON47 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:290146 stream:0x6a2120c2 wall:0 window_ms:60000 blocks:2980 rate:8000
**ACOUSTIC** rms_mean:118 rms_max:1040 peak:2361 transients:1
**TRANSIENT** t_ms:282991 stream:0x6a2120c2 wall:0 rms:1040

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:623651 stream:0x6a2120c2 wall:0 window_ms:573520 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:985480 stream:0x6a2120c2 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:985480 stream:0x6a2120c2 wall:0 window_ms:60000 n:950
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---


---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xdffbae31 wall:0 t_ms:45175 node:0x300 from:0x10
**REMAP** prev_stream:0xe8be1ed7 prev_t_ms:6023 offset_ms:39152 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:91319 stream:0xdffbae31 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:91319 stream:0xdffbae31 wall:0 window_ms:60000 n:944
**MOTION** state:still moving_permille:5 dev_mean_mg:18 dev_max_mg:81 moving_ms:300
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3707322 stream:0xdffbae31 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3707322 stream:0xdffbae31 wall:0 window_ms:60000 n:941
**MOTION** state:still moving_permille:43 dev_mean_mg:22 dev_max_mg:1159 moving_ms:2499
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4259644 stream:0xdffbae31 wall:0 window_ms:552322 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4859642 stream:0xdffbae31 wall:0 window_ms:599998 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5459640 stream:0xdffbae31 wall:0 window_ms:599998 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5507322 stream:0xdffbae31 wall:0 window_ms:60000 n:980
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:23 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28960 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:769 moving_ms:966 first_t_ms:3767322 last_t_ms:5447322 covered_by:@LAT95LON5

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6111481 stream:0xdffbae31 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:6111481 stream:0xdffbae31 wall:0 window_ms:60000 n:940
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:21 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6663857 stream:0xdffbae31 wall:0 window_ms:552376 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x185f5a4b wall:0 t_ms:55193 node:0x300 from:0x10
**REMAP** prev_stream:0x4f741d74 prev_t_ms:5700 offset_ms:49493 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:101748 stream:0x185f5a4b wall:0 window_ms:60000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:101748 stream:0x185f5a4b wall:0 window_ms:60000 n:947
**MOTION** state:still moving_permille:31 dev_mean_mg:13 dev_max_mg:609 moving_ms:1800
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:653568 stream:0x185f5a4b wall:0 window_ms:551820 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1253568 stream:0x185f5a4b wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1853567 stream:0x185f5a4b wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1901748 stream:0x185f5a4b wall:0 window_ms:60000 n:986
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28945 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:17 moving_ms:0 first_t_ms:161748 last_t_ms:1841748 covered_by:@LAT95LON8

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2669287 stream:0x185f5a4b wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-98

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2669287 stream:0x185f5a4b wall:0 window_ms:60000 n:951
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3220986 stream:0x185f5a4b wall:0 window_ms:551699 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-95

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3820984 stream:0x185f5a4b wall:0 window_ms:599998 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-95

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4420984 stream:0x185f5a4b wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4469288 stream:0x185f5a4b wall:0 window_ms:60000 n:981
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28803 window_ms:1740001 moving_permille:0 dev_mean_mg:10 dev_max_mg:15 moving_ms:0 first_t_ms:2729287 last_t_ms:4409288 covered_by:@LAT95LON10

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4792580 stream:0x185f5a4b wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4792580 stream:0x185f5a4b wall:0 window_ms:60000 n:938
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5345074 stream:0x185f5a4b wall:0 window_ms:552494 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5945074 stream:0x185f5a4b wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-94

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6545073 stream:0x185f5a4b wall:0 window_ms:599999 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:6592580 stream:0x185f5a4b wall:0 window_ms:60000 n:979
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28942 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:15 moving_ms:0 first_t_ms:4852580 last_t_ms:6532580 covered_by:@LAT95LON12

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7145073 stream:0x185f5a4b wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-97

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7516834 stream:0x185f5a4b wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-95

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7516834 stream:0x185f5a4b wall:0 window_ms:60000 n:942
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8068999 stream:0x185f5a4b wall:0 window_ms:552165 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8669000 stream:0x185f5a4b wall:0 window_ms:600001 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-96

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9268999 stream:0x185f5a4b wall:0 window_ms:599999 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:9316834 stream:0x185f5a4b wall:0 window_ms:60000 n:981
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28927 window_ms:1740000 moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0 first_t_ms:7576834 last_t_ms:9256834 covered_by:@LAT95LON14

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9908756 stream:0x185f5a4b wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:9908756 stream:0x185f5a4b wall:0 window_ms:60000 n:945
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10460791 stream:0x185f5a4b wall:0 window_ms:552035 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11060790 stream:0x185f5a4b wall:0 window_ms:599999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11660790 stream:0x185f5a4b wall:0 window_ms:600000 entities:11
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-95

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:11708756 stream:0x185f5a4b wall:0 window_ms:60000 n:1000
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28976 window_ms:1740000 moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0 first_t_ms:9968756 last_t_ms:11648756 covered_by:@LAT95LON16

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12260789 stream:0x185f5a4b wall:0 window_ms:599999 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12921415 stream:0x185f5a4b wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-96

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:12921415 stream:0x185f5a4b wall:0 window_ms:60000 n:946
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13473434 stream:0x185f5a4b wall:0 window_ms:552019 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:14073434 stream:0x185f5a4b wall:0 window_ms:600000 entities:11
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x946fea42 wall:0 t_ms:13843165 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13899575 stream:0x946fea42 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:13899575 stream:0x946fea42 wall:0 window_ms:60000 n:935
**MOTION** state:still moving_permille:34 dev_mean_mg:12 dev_max_mg:600 moving_ms:1936
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:14452191 stream:0x946fea42 wall:0 window_ms:552616 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:15052192 stream:0x946fea42 wall:0 window_ms:600001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT91LON0 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:206
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000100 proto:espnow node:0x300
**TOUCHED** t_ms:15335263 stream:0x946fea42 wall:0 unix_s:0
**TALLY** met:39 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT91LON1 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:188
rev:1
sal:8
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:15335263 stream:0x946fea42 wall:0 unix_s:0
**TALLY** met:38 violated:1 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT91LON2 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:198
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TOUCHED** t_ms:15335263 stream:0x946fea42 wall:0 unix_s:0
**TALLY** met:35 violated:0 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline
