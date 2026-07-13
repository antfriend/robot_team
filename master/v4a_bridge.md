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

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61604 synced:0 window_ms:61604 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-97

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610061 synced:0 window_ms:550061 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210062 synced:0 window_ms:600001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1810062 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2410061 synced:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3010062 synced:0 window_ms:600001 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3610062 synced:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4210061 synced:0 window_ms:599999 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61604 synced:0 window_ms:61604 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:614611 synced:0 window_ms:553007 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61882 synced:0 window_ms:61882 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:29 rssi_min:-74 rssi_med:-71 rssi_max:-66
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-86 rssi_med:-85 rssi_max:-83
**LINK** peer:0x00000011 proto:espnow n:83 rssi_min:-87 rssi_med:-84 rssi_max:-80
**LINK** peer:0x00000200 proto:ble n:26 rssi_min:-97 rssi_med:-93 rssi_max:-91
**LINK** peer:0x00000011 proto:ble n:6 rssi_min:-100 rssi_med:-99 rssi_max:-97

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60117 synced:0 window_ms:60117 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:22ad56a6bed1 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-74 rssi_med:-68 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:19 rssi_min:-99 rssi_med:-96 rssi_max:-91
**LINK** peer:0x00000200 proto:ble n:28 rssi_min:-98 rssi_med:-94 rssi_max:-91
**LINK** peer:0x00000200 proto:espnow n:95 rssi_min:-91 rssi_med:-88 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-84 rssi_med:-81 rssi_max:-78

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60152 synced:0 window_ms:60152 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:61198 synced:0 window_ms:61198
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-85 rssi_med:-82 rssi_max:-78
**LINK** peer:0x00000200 proto:ble n:27 rssi_min:-98 rssi_med:-94 rssi_max:-92
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-74 rssi_med:-71 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:20 rssi_min:-99 rssi_med:-96 rssi_max:-92
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-88 rssi_med:-85 rssi_max:-80

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:63381 synced:0 window_ms:63381 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:61445 synced:0 window_ms:61445
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-89 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-74 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000011 proto:ble n:11 rssi_min:-99 rssi_med:-97 rssi_max:-95
**LINK** peer:0x00000200 proto:ble n:36 rssi_min:-99 rssi_med:-94 rssi_max:-91
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-87 rssi_med:-83 rssi_max:-77

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:63630 synced:0 window_ms:63630 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:122945 synced:0 window_ms:61500
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-75 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000200 proto:ble n:31 rssi_min:-100 rssi_med:-93 rssi_max:-91
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-83 rssi_med:-80 rssi_max:-77
**LINK** peer:0x00000011 proto:ble n:18 rssi_min:-99 rssi_med:-97 rssi_max:-94
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-85 rssi_med:-83 rssi_max:-83

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:184479 synced:0 window_ms:61534
**LINK** peer:0x00000011 proto:ble n:19 rssi_min:-100 rssi_med:-98 rssi_max:-96
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-73 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-85 rssi_med:-84 rssi_max:-82
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-84 rssi_med:-82 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:19 rssi_min:-100 rssi_med:-95 rssi_max:-92

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:245979 synced:0 window_ms:61500
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-70 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000200 proto:ble n:33 rssi_min:-100 rssi_med:-95 rssi_max:-92
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-83 rssi_med:-80 rssi_max:-77
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-88 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000011 proto:ble n:14 rssi_min:-97 rssi_med:-96 rssi_max:-93

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:307479 synced:0 window_ms:61500
**LINK** peer:0x00000200 proto:ble n:36 rssi_min:-100 rssi_med:-95 rssi_max:-90
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-86 rssi_med:-84 rssi_max:-82
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-83 rssi_med:-81 rssi_max:-78
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-73 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000011 proto:ble n:13 rssi_min:-100 rssi_med:-97 rssi_max:-95

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:368984 synced:0 window_ms:61505
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-74 rssi_med:-71 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:14 rssi_min:-100 rssi_med:-98 rssi_max:-94
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-87 rssi_med:-83 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-84 rssi_med:-81 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:35 rssi_min:-97 rssi_med:-94 rssi_max:-90

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-86 rssi_med:-83 rssi_max:-79
**LINK** peer:0x00000200 proto:ble n:34 rssi_min:-96 rssi_med:-94 rssi_max:-91
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-74 rssi_med:-68 rssi_max:-66
**LINK** peer:0x00000011 proto:ble n:6 rssi_min:-99 rssi_med:-98 rssi_max:-96
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-87 rssi_med:-85 rssi_max:-81

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60200 synced:0 window_ms:60200 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:26 rssi_min:-77 rssi_med:-73 rssi_max:-66
**LINK** peer:0x00000200 proto:ble n:37 rssi_min:-99 rssi_med:-92 rssi_max:-90
**LINK** peer:0x00000011 proto:ble n:14 rssi_min:-99 rssi_med:-98 rssi_max:-96
**LINK** peer:0x00000011 proto:espnow n:116 rssi_min:-85 rssi_med:-81 rssi_max:-77
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-89 rssi_med:-84 rssi_max:-80

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60226 synced:0 window_ms:60226 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-25
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-97

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-91 rssi_med:-85 rssi_max:-81
**LINK** peer:0x00000200 proto:ble n:32 rssi_min:-98 rssi_med:-94 rssi_max:-91
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-79 rssi_med:-70 rssi_max:-65
**LINK** peer:0x00000011 proto:ble n:16 rssi_min:-100 rssi_med:-97 rssi_max:-91
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-95 rssi_med:-83 rssi_max:-77

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:61500 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:13 rssi_min:-95 rssi_med:-91 rssi_max:-81
**LINK** peer:0x00000100 proto:espnow n:27 rssi_min:-84 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-89 rssi_med:-80 rssi_max:-76
**LINK** peer:0x00000011 proto:ble n:11 rssi_min:-100 rssi_med:-96 rssi_max:-92
**LINK** peer:0x00000200 proto:ble n:25 rssi_min:-98 rssi_med:-95 rssi_max:-91

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:63790 synced:0 window_ms:63790 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:61136 synced:0 window_ms:61136
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-83 rssi_med:-78 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-82 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000200 proto:ble n:27 rssi_min:-99 rssi_med:-94 rssi_max:-91
**LINK** peer:0x00000011 proto:ble n:17 rssi_min:-99 rssi_med:-95 rssi_max:-93
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-96 rssi_med:-93 rssi_max:-91

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:63475 synced:0 window_ms:63475 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:123121 synced:0 window_ms:61985
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-78 rssi_med:-74 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-82 rssi_med:-81 rssi_max:-78
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-95 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000200 proto:ble n:37 rssi_min:-99 rssi_med:-93 rssi_max:-90
**LINK** peer:0x00000011 proto:ble n:20 rssi_min:-98 rssi_med:-96 rssi_max:-91

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:62009 synced:0 window_ms:62009
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-96 rssi_med:-93 rssi_max:-91
**LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-77 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:27 rssi_min:-99 rssi_med:-93 rssi_max:-91
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-82 rssi_med:-81 rssi_max:-79
**LINK** peer:0x00000011 proto:ble n:25 rssi_min:-99 rssi_med:-96 rssi_max:-94

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:64208 synced:0 window_ms:64208 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-98

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:123544 synced:0 window_ms:61535
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-82 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000011 proto:ble n:22 rssi_min:-98 rssi_med:-96 rssi_max:-94
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-76 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:28 rssi_min:-97 rssi_med:-95 rssi_max:-91
**LINK** peer:0x00000011 proto:espnow n:10 rssi_min:-96 rssi_med:-94 rssi_max:-92

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:185475 synced:0 window_ms:61931
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-77 rssi_med:-75 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-82 rssi_med:-81 rssi_max:-79
**LINK** peer:0x00000200 proto:ble n:38 rssi_min:-100 rssi_med:-93 rssi_max:-90
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-95 rssi_med:-91 rssi_max:-88
**LINK** peer:0x00000011 proto:ble n:22 rssi_min:-98 rssi_med:-96 rssi_max:-91

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:247080 synced:0 window_ms:61605
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-76 rssi_med:-73 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-83 rssi_med:-81 rssi_max:-79
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-94 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000200 proto:ble n:30 rssi_min:-99 rssi_med:-95 rssi_max:-92
**LINK** peer:0x00000011 proto:ble n:10 rssi_min:-98 rssi_med:-96 rssi_max:-94

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:308588 synced:0 window_ms:61508
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-92 rssi_med:-90 rssi_max:-87
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-70 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000200 proto:ble n:24 rssi_min:-98 rssi_med:-95 rssi_max:-92
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-84 rssi_med:-82 rssi_max:-78
**LINK** peer:0x00000011 proto:ble n:16 rssi_min:-99 rssi_med:-96 rssi_max:-93

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:370079 synced:0 window_ms:61491
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-92 rssi_med:-90 rssi_max:-85
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-73 rssi_med:-70 rssi_max:-66
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-84 rssi_med:-82 rssi_max:-80
**LINK** peer:0x00000200 proto:ble n:33 rssi_min:-100 rssi_med:-95 rssi_max:-93
**LINK** peer:0x00000011 proto:ble n:12 rssi_min:-100 rssi_med:-96 rssi_max:-95

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:431579 synced:0 window_ms:61500
**LINK** peer:0x00000200 proto:ble n:36 rssi_min:-98 rssi_med:-94 rssi_max:-91
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-79 rssi_med:-74 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-81 rssi_med:-79 rssi_max:-79
**LINK** peer:0x00000011 proto:ble n:26 rssi_min:-100 rssi_med:-95 rssi_max:-91
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-94 rssi_med:-91 rssi_max:-88

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:493084 synced:0 window_ms:61505
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-85 rssi_med:-75 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:40 rssi_min:-97 rssi_med:-95 rssi_max:-91
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-82 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-95 rssi_med:-93 rssi_max:-89
**LINK** peer:0x00000011 proto:ble n:20 rssi_min:-97 rssi_med:-95 rssi_max:-94

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:554974 synced:0 window_ms:61890
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-78 rssi_med:-74 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:26 rssi_min:-100 rssi_med:-95 rssi_max:-92
**LINK** peer:0x00000200 proto:ble n:43 rssi_min:-99 rssi_med:-93 rssi_max:-90
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-95 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-81 rssi_med:-80 rssi_max:-78

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:614510 synced:0 window_ms:550302 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e0c25086ede3 n:1 rssi:-95

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:616946 synced:0 window_ms:61972
**LINK** peer:0x00000011 proto:espnow n:11 rssi_min:-95 rssi_med:-90 rssi_max:-87
**LINK** peer:0x00000200 proto:ble n:41 rssi_min:-99 rssi_med:-94 rssi_max:-89
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-82 rssi_med:-79 rssi_max:-78
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-84 rssi_med:-77 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:18 rssi_min:-100 rssi_med:-97 rssi_max:-92

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:678509 synced:0 window_ms:61563
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-92 rssi_med:-86 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-84 rssi_med:-82 rssi_max:-79
**LINK** peer:0x00000011 proto:ble n:27 rssi_min:-100 rssi_med:-92 rssi_max:-68
**LINK** peer:0x00000200 proto:ble n:32 rssi_min:-100 rssi_med:-96 rssi_max:-91
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-73 rssi_med:-71 rssi_max:-69

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:738509 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-76 rssi_med:-50 rssi_max:-45
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-93 rssi_med:-78 rssi_max:-68
**LINK** peer:0x00000011 proto:espnow n:11 rssi_min:-54 rssi_med:-39 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-90 rssi_med:-82 rssi_max:-80
**LINK** peer:0x00000200 proto:ble n:29 rssi_min:-96 rssi_med:-94 rssi_max:-91

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:798541 synced:0 window_ms:60032
**LINK** peer:0x00000100 proto:espnow n:30 rssi_min:-82 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-82 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-41 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:30 rssi_min:-97 rssi_med:-92 rssi_max:-90
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-79 rssi_med:-49 rssi_max:-46

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:858542 synced:0 window_ms:60001
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-52 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:41 rssi_min:-98 rssi_med:-93 rssi_max:-90
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-83 rssi_med:-80 rssi_max:-77
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-36 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-82 rssi_med:-80 rssi_max:-78

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:918548 synced:0 window_ms:60006
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-31 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000100 proto:espnow n:30 rssi_min:-85 rssi_med:-81 rssi_max:-76
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-83 rssi_med:-81 rssi_max:-79
**LINK** peer:0x00000200 proto:ble n:30 rssi_min:-99 rssi_med:-93 rssi_max:-89

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:978548 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-97 rssi_med:-92 rssi_max:-63
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-85 rssi_med:-75 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-92 rssi_med:-83 rssi_max:-80
**LINK** peer:0x00000200 proto:ble n:22 rssi_min:-98 rssi_med:-93 rssi_max:-90
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-94 rssi_med:-78 rssi_max:-68

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1038548 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-97 rssi_med:-93 rssi_max:-90
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-79 rssi_med:-74 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-86 rssi_med:-78 rssi_max:-70
**LINK** peer:0x00000011 proto:espnow n:11 rssi_min:-90 rssi_med:-87 rssi_max:-86
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-97 rssi_med:-89 rssi_max:-78

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1098548 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-91 rssi_med:-75 rssi_max:-67
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-79 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000200 proto:ble n:43 rssi_min:-97 rssi_med:-87 rssi_max:-78
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-92 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000011 proto:ble n:46 rssi_min:-98 rssi_med:-93 rssi_max:-90

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1158548 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-82 rssi_med:-78 rssi_max:-71
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-92 rssi_med:-89 rssi_max:-86
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-56 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-60 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-97 rssi_med:-94 rssi_max:-90

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210751 synced:0 window_ms:596241 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e0c25086ede3 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1218548 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-79 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-81 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:48 rssi_min:-100 rssi_med:-94 rssi_max:-91
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-94 rssi_med:-90 rssi_max:-86

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1278548 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-99 rssi_med:-93 rssi_max:-90
**LINK** peer:0x00000200 proto:ble n:69 rssi_min:-81 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-84 rssi_med:-80 rssi_max:-76
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-93 rssi_med:-87 rssi_max:-83
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-42 rssi_med:-40 rssi_max:-36

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-78 rssi_med:-63 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-91 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-74 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000011 proto:ble n:38 rssi_min:-94 rssi_med:-91 rssi_max:-89
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-97 rssi_med:-76 rssi_max:-59

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60442 synced:0 window_ms:60442 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-94
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000200 proto:ble n:35 rssi_min:-97 rssi_med:-92 rssi_max:-77
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-95 rssi_med:-92 rssi_max:-89
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-93 rssi_med:-87 rssi_max:-84
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-95 rssi_med:-84 rssi_max:-77

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:38 rssi_min:-97 rssi_med:-91 rssi_max:-89
**LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000011 proto:ble n:30 rssi_min:-100 rssi_med:-93 rssi_max:-90
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-82 rssi_med:-81 rssi_max:-79
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-89 rssi_med:-86 rssi_max:-84

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-71 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000011 proto:ble n:35 rssi_min:-100 rssi_med:-91 rssi_max:-89
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-82 rssi_med:-81 rssi_max:-76
**LINK** peer:0x00000011 proto:espnow n:9 rssi_min:-88 rssi_med:-87 rssi_max:-84
**LINK** peer:0x00000200 proto:ble n:42 rssi_min:-97 rssi_med:-91 rssi_max:-89
