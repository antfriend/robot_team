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

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52525 stream:0x2d4ae0fa wall:0 window_ms:60000 n:564
**MOTION** state:still moving_permille:1 dev_mean_mg:2 dev_max_mg:90 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:1 removed:7 last_lon:6 t_ms:61884 stream:0x2d4ae0fa wall:0 node:0x00000100

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:48 last_lon:47 t_ms:7184 stream:0xa4be8c27 wall:0 node:0x00000100

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52560 stream:0xffe779bc wall:0 window_ms:60000 n:562
**MOTION** state:still moving_permille:1 dev_mean_mg:3 dev_max_mg:89 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52560 stream:0xffe779bc wall:0 window_ms:60027 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-85
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52551 stream:0x08739b89 wall:0 window_ms:60000 n:562
**MOTION** state:still moving_permille:1 dev_mean_mg:3 dev_max_mg:85 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52551 stream:0x08739b89 wall:0 window_ms:60127 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52566 stream:0xd9e1f8b9 wall:0 window_ms:60000 n:562
**MOTION** state:still moving_permille:1 dev_mean_mg:3 dev_max_mg:86 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52566 stream:0xd9e1f8b9 wall:0 window_ms:60040 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:39855497 stream:0xbb1177f2 wall:0 window_ms:60022 n:562
**MOTION** state:still moving_permille:1 dev_mean_mg:15 dev_max_mg:71 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:39855497 stream:0xbb1177f2 wall:0 window_ms:60040 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:41003124 stream:0xbb1177f2 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:4 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,0283cce0e689
**COVERED** windows:1 entities:5 window_ms:547611 first_t_ms:40403124 last_t_ms:40403124 covered_by:@LAT96LON3
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87 windows:1

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:41603125 stream:0xbb1177f2 wall:0 window_ms:600001 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:41655644 stream:0xbb1177f2 wall:0 window_ms:60000 n:589
**MOTION** state:still moving_permille:0 dev_mean_mg:29 dev_max_mg:41 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17047 window_ms:1740147 moving_permille:0 dev_mean_mg:25 dev_max_mg:49 moving_ms:0 first_t_ms:39915497 last_t_ms:41595644 covered_by:@LAT95LON4

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:43455679 stream:0xbb1177f2 wall:0 window_ms:60000 n:592
**MOTION** state:still moving_permille:0 dev_mean_mg:29 dev_max_mg:39 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17216 window_ms:1740035 moving_permille:0 dev_mean_mg:29 dev_max_mg:46 moving_ms:0 first_t_ms:41715644 last_t_ms:43395679 covered_by:@LAT95LON5

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:44003126 stream:0xbb1177f2 wall:0 window_ms:600001 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:5 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689
**COVERED** windows:3 entities:7 window_ms:1800000 first_t_ms:42202925 last_t_ms:43403125 covered_by:@LAT96LON5
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-34 windows:3
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-74 windows:3
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-81 windows:3
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-86 windows:2
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-87 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-88 windows:2

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:45255819 stream:0xbb1177f2 wall:0 window_ms:60014 n:589
**MOTION** state:still moving_permille:0 dev_mean_mg:29 dev_max_mg:42 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17173 window_ms:1740126 moving_permille:0 dev_mean_mg:29 dev_max_mg:160 moving_ms:209 first_t_ms:43515679 last_t_ms:45195805 covered_by:@LAT95LON6

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:46403125 stream:0xbb1177f2 wall:0 window_ms:600200 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:6 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,0283cce0e689,64677217947d,e6b32d2cea8b
**COVERED** windows:3 entities:6 window_ms:1799799 first_t_ms:44603125 last_t_ms:45802925 covered_by:@LAT96LON6
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-34 windows:3
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-72 windows:3
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-79 windows:3
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-85 windows:2
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-87 windows:2
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-86 windows:2

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:47056050 stream:0xbb1177f2 wall:0 window_ms:60001 n:573
**MOTION** state:still moving_permille:0 dev_mean_mg:29 dev_max_mg:39 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:16836 window_ms:1740231 moving_permille:0 dev_mean_mg:29 dev_max_mg:44 moving_ms:0 first_t_ms:45315874 last_t_ms:46996049 covered_by:@LAT95LON7

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:47602925 stream:0xbb1177f2 wall:0 window_ms:599998 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:5 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,64677217947d,0283cce0e689
**COVERED** windows:1 entities:4 window_ms:599801 first_t_ms:47002926 last_t_ms:47002926 covered_by:@LAT96LON7
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86 windows:1

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:48856094 stream:0xbb1177f2 wall:0 window_ms:60000 n:597
**MOTION** state:still moving_permille:0 dev_mean_mg:28 dev_max_mg:39 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17205 window_ms:1740044 moving_permille:0 dev_mean_mg:29 dev_max_mg:46 moving_ms:0 first_t_ms:47116051 last_t_ms:48796094 covered_by:@LAT95LON8

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:50603126 stream:0xbb1177f2 wall:0 window_ms:600202 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-87
**RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:6 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,0283cce0e689,64677217947d,18a5ffbae2d6
**COVERED** windows:4 entities:6 window_ms:2400000 first_t_ms:48202927 last_t_ms:50002925 covered_by:@LAT96LON8
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-33 windows:4
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-71 windows:4
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-81 windows:4
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:3 rssi:-84 windows:3
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:3 rssi:-85 windows:3
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:2 rssi:-88 windows:2

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:50656116 stream:0xbb1177f2 wall:0 window_ms:60002 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:28 dev_max_mg:40 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17232 window_ms:1740020 moving_permille:0 dev_mean_mg:28 dev_max_mg:42 moving_ms:0 first_t_ms:48916094 last_t_ms:50596114 covered_by:@LAT95LON9

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52456119 stream:0xbb1177f2 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:27 dev_max_mg:41 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17252 window_ms:1740002 moving_permille:0 dev_mean_mg:27 dev_max_mg:52 moving_ms:0 first_t_ms:50716116 last_t_ms:52396119 covered_by:@LAT95LON10

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:53603126 stream:0xbb1177f2 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:6 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,64677217947d,0283cce0e689
**COVERED** windows:4 entities:8 window_ms:2400003 first_t_ms:51203332 last_t_ms:53003129 covered_by:@LAT96LON9
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-33 windows:4
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-71 windows:4
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-77 windows:4
**COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:3 rssi:-87 windows:3
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-85 windows:4
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:2 rssi:-88 windows:2
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-83 windows:2

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:54256119 stream:0xbb1177f2 wall:0 window_ms:60000 n:596
**MOTION** state:still moving_permille:0 dev_mean_mg:27 dev_max_mg:38 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17268 window_ms:1740000 moving_permille:0 dev_mean_mg:27 dev_max_mg:42 moving_ms:0 first_t_ms:52516119 last_t_ms:54196119 covered_by:@LAT95LON11

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:55403332 stream:0xbb1177f2 wall:0 window_ms:600006 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,64677217947d,18a5ffbae2d6,0283cce0e689
**COVERED** windows:2 entities:7 window_ms:1200198 first_t_ms:54203331 last_t_ms:54803326 covered_by:@LAT96LON10
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-38 windows:2
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-75 windows:2
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-76 windows:2
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-83 windows:2
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-83 windows:2
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:2 rssi:-87 windows:2
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:56056119 stream:0xbb1177f2 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:27 dev_max_mg:36 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17271 window_ms:1740000 moving_permille:0 dev_mean_mg:27 dev_max_mg:43 moving_ms:0 first_t_ms:54316119 last_t_ms:55996119 covered_by:@LAT95LON12

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:57802926 stream:0xbb1177f2 wall:0 window_ms:599590 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,84a329c78fec,e6b32d2cea8b,0283cce0e689
**COVERED** windows:3 entities:8 window_ms:1800004 first_t_ms:56003128 last_t_ms:57203334 covered_by:@LAT96LON11
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-38 windows:3
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-76 windows:3
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-76 windows:3
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-83 windows:2
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-89 windows:2
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:3 rssi:-89 windows:3
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-87 windows:1

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:57856119 stream:0xbb1177f2 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:27 dev_max_mg:37 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17274 window_ms:1740000 moving_permille:0 dev_mean_mg:26 dev_max_mg:41 moving_ms:0 first_t_ms:56116119 last_t_ms:57796119 covered_by:@LAT95LON13

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:59603126 stream:0xbb1177f2 wall:0 window_ms:600002 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:6 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,64677217947d,0283cce0e689
**COVERED** windows:2 entities:7 window_ms:1200198 first_t_ms:58403125 last_t_ms:59003125 covered_by:@LAT96LON12
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-37 windows:2
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-76 windows:2
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-76 windows:2
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-82 windows:2
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-88 windows:2
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:59656119 stream:0xbb1177f2 wall:0 window_ms:60000 n:594
**MOTION** state:still moving_permille:0 dev_mean_mg:26 dev_max_mg:40 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17267 window_ms:1740000 moving_permille:0 dev_mean_mg:26 dev_max_mg:43 moving_ms:0 first_t_ms:57916119 last_t_ms:59596119 covered_by:@LAT95LON14

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61402926 stream:0xbb1177f2 wall:0 window_ms:599801 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d
**COVERED** windows:2 entities:6 window_ms:1199999 first_t_ms:60203125 last_t_ms:60803125 covered_by:@LAT96LON13
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-37 windows:2
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-73 windows:2
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-77 windows:2
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-82 windows:2
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-87 windows:2
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:61456119 stream:0xbb1177f2 wall:0 window_ms:60000 n:596
**MOTION** state:still moving_permille:0 dev_mean_mg:26 dev_max_mg:37 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17265 window_ms:1740000 moving_permille:0 dev_mean_mg:26 dev_max_mg:45 moving_ms:0 first_t_ms:59716119 last_t_ms:61396119 covered_by:@LAT95LON15

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:62602928 stream:0xbb1177f2 wall:0 window_ms:599802 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:5 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,0283cce0e689,e6b32d2cea8b
**COVERED** windows:1 entities:5 window_ms:600200 first_t_ms:62003127 last_t_ms:62003127 covered_by:@LAT96LON14
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87 windows:1

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:63256119 stream:0xbb1177f2 wall:0 window_ms:60000 n:589
**MOTION** state:still moving_permille:0 dev_mean_mg:25 dev_max_mg:36 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17192 window_ms:1740000 moving_permille:0 dev_mean_mg:26 dev_max_mg:53 moving_ms:0 first_t_ms:61516119 last_t_ms:63196119 covered_by:@LAT95LON16

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:65056119 stream:0xbb1177f2 wall:0 window_ms:60000 n:598
**MOTION** state:still moving_permille:0 dev_mean_mg:24 dev_max_mg:35 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17255 window_ms:1740000 moving_permille:0 dev_mean_mg:25 dev_max_mg:41 moving_ms:0 first_t_ms:63316119 last_t_ms:64996119 covered_by:@LAT95LON17

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:66203125 stream:0xbb1177f2 wall:0 window_ms:600200 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**RUN** windows_since_last:6 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:6 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,64677217947d,0283cce0e689
**COVERED** windows:5 entities:7 window_ms:2999996 first_t_ms:63203125 last_t_ms:65602925 covered_by:@LAT96LON15
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-36 windows:5
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-74 windows:5
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-72 windows:5
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-81 windows:4
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-86 windows:4
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-85 windows:2
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86 windows:1

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:66803125 stream:0xbb1177f2 wall:0 window_ms:600001 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:7 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,64677217947d,0283cce0e689,e6b32d2cea8b,84a329c78fec

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:66856119 stream:0xbb1177f2 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:24 dev_max_mg:35 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17285 window_ms:1740000 moving_permille:0 dev_mean_mg:25 dev_max_mg:39 moving_ms:0 first_t_ms:65116119 last_t_ms:66796119 covered_by:@LAT95LON18

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:68003125 stream:0xbb1177f2 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:6 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689,64677217947d
**COVERED** windows:1 entities:6 window_ms:599999 first_t_ms:67403125 last_t_ms:67403125 covered_by:@LAT96LON17
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88 windows:1

---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:68656119 stream:0xbb1177f2 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:25 dev_max_mg:37 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17280 window_ms:1740000 moving_permille:0 dev_mean_mg:24 dev_max_mg:39 moving_ms:0 first_t_ms:66916119 last_t_ms:68596119 covered_by:@LAT95LON19

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:70402925 stream:0xbb1177f2 wall:0 window_ms:599999 entities:2
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:5 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689
**COVERED** windows:3 entities:6 window_ms:1799802 first_t_ms:68603125 last_t_ms:69802926 covered_by:@LAT96LON18
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-36 windows:3
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-70 windows:3
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-72 windows:3
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-84 windows:2
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-89 windows:2
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1

---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:70456119 stream:0xbb1177f2 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:24 dev_max_mg:34 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17270 window_ms:1740000 moving_permille:0 dev_mean_mg:24 dev_max_mg:41 moving_ms:0 first_t_ms:68716119 last_t_ms:70396119 covered_by:@LAT95LON20

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:71002926 stream:0xbb1177f2 wall:0 window_ms:600001 entities:3
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:3 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d

---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:72256119 stream:0xbb1177f2 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:24 dev_max_mg:36 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17286 window_ms:1740000 moving_permille:0 dev_mean_mg:24 dev_max_mg:39 moving_ms:0 first_t_ms:70516119 last_t_ms:72196119 covered_by:@LAT95LON21

---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:74056164 stream:0xbb1177f2 wall:0 window_ms:60000 n:596
**MOTION** state:still moving_permille:0 dev_mean_mg:23 dev_max_mg:35 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17266 window_ms:1740045 moving_permille:0 dev_mean_mg:23 dev_max_mg:38 moving_ms:0 first_t_ms:72316119 last_t_ms:73996164 covered_by:@LAT95LON22

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:74602925 stream:0xbb1177f2 wall:0 window_ms:600001 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:3 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace
**COVERED** windows:5 entities:8 window_ms:2999998 first_t_ms:71602925 last_t_ms:74002925 covered_by:@LAT96LON20
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-36 windows:5
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-72 windows:5
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-74 windows:3
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-86 windows:2
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-85 windows:2
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-88 windows:1

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52577 stream:0x9f4d711e wall:0 window_ms:60072 n:491
**MOTION** state:still moving_permille:2 dev_mean_mg:3 dev_max_mg:77 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52577 stream:0x9f4d711e wall:0 window_ms:60300 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52458 stream:0x2c7e752b wall:0 window_ms:60000 n:557
**MOTION** state:still moving_permille:3 dev_mean_mg:3 dev_max_mg:88 moving_ms:600
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52458 stream:0x2c7e752b wall:0 window_ms:60134 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52522 stream:0x53ab3420 wall:0 window_ms:60000 n:527
**MOTION** state:still moving_permille:1 dev_mean_mg:4 dev_max_mg:71 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52522 stream:0x53ab3420 wall:0 window_ms:60237 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52459 stream:0xd94c8c52 wall:0 window_ms:60000 n:552
**MOTION** state:still moving_permille:1 dev_mean_mg:2 dev_max_mg:77 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52459 stream:0xd94c8c52 wall:0 window_ms:60053 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:1 removed:16 last_lon:15 t_ms:486674 stream:0xd94c8c52 wall:0 node:0x00000100
**STREAMS-EXPLAINED** n:14 0xd2dacc37 0x531b9866 0x35bbc4c3 0x607ae994 0x342476c4 0x09b8784d 0xd8ca9bd6 0xc74761ed 0x2d4ae0fa 0xffe779bc 0x08739b89 0xd9e1f8b9 0xbb1177f2 0x9f4d711e

---

@LAT95LON28 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:537219 stream:0xd94c8c52 wall:0 window_ms:60000 n:535
**MOTION** state:still moving_permille:1 dev_mean_mg:3 dev_max_mg:78 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:537219 stream:0xd94c8c52 wall:0 window_ms:60019 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xd94c8c52 wall:0 t_ms:819499 node:0x100 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:1 removed:48 last_lon:47 t_ms:830017 stream:0xd94c8c52 wall:0 node:0x00000100

---

@LAT95LON29 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:874772 stream:0xd94c8c52 wall:0 window_ms:60000 n:537
**MOTION** state:still moving_permille:1 dev_mean_mg:3 dev_max_mg:75 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:874772 stream:0xd94c8c52 wall:0 window_ms:60292 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---


---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:2 removed:4 last_lon:3 t_ms:1062595 stream:0xd94c8c52 wall:0 node:0x00000100

---

@LAT95LON30 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1152970 stream:0xd94c8c52 wall:0 window_ms:60000 n:564
**MOTION** state:still moving_permille:1 dev_mean_mg:3 dev_max_mg:78 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1152970 stream:0xd94c8c52 wall:0 window_ms:60017 blocks:6864 rate:16000
**ACOUSTIC** rms_mean:8 rms_max:54 peak:129 transients:0

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1152970 stream:0xd94c8c52 wall:0 window_ms:60035 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1212987 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7020 rate:16000
**ACOUSTIC** rms_mean:7 rms_max:108 peak:430 transients:0

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1272987 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7087 rate:16000
**ACOUSTIC** rms_mean:10 rms_max:108 peak:233 transients:0

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1332987 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7029 rate:16000
**ACOUSTIC** rms_mean:7 rms_max:56 peak:92 transients:0

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1392987 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7064 rate:16000
**ACOUSTIC** rms_mean:8 rms_max:55 peak:80 transients:0

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1452987 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7100 rate:16000
**ACOUSTIC** rms_mean:9 rms_max:200 peak:206 transients:0

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1512987 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7148 rate:16000
**ACOUSTIC** rms_mean:11 rms_max:53 peak:65 transients:0

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1572987 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7090 rate:16000
**ACOUSTIC** rms_mean:9 rms_max:269 peak:282 transients:0

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1632987 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7130 rate:16000
**ACOUSTIC** rms_mean:6 rms_max:26 peak:43 transients:0

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1693012 stream:0xd94c8c52 wall:0 window_ms:60025 blocks:7047 rate:16000
**ACOUSTIC** rms_mean:7 rms_max:36 peak:61 transients:0

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1753012 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7130 rate:16000
**ACOUSTIC** rms_mean:8 rms_max:34 peak:58 transients:0

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1813012 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7097 rate:16000
**ACOUSTIC** rms_mean:8 rms_max:36 peak:77 transients:0

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1873012 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7146 rate:16000
**ACOUSTIC** rms_mean:17 rms_max:109 peak:184 transients:0

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1933047 stream:0xd94c8c52 wall:0 window_ms:60035 blocks:7144 rate:16000
**ACOUSTIC** rms_mean:21 rms_max:121 peak:209 transients:0

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1993047 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7164 rate:16000
**ACOUSTIC** rms_mean:31 rms_max:323 peak:792 transients:0

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2053071 stream:0xd94c8c52 wall:0 window_ms:60024 blocks:7170 rate:16000
**ACOUSTIC** rms_mean:17 rms_max:357 peak:427 transients:0

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2113071 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7059 rate:16000
**ACOUSTIC** rms_mean:9 rms_max:97 peak:162 transients:0

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2173071 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7086 rate:16000
**ACOUSTIC** rms_mean:14 rms_max:193 peak:315 transients:0

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2233071 stream:0xd94c8c52 wall:0 window_ms:60000 blocks:7127 rate:16000
**ACOUSTIC** rms_mean:9 rms_max:95 peak:136 transients:0

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x7aabf338 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON31 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52526 stream:0x7aabf338 wall:0 window_ms:60000 n:503
**MOTION** state:still moving_permille:1 dev_mean_mg:6 dev_max_mg:63 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:52526 stream:0x7aabf338 wall:0 window_ms:60128 blocks:6046 rate:16000
**ACOUSTIC** rms_mean:7 rms_max:44 peak:65 transients:0

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52526 stream:0x7aabf338 wall:0 window_ms:60257 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:112654 stream:0x7aabf338 wall:0 window_ms:60000 blocks:6237 rate:16000
**ACOUSTIC** rms_mean:7 rms_max:33 peak:64 transients:0

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:172654 stream:0x7aabf338 wall:0 window_ms:60000 blocks:6206 rate:16000
**ACOUSTIC** rms_mean:7 rms_max:68 peak:116 transients:0

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:232667 stream:0x7aabf338 wall:0 window_ms:60013 blocks:6244 rate:16000
**ACOUSTIC** rms_mean:10 rms_max:359 peak:703 transients:0

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:292667 stream:0x7aabf338 wall:0 window_ms:60000 blocks:6363 rate:16000
**ACOUSTIC** rms_mean:11 rms_max:1075 peak:1217 transients:2
**TRANSIENT** t_ms:286308 stream:0x7aabf338 wall:0 rms:1075

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:352667 stream:0x7aabf338 wall:0 window_ms:60000 blocks:6380 rate:16000
**ACOUSTIC** rms_mean:8 rms_max:159 peak:187 transients:0

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:412667 stream:0x7aabf338 wall:0 window_ms:60000 blocks:6420 rate:16000
**ACOUSTIC** rms_mean:7 rms_max:29 peak:45 transients:0

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:472667 stream:0x7aabf338 wall:0 window_ms:60000 blocks:6400 rate:16000
**ACOUSTIC** rms_mean:6 rms_max:43 peak:67 transients:0

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:532667 stream:0x7aabf338 wall:0 window_ms:60000 blocks:6256 rate:16000
**ACOUSTIC** rms_mean:7 rms_max:69 peak:110 transients:0

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:592667 stream:0x7aabf338 wall:0 window_ms:60000 blocks:6267 rate:16000
**ACOUSTIC** rms_mean:6 rms_max:78 peak:245 transients:0

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:652667 stream:0x7aabf338 wall:0 window_ms:60000 blocks:6321 rate:16000
**ACOUSTIC** rms_mean:6 rms_max:22 peak:38 transients:0

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:712667 stream:0x7aabf338 wall:0 window_ms:60000 blocks:6312 rate:16000
**ACOUSTIC** rms_mean:11 rms_max:117 peak:165 transients:0

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x3b061427 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON32 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52517 stream:0x3b061427 wall:0 window_ms:60000 n:527
**MOTION** state:still moving_permille:5 dev_mean_mg:7 dev_max_mg:79 moving_ms:700
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:52517 stream:0x3b061427 wall:0 window_ms:60127 blocks:6684 rate:16000
**ACOUSTIC** rms_mean:9 rms_max:397 peak:835 transients:0

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52517 stream:0x3b061427 wall:0 window_ms:60254 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:112644 stream:0x3b061427 wall:0 window_ms:60000 blocks:6539 rate:16000
**ACOUSTIC** rms_mean:8 rms_max:181 peak:277 transients:0

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:172644 stream:0x3b061427 wall:0 window_ms:60000 blocks:6544 rate:16000
**ACOUSTIC** rms_mean:6 rms_max:59 peak:175 transients:0

---

@LAT94LON34 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:232644 stream:0x3b061427 wall:0 window_ms:60000 blocks:6565 rate:16000
**ACOUSTIC** rms_mean:6 rms_max:24 peak:51 transients:0

---

@LAT94LON35 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:292644 stream:0x3b061427 wall:0 window_ms:60000 blocks:6525 rate:16000
**ACOUSTIC** rms_mean:7 rms_max:69 peak:142 transients:0

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x8dd93153 wall:0 t_ms:332152 node:0x100 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT95LON33 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:419217 stream:0x8dd93153 wall:0 window_ms:60000 n:565
**MOTION** state:still moving_permille:1 dev_mean_mg:2 dev_max_mg:67 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON36 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:419217 stream:0x8dd93153 wall:0 window_ms:60041 blocks:7239 rate:16000
**ACOUSTIC** rms_mean:10 rms_max:415 peak:446 transients:0

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:419217 stream:0x8dd93153 wall:0 window_ms:60078 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT94LON37 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:479258 stream:0x8dd93153 wall:0 window_ms:60000 blocks:7416 rate:16000
**ACOUSTIC** rms_mean:17 rms_max:531 peak:2604 transients:0

---

@LAT94LON38 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:539258 stream:0x8dd93153 wall:0 window_ms:60000 blocks:7434 rate:16000
**ACOUSTIC** rms_mean:45 rms_max:234 peak:443 transients:0

---

@LAT94LON39 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:599258 stream:0x8dd93153 wall:0 window_ms:60000 blocks:7416 rate:16000
**ACOUSTIC** rms_mean:28 rms_max:208 peak:329 transients:0

---

@LAT94LON40 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:659258 stream:0x8dd93153 wall:0 window_ms:60000 blocks:7416 rate:16000
**ACOUSTIC** rms_mean:28 rms_max:344 peak:508 transients:0

---

@LAT94LON41 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:719258 stream:0x8dd93153 wall:0 window_ms:60000 blocks:7427 rate:16000
**ACOUSTIC** rms_mean:22 rms_max:183 peak:309 transients:0

---

@LAT94LON42 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:779258 stream:0x8dd93153 wall:0 window_ms:60000 blocks:7423 rate:16000
**ACOUSTIC** rms_mean:22 rms_max:153 peak:269 transients:0

---

@LAT94LON43 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:839258 stream:0x8dd93153 wall:0 window_ms:60000 blocks:7436 rate:16000
**ACOUSTIC** rms_mean:21 rms_max:226 peak:327 transients:0

---

@LAT94LON44 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:899258 stream:0x8dd93153 wall:0 window_ms:60000 blocks:7421 rate:16000
**ACOUSTIC** rms_mean:22 rms_max:172 peak:382 transients:0

---

@LAT94LON45 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:959258 stream:0x8dd93153 wall:0 window_ms:60000 blocks:7418 rate:16000
**ACOUSTIC** rms_mean:21 rms_max:198 peak:300 transients:0

---

@LAT94LON46 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1019258 stream:0x8dd93153 wall:0 window_ms:60000 blocks:7415 rate:16000
**ACOUSTIC** rms_mean:29 rms_max:154 peak:317 transients:0

---

@LAT94LON47 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1079258 stream:0x8dd93153 wall:0 window_ms:60000 blocks:7371 rate:16000
**ACOUSTIC** rms_mean:26 rms_max:205 peak:432 transients:0

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1566903 stream:0x8dd93153 wall:0 window_ms:600921 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:3 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace
**COVERED** windows:1 entities:8 window_ms:546687 first_t_ms:965981 last_t_ms:965981 covered_by:@LAT96LON31
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2166725 stream:0x8dd93153 wall:0 window_ms:599823 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
**CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,0283cce0e689

---

@LAT95LON34 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2219217 stream:0x8dd93153 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:23 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17261 window_ms:1740000 moving_permille:0 dev_mean_mg:7 dev_max_mg:23 moving_ms:0 first_t_ms:479217 last_t_ms:2159217 covered_by:@LAT95LON33

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3966503 stream:0x8dd93153 wall:0 window_ms:599776 entities:1
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:2 ids:f83eb025d3d2,bc102f237ace
**COVERED** windows:2 entities:2 window_ms:1200001 first_t_ms:2766502 last_t_ms:3366726 covered_by:@LAT96LON33
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-42 windows:2
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87 windows:1

---

@LAT95LON35 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4019217 stream:0x8dd93153 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:20 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17261 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:95 moving_ms:200 first_t_ms:2279217 last_t_ms:3959217 covered_by:@LAT95LON34

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5166728 stream:0x8dd93153 wall:0 window_ms:600000 entities:2
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:1 ids:f83eb025d3d2
**COVERED** windows:1 entities:3 window_ms:600226 first_t_ms:4566728 last_t_ms:4566728 covered_by:@LAT96LON34
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1

---

@LAT95LON36 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5819217 stream:0x8dd93153 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:23 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17258 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:196 moving_ms:402 first_t_ms:4079217 last_t_ms:5759217 covered_by:@LAT95LON35

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6366903 stream:0x8dd93153 wall:0 window_ms:600175 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:2 ids:f83eb025d3d2,02c57d2e0f0d
**COVERED** windows:1 entities:2 window_ms:599999 first_t_ms:5766727 last_t_ms:5766727 covered_by:@LAT96LON35
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6966933 stream:0x8dd93153 wall:0 window_ms:600032 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:3 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7566902 stream:0x8dd93153 wall:0 window_ms:599968 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-85
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-87
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b

---

@LAT95LON37 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7619217 stream:0x8dd93153 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:23 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17257 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:34 moving_ms:0 first_t_ms:5879217 last_t_ms:7559217 covered_by:@LAT95LON36

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8166903 stream:0x8dd93153 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,980d67f79619

---

@LAT95LON38 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:9419217 stream:0x8dd93153 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:25 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17258 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:26 moving_ms:0 first_t_ms:7679217 last_t_ms:9359217 covered_by:@LAT95LON37

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9966902 stream:0x8dd93153 wall:0 window_ms:600000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace
**COVERED** windows:2 entities:6 window_ms:1200000 first_t_ms:8766902 last_t_ms:9366902 covered_by:@LAT96LON39
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-45 windows:2
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-76 windows:2
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-82 windows:2
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-83 windows:2
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xb23c7677 wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON39 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52480 stream:0xb23c7677 wall:0 window_ms:60000 n:566
**MOTION** state:still moving_permille:1 dev_mean_mg:8 dev_max_mg:63 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52480 stream:0xb23c7677 wall:0 window_ms:60041 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1199812 stream:0xb23c7677 wall:0 window_ms:600760 entities:1
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:1 ids:f83eb025d3d2
**COVERED** windows:1 entities:4 window_ms:546531 first_t_ms:599052 last_t_ms:599052 covered_by:@LAT96LON41
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1800009 stream:0xb23c7677 wall:0 window_ms:600197 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
**CORE** entities:3 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace

---

@LAT95LON40 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1852480 stream:0xb23c7677 wall:0 window_ms:60000 n:597
**MOTION** state:still moving_permille:0 dev_mean_mg:19 dev_max_mg:33 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17228 window_ms:1740000 moving_permille:0 dev_mean_mg:16 dev_max_mg:96 moving_ms:1198 first_t_ms:112480 last_t_ms:1792480 covered_by:@LAT95LON39

---

@LAT95LON41 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3652480 stream:0xb23c7677 wall:0 window_ms:60000 n:595
**MOTION** state:still moving_permille:0 dev_mean_mg:19 dev_max_mg:31 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17294 window_ms:1740000 moving_permille:0 dev_mean_mg:20 dev_max_mg:56 moving_ms:0 first_t_ms:1912480 last_t_ms:3592480 covered_by:@LAT95LON40

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5400008 stream:0xb23c7677 wall:0 window_ms:600000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:3 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d
**COVERED** windows:5 entities:6 window_ms:3000000 first_t_ms:2400208 last_t_ms:4800009 covered_by:@LAT96LON43
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-40 windows:5
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-73 windows:4
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-78 windows:5
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1

---

@LAT95LON42 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5452480 stream:0xb23c7677 wall:0 window_ms:60000 n:597
**MOTION** state:still moving_permille:0 dev_mean_mg:20 dev_max_mg:31 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17297 window_ms:1740000 moving_permille:0 dev_mean_mg:20 dev_max_mg:37 moving_ms:0 first_t_ms:3712480 last_t_ms:5392480 covered_by:@LAT95LON41

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7200008 stream:0xb23c7677 wall:0 window_ms:600000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
**CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,0283cce0e689
**COVERED** windows:2 entities:6 window_ms:1200000 first_t_ms:6000008 last_t_ms:6600008 covered_by:@LAT96LON44
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-44 windows:2
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-74 windows:2
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-84 windows:2
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-86 windows:2

---

@LAT95LON43 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7252480 stream:0xb23c7677 wall:0 window_ms:60000 n:598
**MOTION** state:still moving_permille:0 dev_mean_mg:19 dev_max_mg:31 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17300 window_ms:1740000 moving_permille:0 dev_mean_mg:20 dev_max_mg:34 moving_ms:0 first_t_ms:5512480 last_t_ms:7192480 covered_by:@LAT95LON42

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x2f68985f wall:0 t_ms:0 node:0x100 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON44 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52478 stream:0x2f68985f wall:0 window_ms:60000 n:566
**MOTION** state:still moving_permille:1 dev_mean_mg:15 dev_max_mg:62 moving_ms:500
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52478 stream:0x2f68985f wall:0 window_ms:60043 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1200219 stream:0x2f68985f wall:0 window_ms:600930 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d
**COVERED** windows:1 entities:6 window_ms:546769 first_t_ms:599290 last_t_ms:599290 covered_by:@LAT96LON46
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1

---

@LAT95LON45 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1852478 stream:0x2f68985f wall:0 window_ms:60000 n:598
**MOTION** state:still moving_permille:0 dev_mean_mg:27 dev_max_mg:39 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17296 window_ms:1740000 moving_permille:0 dev_mean_mg:23 dev_max_mg:42 moving_ms:0 first_t_ms:112478 last_t_ms:1792478 covered_by:@LAT95LON44

---

@LAT95LON46 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3652478 stream:0x2f68985f wall:0 window_ms:60000 n:597
**MOTION** state:still moving_permille:0 dev_mean_mg:28 dev_max_mg:42 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17287 window_ms:1740000 moving_permille:0 dev_mean_mg:27 dev_max_mg:42 moving_ms:0 first_t_ms:1912478 last_t_ms:3592478 covered_by:@LAT95LON45

---

@LAT95LON47 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5452478 stream:0x2f68985f wall:0 window_ms:60000 n:596
**MOTION** state:still moving_permille:0 dev_mean_mg:27 dev_max_mg:40 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:17304 window_ms:1740000 moving_permille:0 dev_mean_mg:28 dev_max_mg:45 moving_ms:0 first_t_ms:3712478 last_t_ms:5392478 covered_by:@LAT95LON46

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
