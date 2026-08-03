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


---


---


---


---


---


---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x59fb8ce8 wall:0 t_ms:1740837 node:0x11 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6483038 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-50 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-46 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000012 proto:ble n:68 rssi_min:-81 rssi_med:-42 rssi_max:-31
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-81 rssi_med:-63 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-84 rssi_med:-57 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-31 rssi_med:-28 rssi_max:-23
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-60 rssi_med:-51 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-59 rssi_med:-42 rssi_max:-35

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6543038 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-82 rssi_med:-56 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-51 rssi_max:-46
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-30 rssi_med:-28 rssi_max:-27
**LINK** peer:0x00000012 proto:ble n:69 rssi_min:-82 rssi_med:-41 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-46 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-43 rssi_med:-33 rssi_max:-29
**LINK** peer:0x00000010 proto:espnow n:7 rssi_min:-49 rssi_med:-45 rssi_max:-45

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6603038 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-50 rssi_max:-46
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-41 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:43 rssi_min:-48 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-36 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000010 proto:ble n:48 rssi_min:-82 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-30 rssi_med:-28 rssi_max:-27
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-82 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-46 rssi_med:-45 rssi_max:-43
