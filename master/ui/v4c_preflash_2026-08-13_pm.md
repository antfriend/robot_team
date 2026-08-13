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

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x59fb8ce8 wall:0 t_ms:4048832 node:0x12 from:0x11
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7579622 stream:0x59fb8ce8 wall:0 window_ms:62017 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8133345 stream:0x59fb8ce8 wall:0 window_ms:551707 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8733345 stream:0x59fb8ce8 wall:0 window_ms:599999 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9333345 stream:0x59fb8ce8 wall:0 window_ms:600001 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9933345 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10533345 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11133345 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11733345 stream:0x59fb8ce8 wall:0 window_ms:599999 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12333345 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12933345 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13533345 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbdc62024 wall:0 t_ms:609285 node:0x12 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:667955 stream:0xbdc62024 wall:0 window_ms:60006 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:778618 stream:0xbdc62024 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:846755 stream:0xbdc62024 wall:0 node:0x00000012

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:910246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-32 rssi_med:-27 rssi_max:-25
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-64 rssi_med:-52 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-70 rssi_med:-51 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-46 rssi_med:-30 rssi_max:-27
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-56 rssi_med:-45 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-60 rssi_max:-49
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-44 rssi_max:-37
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-81 rssi_med:-65 rssi_max:-53

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:910246 stream:0xbdc62024 wall:0 window_ms:62107 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:970246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-80 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-56 rssi_med:-46 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-58 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-42 rssi_med:-29 rssi_max:-27
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-63 rssi_max:-54
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-80 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-31 rssi_med:-28 rssi_max:-25
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-61 rssi_med:-50 rssi_max:-44

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1030246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:65 rssi_min:-31 rssi_med:-27 rssi_max:-25
**LINK** peer:0x00000011 proto:ble n:68 rssi_min:-81 rssi_med:-47 rssi_max:-41
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-62 rssi_med:-47 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-56 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-60 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-62 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-50 rssi_med:-30 rssi_max:-27

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1090246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-54 rssi_med:-46 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-27 rssi_med:-26 rssi_max:-23
**LINK** peer:0x00000300 proto:ble n:69 rssi_min:-81 rssi_med:-41 rssi_max:-37
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-81 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-58 rssi_med:-51 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-52 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-62 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-54 rssi_max:-41

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1150246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-41 rssi_max:-36
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-60 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-29 rssi_med:-25 rssi_max:-23
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-63 rssi_med:-45 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-58 rssi_med:-51 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-38 rssi_med:-28 rssi_max:-25

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1210245 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-83 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-45 rssi_max:-39
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-54 rssi_med:-51 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-39 rssi_med:-28 rssi_max:-27
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-45 rssi_med:-28 rssi_max:-21
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-47 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-67 rssi_med:-50 rssi_max:-47

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1270246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-53 rssi_med:-42 rssi_max:-32
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-58 rssi_med:-46 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-79 rssi_med:-60 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-45 rssi_max:-40
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-55 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-55 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-54 rssi_med:-43 rssi_max:-33
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-43 rssi_med:-29 rssi_max:-24

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1330245 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-55 rssi_med:-37 rssi_max:-19
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-59 rssi_max:-47
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-69 rssi_med:-53 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-65 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-64 rssi_med:-46 rssi_max:-40
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-62 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-80 rssi_med:-58 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-81 rssi_med:-51 rssi_max:-37

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1390246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-51 rssi_med:-40 rssi_max:-35
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-55 rssi_max:-49
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-80 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-50 rssi_med:-42 rssi_max:-35
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-44 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000011 proto:espnow n:13 rssi_min:-19 rssi_med:-19 rssi_max:-17

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1450246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-19 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-44 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-44 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-40 rssi_med:-38 rssi_max:-35
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-80 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-79 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-50 rssi_max:-48

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1461975 stream:0xbdc62024 wall:0 window_ms:549623 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1510246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-20 rssi_med:-17 rssi_max:-17
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-49 rssi_med:-44 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-83 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-59 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-46 rssi_med:-44 rssi_max:-39
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-42 rssi_med:-40 rssi_max:-35

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1570246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-79 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-22 rssi_med:-19 rssi_max:-17
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-45 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-52 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-42 rssi_med:-40 rssi_max:-39

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1630246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000010 proto:ble n:21 rssi_min:-76 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-52 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-54 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-19 rssi_med:-18 rssi_max:-16
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:10 rssi_min:-51 rssi_med:-45 rssi_max:-42

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1690246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:5 rssi_min:-46 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-20 rssi_med:-19 rssi_max:-17
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-81 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000300 proto:ble n:18 rssi_min:-69 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-44 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-83 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-43 rssi_med:-41 rssi_max:-40

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1750246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-41 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-43 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-20 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:5 rssi_min:-46 rssi_med:-46 rssi_max:-45

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1810246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-84 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-20 rssi_med:-19 rssi_max:-17
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-51 rssi_med:-46 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-46 rssi_med:-41 rssi_max:-36
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-45 rssi_med:-41 rssi_max:-40

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1870246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-47 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:71 rssi_min:-81 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-46 rssi_med:-45 rssi_max:-35
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-47 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-19 rssi_med:-18 rssi_max:-17

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1930246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-20 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-46 rssi_med:-45 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-55 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-46 rssi_med:-43 rssi_max:-41

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1990246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-82 rssi_med:-59 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-21 rssi_med:-19 rssi_max:-17
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-46 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-56 rssi_med:-51 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-55 rssi_med:-45 rssi_max:-40

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2050246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-60 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-48 rssi_med:-40 rssi_max:-32
**LINK** peer:0x00000200 proto:ble n:69 rssi_min:-81 rssi_med:-53 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-47 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-21 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-59 rssi_med:-52 rssi_max:-43

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2061976 stream:0xbdc62024 wall:0 window_ms:600001 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2110246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-20 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-86 rssi_med:-48 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-82 rssi_med:-52 rssi_max:-48
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-83 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-80 rssi_med:-50 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-40 rssi_med:-38 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-52 rssi_med:-40 rssi_max:-36

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2170246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-88 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-53 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-59 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-46 rssi_med:-44 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-19 rssi_med:-17 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-57 rssi_med:-46 rssi_max:-41

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2230246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-53 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-61 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-59 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-21 rssi_med:-19 rssi_max:-16
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-60 rssi_med:-47 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-46 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-49

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2290246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-60 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-46 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-46 rssi_med:-45 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-45 rssi_med:-43 rssi_max:-36
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-80 rssi_med:-55 rssi_max:-52

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2350246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-20 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-48 rssi_med:-46 rssi_max:-46
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-48 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-47 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-55 rssi_max:-53

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2410246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-46 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-20 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-48 rssi_med:-46 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-46 rssi_med:-45 rssi_max:-45

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2470246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-20 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-79 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-81 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-48 rssi_med:-46 rssi_max:-46
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-46 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-47 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000300 proto:ble n:49 rssi_min:-80 rssi_med:-55 rssi_max:-53

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2530246 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:68 rssi_min:-81 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-20 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-47 rssi_med:-47 rssi_max:-46

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2590277 stream:0xbdc62024 wall:0 window_ms:60031
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-46 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:72 rssi_min:-81 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-20 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-48 rssi_med:-46 rssi_max:-46
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-80 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-47 rssi_med:-45 rssi_max:-45

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2650290 stream:0xbdc62024 wall:0 window_ms:60013
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-20 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-82 rssi_med:-61 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-82 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-47 rssi_med:-46 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-46 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-46 rssi_med:-45 rssi_max:-45

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2661976 stream:0xbdc62024 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2710307 stream:0xbdc62024 wall:0 window_ms:60017
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-20 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-46 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-80 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-48 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-46 rssi_med:-45 rssi_max:-45

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2770307 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-20 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-58 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-47 rssi_med:-46 rssi_max:-46
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000300 proto:ble n:49 rssi_min:-81 rssi_med:-54 rssi_max:-53

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2830319 stream:0xbdc62024 wall:0 window_ms:60012
**LINK** peer:0x00000011 proto:ble n:67 rssi_min:-80 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-19 rssi_med:-19 rssi_max:-17
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-46 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-49 rssi_med:-45 rssi_max:-40
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-79 rssi_med:-59 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-59 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-56 rssi_max:-52

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2890343 stream:0xbdc62024 wall:0 window_ms:60024
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-19 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-47 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-46 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-59 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-45 rssi_med:-41 rssi_max:-40

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2950343 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-20 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-46 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-43 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-51 rssi_med:-44 rssi_max:-41

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3010342 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-52 rssi_med:-40 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-50 rssi_med:-44 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-47 rssi_med:-42 rssi_max:-35
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-20 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-57 rssi_max:-51

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3070343 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-64 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-21 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:74 rssi_min:-80 rssi_med:-60 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-79 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-83 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-45 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-52 rssi_med:-47 rssi_max:-39
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-47 rssi_med:-41 rssi_max:-39

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3130343 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-46 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-81 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:4 rssi_min:-47 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-45 rssi_med:-42 rssi_max:-39

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3190343 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-20 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-46 rssi_med:-44 rssi_max:-36
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-45 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-55 rssi_max:-50

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3250343 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-20 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-82 rssi_med:-58 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-47 rssi_med:-46 rssi_max:-44

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3261975 stream:0xbdc62024 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3310343 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-20 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-45 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-57 rssi_med:-47 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-62 rssi_max:-51

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3370342 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000300 proto:ble n:50 rssi_min:-81 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-81 rssi_med:-60 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-53 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-46 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-80 rssi_med:-35 rssi_max:-33

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3430343 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-45 rssi_med:-41 rssi_max:-37
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-55 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-49 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-80 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-19 rssi_med:-18 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-81 rssi_med:-57 rssi_max:-51

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3490343 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-21 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-61 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-45 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-45 rssi_med:-43 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-55 rssi_max:-50

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3550343 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-80 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-59 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-79 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-55 rssi_max:-49
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-51 rssi_med:-48 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-20 rssi_med:-20 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-52 rssi_med:-44 rssi_max:-41

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3610343 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-47 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-20 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-50 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-61 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-53 rssi_max:-48

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3670342 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-83 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-52 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-80 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-20 rssi_med:-20 rssi_max:-18
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-47 rssi_med:-44 rssi_max:-39

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3730343 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:70 rssi_min:-81 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-19 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-44 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-81 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-50 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-61 rssi_max:-52

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3861975 stream:0xbdc62024 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4461975 stream:0xbdc62024 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5061976 stream:0xbdc62024 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5661975 stream:0xbdc62024 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xe7384824 wall:0 t_ms:220578 node:0x12 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:279472 stream:0xe7384824 wall:0 window_ms:60006 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:829255 stream:0xe7384824 wall:0 window_ms:549784 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1429255 stream:0xe7384824 wall:0 window_ms:599999 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2029255 stream:0xe7384824 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2629255 stream:0xe7384824 wall:0 window_ms:600001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-67
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2717345 stream:0xe7384824 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e45e1beaab37 n:1 rssi:-93

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2862659 stream:0xe7384824 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-66
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e45e1beaab37 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3414447 stream:0xe7384824 wall:0 window_ms:551788 entities:11
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:08bfb88eddd0 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4014447 stream:0xe7384824 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4614446 stream:0xe7384824 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5214447 stream:0xe7384824 wall:0 window_ms:600001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5814446 stream:0xe7384824 wall:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6414447 stream:0xe7384824 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7014446 stream:0xe7384824 wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7614467 stream:0xe7384824 wall:0 window_ms:600020 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8214447 stream:0xe7384824 wall:0 window_ms:599980 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8814446 stream:0xe7384824 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xaf869fce wall:0 t_ms:17185 node:0x12 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:76311 stream:0xaf869fce wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xdffbae31 wall:0 t_ms:3707175 node:0x12 from:0x10
**REMAP** prev_stream:0xb7227f6f prev_t_ms:3379 offset_ms:3703796 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3757000 stream:0xdffbae31 wall:0 window_ms:60006 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4306792 stream:0xdffbae31 wall:0 window_ms:549792 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4906791 stream:0xdffbae31 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5506791 stream:0xdffbae31 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6106791 stream:0xdffbae31 wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbe8a1293 wall:0 t_ms:11834473 node:0x12 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11893222 stream:0xbe8a1293 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-20
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12443021 stream:0xbe8a1293 wall:0 window_ms:549798 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-14
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-95

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13043021 stream:0xbe8a1293 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-16
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-95

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbce80555 wall:0 t_ms:22886 node:0x12 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x66486d22 wall:0 t_ms:1256016 node:0x12 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x95cc309e wall:0 t_ms:4256100 node:0x12 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbeb39900 wall:0 t_ms:0 node:0x12 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x1de72b4d wall:0 t_ms:148688 node:0x12 from:0x11
**REMAP** prev_stream:0xffb51d2f prev_t_ms:3264 offset_ms:145424 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x0c8e926c wall:0 t_ms:0 node:0x12 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xdd4bfb6c wall:0 t_ms:0 node:0x12 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xd2dacc37 wall:0 t_ms:0 node:0x12 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbb1177f2 wall:0 t_ms:3905253 node:0x12 from:0x10
**REMAP** prev_stream:0x1d5c0838 prev_t_ms:3788 offset_ms:3901465 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x7d224c73 wall:0 t_ms:140479 node:0x12 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted
