# K10 Percept Node TTDB

```mmpdb
db_id: k10-percept-001
db_name: K10 Percept Node
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: k10-percept
  role: percept-capture
  perspective: first-person-sensor
  scope: local-cluster
  constraints:
    - no-lora
    - espnow-default
  globe:
    frame: sensor-grid
    origin: "@LAT0LON0"
    mapping: "ambient sensors quantized onto the lat/lon knowledge grid"
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

@LAT0LON0 | created:1750000000 | updated:1750000000 | relates:navigates_to@LAT10LON0

Home node. Idle perception state. The agent rests here until a sensor reading
quantizes elsewhere on the grid.

---

@LAT10LON0 | created:1750000000 | updated:1750000000 | relates:triggers@LAT10LON0,logs@LAT0LON0

Warm ambient region. Reached when the temperature sensor reads into the upper
band. `triggers` fires the local indicator; `logs` records the observation.

---

@LAT99LON0 | created:1782170699 | updated:1782170699 | relates:logs@LAT0LON0

**SYNC** id:1 t_ms:1782170699715 recv_ms:103890 offset_ms:1782170595825

---

@LAT99LON1 | created:1782170835 | updated:1782170835 | relates:logs@LAT0LON0

**SYNC** id:2 t_ms:1782170835676 recv_ms:239291 offset_ms:1782170596385

---

@LAT98LON0 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:1 bytes:978 crc:65118C32 recv_ms:14537

---

@LAT98LON1 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:2 bytes:978 crc:65118C32 recv_ms:19353

---

@LAT98LON2 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:3 bytes:978 crc:65118C32 recv_ms:30571

---

@LAT98LON3 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:3 bytes:978 crc:65118C32 recv_ms:69125

---

@LAT98LON4 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:4 bytes:978 crc:65118C32 recv_ms:254982

---

@LAT98LON5 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:5 bytes:1121 crc:78BA4258 recv_ms:51732 applied:interval_ms:300

---

@LAT98LON6 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:5 bytes:1121 crc:78BA4258 recv_ms:70501 applied:interval_ms:300

---

@LAT98LON7 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:6 bytes:1121 crc:F69589F6 recv_ms:231581 applied:interval_ms:700

---

@LAT98LON8 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:7 bytes:1121 crc:78BA4258 recv_ms:18516 applied:interval_ms:300

---

@LAT98LON9 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:8 bytes:1121 crc:78BA4258 recv_ms:57087 applied:interval_ms:300

---

@LAT99LON2 | created:1782429925 | updated:1782429925 | relates:logs@LAT0LON0

**SYNC** id:3 t_ms:1782429925125 recv_ms:1293165 offset_ms:1782428631960

---

@LAT99LON3 | created:1782430029 | updated:1782430029 | relates:logs@LAT0LON0

**SYNC** id:4 t_ms:1782430029108 recv_ms:1397154 offset_ms:1782428631954

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:608825 synced:0 window_ms:548825 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1208628 synced:0 window_ms:599803 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1808625 synced:0 window_ms:599997 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2408825 synced:0 window_ms:600200 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3008826 synced:0 window_ms:600001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-63
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-88

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:609114 synced:0 window_ms:549114 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-63
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1209116 synced:0 window_ms:600002 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-87

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1809315 synced:0 window_ms:600199 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-86
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-88

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2409320 synced:0 window_ms:600005 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-67
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-88

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3009316 synced:0 window_ms:599996 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-89

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3609314 synced:0 window_ms:599998 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-67
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-85
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-88

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4209115 synced:0 window_ms:599801 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4809314 synced:0 window_ms:600199 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5409314 synced:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-66
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-87

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6009316 synced:0 window_ms:600002 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-67
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6609114 synced:0 window_ms:599798 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:609065 synced:0 window_ms:549065 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60110 synced:0 window_ms:60110 entities:2
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
