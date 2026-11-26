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

@LAT100LON12 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:5 removed:48 last_lon:47 t_ms:1558270 stream:0xc909d5a8 wall:0 node:0x00000010

---

@LAT100LON13 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:6 removed:48 last_lon:47 t_ms:1566750 stream:0xc909d5a8 wall:0 node:0x00000010

---

@LAT103LON8246 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 16571038 ±21 frame:20500
seq: 817
follows: 0x00000011:751 0x00000012:659 0x00000100:732 0x00000200:1433 0x00000300:3494
said: 1 | **ENTWIN** t_ms:16540779 stream:0xa0be1a79 wall:0 window_ms:74068 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8247 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 17744957 ±21 frame:20500
seq: 837
follows: 0x00000011:773 0x00000012:680 0x00000100:732 0x00000200:1453 0x00000300:3533
said: 1 | **ENTWIN** t_ms:17726783 stream:0xa0be1a79 wall:0 window_ms:600021 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,c2e94427adcf,64677217947d
said: 11 | **COVERED** windows:1 entities:8 window_ms:573889 first_t_ms:17126762 last_t_ms:17126762 covered_by:@LAT103LON8246
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
```

---

@LAT103LON8248 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 19543037 ±21 frame:20500
seq: 868
follows: 0x00000011:803 0x00000012:710 0x00000100:732 0x00000200:1485 0x00000300:3596
said: 1 | **ENTWIN** t_ms:19526846 stream:0xa0be1a79 wall:0 window_ms:600030 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,e6b32d2cea8b,02c57d2e0f0d,84a329c78fec,64677217947d
said: 12 | **COVERED** windows:2 entities:7 window_ms:1198034 first_t_ms:18326817 last_t_ms:18926816 covered_by:@LAT103LON8247
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-37 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-71 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-77 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-80 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-83 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-91 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94 windows:1
```

---

@LAT103LON8249 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21943088 ±21 frame:20500
seq: 909
follows: 0x00000011:845 0x00000012:752 0x00000100:732 0x00000200:1525 0x00000300:3680
said: 1 | **ENTWIN** t_ms:21926876 stream:0xa0be1a79 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,64677217947d,0283cce0e689
said: 11 | **COVERED** windows:3 entities:9 window_ms:1800030 first_t_ms:20126859 last_t_ms:21326876 covered_by:@LAT103LON8248
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-35 windows:3
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-71 windows:3
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-75 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-76 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-82 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-90 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-94 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95 windows:1
```

---

@LAT103LON8250 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 23743098 ±21 frame:20500
seq: 940
follows: 0x00000011:877 0x00000012:783 0x00000100:732 0x00000200:1557 0x00000300:3743
said: 1 | **ENTWIN** t_ms:23726927 stream:0xa0be1a79 wall:0 window_ms:599982 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-96
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689
said: 11 | **COVERED** windows:2 entities:8 window_ms:1200018 first_t_ms:22526876 last_t_ms:23126945 covered_by:@LAT103LON8249
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-39 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-71 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-78 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-83 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-80 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-92 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94 windows:1
```

---

@LAT103LON8251 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 25543116 ±21 frame:20500
seq: 971
follows: 0x00000011:909 0x00000012:814 0x00000100:732 0x00000200:1588 0x00000300:3806
said: 1 | **ENTWIN** t_ms:25526927 stream:0xa0be1a79 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,0283cce0e689
said: 12 | **COVERED** windows:2 entities:8 window_ms:1200000 first_t_ms:24326928 last_t_ms:24926928 covered_by:@LAT103LON8250
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-35 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-67 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-71 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-89 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-90 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-96 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
```

---

@LAT103LON8252 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 27343137 ±21 frame:20500
seq: 1002
follows: 0x00000011:940 0x00000012:844 0x00000100:732 0x00000200:1619 0x00000300:3868
said: 1 | **ENTWIN** t_ms:27326927 stream:0xa0be1a79 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,0283cce0e689
said: 11 | **COVERED** windows:2 entities:8 window_ms:1200000 first_t_ms:26126927 last_t_ms:26726928 covered_by:@LAT103LON8251
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-39 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-67 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-70 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-88 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-87 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-90 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94 windows:1
```

---

@LAT103LON8253 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 29743161 ±21 frame:20500
seq: 1043
follows: 0x00000011:983 0x00000012:886 0x00000100:732 0x00000200:1662 0x00000300:3951
said: 1 | **ENTWIN** t_ms:29726979 stream:0xa0be1a79 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96
said: 10 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,c2e94427adcf
said: 12 | **COVERED** windows:3 entities:8 window_ms:1800000 first_t_ms:27926928 last_t_ms:29126978 covered_by:@LAT103LON8252
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-39 windows:3
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-67 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-69 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-87 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-88 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-92 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-94 windows:2
```

---

@LAT103LON8254 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 30943171 ±21 frame:20500
seq: 1064
follows: 0x00000011:1005 0x00000012:906 0x00000100:732 0x00000200:1683 0x00000300:3991
said: 1 | **ENTWIN** t_ms:30926978 stream:0xa0be1a79 wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,0283cce0e689,c2e94427adcf
said: 10 | **COVERED** windows:1 entities:8 window_ms:600000 first_t_ms:30326978 last_t_ms:30326978 covered_by:@LAT103LON8253
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
```

---

@LAT103LON8255 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31543178 ±21 frame:20500
seq: 1075
follows: 0x00000011:1016 0x00000012:917 0x00000100:732 0x00000200:1694 0x00000300:4012
said: 1 | **ENTWIN** t_ms:31526978 stream:0xa0be1a79 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-96
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-98
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,0283cce0e689,7236bc441422,c2e94427adcf
```

---

@LAT103LON8256 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 32743213 ±21 frame:20500
seq: 1096
follows: 0x00000011:1038 0x00000012:937 0x00000100:732 0x00000200:1716 0x00000300:4053
said: 1 | **ENTWIN** t_ms:32727004 stream:0xa0be1a79 wall:0 window_ms:600026 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,84a329c78fec,c2e94427adcf
said: 12 | **COVERED** windows:1 entities:8 window_ms:600000 first_t_ms:32126978 last_t_ms:32126978 covered_by:@LAT103LON8255
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94 windows:1
```

---

@LAT103LON8257 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34609089 ±21 frame:20500
seq: 1127
follows: 0x00000011:1071 0x00000012:969 0x00000100:732 0x00000200:1748 0x00000300:4118
said: 1 | **ENTWIN** t_ms:34578797 stream:0xa0be1a79 wall:0 window_ms:74117 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8258 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 35780281 ±21 frame:20500
seq: 1147
follows: 0x00000011:1092 0x00000012:989 0x00000100:732 0x00000200:1770 0x00000300:4161
said: 1 | **ENTWIN** t_ms:35764095 stream:0xa0be1a79 wall:0 window_ms:598000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 9 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace
said: 10 | **COVERED** windows:1 entities:8 window_ms:573180 first_t_ms:35164095 last_t_ms:35164095 covered_by:@LAT103LON8257
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-97 windows:1
```

---

@LAT103LON8259 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36380298 ±21 frame:20500
seq: 1158
follows: 0x00000011:1103 0x00000012:1000 0x00000100:732 0x00000200:1780 0x00000300:4180
said: 1 | **ENTWIN** t_ms:36364113 stream:0xa0be1a79 wall:0 window_ms:600018 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,e6b32d2cea8b,02c57d2e0f0d,64677217947d
```

---

@LAT103LON8260 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36980302 ±21 frame:20500
seq: 1169
follows: 0x00000011:1113 0x00000012:1010 0x00000100:732 0x00000200:1790 0x00000300:4198
said: 1 | **ENTWIN** t_ms:36964112 stream:0xa0be1a79 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,980d67f79619,64677217947d
```

---

@LAT103LON8261 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 37582311 ±23 frame:20500
seq: 1180
follows: 0x00000011:1124 0x00000012:1021 0x00000100:732 0x00000200:1801 0x00000300:4214
said: 1 | **ENTWIN** t_ms:37564121 stream:0xa0be1a79 wall:0 window_ms:602008 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-97
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON8262 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 37919686 ±21 frame:20500
seq: 1182
follows: 0x00000011:1130 0x00000012:1028 0x00000100:732 0x00000200:1806 0x00000300:4214
said: 1 | **ENTWIN** t_ms:37900350 stream:0xa0be1a79 wall:0 window_ms:63148 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON8263 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 609087 ±21 frame:10000
seq: 1185
follows: 0x00000011:1133 0x00000012:1036 0x00000100:742 0x00000200:1829 0x00000300:4214
said: 1 | **ENTWIN** t_ms:925001 stream:0x364dd329 wall:0 window_ms:60045 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8264 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 93523 ±21 frame:8000
seq: 1193
follows: 0x00000011:1143 0x00000012:1046 0x00000100:751 0x00000200:1840 0x00000300:4236
said: 1 | **ENTWIN** t_ms:82857 stream:0x732acba3 wall:0 window_ms:60000 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON8265 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1251327 ±21 frame:8000
seq: 1214
follows: 0x00000011:1163 0x00000012:1066 0x00000100:773 0x00000200:1860 0x00000300:4275
said: 1 | **ENTWIN** t_ms:1240651 stream:0x732acba3 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 12 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace
said: 13 | **COVERED** windows:1 entities:10 window_ms:557794 first_t_ms:640652 last_t_ms:640652 covered_by:@LAT103LON8264
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-98 windows:1
```

---

@LAT103LON8266 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1851358 ±21 frame:8000
seq: 1225
follows: 0x00000011:1174 0x00000012:1077 0x00000100:784 0x00000200:1871 0x00000300:4296
said: 1 | **ENTWIN** t_ms:1840677 stream:0x732acba3 wall:0 window_ms:600025 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,84a329c78fec,c2e94427adcf
```

---

@LAT103LON8267 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2451370 ±21 frame:8000
seq: 1236
follows: 0x00000011:1184 0x00000012:1087 0x00000100:796 0x00000200:1881 0x00000300:4317
said: 1 | **ENTWIN** t_ms:2440683 stream:0x732acba3 wall:0 window_ms:600007 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 12 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-95
said: 13 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-95
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,c2e94427adcf,84a329c78fec,0283cce0e689
```

---

@LAT103LON8268 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3051376 ±21 frame:8000
seq: 1247
follows: 0x00000011:1194 0x00000012:1097 0x00000100:805 0x00000200:1891 0x00000300:4337
said: 1 | **ENTWIN** t_ms:3040683 stream:0x732acba3 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,0283cce0e689,980d67f79619,c2e94427adcf,84a329c78fec
```

---

@LAT103LON8269 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3651381 ±21 frame:8000
seq: 1258
follows: 0x00000011:1204 0x00000012:1107 0x00000100:816 0x00000200:1901 0x00000300:4357
said: 1 | **ENTWIN** t_ms:3640683 stream:0x732acba3 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,c2e94427adcf,84a329c78fec,0283cce0e689,02c57d2f9719,980d67f79619
```

---

@LAT103LON8270 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4251385 ±21 frame:8000
seq: 1269
follows: 0x00000011:1214 0x00000012:1119 0x00000100:829 0x00000200:1912 0x00000300:4378
said: 1 | **ENTWIN** t_ms:4240683 stream:0x732acba3 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,c2e94427adcf,0283cce0e689,84a329c78fec,02c57d2f9719
```

---

@LAT103LON8271 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4851391 ±21 frame:8000
seq: 1280
follows: 0x00000011:1224 0x00000012:1130 0x00000100:839 0x00000200:1923 0x00000300:4399
said: 1 | **ENTWIN** t_ms:4840683 stream:0x732acba3 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,0283cce0e689,02c57d2f9719,5ce28c488e0c,c2e94427adcf
```

---

@LAT103LON8272 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5451420 ±21 frame:8000
seq: 1291
follows: 0x00000011:1235 0x00000012:1141 0x00000100:850 0x00000200:1933 0x00000300:4419
said: 1 | **ENTWIN** t_ms:5440705 stream:0x732acba3 wall:0 window_ms:600022 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-55
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,64677217947d,c2e94427adcf,5203cfd1b904,0283cce0e689,02c57d2f9719
```

---

@LAT103LON8273 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6051413 ±21 frame:8000
seq: 1302
follows: 0x00000011:1246 0x00000012:1152 0x00000100:862 0x00000200:1943 0x00000300:4440
said: 1 | **ENTWIN** t_ms:6040755 stream:0x732acba3 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-53
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,5ce28c488e0c,c2e94427adcf,0283cce0e689
```

---

@LAT103LON8274 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6651447 ±21 frame:8000
seq: 1313
follows: 0x00000011:1256 0x00000012:1162 0x00000100:873 0x00000200:1953 0x00000300:4460
said: 1 | **ENTWIN** t_ms:6640774 stream:0x732acba3 wall:0 window_ms:600018 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-52
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,5ce28c488e0c,c2e94427adcf,bc102f237ace
```

---

@LAT106LON118 | created:0 | updated:0

**BAR** frame:8000 bar:12 own:10 held:40 terms:9 digest:0x9c7c5137 settled_ms:300024
**HOLDS** agent:0x00000010 n:10 lo:1312 hi:1322 sum:13174
**HOLDS** agent:0x00000011 n:10 lo:1256 hi:1265 sum:12605
**HOLDS** agent:0x00000012 n:10 lo:1162 hi:1171 sum:11665
**HOLDS** agent:0x00000200 n:10 lo:1954 hi:1963 sum:19585
**HOLDS** agent:0x00000300 n:10 lo:4459 hi:4477 sum:44680
**DELIVER** up_s:7481 heap:122828 fetched:547 unanswered:314 broken:80 resumed:1747 empty:231 served:1764 wants:1804 early:119 wantq_drop:0 superseded:1

---

@LAT106LON119 | created:0 | updated:0

**BAR** frame:8000 bar:13 own:10 held:40 terms:9 digest:0x45949f72 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1323 hi:1332 sum:13275
**HOLDS** agent:0x00000011 n:10 lo:1266 hi:1275 sum:12705
**HOLDS** agent:0x00000012 n:10 lo:1172 hi:1182 sum:11774
**HOLDS** agent:0x00000200 n:10 lo:1964 hi:1973 sum:19685
**HOLDS** agent:0x00000300 n:10 lo:4479 hi:4499 sum:44897
**DELIVER** up_s:8080 heap:123352 fetched:586 unanswered:332 broken:89 resumed:1940 empty:244 served:1953 wants:1993 early:119 wantq_drop:0 superseded:1

---

@LAT103LON8275 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8451498 ±21 frame:8000
seq: 1344
follows: 0x00000011:1286 0x00000012:1195 0x00000100:906 0x00000200:1984 0x00000300:4524
said: 1 | **ENTWIN** t_ms:8440806 stream:0x732acba3 wall:0 window_ms:600017 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-55
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,5ce28c488e0c,c2e94427adcf,980d67f79619
said: 13 | **COVERED** windows:2 entities:10 window_ms:1200016 first_t_ms:7240792 last_t_ms:7840790 covered_by:@LAT103LON8274
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-55 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-74 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-86 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95 windows:1
```

---

@LAT106LON120 | created:0 | updated:0

**BAR** frame:8000 bar:14 own:10 held:40 terms:9 digest:0x4b93e0ea settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1333 hi:1342 sum:13375
**HOLDS** agent:0x00000011 n:10 lo:1276 hi:1285 sum:12805
**HOLDS** agent:0x00000012 n:10 lo:1183 hi:1193 sum:11884
**HOLDS** agent:0x00000200 n:10 lo:1975 hi:1984 sum:19795
**HOLDS** agent:0x00000300 n:10 lo:4501 hi:4520 sum:45109
**DELIVER** up_s:8676 heap:122812 fetched:630 unanswered:358 broken:95 resumed:2115 empty:259 served:2097 wants:2139 early:119 wantq_drop:0 superseded:1

---

@LAT103LON8276 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9051501 ±21 frame:8000
seq: 1355
follows: 0x00000011:1296 0x00000012:1206 0x00000100:918 0x00000200:1994 0x00000300:4544
said: 1 | **ENTWIN** t_ms:9040805 stream:0x732acba3 wall:0 window_ms:599999 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-55
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,5ce28c488e0c,c2e94427adcf,0283cce0e689,980d67f79619
```

---

@LAT106LON121 | created:0 | updated:0

**BAR** frame:8000 bar:15 own:10 held:40 terms:9 digest:0x033334fc settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1343 hi:1353 sum:13484
**HOLDS** agent:0x00000011 n:10 lo:1286 hi:1295 sum:12905
**HOLDS** agent:0x00000012 n:10 lo:1194 hi:1204 sum:11994
**HOLDS** agent:0x00000200 n:10 lo:1985 hi:1994 sum:19895
**HOLDS** agent:0x00000300 n:10 lo:4522 hi:4541 sum:45319
**DELIVER** up_s:9280 heap:122556 fetched:667 unanswered:386 broken:104 resumed:2253 empty:278 served:2211 wants:2256 early:119 wantq_drop:0 superseded:1

---

@LAT106LON122 | created:0 | updated:0

**BAR** frame:8000 bar:16 own:10 held:40 terms:9 digest:0x8fff28fa settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1354 hi:1364 sum:13594
**HOLDS** agent:0x00000011 n:10 lo:1296 hi:1306 sum:13014
**HOLDS** agent:0x00000012 n:10 lo:1205 hi:1215 sum:12104
**HOLDS** agent:0x00000200 n:10 lo:1995 hi:2004 sum:19995
**HOLDS** agent:0x00000300 n:10 lo:4543 hi:4562 sum:45528
**DELIVER** up_s:9879 heap:122808 fetched:709 unanswered:407 broken:112 resumed:2407 empty:296 served:2351 wants:2397 early:119 wantq_drop:0 superseded:1

---

@LAT106LON123 | created:0 | updated:0

**BAR** frame:8000 bar:17 own:10 held:40 terms:9 digest:0x5345e039 settled_ms:300028
**HOLDS** agent:0x00000010 n:10 lo:1365 hi:1374 sum:13695
**HOLDS** agent:0x00000011 n:10 lo:1307 hi:1316 sum:13115
**HOLDS** agent:0x00000012 n:10 lo:1216 hi:1226 sum:12214
**HOLDS** agent:0x00000200 n:10 lo:2005 hi:2014 sum:20095
**HOLDS** agent:0x00000300 n:10 lo:4564 hi:4582 sum:45730
**DELIVER** up_s:10478 heap:122552 fetched:748 unanswered:431 broken:117 resumed:2535 empty:313 served:2479 wants:2525 early:119 wantq_drop:0 superseded:1

---

@LAT103LON8277 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10851526 ±21 frame:8000
seq: 1386
follows: 0x00000011:1328 0x00000012:1239 0x00000100:950 0x00000200:2024 0x00000300:4605
said: 1 | **ENTWIN** t_ms:10840812 stream:0x732acba3 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-54
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 11 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,980d67f79619,02c57d2f9717,0283cce0e689,c2e94427adcf,5ce28c488e0c
said: 13 | **COVERED** windows:2 entities:11 window_ms:1200007 first_t_ms:9640813 last_t_ms:10240812 covered_by:@LAT103LON8276
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-54 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-67 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-73 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-85 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-85 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-91 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-92 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-95 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-97 windows:1
```

---

@LAT106LON124 | created:0 | updated:0

**BAR** frame:8000 bar:18 own:10 held:40 terms:9 digest:0xabc37525 settled_ms:300010
**HOLDS** agent:0x00000010 n:10 lo:1375 hi:1384 sum:13795
**HOLDS** agent:0x00000011 n:10 lo:1317 hi:1326 sum:13215
**HOLDS** agent:0x00000012 n:10 lo:1227 hi:1237 sum:12324
**HOLDS** agent:0x00000200 n:10 lo:2015 hi:2024 sum:20195
**HOLDS** agent:0x00000300 n:10 lo:4584 hi:4602 sum:45930
**DELIVER** up_s:11078 heap:122044 fetched:790 unanswered:458 broken:125 resumed:2653 empty:334 served:2627 wants:2679 early:119 wantq_drop:0 superseded:1

---

@LAT106LON125 | created:0 | updated:0

**BAR** frame:8000 bar:19 own:10 held:38 terms:9 digest:0xb5144cb4 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1385 hi:1395 sum:13904
**HOLDS** agent:0x00000011 n:10 lo:1327 hi:1337 sum:13324
**HOLDS** agent:0x00000012 n:10 lo:1238 hi:1248 sum:12434
**HOLDS** agent:0x00000200 n:10 lo:2025 hi:2034 sum:20295
**HOLDS** agent:0x00000300 n:8 lo:4604 hi:4623 sum:36901
**DELIVER** up_s:11681 heap:122296 fetched:828 unanswered:482 broken:136 resumed:2797 empty:344 served:2738 wants:2790 early:119 wantq_drop:0 superseded:2

---

@LAT103LON8278 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 62003 ±0 frame:7000
seq: 1406
follows: 0x00000011:1348 0x00000012:1259 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **ENTWIN** t_ms:50253 stream:0x5560e405 wall:0 window_ms:62003 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8279 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60043 ±0 frame:7500
seq: 1408
follows: 0x00000011:1352 0x00000012:1267 0x00000100:998 0x00000200:2044 0x00000300:4641
said: 1 | **ENTWIN** t_ms:381746 stream:0xc9e0e898 wall:0 window_ms:60043 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT106LON126 | created:0 | updated:0

**BAR** frame:7500 bar:1 own:10 held:35 terms:9 digest:0xd2c5d402 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1407 hi:1417 sum:14124
**HOLDS** agent:0x00000011 n:8 lo:1354 hi:1361 sum:10860
**HOLDS** agent:0x00000012 n:10 lo:1267 hi:1276 sum:12715
**HOLDS** agent:0x00000200 n:8 lo:2047 hi:2054 sum:16404
**HOLDS** agent:0x00000300 n:9 lo:4642 hi:4660 sum:41866
**DELIVER** up_s:909 heap:122936 fetched:67 unanswered:56 broken:5 resumed:210 empty:29 served:209 wants:213 early:41 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:4 split:1
**SPLIT** agent:0x00000012 grammar:0xaf98ac36

---

@LAT103LON8280 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1213201 ±21 frame:7500
seq: 1428
follows: 0x00000011:1372 0x00000012:1287 0x00000100:1019 0x00000200:2064 0x00000300:4681
said: 1 | **ENTWIN** t_ms:1534941 stream:0xc9e0e898 wall:0 window_ms:600000 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 8 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 9 | **COVERED** windows:1 entities:7 window_ms:553153 first_t_ms:934941 last_t_ms:934941 covered_by:@LAT103LON8279
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
```

---

@LAT106LON127 | created:0 | updated:0

**BAR** frame:7500 bar:2 own:10 held:40 terms:9 digest:0x4d262fda settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1418 hi:1427 sum:14225
**HOLDS** agent:0x00000011 n:10 lo:1362 hi:1371 sum:13665
**HOLDS** agent:0x00000012 n:10 lo:1277 hi:1287 sum:12821
**HOLDS** agent:0x00000200 n:10 lo:2055 hi:2064 sum:20595
**HOLDS** agent:0x00000300 n:10 lo:4662 hi:4680 sum:46710
**DELIVER** up_s:1514 heap:123740 fetched:107 unanswered:78 broken:11 resumed:334 empty:51 served:340 wants:349 early:41 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:4 split:1
**SPLIT** agent:0x00000012 grammar:0xaf98ac36

---

@LAT103LON8281 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1813206 ±21 frame:7500
seq: 1439
follows: 0x00000011:1382 0x00000012:1298 0x00000100:1030 0x00000200:2075 0x00000300:4702
said: 1 | **ENTWIN** t_ms:2134941 stream:0xc9e0e898 wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT106LON128 | created:0 | updated:0

**BAR** frame:7500 bar:3 own:10 held:39 terms:9 digest:0xcd88d703 settled_ms:300028
**HOLDS** agent:0x00000010 n:10 lo:1429 hi:1438 sum:14335
**HOLDS** agent:0x00000011 n:10 lo:1373 hi:1382 sum:13775
**HOLDS** agent:0x00000012 n:9 lo:1288 hi:1297 sum:11633
**HOLDS** agent:0x00000200 n:10 lo:2065 hi:2075 sum:20704
**HOLDS** agent:0x00000300 n:10 lo:4682 hi:4701 sum:46919
**DELIVER** up_s:2110 heap:123980 fetched:142 unanswered:124 broken:20 resumed:458 empty:68 served:474 wants:486 early:41 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON1458 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2461505 ±21 frame:7500
seq: 1450
follows: 0x00000011:1394 0x00000012:1308 0x00000100:1044 0x00000200:2086 0x00000300:4726
said: 1 | **LINKWIN** t_ms:2783235 stream:0xc9e0e898 wall:0 window_ms:60008
said: 2 | **LINK** peer:0x00000011 proto:espnow n:139 rssi_min:-42 rssi_med:-40 rssi_max:-36
said: 3 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-58 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:espnow n:110 rssi_min:-51 rssi_med:-49 rssi_max:-46
said: 5 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-59 rssi_med:-52 rssi_max:-46
said: 6 | **LINK** peer:0x00000012 proto:espnow n:76 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000300 proto:espnow n:104 rssi_min:-92 rssi_med:-43 rssi_max:-40
said: 8 | **LINK** peer:0x00000011 proto:ble n:51 rssi_min:-58 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-77 rssi_med:-58 rssi_max:-54
```

---

@LAT103LON1459 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2521525 ±21 frame:7500
seq: 1451
follows: 0x00000011:1395 0x00000012:1309 0x00000100:1045 0x00000200:2087 0x00000300:4728
said: 1 | **LINKWIN** t_ms:2843254 stream:0xc9e0e898 wall:0 window_ms:60019
said: 2 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000300 proto:espnow n:228 rssi_min:-45 rssi_med:-43 rssi_max:-41
said: 4 | **LINK** peer:0x00000012 proto:espnow n:138 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:espnow n:73 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 6 | **LINK** peer:0x00000200 proto:espnow n:133 rssi_min:-49 rssi_med:-49 rssi_max:-43
said: 7 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-79 rssi_med:-46 rssi_max:-39
said: 8 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-66 rssi_med:-58 rssi_max:-54
said: 9 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-82 rssi_med:-55 rssi_max:-52
```

---

@LAT103LON1460 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2581537 ±21 frame:7500
seq: 1452
follows: 0x00000011:1396 0x00000012:1310 0x00000100:1046 0x00000200:2088 0x00000300:4730
said: 1 | **LINKWIN** t_ms:2903264 stream:0xc9e0e898 wall:0 window_ms:60011
said: 2 | **LINK** peer:0x00000300 proto:espnow n:277 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000012 proto:espnow n:130 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 4 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-59 rssi_max:-55
said: 5 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-59 rssi_med:-58 rssi_max:-55
said: 6 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-70 rssi_med:-46 rssi_max:-39
said: 7 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-58 rssi_med:-55 rssi_max:-52
said: 8 | **LINK** peer:0x00000011 proto:espnow n:143 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 9 | **LINK** peer:0x00000200 proto:espnow n:124 rssi_min:-49 rssi_med:-49 rssi_max:-46
```

---

@LAT103LON1461 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2641538 ±21 frame:7500
seq: 1453
follows: 0x00000011:1397 0x00000012:1310 0x00000100:1047 0x00000200:2089 0x00000300:4732
said: 1 | **LINKWIN** t_ms:2963264 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-34 rssi_med:-32 rssi_max:-30
said: 3 | **LINK** peer:0x00000300 proto:espnow n:124 rssi_min:-45 rssi_med:-43 rssi_max:-41
said: 4 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-60 rssi_med:-58 rssi_max:-56
said: 5 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 6 | **LINK** peer:0x00000011 proto:espnow n:95 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 7 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-79 rssi_med:-58 rssi_max:-54
said: 8 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-60 rssi_med:-53 rssi_max:-46
said: 9 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-46 rssi_max:-38
```

---

@LAT103LON1462 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2701538 ±21 frame:7500
seq: 1454
follows: 0x00000011:1398 0x00000012:1311 0x00000100:1048 0x00000200:2090 0x00000300:4734
said: 1 | **LINKWIN** t_ms:3023264 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:74 rssi_min:-82 rssi_med:-52 rssi_max:-46
said: 3 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-58 rssi_med:-55 rssi_max:-52
said: 4 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-59 rssi_med:-58 rssi_max:-56
said: 5 | **LINK** peer:0x00000011 proto:espnow n:101 rssi_min:-41 rssi_med:-40 rssi_max:-37
said: 6 | **LINK** peer:0x00000200 proto:espnow n:124 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000300 proto:espnow n:223 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-58 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:espnow n:118 rssi_min:-35 rssi_med:-31 rssi_max:-30
```

---

@LAT106LON129 | created:0 | updated:0

**BAR** frame:7500 bar:4 own:10 held:38 terms:9 digest:0xc9a9ac56 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1440 hi:1449 sum:14445
**HOLDS** agent:0x00000011 n:10 lo:1383 hi:1392 sum:13875
**HOLDS** agent:0x00000012 n:8 lo:1299 hi:1307 sum:10425
**HOLDS** agent:0x00000200 n:10 lo:2076 hi:2085 sum:20805
**HOLDS** agent:0x00000300 n:10 lo:4703 hi:4723 sum:47137
**DELIVER** up_s:2712 heap:123992 fetched:185 unanswered:159 broken:25 resumed:607 empty:88 served:607 wants:619 early:41 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON1463 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2761538 ±21 frame:7500
seq: 1455
follows: 0x00000011:1399 0x00000012:1312 0x00000100:1049 0x00000200:2091 0x00000300:4736
said: 1 | **LINKWIN** t_ms:3083264 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:49 rssi_min:-81 rssi_med:-58 rssi_max:-55
said: 3 | **LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000300 proto:espnow n:127 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 5 | **LINK** peer:0x00000012 proto:espnow n:75 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000200 proto:espnow n:91 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-46 rssi_max:-39
said: 8 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-79 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:espnow n:80 rssi_min:-41 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON1464 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2821539 ±21 frame:7500
seq: 1456
follows: 0x00000011:1400 0x00000012:1314 0x00000100:1050 0x00000200:2092 0x00000300:4738
said: 1 | **LINKWIN** t_ms:3143265 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000300 proto:espnow n:125 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 4 | **LINK** peer:0x00000011 proto:espnow n:114 rssi_min:-42 rssi_med:-40 rssi_max:-36
said: 5 | **LINK** peer:0x00000012 proto:espnow n:107 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-73 rssi_med:-58 rssi_max:-55
said: 7 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-45
said: 8 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 9 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-80 rssi_med:-46 rssi_max:-39
```

---

@LAT103LON1465 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2881568 ±21 frame:7500
seq: 1457
follows: 0x00000011:1401 0x00000012:1315 0x00000100:1051 0x00000200:2093 0x00000300:4740
said: 1 | **LINKWIN** t_ms:3203294 stream:0xc9e0e898 wall:0 window_ms:60029
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:109 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:95 rssi_min:-42 rssi_med:-40 rssi_max:-36
said: 5 | **LINK** peer:0x00000300 proto:espnow n:206 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-59 rssi_med:-55 rssi_max:-52
said: 7 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-76 rssi_med:-58 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-46 rssi_max:-39
said: 9 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-59 rssi_med:-52 rssi_max:-46
```

---

@LAT103LON1466 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1467 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1468 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1469 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1470 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1471 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1472 | created:0 | updated:0

**link window**

```ttdb-episode
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
@LAT106LON130 | created:0 | updated:0

**BAR** frame:7500 bar:5 own:10 held:40 terms:9 digest:0xdd4d4ce8 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1450 hi:1459 sum:14545
**HOLDS** agent:0x00000011 n:10 lo:1394 hi:1403 sum:13985
**HOLDS** agent:0x00000012 n:10 lo:1308 hi:1317 sum:13125
**HOLDS** agent:0x00000200 n:10 lo:2086 hi:2095 sum:20905
**HOLDS** agent:0x00000300 n:10 lo:4725 hi:4743 sum:47340
**DELIVER** up_s:3311 heap:126416 fetched:226 unanswered:175 broken:31 resumed:712 empty:110 served:737 wants:749 early:41 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON1473 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1474 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1475 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1476 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1477 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1478 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1479 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1480 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1481 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1482 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT106LON131 | created:0 | updated:0

**BAR** frame:7500 bar:6 own:10 held:40 terms:8 digest:0xe5fee0c4 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1460 hi:1469 sum:14645
**HOLDS** agent:0x00000011 n:10 lo:1404 hi:1413 sum:14085
**HOLDS** agent:0x00000012 n:10 lo:1318 hi:1328 sum:13231
**HOLDS** agent:0x00000200 n:10 lo:2096 hi:2105 sum:21005
**HOLDS** agent:0x00000300 n:10 lo:4745 hi:4763 sum:47540
**DELIVER** up_s:3914 heap:123464 fetched:263 unanswered:195 broken:34 resumed:811 empty:130 served:866 wants:879 early:41 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON1483 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1484 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1485 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1486 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1487 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON8282 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4228442 ±21 frame:7500
seq: 1480
follows: 0x00000011:1424 0x00000012:1338 0x00000100:1076 0x00000200:2116 0x00000300:4785
said: 1 | **ENTWIN** t_ms:4550125 stream:0xc9e0e898 wall:0 window_ms:60042 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-95
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-97
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON1488 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1489 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1490 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1491 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON5030 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4399631 ±21 frame:7500
seq: 2119
follows: 0x00000010:1482 0x00000011:1428 0x00000012:1341 0x00000100:1081 0x00000300:4791
said: 1 | **LINKWIN** t_ms:4721379 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-85 rssi_med:-60 rssi_max:-54
said: 3 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-30 rssi_med:-28 rssi_max:-27
said: 4 | **LINK** peer:0x00000300 proto:espnow n:81 rssi_min:-54 rssi_med:-40 rssi_max:-37
said: 5 | **LINK** peer:0x00000012 proto:espnow n:56 rssi_min:-29 rssi_med:-27 rssi_max:-26
said: 6 | **LINK** peer:0x00000010 proto:espnow n:107 rssi_min:-56 rssi_med:-47 rssi_max:-42
said: 7 | **LINK** peer:0x00000011 proto:espnow n:81 rssi_min:-68 rssi_med:-62 rssi_max:-49
said: 8 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-65 rssi_max:-53
said: 9 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-43 rssi_max:-40
```

---

@LAT105LON5031 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4459685 ±21 frame:7500
seq: 2120
follows: 0x00000010:1483 0x00000011:1429 0x00000012:1342 0x00000100:1082 0x00000300:4793
said: 1 | **LINKWIN** t_ms:4781426 stream:0xc9e0e898 wall:0 window_ms:60051
said: 2 | **LINK** peer:0x00000300 proto:espnow n:147 rssi_min:-54 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-30 rssi_med:-28 rssi_max:-27
said: 4 | **LINK** peer:0x00000012 proto:espnow n:107 rssi_min:-32 rssi_med:-26 rssi_max:-26
said: 5 | **LINK** peer:0x00000010 proto:espnow n:79 rssi_min:-56 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000011 proto:espnow n:113 rssi_min:-67 rssi_med:-60 rssi_max:-55
said: 7 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-51
said: 8 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-80 rssi_med:-68 rssi_max:-55
said: 9 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-81 rssi_med:-59 rssi_max:-53
```

---

@LAT105LON5032 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1519178 ±0 frame:11000
seq: 4871
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1092 0x00000200:2120
said: 1 | **LINKWIN** t_ms:1505622 stream:0xed9951d6 wall:0 window_ms:67762
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-37 rssi_med:-34 rssi_max:-34
said: 3 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT105LON5033 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 59993 ±21 frame:8500
seq: 2121
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4929
said: 1 | **LINKWIN** t_ms:187868 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:90 rssi_min:-46 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-73 rssi_med:-52 rssi_max:-46
```

---

@LAT105LON5034 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1579205 ±0 frame:11000
seq: 4873
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1093 0x00000200:2120
said: 1 | **LINKWIN** t_ms:1565649 stream:0xed9951d6 wall:0 window_ms:60027
said: 2 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-38 rssi_med:-34 rssi_max:-34
said: 3 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT105LON5035 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4440985 ±21 frame:7500
seq: 1429
follows: 0x00000010:1483 0x00000012:1342 0x00000100:1082 0x00000200:2119 0x00000300:4791
said: 1 | **LINKWIN** t_ms:4762717 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-71 rssi_max:-60
said: 3 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-61 rssi_max:-49
said: 4 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-83 rssi_med:-37 rssi_max:-32
said: 5 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-83 rssi_med:-44 rssi_max:-41
said: 6 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-44 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000200 proto:espnow n:71 rssi_min:-68 rssi_med:-63 rssi_max:-59
said: 8 | **LINK** peer:0x00000300 proto:espnow n:132 rssi_min:-31 rssi_med:-28 rssi_max:-27
said: 9 | **LINK** peer:0x00000012 proto:espnow n:93 rssi_min:-49 rssi_med:-45 rssi_max:-43
```

---

@LAT105LON5036 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4371632 ±21 frame:7500
seq: 1341
follows: 0x00000010:1482 0x00000011:1427 0x00000100:1081 0x00000200:2118 0x00000300:4789
said: 1 | **LINKWIN** t_ms:4693366 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:127 rssi_min:-57 rssi_med:-45 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:espnow n:138 rssi_min:-27 rssi_med:-25 rssi_max:-23
said: 4 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-19 rssi_med:-17 rssi_max:-17
said: 5 | **LINK** peer:0x00000010 proto:espnow n:194 rssi_min:-60 rssi_med:-45 rssi_max:-40
said: 6 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-39 rssi_max:-37
said: 7 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-61 rssi_max:-49
said: 8 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-41 rssi_max:-37
said: 9 | **LINK** peer:0x00000200 proto:espnow n:131 rssi_min:-27 rssi_med:-25 rssi_max:-23
```

---

@LAT105LON5037 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 117996 ±21 frame:8500
seq: 2123
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4930
said: 1 | **LINKWIN** t_ms:247868 stream:0x678473b9 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000300 proto:espnow n:97 rssi_min:-42 rssi_med:-37 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-49
```

---

@LAT105LON5038 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1639278 ±0 frame:11000
seq: 4875
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1094 0x00000200:2120
said: 1 | **LINKWIN** t_ms:1625722 stream:0xed9951d6 wall:0 window_ms:60073
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-39 rssi_med:-34 rssi_max:-34
said: 3 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT105LON5039 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4431631 ±21 frame:7500
seq: 1342
follows: 0x00000010:1483 0x00000011:1428 0x00000100:1082 0x00000200:2119 0x00000300:4791
said: 1 | **LINKWIN** t_ms:4753366 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-84 rssi_med:-65 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-41 rssi_max:-38
said: 5 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-19 rssi_med:-17 rssi_max:-16
said: 6 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-48 rssi_med:-45 rssi_max:-41
said: 7 | **LINK** peer:0x00000200 proto:espnow n:100 rssi_min:-27 rssi_med:-24 rssi_max:-23
said: 8 | **LINK** peer:0x00000300 proto:espnow n:134 rssi_min:-29 rssi_med:-26 rssi_max:-24
said: 9 | **LINK** peer:0x00000010 proto:espnow n:124 rssi_min:-66 rssi_med:-52 rssi_max:-43
```

---

@LAT103LON8283 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 272982 ±21 frame:10500
seq: 1485
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2161 0x00000300:5091
said: 1 | **ENTWIN** t_ms:259619 stream:0x3bead35c wall:0 window_ms:60000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON1492 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON5040 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 175992 ±21 frame:8500
seq: 2124
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4933
said: 1 | **LINKWIN** t_ms:307869 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-61 rssi_med:-52 rssi_max:-46
said: 3 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-40 rssi_med:-36 rssi_max:-33
```

---

@LAT105LON5041 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 235995 ±21 frame:8500
seq: 2125
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4935
said: 1 | **LINKWIN** t_ms:367869 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-38 rssi_med:-36 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-60 rssi_med:-53 rssi_max:-48
```

---

@LAT105LON5042 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 297998 ±21 frame:8500
seq: 2126
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4936
said: 1 | **LINKWIN** t_ms:427868 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-39 rssi_med:-36 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-54 rssi_max:-48
```

---

@LAT105LON5043 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 351998 ±23 frame:8500
seq: 2127
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4937
said: 1 | **LINKWIN** t_ms:487869 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:29 rssi_min:-58 rssi_med:-54 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-37 rssi_med:-35 rssi_max:-35
```

---

@LAT103LON1493 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON8284 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 218558 ±21 frame:12000
seq: 1488
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1359 0x00000200:2165 0x00000300:5103
said: 1 | **ENTWIN** t_ms:203503 stream:0x5d34e552 wall:0 window_ms:60089 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT105LON5044 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 411998 ±0 frame:8500
seq: 2128
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4941
said: 1 | **LINKWIN** t_ms:547869 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:79 rssi_min:-51 rssi_med:-40 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-81 rssi_med:-55 rssi_max:-49
```

---

@LAT105LON5045 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 2059388 ±0 frame:11000
seq: 4890
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1101 0x00000200:2120
said: 1 | **LINKWIN** t_ms:2045832 stream:0xed9951d6 wall:0 window_ms:60052
said: 2 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-37 rssi_med:-34 rssi_max:-34
said: 3 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT105LON5046 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 2120491 ±0 frame:11000
seq: 4892
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1102 0x00000200:2120
said: 1 | **LINKWIN** t_ms:2106935 stream:0xed9951d6 wall:0 window_ms:61103
said: 2 | **LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-37 rssi_med:-34 rssi_max:-34
said: 3 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT105LON5047 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 60000 ±0 frame:9500
seq: 2129
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4943
said: 1 | **LINKWIN** t_ms:643355 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-38 rssi_med:-36 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-81 rssi_med:-54 rssi_max:-47
```

---

@LAT105LON5048 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 51993 ±21 frame:8500
seq: 2131
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5029
said: 1 | **LINKWIN** t_ms:3213502 stream:0xf569ab0e wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-47 rssi_max:-44
said: 3 | **LINK** peer:0x00000300 proto:espnow n:7 rssi_min:-34 rssi_med:-30 rssi_max:-30
```

---

@LAT105LON5049 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 141212 ±21 frame:8500
seq: 2133
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5032
said: 1 | **LINKWIN** t_ms:3324773 stream:0xf569ab0e wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-46 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:9 rssi_min:-30 rssi_med:-30 rssi_max:-29
```

---

@LAT103LON1494 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 60002 ±0 frame:10500
seq: 1489
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2181 0x00000300:5113
said: 1 | **LINKWIN** t_ms:46532 stream:0xb16505e0 wall:0 window_ms:60002
said: 2 | **LINK** peer:0x00000200 proto:espnow n:55 rssi_min:-51 rssi_med:-41 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:ble n:33 rssi_min:-63 rssi_med:-55 rssi_max:-49
```

---

@LAT103LON8285 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60036 ±0 frame:10500
seq: 1490
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2181 0x00000300:5113
said: 1 | **ENTWIN** t_ms:46532 stream:0xb16505e0 wall:0 window_ms:60036 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT105LON5050 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 61903 ±21 frame:9500
seq: 2135
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5034
said: 1 | **LINKWIN** t_ms:47884 stream:0xdfce8729 wall:0 window_ms:61911
said: 2 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-43 rssi_med:-34 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:39 rssi_min:-81 rssi_med:-52 rssi_max:-46
```

---

@LAT105LON5051 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 122306 ±21 frame:9500
seq: 2137
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5038
said: 1 | **LINKWIN** t_ms:107884 stream:0xdfce8729 wall:0 window_ms:60401
said: 2 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-39 rssi_med:-36 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-52 rssi_max:-49
```

---

@LAT105LON5052 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 182310 ±21 frame:9500
seq: 2138
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5040
said: 1 | **LINKWIN** t_ms:170196 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-56 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:141 rssi_min:-40 rssi_med:-37 rssi_max:-34
```

---

@LAT105LON5053 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 242306 ±22 frame:9500
seq: 2139
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5042
said: 1 | **LINKWIN** t_ms:230196 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-39 rssi_med:-38 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:49 rssi_min:-59 rssi_med:-53 rssi_max:-47
```

---

@LAT105LON5054 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 302306 ±25 frame:9500
seq: 2140
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5046
said: 1 | **LINKWIN** t_ms:290196 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-54 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:61 rssi_min:-45 rssi_med:-35 rssi_max:-29
```

---

@LAT105LON5055 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 133458 ±21 frame:9500
seq: 2141
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5048
said: 1 | **LINKWIN** t_ms:358618 stream:0xdfce8729 wall:0 window_ms:61409
said: 2 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-37 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-50 rssi_max:-47
```

---

@LAT105LON5056 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 193459 ±21 frame:9500
seq: 2143
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5050
said: 1 | **LINKWIN** t_ms:420027 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-69 rssi_med:-52 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:69 rssi_min:-53 rssi_med:-37 rssi_max:-34
```

---

@LAT105LON5057 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 253460 ±21 frame:9500
seq: 2144
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:480027 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:67 rssi_min:-52 rssi_med:-38 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-79 rssi_med:-54 rssi_max:-46
```

---

@LAT105LON5058 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1073202 ±0 frame:8500
seq: 2146
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:1061712 stream:0xb8b08067 wall:0 window_ms:1073202
said: 2 | **LINK** peer:0x00000300 proto:espnow n:3 rssi_min:-47 rssi_med:-47 rssi_max:-47
```

---

@LAT105LON5059 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1133193 ±21 frame:8500
seq: 2147
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:1121715 stream:0xb8b08067 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-75 rssi_med:-61 rssi_max:-58
said: 3 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-91 rssi_med:-49 rssi_max:-47
```

---

@LAT105LON5060 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 68995 ±21 frame:7500
seq: 2148
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5060
said: 1 | **LINKWIN** t_ms:57427 stream:0x1f824110 wall:0 window_ms:61386
said: 2 | **LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-40 rssi_med:-37 rssi_max:-32
said: 3 | **LINK** peer:0x00000300 proto:ble n:50 rssi_min:-82 rssi_med:-54 rssi_max:-48
```

---

@LAT105LON5061 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 139634 ±21 frame:7500
seq: 2150
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5067
said: 1 | **LINKWIN** t_ms:129626 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-53 rssi_med:-37 rssi_max:-29
said: 3 | **LINK** peer:0x00000300 proto:ble n:46 rssi_min:-75 rssi_med:-53 rssi_max:-44
```

---

@LAT105LON5062 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 199636 ±21 frame:7500
seq: 2152
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5069
said: 1 | **LINKWIN** t_ms:189626 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:73 rssi_min:-47 rssi_med:-35 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-67 rssi_med:-45 rssi_max:-37
```

---

@LAT103LON1495 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 120002 ±0 frame:10500
seq: 1491
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2183 0x00000300:5113
said: 1 | **LINKWIN** t_ms:106535 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-78 rssi_med:-60 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:130 rssi_min:-61 rssi_med:-46 rssi_max:-35
```

---

@LAT105LON5063 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 259638 ±21 frame:7500
seq: 2153
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5071
said: 1 | **LINKWIN** t_ms:249627 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:83 rssi_min:-44 rssi_med:-27 rssi_max:-25
```

---

@LAT105LON5064 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 95985 ±21 frame:7500
seq: 2154
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5075
said: 1 | **LINKWIN** t_ms:84171 stream:0xb4b25252 wall:0 window_ms:61315
said: 2 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-29 rssi_med:-24 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT105LON5065 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 155984 ±21 frame:7500
seq: 2156
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5077
said: 1 | **LINKWIN** t_ms:145486 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:64 rssi_min:-28 rssi_med:-25 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-70 rssi_med:-40 rssi_max:-36
```

---

@LAT105LON5066 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 215985 ±21 frame:7500
seq: 2157
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5079
said: 1 | **LINKWIN** t_ms:205486 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:64 rssi_min:-26 rssi_med:-25 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-47 rssi_med:-41 rssi_max:-37
```

---

@LAT105LON5067 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 141238 ±21 frame:10500
seq: 2158
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5086
said: 1 | **LINKWIN** t_ms:127872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-29 rssi_med:-27 rssi_max:-25
said: 3 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-47 rssi_med:-43 rssi_max:-39
```

---

@LAT105LON5068 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 201238 ±21 frame:10500
seq: 2160
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5088
said: 1 | **LINKWIN** t_ms:187872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:65 rssi_min:-30 rssi_med:-28 rssi_max:-24
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-50 rssi_med:-43 rssi_max:-40
```

---

@LAT105LON5069 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT105LON5070 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT105LON5071 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 107656 ±22 frame:12000
seq: 2163
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000300:5097
said: 1 | **LINKWIN** t_ms:90717 stream:0x5d34e552 wall:0 window_ms:61963
said: 2 | **LINK** peer:0x00000300 proto:espnow n:65 rssi_min:-27 rssi_med:-23 rssi_max:-22
said: 3 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-45 rssi_med:-41 rssi_max:-35
```

---

@LAT105LON5072 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT103LON1496 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 180002 ±0 frame:10500
seq: 1492
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2184 0x00000300:5113
said: 1 | **LINKWIN** t_ms:166535 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:124 rssi_min:-65 rssi_med:-49 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-81 rssi_med:-61 rssi_max:-49
```

---

@LAT105LON5073 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 60001 ±0 frame:9500
seq: 2166
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1467 0x00000300:5103
said: 1 | **LINKWIN** t_ms:47860 stream:0x69cc95ce wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-40 rssi_med:-37 rssi_max:-33
```

---

@LAT105LON5074 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 120001 ±0 frame:9500
seq: 2168
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1470 0x00000300:5103
said: 1 | **LINKWIN** t_ms:107861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-42 rssi_med:-39 rssi_max:-33
```

---

@LAT105LON5075 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 180001 ±0 frame:9500
seq: 2169
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1471 0x00000300:5103
said: 1 | **LINKWIN** t_ms:167861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-41 rssi_med:-39 rssi_max:-36
```

---

@LAT105LON5076 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 240001 ±0 frame:9500
seq: 2170
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1472 0x00000300:5103
said: 1 | **LINKWIN** t_ms:227861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-40 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON5077 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 300030 ±0 frame:9500
seq: 2171
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1473 0x00000300:5103
said: 1 | **LINKWIN** t_ms:287890 stream:0x69cc95ce wall:0 window_ms:60029
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON5078 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 360030 ±0 frame:9500
seq: 2172
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1474 0x00000300:5103
said: 1 | **LINKWIN** t_ms:347890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-40 rssi_med:-39 rssi_max:-39
```

---

@LAT105LON5079 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 420030 ±0 frame:9500
seq: 2173
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1475 0x00000300:5103
said: 1 | **LINKWIN** t_ms:407890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT103LON1497 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 240002 ±0 frame:10500
seq: 1493
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2185 0x00000300:5113
said: 1 | **LINKWIN** t_ms:226534 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:109 rssi_min:-61 rssi_med:-48 rssi_max:-40
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-90 rssi_med:-63 rssi_max:-53
```

---

@LAT104LON167 | created:0 | updated:0

**carried through @LAT103LON1457**

```ttdb-carried
through: 1457
through: 8245
```

---

@LAT105LON5080 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 480030 ±0 frame:9500
seq: 2174
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1476 0x00000300:5103
said: 1 | **LINKWIN** t_ms:467890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-40 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON5081 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 540030 ±0 frame:9500
seq: 2175
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1477 0x00000300:5103
said: 1 | **LINKWIN** t_ms:527890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON5082 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 600030 ±0 frame:9500
seq: 2176
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1478 0x00000300:5103
said: 1 | **LINKWIN** t_ms:587890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-39 rssi_med:-39 rssi_max:-39
```

---

@LAT105LON5083 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 660030 ±0 frame:9500
seq: 2177
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1479 0x00000300:5103
said: 1 | **LINKWIN** t_ms:647890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-43 rssi_med:-39 rssi_max:-38
```

---

@LAT103LON1498 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 300002 ±0 frame:10500
seq: 1494
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2186 0x00000300:5113
said: 1 | **LINKWIN** t_ms:286535 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-60 rssi_max:-54
said: 3 | **LINK** peer:0x00000200 proto:espnow n:88 rssi_min:-54 rssi_med:-47 rssi_max:-44
```

---

@LAT105LON5084 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 720030 ±0 frame:9500
seq: 2178
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1480 0x00000300:5103
said: 1 | **LINKWIN** t_ms:707890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-41 rssi_med:-39 rssi_max:-37
```

---

@LAT105LON5085 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT105LON5086 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT103LON1499 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 360002 ±0 frame:10500
seq: 1495
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2187 0x00000300:5113
said: 1 | **LINKWIN** t_ms:346534 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-72 rssi_med:-59 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:espnow n:76 rssi_min:-51 rssi_med:-47 rssi_max:-44
```

---

@LAT105LON5087 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 900077 ±21 frame:9500
seq: 2181
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:887945 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-71 rssi_med:-57 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-88 rssi_med:-69 rssi_max:-49
```

---

@LAT105LON5088 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 75414 ±21 frame:10500
seq: 2182
follows: 0x00000010:1490 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:61947 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:91 rssi_min:-54 rssi_med:-43 rssi_max:-36
said: 3 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-57 rssi_max:-49
```

---

@LAT105LON5089 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 135433 ±21 frame:10500
seq: 2184
follows: 0x00000010:1491 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:121966 stream:0xb16505e0 wall:0 window_ms:60019
said: 2 | **LINK** peer:0x00000010 proto:espnow n:161 rssi_min:-56 rssi_med:-46 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-62 rssi_max:-55
```

---

@LAT105LON5090 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 195434 ±21 frame:10500
seq: 2185
follows: 0x00000010:1492 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:181966 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-69 rssi_med:-48 rssi_max:-37
said: 3 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-75 rssi_med:-62 rssi_max:-55
```

---

@LAT105LON5091 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 255445 ±21 frame:10500
seq: 2186
follows: 0x00000010:1493 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:241977 stream:0xb16505e0 wall:0 window_ms:60011
said: 2 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-60 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-62 rssi_max:-54
```

---

@LAT105LON5092 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 315446 ±21 frame:10500
seq: 2187
follows: 0x00000010:1494 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:301978 stream:0xb16505e0 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000010 proto:espnow n:107 rssi_min:-48 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-70 rssi_med:-58 rssi_max:-56
```

---

@LAT105LON5093 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 375447 ±21 frame:10500
seq: 2188
follows: 0x00000010:1495 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:361978 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:71 rssi_min:-48 rssi_med:-45 rssi_max:-42
said: 3 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-71 rssi_med:-61 rssi_max:-57
```

---

@LAT103LON1500 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 420002 ±0 frame:10500
seq: 1496
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2188 0x00000300:5113
said: 1 | **LINKWIN** t_ms:406535 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:74 rssi_min:-72 rssi_med:-60 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:96 rssi_min:-51 rssi_med:-48 rssi_max:-47
```

---

@LAT105LON5094 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 435448 ±21 frame:10500
seq: 2189
follows: 0x00000010:1496 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:421977 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:115 rssi_min:-48 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-71 rssi_med:-60 rssi_max:-57
```

---

@LAT103LON1501 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 480002 ±0 frame:10500
seq: 1497
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2189 0x00000300:5113
said: 1 | **LINKWIN** t_ms:466534 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-60 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:espnow n:57 rssi_min:-53 rssi_med:-49 rssi_max:-45
```

---

@LAT105LON5095 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 495447 ±21 frame:10500
seq: 2190
follows: 0x00000010:1497 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:481978 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:57 rssi_min:-49 rssi_med:-45 rssi_max:-43
said: 3 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-73 rssi_med:-60 rssi_max:-57
```

---

@LAT103LON1502 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 540002 ±0 frame:10500
seq: 1498
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2190 0x00000300:5113
said: 1 | **LINKWIN** t_ms:526534 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:52 rssi_min:-56 rssi_med:-49 rssi_max:-46
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-75 rssi_med:-61 rssi_max:-56
```

---

@LAT105LON5096 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 555448 ±21 frame:10500
seq: 2191
follows: 0x00000010:1498 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5113
said: 1 | **LINKWIN** t_ms:541978 stream:0xb16505e0 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-60 rssi_max:-59
said: 3 | **LINK** peer:0x00000010 proto:espnow n:61 rssi_min:-47 rssi_med:-46 rssi_max:-45
```
@LAT106LON132 | created:0 | updated:0

**BAR** frame:45500 bar:3 own:0 held:0 terms:0 digest:0x00000000 settled_ms:849281
**DELIVER** up_s:4 heap:126364 fetched:0 unanswered:0 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0
@LAT106LON133 | created:0 | updated:0

**BAR** frame:45500 bar:2 own:0 held:0 terms:0 digest:0x00000000 settled_ms:1449281
**DELIVER** up_s:5 heap:125280 fetched:0 unanswered:0 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0
@LAT106LON134 | created:0 | updated:0

**BAR** frame:45500 bar:4 own:0 held:0 terms:0 digest:0x00000000 settled_ms:328332
**DELIVER** up_s:26 heap:123068 fetched:0 unanswered:5 broken:0 resumed:0 empty:0 served:3 wants:3 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:1
**SPLIT** agent:0x00000300 grammar:0x42e3bb8a
