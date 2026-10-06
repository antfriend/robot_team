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

@LAT103LON8219 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8128625 ±21 frame:7000
seq: 252
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000200:585 0x00000300:1797
said: 1 | **ENTWIN** t_ms:8172018 stream:0x3c4214c9 wall:0 window_ms:600400 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 9 | **CORE** entities:4 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d
```

---

@LAT103LON8220 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8728632 ±21 frame:7000
seq: 264
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000200:596 0x00000300:1818
said: 1 | **ENTWIN** t_ms:8772018 stream:0x3c4214c9 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b
```

---

@LAT103LON8221 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10605468 ±21 frame:7000
seq: 296
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000200:629 0x00000300:1884
said: 1 | **ENTWIN** t_ms:10648608 stream:0x3c4214c9 wall:0 window_ms:60286 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON8222 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11002632 ±21 frame:7000
seq: 304
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000200:635 0x00000300:1897
said: 1 | **ENTWIN** t_ms:11045803 stream:0x3c4214c9 wall:0 window_ms:60234 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8223 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12134768 ±21 frame:7000
seq: 324
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000200:652 0x00000300:1931
said: 1 | **ENTWIN** t_ms:12202408 stream:0x3c4214c9 wall:0 window_ms:602365 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 9 | **CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,0283cce0e689
said: 10 | **COVERED** windows:1 entities:4 window_ms:554008 first_t_ms:11600044 last_t_ms:11600044 covered_by:@LAT103LON8222
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88 windows:1
```

---

@LAT103LON8224 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12732617 ±21 frame:7000
seq: 335
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000200:663 0x00000300:1951
said: 1 | **ENTWIN** t_ms:12800247 stream:0x3c4214c9 wall:0 window_ms:597838 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 7 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 8 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,0283cce0e689
```

---

@LAT103LON8225 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13335885 ±21 frame:7000
seq: 347
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000200:673 0x00000300:1972
said: 1 | **ENTWIN** t_ms:13403509 stream:0x3c4214c9 wall:0 window_ms:603262 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON8226 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 14536446 ±21 frame:7000
seq: 368
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000200:694 0x00000300:2015
said: 1 | **ENTWIN** t_ms:14604056 stream:0x3c4214c9 wall:0 window_ms:603814 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b
said: 9 | **COVERED** windows:1 entities:4 window_ms:596733 first_t_ms:14000242 last_t_ms:14000242 covered_by:@LAT103LON8225
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80 windows:1
```

---

@LAT103LON8227 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 15307194 ±21 frame:7000
seq: 383
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000200:708 0x00000300:2042
said: 1 | **ENTWIN** t_ms:15377850 stream:0x3c4214c9 wall:0 window_ms:60549 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON8228 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21959020 ±21 frame:7000
seq: 393
follows: 0x00000010:192 0x00000011:122 0x00000012:39 0x00000200:825 0x00000300:2274
said: 1 | **ENTWIN** t_ms:22030112 stream:0x3c4214c9 wall:0 window_ms:60089 entities:4
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 6 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 7 | **CORE** entities:0
```

---

@LAT103LON8229 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 23111009 ±21 frame:7000
seq: 413
follows: 0x00000010:212 0x00000011:143 0x00000012:59 0x00000200:845 0x00000300:2313
said: 1 | **ENTWIN** t_ms:23182217 stream:0x3c4214c9 wall:0 window_ms:600000 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 7 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 8 | **CORE** entities:3 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace
said: 9 | **COVERED** windows:1 entities:5 window_ms:551965 first_t_ms:22582166 last_t_ms:22582166 covered_by:@LAT103LON8228
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46 windows:1
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
```

---

@LAT103LON8230 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 24308001 ±21 frame:7000
seq: 435
follows: 0x00000010:233 0x00000011:165 0x00000012:81 0x00000200:866 0x00000300:2355
said: 1 | **ENTWIN** t_ms:24379196 stream:0x3c4214c9 wall:0 window_ms:596980 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,0283cce0e689
said: 11 | **COVERED** windows:1 entities:5 window_ms:600000 first_t_ms:23782217 last_t_ms:23782217 covered_by:@LAT103LON8229
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1
```

---

@LAT103LON8231 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 25511036 ±21 frame:7000
seq: 456
follows: 0x00000010:254 0x00000011:187 0x00000012:102 0x00000200:886 0x00000300:2396
said: 1 | **ENTWIN** t_ms:25582217 stream:0x3c4214c9 wall:0 window_ms:599998 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
said: 7 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,5203cfd1b904
said: 9 | **COVERED** windows:1 entities:5 window_ms:603022 first_t_ms:24982218 last_t_ms:24982218 covered_by:@LAT103LON8230
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46 windows:1
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87 windows:1
```

---

@LAT103LON16420 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 25559081 ±21 frame:7000
seq: 457
follows: 0x00000010:255 0x00000011:188 0x00000012:103 0x00000200:887 0x00000300:2399
said: 1 | **MOTIONWIN** t_ms:25630264 stream:0x3c4214c9 wall:0 window_ms:60000 n:596
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:28 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16742 window_ms:1740079 moving_permille:0 dev_mean_mg:14 dev_max_mg:29 moving_ms:0 first_t_ms:23890185 last_t_ms:25570264 covered_by:@LAT103LON16419
```

---

@LAT103LON8232 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 27311049 ±21 frame:7000
seq: 488
follows: 0x00000010:286 0x00000011:219 0x00000012:133 0x00000200:915 0x00000300:2456
said: 1 | **ENTWIN** t_ms:27382219 stream:0x3c4214c9 wall:0 window_ms:600002 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 7 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,0283cce0e689
said: 9 | **COVERED** windows:2 entities:5 window_ms:1200000 first_t_ms:26182217 last_t_ms:26782217 covered_by:@LAT103LON8231
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-40 windows:2
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-67 windows:2
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-72 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-75 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-86 windows:2
```

---

@LAT103LON16421 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 27357095 ±21 frame:7000
seq: 489
follows: 0x00000010:287 0x00000011:220 0x00000012:134 0x00000200:916 0x00000300:2458
said: 1 | **MOTIONWIN** t_ms:27430264 stream:0x3c4214c9 wall:0 window_ms:60000 n:584
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:25 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16741 window_ms:1740000 moving_permille:0 dev_mean_mg:14 dev_max_mg:46 moving_ms:0 first_t_ms:25690264 last_t_ms:27370264 covered_by:@LAT103LON16420
```

---

@LAT103LON16422 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 28823096 ±21 frame:7000
seq: 512
follows: 0x00000010:313 0x00000011:247 0x00000012:162 0x00000200:941 0x00000300:2502
said: 1 | **MOTIONWIN** t_ms:28938426 stream:0x3c4214c9 wall:0 window_ms:60000 n:394
said: 2 | **MOTION** state:still moving_permille:2 dev_mean_mg:2 dev_max_mg:86 moving_ms:500
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8233 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 28823495 ±21 frame:7000
seq: 514
follows: 0x00000010:313 0x00000011:247 0x00000012:162 0x00000200:941 0x00000300:2502
said: 1 | **ENTWIN** t_ms:28938426 stream:0x3c4214c9 wall:0 window_ms:60399 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON16423 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 29628280 ±21 frame:7000
seq: 521
follows: 0x00000010:325 0x00000011:258 0x00000012:177 0x00000200:954 0x00000300:2531
said: 1 | **MOTIONWIN** t_ms:29743580 stream:0x3c4214c9 wall:0 window_ms:60000 n:386
said: 2 | **MOTION** state:still moving_permille:2 dev_mean_mg:3 dev_max_mg:86 moving_ms:500
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8234 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 29628595 ±21 frame:7000
seq: 523
follows: 0x00000010:325 0x00000011:258 0x00000012:177 0x00000200:954 0x00000300:2531
said: 1 | **ENTWIN** t_ms:29743580 stream:0x3c4214c9 wall:0 window_ms:60315 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 7 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 8 | **CORE** entities:0
```

---

@LAT103LON8235 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 30782050 ±21 frame:7000
seq: 543
follows: 0x00000010:345 0x00000011:277 0x00000012:195 0x00000200:975 0x00000300:2572
said: 1 | **ENTWIN** t_ms:30897390 stream:0x3c4214c9 wall:0 window_ms:599797 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 9 | **CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace
said: 10 | **COVERED** windows:1 entities:6 window_ms:553647 first_t_ms:30297541 last_t_ms:30297541 covered_by:@LAT103LON8234
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-65 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85 windows:1
```

---

@LAT103LON8236 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31381860 ±21 frame:7000
seq: 554
follows: 0x00000010:356 0x00000011:288 0x00000012:206 0x00000200:986 0x00000300:2593
said: 1 | **ENTWIN** t_ms:31497191 stream:0x3c4214c9 wall:0 window_ms:599802 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 7 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 8 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,0283cce0e689
```

---

@LAT103LON16424 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 31428299 ±21 frame:7000
seq: 555
follows: 0x00000010:357 0x00000011:289 0x00000012:207 0x00000200:987 0x00000300:2595
said: 1 | **MOTIONWIN** t_ms:31543631 stream:0x3c4214c9 wall:0 window_ms:60000 n:586
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:3 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16612 window_ms:1740000 moving_permille:0 dev_mean_mg:3 dev_max_mg:29 moving_ms:0 first_t_ms:29803580 last_t_ms:31483631 covered_by:@LAT103LON16423
```

---

@LAT103LON8237 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31982266 ±21 frame:7000
seq: 566
follows: 0x00000010:367 0x00000011:298 0x00000012:217 0x00000200:996 0x00000300:2614
said: 1 | **ENTWIN** t_ms:32097590 stream:0x3c4214c9 wall:0 window_ms:600399 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON16425 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 33229386 ±21 frame:7000
seq: 587
follows: 0x00000010:390 0x00000011:320 0x00000012:239 0x00000200:1017 0x00000300:2656
said: 1 | **MOTIONWIN** t_ms:33344697 stream:0x3c4214c9 wall:0 window_ms:60000 n:583
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:3 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16713 window_ms:1741066 moving_permille:0 dev_mean_mg:3 dev_max_mg:42 moving_ms:0 first_t_ms:31603631 last_t_ms:33284697 covered_by:@LAT103LON16424
```

---

@LAT103LON8238 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 33782088 ±21 frame:7000
seq: 598
follows: 0x00000010:399 0x00000011:329 0x00000012:248 0x00000200:1027 0x00000300:2675
said: 1 | **ENTWIN** t_ms:33897393 stream:0x3c4214c9 wall:0 window_ms:599804 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,0283cce0e689,e6b32d2cea8b
said: 11 | **COVERED** windows:2 entities:8 window_ms:1199999 first_t_ms:32697391 last_t_ms:33297590 covered_by:@LAT103LON8237
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-38 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-67 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-77 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-72 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-80 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-87 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
```

---

@LAT103LON8239 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34982100 ±21 frame:7000
seq: 619
follows: 0x00000010:420 0x00000011:350 0x00000012:271 0x00000200:1047 0x00000300:2716
said: 1 | **ENTWIN** t_ms:35097392 stream:0x3c4214c9 wall:0 window_ms:600001 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689
said: 10 | **COVERED** windows:1 entities:5 window_ms:599997 first_t_ms:34497390 last_t_ms:34497390 covered_by:@LAT103LON8238
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78 windows:1
```

---

@LAT103LON16426 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 35029444 ±21 frame:7000
seq: 620
follows: 0x00000010:421 0x00000011:351 0x00000012:271 0x00000200:1048 0x00000300:2718
said: 1 | **MOTIONWIN** t_ms:35144787 stream:0x3c4214c9 wall:0 window_ms:60000 n:584
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:3 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16652 window_ms:1740039 moving_permille:0 dev_mean_mg:3 dev_max_mg:42 moving_ms:0 first_t_ms:33404697 last_t_ms:35084736 covered_by:@LAT103LON16425
```

---

@LAT103LON8240 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 35578885 ±21 frame:7000
seq: 631
follows: 0x00000010:431 0x00000011:361 0x00000012:282 0x00000200:1058 0x00000300:2738
said: 1 | **ENTWIN** t_ms:35694221 stream:0x3c4214c9 wall:0 window_ms:596779 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,0283cce0e689
```

---

@LAT103LON8241 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36182315 ±21 frame:7000
seq: 642
follows: 0x00000010:441 0x00000011:372 0x00000012:292 0x00000200:1068 0x00000300:2758
said: 1 | **ENTWIN** t_ms:36297644 stream:0x3c4214c9 wall:0 window_ms:603423 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON16427 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 36829487 ±21 frame:7000
seq: 653
follows: 0x00000010:453 0x00000011:383 0x00000012:303 0x00000200:1079 0x00000300:2781
said: 1 | **MOTIONWIN** t_ms:36944812 stream:0x3c4214c9 wall:0 window_ms:60000 n:595
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:3 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16596 window_ms:1740025 moving_permille:0 dev_mean_mg:3 dev_max_mg:18 moving_ms:0 first_t_ms:35204787 last_t_ms:36884812 covered_by:@LAT103LON16426
```

---

@LAT103LON16428 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 38629592 ±21 frame:7000
seq: 684
follows: 0x00000010:484 0x00000011:414 0x00000012:334 0x00000200:1110 0x00000300:2844
said: 1 | **MOTIONWIN** t_ms:38744895 stream:0x3c4214c9 wall:0 window_ms:60000 n:594
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:3 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16658 window_ms:1740083 moving_permille:0 dev_mean_mg:3 dev_max_mg:15 moving_ms:0 first_t_ms:37004812 last_t_ms:38684895 covered_by:@LAT103LON16427
```

---

@LAT103LON8242 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 39782268 ±21 frame:7000
seq: 705
follows: 0x00000010:503 0x00000011:434 0x00000012:354 0x00000200:1129 0x00000300:2885
said: 1 | **ENTWIN** t_ms:39897608 stream:0x3c4214c9 wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **RUN** windows_since_last:6 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,0283cce0e689,e6b32d2cea8b
said: 10 | **COVERED** windows:5 entities:8 window_ms:2999913 first_t_ms:36894080 last_t_ms:39297557 covered_by:@LAT103LON8241
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-39 windows:5
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-71 windows:4
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-72 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-73 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-78 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-87 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-86 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
```

---

@LAT103LON16429 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 40429614 ±21 frame:7000
seq: 716
follows: 0x00000010:514 0x00000011:446 0x00000012:364 0x00000200:1141 0x00000300:2907
said: 1 | **MOTIONWIN** t_ms:40544947 stream:0x3c4214c9 wall:0 window_ms:60000 n:596
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:3 dev_max_mg:28 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16550 window_ms:1740001 moving_permille:0 dev_mean_mg:3 dev_max_mg:16 moving_ms:0 first_t_ms:38804895 last_t_ms:40484947 covered_by:@LAT103LON16428
```

---

@LAT103LON8243 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 40982280 ±21 frame:7000
seq: 727
follows: 0x00000010:524 0x00000011:456 0x00000012:375 0x00000200:1150 0x00000300:2926
said: 1 | **ENTWIN** t_ms:41097608 stream:0x3c4214c9 wall:0 window_ms:599799 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,84a329c78fec,0283cce0e689
said: 10 | **COVERED** windows:1 entities:7 window_ms:600200 first_t_ms:40497809 last_t_ms:40497809 covered_by:@LAT103LON8242
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
```

---

@LAT103LON16430 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 158659 ±21 frame:10000
seq: 733
follows: 0x00000010:1183 0x00000011:1133 0x00000012:1036 0x00000200:1822 0x00000300:4214
said: 1 | **MOTIONWIN** t_ms:474669 stream:0x364dd329 wall:0 window_ms:60835 n:479
said: 2 | **MOTION** state:still moving_permille:2 dev_mean_mg:3 dev_max_mg:72 moving_ms:500
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8244 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 158967 ±21 frame:10000
seq: 735
follows: 0x00000010:1183 0x00000011:1133 0x00000012:1036 0x00000200:1822 0x00000300:4214
said: 1 | **ENTWIN** t_ms:474669 stream:0x364dd329 wall:0 window_ms:61143 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-89
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON16431 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 101941 ±21 frame:8000
seq: 752
follows: 0x00000010:1194 0x00000011:1143 0x00000012:1046 0x00000200:1840 0x00000300:4236
said: 1 | **MOTIONWIN** t_ms:91273 stream:0x732acba3 wall:0 window_ms:60000 n:493
said: 2 | **MOTION** state:still moving_permille:2 dev_mean_mg:3 dev_max_mg:69 moving_ms:500
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8245 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 102128 ±21 frame:8000
seq: 754
follows: 0x00000010:1194 0x00000011:1143 0x00000012:1046 0x00000200:1840 0x00000300:4236
said: 1 | **ENTWIN** t_ms:91273 stream:0x732acba3 wall:0 window_ms:60187 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8246 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1257077 ±21 frame:8000
seq: 774
follows: 0x00000010:1213 0x00000011:1163 0x00000012:1066 0x00000200:1860 0x00000300:4275
said: 1 | **ENTWIN** t_ms:1246397 stream:0x732acba3 wall:0 window_ms:600646 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-84
said: 7 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 8 | **CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904
said: 9 | **COVERED** windows:1 entities:4 window_ms:554292 first_t_ms:645751 last_t_ms:645751 covered_by:@LAT103LON8245
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
```

---

@LAT103LON8247 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1853662 ±21 frame:8000
seq: 785
follows: 0x00000010:1224 0x00000011:1174 0x00000012:1077 0x00000200:1871 0x00000300:4296
said: 1 | **ENTWIN** t_ms:1842975 stream:0x732acba3 wall:0 window_ms:596578 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 9 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5ce28c488e0c,5203cfd1b904
```

---

@LAT103LON16432 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 1902209 ±21 frame:8000
seq: 786
follows: 0x00000010:1226 0x00000011:1175 0x00000012:1078 0x00000200:1872 0x00000300:4299
said: 1 | **MOTIONWIN** t_ms:1891522 stream:0x732acba3 wall:0 window_ms:60000 n:596
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:25 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16891 window_ms:1740250 moving_permille:0 dev_mean_mg:6 dev_max_mg:23 moving_ms:0 first_t_ms:151273 last_t_ms:1831523 covered_by:@LAT103LON16431
```

---

@LAT103LON8248 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3057296 ±21 frame:8000
seq: 807
follows: 0x00000010:1246 0x00000011:1194 0x00000012:1097 0x00000200:1891 0x00000300:4337
said: 1 | **ENTWIN** t_ms:3046596 stream:0x732acba3 wall:0 window_ms:600200 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,5ce28c488e0c,7236bc441422
said: 11 | **COVERED** windows:1 entities:6 window_ms:603421 first_t_ms:2446396 last_t_ms:2446396 covered_by:@LAT103LON8247
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-65 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90 windows:1
```

---

@LAT103LON8249 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3657305 ±21 frame:8000
seq: 818
follows: 0x00000010:1257 0x00000011:1204 0x00000012:1108 0x00000200:1901 0x00000300:4357
said: 1 | **ENTWIN** t_ms:3646599 stream:0x732acba3 wall:0 window_ms:600003 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,7236bc441422
```

---

@LAT103LON16433 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3702268 ±21 frame:8000
seq: 819
follows: 0x00000010:1259 0x00000011:1205 0x00000012:1109 0x00000200:1902 0x00000300:4360
said: 1 | **MOTIONWIN** t_ms:3691563 stream:0x732acba3 wall:0 window_ms:60000 n:576
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:22 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16652 window_ms:1740040 moving_permille:0 dev_mean_mg:10 dev_max_mg:30 moving_ms:0 first_t_ms:1951523 last_t_ms:3631563 covered_by:@LAT103LON16432
```

---

@LAT103LON8250 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4857513 ±21 frame:8000
seq: 840
follows: 0x00000010:1279 0x00000011:1224 0x00000012:1130 0x00000200:1923 0x00000300:4399
said: 1 | **ENTWIN** t_ms:4846796 stream:0x732acba3 wall:0 window_ms:600600 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c
said: 11 | **COVERED** windows:1 entities:5 window_ms:599597 first_t_ms:4246196 last_t_ms:4246196 covered_by:@LAT103LON8249
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
```

---

@LAT103LON8251 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5457322 ±21 frame:8000
seq: 851
follows: 0x00000010:1290 0x00000011:1235 0x00000012:1141 0x00000200:1933 0x00000300:4419
said: 1 | **ENTWIN** t_ms:5446649 stream:0x732acba3 wall:0 window_ms:599802 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,5ce28c488e0c
```

---

@LAT103LON16434 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5502339 ±21 frame:8000
seq: 852
follows: 0x00000010:1292 0x00000011:1236 0x00000012:1142 0x00000200:1934 0x00000300:4422
said: 1 | **MOTIONWIN** t_ms:5491666 stream:0x732acba3 wall:0 window_ms:60000 n:596
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:22 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16633 window_ms:1740052 moving_permille:0 dev_mean_mg:11 dev_max_mg:86 moving_ms:200 first_t_ms:3751563 last_t_ms:5431666 covered_by:@LAT103LON16433
```

---

@LAT103LON8252 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6053067 ±21 frame:8000
seq: 863
follows: 0x00000010:1301 0x00000011:1246 0x00000012:1152 0x00000200:1943 0x00000300:4440
said: 1 | **ENTWIN** t_ms:6042386 stream:0x732acba3 wall:0 window_ms:595737 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,5ce28c488e0c,64677217947d
```

---

@LAT103LON8253 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6657334 ±21 frame:8000
seq: 874
follows: 0x00000010:1312 0x00000011:1256 0x00000012:1162 0x00000200:1953 0x00000300:4460
said: 1 | **ENTWIN** t_ms:6646648 stream:0x732acba3 wall:0 window_ms:604262 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,5ce28c488e0c
```

---

@LAT103LON8254 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7257341 ±21 frame:8000
seq: 885
follows: 0x00000010:1323 0x00000011:1266 0x00000012:1173 0x00000200:1963 0x00000300:4481
said: 1 | **ENTWIN** t_ms:7246648 stream:0x732acba3 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-89
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c,5203cfd1b904
```

---

@LAT103LON16435 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 7302355 ±21 frame:8000
seq: 886
follows: 0x00000010:1324 0x00000011:1267 0x00000012:1174 0x00000200:1964 0x00000300:4484
said: 1 | **MOTIONWIN** t_ms:7291685 stream:0x732acba3 wall:0 window_ms:60000 n:595
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:22 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16639 window_ms:1740019 moving_permille:0 dev_mean_mg:11 dev_max_mg:35 moving_ms:0 first_t_ms:5551666 last_t_ms:7231685 covered_by:@LAT103LON16434
```

---

@LAT106LON69 | created:0 | updated:0

**BAR** frame:8000 bar:12 own:0 held:50 terms:9 digest:0x9c7c5137 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1312 hi:1322 sum:13174
**HOLDS** agent:0x00000011 n:10 lo:1256 hi:1265 sum:12605
**HOLDS** agent:0x00000012 n:10 lo:1162 hi:1171 sum:11665
**HOLDS** agent:0x00000200 n:10 lo:1954 hi:1963 sum:19585
**HOLDS** agent:0x00000300 n:10 lo:4459 hi:4477 sum:44680
**DELIVER** up_s:7474 heap:225996 fetched:620 unanswered:231 broken:0 resumed:10 empty:151 served:0 wants:671 early:48 wantq_drop:0 superseded:0

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

@LAT106LON70 | created:0 | updated:0

**BAR** frame:8000 bar:13 own:0 held:50 terms:9 digest:0x45949f72 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1323 hi:1332 sum:13275
**HOLDS** agent:0x00000011 n:10 lo:1266 hi:1275 sum:12705
**HOLDS** agent:0x00000012 n:10 lo:1172 hi:1182 sum:11774
**HOLDS** agent:0x00000200 n:10 lo:1964 hi:1973 sum:19685
**HOLDS** agent:0x00000300 n:10 lo:4479 hi:4499 sum:44897
**DELIVER** up_s:8079 heap:225972 fetched:670 unanswered:266 broken:0 resumed:15 empty:162 served:0 wants:725 early:48 wantq_drop:0 superseded:0

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

@LAT106LON71 | created:0 | updated:0

**BAR** frame:8000 bar:14 own:0 held:50 terms:9 digest:0x4b93e0ea settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1333 hi:1342 sum:13375
**HOLDS** agent:0x00000011 n:10 lo:1276 hi:1285 sum:12805
**HOLDS** agent:0x00000012 n:10 lo:1183 hi:1193 sum:11884
**HOLDS** agent:0x00000200 n:10 lo:1975 hi:1984 sum:19795
**HOLDS** agent:0x00000300 n:10 lo:4501 hi:4520 sum:45109
**DELIVER** up_s:8671 heap:225996 fetched:721 unanswered:288 broken:0 resumed:17 empty:173 served:0 wants:784 early:48 wantq_drop:0 superseded:0

---

@LAT103LON16436 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 9102398 ±21 frame:8000
seq: 919
follows: 0x00000010:1356 0x00000011:1298 0x00000012:1207 0x00000200:1995 0x00000300:4547
said: 1 | **MOTIONWIN** t_ms:9091685 stream:0x732acba3 wall:0 window_ms:60000 n:596
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:21 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16589 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:25 moving_ms:0 first_t_ms:7351685 last_t_ms:9031685 covered_by:@LAT103LON16435
```

---

@LAT106LON72 | created:0 | updated:0

**BAR** frame:8000 bar:15 own:0 held:50 terms:9 digest:0x033334fc settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1343 hi:1353 sum:13484
**HOLDS** agent:0x00000011 n:10 lo:1286 hi:1295 sum:12905
**HOLDS** agent:0x00000012 n:10 lo:1194 hi:1204 sum:11994
**HOLDS** agent:0x00000200 n:10 lo:1985 hi:1994 sum:19895
**HOLDS** agent:0x00000300 n:10 lo:4522 hi:4541 sum:45319
**DELIVER** up_s:9274 heap:225996 fetched:771 unanswered:293 broken:1 resumed:19 empty:186 served:0 wants:837 early:48 wantq_drop:0 superseded:0

---

@LAT106LON73 | created:0 | updated:0

**BAR** frame:8000 bar:16 own:0 held:50 terms:9 digest:0x8fff28fa settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1354 hi:1364 sum:13594
**HOLDS** agent:0x00000011 n:10 lo:1296 hi:1306 sum:13014
**HOLDS** agent:0x00000012 n:10 lo:1205 hi:1215 sum:12104
**HOLDS** agent:0x00000200 n:10 lo:1995 hi:2004 sum:19995
**HOLDS** agent:0x00000300 n:10 lo:4543 hi:4562 sum:45528
**DELIVER** up_s:9877 heap:225996 fetched:821 unanswered:305 broken:1 resumed:19 empty:197 served:0 wants:891 early:48 wantq_drop:0 superseded:0

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

@LAT106LON74 | created:0 | updated:0

**BAR** frame:8000 bar:17 own:0 held:50 terms:9 digest:0x5345e039 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1365 hi:1374 sum:13695
**HOLDS** agent:0x00000011 n:10 lo:1307 hi:1316 sum:13115
**HOLDS** agent:0x00000012 n:10 lo:1216 hi:1226 sum:12214
**HOLDS** agent:0x00000200 n:10 lo:2005 hi:2014 sum:20095
**HOLDS** agent:0x00000300 n:10 lo:4564 hi:4582 sum:45730
**DELIVER** up_s:10470 heap:223172 fetched:871 unanswered:328 broken:1 resumed:19 empty:207 served:0 wants:943 early:48 wantq_drop:0 superseded:0

---

@LAT103LON16437 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 10902459 ±21 frame:8000
seq: 951
follows: 0x00000010:1387 0x00000011:1329 0x00000012:1240 0x00000200:2025 0x00000300:4608
said: 1 | **MOTIONWIN** t_ms:10891805 stream:0x732acba3 wall:0 window_ms:60000 n:596
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:20 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16653 window_ms:1740069 moving_permille:0 dev_mean_mg:9 dev_max_mg:24 moving_ms:0 first_t_ms:9151685 last_t_ms:10831804 covered_by:@LAT103LON16436
```

---

@LAT106LON75 | created:0 | updated:0

**BAR** frame:8000 bar:18 own:0 held:50 terms:9 digest:0xabc37525 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1375 hi:1384 sum:13795
**HOLDS** agent:0x00000011 n:10 lo:1317 hi:1326 sum:13215
**HOLDS** agent:0x00000012 n:10 lo:1227 hi:1237 sum:12324
**HOLDS** agent:0x00000200 n:10 lo:2015 hi:2024 sum:20195
**HOLDS** agent:0x00000300 n:10 lo:4584 hi:4602 sum:45930
**DELIVER** up_s:11074 heap:225996 fetched:921 unanswered:343 broken:3 resumed:27 empty:221 served:0 wants:996 early:48 wantq_drop:0 superseded:0

---

@LAT106LON76 | created:0 | updated:0

**BAR** frame:8000 bar:19 own:0 held:48 terms:9 digest:0xb5144cb4 settled_ms:300019
**HOLDS** agent:0x00000010 n:10 lo:1385 hi:1395 sum:13904
**HOLDS** agent:0x00000011 n:10 lo:1327 hi:1337 sum:13324
**HOLDS** agent:0x00000012 n:10 lo:1238 hi:1248 sum:12434
**HOLDS** agent:0x00000200 n:10 lo:2025 hi:2034 sum:20295
**HOLDS** agent:0x00000300 n:8 lo:4604 hi:4623 sum:36901
**DELIVER** up_s:11673 heap:222972 fetched:970 unanswered:370 broken:4 resumed:31 empty:229 served:0 wants:1048 early:48 wantq_drop:0 superseded:0

---

@LAT103LON16438 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60906 ±0 frame:10000
seq: 968
follows: 0x00000010:1402 0x00000011:1345 0x00000012:1256 0x00000200:2041 0x00000300:4636
said: 1 | **MOTIONWIN** t_ms:48034 stream:0x92e790ea wall:0 window_ms:60906 n:480
said: 2 | **MOTION** state:still moving_permille:2 dev_mean_mg:3 dev_max_mg:65 moving_ms:500
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
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

@LAT106LON77 | created:0 | updated:0

**BAR** frame:10000 bar:1 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:917 heap:225828 fetched:0 unanswered:0 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

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

@LAT106LON78 | created:0 | updated:0

**BAR** frame:10000 bar:2 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:1515 heap:225828 fetched:0 unanswered:0 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON16439 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 87874 ±21 frame:7500
seq: 999
follows: 0x00000010:1408 0x00000011:1352 0x00000012:1267 0x00000200:2044 0x00000300:4641
said: 1 | **MOTIONWIN** t_ms:409624 stream:0xc9e0e898 wall:0 window_ms:60000 n:468
said: 2 | **MOTION** state:still moving_permille:2 dev_mean_mg:4 dev_max_mg:71 moving_ms:500
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
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

@LAT106LON79 | created:0 | updated:0

**BAR** frame:7500 bar:1 own:0 held:46 terms:9 digest:0xd2c5d402 settled_ms:300022
**HOLDS** agent:0x00000010 n:9 lo:1409 hi:1417 sum:12717
**HOLDS** agent:0x00000011 n:9 lo:1353 hi:1361 sum:12213
**HOLDS** agent:0x00000012 n:10 lo:1267 hi:1276 sum:12715
**HOLDS** agent:0x00000200 n:9 lo:2045 hi:2054 sum:18449
**HOLDS** agent:0x00000300 n:9 lo:4642 hi:4660 sum:41866
**DELIVER** up_s:888 heap:225812 fetched:83 unanswered:23 broken:0 resumed:5 empty:19 served:0 wants:79 early:48 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:4 split:1
**SPLIT** agent:0x00000012 grammar:0xaf98ac36

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

@LAT106LON80 | created:0 | updated:0

**BAR** frame:7500 bar:2 own:0 held:50 terms:9 digest:0x4d262fda settled_ms:300031
**HOLDS** agent:0x00000010 n:10 lo:1418 hi:1427 sum:14225
**HOLDS** agent:0x00000011 n:10 lo:1362 hi:1371 sum:13665
**HOLDS** agent:0x00000012 n:10 lo:1277 hi:1287 sum:12821
**HOLDS** agent:0x00000200 n:10 lo:2055 hi:2064 sum:20595
**HOLDS** agent:0x00000300 n:10 lo:4662 hi:4680 sum:46710
**DELIVER** up_s:1492 heap:225812 fetched:133 unanswered:49 broken:0 resumed:5 empty:33 served:0 wants:136 early:50 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:4 split:1
**SPLIT** agent:0x00000012 grammar:0xaf98ac36

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

@LAT103LON16440 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 1895598 ±21 frame:7500
seq: 1033
follows: 0x00000010:1440 0x00000011:1384 0x00000012:1300 0x00000200:2076 0x00000300:4705
said: 1 | **MOTIONWIN** t_ms:2217327 stream:0xc9e0e898 wall:0 window_ms:60000 n:594
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:24 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16878 window_ms:1747703 moving_permille:0 dev_mean_mg:10 dev_max_mg:25 moving_ms:0 first_t_ms:469624 last_t_ms:2157327 covered_by:@LAT103LON16439
```

---

@LAT106LON81 | created:0 | updated:0

**BAR** frame:7500 bar:3 own:0 held:49 terms:9 digest:0xcd88d703 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1429 hi:1438 sum:14335
**HOLDS** agent:0x00000011 n:10 lo:1373 hi:1382 sum:13775
**HOLDS** agent:0x00000012 n:9 lo:1288 hi:1297 sum:11633
**HOLDS** agent:0x00000200 n:10 lo:2065 hi:2075 sum:20704
**HOLDS** agent:0x00000300 n:10 lo:4682 hi:4701 sum:46919
**DELIVER** up_s:2082 heap:225812 fetched:180 unanswered:88 broken:0 resumed:10 empty:46 served:0 wants:194 early:50 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

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

@LAT106LON82 | created:0 | updated:0

**BAR** frame:7500 bar:4 own:0 held:48 terms:9 digest:0xc9a9ac56 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1440 hi:1449 sum:14445
**HOLDS** agent:0x00000011 n:10 lo:1383 hi:1392 sum:13875
**HOLDS** agent:0x00000012 n:8 lo:1299 hi:1307 sum:10425
**HOLDS** agent:0x00000200 n:10 lo:2076 hi:2085 sum:20805
**HOLDS** agent:0x00000300 n:10 lo:4703 hi:4723 sum:47137
**DELIVER** up_s:2689 heap:225812 fetched:230 unanswered:104 broken:1 resumed:16 empty:57 served:0 wants:248 early:50 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

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

@LAT103LON25566 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3275655 ±21 frame:7500
seq: 1059
follows: 0x00000010:1463 0x00000011:1408 0x00000012:1322 0x00000200:2099 0x00000300:4752
said: 1 | **ACOUSTICWIN** t_ms:3597369 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7423 rate:16000
said: 2 | **ACOUSTIC** rms_mean:7 rms_max:23 peak:35 transients:0
```

---

@LAT106LON83 | created:0 | updated:0

**BAR** frame:7500 bar:5 own:0 held:50 terms:9 digest:0xdd4d4ce8 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1450 hi:1459 sum:14545
**HOLDS** agent:0x00000011 n:10 lo:1394 hi:1403 sum:13985
**HOLDS** agent:0x00000012 n:10 lo:1308 hi:1317 sum:13125
**HOLDS** agent:0x00000200 n:10 lo:2086 hi:2095 sum:20905
**HOLDS** agent:0x00000300 n:10 lo:4725 hi:4743 sum:47340
**DELIVER** up_s:3283 heap:225812 fetched:280 unanswered:111 broken:1 resumed:25 empty:68 served:0 wants:305 early:50 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON25567 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3335656 ±21 frame:7500
seq: 1060
follows: 0x00000010:1464 0x00000011:1409 0x00000012:1323 0x00000200:2100 0x00000300:4754
said: 1 | **ACOUSTICWIN** t_ms:3657369 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:6241 rate:16000
said: 2 | **ACOUSTIC** rms_mean:7 rms_max:22 peak:35 transients:0
```

---

@LAT103LON25568 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3395656 ±21 frame:7500
seq: 1061
follows: 0x00000010:1465 0x00000011:1410 0x00000012:1324 0x00000200:2101 0x00000300:4756
said: 1 | **ACOUSTICWIN** t_ms:3717369 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7432 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:26 peak:37 transients:0
```

---

@LAT103LON25569 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3455656 ±21 frame:7500
seq: 1062
follows: 0x00000010:1466 0x00000011:1411 0x00000012:1325 0x00000200:2102 0x00000300:4758
said: 1 | **ACOUSTICWIN** t_ms:3777369 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7261 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:22 peak:32 transients:0
```

---

@LAT103LON25570 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3515655 ±21 frame:7500
seq: 1063
follows: 0x00000010:1467 0x00000011:1412 0x00000012:1326 0x00000200:2103 0x00000300:4760
said: 1 | **ACOUSTICWIN** t_ms:3837369 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7406 rate:16000
said: 2 | **ACOUSTIC** rms_mean:7 rms_max:26 peak:42 transients:0
```

---

@LAT103LON25571 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3575657 ±21 frame:7500
seq: 1064
follows: 0x00000010:1468 0x00000011:1413 0x00000012:1327 0x00000200:2104 0x00000300:4762
said: 1 | **ACOUSTICWIN** t_ms:3897369 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7402 rate:16000
said: 2 | **ACOUSTIC** rms_mean:6 rms_max:25 peak:37 transients:0
```

---

@LAT105LON3675 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3633008 ±21 frame:7500
seq: 1414
follows: 0x00000010:1469 0x00000012:1328 0x00000100:1064 0x00000200:2105 0x00000300:4764
said: 1 | **LINKWIN** t_ms:3954731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-63 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 4 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-70 rssi_med:-69 rssi_max:-68
said: 5 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-62 rssi_med:-59 rssi_max:-56
said: 6 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-80 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-41 rssi_med:-35 rssi_max:-35
```

---

@LAT103LON25572 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3635658 ±21 frame:7500
seq: 1065
follows: 0x00000010:1469 0x00000011:1414 0x00000012:1328 0x00000200:2105 0x00000300:4764
said: 1 | **ACOUSTICWIN** t_ms:3957369 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7420 rate:16000
said: 2 | **ACOUSTIC** rms_mean:7 rms_max:24 peak:37 transients:0
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

@LAT105LON3676 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3648251 ±0 frame:7500
seq: 4765
follows: 0x00000010:1469 0x00000011:1414 0x00000012:1328 0x00000100:1066 0x00000200:2105
said: 1 | **LINKWIN** t_ms:3969995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:141 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-65 rssi_med:-61 rssi_max:-49
said: 4 | **LINK** peer:0x00000200 proto:espnow n:86 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 6 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-64 rssi_med:-59 rssi_max:-54
said: 7 | **LINK** peer:0x00000010 proto:espnow n:116 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-79 rssi_med:-63 rssi_max:-57
said: 10 | 0x00000200 ble met predicted:-59 observed:-59
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-48
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-56 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-63
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-61 observed:-61
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT105LON3677 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3650561 ±21 frame:7500
seq: 2106
follows: 0x00000010:1469 0x00000011:1414 0x00000012:1328 0x00000100:1066 0x00000300:4766
said: 1 | **LINKWIN** t_ms:3972300 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:140 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | **LINK** peer:0x00000300 proto:espnow n:185 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000012 proto:espnow n:119 rssi_min:-33 rssi_med:-32 rssi_max:-32
said: 6 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-50 rssi_med:-47 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-57 rssi_max:-50
```

---

@LAT105LON3678 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3651591 ±21 frame:7500
seq: 1329
follows: 0x00000010:1469 0x00000011:1414 0x00000100:1065 0x00000200:2105 0x00000300:4764
said: 1 | **LINKWIN** t_ms:3973324 stream:0xc9e0e898 wall:0 window_ms:60033
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 4 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:espnow n:140 rssi_min:-43 rssi_med:-41 rssi_max:-36
said: 6 | **LINK** peer:0x00000300 proto:espnow n:180 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 7 | **LINK** peer:0x00000200 proto:espnow n:90 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-51 rssi_max:-43
said: 9 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-36 rssi_med:-32 rssi_max:-31
```

---

@LAT103LON16441 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3695646 ±21 frame:7500
seq: 1067
follows: 0x00000010:1470 0x00000011:1415 0x00000012:1329 0x00000200:2106 0x00000300:4766
said: 1 | **MOTIONWIN** t_ms:4017356 stream:0xc9e0e898 wall:0 window_ms:60000 n:594
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:25 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:16750 window_ms:1740029 moving_permille:0 dev_mean_mg:13 dev_max_mg:27 moving_ms:0 first_t_ms:2277327 last_t_ms:3957356 covered_by:@LAT103LON16440
```

---

@LAT103LON25573 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3695723 ±21 frame:7500
seq: 1068
follows: 0x00000010:1470 0x00000011:1415 0x00000012:1329 0x00000200:2106 0x00000300:4766
said: 1 | **ACOUSTICWIN** t_ms:4017356 stream:0xc9e0e898 wall:0 window_ms:60064 blocks:7409 rate:16000
said: 2 | **ACOUSTIC** rms_mean:7 rms_max:25 peak:36 transients:0
```

---

@LAT105LON3679 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3693008 ±21 frame:7500
seq: 1415
follows: 0x00000010:1470 0x00000012:1329 0x00000100:1066 0x00000200:2106 0x00000300:4766
said: 1 | **LINKWIN** t_ms:4014730 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-63 rssi_max:-60
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-70 rssi_med:-69 rssi_max:-64
said: 5 | **LINK** peer:0x00000200 proto:espnow n:65 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000300 proto:espnow n:117 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 7 | **LINK** peer:0x00000010 proto:espnow n:48 rssi_min:-40 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000012 proto:espnow n:76 rssi_min:-42 rssi_med:-35 rssi_max:-35
said: 9 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-81 rssi_med:-49 rssi_max:-44
```

---

@LAT105LON3680 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3661555 ±21 frame:7500
seq: 1470
follows: 0x00000011:1414 0x00000012:1329 0x00000100:1066 0x00000200:2106 0x00000300:4766
said: 1 | **LINKWIN** t_ms:3983322 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-58 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:63 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:espnow n:126 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 5 | **LINK** peer:0x00000012 proto:espnow n:77 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:116 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 7 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-49 rssi_med:-46 rssi_max:-39
said: 8 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-80 rssi_med:-52 rssi_max:-45
said: 9 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-58 rssi_max:-54
```

---

@LAT105LON3681 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3708457 ±0 frame:7500
seq: 4767
follows: 0x00000010:1470 0x00000011:1415 0x00000012:1329 0x00000100:1068 0x00000200:2106
said: 1 | **LINKWIN** t_ms:4030201 stream:0xc9e0e898 wall:0 window_ms:60206
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-64 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000010 proto:espnow n:66 rssi_min:-49 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000200 proto:espnow n:63 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-82 rssi_med:-62 rssi_max:-49
said: 10 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000010 ble met predicted:-61 observed:-62
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-59 observed:-59
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-48 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT105LON3682 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3710561 ±21 frame:7500
seq: 2107
follows: 0x00000010:1470 0x00000011:1415 0x00000012:1329 0x00000100:1068 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4032301 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-79 rssi_med:-49 rssi_max:-48
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-39 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000011 proto:espnow n:98 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:61 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 6 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-57 rssi_max:-50
said: 7 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-62
said: 8 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-69 rssi_med:-63 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:espnow n:76 rssi_min:-33 rssi_med:-32 rssi_max:-32
```

---

@LAT105LON3683 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3711596 ±21 frame:7500
seq: 1330
follows: 0x00000010:1470 0x00000011:1415 0x00000100:1068 0x00000200:2106 0x00000300:4766
said: 1 | **LINKWIN** t_ms:4033328 stream:0xc9e0e898 wall:0 window_ms:60004
said: 2 | **LINK** peer:0x00000011 proto:espnow n:112 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:espnow n:68 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 4 | **LINK** peer:0x00000011 proto:ble n:70 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 5 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 7 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-51
said: 8 | **LINK** peer:0x00000200 proto:espnow n:90 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-36 rssi_med:-31 rssi_max:-30
```

---

@LAT105LON3684 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3721605 ±21 frame:7500
seq: 1471
follows: 0x00000011:1415 0x00000012:1330 0x00000100:1068 0x00000200:2107 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4043323 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:108 rssi_min:-35 rssi_med:-31 rssi_max:-28
said: 3 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 4 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-52 rssi_max:-46
said: 5 | **LINK** peer:0x00000011 proto:espnow n:119 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 6 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000300 proto:espnow n:134 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 8 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-46 rssi_max:-39
said: 9 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-59 rssi_med:-58 rssi_max:-57
```

---

@LAT105LON3685 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3753010 ±21 frame:7500
seq: 1416
follows: 0x00000010:1471 0x00000012:1330 0x00000100:1068 0x00000200:2107 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4074731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 3 | **LINK** peer:0x00000300 proto:espnow n:137 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 4 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000200 proto:espnow n:137 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-41 rssi_med:-35 rssi_max:-32
said: 7 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON25574 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3755724 ±21 frame:7500
seq: 1069
follows: 0x00000010:1471 0x00000011:1416 0x00000012:1330 0x00000200:2107 0x00000300:4769
said: 1 | **ACOUSTICWIN** t_ms:4077433 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7387 rate:16000
said: 2 | **ACOUSTIC** rms_mean:8 rms_max:29 peak:39 transients:0
```

---

@LAT105LON3686 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3770592 ±21 frame:7500
seq: 2108
follows: 0x00000010:1471 0x00000011:1416 0x00000012:1330 0x00000100:1069 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4092327 stream:0xc9e0e898 wall:0 window_ms:60029
said: 2 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-80 rssi_med:-57 rssi_max:-50
said: 3 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-38 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000010 proto:espnow n:119 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000300 proto:espnow n:141 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:espnow n:145 rssi_min:-49 rssi_med:-46 rssi_max:-46
said: 7 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-80 rssi_med:-63 rssi_max:-62
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-34 rssi_med:-32 rssi_max:-32
```

---

@LAT105LON3687 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3771597 ±21 frame:7500
seq: 1331
follows: 0x00000010:1471 0x00000011:1416 0x00000100:1069 0x00000200:2107 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4093328 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 3 | **LINK** peer:0x00000010 proto:espnow n:110 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 4 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000300 proto:ble n:74 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:espnow n:147 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 7 | **LINK** peer:0x00000011 proto:espnow n:166 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-45 rssi_max:-44
said: 9 | **LINK** peer:0x00000200 proto:espnow n:125 rssi_min:-35 rssi_med:-30 rssi_max:-30
```

---

@LAT105LON3688 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3781605 ±21 frame:7500
seq: 1472
follows: 0x00000011:1416 0x00000012:1331 0x00000100:1069 0x00000200:2108 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4103322 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-79 rssi_med:-46 rssi_max:-39
said: 3 | **LINK** peer:0x00000012 proto:espnow n:105 rssi_min:-35 rssi_med:-31 rssi_max:-31
said: 4 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-77 rssi_med:-52 rssi_max:-46
said: 5 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-59 rssi_med:-57 rssi_max:-57
said: 6 | **LINK** peer:0x00000200 proto:espnow n:110 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000300 proto:espnow n:130 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 8 | **LINK** peer:0x00000011 proto:espnow n:141 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 9 | **LINK** peer:0x00000011 proto:ble n:71 rssi_min:-73 rssi_med:-55 rssi_max:-52
```

---

@LAT105LON3689 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3768457 ±0 frame:7500
seq: 4770
follows: 0x00000010:1471 0x00000011:1416 0x00000012:1330 0x00000100:1069 0x00000200:2107
said: 1 | **LINKWIN** t_ms:4090201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:159 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:espnow n:130 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 6 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-56 rssi_max:-52
said: 7 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-65 rssi_med:-62 rssi_max:-50
said: 8 | **LINK** peer:0x00000010 proto:espnow n:95 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 10 | 0x00000011 ble met predicted:-63 observed:-63
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-59 observed:-59
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-62 observed:-62
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT105LON3690 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3813010 ±21 frame:7500
seq: 1417
follows: 0x00000010:1472 0x00000012:1331 0x00000100:1069 0x00000200:2108 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4134731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000200 proto:espnow n:141 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000300 proto:espnow n:159 rssi_min:-62 rssi_med:-58 rssi_max:-57
said: 5 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-70 rssi_med:-69 rssi_max:-65
said: 6 | **LINK** peer:0x00000012 proto:espnow n:107 rssi_min:-42 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 8 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 9 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-63 rssi_max:-60
```

---

@LAT103LON25575 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3815725 ±21 frame:7500
seq: 1070
follows: 0x00000010:1472 0x00000011:1417 0x00000012:1331 0x00000200:2108 0x00000300:4771
said: 1 | **ACOUSTICWIN** t_ms:4137433 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7416 rate:16000
said: 2 | **ACOUSTIC** rms_mean:12 rms_max:149 peak:241 transients:0
```

---

@LAT105LON3691 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3830592 ±21 frame:7500
seq: 2109
follows: 0x00000010:1472 0x00000011:1417 0x00000012:1331 0x00000100:1070 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4152330 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:98 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000300 proto:espnow n:152 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 8 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-57 rssi_max:-50
```

---

@LAT105LON3692 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3828457 ±0 frame:7500
seq: 4772
follows: 0x00000010:1472 0x00000011:1417 0x00000012:1331 0x00000100:1070 0x00000200:2108
said: 1 | **LINKWIN** t_ms:4150201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-61 rssi_med:-60 rssi_max:-51
said: 6 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-64 rssi_med:-59 rssi_max:-54
said: 7 | **LINK** peer:0x00000011 proto:ble n:46 rssi_min:-79 rssi_med:-63 rssi_max:-58
said: 8 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-65 rssi_med:-61 rssi_max:-49
said: 9 | **LINK** peer:0x00000200 proto:espnow n:142 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 10 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 ble met predicted:-63 observed:-63
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000012 ble met predicted:-56 observed:-60
percept: 14 | 0x00000012 | link_stable | ble | + | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-61
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-59 observed:-59
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON3693 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3831596 ±21 frame:7500
seq: 1332
follows: 0x00000010:1472 0x00000011:1417 0x00000100:1070 0x00000200:2108 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4153328 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:155 rssi_min:-46 rssi_med:-45 rssi_max:-41
said: 4 | **LINK** peer:0x00000010 proto:espnow n:112 rssi_min:-38 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000200 proto:espnow n:186 rssi_min:-36 rssi_med:-30 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:113 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 7 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-53 rssi_max:-51
said: 9 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-52 rssi_max:-43
```

---

@LAT105LON3694 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3841629 ±21 frame:7500
seq: 1473
follows: 0x00000011:1417 0x00000012:1331 0x00000100:1070 0x00000200:2109 0x00000300:4773
said: 1 | **LINKWIN** t_ms:4163344 stream:0xc9e0e898 wall:0 window_ms:60022
said: 2 | **LINK** peer:0x00000200 proto:espnow n:151 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:180 rssi_min:-45 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-59 rssi_med:-58 rssi_max:-56
said: 5 | **LINK** peer:0x00000012 proto:espnow n:51 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 7 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-59 rssi_max:-55
said: 8 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-77 rssi_med:-55 rssi_max:-51
said: 9 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-60 rssi_med:-53 rssi_max:-46
```

---

@LAT103LON25576 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3875723 ±21 frame:7500
seq: 1071
follows: 0x00000010:1473 0x00000011:1418 0x00000012:1332 0x00000200:2109 0x00000300:4773
said: 1 | **ACOUSTICWIN** t_ms:4197433 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7383 rate:16000
said: 2 | **ACOUSTIC** rms_mean:8 rms_max:30 peak:41 transients:0
```

---

@LAT105LON3695 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3888457 ±0 frame:7500
seq: 4774
follows: 0x00000010:1473 0x00000011:1418 0x00000012:1332 0x00000100:1071 0x00000200:2109
said: 1 | **LINKWIN** t_ms:4210201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 5 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-66 rssi_med:-62 rssi_max:-49
said: 6 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-65 rssi_med:-61 rssi_max:-59
said: 7 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-63 rssi_max:-58
said: 8 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000010 proto:espnow n:94 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 10 | 0x00000011 espnow met predicted:-62 observed:-61
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-60 observed:-56
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000200 ble met predicted:-59 observed:-59
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000011 ble met predicted:-63 observed:-63
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-61 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON3696 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3873010 ±21 frame:7500
seq: 1418
follows: 0x00000010:1473 0x00000012:1332 0x00000100:1070 0x00000200:2109 0x00000300:4773
said: 1 | **LINKWIN** t_ms:4194731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-83 rssi_med:-54 rssi_max:-50
said: 3 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 4 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-49 rssi_max:-43
said: 5 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-58 rssi_max:-54
said: 6 | **LINK** peer:0x00000200 proto:espnow n:119 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000300 proto:espnow n:178 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-63 rssi_max:-60
```

---

@LAT105LON3697 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3890593 ±21 frame:7500
seq: 2110
follows: 0x00000010:1473 0x00000011:1418 0x00000012:1332 0x00000100:1071 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4212330 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-38 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000010 proto:espnow n:93 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:114 rssi_min:-48 rssi_med:-46 rssi_max:-45
said: 5 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-57 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:ble n:74 rssi_min:-81 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 9 | **LINK** peer:0x00000012 proto:espnow n:64 rssi_min:-33 rssi_med:-32 rssi_max:-32
```

---

@LAT105LON3698 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3901629 ±21 frame:7500
seq: 1474
follows: 0x00000011:1418 0x00000012:1333 0x00000100:1071 0x00000200:2110 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4223344 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-58 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000300 proto:espnow n:234 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 4 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-46 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-49 rssi_med:-49 rssi_max:-46
said: 6 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 7 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-70 rssi_med:-56 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-66 rssi_med:-58 rssi_max:-55
said: 9 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-77 rssi_med:-53 rssi_max:-46
```

---

@LAT105LON3699 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3891610 ±21 frame:7500
seq: 1333
follows: 0x00000010:1473 0x00000011:1418 0x00000100:1071 0x00000200:2109 0x00000300:4773
said: 1 | **LINKWIN** t_ms:4213341 stream:0xc9e0e898 wall:0 window_ms:60013
said: 2 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 4 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000010 proto:espnow n:82 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 6 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-83 rssi_med:-53 rssi_max:-49
said: 7 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000300 proto:espnow n:221 rssi_min:-86 rssi_med:-44 rssi_max:-40
said: 9 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-50 rssi_max:-43
```
@LAT106LON84 | created:0 | updated:0

**BAR** frame:7500 bar:6 own:0 held:50 terms:8 digest:0xe5fee0c4 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1460 hi:1469 sum:14645
**HOLDS** agent:0x00000011 n:10 lo:1404 hi:1413 sum:14085
**HOLDS** agent:0x00000012 n:10 lo:1318 hi:1328 sum:13231
**HOLDS** agent:0x00000200 n:10 lo:2096 hi:2105 sum:21005
**HOLDS** agent:0x00000300 n:10 lo:4745 hi:4763 sum:47540
**DELIVER** up_s:3886 heap:225812 fetched:330 unanswered:133 broken:1 resumed:33 empty:78 served:0 wants:359 early:50 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT105LON3700 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3933010 ±21 frame:7500
seq: 1419
follows: 0x00000010:1474 0x00000012:1333 0x00000100:1071 0x00000200:2110 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4254731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:141 rssi_min:-62 rssi_med:-58 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-70 rssi_med:-69 rssi_max:-54
said: 4 | **LINK** peer:0x00000010 proto:espnow n:110 rssi_min:-41 rssi_med:-34 rssi_max:-31
said: 5 | **LINK** peer:0x00000012 proto:espnow n:127 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 6 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-82 rssi_med:-63 rssi_max:-55
said: 7 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-82 rssi_med:-49 rssi_max:-41
said: 8 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-54 rssi_max:-47
said: 9 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-82 rssi_med:-59 rssi_max:-53
```

---

@LAT103LON25577 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3935726 ±21 frame:7500
seq: 1072
follows: 0x00000010:1474 0x00000011:1419 0x00000012:1333 0x00000200:2110 0x00000300:4775
said: 1 | **ACOUSTICWIN** t_ms:4257433 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:5163 rate:16000
said: 2 | **ACOUSTIC** rms_mean:9 rms_max:92 peak:102 transients:0
```

---

@LAT105LON3701 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 3948457 ±0 frame:7500
seq: 4776
follows: 0x00000010:1474 0x00000011:1419 0x00000012:1333 0x00000100:1072 0x00000200:2110
said: 1 | **LINKWIN** t_ms:4270201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-62 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-65 rssi_med:-60 rssi_max:-45
said: 4 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-46 rssi_med:-45 rssi_max:-38
said: 6 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-65 rssi_med:-59 rssi_max:-53
said: 7 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-67 rssi_med:-57 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-51 rssi_med:-47 rssi_max:-45
said: 9 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-78 rssi_med:-64 rssi_max:-56
said: 10 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000012 ble met predicted:-56 observed:-57
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000010 ble met predicted:-62 observed:-62
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-61 observed:-60
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-63 observed:-64
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-59 observed:-59
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT105LON3702 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3950594 ±21 frame:7500
seq: 2111
follows: 0x00000010:1474 0x00000011:1419 0x00000012:1333 0x00000100:1072 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4272329 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:156 rssi_min:-48 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-73 rssi_med:-63 rssi_max:-61
said: 4 | **LINK** peer:0x00000011 proto:espnow n:94 rssi_min:-50 rssi_med:-46 rssi_max:-45
said: 5 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-39 rssi_med:-35 rssi_max:-33
said: 6 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-79 rssi_med:-57 rssi_max:-47
said: 7 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-35 rssi_med:-32 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-54 rssi_med:-49 rssi_max:-47
said: 9 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-70 rssi_med:-63 rssi_max:-53
```

---

@LAT105LON3703 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3951610 ±21 frame:7500
seq: 1334
follows: 0x00000010:1474 0x00000011:1419 0x00000100:1071 0x00000200:2110 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4273341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:81 rssi_min:-44 rssi_med:-42 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 4 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-38 rssi_med:-33 rssi_max:-30
said: 6 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-37 rssi_med:-32 rssi_max:-30
said: 7 | **LINK** peer:0x00000200 proto:espnow n:131 rssi_min:-38 rssi_med:-31 rssi_max:-28
said: 8 | **LINK** peer:0x00000300 proto:espnow n:140 rssi_min:-54 rssi_med:-52 rssi_max:-35
said: 9 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-51 rssi_max:-43
```

---

@LAT105LON3704 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3961630 ±21 frame:7500
seq: 1475
follows: 0x00000011:1419 0x00000012:1334 0x00000100:1072 0x00000200:2111 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4283345 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-68 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:104 rssi_min:-59 rssi_med:-50 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:76 rssi_min:-42 rssi_med:-38 rssi_max:-33
said: 5 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-83 rssi_med:-46 rssi_max:-38
said: 6 | **LINK** peer:0x00000300 proto:espnow n:138 rssi_min:-51 rssi_med:-44 rssi_max:-40
said: 7 | **LINK** peer:0x00000011 proto:ble n:71 rssi_min:-79 rssi_med:-53 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:espnow n:60 rssi_min:-34 rssi_med:-31 rssi_max:-29
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-52 rssi_max:-46
```

---

@LAT105LON3705 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3993012 ±21 frame:7500
seq: 1420
follows: 0x00000010:1475 0x00000012:1334 0x00000100:1072 0x00000200:2111 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4314731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-73 rssi_med:-56 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:espnow n:97 rssi_min:-54 rssi_med:-48 rssi_max:-44
said: 4 | **LINK** peer:0x00000012 proto:espnow n:120 rssi_min:-44 rssi_med:-35 rssi_max:-33
said: 5 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-58 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:espnow n:112 rssi_min:-47 rssi_med:-32 rssi_max:-30
said: 7 | **LINK** peer:0x00000300 proto:espnow n:165 rssi_min:-55 rssi_med:-49 rssi_max:-36
said: 8 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-83 rssi_med:-51 rssi_max:-42
said: 9 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-61 rssi_max:-52
```

---

@LAT103LON25578 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3995741 ±21 frame:7500
seq: 1073
follows: 0x00000010:1475 0x00000011:1420 0x00000012:1334 0x00000200:2111 0x00000300:4777
said: 1 | **ACOUSTICWIN** t_ms:4317448 stream:0xc9e0e898 wall:0 window_ms:60015 blocks:7413 rate:16000
said: 2 | **ACOUSTIC** rms_mean:7 rms_max:147 peak:429 transients:0
```

---

@LAT105LON3706 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4011611 ±21 frame:7500
seq: 1335
follows: 0x00000010:1475 0x00000011:1420 0x00000100:1073 0x00000200:2111 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4333341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-45 rssi_med:-31 rssi_max:-27
said: 3 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-56 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:89 rssi_min:-56 rssi_med:-41 rssi_max:-35
said: 5 | **LINK** peer:0x00000300 proto:espnow n:123 rssi_min:-60 rssi_med:-38 rssi_max:-27
said: 6 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-53 rssi_max:-43
said: 7 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-52 rssi_med:-32 rssi_max:-30
said: 8 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-50 rssi_med:-31 rssi_max:-25
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-45 rssi_max:-39
```

---

@LAT105LON3707 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 4008457 ±0 frame:7500
seq: 4778
follows: 0x00000010:1475 0x00000011:1420 0x00000012:1334 0x00000100:1073 0x00000200:2111
said: 1 | **LINKWIN** t_ms:4330201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-57 rssi_max:-49
said: 3 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:espnow n:108 rssi_min:-51 rssi_med:-42 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:espnow n:115 rssi_min:-53 rssi_med:-48 rssi_max:-43
said: 6 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-58 rssi_med:-49 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-62 rssi_max:-50
said: 8 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-55
said: 9 | **LINK** peer:0x00000012 proto:ble n:71 rssi_min:-81 rssi_med:-56 rssi_max:-50
said: 10 | 0x00000010 ble met predicted:-62 observed:-62
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000011 espnow violated predicted:-60 observed:-49
percept: 11 | 0x00000011 | link_stable | espnow | - | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-42
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-59 observed:-57
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-57 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-48
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-64 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT105LON3708 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4021560 ±21 frame:7500
seq: 1476
follows: 0x00000011:1420 0x00000012:1335 0x00000100:1073 0x00000200:2112 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4343344 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-71 rssi_med:-53 rssi_max:-47
said: 3 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-50 rssi_med:-39 rssi_max:-31
said: 4 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-65 rssi_med:-51 rssi_max:-44
said: 5 | **LINK** peer:0x00000300 proto:espnow n:135 rssi_min:-56 rssi_med:-49 rssi_max:-35
said: 6 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-51 rssi_med:-49 rssi_max:-41
said: 7 | **LINK** peer:0x00000012 proto:espnow n:170 rssi_min:-51 rssi_med:-43 rssi_max:-29
said: 8 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-77 rssi_med:-59 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-51 rssi_max:-38
```

---

@LAT105LON3709 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4053012 ±21 frame:7500
seq: 1421
follows: 0x00000010:1476 0x00000012:1335 0x00000100:1073 0x00000200:2112 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4374731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-57 rssi_med:-53 rssi_max:-41
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-69 rssi_med:-58 rssi_max:-50
said: 4 | **LINK** peer:0x00000300 proto:espnow n:179 rssi_min:-61 rssi_med:-46 rssi_max:-41
said: 5 | **LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-59 rssi_med:-54 rssi_max:-50
said: 6 | **LINK** peer:0x00000200 proto:ble n:35 rssi_min:-81 rssi_med:-63 rssi_max:-60
said: 7 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-80 rssi_med:-59 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-47
said: 9 | **LINK** peer:0x00000010 proto:espnow n:118 rssi_min:-43 rssi_med:-35 rssi_max:-30
```

---

@LAT103LON25579 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4055742 ±21 frame:7500
seq: 1074
follows: 0x00000010:1476 0x00000011:1421 0x00000012:1335 0x00000200:2112 0x00000300:4779
said: 1 | **ACOUSTICWIN** t_ms:4377448 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7243 rate:16000
said: 2 | **ACOUSTIC** rms_mean:9 rms_max:59 peak:184 transients:0
```

---

@LAT105LON3710 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 4068458 ±0 frame:7500
seq: 4780
follows: 0x00000010:1476 0x00000011:1421 0x00000012:1335 0x00000100:1074 0x00000200:2112
said: 1 | **LINKWIN** t_ms:4390202 stream:0xc9e0e898 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-68 rssi_max:-61
said: 3 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-63 rssi_max:-51
said: 4 | **LINK** peer:0x00000012 proto:espnow n:103 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:33 rssi_min:-80 rssi_med:-58 rssi_max:-55
said: 6 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-56 rssi_med:-54 rssi_max:-46
said: 8 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 9 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-56 rssi_med:-51 rssi_max:-46
said: 10 | 0x00000200 ble met predicted:-57 observed:-58
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-42 observed:-41
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-48 observed:-51
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-49 observed:-54
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-63
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-68
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000012 ble unobserved predicted:-56 observed:-56
percept: 17 | 0x00000012 | link_stable | ble | ? | -
```

---

@LAT105LON3711 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4071612 ±21 frame:7500
seq: 1336
follows: 0x00000010:1476 0x00000011:1421 0x00000100:1074 0x00000200:2112 0x00000300:4781
said: 1 | **LINKWIN** t_ms:4393341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-37 rssi_med:-31 rssi_max:-29
said: 3 | **LINK** peer:0x00000300 proto:espnow n:190 rssi_min:-39 rssi_med:-33 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-60 rssi_med:-55 rssi_max:-49
said: 5 | **LINK** peer:0x00000200 proto:ble n:38 rssi_min:-55 rssi_med:-42 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-65 rssi_max:-53
said: 7 | **LINK** peer:0x00000010 proto:espnow n:104 rssi_min:-56 rssi_med:-48 rssi_max:-43
said: 8 | **LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 9 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-48 rssi_max:-46
```

---

@LAT105LON3712 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4081629 ±21 frame:7500
seq: 1477
follows: 0x00000011:1421 0x00000012:1336 0x00000100:1074 0x00000200:2112 0x00000300:4781
said: 1 | **LINKWIN** t_ms:4403344 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:83 rssi_min:-41 rssi_med:-36 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:espnow n:187 rssi_min:-57 rssi_med:-49 rssi_max:-41
said: 4 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-64 rssi_med:-60 rssi_max:-44
said: 5 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-79 rssi_med:-55 rssi_max:-49
said: 6 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-76 rssi_med:-56 rssi_max:-51
said: 7 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-79 rssi_med:-54 rssi_max:-49
said: 8 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-65 rssi_med:-42 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:ble n:33 rssi_min:-60 rssi_med:-57 rssi_max:-54
```

---

@LAT105LON3713 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4113013 ±21 frame:7500
seq: 1422
follows: 0x00000010:1477 0x00000012:1336 0x00000100:1074 0x00000200:2114 0x00000300:4781
said: 1 | **LINKWIN** t_ms:4434730 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-64 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-63 rssi_max:-61
said: 4 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-61 rssi_med:-59 rssi_max:-49
said: 5 | **LINK** peer:0x00000300 proto:espnow n:144 rssi_min:-57 rssi_med:-53 rssi_max:-45
said: 6 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-56 rssi_med:-54 rssi_max:-53
said: 7 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-83 rssi_med:-62 rssi_max:-53
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 9 | **LINK** peer:0x00000010 proto:espnow n:70 rssi_min:-40 rssi_med:-33 rssi_max:-32
```

---

@LAT103LON25580 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4115743 ±21 frame:7500
seq: 1075
follows: 0x00000010:1477 0x00000011:1422 0x00000012:1336 0x00000200:2114 0x00000300:4781
said: 1 | **ACOUSTICWIN** t_ms:4437448 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7410 rate:16000
said: 2 | **ACOUSTIC** rms_mean:9 rms_max:65 peak:153 transients:0
```

---

@LAT105LON3714 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4010595 ±21 frame:7500
seq: 2112
follows: 0x00000010:1475 0x00000011:1420 0x00000012:1334 0x00000100:1073 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4332329 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-52 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000010 proto:espnow n:111 rssi_min:-62 rssi_med:-48 rssi_max:-42
said: 4 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-61 rssi_max:-52
said: 5 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-74 rssi_med:-62 rssi_max:-57
said: 6 | **LINK** peer:0x00000012 proto:ble n:70 rssi_min:-56 rssi_med:-49 rssi_max:-42
said: 7 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-55 rssi_max:-47
said: 8 | **LINK** peer:0x00000012 proto:espnow n:141 rssi_min:-44 rssi_med:-33 rssi_max:-28
said: 9 | **LINK** peer:0x00000300 proto:espnow n:132 rssi_min:-49 rssi_med:-41 rssi_max:-33
```

---

@LAT105LON3715 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4095175 ±21 frame:7500
seq: 2113
follows: 0x00000010:1476 0x00000011:1420 0x00000012:1335 0x00000100:1073 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4417270 stream:0xc9e0e898 wall:0 window_ms:76125
said: 2 | **LINK** peer:0x00000012 proto:espnow n:57 rssi_min:-33 rssi_med:-32 rssi_max:-32
said: 3 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000011 proto:espnow n:64 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 5 | **LINK** peer:0x00000010 proto:espnow n:41 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 6 | **LINK** peer:0x00000300 proto:espnow n:105 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 7 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-81 rssi_med:-58 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-57 rssi_med:-49 rssi_max:-47
said: 9 | **LINK** peer:0x00000011 proto:ble n:50 rssi_min:-80 rssi_med:-65 rssi_max:-62
```

---

@LAT105LON3716 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 4128458 ±0 frame:7500
seq: 4782
follows: 0x00000010:1477 0x00000011:1422 0x00000012:1336 0x00000100:1075 0x00000200:2114
said: 1 | **LINKWIN** t_ms:4450202 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-91 rssi_med:-59 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 4 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-67 rssi_med:-50 rssi_max:-48
said: 5 | **LINK** peer:0x00000011 proto:espnow n:80 rssi_min:-61 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000012 proto:espnow n:118 rssi_min:-42 rssi_med:-38 rssi_max:-35
said: 7 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-72 rssi_med:-63 rssi_max:-50
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-80 rssi_med:-68 rssi_max:-61
said: 10 | 0x00000011 ble met predicted:-68 observed:-68
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-63 observed:-63
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-39 observed:-38
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-58 observed:-59
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow violated predicted:-54 observed:-47
percept: 15 | 0x00000011 | link_stable | espnow | - | -
said: 16 | 0x00000200 espnow unobserved predicted:-41 observed:-41
percept: 16 | 0x00000200 | link_stable | espnow | ? | -
said: 17 | 0x00000010 espnow met predicted:-51 observed:-50
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT105LON3717 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4131611 ±21 frame:7500
seq: 1337
follows: 0x00000010:1477 0x00000011:1422 0x00000100:1075 0x00000200:2114 0x00000300:4783
said: 1 | **LINKWIN** t_ms:4453341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-60 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:152 rssi_min:-43 rssi_med:-33 rssi_max:-29
said: 4 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-35 rssi_med:-31 rssi_max:-29
said: 5 | **LINK** peer:0x00000011 proto:espnow n:75 rssi_min:-57 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-49 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:espnow n:75 rssi_min:-48 rssi_med:-44 rssi_max:-42
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-44 rssi_max:-40
said: 9 | **LINK** peer:0x00000011 proto:ble n:51 rssi_min:-80 rssi_med:-64 rssi_max:-55
```

---

@LAT105LON3718 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4155241 ±21 frame:7500
seq: 2115
follows: 0x00000010:1477 0x00000011:1422 0x00000012:1337 0x00000100:1075 0x00000300:4783
said: 1 | **LINKWIN** t_ms:4481341 stream:0xc9e0e898 wall:0 window_ms:60070
said: 2 | **LINK** peer:0x00000010 proto:espnow n:70 rssi_min:-65 rssi_med:-51 rssi_max:-43
said: 3 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-52 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:espnow n:202 rssi_min:-53 rssi_med:-37 rssi_max:-26
said: 5 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-81 rssi_med:-64 rssi_max:-56
said: 6 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-84 rssi_med:-64 rssi_max:-54
said: 7 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-44 rssi_med:-37 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:espnow n:123 rssi_min:-47 rssi_med:-34 rssi_max:-31
said: 9 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-68 rssi_med:-48 rssi_max:-45
```

---

@LAT105LON3719 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4141632 ±21 frame:7500
seq: 1478
follows: 0x00000011:1422 0x00000012:1337 0x00000100:1075 0x00000200:2114 0x00000300:4783
said: 1 | **LINKWIN** t_ms:4463345 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:75 rssi_min:-63 rssi_med:-56 rssi_max:-45
said: 3 | **LINK** peer:0x00000012 proto:espnow n:97 rssi_min:-58 rssi_med:-42 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:espnow n:155 rssi_min:-67 rssi_med:-51 rssi_max:-36
said: 5 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-77 rssi_med:-59 rssi_max:-52
said: 6 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-65 rssi_med:-54 rssi_max:-50
said: 7 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-79 rssi_med:-54 rssi_max:-43
said: 8 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-76 rssi_med:-54 rssi_max:-47
said: 9 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-43 rssi_med:-36 rssi_max:-27
```

---

@LAT103LON25581 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4175744 ±21 frame:7500
seq: 1076
follows: 0x00000010:1478 0x00000011:1423 0x00000012:1337 0x00000200:2115 0x00000300:4783
said: 1 | **ACOUSTICWIN** t_ms:4497448 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7393 rate:16000
said: 2 | **ACOUSTIC** rms_mean:9 rms_max:115 peak:325 transients:0
```

---

@LAT104LON116 | created:0 | updated:0

**carried through @LAT103LON8218**

```ttdb-carried
through: 8218
through: 16419
through: 25565
```

---

@LAT105LON3720 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000300
source: linkpercept
at: 4188561 ±0 frame:7500
seq: 4784
follows: 0x00000010:1478 0x00000011:1424 0x00000012:1337 0x00000100:1076 0x00000200:2115
said: 1 | **LINKWIN** t_ms:4510305 stream:0xc9e0e898 wall:0 window_ms:60103
said: 2 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-56 rssi_max:-46
said: 3 | **LINK** peer:0x00000011 proto:espnow n:67 rssi_min:-63 rssi_med:-49 rssi_max:-42
said: 4 | **LINK** peer:0x00000200 proto:espnow n:168 rssi_min:-63 rssi_med:-44 rssi_max:-31
said: 5 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-63 rssi_max:-55
said: 6 | **LINK** peer:0x00000012 proto:espnow n:130 rssi_min:-47 rssi_med:-38 rssi_max:-34
said: 7 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 8 | **LINK** peer:0x00000010 proto:espnow n:53 rssi_min:-60 rssi_med:-48 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-77 rssi_med:-57 rssi_max:-45
said: 10 | 0x00000200 ble met predicted:-59 observed:-57
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-50 observed:-48
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-47 observed:-49
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble unobserved predicted:-63 observed:-63
percept: 15 | 0x00000010 | link_stable | ble | ? | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-68 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT105LON3721 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4173167 ±21 frame:7500
seq: 1423
follows: 0x00000010:1478 0x00000012:1337 0x00000100:1075 0x00000200:2115 0x00000300:4783
said: 1 | **LINKWIN** t_ms:4494885 stream:0xc9e0e898 wall:0 window_ms:60154
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-55 rssi_max:-51
said: 3 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-67 rssi_med:-58 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:espnow n:204 rssi_min:-55 rssi_med:-45 rssi_max:-39
said: 5 | **LINK** peer:0x00000010 proto:espnow n:62 rssi_min:-44 rssi_med:-31 rssi_max:-27
said: 6 | **LINK** peer:0x00000012 proto:espnow n:110 rssi_min:-64 rssi_med:-46 rssi_max:-42
said: 7 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-84 rssi_med:-62 rssi_max:-50
said: 8 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-82 rssi_med:-50 rssi_max:-37
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-62 rssi_max:-57
```

---

@LAT105LON3722 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4191612 ±21 frame:7500
seq: 1338
follows: 0x00000010:1478 0x00000011:1424 0x00000100:1076 0x00000200:2115 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4513341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-35 rssi_med:-29 rssi_max:-28
said: 3 | **LINK** peer:0x00000200 proto:espnow n:145 rssi_min:-56 rssi_med:-43 rssi_max:-26
said: 4 | **LINK** peer:0x00000300 proto:espnow n:149 rssi_min:-45 rssi_med:-34 rssi_max:-28
said: 5 | **LINK** peer:0x00000011 proto:espnow n:52 rssi_min:-58 rssi_med:-46 rssi_max:-39
said: 6 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-53 rssi_max:-40
said: 7 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-48 rssi_max:-44
said: 8 | **LINK** peer:0x00000010 proto:espnow n:57 rssi_min:-57 rssi_med:-45 rssi_max:-39
said: 9 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-80 rssi_med:-59 rssi_max:-45
```

---

@LAT105LON3723 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4219604 ±21 frame:7500
seq: 2116
follows: 0x00000010:1478 0x00000011:1424 0x00000012:1338 0x00000100:1076 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4541346 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:91 rssi_min:-58 rssi_med:-42 rssi_max:-36
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-36 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000300 proto:espnow n:104 rssi_min:-60 rssi_med:-47 rssi_max:-33
said: 5 | **LINK** peer:0x00000010 proto:espnow n:72 rssi_min:-55 rssi_med:-45 rssi_max:-42
said: 6 | **LINK** peer:0x00000011 proto:espnow n:47 rssi_min:-50 rssi_med:-46 rssi_max:-41
said: 7 | **LINK** peer:0x00000010 proto:ble n:49 rssi_min:-80 rssi_med:-59 rssi_max:-51
said: 8 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-79 rssi_med:-53 rssi_max:-47
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-57 rssi_max:-50
```

---

@LAT103LON25582 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4235744 ±21 frame:7500
seq: 1077
follows: 0x00000010:1480 0x00000011:1424 0x00000012:1338 0x00000200:2116 0x00000300:4785
said: 1 | **ACOUSTICWIN** t_ms:4557448 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:7230 rate:16000
said: 2 | **ACOUSTIC** rms_mean:10 rms_max:85 peak:342 transients:0
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

@LAT105LON3724 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4228400 ±21 frame:7500
seq: 1479
follows: 0x00000011:1424 0x00000012:1338 0x00000100:1076 0x00000200:2116 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4550125 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-56 rssi_med:-51 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:96 rssi_min:-54 rssi_med:-43 rssi_max:-27
said: 4 | **LINK** peer:0x00000012 proto:espnow n:73 rssi_min:-50 rssi_med:-44 rssi_max:-35
said: 5 | **LINK** peer:0x00000200 proto:ble n:49 rssi_min:-70 rssi_med:-55 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-65 rssi_med:-54 rssi_max:-38
said: 7 | **LINK** peer:0x00000012 proto:ble n:45 rssi_min:-78 rssi_med:-58 rssi_max:-44
said: 8 | **LINK** peer:0x00000011 proto:ble n:37 rssi_min:-79 rssi_med:-35 rssi_max:-29
said: 9 | **LINK** peer:0x00000011 proto:espnow n:11 rssi_min:-22 rssi_med:-22 rssi_max:-21
```

---

@LAT105LON3725 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4253348 ±22 frame:7500
seq: 1425
follows: 0x00000010:1480 0x00000012:1339 0x00000100:1078 0x00000200:2116 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4582711 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:61 rssi_min:-60 rssi_med:-46 rssi_max:-34
said: 3 | **LINK** peer:0x00000010 proto:espnow n:93 rssi_min:-23 rssi_med:-21 rssi_max:-20
said: 4 | **LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-67 rssi_med:-29 rssi_max:-24
said: 5 | **LINK** peer:0x00000010 proto:ble n:47 rssi_min:-82 rssi_med:-37 rssi_max:-31
said: 6 | **LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-43 rssi_med:-41 rssi_max:-35
said: 7 | **LINK** peer:0x00000300 proto:ble n:21 rssi_min:-83 rssi_med:-46 rssi_max:-41
said: 8 | **LINK** peer:0x00000200 proto:espnow n:91 rssi_min:-67 rssi_med:-53 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:ble n:39 rssi_min:-82 rssi_med:-62 rssi_max:-51
```

---

@LAT105LON3726 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4251612 ±22 frame:7500
seq: 1339
follows: 0x00000010:1480 0x00000011:1424 0x00000100:1078 0x00000200:2116 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4573341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-58 rssi_max:-47
said: 3 | **LINK** peer:0x00000011 proto:espnow n:41 rssi_min:-62 rssi_med:-45 rssi_max:-41
said: 4 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000300 proto:espnow n:70 rssi_min:-61 rssi_med:-41 rssi_max:-20
said: 6 | **LINK** peer:0x00000300 proto:ble n:45 rssi_min:-85 rssi_med:-50 rssi_max:-33
said: 7 | **LINK** peer:0x00000200 proto:espnow n:111 rssi_min:-52 rssi_med:-42 rssi_max:-34
said: 8 | **LINK** peer:0x00000011 proto:ble n:41 rssi_min:-81 rssi_med:-65 rssi_max:-52
said: 9 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-50 rssi_max:-45
```
