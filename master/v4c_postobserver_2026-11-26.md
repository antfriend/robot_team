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

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x26826178 wall:0 t_ms:0 node:0x12 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xb23c7677 wall:0 t_ms:14079 node:0x12 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x5b53f35b wall:0 t_ms:19182 node:0x12 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

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

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xee98fca8 wall:0 t_ms:4459929 node:0x12 from:0x11
**REMAP** prev_stream:0x8aaab6fc prev_t_ms:3704 offset_ms:4456225 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xc909d5a8 wall:0 t_ms:138646 node:0x12 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xc909d5a8 wall:0 t_ms:3488980 node:0x12 from:0x300
**REMAP** prev_stream:0x4a8164a3 prev_t_ms:3185 offset_ms:3485795 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:3 removed:48 last_lon:47 t_ms:4013569 stream:0xc909d5a8 wall:0 node:0x00000012

---

@LAT100LON5 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:2 removed:16 last_lon:15 t_ms:0 stream:0x00000000 wall:0 node:0x00000012

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4100164 stream:0xc909d5a8 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT103LON8228 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9981619 ±21 frame:20500
seq: 548
follows: 0x00000010:702 0x00000011:636 0x00000100:732 0x00000200:1322 0x00000300:3266
said: 1 | **ENTWIN** t_ms:9965448 stream:0xa0be1a79 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 11 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,64677217947d,bc102f237ace,0283cce0e689,84a329c78fec,5ce28c488e0c
said: 13 | **COVERED** windows:2 entities:10 window_ms:1200061 first_t_ms:8765375 last_t_ms:9365397 covered_by:@LAT103LON8227
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-40 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-69 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-71 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-82 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-82 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-84 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-86 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-93 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-92 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95 windows:1
```

---

@LAT103LON8229 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13581661 ±21 frame:20500
seq: 609
follows: 0x00000010:765 0x00000011:699 0x00000100:732 0x00000200:1383 0x00000300:3392
said: 1 | **ENTWIN** t_ms:13565468 stream:0xa0be1a79 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 10 | **RUN** windows_since_last:6 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,bc102f237ace,64677217947d,0283cce0e689,84a329c78fec
said: 12 | **COVERED** windows:5 entities:10 window_ms:3000021 first_t_ms:10565448 last_t_ms:12965468 covered_by:@LAT103LON8228
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-35 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-67 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-71 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-81 windows:5
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:5 rssi:-83 windows:5
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-80 windows:5
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:5 rssi:-86 windows:5
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:3 rssi:-90 windows:3
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:3 rssi:-90 windows:3
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:2 rssi:-95 windows:2
```

---

@LAT103LON8230 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 14781699 ±21 frame:20500
seq: 630
follows: 0x00000010:787 0x00000011:719 0x00000100:732 0x00000200:1404 0x00000300:3433
said: 1 | **ENTWIN** t_ms:14765500 stream:0xa0be1a79 wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689,64677217947d
said: 10 | **COVERED** windows:1 entities:7 window_ms:600032 first_t_ms:14165501 last_t_ms:14165501 covered_by:@LAT103LON8229
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87 windows:1
```

---

@LAT103LON8231 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 16581707 ±21 frame:20500
seq: 661
follows: 0x00000010:817 0x00000011:751 0x00000100:732 0x00000200:1434 0x00000300:3494
said: 1 | **ENTWIN** t_ms:16565499 stream:0xa0be1a79 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689,5ce28c488e0c,64677217947d
said: 11 | **COVERED** windows:2 entities:10 window_ms:1200000 first_t_ms:15365499 last_t_ms:15965500 covered_by:@LAT103LON8230
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-40 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-68 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-72 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-81 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-83 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-80 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-87 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-89 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-95 windows:1
```

---

@LAT103LON8232 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 19581726 ±21 frame:20500
seq: 712
follows: 0x00000010:869 0x00000011:803 0x00000100:732 0x00000200:1486 0x00000300:3598
said: 1 | **ENTWIN** t_ms:19565551 stream:0xa0be1a79 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,0283cce0e689
said: 13 | **COVERED** windows:4 entities:11 window_ms:2400001 first_t_ms:17165501 last_t_ms:18965551 covered_by:@LAT103LON8231
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-41 windows:4
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-73 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-71 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-79 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:3 rssi:-84 windows:3
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-81 windows:4
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-86 windows:4
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-97 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-92 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-90 windows:2
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94 windows:1
```

---

@LAT103LON8233 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21381762 ±21 frame:20500
seq: 743
follows: 0x00000010:898 0x00000011:835 0x00000100:732 0x00000200:1516 0x00000300:3661
said: 1 | **ENTWIN** t_ms:21365574 stream:0xa0be1a79 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-95
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,bc102f237ace,64677217947d,0283cce0e689,aef9ff2626ac,84a329c78fec
said: 12 | **COVERED** windows:2 entities:10 window_ms:1200023 first_t_ms:20165551 last_t_ms:20765574 covered_by:@LAT103LON8232
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-41 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-71 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-73 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-80 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-82 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-86 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-90 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-91 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94 windows:1
```

---

@LAT103LON8234 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21981765 ±21 frame:20500
seq: 754
follows: 0x00000010:909 0x00000011:846 0x00000100:732 0x00000200:1526 0x00000300:3682
said: 1 | **ENTWIN** t_ms:21965574 stream:0xa0be1a79 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,0283cce0e689,84a329c78fec
```

---

@LAT103LON8235 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 23781775 ±21 frame:20500
seq: 785
follows: 0x00000010:940 0x00000011:878 0x00000100:732 0x00000200:1558 0x00000300:3745
said: 1 | **ENTWIN** t_ms:23765574 stream:0xa0be1a79 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689
said: 11 | **COVERED** windows:2 entities:10 window_ms:1200001 first_t_ms:22565574 last_t_ms:23165575 covered_by:@LAT103LON8234
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-41 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-72 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-71 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-80 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-82 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-91 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-92 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93 windows:1
```

---

@LAT103LON8236 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 27381798 ±21 frame:20500
seq: 846
follows: 0x00000010:1002 0x00000011:941 0x00000100:732 0x00000200:1620 0x00000300:3870
said: 1 | **ENTWIN** t_ms:27365630 stream:0xa0be1a79 wall:0 window_ms:599993 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689
said: 11 | **COVERED** windows:5 entities:10 window_ms:3000012 first_t_ms:24365574 last_t_ms:26765585 covered_by:@LAT103LON8235
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-43 windows:5
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-74 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-71 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-80 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-83 windows:5
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-93 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:2 rssi:-95 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-87 windows:4
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-88 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-92 windows:2
```

---

@LAT103LON8237 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 28581810 ±21 frame:20500
seq: 867
follows: 0x00000010:1022 0x00000011:963 0x00000100:732 0x00000200:1641 0x00000300:3911
said: 1 | **ENTWIN** t_ms:28565630 stream:0xa0be1a79 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,64677217947d,0283cce0e689
said: 13 | **COVERED** windows:1 entities:7 window_ms:600000 first_t_ms:27965630 last_t_ms:27965630 covered_by:@LAT103LON8236
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
```

---

@LAT103LON8238 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 30981823 ±21 frame:20500
seq: 908
follows: 0x00000010:1064 0x00000011:1006 0x00000100:732 0x00000200:1684 0x00000300:3993
said: 1 | **ENTWIN** t_ms:30965630 stream:0xa0be1a79 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 11 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d,0283cce0e689,5ce28c488e0c
said: 13 | **COVERED** windows:3 entities:10 window_ms:1800000 first_t_ms:29165630 last_t_ms:30365631 covered_by:@LAT103LON8237
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-44 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-74 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-77 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-82 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-83 windows:3
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-88 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:3 rssi:-91 windows:3
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-91 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96 windows:1
```

---

@LAT103LON8239 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34581889 ±21 frame:20500
seq: 969
follows: 0x00000010:1125 0x00000011:1071 0x00000100:732 0x00000200:1748 0x00000300:4118
said: 1 | **ENTWIN** t_ms:34565674 stream:0xa0be1a79 wall:0 window_ms:600043 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,84a329c78fec,5ce28c488e0c
said: 11 | **COVERED** windows:5 entities:10 window_ms:3000001 first_t_ms:31565630 last_t_ms:33965632 covered_by:@LAT103LON8238
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-44 windows:5
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-74 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-73 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-81 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-84 windows:5
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:5 rssi:-89 windows:5
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:5 rssi:-89 windows:5
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:5 rssi:-84 windows:5
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:4 rssi:-91 windows:4
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-96 windows:1
```

---

@LAT103LON8240 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 35781863 ±21 frame:20500
seq: 990
follows: 0x00000010:1146 0x00000011:1092 0x00000100:732 0x00000200:1770 0x00000300:4161
said: 1 | **ENTWIN** t_ms:35765692 stream:0xa0be1a79 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,5ce28c488e0c,64677217947d
said: 11 | **COVERED** windows:1 entities:6 window_ms:599967 first_t_ms:35165641 last_t_ms:35165641 covered_by:@LAT103LON8239
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
```

---

@LAT103LON8241 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36105756 ±21 frame:20500
seq: 996
follows: 0x00000010:1152 0x00000011:1098 0x00000100:732 0x00000200:1775 0x00000300:4172
said: 1 | **ENTWIN** t_ms:36089294 stream:0xa0be1a79 wall:0 window_ms:60293 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8242 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 37275629 ±21 frame:20500
seq: 1016
follows: 0x00000010:1174 0x00000011:1118 0x00000100:732 0x00000200:1795 0x00000300:4208
said: 1 | **ENTWIN** t_ms:37259462 stream:0xa0be1a79 wall:0 window_ms:600002 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-95
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 11 | **COVERED** windows:1 entities:7 window_ms:569874 first_t_ms:36659460 last_t_ms:36659460 covered_by:@LAT103LON8241
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94 windows:1
```

---

@LAT103LON8243 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 37875624 ±21 frame:20500
seq: 1027
follows: 0x00000010:1180 0x00000011:1129 0x00000100:732 0x00000200:1806 0x00000300:4214
said: 1 | **ENTWIN** t_ms:37859461 stream:0xa0be1a79 wall:0 window_ms:599999 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-97
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 13 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689
```

---

@LAT103LON8244 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 38471471 ±21 frame:20500
seq: 1036
follows: 0x00000010:1183 0x00000011:1133 0x00000100:732 0x00000200:1816 0x00000300:4214
said: 1 | **ENTWIN** t_ms:38455222 stream:0xa0be1a79 wall:0 window_ms:62089 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8245 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 689146 ±21 frame:10000
seq: 1038
follows: 0x00000010:1186 0x00000011:1135 0x00000100:743 0x00000200:1831 0x00000300:4218
said: 1 | **ENTWIN** t_ms:1005034 stream:0x364dd329 wall:0 window_ms:60072 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON8246 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 85996 ±21 frame:8000
seq: 1046
follows: 0x00000010:1192 0x00000011:1141 0x00000100:751 0x00000200:1840 0x00000300:4236
said: 1 | **ENTWIN** t_ms:75033 stream:0x732acba3 wall:0 window_ms:60326 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8247 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1239715 ±21 frame:8000
seq: 1066
follows: 0x00000010:1213 0x00000011:1162 0x00000100:772 0x00000200:1860 0x00000300:4275
said: 1 | **ENTWIN** t_ms:1229046 stream:0x732acba3 wall:0 window_ms:600000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 13 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 14 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,0283cce0e689,64677217947d
said: 15 | **COVERED** windows:1 entities:11 window_ms:553715 first_t_ms:629045 last_t_ms:629045 covered_by:@LAT103LON8246
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94 windows:1
```

---

@LAT103LON8248 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1839720 ±21 frame:8000
seq: 1077
follows: 0x00000010:1223 0x00000011:1173 0x00000100:783 0x00000200:1871 0x00000300:4295
said: 1 | **ENTWIN** t_ms:1829045 stream:0x732acba3 wall:0 window_ms:600000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 12 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 14 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,0283cce0e689,7236bc441422,c2e94427adcf,84a329c78fec,64677217947d
```

---

@LAT103LON8249 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3639739 ±21 frame:8000
seq: 1108
follows: 0x00000010:1257 0x00000011:1204 0x00000100:816 0x00000200:1901 0x00000300:4357
said: 1 | **ENTWIN** t_ms:3629053 stream:0x732acba3 wall:0 window_ms:600008 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 13 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-97
said: 14 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:11 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,64677217947d,c2e94427adcf,0283cce0e689,e45e1b9f675a,84a329c78fec,7236bc441422
said: 16 | **COVERED** windows:2 entities:11 window_ms:1200000 first_t_ms:2429043 last_t_ms:3029045 covered_by:@LAT103LON8248
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-38 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-68 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-77 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-78 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-82 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-89 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95 windows:1
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 27 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91 windows:1
```

---

@LAT103LON8250 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4239743 ±21 frame:8000
seq: 1119
follows: 0x00000010:1268 0x00000011:1214 0x00000100:828 0x00000200:1912 0x00000300:4378
said: 1 | **ENTWIN** t_ms:4229055 stream:0x732acba3 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,0283cce0e689,c2e94427adcf,84a329c78fec,7236bc441422
```

---

@LAT103LON8251 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4839748 ±21 frame:8000
seq: 1130
follows: 0x00000010:1278 0x00000011:1224 0x00000100:838 0x00000200:1923 0x00000300:4396
said: 1 | **ENTWIN** t_ms:4829055 stream:0x732acba3 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,0283cce0e689,c2e94427adcf,7236bc441422,64677217947d,84a329c78fec
```

---

@LAT103LON8252 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5439753 ±21 frame:8000
seq: 1141
follows: 0x00000010:1289 0x00000011:1234 0x00000100:849 0x00000200:1933 0x00000300:4417
said: 1 | **ENTWIN** t_ms:5429056 stream:0x732acba3 wall:0 window_ms:600001 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689,c2e94427adcf,7236bc441422,64677217947d
```

---

@LAT103LON8253 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6039753 ±21 frame:8000
seq: 1152
follows: 0x00000010:1300 0x00000011:1245 0x00000100:861 0x00000200:1943 0x00000300:4438
said: 1 | **ENTWIN** t_ms:6029053 stream:0x732acba3 wall:0 window_ms:599996 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689,c2e94427adcf
```

---

@LAT103LON8254 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7239763 ±21 frame:8000
seq: 1173
follows: 0x00000010:1322 0x00000011:1266 0x00000100:883 0x00000200:1963 0x00000300:4478
said: 1 | **ENTWIN** t_ms:7229056 stream:0x732acba3 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,64677217947d,0283cce0e689,c2e94427adcf
said: 12 | **COVERED** windows:1 entities:10 window_ms:600002 first_t_ms:6629054 last_t_ms:6629054 covered_by:@LAT103LON8253
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-85 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95 windows:1
```

---

@LAT103LON8255 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7839763 ±21 frame:8000
seq: 1184
follows: 0x00000010:1332 0x00000011:1276 0x00000100:895 0x00000200:1974 0x00000300:4500
said: 1 | **ENTWIN** t_ms:7829052 stream:0x732acba3 wall:0 window_ms:599997 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
said: 7 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,5203cfd1b904
```

---

@LAT106LON113 | created:0 | updated:0

**BAR** frame:8000 bar:13 own:10 held:40 terms:9 digest:0x45949f72 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1323 hi:1332 sum:13275
**HOLDS** agent:0x00000011 n:10 lo:1266 hi:1275 sum:12705
**HOLDS** agent:0x00000012 n:10 lo:1172 hi:1182 sum:11774
**HOLDS** agent:0x00000200 n:10 lo:1964 hi:1973 sum:19685
**HOLDS** agent:0x00000300 n:10 lo:4479 hi:4499 sum:44897
**DELIVER** up_s:8089 heap:120644 fetched:545 unanswered:369 broken:73 resumed:1704 empty:256 served:2084 wants:2130 early:70 wantq_drop:0 superseded:0

---

@LAT103LON8256 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8439769 ±21 frame:8000
seq: 1195
follows: 0x00000010:1342 0x00000011:1286 0x00000100:906 0x00000200:1984 0x00000300:4521
said: 1 | **ENTWIN** t_ms:8429055 stream:0x732acba3 wall:0 window_ms:600002 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689
```

---

@LAT106LON114 | created:0 | updated:0

**BAR** frame:8000 bar:14 own:10 held:40 terms:9 digest:0x4b93e0ea settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1333 hi:1342 sum:13375
**HOLDS** agent:0x00000011 n:10 lo:1276 hi:1285 sum:12805
**HOLDS** agent:0x00000012 n:10 lo:1183 hi:1193 sum:11884
**HOLDS** agent:0x00000200 n:10 lo:1975 hi:1984 sum:19795
**HOLDS** agent:0x00000300 n:10 lo:4501 hi:4520 sum:45109
**DELIVER** up_s:8688 heap:120328 fetched:585 unanswered:399 broken:80 resumed:1838 empty:272 served:2270 wants:2321 early:70 wantq_drop:0 superseded:0

---

@LAT103LON8257 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9039771 ±21 frame:8000
seq: 1206
follows: 0x00000010:1353 0x00000011:1296 0x00000100:917 0x00000200:1994 0x00000300:4542
said: 1 | **ENTWIN** t_ms:9029055 stream:0x732acba3 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,5ce28c488e0c
```

---

@LAT106LON115 | created:0 | updated:0

**BAR** frame:8000 bar:15 own:10 held:40 terms:9 digest:0x033334fc settled_ms:300011
**HOLDS** agent:0x00000010 n:10 lo:1343 hi:1353 sum:13484
**HOLDS** agent:0x00000011 n:10 lo:1286 hi:1295 sum:12905
**HOLDS** agent:0x00000012 n:10 lo:1194 hi:1204 sum:11994
**HOLDS** agent:0x00000200 n:10 lo:1985 hi:1994 sum:19895
**HOLDS** agent:0x00000300 n:10 lo:4522 hi:4541 sum:45319
**DELIVER** up_s:9286 heap:119840 fetched:621 unanswered:430 broken:91 resumed:1976 empty:289 served:2408 wants:2463 early:70 wantq_drop:0 superseded:0

---

@LAT103LON8258 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9639775 ±21 frame:8000
seq: 1217
follows: 0x00000010:1364 0x00000011:1307 0x00000100:928 0x00000200:2004 0x00000300:4563
said: 1 | **ENTWIN** t_ms:9629103 stream:0x732acba3 wall:0 window_ms:599998 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,0283cce0e689,64677217947d
```

---

@LAT106LON116 | created:0 | updated:0

**BAR** frame:8000 bar:16 own:10 held:40 terms:9 digest:0x8fff28fa settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1354 hi:1364 sum:13594
**HOLDS** agent:0x00000011 n:10 lo:1296 hi:1306 sum:13014
**HOLDS** agent:0x00000012 n:10 lo:1205 hi:1215 sum:12104
**HOLDS** agent:0x00000200 n:10 lo:1995 hi:2004 sum:19995
**HOLDS** agent:0x00000300 n:10 lo:4543 hi:4562 sum:45528
**DELIVER** up_s:9887 heap:120080 fetched:664 unanswered:471 broken:97 resumed:2099 empty:304 served:2574 wants:2629 early:70 wantq_drop:0 superseded:0

---

@LAT103LON8259 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10239782 ±21 frame:8000
seq: 1228
follows: 0x00000010:1374 0x00000011:1317 0x00000100:938 0x00000200:2014 0x00000300:4583
said: 1 | **ENTWIN** t_ms:10229107 stream:0x732acba3 wall:0 window_ms:600004 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT106LON117 | created:0 | updated:0

**BAR** frame:8000 bar:17 own:10 held:40 terms:9 digest:0x5345e039 settled_ms:300007
**HOLDS** agent:0x00000010 n:10 lo:1365 hi:1374 sum:13695
**HOLDS** agent:0x00000011 n:10 lo:1307 hi:1316 sum:13115
**HOLDS** agent:0x00000012 n:10 lo:1216 hi:1226 sum:12214
**HOLDS** agent:0x00000200 n:10 lo:2005 hi:2014 sum:20095
**HOLDS** agent:0x00000300 n:10 lo:4564 hi:4582 sum:45730
**DELIVER** up_s:10488 heap:119548 fetched:705 unanswered:499 broken:99 resumed:2229 empty:324 served:2717 wants:2775 early:70 wantq_drop:0 superseded:0

---

@LAT103LON8260 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10839806 ±21 frame:8000
seq: 1239
follows: 0x00000010:1384 0x00000011:1327 0x00000100:949 0x00000200:2024 0x00000300:4603
said: 1 | **ENTWIN** t_ms:10829129 stream:0x732acba3 wall:0 window_ms:600021 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c,0283cce0e689
```

---

@LAT106LON118 | created:0 | updated:0

**BAR** frame:8000 bar:18 own:10 held:40 terms:9 digest:0xabc37525 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1375 hi:1384 sum:13795
**HOLDS** agent:0x00000011 n:10 lo:1317 hi:1326 sum:13215
**HOLDS** agent:0x00000012 n:10 lo:1227 hi:1237 sum:12324
**HOLDS** agent:0x00000200 n:10 lo:2015 hi:2024 sum:20195
**HOLDS** agent:0x00000300 n:10 lo:4584 hi:4602 sum:45930
**DELIVER** up_s:11086 heap:119308 fetched:745 unanswered:515 broken:109 resumed:2354 empty:344 served:2839 wants:2901 early:70 wantq_drop:0 superseded:0

---

@LAT103LON8261 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11439798 ±23 frame:8000
seq: 1250
follows: 0x00000010:1395 0x00000011:1338 0x00000100:960 0x00000200:2035 0x00000300:4624
said: 1 | **ENTWIN** t_ms:11429126 stream:0x732acba3 wall:0 window_ms:599997 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,0283cce0e689,c2e94427adcf,5ce28c488e0c
```

---

@LAT106LON119 | created:0 | updated:0

**BAR** frame:8000 bar:19 own:10 held:38 terms:9 digest:0xb5144cb4 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1385 hi:1395 sum:13904
**HOLDS** agent:0x00000011 n:10 lo:1327 hi:1337 sum:13324
**HOLDS** agent:0x00000012 n:10 lo:1238 hi:1248 sum:12434
**HOLDS** agent:0x00000200 n:10 lo:2025 hi:2034 sum:20295
**HOLDS** agent:0x00000300 n:8 lo:4604 hi:4623 sum:36901
**DELIVER** up_s:11688 heap:120108 fetched:779 unanswered:554 broken:117 resumed:2472 empty:356 served:2985 wants:3049 early:70 wantq_drop:0 superseded:0

---

@LAT103LON8262 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12039783 ±21 frame:8000
seq: 1261
follows: 0x00000010:1405 0x00000011:1349 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **ENTWIN** t_ms:12029126 stream:0x732acba3 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,c2e94427adcf,0283cce0e689
```

---

@LAT103LON8263 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:21000
seq: 1263
follows: 0x00000010:1405 0x00000011:1350 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **ENTWIN** t_ms:35353 stream:0xbdfeefa7 wall:0 window_ms:60000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8264 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:15000
seq: 1264
follows: 0x00000010:1405 0x00000011:1350 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **ENTWIN** t_ms:41294 stream:0x5a2f5b97 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8265 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:8000
seq: 1265
follows: 0x00000010:1405 0x00000011:1350 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **ENTWIN** t_ms:49181 stream:0xc9e0e898 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8266 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 881249 ±21 frame:7500
seq: 1281
follows: 0x00000010:1421 0x00000011:1366 0x00000100:1014 0x00000200:2058 0x00000300:4669
said: 1 | **ENTWIN** t_ms:1202999 stream:0xc9e0e898 wall:0 window_ms:599997 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,5ce28c488e0c
said: 12 | **COVERED** windows:1 entities:8 window_ms:553820 first_t_ms:603001 last_t_ms:603001 covered_by:@LAT103LON8265
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-90 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
```

---

@LAT106LON120 | created:0 | updated:0

**BAR** frame:7500 bar:1 own:10 held:26 terms:9 digest:0x1f8bddb7 settled_ms:300000
**HOLDS** agent:0x00000010 n:7 lo:1411 hi:1417 sum:9898
**HOLDS** agent:0x00000011 n:6 lo:1356 hi:1361 sum:8151
**HOLDS** agent:0x00000012 n:10 lo:1267 hi:1276 sum:12715
**HOLDS** agent:0x00000200 n:7 lo:2048 hi:2054 sum:14357
**HOLDS** agent:0x00000300 n:6 lo:4650 hi:4660 sum:27930
**DELIVER** up_s:1245 heap:120460 fetched:59 unanswered:61 broken:5 resumed:157 empty:33 served:251 wants:253 early:48 wantq_drop:0 superseded:3
**GRAMMAR** hash:0xaf98ac36 same:0 split:5
**SPLIT** agent:0x00000010 grammar:0xfe169cb3
**SPLIT** agent:0x00000011 grammar:0xfe169cb3
**SPLIT** agent:0x00000100 grammar:0xfe169cb3
**SPLIT** agent:0x00000200 grammar:0xfe169cb3
**SPLIT** agent:0x00000300 grammar:0xfe169cb3

---

@LAT103LON8267 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1481257 ±21 frame:7500
seq: 1292
follows: 0x00000010:1432 0x00000011:1377 0x00000100:1025 0x00000200:2069 0x00000300:4690
said: 1 | **ENTWIN** t_ms:1803001 stream:0xc9e0e898 wall:0 window_ms:600003 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689,5ce28c488e0c
```

---

@LAT106LON121 | created:0 | updated:0

**BAR** frame:7500 bar:2 own:10 held:40 terms:9 digest:0x4d262fda settled_ms:300029
**HOLDS** agent:0x00000010 n:10 lo:1418 hi:1427 sum:14225
**HOLDS** agent:0x00000011 n:10 lo:1362 hi:1371 sum:13665
**HOLDS** agent:0x00000012 n:10 lo:1277 hi:1287 sum:12821
**HOLDS** agent:0x00000200 n:10 lo:2055 hi:2064 sum:20595
**HOLDS** agent:0x00000300 n:10 lo:4662 hi:4680 sum:46710
**DELIVER** up_s:1845 heap:120184 fetched:99 unanswered:83 broken:11 resumed:276 empty:55 served:381 wants:387 early:48 wantq_drop:0 superseded:3
**GRAMMAR** hash:0xaf98ac36 same:0 split:5
**SPLIT** agent:0x00000010 grammar:0xfe169cb3
**SPLIT** agent:0x00000011 grammar:0xfe169cb3
**SPLIT** agent:0x00000100 grammar:0xfe169cb3
**SPLIT** agent:0x00000200 grammar:0xfe169cb3
**SPLIT** agent:0x00000300 grammar:0xfe169cb3

---

@LAT103LON8268 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1757072 ±21 frame:7500
seq: 1298
follows: 0x00000010:1437 0x00000011:1381 0x00000100:1029 0x00000200:2074 0x00000300:4700
said: 1 | **ENTWIN** t_ms:2076748 stream:0xc9e0e898 wall:0 window_ms:68936 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON1242 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1815029 ±21 frame:7500
seq: 1299
follows: 0x00000010:1439 0x00000011:1382 0x00000100:1030 0x00000200:2075 0x00000300:4702
said: 1 | **LINKWIN** t_ms:2136748 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-35 rssi_med:-31 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000200 proto:espnow n:85 rssi_min:-36 rssi_med:-30 rssi_max:-30
said: 6 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 7 | **LINK** peer:0x00000300 proto:espnow n:132 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000011 proto:ble n:52 rssi_min:-80 rssi_med:-53 rssi_max:-48
said: 9 | **LINK** peer:0x00000011 proto:espnow n:128 rssi_min:-43 rssi_med:-41 rssi_max:-40
```

---

@LAT103LON1243 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1875282 ±21 frame:7500
seq: 1300
follows: 0x00000010:1440 0x00000011:1383 0x00000100:1032 0x00000200:2076 0x00000300:4705
said: 1 | **LINKWIN** t_ms:2196998 stream:0xc9e0e898 wall:0 window_ms:60251
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-50 rssi_max:-43
said: 3 | **LINK** peer:0x00000100 proto:espnow n:73 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:espnow n:120 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 5 | **LINK** peer:0x00000200 proto:espnow n:147 rssi_min:-36 rssi_med:-30 rssi_max:-30
said: 6 | **LINK** peer:0x00000010 proto:espnow n:124 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 7 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 8 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000300 proto:espnow n:164 rssi_min:-46 rssi_med:-45 rssi_max:-41
```

---

@LAT103LON1244 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2077355 ±21 frame:7500
seq: 1301
follows: 0x00000010:1443 0x00000011:1387 0x00000100:1036 0x00000200:2079 0x00000300:4712
said: 1 | **LINKWIN** t_ms:2399097 stream:0xc9e0e898 wall:0 window_ms:62041
said: 2 | **LINK** peer:0x00000300 proto:espnow n:129 rssi_min:-48 rssi_med:-44 rssi_max:-40
said: 3 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-81 rssi_med:-41 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:espnow n:73 rssi_min:-35 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 6 | **LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-33 rssi_med:-31 rssi_max:-29
said: 7 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-82 rssi_med:-50 rssi_max:-41
said: 8 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-45 rssi_max:-43
said: 9 | **LINK** peer:0x00000011 proto:ble n:48 rssi_min:-81 rssi_med:-55 rssi_max:-49
```

---

@LAT103LON8269 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2077406 ±21 frame:7500
seq: 1302
follows: 0x00000010:1443 0x00000011:1387 0x00000100:1036 0x00000200:2079 0x00000300:4712
said: 1 | **ENTWIN** t_ms:2399097 stream:0xc9e0e898 wall:0 window_ms:62092 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT106LON122 | created:0 | updated:0

**BAR** frame:7500 bar:3 own:9 held:40 terms:9 digest:0xcd88d703 settled_ms:300033
**HOLDS** agent:0x00000010 n:10 lo:1429 hi:1438 sum:14335
**HOLDS** agent:0x00000011 n:10 lo:1373 hi:1382 sum:13775
**HOLDS** agent:0x00000012 n:9 lo:1288 hi:1297 sum:11633
**HOLDS** agent:0x00000200 n:10 lo:2065 hi:2075 sum:20704
**HOLDS** agent:0x00000300 n:10 lo:4682 hi:4701 sum:46919
**DELIVER** up_s:99 heap:120676 fetched:5 unanswered:3 broken:1 resumed:25 empty:2 served:17 wants:18 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON1245 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2149356 ±21 frame:7500
seq: 1303
follows: 0x00000010:1444 0x00000011:1388 0x00000100:1037 0x00000200:2080 0x00000300:4714
said: 1 | **LINKWIN** t_ms:2471098 stream:0xc9e0e898 wall:0 window_ms:72001
said: 2 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000100 proto:espnow n:77 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 4 | **LINK** peer:0x00000010 proto:espnow n:81 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000011 proto:ble n:80 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 6 | **LINK** peer:0x00000200 proto:espnow n:132 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000200 proto:ble n:77 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000300 proto:espnow n:244 rssi_min:-46 rssi_med:-45 rssi_max:-41
said: 9 | **LINK** peer:0x00000300 proto:ble n:73 rssi_min:-82 rssi_med:-53 rssi_max:-52
```

---

@LAT103LON1246 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2211357 ±21 frame:7500
seq: 1304
follows: 0x00000010:1445 0x00000011:1389 0x00000100:1038 0x00000200:2081 0x00000300:4716
said: 1 | **LINKWIN** t_ms:2533098 stream:0xc9e0e898 wall:0 window_ms:62000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000200 proto:espnow n:164 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000300 proto:espnow n:136 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 8 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-50 rssi_max:-43
```

---

@LAT103LON1247 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2271356 ±21 frame:7500
seq: 1305
follows: 0x00000010:1446 0x00000011:1390 0x00000100:1039 0x00000200:2082 0x00000300:4718
said: 1 | **LINKWIN** t_ms:2593098 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000100 proto:espnow n:73 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 4 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 5 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-83 rssi_med:-50 rssi_max:-43
said: 6 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-53 rssi_max:-49
said: 7 | **LINK** peer:0x00000300 proto:espnow n:198 rssi_min:-46 rssi_med:-45 rssi_max:-41
said: 8 | **LINK** peer:0x00000011 proto:espnow n:108 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 9 | **LINK** peer:0x00000200 proto:espnow n:125 rssi_min:-32 rssi_med:-31 rssi_max:-30
```

---

@LAT103LON1248 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2331357 ±21 frame:7500
seq: 1306
follows: 0x00000010:1447 0x00000011:1391 0x00000100:1040 0x00000200:2083 0x00000300:4720
said: 1 | **LINKWIN** t_ms:2653099 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 4 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 5 | **LINK** peer:0x00000011 proto:espnow n:135 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 6 | **LINK** peer:0x00000300 proto:espnow n:190 rssi_min:-46 rssi_med:-45 rssi_max:-41
said: 7 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-32 rssi_med:-31 rssi_max:-28
said: 9 | **LINK** peer:0x00000200 proto:espnow n:104 rssi_min:-32 rssi_med:-31 rssi_max:-30
```

---

@LAT103LON1249 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2391375 ±21 frame:7500
seq: 1307
follows: 0x00000010:1448 0x00000011:1392 0x00000100:1041 0x00000200:2084 0x00000300:4722
said: 1 | **LINKWIN** t_ms:2713115 stream:0xc9e0e898 wall:0 window_ms:60017
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-82 rssi_med:-53 rssi_max:-52
said: 4 | **LINK** peer:0x00000011 proto:espnow n:101 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 5 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 6 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-50 rssi_max:-43
said: 8 | **LINK** peer:0x00000200 proto:espnow n:140 rssi_min:-36 rssi_med:-31 rssi_max:-29
said: 9 | **LINK** peer:0x00000010 proto:espnow n:115 rssi_min:-36 rssi_med:-32 rssi_max:-31
```

---

@LAT103LON1250 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2451386 ±21 frame:7500
seq: 1308
follows: 0x00000010:1449 0x00000011:1394 0x00000100:1043 0x00000200:2085 0x00000300:4724
said: 1 | **LINKWIN** t_ms:2773127 stream:0xc9e0e898 wall:0 window_ms:60011
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-50 rssi_max:-42
said: 3 | **LINK** peer:0x00000011 proto:espnow n:156 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 4 | **LINK** peer:0x00000300 proto:espnow n:145 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 6 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000010 proto:espnow n:79 rssi_min:-35 rssi_med:-32 rssi_max:-31
said: 8 | **LINK** peer:0x00000200 proto:espnow n:131 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-45 rssi_max:-44
```

---

@LAT103LON1251 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2511421 ±21 frame:7500
seq: 1309
follows: 0x00000010:1450 0x00000011:1395 0x00000100:1045 0x00000200:2086 0x00000300:4726
said: 1 | **LINKWIN** t_ms:2833161 stream:0xc9e0e898 wall:0 window_ms:60034
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:137 rssi_min:-33 rssi_med:-31 rssi_max:-30
said: 4 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 6 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-79 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:espnow n:94 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 8 | **LINK** peer:0x00000011 proto:espnow n:82 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 9 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-50 rssi_max:-43
```

---

@LAT103LON1252 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2571439 ±21 frame:7500
seq: 1310
follows: 0x00000010:1451 0x00000011:1396 0x00000100:1046 0x00000200:2087 0x00000300:4728
said: 1 | **LINKWIN** t_ms:2893180 stream:0xc9e0e898 wall:0 window_ms:60019
said: 2 | **LINK** peer:0x00000010 proto:espnow n:124 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 3 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-35 rssi_med:-30 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 5 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-83 rssi_med:-54 rssi_max:-52
said: 6 | **LINK** peer:0x00000011 proto:espnow n:101 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000300 proto:espnow n:278 rssi_min:-46 rssi_med:-45 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-80 rssi_med:-45 rssi_max:-44
```

---

@LAT103LON1253 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2631440 ±21 frame:7500
seq: 1311
follows: 0x00000010:1452 0x00000011:1397 0x00000100:1047 0x00000200:2088 0x00000300:4730
said: 1 | **LINKWIN** t_ms:2953180 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 4 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 5 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000300 proto:espnow n:142 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:espnow n:108 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 8 | **LINK** peer:0x00000200 proto:espnow n:89 rssi_min:-32 rssi_med:-31 rssi_max:-28
said: 9 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-50 rssi_max:-43
```

---

@LAT103LON1254 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2691441 ±21 frame:7500
seq: 1312
follows: 0x00000010:1453 0x00000011:1398 0x00000100:1048 0x00000200:2089 0x00000300:4732
said: 1 | **LINKWIN** t_ms:3013180 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-50 rssi_max:-43
said: 4 | **LINK** peer:0x00000010 proto:espnow n:115 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000011 proto:espnow n:95 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 6 | **LINK** peer:0x00000200 proto:espnow n:118 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 8 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 9 | **LINK** peer:0x00000300 proto:espnow n:195 rssi_min:-46 rssi_med:-45 rssi_max:-40
```

---

@LAT106LON123 | created:0 | updated:0

**BAR** frame:7500 bar:4 own:8 held:40 terms:9 digest:0xc9a9ac56 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1440 hi:1449 sum:14445
**HOLDS** agent:0x00000011 n:10 lo:1383 hi:1392 sum:13875
**HOLDS** agent:0x00000012 n:8 lo:1299 hi:1307 sum:10425
**HOLDS** agent:0x00000200 n:10 lo:2076 hi:2085 sum:20805
**HOLDS** agent:0x00000300 n:10 lo:4703 hi:4723 sum:47137
**DELIVER** up_s:697 heap:120704 fetched:50 unanswered:21 broken:7 resumed:171 empty:11 served:164 wants:169 early:0 wantq_drop:0 superseded:4
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON1255 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2751441 ±21 frame:7500
seq: 1313
follows: 0x00000010:1454 0x00000011:1399 0x00000100:1049 0x00000200:2090 0x00000300:4734
said: 1 | **LINKWIN** t_ms:3073180 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 5 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 6 | **LINK** peer:0x00000300 proto:espnow n:79 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 7 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-83 rssi_med:-51 rssi_max:-43
said: 8 | **LINK** peer:0x00000011 proto:espnow n:73 rssi_min:-43 rssi_med:-41 rssi_max:-39
said: 9 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-32 rssi_med:-31 rssi_max:-30
```

---

@LAT103LON1256 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2811441 ±21 frame:7500
seq: 1314
follows: 0x00000010:1455 0x00000011:1400 0x00000100:1050 0x00000200:2091 0x00000300:4736
said: 1 | **LINKWIN** t_ms:3133180 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:espnow n:121 rssi_min:-46 rssi_med:-41 rssi_max:-40
said: 4 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000300 proto:espnow n:181 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000200 proto:espnow n:96 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000010 proto:espnow n:85 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 8 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-80 rssi_med:-50 rssi_max:-43
said: 9 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-54 rssi_max:-52
```

---

@LAT103LON1257 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2871448 ±21 frame:7500
seq: 1315
follows: 0x00000010:1456 0x00000011:1401 0x00000100:1051 0x00000200:2092 0x00000300:4738
said: 1 | **LINKWIN** t_ms:3193188 stream:0xc9e0e898 wall:0 window_ms:60008
said: 2 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-32 rssi_med:-31 rssi_max:-28
said: 4 | **LINK** peer:0x00000010 proto:espnow n:119 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 6 | **LINK** peer:0x00000300 proto:espnow n:175 rssi_min:-46 rssi_med:-45 rssi_max:-41
said: 7 | **LINK** peer:0x00000200 proto:espnow n:115 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000011 proto:espnow n:98 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 9 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-50 rssi_max:-43
```

---

@LAT103LON1258 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2931455 ±21 frame:7500
seq: 1316
follows: 0x00000010:1457 0x00000011:1402 0x00000100:1052 0x00000200:2093 0x00000300:4740
said: 1 | **LINKWIN** t_ms:3253192 stream:0xc9e0e898 wall:0 window_ms:60004
said: 2 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 3 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-79 rssi_med:-50 rssi_max:-43
said: 4 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 5 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000200 proto:espnow n:104 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000300 proto:espnow n:229 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 9 | **LINK** peer:0x00000010 proto:espnow n:96 rssi_min:-37 rssi_med:-32 rssi_max:-31
```

---

@LAT103LON1259 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2991455 ±21 frame:7500
seq: 1317
follows: 0x00000010:1458 0x00000011:1403 0x00000100:1053 0x00000200:2094 0x00000300:4742
said: 1 | **LINKWIN** t_ms:3313192 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-48
said: 4 | **LINK** peer:0x00000011 proto:espnow n:118 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 6 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 7 | **LINK** peer:0x00000010 proto:espnow n:120 rssi_min:-38 rssi_med:-32 rssi_max:-31
said: 8 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-45 rssi_max:-44
```

---

@LAT103LON1260 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3051455 ±21 frame:7500
seq: 1318
follows: 0x00000010:1459 0x00000011:1404 0x00000100:1054 0x00000200:2095 0x00000300:4744
said: 1 | **LINKWIN** t_ms:3373192 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-50 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:espnow n:172 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 5 | **LINK** peer:0x00000011 proto:espnow n:157 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 6 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-35 rssi_med:-30 rssi_max:-30
said: 7 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-53 rssi_max:-51
said: 8 | **LINK** peer:0x00000200 proto:espnow n:154 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-49
```

---

@LAT103LON1261 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3111483 ±21 frame:7500
seq: 1319
follows: 0x00000010:1460 0x00000011:1405 0x00000100:1056 0x00000200:2096 0x00000300:4746
said: 1 | **LINKWIN** t_ms:3433219 stream:0xc9e0e898 wall:0 window_ms:60027
said: 2 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 4 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:espnow n:121 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 6 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 8 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-82 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000300 proto:espnow n:117 rssi_min:-46 rssi_med:-45 rssi_max:-40
```

---

@LAT103LON1262 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3171505 ±21 frame:7500
seq: 1320
follows: 0x00000010:1461 0x00000011:1406 0x00000100:1057 0x00000200:2097 0x00000300:4748
said: 1 | **LINKWIN** t_ms:3493240 stream:0xc9e0e898 wall:0 window_ms:60021
said: 2 | **LINK** peer:0x00000300 proto:espnow n:221 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 4 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:espnow n:110 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 6 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 7 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000010 proto:espnow n:114 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 9 | **LINK** peer:0x00000200 proto:espnow n:68 rssi_min:-36 rssi_med:-31 rssi_max:-30
```

---

@LAT103LON1263 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3231505 ±21 frame:7500
seq: 1321
follows: 0x00000010:1462 0x00000011:1407 0x00000100:1058 0x00000200:2098 0x00000300:4750
said: 1 | **LINKWIN** t_ms:3553240 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:180 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 4 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 5 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:espnow n:150 rssi_min:-46 rssi_med:-45 rssi_max:-41
said: 7 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 9 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-36 rssi_med:-31 rssi_max:-27
```

---

@LAT103LON8270 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3242203 ±21 frame:7500
seq: 1322
follows: 0x00000010:1462 0x00000011:1407 0x00000100:1058 0x00000200:2098 0x00000300:4750
said: 1 | **ENTWIN** t_ms:3561939 stream:0xc9e0e898 wall:0 window_ms:600043 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c
said: 10 | **COVERED** windows:1 entities:7 window_ms:564747 first_t_ms:2961896 last_t_ms:2961896 covered_by:@LAT103LON8269
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-95 windows:1
```

---

@LAT103LON1264 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3291505 ±21 frame:7500
seq: 1323
follows: 0x00000010:1463 0x00000011:1408 0x00000100:1059 0x00000200:2099 0x00000300:4752
said: 1 | **LINKWIN** t_ms:3613239 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:espnow n:125 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000010 proto:espnow n:83 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 6 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 8 | **LINK** peer:0x00000011 proto:espnow n:96 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 9 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-35 rssi_med:-31 rssi_max:-30
```

---

@LAT106LON124 | created:0 | updated:0

**BAR** frame:7500 bar:5 own:10 held:40 terms:9 digest:0xdd4d4ce8 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1450 hi:1459 sum:14545
**HOLDS** agent:0x00000011 n:10 lo:1394 hi:1403 sum:13985
**HOLDS** agent:0x00000012 n:10 lo:1308 hi:1317 sum:13125
**HOLDS** agent:0x00000200 n:10 lo:2086 hi:2095 sum:20905
**HOLDS** agent:0x00000300 n:10 lo:4725 hi:4743 sum:47340
**DELIVER** up_s:1299 heap:120204 fetched:93 unanswered:52 broken:9 resumed:293 empty:22 served:297 wants:310 early:0 wantq_drop:0 superseded:4
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON1265 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3351529 ±21 frame:7500
seq: 1324
follows: 0x00000010:1464 0x00000011:1409 0x00000100:1060 0x00000200:2100 0x00000300:4754
said: 1 | **LINKWIN** t_ms:3673263 stream:0xc9e0e898 wall:0 window_ms:60023
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-51 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 4 | **LINK** peer:0x00000200 proto:espnow n:106 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-82 rssi_med:-53 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:espnow n:83 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 7 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-46 rssi_med:-41 rssi_max:-38
said: 8 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-45 rssi_max:-44
```

---

@LAT103LON1266 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3411550 ±21 frame:7500
seq: 1325
follows: 0x00000010:1465 0x00000011:1410 0x00000100:1061 0x00000200:2101 0x00000300:4756
said: 1 | **LINKWIN** t_ms:3733284 stream:0xc9e0e898 wall:0 window_ms:60021
said: 2 | **LINK** peer:0x00000300 proto:espnow n:172 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-79 rssi_med:-53 rssi_max:-49
said: 4 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 5 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 6 | **LINK** peer:0x00000200 proto:espnow n:72 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-45 rssi_max:-44
said: 9 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-37 rssi_med:-32 rssi_max:-31
```

---

@LAT103LON1267 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1268 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1269 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1270 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1271 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON4936 | created:0 | updated:0

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

@LAT105LON4937 | created:0 | updated:0

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

@LAT105LON4938 | created:0 | updated:0

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

@LAT105LON4939 | created:0 | updated:0

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

@LAT105LON4940 | created:0 | updated:0

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

@LAT105LON4941 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT103LON1272 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON4942 | created:0 | updated:0

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

@LAT105LON4943 | created:0 | updated:0

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

@LAT105LON4944 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT105LON4945 | created:0 | updated:0

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

@LAT105LON4946 | created:0 | updated:0

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

@LAT103LON1273 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON4947 | created:0 | updated:0

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

@LAT103LON1274 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON4948 | created:0 | updated:0

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

@LAT105LON4949 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT105LON4950 | created:0 | updated:0

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
@LAT106LON125 | created:0 | updated:0

**BAR** frame:7500 bar:6 own:10 held:40 terms:8 digest:0xe5fee0c4 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1460 hi:1469 sum:14645
**HOLDS** agent:0x00000011 n:10 lo:1404 hi:1413 sum:14085
**HOLDS** agent:0x00000012 n:10 lo:1318 hi:1328 sum:13231
**HOLDS** agent:0x00000200 n:10 lo:2096 hi:2105 sum:21005
**HOLDS** agent:0x00000300 n:10 lo:4745 hi:4763 sum:47540
**DELIVER** up_s:1899 heap:120712 fetched:134 unanswered:76 broken:15 resumed:417 empty:35 served:459 wants:472 early:0 wantq_drop:1 superseded:12
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT105LON4951 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT103LON1275 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON4952 | created:0 | updated:0

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

@LAT105LON4953 | created:0 | updated:0

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

@LAT105LON4954 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT105LON4955 | created:0 | updated:0

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

@LAT105LON4956 | created:0 | updated:0

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

---

@LAT105LON4957 | created:0 | updated:0

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

@LAT105LON4958 | created:0 | updated:0

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

@LAT105LON4959 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT105LON4960 | created:0 | updated:0

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

@LAT103LON1276 | created:0 | updated:0

**link window**

```ttdb-episode
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

---

@LAT105LON4961 | created:0 | updated:0

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

@LAT105LON4962 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
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

@LAT105LON4963 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4053012 ±21 frame:7500
seq: 1421
follows: 0x00000010:1476 0x00000012:1335 0x00000100:1073 0x00000200:2112 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4374731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-57 rssi_med:-53 rssi_max:-41
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-69 rssi_med:-58 rssi_max:-50
said: 4 | **LINK** peer:0x00000300 proto:espnow n:179 rssi_min:-61 rssi_med:-46 rssi_max:-41
said: 5 | **LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-59 rssi_med:-54 rssi_max:-50
said: 6 | **LINK** peer:0x00000200 proto:ble n:35 rssi_min:-81 rssi_med:-63 rssi_max:-60
said: 7 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-80 rssi_med:-59 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-47
said: 9 | **LINK** peer:0x00000010 proto:espnow n:118 rssi_min:-43 rssi_med:-35 rssi_max:-30
```

---

@LAT103LON1277 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4071612 ±21 frame:7500
seq: 1336
follows: 0x00000010:1476 0x00000011:1421 0x00000100:1074 0x00000200:2112 0x00000300:4781
said: 1 | **LINKWIN** t_ms:4393341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-37 rssi_med:-31 rssi_max:-29
said: 3 | **LINK** peer:0x00000300 proto:espnow n:190 rssi_min:-39 rssi_med:-33 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-60 rssi_med:-55 rssi_max:-49
said: 5 | **LINK** peer:0x00000200 proto:ble n:38 rssi_min:-55 rssi_med:-42 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-65 rssi_max:-53
said: 7 | **LINK** peer:0x00000010 proto:espnow n:104 rssi_min:-56 rssi_med:-48 rssi_max:-43
said: 8 | **LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 9 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-48 rssi_max:-46
```

---

@LAT105LON4964 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 4068458 ±0 frame:7500
seq: 4780
follows: 0x00000010:1476 0x00000011:1421 0x00000012:1335 0x00000100:1074 0x00000200:2112
said: 1 | **LINKWIN** t_ms:4390202 stream:0xc9e0e898 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-68 rssi_max:-61
said: 3 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-63 rssi_max:-51
said: 4 | **LINK** peer:0x00000012 proto:espnow n:103 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:33 rssi_min:-80 rssi_med:-58 rssi_max:-55
said: 6 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-56 rssi_med:-54 rssi_max:-46
said: 8 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 9 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-56 rssi_med:-51 rssi_max:-46
said: 10 | 0x00000200 ble met predicted:-57 observed:-58
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-42 observed:-41
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-48 observed:-51
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-49 observed:-54
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-63
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-68
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000012 ble unobserved predicted:-56 observed:-56
percept: 17 | 0x00000012 | link_stable | ble | ? | -
```

---

@LAT105LON4965 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
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

@LAT103LON1278 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4131611 ±21 frame:7500
seq: 1337
follows: 0x00000010:1477 0x00000011:1422 0x00000100:1075 0x00000200:2114 0x00000300:4783
said: 1 | **LINKWIN** t_ms:4453341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-60 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:152 rssi_min:-43 rssi_med:-33 rssi_max:-29
said: 4 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-35 rssi_med:-31 rssi_max:-29
said: 5 | **LINK** peer:0x00000011 proto:espnow n:75 rssi_min:-57 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-49 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:espnow n:75 rssi_min:-48 rssi_med:-44 rssi_max:-42
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-44 rssi_max:-40
said: 9 | **LINK** peer:0x00000011 proto:ble n:51 rssi_min:-80 rssi_med:-64 rssi_max:-55
```

---

@LAT105LON4966 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
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

@LAT105LON4967 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 4128458 ±0 frame:7500
seq: 4782
follows: 0x00000010:1477 0x00000011:1422 0x00000012:1336 0x00000100:1075 0x00000200:2114
said: 1 | **LINKWIN** t_ms:4450202 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-91 rssi_med:-59 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 4 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-67 rssi_med:-50 rssi_max:-48
said: 5 | **LINK** peer:0x00000011 proto:espnow n:80 rssi_min:-61 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000012 proto:espnow n:118 rssi_min:-42 rssi_med:-38 rssi_max:-35
said: 7 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-72 rssi_med:-63 rssi_max:-50
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-80 rssi_med:-68 rssi_max:-61
said: 10 | 0x00000011 ble met predicted:-68 observed:-68
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-63 observed:-63
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-39 observed:-38
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-58 observed:-59
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow violated predicted:-54 observed:-47
percept: 15 | 0x00000011 | link_stable | espnow | - | -
said: 16 | 0x00000200 espnow unobserved predicted:-41 observed:-41
percept: 16 | 0x00000200 | link_stable | espnow | ? | -
said: 17 | 0x00000010 espnow met predicted:-51 observed:-50
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT105LON4968 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4113013 ±21 frame:7500
seq: 1422
follows: 0x00000010:1477 0x00000012:1336 0x00000100:1074 0x00000200:2114 0x00000300:4781
said: 1 | **LINKWIN** t_ms:4434730 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-64 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-63 rssi_max:-61
said: 4 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-61 rssi_med:-59 rssi_max:-49
said: 5 | **LINK** peer:0x00000300 proto:espnow n:144 rssi_min:-57 rssi_med:-53 rssi_max:-45
said: 6 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-56 rssi_med:-54 rssi_max:-53
said: 7 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-83 rssi_med:-62 rssi_max:-53
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 9 | **LINK** peer:0x00000010 proto:espnow n:70 rssi_min:-40 rssi_med:-33 rssi_max:-32
```

---

@LAT105LON4969 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4095175 ±21 frame:7500
seq: 2113
follows: 0x00000010:1476 0x00000011:1420 0x00000012:1335 0x00000100:1073 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4417270 stream:0xc9e0e898 wall:0 window_ms:76125
said: 2 | **LINK** peer:0x00000012 proto:espnow n:57 rssi_min:-33 rssi_med:-32 rssi_max:-32
said: 3 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000011 proto:espnow n:64 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 5 | **LINK** peer:0x00000010 proto:espnow n:41 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 6 | **LINK** peer:0x00000300 proto:espnow n:105 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 7 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-81 rssi_med:-58 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-57 rssi_med:-49 rssi_max:-47
said: 9 | **LINK** peer:0x00000011 proto:ble n:50 rssi_min:-80 rssi_med:-65 rssi_max:-62
```

---

@LAT105LON4970 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4155241 ±21 frame:7500
seq: 2115
follows: 0x00000010:1477 0x00000011:1422 0x00000012:1337 0x00000100:1075 0x00000300:4783
said: 1 | **LINKWIN** t_ms:4481341 stream:0xc9e0e898 wall:0 window_ms:60070
said: 2 | **LINK** peer:0x00000010 proto:espnow n:70 rssi_min:-65 rssi_med:-51 rssi_max:-43
said: 3 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-52 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:espnow n:202 rssi_min:-53 rssi_med:-37 rssi_max:-26
said: 5 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-81 rssi_med:-64 rssi_max:-56
said: 6 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-84 rssi_med:-64 rssi_max:-54
said: 7 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-44 rssi_med:-37 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:espnow n:123 rssi_min:-47 rssi_med:-34 rssi_max:-31
said: 9 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-68 rssi_med:-48 rssi_max:-45
```

---

@LAT103LON1279 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4191612 ±21 frame:7500
seq: 1338
follows: 0x00000010:1478 0x00000011:1424 0x00000100:1076 0x00000200:2115 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4513341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-35 rssi_med:-29 rssi_max:-28
said: 3 | **LINK** peer:0x00000200 proto:espnow n:145 rssi_min:-56 rssi_med:-43 rssi_max:-26
said: 4 | **LINK** peer:0x00000300 proto:espnow n:149 rssi_min:-45 rssi_med:-34 rssi_max:-28
said: 5 | **LINK** peer:0x00000011 proto:espnow n:52 rssi_min:-58 rssi_med:-46 rssi_max:-39
said: 6 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-53 rssi_max:-40
said: 7 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-48 rssi_max:-44
said: 8 | **LINK** peer:0x00000010 proto:espnow n:57 rssi_min:-57 rssi_med:-45 rssi_max:-39
said: 9 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-80 rssi_med:-59 rssi_max:-45
```

---

@LAT105LON4971 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 4188561 ±0 frame:7500
seq: 4784
follows: 0x00000010:1478 0x00000011:1424 0x00000012:1337 0x00000100:1076 0x00000200:2115
said: 1 | **LINKWIN** t_ms:4510305 stream:0xc9e0e898 wall:0 window_ms:60103
said: 2 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-56 rssi_max:-46
said: 3 | **LINK** peer:0x00000011 proto:espnow n:67 rssi_min:-63 rssi_med:-49 rssi_max:-42
said: 4 | **LINK** peer:0x00000200 proto:espnow n:168 rssi_min:-63 rssi_med:-44 rssi_max:-31
said: 5 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-63 rssi_max:-55
said: 6 | **LINK** peer:0x00000012 proto:espnow n:130 rssi_min:-47 rssi_med:-38 rssi_max:-34
said: 7 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 8 | **LINK** peer:0x00000010 proto:espnow n:53 rssi_min:-60 rssi_med:-48 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-77 rssi_med:-57 rssi_max:-45
said: 10 | 0x00000200 ble met predicted:-59 observed:-57
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-50 observed:-48
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-47 observed:-49
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble unobserved predicted:-63 observed:-63
percept: 15 | 0x00000010 | link_stable | ble | ? | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-68 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT105LON4972 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4219604 ±21 frame:7500
seq: 2116
follows: 0x00000010:1478 0x00000011:1424 0x00000012:1338 0x00000100:1076 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4541346 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:91 rssi_min:-58 rssi_med:-42 rssi_max:-36
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-36 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000300 proto:espnow n:104 rssi_min:-60 rssi_med:-47 rssi_max:-33
said: 5 | **LINK** peer:0x00000010 proto:espnow n:72 rssi_min:-55 rssi_med:-45 rssi_max:-42
said: 6 | **LINK** peer:0x00000011 proto:espnow n:47 rssi_min:-50 rssi_med:-46 rssi_max:-41
said: 7 | **LINK** peer:0x00000010 proto:ble n:49 rssi_min:-80 rssi_med:-59 rssi_max:-51
said: 8 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-79 rssi_med:-53 rssi_max:-47
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-57 rssi_max:-50
```

---

@LAT103LON1280 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4251612 ±22 frame:7500
seq: 1339
follows: 0x00000010:1480 0x00000011:1424 0x00000100:1078 0x00000200:2116 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4573341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-58 rssi_max:-47
said: 3 | **LINK** peer:0x00000011 proto:espnow n:41 rssi_min:-62 rssi_med:-45 rssi_max:-41
said: 4 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000300 proto:espnow n:70 rssi_min:-61 rssi_med:-41 rssi_max:-20
said: 6 | **LINK** peer:0x00000300 proto:ble n:45 rssi_min:-85 rssi_med:-50 rssi_max:-33
said: 7 | **LINK** peer:0x00000200 proto:espnow n:111 rssi_min:-52 rssi_med:-42 rssi_max:-34
said: 8 | **LINK** peer:0x00000011 proto:ble n:41 rssi_min:-81 rssi_med:-65 rssi_max:-52
said: 9 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-50 rssi_max:-45
```

---

@LAT105LON4973 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4173167 ±21 frame:7500
seq: 1423
follows: 0x00000010:1478 0x00000012:1337 0x00000100:1075 0x00000200:2115 0x00000300:4783
said: 1 | **LINKWIN** t_ms:4494885 stream:0xc9e0e898 wall:0 window_ms:60154
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-55 rssi_max:-51
said: 3 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-67 rssi_med:-58 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:espnow n:204 rssi_min:-55 rssi_med:-45 rssi_max:-39
said: 5 | **LINK** peer:0x00000010 proto:espnow n:62 rssi_min:-44 rssi_med:-31 rssi_max:-27
said: 6 | **LINK** peer:0x00000012 proto:espnow n:110 rssi_min:-64 rssi_med:-46 rssi_max:-42
said: 7 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-84 rssi_med:-62 rssi_max:-50
said: 8 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-82 rssi_med:-50 rssi_max:-37
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-62 rssi_max:-57
```

---

@LAT105LON4974 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4253348 ±22 frame:7500
seq: 1425
follows: 0x00000010:1480 0x00000012:1339 0x00000100:1078 0x00000200:2116 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4582711 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:61 rssi_min:-60 rssi_med:-46 rssi_max:-34
said: 3 | **LINK** peer:0x00000010 proto:espnow n:93 rssi_min:-23 rssi_med:-21 rssi_max:-20
said: 4 | **LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-67 rssi_med:-29 rssi_max:-24
said: 5 | **LINK** peer:0x00000010 proto:ble n:47 rssi_min:-82 rssi_med:-37 rssi_max:-31
said: 6 | **LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-43 rssi_med:-41 rssi_max:-35
said: 7 | **LINK** peer:0x00000300 proto:ble n:21 rssi_min:-83 rssi_med:-46 rssi_max:-41
said: 8 | **LINK** peer:0x00000200 proto:espnow n:91 rssi_min:-67 rssi_med:-53 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:ble n:39 rssi_min:-82 rssi_med:-62 rssi_max:-51
```

---

@LAT105LON4975 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4272000 ±23 frame:7500
seq: 2117
follows: 0x00000010:1480 0x00000011:1426 0x00000012:1339 0x00000100:1078 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4601373 stream:0xc9e0e898 wall:0 window_ms:60033
said: 2 | **LINK** peer:0x00000012 proto:espnow n:87 rssi_min:-51 rssi_med:-42 rssi_max:-27
said: 3 | **LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-37 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-57 rssi_med:-44 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-70 rssi_med:-61 rssi_max:-56
said: 6 | **LINK** peer:0x00000010 proto:espnow n:132 rssi_min:-51 rssi_med:-47 rssi_max:-42
said: 7 | **LINK** peer:0x00000300 proto:ble n:36 rssi_min:-81 rssi_med:-54 rssi_max:-49
said: 8 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-54 rssi_max:-41
said: 9 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-79 rssi_med:-59 rssi_max:-51
```

---

@LAT103LON1281 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4311637 ±25 frame:7500
seq: 1340
follows: 0x00000010:1481 0x00000011:1426 0x00000100:1078 0x00000200:2117 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4633366 stream:0xc9e0e898 wall:0 window_ms:60025
said: 2 | **LINK** peer:0x00000011 proto:espnow n:137 rssi_min:-59 rssi_med:-49 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:espnow n:104 rssi_min:-58 rssi_med:-25 rssi_max:-24
said: 4 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-72 rssi_med:-59 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-55 rssi_med:-45 rssi_max:-35
said: 6 | **LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-35 rssi_med:-29 rssi_max:-16
said: 7 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-80 rssi_med:-44 rssi_max:-38
said: 8 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-80 rssi_med:-60 rssi_max:-50
said: 9 | **LINK** peer:0x00000300 proto:espnow n:80 rssi_min:-44 rssi_med:-25 rssi_max:-23
```

---

@LAT104LON141 | created:0 | updated:0

**carried through @LAT103LON1241**

```ttdb-carried
through: 1241
through: 8227
```

---

@LAT105LON4976 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
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

@LAT105LON4977 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
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

@LAT105LON4978 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4339632 ±21 frame:7500
seq: 2118
follows: 0x00000010:1481 0x00000011:1427 0x00000012:1340 0x00000100:1078 0x00000300:4789
said: 1 | **LINKWIN** t_ms:4661379 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:161 rssi_min:-46 rssi_med:-40 rssi_max:-36
said: 4 | **LINK** peer:0x00000012 proto:espnow n:152 rssi_min:-30 rssi_med:-28 rssi_max:-26
said: 5 | **LINK** peer:0x00000011 proto:espnow n:123 rssi_min:-63 rssi_med:-56 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-79 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-82 rssi_med:-63 rssi_max:-55
said: 8 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-56 rssi_max:-51
said: 9 | **LINK** peer:0x00000010 proto:espnow n:166 rssi_min:-63 rssi_med:-50 rssi_max:-45
```

---

@LAT103LON1282 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1283 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON4979 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
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

@LAT105LON4980 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 4326354 ±21 frame:7500
seq: 4786
follows: 0x00000010:1481 0x00000011:1426 0x00000012:1340 0x00000100:1078 0x00000200:2117
said: 1 | **LINKWIN** t_ms:4648060 stream:0xc9e0e898 wall:0 window_ms:67160
said: 2 | **LINK** peer:0x00000100 proto:espnow n:21 rssi_min:-44 rssi_med:-41 rssi_max:-36
said: 3 | **LINK** peer:0x00000012 proto:espnow n:119 rssi_min:-42 rssi_med:-32 rssi_max:-30
said: 4 | **LINK** peer:0x00000010 proto:espnow n:150 rssi_min:-44 rssi_med:-40 rssi_max:-36
said: 5 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-79 rssi_med:-53 rssi_max:-50
said: 6 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-39 rssi_med:-35 rssi_max:-29
said: 7 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-49 rssi_med:-44 rssi_max:-41
said: 8 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-81 rssi_med:-49 rssi_max:-46
said: 9 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-81 rssi_med:-60 rssi_max:-52
```

---

@LAT105LON4981 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4320983 ±21 frame:7500
seq: 1427
follows: 0x00000010:1481 0x00000012:1340 0x00000100:1078 0x00000200:2117 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4642712 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:25 rssi_min:-45 rssi_med:-42 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-69 rssi_med:-56 rssi_max:-46
said: 4 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-34 rssi_max:-31
said: 5 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-63 rssi_max:-55
said: 6 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-81 rssi_med:-58 rssi_max:-50
said: 7 | **LINK** peer:0x00000012 proto:espnow n:116 rssi_min:-57 rssi_med:-47 rssi_max:-42
said: 8 | **LINK** peer:0x00000010 proto:espnow n:131 rssi_min:-24 rssi_med:-21 rssi_max:-20
said: 9 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-45 rssi_max:-40
```

---

@LAT105LON4982 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
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

@LAT105LON4983 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
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

@LAT105LON4984 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4380985 ±21 frame:7500
seq: 1428
follows: 0x00000010:1482 0x00000012:1341 0x00000100:1081 0x00000200:2118 0x00000300:4789
said: 1 | **LINKWIN** t_ms:4702717 stream:0xc9e0e898 wall:0 window_ms:60005
said: 2 | **LINK** peer:0x00000010 proto:espnow n:200 rssi_min:-23 rssi_med:-21 rssi_max:-20
said: 3 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-55 rssi_med:-45 rssi_max:-41
said: 4 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-60 rssi_max:-50
said: 5 | **LINK** peer:0x00000200 proto:espnow n:134 rssi_min:-70 rssi_med:-61 rssi_max:-50
said: 6 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-34 rssi_max:-31
said: 7 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-44 rssi_max:-40
said: 8 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-66 rssi_max:-55
said: 9 | **LINK** peer:0x00000300 proto:espnow n:111 rssi_min:-31 rssi_med:-29 rssi_max:-25
```

---

@LAT105LON4985 | created:0 | updated:0

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

@LAT105LON4986 | created:0 | updated:0

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

@LAT105LON4987 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
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

@LAT105LON4988 | created:0 | updated:0

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

@LAT105LON4989 | created:0 | updated:0

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

@LAT105LON4990 | created:0 | updated:0

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

@LAT105LON4991 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
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

@LAT105LON4992 | created:0 | updated:0

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

@LAT105LON4993 | created:0 | updated:0

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

@LAT105LON4994 | created:0 | updated:0

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

@LAT105LON4995 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 2180526 ±0 frame:11000
seq: 4894
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1103 0x00000200:2120
said: 1 | **LINKWIN** t_ms:2166970 stream:0xed9951d6 wall:0 window_ms:60035
said: 2 | **LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-40 rssi_med:-37 rssi_max:-33
said: 3 | 0x00000100 espnow met predicted:-34 observed:-37
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```
@LAT106LON126 | created:0 | updated:0

**BAR** frame:45500 bar:8 own:0 held:0 terms:0 digest:0x00000000 settled_ms:826715
**DELIVER** up_s:14 heap:121012 fetched:0 unanswered:0 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0
@LAT106LON127 | created:0 | updated:0

**BAR** frame:45500 bar:7 own:0 held:0 terms:0 digest:0x00000000 settled_ms:1461525
**DELIVER** up_s:25 heap:121212 fetched:0 unanswered:1 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:1
**SPLIT** agent:0x00000300 grammar:0x42e3bb8a
@LAT106LON128 | created:0 | updated:0

**BAR** frame:45500 bar:9 own:0 held:0 terms:0 digest:0x00000000 settled_ms:321791
**DELIVER** up_s:52 heap:123376 fetched:0 unanswered:5 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:1
**SPLIT** agent:0x00000300 grammar:0x42e3bb8a

---

@LAT103LON1284 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5779850 ±21 frame:45500
seq: 1343
follows: 0x00000010:1533 0x00000011:1439 0x00000100:1482 0x00000200:2237 0x00000300:7801
said: 1 | **LINKWIN** t_ms:5900331 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:43 rssi_min:-80 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:16 rssi_min:-29 rssi_med:-25 rssi_max:-24
```

---

@LAT103LON8271 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5781896 ±21 frame:45500
seq: 1344
follows: 0x00000010:1533 0x00000011:1439 0x00000100:1482 0x00000200:2237 0x00000300:7801
said: 1 | **ENTWIN** t_ms:5900331 stream:0x7d6723f5 wall:0 window_ms:62046 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-23
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON1285 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5839846 ±21 frame:45500
seq: 1345
follows: 0x00000010:1533 0x00000011:1439 0x00000100:1482 0x00000200:2237 0x00000300:7803
said: 1 | **LINKWIN** t_ms:5960331 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-32 rssi_med:-27 rssi_max:-25
```

---

@LAT105LON4996 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 5826095 ±0 frame:45500
seq: 7802
follows: 0x00000010:1533 0x00000011:1439 0x00000012:1344 0x00000100:1482 0x00000200:2237
said: 1 | **LINKWIN** t_ms:5946555 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:34 rssi_min:-38 rssi_med:-34 rssi_max:-32
said: 3 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-57 rssi_med:-53 rssi_max:-47
said: 4 | 0x00000012 espnow met predicted:-34 observed:-34
percept: 4 | 0x00000300 | link_stable_espnow | 0x00000012 | + | -
said: 5 | 0x00000012 ble met predicted:-52 observed:-53
percept: 5 | 0x00000300 | link_stable_ble | 0x00000012 | + | -
```

---

@LAT103LON1286 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5899873 ±21 frame:45500
seq: 1346
follows: 0x00000010:1533 0x00000011:1439 0x00000100:1482 0x00000200:2237 0x00000300:7806
said: 1 | **LINKWIN** t_ms:6020331 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:71 rssi_min:-80 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-28 rssi_med:-27 rssi_max:-26
```

---

@LAT105LON4997 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 5886095 ±0 frame:45500
seq: 7805
follows: 0x00000010:1533 0x00000011:1439 0x00000012:1345 0x00000100:1482 0x00000200:2237
said: 1 | **LINKWIN** t_ms:6006555 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-38 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 4 | 0x00000012 espnow met predicted:-34 observed:-34
percept: 4 | 0x00000300 | link_stable_espnow | 0x00000012 | + | -
said: 5 | 0x00000012 ble met predicted:-53 observed:-53
percept: 5 | 0x00000300 | link_stable_ble | 0x00000012 | + | -
```

---

@LAT105LON4998 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 5946095 ±0 frame:45500
seq: 7807
follows: 0x00000010:1533 0x00000011:1439 0x00000012:1346 0x00000100:1482 0x00000200:2237
said: 1 | **LINKWIN** t_ms:6066555 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-49
said: 4 | 0x00000012 espnow met predicted:-34 observed:-34
percept: 4 | 0x00000300 | link_stable_espnow | 0x00000012 | + | -
said: 5 | 0x00000012 ble met predicted:-53 observed:-54
percept: 5 | 0x00000300 | link_stable_ble | 0x00000012 | + | -
```

---

@LAT103LON1287 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 5959873 ±21 frame:45500
seq: 1347
follows: 0x00000010:1533 0x00000011:1439 0x00000100:1482 0x00000200:2237 0x00000300:7808
said: 1 | **LINKWIN** t_ms:6080331 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:50 rssi_min:-80 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-28 rssi_med:-27 rssi_max:-26
```

---

@LAT103LON1288 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6019874 ±21 frame:45500
seq: 1348
follows: 0x00000010:1533 0x00000011:1439 0x00000100:1482 0x00000200:2237 0x00000300:7810
said: 1 | **LINKWIN** t_ms:6140331 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-28 rssi_med:-27 rssi_max:-26
```

---

@LAT105LON4999 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 6006096 ±0 frame:45500
seq: 7809
follows: 0x00000010:1533 0x00000011:1439 0x00000012:1347 0x00000100:1482 0x00000200:2237
said: 1 | **LINKWIN** t_ms:6126556 stream:0x7d6723f5 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-81 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000012 proto:espnow n:32 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 4 | 0x00000012 espnow met predicted:-34 observed:-34
percept: 4 | 0x00000300 | link_stable_espnow | 0x00000012 | + | -
said: 5 | 0x00000012 ble met predicted:-54 observed:-54
percept: 5 | 0x00000300 | link_stable_ble | 0x00000012 | + | -
```

---

@LAT105LON5000 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 6066096 ±0 frame:45500
seq: 7811
follows: 0x00000010:1533 0x00000011:1439 0x00000012:1348 0x00000100:1482 0x00000200:2237
said: 1 | **LINKWIN** t_ms:6186556 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:32 rssi_min:-39 rssi_med:-34 rssi_max:-32
said: 3 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-62 rssi_med:-54 rssi_max:-51
said: 4 | 0x00000012 ble met predicted:-54 observed:-54
percept: 4 | 0x00000300 | link_stable_ble | 0x00000012 | + | -
said: 5 | 0x00000012 espnow met predicted:-34 observed:-34
percept: 5 | 0x00000300 | link_stable_espnow | 0x00000012 | + | -
```

---

@LAT103LON1289 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6258416 ±21 frame:45500
seq: 1349
follows: 0x00000010:1533 0x00000011:1439 0x00000100:1482 0x00000200:2237 0x00000300:7818
said: 1 | **LINKWIN** t_ms:6378877 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:49 rssi_min:-82 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-30 rssi_med:-26 rssi_max:-25
```

---

@LAT103LON8272 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6258453 ±21 frame:45500
seq: 1350
follows: 0x00000010:1533 0x00000011:1439 0x00000100:1482 0x00000200:2237 0x00000300:7818
said: 1 | **ENTWIN** t_ms:6378877 stream:0x7d6723f5 wall:0 window_ms:60037 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-78
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT105LON5001 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 6126112 ±0 frame:45500
seq: 7813
follows: 0x00000010:1533 0x00000011:1439 0x00000012:1348 0x00000100:1482 0x00000200:2237
said: 1 | **LINKWIN** t_ms:6246572 stream:0x7d6723f5 wall:0 window_ms:60016
said: 2 | **LINK** peer:0x00000012 proto:espnow n:12 rssi_min:-36 rssi_med:-35 rssi_max:-32
said: 3 | **LINK** peer:0x00000012 proto:ble n:25 rssi_min:-58 rssi_med:-54 rssi_max:-49
said: 4 | 0x00000012 espnow met predicted:-34 observed:-35
percept: 4 | 0x00000300 | link_stable_espnow | 0x00000012 | + | -
said: 5 | 0x00000012 ble met predicted:-54 observed:-54
percept: 5 | 0x00000300 | link_stable_ble | 0x00000012 | + | -
```

---

@LAT105LON5002 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 6186112 ±0 frame:45500
seq: 7815
follows: 0x00000010:1533 0x00000011:1439 0x00000012:1348 0x00000100:1482 0x00000200:2237
said: 1 | **LINKWIN** t_ms:6306572 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:37 rssi_min:-59 rssi_med:-53 rssi_max:-48
said: 3 | **LINK** peer:0x00000012 proto:espnow n:13 rssi_min:-37 rssi_med:-33 rssi_max:-33
said: 4 | 0x00000012 espnow met predicted:-35 observed:-33
percept: 4 | 0x00000300 | link_stable_espnow | 0x00000012 | + | -
said: 5 | 0x00000012 ble met predicted:-54 observed:-53
percept: 5 | 0x00000300 | link_stable_ble | 0x00000012 | + | -
```

---

@LAT105LON5003 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 6246112 ±0 frame:45500
seq: 7817
follows: 0x00000010:1533 0x00000011:1439 0x00000012:1348 0x00000100:1482 0x00000200:2237
said: 1 | **LINKWIN** t_ms:6366572 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:33 rssi_min:-40 rssi_med:-33 rssi_max:-32
said: 3 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-59 rssi_med:-53 rssi_max:-47
said: 4 | 0x00000012 ble met predicted:-53 observed:-53
percept: 4 | 0x00000300 | link_stable_ble | 0x00000012 | + | -
said: 5 | 0x00000012 espnow met predicted:-33 observed:-33
percept: 5 | 0x00000300 | link_stable_espnow | 0x00000012 | + | -
```

---

@LAT103LON1290 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6318417 ±21 frame:45500
seq: 1351
follows: 0x00000010:1533 0x00000011:1439 0x00000100:1482 0x00000200:2237 0x00000300:7820
said: 1 | **LINKWIN** t_ms:6438877 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-32 rssi_med:-27 rssi_max:-24
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-42 rssi_max:-39
```

---

@LAT104LON142 | created:0 | updated:0

**carried through @LAT103LON1250**

```ttdb-carried
through: 1250
through: 8227
```

---

@LAT105LON5004 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 6306112 ±0 frame:45500
seq: 7819
follows: 0x00000010:1533 0x00000011:1439 0x00000012:1350 0x00000100:1482 0x00000200:2237
said: 1 | **LINKWIN** t_ms:6426572 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:49 rssi_min:-36 rssi_med:-34 rssi_max:-32
said: 3 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-80 rssi_med:-54 rssi_max:-47
said: 4 | 0x00000012 espnow met predicted:-33 observed:-34
percept: 4 | 0x00000300 | link_stable_espnow | 0x00000012 | + | -
said: 5 | 0x00000012 ble met predicted:-53 observed:-54
percept: 5 | 0x00000300 | link_stable_ble | 0x00000012 | + | -
```
@LAT106LON129 | created:0 | updated:0

**BAR** frame:45500 bar:10 own:5 held:4 terms:2 digest:0x43226677 settled_ms:300000
**HOLDS** agent:0x00000012 n:5 lo:1343 hi:1348 sum:6729
**HOLDS** agent:0x00000300 n:4 lo:7802 hi:7809 sum:31223
**DELIVER** up_s:152 heap:123544 fetched:5 unanswered:18 broken:0 resumed:5 empty:3 served:5 wants:6 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0x42e3bb8a same:1 split:0

---

@LAT103LON1291 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6378418 ±21 frame:45500
seq: 1352
follows: 0x00000010:1533 0x00000011:1439 0x00000100:1482 0x00000200:2237 0x00000300:7820
said: 1 | **LINKWIN** t_ms:6498877 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-29 rssi_med:-27 rssi_max:-25
```

---

@LAT105LON5005 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 6366112 ±0 frame:45500
seq: 7821
follows: 0x00000010:1533 0x00000011:1439 0x00000012:1351 0x00000100:1482 0x00000200:2237
said: 1 | **LINKWIN** t_ms:6486572 stream:0x7d6723f5 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-58 rssi_med:-53 rssi_max:-47
said: 3 | **LINK** peer:0x00000012 proto:espnow n:37 rssi_min:-38 rssi_med:-34 rssi_max:-32
said: 4 | 0x00000012 espnow met predicted:-34 observed:-34
percept: 4 | 0x00000300 | link_stable_espnow | 0x00000012 | + | -
said: 5 | 0x00000012 ble met predicted:-54 observed:-53
percept: 5 | 0x00000300 | link_stable_ble | 0x00000012 | + | -
```
