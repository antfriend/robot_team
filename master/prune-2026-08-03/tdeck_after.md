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
