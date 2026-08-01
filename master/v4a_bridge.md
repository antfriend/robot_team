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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120034 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:38 rssi_min:-79 rssi_med:-74 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-28 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-43 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-60 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000300 proto:ble n:51 rssi_min:-77 rssi_med:-65 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-92 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-83 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-64 rssi_med:-58 rssi_max:-52

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180034 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-76 rssi_med:-75 rssi_max:-74
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-88 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-42 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-61 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:50 rssi_min:-81 rssi_med:-70 rssi_max:-67

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240034 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:52 rssi_min:-65 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-76 rssi_med:-75 rssi_max:-74
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-87 rssi_med:-84 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-59 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-80 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-26 rssi_med:-26 rssi_max:-25

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300034 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-75 rssi_med:-75 rssi_max:-74
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-78 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-26 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-88 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-81 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-59 rssi_med:-57 rssi_max:-56

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360034 synced:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-79 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-80 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-88 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-59 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-74 rssi_med:-74 rssi_max:-72

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420034 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-88 rssi_med:-84 rssi_max:-74
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-66 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-75 rssi_med:-74 rssi_max:-71
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-81 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-27 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-77 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-59 rssi_med:-58 rssi_max:-57

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480034 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:69 rssi_min:-42 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-66 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-75 rssi_med:-75 rssi_max:-74
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-27 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-87 rssi_med:-84 rssi_max:-75
**LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-62 rssi_med:-58 rssi_max:-56

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540034 synced:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-66 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-84 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-87 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-62 rssi_med:-57 rssi_max:-57
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-75 rssi_med:-75 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-27 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-59 rssi_med:-59 rssi_max:-58

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600034 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-86 rssi_med:-84 rssi_max:-76
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-81 rssi_med:-40 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-75 rssi_med:-74 rssi_max:-73
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-78 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-66 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-59 rssi_med:-59 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-59 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-26 rssi_med:-26 rssi_max:-25
