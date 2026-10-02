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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:70680 stream:0x7d224c73 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:8 rssi_min:-49 rssi_med:-45 rssi_max:-39
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-81 rssi_med:-61 rssi_max:-47

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:70680 stream:0x7d224c73 wall:0 window_ms:62120 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:130681 stream:0x7d224c73 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-60 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-57 rssi_med:-48 rssi_max:-43

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xb23c7677 wall:0 t_ms:10990 node:0x11 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:69533 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-52 rssi_max:-38
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-57 rssi_med:-43 rssi_max:-29
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-60 rssi_med:-48 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-61 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-54 rssi_med:-46 rssi_max:-35
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-82 rssi_med:-36 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:41 rssi_min:-81 rssi_med:-60 rssi_max:-47
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-60 rssi_med:-50 rssi_max:-34

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:69533 stream:0xb23c7677 wall:0 window_ms:60036 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:129533 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-58 rssi_med:-43 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-52 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-63 rssi_med:-50 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:75 rssi_min:-81 rssi_med:-46 rssi_max:-33
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-60 rssi_max:-51
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-50 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-49 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-52 rssi_max:-49

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:189533 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-49 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-36 rssi_med:-32 rssi_max:-29
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-82 rssi_med:-51 rssi_max:-46
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-83 rssi_med:-50 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-53 rssi_max:-47
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-56 rssi_med:-42 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-51 rssi_med:-36 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-50 rssi_med:-46 rssi_max:-41

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:249533 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-51 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-39 rssi_med:-34 rssi_max:-28
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-61 rssi_med:-43 rssi_max:-36
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-45 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-53 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-51 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-51

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:309533 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-82 rssi_med:-50 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-53 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:8 rssi_min:-54 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-57 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-51 rssi_med:-43 rssi_max:-36
**LINK** peer:0x00000300 proto:ble n:12 rssi_min:-81 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-43 rssi_med:-36 rssi_max:-30

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:369533 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-82 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-51 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-56 rssi_med:-41 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-50 rssi_max:-40
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-56 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-58 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-49 rssi_med:-42 rssi_max:-35

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x5b53f35b wall:0 t_ms:11182 node:0x11 from:0x10
**REMAP** prev_stream:0xe76e28cc prev_t_ms:4587 offset_ms:6595 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:59869 stream:0x5b53f35b wall:0 window_ms:60009
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-83 rssi_med:-35 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-23 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000012 proto:ble n:37 rssi_min:-81 rssi_med:-52 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:14 rssi_min:-45 rssi_med:-41 rssi_max:-32
**LINK** peer:0x00000100 proto:espnow n:20 rssi_min:-35 rssi_med:-32 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:33 rssi_min:-81 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:21 rssi_min:-22 rssi_med:-20 rssi_max:-18
**LINK** peer:0x00000200 proto:espnow n:10 rssi_min:-56 rssi_med:-43 rssi_max:-41

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:59869 stream:0x5b53f35b wall:0 window_ms:60048 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:119870 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-37 rssi_med:-31 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-42 rssi_med:-20 rssi_max:-15
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-43 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-35 rssi_max:-29
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-20 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-82 rssi_med:-52 rssi_max:-42

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:179870 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-35 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-83 rssi_med:-50 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-42 rssi_med:-34 rssi_max:-31
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-44 rssi_max:-29
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-21 rssi_med:-20 rssi_max:-20
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-45 rssi_med:-17 rssi_max:-16

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:239870 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-36 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-82 rssi_med:-55 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-44 rssi_med:-34 rssi_max:-31
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-32 rssi_max:-29
**LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-65 rssi_med:-46 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-18 rssi_med:-17 rssi_max:-16
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-53 rssi_max:-48

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:299870 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-38 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-37 rssi_max:-31
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-44 rssi_med:-35 rssi_max:-31
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-42 rssi_med:-29 rssi_max:-27
**LINK** peer:0x00000300 proto:espnow n:56 rssi_min:-45 rssi_med:-22 rssi_max:-16
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-43 rssi_max:-41

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:359870 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-25 rssi_med:-23 rssi_max:-22
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-45 rssi_med:-35 rssi_max:-30
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-54 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-38 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-35 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-21 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-37 rssi_max:-35

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:419870 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-83 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:68 rssi_min:-82 rssi_med:-53 rssi_max:-46
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-34 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-22 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-24 rssi_med:-23 rssi_max:-21
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-37 rssi_max:-33
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-41 rssi_med:-34 rssi_max:-30

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:479870 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:59 rssi_min:-24 rssi_med:-22 rssi_max:-21
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-42 rssi_med:-33 rssi_max:-30
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-38 rssi_med:-31 rssi_max:-29
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-53 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-22 rssi_med:-21 rssi_max:-20

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:539870 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-38 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-42 rssi_med:-34 rssi_max:-31
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-24 rssi_med:-22 rssi_max:-21
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-36 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000200 proto:ble n:69 rssi_min:-82 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-22 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-42 rssi_med:-35 rssi_max:-32

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:599870 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-24 rssi_med:-22 rssi_max:-22
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-39 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:71 rssi_min:-82 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-32 rssi_med:-30 rssi_max:-27
**LINK** peer:0x00000012 proto:ble n:10 rssi_min:-59 rssi_med:-53 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-22 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-43 rssi_med:-34 rssi_max:-32

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:659870 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-83 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-40 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-37 rssi_med:-31 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-24 rssi_med:-22 rssi_max:-21
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-52 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-59 rssi_med:-43 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-22 rssi_med:-21 rssi_max:-20

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:719870 stream:0x5b53f35b wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-85 rssi_med:-59 rssi_max:-49
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-32 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-45 rssi_med:-34 rssi_max:-22
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-38 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-82 rssi_med:-49 rssi_max:-36
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-22 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-59 rssi_med:-49 rssi_max:-44

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xdcd3edce wall:0 t_ms:8089198 node:0x11 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8147775 stream:0xdcd3edce wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-51 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-56 rssi_max:-51

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xdcd3edce wall:0 t_ms:8177519 node:0x11 from:0x300
**REMAP** prev_stream:0x1907c98c prev_t_ms:3815 offset_ms:8173704 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8226959 stream:0xdcd3edce wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-83 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:19 rssi_min:-62 rssi_med:-49 rssi_max:-44

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8226959 stream:0xdcd3edce wall:0 window_ms:60030 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xee98fca8 wall:0 t_ms:4426440 node:0x11 from:0x300
**REMAP** prev_stream:0xef8c54a9 prev_t_ms:23910 offset_ms:4402530 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4455779 stream:0xee98fca8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-58 rssi_max:-50
**LINK** peer:0x00000300 proto:espnow n:9 rssi_min:-57 rssi_med:-50 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-59 rssi_med:-59 rssi_max:-59
**LINK** peer:0x00000200 proto:ble n:13 rssi_min:-81 rssi_med:-55 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:6 rssi_min:-49 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000012 proto:espnow n:1 rssi_min:-28 rssi_med:-28 rssi_max:-28

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4455779 stream:0xee98fca8 wall:0 window_ms:60114 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-54
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4515779 stream:0xee98fca8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-58 rssi_max:-45
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-61 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-45 rssi_max:-39
**LINK** peer:0x00000200 proto:espnow n:43 rssi_min:-60 rssi_med:-47 rssi_max:-31
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-32 rssi_med:-28 rssi_max:-26
**LINK** peer:0x00000300 proto:espnow n:9 rssi_min:-62 rssi_med:-59 rssi_max:-50

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xc909d5a8 wall:0 t_ms:144695 node:0x11 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:203007 stream:0xc909d5a8 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-52
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:203083 stream:0xc909d5a8 wall:0 window_ms:60075
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:10 rssi_min:-67 rssi_med:-25 rssi_max:-22

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:263083 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-80 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-28 rssi_med:-26 rssi_max:-19

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:323083 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:49 rssi_min:-80 rssi_med:-47 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-45 rssi_med:-36 rssi_max:-25
**LINK** peer:0x00000010 proto:ble n:35 rssi_min:-73 rssi_med:-56 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:7 rssi_min:-51 rssi_med:-49 rssi_max:-44

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:383083 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-83 rssi_med:-44 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-40 rssi_med:-29 rssi_max:-20
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-50 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-47 rssi_med:-28 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-81 rssi_med:-44 rssi_max:-37

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:443083 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:20 rssi_min:-80 rssi_med:-52 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:45 rssi_min:-81 rssi_med:-40 rssi_max:-31
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-72 rssi_med:-59 rssi_max:-49
**LINK** peer:0x00000200 proto:espnow n:6 rssi_min:-49 rssi_med:-41 rssi_max:-30
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-49 rssi_med:-44 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:18 rssi_min:-32 rssi_med:-19 rssi_max:-17

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:503082 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-33 rssi_max:-30
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-81 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-45 rssi_med:-42 rssi_max:-36
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-20 rssi_med:-19 rssi_max:-15

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:563083 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-37 rssi_max:-31
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-19 rssi_med:-19 rssi_max:-17
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-44 rssi_med:-42 rssi_max:-41

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:623083 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-19 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-43 rssi_med:-42 rssi_max:-42

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:683083 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-20 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-83 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-42 rssi_med:-42 rssi_max:-42

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:743083 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-19 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-82 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-43 rssi_med:-42 rssi_max:-41

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:803082 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-19 rssi_med:-19 rssi_max:-19
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-58 rssi_max:-54

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2901818 stream:0xc909d5a8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-44 rssi_med:-35 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-81 rssi_med:-49 rssi_max:-43

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2901818 stream:0xc909d5a8 wall:0 window_ms:60126 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0
