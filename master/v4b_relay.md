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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60006 synced:0 window_ms:60006
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-47 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000200 proto:espnow n:33 rssi_min:-53 rssi_med:-29 rssi_max:-26

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120006 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-39 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-37 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-34 rssi_med:-34 rssi_max:-33

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180015 synced:0 window_ms:60009
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-41 rssi_med:-35 rssi_max:-32
**LINK** peer:0x00000200 proto:espnow n:43 rssi_min:-38 rssi_med:-34 rssi_max:-27
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-38 rssi_med:-38 rssi_max:-34

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240043 synced:0 window_ms:60028
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-37 rssi_med:-32 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-34 rssi_med:-29 rssi_max:-27

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300043 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-39 rssi_med:-33 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-30 rssi_med:-27 rssi_max:-27
