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

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x59fb8ce8 wall:0 t_ms:1740837 node:0x11 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6914813 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7514813 stream:0x59fb8ce8 wall:0 window_ms:600001 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8114813 stream:0x59fb8ce8 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8714813 stream:0x59fb8ce8 wall:0 window_ms:600001 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9314835 stream:0x59fb8ce8 wall:0 window_ms:600021 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-94

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9914835 stream:0x59fb8ce8 wall:0 window_ms:600001 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-96

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10514835 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11114835 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11714835 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12314835 stream:0x59fb8ce8 wall:0 window_ms:599999 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbdc62024 wall:0 t_ms:615283 node:0x11 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:742318 stream:0xbdc62024 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:828820 stream:0xbdc62024 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:832981 stream:0xbdc62024 wall:0 node:0x00000011

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:896434 stream:0xbdc62024 wall:0 window_ms:60004
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-36 rssi_med:-28 rssi_max:-26
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-65 rssi_med:-50 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-58 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-58 rssi_med:-52 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-52 rssi_med:-46 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-47 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-44 rssi_max:-36
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-83 rssi_med:-67 rssi_max:-53

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:896434 stream:0xbdc62024 wall:0 window_ms:62041 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:956434 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-47 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-83 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-33 rssi_med:-29 rssi_max:-27
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-33 rssi_med:-29 rssi_max:-26
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-82 rssi_med:-70 rssi_max:-58
**LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-58 rssi_med:-50 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-51 rssi_med:-44 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-62 rssi_med:-50 rssi_max:-43

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1016437 stream:0xbdc62024 wall:0 window_ms:60003
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-55 rssi_med:-50 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-45 rssi_max:-39
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-83 rssi_med:-46 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-36 rssi_med:-29 rssi_max:-26
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-62 rssi_med:-50 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-51 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-66 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-55 rssi_max:-51

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1076437 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-45 rssi_max:-39
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-55 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-31 rssi_med:-29 rssi_max:-26
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-62 rssi_med:-54 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-58 rssi_med:-41 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-69 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-71 rssi_med:-58 rssi_max:-49

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1136439 stream:0xbdc62024 wall:0 window_ms:60002
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-82 rssi_med:-45 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-83 rssi_med:-59 rssi_max:-50
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-50 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-67 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-55 rssi_med:-41 rssi_max:-28
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-73 rssi_med:-57 rssi_max:-49
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-54 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-69 rssi_med:-53 rssi_max:-49

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1196438 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-63 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:68 rssi_min:-82 rssi_med:-46 rssi_max:-39
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-50 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-85 rssi_med:-74 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-47 rssi_med:-40 rssi_max:-31
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-55 rssi_med:-50 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-63 rssi_med:-58 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-62 rssi_med:-50 rssi_max:-42

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1256438 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-56 rssi_med:-51 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-82 rssi_med:-51 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:56 rssi_min:-62 rssi_med:-34 rssi_max:-24
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-55 rssi_med:-48 rssi_max:-32
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-45 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-86 rssi_med:-68 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-38 rssi_med:-27 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-61 rssi_max:-46

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1316451 stream:0xbdc62024 wall:0 window_ms:60012
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-90 rssi_med:-58 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-63 rssi_med:-46 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:9 rssi_min:-45 rssi_med:-43 rssi_max:-36
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-83 rssi_med:-61 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-53 rssi_med:-34 rssi_max:-30
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-53 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-60 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-61 rssi_med:-45 rssi_max:-41

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1376450 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-59 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-53 rssi_med:-44 rssi_max:-37
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-59 rssi_med:-45 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-65 rssi_med:-50 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-27 rssi_med:-17 rssi_max:-16
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-62 rssi_max:-53

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1436451 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-82 rssi_med:-63 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-47 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-53 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-19 rssi_med:-19 rssi_max:-17
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-53 rssi_med:-52 rssi_max:-49

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1450152 stream:0xbdc62024 wall:0 window_ms:551682 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1496451 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-60 rssi_max:-54
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-82 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-61 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-49 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-58 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-19 rssi_med:-17 rssi_max:-16

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1556451 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-83 rssi_med:-61 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:70 rssi_min:-82 rssi_med:-68 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-82 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-49 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-61 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-21 rssi_med:-19 rssi_max:-17
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-50 rssi_med:-44 rssi_max:-41

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1616451 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-61 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-53 rssi_med:-45 rssi_max:-36
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-52 rssi_med:-47 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-19 rssi_med:-17 rssi_max:-16
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-66 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:39 rssi_min:-81 rssi_med:-62 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-70 rssi_med:-57 rssi_max:-45

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1676450 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:10 rssi_min:-48 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-64 rssi_max:-55
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-55 rssi_med:-53 rssi_max:-45
**LINK** peer:0x00000300 proto:ble n:21 rssi_min:-82 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-19 rssi_med:-18 rssi_max:-17
**LINK** peer:0x00000010 proto:ble n:45 rssi_min:-81 rssi_med:-55 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:11 rssi_min:-42 rssi_med:-42 rssi_max:-41

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1736481 stream:0xbdc62024 wall:0 window_ms:60030
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-57 rssi_max:-50
**LINK** peer:0x00000300 proto:ble n:50 rssi_min:-82 rssi_med:-62 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-53 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-19 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000300 proto:espnow n:5 rssi_min:-48 rssi_med:-48 rssi_max:-46

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1796481 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-44 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-53 rssi_med:-47 rssi_max:-41
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-60 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-64 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-19 rssi_med:-19 rssi_max:-17

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1856481 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-49 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-61 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-45 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-66 rssi_med:-52 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-18 rssi_med:-17 rssi_max:-17

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1916481 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-48 rssi_med:-47 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-62 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-42 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-19 rssi_med:-17 rssi_max:-17
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-51 rssi_med:-51 rssi_max:-49

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1976481 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-63 rssi_max:-59
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-44 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-54 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-19 rssi_med:-18 rssi_max:-17

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2036481 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000300 proto:ble n:50 rssi_min:-83 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-43 rssi_med:-40 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-50 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-68 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000012 proto:ble n:68 rssi_min:-82 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-20 rssi_med:-19 rssi_max:-17
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-53 rssi_max:-49

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2050153 stream:0xbdc62024 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2096481 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-57 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-81 rssi_med:-64 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-45 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-79 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-20 rssi_med:-18 rssi_max:-16
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-47 rssi_med:-44 rssi_max:-42

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2156481 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-83 rssi_med:-63 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-46 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-54 rssi_med:-46 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-56 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-20 rssi_med:-17 rssi_max:-16

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2216481 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-52 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-60 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-81 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-60 rssi_med:-52 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-22 rssi_med:-19 rssi_max:-16
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-87 rssi_med:-65 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-45 rssi_med:-41 rssi_max:-35

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2276481 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-62 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-81 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-81 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-45 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-21 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-82 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-61 rssi_med:-49 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-56 rssi_med:-49 rssi_max:-47

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2336481 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-66 rssi_max:-61
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-50 rssi_med:-46 rssi_max:-41
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-21 rssi_med:-20 rssi_max:-20
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-49 rssi_med:-41 rssi_max:-37
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-58 rssi_med:-58 rssi_max:-53

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2396481 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-82 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-42 rssi_med:-41 rssi_max:-41
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-58 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-20 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000300 proto:espnow n:19 rssi_min:-46 rssi_med:-46 rssi_max:-45

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2456514 stream:0xbdc62024 wall:0 window_ms:60033
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-46 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-82 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000300 proto:ble n:49 rssi_min:-81 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-82 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-20 rssi_med:-20 rssi_max:-20
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-42 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-58 rssi_med:-57 rssi_max:-57

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2516514 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-81 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-42 rssi_med:-41 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-46 rssi_med:-46 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-58 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-20 rssi_med:-20 rssi_max:-20

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2576514 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-42 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-20 rssi_med:-20 rssi_max:-20
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-46 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-58 rssi_med:-57 rssi_max:-56

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2636526 stream:0xbdc62024 wall:0 window_ms:60012
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-59 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-46 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-42 rssi_med:-41 rssi_max:-41
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-20 rssi_med:-20 rssi_max:-20

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2650181 stream:0xbdc62024 wall:0 window_ms:600029 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2696538 stream:0xbdc62024 wall:0 window_ms:60012
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-47 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-83 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-82 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-81 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-58 rssi_med:-57 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-42 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000012 proto:espnow n:12 rssi_min:-20 rssi_med:-20 rssi_max:-20

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2756538 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-82 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-58 rssi_med:-57 rssi_max:-57
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-82 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-42 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-46 rssi_med:-46 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:14 rssi_min:-20 rssi_med:-20 rssi_max:-20

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2816538 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-85 rssi_med:-67 rssi_max:-60
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-59 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-44 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-52 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-20 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-67 rssi_med:-57 rssi_max:-51

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2876538 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-72 rssi_max:-61
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-55 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-49 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-70 rssi_med:-63 rssi_max:-54
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-45 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-20 rssi_med:-20 rssi_max:-19

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2936537 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-85 rssi_med:-72 rssi_max:-61
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-55 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-45 rssi_med:-41 rssi_max:-36
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-82 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-20 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-59 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-69 rssi_med:-64 rssi_max:-53

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2996538 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-60 rssi_max:-54
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-62 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-56 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-44 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-83 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-60 rssi_med:-53 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-21 rssi_med:-19 rssi_max:-18
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-50 rssi_med:-46 rssi_max:-42

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3056551 stream:0xbdc62024 wall:0 window_ms:60013
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-62 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-53 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-42 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-50 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-21 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-59 rssi_med:-52 rssi_max:-50

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3116558 stream:0xbdc62024 wall:0 window_ms:60007
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-83 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-86 rssi_med:-67 rssi_max:-60
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-44 rssi_med:-42 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-54 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:11 rssi_min:-57 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-21 rssi_med:-20 rssi_max:-19

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3176558 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:69 rssi_min:-82 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-53 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-86 rssi_med:-74 rssi_max:-59
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-55 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-43 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-21 rssi_med:-20 rssi_max:-20

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3236557 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-92 rssi_med:-79 rssi_max:-59
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-41 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-51 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-62 rssi_max:-59
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-20 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-54 rssi_max:-50

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3250195 stream:0xbdc62024 wall:0 window_ms:600013 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3296558 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-83 rssi_med:-72 rssi_max:-58
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-42 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-52 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:11 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3356558 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-41 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-52 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-83 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3416558 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-45 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-80 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-42 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3476557 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-55 rssi_max:-48
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-57 rssi_med:-50 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-71 rssi_max:-55
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-42 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-63 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-20 rssi_med:-20 rssi_max:-19

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3536560 stream:0xbdc62024 wall:0 window_ms:60002
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-66 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-42 rssi_med:-41 rssi_max:-34
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:50 rssi_min:-88 rssi_med:-71 rssi_max:-55
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-81 rssi_med:-66 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-20 rssi_med:-20 rssi_max:-19

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3596560 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-85 rssi_med:-71 rssi_max:-61
**LINK** peer:0x00000300 proto:espnow n:21 rssi_min:-63 rssi_med:-48 rssi_max:-42
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-42 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-20 rssi_med:-19 rssi_max:-18

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3656559 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-83 rssi_med:-72 rssi_max:-57
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-59 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-46 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-86 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-60 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-20 rssi_med:-20 rssi_max:-18

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3716560 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-56 rssi_med:-49 rssi_max:-41
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-83 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-45 rssi_med:-41 rssi_max:-36
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-20 rssi_med:-20 rssi_max:-18

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3850194 stream:0xbdc62024 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4450193 stream:0xbdc62024 wall:0 window_ms:599999 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5050213 stream:0xbdc62024 wall:0 window_ms:600020 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5650234 stream:0xbdc62024 wall:0 window_ms:600021 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xe7384824 wall:0 t_ms:220578 node:0x11 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:279466 stream:0xe7384824 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:829278 stream:0xe7384824 wall:0 window_ms:549813 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1429279 stream:0xe7384824 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-95

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2070755 stream:0xe7384824 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-98

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2355967 stream:0xe7384824 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2909773 stream:0xe7384824 wall:0 window_ms:553806 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3509807 stream:0xe7384824 wall:0 window_ms:600035 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4109807 stream:0xe7384824 wall:0 window_ms:599999 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4709828 stream:0xe7384824 wall:0 window_ms:600022 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5309807 stream:0xe7384824 wall:0 window_ms:599978 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5909807 stream:0xe7384824 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6509807 stream:0xe7384824 wall:0 window_ms:600001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7109840 stream:0xe7384824 wall:0 window_ms:600033 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7709840 stream:0xe7384824 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8309840 stream:0xe7384824 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xaf869fce wall:0 t_ms:19379 node:0x11 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:78537 stream:0xaf869fce wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xdffbae31 wall:0 t_ms:3705485 node:0x11 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3763554 stream:0xdffbae31 wall:0 window_ms:60019 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4313326 stream:0xdffbae31 wall:0 window_ms:549773 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4913326 stream:0xdffbae31 wall:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5513326 stream:0xdffbae31 wall:0 window_ms:600001 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6113326 stream:0xdffbae31 wall:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbe8a1293 wall:0 t_ms:11833614 node:0x11 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11891900 stream:0xbe8a1293 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12441690 stream:0xbe8a1293 wall:0 window_ms:549790 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-19
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13041690 stream:0xbe8a1293 wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-20
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbce80555 wall:0 t_ms:37941 node:0x11 from:0x12
**REMAP** prev_stream:0xdb1db183 prev_t_ms:4282 offset_ms:33659 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:86866 stream:0xbce80555 wall:0 window_ms:60006 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:636655 stream:0xbce80555 wall:0 window_ms:549790 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-96

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1236655 stream:0xbce80555 wall:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x66486d22 wall:0 t_ms:1253658 node:0x11 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x95cc309e wall:0 t_ms:1796837 node:0x11 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x0870722b wall:0 t_ms:2058767 node:0x11 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x0870722b wall:0 t_ms:2117441 node:0x11 from:0x200
**REMAP** prev_stream:0x9e14abf0 prev_t_ms:3021 offset_ms:2114420 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbeb39900 wall:0 t_ms:8947 node:0x11 from:0x10
**REMAP** prev_stream:0x0fd0f834 prev_t_ms:3361 offset_ms:5586 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x1de72b4d wall:0 t_ms:65261 node:0x11 from:0x10
**REMAP** prev_stream:0xee8b4b22 prev_t_ms:5752 offset_ms:59509 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x498c31b1 wall:0 t_ms:0 node:0x11 from:0x11
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x3a7a2eb0 wall:0 t_ms:0 node:0x11 from:0x11
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbb1177f2 wall:0 t_ms:1155253 node:0x11 from:0x10
**REMAP** prev_stream:0x3e224430 prev_t_ms:9413 offset_ms:1145840 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled
