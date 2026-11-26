# K10 Percept Node TTDB

```mmpdb
db_id: k10-percept-001
db_name: K10 Percept Node
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: k10-percept
  role: percept-capture
  perspective: first-person-sensor
  scope: local-cluster
  constraints:
    - no-lora
    - espnow-default
  globe:
    frame: sensor-grid
    origin: "@LAT0LON0"
    mapping: "ambient sensors quantized onto the lat/lon knowledge grid"
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

@LAT0LON0 | created:1750000000 | updated:1750000000 | relates:navigates_to@LAT10LON0

Home node. Idle perception state. The agent rests here until a sensor reading
quantizes elsewhere on the grid.

---

@LAT10LON0 | created:1750000000 | updated:1750000000 | relates:triggers@LAT10LON0,logs@LAT0LON0

Warm ambient region. Reached when the temperature sensor reads into the upper
band. `triggers` fires the local indicator; `logs` records the observation.

---

@LAT99LON0 | created:1782170699 | updated:1782170699 | relates:logs@LAT0LON0

**SYNC** id:1 t_ms:1782170699715 recv_ms:103890 offset_ms:1782170595825

---

@LAT99LON1 | created:1782170835 | updated:1782170835 | relates:logs@LAT0LON0

**SYNC** id:2 t_ms:1782170835676 recv_ms:239291 offset_ms:1782170596385

---

@LAT98LON0 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:1 bytes:978 crc:65118C32 recv_ms:14537

---

@LAT98LON1 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:2 bytes:978 crc:65118C32 recv_ms:19353

---

@LAT98LON2 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:3 bytes:978 crc:65118C32 recv_ms:30571

---

@LAT98LON3 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:3 bytes:978 crc:65118C32 recv_ms:69125

---

@LAT98LON4 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:4 bytes:978 crc:65118C32 recv_ms:254982

---

@LAT98LON5 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:5 bytes:1121 crc:78BA4258 recv_ms:51732 applied:interval_ms:300

---

@LAT98LON6 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:5 bytes:1121 crc:78BA4258 recv_ms:70501 applied:interval_ms:300

---

@LAT98LON7 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:6 bytes:1121 crc:F69589F6 recv_ms:231581 applied:interval_ms:700

---

@LAT98LON8 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:7 bytes:1121 crc:78BA4258 recv_ms:18516 applied:interval_ms:300

---

@LAT98LON9 | created:0 | updated:0 | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:8 bytes:1121 crc:78BA4258 recv_ms:57087 applied:interval_ms:300

---

@LAT99LON2 | created:1782429925 | updated:1782429925 | relates:logs@LAT0LON0

**SYNC** id:3 t_ms:1782429925125 recv_ms:1293165 offset_ms:1782428631960

---

@LAT99LON3 | created:1782430029 | updated:1782430029 | relates:logs@LAT0LON0

**SYNC** id:4 t_ms:1782430029108 recv_ms:1397154 offset_ms:1782428631954

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:1 removed:7 last_lon:6 t_ms:61884 stream:0x2d4ae0fa wall:0 node:0x00000100

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:48 last_lon:47 t_ms:7184 stream:0xa4be8c27 wall:0 node:0x00000100

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:1 removed:16 last_lon:15 t_ms:486674 stream:0xd94c8c52 wall:0 node:0x00000100
**STREAMS-EXPLAINED** n:14 0xd2dacc37 0x531b9866 0x35bbc4c3 0x607ae994 0x342476c4 0x09b8784d 0xd8ca9bd6 0xc74761ed 0x2d4ae0fa 0xffe779bc 0x08739b89 0xd9e1f8b9 0xbb1177f2 0x9f4d711e

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xd94c8c52 wall:0 t_ms:819499 node:0x100 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:1 removed:48 last_lon:47 t_ms:830017 stream:0xd94c8c52 wall:0 node:0x00000100

---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:2 removed:4 last_lon:3 t_ms:1062595 stream:0xd94c8c52 wall:0 node:0x00000100

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x7aabf338 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x3b061427 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x8dd93153 wall:0 t_ms:332152 node:0x100 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xb23c7677 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x2f68985f wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xb9756538 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xa1f3e636 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x0a5e91fa wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x7048f17a wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xc37a3cc3 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x03316fb0 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x5b53f35b wall:0 t_ms:25861 node:0x100 from:0x11
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x59271d10 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xc48b6525 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xce36ffe3 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT100LON5 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:3 removed:48 last_lon:47 t_ms:5100230 stream:0xc909d5a8 wall:0 node:0x00000100

---

@LAT100LON6 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:2 removed:48 last_lon:47 t_ms:5109520 stream:0xc909d5a8 wall:0 node:0x00000100

---

@LAT100LON7 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:2 removed:48 last_lon:47 t_ms:5118723 stream:0xc909d5a8 wall:0 node:0x00000100

---

@LAT103LON8255 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7856942 ±21 frame:8000
seq: 897
follows: 0x00000010:1333 0x00000011:1276 0x00000012:1184 0x00000200:1974 0x00000300:4503
said: 1 | **ENTWIN** t_ms:7846250 stream:0x732acba3 wall:0 window_ms:599603 entities:3
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 6 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,5203cfd1b904
```

---

@LAT103LON8256 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8457155 ±21 frame:8000
seq: 908
follows: 0x00000010:1343 0x00000011:1286 0x00000012:1195 0x00000200:1984 0x00000300:4524
said: 1 | **ENTWIN** t_ms:8446448 stream:0x732acba3 wall:0 window_ms:600197 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5ce28c488e0c,e6b32d2cea8b
```

---

@LAT103LON8257 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10257175 ±21 frame:8000
seq: 940
follows: 0x00000010:1375 0x00000011:1317 0x00000012:1228 0x00000200:2014 0x00000300:4585
said: 1 | **ENTWIN** t_ms:10246500 stream:0x732acba3 wall:0 window_ms:599598 entities:4
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 7 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b
said: 8 | **COVERED** windows:2 entities:8 window_ms:1200403 first_t_ms:9046652 last_t_ms:9646902 covered_by:@LAT103LON8256
said: 9 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-45 windows:2
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-67 windows:2
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-76 windows:2
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-77 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-82 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-85 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
```

---

@LAT103LON8258 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 61183 ±0 frame:10000
seq: 970
follows: 0x00000010:1402 0x00000011:1345 0x00000012:1256 0x00000200:2041 0x00000300:4636
said: 1 | **ENTWIN** t_ms:48034 stream:0x92e790ea wall:0 window_ms:61183 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8259 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1209829 ±0 frame:10000
seq: 990
follows: 0x00000010:1402 0x00000011:1345 0x00000012:1256 0x00000200:2041 0x00000300:4636
said: 1 | **ENTWIN** t_ms:1196857 stream:0x92e790ea wall:0 window_ms:597568 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 7 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 8 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,0283cce0e689
said: 9 | **COVERED** windows:1 entities:5 window_ms:551078 first_t_ms:599289 last_t_ms:599289 covered_by:@LAT103LON8258
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43 windows:1
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87 windows:1
```

---

@LAT103LON8260 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 87974 ±21 frame:7500
seq: 1001
follows: 0x00000010:1408 0x00000011:1352 0x00000012:1267 0x00000200:2044 0x00000300:4641
said: 1 | **ENTWIN** t_ms:409624 stream:0xc9e0e898 wall:0 window_ms:60100 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8261 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1245534 ±21 frame:7500
seq: 1021
follows: 0x00000010:1428 0x00000011:1373 0x00000012:1287 0x00000200:2064 0x00000300:4681
said: 1 | **ENTWIN** t_ms:1567271 stream:0xc9e0e898 wall:0 window_ms:600712 entities:4
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 7 | **CORE** entities:3 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace
said: 8 | **COVERED** windows:1 entities:6 window_ms:556835 first_t_ms:966559 last_t_ms:966559 covered_by:@LAT103LON8260
said: 9 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46 windows:1
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67 windows:1
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88 windows:1
```

---

@LAT103LON8262 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1845740 ±21 frame:7500
seq: 1032
follows: 0x00000010:1439 0x00000011:1383 0x00000012:1299 0x00000200:2075 0x00000300:4702
said: 1 | **ENTWIN** t_ms:2167469 stream:0xc9e0e898 wall:0 window_ms:600199 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 7 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 8 | **CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace
```

---

@LAT103LON8263 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2445745 ±21 frame:7500
seq: 1044
follows: 0x00000010:1449 0x00000011:1394 0x00000012:1307 0x00000200:2085 0x00000300:4724
said: 1 | **ENTWIN** t_ms:2767469 stream:0xc9e0e898 wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON8264 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3045553 ±21 frame:7500
seq: 1055
follows: 0x00000010:1459 0x00000011:1404 0x00000012:1317 0x00000200:2095 0x00000300:4744
said: 1 | **ENTWIN** t_ms:3367270 stream:0xc9e0e898 wall:0 window_ms:599800 entities:4
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 7 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5203cfd1b904
```

---

@LAT103LON8265 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3645357 ±21 frame:7500
seq: 1066
follows: 0x00000010:1469 0x00000011:1414 0x00000012:1328 0x00000200:2105 0x00000300:4764
said: 1 | **ENTWIN** t_ms:3967070 stream:0xc9e0e898 wall:0 window_ms:599800 entities:4
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
said: 6 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 7 | **CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
```

---

@LAT103LON8266 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4237929 ±21 frame:7500
seq: 1078
follows: 0x00000010:1480 0x00000011:1424 0x00000012:1338 0x00000200:2116 0x00000300:4785
said: 1 | **ENTWIN** t_ms:4567269 stream:0xc9e0e898 wall:0 window_ms:600200 entities:4
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 7 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
```

---

@LAT103LON8267 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4355065 ±21 frame:7500
seq: 1081
follows: 0x00000010:1481 0x00000011:1427 0x00000012:1340 0x00000200:2118 0x00000300:4789
said: 1 | **ENTWIN** t_ms:4676707 stream:0xc9e0e898 wall:0 window_ms:60085 entities:3
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 6 | **CORE** entities:0
```

---

@LAT103LON8268 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1020004 ±21 frame:11000
seq: 1085
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4850
said: 1 | **ENTWIN** t_ms:1006133 stream:0xed9951d6 wall:0 window_ms:60316 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-88
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON8269 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1293567 ±21 frame:11000
seq: 1089
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4863
said: 1 | **ENTWIN** t_ms:1279551 stream:0xed9951d6 wall:0 window_ms:60461 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON8270 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2443254 ±22 frame:11000
seq: 1109
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4902
said: 1 | **ENTWIN** t_ms:2429588 stream:0xed9951d6 wall:0 window_ms:596501 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-88
said: 7 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 8 | **CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 9 | **COVERED** windows:1 entities:6 window_ms:553175 first_t_ms:1833086 last_t_ms:1833086 covered_by:@LAT103LON8269
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41 windows:1
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-87 windows:1
```

---

@LAT103LON8271 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60286 ±0 frame:15500
seq: 1113
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **ENTWIN** t_ms:41957 stream:0xf29d139a wall:0 window_ms:60286 entities:4
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
said: 6 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 7 | **CORE** entities:0
```

---

@LAT103LON8272 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1218652 ±0 frame:15500
seq: 1133
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **ENTWIN** t_ms:1200608 stream:0xf29d139a wall:0 window_ms:600902 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 7 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 8 | **CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 9 | **COVERED** windows:1 entities:6 window_ms:557464 first_t_ms:599706 last_t_ms:599706 covered_by:@LAT103LON8271
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-74 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-87 windows:1
```

---

@LAT103LON8273 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1818652 ±0 frame:15500
seq: 1144
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **ENTWIN** t_ms:1800609 stream:0xf29d139a wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-90
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 10 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b
```

---

@LAT103LON8274 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3018652 ±0 frame:15500
seq: 1166
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **ENTWIN** t_ms:3000609 stream:0xf29d139a wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,980d67f79619
said: 10 | **COVERED** windows:1 entities:6 window_ms:600000 first_t_ms:2400609 last_t_ms:2400609 covered_by:@LAT103LON8273
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91 windows:1
```

---

@LAT103LON16447 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3660000 ±0 frame:15500
seq: 1177
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **MOTIONWIN** t_ms:3641957 stream:0xf29d139a wall:0 window_ms:60000 n:595
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:25 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:17027 window_ms:1740000 moving_permille:0 dev_mean_mg:11 dev_max_mg:28 moving_ms:0 first_t_ms:1901957 last_t_ms:3581957 covered_by:@LAT103LON16446
```

---

@LAT103LON16448 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5460000 ±0 frame:15500
seq: 1208
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **MOTIONWIN** t_ms:5441957 stream:0xf29d139a wall:0 window_ms:60000 n:597
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:21 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16836 window_ms:1740000 moving_permille:0 dev_mean_mg:11 dev_max_mg:52 moving_ms:0 first_t_ms:3701957 last_t_ms:5381957 covered_by:@LAT103LON16447
```

---

@LAT103LON8275 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6018708 ±0 frame:15500
seq: 1219
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **ENTWIN** t_ms:6000664 stream:0xf29d139a wall:0 window_ms:600056 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 7 | **ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 9 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5203cfd1b904,2cfb0f0f0696
said: 11 | **COVERED** windows:4 entities:7 window_ms:2400000 first_t_ms:3600609 last_t_ms:5400609 covered_by:@LAT103LON8274
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-42 windows:4
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-66 windows:4
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-71 windows:4
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-74 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-75 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:2 rssi:-86 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:2 rssi:-90 windows:2
```

---

@LAT103LON16449 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 7260000 ±0 frame:15500
seq: 1240
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **MOTIONWIN** t_ms:7241957 stream:0xf29d139a wall:0 window_ms:60000 n:594
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:22 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16783 window_ms:1740000 moving_permille:0 dev_mean_mg:11 dev_max_mg:26 moving_ms:0 first_t_ms:5501957 last_t_ms:7181957 covered_by:@LAT103LON16448
```

---

@LAT103LON8276 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7818652 ±0 frame:15500
seq: 1251
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **ENTWIN** t_ms:7800609 stream:0xf29d139a wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5203cfd1b904,5ce28c488e0c,2cfb0f0f0696
said: 11 | **COVERED** windows:2 entities:8 window_ms:1199944 first_t_ms:6600609 last_t_ms:7200609 covered_by:@LAT103LON8275
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-42 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-67 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-74 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-75 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-76 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
```

---

@LAT103LON8277 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9018652 ±0 frame:15500
seq: 1272
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **ENTWIN** t_ms:9000609 stream:0xf29d139a wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-88
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,2cfb0f0f0696,980d67f79619,5ce28c488e0c
said: 12 | **COVERED** windows:1 entities:8 window_ms:600000 first_t_ms:8400609 last_t_ms:8400609 covered_by:@LAT103LON8276
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89 windows:1
```

---

@LAT103LON16450 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 9060000 ±0 frame:15500
seq: 1273
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **MOTIONWIN** t_ms:9041957 stream:0xf29d139a wall:0 window_ms:60000 n:596
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:24 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16919 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:25 moving_ms:0 first_t_ms:7301957 last_t_ms:8981957 covered_by:@LAT103LON16449
```

---

@LAT103LON16451 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 10860000 ±0 frame:15500
seq: 1304
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **MOTIONWIN** t_ms:10841957 stream:0xf29d139a wall:0 window_ms:60000 n:595
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:22 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16996 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:24 moving_ms:0 first_t_ms:9101957 last_t_ms:10781957 covered_by:@LAT103LON16450
```

---

@LAT103LON8278 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12618653 ±0 frame:15500
seq: 1335
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **ENTWIN** t_ms:12600610 stream:0xf29d139a wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 9 | **RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5203cfd1b904,5ce28c488e0c,980d67f79619,2cfb0f0f0696
said: 11 | **COVERED** windows:5 entities:9 window_ms:3000001 first_t_ms:9597189 last_t_ms:12000610 covered_by:@LAT103LON8277
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-42 windows:5
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-65 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-75 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-76 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-77 windows:5
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:4 rssi:-86 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:5 rssi:-87 windows:5
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:4 rssi:-88 windows:4
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89 windows:1
```

---

@LAT103LON16452 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 12660000 ±0 frame:15500
seq: 1336
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **MOTIONWIN** t_ms:12641957 stream:0xf29d139a wall:0 window_ms:60000 n:596
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:13 dev_max_mg:26 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16852 window_ms:1740000 moving_permille:0 dev_mean_mg:12 dev_max_mg:27 moving_ms:0 first_t_ms:10901957 last_t_ms:12581957 covered_by:@LAT103LON16451
```

---

@LAT103LON8279 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13218453 ±0 frame:15500
seq: 1347
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000200:2120 0x00000300:4904
said: 1 | **ENTWIN** t_ms:13200410 stream:0xf29d139a wall:0 window_ms:599800 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 7 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,5203cfd1b904,980d67f79619
```

---

@LAT103LON16453 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 215308 ±21 frame:12000
seq: 1357
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000200:2165 0x00000300:5103
said: 1 | **MOTIONWIN** t_ms:200320 stream:0x5d34e552 wall:0 window_ms:60000 n:469
said: 2 | **MOTION** state:still moving_permille:2 dev_mean_mg:19 dev_max_mg:69 moving_ms:500
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8280 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 215607 ±21 frame:12000
seq: 1359
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000200:2165 0x00000300:5103
said: 1 | **ENTWIN** t_ms:200320 stream:0x5d34e552 wall:0 window_ms:60299 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT105LON3799 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 75538 ±0 frame:9500
seq: 5035
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2136
said: 1 | **LINKWIN** t_ms:63418 stream:0xdfce8729 wall:0 window_ms:60038
said: 2 | **LINK** peer:0x00000200 proto:espnow n:46 rssi_min:-48 rssi_med:-39 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:50 rssi_min:-80 rssi_med:-55 rssi_max:-50
```

---

@LAT105LON3800 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 135538 ±0 frame:9500
seq: 5039
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2137
said: 1 | **LINKWIN** t_ms:123418 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:57 rssi_min:-43 rssi_med:-41 rssi_max:-39
said: 4 | 0x00000200 espnow met predicted:-39 observed:-41
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON3801 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 195546 ±0 frame:9500
seq: 5041
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2138
said: 1 | **LINKWIN** t_ms:183426 stream:0xdfce8729 wall:0 window_ms:60008
said: 2 | **LINK** peer:0x00000200 proto:espnow n:67 rssi_min:-46 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-79 rssi_med:-56 rssi_max:-54
said: 4 | 0x00000200 ble met predicted:-55 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-41 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON3802 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 60000 ±0 frame:9500
seq: 5043
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2139
said: 1 | **LINKWIN** t_ms:286568 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-80 rssi_med:-55 rssi_max:-45
said: 3 | **LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-49 rssi_med:-37 rssi_max:-32
```

---

@LAT105LON3803 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 120000 ±0 frame:9500
seq: 5047
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2140
said: 1 | **LINKWIN** t_ms:346568 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:32 rssi_min:-42 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 4 | 0x00000200 ble met predicted:-55 observed:-53
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON3804 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 180000 ±0 frame:9500
seq: 5049
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2142
said: 1 | **LINKWIN** t_ms:406568 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:61 rssi_min:-55 rssi_med:-41 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-56 rssi_max:-51
said: 4 | 0x00000200 espnow met predicted:-37 observed:-41
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-53 observed:-56
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON3805 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 240001 ±0 frame:9500
seq: 5051
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2143
said: 1 | **LINKWIN** t_ms:466569 stream:0xdfce8729 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000200 proto:espnow n:53 rssi_min:-48 rssi_med:-38 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-62 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 espnow met predicted:-41 observed:-38
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-56 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON3806 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 1123505 ±22 frame:8500
seq: 5053
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2146
said: 1 | **LINKWIN** t_ms:1112020 stream:0xb8b08067 wall:0 window_ms:60074
said: 2 | **LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-53 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:ble n:44 rssi_min:-69 rssi_med:-64 rssi_max:-62
```

---

@LAT105LON3807 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 218456 ±21 frame:12000
seq: 1487
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1359 0x00000200:2165 0x00000300:5103
said: 1 | **LINKWIN** t_ms:203503 stream:0x5d34e552 wall:0 window_ms:60016
said: 2 | **LINK** peer:0x00000300 proto:espnow n:136 rssi_min:-21 rssi_med:-18 rssi_max:-16
said: 3 | **LINK** peer:0x00000200 proto:espnow n:133 rssi_min:-38 rssi_med:-32 rssi_max:-30
said: 4 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-35 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-80 rssi_med:-45 rssi_max:-43
said: 6 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-30 rssi_med:-25 rssi_max:-22
said: 7 | **LINK** peer:0x00000011 proto:ble n:48 rssi_min:-79 rssi_med:-38 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:espnow n:43 rssi_min:-39 rssi_med:-26 rssi_max:-23
said: 9 | **LINK** peer:0x00000012 proto:ble n:48 rssi_min:-77 rssi_med:-41 rssi_max:-35
```

---

@LAT103LON8281 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1372953 ±0 frame:12000
seq: 1379
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2165 0x00000300:5103
said: 1 | **ENTWIN** t_ms:1357969 stream:0x5d34e552 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,64677217947d,e6b32d2cea8b
said: 11 | **COVERED** windows:1 entities:6 window_ms:557351 first_t_ms:757969 last_t_ms:757969 covered_by:@LAT103LON8280
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84 windows:1
```

---

@LAT103LON8282 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1972953 ±0 frame:12000
seq: 1390
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2165 0x00000300:5103
said: 1 | **ENTWIN** t_ms:1957970 stream:0x5d34e552 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,e6b32d2cea8b
```

---

@LAT103LON16454 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 2015303 ±0 frame:12000
seq: 1391
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2165 0x00000300:5103
said: 1 | **MOTIONWIN** t_ms:2000320 stream:0x5d34e552 wall:0 window_ms:60000 n:594
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:30 dev_max_mg:41 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:17055 window_ms:1740000 moving_permille:0 dev_mean_mg:26 dev_max_mg:44 moving_ms:0 first_t_ms:260320 last_t_ms:1940320 covered_by:@LAT103LON16453
```

---

@LAT103LON8283 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3169357 ±0 frame:12000
seq: 1412
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2165 0x00000300:5103
said: 1 | **ENTWIN** t_ms:3154373 stream:0x5d34e552 wall:0 window_ms:596405 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,aef9ff2626ac,e6b32d2cea8b
said: 10 | **COVERED** windows:1 entities:8 window_ms:599999 first_t_ms:2557969 last_t_ms:2557969 covered_by:@LAT103LON8282
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-90 windows:1
```

---

@LAT103LON16455 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3815303 ±0 frame:12000
seq: 1423
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2165 0x00000300:5103
said: 1 | **MOTIONWIN** t_ms:3800320 stream:0x5d34e552 wall:0 window_ms:60000 n:585
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:3 dev_max_mg:18 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16852 window_ms:1740000 moving_permille:0 dev_mean_mg:28 dev_max_mg:161 moving_ms:900 first_t_ms:2060320 last_t_ms:3740320 covered_by:@LAT103LON16454
```

---

@LAT103LON8284 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4972967 ±0 frame:12000
seq: 1444
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2165 0x00000300:5103
said: 1 | **ENTWIN** t_ms:4957982 stream:0x5d34e552 wall:0 window_ms:600202 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-87
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,aef9ff2626ac
said: 11 | **COVERED** windows:2 entities:9 window_ms:1203408 first_t_ms:3757985 last_t_ms:4357782 covered_by:@LAT103LON8283
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-40 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-78 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-79 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
```

---

@LAT103LON16456 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5615303 ±0 frame:12000
seq: 1455
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2165 0x00000300:5103
said: 1 | **MOTIONWIN** t_ms:5600320 stream:0x5d34e552 wall:0 window_ms:60000 n:595
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:3 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16940 window_ms:1740000 moving_permille:0 dev_mean_mg:3 dev_max_mg:141 moving_ms:400 first_t_ms:3860320 last_t_ms:5540320 covered_by:@LAT103LON16455
```

---

@LAT106LON118 | created:0 | updated:0

**BAR** frame:12000 bar:9 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:5561 heap:225812 fetched:29 unanswered:33 broken:0 resumed:0 empty:1 served:0 wants:8 early:48 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT106LON119 | created:0 | updated:0

**BAR** frame:12000 bar:10 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:6160 heap:225820 fetched:29 unanswered:35 broken:0 resumed:0 empty:1 served:0 wants:8 early:48 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT105LON3808 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 182310 ±21 frame:9500
seq: 2138
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5040
said: 1 | **LINKWIN** t_ms:170196 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-56 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:141 rssi_min:-40 rssi_med:-37 rssi_max:-34
```

---

@LAT105LON3809 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 242306 ±22 frame:9500
seq: 2139
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5042
said: 1 | **LINKWIN** t_ms:230196 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-39 rssi_med:-38 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:49 rssi_min:-59 rssi_med:-53 rssi_max:-47
```

---

@LAT105LON3810 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 302306 ±25 frame:9500
seq: 2140
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5046
said: 1 | **LINKWIN** t_ms:290196 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-54 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:61 rssi_min:-45 rssi_med:-35 rssi_max:-29
```

---

@LAT105LON3811 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 133458 ±21 frame:9500
seq: 2141
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5048
said: 1 | **LINKWIN** t_ms:358618 stream:0xdfce8729 wall:0 window_ms:61409
said: 2 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-37 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-50 rssi_max:-47
```

---

@LAT105LON3812 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 193459 ±21 frame:9500
seq: 2143
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5050
said: 1 | **LINKWIN** t_ms:420027 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-69 rssi_med:-52 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:69 rssi_min:-53 rssi_med:-37 rssi_max:-34
```

---

@LAT105LON3813 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 253460 ±21 frame:9500
seq: 2144
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:480027 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:67 rssi_min:-52 rssi_med:-38 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-79 rssi_med:-54 rssi_max:-46
```

---

@LAT105LON3814 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1073202 ±0 frame:8500
seq: 2146
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:1061712 stream:0xb8b08067 wall:0 window_ms:1073202
said: 2 | **LINK** peer:0x00000300 proto:espnow n:3 rssi_min:-47 rssi_med:-47 rssi_max:-47
```

---

@LAT103LON16457 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 70547 ±21 frame:9500
seq: 1468
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2167 0x00000300:5103
said: 1 | **MOTIONWIN** t_ms:58428 stream:0x69cc95ce wall:0 window_ms:60000 n:494
said: 2 | **MOTION** state:still moving_permille:2 dev_mean_mg:3 dev_max_mg:66 moving_ms:500
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8285 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 70783 ±21 frame:9500
seq: 1470
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2167 0x00000300:5103
said: 1 | **ENTWIN** t_ms:58428 stream:0x69cc95ce wall:0 window_ms:60217 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT105LON3815 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1133193 ±21 frame:8500
seq: 2147
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:1121715 stream:0xb8b08067 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-75 rssi_med:-61 rssi_max:-58
said: 3 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-91 rssi_med:-49 rssi_max:-47
```

---

@LAT105LON3816 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 68995 ±21 frame:7500
seq: 2148
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5060
said: 1 | **LINKWIN** t_ms:57427 stream:0x1f824110 wall:0 window_ms:61386
said: 2 | **LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-40 rssi_med:-37 rssi_max:-32
said: 3 | **LINK** peer:0x00000300 proto:ble n:50 rssi_min:-82 rssi_med:-54 rssi_max:-48
```

---

@LAT105LON3817 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 139634 ±21 frame:7500
seq: 2150
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5067
said: 1 | **LINKWIN** t_ms:129626 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-53 rssi_med:-37 rssi_max:-29
said: 3 | **LINK** peer:0x00000300 proto:ble n:46 rssi_min:-75 rssi_med:-53 rssi_max:-44
```

---

@LAT105LON3818 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 199636 ±21 frame:7500
seq: 2152
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5069
said: 1 | **LINKWIN** t_ms:189626 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:73 rssi_min:-47 rssi_med:-35 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-67 rssi_med:-45 rssi_max:-37
```

---

@LAT105LON3819 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 259638 ±21 frame:7500
seq: 2153
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5071
said: 1 | **LINKWIN** t_ms:249627 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:83 rssi_min:-44 rssi_med:-27 rssi_max:-25
```

---

@LAT105LON3820 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 95985 ±21 frame:7500
seq: 2154
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5075
said: 1 | **LINKWIN** t_ms:84171 stream:0xb4b25252 wall:0 window_ms:61315
said: 2 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-29 rssi_med:-24 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT105LON3821 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 155984 ±21 frame:7500
seq: 2156
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5077
said: 1 | **LINKWIN** t_ms:145486 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:64 rssi_min:-28 rssi_med:-25 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-70 rssi_med:-40 rssi_max:-36
```

---

@LAT105LON3822 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 215985 ±21 frame:7500
seq: 2157
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5079
said: 1 | **LINKWIN** t_ms:205486 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:64 rssi_min:-26 rssi_med:-25 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-47 rssi_med:-41 rssi_max:-37
```

---

@LAT105LON3823 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 141238 ±21 frame:10500
seq: 2158
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5086
said: 1 | **LINKWIN** t_ms:127872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-29 rssi_med:-27 rssi_max:-25
said: 3 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-47 rssi_med:-43 rssi_max:-39
```

---

@LAT105LON3824 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 201238 ±21 frame:10500
seq: 2160
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5088
said: 1 | **LINKWIN** t_ms:187872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:65 rssi_min:-30 rssi_med:-28 rssi_max:-24
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-50 rssi_med:-43 rssi_max:-40
```

---

@LAT105LON3825 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 261239 ±21 frame:10500
seq: 2161
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5090
said: 1 | **LINKWIN** t_ms:247872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:79 rssi_min:-46 rssi_med:-32 rssi_max:-26
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-66 rssi_med:-47 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:ble n:43 rssi_min:-51 rssi_med:-47 rssi_max:-43
said: 5 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-33 rssi_med:-31 rssi_max:-27
said: 6 | **LINK** peer:0x00000011 proto:ble n:36 rssi_min:-51 rssi_med:-49 rssi_max:-45
said: 7 | **LINK** peer:0x00000011 proto:espnow n:72 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:27 rssi_min:-56 rssi_med:-50 rssi_max:-46
said: 9 | **LINK** peer:0x00000012 proto:espnow n:37 rssi_min:-38 rssi_med:-34 rssi_max:-33
```

---

@LAT105LON3826 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 321240 ±23 frame:10500
seq: 2162
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5092
said: 1 | **LINKWIN** t_ms:307872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:61 rssi_min:-44 rssi_med:-31 rssi_max:-28
said: 3 | **LINK** peer:0x00000011 proto:espnow n:48 rssi_min:-35 rssi_med:-33 rssi_max:-28
said: 4 | **LINK** peer:0x00000010 proto:espnow n:78 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 5 | **LINK** peer:0x00000012 proto:espnow n:40 rssi_min:-36 rssi_med:-35 rssi_max:-33
said: 6 | **LINK** peer:0x00000011 proto:ble n:15 rssi_min:-63 rssi_med:-50 rssi_max:-46
said: 7 | **LINK** peer:0x00000012 proto:ble n:22 rssi_min:-56 rssi_med:-52 rssi_max:-47
said: 8 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-67 rssi_med:-47 rssi_max:-44
said: 9 | **LINK** peer:0x00000010 proto:ble n:26 rssi_min:-54 rssi_med:-47 rssi_max:-44
```

---

@LAT105LON3827 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 107656 ±22 frame:12000
seq: 2163
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000300:5097
said: 1 | **LINKWIN** t_ms:90717 stream:0x5d34e552 wall:0 window_ms:61963
said: 2 | **LINK** peer:0x00000300 proto:espnow n:65 rssi_min:-27 rssi_med:-23 rssi_max:-22
said: 3 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-45 rssi_med:-41 rssi_max:-35
```

---

@LAT105LON3828 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 167627 ±21 frame:12000
seq: 2165
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000300:5101
said: 1 | **LINKWIN** t_ms:152680 stream:0x5d34e552 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-38 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:79 rssi_min:-31 rssi_med:-23 rssi_max:-22
said: 4 | **LINK** peer:0x00000010 proto:ble n:3 rssi_min:-54 rssi_med:-52 rssi_max:-48
```

---

@LAT105LON3829 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 60001 ±0 frame:9500
seq: 2166
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1467 0x00000300:5103
said: 1 | **LINKWIN** t_ms:47860 stream:0x69cc95ce wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-40 rssi_med:-37 rssi_max:-33
```

---

@LAT105LON3830 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 120001 ±0 frame:9500
seq: 2168
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1470 0x00000300:5103
said: 1 | **LINKWIN** t_ms:107861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-42 rssi_med:-39 rssi_max:-33
```

---

@LAT105LON3831 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 180001 ±0 frame:9500
seq: 2169
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1471 0x00000300:5103
said: 1 | **LINKWIN** t_ms:167861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-41 rssi_med:-39 rssi_max:-36
```

---

@LAT105LON3832 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 240001 ±0 frame:9500
seq: 2170
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1472 0x00000300:5103
said: 1 | **LINKWIN** t_ms:227861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-40 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON3833 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 300030 ±0 frame:9500
seq: 2171
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1473 0x00000300:5103
said: 1 | **LINKWIN** t_ms:287890 stream:0x69cc95ce wall:0 window_ms:60029
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON3834 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 360030 ±0 frame:9500
seq: 2172
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1474 0x00000300:5103
said: 1 | **LINKWIN** t_ms:347890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-40 rssi_med:-39 rssi_max:-39
```

---

@LAT105LON3835 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 420030 ±0 frame:9500
seq: 2173
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1475 0x00000300:5103
said: 1 | **LINKWIN** t_ms:407890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON3836 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 480030 ±0 frame:9500
seq: 2174
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1476 0x00000300:5103
said: 1 | **LINKWIN** t_ms:467890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-40 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON3837 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 540030 ±0 frame:9500
seq: 2175
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1477 0x00000300:5103
said: 1 | **LINKWIN** t_ms:527890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON3838 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 600030 ±0 frame:9500
seq: 2176
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1478 0x00000300:5103
said: 1 | **LINKWIN** t_ms:587890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-39 rssi_med:-39 rssi_max:-39
```

---

@LAT105LON3839 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 660030 ±0 frame:9500
seq: 2177
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1479 0x00000300:5103
said: 1 | **LINKWIN** t_ms:647890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-43 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON3840 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 720030 ±0 frame:9500
seq: 2178
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1480 0x00000300:5103
said: 1 | **LINKWIN** t_ms:707890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-41 rssi_med:-39 rssi_max:-37
```

---

@LAT105LON3841 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 60040 ±0 frame:7500
seq: 5057
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2147
said: 1 | **LINKWIN** t_ms:49855 stream:0x1f824110 wall:0 window_ms:60040
said: 2 | **LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-43 rssi_med:-42 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:48 rssi_min:-80 rssi_med:-56 rssi_max:-51
```

---

@LAT105LON3842 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 85818 ±0 frame:7500
seq: 5064
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2147
said: 1 | **LINKWIN** t_ms:75809 stream:0xad373985 wall:0 window_ms:85818
said: 2 | **LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-46 rssi_med:-46 rssi_max:-46
```

---

@LAT105LON3843 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 145818 ±0 frame:7500
seq: 5068
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2151
said: 1 | **LINKWIN** t_ms:135809 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:56 rssi_min:-51 rssi_med:-44 rssi_max:-33
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-67 rssi_med:-56 rssi_max:-47
said: 4 | 0x00000200 espnow met predicted:-46 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON3844 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 205818 ±0 frame:7500
seq: 5070
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2151
said: 1 | **LINKWIN** t_ms:195809 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:70 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-51 rssi_med:-34 rssi_max:-27
said: 4 | 0x00000200 espnow violated predicted:-44 observed:-34
percept: 4 | 0x00000200 | link_stable | espnow | - | -
said: 5 | 0x00000200 ble met predicted:-56 observed:-50
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON3845 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 60000 ±0 frame:7500
seq: 5072
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2153
said: 1 | **LINKWIN** t_ms:49501 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:25 rssi_min:-80 rssi_med:-44 rssi_max:-40
said: 3 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-34 rssi_med:-29 rssi_max:-28
```

---

@LAT105LON3846 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 120000 ±0 frame:7500
seq: 5076
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2155
said: 1 | **LINKWIN** t_ms:109501 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:39 rssi_min:-30 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-44 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-29 observed:-28
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON3847 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 180039 ±0 frame:7500
seq: 5078
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2156
said: 1 | **LINKWIN** t_ms:169540 stream:0xb4b25252 wall:0 window_ms:60039
said: 2 | **LINK** peer:0x00000200 proto:espnow n:59 rssi_min:-31 rssi_med:-29 rssi_max:-27
said: 3 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-45 rssi_max:-41
said: 4 | 0x00000200 espnow met predicted:-28 observed:-29
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-44 observed:-45
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON3848 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 86407 ±0 frame:10500
seq: 5083
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2156
said: 1 | **LINKWIN** t_ms:73043 stream:0x3bead35c wall:0 window_ms:86407
said: 2 | **LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-32 rssi_med:-32 rssi_max:-32
```

---

@LAT105LON3849 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 146407 ±0 frame:10500
seq: 5087
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2157
said: 1 | **LINKWIN** t_ms:133043 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-79 rssi_med:-51 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-32 observed:-32
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON3850 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 207718 ±0 frame:10500
seq: 5089
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2160
said: 1 | **LINKWIN** t_ms:194354 stream:0x3bead35c wall:0 window_ms:61311
said: 2 | **LINK** peer:0x00000200 proto:espnow n:65 rssi_min:-38 rssi_med:-33 rssi_max:-30
said: 3 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-79 rssi_med:-49 rssi_max:-44
said: 4 | 0x00000200 espnow met predicted:-32 observed:-33
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-51 observed:-49
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON3851 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 267790 ±0 frame:10500
seq: 5091
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2161
said: 1 | **LINKWIN** t_ms:254426 stream:0x3bead35c wall:0 window_ms:60072
said: 2 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-56 rssi_med:-36 rssi_max:-31
said: 3 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-52 rssi_max:-44
said: 4 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-52 rssi_med:-32 rssi_max:-29
said: 5 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 6 | **LINK** peer:0x00000011 proto:espnow n:87 rssi_min:-36 rssi_med:-29 rssi_max:-26
said: 7 | **LINK** peer:0x00000011 proto:ble n:38 rssi_min:-55 rssi_med:-45 rssi_max:-42
said: 8 | **LINK** peer:0x00000012 proto:espnow n:45 rssi_min:-21 rssi_med:-19 rssi_max:-18
said: 9 | **LINK** peer:0x00000012 proto:ble n:26 rssi_min:-37 rssi_med:-35 rssi_max:-33
said: 10 | 0x00000200 espnow met predicted:-33 observed:-36
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-49 observed:-52
percept: 11 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON3852 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 327830 ±0 frame:10500
seq: 5093
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2161
said: 1 | **LINKWIN** t_ms:314466 stream:0x3bead35c wall:0 window_ms:60040
said: 2 | **LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-21 rssi_med:-20 rssi_max:-18
said: 3 | **LINK** peer:0x00000010 proto:espnow n:53 rssi_min:-47 rssi_med:-33 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:ble n:15 rssi_min:-81 rssi_med:-45 rssi_max:-41
said: 5 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-51 rssi_max:-46
said: 6 | **LINK** peer:0x00000010 proto:ble n:15 rssi_min:-54 rssi_med:-50 rssi_max:-46
said: 7 | **LINK** peer:0x00000200 proto:espnow n:50 rssi_min:-48 rssi_med:-35 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:13 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 9 | **LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-33 rssi_med:-29 rssi_max:-28
said: 10 | 0x00000200 espnow met predicted:-36 observed:-35
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-52 observed:-51
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000010 espnow met predicted:-32 observed:-33
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-49 observed:-50
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-45 observed:-45
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow met predicted:-19 observed:-20
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-35 observed:-35
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT105LON3853 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 60000 ±0 frame:12000
seq: 5094
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2162
said: 1 | **LINKWIN** t_ms:45024 stream:0x5d34e552 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:10 rssi_min:-30 rssi_med:-30 rssi_max:-29
said: 3 | **LINK** peer:0x00000200 proto:ble n:11 rssi_min:-54 rssi_med:-45 rssi_max:-43
```

---

@LAT105LON3854 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 120074 ±0 frame:12000
seq: 5098
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2164
said: 1 | **LINKWIN** t_ms:105098 stream:0x5d34e552 wall:0 window_ms:60074
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-80 rssi_med:-45 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:66 rssi_min:-33 rssi_med:-29 rssi_max:-27
```

---

@LAT105LON3855 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 180074 ±0 frame:12000
seq: 5102
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2165
said: 1 | **LINKWIN** t_ms:165098 stream:0x5d34e552 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:79 rssi_min:-34 rssi_med:-29 rssi_max:-26
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-44 rssi_max:-41
said: 4 | **LINK** peer:0x00000010 proto:espnow n:9 rssi_min:-28 rssi_med:-27 rssi_max:-25
said: 5 | **LINK** peer:0x00000010 proto:ble n:16 rssi_min:-44 rssi_med:-43 rssi_max:-41
said: 6 | **LINK** peer:0x00000100 proto:espnow n:17 rssi_min:-30 rssi_med:-25 rssi_max:-24
said: 7 | **LINK** peer:0x00000011 proto:espnow n:3 rssi_min:-24 rssi_med:-24 rssi_max:-24
said: 8 | **LINK** peer:0x00000011 proto:ble n:9 rssi_min:-44 rssi_med:-39 rssi_max:-38
said: 9 | **LINK** peer:0x00000012 proto:espnow n:5 rssi_min:-18 rssi_med:-16 rssi_max:-16
said: 10 | 0x00000200 ble met predicted:-45 observed:-44
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON3856 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 780080 ±21 frame:9500
seq: 2179
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1481 0x00000300:5107
said: 1 | **LINKWIN** t_ms:767945 stream:0x69cc95ce wall:0 window_ms:60055
said: 2 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-43 rssi_med:-39 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:130 rssi_min:-84 rssi_med:-46 rssi_max:-28
said: 4 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-62 rssi_max:-44
```

---

@LAT105LON3857 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 778538 ±0 frame:9500
seq: 5104
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1481 0x00000200:2178
said: 1 | **LINKWIN** t_ms:766400 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-65 rssi_med:-51 rssi_max:-25
said: 3 | **LINK** peer:0x00000200 proto:espnow n:85 rssi_min:-78 rssi_med:-54 rssi_max:-31
said: 4 | **LINK** peer:0x00000200 proto:ble n:47 rssi_min:-90 rssi_med:-64 rssi_max:-46
```

---

@LAT103LON16458 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:8000
seq: 1483
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **MOTIONWIN** t_ms:49105 stream:0xb0b57d3a wall:0 window_ms:60000 n:533
said: 2 | **MOTION** state:still moving_permille:1 dev_mean_mg:3 dev_max_mg:71 moving_ms:500
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8286 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60104 ±0 frame:8000
seq: 1485
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ENTWIN** t_ms:49105 stream:0xb0b57d3a wall:0 window_ms:60104 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON16459 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:12500
seq: 1494
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **MOTIONWIN** t_ms:44898 stream:0x769535ae wall:0 window_ms:60000 n:490
said: 2 | **MOTION** state:still moving_permille:2 dev_mean_mg:3 dev_max_mg:73 moving_ms:500
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8287 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60074 ±0 frame:12500
seq: 1496
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ENTWIN** t_ms:44898 stream:0x769535ae wall:0 window_ms:60074 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-87
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT106LON120 | created:0 | updated:0

**BAR** frame:12500 bar:1 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:916 heap:225804 fetched:0 unanswered:24 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON8288 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1215711 ±0 frame:12500
seq: 1516
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ENTWIN** t_ms:1200609 stream:0x769535ae wall:0 window_ms:600921 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:4 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace
said: 11 | **COVERED** windows:1 entities:6 window_ms:554716 first_t_ms:599688 last_t_ms:599688 covered_by:@LAT103LON8287
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
```

---

@LAT106LON121 | created:0 | updated:0

**BAR** frame:12500 bar:2 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:1516 heap:225776 fetched:0 unanswered:28 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON8289 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1815713 ±0 frame:12500
seq: 1527
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ENTWIN** t_ms:1800610 stream:0x769535ae wall:0 window_ms:600002 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 9 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,0283cce0e689
```

---

@LAT103LON16460 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 1860000 ±0 frame:12500
seq: 1528
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **MOTIONWIN** t_ms:1844898 stream:0x769535ae wall:0 window_ms:60000 n:597
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:19 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:17165 window_ms:1740000 moving_permille:0 dev_mean_mg:6 dev_max_mg:60 moving_ms:100 first_t_ms:104898 last_t_ms:1784898 covered_by:@LAT103LON16459
```

---

@LAT106LON122 | created:0 | updated:0

**BAR** frame:12500 bar:3 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:2115 heap:225804 fetched:0 unanswered:32 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON16461 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:13500
seq: 1539
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **MOTIONWIN** t_ms:43952 stream:0x5b22aee5 wall:0 window_ms:60000 n:482
said: 2 | **MOTION** state:still moving_permille:6 dev_mean_mg:3 dev_max_mg:82 moving_ms:700
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8290 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60125 ±0 frame:13500
seq: 1541
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ENTWIN** t_ms:43952 stream:0x5b22aee5 wall:0 window_ms:60125 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT106LON123 | created:0 | updated:0

**BAR** frame:13500 bar:1 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:916 heap:225804 fetched:0 unanswered:24 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON8291 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1216458 ±0 frame:13500
seq: 1561
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ENTWIN** t_ms:1200410 stream:0x5b22aee5 wall:0 window_ms:600921 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-77
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-83
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e89f6dad2951,aef9ff2626ac
said: 11 | **COVERED** windows:1 entities:7 window_ms:555412 first_t_ms:599489 last_t_ms:599489 covered_by:@LAT103LON8290
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-78 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90 windows:1
```

---

@LAT106LON124 | created:0 | updated:0

**BAR** frame:13500 bar:2 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:1523 heap:225804 fetched:0 unanswered:28 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON16462 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 1860000 ±0 frame:13500
seq: 1572
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **MOTIONWIN** t_ms:1843952 stream:0x5b22aee5 wall:0 window_ms:60000 n:597
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:19 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:17036 window_ms:1740000 moving_permille:0 dev_mean_mg:8 dev_max_mg:147 moving_ms:500 first_t_ms:103952 last_t_ms:1783952 covered_by:@LAT103LON16461
```

---

@LAT106LON125 | created:0 | updated:0

**BAR** frame:13500 bar:3 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:2120 heap:225804 fetched:0 unanswered:32 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT106LON126 | created:0 | updated:0

**BAR** frame:13500 bar:4 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:2719 heap:225804 fetched:0 unanswered:32 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT106LON127 | created:0 | updated:0

**BAR** frame:13500 bar:5 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:3321 heap:225804 fetched:0 unanswered:36 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON8292 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3616459 ±0 frame:13500
seq: 1603
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ENTWIN** t_ms:3600411 stream:0x5b22aee5 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-85
said: 9 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e89f6dad2951,bc102f237ace,64677217947d,aef9ff2626ac
said: 11 | **COVERED** windows:3 entities:9 window_ms:1800002 first_t_ms:1800410 last_t_ms:3000411 covered_by:@LAT103LON8291
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-36 windows:3
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-65 windows:3
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:3 rssi:-75 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-73 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-72 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:3 rssi:-83 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-87 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-86 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90 windows:1
```

---

@LAT103LON16463 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3660000 ±0 frame:13500
seq: 1604
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **MOTIONWIN** t_ms:3643952 stream:0x5b22aee5 wall:0 window_ms:60000 n:596
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:22 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16766 window_ms:1740000 moving_permille:0 dev_mean_mg:11 dev_max_mg:143 moving_ms:300 first_t_ms:1903952 last_t_ms:3583952 covered_by:@LAT103LON16462
```

---

@LAT106LON128 | created:0 | updated:0

**BAR** frame:13500 bar:6 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:3921 heap:225804 fetched:0 unanswered:40 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON8293 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4216459 ±0 frame:13500
seq: 1615
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ENTWIN** t_ms:4200411 stream:0x5b22aee5 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e89f6dad2951,bc102f237ace,64677217947d,c2e94427adcf,e6b32d2cea8b,aef9ff2626ac
```

---

@LAT106LON129 | created:0 | updated:0

**BAR** frame:13500 bar:7 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:4520 heap:225804 fetched:0 unanswered:40 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON26079 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4741444 ±0 frame:13500
seq: 1624
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:4725396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7416 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:47 peak:68 transients:0 self_blocks:0
```

---

@LAT103LON26080 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4801444 ±0 frame:13500
seq: 1625
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:4785396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7436 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:27 peak:37 transients:0 self_blocks:0
```

---

@LAT103LON8294 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4816458 ±0 frame:13500
seq: 1626
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ENTWIN** t_ms:4800410 stream:0x5b22aee5 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,e89f6dad2951,bc102f237ace,64677217947d,c2e94427adcf,e6b32d2cea8b,5203cfd1b904
```

---

@LAT103LON26081 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4861444 ±0 frame:13500
seq: 1627
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:4845396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7379 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:25 peak:41 transients:0 self_blocks:0
```

---

@LAT103LON26082 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4921444 ±0 frame:13500
seq: 1628
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:4905396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7429 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:35 peak:47 transients:0 self_blocks:0
```

---

@LAT103LON26083 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4981444 ±0 frame:13500
seq: 1629
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:4965396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7425 rate:16000
said: 2 | **ACOUSTIC** rms_mean:5 rms_max:26 peak:51 transients:0 self_blocks:0
```

---

@LAT103LON26084 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5041444 ±0 frame:13500
seq: 1630
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5025396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7435 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:32 peak:60 transients:0 self_blocks:0
```

---

@LAT103LON26085 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5101444 ±0 frame:13500
seq: 1631
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5085396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7418 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:31 peak:49 transients:0 self_blocks:0
```

---

@LAT106LON130 | created:0 | updated:0

**BAR** frame:13500 bar:8 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:5118 heap:225804 fetched:0 unanswered:44 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON26086 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5161444 ±0 frame:13500
seq: 1632
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5145396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:5805 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:49 peak:60 transients:0 self_blocks:0
```

---

@LAT103LON26087 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5221444 ±0 frame:13500
seq: 1633
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5205396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7418 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:23 peak:37 transients:0 self_blocks:0
```

---

@LAT103LON26088 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5281444 ±0 frame:13500
seq: 1634
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5265396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7441 rate:16000
said: 2 | **ACOUSTIC** rms_mean:7 rms_max:66 peak:103 transients:0 self_blocks:0
```

---

@LAT103LON26089 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5341444 ±0 frame:13500
seq: 1635
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5325396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7414 rate:16000
said: 2 | **ACOUSTIC** rms_mean:7 rms_max:212 peak:550 transients:0 self_blocks:0
```

---

@LAT103LON26090 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5401444 ±0 frame:13500
seq: 1636
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5385396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7427 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:47 peak:120 transients:0 self_blocks:0
```

---

@LAT103LON16464 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5460029 ±0 frame:13500
seq: 1637
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **MOTIONWIN** t_ms:5443981 stream:0x5b22aee5 wall:0 window_ms:60000 n:595
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:24 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16825 window_ms:1740029 moving_permille:0 dev_mean_mg:11 dev_max_mg:26 moving_ms:0 first_t_ms:3703952 last_t_ms:5383981 covered_by:@LAT103LON16463
```

---

@LAT103LON26091 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5461444 ±0 frame:13500
seq: 1638
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5445396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7413 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:39 peak:59 transients:0 self_blocks:0
```

---

@LAT103LON26092 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5521444 ±0 frame:13500
seq: 1639
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5505396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7404 rate:16000
said: 2 | **ACOUSTIC** rms_mean:5 rms_max:22 peak:48 transients:0 self_blocks:0
```

---

@LAT103LON26093 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5581444 ±0 frame:13500
seq: 1640
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5565396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7430 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:38 peak:47 transients:0 self_blocks:0
```

---

@LAT103LON26094 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5641444 ±0 frame:13500
seq: 1641
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5625396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7418 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:45 peak:74 transients:0 self_blocks:0
```

---

@LAT104LON180 | created:0 | updated:0

**carried through @LAT103LON8254**

```ttdb-carried
through: 8254
through: 16446
through: 26078
```

---

@LAT103LON26095 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5701444 ±0 frame:13500
seq: 1642
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5685396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7380 rate:16000
said: 2 | **ACOUSTIC** rms_mean:5 rms_max:28 peak:36 transients:0 self_blocks:0
```
@LAT106LON131 | created:0 | updated:0

**BAR** frame:13500 bar:9 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:5720 heap:225804 fetched:0 unanswered:44 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON26096 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5761444 ±0 frame:13500
seq: 1643
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5745396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:5471 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:46 peak:137 transients:0 self_blocks:0
```

---

@LAT103LON26097 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5821444 ±0 frame:13500
seq: 1644
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000200:2179 0x00000300:5107
said: 1 | **ACOUSTICWIN** t_ms:5805396 stream:0x5b22aee5 wall:0 window_ms:60000 blocks:7413 rate:16000
said: 2 | **ACOUSTIC** rms_mean:10 rms_max:460 peak:1012 transients:0 self_blocks:0
```
@LAT106LON132 | created:0 | updated:0

**BAR** frame:45500 bar:11 own:0 held:0 terms:0 digest:0x00000000 settled_ms:603296
**DELIVER** up_s:14 heap:222404 fetched:0 unanswered:0 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:1
**SPLIT** agent:0x00000300 grammar:0x42e3bb8a
@LAT106LON133 | created:0 | updated:0

**BAR** frame:45500 bar:10 own:0 held:0 terms:0 digest:0x00000000 settled_ms:1203296
**DELIVER** up_s:19 heap:222404 fetched:0 unanswered:0 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:1
**SPLIT** agent:0x00000300 grammar:0x42e3bb8a
