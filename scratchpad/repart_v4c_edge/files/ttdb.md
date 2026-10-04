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

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:846755 stream:0xbdc62024 wall:0 node:0x00000012

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:1 removed:16 last_lon:15 t_ms:95098 stream:0x794a3f7d wall:0 node:0x00000012
**STREAMS-EXPLAINED** n:16 0x59fb8ce8 0xbdc62024 0xe7384824 0xaf869fce 0xdffbae31 0xbe8a1293 0xbce80555 0x66486d22 0x95cc309e 0xbeb39900 0x1de72b4d 0x0c8e926c 0xdd4bfb6c 0xd2dacc37 0xbb1177f2 0x7d224c73

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:48 last_lon:47 t_ms:19075 stream:0xbc01f8c3 wall:0 node:0x00000012

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbc01f8c3 wall:0 t_ms:0 node:0x12 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:2 removed:48 last_lon:47 t_ms:34581 stream:0xbc01f8c3 wall:0 node:0x00000012

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x26826178 wall:0 t_ms:0 node:0x12 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xb23c7677 wall:0 t_ms:14079 node:0x12 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x5b53f35b wall:0 t_ms:19182 node:0x12 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xdcd3edce wall:0 t_ms:8235520 node:0x12 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xdcd3edce wall:0 t_ms:8314867 node:0x12 from:0x300
**REMAP** prev_stream:0x1420f15c prev_t_ms:3464 offset_ms:8311403 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xee98fca8 wall:0 t_ms:4459929 node:0x12 from:0x11
**REMAP** prev_stream:0x8aaab6fc prev_t_ms:3704 offset_ms:4456225 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xc909d5a8 wall:0 t_ms:138646 node:0x12 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xc909d5a8 wall:0 t_ms:3488980 node:0x12 from:0x300
**REMAP** prev_stream:0x4a8164a3 prev_t_ms:3185 offset_ms:3485795 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT103LON0 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3530047 ±21 frame:4000
said: 1 | **LINKWIN** t_ms:3642652 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:50 rssi_min:-80 rssi_med:-43 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:espnow n:23 rssi_min:-30 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON8192 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3530088 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:3642652 stream:0xc909d5a8 wall:0 window_ms:60041 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON1 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3590047 ±21 frame:4000
said: 1 | **LINKWIN** t_ms:3702652 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-44 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-43 rssi_max:-42
```

---

@LAT103LON2 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3650048 ±21 frame:4000
said: 1 | **LINKWIN** t_ms:3762652 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:21 rssi_min:-29 rssi_med:-28 rssi_max:-28
```

---

@LAT103LON3 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3710048 ±21 frame:4000
said: 1 | **LINKWIN** t_ms:3822652 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-44 rssi_max:-41
```

---

@LAT103LON4 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3770048 ±22 frame:4000
said: 1 | **LINKWIN** t_ms:3882652 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-29 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-44 rssi_max:-43
```

---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:3 removed:48 last_lon:47 t_ms:4013569 stream:0xc909d5a8 wall:0 node:0x00000012

---

@LAT100LON5 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:2 removed:16 last_lon:15 t_ms:0 stream:0x00000000 wall:0 node:0x00000012

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4100164 stream:0xc909d5a8 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT103LON5 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3989666 ±21 frame:4000
said: 1 | **LINKWIN** t_ms:4102269 stream:0xc909d5a8 wall:0 window_ms:62105
said: 2 | **LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-44 rssi_max:-43
```

---

@LAT103LON6 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4049666 ±22 frame:4000
said: 1 | **LINKWIN** t_ms:4162270 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 3 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-44 rssi_max:-43
```

---

@LAT103LON7 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4109666 ±21 frame:4000
said: 1 | **LINKWIN** t_ms:4222270 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-29 rssi_med:-28 rssi_max:-28
```

---

@LAT103LON8 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4169667 ±21 frame:4000
said: 1 | **LINKWIN** t_ms:4282270 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-29 rssi_med:-28 rssi_max:-28
```

---

@LAT103LON9 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4229667 ±21 frame:4000
said: 1 | **LINKWIN** t_ms:4342270 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:27 rssi_min:-29 rssi_med:-28 rssi_max:-27
```

---

@LAT103LON10 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4289668 ±21 frame:4000
said: 1 | **LINKWIN** t_ms:4402270 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-29 rssi_med:-28 rssi_max:-28
```

---

@LAT103LON11 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4349667 ±21 frame:4000
said: 1 | **LINKWIN** t_ms:4462270 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 3 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-44 rssi_max:-43
```

---

@LAT103LON12 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4409668 ±21 frame:4000
said: 1 | **LINKWIN** t_ms:4522270 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-48 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-43 rssi_med:-29 rssi_max:-26
```

---

@LAT103LON8193 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1777903 ±21 frame:5000
said: 1 | **ENTWIN** t_ms:2041908 stream:0x40bbc10f wall:0 window_ms:60000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON13 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1779992 ±21 frame:5000
said: 1 | **LINKWIN** t_ms:2043997 stream:0x40bbc10f wall:0 window_ms:62089
said: 2 | **LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-46 rssi_med:-31 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-45 rssi_max:-41
```

---

@LAT103LON14 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1987973 ±21 frame:5000
said: 1 | **LINKWIN** t_ms:2251967 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-81 rssi_med:-44 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-36 rssi_med:-32 rssi_max:-31
```

---

@LAT103LON8194 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1988009 ±21 frame:5000
said: 1 | **ENTWIN** t_ms:2251967 stream:0x40bbc10f wall:0 window_ms:60036 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON15 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2047973 ±22 frame:5000
said: 1 | **LINKWIN** t_ms:2311967 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-38 rssi_med:-32 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-44 rssi_max:-41
```

---

@LAT103LON16 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2107974 ±21 frame:5000
said: 1 | **LINKWIN** t_ms:2371966 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:21 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-44 rssi_max:-41
```

---

@LAT103LON17 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2167974 ±21 frame:5000
said: 1 | **LINKWIN** t_ms:2431966 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-38 rssi_med:-32 rssi_max:-32
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-44 rssi_max:-40
```

---

@LAT103LON18 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21881950 ±21 frame:5500
seq: 1
follows: 0x00000010:86 0x00000011:48 0x00000100:121 0x00000200:5 0x00000300:655
said: 1 | **LINKWIN** t_ms:21880967 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-46 rssi_max:-45
said: 3 | **LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-33 rssi_med:-31 rssi_max:-29
```

---

@LAT103LON8195 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21881992 ±21 frame:5500
seq: 2
follows: 0x00000010:86 0x00000011:48 0x00000100:121 0x00000200:5 0x00000300:655
said: 1 | **ENTWIN** t_ms:21880967 stream:0x9afbb748 wall:0 window_ms:60042 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON19 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 21941950 ±21 frame:5500
seq: 3
follows: 0x00000010:86 0x00000011:48 0x00000100:121 0x00000200:5 0x00000300:657
said: 1 | **LINKWIN** t_ms:21940967 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-37 rssi_med:-31 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-81 rssi_med:-46 rssi_max:-45
```

---

@LAT103LON20 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 22001952 ±21 frame:5500
seq: 4
follows: 0x00000010:86 0x00000011:48 0x00000100:121 0x00000200:5 0x00000300:659
said: 1 | **LINKWIN** t_ms:22000967 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-46 rssi_max:-45
said: 3 | **LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-36 rssi_med:-31 rssi_max:-30
```

---

@LAT103LON21 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 22061951 ±21 frame:5500
seq: 5
follows: 0x00000010:86 0x00000011:48 0x00000100:121 0x00000200:5 0x00000300:661
said: 1 | **LINKWIN** t_ms:22060967 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-32 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-44 rssi_max:-41
```

---

@LAT103LON22 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 22121953 ±21 frame:5500
seq: 6
follows: 0x00000010:86 0x00000011:48 0x00000100:121 0x00000200:5 0x00000300:663
said: 1 | **LINKWIN** t_ms:22120967 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-29 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-43 rssi_max:-41
```
