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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4500009 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-80 rssi_med:-76 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-89 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-96 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-95 rssi_med:-88 rssi_max:-81
**LINK** peer:0x00000300 proto:ble n:41 rssi_min:-93 rssi_med:-89 rssi_max:-83
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-72 rssi_med:-63 rssi_max:-62
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-72 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-83 rssi_med:-76 rssi_max:-75

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4560009 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:46 rssi_min:-93 rssi_med:-88 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:44 rssi_min:-100 rssi_med:-91 rssi_max:-88
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-84 rssi_med:-78 rssi_max:-75
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-88 rssi_med:-84 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-77 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-87 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-70 rssi_med:-69 rssi_max:-69
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-69 rssi_med:-66 rssi_max:-62

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4620009 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:39 rssi_min:-97 rssi_med:-91 rssi_max:-88
**LINK** peer:0x00000200 proto:ble n:48 rssi_min:-93 rssi_med:-88 rssi_max:-83
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-71 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-76 rssi_med:-75 rssi_max:-75
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-88 rssi_med:-85 rssi_max:-77
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-78 rssi_max:-76
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-68 rssi_med:-67 rssi_max:-66
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-88 rssi_med:-86 rssi_max:-85

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4680009 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000300 proto:ble n:35 rssi_min:-94 rssi_med:-91 rssi_max:-89
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-92 rssi_med:-88 rssi_max:-83
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-88 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-76 rssi_med:-75 rssi_max:-75
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-88 rssi_med:-86 rssi_max:-85
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-70 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-69 rssi_med:-67 rssi_max:-66

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4740009 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-87 rssi_med:-85 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-94 rssi_med:-88 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:46 rssi_min:-98 rssi_med:-92 rssi_max:-89
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-70 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-76 rssi_med:-75 rssi_max:-74
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-88 rssi_med:-87 rssi_max:-85
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-82 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-69 rssi_med:-67 rssi_max:-65

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4800009 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-87 rssi_med:-85 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-95 rssi_med:-88 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:37 rssi_min:-98 rssi_med:-92 rssi_max:-89
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-76 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-70 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-87 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-82 rssi_med:-78 rssi_max:-76
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-71 rssi_med:-68 rssi_max:-65

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4812308 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-86
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:f04b8afbada3 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4860009 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-86 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-77 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-93 rssi_med:-88 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:49 rssi_min:-99 rssi_med:-92 rssi_max:-89
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-86 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-87 rssi_med:-85 rssi_max:-77
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-71 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-73 rssi_med:-68 rssi_max:-65

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4920033 synced:0 window_ms:60024
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-87 rssi_med:-85 rssi_max:-77
**LINK** peer:0x00000300 proto:ble n:40 rssi_min:-96 rssi_med:-91 rssi_max:-89
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-84 rssi_med:-80 rssi_max:-74
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-70 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-73 rssi_med:-69 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:47 rssi_min:-93 rssi_med:-87 rssi_max:-82
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-77 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-87 rssi_med:-85 rssi_max:-83

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4980033 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:30 rssi_min:-95 rssi_med:-92 rssi_max:-87
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-93 rssi_med:-88 rssi_max:-81
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-81 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-71 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-88 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-70 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-76 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-89 rssi_med:-85 rssi_max:-80

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5040033 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-94 rssi_med:-79 rssi_max:-73
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-96 rssi_med:-88 rssi_max:-82
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-71 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-88 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000300 proto:ble n:49 rssi_min:-98 rssi_med:-92 rssi_max:-87
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-75 rssi_med:-69 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:8 rssi_min:-80 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000200 proto:espnow n:12 rssi_min:-86 rssi_med:-85 rssi_max:-84

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5100033 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-95 rssi_med:-87 rssi_max:-81
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-85 rssi_med:-79 rssi_max:-74
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-92 rssi_med:-83 rssi_max:-76
**LINK** peer:0x00000300 proto:ble n:50 rssi_min:-95 rssi_med:-92 rssi_max:-86
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-71 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-92 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-84 rssi_med:-77 rssi_max:-72

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5160033 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-81 rssi_med:-76 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-87 rssi_med:-83 rssi_max:-80
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-72 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000012 proto:ble n:70 rssi_min:-82 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-96 rssi_med:-89 rssi_max:-83
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-96 rssi_med:-85 rssi_max:-75
**LINK** peer:0x00000300 proto:ble n:42 rssi_min:-95 rssi_med:-91 rssi_max:-88
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-66 rssi_med:-65 rssi_max:-64

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5220033 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-73 rssi_med:-72 rssi_max:-72
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-92 rssi_med:-89 rssi_max:-83
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-85 rssi_med:-84 rssi_max:-83
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000300 proto:ble n:49 rssi_min:-97 rssi_med:-93 rssi_max:-88
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-80 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-66 rssi_med:-65 rssi_max:-64
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-88 rssi_med:-86 rssi_max:-77

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5280033 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-86 rssi_med:-84 rssi_max:-83
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-89 rssi_med:-85 rssi_max:-76
**LINK** peer:0x00000300 proto:ble n:41 rssi_min:-96 rssi_med:-90 rssi_max:-87
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-93 rssi_med:-89 rssi_max:-83
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-66 rssi_med:-65 rssi_max:-64
**LINK** peer:0x00000010 p                                                                                                                                                                                                          proto:espnow n:21 rssi_min:-77 rssi_med:-73 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:109 rssi_min:-95 rssi_med:-87 rssi_max:-80
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-75 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-79 rssi_max:-74
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-92 rssi_med:-83 rssi_max:-75
**LINK** peer:0x00000300 proto:ble n:47 rssi_min:-97 rssi_med:-92 rssi_max:-87
**LINK** peer:0x00000200 proto:ble n:47 rssi_min:-99 rssi_med:-89 rssi_max:-81
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-65 rssi_med:-65 rssi_max:-65

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5400066 synced:0 window_ms:60033
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-77 rssi_med:-73 rssi_max:-73
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-94 rssi_med:-85 rssi_max:-75
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-82 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-89 rssi_med:-83 rssi_max:-81
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-66 rssi_med:-65 rssi_max:-65
**LINK** peer:0x00000200 proto:ble n:50 rssi_min:-94 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:35 rssi_min:-96 rssi_med:-91 rssi_max:-86

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5412317 synced:0 window_ms:600009 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-86
**ENTITY** kind:wifi_ap id:f04b8afbada3 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5460088 synced:0 window_ms:60022
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-95 rssi_med:-90 rssi_max:-83
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-91 rssi_med:-85 rssi_max:-75
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-98 rssi_med:-92 rssi_max:-84
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-85 rssi_med:-83 rssi_max:-82
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-83 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-73 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-71 rssi_med:-65 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-78 rssi_med:-73 rssi_max:-72

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5520091 synced:0 window_ms:60003
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-90 rssi_med:-83 rssi_max:-75
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-80 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-93 rssi_med:-86 rssi_max:-79
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000300 proto:ble n:38 rssi_min:-99 rssi_med:-90 rssi_max:-85
**LINK** peer:0x00000200 proto:ble n:47 rssi_min:-98 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-65 rssi_med:-65 rssi_max:-65

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5580091 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-96 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-84 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000300 proto:ble n:30 rssi_min:-98 rssi_med:-89 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-88 rssi_med:-85 rssi_max:-83
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-85 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-92 rssi_med:-84 rssi_max:-75
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-69 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-77 rssi_med:-73 rssi_max:-72

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5640091 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-73 rssi_med:-73 rssi_max:-72
**LINK** peer:0x00000300 proto:ble n:18 rssi_min:-95 rssi_med:-89 rssi_max:-87
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-85 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-85 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-93 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-65 rssi_med:-65 rssi_max:-64

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5700091 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-65 rssi_med:-65 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:44 rssi_min:-96 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-82 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-92 rssi_med:-84 rssi_max:-79
**LINK** peer:0x00000300 proto:ble n:40 rssi_min:-99 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-92 rssi_med:-83 rssi_max:-74
**LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-74 rssi_med:-71 rssi_max:-70

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5760121 synced:0 window_ms:60030
**LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-82 rssi_med:-82 rssi_max:-82
**LINK** peer:0x00000300 proto:espnow n:11 rssi_min:-83 rssi_med:-71 rssi_max:-67
**LINK** peer:0x00000200 proto:ble n:1 rssi_min:-94 rssi_med:-94 rssi_max:-94
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-65 rssi_med:-65 rssi_max:-64
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000300 proto:ble n:10 rssi_min:-94 rssi_med:-89 rssi_max:-81

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5820121 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-79 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:31 rssi_min:-65 rssi_med:-65 rssi_max:-64

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5880127 synced:0 window_ms:60006
**LINK** peer:0x00000012 proto:ble n:70 rssi_min:-81 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-65 rssi_med:-65 rssi_max:-64

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5940127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-84 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-69 rssi_med:-65 rssi_max:-64

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6000127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-73 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-83 rssi_med:-78 rssi_max:-73

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6012317 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:fc3fa6b0e046 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:f04b8afbada3 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6060127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-87 rssi_med:-80 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-72 rssi_med:-69 rssi_max:-66

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6120127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-88 rssi_med:-81 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-75 rssi_med:-71 rssi_max:-68

---

@LAT97LON28 | created:0 | updated:0 | relate                                                                                                                                                                                                                                                                                                                                                                                                                    6 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-72 rssi_med:-65 rssi_max:-64

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6300127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-65 rssi_med:-65 rssi_max:-65

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6360127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-66 rssi_med:-65 rssi_max:-65

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6420127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-66 rssi_med:-65 rssi_max:-65

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6480127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-66 rssi_med:-65 rssi_max:-64

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6540127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-66 rssi_med:-65 rssi_max:-64

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6600127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-66 rssi_med:-65 rssi_max:-65

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6612317 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:f04b8afbada3 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:fc3fa6b0e046 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6660127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-78 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-66 rssi_med:-65 rssi_max:-64

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6720127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-89 rssi_med:-80 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-74 rssi_med:-70 rssi_max:-66

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6780127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-83 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:14 rssi_min:-74 rssi_med:-65 rssi_max:-64

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6840127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-66 rssi_med:-65 rssi_max:-64

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6900127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-66 rssi_med:-65 rssi_max:-65

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6960127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-66 rssi_med:-65 rssi_max:-65

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7020127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-66 rssi_med:-65 rssi_max:-65

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7080127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-81 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-66 rssi_med:-65 rssi_max:-65

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7140127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-83 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-66 rssi_med:-65 rssi_max:-65

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7200127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-78 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-83 rssi_med:-78 rssi_max:-73

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7212317 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ff9038cc n:1 rssi:-89
**ENTITY** kind:wifi_ap id:f04b8afbada3 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7260127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-82 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-66 rssi_med:-65 rssi_max:-64

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7320127 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-66 rssi_med:-65 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-78 rssi_max:-73

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7812317 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:fc3fa6b0e046 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:f04b8afbada3 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8412317 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:fc3fa6b0e046 n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bce92f784b0f n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9012317 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        c102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:fc3fa6b0e046 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:f04b8afbada3 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:66c6d284568a n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10212317 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:66c6d284568a n:1 rssi:-86
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-86
**ENTITY** kind:wifi_ap id:fc3fa6b0e046 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:f04b8afbada3 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ff9038cc n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10812317 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:fc3fa6b0e046 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:f04b8afbada3 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11412317 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:fc3fa6b0e046 n:1 rssi:-84
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:f04b8afbada3 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ff9038cc n:1 rssi:-95

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12012316 synced:0 window_ms:599999 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:fc3fa6b0e046 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:f04b8afbada3 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60006 synced:0 window_ms:60006 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-89
**ENTITY**                                                                                                                                                                                                                                                                                                                                                                                                                     ed:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610373 synced:0 window_ms:550373 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210391 synced:0 window_ms:600018 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1810373 synced:0 window_ms:599982 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2410374 synced:0 window_ms:600001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3010374 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3610374 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4210374 synced:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:611778 synced:0 window_ms:551778 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-25
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96
