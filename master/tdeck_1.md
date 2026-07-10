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


---


---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1020197 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:31 rssi_min:-60 rssi_med:-51 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-67 rssi_med:-50 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-46 rssi_med:-41 rssi_max:-34
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-35 rssi_med:-35 rssi_max:-34

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1080197 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-64 rssi_med:-51 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-63 rssi_med:-48 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-88 rssi_med:-47 rssi_max:-39

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1140197 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-53 rssi_med:-45 rssi_max:-37
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-93 rssi_med:-84 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-92 rssi_med:-88 rssi_max:-70

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1200197 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-94 rssi_med:-77 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-97 rssi_med:-88 rssi_max:-80
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-95 rssi_med:-87 rssi_max:-79

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1260197 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-84 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-87 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-96 rssi_med:-92 rssi_max:-88

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1320197 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-78 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-87 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-95 rssi_med:-92 rssi_max:-87

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1380197 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-93 rssi_med:-91 rssi_max:-88
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-79 rssi_med:-78 rssi_max:-76
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-87 rssi_med:-85 rssi_max:-84

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1440197 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-78 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-86 rssi_med:-85 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-94 rssi_med:-91 rssi_max:-89

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1500197 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-78 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-87 rssi_med:-86 rssi_max:-84
**LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-97 rssi_med:-92 rssi_max:-89

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1560197 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-79 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-90 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-94 rssi_med:-90 rssi_max:-85

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1620197 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-78 rssi_med:-77 rssi_max:-76
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-87 rssi_med:-85 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-92 rssi_med:-88 rssi_max:-84

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1680197 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-79 rssi_med:-77 rssi_max:-76
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-93 rssi_med:-89 rssi_max:-85
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-87 rssi_med:-85 rssi_max:-83

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1740393 synced:0 window_ms:60196
**LINK** peer:0x00000011 proto:espnow n:74 rssi_min:-78 rssi_med:-77 rssi_max:-76
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-87 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-94 rssi_med:-89 rssi_max:-85
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-95 rssi_med:-95 rssi_max:-94

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1800511 synced:0 window_ms:60118
**LINK** peer:0x00000011 proto:espnow n:44 rssi_min:-79 rssi_med:-78 rssi_max:-75
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-87 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-93 rssi_med:-89 rssi_max:-84
**LINK** peer:0x00000001 proto:espnow n:8 rssi_min:-87 rssi_med:-85 rssi_max:-84

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1860511 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:43 rssi_min:-79 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-91 rssi_med:-85 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-96 rssi_med:-90 rssi_max:-86
**LINK** peer:0x00000001 proto:espnow n:6 rssi_min:-91 rssi_med:-91 rssi_max:-88

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1920565 synced:0 window_ms:60054
**LINK** peer:0x00000011 proto:espnow n:78 rssi_min:-79 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-87 rssi_med:-85 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-93 rssi_med:-86 rssi_max:-79
**LINK** peer:0x00000001 proto:espnow n:6 rssi_min:-88 rssi_med:-81 rssi_max:-80

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1980565 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-87 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-86 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000011 proto:espnow n:49 rssi_min:-78 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000001 proto:espnow n:7 rssi_min:-85 rssi_med:-81 rssi_max:-80

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2040565 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-79 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-95 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-84 rssi_med:-84 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-87 rssi_med:-83 rssi_max:-79

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2100565 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:34 rssi_min:-79 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-88 rssi_med:-85 rssi_max:-83
**LINK** peer:0x00000001 proto:espnow n:3 rssi_min:-84 rssi_med:-84 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-87 rssi_med:-86 rssi_max:-80

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2160565 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-79 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-87 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000001 proto:espnow n:3 rssi_min:-83 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-88 rssi_med:-83 rssi_max:-80

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2220565 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:39 rssi_min:-79 rssi_med:-78 rssi_max:-77
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-88 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000001 proto:espnow n:4 rssi_min:-90 rssi_med:-86 rssi_max:-83
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-90 rssi_med:-85 rssi_max:-82
