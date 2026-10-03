# T-Deck Fleet Map TTDB (semantic positioning SP6)

```mmpdb
db_id: tdeck-console-001
db_name: T-Deck Handheld Console - Fleet Map
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: tdeck-console
  role: handheld-console
  perspective: operator
  scope: fleet-command
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

fleet_pose_ceiling: 0 of 4
render: SHAPE_NOT_MAP   # unpinned degrees of freedom remain -- this is a
#   SHAPE. Its edge lengths are claims; its placement and handedness are not.
#   Draw it as a shape and say which DoF are pinned (spec 3 Phase 6 rule 2).

```cursor
lat: 0
lon: 0
```

---

@LAT0LON2 | created:1786464490 | updated:1786464490 | relates:espnow@LAT0LON0,espnow@LAT0LON-1

**POSITION** node:cardputer_1
name: Card
x_m: 2.12  y_m: 0.00
sigma_m: 4.04   conf: 0.45
age_s: 1353   # since this belief was last touched
pose_ceiling: 0 of 4
dof_pinned: { translation: none, rotation: none, reflection: none }
render: SHAPE_NOT_MAP   # unpinned DoF remain; draw the shape, not a location
link V4-A: espnow 7.6m conf 0.80
link T-Deck: espnow 7.3m conf 0.80

---

@LAT0LON-1 | created:1786464490 | updated:1786464490 | relates:espnow@LAT0LON0,espnow@LAT0LON23,espnow@LAT0LON-9,espnow@LAT0LON2

**POSITION** node:tdeck_1
name: T-Deck
x_m: -0.87  y_m: 0.02
sigma_m: 7.53   conf: 0.44
age_s: 1353   # since this belief was last touched
pose_ceiling: 0 of 4
dof_pinned: { translation: none, rotation: none, reflection: none }
render: SHAPE_NOT_MAP   # unpinned DoF remain; draw the shape, not a location
link V4-A: espnow 3.8m conf 0.70
link V4-B: espnow 27.6m conf 0.80
link V4-C: espnow 7.6m conf 0.80
link Card: espnow 7.3m conf 0.80

---

@LAT0LON0 | created:1786464490 | updated:1786464490 | relates:espnow@LAT0LON23,espnow@LAT0LON-9,espnow@LAT0LON-1,espnow@LAT0LON2

**POSITION** node:v4a_bridge
name: V4-A
x_m: 0.00  y_m: 0.00
sigma_m: 8.87   conf: 0.44
age_s: 1353   # since this belief was last touched
pose_ceiling: 0 of 4
dof_pinned: { translation: none, rotation: none, reflection: none }
render: SHAPE_NOT_MAP   # unpinned DoF remain; draw the shape, not a location
link V4-B: espnow 23.9m conf 0.80
link V4-C: espnow 14.2m conf 0.80
link T-Deck: espnow 3.8m conf 0.70
link Card: espnow 7.6m conf 0.80

---

@LAT0LON23 | created:1786464490 | updated:1786464490 | relates:espnow@LAT0LON0,espnow@LAT0LON-1

**POSITION** node:v4b_relay
name: V4-B
x_m: 22.99  y_m: -0.14
sigma_m: 12.99   conf: 0.45
age_s: 1353   # since this belief was last touched
pose_ceiling: 0 of 4
dof_pinned: { translation: none, rotation: none, reflection: none }
render: SHAPE_NOT_MAP   # unpinned DoF remain; draw the shape, not a location
link V4-A: espnow 23.9m conf 0.80
link T-Deck: espnow 27.6m conf 0.80

---

@LAT0LON-9 | created:1786464490 | updated:1786464490 | relates:espnow@LAT0LON0,espnow@LAT0LON-1

**POSITION** node:v4c_edge
name: V4-C
x_m: -8.60  y_m: 0.35
sigma_m: 8.96   conf: 0.45
age_s: 1353   # since this belief was last touched
pose_ceiling: 0 of 4
dof_pinned: { translation: none, rotation: none, reflection: none }
render: SHAPE_NOT_MAP   # unpinned DoF remain; draw the shape, not a location
link V4-A: espnow 14.2m conf 0.80
link T-Deck: espnow 7.6m conf 0.80

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x4a194eda wall:0 t_ms:24124234 node:0x200 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x642cef6b wall:0 t_ms:0 node:0x200 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xdcd3edce wall:0 t_ms:4096451 node:0x200 from:0x10
**REMAP** prev_stream:0x3a2f6a8c prev_t_ms:5524 offset_ms:4090927 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xee98fca8 wall:0 t_ms:58252 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x88023c58 wall:0 t_ms:12012426 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x92fb56ae wall:0 t_ms:209090 node:0x200 from:0x300
**REMAP** prev_stream:0x15eea3ed prev_t_ms:5359 offset_ms:203731 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xc909d5a8 wall:0 t_ms:335076 node:0x200 from:0x11
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT103LON8192 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9540377 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:9652941 stream:0xc909d5a8 wall:0 window_ms:60040 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:10118783 stream:0xc909d5a8 wall:0 node:0x00000200

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:43 last_lon:42 t_ms:10128032 stream:0xc909d5a8 wall:0 node:0x00000200

---

@LAT103LON8193 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10095018 ±22 frame:4000
said: 1 | **ENTWIN** t_ms:10207599 stream:0xc909d5a8 wall:0 window_ms:60038 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON8194 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11281500 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:11394190 stream:0xc909d5a8 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 6 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:4 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace
said: 11 | **COVERED** windows:1 entities:6 window_ms:586554 first_t_ms:10794190 last_t_ms:10794190 covered_by:@LAT103LON8193
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94 windows:1
```

---

@LAT103LON8195 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12481510 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:12594189 stream:0xc909d5a8 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,5ce28c488e0c,64677217947d,e6b32d2cea8b
said: 12 | **COVERED** windows:1 entities:7 window_ms:600000 first_t_ms:11994189 last_t_ms:11994189 covered_by:@LAT103LON8194
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-97 windows:1
```

---

@LAT103LON8196 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13681529 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:13794190 stream:0xc909d5a8 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,0283cce0e689
said: 11 | **COVERED** windows:1 entities:6 window_ms:600001 first_t_ms:13194190 last_t_ms:13194190 covered_by:@LAT103LON8195
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93 windows:1
```

---

@LAT103LON8197 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 14281538 ±22 frame:4000
said: 1 | **ENTWIN** t_ms:14394189 stream:0xc909d5a8 wall:0 window_ms:600000 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
said: 7 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,02c57d2e0f0d,5ce28c488e0c
```

---

@LAT103LON8198 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 14881550 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:14994190 stream:0xc909d5a8 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,5ce28c488e0c,0283cce0e689
```

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:16027778 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-32 rssi_max:-30
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-17 rssi_med:-17 rssi_max:-16

---

@LAT103LON8199 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 17881596 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:17994240 stream:0xc909d5a8 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
said: 10 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,0283cce0e689,84a329c78fec
said: 12 | **COVERED** windows:4 entities:9 window_ms:2399999 first_t_ms:15594189 last_t_ms:17394240 covered_by:@LAT103LON8198
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-39 windows:4
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-72 windows:4
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-76 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-84 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-86 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-92 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:4 rssi:-89 windows:4
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-93 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-92 windows:4
```

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18547827 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-37 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-18 rssi_med:-17 rssi_max:-16

---

@LAT103LON8200 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 18481604 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:18594239 stream:0xc909d5a8 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,0283cce0e689
```

---

@LAT103LON8201 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 19081615 ±22 frame:4000
said: 1 | **ENTWIN** t_ms:19194291 stream:0xc909d5a8 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,0283cce0e689,5ce28c488e0c
```

---

@LAT103LON8202 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 209696 ±21 frame:5000
said: 1 | **ENTWIN** t_ms:473670 stream:0x40bbc10f wall:0 window_ms:60032 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON8203 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60665 ±0 frame:5500
said: 1 | **ENTWIN** t_ms:51845 stream:0x9afbb748 wall:0 window_ms:60665 entities:3
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 5 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 6 | **CORE** entities:0
```

---

@LAT103LON8204 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9649193 ±21 frame:5500
said: 1 | **ENTWIN** t_ms:9648147 stream:0x9afbb748 wall:0 window_ms:60066 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8205 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10369514 ±21 frame:5500
seq: 2
follows: 0x00000010:86 0x00000300:255
said: 1 | **ENTWIN** t_ms:10368501 stream:0x9afbb748 wall:0 window_ms:60032 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8206 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 22206461 ±21 frame:5500
seq: 7
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:665
said: 1 | **ENTWIN** t_ms:22201425 stream:0x9afbb748 wall:0 window_ms:70102 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
said: 7 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-95
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON8207 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 23355612 ±21 frame:5500
seq: 26
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:704
said: 1 | **ENTWIN** t_ms:23352602 stream:0x9afbb748 wall:0 window_ms:589991 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-97
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 12 | **CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace
said: 13 | **COVERED** windows:1 entities:10 window_ms:559140 first_t_ms:22760610 last_t_ms:22760610 covered_by:@LAT103LON8206
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95 windows:1
```

---

@LAT103LON8208 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 23959893 ±22 frame:5500
seq: 37
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:726
said: 1 | **ENTWIN** t_ms:23956882 stream:0x9afbb748 wall:0 window_ms:604274 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 12 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,aef9ff2626ac,e6b32d2cea8b,c2e94427adcf
```

---

@LAT103LON8209 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 24164289 ±21 frame:5500
seq: 40
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:734
said: 1 | **ENTWIN** t_ms:24161127 stream:0x9afbb748 wall:0 window_ms:68258 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8210 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 25307248 ±25 frame:5500
seq: 59
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:772
said: 1 | **ENTWIN** t_ms:25306368 stream:0x9afbb748 wall:0 window_ms:600002 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-95
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,e6b32d2cea8b,02c57d2e0f0d,aef9ff2626ac,0283cce0e689
said: 11 | **COVERED** windows:1 entities:7 window_ms:543057 first_t_ms:24706366 last_t_ms:24706366 covered_by:@LAT103LON8209
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-96 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96 windows:1
```

---

@LAT103LON8211 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 26495644 ±21 frame:5500
seq: 78
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:800
said: 1 | **ENTWIN** t_ms:26494564 stream:0x9afbb748 wall:0 window_ms:60206 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON8212 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 26775338 ±21 frame:5500
seq: 83
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:808
said: 1 | **ENTWIN** t_ms:26774451 stream:0x9afbb748 wall:0 window_ms:60035 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON279 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26895304 ±22 frame:5500
seq: 85
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:812
said: 1 | **LINKWIN** t_ms:26894450 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:99 rssi_min:-63 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-67 rssi_med:-55 rssi_max:-52
```

---

@LAT103LON280 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26955306 ±21 frame:5500
seq: 86
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:814
said: 1 | **LINKWIN** t_ms:26954450 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:99 rssi_min:-46 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-79 rssi_med:-55 rssi_max:-50
```

---

@LAT103LON281 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27015306 ±21 frame:5500
seq: 87
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:816
said: 1 | **LINKWIN** t_ms:27014451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-64 rssi_med:-55 rssi_max:-53
```

---

@LAT103LON282 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27075308 ±21 frame:5500
seq: 88
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:818
said: 1 | **LINKWIN** t_ms:27074451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-83 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON283 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27135309 ±21 frame:5500
seq: 89
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:820
said: 1 | **LINKWIN** t_ms:27134451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-56 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-42 rssi_med:-42 rssi_max:-41
```

---

@LAT103LON284 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27195310 ±21 frame:5500
seq: 90
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:822
said: 1 | **LINKWIN** t_ms:27194450 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:105 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON285 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27255311 ±21 frame:5500
seq: 91
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:824
said: 1 | **LINKWIN** t_ms:27254451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-79 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON286 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27315312 ±21 frame:5500
seq: 92
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:826
said: 1 | **LINKWIN** t_ms:27314451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:72 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-69 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON287 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27375312 ±21 frame:5500
seq: 93
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:829
said: 1 | **LINKWIN** t_ms:27374451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-93 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-52
```

---

@LAT103LON288 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27435314 ±21 frame:5500
seq: 94
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:831
said: 1 | **LINKWIN** t_ms:27434451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-58 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON289 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27495314 ±22 frame:5500
seq: 95
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:833
said: 1 | **LINKWIN** t_ms:27494451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON290 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27555316 ±21 frame:5500
seq: 96
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:835
said: 1 | **LINKWIN** t_ms:27554451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-50 rssi_med:-42 rssi_max:-38
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-83 rssi_med:-54 rssi_max:-50
```

---

@LAT103LON291 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27615317 ±21 frame:5500
seq: 97
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:837
said: 1 | **LINKWIN** t_ms:27614451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:56 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-79 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON292 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27675314 ±21 frame:5500
seq: 98
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:839
said: 1 | **LINKWIN** t_ms:27674451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-60 rssi_med:-54 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-48 rssi_med:-40 rssi_max:-40
```

---

@LAT103LON293 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27735319 ±21 frame:5500
seq: 99
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:841
said: 1 | **LINKWIN** t_ms:27734451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-56 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON294 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27795318 ±21 frame:5500
seq: 100
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:843
said: 1 | **LINKWIN** t_ms:27794451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON295 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27855317 ±21 frame:5500
seq: 101
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:845
said: 1 | **LINKWIN** t_ms:27854451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON296 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27915321 ±22 frame:5500
seq: 102
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:847
said: 1 | **LINKWIN** t_ms:27914451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON8213 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 27949938 ±21 frame:5500
seq: 103
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:847
said: 1 | **ENTWIN** t_ms:27949066 stream:0x9afbb748 wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 9 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 10 | **COVERED** windows:1 entities:5 window_ms:574581 first_t_ms:27349066 last_t_ms:27349066 covered_by:@LAT103LON8212
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88 windows:1
```

---

@LAT103LON297 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27975322 ±21 frame:5500
seq: 104
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:850
said: 1 | **LINKWIN** t_ms:27974451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-69 rssi_med:-54 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT105LON71 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 27865526 ±0 frame:5500
seq: 846
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:101
said: 1 | **LINKWIN** t_ms:27864680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:57 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON72 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 27925526 ±0 frame:5500
seq: 848
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:102
said: 1 | **LINKWIN** t_ms:27924680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON73 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 27985526 ±0 frame:5500
seq: 851
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:104
said: 1 | **LINKWIN** t_ms:27984680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:32 rssi_min:-49 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON298 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28035315 ±21 frame:5500
seq: 105
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:853
said: 1 | **LINKWIN** t_ms:28034450 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:70 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-56 rssi_med:-53 rssi_max:-51
```

---

@LAT105LON74 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28045526 ±0 frame:5500
seq: 854
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:105
said: 1 | **LINKWIN** t_ms:28044680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-49 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON299 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28095323 ±21 frame:5500
seq: 106
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:855
said: 1 | **LINKWIN** t_ms:28094451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-79 rssi_med:-54 rssi_max:-51
```

---

@LAT105LON75 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28105526 ±0 frame:5500
seq: 856
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:106
said: 1 | **LINKWIN** t_ms:28104680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON300 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28155320 ±21 frame:5500
seq: 107
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:857
said: 1 | **LINKWIN** t_ms:28154451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-59 rssi_med:-54 rssi_max:-51
```

---

@LAT105LON76 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28165526 ±0 frame:5500
seq: 858
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:107
said: 1 | **LINKWIN** t_ms:28164680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-82 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-49 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 ble met predicted:-57 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON301 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28215326 ±21 frame:5500
seq: 108
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:859
said: 1 | **LINKWIN** t_ms:28214450 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON302 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28275326 ±21 frame:5500
seq: 109
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:861
said: 1 | **LINKWIN** t_ms:28274450 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON303 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28335328 ±21 frame:5500
seq: 110
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:863
said: 1 | **LINKWIN** t_ms:28334451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT105LON77 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28225526 ±0 frame:5500
seq: 860
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:108
said: 1 | **LINKWIN** t_ms:28224680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:46 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-64 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON78 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28285526 ±0 frame:5500
seq: 862
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:109
said: 1 | **LINKWIN** t_ms:28284680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-49 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON304 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28395329 ±21 frame:5500
seq: 111
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:865
said: 1 | **LINKWIN** t_ms:28394451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-79 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON305 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28455330 ±21 frame:5500
seq: 112
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:867
said: 1 | **LINKWIN** t_ms:28454451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-79 rssi_med:-54 rssi_max:-51
```

---

@LAT105LON79 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28345526 ±0 frame:5500
seq: 864
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:110
said: 1 | **LINKWIN** t_ms:28344680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON80 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28405526 ±0 frame:5500
seq: 866
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:111
said: 1 | **LINKWIN** t_ms:28404680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-64 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON81 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28465526 ±0 frame:5500
seq: 868
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:112
said: 1 | **LINKWIN** t_ms:28464680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-63 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT101LON0 | sid:2136c351 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:28514451 stream:0x9afbb748 wall:0

---

@LAT101LON1 | sid:27653a2f | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:28514451 stream:0x9afbb748 wall:0

---

@LAT101LON2 | sid:42caf4db | created:0 | updated:0 |
**PEER** node:0x00000300 spoke:1 declared:0x3fb7 verified:0x2fb7 exercised:0x0015 cap_epoch:9
**TRACE** copresence:255 half_life_ms:600000 reinforced:806 last_ms:1798848
t_ms:28514451 stream:0x9afbb748 wall:0

---

@LAT101LON3 | sid:2665389c | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:28514451 stream:0x9afbb748 wall:0

---

@LAT101LON4 | sid:29653d55 | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:28514451 stream:0x9afbb748 wall:0

---

@LAT103LON306 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28516237 ±21 frame:5500
seq: 113
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:869
said: 1 | **LINKWIN** t_ms:28514451 stream:0x9afbb748 wall:0 window_ms:60906
said: 2 | **LINK** peer:0x00000300 proto:espnow n:59 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-79 rssi_med:-53 rssi_max:-51
```

---

@LAT105LON82 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28525526 ±0 frame:5500
seq: 870
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:112
said: 1 | **LINKWIN** t_ms:28524680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-44 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-57 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON307 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28576254 ±22 frame:5500
seq: 114
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:871
said: 1 | **LINKWIN** t_ms:28575367 stream:0x9afbb748 wall:0 window_ms:60016
said: 2 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-78 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-56 rssi_med:-53 rssi_max:-50
```

---

@LAT105LON83 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28585526 ±0 frame:5500
seq: 872
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:113
said: 1 | **LINKWIN** t_ms:28584680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-64 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON308 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28636255 ±21 frame:5500
seq: 115
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:873
said: 1 | **LINKWIN** t_ms:28635373 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-56 rssi_med:-54 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT105LON84 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28645526 ±0 frame:5500
seq: 874
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:114
said: 1 | **LINKWIN** t_ms:28644680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 ble met predicted:-57 observed:-57
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON309 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28696257 ±21 frame:5500
seq: 116
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:875
said: 1 | **LINKWIN** t_ms:28695373 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT105LON85 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28705526 ±0 frame:5500
seq: 876
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:116
said: 1 | **LINKWIN** t_ms:28704680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:49 rssi_min:-49 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-57 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON310 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28756256 ±23 frame:5500
seq: 117
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:877
said: 1 | **LINKWIN** t_ms:28755373 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-40 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-56 rssi_med:-53 rssi_max:-51
```

---

@LAT105LON86 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28765526 ±0 frame:5500
seq: 878
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:117
said: 1 | **LINKWIN** t_ms:28764680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-56 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:33 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-56
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON311 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28816251 ±21 frame:5500
seq: 118
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:879
said: 1 | **LINKWIN** t_ms:28815373 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-59 rssi_med:-53 rssi_max:-51
```

---

@LAT105LON87 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28825526 ±0 frame:5500
seq: 880
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:118
said: 1 | **LINKWIN** t_ms:28824680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-79 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:45 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 4 | 0x00000200 ble met predicted:-56 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON312 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28876260 ±21 frame:5500
seq: 119
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:881
said: 1 | **LINKWIN** t_ms:28875373 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-59 rssi_med:-53 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT105LON88 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28885526 ±0 frame:5500
seq: 882
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:118
said: 1 | **LINKWIN** t_ms:28884680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:38 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-57 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-57
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON313 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28936305 ±21 frame:5500
seq: 120
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:883
said: 1 | **LINKWIN** t_ms:28935413 stream:0x9afbb748 wall:0 window_ms:60045
said: 2 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-79 rssi_med:-54 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-41 rssi_med:-40 rssi_max:-39
```

---

@LAT105LON89 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 28945526 ±0 frame:5500
seq: 884
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:120
said: 1 | **LINKWIN** t_ms:28944680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-63 rssi_med:-57 rssi_max:-53
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-57 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON314 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28996313 ±21 frame:5500
seq: 121
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:885
said: 1 | **LINKWIN** t_ms:28995419 stream:0x9afbb748 wall:0 window_ms:60006
said: 2 | **LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-59 rssi_med:-53 rssi_max:-51
```

---

@LAT105LON90 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29005526 ±0 frame:5500
seq: 886
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:120
said: 1 | **LINKWIN** t_ms:29004680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-57 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON315 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29056380 ±21 frame:5500
seq: 122
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:887
said: 1 | **LINKWIN** t_ms:29055485 stream:0x9afbb748 wall:0 window_ms:60066
said: 2 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-59 rssi_med:-53 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT103LON316 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29116381 ±21 frame:5500
seq: 123
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:889
said: 1 | **LINKWIN** t_ms:29115490 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-40 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-53 rssi_max:-51
```

---

@LAT105LON91 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29065526 ±0 frame:5500
seq: 888
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:121
said: 1 | **LINKWIN** t_ms:29064680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON92 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29125526 ±0 frame:5500
seq: 890
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:123
said: 1 | **LINKWIN** t_ms:29124680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-64 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON317 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29176382 ±21 frame:5500
seq: 124
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:891
said: 1 | **LINKWIN** t_ms:29175490 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-69 rssi_med:-53 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT105LON93 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29187575 ±0 frame:5500
seq: 892
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:124
said: 1 | **LINKWIN** t_ms:29186729 stream:0x9afbb748 wall:0 window_ms:62049
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON318 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29236383 ±21 frame:5500
seq: 125
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:893
said: 1 | **LINKWIN** t_ms:29235490 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-59 rssi_med:-54 rssi_max:-51
```

---

@LAT104LON30 | created:0 | updated:0

**carried through @LAT103LON278**

```ttdb-carried
through: 278
```

---

@LAT105LON94 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29247575 ±0 frame:5500
seq: 894
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:125
said: 1 | **LINKWIN** t_ms:29246729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON319 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29296384 ±21 frame:5500
seq: 126
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:895
said: 1 | **LINKWIN** t_ms:29295489 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-79 rssi_med:-53 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT105LON95 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29307575 ±0 frame:5500
seq: 896
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:126
said: 1 | **LINKWIN** t_ms:29306729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-49 rssi_med:-44 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON320 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29356385 ±21 frame:5500
seq: 127
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:897
said: 1 | **LINKWIN** t_ms:29355490 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-42 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-79 rssi_med:-54 rssi_max:-50
```

---

@LAT105LON96 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29367575 ±0 frame:5500
seq: 898
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:127
said: 1 | **LINKWIN** t_ms:29366729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-82 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:39 rssi_min:-48 rssi_med:-43 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-43
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON321 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29416385 ±21 frame:5500
seq: 128
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:899
said: 1 | **LINKWIN** t_ms:29415490 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-43 rssi_med:-40 rssi_max:-38
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-53 rssi_max:-51
```

---

@LAT105LON97 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29427575 ±0 frame:5500
seq: 900
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:128
said: 1 | **LINKWIN** t_ms:29426729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-47 rssi_med:-43 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-57 rssi_max:-51
said: 4 | 0x00000200 ble met predicted:-55 observed:-57
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON322 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29476386 ±21 frame:5500
seq: 129
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:901
said: 1 | **LINKWIN** t_ms:29475541 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-73 rssi_med:-55 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-60 rssi_med:-42 rssi_max:-38
```

---

@LAT105LON98 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29487575 ±0 frame:5500
seq: 902
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:129
said: 1 | **LINKWIN** t_ms:29486729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-63 rssi_med:-45 rssi_max:-42
said: 4 | 0x00000200 espnow met predicted:-43 observed:-45
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-57 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON323 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29536388 ±21 frame:5500
seq: 130
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:903
said: 1 | **LINKWIN** t_ms:29535541 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-43 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-54 rssi_max:-49
```

---

@LAT105LON99 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29547575 ±0 frame:5500
seq: 904
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:130
said: 1 | **LINKWIN** t_ms:29546729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-50 rssi_med:-43 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 4 | 0x00000200 ble met predicted:-57 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-45 observed:-43
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON324 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29596388 ±21 frame:5500
seq: 131
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:905
said: 1 | **LINKWIN** t_ms:29595541 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-45 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-79 rssi_med:-55 rssi_max:-51
```

---

@LAT105LON100 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29607575 ±0 frame:5500
seq: 906
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:131
said: 1 | **LINKWIN** t_ms:29606729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-49 rssi_med:-44 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-81 rssi_med:-56 rssi_max:-51
said: 4 | 0x00000200 espnow met predicted:-43 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-56 observed:-56
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON325 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29656390 ±21 frame:5500
seq: 132
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:907
said: 1 | **LINKWIN** t_ms:29655541 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-55 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-64 rssi_med:-46 rssi_max:-39
```

---

@LAT105LON101 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29667575 ±0 frame:5500
seq: 908
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:132
said: 1 | **LINKWIN** t_ms:29666729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-61 rssi_med:-58 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-83 rssi_med:-61 rssi_max:-52
said: 4 | 0x00000200 espnow violated predicted:-44 observed:-58
percept: 4 | 0x00000200 | link_stable | espnow | - | -
said: 5 | 0x00000200 ble met predicted:-56 observed:-61
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON326 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29716389 ±21 frame:5500
seq: 133
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:909
said: 1 | **LINKWIN** t_ms:29715541 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-59 rssi_max:-53
said: 3 | **LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-63 rssi_med:-60 rssi_max:-58
```

---

@LAT105LON102 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 29727575 ±0 frame:5500
seq: 910
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:133
said: 1 | **LINKWIN** t_ms:29726729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:33 rssi_min:-61 rssi_med:-60 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-83 rssi_med:-61 rssi_max:-56
said: 4 | 0x00000200 espnow met predicted:-58 observed:-60
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-61 observed:-61
percept: 5 | 0x00000200 | link_stable | ble | + | -
```
