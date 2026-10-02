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

@LAT103LON8192 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:7034724 stream:0xee98fca8 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8193 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60001 ±0 frame:17500
said: 1 | **ENTWIN** t_ms:7159812 stream:0xee98fca8 wall:0 window_ms:60001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:46 last_lon:45 t_ms:7440342 stream:0xee98fca8 wall:0 node:0x00000300

---


---

@LAT103LON8194 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7483868 ±0 frame:5000
said: 1 | **ENTWIN** t_ms:7553285 stream:0xee98fca8 wall:0 window_ms:98613 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 12 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 13 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 14 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 15 | **CORE** entities:0
```

---

@LAT103LON8195 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 62632 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:8548219 stream:0xee98fca8 wall:0 window_ms:62632 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x88023c58 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT103LON8196 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:50583 stream:0x88023c58 wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8197 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1213636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:1204219 stream:0x88023c58 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,84a329c78fec,0283cce0e689,e6b32d2cea8b
said: 14 | **COVERED** windows:1 entities:10 window_ms:553636 first_t_ms:604219 last_t_ms:604219 covered_by:@LAT103LON8196
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
```

---

@LAT103LON8198 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1813635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:1804218 stream:0x88023c58 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,c2e94427adcf,84a329c78fec,0283cce0e689
```

---

@LAT103LON8199 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2413635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:2404218 stream:0x88023c58 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,5ce28c488e0c,e6b32d2cea8b,c2e94427adcf,0283cce0e689,84a329c78fec
```

---

@LAT103LON8200 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3013636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:3004219 stream:0x88023c58 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,5ce28c488e0c,c2e94427adcf,0283cce0e689
```

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

@LAT103LON24666 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5406034 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6338139 stream:0x92fb56ae wall:0 window_ms:62023 blocks:1251 rate:8000
said: 2 | **ACOUSTIC** rms_mean:127 rms_max:2581 peak:3439 transients:5
said: 3 | **TRANSIENT** t_ms:6324369 stream:0x92fb56ae wall:0 rms:2581
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

@LAT103LON24667 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5468081 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6400186 stream:0x92fb56ae wall:0 window_ms:62047 blocks:243 rate:8000
said: 2 | **ACOUSTIC** rms_mean:96 rms_max:204 peak:502 transients:0
```

---

@LAT103LON24668 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5528129 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6460234 stream:0x92fb56ae wall:0 window_ms:60048 blocks:255 rate:8000
said: 2 | **ACOUSTIC** rms_mean:109 rms_max:256 peak:467 transients:0
```

---

@LAT103LON24669 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5592017 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6524122 stream:0x92fb56ae wall:0 window_ms:63888 blocks:239 rate:8000
said: 2 | **ACOUSTIC** rms_mean:106 rms_max:169 peak:502 transients:0
```

---

@LAT103LON24670 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5654002 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6586107 stream:0x92fb56ae wall:0 window_ms:61985 blocks:361 rate:8000
said: 2 | **ACOUSTIC** rms_mean:139 rms_max:1647 peak:2117 transients:2
said: 3 | **TRANSIENT** t_ms:6554237 stream:0x92fb56ae wall:0 rms:1647
```

---

@LAT103LON24671 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5715628 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6647733 stream:0x92fb56ae wall:0 window_ms:61626 blocks:233 rate:8000
said: 2 | **ACOUSTIC** rms_mean:165 rms_max:1558 peak:3761 transients:2
said: 3 | **TRANSIENT** t_ms:6643662 stream:0x92fb56ae wall:0 rms:1558
```

---

@LAT103LON24672 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5778131 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6710236 stream:0x92fb56ae wall:0 window_ms:62503 blocks:58 rate:8000
said: 2 | **ACOUSTIC** rms_mean:113 rms_max:235 peak:522 transients:0
```

---

@LAT103LON24673 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5840011 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6772116 stream:0x92fb56ae wall:0 window_ms:61880 blocks:238 rate:8000
said: 2 | **ACOUSTIC** rms_mean:97 rms_max:194 peak:385 transients:0
```

---

@LAT103LON24674 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5902001 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6834106 stream:0x92fb56ae wall:0 window_ms:61990 blocks:383 rate:8000
said: 2 | **ACOUSTIC** rms_mean:106 rms_max:465 peak:1319 transients:0
```

---

@LAT103LON24675 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5962001 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6894106 stream:0x92fb56ae wall:0 window_ms:60000 blocks:1700 rate:8000
said: 2 | **ACOUSTIC** rms_mean:120 rms_max:547 peak:1546 transients:0
```

---

@LAT103LON24676 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 6022001 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6954106 stream:0x92fb56ae wall:0 window_ms:60000 blocks:2850 rate:8000
said: 2 | **ACOUSTIC** rms_mean:132 rms_max:777 peak:3058 transients:0
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

@LAT103LON24677 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 6213347 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:7145408 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3399 rate:8000
said: 2 | **ACOUSTIC** rms_mean:187 rms_max:1286 peak:3062 transients:1
said: 3 | **TRANSIENT** t_ms:7116569 stream:0x92fb56ae wall:0 rms:1069
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

@LAT103LON24678 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 6273347 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:7205408 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3720 rate:8000
said: 2 | **ACOUSTIC** rms_mean:101 rms_max:407 peak:1096 transients:0
```

---

@LAT103LON24679 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 6333347 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:7265408 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3731 rate:8000
said: 2 | **ACOUSTIC** rms_mean:100 rms_max:1756 peak:7719 transients:1
said: 3 | **TRANSIENT** t_ms:7221987 stream:0x92fb56ae wall:0 rms:912
```

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

@LAT103LON24680 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 6393347 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:7325408 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3625 rate:8000
said: 2 | **ACOUSTIC** rms_mean:160 rms_max:4552 peak:21265 transients:3
said: 3 | **TRANSIENT** t_ms:7265921 stream:0x92fb56ae wall:0 rms:4552
```

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

@LAT103LON24681 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 6453347 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:7385408 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3708 rate:8000
said: 2 | **ACOUSTIC** rms_mean:134 rms_max:3861 peak:5317 transients:6
said: 3 | **TRANSIENT** t_ms:7371059 stream:0x92fb56ae wall:0 rms:3861
```

---

@LAT103LON24682 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 6513347 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:7445408 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3615 rate:8000
said: 2 | **ACOUSTIC** rms_mean:113 rms_max:1694 peak:5778 transients:3
said: 3 | **TRANSIENT** t_ms:7392731 stream:0x92fb56ae wall:0 rms:1694
```

---


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

@LAT103LON360 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7668030 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:8602080 stream:0x92fb56ae wall:0 window_ms:60005
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-79 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 5 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 6 | 0x00000200 ble met predicted:-54 observed:-55
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON361 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7728031 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:8662081 stream:0x92fb56ae wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-82 rssi_med:-59 rssi_max:-58
said: 5 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | 0x00000200 ble met predicted:-55 observed:-55
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON362 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7788031 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:8722081 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-55 rssi_max:-53
said: 5 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 6 | 0x00000200 ble met predicted:-55 observed:-55
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-59 observed:-59
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON363 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7848042 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:8782092 stream:0x92fb56ae wall:0 window_ms:60011
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-59 rssi_max:-58
said: 3 | **LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-83 rssi_med:-55 rssi_max:-52
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000200 ble met predicted:-55 observed:-55
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON364 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7908042 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:8842092 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 6 | 0x00000010 ble met predicted:-59 observed:-59
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000200 ble met predicted:-55 observed:-54
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON365 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7968068 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:8902118 stream:0x92fb56ae wall:0 window_ms:60026
said: 2 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-59 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-42 rssi_med:-41 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 5 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-79 rssi_med:-59 rssi_max:-57
said: 6 | 0x00000010 espnow met predicted:-42 observed:-41
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000200 ble met predicted:-54 observed:-55
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON366 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8028197 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:8962247 stream:0x92fb56ae wall:0 window_ms:60129
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 6 | 0x00000200 ble met predicted:-55 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-41 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON367 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8088197 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9022247 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-80 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 6 | 0x00000200 ble met predicted:-54 observed:-55
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

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

@LAT103LON368 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8148206 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9082256 stream:0x92fb56ae wall:0 window_ms:60009
said: 2 | **LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-42 rssi_med:-41 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-59 rssi_max:-58
said: 5 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-80 rssi_med:-54 rssi_max:-52
said: 6 | 0x00000200 ble met predicted:-55 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-41
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON369 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8208206 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9142256 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-59 rssi_max:-58
said: 5 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 6 | 0x00000010 espnow met predicted:-41 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-59 observed:-59
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000200 ble met predicted:-54 observed:-55
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON370 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8268207 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9202257 stream:0x92fb56ae wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-59 rssi_max:-58
said: 3 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-59 observed:-59
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000200 ble met predicted:-55 observed:-55
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON371 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8328208 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9262258 stream:0x92fb56ae wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 4 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-59 rssi_max:-57
said: 5 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | 0x00000010 ble met predicted:-59 observed:-59
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000200 ble met predicted:-55 observed:-55
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON372 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8388213 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9322263 stream:0x92fb56ae wall:0 window_ms:60005
said: 2 | **LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-59 rssi_med:-55 rssi_max:-52
said: 5 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-59 rssi_max:-58
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-55 observed:-55
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000010 ble met predicted:-59 observed:-59
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON373 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8448213 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9382263 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-59 rssi_max:-58
said: 3 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-79 rssi_med:-54 rssi_max:-52
said: 5 | **LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000200 ble met predicted:-55 observed:-54
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON374 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8508213 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9442263 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 5 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-59 rssi_max:-58
said: 6 | 0x00000010 ble met predicted:-59 observed:-59
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 ble met predicted:-54 observed:-54
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON375 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8568216 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9502266 stream:0x92fb56ae wall:0 window_ms:60003
said: 2 | **LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-59 rssi_med:-54 rssi_max:-52
said: 4 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-79 rssi_med:-59 rssi_max:-57
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000200 ble met predicted:-54 observed:-54
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON376 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8628216 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9562266 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 5 | **LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-54 observed:-55
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON377 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8701962 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9636012 stream:0x92fb56ae wall:0 window_ms:73746
said: 2 | **LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:ble n:78 rssi_min:-80 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:ble n:82 rssi_min:-79 rssi_med:-55 rssi_max:-52
said: 5 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000200 ble met predicted:-55 observed:-55
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
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

@LAT103LON378 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8761962 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9696012 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-60 rssi_med:-59 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-59 rssi_med:-55 rssi_max:-53
said: 4 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-42 rssi_med:-41 rssi_max:-41
said: 6 | 0x00000010 espnow met predicted:-42 observed:-41
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000200 ble met predicted:-55 observed:-55
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
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

@LAT103LON379 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8821962 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9756012 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:71 rssi_min:-81 rssi_med:-59 rssi_max:-58
said: 3 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-79 rssi_med:-55 rssi_max:-52
said: 6 | 0x00000010 ble met predicted:-59 observed:-59
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000200 ble met predicted:-55 observed:-55
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 espnow met predicted:-41 observed:-42
percept: 9 | 0x00000010 | link_stable | espnow | + | -
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

@LAT103LON380 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8881962 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9816012 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-62 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-70 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 5 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | 0x00000010 ble met predicted:-59 observed:-59
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000200 ble met predicted:-55 observed:-54
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

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

@LAT103LON381 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8941962 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9876012 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 5 | **LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 6 | 0x00000200 ble met predicted:-54 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON382 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9001962 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9936012 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 4 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000200 ble met predicted:-54 observed:-55
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON383 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9061962 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:9996012 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:73 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 5 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-55 observed:-55
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON384 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9121962 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10056012 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-80 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 6 | 0x00000200 ble met predicted:-55 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON385 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9181962 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10116012 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-79 rssi_med:-59 rssi_max:-58
said: 3 | **LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-59 rssi_med:-55 rssi_max:-52
said: 5 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | 0x00000200 ble met predicted:-54 observed:-55
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON386 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9241962 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10176012 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-59 rssi_max:-58
said: 5 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-59 rssi_med:-54 rssi_max:-52
said: 6 | 0x00000010 ble met predicted:-59 observed:-59
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 ble met predicted:-55 observed:-54
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON387 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9302085 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10236135 stream:0x92fb56ae wall:0 window_ms:60123
said: 2 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 3 | **LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-54 rssi_max:-52
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-59 observed:-59
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000200 ble met predicted:-54 observed:-54
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

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

@LAT103LON388 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9362085 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10296135 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 6 | 0x00000010 ble met predicted:-59 observed:-59
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000200 ble met predicted:-54 observed:-54
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON389 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9422088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10356138 stream:0x92fb56ae wall:0 window_ms:60003
said: 2 | **LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 5 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-59 rssi_max:-58
said: 6 | 0x00000200 ble met predicted:-54 observed:-55
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 espnow met predicted:-42 observed:-41
percept: 9 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON390 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9482088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10416138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-59 rssi_max:-58
said: 3 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-62 rssi_med:-55 rssi_max:-52
said: 6 | 0x00000010 espnow met predicted:-41 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000200 ble met predicted:-55 observed:-55
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON391 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9542088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10476138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 5 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | 0x00000010 ble met predicted:-59 observed:-59
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000200 ble met predicted:-55 observed:-55
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON392 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9602088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10536138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-59 rssi_med:-55 rssi_max:-52
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000200 ble met predicted:-55 observed:-55
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON393 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9662088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10596138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000200 ble met predicted:-55 observed:-55
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON394 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9722088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10656138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-59 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-59 rssi_max:-58
said: 6 | 0x00000200 ble met predicted:-55 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON395 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9782088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10716138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000010 proto:ble n:72 rssi_min:-82 rssi_med:-59 rssi_max:-58
said: 5 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-55 rssi_max:-52
said: 6 | 0x00000200 ble met predicted:-54 observed:-55
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON396 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9842088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10776138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-80 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 6 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-38 observed:-38
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-59 observed:-59
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000200 ble met predicted:-55 observed:-55
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON397 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9902088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10836138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-80 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-45 rssi_med:-43 rssi_max:-41
said: 4 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 5 | **LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-44 rssi_med:-41 rssi_max:-38
said: 6 | 0x00000200 ble met predicted:-55 observed:-55
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-59 observed:-61
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000200 espnow met predicted:-38 observed:-41
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 espnow met predicted:-42 observed:-43
percept: 9 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON398 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9962088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10896138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-80 rssi_med:-60 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-79 rssi_med:-54 rssi_max:-52
said: 4 | **LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-44 rssi_med:-43 rssi_max:-40
said: 5 | **LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-41 rssi_med:-39 rssi_max:-37
said: 6 | 0x00000200 ble met predicted:-55 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-43 observed:-43
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-61 observed:-60
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-41 observed:-39
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON399 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10022088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:10956138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-63 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-46 rssi_med:-43 rssi_max:-40
said: 4 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-40 rssi_med:-39 rssi_max:-37
said: 5 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-80 rssi_med:-60 rssi_max:-55
said: 6 | 0x00000010 ble met predicted:-60 observed:-60
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000200 ble met predicted:-54 observed:-54
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-43 observed:-43
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-39 observed:-39
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT104LON49 | created:0 | updated:0

**carried through @LAT103LON359**

```ttdb-carried
through: 359
through: 24665
carried: 224 0 423 146 | 0x00000200 | link_stable | espnow
carried: 287 2 645 158 | 0x00000200 | link_stable | ble
carried: 236 0 589 104 | 0x00000100 | link_stable | espnow
carried: 276 1 631 144 | 0x00000010 | link_stable | ble
carried: 270 6 629 144 | 0x00000010 | link_stable | espnow
carried: 4 0 4 6 | 0x00000011 | link_stable | ble
carried: 3 1 4 6 | 0x00000011 | link_stable | espnow
carried: 27 1 28 28 | 0x00000012 | link_stable | ble
carried: 26 1 27 27 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON400 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10082088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11016138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-44 rssi_med:-43 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-80 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-40 rssi_med:-39 rssi_max:-37
said: 5 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-79 rssi_med:-60 rssi_max:-56
said: 6 | 0x00000200 ble met predicted:-54 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-43 observed:-43
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-39 observed:-39
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 ble met predicted:-60 observed:-60
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON401 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10142088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11076138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-59 rssi_med:-59 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-55 rssi_max:-53
said: 4 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 6 | 0x00000010 espnow met predicted:-43 observed:-40
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-54 observed:-55
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000200 espnow met predicted:-39 observed:-41
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 ble met predicted:-60 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON402 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10202088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11136138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-56 rssi_max:-53
said: 3 | **LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 4 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-79 rssi_med:-59 rssi_max:-56
said: 5 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-41 rssi_med:-41 rssi_max:-40
said: 6 | 0x00000010 ble met predicted:-59 observed:-59
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000200 ble met predicted:-55 observed:-56
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON403 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10262088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11196138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-59 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-45 rssi_med:-40 rssi_max:-39
said: 4 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-56 rssi_max:-53
said: 6 | 0x00000200 ble met predicted:-56 observed:-56
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-59 observed:-59
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-41 observed:-40
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON404 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10322088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11256138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-44 rssi_med:-40 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-63 rssi_med:-55 rssi_max:-54
said: 4 | **LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-44 rssi_med:-41 rssi_max:-40
said: 5 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 6 | 0x00000010 ble met predicted:-59 observed:-59
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-40 observed:-41
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000200 ble met predicted:-56 observed:-55
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON405 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10382088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11316138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-41 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-61 rssi_med:-57 rssi_max:-55
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-79 rssi_med:-56 rssi_max:-54
said: 5 | **LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 6 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-55 observed:-56
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-57
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON406 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10442088 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11376138 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-41 rssi_med:-41 rssi_max:-40
said: 4 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-64 rssi_med:-55 rssi_max:-54
said: 5 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-59 rssi_max:-56
said: 6 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-57 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000200 ble met predicted:-56 observed:-55
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 9 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:11419919 stream:0x92fb56ae wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:562 last_ms:3596980
t_ms:11419919 stream:0x92fb56ae wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:527 last_ms:3596652
t_ms:11419919 stream:0x92fb56ae wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:11419919 stream:0x92fb56ae wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:11419919 stream:0x92fb56ae wall:0

---

@LAT103LON407 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10502093 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11436143 stream:0x92fb56ae wall:0 window_ms:60005
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-63 rssi_med:-55 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 4 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-59 rssi_max:-56
said: 5 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 6 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000200 ble met predicted:-55 observed:-55
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000010 ble met predicted:-59 observed:-59
percept: 9 | 0x00000010 | link_stable | ble | + | -
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

@LAT103LON408 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10562093 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11496143 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-64 rssi_med:-55 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-61 rssi_med:-57 rssi_max:-56
said: 4 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 6 | 0x00000200 ble met predicted:-55 observed:-55
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-59 observed:-57
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT104LON50 | created:0 | updated:0

**carried through @LAT103LON368**

```ttdb-carried
through: 368
through: 24665
carried: 233 0 432 155 | 0x00000200 | link_stable | espnow
carried: 296 2 654 167 | 0x00000200 | link_stable | ble
carried: 236 0 589 104 | 0x00000100 | link_stable | espnow
carried: 285 1 640 153 | 0x00000010 | link_stable | ble
carried: 279 6 638 153 | 0x00000010 | link_stable | espnow
carried: 4 0 4 6 | 0x00000011 | link_stable | ble
carried: 3 1 4 6 | 0x00000011 | link_stable | espnow
carried: 27 1 28 28 | 0x00000012 | link_stable | ble
carried: 26 1 27 27 | 0x00000012 | link_stable | espnow
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

@LAT103LON409 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10622093 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11556143 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-61 rssi_med:-59 rssi_max:-56
said: 4 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 5 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-54
said: 6 | 0x00000200 ble met predicted:-55 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-57 observed:-59
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 9 | 0x00000200 | link_stable | espnow | + | -
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
