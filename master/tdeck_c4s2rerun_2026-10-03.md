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

@LAT103LON8214 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 29839444 ±21 frame:5500
seq: 135
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:914
said: 1 | **ENTWIN** t_ms:29832435 stream:0x9afbb748 wall:0 window_ms:66031 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-98
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8215 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31027398 ±21 frame:5500
seq: 155
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:954
said: 1 | **ENTWIN** t_ms:31026538 stream:0x9afbb748 wall:0 window_ms:599999 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-95
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,5ce28c488e0c,e6b32d2cea8b
said: 14 | **COVERED** windows:1 entities:10 window_ms:587944 first_t_ms:30426539 last_t_ms:30426539 covered_by:@LAT103LON8214
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94 windows:1
```

---

@LAT103LON8216 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31627400 ±0 frame:5500
seq: 166
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:966
said: 1 | **ENTWIN** t_ms:31626539 stream:0x9afbb748 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-95
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-96
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,aef9ff2626ac,7236bc441422,0283cce0e689,5ce28c488e0c
```

---

@LAT103LON8217 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 32227393 ±21 frame:5500
seq: 177
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:988
said: 1 | **ENTWIN** t_ms:32226539 stream:0x9afbb748 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,7236bc441422,e6b32d2cea8b,64677217947d,0283cce0e689,aef9ff2626ac,5ce28c488e0c
```

---

@LAT103LON8218 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 32823283 ±21 frame:5500
seq: 188
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1009
said: 1 | **ENTWIN** t_ms:32826538 stream:0x9afbb748 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,64677217947d,e6b32d2cea8b,7236bc441422,aef9ff2626ac,0283cce0e689
```

---

@LAT106LON0 | created:0 | updated:0

**BAR** frame:5500 bar:54 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:635610
**HOLDS** agent:0x00000200 n:10 lo:170 hi:180 sum:1748
**HOLDS** agent:0x00000300 n:10 lo:975 hi:993 sum:9840
@LAT106LON1 | created:0 | updated:0

**BAR** frame:5500 bar:53 own:10 held:6 terms:2 digest:0x07234745 settled_ms:1235610
**HOLDS** agent:0x00000200 n:10 lo:159 hi:169 sum:1638
**HOLDS** agent:0x00000300 n:6 lo:961 hi:973 sum:5800
@LAT106LON2 | created:0 | updated:0

**BAR** frame:5500 bar:55 own:10 held:10 terms:2 digest:0x2bacbfd9 settled_ms:141519
**HOLDS** agent:0x00000200 n:10 lo:181 hi:191 sum:1858
**HOLDS** agent:0x00000300 n:10 lo:995 hi:1014 sum:10043

---

@LAT103LON8219 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 33221875 ±21 frame:5500
seq: 193
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1023
said: 1 | **ENTWIN** t_ms:33216978 stream:0x9afbb748 wall:0 window_ms:63893 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON387 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33645745 ±21 frame:5500
seq: 200
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1039
said: 1 | **LINKWIN** t_ms:33642883 stream:0x9afbb748 wall:0 window_ms:60072
said: 2 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-81 rssi_med:-52 rssi_max:-52
said: 3 | **LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-42 rssi_med:-41 rssi_max:-40
```

---

@LAT103LON388 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33706364 ±21 frame:5500
seq: 201
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1039
said: 1 | **LINKWIN** t_ms:33703499 stream:0x9afbb748 wall:0 window_ms:60617
said: 2 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-58 rssi_med:-52 rssi_max:-51
```
@LAT106LON3 | created:0 | updated:0

**BAR** frame:5500 bar:56 own:7 held:10 terms:2 digest:0xee5eb19f settled_ms:123120
**HOLDS** agent:0x00000200 n:7 lo:192 hi:199 sum:1371
**HOLDS** agent:0x00000300 n:10 lo:1016 hi:1036 sum:10255

---

@LAT103LON389 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33767668 ±21 frame:5500
seq: 202
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1043
said: 1 | **LINKWIN** t_ms:33766802 stream:0x9afbb748 wall:0 window_ms:61303
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-52 rssi_max:-52
said: 3 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-42 rssi_med:-41 rssi_max:-41
```

---

@LAT103LON390 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33829586 ±21 frame:5500
seq: 203
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1045
said: 1 | **LINKWIN** t_ms:33826719 stream:0x9afbb748 wall:0 window_ms:61917
said: 2 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-71 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-41 rssi_med:-41 rssi_max:-41
```

---

@LAT103LON391 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33889587 ±21 frame:5500
seq: 204
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1047
said: 1 | **LINKWIN** t_ms:33888726 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-41 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-58 rssi_med:-53 rssi_max:-52
```

---

@LAT103LON392 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33949588 ±21 frame:5500
seq: 205
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1049
said: 1 | **LINKWIN** t_ms:33948726 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-42 rssi_med:-41 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-79 rssi_med:-52 rssi_max:-52
```

---

@LAT105LON168 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 33993567 ±0 frame:5500
seq: 1050
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:205
said: 1 | **LINKWIN** t_ms:33992717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:46 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON393 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34009589 ±21 frame:5500
seq: 206
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1052
said: 1 | **LINKWIN** t_ms:34008726 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-79 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:59 rssi_min:-42 rssi_med:-41 rssi_max:-41
```

---

@LAT105LON169 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34053567 ±0 frame:5500
seq: 1053
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:206
said: 1 | **LINKWIN** t_ms:34052717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-65 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON394 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34069590 ±21 frame:5500
seq: 207
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1054
said: 1 | **LINKWIN** t_ms:34068726 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-59 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-42 rssi_med:-41 rssi_max:-41
```

---

@LAT105LON170 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34113567 ±0 frame:5500
seq: 1055
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:207
said: 1 | **LINKWIN** t_ms:34112717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON395 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34129590 ±22 frame:5500
seq: 208
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1056
said: 1 | **LINKWIN** t_ms:34128726 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-42 rssi_med:-41 rssi_max:-41
```

---

@LAT103LON396 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34191663 ±21 frame:5500
seq: 209
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1058
said: 1 | **LINKWIN** t_ms:34190791 stream:0x9afbb748 wall:0 window_ms:62072
said: 2 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-79 rssi_med:-53 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-41 rssi_med:-41 rssi_max:-41
```

---

@LAT105LON171 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34173567 ±0 frame:5500
seq: 1057
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:208
said: 1 | **LINKWIN** t_ms:34172717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-48 rssi_med:-47 rssi_max:-45
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON397 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34253317 ±21 frame:5500
seq: 210
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1060
said: 1 | **LINKWIN** t_ms:34250483 stream:0x9afbb748 wall:0 window_ms:61693
said: 2 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-59 rssi_med:-52 rssi_max:-52
said: 3 | **LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-42 rssi_med:-41 rssi_max:-41
```

---

@LAT105LON172 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34233567 ±0 frame:5500
seq: 1059
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:209
said: 1 | **LINKWIN** t_ms:34232717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 4 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON398 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34313379 ±21 frame:5500
seq: 211
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1062
said: 1 | **LINKWIN** t_ms:34312507 stream:0x9afbb748 wall:0 window_ms:60021
said: 2 | **LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-42 rssi_med:-41 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-59 rssi_med:-52 rssi_max:-51
```
@LAT106LON4 | created:0 | updated:0

**BAR** frame:5500 bar:57 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:132155
**HOLDS** agent:0x00000200 n:10 lo:200 hi:209 sum:2045
**HOLDS** agent:0x00000300 n:10 lo:1038 hi:1057 sum:10473

---

@LAT105LON173 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34293567 ±0 frame:5500
seq: 1061
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:210
said: 1 | **LINKWIN** t_ms:34292717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON8220 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34372462 ±21 frame:5500
seq: 212
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1062
said: 1 | **ENTWIN** t_ms:34369592 stream:0x9afbb748 wall:0 window_ms:600240 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d
said: 11 | **COVERED** windows:1 entities:6 window_ms:550329 first_t_ms:33769352 last_t_ms:33769352 covered_by:@LAT103LON8219
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96 windows:1
```

---

@LAT103LON399 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34374696 ±21 frame:5500
seq: 213
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1064
said: 1 | **LINKWIN** t_ms:34373821 stream:0x9afbb748 wall:0 window_ms:61316
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-59 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-81 rssi_med:-41 rssi_max:-41
```

---

@LAT105LON174 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34353567 ±0 frame:5500
seq: 1063
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:211
said: 1 | **LINKWIN** t_ms:34352717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON400 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34434697 ±21 frame:5500
seq: 214
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1066
said: 1 | **LINKWIN** t_ms:34433828 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-41 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-58 rssi_med:-53 rssi_max:-52
```

---

@LAT105LON175 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34413567 ±0 frame:5500
seq: 1065
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:213
said: 1 | **LINKWIN** t_ms:34412717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 4 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON176 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34473567 ±0 frame:5500
seq: 1067
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:214
said: 1 | **LINKWIN** t_ms:34472717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON401 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34494699 ±21 frame:5500
seq: 215
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1068
said: 1 | **LINKWIN** t_ms:34493828 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-42 rssi_med:-41 rssi_max:-41
```

---

@LAT105LON177 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34533567 ±0 frame:5500
seq: 1069
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:215
said: 1 | **LINKWIN** t_ms:34532717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 4 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON402 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34554700 ±21 frame:5500
seq: 216
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1070
said: 1 | **LINKWIN** t_ms:34553827 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:61 rssi_min:-42 rssi_med:-41 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON403 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34614701 ±21 frame:5500
seq: 217
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1073
said: 1 | **LINKWIN** t_ms:34613828 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-59 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-41 rssi_med:-41 rssi_max:-40
```

---

@LAT103LON404 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34674702 ±21 frame:5500
seq: 218
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1075
said: 1 | **LINKWIN** t_ms:34673828 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-59 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-42 rssi_med:-41 rssi_max:-41
```

---

@LAT105LON178 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34593567 ±0 frame:5500
seq: 1071
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:216
said: 1 | **LINKWIN** t_ms:34592717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON179 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34653567 ±0 frame:5500
seq: 1074
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:217
said: 1 | **LINKWIN** t_ms:34652717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON180 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34713567 ±0 frame:5500
seq: 1076
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:218
said: 1 | **LINKWIN** t_ms:34712717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-83 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:38 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 4 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON405 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34735580 ±21 frame:5500
seq: 219
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1077
said: 1 | **LINKWIN** t_ms:34732698 stream:0x9afbb748 wall:0 window_ms:60878
said: 2 | **LINK** peer:0x00000300 proto:ble n:71 rssi_min:-64 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:69 rssi_min:-44 rssi_med:-41 rssi_max:-37
```

---

@LAT105LON181 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34773567 ±0 frame:5500
seq: 1078
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:219
said: 1 | **LINKWIN** t_ms:34772717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-53 rssi_med:-46 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-47 observed:-46
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON406 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34796141 ±21 frame:5500
seq: 220
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1079
said: 1 | **LINKWIN** t_ms:34793261 stream:0x9afbb748 wall:0 window_ms:60560
said: 2 | **LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-62 rssi_med:-54 rssi_max:-48
```

---

@LAT103LON407 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34856120 ±21 frame:5500
seq: 221
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1081
said: 1 | **LINKWIN** t_ms:34855266 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-41 rssi_med:-39 rssi_max:-39
```

---

@LAT105LON182 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34833567 ±0 frame:5500
seq: 1080
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:220
said: 1 | **LINKWIN** t_ms:34832717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-82 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 4 | 0x00000200 espnow met predicted:-46 observed:-47
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON183 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34893567 ±0 frame:5500
seq: 1082
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:221
said: 1 | **LINKWIN** t_ms:34892717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:71 rssi_min:-80 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-47 observed:-46
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON408 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34919698 ±21 frame:5500
seq: 222
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1083
said: 1 | **LINKWIN** t_ms:34916814 stream:0x9afbb748 wall:0 window_ms:63555
said: 2 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-82 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-41 rssi_med:-39 rssi_max:-38
```

---

@LAT106LON5 | created:0 | updated:0

**BAR** frame:5500 bar:58 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:121270
**HOLDS** agent:0x00000200 n:10 lo:210 hi:220 sum:2153
**HOLDS** agent:0x00000300 n:10 lo:1059 hi:1078 sum:10683

---

@LAT101LON0 | sid:2136c351 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:34958696 stream:0x9afbb748 wall:0

---

@LAT101LON1 | sid:27653a2f | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:34958696 stream:0x9afbb748 wall:0

---

@LAT101LON2 | sid:42caf4db | created:0 | updated:0 |
**PEER** node:0x00000300 spoke:1 declared:0x3fb7 verified:0x2fb7 exercised:0x0015 cap_epoch:9
**TRACE** copresence:255 half_life_ms:600000 reinforced:666 last_ms:1803564
t_ms:34958696 stream:0x9afbb748 wall:0

---

@LAT101LON3 | sid:2665389c | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:34958696 stream:0x9afbb748 wall:0

---

@LAT101LON4 | sid:29653d55 | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:34958696 stream:0x9afbb748 wall:0

---

@LAT103LON409 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34981658 ±21 frame:5500
seq: 223
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1085
said: 1 | **LINKWIN** t_ms:34980773 stream:0x9afbb748 wall:0 window_ms:61958
said: 2 | **LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-47 rssi_med:-39 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-60 rssi_med:-53 rssi_max:-48
```

---

@LAT103LON8221 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34985694 ±21 frame:5500
seq: 224
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1085
said: 1 | **ENTWIN** t_ms:34980773 stream:0x9afbb748 wall:0 window_ms:613221 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-96
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-97
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 13 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,bc102f237ace,5ce28c488e0c
```

---

@LAT105LON184 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 34953567 ±0 frame:5500
seq: 1084
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:222
said: 1 | **LINKWIN** t_ms:34952717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-47 rssi_med:-46 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-75 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON185 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35013567 ±0 frame:5500
seq: 1086
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:224
said: 1 | **LINKWIN** t_ms:35012717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-38 rssi_med:-36 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-52 rssi_max:-50
said: 4 | 0x00000200 espnow violated predicted:-46 observed:-36
percept: 4 | 0x00000200 | link_stable | espnow | - | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-52
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON410 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35041679 ±21 frame:5500
seq: 225
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1087
said: 1 | **LINKWIN** t_ms:35038793 stream:0x9afbb748 wall:0 window_ms:60020
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-36 rssi_med:-31 rssi_max:-31
```

---

@LAT103LON411 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35102767 ±21 frame:5500
seq: 226
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1087
said: 1 | **LINKWIN** t_ms:35099882 stream:0x9afbb748 wall:0 window_ms:61088
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-56 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-37 rssi_med:-31 rssi_max:-31
```

---

@LAT103LON412 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35162857 ±21 frame:5500
seq: 227
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1091
said: 1 | **LINKWIN** t_ms:35159968 stream:0x9afbb748 wall:0 window_ms:60088
said: 2 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-61 rssi_med:-51 rssi_max:-45
said: 3 | **LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-37 rssi_med:-32 rssi_max:-30
```

---

@LAT103LON413 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35223666 ±21 frame:5500
seq: 228
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1091
said: 1 | **LINKWIN** t_ms:35220779 stream:0x9afbb748 wall:0 window_ms:60810
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-47 rssi_max:-44
said: 3 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-34 rssi_med:-32 rssi_max:-30
```

---

@LAT105LON186 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35073567 ±0 frame:5500
seq: 1088
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:225
said: 1 | **LINKWIN** t_ms:35072717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:39 rssi_min:-38 rssi_med:-36 rssi_max:-36
said: 4 | 0x00000200 espnow met predicted:-36 observed:-36
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-52 observed:-52
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON187 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35133567 ±0 frame:5500
seq: 1090
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:226
said: 1 | **LINKWIN** t_ms:35132717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-38 rssi_med:-36 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-52 rssi_max:-50
said: 4 | 0x00000200 ble met predicted:-52 observed:-52
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-36 observed:-36
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON188 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35193567 ±0 frame:5500
seq: 1092
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:227
said: 1 | **LINKWIN** t_ms:35192717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-51 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-43 rssi_med:-34 rssi_max:-33
said: 4 | 0x00000200 espnow met predicted:-36 observed:-34
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-52 observed:-51
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON414 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35287593 ±21 frame:5500
seq: 229
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1096
said: 1 | **LINKWIN** t_ms:35284703 stream:0x9afbb748 wall:0 window_ms:63924
said: 2 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-56 rssi_med:-49 rssi_max:-44
said: 3 | **LINK** peer:0x00000300 proto:espnow n:62 rssi_min:-36 rssi_med:-33 rssi_max:-30
```

---

@LAT103LON415 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35349670 ±21 frame:5500
seq: 230
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1098
said: 1 | **LINKWIN** t_ms:35346778 stream:0x9afbb748 wall:0 window_ms:62076
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-57 rssi_med:-51 rssi_max:-44
said: 3 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-36 rssi_med:-33 rssi_max:-30
```

---

@LAT105LON189 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35253567 ±0 frame:5500
seq: 1094
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:227
said: 1 | **LINKWIN** t_ms:35252717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-79 rssi_med:-51 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 4 | 0x00000200 ble met predicted:-51 observed:-51
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-34 observed:-34
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON190 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35313567 ±0 frame:5500
seq: 1097
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:228
said: 1 | **LINKWIN** t_ms:35312717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-37 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000200 proto:ble n:70 rssi_min:-80 rssi_med:-52 rssi_max:-49
said: 4 | 0x00000200 ble met predicted:-51 observed:-52
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-34 observed:-35
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON416 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35411758 ±21 frame:5500
seq: 231
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1100
said: 1 | **LINKWIN** t_ms:35408868 stream:0x9afbb748 wall:0 window_ms:62089
said: 2 | **LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-55 rssi_med:-52 rssi_max:-47
```

---

@LAT105LON191 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35373567 ±0 frame:5500
seq: 1099
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:230
said: 1 | **LINKWIN** t_ms:35372717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-37 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-81 rssi_med:-53 rssi_max:-48
said: 4 | 0x00000200 espnow met predicted:-35 observed:-35
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-52 observed:-53
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON192 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35433567 ±0 frame:5500
seq: 1101
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:231
said: 1 | **LINKWIN** t_ms:35432717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-59 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-38 rssi_med:-35 rssi_max:-35
said: 4 | 0x00000200 espnow met predicted:-35 observed:-35
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-53 observed:-52
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON417 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35475581 ±21 frame:5500
seq: 232
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1102
said: 1 | **LINKWIN** t_ms:35472687 stream:0x9afbb748 wall:0 window_ms:63820
said: 2 | **LINK** peer:0x00000300 proto:espnow n:61 rssi_min:-37 rssi_med:-31 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-79 rssi_med:-52 rssi_max:-49
```

---

@LAT105LON193 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35493567 ±0 frame:5500
seq: 1103
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:232
said: 1 | **LINKWIN** t_ms:35492717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-58 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 4 | 0x00000200 ble met predicted:-52 observed:-52
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```
@LAT106LON6 | created:0 | updated:0

**BAR** frame:5500 bar:59 own:9 held:10 terms:2 digest:0xee5eb19f settled_ms:122000
**HOLDS** agent:0x00000200 n:9 lo:221 hi:230 sum:2031
**HOLDS** agent:0x00000300 n:10 lo:1080 hi:1099 sum:10892

---

@LAT103LON418 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35537585 ±21 frame:5500
seq: 233
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1104
said: 1 | **LINKWIN** t_ms:35536691 stream:0x9afbb748 wall:0 window_ms:62003
said: 2 | **LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-36 rssi_med:-31 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-56 rssi_med:-52 rssi_max:-49
```

---

@LAT105LON194 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35553567 ±0 frame:5500
seq: 1105
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:233
said: 1 | **LINKWIN** t_ms:35552717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-82 rssi_med:-51 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-38 rssi_med:-35 rssi_max:-35
said: 4 | 0x00000200 ble met predicted:-52 observed:-51
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON419 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35597586 ±21 frame:5500
seq: 234
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1106
said: 1 | **LINKWIN** t_ms:35596697 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-56 rssi_med:-52 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-36 rssi_med:-31 rssi_max:-31
```

---

@LAT105LON195 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35613567 ±0 frame:5500
seq: 1107
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:233
said: 1 | **LINKWIN** t_ms:35612717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 4 | 0x00000200 ble met predicted:-51 observed:-52
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON420 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35658420 ±21 frame:5500
seq: 235
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1108
said: 1 | **LINKWIN** t_ms:35655543 stream:0x9afbb748 wall:0 window_ms:60854
said: 2 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-36 rssi_med:-31 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-56 rssi_med:-52 rssi_max:-49
```

---

@LAT103LON421 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35719663 ±21 frame:5500
seq: 236
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1110
said: 1 | **LINKWIN** t_ms:35716767 stream:0x9afbb748 wall:0 window_ms:61222
said: 2 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-36 rssi_med:-31 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-56 rssi_med:-52 rssi_max:-49
```

---

@LAT105LON196 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35673567 ±0 frame:5500
seq: 1109
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:235
said: 1 | **LINKWIN** t_ms:35672717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 4 | 0x00000200 ble met predicted:-52 observed:-52
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON197 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35733567 ±0 frame:5500
seq: 1111
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:236
said: 1 | **LINKWIN** t_ms:35732717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 4 | 0x00000200 ble met predicted:-52 observed:-52
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON422 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35781607 ±21 frame:5500
seq: 237
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1112
said: 1 | **LINKWIN** t_ms:35778710 stream:0x9afbb748 wall:0 window_ms:61943
said: 2 | **LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-36 rssi_med:-31 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-56 rssi_med:-52 rssi_max:-47
```

---

@LAT105LON198 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35793567 ±0 frame:5500
seq: 1113
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:237
said: 1 | **LINKWIN** t_ms:35792717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-58 rssi_med:-52 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-37 rssi_med:-36 rssi_max:-34
said: 4 | 0x00000200 ble met predicted:-52 observed:-52
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-35 observed:-36
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON423 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35842601 ±21 frame:5500
seq: 238
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1114
said: 1 | **LINKWIN** t_ms:35839702 stream:0x9afbb748 wall:0 window_ms:60993
said: 2 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-36 rssi_med:-34 rssi_max:-30
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-54 rssi_med:-51 rssi_max:-46
```

---

@LAT105LON199 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35853567 ±0 frame:5500
seq: 1115
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:238
said: 1 | **LINKWIN** t_ms:35852717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 4 | 0x00000200 ble met predicted:-52 observed:-53
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-36 observed:-35
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON424 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35903700 ±21 frame:5500
seq: 239
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1116
said: 1 | **LINKWIN** t_ms:35900799 stream:0x9afbb748 wall:0 window_ms:61097
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-54 rssi_med:-52 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-36 rssi_med:-34 rssi_max:-30
```

---

@LAT105LON200 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35913567 ±0 frame:5500
seq: 1117
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:239
said: 1 | **LINKWIN** t_ms:35912717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-36 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-80 rssi_med:-51 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-53 observed:-51
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON425 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35964571 ±21 frame:5500
seq: 240
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1118
said: 1 | **LINKWIN** t_ms:35961671 stream:0x9afbb748 wall:0 window_ms:60870
said: 2 | **LINK** peer:0x00000300 proto:ble n:75 rssi_min:-80 rssi_med:-52 rssi_max:-45
said: 3 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-35 rssi_med:-33 rssi_max:-30
```

---

@LAT105LON201 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 35973567 ±0 frame:5500
seq: 1119
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:240
said: 1 | **LINKWIN** t_ms:35972717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:39 rssi_min:-37 rssi_med:-35 rssi_max:-32
said: 4 | 0x00000200 espnow met predicted:-35 observed:-35
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-51 observed:-51
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON426 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 36025651 ±21 frame:5500
seq: 241
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1120
said: 1 | **LINKWIN** t_ms:36024749 stream:0x9afbb748 wall:0 window_ms:61080
said: 2 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-51 rssi_max:-46
said: 3 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-36 rssi_med:-33 rssi_max:-30
```

---

@LAT104LON42 | created:0 | updated:0

**carried through @LAT103LON386**

```ttdb-carried
through: 386
```

---

@LAT103LON427 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 36085653 ±21 frame:5500
seq: 242
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1122
said: 1 | **LINKWIN** t_ms:36084756 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-34 rssi_med:-32 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-49 rssi_max:-46
```
@LAT106LON7 | created:0 | updated:0

**BAR** frame:5500 bar:60 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:120082
**HOLDS** agent:0x00000200 n:10 lo:231 hi:240 sum:2355
**HOLDS** agent:0x00000300 n:10 lo:1101 hi:1119 sum:11100

---

@LAT105LON202 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 36033567 ±0 frame:5500
seq: 1121
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:241
said: 1 | **LINKWIN** t_ms:36032717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-59 rssi_med:-53 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-39 rssi_med:-36 rssi_max:-33
said: 4 | 0x00000200 ble met predicted:-51 observed:-53
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-35 observed:-36
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON428 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 36145653 ±21 frame:5500
seq: 243
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1124
said: 1 | **LINKWIN** t_ms:36144756 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-34 rssi_med:-32 rssi_max:-30
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-49 rssi_max:-43
```

---

@LAT105LON203 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 36093567 ±0 frame:5500
seq: 1123
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:242
said: 1 | **LINKWIN** t_ms:36092717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-37 rssi_med:-33 rssi_max:-33
said: 4 | 0x00000200 ble met predicted:-53 observed:-51
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-36 observed:-33
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON204 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 36153567 ±0 frame:5500
seq: 1125
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:243
said: 1 | **LINKWIN** t_ms:36152717 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-51 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-36 rssi_med:-34 rssi_max:-32
said: 4 | 0x00000200 ble met predicted:-51 observed:-51
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-33 observed:-34
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON8222 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36189525 ±21 frame:5500
seq: 244
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1126
said: 1 | **ENTWIN** t_ms:36186679 stream:0x9afbb748 wall:0 window_ms:603105 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-97
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d
said: 11 | **COVERED** windows:1 entities:5 window_ms:600766 first_t_ms:35583580 last_t_ms:35583580 covered_by:@LAT103LON8221
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
```

---

@LAT103LON429 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 36207500 ±21 frame:5500
seq: 245
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1126
said: 1 | **LINKWIN** t_ms:36204594 stream:0x9afbb748 wall:0 window_ms:61845
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-52 rssi_med:-48 rssi_max:-45
said: 3 | **LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-34 rssi_med:-32 rssi_max:-31
```
