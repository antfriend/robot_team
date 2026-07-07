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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60714 synced:0 window_ms:60714
**LINK** peer:0x00000011 proto:espnow n:32 rssi_min:-53 rssi_med:-44 rssi_max:-38
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-44 rssi_med:-39 rssi_max:-34
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-46 rssi_med:-40 rssi_max:-34

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120714 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-45 rssi_med:-39 rssi_max:-25
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-48 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-41 rssi_med:-38 rssi_max:-31

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180714 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-32 rssi_med:-28 rssi_max:-26
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-39 rssi_med:-33 rssi_max:-29
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-30 rssi_med:-25 rssi_max:-23

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240714 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-50 rssi_med:-29 rssi_max:-27
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-37 rssi_med:-32 rssi_max:-30
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-30 rssi_med:-25 rssi_max:-23

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300714 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-33 rssi_med:-29 rssi_max:-26
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-39 rssi_med:-32 rssi_max:-29

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360714 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-39 rssi_med:-33 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-38 rssi_med:-30 rssi_max:-25

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:422681 synced:0 window_ms:61967
**LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-41 rssi_med:-35 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-46 rssi_med:-30 rssi_max:-25
**LINK** peer:0x00000011 proto:espnow n:8 rssi_min:-55 rssi_med:-43 rssi_max:-38

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:484198 synced:0 window_ms:61517
**LINK** peer:0x00000011 proto:espnow n:31 rssi_min:-47 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-32 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-44 rssi_med:-40 rssi_max:-34

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:545715 synced:0 window_ms:61517
**LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-44 rssi_med:-41 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:31 rssi_min:-62 rssi_med:-46 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-31 rssi_med:-28 rssi_max:-27
