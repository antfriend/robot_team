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

---

@LAT103LON410 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10795104 ±21 frame:6000
said: 1 | **LINKWIN** t_ms:11729173 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-77 rssi_med:-55 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 4 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-61 rssi_med:-57 rssi_max:-56
said: 5 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-42 rssi_med:-41 rssi_max:-40
```

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

@LAT103LON411 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10855104 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11789173 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-64 rssi_med:-55 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-61 rssi_med:-57 rssi_max:-56
said: 4 | **LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-40 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 6 | 0x00000200 ble met predicted:-55 observed:-55
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-57 observed:-57
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON412 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10915104 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11849173 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-79 rssi_med:-57 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-63 rssi_med:-56 rssi_max:-54
said: 4 | **LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-40 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 6 | 0x00000200 ble met predicted:-55 observed:-56
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-57 observed:-57
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON413 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10975104 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11909173 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-62 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 4 | **LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-45 rssi_med:-41 rssi_max:-40
said: 6 | 0x00000010 ble met predicted:-57 observed:-57
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000200 ble met predicted:-56 observed:-55
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON414 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11035104 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:11969173 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-79 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-68 rssi_med:-57 rssi_max:-53
said: 4 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 5 | **LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 6 | 0x00000010 ble met predicted:-57 observed:-57
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000200 ble met predicted:-55 observed:-55
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-40 observed:-38
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-41 observed:-40
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON415 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11095104 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:12029173 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-80 rssi_med:-56 rssi_max:-53
said: 4 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-45 rssi_med:-41 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-46 rssi_med:-39 rssi_max:-38
said: 6 | 0x00000200 ble met predicted:-55 observed:-56
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-57 observed:-57
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-38 observed:-39
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-40 observed:-41
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON416 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11155104 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:12089173 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-56 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-63 rssi_med:-56 rssi_max:-53
said: 4 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-44 rssi_med:-41 rssi_max:-39
said: 5 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-42 rssi_med:-39 rssi_max:-36
said: 6 | 0x00000010 ble met predicted:-57 observed:-56
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000200 ble met predicted:-56 observed:-56
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 9 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON417 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11518948 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:12455030 stream:0x92fb56ae wall:0 window_ms:62000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-53
said: 4 | **LINK** peer:0x00000010 proto:ble n:49 rssi_min:-65 rssi_med:-57 rssi_max:-55
said: 5 | **LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-42 rssi_med:-39 rssi_max:-38
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

@LAT103LON418 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11582074 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:12518156 stream:0x92fb56ae wall:0 window_ms:63126
said: 2 | **LINK** peer:0x00000200 proto:ble n:72 rssi_min:-82 rssi_med:-55 rssi_max:-54
said: 3 | **LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:ble n:70 rssi_min:-80 rssi_med:-57 rssi_max:-57
said: 5 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 6 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-55 observed:-55
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000010 ble met predicted:-57 observed:-57
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000010 espnow met predicted:-39 observed:-40
percept: 9 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON419 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11644109 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:12580191 stream:0x92fb56ae wall:0 window_ms:62035
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-61 rssi_med:-54 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-81 rssi_med:-57 rssi_max:-57
said: 4 | **LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-41 rssi_med:-39 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 6 | 0x00000200 ble met predicted:-55 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-57 observed:-57
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000010 espnow met predicted:-40 observed:-39
percept: 9 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON420 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11704122 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:12640204 stream:0x92fb56ae wall:0 window_ms:60013
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-61 rssi_med:-54 rssi_max:-54
said: 3 | **LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-42 rssi_med:-40 rssi_max:-37
said: 4 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-60 rssi_med:-57 rssi_max:-57
said: 5 | **LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 6 | 0x00000200 ble met predicted:-54 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-57 observed:-57
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-39 observed:-40
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24693 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11704122 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:12640204 stream:0x92fb56ae wall:0 window_ms:60013 blocks:125 rate:8000
said: 2 | **ACOUSTIC** rms_mean:164 rms_max:1883 peak:2542 transients:2
said: 3 | **TRANSIENT** t_ms:12624106 stream:0x92fb56ae wall:0 rms:1883
```

---

@LAT103LON421 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11764131 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:12700213 stream:0x92fb56ae wall:0 window_ms:60009
said: 2 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-64 rssi_med:-57 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-54 rssi_max:-54
said: 4 | **LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 6 | 0x00000200 ble met predicted:-54 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-57 observed:-57
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 9 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON24694 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11764131 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:12700213 stream:0x92fb56ae wall:0 window_ms:60009 blocks:381 rate:8000
said: 2 | **ACOUSTIC** rms_mean:136 rms_max:500 peak:1037 transients:0
```

---

@LAT103LON422 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11846117 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:12782199 stream:0x92fb56ae wall:0 window_ms:81986
said: 2 | **LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000010 proto:ble n:83 rssi_min:-80 rssi_med:-57 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:ble n:86 rssi_min:-61 rssi_med:-55 rssi_max:-54
said: 5 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 6 | 0x00000010 ble met predicted:-57 observed:-57
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000200 ble met predicted:-54 observed:-55
percept: 7 | 0x00000200 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24695 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11846117 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:12782199 stream:0x92fb56ae wall:0 window_ms:81986 blocks:1374 rate:8000
said: 2 | **ACOUSTIC** rms_mean:99 rms_max:494 peak:1043 transients:0
```

---

@LAT103LON423 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11906117 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:12842199 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-40 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-59 rssi_med:-57 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-55 rssi_max:-54
said: 5 | **LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 6 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-57 observed:-57
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000200 ble met predicted:-55 observed:-55
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24696 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11906117 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:12842199 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3109 rate:8000
said: 2 | **ACOUSTIC** rms_mean:113 rms_max:397 peak:768 transients:0
```

---

@LAT103LON424 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11966117 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:12902199 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-57 rssi_max:-57
said: 3 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-40 rssi_med:-40 rssi_max:-39
said: 4 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 5 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-54 rssi_max:-54
said: 6 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-57 observed:-57
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000200 ble met predicted:-55 observed:-54
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000200 espnow met predicted:-40 observed:-41
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24697 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11966117 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:12902199 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3107 rate:8000
said: 2 | **ACOUSTIC** rms_mean:129 rms_max:774 peak:1542 transients:0
```

---

@LAT103LON425 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12026127 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:12962209 stream:0x92fb56ae wall:0 window_ms:60010
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-60 rssi_med:-57 rssi_max:-57
said: 4 | **LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 6 | 0x00000010 ble met predicted:-57 observed:-57
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-41 observed:-40
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000200 ble met predicted:-54 observed:-54
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24698 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 12026127 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:12962209 stream:0x92fb56ae wall:0 window_ms:60010 blocks:1867 rate:8000
said: 2 | **ACOUSTIC** rms_mean:120 rms_max:721 peak:2775 transients:0
```

---

@LAT103LON426 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12086127 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:13022209 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-40 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-58 rssi_med:-57 rssi_max:-57
said: 5 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-54
said: 6 | 0x00000200 ble met predicted:-54 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-57 observed:-57
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-40 observed:-41
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24699 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 12086127 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:13022209 stream:0x92fb56ae wall:0 window_ms:60000 blocks:2865 rate:8000
said: 2 | **ACOUSTIC** rms_mean:124 rms_max:382 peak:879 transients:0
```

---

@LAT103LON427 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12146127 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:13082209 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-55 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-57 rssi_max:-57
said: 4 | **LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-40 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 6 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-41 observed:-40
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000010 ble met predicted:-57 observed:-57
percept: 8 | 0x00000010 | link_stable | ble | + | -
said: 9 | 0x00000200 ble met predicted:-54 observed:-55
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24700 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 12146127 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:13082209 stream:0x92fb56ae wall:0 window_ms:60000 blocks:2978 rate:8000
said: 2 | **ACOUSTIC** rms_mean:156 rms_max:984 peak:1903 transients:1
said: 3 | **TRANSIENT** t_ms:13080110 stream:0x92fb56ae wall:0 rms:984
```

---

@LAT103LON428 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12206127 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:13142209 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-57 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-79 rssi_med:-54 rssi_max:-54
said: 5 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-40 rssi_med:-40 rssi_max:-39
said: 6 | 0x00000200 ble met predicted:-55 observed:-54
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000010 ble met predicted:-57 observed:-57
percept: 7 | 0x00000010 | link_stable | ble | + | -
said: 8 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 8 | 0x00000010 | link_stable | espnow | + | -
said: 9 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 9 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24701 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 12206127 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:13142209 stream:0x92fb56ae wall:0 window_ms:60000 blocks:1869 rate:8000
said: 2 | **ACOUSTIC** rms_mean:185 rms_max:963 peak:1659 transients:1
said: 3 | **TRANSIENT** t_ms:13093055 stream:0x92fb56ae wall:0 rms:963
```

---

@LAT103LON429 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12266133 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:13202215 stream:0x92fb56ae wall:0 window_ms:60006
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-79 rssi_med:-57 rssi_max:-57
said: 3 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 4 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 5 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-54 rssi_max:-54
said: 6 | 0x00000010 ble met predicted:-57 observed:-57
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000200 ble met predicted:-54 observed:-54
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 9 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON24702 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 12266133 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:13202215 stream:0x92fb56ae wall:0 window_ms:60006 blocks:3115 rate:8000
said: 2 | **ACOUSTIC** rms_mean:268 rms_max:1633 peak:3472 transients:0
```

---

@LAT103LON430 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12326133 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:13262215 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-45 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-44 rssi_med:-41 rssi_max:-40
said: 4 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-55 rssi_max:-53
said: 5 | **LINK** peer:0x00000010 proto:ble n:51 rssi_min:-74 rssi_med:-58 rssi_max:-54
said: 6 | 0x00000010 ble met predicted:-57 observed:-58
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 7 | 0x00000010 | link_stable | espnow | + | -
said: 8 | 0x00000200 espnow met predicted:-40 observed:-41
percept: 8 | 0x00000200 | link_stable | espnow | + | -
said: 9 | 0x00000200 ble met predicted:-54 observed:-55
percept: 9 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24703 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 12326133 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:13262215 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3106 rate:8000
said: 2 | **ACOUSTIC** rms_mean:127 rms_max:14327 peak:32768 transients:3
said: 3 | **TRANSIENT** t_ms:13238710 stream:0x92fb56ae wall:0 rms:14327
```

---

@LAT103LON431 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12386133 ±0 frame:6000
said: 1 | **LINKWIN** t_ms:13322215 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-56 rssi_med:-48 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-65 rssi_med:-57 rssi_max:-51
said: 4 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-60 rssi_max:-51
said: 5 | **LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-47 rssi_med:-44 rssi_max:-37
said: 6 | 0x00000010 espnow violated predicted:-40 observed:-48
percept: 6 | 0x00000010 | link_stable | espnow | - | -
said: 7 | 0x00000200 espnow met predicted:-41 observed:-44
percept: 7 | 0x00000200 | link_stable | espnow | + | -
said: 8 | 0x00000200 ble met predicted:-55 observed:-57
percept: 8 | 0x00000200 | link_stable | ble | + | -
said: 9 | 0x00000010 ble met predicted:-58 observed:-60
percept: 9 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON24704 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 12386133 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:13322215 stream:0x92fb56ae wall:0 window_ms:60000 blocks:1204 rate:8000
said: 2 | **ACOUSTIC** rms_mean:160 rms_max:3945 peak:12212 transients:8
said: 3 | **TRANSIENT** t_ms:13288863 stream:0x92fb56ae wall:0 rms:3945
```

---

@LAT103LON432 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 60000 ±0 frame:7500
said: 1 | **LINKWIN** t_ms:13403057 stream:0x92fb56ae wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:15 rssi_min:-67 rssi_med:-56 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:ble n:6 rssi_min:-65 rssi_med:-54 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-38 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:espnow n:2 rssi_min:-45 rssi_med:-45 rssi_max:-37
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

@LAT103LON24705 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 60000 ±0 frame:7500
said: 1 | **ACOUSTICWIN** t_ms:13403057 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3455 rate:8000
said: 2 | **ACOUSTIC** rms_mean:107 rms_max:3501 peak:12579 transients:7
said: 3 | **TRANSIENT** t_ms:13370220 stream:0x92fb56ae wall:0 rms:3501
```

---

@LAT103LON24706 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 120000 ±0 frame:7500
said: 1 | **ACOUSTICWIN** t_ms:13463057 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3422 rate:8000
said: 2 | **ACOUSTIC** rms_mean:206 rms_max:6246 peak:31273 transients:33
said: 3 | **TRANSIENT** t_ms:13431364 stream:0x92fb56ae wall:0 rms:6246
```

---

@LAT103LON24707 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 180001 ±0 frame:7500
said: 1 | **ACOUSTICWIN** t_ms:13523058 stream:0x92fb56ae wall:0 window_ms:60001 blocks:3735 rate:8000
said: 2 | **ACOUSTIC** rms_mean:107 rms_max:632 peak:2332 transients:0
```

---

@LAT103LON24708 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 240001 ±0 frame:7500
said: 1 | **ACOUSTICWIN** t_ms:13583058 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3726 rate:8000
said: 2 | **ACOUSTIC** rms_mean:108 rms_max:3837 peak:14205 transients:1
said: 3 | **TRANSIENT** t_ms:13574589 stream:0x92fb56ae wall:0 rms:3837
```

---

@LAT104LON55 | created:0 | updated:0

**carried through @LAT103LON386**

```ttdb-carried
through: 386
through: 24692
carried: 251 0 450 173 | 0x00000200 | link_stable | espnow
carried: 314 2 672 185 | 0x00000200 | link_stable | ble
carried: 236 0 589 104 | 0x00000100 | link_stable | espnow
carried: 303 1 658 171 | 0x00000010 | link_stable | ble
carried: 297 6 656 171 | 0x00000010 | link_stable | espnow
carried: 4 0 4 6 | 0x00000011 | link_stable | ble
carried: 3 1 4 6 | 0x00000011 | link_stable | espnow
carried: 27 1 28 28 | 0x00000012 | link_stable | ble
carried: 26 1 27 27 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON24709 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 300001 ±0 frame:7500
said: 1 | **ACOUSTICWIN** t_ms:13643058 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3733 rate:8000
said: 2 | **ACOUSTIC** rms_mean:109 rms_max:816 peak:4763 transients:0
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

@LAT103LON24710 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 60000 ±0 frame:11000
said: 1 | **ACOUSTICWIN** t_ms:46462 stream:0x0947153e wall:0 window_ms:60000 blocks:3256 rate:8000
said: 2 | **ACOUSTIC** rms_mean:144 rms_max:9320 peak:32768 transients:16
said: 3 | **TRANSIENT** t_ms:39115 stream:0x0947153e wall:0 rms:9320
```

---

@LAT103LON24711 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 120000 ±0 frame:11000
said: 1 | **ACOUSTICWIN** t_ms:106462 stream:0x0947153e wall:0 window_ms:60000 blocks:3732 rate:8000
said: 2 | **ACOUSTIC** rms_mean:160 rms_max:12064 peak:32768 transients:10
said: 3 | **TRANSIENT** t_ms:68968 stream:0x0947153e wall:0 rms:12064
```

---

@LAT103LON24712 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 180000 ±0 frame:11000
said: 1 | **ACOUSTICWIN** t_ms:166462 stream:0x0947153e wall:0 window_ms:60000 blocks:3740 rate:8000
said: 2 | **ACOUSTIC** rms_mean:116 rms_max:436 peak:1037 transients:0
```

---

@LAT103LON24713 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 240000 ±0 frame:11000
said: 1 | **ACOUSTICWIN** t_ms:226462 stream:0x0947153e wall:0 window_ms:60000 blocks:3743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:118 rms_max:1030 peak:2987 transients:1
said: 3 | **TRANSIENT** t_ms:207676 stream:0x0947153e wall:0 rms:1030
```

---

@LAT103LON24714 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 300000 ±0 frame:11000
said: 1 | **ACOUSTICWIN** t_ms:286462 stream:0x0947153e wall:0 window_ms:60000 blocks:3740 rate:8000
said: 2 | **ACOUSTIC** rms_mean:104 rms_max:343 peak:1120 transients:0
```

---

@LAT103LON24715 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 360000 ±0 frame:11000
said: 1 | **ACOUSTICWIN** t_ms:346462 stream:0x0947153e wall:0 window_ms:60000 blocks:3739 rate:8000
said: 2 | **ACOUSTIC** rms_mean:104 rms_max:960 peak:1495 transients:0
```

---

@LAT103LON24716 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 420000 ±0 frame:11000
said: 1 | **ACOUSTICWIN** t_ms:406462 stream:0x0947153e wall:0 window_ms:60000 blocks:3743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:105 rms_max:1294 peak:3132 transients:0
```

---

@LAT103LON24717 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 480000 ±0 frame:11000
said: 1 | **ACOUSTICWIN** t_ms:466462 stream:0x0947153e wall:0 window_ms:60000 blocks:3737 rate:8000
said: 2 | **ACOUSTIC** rms_mean:91 rms_max:230 peak:495 transients:0
```

---

@LAT104LON56 | created:0 | updated:0

**carried through @LAT103LON386**

```ttdb-carried
through: 386
through: 24701
carried: 251 0 450 173 | 0x00000200 | link_stable | espnow
carried: 314 2 672 185 | 0x00000200 | link_stable | ble
carried: 236 0 589 104 | 0x00000100 | link_stable | espnow
carried: 303 1 658 171 | 0x00000010 | link_stable | ble
carried: 297 6 656 171 | 0x00000010 | link_stable | espnow
carried: 4 0 4 6 | 0x00000011 | link_stable | ble
carried: 3 1 4 6 | 0x00000011 | link_stable | espnow
carried: 27 1 28 28 | 0x00000012 | link_stable | ble
carried: 26 1 27 27 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON24718 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 540000 ±0 frame:11000
said: 1 | **ACOUSTICWIN** t_ms:526462 stream:0x0947153e wall:0 window_ms:60000 blocks:3725 rate:8000
said: 2 | **ACOUSTIC** rms_mean:104 rms_max:361 peak:677 transients:0
```
