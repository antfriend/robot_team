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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60706 synced:0 window_ms:60706
**LINK** peer:0x00000011 proto:espnow n:32 rssi_min:-44 rssi_med:-41 rssi_max:-36

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:122238 synced:0 window_ms:61532
**LINK** peer:0x00000011 proto:espnow n:32 rssi_min:-71 rssi_med:-58 rssi_max:-39

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:183738 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-67 rssi_med:-59 rssi_max:-56

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:245238 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-61 rssi_med:-57 rssi_max:-56

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:306739 synced:0 window_ms:61501
**LINK** peer:0x00000011 proto:espnow n:32 rssi_min:-84 rssi_med:-59 rssi_max:-56

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:368239 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:34 rssi_min:-87 rssi_med:-75 rssi_max:-66

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:429737 synced:0 window_ms:61498
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-82 rssi_med:-64 rssi_max:-62

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:491237 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-83 rssi_med:-69 rssi_max:-64

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:552737 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:31 rssi_min:-94 rssi_med:-83 rssi_max:-68

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:614237 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-85 rssi_med:-83 rssi_max:-81

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:675737 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-96 rssi_med:-83 rssi_max:-81

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:737237 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:5 rssi_min:-94 rssi_med:-87 rssi_max:-86

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:798669 synced:0 window_ms:61432
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-97 rssi_med:-93 rssi_max:-65

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:61000 synced:0 window_ms:61000
**LINK** peer:0x00000011 proto:espnow n:31 rssi_min:-75 rssi_med:-41 rssi_max:-32

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:122705 synced:0 window_ms:61705
**LINK** peer:0x00000011 proto:espnow n:32 rssi_min:-84 rssi_med:-60 rssi_max:-52

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:184273 synced:0 window_ms:61568
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-87 rssi_med:-67 rssi_max:-56

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:245774 synced:0 window_ms:61501
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-91 rssi_med:-80 rssi_max:-67

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:307273 synced:0 window_ms:61499
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-95 rssi_med:-81 rssi_max:-79

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:368773 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-97 rssi_med:-94 rssi_max:-84

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:430273 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-92 rssi_med:-86 rssi_max:-78

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:491773 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-89 rssi_med:-86 rssi_max:-84

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:553273 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-88 rssi_med:-87 rssi_max:-84

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:614773 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-88 rssi_med:-86 rssi_max:-84

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:676273 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-95 rssi_med:-86 rssi_max:-56

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:737773 synced:0 window_ms:61500
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-51 rssi_med:-43 rssi_max:-36

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:799272 synced:0 window_ms:61499
**LINK** peer:0x00000011 proto:espnow n:33 rssi_min:-45 rssi_med:-44 rssi_max:-43
