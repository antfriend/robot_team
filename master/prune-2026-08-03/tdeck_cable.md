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

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x15ecaee3 wall:0 t_ms:0 node:0x200 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x26a1b82d wall:0 t_ms:1570668 node:0x200 from:0x300
**REMAP** prev_stream:0x15ecaee3 prev_t_ms:7353 offset_ms:1563315 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x26a1b82d wall:0 t_ms:1592668 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x26a1b82d wall:0 t_ms:1596668 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x26a1b82d wall:0 t_ms:1602668 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x26a1b82d wall:0 t_ms:1740668 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x26a1b82d wall:0 t_ms:1867645 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x26a1b82d wall:0 t_ms:2089688 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x59fb8ce8 wall:0 t_ms:204271 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6661032 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-53 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-65 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-29 rssi_med:-28 rssi_max:-28
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-46 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-42 rssi_med:-42 rssi_max:-42

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6721032 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-64 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-52 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-40 rssi_med:-39 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-65 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-59 rssi_med:-53 rssi_max:-46
**LINK** peer:0x00000001 proto:espnow n:10 rssi_min:-45 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:39 rssi_min:-45 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-45 rssi_med:-43 rssi_max:-41

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6731828 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-97
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-97

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6781046 stream:0x59fb8ce8 wall:0 window_ms:60014
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-66 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-62 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-51 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-31 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-56 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-47 rssi_med:-44 rssi_max:-43

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6841046 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-55 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-52 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-47 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-82 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-67 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000300 proto:espnow n:58 rssi_min:-33 rssi_med:-31 rssi_max:-29

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6901046 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:69 rssi_min:-82 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-42 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-33 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-63 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-52 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-52 rssi_med:-45 rssi_max:-43

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6961046 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-79 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-44 rssi_med:-31 rssi_max:-29
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-53 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-64 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-64 rssi_med:-54 rssi_max:-48
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-42 rssi_med:-41 rssi_max:-40

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7021046 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-41 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-42 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-55 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-63 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-72 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-64 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-36 rssi_med:-35 rssi_max:-35

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7081046 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-61 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-42 rssi_med:-39 rssi_max:-37
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-48 rssi_med:-39 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-45 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-64 rssi_med:-43 rssi_max:-34
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-80 rssi_med:-59 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-63 rssi_med:-57 rssi_max:-53

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7141046 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-38 rssi_med:-38 rssi_max:-37
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-59 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-68 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-57 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000001 proto:espnow n:3 rssi_min:-42 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-72 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-47 rssi_med:-45 rssi_max:-41

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7256026 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-55 rssi_med:-39 rssi_max:-31
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-54 rssi_med:-43 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-49 rssi_med:-41 rssi_max:-37
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-64 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-75 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-74 rssi_med:-55 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-80 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-64 rssi_med:-47 rssi_max:-45

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7256026 stream:0x59fb8ce8 wall:0 window_ms:60022 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-55
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7316026 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-78 rssi_med:-56 rssi_max:-49
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-42 rssi_med:-36 rssi_max:-31
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-73 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-65 rssi_med:-41 rssi_max:-37
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-59 rssi_med:-53 rssi_max:-42
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-70 rssi_med:-51 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-44 rssi_med:-34 rssi_max:-29
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-61 rssi_med:-40 rssi_max:-38

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7376026 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-40 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-53 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-45 rssi_med:-42 rssi_max:-37
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-39 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-80 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-54 rssi_max:-50

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7496430 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:39 rssi_min:-79 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-26 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000012 proto:espnow n:4 rssi_min:-36 rssi_med:-34 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-51 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-34 rssi_med:-33 rssi_max:-33

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7496430 stream:0x59fb8ce8 wall:0 window_ms:62040 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-97
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97
