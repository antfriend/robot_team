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

@LAT103LON8264 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 30835645 ±21 frame:7000
seq: 977
follows: 0x00000010:346 0x00000011:278 0x00000012:196 0x00000100:543 0x00000300:2574
said: 1 | **ENTWIN** t_ms:30950944 stream:0x3c4214c9 wall:0 window_ms:600027 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON8265 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 33237499 ±21 frame:7000
seq: 1018
follows: 0x00000010:390 0x00000011:320 0x00000012:239 0x00000100:586 0x00000300:2656
said: 1 | **ENTWIN** t_ms:33352809 stream:0x3c4214c9 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,64677217947d,e6b32d2cea8b,bc102f237ace,7236bc441422,0283cce0e689
said: 12 | **COVERED** windows:3 entities:9 window_ms:1801814 first_t_ms:31552780 last_t_ms:32752810 covered_by:@LAT103LON8264
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-44 windows:3
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-81 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-81 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:3 rssi:-87 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-89 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-85 windows:3
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:3 rssi:-93 windows:3
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:2 rssi:-94 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
```

---

@LAT103LON8266 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 35037531 ±21 frame:7000
seq: 1049
follows: 0x00000010:421 0x00000011:351 0x00000012:271 0x00000100:619 0x00000300:2718
said: 1 | **ENTWIN** t_ms:35152861 stream:0x3c4214c9 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
said: 11 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,64677217947d,bc102f237ace,e6b32d2cea8b,0283cce0e689,7236bc441422,84a329c78fec
said: 13 | **COVERED** windows:2 entities:9 window_ms:1200001 first_t_ms:33952808 last_t_ms:34552861 covered_by:@LAT103LON8265
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-47 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-80 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-86 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-90 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94 windows:1
```

---

@LAT103LON8267 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 38037640 ±21 frame:7000
seq: 1100
follows: 0x00000010:473 0x00000011:403 0x00000012:324 0x00000100:674 0x00000300:2824
said: 1 | **ENTWIN** t_ms:38152972 stream:0x3c4214c9 wall:0 window_ms:600046 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,64677217947d,bc102f237ace,e6b32d2cea8b,0283cce0e689,84a329c78fec
said: 11 | **COVERED** windows:4 entities:9 window_ms:2400014 first_t_ms:35752872 last_t_ms:37552926 covered_by:@LAT103LON8266
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-50 windows:4
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-78 windows:4
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-80 windows:4
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:3 rssi:-82 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-90 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-89 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:2 rssi:-93 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-91 windows:4
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:3 rssi:-92 windows:3
```

---

@LAT103LON8268 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 39837673 ±21 frame:7000
seq: 1131
follows: 0x00000010:504 0x00000011:435 0x00000012:354 0x00000100:705 0x00000300:2887
said: 1 | **ENTWIN** t_ms:39952973 stream:0x3c4214c9 wall:0 window_ms:600002 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689
said: 11 | **COVERED** windows:2 entities:8 window_ms:1199999 first_t_ms:38752971 last_t_ms:39352971 covered_by:@LAT103LON8267
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-49 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-75 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-80 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-86 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-90 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-90 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-93 windows:2
```

---

@LAT103LON8269 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 520774 ±22 frame:20500
seq: 1158
follows: 0x00000010:538 0x00000011:466 0x00000012:383 0x00000100:732 0x00000300:2943
said: 1 | **ENTWIN** t_ms:502561 stream:0xa0be1a79 wall:0 window_ms:62046 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-95
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-99
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8270 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1715298 ±21 frame:20500
seq: 1178
follows: 0x00000010:559 0x00000011:488 0x00000012:404 0x00000100:732 0x00000300:2981
said: 1 | **ENTWIN** t_ms:1699119 stream:0xa0be1a79 wall:0 window_ms:600034 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-88
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec
said: 11 | **COVERED** windows:1 entities:7 window_ms:594478 first_t_ms:1099085 last_t_ms:1099085 covered_by:@LAT103LON8269
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-91 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95 windows:1
```

---

@LAT103LON8271 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3515382 ±21 frame:20500
seq: 1209
follows: 0x00000010:591 0x00000011:521 0x00000012:435 0x00000100:732 0x00000300:3044
said: 1 | **ENTWIN** t_ms:3499175 stream:0xa0be1a79 wall:0 window_ms:600055 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-51
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 8 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,64677217947d,e6b32d2cea8b
said: 10 | **COVERED** windows:2 entities:8 window_ms:1200000 first_t_ms:2299119 last_t_ms:2899120 covered_by:@LAT103LON8270
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-46 windows:2
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-81 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-83 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-89 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-92 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-93 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-96 windows:1
```

---

@LAT103LON8272 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4116567 ±21 frame:20500
seq: 1220
follows: 0x00000010:602 0x00000011:532 0x00000012:445 0x00000100:732 0x00000300:3064
said: 1 | **ENTWIN** t_ms:4100349 stream:0xa0be1a79 wall:0 window_ms:601175 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-51
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,5ce28c488e0c,e6b32d2cea8b,64677217947d
```

---

@LAT103LON8273 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5916619 ±21 frame:20500
seq: 1251
follows: 0x00000010:632 0x00000011:562 0x00000012:476 0x00000100:732 0x00000300:3125
said: 1 | **ENTWIN** t_ms:5900424 stream:0xa0be1a79 wall:0 window_ms:599999 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-95
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
said: 8 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,64677217947d
said: 10 | **COVERED** windows:2 entities:7 window_ms:1200024 first_t_ms:4700399 last_t_ms:5300424 covered_by:@LAT103LON8272
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-50 windows:2
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-82 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-84 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-81 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-91 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-92 windows:2
```

---

@LAT103LON8274 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6517675 ±21 frame:20500
seq: 1262
follows: 0x00000010:643 0x00000011:573 0x00000012:486 0x00000100:732 0x00000300:3147
said: 1 | **ENTWIN** t_ms:6501472 stream:0xa0be1a79 wall:0 window_ms:601049 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,5ce28c488e0c,e6b32d2cea8b
```

---

@LAT103LON8275 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7717718 ±21 frame:20500
seq: 1283
follows: 0x00000010:663 0x00000011:595 0x00000012:508 0x00000100:732 0x00000300:3187
said: 1 | **ENTWIN** t_ms:7701546 stream:0xa0be1a79 wall:0 window_ms:600024 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-97
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,5ce28c488e0c
said: 11 | **COVERED** windows:1 entities:6 window_ms:599999 first_t_ms:7101471 last_t_ms:7101471 covered_by:@LAT103LON8274
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94 windows:1
```

---

@LAT103LON8276 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9517749 ±21 frame:20500
seq: 1314
follows: 0x00000010:693 0x00000011:628 0x00000012:539 0x00000100:732 0x00000300:3248
said: 1 | **ENTWIN** t_ms:9501549 stream:0xa0be1a79 wall:0 window_ms:600001 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,84a329c78fec,5ce28c488e0c
said: 11 | **COVERED** windows:2 entities:7 window_ms:1200001 first_t_ms:8301545 last_t_ms:8901547 covered_by:@LAT103LON8275
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-49 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-79 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-80 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-83 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-91 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-92 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95 windows:1
```

---

@LAT103LON8277 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10717767 ±21 frame:20500
seq: 1335
follows: 0x00000010:714 0x00000011:648 0x00000012:560 0x00000100:732 0x00000300:3290
said: 1 | **ENTWIN** t_ms:10701597 stream:0xa0be1a79 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,64677217947d,e6b32d2cea8b,5ce28c488e0c
said: 11 | **COVERED** windows:1 entities:7 window_ms:599998 first_t_ms:10101546 last_t_ms:10101546 covered_by:@LAT103LON8276
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-86 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94 windows:1
```

---

@LAT103LON8278 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 14317830 ±21 frame:20500
seq: 1396
follows: 0x00000010:778 0x00000011:711 0x00000012:621 0x00000100:732 0x00000300:3416
said: 1 | **ENTWIN** t_ms:14301654 stream:0xa0be1a79 wall:0 window_ms:600006 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-94
said: 8 | **RUN** windows_since_last:6 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,bc102f237ace
said: 10 | **COVERED** windows:5 entities:9 window_ms:3000000 first_t_ms:11301596 last_t_ms:13701597 covered_by:@LAT103LON8277
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-47 windows:5
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-77 windows:5
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-85 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-80 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-89 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:3 rssi:-93 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-93 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94 windows:1
```

---

@LAT103LON8279 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 17917979 ±21 frame:20500
seq: 1457
follows: 0x00000010:840 0x00000011:776 0x00000012:683 0x00000100:732 0x00000300:3539
said: 1 | **ENTWIN** t_ms:17901796 stream:0xa0be1a79 wall:0 window_ms:599966 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
said: 10 | **RUN** windows_since_last:6 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,5ce28c488e0c,e6b32d2cea8b
said: 12 | **COVERED** windows:5 entities:11 window_ms:3000124 first_t_ms:14901652 last_t_ms:17301829 covered_by:@LAT103LON8278
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-45 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-89 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-76 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-89 windows:5
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-82 windows:5
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-92 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:5 rssi:-89 windows:5
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-92 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-97 windows:1
```

---

@LAT103LON8280 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 19118031 ±21 frame:20500
seq: 1478
follows: 0x00000010:860 0x00000011:795 0x00000012:703 0x00000100:732 0x00000300:3582
said: 1 | **ENTWIN** t_ms:19101829 stream:0xa0be1a79 wall:0 window_ms:600008 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,bc102f237ace,e6b32d2cea8b
said: 10 | **COVERED** windows:1 entities:6 window_ms:600026 first_t_ms:18501821 last_t_ms:18501821 covered_by:@LAT103LON8279
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-94 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95 windows:1
```

---

@LAT103LON8281 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 22718090 ±21 frame:20500
seq: 1539
follows: 0x00000010:922 0x00000011:859 0x00000012:766 0x00000100:732 0x00000300:3708
said: 1 | **ENTWIN** t_ms:22701880 stream:0xa0be1a79 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-52
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 10 | **RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,e6b32d2cea8b,bc102f237ace
said: 12 | **COVERED** windows:5 entities:10 window_ms:3000000 first_t_ms:19701829 last_t_ms:22101880 covered_by:@LAT103LON8280
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-46 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-76 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-79 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-87 windows:5
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-90 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-89 windows:5
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-94 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-92 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92 windows:1
```

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

@LAT106LON167 | created:0 | updated:0

**BAR** frame:8000 bar:8 own:10 held:40 terms:9 digest:0x6cf5f785 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1268 hi:1278 sum:12734
**HOLDS** agent:0x00000011 n:10 lo:1214 hi:1223 sum:12185
**HOLDS** agent:0x00000012 n:10 lo:1118 hi:1128 sum:11234
**HOLDS** agent:0x00000200 n:10 lo:1913 hi:1922 sum:19175
**HOLDS** agent:0x00000300 n:10 lo:4377 hi:4395 sum:43860
**DELIVER** up_s:5113 heap:8528 fetched:337 unanswered:251 broken:58 resumed:1023 empty:162 served:1533 wants:1550 early:40 wantq_drop:2 superseded:2

---

@LAT106LON168 | created:0 | updated:0

**BAR** frame:8000 bar:9 own:10 held:40 terms:9 digest:0x30d90ae0 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1279 hi:1289 sum:12844
**HOLDS** agent:0x00000011 n:10 lo:1224 hi:1233 sum:12285
**HOLDS** agent:0x00000012 n:10 lo:1129 hi:1139 sum:11344
**HOLDS** agent:0x00000200 n:10 lo:1924 hi:1933 sum:19285
**HOLDS** agent:0x00000300 n:10 lo:4397 hi:4416 sum:44069
**DELIVER** up_s:5718 heap:9456 fetched:376 unanswered:276 broken:70 resumed:1165 empty:180 served:1677 wants:1694 early:40 wantq_drop:2 superseded:2

---

@LAT106LON169 | created:0 | updated:0

**BAR** frame:8000 bar:10 own:10 held:40 terms:9 digest:0x40588064 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1290 hi:1300 sum:12954
**HOLDS** agent:0x00000011 n:10 lo:1234 hi:1244 sum:12394
**HOLDS** agent:0x00000012 n:10 lo:1140 hi:1150 sum:11454
**HOLDS** agent:0x00000200 n:10 lo:1934 hi:1943 sum:19385
**HOLDS** agent:0x00000300 n:10 lo:4418 hi:4437 sum:44278
**DELIVER** up_s:6317 heap:5972 fetched:416 unanswered:301 broken:80 resumed:1295 empty:195 served:1829 wants:1847 early:40 wantq_drop:2 superseded:2

---

@LAT106LON170 | created:0 | updated:0

**BAR** frame:8000 bar:11 own:10 held:40 terms:9 digest:0xa1cf7219 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1301 hi:1311 sum:13064
**HOLDS** agent:0x00000011 n:10 lo:1245 hi:1255 sum:12504
**HOLDS** agent:0x00000012 n:10 lo:1151 hi:1161 sum:11564
**HOLDS** agent:0x00000200 n:10 lo:1944 hi:1953 sum:19485
**HOLDS** agent:0x00000300 n:10 lo:4439 hi:4457 sum:44480
**DELIVER** up_s:6912 heap:9352 fetched:456 unanswered:323 broken:83 resumed:1398 empty:216 served:1944 wants:1963 early:40 wantq_drop:3 superseded:5

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

@LAT103LON2169 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1549703 ±21 frame:7500
seq: 2071
follows: 0x00000010:1433 0x00000011:1378 0x00000012:1294 0x00000100:1026 0x00000300:4694
said: 1 | **LINKWIN** t_ms:1871426 stream:0xc9e0e898 wall:0 window_ms:60002
said: 2 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-45 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000010 proto:espnow n:118 rssi_min:-58 rssi_med:-48 rssi_max:-45
said: 4 | **LINK** peer:0x00000012 proto:espnow n:79 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 5 | **LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-37 rssi_med:-36 rssi_max:-35
said: 6 | **LINK** peer:0x00000011 proto:espnow n:94 rssi_min:-50 rssi_med:-46 rssi_max:-45
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-79 rssi_med:-63 rssi_max:-54
said: 8 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-79 rssi_med:-58 rssi_max:-50
said: 9 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-55 rssi_med:-50 rssi_max:-49
```

---

@LAT103LON2170 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1609704 ±21 frame:7500
seq: 2072
follows: 0x00000010:1434 0x00000011:1379 0x00000012:1295 0x00000100:1027 0x00000300:4696
said: 1 | **LINKWIN** t_ms:1931426 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-71 rssi_med:-58 rssi_max:-50
said: 3 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-37 rssi_med:-36 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:espnow n:153 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 5 | **LINK** peer:0x00000011 proto:espnow n:101 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 6 | **LINK** peer:0x00000012 proto:espnow n:107 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 8 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-63 rssi_med:-63 rssi_max:-61
said: 9 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-80 rssi_med:-63 rssi_max:-54
```

---

@LAT103LON2171 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1669705 ±21 frame:7500
seq: 2073
follows: 0x00000010:1435 0x00000011:1380 0x00000012:1296 0x00000100:1028 0x00000300:4698
said: 1 | **LINKWIN** t_ms:1991426 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:95 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 3 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-37 rssi_med:-36 rssi_max:-35
said: 4 | **LINK** peer:0x00000010 proto:espnow n:141 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000300 proto:espnow n:160 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000300 proto:ble n:71 rssi_min:-60 rssi_med:-58 rssi_max:-50
said: 7 | **LINK** peer:0x00000011 proto:espnow n:84 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 8 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 9 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-69 rssi_med:-63 rssi_max:-54
```

---

@LAT103LON2172 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1729703 ±21 frame:7500
seq: 2074
follows: 0x00000010:1436 0x00000011:1381 0x00000012:1296 0x00000100:1029 0x00000300:4700
said: 1 | **LINKWIN** t_ms:2051426 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-37 rssi_med:-36 rssi_max:-35
said: 3 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 4 | **LINK** peer:0x00000012 proto:ble n:45 rssi_min:-79 rssi_med:-50 rssi_max:-48
said: 5 | **LINK** peer:0x00000300 proto:espnow n:192 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 6 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-79 rssi_med:-57 rssi_max:-50
said: 8 | **LINK** peer:0x00000011 proto:espnow n:148 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-73 rssi_med:-63 rssi_max:-62
```

---

@LAT103LON2173 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1789707 ±21 frame:7500
seq: 2075
follows: 0x00000010:1437 0x00000011:1382 0x00000012:1298 0x00000100:1030 0x00000300:4702
said: 1 | **LINKWIN** t_ms:2111426 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-79 rssi_med:-63 rssi_max:-54
said: 3 | **LINK** peer:0x00000012 proto:espnow n:102 rssi_min:-33 rssi_med:-33 rssi_max:-32
said: 4 | **LINK** peer:0x00000300 proto:espnow n:107 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 5 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-79 rssi_med:-57 rssi_max:-50
said: 6 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-63 rssi_max:-62
said: 7 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000010 proto:espnow n:118 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 9 | **LINK** peer:0x00000011 proto:espnow n:128 rssi_min:-46 rssi_med:-46 rssi_max:-46
```

---

@LAT103LON2174 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1849708 ±21 frame:7500
seq: 2076
follows: 0x00000010:1439 0x00000011:1383 0x00000012:1299 0x00000100:1032 0x00000300:4704
said: 1 | **LINKWIN** t_ms:2171426 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:73 rssi_min:-37 rssi_med:-36 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-34 rssi_med:-33 rssi_max:-31
said: 5 | **LINK** peer:0x00000300 proto:espnow n:216 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000010 proto:espnow n:130 rssi_min:-51 rssi_med:-47 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:ble n:51 rssi_min:-69 rssi_med:-63 rssi_max:-53
said: 8 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-52 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-63 rssi_max:-62
```

---

@LAT103LON2175 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1909708 ±21 frame:7500
seq: 2077
follows: 0x00000010:1440 0x00000011:1384 0x00000012:1300 0x00000100:1034 0x00000300:4708
said: 1 | **LINKWIN** t_ms:2231426 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:39 rssi_min:-33 rssi_med:-33 rssi_max:-32
said: 3 | **LINK** peer:0x00000300 proto:espnow n:109 rssi_min:-43 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-37 rssi_med:-36 rssi_max:-35
said: 5 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-58 rssi_max:-56
said: 6 | **LINK** peer:0x00000010 proto:espnow n:77 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 7 | **LINK** peer:0x00000012 proto:ble n:43 rssi_min:-80 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 9 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-79 rssi_med:-63 rssi_max:-54
```

---

@LAT103LON2176 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1969708 ±21 frame:7500
seq: 2078
follows: 0x00000010:1441 0x00000011:1385 0x00000012:1300 0x00000100:1035 0x00000300:4710
said: 1 | **LINKWIN** t_ms:2291426 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-37 rssi_med:-36 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:130 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 5 | **LINK** peer:0x00000010 proto:espnow n:124 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 6 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 8 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-60 rssi_med:-58 rssi_max:-50
said: 9 | **LINK** peer:0x00000012 proto:ble n:34 rssi_min:-52 rssi_med:-49 rssi_max:-48
```

---

@LAT103LON2177 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2029528 ±21 frame:7500
seq: 2079
follows: 0x00000010:1442 0x00000011:1386 0x00000012:1300 0x00000100:1036 0x00000300:4712
said: 1 | **LINKWIN** t_ms:2351426 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:161 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 3 | **LINK** peer:0x00000010 proto:espnow n:81 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:espnow n:142 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 5 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-37 rssi_med:-36 rssi_max:-35
said: 6 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-63 rssi_max:-62
said: 7 | **LINK** peer:0x00000012 proto:ble n:45 rssi_min:-52 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-80 rssi_med:-58 rssi_max:-50
said: 9 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-69 rssi_med:-63 rssi_max:-54
```

---

@LAT103LON2178 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2089685 ±21 frame:7500
seq: 2080
follows: 0x00000010:1443 0x00000011:1387 0x00000012:1302 0x00000100:1037 0x00000300:4714
said: 1 | **LINKWIN** t_ms:2411429 stream:0xc9e0e898 wall:0 window_ms:60003
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-37 rssi_med:-36 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:155 rssi_min:-47 rssi_med:-40 rssi_max:-37
said: 4 | **LINK** peer:0x00000010 proto:espnow n:85 rssi_min:-56 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-74 rssi_med:-66 rssi_max:-52
said: 6 | **LINK** peer:0x00000011 proto:ble n:72 rssi_min:-83 rssi_med:-63 rssi_max:-57
said: 7 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-48 rssi_med:-46 rssi_max:-44
said: 8 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-62 rssi_med:-57 rssi_max:-50
said: 9 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-52 rssi_med:-49 rssi_max:-48
```

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

@LAT103LON2179 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2149716 ±21 frame:7500
seq: 2081
follows: 0x00000010:1444 0x00000011:1388 0x00000012:1302 0x00000100:1038 0x00000300:4716
said: 1 | **LINKWIN** t_ms:2471429 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:65 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 3 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-36 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000011 proto:espnow n:78 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:94 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 6 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-57 rssi_max:-50
said: 7 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 9 | **LINK** peer:0x00000300 proto:espnow n:212 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT103LON2180 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2209715 ±21 frame:7500
seq: 2082
follows: 0x00000010:1445 0x00000011:1389 0x00000012:1303 0x00000100:1039 0x00000300:4716
said: 1 | **LINKWIN** t_ms:2531429 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:166 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000011 proto:espnow n:96 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 6 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-82 rssi_med:-49 rssi_max:-48
said: 7 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-60 rssi_med:-57 rssi_max:-50
said: 8 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-72 rssi_med:-63 rssi_max:-62
said: 9 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-79 rssi_med:-63 rssi_max:-54
```

---

@LAT103LON2181 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2269717 ±21 frame:7500
seq: 2083
follows: 0x00000010:1446 0x00000011:1390 0x00000012:1304 0x00000100:1040 0x00000300:4720
said: 1 | **LINKWIN** t_ms:2591429 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-47 rssi_med:-46 rssi_max:-45
said: 4 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-63 rssi_max:-54
said: 6 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 7 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-60 rssi_med:-57 rssi_max:-50
said: 8 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 9 | **LINK** peer:0x00000300 proto:espnow n:206 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT103LON2182 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2330538 ±21 frame:7500
seq: 2084
follows: 0x00000010:1447 0x00000011:1391 0x00000012:1305 0x00000100:1041 0x00000300:4722
said: 1 | **LINKWIN** t_ms:2652241 stream:0xc9e0e898 wall:0 window_ms:60821
said: 2 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-69 rssi_med:-63 rssi_max:-54
said: 3 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-39 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000011 proto:espnow n:140 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 6 | **LINK** peer:0x00000300 proto:espnow n:190 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 7 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-80 rssi_med:-63 rssi_max:-62
said: 8 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-80 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-60 rssi_med:-57 rssi_max:-50
```

---

@LAT103LON2183 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2390538 ±21 frame:7500
seq: 2085
follows: 0x00000010:1448 0x00000011:1393 0x00000012:1306 0x00000100:1042 0x00000300:4724
said: 1 | **LINKWIN** t_ms:2712250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-48 rssi_med:-46 rssi_max:-44
said: 4 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000300 proto:espnow n:182 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-69 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-57 rssi_max:-50
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-78 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-64 rssi_med:-63 rssi_max:-61
```

---

@LAT103LON2184 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2450541 ±21 frame:7500
seq: 2086
follows: 0x00000010:1449 0x00000011:1394 0x00000012:1307 0x00000100:1044 0x00000300:4726
said: 1 | **LINKWIN** t_ms:2772250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-60 rssi_med:-57 rssi_max:-50
said: 3 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-43 rssi_med:-40 rssi_max:-40
said: 5 | **LINK** peer:0x00000010 proto:espnow n:88 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 6 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000012 proto:espnow n:75 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-78 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000011 proto:espnow n:160 rssi_min:-49 rssi_med:-46 rssi_max:-45
```

---

@LAT103LON2185 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2510542 ±21 frame:7500
seq: 2087
follows: 0x00000010:1450 0x00000011:1395 0x00000012:1308 0x00000100:1045 0x00000300:4728
said: 1 | **LINKWIN** t_ms:2832250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:71 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-69 rssi_med:-63 rssi_max:-54
said: 6 | **LINK** peer:0x00000012 proto:espnow n:108 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-80 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-80 rssi_med:-63 rssi_max:-62
said: 9 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-57 rssi_max:-50
```

---

@LAT103LON2186 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2570543 ±21 frame:7500
seq: 2088
follows: 0x00000010:1451 0x00000011:1396 0x00000012:1309 0x00000100:1046 0x00000300:4730
said: 1 | **LINKWIN** t_ms:2892250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | **LINK** peer:0x00000010 proto:espnow n:130 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000300 proto:espnow n:275 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-80 rssi_med:-63 rssi_max:-62
said: 7 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-57 rssi_max:-50
said: 8 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-63 rssi_max:-55
said: 9 | **LINK** peer:0x00000012 proto:espnow n:99 rssi_min:-34 rssi_med:-33 rssi_max:-32
```

---

@LAT103LON2187 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2630544 ±21 frame:7500
seq: 2089
follows: 0x00000010:1452 0x00000011:1397 0x00000012:1310 0x00000100:1047 0x00000300:4732
said: 1 | **LINKWIN** t_ms:2952250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:152 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:espnow n:88 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 6 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 7 | **LINK** peer:0x00000012 proto:espnow n:97 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 8 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-80 rssi_med:-49 rssi_max:-48
```

---

@LAT103LON2188 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2690542 ±21 frame:7500
seq: 2090
follows: 0x00000010:1453 0x00000011:1398 0x00000012:1311 0x00000100:1048 0x00000300:4734
said: 1 | **LINKWIN** t_ms:3012250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-57 rssi_max:-50
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 4 | **LINK** peer:0x00000300 proto:espnow n:211 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 5 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-80 rssi_med:-49 rssi_max:-48
said: 6 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 7 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 8 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-79 rssi_med:-63 rssi_max:-62
said: 9 | **LINK** peer:0x00000012 proto:espnow n:93 rssi_min:-33 rssi_med:-33 rssi_max:-32
```

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

@LAT103LON2189 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2750545 ±21 frame:7500
seq: 2091
follows: 0x00000010:1454 0x00000011:1399 0x00000012:1312 0x00000100:1049 0x00000300:4734
said: 1 | **LINKWIN** t_ms:3072249 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:73 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-37 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:espnow n:83 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 5 | **LINK** peer:0x00000010 proto:espnow n:63 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 6 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 7 | **LINK** peer:0x00000012 proto:espnow n:74 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 8 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-57 rssi_max:-50
said: 9 | **LINK** peer:0x00000012 proto:ble n:68 rssi_min:-80 rssi_med:-49 rssi_max:-48
```

---

@LAT103LON2190 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2810546 ±21 frame:7500
seq: 2092
follows: 0x00000010:1455 0x00000011:1400 0x00000012:1313 0x00000100:1050 0x00000300:4738
said: 1 | **LINKWIN** t_ms:3132249 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:128 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | **LINK** peer:0x00000010 proto:espnow n:81 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-63 rssi_max:-62
said: 6 | **LINK** peer:0x00000012 proto:espnow n:109 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 9 | **LINK** peer:0x00000300 proto:espnow n:180 rssi_min:-43 rssi_med:-40 rssi_max:-40
```

---

@LAT103LON2191 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2870547 ±21 frame:7500
seq: 2093
follows: 0x00000010:1456 0x00000011:1401 0x00000012:1314 0x00000100:1051 0x00000300:4740
said: 1 | **LINKWIN** t_ms:3192250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-71 rssi_med:-57 rssi_max:-50
said: 4 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-64 rssi_med:-63 rssi_max:-62
said: 5 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-49 rssi_max:-48
said: 6 | **LINK** peer:0x00000011 proto:espnow n:87 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 7 | **LINK** peer:0x00000010 proto:espnow n:108 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 8 | **LINK** peer:0x00000300 proto:espnow n:169 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 9 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-37 rssi_med:-35 rssi_max:-35
```

---

@LAT103LON2192 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2930549 ±21 frame:7500
seq: 2094
follows: 0x00000010:1457 0x00000011:1402 0x00000012:1315 0x00000100:1052 0x00000300:4742
said: 1 | **LINKWIN** t_ms:3252250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:211 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000011 proto:espnow n:103 rssi_min:-48 rssi_med:-46 rssi_max:-45
said: 6 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 7 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:espnow n:100 rssi_min:-34 rssi_med:-33 rssi_max:-30
said: 9 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-57 rssi_max:-50
```

---

@LAT103LON2193 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2990550 ±21 frame:7500
seq: 2095
follows: 0x00000010:1458 0x00000011:1403 0x00000012:1316 0x00000100:1053 0x00000300:4744
said: 1 | **LINKWIN** t_ms:3312250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:167 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:espnow n:123 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000011 proto:espnow n:130 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 6 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-61 rssi_med:-57 rssi_max:-50
said: 7 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-69 rssi_med:-63 rssi_max:-55
said: 8 | **LINK** peer:0x00000012 proto:ble n:71 rssi_min:-81 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-34 rssi_med:-32 rssi_max:-32
```

---

@LAT103LON2194 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3050551 ±21 frame:7500
seq: 2096
follows: 0x00000010:1459 0x00000011:1404 0x00000012:1317 0x00000100:1055 0x00000300:4746
said: 1 | **LINKWIN** t_ms:3372250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 3 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-49 rssi_max:-48
said: 4 | **LINK** peer:0x00000010 proto:espnow n:114 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-77 rssi_med:-63 rssi_max:-62
said: 6 | **LINK** peer:0x00000012 proto:espnow n:114 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000011 proto:espnow n:146 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 8 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-57 rssi_max:-50
said: 9 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-37 rssi_med:-35 rssi_max:-34
```

---

@LAT103LON2195 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3110552 ±21 frame:7500
seq: 2097
follows: 0x00000010:1460 0x00000011:1405 0x00000012:1318 0x00000100:1056 0x00000300:4748
said: 1 | **LINKWIN** t_ms:3432250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:120 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-69 rssi_med:-63 rssi_max:-54
said: 6 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 7 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:espnow n:38 rssi_min:-33 rssi_med:-33 rssi_max:-32
said: 9 | **LINK** peer:0x00000300 proto:espnow n:100 rssi_min:-88 rssi_med:-40 rssi_max:-40
```

---

@LAT103LON2196 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3170553 ±21 frame:7500
seq: 2098
follows: 0x00000010:1461 0x00000011:1406 0x00000012:1319 0x00000100:1057 0x00000300:4748
said: 1 | **LINKWIN** t_ms:3492250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:198 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-80 rssi_med:-63 rssi_max:-62
said: 5 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-49 rssi_max:-48
said: 6 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-69 rssi_med:-63 rssi_max:-55
said: 7 | **LINK** peer:0x00000012 proto:espnow n:85 rssi_min:-33 rssi_med:-33 rssi_max:-32
said: 8 | **LINK** peer:0x00000010 proto:espnow n:96 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000011 proto:espnow n:88 rssi_min:-48 rssi_med:-46 rssi_max:-45
```

---

@LAT103LON2197 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3230553 ±21 frame:7500
seq: 2099
follows: 0x00000010:1462 0x00000011:1407 0x00000012:1320 0x00000100:1058 0x00000300:4752
said: 1 | **LINKWIN** t_ms:3552249 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:174 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 5 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-83 rssi_med:-57 rssi_max:-50
said: 6 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000011 proto:espnow n:111 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:espnow n:97 rssi_min:-33 rssi_med:-33 rssi_max:-32
said: 9 | **LINK** peer:0x00000010 proto:espnow n:81 rssi_min:-49 rssi_med:-47 rssi_max:-47
```

---

@LAT103LON2198 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3290555 ±21 frame:7500
seq: 2100
follows: 0x00000010:1463 0x00000011:1408 0x00000012:1322 0x00000100:1059 0x00000300:4752
said: 1 | **LINKWIN** t_ms:3612250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-37 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:162 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:espnow n:105 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000011 proto:espnow n:108 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 6 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-76 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-57 rssi_max:-50
said: 8 | **LINK** peer:0x00000012 proto:espnow n:87 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-79 rssi_med:-49 rssi_max:-48
```

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

@LAT103LON2199 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3350554 ±21 frame:7500
seq: 2101
follows: 0x00000010:1464 0x00000011:1409 0x00000012:1323 0x00000100:1060 0x00000300:4756
said: 1 | **LINKWIN** t_ms:3672250 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-36 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000010 proto:espnow n:75 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:108 rssi_min:-49 rssi_med:-46 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-69 rssi_med:-63 rssi_max:-55
said: 6 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-61 rssi_med:-57 rssi_max:-50
said: 7 | **LINK** peer:0x00000012 proto:espnow n:79 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000011 proto:ble n:51 rssi_min:-63 rssi_med:-63 rssi_max:-62
```

---

@LAT103LON2200 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3410556 ±21 frame:7500
seq: 2102
follows: 0x00000010:1465 0x00000011:1410 0x00000012:1324 0x00000100:1061 0x00000300:4758
said: 1 | **LINKWIN** t_ms:3732301 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-79 rssi_med:-63 rssi_max:-54
said: 3 | **LINK** peer:0x00000300 proto:espnow n:163 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-39 rssi_med:-35 rssi_max:-35
said: 5 | **LINK** peer:0x00000010 proto:espnow n:131 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 6 | **LINK** peer:0x00000011 proto:espnow n:71 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 7 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-63 rssi_med:-62 rssi_max:-62
```

---

@LAT103LON2201 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3470558 ±21 frame:7500
seq: 2103
follows: 0x00000010:1466 0x00000011:1411 0x00000012:1325 0x00000100:1062 0x00000300:4760
said: 1 | **LINKWIN** t_ms:3792301 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:132 rssi_min:-44 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-62
said: 5 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-57 rssi_max:-50
said: 6 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-49 rssi_max:-48
said: 7 | **LINK** peer:0x00000010 proto:espnow n:96 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 8 | **LINK** peer:0x00000011 proto:espnow n:110 rssi_min:-48 rssi_med:-46 rssi_max:-45
said: 9 | **LINK** peer:0x00000012 proto:espnow n:79 rssi_min:-34 rssi_med:-32 rssi_max:-32
```

---

@LAT105LON5700 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3468251 ±0 frame:7500
seq: 4759
follows: 0x00000010:1466 0x00000011:1411 0x00000012:1325 0x00000100:1062 0x00000200:2102
said: 1 | **LINKWIN** t_ms:3789995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 4 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-61 rssi_med:-56 rssi_max:-52
said: 6 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-65 rssi_med:-59 rssi_max:-54
said: 7 | **LINK** peer:0x00000010 proto:espnow n:97 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-61 rssi_max:-49
said: 9 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-79 rssi_med:-63 rssi_max:-57
said: 10 | 0x00000010 ble met predicted:-61 observed:-61
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-63 observed:-63
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000012 ble met predicted:-60 observed:-56
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-59 observed:-59
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5701 | created:0 | updated:0

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

@LAT105LON5702 | created:0 | updated:0

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

@LAT105LON5703 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3513006 ±21 frame:7500
seq: 1412
follows: 0x00000010:1467 0x00000012:1326 0x00000100:1062 0x00000200:2103 0x00000300:4760
said: 1 | **LINKWIN** t_ms:3834731 stream:0xc9e0e898 wall:0 window_ms:60014
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-70 rssi_med:-69 rssi_max:-68
said: 3 | **LINK** peer:0x00000300 proto:espnow n:156 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 4 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000012 proto:espnow n:138 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 7 | **LINK** peer:0x00000200 proto:espnow n:128 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 8 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-63 rssi_max:-60
```

---

@LAT103LON2202 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3530558 ±21 frame:7500
seq: 2104
follows: 0x00000010:1467 0x00000011:1412 0x00000012:1326 0x00000100:1063 0x00000300:4762
said: 1 | **LINKWIN** t_ms:3852301 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:86 rssi_min:-47 rssi_med:-46 rssi_max:-45
said: 3 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000300 proto:espnow n:181 rssi_min:-41 rssi_med:-40 rssi_max:-38
said: 5 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-79 rssi_med:-49 rssi_max:-48
said: 6 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-72 rssi_med:-57 rssi_max:-50
said: 7 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 8 | **LINK** peer:0x00000012 proto:espnow n:143 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 9 | **LINK** peer:0x00000011 proto:ble n:69 rssi_min:-63 rssi_med:-63 rssi_max:-62
```

---

@LAT105LON5704 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3471549 ±21 frame:7500
seq: 1326
follows: 0x00000010:1466 0x00000011:1411 0x00000100:1062 0x00000200:2102 0x00000300:4758
said: 1 | **LINKWIN** t_ms:3793284 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-49 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 6 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000011 proto:espnow n:94 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 8 | **LINK** peer:0x00000010 proto:espnow n:108 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 9 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-80 rssi_med:-53 rssi_max:-49
```

---

@LAT105LON5705 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3528251 ±0 frame:7500
seq: 4761
follows: 0x00000010:1467 0x00000011:1412 0x00000012:1326 0x00000100:1063 0x00000200:2103
said: 1 | **LINKWIN** t_ms:3849995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 3 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-50 rssi_med:-47 rssi_max:-45
said: 4 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-57
said: 5 | **LINK** peer:0x00000200 proto:espnow n:119 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000011 proto:espnow n:83 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-62 rssi_max:-50
said: 8 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-83 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 10 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-56 observed:-56
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000200 ble met predicted:-59 observed:-59
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-61 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT105LON5706 | created:0 | updated:0

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

@LAT105LON5707 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3531551 ±21 frame:7500
seq: 1327
follows: 0x00000010:1467 0x00000011:1412 0x00000100:1063 0x00000200:2103 0x00000300:4760
said: 1 | **LINKWIN** t_ms:3853284 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-80 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 4 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 6 | **LINK** peer:0x00000011 proto:espnow n:85 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000200 proto:espnow n:128 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 9 | **LINK** peer:0x00000300 proto:espnow n:187 rssi_min:-46 rssi_med:-45 rssi_max:-44
```

---

@LAT103LON2203 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3590559 ±21 frame:7500
seq: 2105
follows: 0x00000010:1468 0x00000011:1413 0x00000012:1327 0x00000100:1064 0x00000300:4764
said: 1 | **LINKWIN** t_ms:3912300 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:145 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 5 | **LINK** peer:0x00000011 proto:espnow n:73 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 6 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-61 rssi_med:-57 rssi_max:-50
said: 7 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:espnow n:107 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 9 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-79 rssi_med:-63 rssi_max:-61
```

---

@LAT105LON5708 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3591558 ±21 frame:7500
seq: 1328
follows: 0x00000010:1468 0x00000011:1413 0x00000100:1064 0x00000200:2104 0x00000300:4762
said: 1 | **LINKWIN** t_ms:3913291 stream:0xc9e0e898 wall:0 window_ms:60007
said: 2 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-58 rssi_max:-48
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:espnow n:76 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 6 | **LINK** peer:0x00000200 proto:espnow n:98 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-80 rssi_med:-50 rssi_max:-43
said: 8 | **LINK** peer:0x00000010 proto:espnow n:87 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 9 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-36 rssi_med:-31 rssi_max:-30
```

---

@LAT105LON5709 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3588251 ±0 frame:7500
seq: 4763
follows: 0x00000010:1468 0x00000011:1413 0x00000012:1327 0x00000100:1064 0x00000200:2104
said: 1 | **LINKWIN** t_ms:3909995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 3 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-29 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:espnow n:102 rssi_min:-46 rssi_med:-45 rssi_max:-41
said: 5 | **LINK** peer:0x00000011 proto:espnow n:70 rssi_min:-65 rssi_med:-62 rssi_max:-58
said: 6 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000012 proto:ble n:74 rssi_min:-82 rssi_med:-56 rssi_max:-52
said: 8 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 9 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-66 rssi_med:-61 rssi_max:-50
said: 10 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000011 ble met predicted:-63 observed:-63
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-61
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-59 observed:-59
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-56 observed:-56
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT105LON5710 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3573008 ±21 frame:7500
seq: 1413
follows: 0x00000010:1468 0x00000012:1327 0x00000100:1063 0x00000200:2104 0x00000300:4762
said: 1 | **LINKWIN** t_ms:3894731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:167 rssi_min:-63 rssi_med:-59 rssi_max:-57
said: 3 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-69 rssi_med:-69 rssi_max:-65
said: 4 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 5 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-41 rssi_med:-35 rssi_max:-31
said: 6 | **LINK** peer:0x00000010 proto:espnow n:89 rssi_min:-40 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-54 rssi_max:-51
said: 8 | **LINK** peer:0x00000012 proto:ble n:70 rssi_min:-82 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-59 rssi_max:-54
```

---

@LAT105LON5711 | created:0 | updated:0

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

@LAT105LON5712 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3633008 ±21 frame:7500
seq: 1414
follows: 0x00000010:1469 0x00000012:1328 0x00000100:1064 0x00000200:2105 0x00000300:4764
said: 1 | **LINKWIN** t_ms:3954731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-63 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 4 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-70 rssi_med:-69 rssi_max:-68
said: 5 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-62 rssi_med:-59 rssi_max:-56
said: 6 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-80 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-41 rssi_med:-35 rssi_max:-35
```

---

@LAT103LON2204 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3650561 ±21 frame:7500
seq: 2106
follows: 0x00000010:1469 0x00000011:1414 0x00000012:1328 0x00000100:1066 0x00000300:4766
said: 1 | **LINKWIN** t_ms:3972300 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:140 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | **LINK** peer:0x00000300 proto:espnow n:185 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000012 proto:espnow n:119 rssi_min:-33 rssi_med:-32 rssi_max:-32
said: 6 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-50 rssi_med:-47 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-57 rssi_max:-50
```

---

@LAT105LON5713 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3648251 ±0 frame:7500
seq: 4765
follows: 0x00000010:1469 0x00000011:1414 0x00000012:1328 0x00000100:1066 0x00000200:2105
said: 1 | **LINKWIN** t_ms:3969995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:141 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-65 rssi_med:-61 rssi_max:-49
said: 4 | **LINK** peer:0x00000200 proto:espnow n:86 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 6 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-64 rssi_med:-59 rssi_max:-54
said: 7 | **LINK** peer:0x00000010 proto:espnow n:116 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-79 rssi_med:-63 rssi_max:-57
said: 10 | 0x00000200 ble met predicted:-59 observed:-59
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-48
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-56 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-63
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-61 observed:-61
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON2205 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3710561 ±21 frame:7500
seq: 2107
follows: 0x00000010:1470 0x00000011:1415 0x00000012:1329 0x00000100:1068 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4032301 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-79 rssi_med:-49 rssi_max:-48
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-39 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000011 proto:espnow n:98 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:61 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 6 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-57 rssi_max:-50
said: 7 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-62
said: 8 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-69 rssi_med:-63 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:espnow n:76 rssi_min:-33 rssi_med:-32 rssi_max:-32
```

---

@LAT105LON5714 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3708457 ±0 frame:7500
seq: 4767
follows: 0x00000010:1470 0x00000011:1415 0x00000012:1329 0x00000100:1068 0x00000200:2106
said: 1 | **LINKWIN** t_ms:4030201 stream:0xc9e0e898 wall:0 window_ms:60206
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-64 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000010 proto:espnow n:66 rssi_min:-49 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000200 proto:espnow n:63 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-82 rssi_med:-62 rssi_max:-49
said: 10 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000010 ble met predicted:-61 observed:-62
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-59 observed:-59
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-48 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT105LON5715 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3693008 ±21 frame:7500
seq: 1415
follows: 0x00000010:1470 0x00000012:1329 0x00000100:1066 0x00000200:2106 0x00000300:4766
said: 1 | **LINKWIN** t_ms:4014730 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-63 rssi_max:-60
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-70 rssi_med:-69 rssi_max:-64
said: 5 | **LINK** peer:0x00000200 proto:espnow n:65 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000300 proto:espnow n:117 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 7 | **LINK** peer:0x00000010 proto:espnow n:48 rssi_min:-40 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000012 proto:espnow n:76 rssi_min:-42 rssi_med:-35 rssi_max:-35
said: 9 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-81 rssi_med:-49 rssi_max:-44
```

---

@LAT105LON5716 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3651591 ±21 frame:7500
seq: 1329
follows: 0x00000010:1469 0x00000011:1414 0x00000100:1065 0x00000200:2105 0x00000300:4764
said: 1 | **LINKWIN** t_ms:3973324 stream:0xc9e0e898 wall:0 window_ms:60033
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 4 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:espnow n:140 rssi_min:-43 rssi_med:-41 rssi_max:-36
said: 6 | **LINK** peer:0x00000300 proto:espnow n:180 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 7 | **LINK** peer:0x00000200 proto:espnow n:90 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-51 rssi_max:-43
said: 9 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-36 rssi_med:-32 rssi_max:-31
```

---

@LAT105LON5717 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3711596 ±21 frame:7500
seq: 1330
follows: 0x00000010:1470 0x00000011:1415 0x00000100:1068 0x00000200:2106 0x00000300:4766
said: 1 | **LINKWIN** t_ms:4033328 stream:0xc9e0e898 wall:0 window_ms:60004
said: 2 | **LINK** peer:0x00000011 proto:espnow n:112 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:espnow n:68 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 4 | **LINK** peer:0x00000011 proto:ble n:70 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 5 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 7 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-51
said: 8 | **LINK** peer:0x00000200 proto:espnow n:90 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-36 rssi_med:-31 rssi_max:-30
```

---

@LAT105LON5718 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3753010 ±21 frame:7500
seq: 1416
follows: 0x00000010:1471 0x00000012:1330 0x00000100:1068 0x00000200:2107 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4074731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 3 | **LINK** peer:0x00000300 proto:espnow n:137 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 4 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000200 proto:espnow n:137 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-41 rssi_med:-35 rssi_max:-32
said: 7 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-54 rssi_max:-51
```

---

@LAT101LON0 | sid:2136c351 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:1246 last_ms:3719688
t_ms:4089333 stream:0xc9e0e898 wall:0

---

@LAT101LON1 | sid:27653a2f | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:627 last_ms:3718519
t_ms:4089333 stream:0xc9e0e898 wall:0

---

@LAT101LON2 | sid:42caf4db | created:0 | updated:0 |
**PEER** node:0x00000300 spoke:1 declared:0x3fb7 verified:0x2fb7 exercised:0x0015 cap_epoch:9
**TRACE** copresence:255 half_life_ms:600000 reinforced:1347 last_ms:3719688
t_ms:4089333 stream:0xc9e0e898 wall:0

---

@LAT101LON3 | sid:2665389c | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:616 last_ms:3719016
t_ms:4089333 stream:0xc9e0e898 wall:0

---

@LAT101LON4 | sid:29653d55 | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:253 half_life_ms:600000 reinforced:445 last_ms:3706241
t_ms:4089333 stream:0xc9e0e898 wall:0

---

@LAT103LON2206 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3770592 ±21 frame:7500
seq: 2108
follows: 0x00000010:1471 0x00000011:1416 0x00000012:1330 0x00000100:1069 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4092327 stream:0xc9e0e898 wall:0 window_ms:60029
said: 2 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-80 rssi_med:-57 rssi_max:-50
said: 3 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-38 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000010 proto:espnow n:119 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000300 proto:espnow n:141 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:espnow n:145 rssi_min:-49 rssi_med:-46 rssi_max:-46
said: 7 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-80 rssi_med:-63 rssi_max:-62
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-34 rssi_med:-32 rssi_max:-32
```

---

@LAT105LON5719 | created:0 | updated:0

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

@LAT105LON5720 | created:0 | updated:0

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

@LAT105LON5721 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3771597 ±21 frame:7500
seq: 1331
follows: 0x00000010:1471 0x00000011:1416 0x00000100:1069 0x00000200:2107 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4093328 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 3 | **LINK** peer:0x00000010 proto:espnow n:110 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 4 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000300 proto:ble n:74 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:espnow n:147 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 7 | **LINK** peer:0x00000011 proto:espnow n:166 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-45 rssi_max:-44
said: 9 | **LINK** peer:0x00000200 proto:espnow n:125 rssi_min:-35 rssi_med:-30 rssi_max:-30
```

---

@LAT105LON5722 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3768457 ±0 frame:7500
seq: 4770
follows: 0x00000010:1471 0x00000011:1416 0x00000012:1330 0x00000100:1069 0x00000200:2107
said: 1 | **LINKWIN** t_ms:4090201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:159 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:espnow n:130 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 6 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-56 rssi_max:-52
said: 7 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-65 rssi_med:-62 rssi_max:-50
said: 8 | **LINK** peer:0x00000010 proto:espnow n:95 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 10 | 0x00000011 ble met predicted:-63 observed:-63
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-59 observed:-59
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-62 observed:-62
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT105LON5723 | created:0 | updated:0

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

@LAT105LON5724 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3813010 ±21 frame:7500
seq: 1417
follows: 0x00000010:1472 0x00000012:1331 0x00000100:1069 0x00000200:2108 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4134731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000200 proto:espnow n:141 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000300 proto:espnow n:159 rssi_min:-62 rssi_med:-58 rssi_max:-57
said: 5 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-70 rssi_med:-69 rssi_max:-65
said: 6 | **LINK** peer:0x00000012 proto:espnow n:107 rssi_min:-42 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 8 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 9 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-63 rssi_max:-60
```

---

@LAT103LON2207 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3830592 ±21 frame:7500
seq: 2109
follows: 0x00000010:1472 0x00000011:1417 0x00000012:1331 0x00000100:1070 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4152330 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:98 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000300 proto:espnow n:152 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 8 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-57 rssi_max:-50
```

---

@LAT105LON5725 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3828457 ±0 frame:7500
seq: 4772
follows: 0x00000010:1472 0x00000011:1417 0x00000012:1331 0x00000100:1070 0x00000200:2108
said: 1 | **LINKWIN** t_ms:4150201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-61 rssi_med:-60 rssi_max:-51
said: 6 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-64 rssi_med:-59 rssi_max:-54
said: 7 | **LINK** peer:0x00000011 proto:ble n:46 rssi_min:-79 rssi_med:-63 rssi_max:-58
said: 8 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-65 rssi_med:-61 rssi_max:-49
said: 9 | **LINK** peer:0x00000200 proto:espnow n:142 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 10 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 ble met predicted:-63 observed:-63
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000012 ble met predicted:-56 observed:-60
percept: 14 | 0x00000012 | link_stable | ble | + | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-61
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-59 observed:-59
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5726 | created:0 | updated:0

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

@LAT105LON5727 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3831596 ±21 frame:7500
seq: 1332
follows: 0x00000010:1472 0x00000011:1417 0x00000100:1070 0x00000200:2108 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4153328 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:155 rssi_min:-46 rssi_med:-45 rssi_max:-41
said: 4 | **LINK** peer:0x00000010 proto:espnow n:112 rssi_min:-38 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000200 proto:espnow n:186 rssi_min:-36 rssi_med:-30 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:113 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 7 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-53 rssi_max:-51
said: 9 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-52 rssi_max:-43
```

---

@LAT105LON5728 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3873010 ±21 frame:7500
seq: 1418
follows: 0x00000010:1473 0x00000012:1332 0x00000100:1070 0x00000200:2109 0x00000300:4773
said: 1 | **LINKWIN** t_ms:4194731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-83 rssi_med:-54 rssi_max:-50
said: 3 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 4 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-49 rssi_max:-43
said: 5 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-58 rssi_max:-54
said: 6 | **LINK** peer:0x00000200 proto:espnow n:119 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000300 proto:espnow n:178 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-63 rssi_max:-60
```

---

@LAT103LON2208 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3890593 ±21 frame:7500
seq: 2110
follows: 0x00000010:1473 0x00000011:1418 0x00000012:1332 0x00000100:1071 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4212330 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-38 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000010 proto:espnow n:93 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:114 rssi_min:-48 rssi_med:-46 rssi_max:-45
said: 5 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-57 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:ble n:74 rssi_min:-81 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 9 | **LINK** peer:0x00000012 proto:espnow n:64 rssi_min:-33 rssi_med:-32 rssi_max:-32
```

---

@LAT104LON248 | created:0 | updated:0

**carried through @LAT103LON2168**

```ttdb-carried
through: 2168
through: 8263
```

---

@LAT105LON5729 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3888457 ±0 frame:7500
seq: 4774
follows: 0x00000010:1473 0x00000011:1418 0x00000012:1332 0x00000100:1071 0x00000200:2109
said: 1 | **LINKWIN** t_ms:4210201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 5 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-66 rssi_med:-62 rssi_max:-49
said: 6 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-65 rssi_med:-61 rssi_max:-59
said: 7 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-63 rssi_max:-58
said: 8 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000010 proto:espnow n:94 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 10 | 0x00000011 espnow met predicted:-62 observed:-61
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-60 observed:-56
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000200 ble met predicted:-59 observed:-59
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000011 ble met predicted:-63 observed:-63
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-61 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON5730 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3891610 ±21 frame:7500
seq: 1333
follows: 0x00000010:1473 0x00000011:1418 0x00000100:1071 0x00000200:2109 0x00000300:4773
said: 1 | **LINKWIN** t_ms:4213341 stream:0xc9e0e898 wall:0 window_ms:60013
said: 2 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 4 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000010 proto:espnow n:82 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 6 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-83 rssi_med:-53 rssi_max:-49
said: 7 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000300 proto:espnow n:221 rssi_min:-86 rssi_med:-44 rssi_max:-40
said: 9 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-50 rssi_max:-43
```

---

@LAT105LON5731 | created:0 | updated:0

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

@LAT105LON5732 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3933010 ±21 frame:7500
seq: 1419
follows: 0x00000010:1474 0x00000012:1333 0x00000100:1071 0x00000200:2110 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4254731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:141 rssi_min:-62 rssi_med:-58 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-70 rssi_med:-69 rssi_max:-54
said: 4 | **LINK** peer:0x00000010 proto:espnow n:110 rssi_min:-41 rssi_med:-34 rssi_max:-31
said: 5 | **LINK** peer:0x00000012 proto:espnow n:127 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 6 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-82 rssi_med:-63 rssi_max:-55
said: 7 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-82 rssi_med:-49 rssi_max:-41
said: 8 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-54 rssi_max:-47
said: 9 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-82 rssi_med:-59 rssi_max:-53
```

---

@LAT103LON2209 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3950594 ±21 frame:7500
seq: 2111
follows: 0x00000010:1474 0x00000011:1419 0x00000012:1333 0x00000100:1072 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4272329 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:156 rssi_min:-48 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-73 rssi_med:-63 rssi_max:-61
said: 4 | **LINK** peer:0x00000011 proto:espnow n:94 rssi_min:-50 rssi_med:-46 rssi_max:-45
said: 5 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-39 rssi_med:-35 rssi_max:-33
said: 6 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-79 rssi_med:-57 rssi_max:-47
said: 7 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-35 rssi_med:-32 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-54 rssi_med:-49 rssi_max:-47
said: 9 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-70 rssi_med:-63 rssi_max:-53
```

---

@LAT105LON5733 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3948457 ±0 frame:7500
seq: 4776
follows: 0x00000010:1474 0x00000011:1419 0x00000012:1333 0x00000100:1072 0x00000200:2110
said: 1 | **LINKWIN** t_ms:4270201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-62 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-65 rssi_med:-60 rssi_max:-45
said: 4 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-46 rssi_med:-45 rssi_max:-38
said: 6 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-65 rssi_med:-59 rssi_max:-53
said: 7 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-67 rssi_med:-57 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-51 rssi_med:-47 rssi_max:-45
said: 9 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-78 rssi_med:-64 rssi_max:-56
said: 10 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000012 ble met predicted:-56 observed:-57
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000010 ble met predicted:-62 observed:-62
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-61 observed:-60
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-63 observed:-64
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-59 observed:-59
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT105LON5734 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3951610 ±21 frame:7500
seq: 1334
follows: 0x00000010:1474 0x00000011:1419 0x00000100:1071 0x00000200:2110 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4273341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:81 rssi_min:-44 rssi_med:-42 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 4 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-38 rssi_med:-33 rssi_max:-30
said: 6 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-37 rssi_med:-32 rssi_max:-30
said: 7 | **LINK** peer:0x00000200 proto:espnow n:131 rssi_min:-38 rssi_med:-31 rssi_max:-28
said: 8 | **LINK** peer:0x00000300 proto:espnow n:140 rssi_min:-54 rssi_med:-52 rssi_max:-35
said: 9 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-51 rssi_max:-43
```

---

@LAT105LON5735 | created:0 | updated:0

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

@LAT105LON5736 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3993012 ±21 frame:7500
seq: 1420
follows: 0x00000010:1475 0x00000012:1334 0x00000100:1072 0x00000200:2111 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4314731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-73 rssi_med:-56 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:espnow n:97 rssi_min:-54 rssi_med:-48 rssi_max:-44
said: 4 | **LINK** peer:0x00000012 proto:espnow n:120 rssi_min:-44 rssi_med:-35 rssi_max:-33
said: 5 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-58 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:espnow n:112 rssi_min:-47 rssi_med:-32 rssi_max:-30
said: 7 | **LINK** peer:0x00000300 proto:espnow n:165 rssi_min:-55 rssi_med:-49 rssi_max:-36
said: 8 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-83 rssi_med:-51 rssi_max:-42
said: 9 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-61 rssi_max:-52
```

---

@LAT103LON2210 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4010595 ±21 frame:7500
seq: 2112
follows: 0x00000010:1475 0x00000011:1420 0x00000012:1334 0x00000100:1073 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4332329 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-52 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000010 proto:espnow n:111 rssi_min:-62 rssi_med:-48 rssi_max:-42
said: 4 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-61 rssi_max:-52
said: 5 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-74 rssi_med:-62 rssi_max:-57
said: 6 | **LINK** peer:0x00000012 proto:ble n:70 rssi_min:-56 rssi_med:-49 rssi_max:-42
said: 7 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-55 rssi_max:-47
said: 8 | **LINK** peer:0x00000012 proto:espnow n:141 rssi_min:-44 rssi_med:-33 rssi_max:-28
said: 9 | **LINK** peer:0x00000300 proto:espnow n:132 rssi_min:-49 rssi_med:-41 rssi_max:-33
```

---

@LAT105LON5737 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 4008457 ±0 frame:7500
seq: 4778
follows: 0x00000010:1475 0x00000011:1420 0x00000012:1334 0x00000100:1073 0x00000200:2111
said: 1 | **LINKWIN** t_ms:4330201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-57 rssi_max:-49
said: 3 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:espnow n:108 rssi_min:-51 rssi_med:-42 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:espnow n:115 rssi_min:-53 rssi_med:-48 rssi_max:-43
said: 6 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-58 rssi_med:-49 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-62 rssi_max:-50
said: 8 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-55
said: 9 | **LINK** peer:0x00000012 proto:ble n:71 rssi_min:-81 rssi_med:-56 rssi_max:-50
said: 10 | 0x00000010 ble met predicted:-62 observed:-62
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000011 espnow violated predicted:-60 observed:-49
percept: 11 | 0x00000011 | link_stable | espnow | - | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-42
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-59 observed:-57
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-57 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-48
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-64 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT105LON5738 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4011611 ±21 frame:7500
seq: 1335
follows: 0x00000010:1475 0x00000011:1420 0x00000100:1073 0x00000200:2111 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4333341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-45 rssi_med:-31 rssi_max:-27
said: 3 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-56 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:89 rssi_min:-56 rssi_med:-41 rssi_max:-35
said: 5 | **LINK** peer:0x00000300 proto:espnow n:123 rssi_min:-60 rssi_med:-38 rssi_max:-27
said: 6 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-53 rssi_max:-43
said: 7 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-52 rssi_med:-32 rssi_max:-30
said: 8 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-50 rssi_med:-31 rssi_max:-25
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-45 rssi_max:-39
```
