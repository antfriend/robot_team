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

@LAT99LON0 | created:1782170699 | updated:1782170699 | relates:logs@LAT0LON0

**SYNC** id:1 t_ms:1782170699715 recv_ms:20222 offset_ms:1782170679493

---

@LAT99LON1 | created:1782170835 | updated:1782170835 | relates:logs@LAT0LON0

**SYNC** id:2 t_ms:1782170835676 recv_ms:155661 offset_ms:1782170680015

---

@LAT99LON2 | created:1782429925 | updated:1782429925 | relates:logs@LAT0LON0

**SYNC** id:3 t_ms:1782429925125 recv_ms:2795865 offset_ms:1782427129260

---

@LAT99LON3 | created:1782430029 | updated:1782430029 | relates:logs@LAT0LON0

**SYNC** id:4 t_ms:1782430029108 recv_ms:56335 offset_ms:1782429972773

---

@LAT99LON4 | created:1783367393 | updated:1783367393 | relates:logs@LAT0LON0

**SYNC** id:5 t_ms:1783367393574 recv_ms:29304 offset_ms:1783367364270

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:61304 synced:0 window_ms:61304
**LINK** peer:0x00000200 proto:espnow n:33 rssi_min:-60 rssi_med:-46 rssi_max:-36
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-44 rssi_med:-34 rssi_max:-33

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:61068 synced:0 window_ms:61068
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-62 rssi_med:-58 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-40 rssi_med:-36 rssi_max:-35

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60941 synced:0 window_ms:60941
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-68 rssi_med:-55 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:32 rssi_min:-45 rssi_med:-34 rssi_max:-33

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:122475 synced:0 window_ms:61534
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-71 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:32 rssi_min:-39 rssi_med:-35 rssi_max:-32

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:183975 synced:0 window_ms:61500
**LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-68 rssi_med:-57 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-39 rssi_med:-35 rssi_max:-33
