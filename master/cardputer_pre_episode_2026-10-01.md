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
lane_classes:
  # TTDB-RFC-0010 §7.1. @LAT101 is the SOCIAL field — the fleet's first FIELD lane
  # (decay-on-read, reclaim-lowest, no prune path). Absent this block every lane is
  # EVIDENCE, which is the fail-safe direction, so an un-reflashed filesystem is safe.
  evidence: [0, 91, 92, 93, 94, 95, 96, 97]
  provenance: [90, 98, 99, 100]
  field: [101]
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

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x4a194eda wall:0 t_ms:26584234 node:0x300 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:48 last_ms:59616
t_ms:26647619 stream:0x4a194eda wall:0

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26647619 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-51 rssi_med:-46 rssi_max:-42

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:26647619 stream:0x4a194eda wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:26647619 stream:0x4a194eda wall:0 window_ms:60000 n:972
**MOTION** state:still moving_permille:0 dev_mean_mg:6 dev_max_mg:10 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:26647619 stream:0x4a194eda wall:0 window_ms:60000 blocks:3641 rate:8000
**ACOUSTIC** rms_mean:82 rms_max:645 peak:1057 transients:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26713469 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-48 rssi_med:-46 rssi_max:-40

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:26713469 stream:0x4a194eda wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:26713469 stream:0x4a194eda wall:0 window_ms:60000 n:334
**MOTION** state:still moving_permille:0 dev_mean_mg:6 dev_max_mg:9 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:26713469 stream:0x4a194eda wall:0 window_ms:60000 blocks:1248 rate:8000
**ACOUSTIC** rms_mean:89 rms_max:296 peak:757 transients:0

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26773469 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-49 rssi_med:-45 rssi_max:-43

---

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON2,senses@LAT0LON0

**OUTCOME** t_ms:26773469 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON1+0 observed_in:@LAT97LON2 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-46 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-45 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:26773469 stream:0x4a194eda wall:0 window_ms:60000 blocks:2740 rate:8000
**ACOUSTIC** rms_mean:91 rms_max:1715 peak:4894 transients:2
**TRANSIENT** t_ms:26738922 stream:0x4a194eda wall:0 rms:1715

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26833469 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-46 rssi_med:-44 rssi_max:-43

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:26833469 stream:0x4a194eda wall:0 window_ms:60000 blocks:2990 rate:8000
**ACOUSTIC** rms_mean:81 rms_max:319 peak:702 transients:0

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26893469 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-45 rssi_med:-44 rssi_max:-43

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:26893469 stream:0x4a194eda wall:0 window_ms:60000 blocks:2620 rate:8000
**ACOUSTIC** rms_mean:87 rms_max:255 peak:532 transients:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26953469 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-50 rssi_med:-45 rssi_max:-43

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:26953469 stream:0x4a194eda wall:0 window_ms:60000 blocks:3112 rate:8000
**ACOUSTIC** rms_mean:96 rms_max:1023 peak:3853 transients:1
**TRANSIENT** t_ms:26915975 stream:0x4a194eda wall:0 rms:1023

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27013541 stream:0x4a194eda wall:0 window_ms:60072
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-48 rssi_med:-44 rssi_max:-42

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27013541 stream:0x4a194eda wall:0 window_ms:60072 blocks:773 rate:8000
**ACOUSTIC** rms_mean:108 rms_max:2428 peak:6746 transients:6
**TRANSIENT** t_ms:26969275 stream:0x4a194eda wall:0 rms:2428

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27075506 stream:0x4a194eda wall:0 window_ms:61965
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-47 rssi_med:-45 rssi_max:-43

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27075506 stream:0x4a194eda wall:0 window_ms:61965 blocks:1256 rate:8000
**ACOUSTIC** rms_mean:94 rms_max:1387 peak:3958 transients:2
**TRANSIENT** t_ms:27062045 stream:0x4a194eda wall:0 rms:1387

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27135506 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-50 rssi_med:-47 rssi_max:-44

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27135506 stream:0x4a194eda wall:0 window_ms:60000 blocks:611 rate:8000
**ACOUSTIC** rms_mean:125 rms_max:274 peak:612 transients:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27195506 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-48 rssi_med:-47 rssi_max:-43

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27195506 stream:0x4a194eda wall:0 window_ms:60000 blocks:2916 rate:8000
**ACOUSTIC** rms_mean:103 rms_max:1323 peak:4119 transients:2
**TRANSIENT** t_ms:27164192 stream:0x4a194eda wall:0 rms:1323

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27255506 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-49 rssi_med:-46 rssi_max:-41

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27255506 stream:0x4a194eda wall:0 window_ms:60000 blocks:2900 rate:8000
**ACOUSTIC** rms_mean:92 rms_max:582 peak:2101 transients:0

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27315506 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-49 rssi_med:-44 rssi_max:-41

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27315506 stream:0x4a194eda wall:0 window_ms:60000 blocks:2787 rate:8000
**ACOUSTIC** rms_mean:94 rms_max:1688 peak:5900 transients:2
**TRANSIENT** t_ms:27275382 stream:0x4a194eda wall:0 rms:1688

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27375506 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-48 rssi_med:-44 rssi_max:-43

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27375506 stream:0x4a194eda wall:0 window_ms:60000 blocks:3020 rate:8000
**ACOUSTIC** rms_mean:97 rms_max:1966 peak:8757 transients:2
**TRANSIENT** t_ms:27344638 stream:0x4a194eda wall:0 rms:1966

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27435593 stream:0x4a194eda wall:0 window_ms:60087
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-49 rssi_med:-47 rssi_max:-46

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27435593 stream:0x4a194eda wall:0 window_ms:60087 blocks:1071 rate:8000
**ACOUSTIC** rms_mean:124 rms_max:2802 peak:3190 transients:3
**TRANSIENT** t_ms:27393773 stream:0x4a194eda wall:0 rms:2802

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27495594 stream:0x4a194eda wall:0 window_ms:60001
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-48 rssi_med:-47 rssi_max:-46

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27495594 stream:0x4a194eda wall:0 window_ms:60001 blocks:1556 rate:8000
**ACOUSTIC** rms_mean:149 rms_max:1656 peak:1882 transients:1
**TRANSIENT** t_ms:27477493 stream:0x4a194eda wall:0 rms:1421

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27557534 stream:0x4a194eda wall:0 window_ms:61940
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-51 rssi_med:-47 rssi_max:-46

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27557534 stream:0x4a194eda wall:0 window_ms:61940 blocks:1183 rate:8000
**ACOUSTIC** rms_mean:126 rms_max:8164 peak:32767 transients:4
**TRANSIENT** t_ms:27513953 stream:0x4a194eda wall:0 rms:8164

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27617534 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-52 rssi_med:-50 rssi_max:-47

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27617534 stream:0x4a194eda wall:0 window_ms:60000 blocks:1555 rate:8000
**ACOUSTIC** rms_mean:171 rms_max:943 peak:1644 transients:0

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27677592 stream:0x4a194eda wall:0 window_ms:60058
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-59 rssi_med:-47 rssi_max:-42

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27677592 stream:0x4a194eda wall:0 window_ms:60058 blocks:686 rate:8000
**ACOUSTIC** rms_mean:233 rms_max:4753 peak:18613 transients:5
**TRANSIENT** t_ms:27625894 stream:0x4a194eda wall:0 rms:4753

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27739597 stream:0x4a194eda wall:0 window_ms:62005
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-66 rssi_med:-48 rssi_max:-46

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27739597 stream:0x4a194eda wall:0 window_ms:62005 blocks:677 rate:8000
**ACOUSTIC** rms_mean:180 rms_max:623 peak:1336 transients:0

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27801474 stream:0x4a194eda wall:0 window_ms:61877
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-55 rssi_med:-47 rssi_max:-46

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27801474 stream:0x4a194eda wall:0 window_ms:61877 blocks:1037 rate:8000
**ACOUSTIC** rms_mean:221 rms_max:1598 peak:4520 transients:4
**TRANSIENT** t_ms:27758115 stream:0x4a194eda wall:0 rms:1598

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27861474 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-52 rssi_med:-47 rssi_max:-44

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27861474 stream:0x4a194eda wall:0 window_ms:60000 blocks:1541 rate:8000
**ACOUSTIC** rms_mean:393 rms_max:1338 peak:2021 transients:0

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27970043 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-69 rssi_med:-52 rssi_max:-48

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:27970043 stream:0x4a194eda wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:27970043 stream:0x4a194eda wall:0 window_ms:60000 n:966
**MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:18 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:27970043 stream:0x4a194eda wall:0 window_ms:60000 blocks:3616 rate:8000
**ACOUSTIC** rms_mean:345 rms_max:4263 peak:25796 transients:5
**TRANSIENT** t_ms:27920043 stream:0x4a194eda wall:0 rms:4263

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28030043 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-51 rssi_med:-49 rssi_max:-46

---

@LAT92LON1 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON22,senses@LAT0LON0

**OUTCOME** t_ms:28030043 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON2+0 observed_in:@LAT97LON22 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-52 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-49 delta:3 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28030043 stream:0x4a194eda wall:0 window_ms:60000 blocks:3739 rate:8000
**ACOUSTIC** rms_mean:438 rms_max:8108 peak:20550 transients:6
**TRANSIENT** t_ms:28019703 stream:0x4a194eda wall:0 rms:8108

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28090044 stream:0x4a194eda wall:0 window_ms:60001
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-69 rssi_med:-48 rssi_max:-45

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28090044 stream:0x4a194eda wall:0 window_ms:60001 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:449 rms_max:1770 peak:2745 transients:4
**TRANSIENT** t_ms:28047404 stream:0x4a194eda wall:0 rms:1293

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28150044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-62 rssi_med:-49 rssi_max:-44

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28150044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3711 rate:8000
**ACOUSTIC** rms_mean:481 rms_max:3353 peak:8372 transients:7
**TRANSIENT** t_ms:28106709 stream:0x4a194eda wall:0 rms:3353

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28210044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-56 rssi_med:-49 rssi_max:-44

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28210044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3740 rate:8000
**ACOUSTIC** rms_mean:315 rms_max:1948 peak:5543 transients:5
**TRANSIENT** t_ms:28183661 stream:0x4a194eda wall:0 rms:1948

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28270044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-61 rssi_med:-49 rssi_max:-47

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28270044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3743 rate:8000
**ACOUSTIC** rms_mean:228 rms_max:918 peak:2684 transients:0

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28330044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-62 rssi_med:-49 rssi_max:-47

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28330044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3744 rate:8000
**ACOUSTIC** rms_mean:250 rms_max:1219 peak:3922 transients:0

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28390044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-59 rssi_med:-50 rssi_max:-47

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28390044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:234 rms_max:4588 peak:17026 transients:4
**TRANSIENT** t_ms:28384705 stream:0x4a194eda wall:0 rms:4588

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28450044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-53 rssi_med:-48 rssi_max:-46

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28450044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3673 rate:8000
**ACOUSTIC** rms_mean:218 rms_max:1133 peak:2146 transients:0

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28510044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-55 rssi_med:-47 rssi_max:-44

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28510044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3651 rate:8000
**ACOUSTIC** rms_mean:209 rms_max:2878 peak:10388 transients:2
**TRANSIENT** t_ms:28501148 stream:0x4a194eda wall:0 rms:2878

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28570044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-50 rssi_med:-45 rssi_max:-43

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28570044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3643 rate:8000
**ACOUSTIC** rms_mean:215 rms_max:750 peak:1657 transients:0

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28630044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-56 rssi_med:-46 rssi_max:-43

---

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28630044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3650 rate:8000
**ACOUSTIC** rms_mean:218 rms_max:2054 peak:2656 transients:2
**TRANSIENT** t_ms:28611654 stream:0x4a194eda wall:0 rms:1780

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28690044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-47 rssi_med:-46 rssi_max:-46

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28690044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3642 rate:8000
**ACOUSTIC** rms_mean:234 rms_max:665 peak:2134 transients:0

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28750044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-47 rssi_med:-46 rssi_max:-45

---

@LAT94LON34 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28750044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3641 rate:8000
**ACOUSTIC** rms_mean:222 rms_max:4125 peak:5246 transients:6
**TRANSIENT** t_ms:28718069 stream:0x4a194eda wall:0 rms:3589

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28810044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-52 rssi_med:-47 rssi_max:-45

---

@LAT94LON35 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28810044 stream:0x4a194eda wall:0 window_ms:60000 blocks:3632 rate:8000
**ACOUSTIC** rms_mean:239 rms_max:2696 peak:3472 transients:5
**TRANSIENT** t_ms:28804546 stream:0x4a194eda wall:0 rms:1523

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28872577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-51 rssi_med:-48 rssi_max:-44

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:28872577 stream:0x4a194eda wall:0 window_ms:60000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:28872577 stream:0x4a194eda wall:0 window_ms:60000 n:957
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON36 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28872577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3585 rate:8000
**ACOUSTIC** rms_mean:218 rms_max:963 peak:2936 transients:2
**TRANSIENT** t_ms:28829325 stream:0x4a194eda wall:0 rms:963

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28932577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-53 rssi_med:-49 rssi_max:-45

---

@LAT92LON2 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON37,senses@LAT0LON0

**OUTCOME** t_ms:28932577 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON3+0 observed_in:@LAT97LON37 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-49 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON37 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28932577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3731 rate:8000
**ACOUSTIC** rms_mean:235 rms_max:720 peak:1656 transients:0

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28992577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-60 rssi_med:-48 rssi_max:-44

---

@LAT94LON38 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:28992577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:174 rms_max:864 peak:2448 transients:0

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29052577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-63 rssi_med:-49 rssi_max:-45

---

@LAT94LON39 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:29052577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3718 rate:8000
**ACOUSTIC** rms_mean:153 rms_max:670 peak:1893 transients:0

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29112577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-56 rssi_med:-49 rssi_max:-44

---

@LAT94LON40 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:29112577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:155 rms_max:478 peak:1065 transients:0

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29172577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-54 rssi_med:-47 rssi_max:-44

---

@LAT94LON41 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:29172577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3742 rate:8000
**ACOUSTIC** rms_mean:169 rms_max:871 peak:1789 transients:0

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29232577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-50 rssi_med:-47 rssi_max:-44

---

@LAT94LON42 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:29232577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:124 rms_max:1676 peak:3144 transients:3
**TRANSIENT** t_ms:29217846 stream:0x4a194eda wall:0 rms:1676

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29292577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-48 rssi_med:-47 rssi_max:-45

---

@LAT94LON43 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:29292577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3745 rate:8000
**ACOUSTIC** rms_mean:155 rms_max:1516 peak:2337 transients:2
**TRANSIENT** t_ms:29284260 stream:0x4a194eda wall:0 rms:1516

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29352577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-47 rssi_med:-46 rssi_max:-45

---

@LAT94LON44 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:29352577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3742 rate:8000
**ACOUSTIC** rms_mean:311 rms_max:999 peak:2032 transients:0

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29412577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-50 rssi_med:-46 rssi_max:-45

---

@LAT94LON45 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:29412577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:345 rms_max:1348 peak:2660 transients:2
**TRANSIENT** t_ms:29405186 stream:0x4a194eda wall:0 rms:1058

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29472577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-64 rssi_med:-51 rssi_max:-47

---

@LAT94LON46 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:29472577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3740 rate:8000
**ACOUSTIC** rms_mean:234 rms_max:1688 peak:2545 transients:3
**TRANSIENT** t_ms:29451182 stream:0x4a194eda wall:0 rms:1688

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29532577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-62 rssi_med:-49 rssi_max:-46

---

@LAT94LON47 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:29532577 stream:0x4a194eda wall:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:267 rms_max:944 peak:1920 transients:1
**TRANSIENT** t_ms:29490410 stream:0x4a194eda wall:0 rms:944

---

@LAT91LON0 | sid:ab8f77ba | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:134
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000100 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:3 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:3 method:sequential_fold_from_baseline

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xce6b6750 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:51813 stream:0xce6b6750 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-22
**ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
**ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51813 stream:0xce6b6750 wall:0 window_ms:60000 n:949
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:39 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30
