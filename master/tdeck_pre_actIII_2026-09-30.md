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

**STREAM-ADOPTED** stream:0x6ceb85ae wall:0 t_ms:451063 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x5def950e wall:0 t_ms:0 node:0x200 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x0870722b wall:0 t_ms:56421 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x0870722b wall:0 t_ms:730437 node:0x200 from:0x300
**REMAP** prev_stream:0x3bef0644 prev_t_ms:10012 offset_ms:720425 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbeb39900 wall:0 t_ms:14947 node:0x200 from:0x10
**REMAP** prev_stream:0x1c397174 prev_t_ms:5405 offset_ms:9542 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x1de72b4d wall:0 t_ms:298617 node:0x200 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xcab73254 wall:0 t_ms:0 node:0x200 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbb1177f2 wall:0 t_ms:4040646 node:0x200 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:48 last_lon:47 t_ms:45689045 stream:0xbb1177f2 wall:0 node:0x00000200

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:45700146 stream:0xbb1177f2 wall:0 node:0x00000200

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:45776322 stream:0xbb1177f2 wall:0 window_ms:78202 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-97
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:46366318 stream:0xbb1177f2 wall:0 window_ms:575633 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:46964745 stream:0xbb1177f2 wall:0 window_ms:598420 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,84a329c78fec,0283cce0e689

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:47564744 stream:0xbb1177f2 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:4
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,84a329c78fec,0283cce0e689

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:48121992 stream:0xbb1177f2 wall:0 window_ms:60041 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:48672759 stream:0xbb1177f2 wall:0 window_ms:550726 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:49272759 stream:0xbb1177f2 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:49872815 stream:0xbb1177f2 wall:0 window_ms:600056 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:4
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:50472813 stream:0xbb1177f2 wall:0 window_ms:599998 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d,0283cce0e689

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:51072813 stream:0xbb1177f2 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,84a329c78fec,64677217947d,e6b32d2cea8b,0283cce0e689,18a5ffbae2d6

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:51543921 stream:0xbb1177f2 wall:0 window_ms:60615 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-94
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xdd8340ef wall:0 t_ms:0 node:0x200 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52503 stream:0xdd8340ef wall:0 window_ms:60000 entities:12
**ENTITY** kind:wifi_ap id:98e7f4fafa31 n:1 rssi:-57
**ENTITY** kind:wifi_ap id:60f41901f0c6 n:1 rssi:-59
**ENTITY** kind:wifi_ap id:a2902da54f80 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc5bd583b912 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:c049effec409 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:266a0e4d7e8c n:1 rssi:-75
**ENTITY** kind:wifi_ap id:c8d7194f3a7c n:1 rssi:-77
**ENTITY** kind:wifi_ap id:749be8a5a868 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:acdf9f500570 n:1 rssi:-80
**ENTITY** kind:wifi_ap id:186041a57253 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:acdfbf510570 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:14cb19b7ab58 n:1 rssi:-83
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x44c6e9e1 wall:0 t_ms:674 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:54803 stream:0x44c6e9e1 wall:0 window_ms:60353 entities:12
**ENTITY** kind:wifi_ap id:a2902da54f80 n:1 rssi:-59
**ENTITY** kind:wifi_ap id:60f41901f0c6 n:1 rssi:-61
**ENTITY** kind:wifi_ap id:98e7f4fafa31 n:1 rssi:-62
**ENTITY** kind:wifi_ap id:266a0e4d7e8c n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc5bd583b912 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:acdf9f500570 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:acdfbf510570 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:749be8a5a868 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:c049effec409 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:c8d7194f3a7c n:1 rssi:-85
**ENTITY** kind:wifi_ap id:14cb19b7ab58 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:3c6ad297ddc7 n:1 rssi:-86
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xd94c8c52 wall:0 t_ms:1985246 node:0x200 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x697d2797 wall:0 t_ms:0 node:0x200 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52858 stream:0x697d2797 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:137691 stream:0x697d2797 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x0445bfe4 wall:0 t_ms:14001 node:0x200 from:0x11
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:45546 stream:0x0445bfe4 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-97
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:128572 stream:0x0445bfe4 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:219599 stream:0x0445bfe4 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:2 removed:48 last_lon:47 t_ms:353570 stream:0x0445bfe4 wall:0 node:0x00000200

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x7d224c73 wall:0 t_ms:6001 node:0x200 from:0x11
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:76445 stream:0x7d224c73 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-74 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-56 rssi_med:-47 rssi_max:-43

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:76445 stream:0x7d224c73 wall:0 window_ms:62031 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-98
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:136446 stream:0x7d224c73 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-53 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-80 rssi_med:-60 rssi_max:-51

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x3b061427 wall:0 t_ms:135353 node:0x200 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:193423 stream:0x3b061427 wall:0 window_ms:60060
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-64 rssi_med:-40 rssi_max:-36

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:193423 stream:0x3b061427 wall:0 window_ms:60096 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:253440 stream:0x3b061427 wall:0 window_ms:60017
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-52 rssi_med:-47 rssi_max:-42

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:313440 stream:0x3b061427 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-52 rssi_med:-38 rssi_max:-33

---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x8dd93153 wall:0 t_ms:0 node:0x200 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52745 stream:0x8dd93153 wall:0 window_ms:60022 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:329458 stream:0x8dd93153 wall:0 window_ms:336739
**LINK** peer:0x00000100 proto:espnow n:1 rssi_min:-47 rssi_med:-47 rssi_max:-47

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:389463 stream:0x8dd93153 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:32 rssi_min:-48 rssi_med:-47 rssi_max:-41

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:449463 stream:0x8dd93153 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-53 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-54 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-51 rssi_med:-37 rssi_max:-30

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:80973 stream:0xb23c7677 wall:0 window_ms:60028
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-39 rssi_med:-38 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-57 rssi_med:-45 rssi_max:-39
**LINK** peer:0x00000100 proto:espnow n:30 rssi_min:-40 rssi_med:-38 rssi_max:-37
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-80 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-80 rssi_med:-47 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-34 rssi_med:-33 rssi_max:-28
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-80 rssi_med:-60 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:49 rssi_min:-81 rssi_med:-61 rssi_max:-51

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:80973 stream:0xb23c7677 wall:0 window_ms:60066 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:140979 stream:0xb23c7677 wall:0 window_ms:60006
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-67 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-37 rssi_med:-34 rssi_max:-31
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-61 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-85 rssi_med:-60 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-43 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-41 rssi_med:-36 rssi_max:-31
**LINK** peer:0x00000011 proto:ble n:68 rssi_min:-81 rssi_med:-51 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-60 rssi_max:-50

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:200979 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-44 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-82 rssi_med:-59 rssi_max:-51
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-45 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-37 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-70 rssi_med:-60 rssi_max:-53

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:287566 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-57 rssi_med:-46 rssi_max:-41
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-44 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-71 rssi_med:-60 rssi_max:-47
**LINK** peer:0x00000300 proto:espnow n:17 rssi_min:-54 rssi_med:-38 rssi_max:-31
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-40 rssi_med:-35 rssi_max:-30
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-80 rssi_med:-51 rssi_max:-46
**LINK** peer:0x00000300 proto:ble n:30 rssi_min:-75 rssi_med:-54 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-60 rssi_max:-55

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:287566 stream:0xb23c7677 wall:0 window_ms:60031 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:347577 stream:0xb23c7677 wall:0 window_ms:60015
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-44 rssi_med:-40 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-79 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-44 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-54 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-84 rssi_med:-63 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-86 rssi_med:-60 rssi_max:-53

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2623811 stream:0x0a5e91fa wall:0 window_ms:60211
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-36 rssi_med:-34 rssi_max:-32

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2623811 stream:0x0a5e91fa wall:0 window_ms:60249 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2683812 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-50 rssi_med:-35 rssi_max:-34

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2743812 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-39 rssi_med:-35 rssi_max:-35

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2803812 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-38 rssi_med:-36 rssi_max:-33

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2863812 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-37 rssi_med:-35 rssi_max:-34

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2923812 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-38 rssi_med:-35 rssi_max:-35

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2983988 stream:0x0a5e91fa wall:0 window_ms:60176
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-44 rssi_med:-38 rssi_max:-35

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3043988 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-43 rssi_med:-36 rssi_max:-33

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3103988 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-40 rssi_med:-36 rssi_max:-34

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3163988 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-38 rssi_med:-36 rssi_max:-34

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3174854 stream:0x0a5e91fa wall:0 window_ms:551005 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3223988 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-37 rssi_med:-36 rssi_max:-35

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3284073 stream:0x0a5e91fa wall:0 window_ms:60085
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-37 rssi_med:-36 rssi_max:-35

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3344073 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-37 rssi_med:-36 rssi_max:-35

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3404073 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-39 rssi_med:-36 rssi_max:-35

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3464073 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-42 rssi_med:-36 rssi_max:-35

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:91555 stream:0x5b53f35b wall:0 window_ms:60653
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-59 rssi_med:-44 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-51 rssi_med:-42 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-43 rssi_med:-35 rssi_max:-29
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-66 rssi_med:-44 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-53 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-81 rssi_med:-56 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-81 rssi_med:-52 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-56 rssi_max:-49

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:91555 stream:0x5b53f35b wall:0 window_ms:60686 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:171781 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-49 rssi_med:-40 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-48 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-45 rssi_med:-35 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-52 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-81 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-54 rssi_med:-46 rssi_max:-32
**LINK** peer:0x00000012 proto:ble n:51 rssi_min:-81 rssi_med:-59 rssi_max:-48

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:171781 stream:0x5b53f35b wall:0 window_ms:60065 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:231781 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-48 rssi_med:-37 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-48 rssi_max:-38
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-83 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000300 proto:espnow n:68 rssi_min:-49 rssi_med:-33 rssi_max:-25
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-57 rssi_max:-48
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-66 rssi_med:-45 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-42 rssi_med:-36 rssi_max:-33

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:291781 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-58 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-41 rssi_max:-37
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-49 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000011 proto:ble n:69 rssi_min:-81 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-46 rssi_med:-41 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-46 rssi_med:-24 rssi_max:-23

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:355347 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-38 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-26 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-80 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-44 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-80 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-80 rssi_med:-54 rssi_max:-49

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:355347 stream:0x5b53f35b wall:0 window_ms:60041 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:415347 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-39 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-68 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-42 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-25 rssi_med:-24 rssi_max:-24
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-36 rssi_med:-34 rssi_max:-33

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:475347 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-41 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-25 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-80 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-37 rssi_med:-35 rssi_max:-33

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:535371 stream:0x5b53f35b wall:0 window_ms:60024
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-42 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-42 rssi_med:-40 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-26 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-82 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-37 rssi_med:-35 rssi_max:-33

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:595371 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-39 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-39 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-43 rssi_med:-38 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:17 rssi_min:-80 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:5 rssi_min:-48 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-26 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-58 rssi_med:-54 rssi_max:-49

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:655371 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-79 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-68 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-41 rssi_max:-37
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-83 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-63 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-51 rssi_med:-24 rssi_max:-23
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-49 rssi_med:-35 rssi_max:-34

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:715371 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-54 rssi_med:-39 rssi_max:-32
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-44 rssi_med:-26 rssi_max:-24
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-79 rssi_med:-41 rssi_max:-37
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-62 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-51 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-61 rssi_max:-49

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:775371 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-37 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-61 rssi_med:-46 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:41 rssi_min:-79 rssi_med:-58 rssi_max:-50
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-59 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-26 rssi_med:-24 rssi_max:-21
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-57 rssi_med:-44 rssi_max:-39

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:835371 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-79 rssi_med:-59 rssi_max:-51
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-35 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-24 rssi_med:-23 rssi_max:-23
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-39 rssi_max:-36
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-55 rssi_med:-46 rssi_max:-40

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:69930 stream:0x59271d10 wall:0 window_ms:60156
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-51 rssi_med:-37 rssi_max:-36

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:69930 stream:0x59271d10 wall:0 window_ms:60186 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:67951 stream:0x2fd913e7 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:32 rssi_min:-73 rssi_med:-60 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-88 rssi_med:-73 rssi_max:-66

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:67951 stream:0x2fd913e7 wall:0 window_ms:60036 entities:12
**ENTITY** kind:wifi_ap id:1619a021842c n:1 rssi:-51
**ENTITY** kind:wifi_ap id:84d34300e68d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:9a2a6f5c3f11 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:a62a6f5c3f11 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:942a6f5c3f11 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:942a6f5c42a9 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:9a2a6f5c42a9 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:a62a6f5c42a9 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:66494d2e9f59 n:1 rssi:-84
**ENTITY** kind:wifi_ap id:02fdb22ddcab n:1 rssi:-87
**ENTITY** kind:wifi_ap id:02fdb28ddcab n:1 rssi:-88
**ENTITY** kind:wifi_ap id:02fdb25ddcab n:1 rssi:-88
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:127951 stream:0x2fd913e7 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-86 rssi_med:-69 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:43 rssi_min:-68 rssi_med:-53 rssi_max:-50

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:150088 stream:0x5dc49a3b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:9 rssi_min:-96 rssi_med:-95 rssi_max:-92
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-96 rssi_med:-88 rssi_max:-82

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:150088 stream:0x5dc49a3b wall:0 window_ms:60043 entities:12
**ENTITY** kind:wifi_ap id:1619a021842c n:1 rssi:-64
**ENTITY** kind:wifi_ap id:a62a6f5c42a9 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:942a6f5c42a9 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:9a2a6f5c42a9 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02fdb25ddcab n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02fdb28ddcab n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02fdb22ddcab n:1 rssi:-80
**ENTITY** kind:wifi_ap id:942a6f5c3f11 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:9a2a6f5c3f11 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:a62a6f5c3f11 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:6af0bcbf38c0 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:12b3272f4d48 n:1 rssi:-90
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:99384 stream:0x6223aa03 wall:0 window_ms:60781
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-52 rssi_med:-38 rssi_max:-31
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-54 rssi_max:-45

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:99384 stream:0x6223aa03 wall:0 window_ms:60809 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52925 stream:0x2787c33f wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT101LON0 | sid:42caf4db | created:0 | updated:0 |
**PEER** node:0x00000300 spoke:1 declared:0x3fb7 verified:0x2fa7 exercised:0x0000 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:20 last_ms:56413
t_ms:52865 stream:0x40658fbe wall:0

---

@LAT101LON1 | sid:2665389c | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:59 half_life_ms:600000 reinforced:0 last_ms:1135
t_ms:52865 stream:0x40658fbe wall:0

---

@LAT101LON2 | sid:27653a2f | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:59 half_life_ms:600000 reinforced:0 last_ms:1135
t_ms:52865 stream:0x40658fbe wall:0

---

@LAT101LON3 | sid:29653d55 | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:59 half_life_ms:600000 reinforced:0 last_ms:1135
t_ms:52865 stream:0x40658fbe wall:0

---

@LAT101LON4 | sid:a2622a39 | created:0 | updated:0 |
**PEER** node:0x00000001 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:31 half_life_ms:600000 reinforced:0 last_ms:1135
t_ms:52865 stream:0x40658fbe wall:0

---

@LAT101LON5 | sid:2136c351 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:59 half_life_ms:600000 reinforced:0 last_ms:1135
t_ms:52865 stream:0x40658fbe wall:0

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:52865 stream:0x40658fbe wall:0 window_ms:60760
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-49 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-49 rssi_med:-36 rssi_max:-26

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52865 stream:0x40658fbe wall:0 window_ms:60796 entities:12
**ENTITY** kind:wifi_ap id:903a7213bd78 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:f0b05211bc98 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:441e98272c48 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:441e98272b78 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:f0b05211b988 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:d4c19e3a46c8 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:d4c19e7a46c8 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:441e98272bd8 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:7246e732dfd4 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e0107f2791b8 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:f0b05211b358 n:1 rssi:-84
**ENTITY** kind:wifi_ap id:441e982716d8 n:1 rssi:-84
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:113625 stream:0x40658fbe wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-44 rssi_max:-38

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52428 stream:0x8fd3dab3 wall:0 window_ms:60000 entities:12
**ENTITY** kind:wifi_ap id:441e98272bd8 n:1 rssi:-69
**ENTITY** kind:wifi_ap id:f0b05211bc98 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:7246e732dfd4 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:441e98272c48 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:f0b05211ba48 n:1 rssi:-80
**ENTITY** kind:wifi_ap id:f0b05211bac8 n:1 rssi:-82
**ENTITY** kind:wifi_ap id:f0b05211b988 n:1 rssi:-82
**ENTITY** kind:wifi_ap id:903a7213bd78 n:1 rssi:-82
**ENTITY** kind:wifi_ap id:f0b05211b358 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:441e98272b18 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:d4c19e3a46c8 n:1 rssi:-85
**ENTITY** kind:wifi_ap id:d4c19e7a46c8 n:1 rssi:-85
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:23903301 stream:0x4a194eda wall:0 window_ms:60019 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:24041392 stream:0x4a194eda wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0
