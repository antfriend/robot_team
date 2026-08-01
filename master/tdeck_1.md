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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180070 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-71 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:47 rssi_min:-96 rssi_med:-86 rssi_max:-77
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-30 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000011 proto:espnow n:31 rssi_min:-90 rssi_med:-83 rssi_max:-78
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-56 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-47 rssi_med:-45 rssi_max:-44

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240139 synced:0 window_ms:60069
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-46 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-93 rssi_med:-86 rssi_max:-79
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-62 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-85 rssi_med:-83 rssi_max:-80
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-71 rssi_max:-68

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300200 synced:0 window_ms:60061
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-93 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-79 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-58 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-86 rssi_med:-84 rssi_max:-82
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-30 rssi_med:-29 rssi_max:-28

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360200 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-92 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-58 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-79 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-85 rssi_med:-84 rssi_max:-83
**LINK** peer:0x00000300 proto:ble n:51 rssi_min:-81 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-29 rssi_med:-28 rssi_max:-28

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420200 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-92 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-58 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-86 rssi_med:-84 rssi_max:-83
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-46 rssi_med:-45 rssi_max:-45

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480200 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-80 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-48 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-92 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-57 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-86 rssi_med:-85 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-30 rssi_med:-28 rssi_max:-28

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540200 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-82 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-84 rssi_med:-84 rssi_max:-82
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-30 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-60 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-92 rssi_med:-86 rssi_max:-79

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600200 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-92 rssi_med:-86 rssi_max:-79
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-81 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-58 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-85 rssi_med:-84 rssi_max:-82
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-61 rssi_max:-59
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-30 rssi_med:-28 rssi_max:-28

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:617340 synced:0 window_ms:555209 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660200 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-60 rssi_max:-59
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-58 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-92 rssi_med:-87 rssi_max:-80
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-84 rssi_med:-83 rssi_max:-82
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-81 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-47 rssi_med:-45 rssi_max:-45
