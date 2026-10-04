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

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xd94c8c52 wall:0 t_ms:98428 node:0x10 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xd94c8c52 wall:0 t_ms:2118707 node:0x10 from:0x100
**REMAP** prev_stream:0x8a7e08e6 prev_t_ms:3917 offset_ms:2114790 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xb23c7677 wall:0 t_ms:29 node:0x10 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x5b53f35b wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x2fd913e7 wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x5dc49a3b wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x92beb374 wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x642cef6b wall:0 t_ms:41039 node:0x10 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT103LON8192 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1052557 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:1165151 stream:0xc909d5a8 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT100LON12 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:5 removed:48 last_lon:47 t_ms:1558270 stream:0xc909d5a8 wall:0 node:0x00000010

---

@LAT100LON13 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:6 removed:48 last_lon:47 t_ms:1566750 stream:0xc909d5a8 wall:0 node:0x00000010

---

@LAT103LON8193 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1534757 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:1645324 stream:0xc909d5a8 wall:0 window_ms:62036 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON8194 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2698497 ±22 frame:4000
said: 1 | **ENTWIN** t_ms:2809092 stream:0xc909d5a8 wall:0 window_ms:600001 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 11 | **COVERED** windows:1 entities:8 window_ms:563730 first_t_ms:2209091 last_t_ms:2209091 covered_by:@LAT103LON8193
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96 windows:1
```

---

@LAT103LON8195 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 346831 ±21 frame:5000
said: 1 | **ENTWIN** t_ms:610775 stream:0x40bbc10f wall:0 window_ms:60037 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON8196 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1248603 ±21 frame:5000
said: 1 | **ENTWIN** t_ms:1512567 stream:0x40bbc10f wall:0 window_ms:60043 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON8197 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 812028 ±22 frame:5500
said: 1 | **ENTWIN** t_ms:803805 stream:0x9afbb748 wall:0 window_ms:60072 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
said: 12 | **ENTITY** kind:wifi_ap id:dc4ba1e08b09 n:1 rssi:-95
said: 13 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 14 | **CORE** entities:0
```

---

@LAT103LON8198 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1954074 ±21 frame:5500
said: 1 | **ENTWIN** t_ms:1954088 stream:0x9afbb748 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,0283cce0e689,980d67f79619
said: 12 | **COVERED** windows:1 entities:8 window_ms:550212 first_t_ms:1354089 last_t_ms:1354089 covered_by:@LAT103LON8197
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-89 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93 windows:1
```

---

@LAT103LON8199 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2562254 ±21 frame:5500
said: 1 | **ENTWIN** t_ms:2554089 stream:0x9afbb748 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 13 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,0283cce0e689,aef9ff2626ac,980d67f79619
```

---

@LAT103LON8200 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3155092 ±0 frame:5500
said: 1 | **ENTWIN** t_ms:3154089 stream:0x9afbb748 wall:0 window_ms:600000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:11 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5203cfd1b904,64677217947d,980d67f79619,5ce28c488e0c,aef9ff2626ac,0283cce0e689,acdf9f4ca21c
```

---

@LAT103LON8201 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4623138 ±21 frame:5500
seq: 2
follows: 0x00000300:54
said: 1 | **ENTWIN** t_ms:4622130 stream:0x9afbb748 wall:0 window_ms:60038 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8202 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5773328 ±21 frame:5500
seq: 22
follows: 0x00000300:94
said: 1 | **ENTWIN** t_ms:5772347 stream:0x9afbb748 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,64677217947d
said: 12 | **COVERED** windows:1 entities:9 window_ms:550178 first_t_ms:5172347 last_t_ms:5172347 covered_by:@LAT103LON8201
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-95 windows:1
```

---

@LAT103LON8203 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6373333 ±21 frame:5500
seq: 33
follows: 0x00000300:116
said: 1 | **ENTWIN** t_ms:6372347 stream:0x9afbb748 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,64677217947d,c2e94427adcf,84a329c78fec
```

---

@LAT103LON135 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6963155 ±21 frame:5500
seq: 43
follows: 0x00000300:137
said: 1 | **LINKWIN** t_ms:6962163 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-52 rssi_med:-51 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-65 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON136 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7023155 ±21 frame:5500
seq: 44
follows: 0x00000300:139
said: 1 | **LINKWIN** t_ms:7022163 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-53 rssi_med:-52 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON137 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7083155 ±21 frame:5500
seq: 45
follows: 0x00000300:141
said: 1 | **LINKWIN** t_ms:7082162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-52 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-79 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON138 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7143152 ±22 frame:5500
seq: 46
follows: 0x00000300:144
said: 1 | **LINKWIN** t_ms:7142162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-53 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-65 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON139 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7203156 ±21 frame:5500
seq: 47
follows: 0x00000300:146
said: 1 | **LINKWIN** t_ms:7202162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-52 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-76 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON140 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7263157 ±21 frame:5500
seq: 48
follows: 0x00000300:148
said: 1 | **LINKWIN** t_ms:7262162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-65 rssi_med:-58 rssi_max:-53
said: 3 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-53 rssi_med:-52 rssi_max:-49
```

---

@LAT103LON141 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7323155 ±21 frame:5500
seq: 49
follows: 0x00000300:150
said: 1 | **LINKWIN** t_ms:7322163 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-52 rssi_med:-52 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON142 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7383156 ±21 frame:5500
seq: 50
follows: 0x00000300:152
said: 1 | **LINKWIN** t_ms:7382162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-52 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-65 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON143 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7443130 ±21 frame:5500
seq: 51
follows: 0x00000300:154
said: 1 | **LINKWIN** t_ms:7442163 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-53 rssi_med:-52 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-65 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON144 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7503160 ±21 frame:5500
seq: 52
follows: 0x00000300:156
said: 1 | **LINKWIN** t_ms:7502163 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-52 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON145 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7563160 ±21 frame:5500
seq: 53
follows: 0x00000300:158
said: 1 | **LINKWIN** t_ms:7562162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:ble n:71 rssi_min:-65 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON146 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7623161 ±21 frame:5500
seq: 54
follows: 0x00000300:161
said: 1 | **LINKWIN** t_ms:7622162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-86 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-65 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON147 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7683161 ±21 frame:5500
seq: 55
follows: 0x00000300:163
said: 1 | **LINKWIN** t_ms:7682162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-52 rssi_med:-52 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON148 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7743162 ±21 frame:5500
seq: 56
follows: 0x00000300:165
said: 1 | **LINKWIN** t_ms:7742162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-53 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-65 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON149 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7803162 ±21 frame:5500
seq: 57
follows: 0x00000300:167
said: 1 | **LINKWIN** t_ms:7802163 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-52 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-56 rssi_max:-53
```

---

@LAT103LON150 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7863162 ±21 frame:5500
seq: 58
follows: 0x00000300:169
said: 1 | **LINKWIN** t_ms:7862162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-53 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-65 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON151 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7923163 ±21 frame:5500
seq: 59
follows: 0x00000300:171
said: 1 | **LINKWIN** t_ms:7922162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-65 rssi_med:-58 rssi_max:-52
said: 3 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-52 rssi_med:-51 rssi_max:-43
```

---

@LAT103LON152 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7983164 ±21 frame:5500
seq: 60
follows: 0x00000300:173
said: 1 | **LINKWIN** t_ms:7982162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-47 rssi_med:-42 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-54 rssi_max:-47
```

---

@LAT103LON153 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8043142 ±21 frame:5500
seq: 61
follows: 0x00000300:175
said: 1 | **LINKWIN** t_ms:8042162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-63 rssi_med:-54 rssi_max:-49
```

---

@LAT103LON154 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8103164 ±21 frame:5500
seq: 62
follows: 0x00000300:177
said: 1 | **LINKWIN** t_ms:8102162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-73 rssi_med:-54 rssi_max:-49
```

---

@LAT103LON155 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8163165 ±21 frame:5500
seq: 63
follows: 0x00000300:179
said: 1 | **LINKWIN** t_ms:8162162 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-43 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-63 rssi_med:-54 rssi_max:-49
```

---

@LAT103LON156 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8223165 ±21 frame:5500
seq: 64
follows: 0x00000300:181
said: 1 | **LINKWIN** t_ms:8222163 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-79 rssi_med:-54 rssi_max:-49
```

---

@LAT103LON157 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8283098 ±21 frame:5500
seq: 65
follows: 0x00000300:184
said: 1 | **LINKWIN** t_ms:8282163 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-43 rssi_med:-42 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-54 rssi_max:-49
```

---

@LAT103LON158 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8463603 ±21 frame:5500
seq: 66
follows: 0x00000300:190
said: 1 | **LINKWIN** t_ms:8462601 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-43 rssi_med:-42 rssi_max:-41
```

---

@LAT103LON8204 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8463647 ±21 frame:5500
seq: 67
follows: 0x00000300:190
said: 1 | **ENTWIN** t_ms:8462601 stream:0x9afbb748 wall:0 window_ms:60044 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-89
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON159 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8523603 ±21 frame:5500
seq: 68
follows: 0x00000300:192
said: 1 | **LINKWIN** t_ms:8522601 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-49
```

---

@LAT103LON160 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8583603 ±21 frame:5500
seq: 69
follows: 0x00000300:194
said: 1 | **LINKWIN** t_ms:8582601 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-63 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-43 rssi_med:-42 rssi_max:-41
```

---

@LAT103LON161 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8643605 ±21 frame:5500
seq: 70
follows: 0x00000300:196
said: 1 | **LINKWIN** t_ms:8642602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-43 rssi_med:-42 rssi_max:-41
```

---

@LAT103LON162 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8703606 ±21 frame:5500
seq: 71
follows: 0x00000300:198
said: 1 | **LINKWIN** t_ms:8702601 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-63 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-43 rssi_med:-42 rssi_max:-41
```

---

@LAT103LON163 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8763606 ±21 frame:5500
seq: 72
follows: 0x00000300:200
said: 1 | **LINKWIN** t_ms:8762601 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-63 rssi_med:-54 rssi_max:-48
said: 3 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-43 rssi_med:-42 rssi_max:-42
```

---

@LAT103LON164 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8823606 ±21 frame:5500
seq: 73
follows: 0x00000300:202
said: 1 | **LINKWIN** t_ms:8822602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-63 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-43 rssi_med:-42 rssi_max:-41
```

---

@LAT103LON165 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8883606 ±21 frame:5500
seq: 74
follows: 0x00000300:204
said: 1 | **LINKWIN** t_ms:8882602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-43 rssi_med:-42 rssi_max:-41
```

---

@LAT103LON166 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8943608 ±22 frame:5500
seq: 75
follows: 0x00000300:206
said: 1 | **LINKWIN** t_ms:8942602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-43 rssi_med:-40 rssi_max:-16
said: 3 | **LINK** peer:0x00000300 proto:ble n:46 rssi_min:-81 rssi_med:-41 rssi_max:-31
```

---

@LAT103LON167 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9003608 ±0 frame:5500
seq: 76
follows: 0x00000300:206
said: 1 | **LINKWIN** t_ms:9002602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:30 rssi_min:-79 rssi_med:-39 rssi_max:-39
```

---

@LAT103LON168 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9063608 ±0 frame:5500
seq: 77
follows: 0x00000300:210
said: 1 | **LINKWIN** t_ms:9062602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-41 rssi_med:-39 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:9 rssi_min:-26 rssi_med:-26 rssi_max:-25
```

---

@LAT103LON169 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9123608 ±0 frame:5500
seq: 78
follows: 0x00000300:212
said: 1 | **LINKWIN** t_ms:9122601 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-77 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-27 rssi_med:-26 rssi_max:-25
```

---

@LAT103LON170 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9183608 ±0 frame:5500
seq: 79
follows: 0x00000300:214
said: 1 | **LINKWIN** t_ms:9182602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:71 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-26 rssi_med:-26 rssi_max:-25
```

---

@LAT103LON171 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9243608 ±0 frame:5500
seq: 80
follows: 0x00000300:216
said: 1 | **LINKWIN** t_ms:9242602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:18 rssi_min:-27 rssi_med:-26 rssi_max:-25
```

---

@LAT103LON172 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9303579 ±21 frame:5500
seq: 81
follows: 0x00000300:218
said: 1 | **LINKWIN** t_ms:9302602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-26 rssi_med:-26 rssi_max:-25
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-40 rssi_max:-39
```

---

@LAT103LON173 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9363579 ±21 frame:5500
seq: 82
follows: 0x00000300:220
said: 1 | **LINKWIN** t_ms:9362602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-27 rssi_med:-26 rssi_max:-25
```

---

@LAT103LON174 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9423579 ±21 frame:5500
seq: 83
follows: 0x00000300:222
said: 1 | **LINKWIN** t_ms:9422601 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:16 rssi_min:-27 rssi_med:-26 rssi_max:-25
```

---

@LAT104LON14 | created:0 | updated:0

**carried through @LAT103LON134**

```ttdb-carried
through: 134
```

---

@LAT103LON175 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9483581 ±21 frame:5500
seq: 84
follows: 0x00000300:224
said: 1 | **LINKWIN** t_ms:9482602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-40 rssi_max:-38
said: 3 | **LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-27 rssi_med:-26 rssi_max:-24
```

---

@LAT103LON176 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9543563 ±21 frame:5500
seq: 85
follows: 0x00000300:226
said: 1 | **LINKWIN** t_ms:9542602 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-27 rssi_med:-26 rssi_max:-25
```

---

@LAT103LON177 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9603582 ±21 frame:5500
seq: 86
follows: 0x00000300:230
said: 1 | **LINKWIN** t_ms:9602601 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-46 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-64 rssi_med:-40 rssi_max:-31
said: 4 | **LINK** peer:0x00000200 proto:espnow n:5 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 5 | **LINK** peer:0x00000200 proto:ble n:8 rssi_min:-55 rssi_med:-51 rssi_max:-45
```

---

@LAT103LON8205 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9613872 ±21 frame:5500
seq: 87
follows: 0x00000300:230
said: 1 | **ENTWIN** t_ms:9612891 stream:0x9afbb748 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-93
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,64677217947d,e6b32d2cea8b
said: 12 | **COVERED** windows:1 entities:10 window_ms:550246 first_t_ms:9012891 last_t_ms:9012891 covered_by:@LAT103LON8204
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-97 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97 windows:1
```

---

@LAT103LON178 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15851678 ±21 frame:7000
seq: 88
follows: 0x00000011:48 0x00000012:5 0x00000100:390 0x00000200:717 0x00000300:2060
said: 1 | **LINKWIN** t_ms:15916879 stream:0x3c4214c9 wall:0 window_ms:66000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:68 rssi_min:-42 rssi_med:-38 rssi_max:-32
said: 3 | **LINK** peer:0x00000200 proto:ble n:73 rssi_min:-84 rssi_med:-59 rssi_max:-51
said: 4 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-53 rssi_med:-45 rssi_max:-43
said: 5 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-80 rssi_med:-48 rssi_max:-42
```

---

@LAT103LON8206 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 15853640 ±21 frame:7000
seq: 89
follows: 0x00000011:48 0x00000012:5 0x00000100:390 0x00000200:717 0x00000300:2060
said: 1 | **ENTWIN** t_ms:15916879 stream:0x3c4214c9 wall:0 window_ms:67960 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```
