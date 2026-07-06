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
