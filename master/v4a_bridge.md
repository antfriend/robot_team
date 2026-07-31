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

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60152 synced:0 window_ms:60152 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93

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

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:63630 synced:0 window_ms:63630 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89

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

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:63857 synced:0 window_ms:63857 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:613103 synced:0 window_ms:549246 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1216761 synced:0 window_ms:603658 entities:11
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1813002 synced:0 window_ms:596241 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-95
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-96

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:62000 synced:0 window_ms:62000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61054 synced:0 window_ms:61054 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60060 synced:0 window_ms:60060 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61145 synced:0 window_ms:61145 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60275 synced:0 window_ms:60275 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:614276 synced:0 window_ms:554001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60059 synced:0 window_ms:60059 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61144 synced:0 window_ms:61144 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61054 synced:0 window_ms:61054 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60635 synced:0 window_ms:60635 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60635 synced:0 window_ms:60635 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60724 synced:0 window_ms:60724 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61144 synced:0 window_ms:61144 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61144 synced:0 window_ms:61144 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60060 synced:0 window_ms:60060 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

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
