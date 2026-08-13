# V4-A Bridge Node TTDB

```mmpdb
db_id: v4a-bridge-001
db_name: V4-A Bridge Node
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: v4a-bridge
  role: mesh-gateway
  perspective: spine-head
  scope: whole-mesh
  constraints:
    - always-powered
    - channel-authority
  globe:
    frame: mesh-topology
    origin: "@LAT0LON0"
    mapping: "spine and cluster nodes placed on the lat/lon knowledge grid"
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
lon: 0
```

---

@LAT0LON0 | created:1750000000 | updated:1750000000 | relates:navigates_to@LAT0LON10

Bridge home. Gateway between the laptop (USB-CDC) and the LoRa/ESP-NOW mesh.

---

@LAT0LON10 | created:1750000000 | updated:1750000000 | relates:navigates_to@LAT0LON20

Toward V4-B (relay). Forwarding state for the first LoRa hop.

---


---


---


---


---


---


---


---


---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:47 last_lon:46 t_ms:9913863 stream:0x59fb8ce8 wall:0 node:0x00000010

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:8 last_lon:7 t_ms:9939665 stream:0x59fb8ce8 wall:0 node:0x00000010

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:2 removed:48 last_lon:47 t_ms:16023693 stream:0x946fea42 wall:0 node:0x00000010

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:2 removed:48 last_lon:47 t_ms:16023693 stream:0x946fea42 wall:0 node:0x00000010

---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:1 removed:15 last_lon:14 t_ms:0 stream:0x00000000 wall:0 node:0x00000010
**STREAMS-EXPLAINED** n:14 0x59fb8ce8 0xbdc62024 0xe7384824 0xaf869fce 0x161e88ac 0x67ec2883 0x3ab84e5a 0xbe6d9616 0x6a2120c2 0xdffbae31 0x6549a5c7 0x185f5a4b 0x946fea42 0x32464d87

---

@LAT100LON5 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:3 removed:48 last_lon:47 t_ms:325212 stream:0xf796e624 wall:0 node:0x00000010

---

@LAT100LON6 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:3 removed:48 last_lon:47 t_ms:325212 stream:0xf796e624 wall:0 node:0x00000010

---

@LAT100LON7 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:2 removed:4 last_lon:3 t_ms:0 stream:0x00000000 wall:0 node:0x00000010
**STREAMS-EXPLAINED** n:4 0xe334a7e1 0xbe8a1293 0x9929f0cc 0xf796e624

---

@LAT100LON8 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:4 removed:48 last_lon:47 t_ms:2494798 stream:0x95cc309e wall:0 node:0x00000010

---

@LAT100LON9 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:3 removed:14 last_lon:13 t_ms:1082603 stream:0x516c169d wall:0 node:0x00000010
**STREAMS-EXPLAINED** n:13 0xc8a01245 0xe6a101ec 0x7945c57c 0x50956f00 0xbce80555 0x6d2ca283 0x354b03a5 0x66486d22 0x95cc309e 0x982c89ff 0xb4347c09 0xc49e1cd4 0x516c169d

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x516c169d wall:0 t_ms:1095398 node:0x10 from:0x300
**REMAP** prev_stream:0x31d190a2 prev_t_ms:4211 offset_ms:1091187 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x516c169d wall:0 t_ms:1111398 node:0x10 from:0x300
**REMAP** prev_stream:0xcc392cf5 prev_t_ms:5888 offset_ms:1105510 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x0870722b wall:0 t_ms:1091357 node:0x10 from:0x200
**REMAP** prev_stream:0x7f5e3f9d prev_t_ms:5877 offset_ms:1085480 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x0870722b wall:0 t_ms:1823418 node:0x10 from:0x200
**REMAP** prev_stream:0xb4e66af6 prev_t_ms:3735 offset_ms:1819683 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbeb39900 wall:0 t_ms:7189 node:0x10 from:0x12
**REMAP** prev_stream:0xbdcdb608 prev_t_ms:3427 offset_ms:3762 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x1de72b4d wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xd2dacc37 wall:0 t_ms:5260810 node:0x10 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbb1177f2 wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---


---

@LAT100LON10 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:5 removed:48 last_lon:47 t_ms:38027556 stream:0xbb1177f2 wall:0 node:0x00000010

---

@LAT100LON11 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:4 removed:48 last_lon:47 t_ms:38045805 stream:0xbb1177f2 wall:0 node:0x00000010

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38116757 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-59 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-80 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-25 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-46 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-98 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-44 rssi_med:-43 rssi_max:-42

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:38116757 stream:0xbb1177f2 wall:0 window_ms:62035 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38176757 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-95 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-75 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-54 rssi_med:-50 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-25 rssi_med:-23 rssi_max:-22
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-57 rssi_max:-52

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38236758 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-52 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-62 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-94 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-73 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000300 proto:ble n:26 rssi_min:-44 rssi_med:-39 rssi_max:-36
**LINK** peer:0x00000300 proto:espnow n:15 rssi_min:-25 rssi_med:-24 rssi_max:-23

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38296758 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-92 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-72 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-25 rssi_med:-24 rssi_max:-23
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-51 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-46 rssi_med:-40 rssi_max:-36
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-64 rssi_med:-58 rssi_max:-53

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38356757 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-45 rssi_med:-38 rssi_max:-35
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-73 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-93 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-52 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-25 rssi_med:-23 rssi_max:-22
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-64 rssi_med:-57 rssi_max:-53

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38416758 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:72 rssi_min:-79 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-39 rssi_max:-36
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-96 rssi_med:-87 rssi_max:-82
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-77 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-24 rssi_med:-24 rssi_max:-23
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-51 rssi_med:-50 rssi_max:-45

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38476757 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-25 rssi_med:-23 rssi_max:-20
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-98 rssi_med:-85 rssi_max:-79
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-81 rssi_med:-38 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-76 rssi_med:-74 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-51 rssi_med:-49 rssi_max:-47

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38536757 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-75 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-79 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-50 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-22 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000011 proto:ble n:43 rssi_min:-95 rssi_med:-82 rssi_max:-80

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38596757 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-65 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-75 rssi_med:-74 rssi_max:-70
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-97 rssi_med:-85 rssi_max:-80
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-22 rssi_med:-21 rssi_max:-21
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-53 rssi_med:-49 rssi_max:-46

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38656757 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-41 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-70 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-99 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-77 rssi_med:-74 rssi_max:-71
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-22 rssi_med:-21 rssi_max:-21
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-51 rssi_med:-49 rssi_max:-47

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:38670475 stream:0xbb1177f2 wall:0 window_ms:553682 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38716757 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-96 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000300 proto:espnow n:14 rssi_min:-23 rssi_med:-22 rssi_max:-21
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-77 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-66 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000300 proto:ble n:30 rssi_min:-79 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-55 rssi_med:-49 rssi_max:-48

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38776757 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:47 rssi_min:-98 rssi_med:-85 rssi_max:-81
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-60 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-51 rssi_med:-50 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-80 rssi_med:-76 rssi_max:-68
**LINK** peer:0x00000300 proto:espnow n:10 rssi_min:-21 rssi_med:-21 rssi_max:-20

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38838470 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-77 rssi_med:-73 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-51 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-79 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-95 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-22 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-80 rssi_med:-60 rssi_max:-55

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:38838470 stream:0xbb1177f2 wall:0 window_ms:62111 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38898469 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-95 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-77 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-50 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-63 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-22 rssi_med:-21 rssi_max:-20

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:38958469 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-40 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-64 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-73 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-50 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-21 rssi_med:-20 rssi_max:-18
**LINK** peer:0x00000011 proto:ble n:41 rssi_min:-97 rssi_med:-85 rssi_max:-80

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39018470 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:44 rssi_min:-97 rssi_med:-88 rssi_max:-80
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-74 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-39 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-61 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-25 rssi_med:-23 rssi_max:-18
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-52 rssi_med:-49 rssi_max:-45

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39078470 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-47 rssi_med:-40 rssi_max:-36
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-54 rssi_med:-46 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-65 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-93 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-24 rssi_med:-23 rssi_max:-22

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39162279 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:12 rssi_min:-72 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-45 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-77 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:44 rssi_min:-91 rssi_med:-88 rssi_max:-82
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-44 rssi_med:-42 rssi_max:-37
**LINK** peer:0x00000300 proto:espnow n:1 rssi_min:-25 rssi_med:-25 rssi_max:-25

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:39162279 stream:0xbb1177f2 wall:0 window_ms:62039 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39222278 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-92 rssi_med:-87 rssi_max:-84
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-82 rssi_med:-42 rssi_max:-37
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-73 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-25 rssi_med:-24 rssi_max:-24

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39282279 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-77 rssi_med:-41 rssi_max:-37
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-58 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-72 rssi_med:-71 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-43 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-92 rssi_med:-88 rssi_max:-84
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-26 rssi_med:-24 rssi_max:-24

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39342278 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-42 rssi_max:-37
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-81 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-91 rssi_med:-87 rssi_max:-84
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-72 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-26 rssi_med:-24 rssi_max:-24

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39402279 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-73 rssi_med:-71 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-55 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-95 rssi_med:-87 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-42 rssi_max:-37
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-43 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-25 rssi_med:-24 rssi_max:-24

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39462278 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-96 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-43 rssi_med:-41 rssi_max:-41
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-77 rssi_med:-76 rssi_max:-70
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-23 rssi_med:-20 rssi_max:-19

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39522279 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-57 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-50 rssi_med:-38 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-97 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-81 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-45 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-26 rssi_med:-23 rssi_max:-19

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39582278 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-93 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-45 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-56 rssi_med:-54 rssi_max:-54
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-28 rssi_med:-26 rssi_max:-26

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39642279 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-91 rssi_med:-87 rssi_max:-82
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-54 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-73 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-45 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-27 rssi_med:-26 rssi_max:-26

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39702278 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-44 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-73 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-45 rssi_med:-43 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-56 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-92 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-28 rssi_med:-26 rssi_max:-26

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:39714017 stream:0xbb1177f2 wall:0 window_ms:551699 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-96
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39762279 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-91 rssi_med:-87 rssi_max:-81
**LINK** peer:0x00000200 proto:ble n:49 rssi_min:-79 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-45 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-45 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:10 rssi_min:-27 rssi_med:-26 rssi_max:-26

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39822279 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-67 rssi_med:-60 rssi_max:-50
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-42 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-76 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-58 rssi_med:-48 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-96 rssi_med:-87 rssi_max:-81
**LINK** peer:0x00000100 proto:espnow n:21 rssi_min:-43 rssi_med:-39 rssi_max:-30

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39882279 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-100 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:43 rssi_min:-80 rssi_med:-73 rssi_max:-69
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-79 rssi_med:-42 rssi_max:-31
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-44 rssi_med:-39 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-58 rssi_med:-51 rssi_max:-42

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:39942279 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-44 rssi_med:-41 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-49 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-96 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-60 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:32 rssi_min:-75 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000300 proto:ble n:32 rssi_min:-66 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:2 rssi_min:-19 rssi_med:-19 rssi_max:-19

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40006034 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-21 rssi_med:-20 rssi_max:-18
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-44 rssi_med:-40 rssi_max:-33
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-78 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-81 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-51 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:46 rssi_min:-96 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-35 rssi_med:-34 rssi_max:-32

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:40006034 stream:0xbb1177f2 wall:0 window_ms:62035 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40066035 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-44 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:50 rssi_min:-70 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-97 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-75 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000300 proto:espnow n:6 rssi_min:-21 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-49 rssi_med:-47 rssi_max:-43

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40126035 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-35 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-99 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-44 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-77 rssi_med:-74 rssi_max:-71
**LINK** peer:0x00000300 proto:espnow n:16 rssi_min:-21 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-51 rssi_med:-46 rssi_max:-44

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40186035 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-45 rssi_med:-40 rssi_max:-32
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-49 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-61 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-76 rssi_med:-73 rssi_max:-72
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-21 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000011 proto:ble n:47 rssi_min:-98 rssi_med:-86 rssi_max:-82

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40246035 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-35 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-49 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-99 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-21 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-42 rssi_med:-39 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-75 rssi_med:-74 rssi_max:-71

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40306035 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-77 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-79 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-44 rssi_med:-39 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-49 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:48 rssi_min:-100 rssi_med:-84 rssi_max:-82
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-21 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-76 rssi_med:-74 rssi_max:-73

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40366035 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-43 rssi_med:-40 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-99 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-22 rssi_med:-19 rssi_max:-17
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-34 rssi_med:-33 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-48 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-78 rssi_med:-74 rssi_max:-69

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40426034 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-47 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-76 rssi_med:-32 rssi_max:-30
**LINK** peer:0x00000100 proto:espnow n:32 rssi_min:-42 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-79 rssi_med:-73 rssi_max:-70
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-97 rssi_med:-87 rssi_max:-80
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-19 rssi_med:-17 rssi_max:-16

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40486034 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:73 rssi_min:-81 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-96 rssi_med:-88 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-47 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-78 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-17 rssi_med:-16 rssi_max:-15
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-42 rssi_med:-40 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-79 rssi_med:-31 rssi_max:-30

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40546034 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-63 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-44 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-50 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-80 rssi_med:-76 rssi_max:-72
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-96 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-17 rssi_med:-16 rssi_max:-15

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:40557786 stream:0xbb1177f2 wall:0 window_ms:551716 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40606034 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-80 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-40 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-79 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-48 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-92 rssi_med:-87 rssi_max:-84
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-17 rssi_med:-16 rssi_max:-16
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-74 rssi_med:-72 rssi_max:-71

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40666034 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-97 rssi_med:-87 rssi_max:-82
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-60 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-42 rssi_med:-35 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-48 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-78 rssi_med:-75 rssi_max:-72
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-17 rssi_med:-16 rssi_max:-16

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40726034 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-77 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-94 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-42 rssi_med:-38 rssi_max:-32
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-48 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-80 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-79 rssi_med:-76 rssi_max:-72

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40786034 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-43 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-96 rssi_med:-90 rssi_max:-79
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-45 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-78 rssi_med:-74 rssi_max:-73

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40846035 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-95 rssi_med:-87 rssi_max:-80
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-42 rssi_med:-41 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-48 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:49 rssi_min:-80 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-59 rssi_med:-56 rssi_max:-54

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40906035 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-79 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-96 rssi_med:-88 rssi_max:-80
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-50 rssi_med:-38 rssi_max:-27
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-51 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-76 rssi_med:-74 rssi_max:-71

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:40966035 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-32 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-45 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-96 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-43 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:39 rssi_min:-79 rssi_med:-76 rssi_max:-72

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:41157786 stream:0xbb1177f2 wall:0 window_ms:598001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,64677217947d,84a329c78fec

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:41318017 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-98
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:41420837 stream:0xbb1177f2 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:41976350 stream:0xbb1177f2 wall:0 window_ms:557513 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:42462055 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:42652168 stream:0xbb1177f2 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:43205945 stream:0xbb1177f2 wall:0 window_ms:555777 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:43805945 stream:0xbb1177f2 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,0283cce0e689,e6b32d2cea8b,18a5ffbae2d6

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:44407478 stream:0xbb1177f2 wall:0 window_ms:601533 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:4
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,0283cce0e689,e6b32d2cea8b,64677217947d,18a5ffbae2d6,5ce28c488e0c

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:44959519 stream:0xbb1177f2 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:45151530 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:45433984 stream:0xbb1177f2 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0
