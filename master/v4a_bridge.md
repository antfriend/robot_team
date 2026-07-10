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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:61000 synced:0 window_ms:61000
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-51 rssi_med:-45 rssi_max:-35
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-55 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-58 rssi_med:-42 rssi_max:-31

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:122534 synced:0 window_ms:61534
**LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-84 rssi_med:-67 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-94 rssi_med:-76 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-94 rssi_med:-77 rssi_max:-65

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:184000 synced:0 window_ms:61466
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-94 rssi_med:-88 rssi_max:-76
**LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-71 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-92 rssi_med:-84 rssi_max:-79

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:245102 synced:0 window_ms:61102
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-85 rssi_med:-84 rssi_max:-78
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-67 rssi_med:-67 rssi_max:-66
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-94 rssi_med:-93 rssi_max:-85

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:306534 synced:0 window_ms:61432
**LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-67 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-86 rssi_med:-84 rssi_max:-82
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-95 rssi_med:-92 rssi_max:-90

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:368034 synced:0 window_ms:61500
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-95 rssi_med:-91 rssi_max:-88
**LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-67 rssi_med:-67 rssi_max:-66
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-86 rssi_med:-85 rssi_max:-82

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:429534 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-87 rssi_med:-85 rssi_max:-84
**LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-67 rssi_med:-67 rssi_max:-66
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-93 rssi_med:-91 rssi_max:-89

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:491034 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-86 rssi_med:-85 rssi_max:-83
**LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-69 rssi_med:-67 rssi_max:-66
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-95 rssi_med:-92 rssi_max:-89

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:552611 synced:0 window_ms:61577
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-95 rssi_med:-93 rssi_max:-86
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-69 rssi_med:-67 rssi_max:-66
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-89 rssi_med:-84 rssi_max:-83

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:614109 synced:0 window_ms:61498
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-93 rssi_med:-88 rssi_max:-85
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-73 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-90 rssi_med:-88 rssi_max:-85

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:675613 synced:0 window_ms:61504
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-90 rssi_med:-88 rssi_max:-86
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-76 rssi_med:-70 rssi_max:-64
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-93 rssi_med:-90 rssi_max:-87

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-92 rssi_med:-88 rssi_max:-85
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-71 rssi_med:-68 rssi_max:-65
**LINK** peer:0x00000011 proto:espnow n:49 rssi_min:-90 rssi_med:-87 rssi_max:-83
