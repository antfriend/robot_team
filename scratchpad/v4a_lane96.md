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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-78 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-97 rssi_med:-92 rssi_max:-84
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-63 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:50 rssi_min:-92 rssi_med:-80 rssi_max:-73
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-63 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000011 proto:espnow n:243 rssi_min:-79 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-67 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-48 rssi_med:-44 rssi_max:-40

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-62 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-92 rssi_med:-81 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-80 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-49 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-83 rssi_med:-75 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:14 rssi_min:-65 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:25 rssi_min:-93 rssi_med:-90 rssi_max:-85
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-72 rssi_med:-63 rssi_max:-59

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-58 rssi_med:-56 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-46 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:12 rssi_min:-64 rssi_med:-63 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:79 rssi_min:-69 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-93 rssi_med:-81 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:71 rssi_min:-60 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:46 rssi_min:-93 rssi_med:-86 rssi_max:-85
**LINK** peer:0x00000011 proto:espnow n:9 rssi_min:-75 rssi_med:-75 rssi_max:-73

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:12 rssi_min:-46 rssi_med:-44 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-78 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:13 rssi_min:-67 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-60 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000300 proto:ble n:81 rssi_min:-76 rssi_med:-63 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-98 rssi_med:-89 rssi_max:-84
**LINK** peer:0x00000012 proto:ble n:73 rssi_min:-97 rssi_med:-81 rssi_max:-73

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:71 rssi_min:-53 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-90 rssi_med:-79 rssi_max:-74
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-77 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-69 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-76 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:35 rssi_min:-92 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-41 rssi_med:-40 rssi_max:-36

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-76 rssi_med:-76 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-63 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:36 rssi_min:-92 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-90 rssi_med:-79 rssi_max:-76
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-54 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-79 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-41 rssi_med:-39 rssi_max:-36
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-81 rssi_med:-62 rssi_max:-61

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-78 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-65 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-91 rssi_med:-79 rssi_max:-75
**LINK** peer:0x00000011 proto:ble n:36 rssi_min:-93 rssi_med:-85 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-77 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-41 rssi_med:-39 rssi_max:-36

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60005 synced:0 window_ms:60005
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-73 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-57 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-46 rssi_med:-44 rssi_max:-35
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-97 rssi_med:-92 rssi_max:-89
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-80 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-98 rssi_med:-85 rssi_max:-80
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-86 rssi_med:-84 rssi_max:-80

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120005 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-77 rssi_med:-64 rssi_max:-59
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-61 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-98 rssi_med:-93 rssi_max:-88
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-86 rssi_med:-83 rssi_max:-80
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-70 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-66 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:46 rssi_min:-99 rssi_med:-84 rssi_max:-80
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-46 rssi_med:-43 rssi_max:-41

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180007 synced:0 window_ms:60002
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-48 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-60 rssi_med:-55 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-55 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-95 rssi_med:-85 rssi_max:-79
**LINK** peer:0x00000011 proto:ble n:47 rssi_min:-97 rssi_med:-92 rssi_max:-87
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-90 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-65 rssi_max:-59
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-71 rssi_med:-67 rssi_max:-65

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240007 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-62 rssi_max:-59
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-97 rssi_med:-85 rssi_max:-79
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-62 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-87 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-69 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-66 rssi_med:-62 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-99 rssi_med:-90 rssi_max:-87
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-54 rssi_med:-45 rssi_max:-31

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300007 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-81 rssi_med:-67 rssi_max:-57
**LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-48 rssi_med:-38 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-63 rssi_med:-60 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:49 rssi_min:-96 rssi_med:-83 rssi_max:-79
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-80 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-72 rssi_med:-69 rssi_max:-65
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-88 rssi_med:-83 rssi_max:-80
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-99 rssi_med:-92 rssi_max:-88

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360007 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-94 rssi_med:-83 rssi_max:-75
**LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-38 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-89 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-96 rssi_med:-92 rssi_max:-88
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-77 rssi_med:-67 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-73 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-56 rssi_med:-55 rssi_max:-47

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-82 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-57 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-59 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-86 rssi_med:-46 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-98 rssi_med:-91 rssi_max:-84
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-78 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:39 rssi_min:-38 rssi_med:-32 rssi_max:-30
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-74 rssi_med:-72 rssi_max:-68

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:34 rssi_min:-58 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-98 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-59 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-56 rssi_med:-52 rssi_max:-45
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-66 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:43 rssi_min:-33 rssi_med:-32 rssi_max:-30
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-73 rssi_med:-70 rssi_max:-69

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-57 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-98 rssi_med:-92 rssi_max:-87
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-81 rssi_med:-65 rssi_max:-64
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-58 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-67 rssi_med:-51 rssi_max:-46
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-83 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-41 rssi_med:-37 rssi_max:-32
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-72 rssi_med:-70 rssi_max:-67

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-77 rssi_med:-63 rssi_max:-57
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-97 rssi_med:-93 rssi_max:-85
**LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-39 rssi_med:-33 rssi_max:-31
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-76 rssi_med:-50 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-58 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-79 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-71 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-52 rssi_med:-50 rssi_max:-44

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-39 rssi_med:-34 rssi_max:-31
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-77 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-51 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-74 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-61 rssi_max:-57
**LINK** peer:0x00000011 proto:ble n:32 rssi_min:-95 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-51 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-56 rssi_med:-55 rssi_max:-51

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-74 rssi_med:-70 rssi_max:-66
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-57 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-67 rssi_med:-50 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-80 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-39 rssi_med:-34 rssi_max:-30
**LINK** peer:0x00000011 proto:ble n:47 rssi_min:-98 rssi_med:-91 rssi_max:-84
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-81 rssi_med:-65 rssi_max:-57
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-57 rssi_med:-55 rssi_max:-53

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-74 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-79 rssi_med:-63 rssi_max:-59
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-57 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-52 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-38 rssi_med:-34 rssi_max:-31
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-80 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-55 rssi_med:-51 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-97 rssi_med:-93 rssi_max:-86

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-73 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-78 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-50 rssi_med:-41 rssi_max:-36
**LINK** peer:0x00000011 proto:ble n:44 rssi_min:-98 rssi_med:-92 rssi_max:-87
**LINK** peer:0x00000200 proto:ble n:70 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-38 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-56 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-55 rssi_max:-50

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-73 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-79 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:47 rssi_min:-97 rssi_med:-89 rssi_max:-83
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-56 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-45 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-33 rssi_med:-31 rssi_max:-29
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-79 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-46 rssi_max:-44

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:47 rssi_min:-96 rssi_med:-91 rssi_max:-84
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-54 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-35 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-57 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-60 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:13 rssi_min:-70 rssi_med:-68 rssi_max:-66
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-57 rssi_med:-52 rssi_max:-51

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-69 rssi_med:-68 rssi_max:-66
**LINK** peer:0x00000011 proto:ble n:41 rssi_min:-93 rssi_med:-90 rssi_max:-89
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-44 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-80 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-79 rssi_med:-60 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-55 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-54 rssi_med:-52 rssi_max:-51

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-73 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-61 rssi_med:-60 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-56 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-32 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000011 proto:ble n:31 rssi_min:-95 rssi_med:-90 rssi_max:-89
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-69 rssi_med:-68 rssi_max:-67

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-55 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-60 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-55 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-44 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:31 rssi_min:-93 rssi_med:-90 rssi_max:-89
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-69 rssi_med:-68 rssi_max:-68

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600009 synced:0 window_ms:60009
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-71 rssi_med:-68 rssi_max:-67
**LINK** peer:0x00000300 proto:espnow n:91 rssi_min:-52 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-34 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-77 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-67 rssi_med:-60 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-55 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:31 rssi_min:-93 rssi_med:-90 rssi_max:-85

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-60 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-55 rssi_med:-49 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-44 rssi_med:-36 rssi_max:-29
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-51 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-82 rssi_med:-63 rssi_max:-54
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-80 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:38 rssi_min:-97 rssi_med:-92 rssi_max:-85
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-77 rssi_med:-71 rssi_max:-67

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-62 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:48 rssi_min:-97 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-80 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-79 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-40 rssi_med:-35 rssi_max:-29
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-74 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-57 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-52 rssi_med:-46 rssi_max:-38

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-79 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-69 rssi_med:-68 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-97 rssi_med:-90 rssi_max:-87
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-57 rssi_med:-55 rssi_max:-55
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-76 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-38 rssi_med:-37 rssi_max:-34

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-80 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:46 rssi_min:-97 rssi_med:-89 rssi_max:-86
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-38 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-79 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-69 rssi_med:-68 rssi_max:-67
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-56 rssi_med:-55 rssi_max:-55

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-80 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-77 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-70 rssi_med:-68 rssi_max:-67
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-57 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-38 rssi_med:-37 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:43 rssi_min:-96 rssi_med:-90 rssi_max:-85
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-49 rssi_med:-49 rssi_max:-44

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-83 rssi_med:-63 rssi_max:-54
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-80 rssi_med:-52 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-74 rssi_med:-71 rssi_max:-67
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-59 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-45 rssi_med:-37 rssi_max:-31
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-56 rssi_med:-50 rssi_max:-39
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-99 rssi_med:-92 rssi_max:-84
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-80 rssi_med:-70 rssi_max:-62

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:72 rssi_min:-69 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-59 rssi_med:-48 rssi_max:-43
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-92 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-96 rssi_med:-89 rssi_max:-84
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-76 rssi_med:-70 rssi_max:-66
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-41 rssi_med:-37 rssi_max:-30
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-58 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-52 rssi_med:-45 rssi_max:-43

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:51 rssi_min:-82 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-80 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-93 rssi_med:-90 rssi_max:-83
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-72 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-56 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-41 rssi_med:-32 rssi_max:-30
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-49 rssi_med:-45 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-46 rssi_max:-44

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-79 rssi_med:-61 rssi_max:-56
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-53 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-97 rssi_med:-92 rssi_max:-83
**LINK** peer:0x00000012 proto:ble n:49 rssi_min:-85 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-58 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-45 rssi_med:-42 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-56 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-73 rssi_med:-72 rssi_max:-70

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-52 rssi_max:-45
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-87 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-99 rssi_med:-91 rssi_max:-85
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-76 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-80 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-56 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-59 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-43 rssi_med:-40 rssi_max:-31

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-95 rssi_med:-90 rssi_max:-84
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-55 rssi_med:-51 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-74 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-58 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-49 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-82 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-43 rssi_med:-39 rssi_max:-32

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:46 rssi_min:-96 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-72 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-59 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000300 proto:ble n:69 rssi_min:-82 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-44 rssi_med:-43 rssi_max:-36
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-48 rssi_med:-45 rssi_max:-41

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:780000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-84 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-95 rssi_med:-89 rssi_max:-84
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-58 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000300 proto:espnow n:58 rssi_min:-50 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-53 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-47 rssi_med:-42 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-60 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-79 rssi_med:-69 rssi_max:-66

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:840000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-80 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-77 rssi_med:-73 rssi_max:-70
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-55 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-57 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-45 rssi_med:-40 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:46 rssi_min:-98 rssi_med:-90 rssi_max:-86
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-83 rssi_med:-65 rssi_max:-58
