# V4-C Edge Node TTDB

```mmpdb
db_id: v4c-edge-001
db_name: V4-C Edge Node
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: v4c-edge
  role: remote-cluster-gateway
  perspective: spine-tail
  scope: remote-cluster
  constraints:
    - off-grid
    - airtime-scarce
  globe:
    frame: mesh-topology
    origin: "@LAT0LON30"
    mapping: "tail of the A-B-C spine; gateways the off-grid K10 cluster"
cursor_policy:
  max_preview_chars: 256
  max_nodes: 64
typed_edges:
  enabled: true
  syntax: "type@LATxLONy"
librarian:
  enabled: false
  primitive_queries: []
```

```cursor
lat: 0
lon: 30
```

---

@LAT0LON30 | created:1750000000 | updated:1750000000 | relates:navigates_to@LAT0LON20

Edge home. Aggregates the off-grid K10 cluster's percepts and forwards summaries
to V4-B over LoRa.

---


---


---


---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:846755 stream:0xbdc62024 wall:0 node:0x00000012

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:1 removed:16 last_lon:15 t_ms:95098 stream:0x794a3f7d wall:0 node:0x00000012
**STREAMS-EXPLAINED** n:16 0x59fb8ce8 0xbdc62024 0xe7384824 0xaf869fce 0xdffbae31 0xbe8a1293 0xbce80555 0x66486d22 0x95cc309e 0xbeb39900 0x1de72b4d 0x0c8e926c 0xdd4bfb6c 0xd2dacc37 0xbb1177f2 0x7d224c73

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:48 last_lon:47 t_ms:19075 stream:0xbc01f8c3 wall:0 node:0x00000012

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbc01f8c3 wall:0 t_ms:0 node:0x12 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:2 removed:48 last_lon:47 t_ms:34581 stream:0xbc01f8c3 wall:0 node:0x00000012

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:53200 stream:0xbc01f8c3 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x26826178 wall:0 t_ms:0 node:0x12 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52232 stream:0x26826178 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xb23c7677 wall:0 t_ms:14079 node:0x12 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:72809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-59 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-25 rssi_med:-16 rssi_max:-15
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-33 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-80 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-80 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-40 rssi_med:-39 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-52 rssi_med:-46 rssi_max:-36
**LINK** peer:0x00000300 proto:ble n:47 rssi_min:-81 rssi_med:-50 rssi_max:-39

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:72809 stream:0xb23c7677 wall:0 window_ms:60066 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:132810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-17 rssi_med:-16 rssi_max:-16
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-54 rssi_med:-49 rssi_max:-35
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-48 rssi_med:-44 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-49 rssi_med:-25 rssi_max:-23
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-60 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:69 rssi_min:-80 rssi_med:-58 rssi_max:-51

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:192809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-38 rssi_med:-26 rssi_max:-24
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-80 rssi_med:-52 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-38 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-80 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-47 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-18 rssi_med:-17 rssi_max:-16
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-42 rssi_max:-38

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:252809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-30 rssi_med:-26 rssi_max:-24
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-18 rssi_med:-17 rssi_max:-16
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-38 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-42 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-51 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-80 rssi_med:-40 rssi_max:-39

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:312809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-82 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:10 rssi_min:-81 rssi_med:-48 rssi_max:-39
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-18 rssi_med:-17 rssi_max:-16
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-40 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-50 rssi_med:-42 rssi_max:-36
**LINK** peer:0x00000300 proto:espnow n:4 rssi_min:-30 rssi_med:-29 rssi_max:-25
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-56 rssi_med:-48 rssi_max:-41
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-41 rssi_max:-39

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:372809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:68 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-47 rssi_med:-44 rssi_max:-40
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-18 rssi_med:-17 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-42 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-45 rssi_med:-41 rssi_max:-35

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:432810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:2 rssi_min:-56 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-18 rssi_med:-16 rssi_max:-16
**LINK** peer:0x00000010 proto:espnow n:32 rssi_min:-39 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:1 rssi_min:-35 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-42 rssi_max:-41

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:492810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-18 rssi_med:-16 rssi_max:-16
**LINK** peer:0x00000010 proto:espnow n:35 rssi_min:-39 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-42 rssi_max:-41

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:552810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-40 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-45 rssi_max:-42

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:612810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:40 rssi_min:-40 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-45 rssi_max:-43

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:672810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-80 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-40 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-19 rssi_med:-18 rssi_max:-17

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:732810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:33 rssi_min:-40 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-45 rssi_max:-42

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:792810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-40 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-19 rssi_med:-18 rssi_max:-17

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:852810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-40 rssi_med:-37 rssi_max:-35

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:912810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-40 rssi_med:-38 rssi_max:-35

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:972810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:34 rssi_min:-40 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-83 rssi_med:-46 rssi_max:-43

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1032810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:39 rssi_min:-40 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-19 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-46 rssi_max:-42

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1092810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-40 rssi_med:-38 rssi_max:-35

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1152810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-19 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:34 rssi_min:-40 rssi_med:-38 rssi_max:-35

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1212809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-40 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-80 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-20 rssi_med:-18 rssi_max:-18

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1222523 stream:0xb23c7677 wall:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,84a329c78fec
**COVERED** windows:1 entities:8 window_ms:549648 first_t_ms:622523 last_t_ms:622523 covered_by:@LAT96LON2
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95 windows:1

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1272810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-40 rssi_med:-39 rssi_max:-35

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1332810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-40 rssi_med:-39 rssi_max:-35

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1392809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:32 rssi_min:-40 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-45 rssi_max:-43

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1452810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:71 rssi_min:-81 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:33 rssi_min:-40 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-19 rssi_med:-18 rssi_max:-18

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1512810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-40 rssi_med:-39 rssi_max:-35

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1572810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:33 rssi_min:-40 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-20 rssi_med:-18 rssi_max:-18

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1632810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:33 rssi_min:-40 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-45 rssi_max:-43

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1692810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-40 rssi_med:-39 rssi_max:-35

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1752810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:32 rssi_min:-41 rssi_med:-38 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-19 rssi_med:-18 rssi_max:-18

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1812810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:36 rssi_min:-40 rssi_med:-38 rssi_max:-35

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1822523 stream:0xb23c7677 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,84a329c78fec,18a5ffbae2d6,7236bc441422,e6b32d2cea8b

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1872810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-40 rssi_med:-39 rssi_max:-35

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1932809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-40 rssi_med:-39 rssi_max:-35

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1992809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-80 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:34 rssi_min:-40 rssi_med:-39 rssi_max:-35

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2052810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-40 rssi_med:-38 rssi_max:-35

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2112810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-20 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-40 rssi_med:-38 rssi_max:-35

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2172810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:34 rssi_min:-40 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-20 rssi_med:-18 rssi_max:-18

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2232810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:37 rssi_min:-40 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-82 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-19 rssi_med:-18 rssi_max:-17

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2292809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-82 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-18 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:36 rssi_min:-40 rssi_med:-38 rssi_max:-35

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2352810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:37 rssi_min:-40 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-44 rssi_max:-43

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2412810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:38 rssi_min:-40 rssi_med:-39 rssi_max:-35

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2422523 stream:0xb23c7677 wall:0 window_ms:600001 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,84a329c78fec,5ce28c488e0c,18a5ffbae2d6,7236bc441422

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2472810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-19 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-40 rssi_med:-38 rssi_max:-35

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2532810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-82 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-40 rssi_med:-36 rssi_max:-35

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2592810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-40 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000300 proto:ble n:46 rssi_min:-81 rssi_med:-38 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:18 rssi_min:-43 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000200 proto:espnow n:12 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:29 rssi_min:-79 rssi_med:-54 rssi_max:-51

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2652809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-39 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-19 rssi_med:-18 rssi_max:-17

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2712809 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-39 rssi_med:-35 rssi_max:-34

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2772810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:34 rssi_min:-39 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-42 rssi_max:-42

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2832810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:37 rssi_min:-39 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-19 rssi_med:-18 rssi_max:-17

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2892810 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-82 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-39 rssi_med:-37 rssi_max:-34

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3022523 stream:0xb23c7677 wall:0 window_ms:599999 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,84a329c78fec,18a5ffbae2d6

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4822522 stream:0xb23c7677 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-92
**RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,18a5ffbae2d6
**COVERED** windows:2 entities:8 window_ms:1200000 first_t_ms:3622523 last_t_ms:4222523 covered_by:@LAT96LON6
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-30 windows:2
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-71 windows:2
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:2 rssi:-91 windows:2
**COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94 windows:1
**COVERED-ENTITY** kind:wifi_ap id:acdf9f4ca21c n:2 rssi:-94 windows:2
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6622523 stream:0xb23c7677 wall:0 window_ms:599999 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,18a5ffbae2d6,7236bc441422
**COVERED** windows:2 entities:8 window_ms:1200001 first_t_ms:5422523 last_t_ms:6022524 covered_by:@LAT96LON7
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-29 windows:2
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-68 windows:2
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-83 windows:2
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-83 windows:2
**COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:2 rssi:-90 windows:2
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:2 rssi:-89 windows:2
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7222523 stream:0xb23c7677 wall:0 window_ms:600000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-97
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,84a329c78fec,7236bc441422,18a5ffbae2d6

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x5b53f35b wall:0 t_ms:19182 node:0x12 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:78043 stream:0x5b53f35b wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xdcd3edce wall:0 t_ms:8235520 node:0x12 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xdcd3edce wall:0 t_ms:8314867 node:0x12 from:0x300
**REMAP** prev_stream:0x1420f15c prev_t_ms:3464 offset_ms:8311403 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8364635 stream:0xdcd3edce wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-23
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xee98fca8 wall:0 t_ms:4459929 node:0x12 from:0x11
**REMAP** prev_stream:0x8aaab6fc prev_t_ms:3704 offset_ms:4456225 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4509452 stream:0xee98fca8 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5659221 stream:0xee98fca8 wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec
**COVERED** windows:1 entities:9 window_ms:549770 first_t_ms:5059221 last_t_ms:5059221 covered_by:@LAT96LON12
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-96 windows:1

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6259221 stream:0xee98fca8 wall:0 window_ms:600000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
**CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689,c2e94427adcf,84a329c78fec

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xc909d5a8 wall:0 t_ms:138646 node:0x12 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xc909d5a8 wall:0 t_ms:3488980 node:0x12 from:0x300
**REMAP** prev_stream:0x4a8164a3 prev_t_ms:3185 offset_ms:3485795 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled
