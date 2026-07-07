# T-Deck Console Node TTDB

```mmpdb
db_id: tdeck-console-001
db_name: T-Deck Handheld Console
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
  constraints:
    - battery-powered
    - roaming
    - keyboard-input
  globe:
    frame: mesh-topology
    origin: "@LAT0LON0"
    mapping: "operator endpoint: a mobile mini-orchestrator carried in-hand; keyboard -> CMD, screen -> fleet view"
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

@LAT0LON0 | created:1750000000 | updated:1750000000 | relates:commands@LAT10LON0,connected_over@LAT10LON0

Console home. The operator's handheld: a BlackBerry keyboard injects CMD toots and
a 320x240 color screen shows the fleet. Reaches the mesh over ESP-NOW (in range)
and, once enabled, SX1262 LoRa (long-haul) — so it can drive the fleet without the
laptop.

---

@LAT10LON0 | created:1750000000 | updated:1750000000 | relates:reports_sensor@LAT0LON0

Fleet view. Where collected STATUS / PERCEPT replies land for on-screen display:
which node answered, its cursor, temperature, warm/synced flags, and band phase.

---

@LAT99LON0 | created:1783367393 | updated:1783367393 | relates:logs@LAT0LON0

**SYNC** id:5 t_ms:1783367393574 recv_ms:658665 offset_ms:1783366734909

---


---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-45 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-49 rssi_med:-34 rssi_max:-31
**LINK** peer:0x00000011 proto:espnow n:9 rssi_min:-47 rssi_med:-34 rssi_max:-32

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-36 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-40 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-36 rssi_med:-32 rssi_max:-31

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-36 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-42 rssi_med:-40 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-37 rssi_med:-34 rssi_max:-31
