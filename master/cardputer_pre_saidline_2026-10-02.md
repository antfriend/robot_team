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
lane_classes:
  # TTDB-RFC-0010 §7.1. @LAT101 is the SOCIAL field — the fleet's first FIELD lane
  # (decay-on-read, reclaim-lowest, no prune path). Absent this block every lane is
  # EVIDENCE, which is the fail-safe direction, so an un-reflashed filesystem is safe.
  evidence: [0, 91, 92, 93, 94, 95, 96, 97]
  provenance: [90, 98, 99, 100]
  field: [101]
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

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x4a194eda wall:0 t_ms:26584234 node:0x300 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON2,senses@LAT0LON0

**OUTCOME** t_ms:26773469 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON1+0 observed_in:@LAT97LON2 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-46 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-45 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON1 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON22,senses@LAT0LON0

**OUTCOME** t_ms:28030043 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON2+0 observed_in:@LAT97LON22 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-52 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-49 delta:3 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON2 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON37,senses@LAT0LON0

**OUTCOME** t_ms:28932577 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON3+0 observed_in:@LAT97LON37 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-49 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xce6b6750 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x8a1565a4 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x67ea1389 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xfdaf75bf wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x642cef6b wall:0 t_ms:431045 node:0x300 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x9957bc73 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x7ced00dc wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x55e96c91 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xdf12e1d4 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xdcd3edce wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT93LON0 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON27,derived_from@LAT95LON28

**TRANSITION** t_ms:7812748 stream:0xdcd3edce wall:0 node:0x300 from:still to:moving dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:still t_ms:7752748 window_ms:60000 n:998 moving_permille:0 dev_mean_mg:12 dev_max_mg:20 moving_ms:0 lane:@LAT95LON27+9
  @PERCEPT:after state:moving t_ms:7812748 window_ms:60000 n:998 moving_permille:161 dev_mean_mg:60 dev_max_mg:5563 moving_ms:9664 lane:@LAT95LON28+0
**DELTA** edge:became d_permille:161 d_dev_mean_mg:48 d_dev_max_mg:5543

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x1c3a61ee wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x0c76a2a1 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xee98fca8 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xee98fca8 wall:0 t_ms:6989045 node:0x300 from:0x10
**REMAP** prev_stream:0x98fbaf08 prev_t_ms:5586 offset_ms:6983459 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:46 last_lon:45 t_ms:7440342 stream:0xee98fca8 wall:0 node:0x00000300

---


---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x88023c58 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT103LON8201 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3613636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:3604219 stream:0x88023c58 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689,7236bc441422,c2e94427adcf,5ce28c488e0c
```

---

@LAT103LON8202 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4813635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:4804218 stream:0x88023c58 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,5ce28c488e0c,e6b32d2cea8b,c2e94427adcf,0283cce0e689
said: 13 | **COVERED** windows:1 entities:9 window_ms:600000 first_t_ms:4204219 last_t_ms:4204219 covered_by:@LAT103LON8201
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-92 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93 windows:1
```

---

@LAT103LON8203 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5413636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:5404219 stream:0x88023c58 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,64677217947d,5ce28c488e0c,7236bc441422,0283cce0e689,c2e94427adcf,e6b32d2cea8b
```

---

@LAT103LON8204 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6013635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:6004218 stream:0x88023c58 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,0283cce0e689,5ce28c488e0c,c2e94427adcf,e6b32d2cea8b
```

---

@LAT103LON8205 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6613636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:6604219 stream:0x88023c58 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,5ce28c488e0c,aef9ff2626ac,0283cce0e689,c2e94427adcf
```

---

@LAT103LON8206 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7813635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:7804218 stream:0x88023c58 wall:0 window_ms:600000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 13 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,0283cce0e689,7236bc441422,c2e94427adcf,aef9ff2626ac
said: 15 | **COVERED** windows:1 entities:11 window_ms:599999 first_t_ms:7204218 last_t_ms:7204218 covered_by:@LAT103LON8205
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94 windows:1
```

---

@LAT103LON8207 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8413636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:8404219 stream:0x88023c58 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689,c2e94427adcf,aef9ff2626ac
```

---

@LAT103LON8208 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9013635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:9004218 stream:0x88023c58 wall:0 window_ms:599999 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,0283cce0e689,5ce28c488e0c,7236bc441422,c2e94427adcf,aef9ff2626ac
```

---

@LAT103LON8209 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9613636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:9604219 stream:0x88023c58 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,c2e94427adcf,5ce28c488e0c,7236bc441422,0283cce0e689
```

---

@LAT103LON8210 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10213635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:10204218 stream:0x88023c58 wall:0 window_ms:599999 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,7236bc441422,5ce28c488e0c,84a329c78fec,c2e94427adcf,0283cce0e689
```

---

@LAT103LON8211 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11413635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:11404218 stream:0x88023c58 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,5ce28c488e0c,c2e94427adcf,84a329c78fec,7236bc441422
said: 12 | **COVERED** windows:1 entities:10 window_ms:600000 first_t_ms:10804218 last_t_ms:10804218 covered_by:@LAT103LON8210
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
```

---

@LAT103LON8212 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12013636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:12004219 stream:0x88023c58 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,5ce28c488e0c,7236bc441422,c2e94427adcf
```

---

@LAT103LON8213 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 604978 ±22 frame:4000
said: 1 | **ENTWIN** t_ms:12651644 stream:0x88023c58 wall:0 window_ms:60000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-92
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8214 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 104518 ±0 frame:59000
said: 1 | **ENTWIN** t_ms:45800 stream:0x4d8b207e wall:0 window_ms:104518 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 12 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-95
said: 13 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 14 | **CORE** entities:0
```

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:1 removed:48 last_lon:47 t_ms:15673 stream:0xe1f82632 wall:0 node:0x00000300

---

@LAT103LON8215 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 105949 ±0 frame:60000
said: 1 | **ENTWIN** t_ms:46031 stream:0x4e654405 wall:0 window_ms:105949 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-95
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8216 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:50533 stream:0x01e9f962 wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8217 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 61053 ±0 frame:7000
said: 1 | **ENTWIN** t_ms:51142 stream:0x92fb56ae wall:0 window_ms:61053 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8218 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 102060 ±0 frame:60500
said: 1 | **ENTWIN** t_ms:1961892 stream:0x92fb56ae wall:0 window_ms:102060 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 13 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-97
said: 14 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 15 | **CORE** entities:0
```

---

@LAT103LON8219 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2244248 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:3173909 stream:0x92fb56ae wall:0 window_ms:604629 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,5ce28c488e0c,e6b32d2cea8b,c2e94427adcf,aef9ff2626ac,980d67f79619
said: 14 | **COVERED** windows:1 entities:11 window_ms:600676 first_t_ms:2569280 last_t_ms:2569280 covered_by:@LAT103LON8218
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95 windows:1
```

---

@LAT103LON8220 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:17000
said: 1 | **ENTWIN** t_ms:4126557 stream:0x92fb56ae wall:0 window_ms:60000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON16384 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:17000
said: 1 | **MOTIONWIN** t_ms:4126557 stream:0x92fb56ae wall:0 window_ms:60000 n:738
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:1 removed:48 last_lon:47 t_ms:4429700 stream:0x92fb56ae wall:0 node:0x00000300

---

@LAT103LON16385 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3566077 ±214768 frame:6000
said: 1 | **MOTIONWIN** t_ms:4498196 stream:0x92fb56ae wall:0 window_ms:60081 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:9 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8221 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3612115 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:4546043 stream:0x92fb56ae wall:0 window_ms:106119 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95
said: 12 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 13 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 14 | **CORE** entities:0
```

---

@LAT103LON8222 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4810506 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:5742611 stream:0x92fb56ae wall:0 window_ms:598434 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,980d67f79619
said: 14 | **COVERED** windows:1 entities:7 window_ms:599957 first_t_ms:5144177 last_t_ms:5144177 covered_by:@LAT103LON8221
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95 windows:1
```

---

@LAT103LON16386 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5406034 ±0 frame:6000
said: 1 | **MOTIONWIN** t_ms:6338139 stream:0x92fb56ae wall:0 window_ms:62023 n:335
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:14653 window_ms:1777934 moving_permille:0 dev_mean_mg:8 dev_max_mg:33 moving_ms:0 first_t_ms:4558182 last_t_ms:6276116 covered_by:@LAT103LON16385
```

---

@LAT103LON8223 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5416297 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:6348402 stream:0x92fb56ae wall:0 window_ms:605791 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 12 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 13 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-97
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 15 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,c2e94427adcf,980d67f79619,0283cce0e689
```

---

@LAT103LON8224 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6213347 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:7145408 stream:0x92fb56ae wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON16387 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 6213347 ±0 frame:6000
said: 1 | **MOTIONWIN** t_ms:7145408 stream:0x92fb56ae wall:0 window_ms:60000 n:908
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:22 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT92LON3 | created:0 | updated:0 | relates:testifies_about@LAT103LON16387,derived_from@LAT103LON343,senses@LAT0LON0

**OUTCOME** t_ms:7205408 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16387+0 observed_in:@LAT103LON343 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-60 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-61 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-41 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-44 delta:-2 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT92LON4 | created:0 | updated:0 | relates:testifies_about@LAT103LON16387,derived_from@LAT103LON345,senses@LAT0LON0

**OUTCOME** t_ms:7325408 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16387+2 observed_in:@LAT103LON345 band_dbm:6 met:3 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:2 reason:changed max_run:30
**COVERED-SPAN** windows:1 first_t_ms:7265408 last_t_ms:7265408 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000200 proto:ble verdict:met windows:1 observed_min:-55 observed_max:-55
**COVERED** peer:0x00000010 proto:ble verdict:met windows:1 observed_min:-66 observed_max:-66
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:1 observed_min:-42 observed_max:-42
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:1 observed_min:-47 observed_max:-47
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-66 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-59 delta:7 verdict:violated
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-40 delta:2 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-41 delta:6 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT92LON5 | created:0 | updated:0 | relates:testifies_about@LAT103LON16387,derived_from@LAT103LON346,senses@LAT0LON0

**OUTCOME** t_ms:7385408 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16387+3 observed_in:@LAT103LON346 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-59 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-41 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-42 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-56 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:0 stream:0x00000000 wall:0 node:0x00000300

---


---


---


---


---


---


---


---


---


---


---

@LAT103LON8225 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6947869 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:7881919 stream:0x92fb56ae wall:0 window_ms:62000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-96
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON16388 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 6947869 ±0 frame:6000
said: 1 | **MOTIONWIN** t_ms:7881919 stream:0x92fb56ae wall:0 window_ms:62000 n:904
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT92LON6 | created:0 | updated:0 | relates:testifies_about@LAT103LON16388,derived_from@LAT103LON349,senses@LAT0LON0

**OUTCOME** t_ms:7941919 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16388+0 observed_in:@LAT103LON349 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-59 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-38 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-38 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-42 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT103LON8226 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8101049 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:9035099 stream:0x92fb56ae wall:0 window_ms:600157 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,c2e94427adcf
said: 14 | **COVERED** windows:1 entities:6 window_ms:553023 first_t_ms:8434942 last_t_ms:8434942 covered_by:@LAT103LON8225
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96 windows:1
```

---

@LAT103LON8227 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8701962 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:9636012 stream:0x92fb56ae wall:0 window_ms:600913 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,c2e94427adcf,980d67f79619
```

---

@LAT103LON16389 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 8761962 ±0 frame:6000
said: 1 | **MOTIONWIN** t_ms:9696012 stream:0x92fb56ae wall:0 window_ms:60000 n:464
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:21017 window_ms:1754093 moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0 first_t_ms:7941919 last_t_ms:9636012 covered_by:@LAT103LON16388
```

---

@LAT92LON7 | created:0 | updated:0 | relates:testifies_about@LAT103LON16389,derived_from@LAT103LON379,senses@LAT0LON0

**OUTCOME** t_ms:9756012 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16389+0 observed_in:@LAT103LON379 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED-SPAN** windows:29 first_t_ms:8001919 last_t_ms:9696012 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000200 proto:ble verdict:met windows:29 observed_min:-55 observed_max:-54
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:29 observed_min:-42 observed_max:-41
**COVERED** peer:0x00000010 proto:ble verdict:met windows:29 observed_min:-59 observed_max:-59
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:29 observed_min:-38 observed_max:-38
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-59 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-38 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-38 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-42 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT91LON0 | sid:ab8f77ba | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:134
rev:3
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000100 proto:espnow node:0x300
**TOUCHED** t_ms:9816012 stream:0x92fb56ae wall:0 unix_s:0
**TALLY** met:3 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT91LON1 | sid:76dbf602 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:198
rev:3
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:ble node:0x300
**TOUCHED** t_ms:9816012 stream:0x92fb56ae wall:0 unix_s:0
**TALLY** met:35 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT91LON2 | sid:ca9b482d | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:180
rev:3
sal:8
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:9816012 stream:0x92fb56ae wall:0 unix_s:0
**TALLY** met:34 violated:1 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT91LON3 | sid:8a93826d | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:198
rev:3
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:espnow node:0x300
**TOUCHED** t_ms:9816012 stream:0x92fb56ae wall:0 unix_s:0
**TALLY** met:35 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT91LON4 | sid:2b4da8c8 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:198
rev:3
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TOUCHED** t_ms:9816012 stream:0x92fb56ae wall:0 unix_s:0
**TALLY** met:35 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT103LON8228 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9308730 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:10242780 stream:0x92fb56ae wall:0 window_ms:606768 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-97
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,c2e94427adcf,5ce28c488e0c,980d67f79619,64677217947d
```

---

@LAT103LON8229 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10502093 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:11436143 stream:0x92fb56ae wall:0 window_ms:593363 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,84a329c78fec,64677217947d,980d67f79619,5ce28c488e0c,c2e94427adcf
said: 14 | **COVERED** windows:1 entities:8 window_ms:600000 first_t_ms:10842780 last_t_ms:10842780 covered_by:@LAT103LON8228
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94 windows:1
```

---

@LAT103LON16390 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 10562093 ±0 frame:6000
said: 1 | **MOTIONWIN** t_ms:11496143 stream:0x92fb56ae wall:0 window_ms:60000 n:464
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:20933 window_ms:1740131 moving_permille:0 dev_mean_mg:9 dev_max_mg:96 moving_ms:60 first_t_ms:9756012 last_t_ms:11436143 covered_by:@LAT103LON16389
```

---

@LAT92LON8 | created:0 | updated:0 | relates:testifies_about@LAT103LON16390,derived_from@LAT103LON409,senses@LAT0LON0

**OUTCOME** t_ms:11556143 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16390+0 observed_in:@LAT103LON409 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED-SPAN** windows:29 first_t_ms:9816012 last_t_ms:11496143 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000010 proto:ble verdict:met windows:29 observed_min:-61 observed_max:-57
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:29 observed_min:-43 observed_max:-40
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:29 observed_min:-41 observed_max:-38
**COVERED** peer:0x00000200 proto:ble verdict:met windows:29 observed_min:-56 observed_max:-54
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-54 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-59 delta:-2 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-40 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-41 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT103LON8230 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10795104 ±21 frame:6000
said: 1 | **ENTWIN** t_ms:11729173 stream:0x92fb56ae wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON16391 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 10795104 ±21 frame:6000
said: 1 | **MOTIONWIN** t_ms:11729173 stream:0x92fb56ae wall:0 window_ms:60000 n:924
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8231 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11518948 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:12455030 stream:0x92fb56ae wall:0 window_ms:62000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON16392 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 11518948 ±0 frame:6000
said: 1 | **MOTIONWIN** t_ms:12455030 stream:0x92fb56ae wall:0 window_ms:62000 n:898
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:18 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8232 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:7500
said: 1 | **ENTWIN** t_ms:13403057 stream:0x92fb56ae wall:0 window_ms:60000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON16393 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:7500
said: 1 | **MOTIONWIN** t_ms:13403057 stream:0x92fb56ae wall:0 window_ms:60000 n:924
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:20 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8233 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:11000
said: 1 | **ENTWIN** t_ms:46462 stream:0x0947153e wall:0 window_ms:60000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON16394 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:11000
said: 1 | **MOTIONWIN** t_ms:46462 stream:0x0947153e wall:0 window_ms:60000 n:870
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:36 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8234 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:51120 stream:0x2ee5fee1 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON16395 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:6000
said: 1 | **MOTIONWIN** t_ms:51120 stream:0x2ee5fee1 wall:0 window_ms:60000 n:948
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8235 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 62000 ±0 frame:8500
said: 1 | **ENTWIN** t_ms:50566 stream:0xc909d5a8 wall:0 window_ms:62000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON16396 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 62000 ±0 frame:8500
said: 1 | **MOTIONWIN** t_ms:50566 stream:0xc909d5a8 wall:0 window_ms:62000 n:906
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8236 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:7000
said: 1 | **ENTWIN** t_ms:333393 stream:0xc909d5a8 wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON16397 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:7000
said: 1 | **MOTIONWIN** t_ms:333393 stream:0xc909d5a8 wall:0 window_ms:60000 n:931
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:22 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8237 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 364347 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:476952 stream:0xc909d5a8 wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON16398 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 364347 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:476952 stream:0xc909d5a8 wall:0 window_ms:60000 n:931
said: 2 | **MOTION** state:still moving_permille:1 dev_mean_mg:10 dev_max_mg:316 moving_ms:60
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8238 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1517171 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:1629776 stream:0xc909d5a8 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 12 | **COVERED** windows:1 entities:10 window_ms:552823 first_t_ms:1029775 last_t_ms:1029775 covered_by:@LAT103LON8237
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-88 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
```

---

@LAT103LON8239 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2117171 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:2229776 stream:0xc909d5a8 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c,0283cce0e689
```

---

@LAT103LON8240 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2717171 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:2829776 stream:0xc909d5a8 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,7236bc441422,5ce28c488e0c,0283cce0e689
```

---

@LAT103LON8241 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3317171 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:3429776 stream:0xc909d5a8 wall:0 window_ms:600000 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 13 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,64677217947d,e6b32d2cea8b,5ce28c488e0c,0283cce0e689,aef9ff2626ac,7236bc441422
```

---

@LAT103LON16399 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3966515 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:4079120 stream:0xc909d5a8 wall:0 window_ms:60000 n:968
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28788 window_ms:1740063 moving_permille:0 dev_mean_mg:10 dev_max_mg:85 moving_ms:60 first_t_ms:2339057 last_t_ms:4019120 covered_by:@LAT103LON16399
```

---

@LAT103LON504 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4386515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:4499120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-45 rssi_med:-36 rssi_max:-34
said: 3 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-67 rssi_med:-54 rssi_max:-49
said: 4 | 0x00000012 espnow met predicted:-35 observed:-36
percept: 4 | 0x00000012 | link_stable | espnow | + | -
said: 5 | 0x00000012 ble met predicted:-53 observed:-54
percept: 5 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON505 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4446515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:4559120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:10 rssi_min:-45 rssi_med:-44 rssi_max:-36
said: 3 | **LINK** peer:0x00000012 proto:ble n:26 rssi_min:-80 rssi_med:-56 rssi_max:-49
said: 4 | **LINK** peer:0x00000100 proto:espnow n:17 rssi_min:-52 rssi_med:-43 rssi_max:-37
said: 5 | 0x00000012 espnow violated predicted:-36 observed:-44
percept: 5 | 0x00000012 | link_stable | espnow | - | -
said: 6 | 0x00000012 ble met predicted:-54 observed:-56
percept: 6 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON506 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4506515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:4619120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:25 rssi_min:-52 rssi_med:-47 rssi_max:-41
said: 3 | 0x00000012 espnow unobserved predicted:-44 observed:-44
percept: 3 | 0x00000012 | link_stable | espnow | ? | -
said: 4 | 0x00000012 ble unobserved predicted:-56 observed:-56
percept: 4 | 0x00000012 | link_stable | ble | ? | -
said: 5 | 0x00000100 espnow met predicted:-43 observed:-47
percept: 5 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON8242 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4517259 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:4629864 stream:0xc909d5a8 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-97
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689,64677217947d,7236bc441422,5ce28c488e0c
said: 13 | **COVERED** windows:1 entities:8 window_ms:600089 first_t_ms:4029865 last_t_ms:4029865 covered_by:@LAT103LON8241
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-88 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
```

---

@LAT103LON507 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4566515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:4679120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-54 rssi_med:-43 rssi_max:-41
said: 3 | 0x00000100 espnow met predicted:-47 observed:-43
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON508 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4626515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:4739120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-56 rssi_med:-46 rssi_max:-37
said: 3 | 0x00000100 espnow met predicted:-43 observed:-46
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON509 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4686515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:4799120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-51 rssi_med:-45 rssi_max:-44
said: 3 | 0x00000100 espnow met predicted:-46 observed:-45
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON510 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4746515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:4859120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-46 rssi_med:-44 rssi_max:-41
said: 3 | 0x00000100 espnow met predicted:-45 observed:-44
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON511 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4806515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:4919120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-56 rssi_med:-45 rssi_max:-39
said: 3 | 0x00000100 espnow met predicted:-44 observed:-45
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON512 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4866515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:4979120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-60 rssi_med:-50 rssi_max:-43
said: 3 | 0x00000100 espnow met predicted:-45 observed:-50
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON513 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4926515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5039120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 3 | 0x00000100 espnow met predicted:-50 observed:-44
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON514 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4986515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5099120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-51 rssi_med:-49 rssi_max:-39
said: 3 | 0x00000100 espnow met predicted:-44 observed:-49
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON515 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5046515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5159120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-54 rssi_med:-42 rssi_max:-37
said: 3 | 0x00000100 espnow violated predicted:-49 observed:-42
percept: 3 | 0x00000100 | link_stable | espnow | - | -
```

---

@LAT103LON516 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5106515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5219120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-58 rssi_med:-48 rssi_max:-38
said: 3 | 0x00000100 espnow met predicted:-42 observed:-48
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON8243 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5117260 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:5229865 stream:0xc909d5a8 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,c2e94427adcf,5ce28c488e0c
```

---

@LAT103LON517 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5166515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5279120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-60 rssi_med:-45 rssi_max:-38
said: 3 | 0x00000100 espnow met predicted:-48 observed:-45
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON518 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5226515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5339120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-50 rssi_med:-46 rssi_max:-43
said: 3 | 0x00000100 espnow met predicted:-45 observed:-46
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON519 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5286515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5399120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-48 rssi_med:-46 rssi_max:-44
said: 3 | 0x00000100 espnow met predicted:-46 observed:-46
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON520 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5346515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5459120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 3 | 0x00000100 espnow met predicted:-46 observed:-45
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON521 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5406515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5519120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-49 rssi_med:-40 rssi_max:-35
said: 3 | 0x00000100 espnow met predicted:-45 observed:-40
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON522 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5466515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5579120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-49 rssi_med:-41 rssi_max:-38
said: 3 | 0x00000100 espnow met predicted:-40 observed:-41
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON523 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5526515 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5639120 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-46 rssi_med:-43 rssi_max:-39
said: 3 | 0x00000100 espnow met predicted:-41 observed:-43
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON524 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5586517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5699122 stream:0xc909d5a8 wall:0 window_ms:60002
said: 2 | **LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-45 rssi_med:-41 rssi_max:-38
said: 3 | 0x00000100 espnow met predicted:-43 observed:-41
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON525 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5646517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5759122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-55 rssi_med:-41 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:ble n:48 rssi_min:-81 rssi_med:-45 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-46 rssi_med:-26 rssi_max:-25
said: 5 | 0x00000100 espnow met predicted:-41 observed:-41
percept: 5 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON526 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5706517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5819122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-41 rssi_max:-39
said: 3 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-57 rssi_med:-51 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-28 rssi_med:-26 rssi_max:-26
said: 5 | 0x00000100 espnow violated predicted:-41 observed:-51
percept: 5 | 0x00000100 | link_stable | espnow | - | -
said: 6 | 0x00000200 ble met predicted:-45 observed:-41
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON8244 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5717260 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:5829865 stream:0xc909d5a8 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,e6b32d2cea8b,5ce28c488e0c,0283cce0e689,980d67f79619,c2e94427adcf
```

---

@LAT103LON527 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5766517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5879122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-49 rssi_med:-46 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-46 rssi_med:-41 rssi_max:-39
said: 4 | **LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-27 rssi_med:-26 rssi_max:-26
said: 5 | 0x00000200 ble met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-51 observed:-46
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON16400 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5766517 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:5879122 stream:0xc909d5a8 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:26 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28797 window_ms:1740002 moving_permille:0 dev_mean_mg:10 dev_max_mg:51 moving_ms:0 first_t_ms:4139120 last_t_ms:5819122 covered_by:@LAT103LON16399
```

---

@LAT103LON528 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5826517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5939122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-47 rssi_med:-44 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-33 rssi_med:-27 rssi_max:-26
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-44 rssi_max:-38
said: 5 | 0x00000100 espnow met predicted:-46 observed:-44
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-41 observed:-44
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-26 observed:-27
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON529 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5886517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:5999122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-64 rssi_med:-40 rssi_max:-30
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-55 rssi_med:-45 rssi_max:-40
said: 4 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-31 rssi_med:-30 rssi_max:-26
said: 5 | 0x00000100 espnow met predicted:-44 observed:-40
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-27 observed:-30
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-45
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON530 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5946517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:6059122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-46 rssi_med:-36 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-27 rssi_med:-26 rssi_max:-26
said: 4 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-41 rssi_max:-39
said: 5 | 0x00000100 espnow met predicted:-40 observed:-36
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-45 observed:-41
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-30 observed:-26
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON531 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6006517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:6119122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-46 rssi_med:-41 rssi_max:-37
said: 3 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-47 rssi_med:-36 rssi_max:-32
said: 4 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-26 rssi_med:-26 rssi_max:-25
said: 5 | 0x00000100 espnow met predicted:-36 observed:-36
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-41 observed:-41
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON532 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6066517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:6179122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-47 rssi_med:-39 rssi_max:-33
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-79 rssi_med:-40 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-27 rssi_med:-26 rssi_max:-25
said: 5 | 0x00000200 ble met predicted:-41 observed:-40
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-36 observed:-39
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON533 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6126517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:6239122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-49 rssi_med:-45 rssi_max:-32
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-41 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-26 rssi_med:-26 rssi_max:-26
said: 5 | 0x00000100 espnow met predicted:-39 observed:-45
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-40 observed:-41
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON534 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6186517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:6299122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-82 rssi_med:-41 rssi_max:-38
said: 3 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-43 rssi_med:-35 rssi_max:-32
said: 4 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-28 rssi_med:-26 rssi_max:-26
said: 5 | 0x00000100 espnow violated predicted:-45 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | - | -
said: 6 | 0x00000200 ble met predicted:-41 observed:-41
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON535 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6246517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:6359122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-47 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-44 rssi_med:-39 rssi_max:-37
said: 4 | **LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-27 rssi_med:-26 rssi_max:-26
said: 5 | 0x00000200 ble met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-39
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON536 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6306517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:6419122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-41 rssi_max:-39
said: 3 | **LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-45 rssi_med:-40 rssi_max:-37
said: 4 | **LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-27 rssi_med:-27 rssi_max:-26
said: 5 | 0x00000200 ble met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-39 observed:-40
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-26 observed:-27
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON8245 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6317260 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:6429865 stream:0xc909d5a8 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,5ce28c488e0c,0283cce0e689,bc102f237ace
```

---

@LAT103LON537 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6366517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:6479122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-42 rssi_med:-39 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-78 rssi_med:-41 rssi_max:-39
said: 4 | **LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-31 rssi_med:-27 rssi_max:-26
said: 5 | 0x00000200 ble met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-40 observed:-39
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-27 observed:-27
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON538 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6426517 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:6539122 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:10 rssi_min:-52 rssi_med:-43 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:ble n:30 rssi_min:-59 rssi_med:-43 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:espnow n:11 rssi_min:-45 rssi_med:-27 rssi_max:-26
said: 5 | 0x00000100 espnow met predicted:-39 observed:-43
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-41 observed:-43
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-27 observed:-27
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24873 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8946525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9059130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3746 rate:8000
said: 2 | **ACOUSTIC** rms_mean:84 rms_max:166 peak:427 transients:0
```

---

@LAT103LON24874 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9006525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9119130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3747 rate:8000
said: 2 | **ACOUSTIC** rms_mean:109 rms_max:738 peak:1879 transients:0
```

---

@LAT103LON24875 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9066525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9179130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3748 rate:8000
said: 2 | **ACOUSTIC** rms_mean:209 rms_max:4396 peak:13109 transients:16
said: 3 | **TRANSIENT** t_ms:9161187 stream:0xc909d5a8 wall:0 rms:4396
```

---

@LAT103LON24876 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9126525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9239130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3746 rate:8000
said: 2 | **ACOUSTIC** rms_mean:455 rms_max:32767 peak:32768 transients:60
said: 3 | **TRANSIENT** t_ms:9190851 stream:0xc909d5a8 wall:0 rms:32767
```

---

@LAT103LON24877 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9186525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9299130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3739 rate:8000
said: 2 | **ACOUSTIC** rms_mean:211 rms_max:16524 peak:32768 transients:27
said: 3 | **TRANSIENT** t_ms:9273041 stream:0xc909d5a8 wall:0 rms:16524
```

---

@LAT103LON24878 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9246525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9359130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3746 rate:8000
said: 2 | **ACOUSTIC** rms_mean:124 rms_max:4716 peak:10356 transients:3
said: 3 | **TRANSIENT** t_ms:9355808 stream:0xc909d5a8 wall:0 rms:4716
```

---

@LAT103LON24879 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9306525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9419130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3746 rate:8000
said: 2 | **ACOUSTIC** rms_mean:156 rms_max:2386 peak:5450 transients:15
said: 3 | **TRANSIENT** t_ms:9390196 stream:0xc909d5a8 wall:0 rms:2386
```

---

@LAT103LON8246 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9317260 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:9429865 stream:0xc909d5a8 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689,02c57d2f9717,5ce28c488e0c
said: 13 | **COVERED** windows:4 entities:10 window_ms:2400001 first_t_ms:7029865 last_t_ms:8829866 covered_by:@LAT103LON8245
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-39 windows:4
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-69 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-78 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-73 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-87 windows:4
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:3 rssi:-90 windows:3
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-92 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-90 windows:4
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-90 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2f9717 n:2 rssi:-94 windows:2
```

---

@LAT103LON539 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9355248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:9467853 stream:0xc909d5a8 wall:0 window_ms:2928731
said: 2 | **LINK** peer:0x00000200 proto:ble n:1 rssi_min:-50 rssi_med:-50 rssi_max:-50
said: 3 | 0x00000100 espnow unobserved predicted:-43 observed:-43
percept: 3 | 0x00000100 | link_stable | espnow | ? | -
said: 4 | 0x00000200 ble violated predicted:-43 observed:-50
percept: 4 | 0x00000200 | link_stable | ble | - | -
said: 5 | 0x00000200 espnow unobserved predicted:-27 observed:-27
percept: 5 | 0x00000200 | link_stable | espnow | ? | -
```

---

@LAT103LON24880 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9366525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9479130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3732 rate:8000
said: 2 | **ACOUSTIC** rms_mean:308 rms_max:19516 peak:32768 transients:44
said: 3 | **TRANSIENT** t_ms:9431959 stream:0xc909d5a8 wall:0 rms:19516
```

---

@LAT103LON540 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9415248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:9527853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-41 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-25 rssi_med:-25 rssi_max:-25
said: 4 | 0x00000200 ble violated predicted:-50 observed:-41
percept: 4 | 0x00000200 | link_stable | ble | - | -
```

---

@LAT103LON24881 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9426525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9539130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3605 rate:8000
said: 2 | **ACOUSTIC** rms_mean:232 rms_max:22919 peak:32768 transients:10
said: 3 | **TRANSIENT** t_ms:9505739 stream:0xc909d5a8 wall:0 rms:22919
```

---

@LAT103LON541 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9475248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:9587853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:46 rssi_min:-45 rssi_med:-40 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:espnow n:3 rssi_min:-26 rssi_med:-26 rssi_max:-25
said: 4 | 0x00000200 ble met predicted:-41 observed:-40
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-25 observed:-26
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24882 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9486525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9599130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3741 rate:8000
said: 2 | **ACOUSTIC** rms_mean:213 rms_max:3154 peak:7850 transients:10
said: 3 | **TRANSIENT** t_ms:9581150 stream:0xc909d5a8 wall:0 rms:3154
```

---

@LAT103LON542 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9535248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:9647853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-26 rssi_med:-26 rssi_max:-26
said: 3 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-41 rssi_max:-38
said: 4 | 0x00000200 ble met predicted:-40 observed:-41
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24883 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9546525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9659130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3744 rate:8000
said: 2 | **ACOUSTIC** rms_mean:183 rms_max:8015 peak:14931 transients:13
said: 3 | **TRANSIENT** t_ms:9611084 stream:0xc909d5a8 wall:0 rms:8015
```

---

@LAT103LON543 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9595248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:9707853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-79 rssi_med:-41 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-27 rssi_med:-26 rssi_max:-26
said: 4 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24884 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9606525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9719130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3621 rate:8000
said: 2 | **ACOUSTIC** rms_mean:207 rms_max:6765 peak:23571 transients:7
said: 3 | **TRANSIENT** t_ms:9676621 stream:0xc909d5a8 wall:0 rms:6765
```

---

@LAT103LON544 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9655248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:9767853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-41 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-27 rssi_med:-26 rssi_max:-26
said: 4 | 0x00000200 ble met predicted:-41 observed:-41
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24885 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9666525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9779130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3744 rate:8000
said: 2 | **ACOUSTIC** rms_mean:220 rms_max:18419 peak:32768 transients:12
said: 3 | **TRANSIENT** t_ms:9759076 stream:0xc909d5a8 wall:0 rms:18419
```

---

@LAT103LON545 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9715248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:9827853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-27 rssi_med:-26 rssi_max:-26
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-41 rssi_max:-39
said: 4 | 0x00000200 ble met predicted:-41 observed:-41
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24886 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9726525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9839130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:153 rms_max:734 peak:1108 transients:0
```

---

@LAT103LON546 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9775248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:9887853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-46 rssi_med:-41 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-26 rssi_med:-26 rssi_max:-26
said: 4 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24887 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9786525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9899130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3733 rate:8000
said: 2 | **ACOUSTIC** rms_mean:153 rms_max:308 peak:794 transients:0
```

---

@LAT103LON547 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9835248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:9947853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-41 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-26 rssi_med:-26 rssi_max:-26
said: 4 | 0x00000200 ble met predicted:-41 observed:-41
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24888 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9846525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:9959130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3744 rate:8000
said: 2 | **ACOUSTIC** rms_mean:145 rms_max:2336 peak:2619 transients:2
said: 3 | **TRANSIENT** t_ms:9957020 stream:0xc909d5a8 wall:0 rms:2184
```

---

@LAT104LON89 | created:0 | updated:0

**carried through @LAT103LON503**

```ttdb-carried
through: 503
through: 8200
through: 24872
carried: 294 0 493 216 | 0x00000200 | link_stable | espnow
carried: 357 2 715 228 | 0x00000200 | link_stable | ble
carried: 236 0 589 104 | 0x00000100 | link_stable | espnow
carried: 382 6 742 257 | 0x00000010 | link_stable | ble
carried: 373 13 739 256 | 0x00000010 | link_stable | espnow
carried: 22 0 22 26 | 0x00000011 | link_stable | ble
carried: 19 3 22 26 | 0x00000011 | link_stable | espnow
carried: 42 1 43 44 | 0x00000012 | link_stable | ble
carried: 41 1 42 42 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON548 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9895248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:10007853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-27 rssi_med:-26 rssi_max:-25
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-41 rssi_max:-38
said: 4 | 0x00000200 ble met predicted:-41 observed:-41
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24889 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9906525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:10019130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3735 rate:8000
said: 2 | **ACOUSTIC** rms_mean:136 rms_max:924 peak:2627 transients:1
said: 3 | **TRANSIENT** t_ms:9981168 stream:0xc909d5a8 wall:0 rms:924
```

---

@LAT103LON8247 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9917261 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:10029866 stream:0xc909d5a8 wall:0 window_ms:600001 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,84a329c78fec,0283cce0e689,e6b32d2cea8b,02c57d2f9717
```

---

@LAT103LON549 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9955248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:10067853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-58 rssi_med:-41 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-37 rssi_med:-26 rssi_max:-25
said: 4 | 0x00000200 espnow met predicted:-26 observed:-26
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24890 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9966525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:10079130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3739 rate:8000
said: 2 | **ACOUSTIC** rms_mean:286 rms_max:22150 peak:32768 transients:25
said: 3 | **TRANSIENT** t_ms:10056759 stream:0xc909d5a8 wall:0 rms:20762
```

---

@LAT103LON550 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10015248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:10127853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-39 rssi_med:-36 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:49 rssi_min:-80 rssi_med:-54 rssi_max:-52
said: 4 | 0x00000200 ble violated predicted:-41 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | - | -
said: 5 | 0x00000200 espnow violated predicted:-26 observed:-36
percept: 5 | 0x00000200 | link_stable | espnow | - | -
```

---

@LAT103LON24891 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10026525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:10139130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3742 rate:8000
said: 2 | **ACOUSTIC** rms_mean:160 rms_max:1354 peak:2611 transients:1
said: 3 | **TRANSIENT** t_ms:10128720 stream:0xc909d5a8 wall:0 rms:1354
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:3 half_life_ms:600000 reinforced:0 last_ms:6076466
t_ms:10144563 stream:0xc909d5a8 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0000 cap_epoch:5
**TRACE** copresence:255 half_life_ms:600000 reinforced:122 last_ms:9727611
t_ms:10144563 stream:0xc909d5a8 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:2415410
t_ms:10144563 stream:0xc909d5a8 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:3010101
t_ms:10144563 stream:0xc909d5a8 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:4103353
t_ms:10144563 stream:0xc909d5a8 wall:0

---

@LAT103LON551 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10075248 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:10187853 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:46 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:2 rssi_min:-38 rssi_med:-38 rssi_max:-36
said: 4 | 0x00000200 espnow met predicted:-36 observed:-38
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-54 observed:-54
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24892 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10086525 ±0 frame:4000
said: 1 | **ACOUSTICWIN** t_ms:10199130 stream:0xc909d5a8 wall:0 window_ms:60000 blocks:3600 rate:8000
said: 2 | **ACOUSTIC** rms_mean:362 rms_max:17302 peak:32768 transients:12
said: 3 | **TRANSIENT** t_ms:10169947 stream:0xc909d5a8 wall:0 rms:17302
```
