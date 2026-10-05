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
@LAT103LON8207 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 16485333 ±21 frame:7000
seq: 97
follows: 0x00000011:48 0x00000012:5 0x00000100:390 0x00000200:729 0x00000300:2083
said: 1 | **ENTWIN** t_ms:16554493 stream:0x3c4214c9 wall:0 window_ms:62027 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8208 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 17650209 ±21 frame:7000
seq: 117
follows: 0x00000011:48 0x00000012:5 0x00000100:390 0x00000200:750 0x00000300:2123
said: 1 | **ENTWIN** t_ms:17721383 stream:0x3c4214c9 wall:0 window_ms:598001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 12 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec
said: 13 | **COVERED** windows:1 entities:9 window_ms:566862 first_t_ms:17121382 last_t_ms:17121382 covered_by:@LAT103LON8207
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92 windows:1
```

---

@LAT103LON8209 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 18250215 ±21 frame:7000
seq: 128
follows: 0x00000011:57 0x00000012:5 0x00000100:390 0x00000200:760 0x00000300:2143
said: 1 | **ENTWIN** t_ms:18321383 stream:0x3c4214c9 wall:0 window_ms:600001 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-98
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,84a329c78fec,c2e94427adcf,64677217947d
```

---

@LAT103LON8210 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 19450231 ±21 frame:7000
seq: 149
follows: 0x00000011:79 0x00000012:5 0x00000100:390 0x00000200:782 0x00000300:2185
said: 1 | **ENTWIN** t_ms:19521441 stream:0x3c4214c9 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,5ce28c488e0c,64677217947d,c2e94427adcf
said: 11 | **COVERED** windows:1 entities:10 window_ms:600006 first_t_ms:18921390 last_t_ms:18921390 covered_by:@LAT103LON8209
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-95 windows:1
```

---

@LAT103LON8211 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 20650244 ±21 frame:7000
seq: 170
follows: 0x00000011:100 0x00000012:15 0x00000100:390 0x00000200:803 0x00000300:2228
said: 1 | **ENTWIN** t_ms:20721441 stream:0x3c4214c9 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,5203cfd1b904,c2e94427adcf
said: 12 | **COVERED** windows:1 entities:8 window_ms:600000 first_t_ms:20121441 last_t_ms:20121441 covered_by:@LAT103LON8210
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96 windows:1
```

---

@LAT103LON8212 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21850254 ±21 frame:7000
seq: 191
follows: 0x00000011:121 0x00000012:36 0x00000100:390 0x00000200:823 0x00000300:2269
said: 1 | **ENTWIN** t_ms:21921443 stream:0x3c4214c9 wall:0 window_ms:600002 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,84a329c78fec,64677217947d,0283cce0e689,c2e94427adcf
said: 13 | **COVERED** windows:1 entities:9 window_ms:599999 first_t_ms:21321441 last_t_ms:21321441 covered_by:@LAT103LON8211
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96 windows:1
```

---

@LAT103LON8213 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 23059974 ±21 frame:7000
seq: 212
follows: 0x00000011:142 0x00000012:58 0x00000100:411 0x00000200:844 0x00000300:2311
said: 1 | **ENTWIN** t_ms:23129149 stream:0x3c4214c9 wall:0 window_ms:606529 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,64677217947d,84a329c78fec,5ce28c488e0c,0283cce0e689
said: 12 | **COVERED** windows:1 entities:8 window_ms:603177 first_t_ms:22522619 last_t_ms:22522619 covered_by:@LAT103LON8212
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97 windows:1
```

---

@LAT103LON8214 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 24865198 ±21 frame:7000
seq: 243
follows: 0x00000011:174 0x00000012:90 0x00000100:443 0x00000200:874 0x00000300:2373
said: 1 | **ENTWIN** t_ms:24934405 stream:0x3c4214c9 wall:0 window_ms:608172 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,c2e94427adcf,84a329c78fec
said: 12 | **COVERED** windows:2 entities:9 window_ms:1197033 first_t_ms:23723659 last_t_ms:24326182 covered_by:@LAT103LON8213
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-46 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-70 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-78 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-71 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-89 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-90 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-93 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95 windows:1
```

---

@LAT103LON8215 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 25056621 ±21 frame:7000
seq: 247
follows: 0x00000011:179 0x00000012:95 0x00000100:447 0x00000200:878 0x00000300:2382
said: 1 | **ENTWIN** t_ms:25127761 stream:0x3c4214c9 wall:0 window_ms:60044 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8216 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 25165674 ±21 frame:7000
seq: 249
follows: 0x00000011:181 0x00000012:96 0x00000100:449 0x00000200:880 0x00000300:2384
said: 1 | **ENTWIN** t_ms:25235915 stream:0x3c4214c9 wall:0 window_ms:60941 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8217 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 26337811 ±21 frame:7000
seq: 269
follows: 0x00000011:202 0x00000012:117 0x00000100:470 0x00000200:899 0x00000300:2426
said: 1 | **ENTWIN** t_ms:26408982 stream:0x3c4214c9 wall:0 window_ms:592714 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 12 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b
said: 13 | **COVERED** windows:1 entities:8 window_ms:579412 first_t_ms:25814269 last_t_ms:25814269 covered_by:@LAT103LON8216
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
```

---

@LAT103LON8218 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 26935789 ±21 frame:7000
seq: 280
follows: 0x00000011:212 0x00000012:127 0x00000100:480 0x00000200:909 0x00000300:2444
said: 1 | **ENTWIN** t_ms:27008980 stream:0x3c4214c9 wall:0 window_ms:599998 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d,0283cce0e689
```

---

@LAT103LON8219 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 28693639 ±21 frame:7000
seq: 311
follows: 0x00000011:245 0x00000012:160 0x00000100:511 0x00000200:939 0x00000300:2498
said: 1 | **ENTWIN** t_ms:28808980 stream:0x3c4214c9 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c,84a329c78fec
said: 12 | **COVERED** windows:2 entities:9 window_ms:1200000 first_t_ms:27608981 last_t_ms:28208980 covered_by:@LAT103LON8218
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-31 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-68 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-74 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-82 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-84 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95 windows:1
```

---

@LAT103LON8220 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 29439021 ±21 frame:7000
seq: 322
follows: 0x00000011:257 0x00000012:174 0x00000100:520 0x00000200:951 0x00000300:2525
said: 1 | **ENTWIN** t_ms:29552300 stream:0x3c4214c9 wall:0 window_ms:62044 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON8221 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 30589772 ±21 frame:7000
seq: 342
follows: 0x00000011:274 0x00000012:192 0x00000100:538 0x00000200:972 0x00000300:2566
said: 1 | **ENTWIN** t_ms:30705075 stream:0x3c4214c9 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 12 | **COVERED** windows:1 entities:11 window_ms:550732 first_t_ms:30105075 last_t_ms:30105075 covered_by:@LAT103LON8220
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
```

---

@LAT103LON8222 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31189791 ±21 frame:7000
seq: 353
follows: 0x00000011:285 0x00000012:203 0x00000100:549 0x00000200:983 0x00000300:2587
said: 1 | **ENTWIN** t_ms:31305088 stream:0x3c4214c9 wall:0 window_ms:600013 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,c2e94427adcf,0283cce0e689
```

---

@LAT103LON8223 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31789784 ±21 frame:7000
seq: 364
follows: 0x00000011:295 0x00000012:214 0x00000100:561 0x00000200:993 0x00000300:2608
said: 1 | **ENTWIN** t_ms:31905126 stream:0x3c4214c9 wall:0 window_ms:599987 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,c2e94427adcf,0283cce0e689,5ce28c488e0c
```

---

@LAT103LON8224 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 32389666 ±21 frame:7000
seq: 375
follows: 0x00000011:305 0x00000012:225 0x00000100:572 0x00000200:1003 0x00000300:2628
said: 1 | **ENTWIN** t_ms:32505127 stream:0x3c4214c9 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,bc102f237ace,64677217947d,0283cce0e689,5ce28c488e0c,84a329c78fec,c2e94427adcf
```

---

@LAT103LON8225 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 32989797 ±21 frame:7000
seq: 386
follows: 0x00000011:316 0x00000012:235 0x00000100:582 0x00000200:1013 0x00000300:2648
said: 1 | **ENTWIN** t_ms:33105127 stream:0x3c4214c9 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689,84a329c78fec,c2e94427adcf,64677217947d
```

---

@LAT103LON8226 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 33716344 ±21 frame:7000
seq: 399
follows: 0x00000011:328 0x00000012:247 0x00000100:595 0x00000200:1026 0x00000300:2673
said: 1 | **ENTWIN** t_ms:33817291 stream:0x3c4214c9 wall:0 window_ms:74344 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8227 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34885447 ±21 frame:7000
seq: 419
follows: 0x00000011:348 0x00000012:268 0x00000100:616 0x00000200:1046 0x00000300:2712
said: 1 | **ENTWIN** t_ms:35000778 stream:0x3c4214c9 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,bc102f237ace,84a329c78fec
said: 12 | **COVERED** windows:1 entities:7 window_ms:569093 first_t_ms:34400779 last_t_ms:34400779 covered_by:@LAT103LON8226
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95 windows:1
```

---

@LAT103LON8228 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 35485464 ±21 frame:7000
seq: 430
follows: 0x00000011:359 0x00000012:279 0x00000100:628 0x00000200:1057 0x00000300:2734
said: 1 | **ENTWIN** t_ms:35600789 stream:0x3c4214c9 wall:0 window_ms:600011 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,bc102f237ace,64677217947d,84a329c78fec
```

---

@LAT103LON8229 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36685479 ±21 frame:7000
seq: 451
follows: 0x00000011:380 0x00000012:300 0x00000100:650 0x00000200:1077 0x00000300:2775
said: 1 | **ENTWIN** t_ms:36800794 stream:0x3c4214c9 wall:0 window_ms:600004 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,bc102f237ace,0283cce0e689,64677217947d,84a329c78fec
said: 10 | **COVERED** windows:1 entities:7 window_ms:600000 first_t_ms:36200789 last_t_ms:36200789 covered_by:@LAT103LON8228
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
```

---

@LAT103LON8230 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 38485534 ±21 frame:7000
seq: 482
follows: 0x00000011:411 0x00000012:332 0x00000100:681 0x00000200:1108 0x00000300:2838
said: 1 | **ENTWIN** t_ms:38600834 stream:0x3c4214c9 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,bc102f237ace,64677217947d,0283cce0e689,5ce28c488e0c
said: 12 | **COVERED** windows:2 entities:10 window_ms:1200042 first_t_ms:37400827 last_t_ms:38000835 covered_by:@LAT103LON8229
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-28 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-70 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-80 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-82 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-85 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-91 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-92 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-92 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
```

---

@LAT103LON8231 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 40885558 ±21 frame:7000
seq: 523
follows: 0x00000011:454 0x00000012:372 0x00000100:724 0x00000200:1149 0x00000300:2922
said: 1 | **ENTWIN** t_ms:41000886 stream:0x3c4214c9 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 10 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,bc102f237ace,64677217947d,c2e94427adcf,0283cce0e689,5ce28c488e0c
said: 12 | **COVERED** windows:3 entities:10 window_ms:1800001 first_t_ms:39200837 last_t_ms:40400886 covered_by:@LAT103LON8230
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-28 windows:3
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-70 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-79 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-80 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-86 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:3 rssi:-88 windows:3
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:3 rssi:-88 windows:3
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-94 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-95 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93 windows:1
```

---

@LAT103LON8232 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 103616 ±21 frame:20500
seq: 532
follows: 0x00000011:461 0x00000012:379 0x00000100:732 0x00000200:1155 0x00000300:2941
said: 1 | **ENTWIN** t_ms:73373 stream:0xa0be1a79 wall:0 window_ms:74076 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8233 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1262497 ±21 frame:20500
seq: 552
follows: 0x00000011:479 0x00000012:395 0x00000100:732 0x00000200:1170 0x00000300:2967
said: 1 | **ENTWIN** t_ms:1246328 stream:0xa0be1a79 wall:0 window_ms:600001 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b
said: 11 | **COVERED** windows:1 entities:6 window_ms:558879 first_t_ms:646327 last_t_ms:646327 covered_by:@LAT103LON8232
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-96 windows:1
```

---

@LAT103LON8234 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1862502 ±21 frame:20500
seq: 563
follows: 0x00000011:490 0x00000012:406 0x00000100:732 0x00000200:1181 0x00000300:2987
said: 1 | **ENTWIN** t_ms:1846328 stream:0xa0be1a79 wall:0 window_ms:599999 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON8235 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3062514 ±21 frame:20500
seq: 584
follows: 0x00000011:512 0x00000012:427 0x00000100:732 0x00000200:1201 0x00000300:3030
said: 1 | **ENTWIN** t_ms:3046328 stream:0xa0be1a79 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689
said: 12 | **COVERED** windows:1 entities:8 window_ms:600001 first_t_ms:2446328 last_t_ms:2446328 covered_by:@LAT103LON8234
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96 windows:1
```

---

@LAT103LON8236 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3662519 ±21 frame:20500
seq: 595
follows: 0x00000011:523 0x00000012:437 0x00000100:732 0x00000200:1212 0x00000300:3050
said: 1 | **ENTWIN** t_ms:3646327 stream:0xa0be1a79 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689,c2e94427adcf,64677217947d
```

---

@LAT103LON8237 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6062600 ±21 frame:20500
seq: 636
follows: 0x00000011:564 0x00000012:478 0x00000100:732 0x00000200:1254 0x00000300:3129
said: 1 | **ENTWIN** t_ms:6046382 stream:0xa0be1a79 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 9 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,c2e94427adcf
said: 11 | **COVERED** windows:3 entities:8 window_ms:1800055 first_t_ms:4246328 last_t_ms:5446382 covered_by:@LAT103LON8236
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-43 windows:3
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-70 windows:3
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-70 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-75 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-80 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-88 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-91 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
```

---

@LAT106LON53 | created:0 | updated:0

**BAR** frame:20500 bar:10 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:625 hi:634 sum:6295
**HOLDS** agent:0x00000011 n:10 lo:555 hi:564 sum:5595
**HOLDS** agent:0x00000012 n:10 lo:468 hi:478 sum:4729
**HOLDS** agent:0x00000200 n:10 lo:1243 hi:1253 sum:12477
**HOLDS** agent:0x00000300 n:10 lo:3110 hi:3128 sum:31190

---

@LAT106LON54 | created:0 | updated:0

**BAR** frame:20500 bar:11 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:635 hi:645 sum:6404
**HOLDS** agent:0x00000011 n:10 lo:565 hi:575 sum:5702
**HOLDS** agent:0x00000012 n:10 lo:479 hi:488 sum:4835
**HOLDS** agent:0x00000200 n:10 lo:1254 hi:1264 sum:12587
**HOLDS** agent:0x00000300 n:10 lo:3130 hi:3150 sum:31408

---

@LAT106LON55 | created:0 | updated:0

**BAR** frame:20500 bar:12 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:646 hi:655 sum:6505
**HOLDS** agent:0x00000011 n:10 lo:576 hi:586 sum:5812
**HOLDS** agent:0x00000012 n:10 lo:489 hi:499 sum:4939
**HOLDS** agent:0x00000200 n:10 lo:1265 hi:1274 sum:12695
**HOLDS** agent:0x00000300 n:10 lo:3152 hi:3170 sum:31610

---

@LAT106LON56 | created:0 | updated:0

**BAR** frame:20500 bar:13 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:656 hi:665 sum:6605
**HOLDS** agent:0x00000011 n:10 lo:587 hi:597 sum:5922
**HOLDS** agent:0x00000012 n:10 lo:500 hi:510 sum:5049
**HOLDS** agent:0x00000200 n:10 lo:1275 hi:1285 sum:12797
**HOLDS** agent:0x00000300 n:10 lo:3172 hi:3190 sum:31810

---

@LAT106LON57 | created:0 | updated:0

**BAR** frame:20500 bar:14 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:666 hi:675 sum:6705
**HOLDS** agent:0x00000011 n:10 lo:598 hi:608 sum:6032
**HOLDS** agent:0x00000012 n:10 lo:511 hi:521 sum:5159
**HOLDS** agent:0x00000200 n:10 lo:1286 hi:1295 sum:12905
**HOLDS** agent:0x00000300 n:10 lo:3192 hi:3211 sum:32019

---

@LAT106LON58 | created:0 | updated:0

**BAR** frame:20500 bar:15 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:676 hi:685 sum:6805
**HOLDS** agent:0x00000011 n:10 lo:609 hi:619 sum:6142
**HOLDS** agent:0x00000012 n:10 lo:522 hi:531 sum:5265
**HOLDS** agent:0x00000200 n:10 lo:1296 hi:1305 sum:13005
**HOLDS** agent:0x00000300 n:10 lo:3213 hi:3231 sum:32220

---

@LAT103LON8238 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9662720 ±21 frame:20500
seq: 697
follows: 0x00000011:630 0x00000012:541 0x00000100:732 0x00000200:1317 0x00000300:3252
said: 1 | **ENTWIN** t_ms:9646519 stream:0xa0be1a79 wall:0 window_ms:600077 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 8 | **RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,c2e94427adcf,64677217947d
said: 10 | **COVERED** windows:5 entities:8 window_ms:3000009 first_t_ms:6646433 last_t_ms:9046442 covered_by:@LAT103LON8237
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-42 windows:5
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-70 windows:5
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-70 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-77 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-81 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-87 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:5 rssi:-92 windows:5
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
```

---

@LAT106LON59 | created:0 | updated:0

**BAR** frame:20500 bar:16 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:686 hi:695 sum:6905
**HOLDS** agent:0x00000011 n:10 lo:620 hi:630 sum:6252
**HOLDS** agent:0x00000012 n:10 lo:532 hi:541 sum:5365
**HOLDS** agent:0x00000200 n:10 lo:1306 hi:1316 sum:13107
**HOLDS** agent:0x00000300 n:10 lo:3233 hi:3251 sum:32420

---

@LAT106LON60 | created:0 | updated:0

**BAR** frame:20500 bar:17 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:696 hi:706 sum:7014
**HOLDS** agent:0x00000011 n:10 lo:631 hi:640 sum:6355
**HOLDS** agent:0x00000012 n:10 lo:542 hi:552 sum:5469
**HOLDS** agent:0x00000200 n:10 lo:1317 hi:1326 sum:13215
**HOLDS** agent:0x00000300 n:10 lo:3253 hi:3273 sum:32638

---

@LAT106LON61 | created:0 | updated:0

**BAR** frame:20500 bar:18 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:707 hi:716 sum:7115
**HOLDS** agent:0x00000011 n:10 lo:641 hi:650 sum:6455
**HOLDS** agent:0x00000012 n:10 lo:553 hi:562 sum:5575
**HOLDS** agent:0x00000200 n:10 lo:1327 hi:1337 sum:13317
**HOLDS** agent:0x00000300 n:10 lo:3275 hi:3293 sum:32840

---

@LAT103LON8239 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11462741 ±21 frame:20500
seq: 728
follows: 0x00000011:661 0x00000012:572 0x00000100:732 0x00000200:1348 0x00000300:3314
said: 1 | **ENTWIN** t_ms:11446524 stream:0xa0be1a79 wall:0 window_ms:600005 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 8 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,c2e94427adcf
said: 10 | **COVERED** windows:2 entities:9 window_ms:1200000 first_t_ms:10246519 last_t_ms:10846519 covered_by:@LAT103LON8238
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-45 windows:2
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-71 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-71 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-73 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-83 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-89 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-90 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
```

---

@LAT106LON62 | created:0 | updated:0

**BAR** frame:20500 bar:19 own:10 held:40 terms:8 digest:0xe6dd9bbe settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:717 hi:726 sum:7215
**HOLDS** agent:0x00000011 n:10 lo:651 hi:661 sum:6562
**HOLDS** agent:0x00000012 n:10 lo:563 hi:572 sum:5675
**HOLDS** agent:0x00000200 n:10 lo:1338 hi:1347 sum:13425
**HOLDS** agent:0x00000300 n:10 lo:3295 hi:3313 sum:33040

---

@LAT103LON8240 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12064772 ±21 frame:20500
seq: 739
follows: 0x00000011:671 0x00000012:582 0x00000100:732 0x00000200:1358 0x00000300:3336
said: 1 | **ENTWIN** t_ms:12046602 stream:0xa0be1a79 wall:0 window_ms:602026 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,c2e94427adcf
```

---

@LAT106LON63 | created:0 | updated:0

**BAR** frame:20500 bar:20 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120005
**HOLDS** agent:0x00000010 n:10 lo:727 hi:737 sum:7324
**HOLDS** agent:0x00000011 n:10 lo:662 hi:671 sum:6665
**HOLDS** agent:0x00000012 n:10 lo:573 hi:582 sum:5775
**HOLDS** agent:0x00000200 n:10 lo:1348 hi:1357 sum:13525
**HOLDS** agent:0x00000300 n:10 lo:3315 hi:3335 sum:33258

---

@LAT103LON8241 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12665643 ±21 frame:20500
seq: 750
follows: 0x00000011:681 0x00000012:593 0x00000100:732 0x00000200:1368 0x00000300:3359
said: 1 | **ENTWIN** t_ms:12647467 stream:0xa0be1a79 wall:0 window_ms:600866 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,c2e94427adcf,0283cce0e689
```

---

@LAT106LON64 | created:0 | updated:0

**BAR** frame:20500 bar:21 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:738 hi:748 sum:7434
**HOLDS** agent:0x00000011 n:10 lo:672 hi:681 sum:6765
**HOLDS** agent:0x00000012 n:10 lo:583 hi:592 sum:5875
**HOLDS** agent:0x00000200 n:10 lo:1358 hi:1367 sum:13625
**HOLDS** agent:0x00000300 n:10 lo:3337 hi:3356 sum:33469

---

@LAT106LON65 | created:0 | updated:0

**BAR** frame:20500 bar:22 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120001
**HOLDS** agent:0x00000010 n:10 lo:749 hi:759 sum:7544
**HOLDS** agent:0x00000011 n:10 lo:682 hi:692 sum:6872
**HOLDS** agent:0x00000012 n:10 lo:593 hi:602 sum:5975
**HOLDS** agent:0x00000200 n:10 lo:1368 hi:1377 sum:13725
**HOLDS** agent:0x00000300 n:10 lo:3358 hi:3377 sum:33679

---

@LAT103LON8242 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13867477 ±21 frame:20500
seq: 771
follows: 0x00000011:703 0x00000012:613 0x00000100:732 0x00000200:1388 0x00000300:3402
said: 1 | **ENTWIN** t_ms:13849291 stream:0xa0be1a79 wall:0 window_ms:600936 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,c2e94427adcf,84a329c78fec,0283cce0e689
said: 14 | **COVERED** windows:1 entities:6 window_ms:600888 first_t_ms:13248355 last_t_ms:13248355 covered_by:@LAT103LON8241
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
```

---

@LAT103LON819 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13918315 ±21 frame:20500
seq: 772
follows: 0x00000011:704 0x00000012:614 0x00000100:732 0x00000200:1388 0x00000300:3402
said: 1 | **LINKWIN** t_ms:13902131 stream:0xa0be1a79 wall:0 window_ms:60030
said: 2 | **LINK** peer:0x00000200 proto:ble n:48 rssi_min:-81 rssi_med:-65 rssi_max:-61
said: 3 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-60 rssi_max:-49
said: 4 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-79 rssi_med:-58 rssi_max:-48
said: 5 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-79 rssi_med:-65 rssi_max:-53
said: 6 | **LINK** peer:0x00000012 proto:espnow n:60 rssi_min:-56 rssi_med:-51 rssi_max:-48
said: 7 | **LINK** peer:0x00000200 proto:espnow n:107 rssi_min:-63 rssi_med:-56 rssi_max:-49
said: 8 | **LINK** peer:0x00000011 proto:espnow n:112 rssi_min:-59 rssi_med:-47 rssi_max:-39
said: 9 | **LINK** peer:0x00000300 proto:espnow n:138 rssi_min:-56 rssi_med:-42 rssi_max:-36
```

---

@LAT106LON66 | created:0 | updated:0

**BAR** frame:20500 bar:23 own:10 held:39 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:760 hi:769 sum:7645
**HOLDS** agent:0x00000011 n:9 lo:693 hi:702 sum:6279
**HOLDS** agent:0x00000012 n:10 lo:603 hi:613 sum:6079
**HOLDS** agent:0x00000200 n:10 lo:1378 hi:1387 sum:13825
**HOLDS** agent:0x00000300 n:10 lo:3379 hi:3399 sum:33898

---

@LAT103LON820 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13978320 ±21 frame:20500
seq: 773
follows: 0x00000011:705 0x00000012:616 0x00000100:732 0x00000200:1390 0x00000300:3406
said: 1 | **LINKWIN** t_ms:13962127 stream:0xa0be1a79 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-57 rssi_med:-56 rssi_max:-52
said: 3 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-58 rssi_med:-46 rssi_max:-42
said: 4 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-80 rssi_med:-65 rssi_max:-52
said: 5 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-57 rssi_max:-50
said: 6 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-83 rssi_med:-64 rssi_max:-50
said: 7 | **LINK** peer:0x00000200 proto:ble n:50 rssi_min:-82 rssi_med:-65 rssi_max:-62
said: 8 | **LINK** peer:0x00000300 proto:espnow n:159 rssi_min:-57 rssi_med:-42 rssi_max:-35
said: 9 | **LINK** peer:0x00000012 proto:espnow n:101 rssi_min:-56 rssi_med:-52 rssi_max:-51
```

---

@LAT103LON821 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14038321 ±21 frame:20500
seq: 774
follows: 0x00000011:706 0x00000012:616 0x00000100:732 0x00000200:1390 0x00000300:3406
said: 1 | **LINKWIN** t_ms:14022133 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:126 rssi_min:-54 rssi_med:-45 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-77 rssi_med:-60 rssi_max:-48
said: 4 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-65 rssi_max:-62
said: 5 | **LINK** peer:0x00000012 proto:espnow n:148 rssi_min:-56 rssi_med:-52 rssi_max:-47
said: 6 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-88 rssi_med:-65 rssi_max:-53
said: 7 | **LINK** peer:0x00000011 proto:espnow n:84 rssi_min:-61 rssi_med:-47 rssi_max:-41
said: 8 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-57 rssi_max:-49
said: 9 | **LINK** peer:0x00000200 proto:espnow n:178 rssi_min:-62 rssi_med:-56 rssi_max:-52
```

---

@LAT103LON822 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14098354 ±21 frame:20500
seq: 775
follows: 0x00000011:707 0x00000012:617 0x00000100:732 0x00000200:1392 0x00000300:3408
said: 1 | **LINKWIN** t_ms:14082127 stream:0xa0be1a79 wall:0 window_ms:60033
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-84 rssi_med:-63 rssi_max:-50
said: 3 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-65 rssi_max:-54
said: 4 | **LINK** peer:0x00000200 proto:espnow n:61 rssi_min:-58 rssi_med:-56 rssi_max:-55
said: 5 | **LINK** peer:0x00000011 proto:espnow n:114 rssi_min:-50 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000012 proto:espnow n:93 rssi_min:-52 rssi_med:-52 rssi_max:-50
said: 7 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-65 rssi_max:-64
said: 8 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-64 rssi_max:-52
said: 9 | **LINK** peer:0x00000300 proto:espnow n:181 rssi_min:-44 rssi_med:-42 rssi_max:-39
```

---

@LAT103LON823 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14158355 ±21 frame:20500
seq: 776
follows: 0x00000011:708 0x00000012:618 0x00000100:732 0x00000200:1392 0x00000300:3410
said: 1 | **LINKWIN** t_ms:14142166 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:82 rssi_min:-57 rssi_med:-56 rssi_max:-56
said: 3 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-79 rssi_med:-65 rssi_max:-54
said: 4 | **LINK** peer:0x00000011 proto:espnow n:93 rssi_min:-50 rssi_med:-47 rssi_max:-45
said: 5 | **LINK** peer:0x00000300 proto:espnow n:190 rssi_min:-44 rssi_med:-42 rssi_max:-39
said: 6 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-84 rssi_med:-62 rssi_max:-50
said: 7 | **LINK** peer:0x00000012 proto:espnow n:71 rssi_min:-53 rssi_med:-51 rssi_max:-50
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-65 rssi_max:-64
said: 9 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-80 rssi_med:-64 rssi_max:-52
```

---

@LAT103LON824 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14218355 ±21 frame:20500
seq: 777
follows: 0x00000011:709 0x00000012:619 0x00000100:732 0x00000200:1393 0x00000300:3412
said: 1 | **LINKWIN** t_ms:14202165 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-64 rssi_max:-53
said: 3 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-52 rssi_med:-47 rssi_max:-44
said: 4 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-67 rssi_med:-64 rssi_max:-52
said: 5 | **LINK** peer:0x00000012 proto:espnow n:105 rssi_min:-54 rssi_med:-51 rssi_max:-49
said: 6 | **LINK** peer:0x00000300 proto:espnow n:232 rssi_min:-44 rssi_med:-42 rssi_max:-40
said: 7 | **LINK** peer:0x00000200 proto:espnow n:142 rssi_min:-58 rssi_med:-56 rssi_max:-54
said: 8 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-80 rssi_med:-65 rssi_max:-63
said: 9 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-84 rssi_med:-63 rssi_max:-50
```

---

@LAT103LON825 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14278389 ±21 frame:20500
seq: 778
follows: 0x00000011:710 0x00000012:621 0x00000100:732 0x00000200:1395 0x00000300:3416
said: 1 | **LINKWIN** t_ms:14262200 stream:0xa0be1a79 wall:0 window_ms:60034
said: 2 | **LINK** peer:0x00000300 proto:espnow n:156 rssi_min:-51 rssi_med:-42 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-66 rssi_med:-55 rssi_max:-50
said: 4 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-83 rssi_med:-57 rssi_max:-45
said: 5 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-84 rssi_med:-66 rssi_max:-59
said: 6 | **LINK** peer:0x00000012 proto:espnow n:73 rssi_min:-57 rssi_med:-51 rssi_max:-49
said: 7 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-63 rssi_max:-52
said: 8 | **LINK** peer:0x00000011 proto:espnow n:92 rssi_min:-64 rssi_med:-45 rssi_max:-34
said: 9 | **LINK** peer:0x00000300 proto:ble n:49 rssi_min:-81 rssi_med:-60 rssi_max:-50
```

---

@LAT103LON826 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14338417 ±21 frame:20500
seq: 779
follows: 0x00000011:711 0x00000012:622 0x00000100:732 0x00000200:1397 0x00000300:3418
said: 1 | **LINKWIN** t_ms:14322227 stream:0xa0be1a79 wall:0 window_ms:60027
said: 2 | **LINK** peer:0x00000012 proto:espnow n:108 rssi_min:-56 rssi_med:-53 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:149 rssi_min:-52 rssi_med:-41 rssi_max:-38
said: 4 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-60 rssi_max:-50
said: 5 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-80 rssi_med:-51 rssi_max:-45
said: 6 | **LINK** peer:0x00000200 proto:espnow n:118 rssi_min:-57 rssi_med:-55 rssi_max:-52
said: 7 | **LINK** peer:0x00000011 proto:espnow n:87 rssi_min:-56 rssi_med:-43 rssi_max:-40
said: 8 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-74 rssi_med:-67 rssi_max:-53
said: 9 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-81 rssi_med:-65 rssi_max:-61
```

---

@LAT103LON827 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14399140 ±21 frame:20500
seq: 780
follows: 0x00000011:712 0x00000012:622 0x00000100:732 0x00000200:1398 0x00000300:3420
said: 1 | **LINKWIN** t_ms:14381168 stream:0xa0be1a79 wall:0 window_ms:60725
said: 2 | **LINK** peer:0x00000012 proto:espnow n:148 rssi_min:-62 rssi_med:-52 rssi_max:-45
said: 3 | **LINK** peer:0x00000300 proto:espnow n:238 rssi_min:-51 rssi_med:-43 rssi_max:-37
said: 4 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-74 rssi_med:-59 rssi_max:-48
said: 5 | **LINK** peer:0x00000011 proto:espnow n:120 rssi_min:-52 rssi_med:-43 rssi_max:-40
said: 6 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-62 rssi_max:-55
said: 7 | **LINK** peer:0x00000200 proto:espnow n:140 rssi_min:-59 rssi_med:-55 rssi_max:-45
said: 8 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-52 rssi_max:-47
said: 9 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-80 rssi_med:-62 rssi_max:-50
```

---

@LAT103LON828 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14459144 ±21 frame:20500
seq: 781
follows: 0x00000011:713 0x00000012:624 0x00000100:732 0x00000200:1399 0x00000300:3422
said: 1 | **LINKWIN** t_ms:14442951 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:110 rssi_min:-61 rssi_med:-44 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:espnow n:151 rssi_min:-69 rssi_med:-56 rssi_max:-48
said: 4 | **LINK** peer:0x00000300 proto:espnow n:152 rssi_min:-52 rssi_med:-41 rssi_max:-35
said: 5 | **LINK** peer:0x00000012 proto:espnow n:106 rssi_min:-63 rssi_med:-54 rssi_max:-52
said: 6 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-62 rssi_med:-53 rssi_max:-49
said: 7 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-68 rssi_med:-57 rssi_max:-49
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-83 rssi_med:-64 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-65 rssi_max:-49
```

---

@LAT103LON8243 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 14465511 ±21 frame:20500
seq: 782
follows: 0x00000011:713 0x00000012:624 0x00000100:732 0x00000200:1399 0x00000300:3422
said: 1 | **ENTWIN** t_ms:14449319 stream:0xa0be1a79 wall:0 window_ms:598027 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,84a329c78fec
```

---

@LAT103LON829 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14519167 ±21 frame:20500
seq: 783
follows: 0x00000011:714 0x00000012:625 0x00000100:732 0x00000200:1400 0x00000300:3425
said: 1 | **LINKWIN** t_ms:14502976 stream:0xa0be1a79 wall:0 window_ms:60024
said: 2 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-67 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-70 rssi_med:-65 rssi_max:-61
said: 4 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-80 rssi_med:-51 rssi_max:-50
said: 5 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-81 rssi_med:-61 rssi_max:-49
said: 6 | **LINK** peer:0x00000200 proto:espnow n:115 rssi_min:-57 rssi_med:-56 rssi_max:-55
said: 7 | **LINK** peer:0x00000012 proto:espnow n:63 rssi_min:-54 rssi_med:-53 rssi_max:-53
said: 8 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 9 | **LINK** peer:0x00000300 proto:espnow n:147 rssi_min:-86 rssi_med:-41 rssi_max:-38
```
@LAT106LON67 | created:0 | updated:0

**BAR** frame:20500 bar:24 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:770 hi:780 sum:7754
**HOLDS** agent:0x00000011 n:10 lo:704 hi:713 sum:7085
**HOLDS** agent:0x00000012 n:10 lo:614 hi:623 sum:6185
**HOLDS** agent:0x00000200 n:10 lo:1388 hi:1398 sum:13927
**HOLDS** agent:0x00000300 n:10 lo:3401 hi:3419 sum:34100

---

@LAT103LON830 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14579167 ±21 frame:20500
seq: 784
follows: 0x00000011:715 0x00000012:626 0x00000100:732 0x00000200:1401 0x00000300:3427
said: 1 | **LINKWIN** t_ms:14562976 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:147 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 3 | **LINK** peer:0x00000300 proto:espnow n:76 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 4 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-61 rssi_max:-51
said: 5 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-57 rssi_med:-56 rssi_max:-55
said: 6 | **LINK** peer:0x00000011 proto:espnow n:70 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 7 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-68 rssi_max:-53
said: 8 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-66 rssi_max:-61
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-51 rssi_max:-50
```

---

@LAT103LON831 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14639202 ±21 frame:20500
seq: 785
follows: 0x00000011:717 0x00000012:627 0x00000100:732 0x00000200:1402 0x00000300:3429
said: 1 | **LINKWIN** t_ms:14623008 stream:0xa0be1a79 wall:0 window_ms:60033
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:128 rssi_min:-57 rssi_med:-56 rssi_max:-55
said: 4 | **LINK** peer:0x00000300 proto:espnow n:172 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-66 rssi_max:-61
said: 6 | **LINK** peer:0x00000011 proto:espnow n:83 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 7 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-63 rssi_med:-60 rssi_max:-51
said: 8 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-67 rssi_max:-53
said: 9 | **LINK** peer:0x00000012 proto:espnow n:83 rssi_min:-55 rssi_med:-53 rssi_max:-53
```

---

@LAT103LON832 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14699202 ±21 frame:20500
seq: 786
follows: 0x00000011:718 0x00000012:628 0x00000100:732 0x00000200:1403 0x00000300:3431
said: 1 | **LINKWIN** t_ms:14683008 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-80 rssi_med:-67 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:73 rssi_min:-56 rssi_med:-56 rssi_max:-55
said: 4 | **LINK** peer:0x00000011 proto:espnow n:124 rssi_min:-44 rssi_med:-42 rssi_max:-41
said: 5 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-51 rssi_max:-51
said: 6 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-66 rssi_max:-61
said: 7 | **LINK** peer:0x00000012 proto:espnow n:69 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 8 | **LINK** peer:0x00000300 proto:espnow n:117 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 9 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-63 rssi_med:-60 rssi_max:-50
```

---

@LAT103LON833 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14759201 ±21 frame:20500
seq: 787
follows: 0x00000011:719 0x00000012:629 0x00000100:732 0x00000200:1404 0x00000300:3433
said: 1 | **LINKWIN** t_ms:14743008 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-60 rssi_max:-51
said: 3 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-76 rssi_med:-52 rssi_max:-51
said: 4 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 5 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-70 rssi_med:-65 rssi_max:-60
said: 6 | **LINK** peer:0x00000200 proto:espnow n:109 rssi_min:-57 rssi_med:-56 rssi_max:-55
said: 7 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-68 rssi_max:-53
said: 8 | **LINK** peer:0x00000300 proto:espnow n:154 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 9 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-44 rssi_med:-42 rssi_max:-41
```

---

@LAT103LON834 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14819238 ±21 frame:20500
seq: 788
follows: 0x00000011:720 0x00000012:631 0x00000100:732 0x00000200:1405 0x00000300:3435
said: 1 | **LINKWIN** t_ms:14803043 stream:0xa0be1a79 wall:0 window_ms:60034
said: 2 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-51 rssi_max:-45
said: 3 | **LINK** peer:0x00000011 proto:espnow n:118 rssi_min:-56 rssi_med:-42 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:espnow n:211 rssi_min:-47 rssi_med:-41 rssi_max:-39
said: 5 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-60 rssi_max:-51
said: 6 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-70 rssi_med:-65 rssi_max:-60
said: 7 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-67 rssi_max:-52
said: 8 | **LINK** peer:0x00000012 proto:espnow n:107 rssi_min:-57 rssi_med:-53 rssi_max:-50
said: 9 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-59 rssi_med:-56 rssi_max:-49
```

---

@LAT103LON835 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14879238 ±21 frame:20500
seq: 789
follows: 0x00000011:721 0x00000012:631 0x00000100:732 0x00000200:1405 0x00000300:3435
said: 1 | **LINKWIN** t_ms:14863043 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:110 rssi_min:-58 rssi_med:-53 rssi_max:-48
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-58 rssi_max:-49
said: 4 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-85 rssi_med:-56 rssi_max:-48
said: 5 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-66 rssi_max:-52
said: 6 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-61 rssi_max:-55
said: 7 | **LINK** peer:0x00000200 proto:espnow n:100 rssi_min:-56 rssi_med:-53 rssi_max:-50
said: 8 | **LINK** peer:0x00000011 proto:espnow n:90 rssi_min:-53 rssi_med:-47 rssi_max:-36
said: 9 | **LINK** peer:0x00000300 proto:espnow n:117 rssi_min:-52 rssi_med:-46 rssi_max:-41
```

---

@LAT103LON836 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14939239 ±21 frame:20500
seq: 790
follows: 0x00000011:722 0x00000012:632 0x00000100:732 0x00000200:1406 0x00000300:3437
said: 1 | **LINKWIN** t_ms:14923043 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:49 rssi_min:-53 rssi_med:-46 rssi_max:-44
said: 3 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-58 rssi_max:-52
said: 4 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-83 rssi_med:-60 rssi_max:-54
said: 5 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-60 rssi_med:-55 rssi_max:-50
said: 6 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-82 rssi_med:-64 rssi_max:-53
said: 7 | **LINK** peer:0x00000012 proto:espnow n:73 rssi_min:-51 rssi_med:-50 rssi_max:-45
said: 8 | **LINK** peer:0x00000300 proto:espnow n:161 rssi_min:-59 rssi_med:-50 rssi_max:-40
said: 9 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-61 rssi_max:-56
```

---

@LAT103LON837 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14995116 ±21 frame:20500
seq: 791
follows: 0x00000011:723 0x00000012:634 0x00000100:732 0x00000200:1408 0x00000300:3441
said: 1 | **LINKWIN** t_ms:14983043 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:157 rssi_min:-59 rssi_med:-52 rssi_max:-32
said: 3 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-68 rssi_med:-58 rssi_max:-53
said: 4 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-45
said: 5 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-68 rssi_max:-61
said: 6 | **LINK** peer:0x00000012 proto:espnow n:93 rssi_min:-59 rssi_med:-51 rssi_max:-46
said: 7 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-93 rssi_med:-64 rssi_max:-53
said: 8 | **LINK** peer:0x00000011 proto:espnow n:80 rssi_min:-45 rssi_med:-41 rssi_max:-34
said: 9 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-77 rssi_med:-53 rssi_max:-48
```

---

@LAT103LON838 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15059239 ±21 frame:20500
seq: 792
follows: 0x00000011:724 0x00000012:634 0x00000100:732 0x00000200:1408 0x00000300:3441
said: 1 | **LINKWIN** t_ms:15043043 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:108 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:125 rssi_min:-59 rssi_med:-57 rssi_max:-56
said: 4 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-56 rssi_max:-52
said: 5 | **LINK** peer:0x00000011 proto:espnow n:74 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 6 | **LINK** peer:0x00000300 proto:espnow n:165 rssi_min:-43 rssi_med:-42 rssi_max:-39
said: 7 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-73 rssi_med:-70 rssi_max:-64
said: 8 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-58 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-79 rssi_med:-66 rssi_max:-55
```

---

@LAT103LON8244 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 15069354 ±21 frame:20500
seq: 793
follows: 0x00000011:724 0x00000012:634 0x00000100:732 0x00000200:1408 0x00000300:3441
said: 1 | **ENTWIN** t_ms:15051158 stream:0xa0be1a79 wall:0 window_ms:603840 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,0283cce0e689,c2e94427adcf,64677217947d
```

---

@LAT103LON839 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15119435 ±21 frame:20500
seq: 794
follows: 0x00000011:725 0x00000012:635 0x00000100:732 0x00000200:1409 0x00000300:3444
said: 1 | **LINKWIN** t_ms:15087235 stream:0xa0be1a79 wall:0 window_ms:60194
said: 2 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-60 rssi_med:-57 rssi_max:-56
said: 3 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-73 rssi_med:-66 rssi_max:-55
said: 4 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-59 rssi_med:-58 rssi_max:-52
said: 5 | **LINK** peer:0x00000011 proto:espnow n:60 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 6 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-59 rssi_med:-53 rssi_max:-51
said: 7 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-70 rssi_max:-63
said: 8 | **LINK** peer:0x00000300 proto:espnow n:119 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 9 | **LINK** peer:0x00000012 proto:espnow n:61 rssi_min:-55 rssi_med:-53 rssi_max:-53
```

---

@LAT106LON68 | created:0 | updated:0

**BAR** frame:20500 bar:25 own:10 held:37 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:781 hi:791 sum:7864
**HOLDS** agent:0x00000011 n:9 lo:714 hi:723 sum:6468
**HOLDS** agent:0x00000012 n:10 lo:624 hi:634 sum:6289
**HOLDS** agent:0x00000200 n:8 lo:1399 hi:1406 sum:11220
**HOLDS** agent:0x00000300 n:10 lo:3421 hi:3440 sum:34309

---

@LAT103LON840 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15179436 ±21 frame:20500
seq: 795
follows: 0x00000011:726 0x00000012:636 0x00000100:732 0x00000200:1410 0x00000300:3446
said: 1 | **LINKWIN** t_ms:15147235 stream:0xa0be1a79 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000300 proto:espnow n:160 rssi_min:-43 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-59 rssi_med:-52 rssi_max:-52
said: 4 | **LINK** peer:0x00000011 proto:espnow n:81 rssi_min:-45 rssi_med:-43 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-72 rssi_med:-69 rssi_max:-64
said: 6 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-58 rssi_max:-52
said: 7 | **LINK** peer:0x00000200 proto:espnow n:59 rssi_min:-58 rssi_med:-57 rssi_max:-56
said: 8 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 9 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-72 rssi_med:-66 rssi_max:-55
```

---

@LAT103LON841 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15239512 ±21 frame:20500
seq: 796
follows: 0x00000011:727 0x00000012:637 0x00000100:732 0x00000200:1411 0x00000300:3448
said: 1 | **LINKWIN** t_ms:15223271 stream:0xa0be1a79 wall:0 window_ms:60076
said: 2 | **LINK** peer:0x00000300 proto:espnow n:132 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000011 proto:espnow n:84 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 4 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-82 rssi_med:-53 rssi_max:-51
said: 5 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-66 rssi_max:-54
said: 6 | **LINK** peer:0x00000012 proto:espnow n:78 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 7 | **LINK** peer:0x00000200 proto:espnow n:84 rssi_min:-59 rssi_med:-57 rssi_max:-56
said: 8 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-58 rssi_max:-52
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-73 rssi_med:-70 rssi_max:-64
```

---

@LAT103LON842 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15299513 ±21 frame:20500
seq: 797
follows: 0x00000011:728 0x00000012:638 0x00000100:732 0x00000200:1412 0x00000300:3450
said: 1 | **LINKWIN** t_ms:15283313 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:118 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:133 rssi_min:-59 rssi_med:-57 rssi_max:-56
said: 4 | **LINK** peer:0x00000011 proto:espnow n:80 rssi_min:-45 rssi_med:-43 rssi_max:-39
said: 5 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-58 rssi_med:-58 rssi_max:-52
said: 6 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-59 rssi_med:-53 rssi_max:-51
said: 7 | **LINK** peer:0x00000300 proto:espnow n:158 rssi_min:-43 rssi_med:-42 rssi_max:-39
said: 8 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-66 rssi_max:-55
said: 9 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-70 rssi_max:-64
```

---

@LAT103LON843 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15359517 ±21 frame:20500
seq: 798
follows: 0x00000011:729 0x00000012:639 0x00000100:732 0x00000200:1413 0x00000300:3452
said: 1 | **LINKWIN** t_ms:15343315 stream:0xa0be1a79 wall:0 window_ms:60004
said: 2 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-59 rssi_med:-57 rssi_max:-56
said: 3 | **LINK** peer:0x00000012 proto:espnow n:150 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 4 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-58 rssi_med:-58 rssi_max:-52
said: 5 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-70 rssi_max:-64
said: 6 | **LINK** peer:0x00000300 proto:espnow n:187 rssi_min:-43 rssi_med:-42 rssi_max:-39
said: 7 | **LINK** peer:0x00000011 proto:espnow n:112 rssi_min:-45 rssi_med:-43 rssi_max:-39
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-66 rssi_max:-54
said: 9 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-80 rssi_med:-53 rssi_max:-52
```

---

@LAT103LON844 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15419518 ±21 frame:20500
seq: 799
follows: 0x00000011:730 0x00000012:640 0x00000100:732 0x00000200:1414 0x00000300:3454
said: 1 | **LINKWIN** t_ms:15403319 stream:0xa0be1a79 wall:0 window_ms:60002
said: 2 | **LINK** peer:0x00000300 proto:espnow n:155 rssi_min:-43 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:espnow n:106 rssi_min:-59 rssi_med:-57 rssi_max:-56
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-70 rssi_max:-64
said: 5 | **LINK** peer:0x00000012 proto:espnow n:98 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 6 | **LINK** peer:0x00000011 proto:ble n:69 rssi_min:-59 rssi_med:-52 rssi_max:-52
said: 7 | **LINK** peer:0x00000011 proto:espnow n:108 rssi_min:-45 rssi_med:-43 rssi_max:-39
said: 8 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-64 rssi_med:-58 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-81 rssi_med:-66 rssi_max:-54
```

---

@LAT103LON845 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15479552 ±21 frame:20500
seq: 800
follows: 0x00000011:731 0x00000012:641 0x00000100:732 0x00000200:1415 0x00000300:3456
said: 1 | **LINKWIN** t_ms:15463348 stream:0xa0be1a79 wall:0 window_ms:60032
said: 2 | **LINK** peer:0x00000200 proto:espnow n:217 rssi_min:-59 rssi_med:-57 rssi_max:-56
said: 3 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-59 rssi_med:-53 rssi_max:-52
said: 4 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-70 rssi_max:-64
said: 5 | **LINK** peer:0x00000011 proto:espnow n:127 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 6 | **LINK** peer:0x00000012 proto:espnow n:99 rssi_min:-54 rssi_med:-53 rssi_max:-53
said: 7 | **LINK** peer:0x00000300 proto:espnow n:181 rssi_min:-43 rssi_med:-42 rssi_max:-39
said: 8 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-66 rssi_max:-54
said: 9 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-58 rssi_max:-52
```

---

@LAT103LON846 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15539553 ±21 frame:20500
seq: 801
follows: 0x00000011:732 0x00000012:642 0x00000100:732 0x00000200:1416 0x00000300:3458
said: 1 | **LINKWIN** t_ms:15523351 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-73 rssi_med:-66 rssi_max:-55
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-58 rssi_max:-52
said: 4 | **LINK** peer:0x00000012 proto:espnow n:75 rssi_min:-54 rssi_med:-53 rssi_max:-53
said: 5 | **LINK** peer:0x00000011 proto:espnow n:118 rssi_min:-45 rssi_med:-43 rssi_max:-39
said: 6 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-82 rssi_med:-53 rssi_max:-52
said: 7 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-73 rssi_med:-70 rssi_max:-64
said: 8 | **LINK** peer:0x00000200 proto:espnow n:82 rssi_min:-58 rssi_med:-57 rssi_max:-56
said: 9 | **LINK** peer:0x00000300 proto:espnow n:174 rssi_min:-43 rssi_med:-42 rssi_max:-40
```

---

@LAT106LON69 | created:0 | updated:0

**BAR** frame:20500 bar:26 own:9 held:37 terms:8 digest:0xeb1da612 settled_ms:120000
**HOLDS** agent:0x00000010 n:9 lo:792 hi:801 sum:7172
**HOLDS** agent:0x00000011 n:8 lo:725 hi:732 sum:5828
**HOLDS** agent:0x00000012 n:9 lo:635 hi:643 sum:5751
**HOLDS** agent:0x00000200 n:10 lo:1409 hi:1418 sum:14135
**HOLDS** agent:0x00000300 n:10 lo:3442 hi:3461 sum:34519
**DELIVER** up_s:56 heap:123392 fetched:1 unanswered:6 broken:0 resumed:6 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0

---

@LAT103LON847 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15749240 ±21 frame:20500
seq: 802
follows: 0x00000011:736 0x00000012:646 0x00000100:732 0x00000200:1420 0x00000300:3466
said: 1 | **LINKWIN** t_ms:15724309 stream:0xa0be1a79 wall:0 window_ms:61354
said: 2 | **LINK** peer:0x00000300 proto:espnow n:155 rssi_min:-44 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000011 proto:espnow n:56 rssi_min:-46 rssi_med:-44 rssi_max:-39
said: 4 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-57 rssi_max:-52
said: 5 | **LINK** peer:0x00000012 proto:espnow n:116 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 6 | **LINK** peer:0x00000011 proto:ble n:52 rssi_min:-76 rssi_med:-53 rssi_max:-51
said: 7 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-66 rssi_max:-54
said: 8 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-81 rssi_med:-70 rssi_max:-64
said: 9 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-59 rssi_med:-58 rssi_max:-56
```

---

@LAT103LON8245 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 15749284 ±21 frame:20500
seq: 803
follows: 0x00000011:736 0x00000012:646 0x00000100:732 0x00000200:1420 0x00000300:3466
said: 1 | **ENTWIN** t_ms:15724309 stream:0xa0be1a79 wall:0 window_ms:61398 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON848 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15809240 ±21 frame:20500
seq: 804
follows: 0x00000011:737 0x00000012:647 0x00000100:732 0x00000200:1421 0x00000300:3468
said: 1 | **LINKWIN** t_ms:15793049 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:93 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-73 rssi_med:-70 rssi_max:-63
said: 4 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-72 rssi_med:-66 rssi_max:-55
said: 5 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-58 rssi_max:-52
said: 6 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 7 | **LINK** peer:0x00000011 proto:espnow n:125 rssi_min:-46 rssi_med:-43 rssi_max:-40
said: 8 | **LINK** peer:0x00000300 proto:espnow n:99 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:espnow n:89 rssi_min:-59 rssi_med:-57 rssi_max:-56
```

---

@LAT103LON849 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15869241 ±21 frame:20500
seq: 805
follows: 0x00000011:739 0x00000012:648 0x00000100:732 0x00000200:1422 0x00000300:3470
said: 1 | **LINKWIN** t_ms:15853048 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:112 rssi_min:-46 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000012 proto:espnow n:139 rssi_min:-55 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000200 proto:espnow n:76 rssi_min:-59 rssi_med:-58 rssi_max:-56
said: 5 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-80 rssi_med:-66 rssi_max:-55
said: 6 | **LINK** peer:0x00000300 proto:espnow n:179 rssi_min:-44 rssi_med:-42 rssi_max:-39
said: 7 | **LINK** peer:0x00000011 proto:ble n:68 rssi_min:-79 rssi_med:-53 rssi_max:-51
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-73 rssi_med:-70 rssi_max:-64
said: 9 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-58 rssi_med:-58 rssi_max:-52
```

---

@LAT103LON850 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15929242 ±21 frame:20500
seq: 806
follows: 0x00000011:740 0x00000012:649 0x00000100:732 0x00000200:1423 0x00000300:3472
said: 1 | **LINKWIN** t_ms:15913049 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-59 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-72 rssi_med:-70 rssi_max:-63
said: 4 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-55 rssi_med:-54 rssi_max:-53
said: 5 | **LINK** peer:0x00000200 proto:espnow n:100 rssi_min:-59 rssi_med:-57 rssi_max:-56
said: 6 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-46 rssi_med:-44 rssi_max:-39
said: 7 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-80 rssi_med:-66 rssi_max:-55
said: 8 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-58 rssi_med:-58 rssi_max:-52
said: 9 | **LINK** peer:0x00000300 proto:espnow n:161 rssi_min:-43 rssi_med:-42 rssi_max:-39
```

---

@LAT103LON851 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 15989242 ±21 frame:20500
seq: 807
follows: 0x00000011:741 0x00000012:650 0x00000100:732 0x00000200:1424 0x00000300:3474
said: 1 | **LINKWIN** t_ms:15973048 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:181 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:120 rssi_min:-60 rssi_med:-58 rssi_max:-56
said: 4 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-66 rssi_max:-54
said: 5 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-59 rssi_med:-53 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-59 rssi_med:-58 rssi_max:-52
said: 7 | **LINK** peer:0x00000012 proto:espnow n:91 rssi_min:-55 rssi_med:-54 rssi_max:-53
said: 8 | **LINK** peer:0x00000011 proto:espnow n:69 rssi_min:-46 rssi_med:-44 rssi_max:-40
said: 9 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-70 rssi_max:-64
```

---

@LAT105LON2447 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 15976245 ±21 frame:20500
seq: 741
follows: 0x00000010:806 0x00000012:650 0x00000100:732 0x00000200:1424 0x00000300:3474
said: 1 | **LINKWIN** t_ms:15960055 stream:0xa0be1a79 wall:0 window_ms:61603
said: 2 | **LINK** peer:0x00000200 proto:espnow n:114 rssi_min:-57 rssi_med:-56 rssi_max:-56
said: 3 | **LINK** peer:0x00000300 proto:espnow n:166 rssi_min:-39 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000010 proto:espnow n:83 rssi_min:-45 rssi_med:-45 rssi_max:-41
said: 5 | **LINK** peer:0x00000010 proto:ble n:71 rssi_min:-81 rssi_med:-57 rssi_max:-55
said: 6 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-43 rssi_max:-41
said: 7 | **LINK** peer:0x00000012 proto:espnow n:91 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 8 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-83 rssi_med:-67 rssi_max:-66
said: 9 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-84 rssi_med:-71 rssi_max:-56
```

---

@LAT105LON2448 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 16016277 ±0 frame:20500
seq: 3475
follows: 0x00000010:807 0x00000011:741 0x00000012:650 0x00000100:732 0x00000200:1424
said: 1 | **LINKWIN** t_ms:16000108 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-80 rssi_med:-56 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-61 rssi_med:-60 rssi_max:-57
said: 5 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-57 rssi_max:-46
said: 6 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-72 rssi_med:-71 rssi_max:-61
said: 7 | **LINK** peer:0x00000012 proto:espnow n:75 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:espnow n:71 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 9 | **LINK** peer:0x00000011 proto:espnow n:98 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 10 | 0x00000011 ble met predicted:-52 observed:-57
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-44 observed:-44
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-69 observed:-71
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-59 observed:-60
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000011 espnow met predicted:-41 observed:-41
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000012 espnow met predicted:-50 observed:-50
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-56 observed:-56
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON852 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 16049242 ±21 frame:20500
seq: 808
follows: 0x00000011:742 0x00000012:651 0x00000100:732 0x00000200:1425 0x00000300:3476
said: 1 | **LINKWIN** t_ms:16033048 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:75 rssi_min:-59 rssi_med:-57 rssi_max:-56
said: 3 | **LINK** peer:0x00000011 proto:espnow n:142 rssi_min:-46 rssi_med:-44 rssi_max:-39
said: 4 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-73 rssi_med:-70 rssi_max:-64
said: 5 | **LINK** peer:0x00000300 proto:espnow n:124 rssi_min:-43 rssi_med:-42 rssi_max:-39
said: 6 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-55 rssi_med:-54 rssi_max:-53
said: 7 | **LINK** peer:0x00000011 proto:ble n:70 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 8 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-58 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-73 rssi_med:-66 rssi_max:-55
```

---

@LAT105LON2449 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 16036245 ±21 frame:20500
seq: 742
follows: 0x00000010:807 0x00000012:651 0x00000100:732 0x00000200:1425 0x00000300:3476
said: 1 | **LINKWIN** t_ms:16020054 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:127 rssi_min:-40 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000010 proto:espnow n:70 rssi_min:-45 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000200 proto:espnow n:75 rssi_min:-57 rssi_med:-56 rssi_max:-56
said: 5 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-43 rssi_max:-41
said: 6 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-67 rssi_max:-66
said: 7 | **LINK** peer:0x00000012 proto:ble n:49 rssi_min:-84 rssi_med:-71 rssi_max:-55
said: 8 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-57 rssi_max:-55
said: 9 | **LINK** peer:0x00000012 proto:espnow n:70 rssi_min:-60 rssi_med:-58 rssi_max:-58
```

---

@LAT105LON2450 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 16017420 ±21 frame:20500
seq: 651
follows: 0x00000010:807 0x00000011:741 0x00000100:732 0x00000200:1424 0x00000300:3476
said: 1 | **LINKWIN** t_ms:16001214 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 4 | **LINK** peer:0x00000011 proto:espnow n:69 rssi_min:-58 rssi_med:-56 rssi_max:-55
said: 5 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-66 rssi_max:-53
said: 6 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-55 rssi_max:-52
said: 7 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-71 rssi_max:-55
said: 8 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-65 rssi_max:-53
said: 9 | **LINK** peer:0x00000300 proto:espnow n:130 rssi_min:-48 rssi_med:-47 rssi_max:-46
```

---

@LAT105LON2451 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 16017350 ±21 frame:20500
seq: 1425
follows: 0x00000010:807 0x00000011:741 0x00000012:650 0x00000100:732 0x00000300:3476
said: 1 | **LINKWIN** t_ms:16001147 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-71 rssi_max:-61
said: 3 | **LINK** peer:0x00000011 proto:espnow n:69 rssi_min:-55 rssi_med:-52 rssi_max:-52
said: 4 | **LINK** peer:0x00000012 proto:espnow n:84 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 5 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-80 rssi_med:-57 rssi_max:-54
said: 6 | **LINK** peer:0x00000010 proto:espnow n:85 rssi_min:-58 rssi_med:-56 rssi_max:-56
said: 7 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-79 rssi_med:-65 rssi_max:-61
said: 8 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-56 rssi_med:-53 rssi_max:-52
said: 9 | **LINK** peer:0x00000300 proto:espnow n:149 rssi_min:-41 rssi_med:-39 rssi_max:-39
```

---

@LAT105LON2452 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 16076277 ±0 frame:20500
seq: 3477
follows: 0x00000010:808 0x00000011:742 0x00000012:651 0x00000100:732 0x00000200:1425
said: 1 | **LINKWIN** t_ms:16060108 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-72 rssi_med:-71 rssi_max:-61
said: 3 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-61 rssi_med:-60 rssi_max:-59
said: 4 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-65 rssi_med:-52 rssi_max:-46
said: 5 | **LINK** peer:0x00000011 proto:espnow n:158 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 6 | **LINK** peer:0x00000200 proto:espnow n:71 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 7 | **LINK** peer:0x00000012 proto:espnow n:85 rssi_min:-52 rssi_med:-50 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:espnow n:93 rssi_min:-46 rssi_med:-44 rssi_max:-42
said: 9 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-65 rssi_med:-56 rssi_max:-55
said: 10 | 0x00000200 ble met predicted:-56 observed:-56
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 ble met predicted:-60 observed:-60
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000011 ble met predicted:-57 observed:-52
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000012 ble met predicted:-71 observed:-71
percept: 14 | 0x00000012 | link_stable | ble | + | -
said: 15 | 0x00000012 espnow met predicted:-50 observed:-50
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-44 observed:-44
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000011 espnow met predicted:-41 observed:-41
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT105LON2453 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 16077352 ±21 frame:20500
seq: 1426
follows: 0x00000010:808 0x00000011:742 0x00000012:651 0x00000100:732 0x00000300:3478
said: 1 | **LINKWIN** t_ms:16061148 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-72 rssi_med:-71 rssi_max:-61
said: 3 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-58 rssi_med:-57 rssi_max:-56
said: 4 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000300 proto:espnow n:144 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 6 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-83 rssi_med:-53 rssi_max:-52
said: 7 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-67 rssi_med:-65 rssi_max:-61
said: 8 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-81 rssi_med:-57 rssi_max:-56
said: 9 | **LINK** peer:0x00000011 proto:espnow n:124 rssi_min:-55 rssi_med:-52 rssi_max:-51
```

---

@LAT103LON853 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 16109251 ±21 frame:20500
seq: 809
follows: 0x00000011:743 0x00000012:652 0x00000100:732 0x00000200:1426 0x00000300:3478
said: 1 | **LINKWIN** t_ms:16093056 stream:0xa0be1a79 wall:0 window_ms:60008
said: 2 | **LINK** peer:0x00000300 proto:espnow n:188 rssi_min:-43 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:espnow n:89 rssi_min:-60 rssi_med:-58 rssi_max:-56
said: 4 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-55 rssi_med:-54 rssi_max:-53
said: 5 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-66 rssi_max:-55
said: 6 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-59 rssi_med:-58 rssi_max:-52
said: 7 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 9 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-73 rssi_med:-70 rssi_max:-64
```

---

@LAT105LON2454 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 16096246 ±21 frame:20500
seq: 743
follows: 0x00000010:808 0x00000012:652 0x00000100:732 0x00000200:1426 0x00000300:3478
said: 1 | **LINKWIN** t_ms:16080054 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:76 rssi_min:-59 rssi_med:-59 rssi_max:-58
said: 3 | **LINK** peer:0x00000300 proto:espnow n:186 rssi_min:-39 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000010 proto:espnow n:93 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000200 proto:espnow n:78 rssi_min:-57 rssi_med:-56 rssi_max:-56
said: 6 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-67 rssi_max:-65
said: 7 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-43 rssi_max:-41
said: 8 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-57 rssi_max:-55
said: 9 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-84 rssi_med:-71 rssi_max:-56
```

---

@LAT105LON2455 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 16136277 ±0 frame:20500
seq: 3479
follows: 0x00000010:809 0x00000011:743 0x00000012:652 0x00000100:732 0x00000200:1426
said: 1 | **LINKWIN** t_ms:16120108 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:80 rssi_min:-52 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 4 | **LINK** peer:0x00000200 proto:espnow n:107 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-66 rssi_med:-56 rssi_max:-55
said: 6 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-72 rssi_med:-71 rssi_max:-61
said: 7 | **LINK** peer:0x00000011 proto:espnow n:80 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 8 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-61 rssi_med:-60 rssi_max:-59
said: 9 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-66 rssi_med:-51 rssi_max:-46
said: 10 | 0x00000012 ble met predicted:-71 observed:-71
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-60 observed:-60
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000011 ble met predicted:-52 observed:-51
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000011 espnow met predicted:-41 observed:-41
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-50 observed:-50
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-44 observed:-44
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-56 observed:-56
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON2456 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 16137141 ±21 frame:20500
seq: 1427
follows: 0x00000010:809 0x00000011:743 0x00000012:652 0x00000100:732 0x00000300:3480
said: 1 | **LINKWIN** t_ms:16121158 stream:0xa0be1a79 wall:0 window_ms:60013
said: 2 | **LINK** peer:0x00000011 proto:espnow n:65 rssi_min:-54 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000300 proto:espnow n:194 rssi_min:-40 rssi_med:-40 rssi_max:-39
said: 4 | **LINK** peer:0x00000010 proto:espnow n:72 rssi_min:-58 rssi_med:-57 rssi_max:-56
said: 5 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-71 rssi_max:-61
said: 6 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-80 rssi_med:-66 rssi_max:-61
said: 7 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-57 rssi_max:-56
said: 8 | **LINK** peer:0x00000012 proto:espnow n:70 rssi_min:-93 rssi_med:-45 rssi_max:-44
said: 9 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-53 rssi_max:-52
```

---

@LAT105LON2457 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 16077420 ±21 frame:20500
seq: 652
follows: 0x00000010:808 0x00000011:742 0x00000100:732 0x00000200:1425 0x00000300:3478
said: 1 | **LINKWIN** t_ms:16061214 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:123 rssi_min:-58 rssi_med:-56 rssi_max:-55
said: 3 | **LINK** peer:0x00000300 proto:espnow n:143 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 4 | **LINK** peer:0x00000200 proto:espnow n:82 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-53 rssi_med:-52 rssi_max:-50
said: 6 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 7 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-66 rssi_max:-53
said: 8 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-66 rssi_max:-55
said: 9 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-82 rssi_med:-66 rssi_max:-53
```

---

@LAT105LON2458 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 16137224 ±21 frame:20500
seq: 653
follows: 0x00000010:809 0x00000011:743 0x00000100:732 0x00000200:1426 0x00000300:3480
said: 1 | **LINKWIN** t_ms:16121242 stream:0xa0be1a79 wall:0 window_ms:60028
said: 2 | **LINK** peer:0x00000200 proto:espnow n:126 rssi_min:-47 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:213 rssi_min:-49 rssi_med:-47 rssi_max:-42
said: 4 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-66 rssi_max:-53
said: 5 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 6 | **LINK** peer:0x00000011 proto:espnow n:89 rssi_min:-58 rssi_med:-56 rssi_max:-55
said: 7 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-53 rssi_med:-52 rssi_max:-50
said: 8 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-82 rssi_med:-65 rssi_max:-53
said: 9 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-80 rssi_med:-66 rssi_max:-55
```

---

@LAT105LON2459 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 16156247 ±21 frame:20500
seq: 744
follows: 0x00000010:809 0x00000012:653 0x00000100:732 0x00000200:1427 0x00000300:3480
said: 1 | **LINKWIN** t_ms:16140055 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-82 rssi_med:-61 rssi_max:-55
said: 3 | **LINK** peer:0x00000012 proto:espnow n:95 rssi_min:-59 rssi_med:-59 rssi_max:-58
said: 4 | **LINK** peer:0x00000300 proto:espnow n:173 rssi_min:-39 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-45 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000200 proto:espnow n:139 rssi_min:-57 rssi_med:-56 rssi_max:-56
said: 7 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-84 rssi_med:-71 rssi_max:-56
said: 8 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-43 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-67 rssi_max:-65
```

---

@LAT103LON854 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 16169252 ±21 frame:20500
seq: 810
follows: 0x00000011:744 0x00000012:653 0x00000100:732 0x00000200:1427 0x00000300:3480
said: 1 | **LINKWIN** t_ms:16153057 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:89 rssi_min:-56 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000011 proto:espnow n:114 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:espnow n:153 rssi_min:-44 rssi_med:-42 rssi_max:-39
said: 5 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-77 rssi_med:-66 rssi_max:-55
said: 6 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-59 rssi_med:-58 rssi_max:-52
said: 7 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-79 rssi_med:-53 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:ble n:47 rssi_min:-80 rssi_med:-70 rssi_max:-63
said: 9 | **LINK** peer:0x00000200 proto:espnow n:127 rssi_min:-60 rssi_med:-58 rssi_max:-56
```

---

@LAT105LON2460 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 16197449 ±21 frame:20500
seq: 654
follows: 0x00000010:810 0x00000011:744 0x00000100:732 0x00000200:1427 0x00000300:3482
said: 1 | **LINKWIN** t_ms:16181242 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:105 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 3 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 4 | **LINK** peer:0x00000011 proto:espnow n:85 rssi_min:-58 rssi_med:-56 rssi_max:-55
said: 5 | **LINK** peer:0x00000200 proto:espnow n:62 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-83 rssi_med:-66 rssi_max:-53
said: 7 | **LINK** peer:0x00000010 proto:espnow n:105 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 8 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-66 rssi_max:-53
said: 9 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-71 rssi_max:-55
```

---

@LAT105LON2461 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 16197366 ±21 frame:20500
seq: 1428
follows: 0x00000010:810 0x00000011:744 0x00000012:653 0x00000100:732 0x00000300:3482
said: 1 | **LINKWIN** t_ms:16181161 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:94 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000012 proto:ble n:69 rssi_min:-82 rssi_med:-57 rssi_max:-56
said: 4 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-65 rssi_max:-61
said: 5 | **LINK** peer:0x00000010 proto:espnow n:97 rssi_min:-58 rssi_med:-57 rssi_max:-56
said: 6 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 7 | **LINK** peer:0x00000011 proto:espnow n:78 rssi_min:-54 rssi_med:-53 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-71 rssi_max:-61
said: 9 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-51
```

---

@LAT105LON2462 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 16196277 ±0 frame:20500
seq: 3481
follows: 0x00000010:810 0x00000011:744 0x00000012:653 0x00000100:732 0x00000200:1427
said: 1 | **LINKWIN** t_ms:16180108 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:77 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000011 proto:espnow n:93 rssi_min:-42 rssi_med:-41 rssi_max:-39
said: 4 | **LINK** peer:0x00000010 proto:espnow n:99 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000012 proto:espnow n:87 rssi_min:-52 rssi_med:-50 rssi_max:-49
said: 6 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-65 rssi_med:-56 rssi_max:-55
said: 7 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-61 rssi_med:-60 rssi_max:-58
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-72 rssi_med:-69 rssi_max:-62
said: 9 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-66 rssi_med:-51 rssi_max:-46
said: 10 | 0x00000012 espnow met predicted:-50 observed:-50
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-44 observed:-44
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-56 observed:-56
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000012 ble met predicted:-71 observed:-69
percept: 14 | 0x00000012 | link_stable | ble | + | -
said: 15 | 0x00000011 espnow met predicted:-41 observed:-41
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-60 observed:-60
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-51 observed:-51
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON855 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 16229252 ±21 frame:20500
seq: 811
follows: 0x00000011:745 0x00000012:654 0x00000100:732 0x00000200:1428 0x00000300:3482
said: 1 | **LINKWIN** t_ms:16213056 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:76 rssi_min:-47 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-70 rssi_max:-64
said: 4 | **LINK** peer:0x00000200 proto:espnow n:73 rssi_min:-60 rssi_med:-57 rssi_max:-56
said: 5 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-76 rssi_med:-53 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-58 rssi_max:-52
said: 7 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-79 rssi_med:-66 rssi_max:-55
said: 8 | **LINK** peer:0x00000012 proto:espnow n:92 rssi_min:-55 rssi_med:-54 rssi_max:-53
said: 9 | **LINK** peer:0x00000300 proto:espnow n:177 rssi_min:-43 rssi_med:-42 rssi_max:-39
```

---

@LAT105LON2463 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 16216247 ±21 frame:20500
seq: 745
follows: 0x00000010:810 0x00000012:654 0x00000100:732 0x00000200:1428 0x00000300:3482
said: 1 | **LINKWIN** t_ms:16200055 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-85 rssi_med:-71 rssi_max:-56
said: 3 | **LINK** peer:0x00000300 proto:espnow n:154 rssi_min:-40 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000200 proto:espnow n:75 rssi_min:-57 rssi_med:-56 rssi_max:-56
said: 5 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-59 rssi_med:-59 rssi_max:-58
said: 6 | **LINK** peer:0x00000010 proto:espnow n:92 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-43 rssi_max:-41
said: 8 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-61 rssi_max:-55
said: 9 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-80 rssi_med:-67 rssi_max:-66
```

---

@LAT105LON2464 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 16256277 ±0 frame:20500
seq: 3483
follows: 0x00000010:811 0x00000011:745 0x00000012:654 0x00000100:732 0x00000200:1428
said: 1 | **LINKWIN** t_ms:16240108 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-66 rssi_med:-51 rssi_max:-46
said: 3 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-71 rssi_max:-61
said: 4 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-80 rssi_med:-56 rssi_max:-55
said: 5 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-62 rssi_med:-60 rssi_max:-58
said: 6 | **LINK** peer:0x00000011 proto:espnow n:78 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000200 proto:espnow n:89 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000010 proto:espnow n:73 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 9 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 10 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-41 observed:-41
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-44 observed:-44
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-50 observed:-50
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-56 observed:-56
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000010 ble met predicted:-60 observed:-60
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-69 observed:-71
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-51 observed:-51
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT105LON2465 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 16257449 ±21 frame:20500
seq: 655
follows: 0x00000010:811 0x00000011:745 0x00000100:732 0x00000200:1428 0x00000300:3484
said: 1 | **LINKWIN** t_ms:16241242 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-66 rssi_max:-53
said: 3 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-83 rssi_med:-66 rssi_max:-53
said: 4 | **LINK** peer:0x00000300 proto:espnow n:206 rssi_min:-49 rssi_med:-47 rssi_max:-42
said: 5 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-81 rssi_med:-66 rssi_max:-55
said: 6 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 7 | **LINK** peer:0x00000010 proto:espnow n:72 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 8 | **LINK** peer:0x00000200 proto:espnow n:85 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 9 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-59 rssi_med:-56 rssi_max:-55
```

---

@LAT105LON2466 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 16257386 ±21 frame:20500
seq: 1429
follows: 0x00000010:811 0x00000011:745 0x00000012:654 0x00000100:732 0x00000300:3484
said: 1 | **LINKWIN** t_ms:16241175 stream:0xa0be1a79 wall:0 window_ms:60019
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-71 rssi_max:-61
said: 3 | **LINK** peer:0x00000300 proto:espnow n:193 rssi_min:-40 rssi_med:-40 rssi_max:-39
said: 4 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-53 rssi_max:-51
said: 5 | **LINK** peer:0x00000011 proto:espnow n:76 rssi_min:-54 rssi_med:-53 rssi_max:-52
said: 6 | **LINK** peer:0x00000012 proto:espnow n:90 rssi_min:-45 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-80 rssi_med:-57 rssi_max:-55
said: 8 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-80 rssi_med:-65 rssi_max:-61
said: 9 | **LINK** peer:0x00000010 proto:espnow n:81 rssi_min:-58 rssi_med:-56 rssi_max:-56
```

---

@LAT105LON2467 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 16276248 ±21 frame:20500
seq: 746
follows: 0x00000010:811 0x00000012:655 0x00000100:732 0x00000200:1429 0x00000300:3484
said: 1 | **LINKWIN** t_ms:16260055 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:86 rssi_min:-59 rssi_med:-59 rssi_max:-58
said: 3 | **LINK** peer:0x00000300 proto:espnow n:135 rssi_min:-39 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000010 proto:espnow n:85 rssi_min:-45 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000200 proto:espnow n:112 rssi_min:-57 rssi_med:-56 rssi_max:-56
said: 6 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-57 rssi_max:-55
said: 7 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-43 rssi_max:-41
said: 8 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-85 rssi_med:-71 rssi_max:-56
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-67 rssi_max:-65
```

---

@LAT103LON856 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 16289253 ±21 frame:20500
seq: 812
follows: 0x00000011:746 0x00000012:655 0x00000100:732 0x00000200:1429 0x00000300:3484
said: 1 | **LINKWIN** t_ms:16273056 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:96 rssi_min:-46 rssi_med:-44 rssi_max:-39
said: 3 | **LINK** peer:0x00000012 proto:espnow n:81 rssi_min:-55 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000300 proto:espnow n:126 rssi_min:-43 rssi_med:-42 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:112 rssi_min:-59 rssi_med:-57 rssi_max:-56
said: 6 | **LINK** peer:0x00000012 proto:ble n:72 rssi_min:-82 rssi_med:-66 rssi_max:-55
said: 7 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-73 rssi_med:-70 rssi_max:-64
said: 8 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-58 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-53 rssi_max:-52
```

---

@LAT105LON2468 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 16317387 ±21 frame:20500
seq: 1430
follows: 0x00000010:812 0x00000011:746 0x00000012:655 0x00000100:732 0x00000300:3486
said: 1 | **LINKWIN** t_ms:16301180 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-83 rssi_med:-56 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-61 rssi_med:-57 rssi_max:-56
said: 4 | **LINK** peer:0x00000300 proto:espnow n:98 rssi_min:-40 rssi_med:-39 rssi_max:-39
said: 5 | **LINK** peer:0x00000011 proto:espnow n:88 rssi_min:-54 rssi_med:-52 rssi_max:-52
said: 6 | **LINK** peer:0x00000012 proto:espnow n:124 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 7 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-72 rssi_med:-71 rssi_max:-60
said: 8 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-65 rssi_max:-61
said: 9 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-53 rssi_max:-52
```

---

@LAT105LON2469 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 16317448 ±21 frame:20500
seq: 656
follows: 0x00000010:812 0x00000011:746 0x00000100:732 0x00000200:1429 0x00000300:3486
said: 1 | **LINKWIN** t_ms:16301242 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:107 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 4 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-83 rssi_med:-66 rssi_max:-53
said: 5 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-66 rssi_max:-53
said: 6 | **LINK** peer:0x00000011 proto:espnow n:109 rssi_min:-58 rssi_med:-56 rssi_max:-55
said: 7 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-81 rssi_med:-66 rssi_max:-55
said: 8 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000300 proto:espnow n:99 rssi_min:-48 rssi_med:-47 rssi_max:-46
```

---

@LAT105LON2470 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 16316277 ±0 frame:20500
seq: 3485
follows: 0x00000010:812 0x00000011:746 0x00000012:655 0x00000100:732 0x00000200:1429
said: 1 | **LINKWIN** t_ms:16300108 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-66 rssi_med:-56 rssi_max:-55
said: 3 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-66 rssi_med:-51 rssi_max:-46
said: 4 | **LINK** peer:0x00000012 proto:espnow n:87 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 5 | **LINK** peer:0x00000200 proto:espnow n:94 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 6 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-42 rssi_med:-41 rssi_max:-39
said: 7 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-47 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-72 rssi_med:-71 rssi_max:-62
said: 9 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-82 rssi_med:-60 rssi_max:-59
said: 10 | 0x00000011 ble met predicted:-51 observed:-51
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-71 observed:-71
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000200 ble met predicted:-56 observed:-56
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000010 ble met predicted:-60 observed:-60
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-44 observed:-44
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000012 espnow met predicted:-50 observed:-50
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```
@LAT106LON70 | created:0 | updated:0

**BAR** frame:20500 bar:27 own:8 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:8 lo:802 hi:810 sum:6451
**HOLDS** agent:0x00000011 n:10 lo:735 hi:745 sum:7402
**HOLDS** agent:0x00000012 n:10 lo:645 hi:654 sum:6495
**HOLDS** agent:0x00000200 n:10 lo:1419 hi:1428 sum:14235
**HOLDS** agent:0x00000300 n:10 lo:3463 hi:3481 sum:34720
**DELIVER** up_s:656 heap:122652 fetched:50 unanswered:34 broken:4 resumed:128 empty:7 served:132 wants:135 early:0 wantq_drop:0 superseded:0

---

@LAT103LON857 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 16350455 ±21 frame:20500
seq: 813
follows: 0x00000011:747 0x00000012:656 0x00000100:732 0x00000200:1430 0x00000300:3486
said: 1 | **LINKWIN** t_ms:16332509 stream:0xa0be1a79 wall:0 window_ms:61202
said: 2 | **LINK** peer:0x00000300 proto:espnow n:146 rssi_min:-44 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:102 rssi_min:-60 rssi_med:-58 rssi_max:-56
said: 4 | **LINK** peer:0x00000011 proto:espnow n:93 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-71 rssi_max:-64
said: 6 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-58 rssi_max:-52
said: 7 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-73 rssi_med:-66 rssi_max:-55
said: 8 | **LINK** peer:0x00000012 proto:espnow n:81 rssi_min:-55 rssi_med:-54 rssi_max:-53
said: 9 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-53 rssi_max:-52
```

---

@LAT105LON2471 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 16336249 ±21 frame:20500
seq: 747
follows: 0x00000010:812 0x00000012:656 0x00000100:732 0x00000200:1430 0x00000300:3486
said: 1 | **LINKWIN** t_ms:16320055 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-67 rssi_max:-65
said: 3 | **LINK** peer:0x00000300 proto:espnow n:132 rssi_min:-40 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-59 rssi_med:-59 rssi_max:-58
said: 5 | **LINK** peer:0x00000010 proto:espnow n:126 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-57 rssi_med:-56 rssi_max:-56
said: 7 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-85 rssi_med:-71 rssi_max:-56
said: 8 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-82 rssi_med:-61 rssi_max:-55
said: 9 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-63 rssi_max:-39
```

---

@LAT103LON858 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 16410456 ±21 frame:20500
seq: 814
follows: 0x00000011:748 0x00000012:657 0x00000100:732 0x00000200:1431 0x00000300:3488
said: 1 | **LINKWIN** t_ms:16394259 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-80 rssi_med:-66 rssi_max:-54
said: 4 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-66 rssi_med:-58 rssi_max:-52
said: 5 | **LINK** peer:0x00000012 proto:espnow n:56 rssi_min:-58 rssi_med:-54 rssi_max:-50
said: 6 | **LINK** peer:0x00000011 proto:espnow n:148 rssi_min:-59 rssi_med:-44 rssi_max:-39
said: 7 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-67 rssi_max:-59
said: 8 | **LINK** peer:0x00000300 proto:espnow n:131 rssi_min:-57 rssi_med:-43 rssi_max:-39
said: 9 | **LINK** peer:0x00000200 proto:espnow n:100 rssi_min:-60 rssi_med:-57 rssi_max:-54
```

---

@LAT104LON91 | created:0 | updated:0

**carried through @LAT103LON818**

```ttdb-carried
through: 818
through: 8200
```

---

@LAT105LON2472 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 16376277 ±0 frame:20500
seq: 3487
follows: 0x00000010:813 0x00000011:747 0x00000012:656 0x00000100:732 0x00000200:1430
said: 1 | **LINKWIN** t_ms:16360108 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000012 proto:espnow n:77 rssi_min:-52 rssi_med:-50 rssi_max:-49
said: 4 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-43 rssi_med:-41 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-56 rssi_max:-55
said: 6 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-62 rssi_med:-60 rssi_max:-59
said: 7 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-80 rssi_med:-71 rssi_max:-62
said: 8 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-66 rssi_med:-51 rssi_max:-46
said: 9 | **LINK** peer:0x00000010 proto:espnow n:104 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 10 | 0x00000200 ble met predicted:-56 observed:-56
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-51 observed:-51
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-50 observed:-50
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-44 observed:-44
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-71 observed:-71
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-60 observed:-60
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT105LON2473 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 16377450 ±21 frame:20500
seq: 1431
follows: 0x00000010:813 0x00000011:747 0x00000012:656 0x00000100:732 0x00000300:3488
said: 1 | **LINKWIN** t_ms:16361242 stream:0xa0be1a79 wall:0 window_ms:60064
said: 2 | **LINK** peer:0x00000300 proto:espnow n:142 rssi_min:-40 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-58 rssi_med:-57 rssi_max:-56
said: 4 | **LINK** peer:0x00000012 proto:espnow n:74 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:espnow n:127 rssi_min:-54 rssi_med:-52 rssi_max:-52
said: 6 | **LINK** peer:0x00000012 proto:ble n:74 rssi_min:-81 rssi_med:-57 rssi_max:-55
said: 7 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-71 rssi_max:-61
said: 9 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-65 rssi_max:-61
```

---

@LAT105LON2474 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 16396247 ±21 frame:20500
seq: 748
follows: 0x00000010:813 0x00000012:657 0x00000100:732 0x00000200:1431 0x00000300:3488
said: 1 | **LINKWIN** t_ms:16380055 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:98 rssi_min:-72 rssi_med:-56 rssi_max:-54
said: 3 | **LINK** peer:0x00000300 proto:espnow n:81 rssi_min:-42 rssi_med:-34 rssi_max:-30
said: 4 | **LINK** peer:0x00000012 proto:espnow n:52 rssi_min:-59 rssi_med:-59 rssi_max:-53
said: 5 | **LINK** peer:0x00000010 proto:espnow n:105 rssi_min:-60 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-43 rssi_max:-41
said: 7 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-82 rssi_med:-67 rssi_max:-65
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-61 rssi_max:-53
said: 9 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-85 rssi_med:-77 rssi_max:-56
```

---

@LAT105LON2475 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 16437455 ±21 frame:20500
seq: 1432
follows: 0x00000010:814 0x00000011:749 0x00000012:657 0x00000100:732 0x00000300:3490
said: 1 | **LINKWIN** t_ms:16421245 stream:0xa0be1a79 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000011 proto:espnow n:125 rssi_min:-68 rssi_med:-55 rssi_max:-51
said: 3 | **LINK** peer:0x00000012 proto:espnow n:61 rssi_min:-46 rssi_med:-44 rssi_max:-40
said: 4 | **LINK** peer:0x00000300 proto:espnow n:136 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-64 rssi_med:-56 rssi_max:-50
said: 6 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 7 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-79 rssi_med:-69 rssi_max:-57
said: 8 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-57 rssi_max:-55
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-67 rssi_max:-57
```

---

@LAT105LON2476 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 16377450 ±21 frame:20500
seq: 657
follows: 0x00000010:813 0x00000011:747 0x00000100:732 0x00000200:1430 0x00000300:3488
said: 1 | **LINKWIN** t_ms:16361242 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-54 rssi_med:-51 rssi_max:-51
said: 3 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-58 rssi_med:-56 rssi_max:-55
said: 4 | **LINK** peer:0x00000200 proto:espnow n:99 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000300 proto:espnow n:138 rssi_min:-49 rssi_med:-47 rssi_max:-42
said: 6 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-82 rssi_med:-66 rssi_max:-53
said: 7 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-81 rssi_med:-66 rssi_max:-55
said: 9 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-66 rssi_max:-53
```

---

@LAT105LON2477 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 16437451 ±21 frame:20500
seq: 658
follows: 0x00000010:814 0x00000011:749 0x00000100:732 0x00000200:1431 0x00000300:3490
said: 1 | **LINKWIN** t_ms:16421242 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:123 rssi_min:-64 rssi_med:-54 rssi_max:-47
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-67 rssi_max:-52
said: 4 | **LINK** peer:0x00000300 proto:espnow n:127 rssi_min:-60 rssi_med:-48 rssi_max:-42
said: 5 | **LINK** peer:0x00000010 proto:espnow n:105 rssi_min:-62 rssi_med:-52 rssi_max:-49
said: 6 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-59 rssi_max:-52
said: 7 | **LINK** peer:0x00000200 proto:espnow n:157 rssi_min:-46 rssi_med:-43 rssi_max:-41
said: 8 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-65 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:ble n:70 rssi_min:-82 rssi_med:-54 rssi_max:-50
```

---

@LAT105LON2478 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 16456249 ±21 frame:20500
seq: 750
follows: 0x00000010:814 0x00000012:658 0x00000100:732 0x00000200:1432 0x00000300:3490
said: 1 | **LINKWIN** t_ms:16440055 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-83 rssi_med:-68 rssi_max:-61
said: 3 | **LINK** peer:0x00000300 proto:espnow n:120 rssi_min:-86 rssi_med:-39 rssi_max:-30
said: 4 | **LINK** peer:0x00000200 proto:espnow n:112 rssi_min:-73 rssi_med:-59 rssi_max:-53
said: 5 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-63 rssi_med:-45 rssi_max:-41
said: 6 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-71 rssi_med:-59 rssi_max:-53
said: 7 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-59 rssi_max:-52
said: 8 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-86 rssi_med:-71 rssi_max:-54
said: 9 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-48 rssi_max:-39
```

---

@LAT103LON859 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 16472041 ±21 frame:20500
seq: 815
follows: 0x00000011:750 0x00000012:658 0x00000100:732 0x00000200:1432 0x00000300:3490
said: 1 | **LINKWIN** t_ms:16454208 stream:0xa0be1a79 wall:0 window_ms:61584
said: 2 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-82 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:72 rssi_min:-80 rssi_med:-58 rssi_max:-51
said: 4 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-83 rssi_med:-66 rssi_max:-52
said: 5 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-79 rssi_med:-69 rssi_max:-59
said: 6 | **LINK** peer:0x00000012 proto:espnow n:110 rssi_min:-68 rssi_med:-54 rssi_max:-50
said: 7 | **LINK** peer:0x00000300 proto:espnow n:150 rssi_min:-59 rssi_med:-42 rssi_max:-39
said: 8 | **LINK** peer:0x00000200 proto:espnow n:132 rssi_min:-60 rssi_med:-57 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-66 rssi_med:-44 rssi_max:-40
```

---

@LAT105LON2479 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 16436277 ±0 frame:20500
seq: 3489
follows: 0x00000010:814 0x00000011:749 0x00000012:657 0x00000100:732 0x00000200:1431
said: 1 | **LINKWIN** t_ms:16420108 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-79 rssi_med:-52 rssi_max:-46
said: 3 | **LINK** peer:0x00000012 proto:espnow n:67 rssi_min:-63 rssi_med:-50 rssi_max:-45
said: 4 | **LINK** peer:0x00000011 proto:espnow n:135 rssi_min:-54 rssi_med:-42 rssi_max:-36
said: 5 | **LINK** peer:0x00000200 proto:espnow n:139 rssi_min:-47 rssi_med:-44 rssi_max:-42
said: 6 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-58 rssi_med:-49 rssi_max:-42
said: 7 | **LINK** peer:0x00000012 proto:ble n:51 rssi_min:-73 rssi_med:-64 rssi_max:-61
said: 8 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-79 rssi_med:-61 rssi_max:-54
said: 9 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-57 rssi_max:-55
said: 10 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-50 observed:-50
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-41 observed:-42
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-56 observed:-57
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-60 observed:-61
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000012 ble violated predicted:-71 observed:-64
percept: 15 | 0x00000012 | link_stable | ble | - | -
said: 16 | 0x00000011 ble met predicted:-51 observed:-52
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-44 observed:-49
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```
