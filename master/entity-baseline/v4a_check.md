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

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xe334a7e1 wall:0 t_ms:25286 node:0x10 from:0x300
**REMAP** prev_stream:0x6996769c prev_t_ms:23280 offset_ms:2006 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:54257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:54 rssi_min:-55 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000300 proto:espnow n:10 rssi_min:-43 rssi_med:-42 rssi_max:-41

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:54257 stream:0xe334a7e1 wall:0 window_ms:62036 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:114258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-55 rssi_max:-45
**LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-55 rssi_med:-42 rssi_max:-36

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:174258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-77 rssi_med:-32 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-66 rssi_med:-23 rssi_max:-11

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:234257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-76 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-13 rssi_med:-11 rssi_max:-11

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:294257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-13 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-32 rssi_med:-26 rssi_max:-25

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:354258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-31 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-13 rssi_med:-12 rssi_max:-11

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:414258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-12 rssi_med:-11 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-32 rssi_med:-26 rssi_max:-25

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:474258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-12 rssi_med:-11 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-26 rssi_max:-25

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:534257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-13 rssi_med:-11 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:56 rssi_min:-32 rssi_med:-26 rssi_max:-25

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:594258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-12 rssi_med:-11 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-77 rssi_med:-26 rssi_max:-25

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:603969 stream:0xe334a7e1 wall:0 window_ms:547675 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:654257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-73 rssi_med:-11 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:53 rssi_min:-77 rssi_med:-26 rssi_max:-25

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:714257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-13 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-79 rssi_med:-26 rssi_max:-25

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:774257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-13 rssi_med:-11 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-26 rssi_max:-25

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:834258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-79 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-13 rssi_med:-11 rssi_max:-11

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:894257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-13 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:59 rssi_min:-32 rssi_med:-27 rssi_max:-26

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:954258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-32 rssi_med:-27 rssi_max:-26
**LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-13 rssi_med:-12 rssi_max:-11

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1014258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-13 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-69 rssi_med:-27 rssi_max:-26

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1074258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-13 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-32 rssi_med:-27 rssi_max:-26

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1134258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-13 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-77 rssi_med:-27 rssi_max:-26

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1194258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:24 rssi_min:-13 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-32 rssi_med:-26 rssi_max:-25

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1203968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1254258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-63 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-32 rssi_med:-26 rssi_max:-25

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1314258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:21 rssi_min:-13 rssi_med:-11 rssi_max:-11

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1374257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-13 rssi_med:-11 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-32 rssi_med:-26 rssi_max:-25

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1434258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-13 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-26 rssi_max:-25

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1494257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-13 rssi_med:-11 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-26 rssi_max:-25

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1554258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-13 rssi_med:-12 rssi_max:-11

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1614257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-12 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-26 rssi_max:-25

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1674257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-13 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-32 rssi_med:-26 rssi_max:-25

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1734258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-32 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-13 rssi_med:-11 rssi_max:-11

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1794258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-82 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-13 rssi_med:-11 rssi_max:-11

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1803968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1854258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-31 rssi_med:-26 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-13 rssi_med:-11 rssi_max:-11

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1914258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-27 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-13 rssi_med:-12 rssi_max:-11

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1974258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-13 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-27 rssi_max:-25

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2034258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-13 rssi_med:-12 rssi_max:-11
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-32 rssi_med:-27 rssi_max:-25

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2094258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:73 rssi_min:-80 rssi_med:-27 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-13 rssi_med:-12 rssi_max:-11

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2154258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-27 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-13 rssi_med:-12 rssi_max:-11

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2214257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:espnow n:2 rssi_min:-12 rssi_med:-12 rssi_max:-12
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-32 rssi_med:-27 rssi_max:-25

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2274257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:58 rssi_min:-32 rssi_med:-27 rssi_max:-25
**LINK** peer:0x00000300 proto:espnow n:6 rssi_min:-12 rssi_med:-12 rssi_max:-11

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2334258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-32 rssi_med:-27 rssi_max:-25

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2394258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-26 rssi_max:-25

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2403969 stream:0xe334a7e1 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2454257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:57 rssi_min:-76 rssi_med:-27 rssi_max:-25

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2514258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-27 rssi_max:-25

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2574258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:62 rssi_min:-32 rssi_med:-27 rssi_max:-25

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2634258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-27 rssi_max:-25

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2694258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-27 rssi_max:-25

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2754257 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:66 rssi_min:-32 rssi_med:-27 rssi_max:-25

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2814258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:60 rssi_min:-32 rssi_med:-27 rssi_max:-25

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2874258 stream:0xe334a7e1 wall:0 window_ms:60000
**LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-27 rssi_max:-25

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3003969 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3603968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4203991 stream:0xe334a7e1 wall:0 window_ms:600023 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4803968 stream:0xe334a7e1 wall:0 window_ms:599977 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5403980 stream:0xe334a7e1 wall:0 window_ms:600012 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6003975 stream:0xe334a7e1 wall:0 window_ms:599995 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6603977 stream:0xe334a7e1 wall:0 window_ms:600001 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7203968 stream:0xe334a7e1 wall:0 window_ms:599992 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7803969 stream:0xe334a7e1 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8403968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9003968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9603968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10203969 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-97

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10803969 stream:0xe334a7e1 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11403968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12003968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-97

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12603968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13203968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13803968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:14403968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:15003968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:15603968 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:16204001 stream:0xe334a7e1 wall:0 window_ms:600033 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:16804001 stream:0xe334a7e1 wall:0 window_ms:599999 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:17404000 stream:0xe334a7e1 wall:0 window_ms:599999 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:18004000 stream:0xe334a7e1 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:18604000 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:19204000 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:19804000 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:20404000 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:21004000 stream:0xe334a7e1 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:21604000 stream:0xe334a7e1 wall:0 window_ms:600001 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:22204000 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-26
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:22803999 stream:0xe334a7e1 wall:0 window_ms:599998 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:23403999 stream:0xe334a7e1 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbe8a1293 wall:0 t_ms:270217 node:0x10 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:329282 stream:0xbe8a1293 wall:0 window_ms:60026 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-97

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:879085 stream:0xbe8a1293 wall:0 window_ms:549802 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1479089 stream:0xbe8a1293 wall:0 window_ms:600005 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2079088 stream:0xbe8a1293 wall:0 window_ms:599999 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2679088 stream:0xbe8a1293 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3279089 stream:0xbe8a1293 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3879089 stream:0xbe8a1293 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-96

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4479088 stream:0xbe8a1293 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-28
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
