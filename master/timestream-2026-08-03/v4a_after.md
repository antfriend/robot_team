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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120034 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:38 rssi_min:-79 rssi_med:-74 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-28 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-43 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-60 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000300 proto:ble n:51 rssi_min:-77 rssi_med:-65 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-92 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-83 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-64 rssi_med:-58 rssi_max:-52

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180034 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-76 rssi_med:-75 rssi_max:-74
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-88 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-42 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-61 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:50 rssi_min:-81 rssi_med:-70 rssi_max:-67

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240034 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-65 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-76 rssi_med:-75 rssi_max:-74
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-87 rssi_med:-84 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-59 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-80 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-26 rssi_med:-26 rssi_max:-25

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300034 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-75 rssi_med:-75 rssi_max:-74
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-78 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-26 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-88 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-81 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-59 rssi_med:-57 rssi_max:-56

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360034 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-79 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-80 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-88 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-59 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-74 rssi_med:-74 rssi_max:-72

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420034 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-88 rssi_med:-84 rssi_max:-74
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-66 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-75 rssi_med:-74 rssi_max:-71
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-81 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-77 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-59 rssi_med:-58 rssi_max:-57

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480034 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:69 rssi_min:-42 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-66 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-75 rssi_med:-75 rssi_max:-74
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-27 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-87 rssi_med:-84 rssi_max:-75
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-62 rssi_med:-58 rssi_max:-56

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540034 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-66 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-84 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-87 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-62 rssi_med:-57 rssi_max:-57
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-75 rssi_med:-75 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-27 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-59 rssi_med:-59 rssi_max:-58

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600034 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-86 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-81 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-75 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-78 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-66 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-59 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-26 rssi_med:-26 rssi_max:-25

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-91 rssi_med:-82 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-68 rssi_med:-59 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-65 rssi_med:-61 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:47 rssi_min:-92 rssi_med:-72 rssi_max:-67
**LINK** peer:0x00000011 proto:espnow n:13 rssi_min:-79 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-80 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-26 rssi_med:-25 rssi_max:-25

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60068 synced:0 window_ms:60068 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-92 rssi_med:-85 rssi_max:-75
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-63 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-42 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-80 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-79 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000012 proto:ble n:51 rssi_min:-84 rssi_med:-71 rssi_max:-66
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-68 rssi_med:-58 rssi_max:-53

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-79 rssi_med:-63 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-59 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-72 rssi_med:-71 rssi_max:-71
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-59 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000012 proto:ble n:68 rssi_min:-83 rssi_med:-72 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-88 rssi_med:-85 rssi_max:-76
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-28 rssi_med:-26 rssi_max:-26

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-60 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-91 rssi_med:-72 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-28 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-85 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:48 rssi_min:-43 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-60 rssi_med:-59 rssi_max:-49
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-91 rssi_med:-85 rssi_max:-74

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-76 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-62 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-65 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-76 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-76 rssi_med:-73 rssi_max:-70
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-89 rssi_med:-83 rssi_max:-74
**LINK** peer:0x00000012 proto:ble n:50 rssi_min:-97 rssi_med:-72 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:98 rssi_min:-28 rssi_med:-26 rssi_max:-25

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-91 rssi_med:-72 rssi_max:-67
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-42 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-59 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-92 rssi_med:-84 rssi_max:-75
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-78 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-63 rssi_med:-60 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-28 rssi_med:-26 rssi_max:-25

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-42 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:47 rssi_min:-88 rssi_med:-84 rssi_max:-75
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-60 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-61 rssi_med:-60 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-88 rssi_med:-71 rssi_max:-66
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-82 rssi_med:-63 rssi_max:-59
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-28 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-75 rssi_med:-72 rssi_max:-70

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-72 rssi_med:-63 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-90 rssi_med:-84 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-44 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000012 proto:ble n:50 rssi_min:-91 rssi_med:-68 rssi_max:-65
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-79 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-29 rssi_med:-27 rssi_max:-25
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-61 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-66 rssi_med:-57 rssi_max:-52

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-91 rssi_med:-84 rssi_max:-75
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-78 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-27 rssi_med:-26 rssi_max:-26
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-86 rssi_med:-70 rssi_max:-65
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-58 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-41 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-59 rssi_med:-58 rssi_max:-57

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-60 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-58 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-85 rssi_med:-84 rssi_max:-75
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-72 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-87 rssi_med:-70 rssi_max:-64
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-27 rssi_med:-26 rssi_max:-25

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:612312 synced:0 window_ms:552244 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-31 rssi_med:-27 rssi_max:-26
**LINK** peer:0x00000200 proto:ble n:50 rssi_min:-75 rssi_med:-66 rssi_max:-57
**LINK** peer:0x00000200 proto:espnow n:12 rssi_min:-67 rssi_med:-56 rssi_max:-49

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60025 synced:0 window_ms:60025 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-29 rssi_med:-28 rssi_max:-26
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-48 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-88 rssi_med:-64 rssi_max:-59
**LINK** peer:0x00000200 proto:espnow n:32 rssi_min:-61 rssi_med:-52 rssi_max:-45

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-54 rssi_med:-52 rssi_max:-45
**LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-28 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-76 rssi_med:-65 rssi_max:-59

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-46 rssi_med:-41 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-64 rssi_med:-62 rssi_max:-59
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-49 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-27 rssi_med:-25 rssi_max:-25

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-45 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-49 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-62 rssi_max:-59
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-27 rssi_med:-25 rssi_max:-25

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-50 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-62 rssi_max:-59
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-27 rssi_med:-25 rssi_max:-25

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-76 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-82 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-28 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-54 rssi_med:-50 rssi_max:-44

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-76 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-52 rssi_med:-43 rssi_max:-35
**LINK** peer:0x00000300 proto:ble n:51 rssi_min:-49 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-29 rssi_med:-27 rssi_max:-25

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-45 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000300 proto:ble n:51 rssi_min:-79 rssi_med:-46 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-42 rssi_med:-28 rssi_max:-26
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-54 rssi_max:-49

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-54 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-84 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-44 rssi_med:-33 rssi_max:-30
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-51

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:612834 synced:0 window_ms:552809 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-42 rssi_med:-34 rssi_max:-29
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-47 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-81 rssi_med:-54 rssi_max:-50

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-37 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-53 rssi_max:-52

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:780000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-40 rssi_med:-33 rssi_max:-29
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-61 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-46 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-76 rssi_med:-47 rssi_max:-46

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:840000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:7 rssi_min:-40 rssi_med:-38 rssi_max:-31
**LINK** peer:0x00000300 proto:ble n:39 rssi_min:-53 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-81 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-47 rssi_med:-44 rssi_max:-41

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:900000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:47 rssi_min:-52 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-46 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:16 rssi_min:-40 rssi_med:-34 rssi_max:-31

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:960607 synced:0 window_ms:60607
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-58 rssi_med:-47 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-44 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:11 rssi_min:-41 rssi_med:-33 rssi_max:-33

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1022100 synced:0 window_ms:61493
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-77 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-43 rssi_med:-40 rssi_max:-36
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-63 rssi_med:-49 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:13 rssi_min:-41 rssi_med:-33 rssi_max:-31

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1082100 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-79 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-54 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-41 rssi_med:-40 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-40 rssi_med:-34 rssi_max:-33

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1142100 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-53 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-40 rssi_med:-36 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-50 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-41 rssi_med:-38 rssi_max:-35

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1202127 synced:0 window_ms:60027
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-79 rssi_med:-50 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-41 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-45 rssi_med:-36 rssi_max:-32
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-51 rssi_max:-47

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1212811 synced:0 window_ms:599977 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1262127 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-50 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-41 rssi_med:-38 rssi_max:-35
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-70 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-42 rssi_med:-35 rssi_max:-32

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1322127 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-79 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-41 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000300 proto:ble n:43 rssi_min:-60 rssi_med:-50 rssi_max:-46
**LINK** peer:0x00000300 proto:espnow n:18 rssi_min:-42 rssi_med:-36 rssi_max:-33

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1382127 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-79 rssi_med:-50 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-52 rssi_med:-39 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-40 rssi_med:-33 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-49 rssi_max:-44

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1442127 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-92 rssi_med:-80 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-74 rssi_med:-69 rssi_max:-36
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-71 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-59 rssi_med:-54 rssi_max:-45

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1502127 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-71 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000300 proto:espnow n:56 rssi_min:-56 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-88 rssi_med:-80 rssi_max:-77
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-70 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-90 rssi_med:-70 rssi_max:-65
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-96 rssi_med:-80 rssi_max:-71
**LINK** peer:0x00000012 proto:espnow n:3 rssi_min:-81 rssi_med:-70 rssi_max:-70
**LINK** peer:0x00000012 proto:ble n:14 rssi_min:-92 rssi_med:-80 rssi_max:-74

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1562127 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-94 rssi_med:-77 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-68 rssi_max:-37
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-61 rssi_med:-54 rssi_max:-27
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-68 rssi_med:-65 rssi_max:-27
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-69 rssi_med:-65 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-78 rssi_med:-67 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-95 rssi_med:-78 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-89 rssi_med:-80 rssi_max:-50

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1622127 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-96 rssi_med:-65 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-79 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-30 rssi_med:-28 rssi_max:-26
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-78 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:68 rssi_min:-46 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-31 rssi_med:-29 rssi_max:-26
**LINK** peer:0x00000012 proto:espnow n:14 rssi_min:-51 rssi_med:-43 rssi_max:-40

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1682127 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-94 rssi_med:-82 rssi_max:-75
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-45 rssi_med:-41 rssi_max:-33
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-77 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-68 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-31 rssi_med:-28 rssi_max:-26
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-43 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-44 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-41 rssi_med:-28 rssi_max:-26

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1742132 synced:0 window_ms:60005
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-31 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000012 proto:ble n:68 rssi_min:-80 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-91 rssi_med:-81 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-73 rssi_med:-67 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-82 rssi_med:-46 rssi_max:-35
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-38 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-41 rssi_med:-35 rssi_max:-33

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1810812 synced:0 window_ms:598001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2410811 synced:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3010812 synced:0 window_ms:600001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3612811 synced:0 window_ms:601999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4215938 synced:0 window_ms:603127 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4812811 synced:0 window_ms:596873 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5412811 synced:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:609752 synced:0 window_ms:549752 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:611760 synced:0 window_ms:551760 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60017 synced:0 window_ms:60017 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x59fb8ce8 wall:0 t_ms:1672837 node:0x10 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1731254 stream:0x59fb8ce8 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
