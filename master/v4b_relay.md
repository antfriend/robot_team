# V4-B Relay Node TTDB

```mmpdb
db_id: v4b-relay-001
db_name: V4-B Relay Node
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: v4b-relay
  role: store-and-forward
  perspective: spine-mid
  scope: long-hops
  constraints:
    - solar-powered
    - external-antenna
  globe:
    frame: mesh-topology
    origin: "@LAT0LON20"
    mapping: "midpoint of the A-B-C spine on the knowledge grid"
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
lon: 20
```

---

@LAT0LON20 | created:1750000000 | updated:1750000000 | relates:navigates_to@LAT0LON10,navigates_to@LAT0LON30

Relay home. Forwards between V4-A (lon 10) and V4-C (lon 30); decrements ttl and
dedups on (src,seq).

---

@LAT99LON0 | created:1782429925 | updated:1782429925 | relates:logs@LAT0LON0

**SYNC** id:3 t_ms:1782429925125 recv_ms:45601 offset_ms:1782429879524

---

@LAT99LON1 | created:1782430029 | updated:1782430029 | relates:logs@LAT0LON0

**SYNC** id:4 t_ms:1782430029108 recv_ms:149590 offset_ms:1782429879518

---

@LAT98LON0 | created:1782430070 | updated:1782430070 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:9 bytes:1373 crc:9EFD9530 recv_ms:191382

---

@LAT99LON2 | created:1783367393 | updated:1783367393 | relates:logs@LAT0LON0

**SYNC** id:5 t_ms:1783367393574 recv_ms:249323 offset_ms:1783367144251

---


---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60006 synced:0 window_ms:60006
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-27 rssi_med:-24 rssi_max:-21
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-44 rssi_med:-29 rssi_max:-26
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-51 rssi_med:-35 rssi_max:-33

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120006 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-27 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-35 rssi_med:-29 rssi_max:-27
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-75 rssi_med:-44 rssi_max:-33
