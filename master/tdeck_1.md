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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:16 rssi_min:-40 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-43 rssi_max:-37

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:62068 synced:0 window_ms:62068 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-45
**LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-40 rssi_med:-34 rssi_max:-31

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60020 synced:0 window_ms:60020
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-35 rssi_med:-30 rssi_max:-26
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-80 rssi_med:-44 rssi_max:-40

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:62061 synced:0 window_ms:62061 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-98

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120020 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-30 rssi_med:-30 rssi_max:-29

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180020 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-79 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240040 synced:0 window_ms:60020
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-30 rssi_med:-30 rssi_max:-29

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300040 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360117 synced:0 window_ms:60077
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-30 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-44 rssi_max:-44

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-53 rssi_med:-44 rssi_max:-44

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:615182 synced:0 window_ms:553121 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-79 rssi_med:-44 rssi_max:-44

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-79 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:780117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-53 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:840117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-68 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:900117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-79 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:960117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-79 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1020117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-79 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1080117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-44 rssi_max:-44

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1140117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1200117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1215182 synced:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1260117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-44 rssi_max:-44

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1320117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1380117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1440117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-81 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:21 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1500117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1560117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-30 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-80 rssi_med:-44 rssi_max:-44

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1620117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-44 rssi_max:-44

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1680117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-44 rssi_max:-44

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1740117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-53 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1800117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-53 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1815182 synced:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1860117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-79 rssi_med:-44 rssi_max:-44

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1920117 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60067 synced:0 window_ms:60067
**LINK** peer:0x00000300 proto:espnow n:17 rssi_min:-30 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-80 rssi_med:-44 rssi_max:-42

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60102 synced:0 window_ms:60102 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120067 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-50 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-37 rssi_med:-32 rssi_max:-29

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180159 synced:0 window_ms:60092
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-51 rssi_max:-50
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-36 rssi_med:-32 rssi_max:-32

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240159 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-51 rssi_max:-50
**LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-36 rssi_med:-32 rssi_max:-32

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300159 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-51 rssi_max:-50
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-37 rssi_med:-32 rssi_max:-32

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360159 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:19 rssi_min:-36 rssi_med:-32 rssi_max:-28
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-59 rssi_med:-50 rssi_max:-41

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420159 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-33 rssi_med:-29 rssi_max:-27
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-45 rssi_max:-40

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480159 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-55 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-34 rssi_med:-30 rssi_max:-28

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540159 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-79 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-35 rssi_med:-33 rssi_max:-30

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:18 rssi_min:-34 rssi_med:-33 rssi_max:-30

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:62017 synced:0 window_ms:62017 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
