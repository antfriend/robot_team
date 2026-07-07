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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-49 rssi_med:-42 rssi_max:-37

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-59 rssi_med:-50 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-38 rssi_med:-34 rssi_max:-30

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:40 rssi_min:-38 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-64 rssi_med:-58 rssi_max:-47
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-61 rssi_med:-61 rssi_max:-51

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:43 rssi_min:-38 rssi_med:-37 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-53 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-47 rssi_med:-47 rssi_max:-46

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:32 rssi_min:-35 rssi_med:-33 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-63 rssi_med:-56 rssi_max:-46

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300144 synced:0 window_ms:60144
**LINK** peer:0x00000011 proto:espnow n:32 rssi_min:-35 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-68 rssi_med:-55 rssi_max:-48
