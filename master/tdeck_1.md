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

@LAT0LON16 | created:1750000000 | updated:1750000000 | relates:espnow@LAT0LON0,espnow@LAT35LON7,espnow@LAT32LON34

**POSITION** node:k10_1
name: K10
x_m: 16.25  y_m: -0.00
sigma_m: 51.28   conf: 0.58
link V4-A: espnow 16.3m conf 0.80
link V4-B: espnow 34.1m conf 0.80
link T-Deck: espnow 38.4m conf 0.80

---

@LAT32LON34 | created:1750000000 | updated:1750000000 | relates:espnow@LAT0LON0,espnow@LAT35LON7,espnow@LAT0LON16

**POSITION** node:tdeck_1
name: T-Deck
x_m: 33.61  y_m: 31.87
sigma_m: 61.96   conf: 0.55
link V4-A: espnow 41.8m conf 0.75
link V4-B: espnow 27.2m conf 0.78
link K10: espnow 38.4m conf 0.80

---

@LAT0LON0 | created:1750000000 | updated:1750000000 | relates:espnow@LAT35LON7,espnow@LAT0LON16,espnow@LAT32LON34

**POSITION** node:v4a_bridge
name: V4-A
x_m: 0.00  y_m: -0.00
sigma_m: 57.72   conf: 0.55
link V4-B: espnow 37.1m conf 0.78
link K10: espnow 16.3m conf 0.80
link T-Deck: espnow 41.8m conf 0.75

---

@LAT35LON7 | created:1750000000 | updated:1750000000 | relates:espnow@LAT0LON0,espnow@LAT0LON16,espnow@LAT32LON34

**POSITION** node:v4b_relay
name: V4-B
x_m: 6.83  y_m: 34.78
sigma_m: 53.15   conf: 0.56
link V4-A: espnow 37.1m conf 0.78
link K10: espnow 34.1m conf 0.80
link T-Deck: espnow 27.2m conf 0.78

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60031 synced:0 window_ms:60031
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-41 rssi_med:-39 rssi_max:-37
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-39 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-48 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-68 rssi_med:-61 rssi_max:-58
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-62 rssi_med:-54 rssi_max:-52

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120031 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-79 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-41 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-40 rssi_med:-38 rssi_max:-36
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-44 rssi_med:-43 rssi_max:-41

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180031 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-63 rssi_max:-57
**LINK** peer:0x00000011 proto:ble n:68 rssi_min:-80 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-41 rssi_med:-39 rssi_max:-39
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-46 rssi_med:-46 rssi_max:-41
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-40 rssi_med:-39 rssi_max:-37

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240031 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-40 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-46 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300031 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-68 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-42 rssi_med:-38 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-42 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-47 rssi_med:-44 rssi_max:-41

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-44 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-49 rssi_med:-47 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-79 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-35 rssi_med:-34 rssi_max:-33

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-54 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-53 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-42 rssi_med:-41 rssi_max:-39

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-76 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-55 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-53 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-42 rssi_med:-40 rssi_max:-39

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-34 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-59 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-50 rssi_med:-49 rssi_max:-49
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-41 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-82 rssi_med:-51 rssi_max:-48

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-50 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-52 rssi_max:-48
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-34 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-79 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-41 rssi_med:-40 rssi_max:-40

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-50 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-72 rssi_med:-51 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-34 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-60 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-41 rssi_med:-40 rssi_max:-38

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-63 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-47 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-62 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-51 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-43 rssi_med:-40 rssi_max:-39

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-41 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-57 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-53 rssi_med:-47 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-56 rssi_max:-54

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-46 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-41 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-55 rssi_med:-52 rssi_max:-50

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-35 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-69 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-45 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-67 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-42 rssi_med:-40 rssi_max:-39

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-36 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-71 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-41 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000100 proto:espnow n:32 rssi_min:-43 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-80 rssi_med:-52 rssi_max:-50

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:780000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-35 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-55 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-42 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-45 rssi_med:-40 rssi_max:-38

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:840000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-45 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-55 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-42 rssi_med:-41 rssi_max:-39

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:900000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-34 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-45 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-55 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-44 rssi_med:-41 rssi_max:-40

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:960000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-55 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-35 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-44 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-65 rssi_med:-60 rssi_max:-57

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1020000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-67 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-34 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-44 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-55 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-44 rssi_med:-42 rssi_max:-40

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1080000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-79 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-74 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-52 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-43 rssi_med:-42 rssi_max:-39

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1140000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-56 rssi_med:-49 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-79 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-43 rssi_med:-40 rssi_max:-38

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1200052 synced:0 window_ms:60052
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-35 rssi_med:-34 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-79 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-53 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-61 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-42 rssi_med:-41 rssi_max:-38

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1260052 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:70 rssi_min:-56 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-42 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-53 rssi_med:-48 rssi_max:-43

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1320077 synced:0 window_ms:60025
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-56 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-42 rssi_med:-40 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-62 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-50 rssi_med:-46 rssi_max:-44

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1380077 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-79 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-55 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-40 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-79 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-35 rssi_med:-34 rssi_max:-33

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1440077 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-36 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000011 proto:ble n:68 rssi_min:-79 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-56 rssi_med:-48 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-39 rssi_med:-38 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-62 rssi_med:-55 rssi_max:-54

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1500103 synced:0 window_ms:60026
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-80 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-48 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-41 rssi_med:-39 rssi_max:-37

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1560103 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-55 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-80 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-41 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-35 rssi_med:-34 rssi_max:-33

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1620103 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-79 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-48 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-40 rssi_med:-38 rssi_max:-37

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1680103 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-82 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-77 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-41 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-47 rssi_med:-44 rssi_max:-41

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1740103 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-44 rssi_med:-41 rssi_max:-32
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-80 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-49 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:5 rssi_min:-43 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:12 rssi_min:-69 rssi_med:-57 rssi_max:-55

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1800103 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-80 rssi_med:-55 rssi_max:-49
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-49 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-41 rssi_med:-39 rssi_max:-38

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1860103 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-61 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-44 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-48 rssi_med:-45 rssi_max:-43

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1920103 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-48 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-42 rssi_med:-41 rssi_max:-40

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1980103 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-46 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-59 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-41 rssi_med:-41 rssi_max:-40

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2040103 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:12 rssi_min:-41 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-45 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:48 rssi_min:-57 rssi_med:-55 rssi_max:-50

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2100103 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-79 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-41 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-46 rssi_med:-44 rssi_max:-44

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2160103 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-59 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-45 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-43 rssi_med:-36 rssi_max:-35

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2220103 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-57 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-50 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-37 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:32 rssi_min:-79 rssi_med:-61 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:5 rssi_min:-49 rssi_med:-49 rssi_max:-48

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2280103 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-55 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-49 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-72 rssi_med:-63 rssi_max:-59

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2340103 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-56 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-80 rssi_med:-63 rssi_max:-57
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-59 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:67 rssi_min:-80 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-47 rssi_med:-38 rssi_max:-35

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2400103 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-68 rssi_med:-58 rssi_max:-48
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-79 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-83 rssi_med:-71 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-45 rssi_med:-42 rssi_max:-41

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2460103 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-79 rssi_med:-66 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-66 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-79 rssi_med:-57 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-61 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:9 rssi_min:-40 rssi_med:-40 rssi_max:-39

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2520103 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-49 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-74 rssi_med:-60 rssi_max:-53
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-46 rssi_med:-44 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-64 rssi_med:-51 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-74 rssi_med:-61 rssi_max:-59

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2580103 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-50 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:70 rssi_min:-73 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-46 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-57 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:67 rssi_min:-72 rssi_med:-59 rssi_max:-53

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:612589 synced:0 window_ms:552589 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1212590 synced:0 window_ms:600001 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1812591 synced:0 window_ms:600001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2412649 synced:0 window_ms:600058 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:611954 synced:0 window_ms:551954 entities:12
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-83
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e0c25086ede3 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:923badc7ab14 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1211954 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc3e073874d8 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e0c25086ede3 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1811954 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-62
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e0c25086ede3 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-93

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2412009 synced:0 window_ms:600055 entities:12
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-61
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e0c25086ede3 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-91
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc3e073874d8 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ff9038cc n:1 rssi:-95

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3011955 synced:0 window_ms:599946 entities:12
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-63
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e0c25086ede3 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
