# Cardputer Fleet Map TTDB (semantic positioning SP6)

The mesh-facing globe: one record per fleet node at its believed position, the map the
mesh draws of itself. The four POSITION records below are real beliefs, carried over
from the fleet's last embedding (companion.py positions -> fleetmap). The Cardputer's
own record is **not** a belief — it has no proximity evidence yet, and says so.

Regenerate this file from live beliefs with:

    python orchestrator/companion.py fleetmap --out firmware/cardputer_console/data/ttdb.md

then flash it with `scripts/Upload-Cardputer-FS.ps1`.

```mmpdb
db_id: cardputer-console-001
db_name: Cardputer ADV Console - Fleet Map
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: cardputer-console
  role: handheld-console-sense-organ
  perspective: operator
  scope: fleet-command
  senses:
    - "link rssi (esp-now + ble) -> @LAT97"
    - "wifi entity co-occurrence -> @LAT96"
    - "motion, from a BMI270 accelerometer -> @LAT95"
    - "sound, from an ES8311 codec + MEMS microphone -> @LAT94"
  globe:
    frame: mesh-topology
    origin: "@LAT0LON0"
    mapping: "each record is a fleet node at its believed position; the map the mesh draws of itself (companion.py fleetmap from positions.md + proximity.md)"
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

@LAT0LON16 | created:1750000000 | updated:1750000000 | relates:espnow@LAT0LON0,espnow@LAT35LON7,espnow@LAT32LON34

**POSITION** node:k10_1
name: K10
x_m: 16.25  y_m: -0.00
sigma_m: 51.28   conf: 0.58
link V4-A: espnow 16.3m conf 0.80
link V4-B: espnow 34.1m conf 0.80
link T-Deck: espnow 38.4m conf 0.80

---

@LAT32LON34 | created:1750000000 | updated:1750000000 | relates:espnow@LAT0LON0,espnow@LAT35LON7,espnow@LAT0LON16

**POSITION** node:tdeck_1
name: T-Deck
x_m: 33.61  y_m: 31.87
sigma_m: 61.96   conf: 0.55
link V4-A: espnow 41.8m conf 0.75
link V4-B: espnow 27.2m conf 0.78
link K10: espnow 38.4m conf 0.80

---

@LAT0LON0 | created:1750000000 | updated:1750000000 | relates:espnow@LAT35LON7,espnow@LAT0LON16,espnow@LAT32LON34

**POSITION** node:v4a_bridge
name: V4-A
x_m: 0.00  y_m: -0.00
sigma_m: 57.72   conf: 0.55
link V4-B: espnow 37.1m conf 0.78
link K10: espnow 16.3m conf 0.80
link T-Deck: espnow 41.8m conf 0.75

---

@LAT35LON7 | created:1750000000 | updated:1750000000 | relates:espnow@LAT0LON0,espnow@LAT0LON16,espnow@LAT32LON34

**POSITION** node:v4b_relay
name: V4-B
x_m: 6.83  y_m: 34.78
sigma_m: 53.15   conf: 0.56
link V4-A: espnow 37.1m conf 0.78
link K10: espnow 34.1m conf 0.80
link T-Deck: espnow 27.2m conf 0.78

---

@LAT-20LON-20 | created:1750000000 | updated:1750000000 | relates:espnow@LAT0LON0

**POSITION-UNKNOWN** node:cardputer_1
name: Card
conf: 0.00
This node has just joined the fleet and has no position belief. It has not yet appeared
in a proximity fuse, so it has no x_m/y_m and no sigma. The coordinate above is a
PARKING SPOT so the record is navigable on the globe — it is not a claim about where
this node is. It becomes a real POSITION record the first time the fleet runs
`proximity` -> `positions` -> `fleetmap` with this node's @LAT97 windows in the pull.

---

@LAT99LON0 | created:1785774270 | updated:1785774270 | relates:logs@LAT0LON0

**SYNC** id:8 t_ms:1785774270662 recv_ms:4040166 offset_ms:1785770230496

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:418673 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:1 removed:48 last_lon:47 t_ms:1683303 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:1 removed:48 last_lon:47 t_ms:1688500 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:1 removed:16 last_lon:15 t_ms:1438863 stream:0xe7384824 wall:0 node:0x00000300
**STREAMS-EXPLAINED** n:12 0x0ad62c42 0xfc36a38c 0x10578c80 0x26a1b82d 0x44574814 0x59fb8ce8 0x450f0e1c 0x2434b81f 0xbdc62024 0x1428c702 0xa315ec7d 0x9c462b30

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xe7384824 wall:0 t_ms:1447466 node:0x300 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---


---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xaf869fce wall:0 t_ms:7185 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x161e88ac wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x5f6eb232 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x41ba1242 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x67ec2883 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x3ab84e5a wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---


---


---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbe6d9616 wall:0 t_ms:4001 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---


---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbe6d9616 wall:0 t_ms:5743568 node:0x300 from:0x10
**REMAP** prev_stream:0x9feeb581 prev_t_ms:7042 offset_ms:5736526 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:2 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON5 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:2 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON6 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON7 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:2 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---


---


---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbe6d9616 wall:0 t_ms:6944002 node:0x300 from:0x10
**REMAP** prev_stream:0x36d6dcee prev_t_ms:5710 offset_ms:6938292 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---


---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7084422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-64 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:29 rssi_min:-36 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-42 rssi_med:-40 rssi_max:-39

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7084422 stream:0xbe6d9616 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7084422 stream:0xbe6d9616 wall:0 window_ms:60000 n:280
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:11 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7084422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:1044 rate:8000
**ACOUSTIC** rms_mean:131 rms_max:305 peak:652 transients:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7144422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-60 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-41 rssi_med:-40 rssi_max:-40

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7144422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2844 rate:8000
**ACOUSTIC** rms_mean:123 rms_max:361 peak:852 transients:0

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7204422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-41 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-79 rssi_med:-56 rssi_max:-55

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7204422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2991 rate:8000
**ACOUSTIC** rms_mean:203 rms_max:20902 peak:32768 transients:7
**TRANSIENT** t_ms:7181840 stream:0xbe6d9616 wall:0 rms:20902

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7264422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-60 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-41 rssi_med:-40 rssi_max:-40

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7264422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2859 rate:8000
**ACOUSTIC** rms_mean:122 rms_max:1181 peak:1892 transients:1
**TRANSIENT** t_ms:7242525 stream:0xbe6d9616 wall:0 rms:1181

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7324422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-60 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-41 rssi_med:-40 rssi_max:-39

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7324422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3115 rate:8000
**ACOUSTIC** rms_mean:124 rms_max:611 peak:1063 transients:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7384422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-79 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-41 rssi_med:-40 rssi_max:-40

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7384422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3114 rate:8000
**ACOUSTIC** rms_mean:149 rms_max:1546 peak:1857 transients:3
**TRANSIENT** t_ms:7376333 stream:0xbe6d9616 wall:0 rms:1261

---


---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7537235 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-61 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-41 rssi_med:-40 rssi_max:-40

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7537235 stream:0xbe6d9616 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7537235 stream:0xbe6d9616 wall:0 window_ms:60000 n:274
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7537235 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:1025 rate:8000
**ACOUSTIC** rms_mean:108 rms_max:212 peak:461 transients:0

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7597235 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-42 rssi_med:-40 rssi_max:-40

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7597235 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2858 rate:8000
**ACOUSTIC** rms_mean:131 rms_max:1357 peak:2553 transients:0

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7657235 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-72 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-37 rssi_med:-36 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-41 rssi_med:-40 rssi_max:-39

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7657235 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2988 rate:8000
**ACOUSTIC** rms_mean:135 rms_max:465 peak:785 transients:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7717235 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-61 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-41 rssi_med:-40 rssi_max:-40

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7717235 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2858 rate:8000
**ACOUSTIC** rms_mean:127 rms_max:864 peak:1642 transients:0

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7777235 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-61 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-42 rssi_med:-40 rssi_max:-40

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7777235 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3114 rate:8000
**ACOUSTIC** rms_mean:118 rms_max:381 peak:1144 transients:0

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7837235 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-40 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-61 rssi_med:-57 rssi_max:-55

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7837235 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3117 rate:8000
**ACOUSTIC** rms_mean:117 rms_max:328 peak:665 transients:0

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7897235 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-61 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-40 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-36 rssi_med:-35 rssi_max:-35

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7897235 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2977 rate:8000
**ACOUSTIC** rms_mean:120 rms_max:278 peak:641 transients:0

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7957235 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-61 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-41 rssi_med:-40 rssi_max:-40

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7957235 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3113 rate:8000
**ACOUSTIC** rms_mean:120 rms_max:281 peak:550 transients:0

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8017235 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-41 rssi_med:-40 rssi_max:-40
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-61 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-36 rssi_med:-35 rssi_max:-35

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8017235 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3116 rate:8000
**ACOUSTIC** rms_mean:122 rms_max:291 peak:640 transients:0

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8077235 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-60 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-41 rssi_med:-40 rssi_max:-40

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8077235 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2855 rate:8000
**ACOUSTIC** rms_mean:135 rms_max:618 peak:1165 transients:0

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8123599 stream:0xbe6d9616 wall:0 window_ms:586364 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8137235 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-41 rssi_med:-39 rssi_max:-36
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-62 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-37 rssi_med:-35 rssi_max:-34

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8137235 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2860 rate:8000
**ACOUSTIC** rms_mean:170 rms_max:14159 peak:32768 transients:8
**TRANSIENT** t_ms:8121344 stream:0xbe6d9616 wall:0 rms:14159

---

@LAT100LON8 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:92 gen:1 removed:24 last_lon:23 t_ms:8137821 stream:0xbe6d9616 wall:0 node:0x00000300
**OUTCOMES-CARRIED** records:24 windows_max:24 beliefs:8 met:167 violated:14 unobserved:2 baseline_conf:128 rule:+2/-16
**BELIEF-AT-BOUNDARY** peer:0x00000010 proto:ble conf:176 sal:0 met:24 violated:0 unobserved:0 max_streak:0 contradiction:0
**BELIEF-AT-BOUNDARY** peer:0x00000012 proto:ble conf:176 sal:0 met:24 violated:0 unobserved:0 max_streak:0 contradiction:0
**BELIEF-AT-BOUNDARY** peer:0x00000011 proto:ble conf:176 sal:0 met:24 violated:0 unobserved:0 max_streak:0 contradiction:0
**BELIEF-AT-BOUNDARY** peer:0x00000011 proto:espnow conf:176 sal:0 met:24 violated:0 unobserved:0 max_streak:0 contradiction:0
**BELIEF-AT-BOUNDARY** peer:0x00000012 proto:espnow conf:158 sal:8 met:23 violated:1 unobserved:0 max_streak:1 contradiction:0
**BELIEF-AT-BOUNDARY** peer:0x00000200 proto:ble conf:64 sal:40 met:8 violated:5 unobserved:2 max_streak:2 contradiction:1
**BELIEF-AT-BOUNDARY** peer:0x00000200 proto:espnow conf:50 sal:56 met:17 violated:7 unobserved:0 max_streak:2 contradiction:1
**BELIEF-AT-BOUNDARY** peer:0x00000010 proto:espnow conf:158 sal:8 met:23 violated:1 unobserved:0 max_streak:1 contradiction:0

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8200943 stream:0xbe6d9616 wall:0 window_ms:62001
**LINK** peer:0x00000100 proto:espnow n:30 rssi_min:-38 rssi_med:-37 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-62 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-39 rssi_med:-38 rssi_max:-36

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8200943 stream:0xbe6d9616 wall:0 window_ms:62001 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:8200943 stream:0xbe6d9616 wall:0 window_ms:62001 n:639
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8200943 stream:0xbe6d9616 wall:0 window_ms:62001 blocks:2390 rate:8000
**ACOUSTIC** rms_mean:139 rms_max:596 peak:1619 transients:0

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8260961 stream:0xbe6d9616 wall:0 window_ms:60018
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-38 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-40 rssi_med:-39 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-60 rssi_med:-56 rssi_max:-54

---

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON18,senses@LAT0LON0

**OUTCOME** t_ms:8260961 stream:0xbe6d9616 wall:0 node:0x300 acting:@LAT95LON2+0 observed_in:@LAT97LON18 band_dbm:6 met:3 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-37 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-37 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-56 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-38 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8260961 stream:0xbe6d9616 wall:0 window_ms:60018 blocks:2860 rate:8000
**ACOUSTIC** rms_mean:141 rms_max:693 peak:2267 transients:0

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8320961 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-39 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-56 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-38 rssi_med:-37 rssi_max:-37

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8320961 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2983 rate:8000
**ACOUSTIC** rms_mean:144 rms_max:592 peak:964 transients:0

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8380961 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-39 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-38 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-60 rssi_med:-55 rssi_max:-54

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8380961 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2332 rate:8000
**ACOUSTIC** rms_mean:147 rms_max:341 peak:722 transients:0

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8440965 stream:0xbe6d9616 wall:0 window_ms:60004
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-39 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-38 rssi_med:-37 rssi_max:-37

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8440965 stream:0xbe6d9616 wall:0 window_ms:60004 blocks:3111 rate:8000
**ACOUSTIC** rms_mean:124 rms_max:1034 peak:1626 transients:1
**TRANSIENT** t_ms:8403213 stream:0xbe6d9616 wall:0 rms:948

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8501012 stream:0xbe6d9616 wall:0 window_ms:60047
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8501012 stream:0xbe6d9616 wall:0 window_ms:60047 blocks:3116 rate:8000
**ACOUSTIC** rms_mean:117 rms_max:219 peak:534 transients:0

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8561012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8561012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2989 rate:8000
**ACOUSTIC** rms_mean:114 rms_max:200 peak:541 transients:0

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8621012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-60 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8621012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3116 rate:8000
**ACOUSTIC** rms_mean:120 rms_max:316 peak:626 transients:0

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8681012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-38 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-41 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-60 rssi_med:-55 rssi_max:-54

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8681012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2989 rate:8000
**ACOUSTIC** rms_mean:119 rms_max:215 peak:558 transients:0

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8741012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-60 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8741012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2990 rate:8000
**ACOUSTIC** rms_mean:119 rms_max:238 peak:548 transients:0

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8763466 stream:0xbe6d9616 wall:0 window_ms:562523 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8801012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-60 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-40 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-38 rssi_med:-37 rssi_max:-37

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8801012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2867 rate:8000
**ACOUSTIC** rms_mean:124 rms_max:322 peak:647 transients:0

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8861012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-38 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8861012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3103 rate:8000
**ACOUSTIC** rms_mean:121 rms_max:264 peak:630 transients:0

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8921012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-61 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-38 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8921012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2989 rate:8000
**ACOUSTIC** rms_mean:117 rms_max:259 peak:553 transients:0

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:8981012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-38 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-60 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-39 rssi_med:-39 rssi_max:-38

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:8981012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3118 rate:8000
**ACOUSTIC** rms_mean:119 rms_max:231 peak:550 transients:0

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9041012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-82 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-38 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9041012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2993 rate:8000
**ACOUSTIC** rms_mean:142 rms_max:974 peak:1767 transients:0

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9101012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-40 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-56 rssi_max:-54

---

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9101012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2992 rate:8000
**ACOUSTIC** rms_mean:128 rms_max:478 peak:895 transients:0

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9161012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-56 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-39 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-38 rssi_med:-37 rssi_max:-37

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9161012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3117 rate:8000
**ACOUSTIC** rms_mean:145 rms_max:757 peak:1838 transients:0

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9221012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:71 rssi_min:-80 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON34 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9221012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3114 rate:8000
**ACOUSTIC** rms_mean:126 rms_max:379 peak:805 transients:0

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9281012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-79 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON35 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9281012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2987 rate:8000
**ACOUSTIC** rms_mean:124 rms_max:462 peak:937 transients:0

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9341012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-60 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON36 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9341012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3103 rate:8000
**ACOUSTIC** rms_mean:116 rms_max:256 peak:571 transients:0

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9363465 stream:0xbe6d9616 wall:0 window_ms:599999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9401012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:32 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-40 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-83 rssi_med:-56 rssi_max:-54

---

@LAT94LON37 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9401012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2737 rate:8000
**ACOUSTIC** rms_mean:115 rms_max:220 peak:569 transients:0

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9461012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-40 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-60 rssi_med:-56 rssi_max:-54

---

@LAT94LON38 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9461012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2991 rate:8000
**ACOUSTIC** rms_mean:114 rms_max:238 peak:610 transients:0

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9521012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-79 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-40 rssi_med:-39 rssi_max:-39

---

@LAT94LON39 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9521012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3114 rate:8000
**ACOUSTIC** rms_mean:116 rms_max:358 peak:613 transients:0

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9581012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-40 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-79 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-39 rssi_med:-37 rssi_max:-37

---

@LAT94LON40 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9581012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3113 rate:8000
**ACOUSTIC** rms_mean:149 rms_max:1102 peak:1715 transients:1
**TRANSIENT** t_ms:9576405 stream:0xbe6d9616 wall:0 rms:1102

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9641012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-79 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-40 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-38 rssi_med:-37 rssi_max:-37

---

@LAT94LON41 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9641012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2992 rate:8000
**ACOUSTIC** rms_mean:138 rms_max:323 peak:671 transients:0

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9701012 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-82 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-41 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-38 rssi_med:-37 rssi_max:-37

---

@LAT94LON42 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9701012 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3113 rate:8000
**ACOUSTIC** rms_mean:176 rms_max:596 peak:1028 transients:0

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9761121 stream:0xbe6d9616 wall:0 window_ms:60109
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-38 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-80 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON43 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9761121 stream:0xbe6d9616 wall:0 window_ms:60109 blocks:2987 rate:8000
**ACOUSTIC** rms_mean:143 rms_max:504 peak:903 transients:0

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9821123 stream:0xbe6d9616 wall:0 window_ms:60002
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-60 rssi_med:-55 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-39 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-40 rssi_med:-39 rssi_max:-38

---

@LAT94LON44 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9821123 stream:0xbe6d9616 wall:0 window_ms:60002 blocks:2878 rate:8000
**ACOUSTIC** rms_mean:115 rms_max:240 peak:592 transients:0

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9881123 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-39 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-41 rssi_med:-39 rssi_max:-38

---

@LAT94LON45 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9881123 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3034 rate:8000
**ACOUSTIC** rms_mean:115 rms_max:232 peak:595 transients:0

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:9941124 stream:0xbe6d9616 wall:0 window_ms:60001
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-39 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-56 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-39 rssi_med:-37 rssi_max:-37

---

@LAT94LON46 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:9941124 stream:0xbe6d9616 wall:0 window_ms:60001 blocks:3041 rate:8000
**ACOUSTIC** rms_mean:115 rms_max:216 peak:557 transients:0

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9963509 stream:0xbe6d9616 wall:0 window_ms:600044 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT91LON0 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:130
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000100 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:1 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:1 method:sequential_fold_from_baseline

---

@LAT91LON1 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:130
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:1 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:1 method:sequential_fold_from_baseline

---

@LAT91LON2 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:130
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:1 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:1 method:sequential_fold_from_baseline

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:10061799 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-38 rssi_med:-37 rssi_max:-37
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-39 rssi_med:-39 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:49 rssi_min:-82 rssi_med:-56 rssi_max:-53

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10061799 stream:0xbe6d9616 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:10061799 stream:0xbe6d9616 wall:0 window_ms:60000 n:950
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON47 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:10061799 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3558 rate:8000
**ACOUSTIC** rms_mean:274 rms_max:574 peak:1158 transients:0

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10613553 stream:0xbe6d9616 wall:0 window_ms:551754 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-95

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11213553 stream:0xbe6d9616 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
