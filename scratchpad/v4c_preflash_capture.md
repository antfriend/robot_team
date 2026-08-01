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

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610294 synced:0 window_ms:550294 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210294 synced:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60253 synced:0 window_ms:60253 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60298 synced:0 window_ms:60298 entities:12
**ENTITY** kind:wifi_ap id:cc5830efdbe7 n:1 rssi:-57
**ENTITY** kind:wifi_ap id:026ae3f1361d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:026ae3f1361f n:1 rssi:-83
**ENTITY** kind:wifi_ap id:60b76e6c8f17 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:60b76e80dbdc n:1 rssi:-83
**ENTITY** kind:wifi_ap id:026ae3f13617 n:1 rssi:-84
**ENTITY** kind:wifi_ap id:78d6d67da8a5 n:1 rssi:-84
**ENTITY** kind:wifi_ap id:60b76e80e201 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:9009d031a7ed n:1 rssi:-90
**ENTITY** kind:wifi_ap id:647b1ec95706 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:784558ecc28a n:1 rssi:-93
**ENTITY** kind:wifi_ap id:688f2e20e4d8 n:1 rssi:-93

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60146 synced:0 window_ms:60146 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-67
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60191 synced:0 window_ms:60191 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610454 synced:0 window_ms:550263 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60232 synced:0 window_ms:60232 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60455 synced:0 window_ms:60455 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610692 synced:0 window_ms:550237 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-92

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610775 synced:0 window_ms:550775 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210775 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1810775 synced:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2410775 synced:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3010775 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-92

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3610775 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4210775 synced:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-92

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-91

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610742 synced:0 window_ms:550742 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-91

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-92

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610897 synced:0 window_ms:550897 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210897 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1810897 synced:0 window_ms:600000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2410897 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60006 synced:0 window_ms:60006 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-96

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60006 synced:0 window_ms:60006 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610624 synced:0 window_ms:550618 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60011 synced:0 window_ms:60011 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610769 synced:0 window_ms:550769 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210768 synced:0 window_ms:599999 entities:11
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-96

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1810778 synced:0 window_ms:600010 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-65
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2410777 synced:0 window_ms:599999 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3010777 synced:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3610778 synced:0 window_ms:600001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4210777 synced:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4810808 synced:0 window_ms:600031 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-23
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300006 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-77 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:67 rssi_min:-81 rssi_med:-78 rssi_max:-75
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-55 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:38 rssi_min:-63 rssi_med:-61 rssi_max:-60

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360006 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-67 rssi_med:-64 rssi_max:-59
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-60 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-87 rssi_med:-79 rssi_max:-71
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000300 proto:espnow n:59 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-55 rssi_med:-54 rssi_max:-53

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420039 synced:0 window_ms:60033
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000200 proto:espnow n:32 rssi_min:-65 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-82 rssi_med:-78 rssi_max:-75
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-56 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-74 rssi_max:-64

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480043 synced:0 window_ms:60004
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-81 rssi_med:-67 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-62 rssi_med:-59 rssi_max:-59
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-65 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-57 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-82 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-83 rssi_med:-77 rssi_max:-71

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540043 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-64 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-80 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-56 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-75 rssi_max:-72

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600043 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-83 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-62 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-56 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-84 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-78 rssi_max:-74
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-69 rssi_med:-65 rssi_max:-61

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660043 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:47 rssi_min:-86 rssi_med:-76 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-83 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000010 proto:espnow n:11 rssi_min:-56 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-68 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-62 rssi_med:-59 rssi_max:-58

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720043 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-55 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-77 rssi_max:-71
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-54 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-65 rssi_med:-62 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-78 rssi_max:-75
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-60 rssi_med:-59 rssi_max:-58

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:780043 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-82 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-54 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-64 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-84 rssi_med:-75 rssi_max:-72
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-55 rssi_med:-54 rssi_max:-53

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:840043 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-89 rssi_med:-80 rssi_max:-73
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-64 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-54 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-54 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-65 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-76 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-62 rssi_max:-59

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:900043 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-83 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-88 rssi_med:-81 rssi_max:-74
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-53 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-65 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-60 rssi_med:-59 rssi_max:-57

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:960043 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-92 rssi_med:-80 rssi_max:-73
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-53 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-65 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-56 rssi_med:-53 rssi_max:-49

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1020043 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-91 rssi_med:-80 rssi_max:-73
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-60 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-57 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-65 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-55 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-80 rssi_med:-77 rssi_max:-73

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1080043 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-90 rssi_med:-79 rssi_max:-72
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-54 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-82 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-65 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-60 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:116 rssi_min:-54 rssi_med:-53 rssi_max:-51

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1140043 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-69 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-85 rssi_med:-79 rssi_max:-73
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-59 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000001 proto:espnow n:16 rssi_min:-57 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-56 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:67 rssi_min:-54 rssi_med:-53 rssi_max:-51

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1200043 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-80 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-80 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-62 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-84 rssi_med:-77 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-66 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-58 rssi_med:-55 rssi_max:-53

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1260043 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-59 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-65 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-57 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-82 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000200 proto:ble n:48 rssi_min:-82 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000010 proto:espnow n:8 rssi_min:-55 rssi_med:-54 rssi_max:-53

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1320043 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-74 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-59 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000200 proto:ble n:48 rssi_min:-82 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-64 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-82 rssi_med:-78 rssi_max:-75
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-56 rssi_med:-54 rssi_max:-53

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1380043 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-83 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-82 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-59 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-65 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-55 rssi_med:-54 rssi_max:-54
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-54 rssi_med:-53 rssi_max:-52

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1440043 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:50 rssi_min:-82 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-59 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-55 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-66 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-57 rssi_med:-54 rssi_max:-54

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1500043 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-83 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-86 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-60 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-67 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-58 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-76 rssi_max:-75

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1560043 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-83 rssi_med:-68 rssi_max:-62
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-67 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-85 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-57 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-60 rssi_med:-58 rssi_max:-57

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1620043 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-85 rssi_med:-76 rssi_max:-72
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-82 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-68 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-60 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-65 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-56 rssi_med:-54 rssi_max:-52

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1680043 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-96 rssi_med:-79 rssi_max:-74
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-60 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-75 rssi_med:-70 rssi_max:-62
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-84 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:11 rssi_min:-56 rssi_med:-55 rssi_max:-54

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1740043 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-87 rssi_med:-79 rssi_max:-75
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000011 proto:ble n:70 rssi_min:-82 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-85 rssi_med:-68 rssi_max:-65
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:11 rssi_min:-57 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-67 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-60 rssi_med:-58 rssi_max:-58

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1800043 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:68 rssi_min:-81 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-68 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-60 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-83 rssi_med:-79 rssi_max:-75
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-56 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-67 rssi_med:-65 rssi_max:-63

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1860043 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:67 rssi_min:-80 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-93 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-72 rssi_max:-64
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-59 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-68 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-55 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-56 rssi_med:-54 rssi_max:-53

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1920043 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-92 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-60 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-58 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-69 rssi_med:-64 rssi_max:-60

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1980043 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-90 rssi_med:-81 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-81 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-60 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-66 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-56 rssi_med:-54 rssi_max:-52

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2040043 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:46 rssi_min:-82 rssi_med:-68 rssi_max:-62
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-87 rssi_med:-79 rssi_max:-70
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-67 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-60 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:7 rssi_min:-58 rssi_med:-55 rssi_max:-53

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2100043 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-54 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-95 rssi_med:-78 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-83 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-70 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-60 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-55 rssi_med:-54 rssi_max:-53

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2160043 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-55 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:40 rssi_min:-89 rssi_med:-81 rssi_max:-73
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-62 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:10 rssi_min:-65 rssi_med:-64 rssi_max:-62

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2220043 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-55 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-55 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-61 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-81 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-66 rssi_med:-64 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-91 rssi_med:-81 rssi_max:-73

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2280043 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-89 rssi_med:-80 rssi_max:-73
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-60 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-54 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-64 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-81 rssi_med:-76 rssi_max:-74

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2340043 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-88 rssi_med:-81 rssi_max:-74
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-64 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-61 rssi_max:-61
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-81 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-81 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-54 rssi_med:-53 rssi_max:-52

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2400050 synced:0 window_ms:60007
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-89 rssi_med:-80 rssi_max:-73
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-54 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-81 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-82 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-60 rssi_med:-58 rssi_max:-57
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-65 rssi_med:-64 rssi_max:-63

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2460050 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-91 rssi_med:-81 rssi_max:-73
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-81 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-81 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-79 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:11 rssi_min:-65 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-54 rssi_med:-53 rssi_max:-53

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2520050 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-57 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-55 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-92 rssi_med:-80 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-68 rssi_max:-63
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-67 rssi_med:-64 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-60 rssi_med:-58 rssi_max:-58

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2580074 synced:0 window_ms:60024
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-60 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-83 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:48 rssi_min:-93 rssi_med:-84 rssi_max:-72
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-75 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-55 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-90 rssi_med:-76 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-68 rssi_med:-64 rssi_max:-62

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2640074 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-57 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:13 rssi_min:-74 rssi_med:-69 rssi_max:-65
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-91 rssi_med:-81 rssi_max:-73
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-87 rssi_med:-78 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-68 rssi_med:-65 rssi_max:-61

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2700074 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-68 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:48 rssi_min:-96 rssi_med:-81 rssi_max:-74
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-82 rssi_med:-79 rssi_max:-72
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-73 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:11 rssi_min:-76 rssi_med:-70 rssi_max:-65
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-56 rssi_med:-54 rssi_max:-53

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2760074 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-85 rssi_med:-73 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-92 rssi_med:-77 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-94 rssi_med:-79 rssi_max:-72
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-56 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-67 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-66 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:11 rssi_min:-74 rssi_med:-67 rssi_max:-66

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2820074 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-80 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:71 rssi_min:-83 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-62 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-76 rssi_med:-73 rssi_max:-64
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-96 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-65 rssi_med:-65 rssi_max:-64

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2880087 synced:0 window_ms:60013
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000300 proto:espnow n:64 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-75 rssi_med:-73 rssi_max:-70
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-61 rssi_max:-61
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-56 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-82 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000200 proto:ble n:45 rssi_min:-95 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-65 rssi_med:-65 rssi_max:-64

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2940087 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-56 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000300 proto:ble n:71 rssi_min:-81 rssi_med:-61 rssi_max:-61
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-96 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-65 rssi_med:-65 rssi_max:-64
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-74 rssi_med:-73 rssi_max:-71

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3000087 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-97 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-68 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-74 rssi_med:-73 rssi_max:-67
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-54 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-67 rssi_med:-65 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-57 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-84 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-82 rssi_med:-66 rssi_max:-64

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3060087 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-65 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-89 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-85 rssi_med:-68 rssi_max:-64
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-57 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-73 rssi_med:-68 rssi_max:-64
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-93 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:12 rssi_min:-68 rssi_med:-64 rssi_max:-61

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3120087 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-57 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-56 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-91 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-90 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-70 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-89 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-79 rssi_med:-71 rssi_max:-66
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-64 rssi_med:-63 rssi_max:-60
