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

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-37 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:55 rssi_min:-36 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000001 proto:espnow n:4 rssi_min:-33 rssi_med:-33 rssi_max:-33

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-32 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-33 rssi_med:-32 rssi_max:-31

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-32 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-36 rssi_med:-32 rssi_max:-32

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-33 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-35 rssi_med:-32 rssi_max:-31

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-35 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-32 rssi_med:-32 rssi_max:-31

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-36 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-32 rssi_med:-32 rssi_max:-32

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-32 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-33 rssi_med:-32 rssi_max:-32

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-33 rssi_med:-32 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-36 rssi_med:-32 rssi_max:-31

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-32 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-35 rssi_med:-32 rssi_max:-32

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-32 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-35 rssi_med:-32 rssi_max:-32

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-35 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-37 rssi_med:-32 rssi_max:-31

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-38 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-36 rssi_med:-32 rssi_max:-32

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:780000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-37 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-35 rssi_med:-32 rssi_max:-32

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:840000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-36 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-36 rssi_med:-32 rssi_max:-32

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:900000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-32 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-33 rssi_med:-32 rssi_max:-32

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:960000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-37 rssi_med:-32 rssi_max:-32
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-33 rssi_med:-32 rssi_max:-32

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1020000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-35 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-35 rssi_med:-32 rssi_max:-32

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1080000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-36 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-35 rssi_med:-32 rssi_max:-32

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1140000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-36 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-36 rssi_med:-32 rssi_max:-29

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1200000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-35 rssi_med:-32 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-36 rssi_med:-32 rssi_max:-32

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1260000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-45 rssi_med:-33 rssi_max:-31
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-36 rssi_med:-32 rssi_max:-30

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1320000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-30 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-40 rssi_med:-34 rssi_max:-31

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1380000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-37 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-34 rssi_med:-30 rssi_max:-28

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1440000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-36 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-32 rssi_med:-30 rssi_max:-29

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1500000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-35 rssi_med:-31 rssi_max:-29
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-39 rssi_med:-34 rssi_max:-32

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1560000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-31 rssi_med:-31 rssi_max:-29
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-38 rssi_med:-34 rssi_max:-33

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-58 rssi_med:-51 rssi_max:-33

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-55 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-40 rssi_med:-40 rssi_max:-36

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-43 rssi_med:-36 rssi_max:-34

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-57 rssi_med:-41 rssi_max:-33

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-71 rssi_med:-62 rssi_max:-52

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-63 rssi_med:-57 rssi_max:-55

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-63 rssi_med:-57 rssi_max:-56

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-78 rssi_med:-63 rssi_max:-58

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-83 rssi_med:-74 rssi_max:-62

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-71 rssi_med:-64 rssi_max:-62

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-91 rssi_med:-74 rssi_max:-64

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-95 rssi_med:-83 rssi_max:-81

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:780000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-91 rssi_med:-83 rssi_max:-81

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:840000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-91 rssi_med:-82 rssi_max:-80

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:900000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:4 rssi_min:-95 rssi_med:-92 rssi_max:-87

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:960000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-95 rssi_med:-73 rssi_max:-43

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1020000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-68 rssi_med:-41 rssi_max:-31
