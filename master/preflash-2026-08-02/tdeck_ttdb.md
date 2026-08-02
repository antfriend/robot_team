# T-Deck Fleet Map TTDB (semantic positioning SP6)

```mmpdb
db_id: tdeck-console-001
db_name: T-Deck Handheld Console - Fleet Map
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: tdeck-console
  role: handheld-console
  perspective: operator
  scope: fleet-command
  globe:
    frame: mesh-topology
    origin: "@LAT0LON0"
    mapping: "each record is a fleet node at its believed position; the map the mesh draws of itself (companion.py fleetmap from positions.md + proximity.md)"
    note: "2026-07-29: the K10 left this map (still on v1 firmware, off the band roster and off the current mesh) and the Cardputer joined it. Selecting a record here opens that node's INTEROCEPTION in the record pane, so the map is now navigable INTO each body, not just across the topology."
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

@LAT32LON34 | created:1750000000 | updated:1785276000 | relates:espnow@LAT0LON0,espnow@LAT35LON7,espnow@LAT30LON37

**POSITION** node:tdeck_1
name: T-Deck
x_m: 33.61  y_m: 31.87
sigma_m: 61.96   conf: 0.55
link V4-A: espnow 41.8m conf 0.75
link V4-B: espnow 27.2m conf 0.78
link Card: espnow 3.7m conf 0.60

---

@LAT0LON0 | created:1750000000 | updated:1785276000 | relates:espnow@LAT35LON7,espnow@LAT32LON34,espnow@LAT30LON37

**POSITION** node:v4a_bridge
name: V4-A
x_m: 0.00  y_m: -0.00
sigma_m: 57.72   conf: 0.55
link V4-B: espnow 37.1m conf 0.78
link T-Deck: espnow 41.8m conf 0.75
link Card: espnow 5.0m conf 0.55

---

@LAT35LON7 | created:1750000000 | updated:1785276000 | relates:espnow@LAT0LON0,espnow@LAT32LON34,espnow@LAT30LON37

**POSITION** node:v4b_relay
name: V4-B
x_m: 6.83  y_m: 34.78
sigma_m: 53.15   conf: 0.56
link V4-A: espnow 37.1m conf 0.78
link T-Deck: espnow 27.2m conf 0.78
link Card: espnow 3.9m conf 0.55

---

@LAT30LON37 | created:1785190256 | updated:1785276000 | relates:espnow@LAT32LON34,espnow@LAT35LON7,espnow@LAT0LON0

**POSITION** node:cardputer_1
name: Card
x_m: 37.30  y_m: 30.10
sigma_m: 12.00   conf: 0.35
link T-Deck: espnow 3.7m conf 0.60
link V4-B: espnow 3.9m conf 0.55
link V4-A: espnow 5.0m conf 0.55
seed: unfused - own @LAT97 windows only, no SP2 embedding has included this node yet
evidence: its last link-percept window (master/cardputer_1.md @LAT97LON12) heard all
four peers over ESP-NOW at rssi_max -34 (T-Deck) / -35 (V4-B) / -40 (V4-A) / -40
(V4-C); the radii above are those through the SP1 calibration
RSSI(d) = -6.3 - 48.4*log10(d).
caveat: those radii are BENCH scale while the three static nodes above still carry
GARDEN-run coordinates (embedding_rev 4, 2026-07-13), so the drawn triangle is
INCONSISTENT on purpose rather than by accident - 3.7 + 5.0 cannot also be 41.8. The
fix is a fresh proximity -> positions -> fleetmap run with the whole fleet powered and
the bridge cabled, which needs hardware this session did not have. Believe the sigma,
not the dot.

---


---


---


---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:617340 synced:0 window_ms:555209 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:62127 synced:0 window_ms:62127 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85

---


---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360138 synced:0 window_ms:60078
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-79 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-74 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-91 rssi_med:-83 rssi_max:-77
**LINK** peer:0x00000011 proto:ble n:48 rssi_min:-95 rssi_med:-90 rssi_max:-80
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-77 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-30 rssi_med:-29 rssi_max:-27
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-47 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-58 rssi_med:-56 rssi_max:-55

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420138 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-61 rssi_max:-57
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-96 rssi_med:-90 rssi_max:-81
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-47 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-57 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-30 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-87 rssi_med:-81 rssi_max:-78
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-46 rssi_med:-45 rssi_max:-43

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480138 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-60 rssi_max:-59
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-72 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-95 rssi_med:-90 rssi_max:-79
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-92 rssi_med:-81 rssi_max:-78
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-81 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-48 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-61 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-30 rssi_med:-29 rssi_max:-28

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540147 synced:0 window_ms:60009
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-89 rssi_med:-84 rssi_max:-78
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-75 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-79 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-49 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-57 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-30 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-97 rssi_med:-89 rssi_max:-81

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600147 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-90 rssi_med:-83 rssi_max:-79
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-58 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-30 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-81 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-60 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-96 rssi_med:-87 rssi_max:-81

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:615763 synced:0 window_ms:553636 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660147 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-84 rssi_med:-83 rssi_max:-83
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-81 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-92 rssi_med:-90 rssi_max:-81
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-46 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-73 rssi_max:-69
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-57 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-30 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-81 rssi_med:-60 rssi_max:-59

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720147 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-71 rssi_max:-69
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-92 rssi_med:-82 rssi_max:-78
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:44 rssi_min:-97 rssi_med:-90 rssi_max:-80
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-56 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-35 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-48 rssi_med:-45 rssi_max:-44

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-74 rssi_med:-50 rssi_max:-36
**LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-37 rssi_med:-34 rssi_max:-29

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60028 synced:0 window_ms:60028 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-65
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-42 rssi_med:-34 rssi_max:-29
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-51 rssi_max:-43

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-36 rssi_med:-34 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-50 rssi_max:-44

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-56 rssi_med:-38 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-35 rssi_med:-23 rssi_max:-21

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-64 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-52 rssi_med:-50 rssi_max:-21

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-75 rssi_med:-50 rssi_max:-46
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-78 rssi_med:-66 rssi_max:-60

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-53 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:71 rssi_min:-70 rssi_med:-60 rssi_max:-56

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-50 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-60 rssi_max:-57

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-64 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-52 rssi_med:-48 rssi_max:-46

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-49 rssi_med:-48 rssi_max:-48
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-64 rssi_med:-62 rssi_max:-58

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610963 synced:0 window_ms:550935 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-61
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-96
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-98

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-64 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-50 rssi_med:-49 rssi_max:-48

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-64 rssi_med:-61 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-50 rssi_med:-49 rssi_max:-48

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:12 rssi_min:-29 rssi_med:-27 rssi_max:-26

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60044 synced:0 window_ms:60044 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-28 rssi_med:-27 rssi_max:-26
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-44 rssi_max:-41

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:73 rssi_min:-81 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-28 rssi_med:-27 rssi_max:-26

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-28 rssi_med:-27 rssi_max:-26

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-27 rssi_med:-27 rssi_max:-26

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-28 rssi_med:-27 rssi_max:-25

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-28 rssi_med:-27 rssi_max:-26
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-79 rssi_med:-42 rssi_max:-40

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-45 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-29 rssi_med:-27 rssi_max:-26

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:40 rssi_min:-80 rssi_med:-43 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:21 rssi_min:-28 rssi_med:-26 rssi_max:-25

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60032 synced:0 window_ms:60032 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-95
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-96
