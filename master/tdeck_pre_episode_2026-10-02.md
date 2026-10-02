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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:24183021 stream:0x4a194eda wall:0 window_ms:60024
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-50 rssi_med:-47 rssi_max:-44

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:24183021 stream:0x4a194eda wall:0 window_ms:60049 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:24243045 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-49 rssi_med:-48 rssi_max:-46

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:24303045 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-54 rssi_med:-48 rssi_max:-46

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:24363072 stream:0x4a194eda wall:0 window_ms:60028
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-55 rssi_med:-48 rssi_max:-43

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:24423073 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-51 rssi_med:-45 rssi_max:-45

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:24483073 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-47 rssi_med:-45 rssi_max:-43

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:24543073 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-48 rssi_med:-45 rssi_max:-44

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:24603073 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-48 rssi_med:-46 rssi_max:-43

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x642cef6b wall:0 t_ms:0 node:0x200 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:52627 stream:0x642cef6b wall:0 window_ms:60223
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-59 rssi_med:-50 rssi_max:-47
**LINK** peer:0x00000100 proto:espnow n:22 rssi_min:-37 rssi_med:-36 rssi_max:-30
**LINK** peer:0x00000010 proto:ble n:11 rssi_min:-70 rssi_med:-62 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:4 rssi_min:-48 rssi_med:-48 rssi_max:-48

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52627 stream:0x642cef6b wall:0 window_ms:60241 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:112850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-36 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-63 rssi_max:-55
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:39 rssi_min:-57 rssi_med:-51 rssi_max:-46

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:172850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-66 rssi_max:-59
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-32 rssi_med:-31 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:36 rssi_min:-52 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-49 rssi_max:-46

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:232850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:44 rssi_min:-52 rssi_med:-51 rssi_max:-51
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-33 rssi_med:-31 rssi_max:-31
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-79 rssi_med:-66 rssi_max:-59
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-49 rssi_max:-46

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:292850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-32 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000010 proto:espnow n:39 rssi_min:-52 rssi_med:-51 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-79 rssi_med:-66 rssi_max:-58

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:352850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-31 rssi_med:-30 rssi_max:-27
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-65 rssi_max:-59
**LINK** peer:0x00000010 proto:espnow n:35 rssi_min:-52 rssi_med:-51 rssi_max:-46

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:412850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-38 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:71 rssi_min:-81 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-52 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-49 rssi_max:-45

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:472850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-37 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:39 rssi_min:-50 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:16 rssi_min:-34 rssi_med:-33 rssi_max:-31

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:532850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-64 rssi_max:-57
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-38 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-40 rssi_med:-33 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-54 rssi_med:-47 rssi_max:-45

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:592850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-63 rssi_max:-59
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-38 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-53 rssi_max:-46
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-45 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-50 rssi_med:-48 rssi_max:-45

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:603591 stream:0x642cef6b wall:0 window_ms:550723 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:652850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-40 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-51 rssi_max:-45
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-38 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-50 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-63 rssi_max:-56

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:712850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-37 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-40 rssi_med:-33 rssi_max:-31
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-61 rssi_max:-57
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-51 rssi_med:-48 rssi_max:-45

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:772850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-82 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-37 rssi_med:-34 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-51 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-48 rssi_max:-45

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:832850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-37 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-35 rssi_med:-33 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:69 rssi_min:-80 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-64 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-55 rssi_med:-47 rssi_max:-44

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:892850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-37 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-63 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:5 rssi_min:-33 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-54 rssi_med:-48 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-73 rssi_med:-53 rssi_max:-46

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:952850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-69 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-62 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-36 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-52 rssi_med:-48 rssi_max:-43

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1012850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-37 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-50 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-63 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-49 rssi_med:-47 rssi_max:-44

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1072850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-37 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-64 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-49 rssi_max:-44

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1132850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-79 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000010 proto:espnow n:41 rssi_min:-48 rssi_med:-47 rssi_max:-43

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1192850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-63 rssi_max:-59
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-79 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:32 rssi_min:-48 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-37 rssi_med:-33 rssi_max:-33

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1203590 stream:0x642cef6b wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,64677217947d

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1252850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-36 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-61 rssi_max:-58
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-82 rssi_med:-50 rssi_max:-46
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-47 rssi_med:-45 rssi_max:-44

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1312850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-37 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:70 rssi_min:-81 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-61 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-48 rssi_med:-45 rssi_max:-43

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1372850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-60 rssi_max:-56
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-38 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-47 rssi_max:-44

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1432850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-38 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-63 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-61 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-48 rssi_med:-45 rssi_max:-43

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1492850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-64 rssi_med:-51 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-71 rssi_med:-64 rssi_max:-59

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1552850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-62 rssi_max:-56
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-80 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-49 rssi_med:-46 rssi_max:-44

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1612850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-38 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-80 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:35 rssi_min:-47 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-58 rssi_med:-46 rssi_max:-45

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1672850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-47 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-36 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-46 rssi_max:-44

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1732850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000010 proto:espnow n:34 rssi_min:-46 rssi_med:-45 rssi_max:-44

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1792850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-79 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:36 rssi_min:-48 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:48 rssi_min:-81 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:4 rssi_min:-31 rssi_med:-31 rssi_max:-30

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1803589 stream:0x642cef6b wall:0 window_ms:599999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:4
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1852850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-68 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-37 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-51 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:50 rssi_min:-80 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-33 rssi_med:-30 rssi_max:-29

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1912850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-38 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-80 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-33 rssi_med:-31 rssi_max:-29
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-49 rssi_med:-45 rssi_max:-44

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1972850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-36 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:9 rssi_min:-34 rssi_med:-31 rssi_max:-29
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-49 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-85 rssi_med:-47 rssi_max:-45

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2032850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-37 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-67 rssi_med:-62 rssi_max:-56
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-67 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-50 rssi_med:-46 rssi_max:-44

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2092850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-47 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-35 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-51 rssi_med:-45 rssi_max:-44

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2152850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-81 rssi_med:-61 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:32 rssi_min:-48 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-47 rssi_max:-44

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2212850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-80 rssi_med:-61 rssi_max:-56
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-37 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-52 rssi_med:-46 rssi_max:-42

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2272850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-37 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-79 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-51 rssi_med:-47 rssi_max:-41

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2332850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-79 rssi_med:-64 rssi_max:-57
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-38 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-57 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:34 rssi_min:-59 rssi_med:-46 rssi_max:-43

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2392850 stream:0x642cef6b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-79 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-34 rssi_med:-32 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-47 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-33 rssi_med:-33 rssi_max:-32

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2403588 stream:0x642cef6b wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,5ce28c488e0c,e6b32d2cea8b,64677217947d

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3138114 stream:0x642cef6b wall:0 window_ms:60009 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---


---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3688177 stream:0x642cef6b wall:0 window_ms:550059 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4288177 stream:0x642cef6b wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b

---


---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4888178 stream:0x642cef6b wall:0 window_ms:600001 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:4
**CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,aef9ff2626ac,64677217947d,5ce28c488e0c,84a329c78fec

---


---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5488178 stream:0x642cef6b wall:0 window_ms:599999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-96
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,64677217947d,aef9ff2626ac,5ce28c488e0c,84a329c78fec

---


---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6148709 stream:0x642cef6b wall:0 window_ms:60006 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---


---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6699112 stream:0x642cef6b wall:0 window_ms:550409 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---


---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7299268 stream:0x642cef6b wall:0 window_ms:600151 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
**ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-97
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b

---


---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7899323 stream:0x642cef6b wall:0 window_ms:600055 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-96
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:4
**CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8499323 stream:0x642cef6b wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,64677217947d,0283cce0e689,e6b32d2cea8b

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xdcd3edce wall:0 t_ms:4096451 node:0x200 from:0x10
**REMAP** prev_stream:0x3a2f6a8c prev_t_ms:5524 offset_ms:4090927 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4143520 stream:0xdcd3edce wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4694479 stream:0xdcd3edce wall:0 window_ms:550960 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5294479 stream:0xdcd3edce wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace

---


---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5894490 stream:0xdcd3edce wall:0 window_ms:600011 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:4
**CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6552655 stream:0xdcd3edce wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7103851 stream:0xdcd3edce wall:0 window_ms:551197 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-52
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7703902 stream:0xdcd3edce wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-84
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-98
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8060552 stream:0xdcd3edce wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xee98fca8 wall:0 t_ms:58252 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:115789 stream:0xee98fca8 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---


---


---


---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1266775 stream:0xee98fca8 wall:0 window_ms:600013 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b
**COVERED** windows:1 entities:8 window_ms:550974 first_t_ms:666762 last_t_ms:666762 covered_by:@LAT96LON24
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96 windows:1

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1866771 stream:0xee98fca8 wall:0 window_ms:599996 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
**CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,e6b32d2cea8b,02c57d2e0f0d,5ce28c488e0c

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2466779 stream:0xee98fca8 wall:0 window_ms:600008 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,5ce28c488e0c,84a329c78fec

---


---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4503823 stream:0xee98fca8 wall:0 window_ms:60707 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6800421 stream:0xee98fca8 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-52
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x88023c58 wall:0 t_ms:12012426 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12070722 stream:0x88023c58 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x92fb56ae wall:0 t_ms:209090 node:0x200 from:0x300
**REMAP** prev_stream:0x15eea3ed prev_t_ms:5359 offset_ms:203731 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:256288 stream:0x92fb56ae wall:0 window_ms:60757 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1407250 stream:0x92fb56ae wall:0 window_ms:600001 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-96
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689
**COVERED** windows:1 entities:9 window_ms:550205 first_t_ms:807249 last_t_ms:807249 covered_by:@LAT96LON31
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92 windows:1
**COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96 windows:1

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2007250 stream:0x92fb56ae wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
**CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3207250 stream:0x92fb56ae wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,0283cce0e689,64677217947d,e6b32d2cea8b,aef9ff2626ac
**COVERED** windows:1 entities:8 window_ms:600000 first_t_ms:2607250 last_t_ms:2607250 covered_by:@LAT96LON33
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92 windows:1
**COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-96 windows:1

---


---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5007250 stream:0x92fb56ae wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689,5ce28c488e0c
**COVERED** windows:2 entities:8 window_ms:1200000 first_t_ms:3807250 last_t_ms:4407250 covered_by:@LAT96LON34
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-45 windows:2
**COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-72 windows:2
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-75 windows:2
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-85 windows:2
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-90 windows:2
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-89 windows:2
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-91 windows:2

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6207250 stream:0x92fb56ae wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,84a329c78fec,e6b32d2cea8b,0283cce0e689,64677217947d
**COVERED** windows:1 entities:8 window_ms:600000 first_t_ms:5607250 last_t_ms:5607250 covered_by:@LAT96LON35
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1

---


---


---


---


---


---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9807250 stream:0x92fb56ae wall:0 window_ms:600001 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,64677217947d,0283cce0e689,e6b32d2cea8b
**COVERED** windows:5 entities:9 window_ms:2999999 first_t_ms:6807250 last_t_ms:9207249 covered_by:@LAT96LON36
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-41 windows:5
**COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-72 windows:5
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-73 windows:5
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-82 windows:5
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-88 windows:4
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:3 rssi:-89 windows:3
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-92 windows:4
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:5 rssi:-91 windows:5

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10407249 stream:0x92fb56ae wall:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,0283cce0e689,e6b32d2cea8b

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11007250 stream:0x92fb56ae wall:0 window_ms:600001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,5ce28c488e0c,0283cce0e689

---


---


---


---


---

@LAT101LON0 | sid:2136c351 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:1443
t_ms:12465738 stream:0x92fb56ae wall:0

---

@LAT101LON1 | sid:27653a2f | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:147 last_ms:12268279
t_ms:12465738 stream:0x92fb56ae wall:0

---

@LAT101LON2 | sid:42caf4db | created:0 | updated:0 |
**PEER** node:0x00000300 spoke:1 declared:0x3fb7 verified:0x2fb7 exercised:0x0015 cap_epoch:9
**TRACE** copresence:255 half_life_ms:600000 reinforced:28 last_ms:12269399
t_ms:12465738 stream:0x92fb56ae wall:0

---

@LAT101LON3 | sid:2665389c | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:1443
t_ms:12465738 stream:0x92fb56ae wall:0

---

@LAT101LON4 | sid:29653d55 | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:1443
t_ms:12465738 stream:0x92fb56ae wall:0

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xc909d5a8 wall:0 t_ms:335076 node:0x200 from:0x11
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:392506 stream:0xc909d5a8 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5768637 stream:0xc909d5a8 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0
