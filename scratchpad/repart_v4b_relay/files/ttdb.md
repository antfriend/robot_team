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

@LAT103LON8192 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2904437 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:3017241 stream:0xc909d5a8 wall:0 window_ms:60042 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:3 removed:36 last_lon:35 t_ms:3387283 stream:0xc909d5a8 wall:0 node:0x00000011

---

@LAT100LON5 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:2 removed:7 last_lon:6 t_ms:3395371 stream:0xc909d5a8 wall:0 node:0x00000011

---

@LAT103LON8193 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1381336 ±21 frame:5000
said: 1 | **ENTWIN** t_ms:1645292 stream:0x40bbc10f wall:0 window_ms:60050 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8194 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1631221 ±21 frame:5000
said: 1 | **ENTWIN** t_ms:1895202 stream:0x40bbc10f wall:0 window_ms:60029 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON8195 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 17889129 ±21 frame:5500
said: 1 | **ENTWIN** t_ms:17886105 stream:0x9afbb748 wall:0 window_ms:62040 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8196 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 18557247 ±21 frame:5500
said: 1 | **ENTWIN** t_ms:18556127 stream:0x9afbb748 wall:0 window_ms:60139 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8197 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 18948456 ±21 frame:5500
seq: 2
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:554
said: 1 | **ENTWIN** t_ms:18947434 stream:0x9afbb748 wall:0 window_ms:60038 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON27 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19188421 ±21 frame:5500
seq: 6
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:562
said: 1 | **LINKWIN** t_ms:19187433 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON28 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19248421 ±21 frame:5500
seq: 7
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:564
said: 1 | **LINKWIN** t_ms:19247434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON29 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19308422 ±21 frame:5500
seq: 8
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:566
said: 1 | **LINKWIN** t_ms:19307434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON30 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19368422 ±21 frame:5500
seq: 9
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:568
said: 1 | **LINKWIN** t_ms:19367434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-29 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON31 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19428423 ±21 frame:5500
seq: 10
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:570
said: 1 | **LINKWIN** t_ms:19427434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-83 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON32 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19488423 ±21 frame:5500
seq: 11
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:572
said: 1 | **LINKWIN** t_ms:19487434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON33 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19548424 ±22 frame:5500
seq: 12
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:574
said: 1 | **LINKWIN** t_ms:19547434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-83 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON34 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19608424 ±21 frame:5500
seq: 13
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:576
said: 1 | **LINKWIN** t_ms:19607434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-83 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON35 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19668425 ±21 frame:5500
seq: 14
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:578
said: 1 | **LINKWIN** t_ms:19667434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON36 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19728425 ±21 frame:5500
seq: 15
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:580
said: 1 | **LINKWIN** t_ms:19727433 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-83 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON37 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19788426 ±21 frame:5500
seq: 16
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:582
said: 1 | **LINKWIN** t_ms:19787433 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON38 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19848427 ±21 frame:5500
seq: 17
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:585
said: 1 | **LINKWIN** t_ms:19847434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON39 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19908427 ±21 frame:5500
seq: 18
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:587
said: 1 | **LINKWIN** t_ms:19907434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON40 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 19968427 ±21 frame:5500
seq: 19
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:589
said: 1 | **LINKWIN** t_ms:19967434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON41 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20028428 ±21 frame:5500
seq: 20
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:591
said: 1 | **LINKWIN** t_ms:20027434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON42 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20088428 ±21 frame:5500
seq: 21
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:593
said: 1 | **LINKWIN** t_ms:20087434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-29 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON8198 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 20104631 ±21 frame:5500
seq: 22
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:593
said: 1 | **ENTWIN** t_ms:20101634 stream:0x9afbb748 wall:0 window_ms:600032 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689,64677217947d,aef9ff2626ac
said: 14 | **COVERED** windows:1 entities:10 window_ms:556132 first_t_ms:19501602 last_t_ms:19501602 covered_by:@LAT103LON8197
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94 windows:1
```

---

@LAT103LON43 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20148429 ±21 frame:5500
seq: 23
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:595
said: 1 | **LINKWIN** t_ms:20147434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON44 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20208430 ±21 frame:5500
seq: 24
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:597
said: 1 | **LINKWIN** t_ms:20207433 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON45 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20268430 ±21 frame:5500
seq: 25
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:599
said: 1 | **LINKWIN** t_ms:20267433 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON46 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20328430 ±21 frame:5500
seq: 26
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:601
said: 1 | **LINKWIN** t_ms:20327434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON47 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20388432 ±21 frame:5500
seq: 27
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:603
said: 1 | **LINKWIN** t_ms:20387434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON48 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20448432 ±21 frame:5500
seq: 28
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:605
said: 1 | **LINKWIN** t_ms:20447434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON49 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20508431 ±21 frame:5500
seq: 29
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:607
said: 1 | **LINKWIN** t_ms:20507434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON50 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20568431 ±22 frame:5500
seq: 30
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:609
said: 1 | **LINKWIN** t_ms:20567434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON51 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20628432 ±21 frame:5500
seq: 31
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:611
said: 1 | **LINKWIN** t_ms:20627434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-29 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON52 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20688434 ±21 frame:5500
seq: 32
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:613
said: 1 | **LINKWIN** t_ms:20687434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON8199 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 20704719 ±21 frame:5500
seq: 33
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:613
said: 1 | **ENTWIN** t_ms:20701718 stream:0x9afbb748 wall:0 window_ms:600083 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,980d67f79619,0283cce0e689,aef9ff2626ac
```

---

@LAT103LON53 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20748433 ±21 frame:5500
seq: 34
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:615
said: 1 | **LINKWIN** t_ms:20747434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON54 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20808435 ±21 frame:5500
seq: 35
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:617
said: 1 | **LINKWIN** t_ms:20807433 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON55 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20868434 ±21 frame:5500
seq: 36
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:619
said: 1 | **LINKWIN** t_ms:20867434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON56 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20928436 ±21 frame:5500
seq: 37
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:621
said: 1 | **LINKWIN** t_ms:20927434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-29 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON57 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20988437 ±21 frame:5500
seq: 38
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:623
said: 1 | **LINKWIN** t_ms:20987434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON58 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21048438 ±21 frame:5500
seq: 39
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:625
said: 1 | **LINKWIN** t_ms:21047434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-43 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-29 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON59 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21108438 ±21 frame:5500
seq: 40
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:628
said: 1 | **LINKWIN** t_ms:21107434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-30 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON60 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21168439 ±21 frame:5500
seq: 41
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:630
said: 1 | **LINKWIN** t_ms:21167434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-82 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON61 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21228439 ±21 frame:5500
seq: 42
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:632
said: 1 | **LINKWIN** t_ms:21227434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-28 rssi_med:-28 rssi_max:-26
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON62 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21288439 ±21 frame:5500
seq: 43
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:634
said: 1 | **LINKWIN** t_ms:21287434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON63 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21348441 ±21 frame:5500
seq: 44
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:636
said: 1 | **LINKWIN** t_ms:21347434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-29 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON64 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21408441 ±21 frame:5500
seq: 45
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:638
said: 1 | **LINKWIN** t_ms:21407434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON65 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21468441 ±21 frame:5500
seq: 46
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:640
said: 1 | **LINKWIN** t_ms:21467434 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON66 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21528442 ±21 frame:5500
seq: 47
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:642
said: 1 | **LINKWIN** t_ms:21527433 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-28 rssi_med:-28 rssi_max:-27
```

---

@LAT104LON2 | created:0 | updated:0

**carried through @LAT103LON26**

```ttdb-carried
through: 26
```

---

@LAT103LON67 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21588439 ±21 frame:5500
seq: 48
follows: 0x00000010:86 0x00000100:121 0x00000200:5 0x00000300:644
said: 1 | **LINKWIN** t_ms:21587433 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-29 rssi_med:-28 rssi_max:-27
```
