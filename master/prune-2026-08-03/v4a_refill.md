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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6772112 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-28 rssi_med:-26 rssi_max:-24
**LINK** peer:0x00000300 proto:ble n:78 rssi_min:-80 rssi_med:-41 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:8 rssi_min:-45 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:75 rssi_min:-81 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-48 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000012 proto:ble n:76 rssi_min:-64 rssi_med:-59 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:72 rssi_min:-80 rssi_med:-67 rssi_max:-48
**LINK** peer:0x00000011 proto:espnow n:9 rssi_min:-64 rssi_med:-57 rssi_max:-54

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6772112 stream:0x59fb8ce8 wall:0 window_ms:60180 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6832112 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:98 rssi_min:-46 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:91 rssi_min:-81 rssi_med:-60 rssi_max:-54
**LINK** peer:0x00000200 proto:ble n:91 rssi_min:-70 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:91 rssi_min:-81 rssi_med:-66 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:9 rssi_min:-58 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:10 rssi_min:-49 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000012 proto:espnow n:8 rssi_min:-45 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000300 proto:espnow n:19 rssi_min:-27 rssi_med:-26 rssi_max:-25

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6892111 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:85 rssi_min:-80 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000011 proto:ble n:81 rssi_min:-81 rssi_med:-63 rssi_max:-53
**LINK** peer:0x00000300 proto:ble n:89 rssi_min:-79 rssi_med:-42 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:96 rssi_min:-79 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:7 rssi_min:-49 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-28 rssi_med:-26 rssi_max:-26
**LINK** peer:0x00000011 proto:espnow n:6 rssi_min:-55 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000012 proto:espnow n:7 rssi_min:-45 rssi_med:-44 rssi_max:-43
