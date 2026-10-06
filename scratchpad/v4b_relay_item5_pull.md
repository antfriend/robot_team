# V4-B Relay Node TTDB

```mmpdb
db_id: v4b-relay-001
db_name: V4-B Relay Node
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: v4b-relay
  role: store-and-forward
  perspective: spine-mid
  scope: long-hops
  constraints:
    - solar-powered
    - external-antenna
  globe:
    frame: mesh-topology
    origin: "@LAT0LON20"
    mapping: "midpoint of the A-B-C spine on the knowledge grid"
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
lon: 20
```

---

@LAT0LON20 | created:1750000000 | updated:1750000000 | relates:navigates_to@LAT0LON10,navigates_to@LAT0LON30

Relay home. Forwards between V4-A (lon 10) and V4-C (lon 30); decrements ttl and
dedups on (src,seq).

---

@LAT99LON0 | created:1782429925 | updated:1782429925 | relates:logs@LAT0LON0

**SYNC** id:3 t_ms:1782429925125 recv_ms:45601 offset_ms:1782429879524

---

@LAT99LON1 | created:1782430029 | updated:1782430029 | relates:logs@LAT0LON0

**SYNC** id:4 t_ms:1782430029108 recv_ms:149590 offset_ms:1782429879518

---

@LAT98LON0 | created:1782430070 | updated:1782430070 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:9 bytes:1373 crc:9EFD9530 recv_ms:191382

---

@LAT99LON2 | created:1783367393 | updated:1783367393 | relates:logs@LAT0LON0

**SYNC** id:5 t_ms:1783367393574 recv_ms:249323 offset_ms:1783367144251

---


---


---


---


---


---


---


---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:832981 stream:0xbdc62024 wall:0 node:0x00000011

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:1 removed:16 last_lon:15 t_ms:338331 stream:0x0445bfe4 wall:0 node:0x00000011
**STREAMS-EXPLAINED** n:15 0x59fb8ce8 0xbdc62024 0xe7384824 0xaf869fce 0xdffbae31 0xbe8a1293 0xbce80555 0x66486d22 0x95cc309e 0x0870722b 0xbeb39900 0x1de72b4d 0x498c31b1 0x3a7a2eb0 0xbb1177f2

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:48 last_lon:47 t_ms:0 stream:0x00000000 wall:0 node:0x00000011

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x0445bfe4 wall:0 t_ms:343786 node:0x11 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:2 removed:48 last_lon:47 t_ms:344934 stream:0x0445bfe4 wall:0 node:0x00000011

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x7d224c73 wall:0 t_ms:13491 node:0x11 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xb23c7677 wall:0 t_ms:10990 node:0x11 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x5b53f35b wall:0 t_ms:11182 node:0x11 from:0x10
**REMAP** prev_stream:0xe76e28cc prev_t_ms:4587 offset_ms:6595 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xdcd3edce wall:0 t_ms:8089198 node:0x11 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xdcd3edce wall:0 t_ms:8177519 node:0x11 from:0x300
**REMAP** prev_stream:0x1907c98c prev_t_ms:3815 offset_ms:8173704 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xee98fca8 wall:0 t_ms:4426440 node:0x11 from:0x300
**REMAP** prev_stream:0xef8c54a9 prev_t_ms:23910 offset_ms:4402530 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xc909d5a8 wall:0 t_ms:144695 node:0x11 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:3 removed:36 last_lon:35 t_ms:3387283 stream:0xc909d5a8 wall:0 node:0x00000011

---

@LAT100LON5 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:2 removed:7 last_lon:6 t_ms:3395371 stream:0xc909d5a8 wall:0 node:0x00000011

---

@LAT103LON8237 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11019804 ±21 frame:20500
seq: 654
follows: 0x00000010:719 0x00000012:565 0x00000100:732 0x00000200:1340 0x00000300:3300
said: 1 | **ENTWIN** t_ms:11003602 stream:0xa0be1a79 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-97
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,5ce28c488e0c,84a329c78fec,64677217947d
said: 12 | **COVERED** windows:2 entities:9 window_ms:1200034 first_t_ms:9803602 last_t_ms:10403602 covered_by:@LAT103LON8236
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-35 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-73 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-74 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-84 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-90 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-91 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-92 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-97 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
```

---

@LAT103LON8238 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12819818 ±21 frame:20500
seq: 685
follows: 0x00000010:752 0x00000012:595 0x00000100:732 0x00000200:1370 0x00000300:3364
said: 1 | **ENTWIN** t_ms:12803602 stream:0xa0be1a79 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,84a329c78fec,5ce28c488e0c,0283cce0e689
said: 12 | **COVERED** windows:2 entities:10 window_ms:1199999 first_t_ms:11603602 last_t_ms:12203601 covered_by:@LAT103LON8237
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-42 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-73 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-72 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-82 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-87 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-91 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-92 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-93 windows:2
```

---

@LAT103LON8239 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13419824 ±21 frame:20500
seq: 696
follows: 0x00000010:762 0x00000012:605 0x00000100:732 0x00000200:1380 0x00000300:3386
said: 1 | **ENTWIN** t_ms:13403653 stream:0xa0be1a79 wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c,0283cce0e689
```

---

@LAT103LON8240 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 14619834 ±21 frame:20500
seq: 717
follows: 0x00000010:784 0x00000012:626 0x00000100:732 0x00000200:1401 0x00000300:3427
said: 1 | **ENTWIN** t_ms:14603654 stream:0xa0be1a79 wall:0 window_ms:600001 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,0283cce0e689,64677217947d
said: 10 | **COVERED** windows:1 entities:8 window_ms:600000 first_t_ms:14003653 last_t_ms:14003653 covered_by:@LAT103LON8239
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
```

---

@LAT103LON8241 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 15819840 ±21 frame:20500
seq: 738
follows: 0x00000010:803 0x00000012:647 0x00000100:732 0x00000200:1421 0x00000300:3468
said: 1 | **ENTWIN** t_ms:15803653 stream:0xa0be1a79 wall:0 window_ms:600001 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d
said: 11 | **COVERED** windows:1 entities:8 window_ms:599998 first_t_ms:15203653 last_t_ms:15203653 covered_by:@LAT103LON8240
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1
```

---

@LAT103LON8242 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 16419847 ±21 frame:20500
seq: 749
follows: 0x00000010:813 0x00000012:657 0x00000100:732 0x00000200:1431 0x00000300:3488
said: 1 | **ENTWIN** t_ms:16403653 stream:0xa0be1a79 wall:0 window_ms:599999 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON8243 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 17019853 ±21 frame:20500
seq: 760
follows: 0x00000010:824 0x00000012:668 0x00000100:732 0x00000200:1441 0x00000300:3509
said: 1 | **ENTWIN** t_ms:17003653 stream:0xa0be1a79 wall:0 window_ms:600001 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace
```

---

@LAT103LON8244 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 17619856 ±21 frame:20500
seq: 771
follows: 0x00000010:834 0x00000012:678 0x00000100:732 0x00000200:1451 0x00000300:3529
said: 1 | **ENTWIN** t_ms:17603653 stream:0xa0be1a79 wall:0 window_ms:599999 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec
```

---

@LAT103LON8245 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 18134218 ±21 frame:20500
seq: 779
follows: 0x00000010:844 0x00000012:687 0x00000100:732 0x00000200:1461 0x00000300:3548
said: 1 | **ENTWIN** t_ms:18118005 stream:0xa0be1a79 wall:0 window_ms:60044 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8246 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 19304942 ±21 frame:20500
seq: 799
follows: 0x00000010:863 0x00000012:706 0x00000100:732 0x00000200:1481 0x00000300:3588
said: 1 | **ENTWIN** t_ms:19286761 stream:0xa0be1a79 wall:0 window_ms:601545 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 12 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,0283cce0e689
said: 13 | **COVERED** windows:1 entities:8 window_ms:569168 first_t_ms:18685216 last_t_ms:18685216 covered_by:@LAT103LON8245
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95 windows:1
```

---

@LAT103LON8247 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 19905041 ±21 frame:20500
seq: 810
follows: 0x00000010:874 0x00000012:717 0x00000100:732 0x00000200:1491 0x00000300:3608
said: 1 | **ENTWIN** t_ms:19886856 stream:0xa0be1a79 wall:0 window_ms:600095 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 14 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,c2e94427adcf,0283cce0e689
```

---

@LAT103LON8248 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 20442147 ±21 frame:20500
seq: 820
follows: 0x00000010:883 0x00000012:726 0x00000100:732 0x00000200:1500 0x00000300:3626
said: 1 | **ENTWIN** t_ms:20425897 stream:0xa0be1a79 wall:0 window_ms:60081 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8249 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21613831 ±21 frame:20500
seq: 840
follows: 0x00000010:902 0x00000012:746 0x00000100:732 0x00000200:1519 0x00000300:3669
said: 1 | **ENTWIN** t_ms:21595651 stream:0xa0be1a79 wall:0 window_ms:602478 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 12 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,e6b32d2cea8b
said: 13 | **COVERED** windows:1 entities:9 window_ms:569196 first_t_ms:20993173 last_t_ms:20993173 covered_by:@LAT103LON8248
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95 windows:1
```

---

@LAT103LON8250 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 22213881 ±21 frame:20500
seq: 851
follows: 0x00000010:913 0x00000012:757 0x00000100:732 0x00000200:1529 0x00000300:3688
said: 1 | **ENTWIN** t_ms:22195695 stream:0xa0be1a79 wall:0 window_ms:600044 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,84a329c78fec,e6b32d2cea8b,64677217947d
```

---

@LAT103LON8251 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 22814093 ±21 frame:20500
seq: 862
follows: 0x00000010:923 0x00000012:767 0x00000100:732 0x00000200:1540 0x00000300:3710
said: 1 | **ENTWIN** t_ms:22795903 stream:0xa0be1a79 wall:0 window_ms:600208 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689,c2e94427adcf,84a329c78fec,64677217947d
```

---

@LAT103LON8252 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 24614192 ±21 frame:20500
seq: 893
follows: 0x00000010:954 0x00000012:798 0x00000100:732 0x00000200:1572 0x00000300:3772
said: 1 | **ENTWIN** t_ms:24595986 stream:0xa0be1a79 wall:0 window_ms:602022 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96
said: 11 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c,c2e94427adcf,0283cce0e689
said: 13 | **COVERED** windows:2 entities:11 window_ms:1198061 first_t_ms:23395936 last_t_ms:23995964 covered_by:@LAT103LON8251
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-35 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-68 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-81 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-81 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-85 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-89 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-91 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
```

---

@LAT103LON8253 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 25214272 ±21 frame:20500
seq: 904
follows: 0x00000010:964 0x00000012:808 0x00000100:732 0x00000200:1582 0x00000300:3793
said: 1 | **ENTWIN** t_ms:25196061 stream:0xa0be1a79 wall:0 window_ms:600075 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,64677217947d,c2e94427adcf,980d67f79619
```

---

@LAT103LON8254 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 27012288 ±21 frame:20500
seq: 935
follows: 0x00000010:995 0x00000012:839 0x00000100:732 0x00000200:1614 0x00000300:3858
said: 1 | **ENTWIN** t_ms:26996113 stream:0xa0be1a79 wall:0 window_ms:600003 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-96
said: 12 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,84a329c78fec,e6b32d2cea8b,bc102f237ace,980d67f79619,0283cce0e689,e45e1b9f675a,64677217947d,c2e94427adcf
said: 14 | **COVERED** windows:2 entities:11 window_ms:1197998 first_t_ms:25796061 last_t_ms:26396111 covered_by:@LAT103LON8253
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-33 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-65 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-78 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-87 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-87 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-88 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-91 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-91 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:2 rssi:-91 windows:2
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:e45e1b9f675a n:2 rssi:-94 windows:2
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95 windows:1
```

---

@LAT103LON8255 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 27613812 ±21 frame:20500
seq: 946
follows: 0x00000010:1006 0x00000012:850 0x00000100:732 0x00000200:1625 0x00000300:3878
said: 1 | **ENTWIN** t_ms:27597633 stream:0xa0be1a79 wall:0 window_ms:601520 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,e6b32d2cea8b,980d67f79619,0283cce0e689,e45e1b9f675a,64677217947d
```

---

@LAT103LON8256 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 28213818 ±21 frame:20500
seq: 957
follows: 0x00000010:1016 0x00000012:860 0x00000100:732 0x00000200:1635 0x00000300:3899
said: 1 | **ENTWIN** t_ms:28197634 stream:0xa0be1a79 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,e6b32d2cea8b,0283cce0e689,980d67f79619,e45e1b9f675a
```

---

@LAT103LON8257 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 28813823 ±21 frame:20500
seq: 968
follows: 0x00000010:1026 0x00000012:871 0x00000100:732 0x00000200:1646 0x00000300:3919
said: 1 | **ENTWIN** t_ms:28797633 stream:0xa0be1a79 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689,84a329c78fec
```

---

@LAT103LON8258 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 30013832 ±21 frame:20500
seq: 989
follows: 0x00000010:1047 0x00000012:890 0x00000100:732 0x00000200:1668 0x00000300:3961
said: 1 | **ENTWIN** t_ms:29997633 stream:0xa0be1a79 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,0283cce0e689,c2e94427adcf
said: 14 | **COVERED** windows:1 entities:8 window_ms:600000 first_t_ms:29397633 last_t_ms:29397633 covered_by:@LAT103LON8257
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95 windows:1
```

---

@LAT103LON8259 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 30613837 ±21 frame:20500
seq: 1000
follows: 0x00000010:1057 0x00000012:900 0x00000100:732 0x00000200:1678 0x00000300:3981
said: 1 | **ENTWIN** t_ms:30597634 stream:0xa0be1a79 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,980d67f79619,0283cce0e689,c2e94427adcf
```

---

@LAT103LON8260 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31213843 ±21 frame:20500
seq: 1011
follows: 0x00000010:1068 0x00000012:911 0x00000100:732 0x00000200:1689 0x00000300:4001
said: 1 | **ENTWIN** t_ms:31197633 stream:0xa0be1a79 wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,bc102f237ace,980d67f79619,0283cce0e689
```

---

@LAT103LON8261 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31813849 ±21 frame:20500
seq: 1022
follows: 0x00000010:1079 0x00000012:921 0x00000100:732 0x00000200:1699 0x00000300:4022
said: 1 | **ENTWIN** t_ms:31797634 stream:0xa0be1a79 wall:0 window_ms:600001 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,980d67f79619,e6b32d2cea8b,bc102f237ace
```

---

@LAT103LON8262 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 32413877 ±21 frame:20500
seq: 1033
follows: 0x00000010:1089 0x00000012:931 0x00000100:732 0x00000200:1711 0x00000300:4043
said: 1 | **ENTWIN** t_ms:32397658 stream:0xa0be1a79 wall:0 window_ms:600024 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,e6b32d2cea8b,c2e94427adcf,980d67f79619
```

---

@LAT103LON8263 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 33013905 ±21 frame:20500
seq: 1044
follows: 0x00000010:1100 0x00000012:941 0x00000100:732 0x00000200:1722 0x00000300:4063
said: 1 | **ENTWIN** t_ms:32997731 stream:0xa0be1a79 wall:0 window_ms:600022 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-98
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,64677217947d,c2e94427adcf,e6b32d2cea8b,980d67f79619
```

---

@LAT103LON8264 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 33613911 ±21 frame:20500
seq: 1055
follows: 0x00000010:1110 0x00000012:951 0x00000100:732 0x00000200:1732 0x00000300:4085
said: 1 | **ENTWIN** t_ms:33597733 stream:0xa0be1a79 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,980d67f79619,84a329c78fec,64677217947d,c2e94427adcf
```

---

@LAT103LON8265 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34483875 ±21 frame:20500
seq: 1070
follows: 0x00000010:1125 0x00000012:966 0x00000100:732 0x00000200:1746 0x00000300:4114
said: 1 | **ENTWIN** t_ms:34465617 stream:0xa0be1a79 wall:0 window_ms:62075 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8266 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 35652041 ±21 frame:20500
seq: 1090
follows: 0x00000010:1144 0x00000012:986 0x00000100:732 0x00000200:1768 0x00000300:4157
said: 1 | **ENTWIN** t_ms:35635865 stream:0xa0be1a79 wall:0 window_ms:600033 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-96
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,bc102f237ace
said: 11 | **COVERED** windows:1 entities:9 window_ms:568122 first_t_ms:35035832 last_t_ms:35035832 covered_by:@LAT103LON8265
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
```

---

@LAT103LON8267 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36252058 ±25 frame:20500
seq: 1101
follows: 0x00000010:1155 0x00000012:998 0x00000100:732 0x00000200:1778 0x00000300:4174
said: 1 | **ENTWIN** t_ms:36235879 stream:0xa0be1a79 wall:0 window_ms:600014 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,c2e94427adcf
```

---

@LAT103LON8268 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 37452071 ±21 frame:20500
seq: 1122
follows: 0x00000010:1177 0x00000012:1019 0x00000100:732 0x00000200:1799 0x00000300:4210
said: 1 | **ENTWIN** t_ms:37435890 stream:0xa0be1a79 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,c2e94427adcf
said: 11 | **COVERED** windows:1 entities:7 window_ms:600012 first_t_ms:36835891 last_t_ms:36835891 covered_by:@LAT103LON8267
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
```

---

@LAT103LON8269 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 38212802 ±21 frame:20500
seq: 1133
follows: 0x00000010:1183 0x00000012:1033 0x00000100:732 0x00000200:1811 0x00000300:4214
said: 1 | **ENTWIN** t_ms:38196602 stream:0xa0be1a79 wall:0 window_ms:60038 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8270 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 679462 ±21 frame:10000
seq: 1135
follows: 0x00000010:1186 0x00000012:1036 0x00000100:743 0x00000200:1831 0x00000300:4218
said: 1 | **ENTWIN** t_ms:995090 stream:0x364dd329 wall:0 window_ms:60336 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON8271 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 85724 ±21 frame:8000
seq: 1143
follows: 0x00000010:1192 0x00000012:1044 0x00000100:751 0x00000200:1840 0x00000300:4236
said: 1 | **ENTWIN** t_ms:75012 stream:0x732acba3 wall:0 window_ms:60045 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8272 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1242338 ±21 frame:8000
seq: 1163
follows: 0x00000010:1212 0x00000012:1065 0x00000100:772 0x00000200:1860 0x00000300:4275
said: 1 | **ENTWIN** t_ms:1231661 stream:0x732acba3 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 12 | **COVERED** windows:1 entities:6 window_ms:556605 first_t_ms:631661 last_t_ms:631661 covered_by:@LAT103LON8271
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
```

---

@LAT103LON8273 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1842345 ±21 frame:8000
seq: 1174
follows: 0x00000010:1223 0x00000012:1076 0x00000100:783 0x00000200:1871 0x00000300:4296
said: 1 | **ENTWIN** t_ms:1831662 stream:0x732acba3 wall:0 window_ms:600001 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT106LON112 | created:0 | updated:0

**BAR** frame:8000 bar:8 own:10 held:40 terms:9 digest:0x6cf5f785 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1268 hi:1278 sum:12734
**HOLDS** agent:0x00000011 n:10 lo:1214 hi:1223 sum:12185
**HOLDS** agent:0x00000012 n:10 lo:1118 hi:1128 sum:11234
**HOLDS** agent:0x00000200 n:10 lo:1913 hi:1922 sum:19175
**HOLDS** agent:0x00000300 n:10 lo:4377 hi:4395 sum:43860
**DELIVER** up_s:5084 heap:119944 fetched:340 unanswered:231 broken:57 resumed:1140 empty:165 served:1270 wants:1284 early:54 wantq_drop:0 superseded:0

---

@LAT103LON8274 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5442381 ±21 frame:8000
seq: 1235
follows: 0x00000010:1290 0x00000012:1140 0x00000100:849 0x00000200:1933 0x00000300:4419
said: 1 | **ENTWIN** t_ms:5431665 stream:0x732acba3 wall:0 window_ms:600004 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:6 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,64677217947d
said: 13 | **COVERED** windows:5 entities:10 window_ms:2999999 first_t_ms:2431661 last_t_ms:4831661 covered_by:@LAT103LON8273
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-43 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-62 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-69 windows:5
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-80 windows:5
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-85 windows:5
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:5 rssi:-91 windows:5
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-90 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94 windows:1
```

---

@LAT106LON113 | created:0 | updated:0

**BAR** frame:8000 bar:9 own:10 held:40 terms:9 digest:0x30d90ae0 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1279 hi:1289 sum:12844
**HOLDS** agent:0x00000011 n:10 lo:1224 hi:1233 sum:12285
**HOLDS** agent:0x00000012 n:10 lo:1129 hi:1139 sum:11344
**HOLDS** agent:0x00000200 n:10 lo:1924 hi:1933 sum:19285
**HOLDS** agent:0x00000300 n:10 lo:4397 hi:4416 sum:44069
**DELIVER** up_s:5689 heap:120436 fetched:379 unanswered:267 broken:62 resumed:1279 empty:182 served:1450 wants:1467 early:54 wantq_drop:0 superseded:0

---

@LAT103LON8275 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6042384 ±21 frame:8000
seq: 1246
follows: 0x00000010:1300 0x00000012:1151 0x00000100:861 0x00000200:1943 0x00000300:4438
said: 1 | **ENTWIN** t_ms:6031715 stream:0x732acba3 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,0283cce0e689,5ce28c488e0c,bc102f237ace
```

---

@LAT106LON114 | created:0 | updated:0

**BAR** frame:8000 bar:10 own:10 held:40 terms:9 digest:0x40588064 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1290 hi:1300 sum:12954
**HOLDS** agent:0x00000011 n:10 lo:1234 hi:1244 sum:12394
**HOLDS** agent:0x00000012 n:10 lo:1140 hi:1150 sum:11454
**HOLDS** agent:0x00000200 n:10 lo:1934 hi:1943 sum:19385
**HOLDS** agent:0x00000300 n:10 lo:4418 hi:4437 sum:44278
**DELIVER** up_s:6284 heap:122900 fetched:421 unanswered:288 broken:65 resumed:1389 empty:201 served:1612 wants:1631 early:54 wantq_drop:1 superseded:0

---

@LAT106LON115 | created:0 | updated:0

**BAR** frame:8000 bar:11 own:10 held:40 terms:9 digest:0xa1cf7219 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1301 hi:1311 sum:13064
**HOLDS** agent:0x00000011 n:10 lo:1245 hi:1255 sum:12504
**HOLDS** agent:0x00000012 n:10 lo:1151 hi:1161 sum:11564
**HOLDS** agent:0x00000200 n:10 lo:1944 hi:1953 sum:19485
**HOLDS** agent:0x00000300 n:10 lo:4439 hi:4457 sum:44480
**DELIVER** up_s:6888 heap:120204 fetched:459 unanswered:313 broken:70 resumed:1522 empty:221 served:1755 wants:1774 early:54 wantq_drop:1 superseded:0

---

@LAT106LON116 | created:0 | updated:0

**BAR** frame:8000 bar:12 own:10 held:40 terms:9 digest:0x9c7c5137 settled_ms:300020
**HOLDS** agent:0x00000010 n:10 lo:1312 hi:1322 sum:13174
**HOLDS** agent:0x00000011 n:10 lo:1256 hi:1265 sum:12605
**HOLDS** agent:0x00000012 n:10 lo:1162 hi:1171 sum:11665
**HOLDS** agent:0x00000200 n:10 lo:1954 hi:1963 sum:19585
**HOLDS** agent:0x00000300 n:10 lo:4459 hi:4477 sum:44680
**DELIVER** up_s:7488 heap:120416 fetched:500 unanswered:335 broken:76 resumed:1664 empty:240 served:1939 wants:1958 early:54 wantq_drop:1 superseded:0

---

@LAT106LON117 | created:0 | updated:0

**BAR** frame:8000 bar:13 own:10 held:40 terms:9 digest:0x45949f72 settled_ms:300016
**HOLDS** agent:0x00000010 n:10 lo:1323 hi:1332 sum:13275
**HOLDS** agent:0x00000011 n:10 lo:1266 hi:1275 sum:12705
**HOLDS** agent:0x00000012 n:10 lo:1172 hi:1182 sum:11774
**HOLDS** agent:0x00000200 n:10 lo:1964 hi:1973 sum:19685
**HOLDS** agent:0x00000300 n:10 lo:4479 hi:4499 sum:44897
**DELIVER** up_s:8088 heap:120448 fetched:539 unanswered:375 broken:84 resumed:1804 empty:256 served:2130 wants:2149 early:54 wantq_drop:1 superseded:0

---

@LAT106LON118 | created:0 | updated:0

**BAR** frame:8000 bar:14 own:10 held:40 terms:9 digest:0x4b93e0ea settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1333 hi:1342 sum:13375
**HOLDS** agent:0x00000011 n:10 lo:1276 hi:1285 sum:12805
**HOLDS** agent:0x00000012 n:10 lo:1183 hi:1193 sum:11884
**HOLDS** agent:0x00000200 n:10 lo:1975 hi:1984 sum:19795
**HOLDS** agent:0x00000300 n:10 lo:4501 hi:4520 sum:45109
**DELIVER** up_s:8687 heap:120452 fetched:579 unanswered:406 broken:90 resumed:1919 empty:274 served:2288 wants:2307 early:54 wantq_drop:1 superseded:0

---

@LAT103LON8276 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9042442 ±21 frame:8000
seq: 1297
follows: 0x00000010:1354 0x00000012:1205 0x00000100:917 0x00000200:1994 0x00000300:4544
said: 1 | **ENTWIN** t_ms:9031744 stream:0x732acba3 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 10 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,5ce28c488e0c
said: 12 | **COVERED** windows:4 entities:10 window_ms:2400029 first_t_ms:6631744 last_t_ms:8431744 covered_by:@LAT103LON8275
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-42 windows:4
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-63 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-69 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-83 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-87 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:3 rssi:-91 windows:3
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-92 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:3 rssi:-92 windows:3
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-92 windows:2
```

---

@LAT106LON119 | created:0 | updated:0

**BAR** frame:8000 bar:15 own:10 held:40 terms:9 digest:0x033334fc settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1343 hi:1353 sum:13484
**HOLDS** agent:0x00000011 n:10 lo:1286 hi:1295 sum:12905
**HOLDS** agent:0x00000012 n:10 lo:1194 hi:1204 sum:11994
**HOLDS** agent:0x00000200 n:10 lo:1985 hi:1994 sum:19895
**HOLDS** agent:0x00000300 n:10 lo:4522 hi:4541 sum:45319
**DELIVER** up_s:9288 heap:123384 fetched:621 unanswered:428 broken:99 resumed:2057 empty:292 served:2473 wants:2494 early:54 wantq_drop:1 superseded:0

---

@LAT106LON120 | created:0 | updated:0

**BAR** frame:8000 bar:16 own:10 held:40 terms:9 digest:0x8fff28fa settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1354 hi:1364 sum:13594
**HOLDS** agent:0x00000011 n:10 lo:1296 hi:1306 sum:13014
**HOLDS** agent:0x00000012 n:10 lo:1205 hi:1215 sum:12104
**HOLDS** agent:0x00000200 n:10 lo:1995 hi:2004 sum:19995
**HOLDS** agent:0x00000300 n:10 lo:4543 hi:4562 sum:45528
**DELIVER** up_s:9887 heap:123204 fetched:660 unanswered:459 broken:107 resumed:2191 empty:306 served:2602 wants:2623 early:54 wantq_drop:1 superseded:0

---

@LAT106LON121 | created:0 | updated:0

**BAR** frame:8000 bar:17 own:10 held:40 terms:9 digest:0x5345e039 settled_ms:300034
**HOLDS** agent:0x00000010 n:10 lo:1365 hi:1374 sum:13695
**HOLDS** agent:0x00000011 n:10 lo:1307 hi:1316 sum:13115
**HOLDS** agent:0x00000012 n:10 lo:1216 hi:1226 sum:12214
**HOLDS** agent:0x00000200 n:10 lo:2005 hi:2014 sum:20095
**HOLDS** agent:0x00000300 n:10 lo:4564 hi:4582 sum:45730
**DELIVER** up_s:10488 heap:122344 fetched:701 unanswered:480 broken:115 resumed:2339 empty:326 served:2753 wants:2774 early:54 wantq_drop:1 superseded:0

---

@LAT103LON8277 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10842475 ±22 frame:8000
seq: 1328
follows: 0x00000010:1384 0x00000012:1238 0x00000100:949 0x00000200:2024 0x00000300:4603
said: 1 | **ENTWIN** t_ms:10831762 stream:0x732acba3 wall:0 window_ms:599998 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,5ce28c488e0c,e6b32d2cea8b,0283cce0e689
said: 11 | **COVERED** windows:2 entities:8 window_ms:1200019 first_t_ms:9631762 last_t_ms:10231763 covered_by:@LAT103LON8276
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-44 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-63 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-70 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-82 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-89 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-92 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-92 windows:2
```

---

@LAT106LON122 | created:0 | updated:0

**BAR** frame:8000 bar:18 own:10 held:40 terms:9 digest:0xabc37525 settled_ms:300010
**HOLDS** agent:0x00000010 n:10 lo:1375 hi:1384 sum:13795
**HOLDS** agent:0x00000011 n:10 lo:1317 hi:1326 sum:13215
**HOLDS** agent:0x00000012 n:10 lo:1227 hi:1237 sum:12324
**HOLDS** agent:0x00000200 n:10 lo:2015 hi:2024 sum:20195
**HOLDS** agent:0x00000300 n:10 lo:4584 hi:4602 sum:45930
**DELIVER** up_s:11086 heap:120708 fetched:738 unanswered:505 broken:127 resumed:2472 empty:347 served:2885 wants:2910 early:54 wantq_drop:1 superseded:0

---

@LAT103LON8278 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11440471 ±22 frame:8000
seq: 1339
follows: 0x00000010:1396 0x00000012:1249 0x00000100:960 0x00000200:2035 0x00000300:4624
said: 1 | **ENTWIN** t_ms:11431761 stream:0x732acba3 wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,0283cce0e689
```

---

@LAT106LON123 | created:0 | updated:0

**BAR** frame:8000 bar:19 own:10 held:38 terms:9 digest:0xb5144cb4 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1385 hi:1395 sum:13904
**HOLDS** agent:0x00000011 n:10 lo:1327 hi:1337 sum:13324
**HOLDS** agent:0x00000012 n:10 lo:1238 hi:1248 sum:12434
**HOLDS** agent:0x00000200 n:10 lo:2025 hi:2034 sum:20295
**HOLDS** agent:0x00000300 n:8 lo:4604 hi:4623 sum:36901
**DELIVER** up_s:11686 heap:120200 fetched:779 unanswered:543 broken:134 resumed:2604 empty:359 served:3016 wants:3043 early:54 wantq_drop:1 superseded:0

---

@LAT103LON8279 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12042475 ±0 frame:8000
seq: 1350
follows: 0x00000010:1405 0x00000012:1260 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **ENTWIN** t_ms:12031762 stream:0x732acba3 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,bc102f237ace,0283cce0e689,5ce28c488e0c
```

---

@LAT103LON8280 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 33163 ±21 frame:7500
seq: 1352
follows: 0x00000010:1406 0x00000012:1266 0x00000100:967 0x00000200:2043 0x00000300:4638
said: 1 | **ENTWIN** t_ms:354610 stream:0xc9e0e898 wall:0 window_ms:60304 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT106LON124 | created:0 | updated:0

**BAR** frame:7500 bar:1 own:10 held:30 terms:9 digest:0x7688be17 settled_ms:300000
**HOLDS** agent:0x00000010 n:8 lo:1410 hi:1417 sum:11308
**HOLDS** agent:0x00000011 n:10 lo:1351 hi:1361 sum:13564
**HOLDS** agent:0x00000012 n:7 lo:1270 hi:1276 sum:8911
**HOLDS** agent:0x00000200 n:8 lo:2047 hi:2054 sum:16404
**HOLDS** agent:0x00000300 n:7 lo:4648 hi:4660 sum:32578
**DELIVER** up_s:936 heap:120276 fetched:60 unanswered:41 broken:6 resumed:170 empty:32 served:246 wants:249 early:45 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:4 split:1
**SPLIT** agent:0x00000012 grammar:0xaf98ac36

---

@LAT103LON8281 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1186346 ±21 frame:7500
seq: 1372
follows: 0x00000010:1426 0x00000012:1286 0x00000100:1019 0x00000200:2063 0x00000300:4679
said: 1 | **ENTWIN** t_ms:1508091 stream:0xc9e0e898 wall:0 window_ms:599999 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,0283cce0e689
said: 10 | **COVERED** windows:1 entities:7 window_ms:553178 first_t_ms:908091 last_t_ms:908091 covered_by:@LAT103LON8280
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
```

---

@LAT103LON1314 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT106LON125 | created:0 | updated:0

**BAR** frame:7500 bar:2 own:10 held:40 terms:9 digest:0x4d262fda settled_ms:300030
**HOLDS** agent:0x00000010 n:10 lo:1418 hi:1427 sum:14225
**HOLDS** agent:0x00000011 n:10 lo:1362 hi:1371 sum:13665
**HOLDS** agent:0x00000012 n:10 lo:1277 hi:1287 sum:12821
**HOLDS** agent:0x00000200 n:10 lo:2055 hi:2064 sum:20595
**HOLDS** agent:0x00000300 n:10 lo:4662 hi:4680 sum:46710
**DELIVER** up_s:1542 heap:122952 fetched:100 unanswered:78 broken:12 resumed:300 empty:50 served:428 wants:435 early:45 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:4 split:1
**SPLIT** agent:0x00000012 grammar:0xaf98ac36

---

@LAT103LON1315 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1316 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1317 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON1318 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1712947 ±21 frame:7500
seq: 1381
follows: 0x00000010:1436 0x00000012:1296 0x00000100:1028 0x00000200:2073 0x00000300:4698
said: 1 | **LINKWIN** t_ms:2034687 stream:0xc9e0e898 wall:0 window_ms:60032
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-62 rssi_max:-59
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-58 rssi_max:-54
said: 4 | **LINK** peer:0x00000010 proto:espnow n:80 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000012 proto:ble n:49 rssi_min:-81 rssi_med:-51 rssi_max:-45
said: 6 | **LINK** peer:0x00000012 proto:espnow n:40 rssi_min:-41 rssi_med:-36 rssi_max:-35
said: 7 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 8 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:espnow n:81 rssi_min:-48 rssi_med:-48 rssi_max:-46
```

---

@LAT103LON1319 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1772947 ±21 frame:7500
seq: 1382
follows: 0x00000010:1437 0x00000012:1298 0x00000100:1029 0x00000200:2074 0x00000300:4700
said: 1 | **LINKWIN** t_ms:2094687 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:76 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000300 proto:espnow n:109 rssi_min:-63 rssi_med:-60 rssi_max:-58
said: 4 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-70 rssi_med:-69 rssi_max:-67
said: 5 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-81 rssi_med:-50 rssi_max:-45
said: 6 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-72 rssi_max:-54
said: 7 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-62 rssi_max:-59
said: 8 | **LINK** peer:0x00000010 proto:espnow n:108 rssi_min:-42 rssi_med:-34 rssi_max:-33
said: 9 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON1320 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1832949 ±21 frame:7500
seq: 1383
follows: 0x00000010:1439 0x00000012:1299 0x00000100:1030 0x00000200:2075 0x00000300:4702
said: 1 | **LINKWIN** t_ms:2154687 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:107 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 4 | **LINK** peer:0x00000300 proto:espnow n:125 rssi_min:-63 rssi_med:-60 rssi_max:-57
said: 5 | **LINK** peer:0x00000010 proto:espnow n:122 rssi_min:-42 rssi_med:-34 rssi_max:-32
said: 6 | **LINK** peer:0x00000010 proto:ble n:51 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 7 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-50 rssi_max:-44
said: 8 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-62 rssi_max:-59
said: 9 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-58 rssi_max:-54
```

---

@LAT103LON1321 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1892953 ±21 frame:7500
seq: 1384
follows: 0x00000010:1440 0x00000012:1300 0x00000100:1032 0x00000200:2076 0x00000300:4705
said: 1 | **LINKWIN** t_ms:2214693 stream:0xc9e0e898 wall:0 window_ms:60006
said: 2 | **LINK** peer:0x00000200 proto:espnow n:132 rssi_min:-48 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-70 rssi_med:-69 rssi_max:-65
said: 4 | **LINK** peer:0x00000300 proto:espnow n:182 rssi_min:-63 rssi_med:-60 rssi_max:-55
said: 5 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-41 rssi_med:-34 rssi_max:-32
said: 6 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-54 rssi_max:-51
said: 7 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-83 rssi_med:-62 rssi_max:-59
said: 8 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-58 rssi_max:-53
said: 9 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-50 rssi_max:-44
```

---

@LAT103LON1322 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1952955 ±21 frame:7500
seq: 1385
follows: 0x00000010:1441 0x00000012:1300 0x00000100:1034 0x00000200:2077 0x00000300:4708
said: 1 | **LINKWIN** t_ms:2274693 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:132 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:66 rssi_min:-48 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000010 proto:espnow n:123 rssi_min:-42 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 6 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-62 rssi_max:-59
said: 7 | **LINK** peer:0x00000012 proto:ble n:25 rssi_min:-82 rssi_med:-53 rssi_max:-42
said: 8 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-83 rssi_med:-58 rssi_max:-54
said: 9 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-83 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON1323 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2012954 ±21 frame:7500
seq: 1386
follows: 0x00000010:1442 0x00000012:1300 0x00000100:1035 0x00000200:2078 0x00000300:4710
said: 1 | **LINKWIN** t_ms:2334693 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-70 rssi_med:-69 rssi_max:-65
said: 4 | **LINK** peer:0x00000300 proto:espnow n:149 rssi_min:-64 rssi_med:-60 rssi_max:-57
said: 5 | **LINK** peer:0x00000200 proto:espnow n:146 rssi_min:-48 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-82 rssi_med:-58 rssi_max:-54
said: 7 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-82 rssi_med:-50 rssi_max:-43
said: 8 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-55 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-63 rssi_max:-59
```

---

@LAT103LON1324 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2072957 ±21 frame:7500
seq: 1387
follows: 0x00000010:1443 0x00000012:1300 0x00000100:1036 0x00000200:2079 0x00000300:4712
said: 1 | **LINKWIN** t_ms:2394693 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-70 rssi_med:-69 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:espnow n:81 rssi_min:-42 rssi_med:-34 rssi_max:-32
said: 4 | **LINK** peer:0x00000300 proto:espnow n:152 rssi_min:-63 rssi_med:-58 rssi_max:-49
said: 5 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-60 rssi_max:-54
said: 6 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-62 rssi_max:-54
said: 7 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-52 rssi_med:-48 rssi_max:-44
said: 8 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-54 rssi_max:-49
said: 9 | **LINK** peer:0x00000012 proto:espnow n:45 rssi_min:-44 rssi_med:-35 rssi_max:-34
```

---

@LAT106LON126 | created:0 | updated:0

**BAR** frame:7500 bar:3 own:10 held:39 terms:9 digest:0xcd88d703 settled_ms:300027
**HOLDS** agent:0x00000010 n:10 lo:1429 hi:1438 sum:14335
**HOLDS** agent:0x00000011 n:10 lo:1373 hi:1382 sum:13775
**HOLDS** agent:0x00000012 n:9 lo:1288 hi:1297 sum:11633
**HOLDS** agent:0x00000200 n:10 lo:2065 hi:2075 sum:20704
**HOLDS** agent:0x00000300 n:10 lo:4682 hi:4701 sum:46919
**DELIVER** up_s:2138 heap:119968 fetched:134 unanswered:109 broken:17 resumed:399 empty:69 served:602 wants:610 early:45 wantq_drop:1 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON1325 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2132955 ±21 frame:7500
seq: 1388
follows: 0x00000010:1444 0x00000012:1302 0x00000100:1037 0x00000200:2080 0x00000300:4714
said: 1 | **LINKWIN** t_ms:2454693 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-71 rssi_med:-69 rssi_max:-57
said: 3 | **LINK** peer:0x00000300 proto:espnow n:197 rssi_min:-67 rssi_med:-58 rssi_max:-51
said: 4 | **LINK** peer:0x00000200 proto:espnow n:91 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 5 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-42 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000010 proto:espnow n:97 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-63 rssi_max:-59
said: 8 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 9 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-55 rssi_max:-51
```

---

@LAT103LON1326 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2192958 ±21 frame:7500
seq: 1389
follows: 0x00000010:1445 0x00000012:1303 0x00000100:1038 0x00000200:2081 0x00000300:4716
said: 1 | **LINKWIN** t_ms:2514692 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 3 | **LINK** peer:0x00000012 proto:espnow n:81 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000300 proto:espnow n:188 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 5 | **LINK** peer:0x00000200 proto:espnow n:163 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000010 proto:espnow n:129 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-58 rssi_max:-54
said: 8 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-79 rssi_med:-54 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-63 rssi_max:-60
```

---

@LAT103LON1327 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2252955 ±21 frame:7500
seq: 1390
follows: 0x00000010:1446 0x00000012:1304 0x00000100:1039 0x00000200:2082 0x00000300:4718
said: 1 | **LINKWIN** t_ms:2574693 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:107 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 4 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-70 rssi_med:-69 rssi_max:-67
said: 5 | **LINK** peer:0x00000010 proto:espnow n:87 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 6 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 7 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-73 rssi_max:-54
```

---

@LAT103LON1328 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2312957 ±21 frame:7500
seq: 1391
follows: 0x00000010:1447 0x00000012:1305 0x00000100:1040 0x00000200:2083 0x00000300:4720
said: 1 | **LINKWIN** t_ms:2634692 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:109 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:192 rssi_min:-62 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-69 rssi_med:-69 rssi_max:-65
said: 5 | **LINK** peer:0x00000200 proto:espnow n:118 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000010 proto:espnow n:91 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-82 rssi_med:-49 rssi_max:-44
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-63 rssi_max:-59
said: 9 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-68 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON1329 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2372959 ±21 frame:7500
seq: 1392
follows: 0x00000010:1448 0x00000012:1306 0x00000100:1041 0x00000200:2084 0x00000300:4722
said: 1 | **LINKWIN** t_ms:2694693 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-70 rssi_med:-69 rssi_max:-64
said: 3 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000012 proto:espnow n:148 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 5 | **LINK** peer:0x00000300 proto:espnow n:145 rssi_min:-62 rssi_med:-58 rssi_max:-57
said: 6 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 8 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 9 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-59 rssi_max:-54
```

---

@LAT103LON8282 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2386403 ±21 frame:7500
seq: 1393
follows: 0x00000010:1448 0x00000012:1306 0x00000100:1042 0x00000200:2084 0x00000300:4722
said: 1 | **ENTWIN** t_ms:2708137 stream:0xc9e0e898 wall:0 window_ms:599964 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,5ce28c488e0c,0283cce0e689
said: 10 | **COVERED** windows:1 entities:7 window_ms:600082 first_t_ms:2108173 last_t_ms:2108173 covered_by:@LAT103LON8281
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95 windows:1
```

---

@LAT103LON1330 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2432960 ±21 frame:7500
seq: 1394
follows: 0x00000010:1449 0x00000012:1307 0x00000100:1042 0x00000200:2085 0x00000300:4724
said: 1 | **LINKWIN** t_ms:2754692 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-55 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-58 rssi_max:-54
said: 4 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-70 rssi_med:-69 rssi_max:-67
said: 5 | **LINK** peer:0x00000300 proto:espnow n:146 rssi_min:-61 rssi_med:-58 rssi_max:-57
said: 6 | **LINK** peer:0x00000012 proto:espnow n:79 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000010 proto:espnow n:68 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 9 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-49 rssi_max:-44
```

---

@LAT103LON1331 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2492958 ±21 frame:7500
seq: 1395
follows: 0x00000010:1450 0x00000012:1308 0x00000100:1044 0x00000200:2086 0x00000300:4726
said: 1 | **LINKWIN** t_ms:2814693 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 3 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 4 | **LINK** peer:0x00000300 proto:espnow n:180 rssi_min:-62 rssi_med:-58 rssi_max:-56
said: 5 | **LINK** peer:0x00000200 proto:espnow n:147 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000010 proto:espnow n:136 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-76 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-63 rssi_max:-60
said: 9 | **LINK** peer:0x00000012 proto:espnow n:126 rssi_min:-41 rssi_med:-35 rssi_max:-35
```

---

@LAT103LON1332 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2552960 ±21 frame:7500
seq: 1396
follows: 0x00000010:1451 0x00000012:1309 0x00000100:1045 0x00000200:2087 0x00000300:4728
said: 1 | **LINKWIN** t_ms:2874693 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-69 rssi_med:-69 rssi_max:-65
said: 3 | **LINK** peer:0x00000300 proto:espnow n:234 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 4 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-54 rssi_max:-51
said: 5 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 6 | **LINK** peer:0x00000012 proto:espnow n:107 rssi_min:-42 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000010 proto:espnow n:146 rssi_min:-41 rssi_med:-34 rssi_max:-32
said: 9 | **LINK** peer:0x00000200 proto:espnow n:123 rssi_min:-49 rssi_med:-48 rssi_max:-46
```

---

@LAT103LON1333 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2612961 ±21 frame:7500
seq: 1397
follows: 0x00000010:1452 0x00000012:1310 0x00000100:1046 0x00000200:2088 0x00000300:4730
said: 1 | **LINKWIN** t_ms:2934693 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:87 rssi_min:-40 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:193 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 4 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-70 rssi_med:-69 rssi_max:-65
said: 5 | **LINK** peer:0x00000010 proto:espnow n:99 rssi_min:-43 rssi_med:-34 rssi_max:-33
said: 6 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-49 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 8 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000200 proto:espnow n:97 rssi_min:-49 rssi_med:-48 rssi_max:-46
```

---

@LAT103LON1334 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2672961 ±21 frame:7500
seq: 1398
follows: 0x00000010:1453 0x00000012:1311 0x00000100:1047 0x00000200:2089 0x00000300:4732
said: 1 | **LINKWIN** t_ms:2994693 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:127 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:171 rssi_min:-62 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-82 rssi_med:-50 rssi_max:-43
said: 5 | **LINK** peer:0x00000012 proto:espnow n:80 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-70 rssi_med:-69 rssi_max:-65
said: 7 | **LINK** peer:0x00000010 proto:espnow n:107 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000010 proto:ble n:71 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-82 rssi_med:-63 rssi_max:-60
```
@LAT106LON127 | created:0 | updated:0

**BAR** frame:7500 bar:4 own:10 held:38 terms:9 digest:0xc9a9ac56 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1440 hi:1449 sum:14445
**HOLDS** agent:0x00000011 n:10 lo:1383 hi:1392 sum:13875
**HOLDS** agent:0x00000012 n:8 lo:1299 hi:1307 sum:10425
**HOLDS** agent:0x00000200 n:10 lo:2076 hi:2085 sum:20805
**HOLDS** agent:0x00000300 n:10 lo:4703 hi:4723 sum:47137
**DELIVER** up_s:2739 heap:120556 fetched:174 unanswered:134 broken:25 resumed:542 empty:85 served:756 wants:766 early:45 wantq_drop:1 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON1335 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2732960 ±21 frame:7500
seq: 1399
follows: 0x00000010:1454 0x00000012:1312 0x00000100:1048 0x00000200:2090 0x00000300:4734
said: 1 | **LINKWIN** t_ms:3054693 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-70 rssi_med:-69 rssi_max:-67
said: 3 | **LINK** peer:0x00000200 proto:espnow n:76 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000012 proto:espnow n:80 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 5 | **LINK** peer:0x00000010 proto:espnow n:48 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 6 | **LINK** peer:0x00000300 proto:espnow n:110 rssi_min:-62 rssi_med:-58 rssi_max:-57
said: 7 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 8 | **LINK** peer:0x00000012 proto:ble n:69 rssi_min:-82 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-74 rssi_max:-54
```

---

@LAT103LON1336 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2792964 ±21 frame:7500
seq: 1400
follows: 0x00000010:1455 0x00000012:1313 0x00000100:1049 0x00000200:2091 0x00000300:4736
said: 1 | **LINKWIN** t_ms:3114694 stream:0xc9e0e898 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 3 | **LINK** peer:0x00000012 proto:espnow n:82 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 5 | **LINK** peer:0x00000010 proto:espnow n:97 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 6 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 7 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 8 | **LINK** peer:0x00000300 proto:espnow n:177 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 9 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-70 rssi_med:-69 rssi_max:-67
```

---

@LAT103LON1337 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2852963 ±21 frame:7500
seq: 1401
follows: 0x00000010:1456 0x00000012:1314 0x00000100:1050 0x00000200:2092 0x00000300:4738
said: 1 | **LINKWIN** t_ms:3174694 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:183 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-70 rssi_med:-69 rssi_max:-67
said: 4 | **LINK** peer:0x00000200 proto:espnow n:102 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 5 | **LINK** peer:0x00000010 proto:espnow n:118 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 6 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 7 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-81 rssi_med:-55 rssi_max:-51
said: 8 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:espnow n:67 rssi_min:-41 rssi_med:-35 rssi_max:-35
```

---

@LAT103LON1338 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2912968 ±21 frame:7500
seq: 1402
follows: 0x00000010:1457 0x00000012:1315 0x00000100:1051 0x00000200:2093 0x00000300:4740
said: 1 | **LINKWIN** t_ms:3234698 stream:0xc9e0e898 wall:0 window_ms:60004
said: 2 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-70 rssi_med:-69 rssi_max:-67
said: 4 | **LINK** peer:0x00000010 proto:espnow n:78 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 6 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-62 rssi_med:-58 rssi_max:-57
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-55 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-63 rssi_max:-59
```

---

@LAT103LON1339 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2972970 ±21 frame:7500
seq: 1403
follows: 0x00000010:1458 0x00000012:1316 0x00000100:1052 0x00000200:2094 0x00000300:4742
said: 1 | **LINKWIN** t_ms:3294698 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 3 | **LINK** peer:0x00000300 proto:espnow n:184 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 4 | **LINK** peer:0x00000010 proto:espnow n:117 rssi_min:-42 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000012 proto:espnow n:91 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-59
said: 8 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-49 rssi_max:-44
```

---

@LAT103LON1340 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3032989 ±21 frame:7500
seq: 1404
follows: 0x00000010:1459 0x00000012:1317 0x00000100:1053 0x00000200:2095 0x00000300:4744
said: 1 | **LINKWIN** t_ms:3354717 stream:0xc9e0e898 wall:0 window_ms:60019
said: 2 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-82 rssi_med:-50 rssi_max:-44
said: 3 | **LINK** peer:0x00000012 proto:espnow n:90 rssi_min:-41 rssi_med:-36 rssi_max:-35
said: 4 | **LINK** peer:0x00000200 proto:espnow n:132 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 5 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-70 rssi_med:-69 rssi_max:-68
said: 6 | **LINK** peer:0x00000300 proto:espnow n:145 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 7 | **LINK** peer:0x00000010 proto:espnow n:112 rssi_min:-42 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-82 rssi_med:-63 rssi_max:-60
```

---

@LAT103LON1341 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3092989 ±21 frame:7500
seq: 1405
follows: 0x00000010:1460 0x00000012:1318 0x00000100:1055 0x00000200:2096 0x00000300:4746
said: 1 | **LINKWIN** t_ms:3414717 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-69 rssi_med:-69 rssi_max:-67
said: 4 | **LINK** peer:0x00000300 proto:espnow n:134 rssi_min:-62 rssi_med:-58 rssi_max:-55
said: 5 | **LINK** peer:0x00000200 proto:espnow n:88 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000010 proto:espnow n:104 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 8 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON1342 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3152990 ±21 frame:7500
seq: 1406
follows: 0x00000010:1461 0x00000012:1319 0x00000100:1056 0x00000200:2097 0x00000300:4748
said: 1 | **LINKWIN** t_ms:3474716 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-70 rssi_med:-69 rssi_max:-65
said: 3 | **LINK** peer:0x00000200 proto:espnow n:68 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000010 proto:espnow n:91 rssi_min:-40 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000300 proto:espnow n:204 rssi_min:-63 rssi_med:-59 rssi_max:-57
said: 6 | **LINK** peer:0x00000012 proto:espnow n:85 rssi_min:-41 rssi_med:-36 rssi_max:-35
said: 7 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 8 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON1343 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3212991 ±21 frame:7500
seq: 1407
follows: 0x00000010:1462 0x00000012:1320 0x00000100:1057 0x00000200:2098 0x00000300:4750
said: 1 | **LINKWIN** t_ms:3534717 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-49 rssi_max:-44
said: 3 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-70 rssi_med:-69 rssi_max:-68
said: 4 | **LINK** peer:0x00000200 proto:espnow n:151 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 5 | **LINK** peer:0x00000300 proto:espnow n:184 rssi_min:-62 rssi_med:-59 rssi_max:-56
said: 6 | **LINK** peer:0x00000012 proto:espnow n:106 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000010 proto:espnow n:104 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 9 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON1344 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3272988 ±21 frame:7500
seq: 1408
follows: 0x00000010:1463 0x00000012:1322 0x00000100:1058 0x00000200:2099 0x00000300:4752
said: 1 | **LINKWIN** t_ms:3594717 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-82 rssi_med:-55 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:110 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000300 proto:espnow n:179 rssi_min:-64 rssi_med:-59 rssi_max:-57
said: 5 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-70 rssi_med:-69 rssi_max:-65
said: 6 | **LINK** peer:0x00000012 proto:espnow n:68 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-42 rssi_med:-35 rssi_max:-33
said: 8 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 9 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-82 rssi_med:-50 rssi_max:-43
```

---

@LAT106LON128 | created:0 | updated:0

**BAR** frame:7500 bar:5 own:10 held:40 terms:9 digest:0xdd4d4ce8 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1450 hi:1459 sum:14545
**HOLDS** agent:0x00000011 n:10 lo:1394 hi:1403 sum:13985
**HOLDS** agent:0x00000012 n:10 lo:1308 hi:1317 sum:13125
**HOLDS** agent:0x00000200 n:10 lo:2086 hi:2095 sum:20905
**HOLDS** agent:0x00000300 n:10 lo:4725 hi:4743 sum:47340
**DELIVER** up_s:3340 heap:120084 fetched:215 unanswered:170 broken:29 resumed:669 empty:104 served:902 wants:912 early:45 wantq_drop:1 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON1345 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3332991 ±21 frame:7500
seq: 1409
follows: 0x00000010:1464 0x00000012:1323 0x00000100:1059 0x00000200:2100 0x00000300:4754
said: 1 | **LINKWIN** t_ms:3654717 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-58 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 4 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-81 rssi_med:-50 rssi_max:-44
said: 5 | **LINK** peer:0x00000300 proto:espnow n:125 rssi_min:-61 rssi_med:-59 rssi_max:-57
said: 6 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-70 rssi_med:-69 rssi_max:-65
said: 7 | **LINK** peer:0x00000010 proto:espnow n:60 rssi_min:-40 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000012 proto:espnow n:80 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 9 | **LINK** peer:0x00000200 proto:espnow n:113 rssi_min:-49 rssi_med:-48 rssi_max:-46
```

---

@LAT103LON1346 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3392992 ±21 frame:7500
seq: 1410
follows: 0x00000010:1465 0x00000012:1324 0x00000100:1060 0x00000200:2101 0x00000300:4756
said: 1 | **LINKWIN** t_ms:3714717 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-70 rssi_med:-69 rssi_max:-67
said: 3 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000300 proto:espnow n:216 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 5 | **LINK** peer:0x00000012 proto:espnow n:80 rssi_min:-41 rssi_med:-35 rssi_max:-32
said: 6 | **LINK** peer:0x00000010 proto:espnow n:80 rssi_min:-40 rssi_med:-34 rssi_max:-31
said: 7 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 8 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-63 rssi_max:-60
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-58 rssi_max:-54
```

---

@LAT103LON1347 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3452992 ±21 frame:7500
seq: 1411
follows: 0x00000010:1466 0x00000012:1325 0x00000100:1061 0x00000200:2102 0x00000300:4758
said: 1 | **LINKWIN** t_ms:3774717 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:143 rssi_min:-61 rssi_med:-59 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:91 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-70 rssi_med:-69 rssi_max:-68
said: 5 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-58 rssi_max:-54
said: 6 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-49 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:espnow n:132 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000012 proto:espnow n:78 rssi_min:-40 rssi_med:-35 rssi_max:-35
said: 9 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-50
```

---

@LAT103LON1348 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3513006 ±21 frame:7500
seq: 1412
follows: 0x00000010:1467 0x00000012:1326 0x00000100:1062 0x00000200:2103 0x00000300:4760
said: 1 | **LINKWIN** t_ms:3834731 stream:0xc9e0e898 wall:0 window_ms:60014
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-70 rssi_med:-69 rssi_max:-68
said: 3 | **LINK** peer:0x00000300 proto:espnow n:156 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 4 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000012 proto:espnow n:138 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 7 | **LINK** peer:0x00000200 proto:espnow n:128 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 8 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-63 rssi_max:-60
```

---

@LAT103LON1349 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3573008 ±21 frame:7500
seq: 1413
follows: 0x00000010:1468 0x00000012:1327 0x00000100:1063 0x00000200:2104 0x00000300:4762
said: 1 | **LINKWIN** t_ms:3894731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:167 rssi_min:-63 rssi_med:-59 rssi_max:-57
said: 3 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-69 rssi_med:-69 rssi_max:-65
said: 4 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 5 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-41 rssi_med:-35 rssi_max:-31
said: 6 | **LINK** peer:0x00000010 proto:espnow n:89 rssi_min:-40 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-54 rssi_max:-51
said: 8 | **LINK** peer:0x00000012 proto:ble n:70 rssi_min:-82 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-59 rssi_max:-54
```

---

@LAT103LON1350 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON5117 | created:0 | updated:0

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

@LAT103LON1351 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON5118 | created:0 | updated:0

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

@LAT105LON5119 | created:0 | updated:0

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

@LAT105LON5120 | created:0 | updated:0

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

@LAT105LON5121 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
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

@LAT105LON5122 | created:0 | updated:0

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

@LAT105LON5123 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
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

@LAT105LON5124 | created:0 | updated:0

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

@LAT103LON1352 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON5125 | created:0 | updated:0

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

@LAT105LON5126 | created:0 | updated:0

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

@LAT105LON5127 | created:0 | updated:0

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

@LAT105LON5128 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
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

@LAT103LON1353 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT104LON150 | created:0 | updated:0

**carried through @LAT103LON1313**

```ttdb-carried
through: 1313
through: 8236
```

---

@LAT103LON1354 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON5129 | created:0 | updated:0

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

@LAT105LON5130 | created:0 | updated:0

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

@LAT105LON5131 | created:0 | updated:0

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

---

@LAT105LON5132 | created:0 | updated:0

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

@LAT105LON5133 | created:0 | updated:0

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

@LAT105LON5134 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
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

@LAT105LON5135 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
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

@LAT105LON5136 | created:0 | updated:0

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
@LAT106LON129 | created:0 | updated:0

**BAR** frame:7500 bar:6 own:10 held:40 terms:8 digest:0xe5fee0c4 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1460 hi:1469 sum:14645
**HOLDS** agent:0x00000011 n:10 lo:1404 hi:1413 sum:14085
**HOLDS** agent:0x00000012 n:10 lo:1318 hi:1328 sum:13231
**HOLDS** agent:0x00000200 n:10 lo:2096 hi:2105 sum:21005
**HOLDS** agent:0x00000300 n:10 lo:4745 hi:4763 sum:47540
**DELIVER** up_s:3940 heap:123272 fetched:258 unanswered:195 broken:32 resumed:771 empty:125 served:1063 wants:1073 early:45 wantq_drop:1 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON1355 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON5137 | created:0 | updated:0

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

@LAT105LON5138 | created:0 | updated:0

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

@LAT105LON5139 | created:0 | updated:0

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

@LAT105LON5140 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
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

@LAT103LON1356 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON5141 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
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

@LAT105LON5142 | created:0 | updated:0

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

@LAT105LON5143 | created:0 | updated:0

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

@LAT103LON1357 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON5144 | created:0 | updated:0

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

@LAT105LON5145 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
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

@LAT105LON5146 | created:0 | updated:0

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

@LAT103LON1358 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT105LON5147 | created:0 | updated:0

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

@LAT105LON5148 | created:0 | updated:0

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

@LAT105LON5149 | created:0 | updated:0

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

@LAT105LON5150 | created:0 | updated:0

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

@LAT105LON5151 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
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

@LAT105LON5152 | created:0 | updated:0

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

@LAT103LON1359 | created:0 | updated:0

**link window**

```ttdb-episode
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

@LAT103LON8283 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4186439 ±21 frame:7500
seq: 1424
follows: 0x00000010:1478 0x00000012:1337 0x00000100:1076 0x00000200:2115 0x00000300:4783
said: 1 | **ENTWIN** t_ms:4508156 stream:0xc9e0e898 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c
said: 12 | **COVERED** windows:2 entities:8 window_ms:1200019 first_t_ms:3308148 last_t_ms:3908156 covered_by:@LAT103LON8282
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-32 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-71 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-80 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-82 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-83 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-92 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:2 rssi:-93 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-98 windows:1
```
