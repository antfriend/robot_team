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


---


---


---


---


---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:47 last_lon:46 t_ms:9913863 stream:0x59fb8ce8 wall:0 node:0x00000010

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:8 last_lon:7 t_ms:9939665 stream:0x59fb8ce8 wall:0 node:0x00000010

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:2 removed:48 last_lon:47 t_ms:16023693 stream:0x946fea42 wall:0 node:0x00000010

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:2 removed:48 last_lon:47 t_ms:16023693 stream:0x946fea42 wall:0 node:0x00000010

---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:1 removed:15 last_lon:14 t_ms:0 stream:0x00000000 wall:0 node:0x00000010
**STREAMS-EXPLAINED** n:14 0x59fb8ce8 0xbdc62024 0xe7384824 0xaf869fce 0x161e88ac 0x67ec2883 0x3ab84e5a 0xbe6d9616 0x6a2120c2 0xdffbae31 0x6549a5c7 0x185f5a4b 0x946fea42 0x32464d87

---

@LAT100LON5 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:3 removed:48 last_lon:47 t_ms:325212 stream:0xf796e624 wall:0 node:0x00000010

---

@LAT100LON6 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:3 removed:48 last_lon:47 t_ms:325212 stream:0xf796e624 wall:0 node:0x00000010

---

@LAT100LON7 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:2 removed:4 last_lon:3 t_ms:0 stream:0x00000000 wall:0 node:0x00000010
**STREAMS-EXPLAINED** n:4 0xe334a7e1 0xbe8a1293 0x9929f0cc 0xf796e624

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:53756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-66 rssi_med:-44 rssi_max:-39
**LINK** peer:0x00000300 proto:espnow n:14 rssi_min:-41 rssi_med:-31 rssi_max:-26

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:113755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-79 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-43 rssi_med:-15 rssi_max:-14

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:173756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-34 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-16 rssi_med:-15 rssi_max:-15

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:233756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-16 rssi_med:-15 rssi_max:-15

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:293755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-34 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-16 rssi_med:-15 rssi_max:-14

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:353756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-16 rssi_med:-15 rssi_max:-14

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:413756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:473756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-16 rssi_med:-15 rssi_max:-14

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:533756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-79 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:593755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:653756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:69 rssi_min:-82 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:713756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-16 rssi_med:-14 rssi_max:-14
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-80 rssi_med:-29 rssi_max:-29

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:773756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:833755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:893756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-79 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-16 rssi_med:-15 rssi_max:-14

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:953755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-16 rssi_med:-14 rssi_max:-14
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-33 rssi_med:-29 rssi_max:-29

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1013755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-16 rssi_med:-14 rssi_max:-14
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-80 rssi_med:-29 rssi_max:-29

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1073756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-16 rssi_med:-14 rssi_max:-14
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-76 rssi_med:-29 rssi_max:-29

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1133755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1193755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1253756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-76 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:18 rssi_min:-16 rssi_med:-15 rssi_max:-14

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1313755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1373756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-79 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1433755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-77 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1493756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1553755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-79 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1613756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1673756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-76 rssi_med:-29 rssi_max:-27
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1733756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1793756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1853756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:21 rssi_min:-60 rssi_med:-15 rssi_max:-14

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1913755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-16 rssi_med:-15 rssi_max:-14

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1973756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-16 rssi_med:-14 rssi_max:-14
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-33 rssi_med:-29 rssi_max:-29

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2033756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-33 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:7 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2093755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-33 rssi_med:-29 rssi_max:-29

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2153755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-80 rssi_med:-29 rssi_max:-29

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2213756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-58 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:15 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2273755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2333756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-79 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2393756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-33 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2453755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-79 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2513755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-81 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2573756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-79 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2633756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-16 rssi_med:-14 rssi_max:-14

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2693755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-15 rssi_med:-14 rssi_max:-13

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2753756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-33 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2813756 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:21 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2873755 stream:0xc8a01245 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-33 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-15 rssi_med:-14 rssi_max:-14

---

@LAT100LON8 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:4 removed:48 last_lon:47 t_ms:2494798 stream:0x95cc309e wall:0 node:0x00000010

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2555362 stream:0x95cc309e wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3709178 stream:0x95cc309e wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec
**COVERED** windows:1 entities:9 window_ms:555816 first_t_ms:3109178 last_t_ms:3109178 covered_by:@LAT96LON0
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92 windows:1
**COVERED-ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95 windows:1

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3936032 stream:0x95cc309e wall:0 window_ms:61831 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:53204 stream:0xb4347c09 wall:0 window_ms:60000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1202996 stream:0xb4347c09 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
**COVERED** windows:1 entities:7 window_ms:549792 first_t_ms:602996 last_t_ms:602996 covered_by:@LAT96LON3
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93 windows:1

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1802996 stream:0xb4347c09 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
**CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2402996 stream:0xb4347c09 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,84a329c78fec,e6b32d2cea8b,0283cce0e689,64677217947d

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6002995 stream:0xb4347c09 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d,0283cce0e689
**COVERED** windows:5 entities:8 window_ms:3000000 first_t_ms:3002996 last_t_ms:5402996 covered_by:@LAT96LON6
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-39 windows:5
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-74 windows:5
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-83 windows:5
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-85 windows:5
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:4 rssi:-91 windows:4
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:5 rssi:-92 windows:5
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:2 rssi:-93 windows:2
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:5 rssi:-91 windows:5

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8402996 stream:0xb4347c09 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,18a5ffbae2d6,64677217947d,84a329c78fec
**COVERED** windows:3 entities:8 window_ms:1800000 first_t_ms:6602996 last_t_ms:7802996 covered_by:@LAT96LON7
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-40 windows:3
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-73 windows:3
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-84 windows:3
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-90 windows:3
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:3 rssi:-90 windows:3
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:3 rssi:-91 windows:3
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-88 windows:2
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:2 rssi:-95 windows:2

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12002996 stream:0xb4347c09 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,18a5ffbae2d6,84a329c78fec
**COVERED** windows:5 entities:8 window_ms:3000001 first_t_ms:9002996 last_t_ms:11402996 covered_by:@LAT96LON8
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-40 windows:5
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-70 windows:5
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-80 windows:5
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-89 windows:5
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:5 rssi:-91 windows:5
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-91 windows:4
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-91 windows:4
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:5 rssi:-92 windows:5

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:14402996 stream:0xb4347c09 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,84a329c78fec
**COVERED** windows:3 entities:8 window_ms:1800000 first_t_ms:12602996 last_t_ms:13802996 covered_by:@LAT96LON9
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-40 windows:3
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-72 windows:3
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-83 windows:3
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-88 windows:3
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:3 rssi:-89 windows:3
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:2 rssi:-91 windows:2
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:3 rssi:-90 windows:3
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-92 windows:2

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:15003021 stream:0xb4347c09 wall:0 window_ms:600026 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,84a329c78fec,18a5ffbae2d6,0283cce0e689

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:15603021 stream:0xb4347c09 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,84a329c78fec,18a5ffbae2d6

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:19202995 stream:0xb4347c09 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,18a5ffbae2d6,84a329c78fec,64677217947d
**COVERED** windows:5 entities:9 window_ms:2999975 first_t_ms:16202996 last_t_ms:18602996 covered_by:@LAT96LON12
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-40 windows:5
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-73 windows:5
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-81 windows:5
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-88 windows:5
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:5 rssi:-91 windows:5
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:5 rssi:-91 windows:5
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:5 rssi:-92 windows:5
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-90 windows:2
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95 windows:1

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:53252 stream:0xc49e1cd4 wall:0 window_ms:60025 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1202996 stream:0xc49e1cd4 wall:0 window_ms:600001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,18a5ffbae2d6
**COVERED** windows:1 entities:8 window_ms:549744 first_t_ms:602996 last_t_ms:602996 covered_by:@LAT96LON14
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92 windows:1

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4802996 stream:0xc49e1cd4 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d,18a5ffbae2d6
**COVERED** windows:5 entities:8 window_ms:2999999 first_t_ms:1802996 last_t_ms:4202996 covered_by:@LAT96LON15
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-40 windows:5
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-73 windows:5
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-82 windows:5
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-87 windows:5
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:5 rssi:-91 windows:5
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:5 rssi:-92 windows:5
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:3 rssi:-92 windows:3
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7802996 stream:0xc49e1cd4 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d,18a5ffbae2d6,0283cce0e689
**COVERED** windows:4 entities:8 window_ms:2400000 first_t_ms:5402996 last_t_ms:7202996 covered_by:@LAT96LON16
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-39 windows:4
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-74 windows:4
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-83 windows:4
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:3 rssi:-91 windows:3
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-90 windows:4
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-90 windows:4
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:4 rssi:-90 windows:4
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-96 windows:2

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11402996 stream:0xc49e1cd4 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d,18a5ffbae2d6,0283cce0e689
**COVERED** windows:5 entities:8 window_ms:3000000 first_t_ms:8402996 last_t_ms:10802996 covered_by:@LAT96LON17
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-40 windows:5
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-74 windows:5
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-82 windows:5
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-88 windows:5
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:5 rssi:-90 windows:5
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:4 rssi:-92 windows:4
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:5 rssi:-91 windows:5
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:3 rssi:-92 windows:3

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:15002996 stream:0xc49e1cd4 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96
**RUN** windows_since_last:6 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,18a5ffbae2d6,84a329c78fec
**COVERED** windows:5 entities:8 window_ms:3000001 first_t_ms:12002996 last_t_ms:14402996 covered_by:@LAT96LON18
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-40 windows:5
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-74 windows:5
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-81 windows:5
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:3 rssi:-89 windows:3
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-88 windows:5
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:5 rssi:-90 windows:5
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:5 rssi:-93 windows:5
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:5 rssi:-90 windows:5

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52188 stream:0x516c169d wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT100LON9 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:3 removed:14 last_lon:13 t_ms:1082603 stream:0x516c169d wall:0 node:0x00000010
**STREAMS-EXPLAINED** n:13 0xc8a01245 0xe6a101ec 0x7945c57c 0x50956f00 0xbce80555 0x6d2ca283 0x354b03a5 0x66486d22 0x95cc309e 0x982c89ff 0xb4347c09 0xc49e1cd4 0x516c169d

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x516c169d wall:0 t_ms:1095398 node:0x10 from:0x300
**REMAP** prev_stream:0x31d190a2 prev_t_ms:4211 offset_ms:1091187 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x516c169d wall:0 t_ms:1111398 node:0x10 from:0x300
**REMAP** prev_stream:0xcc392cf5 prev_t_ms:5888 offset_ms:1105510 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1158738 stream:0x516c169d wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2308506 stream:0x516c169d wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:4 ids:f83eb025d3d2,bc102f237ace,e6b32d2cea8b,02c57d2e0f0d
**COVERED** windows:1 entities:6 window_ms:549768 first_t_ms:1708506 last_t_ms:1708506 covered_by:@LAT96LON21
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95 windows:1

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x0870722b wall:0 t_ms:1091357 node:0x10 from:0x200
**REMAP** prev_stream:0x7f5e3f9d prev_t_ms:5877 offset_ms:1085480 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1138670 stream:0x0870722b wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x0870722b wall:0 t_ms:1823418 node:0x10 from:0x200
**REMAP** prev_stream:0xb4e66af6 prev_t_ms:3735 offset_ms:1819683 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1872903 stream:0x0870722b wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-53
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbeb39900 wall:0 t_ms:7189 node:0x10 from:0x12
**REMAP** prev_stream:0xbdcdb608 prev_t_ms:3427 offset_ms:3762 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:56947 stream:0xbeb39900 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x1de72b4d wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:53252 stream:0x1de72b4d wall:0 window_ms:60026 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:441524 stream:0x1de72b4d wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xd2dacc37 wall:0 t_ms:5260810 node:0x10 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbb1177f2 wall:0 t_ms:0 node:0x10 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:53252 stream:0xbb1177f2 wall:0 window_ms:60033 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:602996 stream:0xbb1177f2 wall:0 window_ms:549744 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-23
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1202997 stream:0xbb1177f2 wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,18a5ffbae2d6

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1802996 stream:0xbb1177f2 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:4
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,84a329c78fec,18a5ffbae2d6

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2402997 stream:0xbb1177f2 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,84a329c78fec,0283cce0e689,5ce28c488e0c,e6b32d2cea8b,18a5ffbae2d6

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3002996 stream:0xbb1177f2 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-25
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,0283cce0e689,18a5ffbae2d6

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3602996 stream:0xbb1177f2 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,5ce28c488e0c,18a5ffbae2d6,0283cce0e689

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4203025 stream:0xbb1177f2 wall:0 window_ms:600029 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-25
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,84a329c78fec,18a5ffbae2d6

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4803025 stream:0xbb1177f2 wall:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,18a5ffbae2d6,84a329c78fec

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5403024 stream:0xbb1177f2 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,18a5ffbae2d6,84a329c78fec

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6003024 stream:0xbb1177f2 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,18a5ffbae2d6,84a329c78fec

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6603024 stream:0xbb1177f2 wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,84a329c78fec,18a5ffbae2d6

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7203024 stream:0xbb1177f2 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,18a5ffbae2d6

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7803024 stream:0xbb1177f2 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,0283cce0e689,18a5ffbae2d6,64677217947d

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8403024 stream:0xbb1177f2 wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-95
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,18a5ffbae2d6,64677217947d,0283cce0e689,5ce28c488e0c

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9003024 stream:0xbb1177f2 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c,0283cce0e689,18a5ffbae2d6

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9603024 stream:0xbb1177f2 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-96
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c,18a5ffbae2d6,0283cce0e689

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10203024 stream:0xbb1177f2 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,64677217947d,0283cce0e689,18a5ffbae2d6

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10803024 stream:0xbb1177f2 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,18a5ffbae2d6,64677217947d,0283cce0e689

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11403025 stream:0xbb1177f2 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-24
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-97
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:5
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,5ce28c488e0c,18a5ffbae2d6
