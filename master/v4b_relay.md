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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60978 synced:0 window_ms:60978
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-23 rssi_med:-23 rssi_max:-21
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-51 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-47 rssi_max:-45

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:61032 synced:0 window_ms:61032
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-23 rssi_med:-22 rssi_max:-21
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-86 rssi_med:-61 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-57 rssi_med:-54 rssi_max:-35

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:122033 synced:0 window_ms:61001
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-65 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-55 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-22 rssi_med:-22 rssi_max:-21

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:183036 synced:0 window_ms:61003
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-22 rssi_med:-22 rssi_max:-22
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-56 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-37 rssi_max:-34

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:244036 synced:0 window_ms:61000
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-80 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-54 rssi_med:-53 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-22 rssi_med:-22 rssi_max:-22

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:305076 synced:0 window_ms:61040
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-22 rssi_med:-22 rssi_max:-22
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-54 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-63 rssi_max:-60

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:61562 synced:0 window_ms:61562
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-36 rssi_max:-32
**LINK** peer:0x00000200 proto:ble n:72 rssi_min:-82 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-22 rssi_med:-21 rssi_max:-21
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-51 rssi_med:-45 rssi_max:-42

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:122562 synced:0 window_ms:61000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-22 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-59 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-81 rssi_med:-54 rssi_max:-53

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:183622 synced:0 window_ms:61060
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-36 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-80 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-22 rssi_med:-21 rssi_max:-20
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-46 rssi_med:-44 rssi_max:-35

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-38 rssi_med:-25 rssi_max:-23
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-53 rssi_med:-36 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-50 rssi_med:-42 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-81 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-54 rssi_max:-49

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-83 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-63 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-26 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-53 rssi_med:-51 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-41 rssi_med:-36 rssi_max:-34

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-83 rssi_med:-63 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-54 rssi_med:-50 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-82 rssi_med:-53 rssi_max:-47
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-27 rssi_med:-25 rssi_max:-24

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:240000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-52 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-63 rssi_max:-53
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-26 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-41 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-47 rssi_max:-45

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:300000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-27 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-48 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-59 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-57 rssi_med:-46 rssi_max:-32

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:360000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-82 rssi_med:-61 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-61 rssi_max:-51
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-27 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-53 rssi_med:-48 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-46 rssi_med:-44 rssi_max:-40

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:420000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-66 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-63 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-26 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-61 rssi_med:-51 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-64 rssi_med:-58 rssi_max:-53

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:480030 synced:0 window_ms:60030
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-60 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-60 rssi_med:-52 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-37 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-65 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-62 rssi_med:-49 rssi_max:-42

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:540030 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-82 rssi_med:-64 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-59 rssi_max:-49
**LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-33 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-58 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-50 rssi_med:-48 rssi_max:-44

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:600030 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-59 rssi_max:-52
**LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-32 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-69 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-50 rssi_med:-48 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-57 rssi_med:-49 rssi_max:-47

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:660030 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-65 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-38 rssi_med:-31 rssi_max:-29
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-54 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-55 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-59 rssi_max:-51

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:720030 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-58 rssi_med:-51 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-83 rssi_med:-65 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-66 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-65 rssi_max:-53
**LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-38 rssi_med:-31 rssi_max:-30

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:780030 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-36 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-62 rssi_max:-51
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-66 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-66 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-56 rssi_med:-46 rssi_max:-43

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:840030 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-58 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-35 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-53 rssi_med:-43 rssi_max:-36
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-66 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-67 rssi_med:-55 rssi_max:-47

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:900030 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-63 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-44 rssi_med:-42 rssi_max:-35
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-33 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-69 rssi_med:-50 rssi_max:-43

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:960031 synced:0 window_ms:60001
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-63 rssi_max:-51
**LINK** peer:0x00000200 proto:espnow n:9 rssi_min:-54 rssi_med:-41 rssi_max:-36
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-60 rssi_med:-50 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:24 rssi_min:-82 rssi_med:-57 rssi_max:-51
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-32 rssi_med:-24 rssi_max:-17

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1020031 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-26 rssi_med:-24 rssi_max:-24
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-62 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-54 rssi_med:-50 rssi_max:-45

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1080031 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-25 rssi_med:-24 rssi_max:-23
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-85 rssi_med:-65 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-61 rssi_med:-52 rssi_max:-44

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1140031 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-82 rssi_med:-64 rssi_max:-53
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-25 rssi_med:-24 rssi_max:-23
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-62 rssi_med:-51 rssi_max:-46

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1200032 synced:0 window_ms:60001
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-61 rssi_med:-53 rssi_max:-45
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-26 rssi_med:-24 rssi_max:-23
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-65 rssi_max:-53

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1260032 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-26 rssi_med:-24 rssi_max:-24
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-80 rssi_med:-64 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-64 rssi_med:-51 rssi_max:-45

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1320032 synced:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-25 rssi_med:-24 rssi_max:-23
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-63 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-58 rssi_med:-50 rssi_max:-44

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1380032 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-81 rssi_med:-68 rssi_max:-52
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-26 rssi_med:-24 rssi_max:-23
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-65 rssi_med:-53 rssi_max:-48

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1440032 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-86 rssi_med:-67 rssi_max:-52
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-26 rssi_med:-24 rssi_max:-23
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-64 rssi_med:-55 rssi_max:-49

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1500032 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-88 rssi_med:-69 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-71 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-25 rssi_med:-24 rssi_max:-23

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1560032 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-83 rssi_med:-68 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-25 rssi_med:-24 rssi_max:-21
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-69 rssi_med:-55 rssi_max:-48

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1620032 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:70 rssi_min:-82 rssi_med:-66 rssi_max:-60
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-24 rssi_med:-24 rssi_max:-24
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-55 rssi_med:-54 rssi_max:-49

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:97701 synced:0 window_ms:97701
**LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-76 rssi_med:-76 rssi_max:-76

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:157701 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-79 rssi_med:-73 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-100 rssi_med:-87 rssi_max:-80

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:217701 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-76 rssi_med:-73 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-97 rssi_med:-88 rssi_max:-82

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:277701 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-78 rssi_med:-76 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-99 rssi_med:-85 rssi_max:-80

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:337701 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-73 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-91 rssi_med:-82 rssi_max:-79

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:397701 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:50 rssi_min:-97 rssi_med:-82 rssi_max:-79
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-80 rssi_med:-76 rssi_max:-71

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:457701 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:44 rssi_min:-98 rssi_med:-82 rssi_max:-80
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-79 rssi_med:-78 rssi_max:-69

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3546937 synced:0 window_ms:3089236
**LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-73 rssi_med:-73 rssi_max:-73

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3606937 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:38 rssi_min:-92 rssi_med:-87 rssi_max:-82
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-80 rssi_med:-75 rssi_max:-70

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:13704678 synced:0 window_ms:10097741
**LINK** peer:0x00000200 proto:ble n:1 rssi_min:-86 rssi_med:-86 rssi_max:-86

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:13764678 synced:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:5 rssi_min:-95 rssi_med:-91 rssi_max:-86
**LINK** peer:0x00000200 proto:espnow n:2 rssi_min:-83 rssi_med:-83 rssi_max:-78

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:17728695 synced:0 window_ms:3964017
**LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-59 rssi_med:-59 rssi_max:-59

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61188 synced:0 window_ms:61188 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61996 synced:0 window_ms:61996 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60006 synced:0 window_ms:60006 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:609850 synced:0 window_ms:549844 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-96

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1209861 synced:0 window_ms:600011 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-95
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1809862 synced:0 window_ms:600001 entities:11
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2409865 synced:0 window_ms:600003 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-95
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3009866 synced:0 window_ms:600001 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-95
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-96

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3609865 synced:0 window_ms:599999 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60006 synced:0 window_ms:60006 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60000 synced:0 window_ms:60000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-67
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-94

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:610172 synced:0 window_ms:550172 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-57
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
**ENTITY** kind:wifi_ap id:d2102f3f25ea n:1 rssi:-91
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-92

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1210172 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-58
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:ce102f3f25ea n:1 rssi:-90
**ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-92

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1810172 synced:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-58
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-88

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2410172 synced:0 window_ms:600000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-57
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3010172 synced:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
