# V4-A Bridge Node TTDB

```mmpdb
db_id: v4a-bridge-001
db_name: V4-A Bridge Node
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: v4a-bridge
  role: mesh-gateway
  perspective: spine-head
  scope: whole-mesh
  constraints:
    - always-powered
    - channel-authority
  globe:
    frame: mesh-topology
    origin: "@LAT0LON0"
    mapping: "spine and cluster nodes placed on the lat/lon knowledge grid"
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

@LAT0LON0 | created:1750000000 | updated:1750000000 | relates:navigates_to@LAT0LON10

Bridge home. Gateway between the laptop (USB-CDC) and the LoRa/ESP-NOW mesh.

---

@LAT0LON10 | created:1750000000 | updated:1750000000 | relates:navigates_to@LAT0LON20

Toward V4-B (relay). Forwarding state for the first LoRa hop.

---


---


---


---


---


---


---


---


---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x59fb8ce8 wall:0 t_ms:1672837 node:0x10 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---


---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:47 last_lon:46 t_ms:9913863 stream:0x59fb8ce8 wall:0 node:0x00000010

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:8 last_lon:7 t_ms:9939665 stream:0x59fb8ce8 wall:0 node:0x00000010

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10002853 stream:0x59fb8ce8 wall:0 window_ms:60006
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-61 rssi_med:-53 rssi_max:-44
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-42 rssi_med:-39 rssi_max:-31
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-81 rssi_med:-51 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-83 rssi_med:-60 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:37 rssi_min:-41 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-79 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-60 rssi_med:-50 rssi_max:-46

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10002853 stream:0x59fb8ce8 wall:0 window_ms:62043 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10062853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:68 rssi_min:-77 rssi_med:-49 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-42 rssi_med:-39 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-55 rssi_med:-50 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-55 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-81 rssi_med:-51 rssi_max:-43
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-49 rssi_med:-37 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:17 rssi_min:-55 rssi_med:-43 rssi_max:-32

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10122853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-76 rssi_med:-55 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-80 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-80 rssi_med:-48 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-40 rssi_med:-38 rssi_max:-35
**LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-51 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-38 rssi_med:-37 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-71 rssi_med:-55 rssi_max:-48
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-43 rssi_med:-42 rssi_max:-41

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10182853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-61 rssi_med:-49 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-79 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-48 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-80 rssi_med:-49 rssi_max:-38
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-68 rssi_med:-44 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-62 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-45 rssi_med:-39 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-52 rssi_med:-26 rssi_max:-25

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10242852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-51 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-46 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-80 rssi_med:-61 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-60 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-26 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-80 rssi_med:-47 rssi_max:-37
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-40 rssi_med:-37 rssi_max:-33

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10302852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-53 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-77 rssi_med:-45 rssi_max:-36
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-46 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-79 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-28 rssi_med:-26 rssi_max:-24
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-46 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-80 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-37 rssi_med:-32 rssi_max:-31

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10362852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-80 rssi_med:-59 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-49 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-27 rssi_med:-26 rssi_max:-24
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-46 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-39 rssi_med:-37 rssi_max:-32
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-57 rssi_med:-48 rssi_max:-39

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10422853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-62 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-47 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-28 rssi_med:-26 rssi_max:-23
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-41 rssi_med:-37 rssi_max:-30
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-47 rssi_max:-38
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-77 rssi_med:-59 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-52 rssi_med:-46 rssi_max:-41
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-41 rssi_max:-37

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10482852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000012 proto:ble n:68 rssi_min:-76 rssi_med:-50 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-44 rssi_med:-39 rssi_max:-36
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-24 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-58 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-58 rssi_med:-32 rssi_max:-27

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10542853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-53 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-77 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-45 rssi_med:-42 rssi_max:-36
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-77 rssi_med:-51 rssi_max:-43
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-41 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-24 rssi_med:-22 rssi_max:-20

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10556575 stream:0x59fb8ce8 wall:0 window_ms:553685 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10602852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-48 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-60 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-42 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-23 rssi_med:-22 rssi_max:-21
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-42 rssi_med:-32 rssi_max:-29
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-53 rssi_med:-48 rssi_max:-46

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10662853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-58 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-76 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-45 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-53 rssi_med:-47 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-22 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-47 rssi_med:-32 rssi_max:-28
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-36 rssi_max:-33

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10722852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-83 rssi_med:-64 rssi_max:-55
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-77 rssi_med:-37 rssi_max:-33
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-43 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-26 rssi_med:-22 rssi_max:-18
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-65 rssi_med:-57 rssi_max:-47
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-34 rssi_med:-30 rssi_max:-28

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10782853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-60 rssi_med:-55 rssi_max:-47
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-23 rssi_med:-21 rssi_max:-19
**LINK** peer:0x00000012 proto:ble n:67 rssi_min:-80 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-48 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-32 rssi_med:-28 rssi_max:-26
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-66 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-58 rssi_max:-52

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10842853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-79 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-47 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-81 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-41 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-86 rssi_med:-65 rssi_max:-60
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-22 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-30 rssi_med:-27 rssi_max:-27

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10902852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-83 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-80 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-47 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-85 rssi_med:-66 rssi_max:-60
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-23 rssi_med:-22 rssi_max:-21
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-29 rssi_med:-28 rssi_max:-27
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-82 rssi_med:-59 rssi_max:-53

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10962852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-76 rssi_med:-59 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-72 rssi_med:-62 rssi_max:-54
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-46 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-40 rssi_med:-29 rssi_max:-27
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-41 rssi_med:-36 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-23 rssi_med:-21 rssi_max:-17

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:11022853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-76 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-47 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-48 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-22 rssi_med:-21 rssi_max:-19
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-37 rssi_med:-28 rssi_max:-26
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-76 rssi_med:-60 rssi_max:-53

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:11082852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-36 rssi_max:-31
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-48 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-77 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-23 rssi_med:-21 rssi_max:-18
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-83 rssi_med:-61 rssi_max:-53
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-38 rssi_med:-30 rssi_max:-27
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-59 rssi_max:-54

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:11142853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-42 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-76 rssi_med:-64 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-54 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-59 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-22 rssi_med:-20 rssi_max:-19
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-34 rssi_med:-29 rssi_max:-27
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-70 rssi_med:-60 rssi_max:-55

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11156603 stream:0x59fb8ce8 wall:0 window_ms:600029 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:11202853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-48 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-24 rssi_med:-20 rssi_max:-17
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-34 rssi_max:-31
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-39 rssi_med:-31 rssi_max:-28
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-82 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-50 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-56 rssi_max:-51

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:11262853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-44 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-57 rssi_med:-44 rssi_max:-36
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-42 rssi_med:-27 rssi_max:-21
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-76 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-67 rssi_med:-51 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-41 rssi_med:-38 rssi_max:-29

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:11322852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-43 rssi_med:-40 rssi_max:-36
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-35 rssi_med:-28 rssi_max:-23
**LINK** peer:0x00000012 proto:espnow n:30 rssi_min:-42 rssi_med:-32 rssi_max:-28
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-81 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-77 rssi_med:-44 rssi_max:-37

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:11382853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-64 rssi_med:-46 rssi_max:-37
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-45 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-41 rssi_med:-28 rssi_max:-24
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-38 rssi_med:-31 rssi_max:-28
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-79 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-61 rssi_med:-50 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-80 rssi_med:-54 rssi_max:-51

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:11442852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-80 rssi_med:-55 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-45 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-38 rssi_med:-27 rssi_max:-21
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-44 rssi_max:-34
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-77 rssi_med:-50 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-77 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-42 rssi_med:-31 rssi_max:-28

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:11502852 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-60 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-43 rssi_max:-38
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-46 rssi_max:-41
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-51 rssi_med:-28 rssi_max:-23
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-38 rssi_med:-29 rssi_max:-26
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-82 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-46 rssi_med:-42 rssi_max:-40

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:11562853 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-46 rssi_med:-44 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-73 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-44 rssi_max:-34
**LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-40 rssi_med:-26 rssi_max:-20
**LINK** peer:0x00000012 proto:ble n:50 rssi_min:-76 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-38 rssi_med:-31 rssi_max:-28

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbdc62024 wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:53227 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-38 rssi_med:-33 rssi_max:-25
**LINK** peer:0x00000200 proto:espnow n:9 rssi_min:-48 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000200 proto:ble n:39 rssi_min:-81 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:8 rssi_min:-49 rssi_med:-41 rssi_max:-29
**LINK** peer:0x00000300 proto:ble n:12 rssi_min:-79 rssi_med:-50 rssi_max:-42

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:53227 stream:0xbdc62024 wall:0 window_ms:60042 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:113226 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-26 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-39 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-76 rssi_med:-52 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:40 rssi_min:-76 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-58 rssi_med:-50 rssi_max:-36

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:173227 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-26 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-79 rssi_med:-53 rssi_max:-45
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-58 rssi_med:-47 rssi_max:-42

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:233227 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:18 rssi_min:-67 rssi_med:-54 rssi_max:-46
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:3 rssi_min:-58 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-81 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-37 rssi_med:-34 rssi_max:-32

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:293226 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-77 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-36 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-27 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:6 rssi_min:-77 rssi_med:-58 rssi_max:-46

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:353227 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-38 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000300 proto:ble n:42 rssi_min:-62 rssi_med:-51 rssi_max:-46
**LINK** peer:0x00000300 proto:espnow n:2 rssi_min:-76 rssi_med:-76 rssi_max:-39

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:413226 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:9 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:46 rssi_min:-79 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000100 proto:espnow n:32 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-50 rssi_max:-47
**LINK** peer:0x00000300 proto:espnow n:14 rssi_min:-36 rssi_med:-36 rssi_max:-35

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:473226 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-26 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000300 proto:espnow n:5 rssi_min:-41 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-34 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:45 rssi_min:-80 rssi_med:-48 rssi_max:-45

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:533226 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-71 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-27 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-46 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-70 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:11 rssi_min:-39 rssi_med:-35 rssi_max:-34

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:593227 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-55 rssi_med:-40 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-39 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-83 rssi_med:-51 rssi_max:-45
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-52 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-26 rssi_med:-25 rssi_max:-25

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:602995 stream:0xbdc62024 wall:0 window_ms:549727 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:653227 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-42 rssi_med:-28 rssi_max:-25
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-46 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-27 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-63 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-81 rssi_med:-50 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:48 rssi_min:-81 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:35 rssi_min:-82 rssi_med:-59 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-52 rssi_med:-44 rssi_max:-40

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:713227 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-37 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:69 rssi_min:-82 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-26 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:69 rssi_min:-80 rssi_med:-53 rssi_max:-46
**LINK** peer:0x00000012 proto:ble n:33 rssi_min:-70 rssi_med:-53 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-45 rssi_med:-42 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-50 rssi_med:-43 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:30 rssi_min:-81 rssi_med:-64 rssi_max:-51

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:773227 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-28 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-64 rssi_med:-55 rssi_max:-46
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-76 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:41 rssi_min:-86 rssi_med:-63 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-45 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000011 proto:espnow n:12 rssi_min:-52 rssi_med:-50 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:51 rssi_min:-80 rssi_med:-58 rssi_max:-45

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:833226 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-62 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-61 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:47 rssi_min:-81 rssi_med:-55 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:10 rssi_min:-55 rssi_med:-52 rssi_max:-44
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-27 rssi_med:-26 rssi_max:-26
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-45 rssi_med:-43 rssi_max:-41

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:893226 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-56 rssi_max:-45
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-46 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:72 rssi_min:-61 rssi_med:-54 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-61 rssi_med:-50 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:58 rssi_min:-28 rssi_med:-26 rssi_max:-24
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-80 rssi_med:-63 rssi_max:-52

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:953227 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:51 rssi_min:-77 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-61 rssi_med:-51 rssi_max:-44
**LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-28 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-60 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-65 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-45 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-64 rssi_med:-55 rssi_max:-46
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-57 rssi_med:-49 rssi_max:-44

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1013227 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-28 rssi_med:-27 rssi_max:-25
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-26 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-58 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-64 rssi_med:-51 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-56 rssi_max:-46
**LINK** peer:0x00000011 proto:ble n:67 rssi_min:-84 rssi_med:-63 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-61 rssi_med:-49 rssi_max:-42

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1073226 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-26 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-60 rssi_med:-54 rssi_max:-48
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-83 rssi_med:-64 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-44 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-79 rssi_med:-60 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-55 rssi_med:-48 rssi_max:-44

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1133226 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-82 rssi_med:-64 rssi_max:-52
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-57 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-26 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-79 rssi_med:-54 rssi_max:-46
**LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-27 rssi_med:-26 rssi_max:-24
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-45 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-62 rssi_med:-51 rssi_max:-46
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-61 rssi_med:-50 rssi_max:-43

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1193226 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-27 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-59 rssi_med:-53 rssi_max:-46
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-84 rssi_med:-64 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-43 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-61 rssi_med:-48 rssi_max:-41
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-69 rssi_med:-56 rssi_max:-45
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-76 rssi_med:-39 rssi_max:-38

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1202995 stream:0xbdc62024 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1253226 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-63 rssi_med:-34 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-50 rssi_max:-38
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-52 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-62 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-80 rssi_med:-57 rssi_max:-41
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-55 rssi_med:-44 rssi_max:-27
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-81 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-68 rssi_med:-51 rssi_max:-43

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1689507 stream:0xbdc62024 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2243278 stream:0xbdc62024 wall:0 window_ms:555772 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2843278 stream:0xbdc62024 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3443283 stream:0xbdc62024 wall:0 window_ms:600005 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4043283 stream:0xbdc62024 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4643282 stream:0xbdc62024 wall:0 window_ms:599999 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5243282 stream:0xbdc62024 wall:0 window_ms:600001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5843283 stream:0xbdc62024 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xe7384824 wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:53201 stream:0xe7384824 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:602996 stream:0xe7384824 wall:0 window_ms:549794 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1202996 stream:0xe7384824 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-67
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-86
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1802996 stream:0xe7384824 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-63
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2039543 stream:0xe7384824 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2195648 stream:0xe7384824 wall:0 window_ms:60000 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2350549 stream:0xe7384824 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2900310 stream:0xe7384824 wall:0 window_ms:549762 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3500312 stream:0xe7384824 wall:0 window_ms:602001 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4100892 stream:0xe7384824 wall:0 window_ms:600580 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4700892 stream:0xe7384824 wall:0 window_ms:600001 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5300892 stream:0xe7384824 wall:0 window_ms:599999 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5900892 stream:0xe7384824 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-92

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6500950 stream:0xe7384824 wall:0 window_ms:600058 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7100980 stream:0xe7384824 wall:0 window_ms:598030 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7700979 stream:0xe7384824 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8300979 stream:0xe7384824 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-67
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xaf869fce wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:53185 stream:0xaf869fce wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-23
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x161e88ac wall:0 t_ms:22773 node:0x10 from:0x300
**REMAP** prev_stream:0x907f7c71 prev_t_ms:3025 offset_ms:19748 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:72973 stream:0x161e88ac wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:622744 stream:0x161e88ac wall:0 window_ms:549772 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1222744 stream:0x161e88ac wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1822744 stream:0x161e88ac wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2422744 stream:0x161e88ac wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3022744 stream:0x161e88ac wall:0 window_ms:600001 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3622744 stream:0x161e88ac wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4222744 stream:0x161e88ac wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4822744 stream:0x161e88ac wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x67ec2883 wall:0 t_ms:50830 node:0x10 from:0x300
**REMAP** prev_stream:0xbbc3158d prev_t_ms:4001 offset_ms:46829 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:99002 stream:0x67ec2883 wall:0 window_ms:60000 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x3ab84e5a wall:0 t_ms:8707 node:0x10 from:0x300
**REMAP** prev_stream:0x6af8be6a prev_t_ms:4499 offset_ms:4208 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:57407 stream:0x3ab84e5a wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbe6d9616 wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:51800 stream:0xbe6d9616 wall:0 window_ms:61631 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:601963 stream:0xbe6d9616 wall:0 window_ms:550162 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1201962 stream:0xbe6d9616 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1801962 stream:0xbe6d9616 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2401962 stream:0xbe6d9616 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x6a2120c2 wall:0 t_ms:150131 node:0x10 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xdffbae31 wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x6549a5c7 wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x185f5a4b wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x946fea42 wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x946fea42 wall:0 t_ms:15438857 node:0x10 from:0x300
**REMAP** prev_stream:0xc1f36de7 prev_t_ms:8843 offset_ms:15430014 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x32464d87 wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin
