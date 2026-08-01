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

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61188 synced:0 window_ms:61188 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61996 synced:0 window_ms:61996 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60006 synced:0 window_ms:60006 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:609850 synced:0 window_ms:549844 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-96

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1209861 synced:0 window_ms:600011 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-95
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1809862 synced:0 window_ms:600001 entities:11
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2409865 synced:0 window_ms:600003 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3009866 synced:0 window_ms:600001 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-95
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-96

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3609865 synced:0 window_ms:599999 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60006 synced:0 window_ms:60006 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-67
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-94

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610172 synced:0 window_ms:550172 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-57
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:d2102f3f25ea n:1 rssi:-91
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-92

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210172 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-58
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:ce102f3f25ea n:1 rssi:-90
**ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-92

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1810172 synced:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-58
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-88

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2410172 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-57
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3010172 synced:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61327 synced:0 window_ms:61327 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-25
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:62683 synced:0 window_ms:62683 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60139 synced:0 window_ms:60139 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-96

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:609795 synced:0 window_ms:549656 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-55
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-90
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-91
**ENTITY** kind:wifi_ap id:ce102f3f25ea n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-93

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1209795 synced:0 window_ms:600000 entities:11
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-54
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-94

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1809796 synced:0 window_ms:600001 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-55
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:d2102f3f25ea n:1 rssi:-89
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:8470d7633e07 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2409796 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-55
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:8470d7633e07 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-90
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:ce102f3f25ea n:1 rssi:-91
**ENTITY** kind:wifi_ap id:d2102f3f25ea n:1 rssi:-91

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3009795 synced:0 window_ms:599999 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-55
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:d2102f3f25ea n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-90
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:ce102f3f25ea n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-93

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-96

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610266 synced:0 window_ms:550266 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210266 synced:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60006 synced:0 window_ms:60006 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:62040 synced:0 window_ms:62040 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60006 synced:0 window_ms:60006 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-57
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60006 synced:0 window_ms:60006 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-92

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610975 synced:0 window_ms:550975 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210975 synced:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:cc5830efdbe7 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:60b76e80dbdc n:1 rssi:-88
**ENTITY** kind:wifi_ap id:026ae3f13617 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:784558ecc28a n:1 rssi:-91
**ENTITY** kind:wifi_ap id:026ae3f1361d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:026ae3f1361f n:1 rssi:-95

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-23
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2400220 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-78 rssi_med:-75 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-97 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000010 proto:ble n:44 rssi_min:-94 rssi_med:-88 rssi_max:-82
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-71 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-62 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-83 rssi_med:-79 rssi_max:-76
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-81 rssi_med:-76 rssi_max:-75

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2460221 synced:0 window_ms:60001
**LINK** peer:0x00000010 proto:ble n:41 rssi_min:-95 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-72 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000012 proto:espnow n:14 rssi_min:-61 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-83 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-96 rssi_med:-87 rssi_max:-81
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-82 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-77 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-81 rssi_med:-78 rssi_max:-74

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2520221 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-70 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-80 rssi_med:-75 rssi_max:-70
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-83 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-83 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-96 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-61 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000200 proto:ble n:41 rssi_min:-96 rssi_med:-88 rssi_max:-81
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-88 rssi_med:-84 rssi_max:-80

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2580221 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-78 rssi_max:-75
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-84 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-87 rssi_med:-82 rssi_max:-80
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-71 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000010 proto:ble n:45 rssi_min:-96 rssi_med:-92 rssi_max:-89
**LINK** peer:0x00000200 proto:ble n:41 rssi_min:-98 rssi_med:-88 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-81 rssi_med:-75 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-61 rssi_med:-61 rssi_max:-59

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2640221 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-97 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-61 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-83 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:48 rssi_min:-96 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-75 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000012 proto:ble n:67 rssi_min:-82 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-70 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-88 rssi_med:-83 rssi_max:-78

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2700221 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:39 rssi_min:-98 rssi_med:-89 rssi_max:-85
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:49 rssi_min:-95 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-61 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-83 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-87 rssi_med:-85 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-85 rssi_med:-75 rssi_max:-71
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-72 rssi_med:-70 rssi_max:-68

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2760221 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-83 rssi_med:-80 rssi_max:-76
**LINK** peer:0x00000010 proto:ble n:46 rssi_min:-97 rssi_med:-92 rssi_max:-85
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-88 rssi_med:-85 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-86 rssi_med:-82 rssi_max:-76
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-72 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:ble n:38 rssi_min:-98 rssi_med:-92 rssi_max:-87
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-61 rssi_med:-61 rssi_max:-59

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2820221 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-93 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:46 rssi_min:-96 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-66 rssi_med:-60 rssi_max:-59
**LINK** peer:0x00000010 proto:ble n:47 rssi_min:-97 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-90 rssi_med:-85 rssi_max:-80
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-83 rssi_med:-71 rssi_max:-67
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-90 rssi_med:-78 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-82 rssi_med:-80 rssi_max:-77

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2880221 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000010 proto:ble n:47 rssi_min:-94 rssi_med:-91 rssi_max:-80
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-89 rssi_med:-82 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-88 rssi_med:-82 rssi_max:-78
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000200 proto:ble n:47 rssi_min:-96 rssi_med:-91 rssi_max:-85
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-61 rssi_med:-60 rssi_max:-59

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2940221 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:42 rssi_min:-97 rssi_med:-88 rssi_max:-83
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-97 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-77 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-88 rssi_med:-83 rssi_max:-78
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-61 rssi_med:-60 rssi_max:-59

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3000221 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-97 rssi_med:-90 rssi_max:-86
**LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-88 rssi_med:-83 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:33 rssi_min:-74 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000010 proto:ble n:45 rssi_min:-95 rssi_med:-90 rssi_max:-84
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-75 rssi_max:-72
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-61 rssi_med:-60 rssi_max:-59

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3060221 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-86 rssi_med:-83 rssi_max:-78
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-77 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-81 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:47 rssi_min:-97 rssi_med:-91 rssi_max:-84
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-93 rssi_med:-90 rssi_max:-86

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3120221 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-90 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:47 rssi_min:-94 rssi_med:-90 rssi_max:-85
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:39 rssi_min:-97 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-74 rssi_med:-70 rssi_max:-68

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3180221 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:50 rssi_min:-83 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-82 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-98 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-73 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:46 rssi_min:-96 rssi_med:-90 rssi_max:-85
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-87 rssi_med:-85 rssi_max:-81
**LINK** peer:0x00000010 proto:espnow n:37 rssi_min:-72 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-60 rssi_med:-59 rssi_max:-58

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3240221 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-96 rssi_med:-91 rssi_max:-88
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-73 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000010 proto:espnow n:36 rssi_min:-72 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-89 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-59 rssi_med:-59 rssi_max:-59
**LINK** peer:0x00000010 proto:ble n:49 rssi_min:-97 rssi_med:-88 rssi_max:-83

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3300221 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-74 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-80 rssi_max:-77
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-86 rssi_med:-83 rssi_max:-80
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-74 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000010 proto:ble n:39 rssi_min:-98 rssi_med:-89 rssi_max:-83
**LINK** peer:0x00000200 proto:ble n:49 rssi_min:-98 rssi_med:-92 rssi_max:-88
**LINK** peer:0x00000012 proto:espnow n:133 rssi_min:-60 rssi_med:-59 rssi_max:-58

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3360221 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-73 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-75 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-95 rssi_med:-89 rssi_max:-82
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-87 rssi_med:-83 rssi_max:-79
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-97 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-60 rssi_med:-59 rssi_max:-59

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3420221 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-74 rssi_med:-71 rssi_max:-66
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-73 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-75 rssi_max:-71
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:46 rssi_min:-96 rssi_med:-90 rssi_max:-87
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-59 rssi_med:-59 rssi_max:-59
**LINK** peer:0x00000010 proto:ble n:49 rssi_min:-97 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-87 rssi_med:-83 rssi_max:-80

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3480221 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-97 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-73 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-59 rssi_med:-59 rssi_max:-59
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-87 rssi_med:-84 rssi_max:-79
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-96 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-74 rssi_med:-70 rssi_max:-68

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3540221 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-80 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-73 rssi_med:-71 rssi_max:-67
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-82 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-59 rssi_med:-59 rssi_max:-59
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-96 rssi_med:-91 rssi_max:-89
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-97 rssi_med:-89 rssi_max:-83
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-89 rssi_med:-84 rssi_max:-78

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3600221 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-73 rssi_med:-68 rssi_max:-67
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-97 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-74 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-75 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-85 rssi_med:-82 rssi_max:-78
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000010 proto:ble n:49 rssi_min:-98 rssi_med:-89 rssi_max:-82
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-79 rssi_max:-77

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3660221 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-70 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-73 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-62 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-82 rssi_med:-75 rssi_max:-71
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-97 rssi_med:-89 rssi_max:-85
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:50 rssi_min:-94 rssi_med:-92 rssi_max:-89
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-84 rssi_med:-83 rssi_max:-82

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3720221 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-69 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-96 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-75 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-84 rssi_med:-83 rssi_max:-81
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-96 rssi_med:-89 rssi_max:-86
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-78 rssi_max:-77

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3780221 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-94 rssi_med:-91 rssi_max:-88
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-85 rssi_med:-83 rssi_max:-82
**LINK** peer:0x00000010 proto:ble n:46 rssi_min:-96 rssi_med:-88 rssi_max:-85
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-75 rssi_max:-71
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-69 rssi_med:-68 rssi_max:-67

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3840221 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-69 rssi_med:-68 rssi_max:-68
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-97 rssi_med:-89 rssi_max:-86
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-95 rssi_med:-90 rssi_max:-87
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-60 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-85 rssi_med:-83 rssi_max:-81
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-75 rssi_max:-73

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3900221 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-75 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000300 proto:espnow n:143 rssi_min:-77 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-96 rssi_med:-90 rssi_max:-87
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-60 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000010 proto:ble n:49 rssi_min:-96 rssi_med:-89 rssi_max:-82
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-86 rssi_med:-80 rssi_max:-77

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3960221 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-96 rssi_med:-89 rssi_max:-86
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-70 rssi_med:-70 rssi_max:-70
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-81 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000010 proto:ble n:41 rssi_min:-95 rssi_med:-90 rssi_max:-83
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-59 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-84 rssi_med:-79 rssi_max:-77

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4020221 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-81 rssi_med:-74 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-95 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-59 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-94 rssi_med:-89 rssi_max:-81
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-88 rssi_med:-82 rssi_max:-78
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-74 rssi_med:-72 rssi_max:-68
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-79 rssi_max:-77

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4080236 synced:0 window_ms:60015
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-95 rssi_med:-88 rssi_max:-83
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-94 rssi_med:-91 rssi_max:-88
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-84 rssi_med:-81 rssi_max:-79
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-70 rssi_med:-68 rssi_max:-68
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-81 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-76 rssi_med:-70 rssi_max:-69

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4140236 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-94 rssi_med:-91 rssi_max:-89
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-59 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-95 rssi_med:-88 rssi_max:-85
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-69 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-81 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-82 rssi_med:-80 rssi_max:-80

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4200236 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-95 rssi_med:-87 rssi_max:-84
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-59 rssi_med:-58 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-81 rssi_med:-80 rssi_max:-80
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-94 rssi_med:-91 rssi_max:-88
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-70 rssi_med:-68 rssi_max:-68

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4260236 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-61 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:45 rssi_min:-95 rssi_med:-90 rssi_max:-87
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-96 rssi_med:-90 rssi_max:-82
**LINK** peer:0x00000012 proto:ble n:49 rssi_min:-81 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-73 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-74 rssi_med:-72 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-86 rssi_med:-81 rssi_max:-77

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4320236 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000200 proto:ble n:43 rssi_min:-97 rssi_med:-90 rssi_max:-85
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-96 rssi_med:-87 rssi_max:-82
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-88 rssi_med:-79 rssi_max:-76
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-77 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-78 rssi_max:-77

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4380236 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-83 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-83 rssi_med:-78 rssi_max:-76
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-70 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000200 proto:ble n:47 rssi_min:-97 rssi_med:-91 rssi_max:-88
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-96 rssi_med:-87 rssi_max:-82
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-59 rssi_med:-59 rssi_max:-58

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4440262 synced:0 window_ms:60026
**LINK** peer:0x00000010 proto:ble n:46 rssi_min:-97 rssi_med:-90 rssi_max:-84
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-95 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-82 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-72 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-84 rssi_med:-79 rssi_max:-76
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-74 rssi_med:-71 rssi_max:-67

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4500262 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000300 proto:ble n:72 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-86 rssi_med:-80 rssi_max:-74
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-73 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000010 proto:espnow n:10 rssi_min:-73 rssi_med:-71 rssi_max:-67
**LINK** peer:0x00000010 proto:ble n:49 rssi_min:-96 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-98 rssi_med:-88 rssi_max:-85

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4560262 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-71 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-93 rssi_med:-89 rssi_max:-85
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-71 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-83 rssi_med:-81 rssi_max:-77
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000012 proto:ble n:51 rssi_min:-81 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-92 rssi_med:-89 rssi_max:-86

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4620262 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-82 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-81 rssi_med:-79 rssi_max:-76
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-74 rssi_max:-71
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-95 rssi_med:-88 rssi_max:-83
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-93 rssi_med:-88 rssi_max:-84
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-72 rssi_med:-69 rssi_max:-66

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4680262 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-72 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-72 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-91 rssi_med:-87 rssi_max:-83
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-78 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-95 rssi_med:-88 rssi_max:-83

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4740262 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:49 rssi_min:-97 rssi_med:-90 rssi_max:-85
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-87 rssi_med:-81 rssi_max:-74
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-82 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-77 rssi_med:-72 rssi_max:-68
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-80 rssi_max:-77
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-97 rssi_med:-90 rssi_max:-86
**LINK** peer:0x00000012 proto:espnow n:12 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-72 rssi_med:-70 rssi_max:-69

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4800262 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-98 rssi_med:-91 rssi_max:-83
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-80 rssi_max:-77
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-72 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-78 rssi_med:-76 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-97 rssi_med:-90 rssi_max:-86
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-90 rssi_med:-82 rssi_max:-78

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4860262 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-82 rssi_med:-80 rssi_max:-77
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:48 rssi_min:-96 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-89 rssi_med:-83 rssi_max:-79
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000010 proto:ble n:38 rssi_min:-97 rssi_med:-90 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:9 rssi_min:-72 rssi_med:-71 rssi_max:-69

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4920262 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-75 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-89 rssi_med:-83 rssi_max:-78
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-71 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000010 proto:ble n:45 rssi_min:-95 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-76 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000200 proto:ble n:47 rssi_min:-96 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-79 rssi_max:-75

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4980262 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000200 proto:espnow n:7 rssi_min:-83 rssi_med:-82 rssi_max:-78
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000200 proto:ble n:33 rssi_min:-94 rssi_med:-89 rssi_max:-86
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-80 rssi_med:-73 rssi_max:-69
**LINK** peer:0x00000010 proto:ble n:39 rssi_min:-97 rssi_med:-90 rssi_max:-85

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5040262 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-77 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-82 rssi_med:-80 rssi_max:-76
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-94 rssi_med:-91 rssi_max:-85
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-79 rssi_max:-76
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-74 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:33 rssi_min:-96 rssi_med:-91 rssi_max:-89
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-73 rssi_med:-71 rssi_max:-69

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5100262 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-60 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-71 rssi_med:-70 rssi_max:-70
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-82 rssi_med:-80 rssi_max:-77
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-82 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-93 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000010 proto:ble n:38 rssi_min:-93 rssi_med:-91 rssi_max:-89

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5160262 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000010 proto:ble n:41 rssi_min:-93 rssi_med:-92 rssi_max:-90
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-81 rssi_med:-80 rssi_max:-78
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-94 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-82 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-71 rssi_med:-71 rssi_max:-70

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5220262 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-79 rssi_max:-77
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:14 rssi_min:-61 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-93 rssi_med:-91 rssi_max:-87
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-72 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-82 rssi_med:-81 rssi_max:-79
**LINK** peer:0x00000010 proto:ble n:38 rssi_min:-93 rssi_med:-91 rssi_max:-89
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-71 rssi_med:-71 rssi_max:-70
