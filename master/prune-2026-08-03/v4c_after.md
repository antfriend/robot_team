# V4-C Edge Node TTDB

```mmpdb
db_id: v4c-edge-001
db_name: V4-C Edge Node
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: v4c-edge
  role: remote-cluster-gateway
  perspective: spine-tail
  scope: remote-cluster
  constraints:
    - off-grid
    - airtime-scarce
  globe:
    frame: mesh-topology
    origin: "@LAT0LON30"
    mapping: "tail of the A-B-C spine; gateways the off-grid K10 cluster"
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
lon: 30
```

---

@LAT0LON30 | created:1750000000 | updated:1750000000 | relates:navigates_to@LAT0LON20

Edge home. Aggregates the off-grid K10 cluster's percepts and forwards summaries
to V4-B over LoRa.

---


---


---


---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x59fb8ce8 wall:0 t_ms:4048832 node:0x12 from:0x11
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7137667 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-51 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-80 rssi_med:-50 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-23 rssi_med:-22 rssi_max:-21
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-40 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:8 rssi_min:-39 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000001 proto:espnow n:3 rssi_min:-37 rssi_med:-32 rssi_max:-32

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7197667 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-23 rssi_med:-21 rssi_max:-19
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-43 rssi_med:-40 rssi_max:-36
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-62 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-43 rssi_med:-40 rssi_max:-34
**LINK** peer:0x00000001 proto:espnow n:1 rssi_min:-40 rssi_med:-40 rssi_max:-40

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7257667 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-49 rssi_med:-38 rssi_max:-32
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-23 rssi_med:-21 rssi_max:-19
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-84 rssi_med:-57 rssi_max:-44
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-56 rssi_med:-39 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-60 rssi_med:-43 rssi_max:-32
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-51

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7317667 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-28 rssi_med:-24 rssi_max:-20
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-49 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-52 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-56 rssi_med:-30 rssi_max:-26
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-39 rssi_max:-32
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-56 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-56 rssi_med:-44 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-46 rssi_med:-41 rssi_max:-29

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7377667 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-42 rssi_med:-39 rssi_max:-34
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-40 rssi_max:-37
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-31 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-26 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-43 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-47 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-53 rssi_max:-52

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7437666 stream:0x59fb8ce8 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-45 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-41 rssi_med:-38 rssi_max:-32
**LINK** peer:0x00000200 proto:ble n:39 rssi_min:-80 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-31 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-28 rssi_med:-25 rssi_max:-24
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-50 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-40 rssi_max:-37
