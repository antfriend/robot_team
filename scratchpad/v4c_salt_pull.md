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

@LAT106LON104 | created:0 | updated:0

**BAR** frame:8000 bar:4 own:10 held:40 terms:9 digest:0x161a9dd7 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1224 hi:1234 sum:12294
**HOLDS** agent:0x00000011 n:10 lo:1173 hi:1183 sum:11784
**HOLDS** agent:0x00000012 n:10 lo:1076 hi:1086 sum:10814
**HOLDS** agent:0x00000200 n:10 lo:1872 hi:1881 sum:18765
**HOLDS** agent:0x00000300 n:10 lo:4294 hi:4314 sum:43047
**DELIVER** up_s:2688 heap:120096 fetched:182 unanswered:157 broken:30 resumed:629 empty:86 served:717 wants:731 early:70 wantq_drop:0 superseded:0

---

@LAT106LON105 | created:0 | updated:0

**BAR** frame:8000 bar:5 own:10 held:40 terms:9 digest:0x14f3b7aa settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1235 hi:1245 sum:12404
**HOLDS** agent:0x00000011 n:10 lo:1184 hi:1193 sum:11885
**HOLDS** agent:0x00000012 n:10 lo:1087 hi:1096 sum:10915
**HOLDS** agent:0x00000200 n:10 lo:1882 hi:1891 sum:18865
**HOLDS** agent:0x00000300 n:10 lo:4316 hi:4334 sum:43250
**DELIVER** up_s:3289 heap:119836 fetched:224 unanswered:186 broken:35 resumed:724 empty:106 served:878 wants:893 early:70 wantq_drop:0 superseded:0

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

@LAT106LON106 | created:0 | updated:0

**BAR** frame:8000 bar:6 own:10 held:40 terms:9 digest:0x604cc9d2 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1246 hi:1256 sum:12514
**HOLDS** agent:0x00000011 n:10 lo:1194 hi:1203 sum:11985
**HOLDS** agent:0x00000012 n:10 lo:1097 hi:1106 sum:11015
**HOLDS** agent:0x00000200 n:10 lo:1892 hi:1901 sum:18965
**HOLDS** agent:0x00000300 n:10 lo:4336 hi:4354 sum:43450
**DELIVER** up_s:3889 heap:122800 fetched:265 unanswered:204 broken:41 resumed:833 empty:127 served:1021 wants:1041 early:70 wantq_drop:0 superseded:0

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

@LAT106LON107 | created:0 | updated:0

**BAR** frame:8000 bar:7 own:10 held:40 terms:9 digest:0x8f8983eb settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1257 hi:1267 sum:12624
**HOLDS** agent:0x00000011 n:10 lo:1204 hi:1213 sum:12085
**HOLDS** agent:0x00000012 n:10 lo:1107 hi:1117 sum:11124
**HOLDS** agent:0x00000200 n:10 lo:1902 hi:1911 sum:19065
**HOLDS** agent:0x00000300 n:10 lo:4356 hi:4375 sum:43658
**DELIVER** up_s:4488 heap:123040 fetched:306 unanswered:231 broken:46 resumed:961 empty:144 served:1141 wants:1168 early:70 wantq_drop:0 superseded:0

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

@LAT106LON108 | created:0 | updated:0

**BAR** frame:8000 bar:8 own:10 held:40 terms:9 digest:0x6cf5f785 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1268 hi:1278 sum:12734
**HOLDS** agent:0x00000011 n:10 lo:1214 hi:1223 sum:12185
**HOLDS** agent:0x00000012 n:10 lo:1118 hi:1128 sum:11234
**HOLDS** agent:0x00000200 n:10 lo:1913 hi:1922 sum:19175
**HOLDS** agent:0x00000300 n:10 lo:4377 hi:4395 sum:43860
**DELIVER** up_s:5087 heap:119556 fetched:344 unanswered:242 broken:53 resumed:1061 empty:165 served:1289 wants:1318 early:70 wantq_drop:0 superseded:0

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

@LAT106LON109 | created:0 | updated:0

**BAR** frame:8000 bar:9 own:10 held:40 terms:9 digest:0x30d90ae0 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1279 hi:1289 sum:12844
**HOLDS** agent:0x00000011 n:10 lo:1224 hi:1233 sum:12285
**HOLDS** agent:0x00000012 n:10 lo:1129 hi:1139 sum:11344
**HOLDS** agent:0x00000200 n:10 lo:1924 hi:1933 sum:19285
**HOLDS** agent:0x00000300 n:10 lo:4397 hi:4416 sum:44069
**DELIVER** up_s:5686 heap:119508 fetched:383 unanswered:269 broken:55 resumed:1171 empty:183 served:1449 wants:1484 early:70 wantq_drop:0 superseded:0

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

@LAT106LON110 | created:0 | updated:0

**BAR** frame:8000 bar:10 own:10 held:40 terms:9 digest:0x40588064 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1290 hi:1300 sum:12954
**HOLDS** agent:0x00000011 n:10 lo:1234 hi:1244 sum:12394
**HOLDS** agent:0x00000012 n:10 lo:1140 hi:1150 sum:11454
**HOLDS** agent:0x00000200 n:10 lo:1934 hi:1943 sum:19385
**HOLDS** agent:0x00000300 n:10 lo:4418 hi:4437 sum:44278
**DELIVER** up_s:6285 heap:119260 fetched:424 unanswered:289 broken:59 resumed:1307 empty:201 served:1586 wants:1624 early:70 wantq_drop:0 superseded:0

---

@LAT106LON111 | created:0 | updated:0

**BAR** frame:8000 bar:11 own:10 held:40 terms:9 digest:0xa1cf7219 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1301 hi:1311 sum:13064
**HOLDS** agent:0x00000011 n:10 lo:1245 hi:1255 sum:12504
**HOLDS** agent:0x00000012 n:10 lo:1151 hi:1161 sum:11564
**HOLDS** agent:0x00000200 n:10 lo:1944 hi:1953 sum:19485
**HOLDS** agent:0x00000300 n:10 lo:4439 hi:4457 sum:44480
**DELIVER** up_s:6885 heap:123064 fetched:466 unanswered:312 broken:62 resumed:1411 empty:220 served:1741 wants:1779 early:70 wantq_drop:0 superseded:0

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

@LAT106LON112 | created:0 | updated:0

**BAR** frame:8000 bar:12 own:10 held:40 terms:9 digest:0x9c7c5137 settled_ms:300015
**HOLDS** agent:0x00000010 n:10 lo:1312 hi:1322 sum:13174
**HOLDS** agent:0x00000011 n:10 lo:1256 hi:1265 sum:12605
**HOLDS** agent:0x00000012 n:10 lo:1162 hi:1171 sum:11665
**HOLDS** agent:0x00000200 n:10 lo:1954 hi:1963 sum:19585
**HOLDS** agent:0x00000300 n:10 lo:4459 hi:4477 sum:44680
**DELIVER** up_s:7489 heap:121160 fetched:505 unanswered:340 broken:67 resumed:1528 empty:240 served:1913 wants:1956 early:70 wantq_drop:0 superseded:0

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

@LAT103LON1197 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11247566 ±21 frame:8000
seq: 1246
follows: 0x00000010:1392 0x00000011:1335 0x00000100:957 0x00000200:2031 0x00000300:4616
said: 1 | **LINKWIN** t_ms:11236890 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-68 rssi_max:-60
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-55 rssi_max:-53
said: 4 | **LINK** peer:0x00000200 proto:espnow n:58 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 5 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-41 rssi_med:-39 rssi_max:-34
said: 6 | **LINK** peer:0x00000010 proto:espnow n:69 rssi_min:-59 rssi_med:-56 rssi_max:-52
said: 7 | **LINK** peer:0x00000011 proto:espnow n:69 rssi_min:-41 rssi_med:-39 rssi_max:-35
said: 8 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-51 rssi_max:-48
said: 9 | **LINK** peer:0x00000300 proto:ble n:36 rssi_min:-81 rssi_med:-31 rssi_max:-30
```

---

@LAT103LON1198 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11307564 ±21 frame:8000
seq: 1247
follows: 0x00000010:1393 0x00000011:1336 0x00000100:958 0x00000200:2032 0x00000300:4622
said: 1 | **LINKWIN** t_ms:11296892 stream:0x732acba3 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000200 proto:espnow n:114 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 3 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-58 rssi_med:-56 rssi_max:-52
said: 4 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-44 rssi_med:-39 rssi_max:-34
said: 5 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-40 rssi_med:-39 rssi_max:-35
said: 6 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-81 rssi_med:-57 rssi_max:-53
said: 7 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-67 rssi_max:-60
said: 8 | **LINK** peer:0x00000011 proto:ble n:69 rssi_min:-80 rssi_med:-51 rssi_max:-48
said: 9 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-31 rssi_max:-30
```

---

@LAT103LON1199 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11365562 ±21 frame:8000
seq: 1248
follows: 0x00000010:1394 0x00000011:1337 0x00000100:959 0x00000200:2033 0x00000300:4624
said: 1 | **LINKWIN** t_ms:11356891 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:64 rssi_min:-40 rssi_med:-39 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-80 rssi_med:-55 rssi_max:-53
said: 4 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 5 | **LINK** peer:0x00000010 proto:espnow n:117 rssi_min:-58 rssi_med:-56 rssi_max:-54
said: 6 | **LINK** peer:0x00000300 proto:espnow n:166 rssi_min:-17 rssi_med:-16 rssi_max:-16
said: 7 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-67 rssi_max:-60
said: 9 | **LINK** peer:0x00000011 proto:ble n:68 rssi_min:-81 rssi_med:-51 rssi_max:-48
```

---

@LAT103LON1200 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11427583 ±22 frame:8000
seq: 1249
follows: 0x00000010:1395 0x00000011:1338 0x00000100:960 0x00000200:2035 0x00000300:4624
said: 1 | **LINKWIN** t_ms:11416911 stream:0x732acba3 wall:0 window_ms:60019
said: 2 | **LINK** peer:0x00000010 proto:espnow n:78 rssi_min:-58 rssi_med:-56 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:71 rssi_min:-40 rssi_med:-39 rssi_max:-34
said: 4 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-68 rssi_max:-60
said: 5 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-55 rssi_max:-53
said: 6 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-31 rssi_max:-29
said: 7 | **LINK** peer:0x00000011 proto:espnow n:79 rssi_min:-40 rssi_med:-39 rssi_max:-35
said: 8 | **LINK** peer:0x00000300 proto:espnow n:173 rssi_min:-18 rssi_med:-16 rssi_max:-16
said: 9 | **LINK** peer:0x00000200 proto:espnow n:113 rssi_min:-47 rssi_med:-45 rssi_max:-40
```

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

@LAT103LON1201 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11487583 ±21 frame:8000
seq: 1251
follows: 0x00000010:1396 0x00000011:1340 0x00000100:961 0x00000200:2036 0x00000300:4626
said: 1 | **LINKWIN** t_ms:11476911 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:94 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 3 | **LINK** peer:0x00000011 proto:espnow n:75 rssi_min:-40 rssi_med:-39 rssi_max:-35
said: 4 | **LINK** peer:0x00000010 proto:espnow n:62 rssi_min:-58 rssi_med:-56 rssi_max:-53
said: 5 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-40 rssi_med:-38 rssi_max:-34
said: 7 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-79 rssi_med:-51 rssi_max:-47
said: 8 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-55 rssi_max:-53
said: 9 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-81 rssi_med:-68 rssi_max:-59
```

---

@LAT103LON1202 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11547582 ±21 frame:8000
seq: 1252
follows: 0x00000010:1397 0x00000011:1341 0x00000100:962 0x00000200:2037 0x00000300:4628
said: 1 | **LINKWIN** t_ms:11536911 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:144 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 3 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-45 rssi_med:-39 rssi_max:-34
said: 4 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-58 rssi_med:-56 rssi_max:-53
said: 5 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-82 rssi_med:-51 rssi_max:-47
said: 7 | **LINK** peer:0x00000300 proto:espnow n:233 rssi_min:-17 rssi_med:-16 rssi_max:-15
said: 8 | **LINK** peer:0x00000011 proto:espnow n:153 rssi_min:-41 rssi_med:-39 rssi_max:-35
said: 9 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-55 rssi_max:-53
```

---

@LAT103LON1203 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11607583 ±22 frame:8000
seq: 1253
follows: 0x00000010:1398 0x00000011:1342 0x00000100:963 0x00000200:2038 0x00000300:4630
said: 1 | **LINKWIN** t_ms:11596910 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-68 rssi_max:-60
said: 3 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-40 rssi_med:-39 rssi_max:-35
said: 4 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-57 rssi_max:-53
said: 5 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-41 rssi_med:-39 rssi_max:-34
said: 6 | **LINK** peer:0x00000200 proto:espnow n:113 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 7 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-58 rssi_med:-56 rssi_max:-54
said: 8 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-81 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000300 proto:espnow n:87 rssi_min:-18 rssi_med:-16 rssi_max:-15
```

---

@LAT103LON1204 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11667585 ±21 frame:8000
seq: 1254
follows: 0x00000010:1399 0x00000011:1343 0x00000100:964 0x00000200:2039 0x00000300:4632
said: 1 | **LINKWIN** t_ms:11656911 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-40 rssi_med:-39 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:90 rssi_min:-48 rssi_med:-45 rssi_max:-45
said: 4 | **LINK** peer:0x00000010 proto:espnow n:116 rssi_min:-58 rssi_med:-56 rssi_max:-54
said: 5 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-42 rssi_med:-39 rssi_max:-35
said: 6 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-67 rssi_max:-60
said: 7 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-51 rssi_max:-48
said: 8 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-57 rssi_max:-53
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

@LAT103LON1205 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11727597 ±22 frame:8000
seq: 1255
follows: 0x00000010:1400 0x00000011:1344 0x00000100:965 0x00000200:2040 0x00000300:4634
said: 1 | **LINKWIN** t_ms:11716922 stream:0x732acba3 wall:0 window_ms:60011
said: 2 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-51 rssi_max:-47
said: 3 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-81 rssi_med:-68 rssi_max:-60
said: 4 | **LINK** peer:0x00000011 proto:espnow n:75 rssi_min:-40 rssi_med:-39 rssi_max:-35
said: 5 | **LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-41 rssi_med:-39 rssi_max:-35
said: 6 | **LINK** peer:0x00000200 proto:espnow n:68 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 7 | **LINK** peer:0x00000010 proto:espnow n:60 rssi_min:-58 rssi_med:-56 rssi_max:-54
said: 8 | **LINK** peer:0x00000300 proto:espnow n:226 rssi_min:-18 rssi_med:-16 rssi_max:-16
said: 9 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-31 rssi_max:-30
```

---

@LAT103LON1206 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11787596 ±22 frame:8000
seq: 1256
follows: 0x00000010:1401 0x00000011:1345 0x00000100:966 0x00000200:2041 0x00000300:4636
said: 1 | **LINKWIN** t_ms:11776921 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:153 rssi_min:-40 rssi_med:-39 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-55 rssi_max:-53
said: 4 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-80 rssi_med:-68 rssi_max:-59
said: 5 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-80 rssi_med:-51 rssi_max:-47
said: 6 | **LINK** peer:0x00000010 proto:espnow n:130 rssi_min:-59 rssi_med:-56 rssi_max:-54
said: 7 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-43 rssi_med:-39 rssi_max:-35
said: 8 | **LINK** peer:0x00000200 proto:espnow n:115 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 9 | **LINK** peer:0x00000300 proto:espnow n:147 rssi_min:-18 rssi_med:-16 rssi_max:-15
```

---

@LAT103LON1207 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11847629 ±22 frame:8000
seq: 1257
follows: 0x00000010:1402 0x00000011:1345 0x00000100:967 0x00000200:2042 0x00000300:4638
said: 1 | **LINKWIN** t_ms:11836954 stream:0x732acba3 wall:0 window_ms:60032
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-85 rssi_med:-65 rssi_max:-51
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-44 rssi_med:-39 rssi_max:-22
said: 4 | **LINK** peer:0x00000200 proto:espnow n:112 rssi_min:-55 rssi_med:-47 rssi_max:-44
said: 5 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-60 rssi_med:-51 rssi_max:-44
said: 6 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-46 rssi_med:-39 rssi_max:-31
said: 7 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-82 rssi_med:-51 rssi_max:-45
said: 8 | **LINK** peer:0x00000300 proto:ble n:27 rssi_min:-80 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-59 rssi_max:-53
```

---

@LAT103LON1208 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11907651 ±21 frame:8000
seq: 1258
follows: 0x00000010:1403 0x00000011:1346 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **LINKWIN** t_ms:11896981 stream:0x732acba3 wall:0 window_ms:60027
said: 2 | **LINK** peer:0x00000010 proto:espnow n:74 rssi_min:-66 rssi_med:-51 rssi_max:-42
said: 3 | **LINK** peer:0x00000011 proto:espnow n:94 rssi_min:-56 rssi_med:-35 rssi_max:-30
said: 4 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-56 rssi_max:-42
said: 5 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-86 rssi_med:-65 rssi_max:-53
said: 6 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-80 rssi_med:-50 rssi_max:-42
said: 7 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-44 rssi_med:-22 rssi_max:-21
said: 8 | **LINK** peer:0x00000200 proto:espnow n:77 rssi_min:-55 rssi_med:-45 rssi_max:-41
```

---

@LAT103LON1209 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11967653 ±21 frame:8000
seq: 1259
follows: 0x00000010:1404 0x00000011:1347 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **LINKWIN** t_ms:11956981 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-52 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-45 rssi_med:-38 rssi_max:-27
said: 4 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-57 rssi_med:-40 rssi_max:-32
said: 5 | **LINK** peer:0x00000010 proto:espnow n:66 rssi_min:-58 rssi_med:-48 rssi_max:-44
said: 6 | **LINK** peer:0x00000200 proto:ble n:35 rssi_min:-79 rssi_med:-49 rssi_max:-45
said: 7 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-81 rssi_med:-67 rssi_max:-53
```

---

@LAT103LON1210 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12027648 ±21 frame:8000
seq: 1260
follows: 0x00000010:1405 0x00000011:1348 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **LINKWIN** t_ms:12016981 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:55 rssi_min:-44 rssi_med:-38 rssi_max:-30
said: 3 | **LINK** peer:0x00000010 proto:espnow n:53 rssi_min:-58 rssi_med:-45 rssi_max:-27
said: 4 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-82 rssi_med:-50 rssi_max:-42
said: 5 | **LINK** peer:0x00000010 proto:ble n:42 rssi_min:-84 rssi_med:-54 rssi_max:-43
```

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

@LAT103LON1211 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12087653 ±22 frame:8000
seq: 1262
follows: 0x00000010:1405 0x00000011:1350 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **LINKWIN** t_ms:12076980 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:4 rssi_min:-50 rssi_med:-50 rssi_max:-40
said: 3 | **LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-42 rssi_med:-25 rssi_max:-23
said: 4 | **LINK** peer:0x00000011 proto:ble n:38 rssi_min:-81 rssi_med:-46 rssi_max:-35
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

@LAT103LON1212 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 316086 ±0 frame:8000
seq: 1266
follows: 0x00000010:1405 0x00000011:1350 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **LINKWIN** t_ms:305268 stream:0xc9e0e898 wall:0 window_ms:316086
said: 2 | **LINK** peer:0x00000011 proto:espnow n:3 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:ble n:5 rssi_min:-62 rssi_med:-52 rssi_max:-45
```

---

@LAT103LON1213 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 43517 ±21 frame:7500
seq: 1267
follows: 0x00000010:1406 0x00000011:1350 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **LINKWIN** t_ms:365268 stream:0xc9e0e898 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-52 rssi_max:-45
said: 3 | **LINK** peer:0x00000011 proto:espnow n:50 rssi_min:-55 rssi_med:-42 rssi_max:-35
said: 4 | **LINK** peer:0x00000010 proto:espnow n:43 rssi_min:-33 rssi_med:-32 rssi_max:-28
said: 5 | **LINK** peer:0x00000010 proto:ble n:42 rssi_min:-80 rssi_med:-48 rssi_max:-41
said: 6 | **LINK** peer:0x00000100 proto:espnow n:3 rssi_min:-36 rssi_med:-32 rssi_max:-31
```

---

@LAT103LON1214 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 103513 ±21 frame:7500
seq: 1268
follows: 0x00000010:1408 0x00000011:1353 0x00000100:1001 0x00000200:2044 0x00000300:4641
said: 1 | **LINKWIN** t_ms:425269 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:95 rssi_min:-37 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000011 proto:espnow n:137 rssi_min:-43 rssi_med:-40 rssi_max:-35
said: 4 | **LINK** peer:0x00000100 proto:espnow n:94 rssi_min:-36 rssi_med:-30 rssi_max:-28
said: 5 | **LINK** peer:0x00000010 proto:ble n:72 rssi_min:-80 rssi_med:-48 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-80 rssi_med:-53 rssi_max:-43
said: 7 | **LINK** peer:0x00000300 proto:espnow n:175 rssi_min:-42 rssi_med:-39 rssi_max:-31
said: 8 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-80 rssi_med:-51 rssi_max:-46
said: 9 | **LINK** peer:0x00000200 proto:espnow n:110 rssi_min:-32 rssi_med:-30 rssi_max:-28
```

---

@LAT103LON1215 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 163514 ±21 frame:7500
seq: 1269
follows: 0x00000010:1409 0x00000011:1354 0x00000100:1002 0x00000200:2046 0x00000300:4645
said: 1 | **LINKWIN** t_ms:485268 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-52 rssi_max:-46
said: 3 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-45 rssi_max:-43
said: 4 | **LINK** peer:0x00000011 proto:espnow n:110 rssi_min:-44 rssi_med:-40 rssi_max:-35
said: 5 | **LINK** peer:0x00000300 proto:espnow n:186 rssi_min:-52 rssi_med:-39 rssi_max:-32
said: 6 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-32 rssi_med:-30 rssi_max:-27
said: 7 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-38 rssi_med:-31 rssi_max:-29
said: 8 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-80 rssi_med:-49 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:espnow n:132 rssi_min:-34 rssi_med:-30 rssi_max:-29
```

---

@LAT103LON1216 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 223515 ±21 frame:7500
seq: 1270
follows: 0x00000010:1410 0x00000011:1355 0x00000100:1003 0x00000200:2047 0x00000300:4647
said: 1 | **LINKWIN** t_ms:545269 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:157 rssi_min:-37 rssi_med:-32 rssi_max:-30
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-52 rssi_max:-49
said: 4 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-43 rssi_med:-40 rssi_max:-35
said: 5 | **LINK** peer:0x00000300 proto:espnow n:192 rssi_min:-51 rssi_med:-41 rssi_max:-33
said: 6 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 7 | **LINK** peer:0x00000010 proto:espnow n:97 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-81 rssi_med:-49 rssi_max:-42
said: 9 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-80 rssi_med:-47 rssi_max:-44
```

---

@LAT103LON1217 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 283515 ±21 frame:7500
seq: 1271
follows: 0x00000010:1411 0x00000011:1356 0x00000100:1004 0x00000200:2048 0x00000300:4649
said: 1 | **LINKWIN** t_ms:605269 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-80 rssi_med:-52 rssi_max:-45
said: 4 | **LINK** peer:0x00000011 proto:espnow n:79 rssi_min:-44 rssi_med:-41 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:espnow n:111 rssi_min:-37 rssi_med:-32 rssi_max:-30
said: 6 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-35 rssi_med:-30 rssi_max:-29
said: 7 | **LINK** peer:0x00000300 proto:espnow n:198 rssi_min:-49 rssi_med:-43 rssi_max:-35
said: 8 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-47 rssi_max:-45
said: 9 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-37 rssi_med:-31 rssi_max:-30
```

---

@LAT103LON1218 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 343515 ±21 frame:7500
seq: 1272
follows: 0x00000010:1412 0x00000011:1357 0x00000100:1005 0x00000200:2049 0x00000300:4651
said: 1 | **LINKWIN** t_ms:665269 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:104 rssi_min:-37 rssi_med:-32 rssi_max:-30
said: 3 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-80 rssi_med:-46 rssi_max:-45
said: 4 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-49 rssi_max:-42
said: 5 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-35 rssi_med:-31 rssi_max:-29
said: 6 | **LINK** peer:0x00000300 proto:espnow n:156 rssi_min:-50 rssi_med:-44 rssi_max:-35
said: 7 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-52 rssi_max:-50
said: 8 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-37 rssi_med:-32 rssi_max:-30
said: 9 | **LINK** peer:0x00000011 proto:espnow n:75 rssi_min:-45 rssi_med:-42 rssi_max:-36
```

---

@LAT103LON1219 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 403516 ±21 frame:7500
seq: 1273
follows: 0x00000010:1413 0x00000011:1358 0x00000100:1006 0x00000200:2050 0x00000300:4653
said: 1 | **LINKWIN** t_ms:725269 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-53 rssi_max:-46
said: 3 | **LINK** peer:0x00000200 proto:espnow n:98 rssi_min:-36 rssi_med:-31 rssi_max:-31
said: 4 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-52 rssi_max:-50
said: 5 | **LINK** peer:0x00000011 proto:espnow n:153 rssi_min:-45 rssi_med:-43 rssi_max:-41
said: 6 | **LINK** peer:0x00000010 proto:espnow n:110 rssi_min:-38 rssi_med:-32 rssi_max:-29
said: 7 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-35 rssi_med:-31 rssi_max:-31
said: 8 | **LINK** peer:0x00000300 proto:espnow n:188 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 9 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-49 rssi_max:-43
```

---

@LAT103LON1220 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 463516 ±21 frame:7500
seq: 1274
follows: 0x00000010:1414 0x00000011:1359 0x00000100:1007 0x00000200:2051 0x00000300:4655
said: 1 | **LINKWIN** t_ms:785269 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-51 rssi_max:-50
said: 3 | **LINK** peer:0x00000011 proto:ble n:46 rssi_min:-81 rssi_med:-53 rssi_max:-46
said: 4 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-37 rssi_med:-31 rssi_max:-29
said: 5 | **LINK** peer:0x00000200 proto:espnow n:98 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 6 | **LINK** peer:0x00000300 proto:espnow n:175 rssi_min:-46 rssi_med:-44 rssi_max:-39
said: 7 | **LINK** peer:0x00000011 proto:espnow n:82 rssi_min:-44 rssi_med:-42 rssi_max:-41
said: 8 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-49 rssi_max:-43
said: 9 | **LINK** peer:0x00000010 proto:espnow n:95 rssi_min:-37 rssi_med:-32 rssi_max:-31
```

---

@LAT103LON1221 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 523516 ±21 frame:7500
seq: 1275
follows: 0x00000010:1415 0x00000011:1360 0x00000100:1008 0x00000200:2052 0x00000300:4657
said: 1 | **LINKWIN** t_ms:845269 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-49 rssi_max:-42
said: 3 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-52 rssi_max:-45
said: 4 | **LINK** peer:0x00000300 proto:espnow n:207 rssi_min:-53 rssi_med:-44 rssi_max:-39
said: 5 | **LINK** peer:0x00000011 proto:espnow n:130 rssi_min:-44 rssi_med:-42 rssi_max:-36
said: 6 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-36 rssi_med:-32 rssi_max:-30
said: 8 | **LINK** peer:0x00000200 proto:espnow n:137 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 9 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-52 rssi_max:-50
```

---

@LAT103LON1222 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 583516 ±21 frame:7500
seq: 1276
follows: 0x00000010:1416 0x00000011:1361 0x00000100:1009 0x00000200:2053 0x00000300:4659
said: 1 | **LINKWIN** t_ms:905269 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-45
said: 4 | **LINK** peer:0x00000011 proto:espnow n:78 rssi_min:-44 rssi_med:-41 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:85 rssi_min:-37 rssi_med:-32 rssi_max:-30
said: 6 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-35 rssi_med:-31 rssi_max:-29
said: 7 | **LINK** peer:0x00000200 proto:ble n:70 rssi_min:-80 rssi_med:-46 rssi_max:-45
said: 8 | **LINK** peer:0x00000300 proto:espnow n:218 rssi_min:-54 rssi_med:-45 rssi_max:-41
said: 9 | **LINK** peer:0x00000010 proto:espnow n:124 rssi_min:-37 rssi_med:-32 rssi_max:-30
```

---

@LAT103LON1223 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 643516 ±21 frame:7500
seq: 1277
follows: 0x00000010:1417 0x00000011:1362 0x00000100:1010 0x00000200:2054 0x00000300:4661
said: 1 | **LINKWIN** t_ms:965269 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000300 proto:espnow n:271 rssi_min:-46 rssi_med:-44 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000200 proto:espnow n:97 rssi_min:-35 rssi_med:-31 rssi_max:-31
said: 6 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-49 rssi_max:-43
said: 7 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-53 rssi_max:-48
said: 8 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-51 rssi_max:-50
said: 9 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-46 rssi_max:-45
```

---

@LAT103LON1224 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 703518 ±21 frame:7500
seq: 1278
follows: 0x00000010:1418 0x00000011:1363 0x00000100:1011 0x00000200:2055 0x00000300:4663
said: 1 | **LINKWIN** t_ms:1025269 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:116 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 3 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-42 rssi_med:-41 rssi_max:-39
said: 4 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-80 rssi_med:-54 rssi_max:-48
said: 5 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-37 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-51 rssi_max:-50
said: 7 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-46 rssi_max:-45
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-49 rssi_max:-42
said: 9 | **LINK** peer:0x00000300 proto:espnow n:225 rssi_min:-46 rssi_med:-44 rssi_max:-40
```

---

@LAT103LON1225 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 763517 ±21 frame:7500
seq: 1279
follows: 0x00000010:1419 0x00000011:1364 0x00000100:1012 0x00000200:2056 0x00000300:4665
said: 1 | **LINKWIN** t_ms:1085269 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-51 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-46 rssi_max:-45
said: 4 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-38 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000300 proto:espnow n:189 rssi_min:-46 rssi_med:-44 rssi_max:-39
said: 6 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-50 rssi_max:-42
said: 7 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-35 rssi_med:-31 rssi_max:-28
said: 8 | **LINK** peer:0x00000011 proto:espnow n:103 rssi_min:-42 rssi_med:-40 rssi_max:-36
said: 9 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-54 rssi_max:-48
```

---

@LAT103LON1226 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 823525 ±21 frame:7500
seq: 1280
follows: 0x00000010:1420 0x00000011:1365 0x00000100:1013 0x00000200:2057 0x00000300:4667
said: 1 | **LINKWIN** t_ms:1145274 stream:0xc9e0e898 wall:0 window_ms:60005
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-46 rssi_max:-45
said: 3 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-80 rssi_med:-54 rssi_max:-48
said: 4 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000100 proto:espnow n:79 rssi_min:-34 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000200 proto:espnow n:142 rssi_min:-35 rssi_med:-31 rssi_max:-31
said: 7 | **LINK** peer:0x00000011 proto:espnow n:155 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 8 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-45 rssi_med:-44 rssi_max:-40
said: 9 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-50 rssi_max:-43
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

@LAT103LON1227 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 883528 ±21 frame:7500
seq: 1282
follows: 0x00000010:1421 0x00000011:1366 0x00000100:1014 0x00000200:2058 0x00000300:4669
said: 1 | **LINKWIN** t_ms:1205277 stream:0xc9e0e898 wall:0 window_ms:60003
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-51 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:177 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-80 rssi_med:-50 rssi_max:-42
said: 5 | **LINK** peer:0x00000011 proto:espnow n:67 rssi_min:-43 rssi_med:-41 rssi_max:-37
said: 6 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-34 rssi_med:-31 rssi_max:-29
said: 7 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-47 rssi_max:-45
said: 9 | **LINK** peer:0x00000010 proto:espnow n:115 rssi_min:-37 rssi_med:-32 rssi_max:-31
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

@LAT103LON1228 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 943528 ±21 frame:7500
seq: 1283
follows: 0x00000010:1422 0x00000011:1367 0x00000100:1015 0x00000200:2059 0x00000300:4671
said: 1 | **LINKWIN** t_ms:1265277 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 3 | **LINK** peer:0x00000010 proto:espnow n:156 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 4 | **LINK** peer:0x00000011 proto:espnow n:114 rssi_min:-43 rssi_med:-41 rssi_max:-39
said: 5 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-36 rssi_med:-31 rssi_max:-31
said: 6 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-47 rssi_max:-45
said: 7 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-51 rssi_max:-49
said: 8 | **LINK** peer:0x00000300 proto:espnow n:192 rssi_min:-46 rssi_med:-44 rssi_max:-40
said: 9 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-80 rssi_med:-55 rssi_max:-48
```

---

@LAT103LON1229 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1003529 ±21 frame:7500
seq: 1284
follows: 0x00000010:1423 0x00000011:1368 0x00000100:1016 0x00000200:2060 0x00000300:4673
said: 1 | **LINKWIN** t_ms:1325277 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-79 rssi_med:-47 rssi_max:-45
said: 4 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 5 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000200 proto:espnow n:75 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 7 | **LINK** peer:0x00000300 proto:espnow n:162 rssi_min:-47 rssi_med:-44 rssi_max:-41
said: 8 | **LINK** peer:0x00000010 proto:espnow n:91 rssi_min:-36 rssi_med:-32 rssi_max:-30
said: 9 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-52 rssi_max:-50
```

---

@LAT103LON1230 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1063529 ±21 frame:7500
seq: 1285
follows: 0x00000010:1424 0x00000011:1369 0x00000100:1017 0x00000200:2061 0x00000300:4675
said: 1 | **LINKWIN** t_ms:1385277 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-80 rssi_med:-47 rssi_max:-45
said: 3 | **LINK** peer:0x00000300 proto:espnow n:190 rssi_min:-46 rssi_med:-44 rssi_max:-41
said: 4 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000010 proto:espnow n:89 rssi_min:-38 rssi_med:-32 rssi_max:-31
said: 6 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-50 rssi_max:-43
said: 7 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-52 rssi_max:-50
said: 8 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000011 proto:espnow n:112 rssi_min:-45 rssi_med:-42 rssi_max:-40
```

---

@LAT103LON1231 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1123549 ±21 frame:7500
seq: 1286
follows: 0x00000010:1425 0x00000011:1370 0x00000100:1018 0x00000200:2062 0x00000300:4677
said: 1 | **LINKWIN** t_ms:1445296 stream:0xc9e0e898 wall:0 window_ms:60019
said: 2 | **LINK** peer:0x00000300 proto:espnow n:205 rssi_min:-47 rssi_med:-44 rssi_max:-39
said: 3 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-80 rssi_med:-50 rssi_max:-42
said: 4 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-36 rssi_med:-31 rssi_max:-29
said: 5 | **LINK** peer:0x00000200 proto:espnow n:209 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 6 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-46 rssi_max:-45
said: 7 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-80 rssi_med:-54 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:espnow n:105 rssi_min:-36 rssi_med:-32 rssi_max:-30
said: 9 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-51 rssi_max:-48
```

---

@LAT105LON4771 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 1140092 ±21 frame:7500
seq: 1426
follows: 0x00000011:1370 0x00000012:1286 0x00000100:1018 0x00000200:2063 0x00000300:4679
said: 1 | **LINKWIN** t_ms:1461834 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:112 rssi_min:-43 rssi_med:-40 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:espnow n:182 rssi_min:-46 rssi_med:-43 rssi_max:-40
said: 4 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-61 rssi_max:-54
said: 5 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-51 rssi_med:-47 rssi_max:-41
said: 6 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-59 rssi_med:-54 rssi_max:-48
said: 7 | **LINK** peer:0x00000200 proto:espnow n:172 rssi_min:-59 rssi_med:-51 rssi_max:-45
said: 8 | **LINK** peer:0x00000100 proto:espnow n:75 rssi_min:-69 rssi_med:-58 rssi_max:-50
said: 9 | **LINK** peer:0x00000012 proto:espnow n:114 rssi_min:-35 rssi_med:-32 rssi_max:-30
```

---

@LAT103LON1232 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1183549 ±21 frame:7500
seq: 1287
follows: 0x00000010:1426 0x00000011:1371 0x00000100:1019 0x00000200:2063 0x00000300:4679
said: 1 | **LINKWIN** t_ms:1505295 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-49 rssi_med:-47 rssi_max:-45
said: 3 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-48
said: 4 | **LINK** peer:0x00000011 proto:espnow n:82 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 5 | **LINK** peer:0x00000010 proto:espnow n:107 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 6 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000200 proto:espnow n:104 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 8 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-51 rssi_max:-50
said: 9 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-50 rssi_max:-43
```

---

@LAT105LON4772 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1184177 ±0 frame:7500
seq: 4680
follows: 0x00000010:1426 0x00000011:1371 0x00000012:1287 0x00000100:1019 0x00000200:2063
said: 1 | **LINKWIN** t_ms:1505921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:75 rssi_min:-62 rssi_med:-60 rssi_max:-56
said: 3 | **LINK** peer:0x00000012 proto:espnow n:102 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 5 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 6 | **LINK** peer:0x00000200 proto:espnow n:118 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 7 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-56 rssi_max:-53
said: 9 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-80 rssi_med:-62 rssi_max:-49
said: 10 | 0x00000200 ble met predicted:-59 observed:-59
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-56 observed:-56
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-42 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-55 observed:-60
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-48 observed:-47
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble unobserved predicted:-68 observed:-68
percept: 17 | 0x00000011 | link_stable | ble | ? | -
```

---

@LAT105LON4773 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1189660 ±21 frame:7500
seq: 2064
follows: 0x00000010:1426 0x00000011:1372 0x00000012:1287 0x00000100:1019 0x00000300:4681
said: 1 | **LINKWIN** t_ms:1511389 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:84 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 3 | **LINK** peer:0x00000300 proto:espnow n:159 rssi_min:-39 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000012 proto:espnow n:83 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-67 rssi_med:-62 rssi_max:-61
said: 6 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-72 rssi_med:-64 rssi_max:-56
said: 7 | **LINK** peer:0x00000010 proto:espnow n:114 rssi_min:-51 rssi_med:-49 rssi_max:-49
said: 8 | **LINK** peer:0x00000300 proto:ble n:50 rssi_min:-79 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-52 rssi_max:-51
```

---

@LAT105LON4774 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 1172909 ±21 frame:7500
seq: 1371
follows: 0x00000010:1426 0x00000012:1286 0x00000100:1019 0x00000200:2063 0x00000300:4679
said: 1 | **LINKWIN** t_ms:1494655 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-63 rssi_med:-61 rssi_max:-53
said: 3 | **LINK** peer:0x00000300 proto:espnow n:165 rssi_min:-62 rssi_med:-58 rssi_max:-53
said: 4 | **LINK** peer:0x00000200 proto:espnow n:109 rssi_min:-49 rssi_med:-45 rssi_max:-43
said: 5 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-62 rssi_max:-56
said: 6 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-51 rssi_max:-47
said: 7 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-61 rssi_max:-56
said: 8 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 9 | **LINK** peer:0x00000010 proto:espnow n:92 rssi_min:-42 rssi_med:-35 rssi_max:-34
```

---

@LAT105LON4775 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 1200121 ±21 frame:7500
seq: 1427
follows: 0x00000011:1372 0x00000012:1287 0x00000100:1019 0x00000200:2064 0x00000300:4681
said: 1 | **LINKWIN** t_ms:1521862 stream:0xc9e0e898 wall:0 window_ms:60028
said: 2 | **LINK** peer:0x00000300 proto:espnow n:111 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 3 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 4 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-48 rssi_max:-42
said: 5 | **LINK** peer:0x00000011 proto:ble n:68 rssi_min:-58 rssi_med:-53 rssi_max:-52
said: 6 | **LINK** peer:0x00000012 proto:espnow n:78 rssi_min:-34 rssi_med:-32 rssi_max:-30
said: 7 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-61 rssi_med:-59 rssi_max:-57
said: 8 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-70 rssi_med:-60 rssi_max:-55
said: 9 | **LINK** peer:0x00000200 proto:espnow n:85 rssi_min:-51 rssi_med:-50 rssi_max:-48
```

---

@LAT103LON1233 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1243549 ±21 frame:7500
seq: 1288
follows: 0x00000010:1428 0x00000011:1373 0x00000100:1020 0x00000200:2064 0x00000300:4681
said: 1 | **LINKWIN** t_ms:1565296 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:71 rssi_min:-80 rssi_med:-50 rssi_max:-42
said: 3 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 4 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000200 proto:espnow n:151 rssi_min:-37 rssi_med:-32 rssi_max:-28
said: 6 | **LINK** peer:0x00000010 proto:espnow n:119 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 7 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-54 rssi_med:-51 rssi_max:-50
said: 8 | **LINK** peer:0x00000300 proto:espnow n:171 rssi_min:-45 rssi_med:-43 rssi_max:-39
said: 9 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-83 rssi_med:-47 rssi_max:-45
```

---

@LAT105LON4776 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 1232911 ±21 frame:7500
seq: 1373
follows: 0x00000010:1428 0x00000012:1287 0x00000100:1020 0x00000200:2064 0x00000300:4681
said: 1 | **LINKWIN** t_ms:1554655 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 3 | **LINK** peer:0x00000010 proto:espnow n:107 rssi_min:-42 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-62 rssi_med:-61 rssi_max:-59
said: 5 | **LINK** peer:0x00000300 proto:espnow n:144 rssi_min:-60 rssi_med:-57 rssi_max:-54
said: 6 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-61 rssi_max:-56
said: 7 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-82 rssi_med:-62 rssi_max:-57
said: 8 | **LINK** peer:0x00000012 proto:ble n:49 rssi_min:-81 rssi_med:-51 rssi_max:-47
said: 9 | **LINK** peer:0x00000200 proto:espnow n:147 rssi_min:-46 rssi_med:-45 rssi_max:-45
```

---

@LAT105LON4777 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1249662 ±21 frame:7500
seq: 2065
follows: 0x00000010:1428 0x00000011:1373 0x00000012:1288 0x00000100:1021 0x00000300:4683
said: 1 | **LINKWIN** t_ms:1571389 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:166 rssi_min:-39 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000011 proto:espnow n:155 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 4 | **LINK** peer:0x00000012 proto:espnow n:124 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-35 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 7 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-54 rssi_med:-52 rssi_max:-51
said: 8 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-72 rssi_med:-65 rssi_max:-55
said: 9 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-80 rssi_med:-55 rssi_max:-52
```

---

@LAT105LON4778 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1244177 ±0 frame:7500
seq: 4682
follows: 0x00000010:1428 0x00000011:1373 0x00000012:1288 0x00000100:1020 0x00000200:2064
said: 1 | **LINKWIN** t_ms:1565921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:101 rssi_min:-46 rssi_med:-45 rssi_max:-45
said: 3 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-79 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-56 rssi_max:-53
said: 5 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 6 | **LINK** peer:0x00000010 proto:espnow n:121 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000200 proto:espnow n:140 rssi_min:-42 rssi_med:-41 rssi_max:-41
said: 8 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-63 rssi_max:-49
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-67 rssi_max:-60
said: 10 | 0x00000011 espnow unobserved predicted:-60 observed:-60
percept: 10 | 0x00000011 | link_stable | espnow | ? | -
said: 11 | 0x00000012 espnow met predicted:-45 observed:-45
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-59 observed:-59
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-62 observed:-63
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT105LON4779 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 1292911 ±21 frame:7500
seq: 1374
follows: 0x00000010:1429 0x00000012:1288 0x00000100:1022 0x00000200:2066 0x00000300:4684
said: 1 | **LINKWIN** t_ms:1614655 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-42 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-63 rssi_med:-61 rssi_max:-59
said: 4 | **LINK** peer:0x00000300 proto:espnow n:165 rssi_min:-60 rssi_med:-57 rssi_max:-55
said: 5 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 6 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-55 rssi_max:-51
said: 7 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-80 rssi_med:-51 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:espnow n:83 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-61 rssi_max:-56
```

---

@LAT103LON1234 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1303556 ±21 frame:7500
seq: 1289
follows: 0x00000010:1429 0x00000011:1374 0x00000100:1022 0x00000200:2066 0x00000300:4684
said: 1 | **LINKWIN** t_ms:1625302 stream:0xc9e0e898 wall:0 window_ms:60006
said: 2 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-83 rssi_med:-53 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-51 rssi_max:-50
said: 4 | **LINK** peer:0x00000300 proto:espnow n:155 rssi_min:-45 rssi_med:-43 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:95 rssi_min:-38 rssi_med:-32 rssi_max:-31
said: 6 | **LINK** peer:0x00000011 proto:espnow n:183 rssi_min:-44 rssi_med:-41 rssi_max:-38
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-50 rssi_max:-43
said: 8 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 9 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-47 rssi_max:-45
```

---

@LAT105LON4780 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1309681 ±21 frame:7500
seq: 2067
follows: 0x00000010:1429 0x00000011:1374 0x00000012:1289 0x00000100:1022 0x00000300:4686
said: 1 | **LINKWIN** t_ms:1631408 stream:0xc9e0e898 wall:0 window_ms:60019
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-38 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:espnow n:181 rssi_min:-39 rssi_med:-37 rssi_max:-36
said: 5 | **LINK** peer:0x00000011 proto:espnow n:139 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-64 rssi_med:-62 rssi_max:-60
said: 7 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-54 rssi_med:-52 rssi_max:-51
said: 8 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-76 rssi_med:-65 rssi_max:-53
said: 9 | **LINK** peer:0x00000012 proto:espnow n:80 rssi_min:-36 rssi_med:-34 rssi_max:-33
```

---

@LAT105LON4781 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 1260121 ±21 frame:7500
seq: 1429
follows: 0x00000011:1373 0x00000012:1288 0x00000100:1021 0x00000200:2065 0x00000300:4683
said: 1 | **LINKWIN** t_ms:1581862 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-42 rssi_med:-40 rssi_max:-38
said: 3 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-80 rssi_med:-48 rssi_max:-42
said: 4 | **LINK** peer:0x00000200 proto:espnow n:71 rssi_min:-54 rssi_med:-50 rssi_max:-48
said: 5 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-59 rssi_med:-54 rssi_max:-53
said: 6 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 7 | **LINK** peer:0x00000012 proto:espnow n:69 rssi_min:-35 rssi_med:-31 rssi_max:-31
said: 8 | **LINK** peer:0x00000300 proto:espnow n:131 rssi_min:-46 rssi_med:-44 rssi_max:-40
said: 9 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-60 rssi_med:-52 rssi_max:-45
```

---

@LAT105LON4782 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 1320122 ±21 frame:7500
seq: 1430
follows: 0x00000011:1374 0x00000012:1289 0x00000100:1022 0x00000200:2067 0x00000300:4686
said: 1 | **LINKWIN** t_ms:1641861 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:140 rssi_min:-43 rssi_med:-40 rssi_max:-38
said: 3 | **LINK** peer:0x00000300 proto:espnow n:234 rssi_min:-51 rssi_med:-44 rssi_max:-35
said: 4 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-47 rssi_max:-42
said: 5 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-60 rssi_med:-55 rssi_max:-52
said: 6 | **LINK** peer:0x00000012 proto:espnow n:102 rssi_min:-35 rssi_med:-32 rssi_max:-30
said: 7 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-52 rssi_max:-45
said: 8 | **LINK** peer:0x00000100 proto:espnow n:76 rssi_min:-61 rssi_med:-58 rssi_max:-50
said: 9 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-51 rssi_med:-50 rssi_max:-45
```

---

@LAT105LON4783 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 1352912 ±21 frame:7500
seq: 1375
follows: 0x00000010:1430 0x00000012:1289 0x00000100:1023 0x00000200:2067 0x00000300:4686
said: 1 | **LINKWIN** t_ms:1674655 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-64 rssi_med:-60 rssi_max:-53
said: 3 | **LINK** peer:0x00000300 proto:espnow n:175 rssi_min:-65 rssi_med:-56 rssi_max:-45
said: 4 | **LINK** peer:0x00000200 proto:espnow n:143 rssi_min:-48 rssi_med:-45 rssi_max:-45
said: 5 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-42 rssi_med:-35 rssi_max:-34
said: 6 | **LINK** peer:0x00000012 proto:espnow n:117 rssi_min:-43 rssi_med:-40 rssi_max:-32
said: 7 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-54 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-51 rssi_max:-46
said: 9 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-61 rssi_max:-55
```

---

@LAT103LON1235 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1363556 ±21 frame:7500
seq: 1290
follows: 0x00000010:1430 0x00000011:1375 0x00000100:1023 0x00000200:2067 0x00000300:4686
said: 1 | **LINKWIN** t_ms:1685302 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-46 rssi_max:-45
said: 3 | **LINK** peer:0x00000300 proto:espnow n:184 rssi_min:-45 rssi_med:-43 rssi_max:-39
said: 4 | **LINK** peer:0x00000011 proto:espnow n:126 rssi_min:-44 rssi_med:-42 rssi_max:-39
said: 5 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000200 proto:espnow n:110 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 7 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-80 rssi_med:-52 rssi_max:-49
said: 8 | **LINK** peer:0x00000011 proto:ble n:69 rssi_min:-79 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-36 rssi_med:-32 rssi_max:-29
```

---

@LAT105LON4784 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1304177 ±0 frame:7500
seq: 4685
follows: 0x00000010:1429 0x00000011:1374 0x00000012:1288 0x00000100:1022 0x00000200:2066
said: 1 | **LINKWIN** t_ms:1625921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:73 rssi_min:-46 rssi_med:-45 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-64 rssi_med:-59 rssi_max:-53
said: 4 | **LINK** peer:0x00000011 proto:espnow n:153 rssi_min:-64 rssi_med:-59 rssi_max:-48
said: 5 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-66 rssi_med:-62 rssi_max:-50
said: 6 | **LINK** peer:0x00000200 proto:espnow n:81 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 7 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-79 rssi_med:-56 rssi_max:-53
said: 8 | **LINK** peer:0x00000010 proto:espnow n:72 rssi_min:-52 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-77 rssi_med:-67 rssi_max:-60
said: 10 | 0x00000012 espnow met predicted:-45 observed:-45
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-59 observed:-59
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000012 ble met predicted:-56 observed:-56
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow unobserved predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | ? | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-63 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-67 observed:-67
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT105LON4785 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1364177 ±0 frame:7500
seq: 4687
follows: 0x00000010:1430 0x00000011:1375 0x00000012:1290 0x00000100:1023 0x00000200:2067
said: 1 | **LINKWIN** t_ms:1685921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:138 rssi_min:-62 rssi_med:-58 rssi_max:-55
said: 3 | **LINK** peer:0x00000012 proto:espnow n:102 rssi_min:-48 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 5 | **LINK** peer:0x00000010 proto:espnow n:87 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 6 | **LINK** peer:0x00000200 proto:espnow n:140 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 7 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-79 rssi_med:-66 rssi_max:-59
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-80 rssi_med:-56 rssi_max:-53
said: 10 | 0x00000012 espnow met predicted:-45 observed:-45
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-59 observed:-59
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000011 espnow met predicted:-59 observed:-58
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble unobserved predicted:-62 observed:-62
percept: 13 | 0x00000010 | link_stable | ble | ? | -
said: 14 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-56 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-49
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-67 observed:-66
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT105LON4786 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1369682 ±21 frame:7500
seq: 2068
follows: 0x00000010:1430 0x00000011:1375 0x00000012:1290 0x00000100:1023 0x00000300:4688
said: 1 | **LINKWIN** t_ms:1691408 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:96 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 3 | **LINK** peer:0x00000012 proto:espnow n:114 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000011 proto:espnow n:132 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000300 proto:espnow n:175 rssi_min:-39 rssi_med:-37 rssi_max:-36
said: 7 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-61 rssi_max:-60
said: 8 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-55 rssi_max:-51
said: 9 | **LINK** peer:0x00000010 proto:ble n:51 rssi_min:-73 rssi_med:-65 rssi_max:-56
```

---

@LAT105LON4787 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 1380135 ±21 frame:7500
seq: 1431
follows: 0x00000011:1375 0x00000012:1290 0x00000100:1023 0x00000200:2068 0x00000300:4688
said: 1 | **LINKWIN** t_ms:1701874 stream:0xc9e0e898 wall:0 window_ms:60012
said: 2 | **LINK** peer:0x00000011 proto:espnow n:144 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:204 rssi_min:-49 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-80 rssi_med:-60 rssi_max:-56
said: 5 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-57 rssi_med:-55 rssi_max:-53
said: 6 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-59 rssi_med:-57 rssi_max:-56
said: 7 | **LINK** peer:0x00000200 proto:espnow n:161 rssi_min:-52 rssi_med:-50 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-51 rssi_med:-47 rssi_max:-42
said: 9 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-59 rssi_med:-52 rssi_max:-46
```

---

@LAT105LON4788 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 1412913 ±21 frame:7500
seq: 1376
follows: 0x00000010:1431 0x00000012:1290 0x00000100:1024 0x00000200:2068 0x00000300:4688
said: 1 | **LINKWIN** t_ms:1734655 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-67 rssi_med:-61 rssi_max:-59
said: 3 | **LINK** peer:0x00000300 proto:espnow n:205 rssi_min:-59 rssi_med:-56 rssi_max:-53
said: 4 | **LINK** peer:0x00000200 proto:espnow n:136 rssi_min:-51 rssi_med:-45 rssi_max:-45
said: 5 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-82 rssi_med:-63 rssi_max:-55
said: 6 | **LINK** peer:0x00000010 proto:espnow n:95 rssi_min:-41 rssi_med:-35 rssi_max:-33
said: 7 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-51 rssi_max:-47
said: 8 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-60 rssi_max:-56
```

---

@LAT103LON1236 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1423557 ±21 frame:7500
seq: 1291
follows: 0x00000010:1431 0x00000011:1376 0x00000100:1024 0x00000200:2068 0x00000300:4688
said: 1 | **LINKWIN** t_ms:1745302 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:121 rssi_min:-44 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:espnow n:139 rssi_min:-36 rssi_med:-32 rssi_max:-30
said: 4 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000300 proto:espnow n:172 rssi_min:-45 rssi_med:-43 rssi_max:-35
said: 6 | **LINK** peer:0x00000010 proto:espnow n:80 rssi_min:-38 rssi_med:-32 rssi_max:-31
said: 7 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-46 rssi_max:-44
said: 8 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-52 rssi_max:-49
said: 9 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-53 rssi_max:-49
```

---

@LAT105LON4789 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1424177 ±0 frame:7500
seq: 4689
follows: 0x00000010:1431 0x00000011:1376 0x00000012:1291 0x00000100:1024 0x00000200:2068
said: 1 | **LINKWIN** t_ms:1745921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-80 rssi_med:-58 rssi_max:-53
said: 3 | **LINK** peer:0x00000012 proto:espnow n:101 rssi_min:-47 rssi_med:-45 rssi_max:-39
said: 4 | **LINK** peer:0x00000011 proto:espnow n:102 rssi_min:-67 rssi_med:-58 rssi_max:-47
said: 5 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-74 rssi_med:-62 rssi_max:-50
said: 6 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-83 rssi_med:-58 rssi_max:-51
said: 7 | **LINK** peer:0x00000200 proto:espnow n:130 rssi_min:-45 rssi_med:-41 rssi_max:-35
said: 8 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-83 rssi_med:-67 rssi_max:-59
said: 9 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-31 rssi_med:-29 rssi_max:-27
said: 10 | 0x00000011 espnow met predicted:-58 observed:-58
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-45 observed:-45
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow unobserved predicted:-49 observed:-49
percept: 13 | 0x00000010 | link_stable | espnow | ? | -
said: 14 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-66 observed:-67
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-59 observed:-58
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-56 observed:-58
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT105LON4790 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1429682 ±21 frame:7500
seq: 2069
follows: 0x00000010:1431 0x00000011:1376 0x00000012:1291 0x00000100:1024 0x00000300:4690
said: 1 | **LINKWIN** t_ms:1751408 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-37 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:espnow n:211 rssi_min:-40 rssi_med:-37 rssi_max:-33
said: 4 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-36 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000011 proto:espnow n:102 rssi_min:-48 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000010 proto:espnow n:87 rssi_min:-63 rssi_med:-49 rssi_max:-46
said: 7 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-60 rssi_med:-55 rssi_max:-47
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-73 rssi_med:-65 rssi_max:-53
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-51 rssi_max:-50
```

---

@LAT105LON4791 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 1440135 ±21 frame:7500
seq: 1432
follows: 0x00000011:1376 0x00000012:1291 0x00000100:1024 0x00000200:2069 0x00000300:4690
said: 1 | **LINKWIN** t_ms:1761873 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:119 rssi_min:-65 rssi_med:-50 rssi_max:-45
said: 3 | **LINK** peer:0x00000011 proto:espnow n:96 rssi_min:-45 rssi_med:-41 rssi_max:-35
said: 4 | **LINK** peer:0x00000300 proto:espnow n:178 rssi_min:-52 rssi_med:-45 rssi_max:-40
said: 5 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-48 rssi_max:-41
said: 6 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-72 rssi_med:-54 rssi_max:-46
said: 7 | **LINK** peer:0x00000100 proto:espnow n:75 rssi_min:-66 rssi_med:-56 rssi_max:-45
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-79 rssi_med:-60 rssi_max:-53
said: 9 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-36 rssi_med:-32 rssi_max:-29
```

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

@LAT104LON136 | created:0 | updated:0

**carried through @LAT103LON1196**

```ttdb-carried
through: 1196
through: 8227
```

---

@LAT103LON1237 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1483584 ±21 frame:7500
seq: 1293
follows: 0x00000010:1432 0x00000011:1377 0x00000100:1025 0x00000200:2069 0x00000300:4690
said: 1 | **LINKWIN** t_ms:1805331 stream:0xc9e0e898 wall:0 window_ms:60029
said: 2 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-50 rssi_max:-42
said: 3 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-38 rssi_med:-32 rssi_max:-28
said: 4 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-33 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:espnow n:59 rssi_min:-45 rssi_med:-41 rssi_max:-39
said: 6 | **LINK** peer:0x00000300 proto:espnow n:177 rssi_min:-46 rssi_med:-43 rssi_max:-34
said: 7 | **LINK** peer:0x00000200 proto:espnow n:91 rssi_min:-37 rssi_med:-32 rssi_max:-29
said: 8 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-46 rssi_max:-44
said: 9 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-53 rssi_max:-49
```

---

@LAT105LON4792 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 1472913 ±21 frame:7500
seq: 1377
follows: 0x00000010:1432 0x00000012:1291 0x00000100:1025 0x00000200:2069 0x00000300:4690
said: 1 | **LINKWIN** t_ms:1794655 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-43 rssi_med:-36 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:165 rssi_min:-70 rssi_med:-56 rssi_max:-43
said: 4 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-54 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-46 rssi_med:-35 rssi_max:-31
said: 6 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-62 rssi_max:-54
said: 7 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-62 rssi_max:-56
said: 8 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-68 rssi_med:-61 rssi_max:-55
said: 9 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-55 rssi_max:-48
```

---

@LAT105LON4793 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1484177 ±0 frame:7500
seq: 4691
follows: 0x00000010:1432 0x00000011:1377 0x00000012:1292 0x00000100:1025 0x00000200:2069
said: 1 | **LINKWIN** t_ms:1805921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:92 rssi_min:-50 rssi_med:-44 rssi_max:-39
said: 3 | **LINK** peer:0x00000010 proto:espnow n:112 rssi_min:-54 rssi_med:-48 rssi_max:-43
said: 4 | **LINK** peer:0x00000011 proto:espnow n:124 rssi_min:-67 rssi_med:-57 rssi_max:-48
said: 5 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-68 rssi_med:-60 rssi_max:-49
said: 6 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 7 | **LINK** peer:0x00000200 proto:espnow n:87 rssi_min:-49 rssi_med:-42 rssi_max:-40
said: 8 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-82 rssi_med:-59 rssi_max:-53
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-83 rssi_med:-66 rssi_max:-59
said: 10 | 0x00000012 ble met predicted:-58 observed:-59
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000012 espnow met predicted:-45 observed:-44
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-58 observed:-57
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-62 observed:-60
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000200 ble unobserved predicted:-58 observed:-58
percept: 14 | 0x00000200 | link_stable | ble | ? | -
said: 15 | 0x00000200 espnow met predicted:-41 observed:-42
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-67 observed:-66
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 17 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT105LON4794 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1489700 ±21 frame:7500
seq: 2070
follows: 0x00000010:1432 0x00000011:1377 0x00000012:1293 0x00000100:1025 0x00000300:4692
said: 1 | **LINKWIN** t_ms:1811424 stream:0xc9e0e898 wall:0 window_ms:60016
said: 2 | **LINK** peer:0x00000012 proto:espnow n:93 rssi_min:-36 rssi_med:-34 rssi_max:-31
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-38 rssi_med:-35 rssi_max:-33
said: 4 | **LINK** peer:0x00000300 proto:espnow n:199 rssi_min:-52 rssi_med:-38 rssi_max:-35
said: 5 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-52 rssi_med:-48 rssi_max:-44
said: 6 | **LINK** peer:0x00000010 proto:espnow n:117 rssi_min:-69 rssi_med:-50 rssi_max:-47
said: 7 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-52 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-76 rssi_med:-65 rssi_max:-53
said: 9 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-63 rssi_max:-58
```
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

@LAT105LON4795 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 1500144 ±21 frame:7500
seq: 1433
follows: 0x00000011:1377 0x00000012:1293 0x00000100:1025 0x00000200:2070 0x00000300:4692
said: 1 | **LINKWIN** t_ms:1821883 stream:0xc9e0e898 wall:0 window_ms:60009
said: 2 | **LINK** peer:0x00000011 proto:espnow n:131 rssi_min:-44 rssi_med:-40 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-52 rssi_max:-45
said: 4 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-54 rssi_max:-50
said: 5 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-63 rssi_med:-55 rssi_max:-45
said: 6 | **LINK** peer:0x00000300 proto:espnow n:183 rssi_min:-50 rssi_med:-43 rssi_max:-38
said: 7 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-61 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:espnow n:86 rssi_min:-67 rssi_med:-53 rssi_max:-46
said: 9 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-80 rssi_med:-48 rssi_max:-40
```

---

@LAT105LON4796 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 1532913 ±21 frame:7500
seq: 1378
follows: 0x00000010:1433 0x00000012:1293 0x00000100:1025 0x00000200:2070 0x00000300:4692
said: 1 | **LINKWIN** t_ms:1854655 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:118 rssi_min:-43 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000200 proto:espnow n:96 rssi_min:-55 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000300 proto:espnow n:170 rssi_min:-63 rssi_med:-53 rssi_max:-47
said: 5 | **LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-70 rssi_med:-64 rssi_max:-55
said: 6 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-43 rssi_med:-41 rssi_max:-34
said: 7 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-63 rssi_max:-56
said: 8 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-47
said: 9 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-83 rssi_med:-65 rssi_max:-54
```

---

@LAT103LON1238 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1543587 ±21 frame:7500
seq: 1294
follows: 0x00000010:1433 0x00000011:1378 0x00000100:1026 0x00000200:2070 0x00000300:4692
said: 1 | **LINKWIN** t_ms:1865331 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-45 rssi_med:-42 rssi_max:-40
said: 3 | **LINK** peer:0x00000010 proto:espnow n:118 rssi_min:-39 rssi_med:-32 rssi_max:-31
said: 4 | **LINK** peer:0x00000200 proto:espnow n:89 rssi_min:-35 rssi_med:-30 rssi_max:-30
said: 5 | **LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-36 rssi_med:-31 rssi_max:-29
said: 6 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000300 proto:espnow n:148 rssi_min:-48 rssi_med:-44 rssi_max:-40
said: 8 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-82 rssi_med:-53 rssi_max:-50
```

---

@LAT105LON4797 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1544177 ±0 frame:7500
seq: 4693
follows: 0x00000010:1433 0x00000011:1378 0x00000012:1294 0x00000100:1026 0x00000200:2070
said: 1 | **LINKWIN** t_ms:1865921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-62 rssi_max:-49
said: 3 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-53 rssi_med:-47 rssi_max:-43
said: 4 | **LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-50 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000011 proto:espnow n:78 rssi_min:-69 rssi_med:-63 rssi_max:-50
said: 7 | **LINK** peer:0x00000011 proto:ble n:52 rssi_min:-83 rssi_med:-63 rssi_max:-58
said: 8 | **LINK** peer:0x00000200 proto:espnow n:109 rssi_min:-48 rssi_med:-45 rssi_max:-41
said: 9 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-80 rssi_med:-58 rssi_max:-55
said: 10 | 0x00000012 espnow met predicted:-44 observed:-47
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-48 observed:-47
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-57 observed:-63
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-60 observed:-62
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-42 observed:-45
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-59 observed:-58
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-66 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT105LON4798 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 1560145 ±21 frame:7500
seq: 1434
follows: 0x00000011:1378 0x00000012:1294 0x00000100:1026 0x00000200:2071 0x00000300:4694
said: 1 | **LINKWIN** t_ms:1881883 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:90 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 4 | **LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 5 | **LINK** peer:0x00000200 proto:espnow n:96 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 6 | **LINK** peer:0x00000300 proto:espnow n:161 rssi_min:-46 rssi_med:-43 rssi_max:-43
said: 7 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-53 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-48 rssi_max:-42
said: 9 | **LINK** peer:0x00000012 proto:espnow n:90 rssi_min:-35 rssi_med:-32 rssi_max:-30
```

---

@LAT105LON4799 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1549703 ±21 frame:7500
seq: 2071
follows: 0x00000010:1433 0x00000011:1378 0x00000012:1294 0x00000100:1026 0x00000300:4694
said: 1 | **LINKWIN** t_ms:1871426 stream:0xc9e0e898 wall:0 window_ms:60002
said: 2 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-45 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000010 proto:espnow n:118 rssi_min:-58 rssi_med:-48 rssi_max:-45
said: 4 | **LINK** peer:0x00000012 proto:espnow n:79 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 5 | **LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-37 rssi_med:-36 rssi_max:-35
said: 6 | **LINK** peer:0x00000011 proto:espnow n:94 rssi_min:-50 rssi_med:-46 rssi_max:-45
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-79 rssi_med:-63 rssi_max:-54
said: 8 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-79 rssi_med:-58 rssi_max:-50
said: 9 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-55 rssi_med:-50 rssi_max:-49
```

---

@LAT103LON1239 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1603586 ±21 frame:7500
seq: 1295
follows: 0x00000010:1434 0x00000011:1379 0x00000100:1027 0x00000200:2071 0x00000300:4694
said: 1 | **LINKWIN** t_ms:1925331 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000200 proto:espnow n:73 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 4 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000300 proto:espnow n:172 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:espnow n:96 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000010 proto:espnow n:99 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 8 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 9 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-53 rssi_max:-52
```

---

@LAT105LON4800 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1604177 ±0 frame:7500
seq: 4695
follows: 0x00000010:1434 0x00000011:1379 0x00000012:1295 0x00000100:1027 0x00000200:2071
said: 1 | **LINKWIN** t_ms:1925921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-48 rssi_med:-47 rssi_max:-45
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-60 rssi_max:-54
said: 4 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-81 rssi_med:-58 rssi_max:-55
said: 5 | **LINK** peer:0x00000011 proto:espnow n:117 rssi_min:-68 rssi_med:-64 rssi_max:-60
said: 6 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000200 proto:espnow n:73 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-62 rssi_max:-50
said: 9 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-63 rssi_max:-58
said: 10 | 0x00000010 ble met predicted:-62 observed:-62
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow unobserved predicted:-47 observed:-47
percept: 13 | 0x00000010 | link_stable | espnow | ? | -
said: 14 | 0x00000011 espnow met predicted:-63 observed:-64
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-63 observed:-63
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-58 observed:-58
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT105LON4801 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 1592915 ±21 frame:7500
seq: 1379
follows: 0x00000010:1434 0x00000012:1294 0x00000100:1026 0x00000200:2071 0x00000300:4694
said: 1 | **LINKWIN** t_ms:1914655 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-58 rssi_max:-54
said: 3 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-51 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:espnow n:82 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-41 rssi_med:-36 rssi_max:-35
said: 6 | **LINK** peer:0x00000010 proto:espnow n:116 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-54 rssi_max:-51
said: 8 | **LINK** peer:0x00000300 proto:espnow n:183 rssi_min:-64 rssi_med:-59 rssi_max:-57
said: 9 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-62 rssi_max:-59
```

---

@LAT105LON4802 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1609704 ±21 frame:7500
seq: 2072
follows: 0x00000010:1434 0x00000011:1379 0x00000012:1295 0x00000100:1027 0x00000300:4696
said: 1 | **LINKWIN** t_ms:1931426 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-71 rssi_med:-58 rssi_max:-50
said: 3 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-37 rssi_med:-36 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:espnow n:153 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 5 | **LINK** peer:0x00000011 proto:espnow n:101 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 6 | **LINK** peer:0x00000012 proto:espnow n:107 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 8 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-63 rssi_med:-63 rssi_max:-61
said: 9 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-80 rssi_med:-63 rssi_max:-54
```

---

@LAT105LON4803 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 1620907 ±21 frame:7500
seq: 1435
follows: 0x00000011:1379 0x00000012:1295 0x00000100:1027 0x00000200:2072 0x00000300:4696
said: 1 | **LINKWIN** t_ms:1940852 stream:0xc9e0e898 wall:0 window_ms:60761
said: 2 | **LINK** peer:0x00000200 proto:espnow n:73 rssi_min:-49 rssi_med:-49 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:137 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-77 rssi_med:-48 rssi_max:-42
said: 5 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-73 rssi_med:-55 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-53 rssi_max:-46
said: 7 | **LINK** peer:0x00000011 proto:espnow n:110 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 8 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 9 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-36 rssi_med:-32 rssi_max:-31
```

---

@LAT103LON1240 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1663587 ±21 frame:7500
seq: 1296
follows: 0x00000010:1435 0x00000011:1380 0x00000100:1028 0x00000200:2072 0x00000300:4696
said: 1 | **LINKWIN** t_ms:1985331 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-53 rssi_max:-52
said: 3 | **LINK** peer:0x00000011 proto:espnow n:64 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 4 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-36 rssi_med:-31 rssi_max:-31
said: 5 | **LINK** peer:0x00000010 proto:espnow n:155 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 6 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 8 | **LINK** peer:0x00000300 proto:espnow n:164 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 9 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-45 rssi_max:-44
```

---

@LAT105LON4804 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 1652915 ±21 frame:7500
seq: 1380
follows: 0x00000010:1435 0x00000012:1295 0x00000100:1027 0x00000200:2072 0x00000300:4696
said: 1 | **LINKWIN** t_ms:1974655 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 3 | **LINK** peer:0x00000300 proto:espnow n:157 rssi_min:-64 rssi_med:-60 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 5 | **LINK** peer:0x00000012 proto:espnow n:112 rssi_min:-41 rssi_med:-36 rssi_max:-35
said: 6 | **LINK** peer:0x00000010 proto:espnow n:133 rssi_min:-42 rssi_med:-35 rssi_max:-33
said: 7 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-62 rssi_max:-59
said: 8 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-58 rssi_max:-54
said: 9 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-54 rssi_max:-51
```

---

@LAT105LON4805 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1664177 ±0 frame:7500
seq: 4697
follows: 0x00000010:1435 0x00000011:1380 0x00000012:1296 0x00000100:1028 0x00000200:2072
said: 1 | **LINKWIN** t_ms:1985921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:91 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 3 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-83 rssi_med:-62 rssi_max:-50
said: 5 | **LINK** peer:0x00000011 proto:espnow n:60 rssi_min:-68 rssi_med:-63 rssi_max:-61
said: 6 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000010 proto:espnow n:169 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 8 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-60 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-64 rssi_med:-58 rssi_max:-56
said: 10 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-60 observed:-60
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000012 ble met predicted:-58 observed:-58
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000011 espnow met predicted:-64 observed:-63
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-62 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000011 ble unobserved predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | ? | -
```
