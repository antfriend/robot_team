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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3060060 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-75 rssi_max:-73
**LINK** peer:0x00000011 proto:espnow n:34 rssi_min:-63 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-60 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-60 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000010 proto:ble n:45 rssi_min:-85 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000300 proto:espnow n:18 rssi_min:-54 rssi_med:-53 rssi_max:-51

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3120060 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-82 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-66 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-63 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-80 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-80 rssi_med:-68 rssi_max:-66
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-73 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-62 rssi_med:-58 rssi_max:-57

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3180060 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000300 proto:espnow n:59 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-68 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-58 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-80 rssi_med:-77 rssi_max:-74

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3240060 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-65 rssi_med:-63 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-67 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-58 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-80 rssi_med:-77 rssi_max:-74

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3300060 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-81 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-67 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-58 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-83 rssi_med:-63 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-70 rssi_max:-67

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3360060 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-75 rssi_max:-67
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-68 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-63 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-58 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-54 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-60 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-72 rssi_max:-71

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3420060 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-82 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-56 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-70 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-58 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-60 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-72 rssi_max:-70

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3480060 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-84 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-79 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-59 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-59 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-74 rssi_med:-68 rssi_max:-65
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-60 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-82 rssi_med:-78 rssi_max:-74

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3540060 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-84 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-61 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-71 rssi_med:-69 rssi_max:-65
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-62 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-59 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-69 rssi_max:-67

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3600060 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-60 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-56 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-73 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-84 rssi_med:-76 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-84 rssi_med:-73 rssi_max:-65
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-60 rssi_med:-57 rssi_max:-55

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3610317 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-61
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-94

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3660060 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-67 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-61 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000010 proto:ble n:44 rssi_min:-88 rssi_med:-73 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-89 rssi_med:-78 rssi_max:-72
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-72 rssi_max:-68
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-72 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-64 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:8 rssi_min:-73 rssi_med:-60 rssi_max:-56

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3720060 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-80 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-64 rssi_med:-60 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-56 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-83 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-93 rssi_med:-69 rssi_max:-65
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-62 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-81 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-70 rssi_med:-65 rssi_max:-63

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3780060 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-80 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-65 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-62 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-61 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-65 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-83 rssi_med:-73 rssi_max:-68
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000010 proto:ble n:47 rssi_min:-82 rssi_med:-71 rssi_max:-66

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3840060 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-81 rssi_med:-73 rssi_max:-68
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000010 proto:ble n:46 rssi_min:-82 rssi_med:-71 rssi_max:-66
**LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-53 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-59 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-58 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-76 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-64 rssi_med:-64 rssi_max:-64

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3900060 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-62 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-56 rssi_med:-51 rssi_max:-50
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-91 rssi_med:-70 rssi_max:-66
**LINK** peer:0x00000200 proto:espnow n:79 rssi_min:-61 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-64 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-82 rssi_med:-73 rssi_max:-68

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3960060 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-74 rssi_max:-69
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-60 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-64 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-60 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-53 rssi_med:-51 rssi_max:-50
**LINK** peer:0x00000001 proto:espnow n:17 rssi_min:-61 rssi_med:-59 rssi_max:-57

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4020060 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-73 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-60 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-83 rssi_med:-76 rssi_max:-70
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-71 rssi_max:-66
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-53 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-58 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-70 rssi_med:-64 rssi_max:-63

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4080060 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-61 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-80 rssi_med:-73 rssi_max:-68
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-72 rssi_med:-64 rssi_max:-64
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-55 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-60 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-82 rssi_med:-76 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-92 rssi_med:-71 rssi_max:-65

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4140060 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-92 rssi_med:-76 rssi_max:-72
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-61 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-93 rssi_med:-70 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-81 rssi_med:-75 rssi_max:-68
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-66 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-60 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-53 rssi_med:-52 rssi_max:-50

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4200060 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-85 rssi_med:-69 rssi_max:-65
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-76 rssi_max:-72
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-55 rssi_med:-51 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-60 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-63 rssi_max:-62
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-74 rssi_max:-68
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-59 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-65 rssi_med:-64 rssi_max:-63

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4210317 synced:0 window_ms:600000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-60
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4260060 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-63 rssi_max:-62
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-74 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-61 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-55 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-88 rssi_med:-69 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-59 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-64 rssi_med:-64 rssi_max:-63

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4320060 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000200 proto:ble n:38 rssi_min:-81 rssi_med:-74 rssi_max:-68
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-68 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-64 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-89 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000010 proto:ble n:30 rssi_min:-84 rssi_med:-69 rssi_max:-64
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-71 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:9 rssi_min:-67 rssi_med:-59 rssi_max:-56

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4380060 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-76 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-64 rssi_med:-64 rssi_max:-63

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4440060 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-77 rssi_max:-71
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-64 rssi_med:-64 rssi_max:-63

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4500060 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-82 rssi_med:-76 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-64 rssi_med:-64 rssi_max:-63

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4560084 synced:0 window_ms:60024
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-70 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-82 rssi_med:-77 rssi_max:-72

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4620084 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-82 rssi_med:-79 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-70 rssi_med:-65 rssi_max:-63

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4680084 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-74 rssi_med:-70 rssi_max:-66
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-86 rssi_med:-79 rssi_max:-74

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4740084 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:37 rssi_min:-74 rssi_med:-69 rssi_max:-65
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-84 rssi_med:-79 rssi_max:-72

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4800104 synced:0 window_ms:60020
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-73 rssi_med:-69 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-88 rssi_med:-81 rssi_max:-72

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4810317 synced:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-62
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4860104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-82 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-64 rssi_med:-64 rssi_max:-63

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4920104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-64 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-77 rssi_max:-72

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4980104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:31 rssi_min:-65 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-77 rssi_max:-72

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5040104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-78 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-64 rssi_med:-64 rssi_max:-64

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5100104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-64 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-77 rssi_max:-72

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5160104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-65 rssi_med:-64 rssi_max:-64

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5220104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-77 rssi_max:-71
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-65 rssi_med:-64 rssi_max:-64

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5280104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-82 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:32 rssi_min:-71 rssi_med:-64 rssi_max:-63

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5340104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-84 rssi_med:-80 rssi_max:-73
**LINK** peer:0x00000011 proto:espnow n:39 rssi_min:-74 rssi_med:-70 rssi_max:-64

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5400104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-84 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-69 rssi_med:-64 rssi_max:-64

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5410317 synced:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-61
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5460104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-65 rssi_med:-64 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-77 rssi_max:-72

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5520104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-65 rssi_med:-64 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-83 rssi_med:-77 rssi_max:-73

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5580104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-64 rssi_med:-64 rssi_max:-64

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5640104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-80 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-65 rssi_med:-64 rssi_max:-63

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5700104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-65 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-77 rssi_max:-72

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5760104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-82 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:34 rssi_min:-65 rssi_med:-64 rssi_max:-64

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5820104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-84 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-72 rssi_med:-65 rssi_max:-62

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5880104 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-65 rssi_med:-64 rssi_max:-64

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6010317 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-60
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6610317 synced:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-60
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7210317 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-60
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7810318 synced:0 window_ms:600001 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-60
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8410317 synced:0 window_ms:599999 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-60
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9010317 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-60
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9610317 synced:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-60
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60006 synced:0 window_ms:60006 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610372 synced:0 window_ms:550366 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210372 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1810372 synced:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2410372 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3010372 synced:0 window_ms:600000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3610372 synced:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4210374 synced:0 window_ms:600002 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-25
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:611765 synced:0 window_ms:551765 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1211765 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1811765 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2411765 synced:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3011765 synced:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3611765 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4211765 synced:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-25
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4811765 synced:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x59fb8ce8 wall:0 t_ms:4048832 node:0x12 from:0x11
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted
