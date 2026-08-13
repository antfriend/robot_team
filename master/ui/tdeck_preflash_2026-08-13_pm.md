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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45776322 stream:0xbb1177f2 wall:0 window_ms:76141
**LINK** peer:0x00000011 proto:espnow n:31 rssi_min:-78 rssi_med:-77 rssi_max:-76
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-93 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-50 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-44 rssi_med:-43 rssi_max:-41

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

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45850631 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-94 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-78 rssi_med:-77 rssi_max:-76
**LINK** peer:0x00000300 proto:espnow n:56 rssi_min:-26 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-43 rssi_max:-42

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45910404 stream:0xbb1177f2 wall:0 window_ms:61780
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-26 rssi_med:-26 rssi_max:-26
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-78 rssi_med:-78 rssi_max:-76
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-93 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-79 rssi_med:-43 rssi_max:-42

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45974320 stream:0xbb1177f2 wall:0 window_ms:63915
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-36 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-94 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-28 rssi_med:-28 rssi_max:-28

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46034321 stream:0xbb1177f2 wall:0 window_ms:60002
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-50 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-95 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-78 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000010 proto:ble n:75 rssi_min:-80 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-35 rssi_med:-33 rssi_max:-33

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46095955 stream:0xbb1177f2 wall:0 window_ms:61635
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-94 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-79 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000300 proto:ble n:69 rssi_min:-51 rssi_med:-42 rssi_max:-38

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46156238 stream:0xbb1177f2 wall:0 window_ms:60281
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-94 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-29 rssi_med:-28 rssi_max:-28

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46218317 stream:0xbb1177f2 wall:0 window_ms:60080
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-70 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-94 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-51 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-78 rssi_med:-77 rssi_max:-77

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46278970 stream:0xbb1177f2 wall:0 window_ms:62652
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-80 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-50 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-93 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-27 rssi_med:-26 rssi_max:-25

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46342235 stream:0xbb1177f2 wall:0 window_ms:61266
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-93 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-78 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-79 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-29 rssi_med:-28 rssi_max:-28

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

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46402242 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-26 rssi_med:-26 rssi_max:-26
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-94 rssi_med:-87 rssi_max:-83
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-28 rssi_med:-28 rssi_max:-28

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46462242 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-93 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-79 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-26 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-29 rssi_med:-28 rssi_max:-28

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46522242 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-78 rssi_med:-77 rssi_max:-76
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-94 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-36 rssi_med:-35 rssi_max:-33

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46582242 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-94 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-78 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-42 rssi_max:-39

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46642242 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-79 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:19 rssi_min:-26 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-94 rssi_med:-87 rssi_max:-83

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46702242 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-94 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-78 rssi_med:-77 rssi_max:-77

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46762242 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-95 rssi_med:-87 rssi_max:-83
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-36 rssi_med:-33 rssi_max:-33

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46820770 stream:0xbb1177f2 wall:0 window_ms:62696
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-81 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-94 rssi_med:-87 rssi_max:-83
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000300 proto:espnow n:3 rssi_min:-26 rssi_med:-26 rssi_max:-26

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46882771 stream:0xbb1177f2 wall:0 window_ms:60130
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-81 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-28 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-93 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-27 rssi_med:-26 rssi_max:-25

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46945068 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-78 rssi_med:-77 rssi_max:-76
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:48 rssi_min:-94 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-71 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-29 rssi_med:-28 rssi_max:-28

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

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47005074 stream:0xbb1177f2 wall:0 window_ms:60006
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-26 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-93 rssi_med:-87 rssi_max:-82
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:27 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-79 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-81 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-28 rssi_med:-28 rssi_max:-28

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47065098 stream:0xbb1177f2 wall:0 window_ms:60025
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-79 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-94 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-28 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-79 rssi_med:-42 rssi_max:-38

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47125100 stream:0xbb1177f2 wall:0 window_ms:60001
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-27 rssi_med:-26 rssi_max:-26
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-51 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-78 rssi_med:-77 rssi_max:-76
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-94 rssi_med:-87 rssi_max:-83

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47182770 stream:0xbb1177f2 wall:0 window_ms:60058
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-94 rssi_med:-87 rssi_max:-84
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-27 rssi_med:-26 rssi_max:-26
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-30 rssi_med:-28 rssi_max:-28

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47245167 stream:0xbb1177f2 wall:0 window_ms:60009
**LINK** peer:0x00000300 proto:ble n:74 rssi_min:-80 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-80 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-30 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-94 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-27 rssi_med:-26 rssi_max:-26
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-78 rssi_med:-77 rssi_max:-77

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47305169 stream:0xbb1177f2 wall:0 window_ms:60002
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-82 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-26 rssi_med:-26 rssi_max:-26
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-94 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-35 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-29 rssi_med:-28 rssi_max:-28

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47365188 stream:0xbb1177f2 wall:0 window_ms:60019
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-94 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-67 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-51 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-29 rssi_med:-28 rssi_max:-28

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47422771 stream:0xbb1177f2 wall:0 window_ms:60507
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-79 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:11 rssi_min:-26 rssi_med:-26 rssi_max:-26
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-94 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-51 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-78 rssi_med:-77 rssi_max:-76
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-36 rssi_med:-33 rssi_max:-33

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47482771 stream:0xbb1177f2 wall:0 window_ms:60120
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-94 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-78 rssi_med:-77 rssi_max:-77
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-50 rssi_med:-42 rssi_max:-38

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47545859 stream:0xbb1177f2 wall:0 window_ms:60051
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-93 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-78 rssi_med:-77 rssi_max:-77

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

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47605920 stream:0xbb1177f2 wall:0 window_ms:60061
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-36 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-80 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-50 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-93 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000011 proto:espnow n:13 rssi_min:-78 rssi_med:-77 rssi_max:-76
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-29 rssi_med:-28 rssi_max:-28

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47665940 stream:0xbb1177f2 wall:0 window_ms:60020
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-94 rssi_med:-87 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-28 rssi_med:-28 rssi_max:-27
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-78 rssi_med:-77 rssi_max:-75

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47725962 stream:0xbb1177f2 wall:0 window_ms:60020
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-98 rssi_med:-87 rssi_max:-82
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-46 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-79 rssi_med:-78 rssi_max:-76
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-29 rssi_med:-28 rssi_max:-28

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47782771 stream:0xbb1177f2 wall:0 window_ms:60006
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-37 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-52 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-95 rssi_med:-90 rssi_max:-81
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-32 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-80 rssi_med:-78 rssi_max:-72

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47845973 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-37 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000011 proto:ble n:33 rssi_min:-96 rssi_med:-88 rssi_max:-84
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-81 rssi_med:-79 rssi_max:-73
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-31 rssi_med:-30 rssi_max:-29

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47905973 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000011 proto:ble n:41 rssi_min:-96 rssi_med:-88 rssi_max:-87
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-50 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-31 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-81 rssi_med:-79 rssi_max:-77

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:47965973 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-37 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-79 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-31 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-82 rssi_med:-79 rssi_max:-78
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-100 rssi_med:-87 rssi_max:-84

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:48121992 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-83 rssi_med:-80 rssi_max:-74
**LINK** peer:0x00000010 proto:espnow n:34 rssi_min:-30 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-82 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-49 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-97 rssi_med:-87 rssi_max:-83

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

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:48181993 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-37 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-99 rssi_med:-88 rssi_max:-85
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-82 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-29 rssi_med:-28 rssi_max:-28

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:48241993 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-36 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-49 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:38 rssi_min:-99 rssi_med:-86 rssi_max:-85
**LINK** peer:0x00000011 proto:espnow n:13 rssi_min:-81 rssi_med:-81 rssi_max:-80

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:48301993 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-100 rssi_med:-88 rssi_max:-85
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-80 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-81 rssi_med:-81 rssi_max:-80

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:48361993 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-82 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000011 proto:ble n:36 rssi_min:-100 rssi_med:-88 rssi_max:-85
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-30 rssi_med:-28 rssi_max:-28

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:48421993 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-36 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:38 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-100 rssi_med:-88 rssi_max:-85
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-82 rssi_med:-81 rssi_max:-80

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:48481993 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-36 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:35 rssi_min:-99 rssi_med:-88 rssi_max:-85
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-82 rssi_med:-81 rssi_max:-81
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-30 rssi_med:-28 rssi_max:-28

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:48541993 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-36 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:33 rssi_min:-100 rssi_med:-86 rssi_max:-85
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-82 rssi_med:-81 rssi_max:-81

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:48601993 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:38 rssi_min:-100 rssi_med:-88 rssi_max:-85
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-37 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-79 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-82 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-29 rssi_med:-28 rssi_max:-28

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:48661992 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:70 rssi_min:-82 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:36 rssi_min:-99 rssi_med:-86 rssi_max:-85
**LINK** peer:0x00000010 proto:espnow n:35 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-82 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000300 proto:espnow n:9 rssi_min:-26 rssi_med:-25 rssi_max:-25

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

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:48721993 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-26 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-80 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-82 rssi_med:-81 rssi_max:-81
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:41 rssi_min:-100 rssi_med:-88 rssi_max:-85

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

@LAT101LON0 | sid:42caf4db | created:0 | updated:0 |
**PEER** node:0x00000300 spoke:1 declared:0x3fb7 verified:0x2fb7 exercised:0x0014 cap_epoch:8
**TRACE** copresence:255 half_life_ms:600000 reinforced:44 last_ms:59738
t_ms:51543921 stream:0xbb1177f2 wall:0

---

@LAT101LON1 | sid:2665389c | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:22 last_ms:59738
t_ms:51543921 stream:0xbb1177f2 wall:0

---

@LAT101LON2 | sid:27653a2f | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:13 last_ms:56212
t_ms:51543921 stream:0xbb1177f2 wall:0

---

@LAT101LON3 | sid:29653d55 | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:51543921 stream:0xbb1177f2 wall:0

---

@LAT101LON4 | sid:a2622a39 | created:0 | updated:0 |
**PEER** node:0x00000001 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:53 half_life_ms:600000 reinforced:0 last_ms:1118
t_ms:51543921 stream:0xbb1177f2 wall:0

---

@LAT101LON5 | sid:2136c351 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:50 last_ms:59257
t_ms:51543921 stream:0xbb1177f2 wall:0

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
