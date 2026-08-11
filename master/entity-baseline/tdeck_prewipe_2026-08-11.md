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

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbdc62024 wall:0 t_ms:17253 node:0x200 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:463764 stream:0xbdc62024 wall:0 node:0x00000200

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:527306 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-38 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-80 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-40 rssi_med:-39 rssi_max:-37
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:21 rssi_min:-33 rssi_med:-31 rssi_max:-30

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:587342 stream:0xbdc62024 wall:0 window_ms:60036
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-50 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-47 rssi_med:-33 rssi_max:-31
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-39 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-40 rssi_med:-38 rssi_max:-37

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:647342 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-42 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-46 rssi_med:-38 rssi_max:-36
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-79 rssi_med:-50 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-66 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-39 rssi_med:-33 rssi_max:-28
**LINK** peer:0x00000012 proto:ble n:34 rssi_min:-78 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:13 rssi_min:-62 rssi_med:-36 rssi_max:-32
**LINK** peer:0x00000011 proto:ble n:31 rssi_min:-67 rssi_med:-54 rssi_max:-50

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:707346 stream:0xbdc62024 wall:0 window_ms:60004
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-79 rssi_med:-50 rssi_max:-46
**LINK** peer:0x00000011 proto:ble n:25 rssi_min:-65 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:35 rssi_min:-81 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-36 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-45 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-68 rssi_med:-50 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-58 rssi_max:-52

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:767384 stream:0xbdc62024 wall:0 window_ms:60038
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-35 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-46 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-81 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-37 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-67 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-77 rssi_med:-52 rssi_max:-46
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-51 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000012 proto:ble n:47 rssi_min:-79 rssi_med:-60 rssi_max:-51

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:827384 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-34 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-46 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-79 rssi_med:-53 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-79 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:11 rssi_min:-59 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-37 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000012 proto:ble n:38 rssi_min:-80 rssi_med:-64 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-58 rssi_max:-50

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:887384 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-34 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-46 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:56 rssi_min:-38 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-52 rssi_max:-48
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-63 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-50 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-58 rssi_max:-51

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:947384 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-34 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-79 rssi_med:-52 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:51 rssi_min:-79 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-38 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:70 rssi_min:-79 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-55 rssi_med:-50 rssi_max:-42

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1007384 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:31 rssi_min:-34 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-59 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-65 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-58 rssi_med:-50 rssi_max:-46
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-47 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-52 rssi_med:-43 rssi_max:-40

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1067384 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-37 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-44 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-79 rssi_med:-50 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-79 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-80 rssi_med:-60 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-55 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:70 rssi_min:-81 rssi_med:-59 rssi_max:-54

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1127384 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-65 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-45 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-59 rssi_max:-47
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-49 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-49 rssi_med:-42 rssi_max:-40

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1187384 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-79 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-50 rssi_med:-32 rssi_max:-32
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-79 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-46 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-48 rssi_med:-45 rssi_max:-38
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-72 rssi_med:-51 rssi_max:-45
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-57 rssi_max:-52

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1247397 stream:0xbdc62024 wall:0 window_ms:60013
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-79 rssi_med:-60 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-71 rssi_med:-56 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-44 rssi_med:-41 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-62 rssi_med:-46 rssi_max:-32
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-51 rssi_med:-41 rssi_max:-36
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-52 rssi_med:-43 rssi_max:-37
**LINK** peer:0x00000012 proto:ble n:51 rssi_min:-70 rssi_med:-55 rssi_max:-52

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1307397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-55 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:73 rssi_min:-81 rssi_med:-56 rssi_max:-48
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-50 rssi_med:-42 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:14 rssi_min:-34 rssi_med:-34 rssi_max:-31
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-82 rssi_med:-60 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-50 rssi_med:-38 rssi_max:-30
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-57 rssi_med:-45 rssi_max:-41

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1367397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-82 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-45 rssi_med:-38 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-52 rssi_med:-41 rssi_max:-36
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-82 rssi_med:-62 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-58 rssi_med:-47 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-50 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-66 rssi_med:-59 rssi_max:-53

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1427397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-60 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-62 rssi_med:-59 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-80 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-39 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-50 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-59 rssi_med:-49 rssi_max:-47

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1487397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-53 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-79 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-60 rssi_max:-54
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-40 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-58 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-59 rssi_max:-53

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1547397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-80 rssi_med:-68 rssi_max:-59
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-56 rssi_max:-49
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-63 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000010 proto:ble n:70 rssi_min:-80 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-60 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-41 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-48 rssi_med:-46 rssi_max:-44

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1607397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:49 rssi_min:-62 rssi_med:-60 rssi_max:-54
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-56 rssi_max:-49
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-77 rssi_med:-65 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-43 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-70 rssi_med:-54 rssi_max:-48
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-57 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-45 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-59 rssi_max:-54

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1667397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-80 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-63 rssi_max:-57
**LINK** peer:0x00000300 proto:ble n:30 rssi_min:-81 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000300 proto:espnow n:9 rssi_min:-54 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-48 rssi_med:-39 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-58 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:37 rssi_min:-81 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-43 rssi_med:-41 rssi_max:-40

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1727397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-64 rssi_max:-59
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-69 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-62 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-41 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-40 rssi_med:-39 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-50 rssi_med:-49 rssi_max:-49
**LINK** peer:0x00000300 proto:ble n:40 rssi_min:-82 rssi_med:-62 rssi_max:-58

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1787397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-42 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-64 rssi_max:-59
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-42 rssi_med:-39 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-61 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-64 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-52 rssi_med:-49 rssi_max:-49

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1847397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-65 rssi_max:-59
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-54 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-43 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-58 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-79 rssi_med:-61 rssi_max:-58
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-83 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-42 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-81 rssi_med:-55 rssi_max:-50

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1907397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-79 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-41 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-60 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-50 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-42 rssi_med:-41 rssi_max:-41
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-48 rssi_med:-48 rssi_max:-47

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1967397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-44 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-50 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-81 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-43 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-55 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-81 rssi_med:-63 rssi_max:-59
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-63 rssi_max:-57

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2027397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-81 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-45 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-60 rssi_max:-56
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-49 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-44 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-61 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-49 rssi_med:-46 rssi_max:-42

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2087397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-64 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-49 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-45 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-81 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-60 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-59 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-81 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-45 rssi_med:-41 rssi_max:-40

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2147397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-43 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-51 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-79 rssi_med:-63 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-46 rssi_med:-41 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-50 rssi_med:-48 rssi_max:-46

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2207397 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-43 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-56 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-55 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-81 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-55 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-46 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-72 rssi_med:-60 rssi_max:-56

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2267415 stream:0xbdc62024 wall:0 window_ms:60018
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-82 rssi_med:-63 rssi_max:-59
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-43 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-58 rssi_med:-56 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-46 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-53 rssi_med:-46 rssi_max:-44

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2327415 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-81 rssi_med:-66 rssi_max:-60
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-79 rssi_med:-65 rssi_max:-57
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-59 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-62 rssi_med:-61 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-45 rssi_med:-44 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:13 rssi_min:-53 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-42 rssi_med:-40 rssi_max:-39

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2387415 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-62 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-81 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-46 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-41 rssi_med:-40 rssi_max:-39

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2447415 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-62 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-70 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-54 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-40 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-45 rssi_med:-44 rssi_max:-44

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2507429 stream:0xbdc62024 wall:0 window_ms:60014
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-63 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-45 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-53 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-41 rssi_med:-40 rssi_max:-39

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2567429 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-63 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-54 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-41 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-79 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-45 rssi_med:-44 rssi_max:-44

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2627429 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-58 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-40 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-63 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-79 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-45 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-54 rssi_med:-53 rssi_max:-52

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2687429 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-45 rssi_med:-44 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-40 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-63 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-79 rssi_med:-58 rssi_max:-51

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2747429 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-80 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-80 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-63 rssi_med:-61 rssi_max:-61
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-54 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-40 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000012 proto:espnow n:12 rssi_min:-45 rssi_med:-44 rssi_max:-44

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2807429 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-72 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-84 rssi_med:-67 rssi_max:-60
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-66 rssi_med:-61 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-62 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-74 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-80 rssi_med:-65 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-42 rssi_med:-40 rssi_max:-38

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2867429 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-71 rssi_max:-57
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-71 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:68 rssi_min:-79 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-45 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-68 rssi_med:-62 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:69 rssi_min:-81 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-43 rssi_med:-41 rssi_max:-40

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2927428 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-81 rssi_med:-71 rssi_max:-60
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-79 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-43 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-65 rssi_med:-60 rssi_max:-50
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-68 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-42 rssi_med:-42 rssi_max:-40

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2987429 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-64 rssi_max:-54
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-59 rssi_med:-55 rssi_max:-48
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-44 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-62 rssi_med:-52 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-45 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-60 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-65 rssi_max:-57

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3047459 stream:0xbdc62024 wall:0 window_ms:60030
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-61 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-41 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-51 rssi_med:-48 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-69 rssi_med:-62 rssi_max:-59
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-44 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-55 rssi_med:-53 rssi_max:-48

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3107459 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-64 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-82 rssi_med:-65 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-46 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-60 rssi_med:-53 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-81 rssi_med:-65 rssi_max:-59
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-43 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-79 rssi_med:-58 rssi_max:-49

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3167484 stream:0xbdc62024 wall:0 window_ms:60025
**LINK** peer:0x00000011 proto:ble n:73 rssi_min:-92 rssi_med:-73 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-79 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-68 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-45 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-78 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-41 rssi_med:-39 rssi_max:-38

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3227484 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-85 rssi_med:-70 rssi_max:-55
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-66 rssi_med:-61 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-59 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-42 rssi_med:-40 rssi_max:-39

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3287484 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-69 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-66 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-44 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-55 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-42 rssi_med:-41 rssi_max:-39

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3347500 stream:0xbdc62024 wall:0 window_ms:60016
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-79 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-66 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-82 rssi_med:-67 rssi_max:-56
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-61 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-66 rssi_max:-62
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-75 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-42 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-44 rssi_med:-43 rssi_max:-42

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xe7384824 wall:0 t_ms:37202 node:0x200 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xaf869fce wall:0 t_ms:9185 node:0x200 from:0x10
**REMAP** prev_stream:0x00144493 prev_t_ms:4621 offset_ms:4564 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x161e88ac wall:0 t_ms:1016973 node:0x200 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x41ba1242 wall:0 t_ms:1852959 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x6a2120c2 wall:0 t_ms:1206493 node:0x200 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xdffbae31 wall:0 t_ms:3683175 node:0x200 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:48 last_lon:47 t_ms:2515800 stream:0x9cf79991 wall:0 node:0x00000200

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52799 stream:0x9841b0fd wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:37169 stream:0x95cc309e wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1208793 stream:0x95cc309e wall:0 window_ms:600001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
**COVERED** windows:1 entities:4 window_ms:571624 first_t_ms:608791 last_t_ms:608791 covered_by:@LAT96LON1
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93 windows:1

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1349238 stream:0x95cc309e wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2531628 stream:0x95cc309e wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-98
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5ce28c488e0c,e6b32d2cea8b
**COVERED** windows:1 entities:6 window_ms:582392 first_t_ms:1931629 last_t_ms:1931629 covered_by:@LAT96LON3
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95 windows:1

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4316596 stream:0x95cc309e wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT101LON0 | sid:42caf4db | created:0 | updated:0 |
**PEER** node:0x00000300 spoke:1 declared:0x3fb7 verified:0x2fa7 exercised:0x0004 cap_epoch:7
**TRACE** copresence:255 half_life_ms:600000 reinforced:24 last_ms:59105
t_ms:68967 stream:0x6ceb85ae wall:0

---

@LAT101LON1 | sid:2665389c | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:61 half_life_ms:600000 reinforced:0 last_ms:1411
t_ms:68967 stream:0x6ceb85ae wall:0

---

@LAT101LON2 | sid:2136c351 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:1 half_life_ms:600000 reinforced:0 last_ms:1411
t_ms:68967 stream:0x6ceb85ae wall:0

---

@LAT101LON3 | sid:29653d55 | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:1 half_life_ms:600000 reinforced:0 last_ms:1411
t_ms:68967 stream:0x6ceb85ae wall:0

---

@LAT101LON4 | sid:27653a2f | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:61 half_life_ms:600000 reinforced:0 last_ms:1411
t_ms:68967 stream:0x6ceb85ae wall:0

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:68967 stream:0x6ceb85ae wall:0 window_ms:60637 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0
