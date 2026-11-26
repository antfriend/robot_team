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

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:10118783 stream:0xc909d5a8 wall:0 node:0x00000200

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:43 last_lon:42 t_ms:10128032 stream:0xc909d5a8 wall:0 node:0x00000200

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:16027778 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-32 rssi_max:-30
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-17 rssi_med:-17 rssi_max:-16

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:18547827 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-37 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-18 rssi_med:-17 rssi_max:-16

---

@LAT103LON8282 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 23318173 ±21 frame:20500
seq: 1550
follows: 0x00000010:932 0x00000011:870 0x00000012:776 0x00000100:732 0x00000300:3728
said: 1 | **ENTWIN** t_ms:23301954 stream:0xa0be1a79 wall:0 window_ms:600073 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-52
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON8283 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 23918180 ±21 frame:20500
seq: 1561
follows: 0x00000010:943 0x00000011:880 0x00000012:787 0x00000100:732 0x00000300:3749
said: 1 | **ENTWIN** t_ms:23902002 stream:0xa0be1a79 wall:0 window_ms:599998 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-54
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,bc102f237ace,5ce28c488e0c,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON8284 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 26918251 ±21 frame:20500
seq: 1612
follows: 0x00000010:994 0x00000011:932 0x00000012:837 0x00000100:732 0x00000300:3854
said: 1 | **ENTWIN** t_ms:26902076 stream:0xa0be1a79 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-97
said: 10 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,bc102f237ace,84a329c78fec,e6b32d2cea8b,0283cce0e689
said: 12 | **COVERED** windows:4 entities:9 window_ms:2400022 first_t_ms:24502005 last_t_ms:26302024 covered_by:@LAT103LON8283
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-48 windows:4
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-73 windows:4
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-75 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:3 rssi:-89 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-89 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-87 windows:4
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-95 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-95 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-94 windows:2
```

---

@LAT103LON8285 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 27518266 ±21 frame:20500
seq: 1623
follows: 0x00000010:1005 0x00000011:943 0x00000012:848 0x00000100:732 0x00000300:3874
said: 1 | **ENTWIN** t_ms:27502081 stream:0xa0be1a79 wall:0 window_ms:600005 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-51
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec
```

---

@LAT103LON8286 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 28718296 ±21 frame:20500
seq: 1644
follows: 0x00000010:1025 0x00000011:965 0x00000012:869 0x00000100:732 0x00000300:3915
said: 1 | **ENTWIN** t_ms:28702092 stream:0xa0be1a79 wall:0 window_ms:600012 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,bc102f237ace,84a329c78fec,0283cce0e689,e6b32d2cea8b
said: 13 | **COVERED** windows:1 entities:6 window_ms:599999 first_t_ms:28102080 last_t_ms:28102080 covered_by:@LAT103LON8285
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95 windows:1
```

---

@LAT103LON8287 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 29318304 ±21 frame:20500
seq: 1655
follows: 0x00000010:1035 0x00000011:976 0x00000012:879 0x00000100:732 0x00000300:3935
said: 1 | **ENTWIN** t_ms:29302092 stream:0xa0be1a79 wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,84a329c78fec
```

---

@LAT103LON8288 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 29918316 ±21 frame:20500
seq: 1666
follows: 0x00000010:1046 0x00000011:986 0x00000012:889 0x00000100:732 0x00000300:3957
said: 1 | **ENTWIN** t_ms:29902144 stream:0xa0be1a79 wall:0 window_ms:600001 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,5ce28c488e0c,e6b32d2cea8b,64677217947d
```

---

@LAT103LON8289 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31118353 ±21 frame:20500
seq: 1687
follows: 0x00000010:1067 0x00000011:1008 0x00000012:910 0x00000100:732 0x00000300:3997
said: 1 | **ENTWIN** t_ms:31102161 stream:0xa0be1a79 wall:0 window_ms:600017 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,84a329c78fec,bc102f237ace,5ce28c488e0c
said: 10 | **COVERED** windows:1 entities:9 window_ms:600000 first_t_ms:30502144 last_t_ms:30502144 covered_by:@LAT103LON8288
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93 windows:1
```

---

@LAT103LON8290 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31718379 ±21 frame:20500
seq: 1698
follows: 0x00000010:1078 0x00000011:1019 0x00000012:920 0x00000100:732 0x00000300:4018
said: 1 | **ENTWIN** t_ms:31702178 stream:0xa0be1a79 wall:0 window_ms:600016 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b
```

---

@LAT103LON8291 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 32318388 ±21 frame:20500
seq: 1709
follows: 0x00000010:1088 0x00000011:1030 0x00000012:930 0x00000100:732 0x00000300:4039
said: 1 | **ENTWIN** t_ms:32302176 stream:0xa0be1a79 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c
```

---

@LAT103LON8292 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 32918405 ±21 frame:20500
seq: 1720
follows: 0x00000010:1099 0x00000011:1041 0x00000012:940 0x00000100:732 0x00000300:4059
said: 1 | **ENTWIN** t_ms:32902235 stream:0xa0be1a79 wall:0 window_ms:600007 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec
```

---

@LAT103LON8293 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34718450 ±21 frame:20500
seq: 1751
follows: 0x00000010:1128 0x00000011:1073 0x00000012:971 0x00000100:732 0x00000300:4122
said: 1 | **ENTWIN** t_ms:34702251 stream:0xa0be1a79 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,5ce28c488e0c
said: 12 | **COVERED** windows:2 entities:8 window_ms:1200015 first_t_ms:33502271 last_t_ms:34102250 covered_by:@LAT103LON8292
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-49 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-74 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-80 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-90 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-90 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-92 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-92 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96 windows:1
```

---

@LAT103LON8294 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 35318459 ±21 frame:20500
seq: 1762
follows: 0x00000010:1138 0x00000011:1083 0x00000012:981 0x00000100:732 0x00000300:4144
said: 1 | **ENTWIN** t_ms:35302250 stream:0xa0be1a79 wall:0 window_ms:599999 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,84a329c78fec
```

---

@LAT103LON8295 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36177747 ±22 frame:20500
seq: 1777
follows: 0x00000010:1153 0x00000011:1098 0x00000012:996 0x00000100:732 0x00000300:4174
said: 1 | **ENTWIN** t_ms:36161512 stream:0xa0be1a79 wall:0 window_ms:60122 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8296 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 37378831 ±24 frame:20500
seq: 1798
follows: 0x00000010:1176 0x00000011:1120 0x00000012:1018 0x00000100:732 0x00000300:4210
said: 1 | **ENTWIN** t_ms:37362628 stream:0xa0be1a79 wall:0 window_ms:599979 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 9 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 10 | **COVERED** windows:1 entities:6 window_ms:601091 first_t_ms:36762648 last_t_ms:36762648 covered_by:@LAT103LON8295
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90 windows:1
```

---

@LAT103LON8297 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 62080 ±0 frame:8000
seq: 1818
follows: 0x00000010:1183 0x00000011:1133 0x00000012:1036 0x00000100:732 0x00000300:4214
said: 1 | **ENTWIN** t_ms:51320 stream:0x364dd329 wall:0 window_ms:62080 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8298 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 887881 ±21 frame:10000
seq: 1835
follows: 0x00000010:1189 0x00000011:1138 0x00000012:1041 0x00000100:746 0x00000300:4226
said: 1 | **ENTWIN** t_ms:1203830 stream:0x364dd329 wall:0 window_ms:600072 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 9 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 10 | **COVERED** windows:1 entities:6 window_ms:552437 first_t_ms:603763 last_t_ms:603763 covered_by:@LAT103LON8297
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
```

---

@LAT103LON8299 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 62143 ±21 frame:8000
seq: 1840
follows: 0x00000010:1192 0x00000011:1141 0x00000012:1044 0x00000100:751 0x00000300:4232
said: 1 | **ENTWIN** t_ms:49353 stream:0x732acba3 wall:0 window_ms:62152 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-53
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8300 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1213968 ±21 frame:8000
seq: 1860
follows: 0x00000010:1212 0x00000011:1161 0x00000012:1064 0x00000100:772 0x00000300:4272
said: 1 | **ENTWIN** t_ms:1203287 stream:0x732acba3 wall:0 window_ms:600002 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-54
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,84a329c78fec,0283cce0e689
said: 12 | **COVERED** windows:1 entities:8 window_ms:551802 first_t_ms:603285 last_t_ms:603285 covered_by:@LAT103LON8299
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-52 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
```

---

@LAT103LON8301 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1813976 ±21 frame:8000
seq: 1871
follows: 0x00000010:1223 0x00000011:1172 0x00000012:1075 0x00000100:783 0x00000300:4293
said: 1 | **ENTWIN** t_ms:1803287 stream:0x732acba3 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-55
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,84a329c78fec,c2e94427adcf,0283cce0e689
```

---

@LAT103LON8302 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4214014 ±21 frame:8000
seq: 1912
follows: 0x00000010:1267 0x00000011:1213 0x00000012:1117 0x00000100:828 0x00000300:4376
said: 1 | **ENTWIN** t_ms:4203338 stream:0x732acba3 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,e6b32d2cea8b,02c57d2e0f0d,c2e94427adcf,7236bc441422,0283cce0e689
said: 12 | **COVERED** windows:3 entities:10 window_ms:1800000 first_t_ms:2403287 last_t_ms:3603286 covered_by:@LAT103LON8301
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-44 windows:3
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-75 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-77 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-84 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-85 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:3 rssi:-91 windows:3
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-94 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1
```

---

@LAT103LON8303 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4814022 ±21 frame:8000
seq: 1923
follows: 0x00000010:1278 0x00000011:1223 0x00000012:1128 0x00000100:838 0x00000300:4396
said: 1 | **ENTWIN** t_ms:4803337 stream:0x732acba3 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,64677217947d,e6b32d2cea8b,02c57d2e0f0d,7236bc441422,c2e94427adcf,0283cce0e689
```

---

@LAT106LON171 | created:0 | updated:0

**BAR** frame:8000 bar:12 own:10 held:40 terms:9 digest:0x9c7c5137 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1312 hi:1322 sum:13174
**HOLDS** agent:0x00000011 n:10 lo:1256 hi:1265 sum:12605
**HOLDS** agent:0x00000012 n:10 lo:1162 hi:1171 sum:11665
**HOLDS** agent:0x00000200 n:10 lo:1954 hi:1963 sum:19585
**HOLDS** agent:0x00000300 n:10 lo:4459 hi:4477 sum:44680
**DELIVER** up_s:7517 heap:6236 fetched:494 unanswered:348 broken:90 resumed:1524 empty:234 served:2107 wants:2126 early:40 wantq_drop:3 superseded:5

---

@LAT103LON8304 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7814142 ±21 frame:8000
seq: 1974
follows: 0x00000010:1332 0x00000011:1275 0x00000012:1182 0x00000100:895 0x00000300:4500
said: 1 | **ENTWIN** t_ms:7803467 stream:0x732acba3 wall:0 window_ms:599999 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
said: 5 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 8 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:8 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,7236bc441422,e6b32d2cea8b,c2e94427adcf,5203cfd1b904,64677217947d
said: 10 | **COVERED** windows:4 entities:10 window_ms:2400080 first_t_ms:5403337 last_t_ms:7203468 covered_by:@LAT103LON8303
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-43 windows:4
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-72 windows:4
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-78 windows:4
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-80 windows:4
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-84 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:3 rssi:-87 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:4 rssi:-91 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:2 rssi:-94 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-93 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97 windows:1
```

---

@LAT106LON172 | created:0 | updated:0

**BAR** frame:8000 bar:13 own:10 held:40 terms:9 digest:0x45949f72 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1323 hi:1332 sum:13275
**HOLDS** agent:0x00000011 n:10 lo:1266 hi:1275 sum:12705
**HOLDS** agent:0x00000012 n:10 lo:1172 hi:1182 sum:11774
**HOLDS** agent:0x00000200 n:10 lo:1964 hi:1973 sum:19685
**HOLDS** agent:0x00000300 n:10 lo:4479 hi:4499 sum:44897
**DELIVER** up_s:8117 heap:7152 fetched:533 unanswered:375 broken:100 resumed:1687 empty:248 served:2302 wants:2325 early:40 wantq_drop:5 superseded:7

---

@LAT106LON173 | created:0 | updated:0

**BAR** frame:8000 bar:14 own:10 held:40 terms:9 digest:0x4b93e0ea settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1333 hi:1342 sum:13375
**HOLDS** agent:0x00000011 n:10 lo:1276 hi:1285 sum:12805
**HOLDS** agent:0x00000012 n:10 lo:1183 hi:1193 sum:11884
**HOLDS** agent:0x00000200 n:10 lo:1975 hi:1984 sum:19795
**HOLDS** agent:0x00000300 n:10 lo:4501 hi:4520 sum:45109
**DELIVER** up_s:8710 heap:9084 fetched:577 unanswered:406 broken:105 resumed:1847 empty:268 served:2483 wants:2507 early:40 wantq_drop:5 superseded:9

---

@LAT106LON174 | created:0 | updated:0

**BAR** frame:8000 bar:15 own:10 held:40 terms:9 digest:0x033334fc settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1343 hi:1353 sum:13484
**HOLDS** agent:0x00000011 n:10 lo:1286 hi:1295 sum:12905
**HOLDS** agent:0x00000012 n:10 lo:1194 hi:1204 sum:11994
**HOLDS** agent:0x00000200 n:10 lo:1985 hi:1994 sum:19895
**HOLDS** agent:0x00000300 n:10 lo:4522 hi:4541 sum:45319
**DELIVER** up_s:9315 heap:5232 fetched:616 unanswered:435 broken:109 resumed:1954 empty:283 served:2655 wants:2681 early:40 wantq_drop:5 superseded:9

---

@LAT106LON175 | created:0 | updated:0

**BAR** frame:8000 bar:16 own:10 held:40 terms:9 digest:0x8fff28fa settled_ms:300002
**HOLDS** agent:0x00000010 n:10 lo:1354 hi:1364 sum:13594
**HOLDS** agent:0x00000011 n:10 lo:1296 hi:1306 sum:13014
**HOLDS** agent:0x00000012 n:10 lo:1205 hi:1215 sum:12104
**HOLDS** agent:0x00000200 n:10 lo:1995 hi:2004 sum:19995
**HOLDS** agent:0x00000300 n:10 lo:4543 hi:4562 sum:45528
**DELIVER** up_s:9915 heap:5500 fetched:656 unanswered:461 broken:117 resumed:2075 empty:302 served:2831 wants:2859 early:40 wantq_drop:5 superseded:9

---

@LAT106LON176 | created:0 | updated:0

**BAR** frame:8000 bar:17 own:10 held:40 terms:9 digest:0x5345e039 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1365 hi:1374 sum:13695
**HOLDS** agent:0x00000011 n:10 lo:1307 hi:1316 sum:13115
**HOLDS** agent:0x00000012 n:10 lo:1216 hi:1226 sum:12214
**HOLDS** agent:0x00000200 n:10 lo:2005 hi:2014 sum:20095
**HOLDS** agent:0x00000300 n:10 lo:4564 hi:4582 sum:45730
**DELIVER** up_s:10515 heap:8176 fetched:697 unanswered:500 broken:121 resumed:2180 empty:320 served:3001 wants:3029 early:40 wantq_drop:8 superseded:10

---

@LAT106LON177 | created:0 | updated:0

**BAR** frame:8000 bar:18 own:10 held:40 terms:9 digest:0xabc37525 settled_ms:300012
**HOLDS** agent:0x00000010 n:10 lo:1375 hi:1384 sum:13795
**HOLDS** agent:0x00000011 n:10 lo:1317 hi:1326 sum:13215
**HOLDS** agent:0x00000012 n:10 lo:1227 hi:1237 sum:12324
**HOLDS** agent:0x00000200 n:10 lo:2015 hi:2024 sum:20195
**HOLDS** agent:0x00000300 n:10 lo:4584 hi:4602 sum:45930
**DELIVER** up_s:11116 heap:8444 fetched:736 unanswered:525 broken:126 resumed:2305 empty:338 served:3175 wants:3205 early:40 wantq_drop:8 superseded:12

---

@LAT103LON8305 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11412199 ±22 frame:8000
seq: 2035
follows: 0x00000010:1395 0x00000011:1337 0x00000012:1248 0x00000100:960 0x00000300:4624
said: 1 | **ENTWIN** t_ms:11403519 stream:0x732acba3 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,64677217947d,c2e94427adcf,7236bc441422
said: 12 | **COVERED** windows:5 entities:10 window_ms:3000001 first_t_ms:8403467 last_t_ms:10803519 covered_by:@LAT103LON8304
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-44 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-75 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-80 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-84 windows:5
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-82 windows:5
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-85 windows:4
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:4 rssi:-91 windows:4
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-96 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:4 rssi:-94 windows:4
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95 windows:1
```

---

@LAT106LON178 | created:0 | updated:0

**BAR** frame:8000 bar:19 own:10 held:38 terms:9 digest:0xb5144cb4 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1385 hi:1395 sum:13904
**HOLDS** agent:0x00000011 n:10 lo:1327 hi:1337 sum:13324
**HOLDS** agent:0x00000012 n:10 lo:1238 hi:1248 sum:12434
**HOLDS** agent:0x00000200 n:10 lo:2025 hi:2034 sum:20295
**HOLDS** agent:0x00000300 n:8 lo:4604 hi:4623 sum:36901
**DELIVER** up_s:11714 heap:5204 fetched:772 unanswered:553 broken:132 resumed:2425 empty:351 served:3316 wants:3346 early:40 wantq_drop:8 superseded:13

---

@LAT103LON8306 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 62081 ±0 frame:7500
seq: 2044
follows: 0x00000010:1403 0x00000011:1346 0x00000012:1257 0x00000100:967 0x00000300:4638
said: 1 | **ENTWIN** t_ms:51955 stream:0xe106395b wall:0 window_ms:62081 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON8307 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 109565 ±21 frame:7500
seq: 2046
follows: 0x00000010:1408 0x00000011:1353 0x00000012:1268 0x00000100:1001 0x00000300:4641
said: 1 | **ENTWIN** t_ms:429268 stream:0xc9e0e898 wall:0 window_ms:62065 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT106LON179 | created:0 | updated:0

**BAR** frame:7500 bar:1 own:9 held:32 terms:9 digest:0x7688be17 settled_ms:300000
**HOLDS** agent:0x00000010 n:9 lo:1409 hi:1417 sum:12717
**HOLDS** agent:0x00000011 n:8 lo:1354 hi:1361 sum:10860
**HOLDS** agent:0x00000012 n:8 lo:1269 hi:1276 sum:10180
**HOLDS** agent:0x00000200 n:9 lo:2045 hi:2054 sum:18449
**HOLDS** agent:0x00000300 n:7 lo:4648 hi:4660 sum:32578
**DELIVER** up_s:866 heap:6084 fetched:68 unanswered:41 broken:6 resumed:173 empty:28 served:237 wants:245 early:47 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:4 split:1
**SPLIT** agent:0x00000012 grammar:0xaf98ac36

---

@LAT103LON8308 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1261502 ±21 frame:7500
seq: 2066
follows: 0x00000010:1428 0x00000011:1373 0x00000012:1288 0x00000100:1021 0x00000300:4683
said: 1 | **ENTWIN** t_ms:1583228 stream:0xc9e0e898 wall:0 window_ms:600002 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689
said: 10 | **COVERED** windows:1 entities:6 window_ms:551894 first_t_ms:983226 last_t_ms:983226 covered_by:@LAT103LON8307
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
```

---

@LAT106LON180 | created:0 | updated:0

**BAR** frame:7500 bar:2 own:10 held:40 terms:9 digest:0x4d262fda settled_ms:300033
**HOLDS** agent:0x00000010 n:10 lo:1418 hi:1427 sum:14225
**HOLDS** agent:0x00000011 n:10 lo:1362 hi:1371 sum:13665
**HOLDS** agent:0x00000012 n:10 lo:1277 hi:1287 sum:12821
**HOLDS** agent:0x00000200 n:10 lo:2055 hi:2064 sum:20595
**HOLDS** agent:0x00000300 n:10 lo:4662 hi:4680 sum:46710
**DELIVER** up_s:1465 heap:6640 fetched:106 unanswered:68 broken:14 resumed:290 empty:47 served:405 wants:416 early:47 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:4 split:1
**SPLIT** agent:0x00000012 grammar:0xaf98ac36

---

@LAT106LON181 | created:0 | updated:0

**BAR** frame:7500 bar:3 own:10 held:39 terms:9 digest:0xcd88d703 settled_ms:300032
**HOLDS** agent:0x00000010 n:10 lo:1429 hi:1438 sum:14335
**HOLDS** agent:0x00000011 n:10 lo:1373 hi:1382 sum:13775
**HOLDS** agent:0x00000012 n:9 lo:1288 hi:1297 sum:11633
**HOLDS** agent:0x00000200 n:10 lo:2065 hi:2075 sum:20704
**HOLDS** agent:0x00000300 n:10 lo:4682 hi:4701 sum:46919
**DELIVER** up_s:2067 heap:6372 fetched:144 unanswered:83 broken:20 resumed:404 empty:69 served:545 wants:559 early:47 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT106LON182 | created:0 | updated:0

**BAR** frame:7500 bar:4 own:10 held:38 terms:9 digest:0xc9a9ac56 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1440 hi:1449 sum:14445
**HOLDS** agent:0x00000011 n:10 lo:1383 hi:1392 sum:13875
**HOLDS** agent:0x00000012 n:8 lo:1299 hi:1307 sum:10425
**HOLDS** agent:0x00000200 n:10 lo:2076 hi:2085 sum:20805
**HOLDS** agent:0x00000300 n:10 lo:4703 hi:4723 sum:47137
**DELIVER** up_s:2667 heap:9580 fetched:186 unanswered:109 broken:25 resumed:489 empty:92 served:732 wants:746 early:47 wantq_drop:0 superseded:2
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT106LON183 | created:0 | updated:0

**BAR** frame:7500 bar:5 own:10 held:40 terms:9 digest:0xdd4d4ce8 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1450 hi:1459 sum:14545
**HOLDS** agent:0x00000011 n:10 lo:1394 hi:1403 sum:13985
**HOLDS** agent:0x00000012 n:10 lo:1308 hi:1317 sum:13125
**HOLDS** agent:0x00000200 n:10 lo:2086 hi:2095 sum:20905
**HOLDS** agent:0x00000300 n:10 lo:4725 hi:4743 sum:47340
**DELIVER** up_s:3266 heap:6616 fetched:224 unanswered:120 broken:26 resumed:607 empty:112 served:904 wants:919 early:47 wantq_drop:5 superseded:3
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT106LON184 | created:0 | updated:0

**BAR** frame:7500 bar:6 own:10 held:40 terms:8 digest:0xe5fee0c4 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1460 hi:1469 sum:14645
**HOLDS** agent:0x00000011 n:10 lo:1404 hi:1413 sum:14085
**HOLDS** agent:0x00000012 n:10 lo:1318 hi:1328 sum:13231
**HOLDS** agent:0x00000200 n:10 lo:2096 hi:2105 sum:21005
**HOLDS** agent:0x00000300 n:10 lo:4745 hi:4763 sum:47540
**DELIVER** up_s:3868 heap:9568 fetched:266 unanswered:152 broken:30 resumed:744 empty:130 served:1033 wants:1049 early:47 wantq_drop:5 superseded:4
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON8309 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4103572 ±21 frame:7500
seq: 2114
follows: 0x00000010:1476 0x00000011:1420 0x00000012:1335 0x00000100:1073 0x00000300:4779
said: 1 | **ENTWIN** t_ms:4417270 stream:0xc9e0e898 wall:0 window_ms:80164 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-96
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-96
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8310 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60031 ±21 frame:8500
seq: 2122
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4929
said: 1 | **ENTWIN** t_ms:187868 stream:0x678473b9 wall:0 window_ms:60038 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON8311 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60037 ±0 frame:9500
seq: 2130
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4943
said: 1 | **ENTWIN** t_ms:643355 stream:0x678473b9 wall:0 window_ms:60037 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-51
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON8312 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 52261 ±21 frame:8500
seq: 2132
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5029
said: 1 | **ENTWIN** t_ms:3213502 stream:0xf569ab0e wall:0 window_ms:60268 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8313 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 141261 ±21 frame:8500
seq: 2134
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5032
said: 1 | **ENTWIN** t_ms:3324773 stream:0xf569ab0e wall:0 window_ms:60049 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8314 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 61935 ±21 frame:9500
seq: 2136
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5034
said: 1 | **ENTWIN** t_ms:47884 stream:0xdfce8729 wall:0 window_ms:61943 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-53
said: 3 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON2232 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 302306 ±25 frame:9500
seq: 2140
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5046
said: 1 | **LINKWIN** t_ms:290196 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-54 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:61 rssi_min:-45 rssi_med:-35 rssi_max:-29
```

---

@LAT103LON2233 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 133458 ±21 frame:9500
seq: 2141
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5048
said: 1 | **LINKWIN** t_ms:358618 stream:0xdfce8729 wall:0 window_ms:61409
said: 2 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-37 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-50 rssi_max:-47
```

---

@LAT103LON8315 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 133503 ±21 frame:9500
seq: 2142
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5048
said: 1 | **ENTWIN** t_ms:358618 stream:0xdfce8729 wall:0 window_ms:61454 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON2234 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 193459 ±21 frame:9500
seq: 2143
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5050
said: 1 | **LINKWIN** t_ms:420027 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-69 rssi_med:-52 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:69 rssi_min:-53 rssi_med:-37 rssi_max:-34
```

---

@LAT103LON2235 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 253460 ±21 frame:9500
seq: 2144
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:480027 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:67 rssi_min:-52 rssi_med:-38 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-79 rssi_med:-54 rssi_max:-46
```

---

@LAT103LON8316 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:8500
seq: 2145
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **ENTWIN** t_ms:48514 stream:0xb8b08067 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```
@LAT106LON185 | created:0 | updated:0

**BAR** frame:8500 bar:1 own:9 held:11 terms:2 digest:0xa71b89d1 settled_ms:300000
**HOLDS** agent:0x00000200 n:9 lo:2121 hi:2133 sum:19138
**HOLDS** agent:0x00000300 n:11 lo:4930 hi:5033 sum:54596
**DELIVER** up_s:911 heap:9936 fetched:0 unanswered:30 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON2236 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1073202 ±0 frame:8500
seq: 2146
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:1061712 stream:0xb8b08067 wall:0 window_ms:1073202
said: 2 | **LINK** peer:0x00000300 proto:espnow n:3 rssi_min:-47 rssi_med:-47 rssi_max:-47
```

---

@LAT103LON2237 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1133193 ±21 frame:8500
seq: 2147
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:1121715 stream:0xb8b08067 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-75 rssi_med:-61 rssi_max:-58
said: 3 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-91 rssi_med:-49 rssi_max:-47
```

---

@LAT103LON2238 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 68995 ±21 frame:7500
seq: 2148
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5060
said: 1 | **LINKWIN** t_ms:57427 stream:0x1f824110 wall:0 window_ms:61386
said: 2 | **LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-40 rssi_med:-37 rssi_max:-32
said: 3 | **LINK** peer:0x00000300 proto:ble n:50 rssi_min:-82 rssi_med:-54 rssi_max:-48
```

---

@LAT103LON8317 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 69034 ±21 frame:7500
seq: 2149
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5060
said: 1 | **ENTWIN** t_ms:57427 stream:0x1f824110 wall:0 window_ms:61425 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON2239 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 139634 ±21 frame:7500
seq: 2150
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5067
said: 1 | **LINKWIN** t_ms:129626 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-53 rssi_med:-37 rssi_max:-29
said: 3 | **LINK** peer:0x00000300 proto:ble n:46 rssi_min:-75 rssi_med:-53 rssi_max:-44
```

---

@LAT103LON8318 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 139665 ±21 frame:7500
seq: 2151
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5067
said: 1 | **ENTWIN** t_ms:129626 stream:0xad373985 wall:0 window_ms:60031 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-60
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON2240 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 199636 ±21 frame:7500
seq: 2152
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5069
said: 1 | **LINKWIN** t_ms:189626 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:73 rssi_min:-47 rssi_med:-35 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-67 rssi_med:-45 rssi_max:-37
```

---

@LAT103LON2241 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 259638 ±21 frame:7500
seq: 2153
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5071
said: 1 | **LINKWIN** t_ms:249627 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:83 rssi_min:-44 rssi_med:-27 rssi_max:-25
```

---

@LAT103LON2242 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 95985 ±21 frame:7500
seq: 2154
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5075
said: 1 | **LINKWIN** t_ms:84171 stream:0xb4b25252 wall:0 window_ms:61315
said: 2 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-29 rssi_med:-24 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON8319 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 96031 ±21 frame:7500
seq: 2155
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5075
said: 1 | **ENTWIN** t_ms:84171 stream:0xb4b25252 wall:0 window_ms:61361 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON2243 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 155984 ±21 frame:7500
seq: 2156
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5077
said: 1 | **LINKWIN** t_ms:145486 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:64 rssi_min:-28 rssi_med:-25 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-70 rssi_med:-40 rssi_max:-36
```

---

@LAT103LON2244 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 215985 ±21 frame:7500
seq: 2157
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5079
said: 1 | **LINKWIN** t_ms:205486 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:64 rssi_min:-26 rssi_med:-25 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-47 rssi_med:-41 rssi_max:-37
```

---

@LAT103LON2245 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 141238 ±21 frame:10500
seq: 2158
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5086
said: 1 | **LINKWIN** t_ms:127872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-29 rssi_med:-27 rssi_max:-25
said: 3 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-47 rssi_med:-43 rssi_max:-39
```

---

@LAT103LON8320 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 141275 ±21 frame:10500
seq: 2159
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5086
said: 1 | **ENTWIN** t_ms:127872 stream:0x3bead35c wall:0 window_ms:60037 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON2246 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 201238 ±21 frame:10500
seq: 2160
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5088
said: 1 | **LINKWIN** t_ms:187872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:65 rssi_min:-30 rssi_med:-28 rssi_max:-24
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-50 rssi_med:-43 rssi_max:-40
```

---

@LAT103LON2247 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 261239 ±21 frame:10500
seq: 2161
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5090
said: 1 | **LINKWIN** t_ms:247872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:79 rssi_min:-46 rssi_med:-32 rssi_max:-26
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-66 rssi_med:-47 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:ble n:43 rssi_min:-51 rssi_med:-47 rssi_max:-43
said: 5 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-33 rssi_med:-31 rssi_max:-27
said: 6 | **LINK** peer:0x00000011 proto:ble n:36 rssi_min:-51 rssi_med:-49 rssi_max:-45
said: 7 | **LINK** peer:0x00000011 proto:espnow n:72 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:27 rssi_min:-56 rssi_med:-50 rssi_max:-46
said: 9 | **LINK** peer:0x00000012 proto:espnow n:37 rssi_min:-38 rssi_med:-34 rssi_max:-33
```

---

@LAT103LON2248 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 321240 ±23 frame:10500
seq: 2162
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5092
said: 1 | **LINKWIN** t_ms:307872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:61 rssi_min:-44 rssi_med:-31 rssi_max:-28
said: 3 | **LINK** peer:0x00000011 proto:espnow n:48 rssi_min:-35 rssi_med:-33 rssi_max:-28
said: 4 | **LINK** peer:0x00000010 proto:espnow n:78 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 5 | **LINK** peer:0x00000012 proto:espnow n:40 rssi_min:-36 rssi_med:-35 rssi_max:-33
said: 6 | **LINK** peer:0x00000011 proto:ble n:15 rssi_min:-63 rssi_med:-50 rssi_max:-46
said: 7 | **LINK** peer:0x00000012 proto:ble n:22 rssi_min:-56 rssi_med:-52 rssi_max:-47
said: 8 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-67 rssi_med:-47 rssi_max:-44
said: 9 | **LINK** peer:0x00000010 proto:ble n:26 rssi_min:-54 rssi_med:-47 rssi_max:-44
```

---

@LAT103LON2249 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 107656 ±22 frame:12000
seq: 2163
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000300:5097
said: 1 | **LINKWIN** t_ms:90717 stream:0x5d34e552 wall:0 window_ms:61963
said: 2 | **LINK** peer:0x00000300 proto:espnow n:65 rssi_min:-27 rssi_med:-23 rssi_max:-22
said: 3 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-45 rssi_med:-41 rssi_max:-35
```

---

@LAT103LON8321 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 107696 ±22 frame:12000
seq: 2164
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000300:5097
said: 1 | **ENTWIN** t_ms:90717 stream:0x5d34e552 wall:0 window_ms:62003 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT105LON5832 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 327830 ±0 frame:10500
seq: 5093
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2161
said: 1 | **LINKWIN** t_ms:314466 stream:0x3bead35c wall:0 window_ms:60040
said: 2 | **LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-21 rssi_med:-20 rssi_max:-18
said: 3 | **LINK** peer:0x00000010 proto:espnow n:53 rssi_min:-47 rssi_med:-33 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:ble n:15 rssi_min:-81 rssi_med:-45 rssi_max:-41
said: 5 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-51 rssi_max:-46
said: 6 | **LINK** peer:0x00000010 proto:ble n:15 rssi_min:-54 rssi_med:-50 rssi_max:-46
said: 7 | **LINK** peer:0x00000200 proto:espnow n:50 rssi_min:-48 rssi_med:-35 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:13 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 9 | **LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-33 rssi_med:-29 rssi_max:-28
said: 10 | 0x00000200 espnow met predicted:-36 observed:-35
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-52 observed:-51
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000010 espnow met predicted:-32 observed:-33
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-49 observed:-50
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-45 observed:-45
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow met predicted:-19 observed:-20
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-35 observed:-35
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT105LON5833 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 60000 ±0 frame:12000
seq: 5094
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2162
said: 1 | **LINKWIN** t_ms:45024 stream:0x5d34e552 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:10 rssi_min:-30 rssi_med:-30 rssi_max:-29
said: 3 | **LINK** peer:0x00000200 proto:ble n:11 rssi_min:-54 rssi_med:-45 rssi_max:-43
```

---

@LAT105LON5834 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 120074 ±0 frame:12000
seq: 5098
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2164
said: 1 | **LINKWIN** t_ms:105098 stream:0x5d34e552 wall:0 window_ms:60074
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-80 rssi_med:-45 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:66 rssi_min:-33 rssi_med:-29 rssi_max:-27
```

---

@LAT103LON2250 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 167627 ±21 frame:12000
seq: 2165
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000300:5101
said: 1 | **LINKWIN** t_ms:152680 stream:0x5d34e552 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-38 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:79 rssi_min:-31 rssi_med:-23 rssi_max:-22
said: 4 | **LINK** peer:0x00000010 proto:ble n:3 rssi_min:-54 rssi_med:-52 rssi_max:-48
```

---

@LAT105LON5835 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 2941588 ±21 frame:7500
seq: 1458
follows: 0x00000011:1402 0x00000012:1316 0x00000100:1052 0x00000200:2094 0x00000300:4742
said: 1 | **LINKWIN** t_ms:3263313 stream:0xc9e0e898 wall:0 window_ms:60019
said: 2 | **LINK** peer:0x00000200 proto:espnow n:127 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 3 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000300 proto:espnow n:210 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 5 | **LINK** peer:0x00000012 proto:espnow n:100 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:119 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 7 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-59 rssi_med:-55 rssi_max:-52
said: 8 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-52 rssi_max:-46
said: 9 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-49 rssi_med:-46 rssi_max:-39
```

---

@LAT105LON5836 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 2852963 ±21 frame:7500
seq: 1401
follows: 0x00000010:1456 0x00000012:1314 0x00000100:1050 0x00000200:2092 0x00000300:4738
said: 1 | **LINKWIN** t_ms:3174694 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:183 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-70 rssi_med:-69 rssi_max:-67
said: 4 | **LINK** peer:0x00000200 proto:espnow n:102 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 5 | **LINK** peer:0x00000010 proto:espnow n:118 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 6 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 7 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-81 rssi_med:-55 rssi_max:-51
said: 8 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:espnow n:67 rssi_min:-41 rssi_med:-35 rssi_max:-35
```

---

@LAT105LON5837 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3001589 ±21 frame:7500
seq: 1459
follows: 0x00000011:1403 0x00000012:1317 0x00000100:1053 0x00000200:2095 0x00000300:4744
said: 1 | **LINKWIN** t_ms:3323312 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-74 rssi_med:-56 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-66 rssi_med:-58 rssi_max:-54
said: 4 | **LINK** peer:0x00000012 proto:espnow n:116 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-58 rssi_med:-58 rssi_max:-57
said: 6 | **LINK** peer:0x00000200 proto:espnow n:108 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000011 proto:espnow n:116 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 8 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-46 rssi_max:-39
said: 9 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-60 rssi_med:-52 rssi_max:-46
```

---

@LAT105LON5838 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 2912968 ±21 frame:7500
seq: 1402
follows: 0x00000010:1457 0x00000012:1315 0x00000100:1051 0x00000200:2093 0x00000300:4740
said: 1 | **LINKWIN** t_ms:3234698 stream:0xc9e0e898 wall:0 window_ms:60004
said: 2 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-70 rssi_med:-69 rssi_max:-67
said: 4 | **LINK** peer:0x00000010 proto:espnow n:78 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 6 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-62 rssi_med:-58 rssi_max:-57
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-55 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-63 rssi_max:-59
```

---

@LAT105LON5839 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3061589 ±21 frame:7500
seq: 1460
follows: 0x00000011:1404 0x00000012:1318 0x00000100:1055 0x00000200:2096 0x00000300:4746
said: 1 | **LINKWIN** t_ms:3383313 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:155 rssi_min:-46 rssi_med:-43 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-58 rssi_med:-58 rssi_max:-56
said: 4 | **LINK** peer:0x00000200 proto:espnow n:108 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 5 | **LINK** peer:0x00000012 proto:espnow n:89 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:130 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 7 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-58 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-81 rssi_med:-46 rssi_max:-39
said: 9 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-60 rssi_med:-52 rssi_max:-45
```

---

@LAT105LON5840 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 2972970 ±21 frame:7500
seq: 1403
follows: 0x00000010:1458 0x00000012:1316 0x00000100:1052 0x00000200:2094 0x00000300:4742
said: 1 | **LINKWIN** t_ms:3294698 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 3 | **LINK** peer:0x00000300 proto:espnow n:184 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 4 | **LINK** peer:0x00000010 proto:espnow n:117 rssi_min:-42 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000012 proto:espnow n:91 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-59
said: 8 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-49 rssi_max:-44
```

---

@LAT105LON5841 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 2691441 ±21 frame:7500
seq: 1312
follows: 0x00000010:1453 0x00000011:1398 0x00000100:1048 0x00000200:2089 0x00000300:4732
said: 1 | **LINKWIN** t_ms:3013180 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-50 rssi_max:-43
said: 4 | **LINK** peer:0x00000010 proto:espnow n:115 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000011 proto:espnow n:95 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 6 | **LINK** peer:0x00000200 proto:espnow n:118 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 8 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 9 | **LINK** peer:0x00000300 proto:espnow n:195 rssi_min:-46 rssi_med:-45 rssi_max:-40
```

---

@LAT103LON2251 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 60001 ±0 frame:9500
seq: 2166
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1467 0x00000300:5103
said: 1 | **LINKWIN** t_ms:47860 stream:0x69cc95ce wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-40 rssi_med:-37 rssi_max:-33
```

---

@LAT103LON8322 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60040 ±0 frame:9500
seq: 2167
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1467 0x00000300:5103
said: 1 | **ENTWIN** t_ms:47860 stream:0x69cc95ce wall:0 window_ms:60040 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON2252 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 120001 ±0 frame:9500
seq: 2168
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1470 0x00000300:5103
said: 1 | **LINKWIN** t_ms:107861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-42 rssi_med:-39 rssi_max:-33
```

---

@LAT103LON2253 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 180001 ±0 frame:9500
seq: 2169
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1471 0x00000300:5103
said: 1 | **LINKWIN** t_ms:167861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-41 rssi_med:-39 rssi_max:-36
```

---

@LAT103LON2254 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 240001 ±0 frame:9500
seq: 2170
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1472 0x00000300:5103
said: 1 | **LINKWIN** t_ms:227861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-40 rssi_med:-39 rssi_max:-38
```

---

@LAT103LON2255 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 300030 ±0 frame:9500
seq: 2171
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1473 0x00000300:5103
said: 1 | **LINKWIN** t_ms:287890 stream:0x69cc95ce wall:0 window_ms:60029
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT103LON2256 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 360030 ±0 frame:9500
seq: 2172
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1474 0x00000300:5103
said: 1 | **LINKWIN** t_ms:347890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-40 rssi_med:-39 rssi_max:-39
```

---

@LAT103LON2257 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 420030 ±0 frame:9500
seq: 2173
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1475 0x00000300:5103
said: 1 | **LINKWIN** t_ms:407890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT103LON2258 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 480030 ±0 frame:9500
seq: 2174
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1476 0x00000300:5103
said: 1 | **LINKWIN** t_ms:467890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-40 rssi_med:-39 rssi_max:-38
```

---

@LAT103LON2259 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 540030 ±0 frame:9500
seq: 2175
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1477 0x00000300:5103
said: 1 | **LINKWIN** t_ms:527890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT103LON2260 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 600030 ±0 frame:9500
seq: 2176
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1478 0x00000300:5103
said: 1 | **LINKWIN** t_ms:587890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-39 rssi_med:-39 rssi_max:-39
```

---

@LAT103LON2261 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 660030 ±0 frame:9500
seq: 2177
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1479 0x00000300:5103
said: 1 | **LINKWIN** t_ms:647890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-43 rssi_med:-39 rssi_max:-38
```

---

@LAT103LON2262 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 720030 ±0 frame:9500
seq: 2178
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1480 0x00000300:5103
said: 1 | **LINKWIN** t_ms:707890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-41 rssi_med:-39 rssi_max:-37
```

---

@LAT105LON5842 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 180074 ±0 frame:12000
seq: 5102
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2165
said: 1 | **LINKWIN** t_ms:165098 stream:0x5d34e552 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:79 rssi_min:-34 rssi_med:-29 rssi_max:-26
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-44 rssi_max:-41
said: 4 | **LINK** peer:0x00000010 proto:espnow n:9 rssi_min:-28 rssi_med:-27 rssi_max:-25
said: 5 | **LINK** peer:0x00000010 proto:ble n:16 rssi_min:-44 rssi_med:-43 rssi_max:-41
said: 6 | **LINK** peer:0x00000100 proto:espnow n:17 rssi_min:-30 rssi_med:-25 rssi_max:-24
said: 7 | **LINK** peer:0x00000011 proto:espnow n:3 rssi_min:-24 rssi_med:-24 rssi_max:-24
said: 8 | **LINK** peer:0x00000011 proto:ble n:9 rssi_min:-44 rssi_med:-39 rssi_max:-38
said: 9 | **LINK** peer:0x00000012 proto:espnow n:5 rssi_min:-18 rssi_med:-16 rssi_max:-16
said: 10 | 0x00000200 ble met predicted:-45 observed:-44
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON2263 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 780080 ±21 frame:9500
seq: 2179
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1481 0x00000300:5107
said: 1 | **LINKWIN** t_ms:767945 stream:0x69cc95ce wall:0 window_ms:60055
said: 2 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-43 rssi_med:-39 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:130 rssi_min:-84 rssi_med:-46 rssi_max:-28
said: 4 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-62 rssi_max:-44
```

---

@LAT105LON5843 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 778538 ±0 frame:9500
seq: 5104
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1481 0x00000200:2178
said: 1 | **LINKWIN** t_ms:766400 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-65 rssi_med:-51 rssi_max:-25
said: 3 | **LINK** peer:0x00000200 proto:espnow n:85 rssi_min:-78 rssi_med:-54 rssi_max:-31
said: 4 | **LINK** peer:0x00000200 proto:ble n:47 rssi_min:-90 rssi_med:-64 rssi_max:-46
```

---

@LAT101LON0 | sid:2136c351 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:38 last_ms:794297
t_ms:784543 stream:0x69cc95ce wall:0

---

@LAT101LON1 | sid:27653a2f | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:4 half_life_ms:600000 reinforced:0 last_ms:6141
t_ms:784543 stream:0x69cc95ce wall:0

---

@LAT101LON2 | sid:42caf4db | created:0 | updated:0 |
**PEER** node:0x00000300 spoke:1 declared:0x3fb7 verified:0x2fb7 exercised:0x0015 cap_epoch:9
**TRACE** copresence:255 half_life_ms:600000 reinforced:26 last_ms:796206
t_ms:784543 stream:0x69cc95ce wall:0

---

@LAT101LON3 | sid:2665389c | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:4 half_life_ms:600000 reinforced:0 last_ms:6141
t_ms:784543 stream:0x69cc95ce wall:0

---

@LAT101LON4 | sid:29653d55 | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:4 half_life_ms:600000 reinforced:0 last_ms:6141
t_ms:784543 stream:0x69cc95ce wall:0

---

@LAT105LON5844 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 838538 ±0 frame:9500
seq: 5108
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2179
said: 1 | **LINKWIN** t_ms:826400 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-76 rssi_med:-66 rssi_max:-60
said: 3 | **LINK** peer:0x00000100 proto:espnow n:25 rssi_min:-54 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:espnow n:65 rssi_min:-66 rssi_med:-50 rssi_max:-47
said: 5 | 0x00000100 espnow met predicted:-51 observed:-49
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-54 observed:-50
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-64 observed:-66
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON2264 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 840079 ±21 frame:9500
seq: 2180
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5109
said: 1 | **LINKWIN** t_ms:827945 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:74 rssi_min:-61 rssi_med:-47 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:16 rssi_min:-48 rssi_med:-39 rssi_max:-38
said: 4 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-79 rssi_med:-62 rssi_max:-53
```

---

@LAT103LON2265 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 900077 ±21 frame:9500
seq: 2181
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:887945 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-71 rssi_med:-57 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-88 rssi_med:-69 rssi_max:-49
```

---

@LAT105LON5845 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 898538 ±0 frame:9500
seq: 5110
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **LINKWIN** t_ms:886400 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-74 rssi_med:-61 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-69 rssi_max:-51
said: 4 | 0x00000200 ble met predicted:-66 observed:-69
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000100 espnow unobserved predicted:-49 observed:-49
percept: 5 | 0x00000100 | link_stable | espnow | ? | -
said: 6 | 0x00000200 espnow violated predicted:-50 observed:-61
percept: 6 | 0x00000200 | link_stable | espnow | - | -
```
@LAT106LON186 | created:0 | updated:0

**BAR** frame:9500 bar:1 own:19 held:7 terms:2 digest:0x07234745 settled_ms:300000
**HOLDS** agent:0x00000200 n:19 lo:2129 hi:2176 sum:40960
**HOLDS** agent:0x00000300 n:7 lo:5035 hi:5051 sum:35305
**DELIVER** up_s:912 heap:11052 fetched:4 unanswered:29 broken:0 resumed:10 empty:17 served:59 wants:59 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:2 split:0

---

@LAT105LON5846 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3121590 ±21 frame:7500
seq: 1461
follows: 0x00000011:1405 0x00000012:1319 0x00000100:1056 0x00000200:2097 0x00000300:4748
said: 1 | **LINKWIN** t_ms:3443313 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:84 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000300 proto:espnow n:193 rssi_min:-46 rssi_med:-43 rssi_max:-42
said: 4 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-80 rssi_med:-58 rssi_max:-55
said: 5 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-77 rssi_med:-46 rssi_max:-39
said: 6 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 7 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-69 rssi_med:-58 rssi_max:-56
said: 8 | **LINK** peer:0x00000200 proto:espnow n:86 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 9 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-52 rssi_max:-46
```

---

@LAT105LON5847 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3181600 ±21 frame:7500
seq: 1462
follows: 0x00000011:1406 0x00000012:1320 0x00000100:1057 0x00000200:2098 0x00000300:4750
said: 1 | **LINKWIN** t_ms:3503323 stream:0xc9e0e898 wall:0 window_ms:60010
said: 2 | **LINK** peer:0x00000012 proto:espnow n:92 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-49 rssi_med:-46 rssi_max:-39
said: 4 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-58 rssi_med:-58 rssi_max:-57
said: 5 | **LINK** peer:0x00000300 proto:espnow n:182 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 6 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-60 rssi_med:-53 rssi_max:-46
said: 7 | **LINK** peer:0x00000200 proto:espnow n:119 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 8 | **LINK** peer:0x00000011 proto:espnow n:93 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 9 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-55 rssi_max:-52
```

---

@LAT105LON5848 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3241601 ±21 frame:7500
seq: 1463
follows: 0x00000011:1407 0x00000012:1320 0x00000100:1058 0x00000200:2099 0x00000300:4752
said: 1 | **LINKWIN** t_ms:3563322 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:136 rssi_min:-45 rssi_med:-43 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-58 rssi_max:-54
said: 4 | **LINK** peer:0x00000011 proto:espnow n:77 rssi_min:-42 rssi_med:-40 rssi_max:-36
said: 5 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-74 rssi_med:-55 rssi_max:-52
said: 6 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-50 rssi_med:-46 rssi_max:-38
said: 7 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-59 rssi_med:-58 rssi_max:-56
said: 8 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-60 rssi_med:-53 rssi_max:-46
said: 9 | **LINK** peer:0x00000012 proto:espnow n:62 rssi_min:-34 rssi_med:-31 rssi_max:-30
```

---

@LAT103LON2266 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 75414 ±21 frame:10500
seq: 2182
follows: 0x00000010:1490 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:61947 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:91 rssi_min:-54 rssi_med:-43 rssi_max:-36
said: 3 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-57 rssi_max:-49
```

---

@LAT103LON8323 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 75450 ±21 frame:10500
seq: 2183
follows: 0x00000010:1490 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **ENTWIN** t_ms:61947 stream:0xb16505e0 wall:0 window_ms:60036 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT105LON5849 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3301599 ±21 frame:7500
seq: 1464
follows: 0x00000011:1408 0x00000012:1323 0x00000100:1059 0x00000200:2100 0x00000300:4754
said: 1 | **LINKWIN** t_ms:3623323 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:150 rssi_min:-49 rssi_med:-49 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:espnow n:175 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 5 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-59 rssi_med:-58 rssi_max:-56
said: 6 | **LINK** peer:0x00000011 proto:espnow n:121 rssi_min:-42 rssi_med:-39 rssi_max:-36
said: 7 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-53 rssi_max:-46
said: 8 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-67 rssi_med:-58 rssi_max:-55
said: 9 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-77 rssi_med:-46 rssi_max:-39
```

---

@LAT105LON5850 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3361602 ±21 frame:7500
seq: 1465
follows: 0x00000011:1409 0x00000012:1323 0x00000100:1060 0x00000200:2101 0x00000300:4756
said: 1 | **LINKWIN** t_ms:3683323 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:68 rssi_min:-81 rssi_med:-46 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:espnow n:73 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:espnow n:192 rssi_min:-45 rssi_med:-44 rssi_max:-40
said: 5 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 6 | **LINK** peer:0x00000012 proto:espnow n:59 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000011 proto:espnow n:98 rssi_min:-42 rssi_med:-40 rssi_max:-36
said: 8 | **LINK** peer:0x00000300 proto:ble n:75 rssi_min:-59 rssi_med:-52 rssi_max:-46
said: 9 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-59 rssi_med:-55 rssi_max:-52
```

---

@LAT105LON5851 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3421602 ±21 frame:7500
seq: 1466
follows: 0x00000011:1410 0x00000012:1325 0x00000100:1061 0x00000200:2102 0x00000300:4758
said: 1 | **LINKWIN** t_ms:3743322 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-77 rssi_med:-52 rssi_max:-46
said: 3 | **LINK** peer:0x00000012 proto:espnow n:109 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 4 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 5 | **LINK** peer:0x00000300 proto:espnow n:154 rssi_min:-45 rssi_med:-43 rssi_max:-39
said: 6 | **LINK** peer:0x00000011 proto:espnow n:82 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 7 | **LINK** peer:0x00000200 proto:espnow n:109 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-50 rssi_med:-46 rssi_max:-39
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-66 rssi_med:-58 rssi_max:-55
```

---

@LAT105LON5852 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3481604 ±21 frame:7500
seq: 1467
follows: 0x00000011:1411 0x00000012:1326 0x00000100:1062 0x00000200:2103 0x00000300:4760
said: 1 | **LINKWIN** t_ms:3803322 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-74 rssi_med:-53 rssi_max:-46
said: 4 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-66 rssi_med:-58 rssi_max:-54
said: 5 | **LINK** peer:0x00000011 proto:espnow n:88 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 6 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-80 rssi_med:-46 rssi_max:-39
said: 7 | **LINK** peer:0x00000200 proto:espnow n:84 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 8 | **LINK** peer:0x00000300 proto:espnow n:177 rssi_min:-45 rssi_med:-43 rssi_max:-41
said: 9 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-82 rssi_med:-55 rssi_max:-52
```

---

@LAT105LON5853 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3541603 ±21 frame:7500
seq: 1468
follows: 0x00000011:1412 0x00000012:1327 0x00000100:1063 0x00000200:2104 0x00000300:4762
said: 1 | **LINKWIN** t_ms:3863322 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:159 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000300 proto:espnow n:171 rssi_min:-64 rssi_med:-43 rssi_max:-40
said: 4 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 5 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 6 | **LINK** peer:0x00000011 proto:espnow n:88 rssi_min:-41 rssi_med:-40 rssi_max:-37
said: 7 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-46 rssi_max:-39
said: 8 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-60 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-52 rssi_max:-46
```

---

@LAT105LON5854 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3601603 ±21 frame:7500
seq: 1469
follows: 0x00000011:1413 0x00000012:1328 0x00000100:1064 0x00000200:2105 0x00000300:4764
said: 1 | **LINKWIN** t_ms:3923323 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:168 rssi_min:-70 rssi_med:-43 rssi_max:-40
said: 3 | **LINK** peer:0x00000200 proto:espnow n:112 rssi_min:-49 rssi_med:-49 rssi_max:-46
said: 4 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-59 rssi_med:-58 rssi_max:-56
said: 5 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-52 rssi_max:-46
said: 6 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-58 rssi_max:-54
said: 7 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-49 rssi_med:-46 rssi_max:-39
said: 8 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-59 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:espnow n:108 rssi_min:-35 rssi_med:-31 rssi_max:-28
```

---

@LAT105LON5855 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3661555 ±21 frame:7500
seq: 1470
follows: 0x00000011:1414 0x00000012:1329 0x00000100:1066 0x00000200:2106 0x00000300:4766
said: 1 | **LINKWIN** t_ms:3983322 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-58 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:63 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:espnow n:126 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 5 | **LINK** peer:0x00000012 proto:espnow n:77 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:116 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 7 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-49 rssi_med:-46 rssi_max:-39
said: 8 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-80 rssi_med:-52 rssi_max:-45
said: 9 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-58 rssi_max:-54
```

---

@LAT103LON2267 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 135433 ±21 frame:10500
seq: 2184
follows: 0x00000010:1491 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:121966 stream:0xb16505e0 wall:0 window_ms:60019
said: 2 | **LINK** peer:0x00000010 proto:espnow n:161 rssi_min:-56 rssi_med:-46 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-62 rssi_max:-55
```

---

@LAT105LON5856 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3721605 ±21 frame:7500
seq: 1471
follows: 0x00000011:1415 0x00000012:1330 0x00000100:1068 0x00000200:2107 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4043323 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:108 rssi_min:-35 rssi_med:-31 rssi_max:-28
said: 3 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 4 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-52 rssi_max:-46
said: 5 | **LINK** peer:0x00000011 proto:espnow n:119 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 6 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000300 proto:espnow n:134 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 8 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-46 rssi_max:-39
said: 9 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-59 rssi_med:-58 rssi_max:-57
```

---

@LAT105LON5857 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3781605 ±21 frame:7500
seq: 1472
follows: 0x00000011:1416 0x00000012:1331 0x00000100:1069 0x00000200:2108 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4103322 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-79 rssi_med:-46 rssi_max:-39
said: 3 | **LINK** peer:0x00000012 proto:espnow n:105 rssi_min:-35 rssi_med:-31 rssi_max:-31
said: 4 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-77 rssi_med:-52 rssi_max:-46
said: 5 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-59 rssi_med:-57 rssi_max:-57
said: 6 | **LINK** peer:0x00000200 proto:espnow n:110 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000300 proto:espnow n:130 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 8 | **LINK** peer:0x00000011 proto:espnow n:141 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 9 | **LINK** peer:0x00000011 proto:ble n:71 rssi_min:-73 rssi_med:-55 rssi_max:-52
```

---

@LAT105LON5858 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3841629 ±21 frame:7500
seq: 1473
follows: 0x00000011:1417 0x00000012:1331 0x00000100:1070 0x00000200:2109 0x00000300:4773
said: 1 | **LINKWIN** t_ms:4163344 stream:0xc9e0e898 wall:0 window_ms:60022
said: 2 | **LINK** peer:0x00000200 proto:espnow n:151 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:180 rssi_min:-45 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-59 rssi_med:-58 rssi_max:-56
said: 5 | **LINK** peer:0x00000012 proto:espnow n:51 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 7 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-59 rssi_max:-55
said: 8 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-77 rssi_med:-55 rssi_max:-51
said: 9 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-60 rssi_med:-53 rssi_max:-46
```

---

@LAT103LON2268 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 195434 ±21 frame:10500
seq: 2185
follows: 0x00000010:1492 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:181966 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-69 rssi_med:-48 rssi_max:-37
said: 3 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-75 rssi_med:-62 rssi_max:-55
```

---

@LAT105LON5859 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3901629 ±21 frame:7500
seq: 1474
follows: 0x00000011:1418 0x00000012:1333 0x00000100:1071 0x00000200:2110 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4223344 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-58 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000300 proto:espnow n:234 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 4 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-46 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-49 rssi_med:-49 rssi_max:-46
said: 6 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 7 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-70 rssi_med:-56 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-66 rssi_med:-58 rssi_max:-55
said: 9 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-77 rssi_med:-53 rssi_max:-46
```

---

@LAT105LON5860 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3961630 ±21 frame:7500
seq: 1475
follows: 0x00000011:1419 0x00000012:1334 0x00000100:1072 0x00000200:2111 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4283345 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-68 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:104 rssi_min:-59 rssi_med:-50 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:76 rssi_min:-42 rssi_med:-38 rssi_max:-33
said: 5 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-83 rssi_med:-46 rssi_max:-38
said: 6 | **LINK** peer:0x00000300 proto:espnow n:138 rssi_min:-51 rssi_med:-44 rssi_max:-40
said: 7 | **LINK** peer:0x00000011 proto:ble n:71 rssi_min:-79 rssi_med:-53 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:espnow n:60 rssi_min:-34 rssi_med:-31 rssi_max:-29
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-52 rssi_max:-46
```

---

@LAT103LON2269 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 255445 ±21 frame:10500
seq: 2186
follows: 0x00000010:1493 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:241977 stream:0xb16505e0 wall:0 window_ms:60011
said: 2 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-60 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-62 rssi_max:-54
```

---

@LAT105LON5861 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4021560 ±21 frame:7500
seq: 1476
follows: 0x00000011:1420 0x00000012:1335 0x00000100:1073 0x00000200:2112 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4343344 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-71 rssi_med:-53 rssi_max:-47
said: 3 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-50 rssi_med:-39 rssi_max:-31
said: 4 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-65 rssi_med:-51 rssi_max:-44
said: 5 | **LINK** peer:0x00000300 proto:espnow n:135 rssi_min:-56 rssi_med:-49 rssi_max:-35
said: 6 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-51 rssi_med:-49 rssi_max:-41
said: 7 | **LINK** peer:0x00000012 proto:espnow n:170 rssi_min:-51 rssi_med:-43 rssi_max:-29
said: 8 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-77 rssi_med:-59 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-51 rssi_max:-38
```

---

@LAT105LON5862 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4081629 ±21 frame:7500
seq: 1477
follows: 0x00000011:1421 0x00000012:1336 0x00000100:1074 0x00000200:2112 0x00000300:4781
said: 1 | **LINKWIN** t_ms:4403344 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:83 rssi_min:-41 rssi_med:-36 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:espnow n:187 rssi_min:-57 rssi_med:-49 rssi_max:-41
said: 4 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-64 rssi_med:-60 rssi_max:-44
said: 5 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-79 rssi_med:-55 rssi_max:-49
said: 6 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-76 rssi_med:-56 rssi_max:-51
said: 7 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-79 rssi_med:-54 rssi_max:-49
said: 8 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-65 rssi_med:-42 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:ble n:33 rssi_min:-60 rssi_med:-57 rssi_max:-54
```

---

@LAT105LON5863 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4141632 ±21 frame:7500
seq: 1478
follows: 0x00000011:1422 0x00000012:1337 0x00000100:1075 0x00000200:2114 0x00000300:4783
said: 1 | **LINKWIN** t_ms:4463345 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:75 rssi_min:-63 rssi_med:-56 rssi_max:-45
said: 3 | **LINK** peer:0x00000012 proto:espnow n:97 rssi_min:-58 rssi_med:-42 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:espnow n:155 rssi_min:-67 rssi_med:-51 rssi_max:-36
said: 5 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-77 rssi_med:-59 rssi_max:-52
said: 6 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-65 rssi_med:-54 rssi_max:-50
said: 7 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-79 rssi_med:-54 rssi_max:-43
said: 8 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-76 rssi_med:-54 rssi_max:-47
said: 9 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-43 rssi_med:-36 rssi_max:-27
```

---

@LAT105LON5864 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4228400 ±21 frame:7500
seq: 1479
follows: 0x00000011:1424 0x00000012:1338 0x00000100:1076 0x00000200:2116 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4550125 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-56 rssi_med:-51 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:96 rssi_min:-54 rssi_med:-43 rssi_max:-27
said: 4 | **LINK** peer:0x00000012 proto:espnow n:73 rssi_min:-50 rssi_med:-44 rssi_max:-35
said: 5 | **LINK** peer:0x00000200 proto:ble n:49 rssi_min:-70 rssi_med:-55 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-65 rssi_med:-54 rssi_max:-38
said: 7 | **LINK** peer:0x00000012 proto:ble n:45 rssi_min:-78 rssi_med:-58 rssi_max:-44
said: 8 | **LINK** peer:0x00000011 proto:ble n:37 rssi_min:-79 rssi_med:-35 rssi_max:-29
said: 9 | **LINK** peer:0x00000011 proto:espnow n:11 rssi_min:-22 rssi_med:-22 rssi_max:-21
```

---

@LAT105LON5865 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4288400 ±24 frame:7500
seq: 1481
follows: 0x00000011:1426 0x00000012:1339 0x00000100:1078 0x00000200:2117 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4610125 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:99 rssi_min:-57 rssi_med:-48 rssi_max:-44
said: 3 | **LINK** peer:0x00000300 proto:ble n:35 rssi_min:-81 rssi_med:-44 rssi_max:-38
said: 4 | **LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-54 rssi_med:-47 rssi_max:-41
said: 5 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-58 rssi_med:-31 rssi_max:-25
said: 6 | **LINK** peer:0x00000012 proto:espnow n:75 rssi_min:-55 rssi_med:-43 rssi_max:-35
said: 7 | **LINK** peer:0x00000011 proto:espnow n:134 rssi_min:-23 rssi_med:-21 rssi_max:-20
said: 8 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-70 rssi_med:-59 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-38 rssi_med:-34 rssi_max:-29
```

---

@LAT103LON2270 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 315446 ±21 frame:10500
seq: 2187
follows: 0x00000010:1494 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:301978 stream:0xb16505e0 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000010 proto:espnow n:107 rssi_min:-48 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-70 rssi_med:-58 rssi_max:-56
```

---

@LAT105LON5866 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4348395 ±21 frame:7500
seq: 1482
follows: 0x00000011:1427 0x00000012:1340 0x00000100:1078 0x00000200:2118 0x00000300:4789
said: 1 | **LINKWIN** t_ms:4670125 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:170 rssi_min:-54 rssi_med:-43 rssi_max:-40
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-62 rssi_max:-54
said: 4 | **LINK** peer:0x00000200 proto:espnow n:158 rssi_min:-63 rssi_med:-52 rssi_max:-46
said: 5 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-34 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:126 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 7 | **LINK** peer:0x00000300 proto:espnow n:176 rssi_min:-39 rssi_med:-31 rssi_max:-29
said: 8 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-77 rssi_med:-60 rssi_max:-46
said: 9 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-79 rssi_med:-45 rssi_max:-42
```

---

@LAT105LON5867 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4408386 ±21 frame:7500
seq: 1483
follows: 0x00000011:1428 0x00000012:1341 0x00000100:1081 0x00000200:2119 0x00000300:4791
said: 1 | **LINKWIN** t_ms:4730125 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-58 rssi_med:-46 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-80 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-34 rssi_max:-30
said: 5 | **LINK** peer:0x00000200 proto:espnow n:84 rssi_min:-54 rssi_med:-46 rssi_max:-43
said: 6 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-58 rssi_med:-41 rssi_max:-35
said: 7 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-64 rssi_med:-47 rssi_max:-39
said: 8 | **LINK** peer:0x00000300 proto:espnow n:86 rssi_min:-39 rssi_med:-31 rssi_max:-28
said: 9 | **LINK** peer:0x00000011 proto:espnow n:108 rssi_min:-21 rssi_med:-21 rssi_max:-20
```

---

@LAT103LON2271 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 375447 ±21 frame:10500
seq: 2188
follows: 0x00000010:1495 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:361978 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:71 rssi_min:-48 rssi_med:-45 rssi_max:-42
said: 3 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-71 rssi_med:-61 rssi_max:-57
```

---

@LAT104LON257 | created:0 | updated:0

**carried through @LAT103LON2231**

```ttdb-carried
through: 2231
through: 8281
```

---

@LAT105LON5868 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4468395 ±21 frame:7500
seq: 1484
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1082 0x00000200:2120 0x00000300:4793
said: 1 | **LINKWIN** t_ms:4790126 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-43 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:espnow n:97 rssi_min:-58 rssi_med:-46 rssi_max:-45
said: 4 | **LINK** peer:0x00000300 proto:espnow n:129 rssi_min:-50 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000012 proto:espnow n:109 rssi_min:-65 rssi_med:-50 rssi_max:-39
said: 6 | **LINK** peer:0x00000300 proto:ble n:71 rssi_min:-81 rssi_med:-46 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:espnow n:81 rssi_min:-21 rssi_med:-21 rssi_max:-20
said: 8 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-39 rssi_med:-33 rssi_max:-30
said: 9 | **LINK** peer:0x00000200 proto:ble n:47 rssi_min:-77 rssi_med:-58 rssi_max:-55
```

---

@LAT105LON5869 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 273054 ±21 frame:10500
seq: 1486
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2161 0x00000300:5091
said: 1 | **LINKWIN** t_ms:259691 stream:0x3bead35c wall:0 window_ms:60072
said: 2 | **LINK** peer:0x00000300 proto:espnow n:81 rssi_min:-52 rssi_med:-23 rssi_max:-20
said: 3 | **LINK** peer:0x00000200 proto:espnow n:130 rssi_min:-29 rssi_med:-26 rssi_max:-23
said: 4 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-72 rssi_med:-39 rssi_max:-35
said: 5 | **LINK** peer:0x00000200 proto:ble n:49 rssi_min:-44 rssi_med:-40 rssi_max:-37
said: 6 | **LINK** peer:0x00000011 proto:espnow n:116 rssi_min:-21 rssi_med:-20 rssi_max:-18
said: 7 | **LINK** peer:0x00000011 proto:ble n:43 rssi_min:-81 rssi_med:-34 rssi_max:-30
said: 8 | **LINK** peer:0x00000012 proto:espnow n:62 rssi_min:-33 rssi_med:-30 rssi_max:-28
said: 9 | **LINK** peer:0x00000012 proto:ble n:40 rssi_min:-79 rssi_med:-47 rssi_max:-40
```

---

@LAT105LON5870 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 218456 ±21 frame:12000
seq: 1487
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1359 0x00000200:2165 0x00000300:5103
said: 1 | **LINKWIN** t_ms:203503 stream:0x5d34e552 wall:0 window_ms:60016
said: 2 | **LINK** peer:0x00000300 proto:espnow n:136 rssi_min:-21 rssi_med:-18 rssi_max:-16
said: 3 | **LINK** peer:0x00000200 proto:espnow n:133 rssi_min:-38 rssi_med:-32 rssi_max:-30
said: 4 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-35 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-80 rssi_med:-45 rssi_max:-43
said: 6 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-30 rssi_med:-25 rssi_max:-22
said: 7 | **LINK** peer:0x00000011 proto:ble n:48 rssi_min:-79 rssi_med:-38 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:espnow n:43 rssi_min:-39 rssi_med:-26 rssi_max:-23
said: 9 | **LINK** peer:0x00000012 proto:ble n:48 rssi_min:-77 rssi_med:-41 rssi_max:-35
```

---

@LAT105LON5871 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 60002 ±0 frame:10500
seq: 1489
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2181 0x00000300:5113
said: 1 | **LINKWIN** t_ms:46532 stream:0xb16505e0 wall:0 window_ms:60002
said: 2 | **LINK** peer:0x00000200 proto:espnow n:55 rssi_min:-51 rssi_med:-41 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:ble n:33 rssi_min:-63 rssi_med:-55 rssi_max:-49
```

---

@LAT105LON5872 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 120002 ±0 frame:10500
seq: 1491
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2183 0x00000300:5113
said: 1 | **LINKWIN** t_ms:106535 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-78 rssi_med:-60 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:130 rssi_min:-61 rssi_med:-46 rssi_max:-35
```

---

@LAT105LON5873 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 180002 ±0 frame:10500
seq: 1492
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2184 0x00000300:5113
said: 1 | **LINKWIN** t_ms:166535 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:124 rssi_min:-65 rssi_med:-49 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-81 rssi_med:-61 rssi_max:-49
```

---

@LAT105LON5874 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 240002 ±0 frame:10500
seq: 1493
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2185 0x00000300:5113
said: 1 | **LINKWIN** t_ms:226534 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:109 rssi_min:-61 rssi_med:-48 rssi_max:-40
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-90 rssi_med:-63 rssi_max:-53
```

---

@LAT105LON5875 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 300002 ±0 frame:10500
seq: 1494
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2186 0x00000300:5113
said: 1 | **LINKWIN** t_ms:286535 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-60 rssi_max:-54
said: 3 | **LINK** peer:0x00000200 proto:espnow n:88 rssi_min:-54 rssi_med:-47 rssi_max:-44
```

---

@LAT105LON5876 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 360002 ±0 frame:10500
seq: 1495
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2187 0x00000300:5113
said: 1 | **LINKWIN** t_ms:346534 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-72 rssi_med:-59 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:espnow n:76 rssi_min:-51 rssi_med:-47 rssi_max:-44
```

---

@LAT105LON5877 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 420002 ±0 frame:10500
seq: 1496
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2188 0x00000300:5113
said: 1 | **LINKWIN** t_ms:406535 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:74 rssi_min:-72 rssi_med:-60 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:96 rssi_min:-51 rssi_med:-48 rssi_max:-47
```

---

@LAT103LON2272 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 435448 ±21 frame:10500
seq: 2189
follows: 0x00000010:1496 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:421977 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:115 rssi_min:-48 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-71 rssi_med:-60 rssi_max:-57
```

---

@LAT105LON5878 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 480002 ±0 frame:10500
seq: 1497
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2189 0x00000300:5113
said: 1 | **LINKWIN** t_ms:466534 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-60 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:espnow n:57 rssi_min:-53 rssi_med:-49 rssi_max:-45
```

---

@LAT103LON2273 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 495447 ±21 frame:10500
seq: 2190
follows: 0x00000010:1497 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:481978 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:57 rssi_min:-49 rssi_med:-45 rssi_max:-43
said: 3 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-73 rssi_med:-60 rssi_max:-57
```

---

@LAT105LON5879 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 540002 ±0 frame:10500
seq: 1498
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2190 0x00000300:5113
said: 1 | **LINKWIN** t_ms:526534 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:52 rssi_min:-56 rssi_med:-49 rssi_max:-46
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-75 rssi_med:-61 rssi_max:-56
```

---

@LAT103LON2274 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 555448 ±21 frame:10500
seq: 2191
follows: 0x00000010:1498 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:541978 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-60 rssi_max:-59
said: 3 | **LINK** peer:0x00000010 proto:espnow n:61 rssi_min:-47 rssi_med:-46 rssi_max:-45
```
