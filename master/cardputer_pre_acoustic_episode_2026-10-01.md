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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26647619 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-51 rssi_med:-46 rssi_max:-42

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

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xce6b6750 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51813 stream:0xce6b6750 wall:0 window_ms:60000 n:949
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:39 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x8a1565a4 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52137 stream:0x8a1565a4 wall:0 window_ms:60000 n:956
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x67ea1389 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51752 stream:0x67ea1389 wall:0 window_ms:60000 n:946
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xfdaf75bf wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52155 stream:0xfdaf75bf wall:0 window_ms:60000 n:953
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x642cef6b wall:0 t_ms:431045 node:0x300 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:480441 stream:0x642cef6b wall:0 window_ms:60000 n:792
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1844408 stream:0x642cef6b wall:0 window_ms:60000 n:928
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:17 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2385132 stream:0x642cef6b wall:0 window_ms:60000 n:932
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3645785 stream:0x642cef6b wall:0 window_ms:60000 n:916
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4538003 stream:0x642cef6b wall:0 window_ms:60000 n:805
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5134772 stream:0x642cef6b wall:0 window_ms:60000 n:894
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5634473 stream:0x642cef6b wall:0 window_ms:60000 n:891
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:6347270 stream:0x642cef6b wall:0 window_ms:60000 n:831
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7283959 stream:0x642cef6b wall:0 window_ms:80000 n:910
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7377662 stream:0x642cef6b wall:0 window_ms:60000 n:921
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:8593376 stream:0x642cef6b wall:0 window_ms:60000 n:926
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x9957bc73 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51039 stream:0x9957bc73 wall:0 window_ms:60000 n:922
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x7ced00dc wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:46216 stream:0x7ced00dc wall:0 window_ms:60000 n:847
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x55e96c91 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:46797 stream:0x55e96c91 wall:0 window_ms:60000 n:852
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xdf12e1d4 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:46366 stream:0xdf12e1d4 wall:0 window_ms:60001 n:845
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:29459 stream:0xdcd3edce wall:0 window_ms:76258 n:2
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xdcd3edce wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1832204 stream:0xdcd3edce wall:0 window_ms:60000 n:700
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:23614 window_ms:1742745 moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0 first_t_ms:89460 last_t_ms:1772204 covered_by:@LAT95LON23

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3632213 stream:0xdcd3edce wall:0 window_ms:60000 n:701
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:24750 window_ms:1740009 moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0 first_t_ms:1892204 last_t_ms:3572213 covered_by:@LAT95LON24

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5412748 stream:0xdcd3edce wall:0 window_ms:60000 n:910
**MOTION** state:still moving_permille:1 dev_mean_mg:12 dev_max_mg:93 moving_ms:60
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7212748 stream:0xdcd3edce wall:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28578 window_ms:1740000 moving_permille:0 dev_mean_mg:12 dev_max_mg:260 moving_ms:360 first_t_ms:5472748 last_t_ms:7152748 covered_by:@LAT95LON26

---

@LAT95LON28 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7812748 stream:0xdcd3edce wall:0 window_ms:60000 n:998
**MOTION** state:moving moving_permille:161 dev_mean_mg:60 dev_max_mg:5563 moving_ms:9664
**RUN** windows_since_last:10 reason:changed max_run:30
**COVERED** state:still windows:9 n:8974 window_ms:540000 moving_permille:10 dev_mean_mg:14 dev_max_mg:635 moving_ms:5835 first_t_ms:7272748 last_t_ms:7752748 covered_by:@LAT95LON27

---

@LAT93LON0 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON27,derived_from@LAT95LON28

**TRANSITION** t_ms:7812748 stream:0xdcd3edce wall:0 node:0x300 from:still to:moving dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:still t_ms:7752748 window_ms:60000 n:998 moving_permille:0 dev_mean_mg:12 dev_max_mg:20 moving_ms:0 lane:@LAT95LON27+9
  @PERCEPT:after state:moving t_ms:7812748 window_ms:60000 n:998 moving_permille:161 dev_mean_mg:60 dev_max_mg:5563 moving_ms:9664 lane:@LAT95LON28+0
**DELTA** edge:became d_permille:161 d_dev_mean_mg:48 d_dev_max_mg:5543

---

@LAT95LON29 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7939326 stream:0xdcd3edce wall:0 window_ms:60000 n:889
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:21 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x1c3a61ee wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON30 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:49702 stream:0x1c3a61ee wall:0 window_ms:60000 n:896
**MOTION** state:still moving_permille:0 dev_mean_mg:13 dev_max_mg:20 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x0c76a2a1 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON31 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51721 stream:0x0c76a2a1 wall:0 window_ms:60000 n:930
**MOTION** state:still moving_permille:0 dev_mean_mg:13 dev_max_mg:17 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xee98fca8 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON32 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51222 stream:0xee98fca8 wall:0 window_ms:60000 n:920
**MOTION** state:still moving_permille:25 dev_mean_mg:15 dev_max_mg:161 moving_ms:1385
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON33 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:321403 stream:0xee98fca8 wall:0 window_ms:60000 n:925
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:19 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON34 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:831699 stream:0xee98fca8 wall:0 window_ms:60000 n:928
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON35 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2638350 stream:0xee98fca8 wall:0 window_ms:63919 n:26
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:21014 window_ms:1742732 moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0 first_t_ms:893699 last_t_ms:2574431 covered_by:@LAT95LON34

---

@LAT95LON36 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4464527 stream:0xee98fca8 wall:0 window_ms:76217 n:396
**MOTION** state:still moving_permille:0 dev_mean_mg:13 dev_max_mg:20 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:18946 window_ms:1749960 moving_permille:0 dev_mean_mg:12 dev_max_mg:96 moving_ms:60 first_t_ms:2698350 last_t_ms:4388310 covered_by:@LAT95LON35

---

@LAT95LON37 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4897754 stream:0xee98fca8 wall:0 window_ms:60000 n:930
**MOTION** state:still moving_permille:0 dev_mean_mg:13 dev_max_mg:50 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT103LON252 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4890438 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-65 observed:-61
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000012 ble met predicted:-60 observed:-61
percept: 2 | 0x00000012 | link_stable | ble | + | -
said: 3 | 0x00000010 espnow met predicted:-51 observed:-47
percept: 3 | 0x00000010 | link_stable | espnow | + | -
said: 4 | 0x00000012 espnow met predicted:-46 observed:-46
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON253 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4950438 ±0 frame:5000
said: 1 | 0x00000012 ble met predicted:-61 observed:-59
percept: 1 | 0x00000012 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-61 observed:-61
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000012 espnow met predicted:-46 observed:-45
percept: 3 | 0x00000012 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-47 observed:-46
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON254 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5010703 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-61 observed:-61
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000012 ble met predicted:-59 observed:-62
percept: 2 | 0x00000012 | link_stable | ble | + | -
said: 3 | 0x00000012 espnow met predicted:-45 observed:-48
percept: 3 | 0x00000012 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-46 observed:-49
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON255 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5070703 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-61 observed:-66
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-49 observed:-51
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000012 ble met predicted:-62 observed:-60
percept: 3 | 0x00000012 | link_stable | ble | + | -
said: 4 | 0x00000012 espnow met predicted:-48 observed:-46
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON256 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5130703 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-66 observed:-67
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000012 ble met predicted:-60 observed:-60
percept: 2 | 0x00000012 | link_stable | ble | + | -
said: 3 | 0x00000010 espnow met predicted:-51 observed:-56
percept: 3 | 0x00000010 | link_stable | espnow | + | -
said: 4 | 0x00000012 espnow met predicted:-46 observed:-48
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON257 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5191236 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-67 observed:-65
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-56 observed:-50
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000012 ble met predicted:-60 observed:-65
percept: 3 | 0x00000012 | link_stable | ble | + | -
said: 4 | 0x00000012 espnow met predicted:-48 observed:-49
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON258 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5253118 ±0 frame:5000
said: 1 | 0x00000012 ble met predicted:-65 observed:-62
percept: 1 | 0x00000012 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-50 observed:-50
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-65 observed:-62
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000012 espnow met predicted:-49 observed:-47
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON259 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5315117 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-50 observed:-55
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000012 ble met predicted:-62 observed:-63
percept: 2 | 0x00000012 | link_stable | ble | + | -
said: 3 | 0x00000010 ble met predicted:-62 observed:-65
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000012 espnow met predicted:-47 observed:-44
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON260 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5375423 ±0 frame:5000
said: 1 | 0x00000012 ble met predicted:-63 observed:-61
percept: 1 | 0x00000012 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-55 observed:-56
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 3 | 0x00000012 | link_stable | espnow | + | -
said: 4 | 0x00000010 ble met predicted:-65 observed:-65
percept: 4 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON261 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5435465 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-56 observed:-57
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-65 observed:-65
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000012 ble met predicted:-61 observed:-61
percept: 3 | 0x00000012 | link_stable | ble | + | -
said: 4 | 0x00000012 espnow met predicted:-44 observed:-45
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON262 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5495465 ±0 frame:5000
said: 1 | 0x00000012 ble met predicted:-61 observed:-61
percept: 1 | 0x00000012 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-65 observed:-63
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000010 espnow met predicted:-57 observed:-52
percept: 3 | 0x00000010 | link_stable | espnow | + | -
said: 4 | 0x00000012 espnow met predicted:-45 observed:-46
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON263 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5556657 ±0 frame:5000
said: 1 | 0x00000012 espnow met predicted:-46 observed:-45
percept: 1 | 0x00000012 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-63 observed:-63
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000012 ble met predicted:-61 observed:-61
percept: 3 | 0x00000012 | link_stable | ble | + | -
said: 4 | 0x00000010 espnow met predicted:-52 observed:-51
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON264 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5616657 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-63 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000012 ble met predicted:-61 observed:-64
percept: 2 | 0x00000012 | link_stable | ble | + | -
said: 3 | 0x00000010 espnow violated predicted:-51 observed:-61
percept: 3 | 0x00000010 | link_stable | espnow | - | -
said: 4 | 0x00000012 espnow violated predicted:-45 observed:-53
percept: 4 | 0x00000012 | link_stable | espnow | - | -
```

---

@LAT103LON265 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5676657 ±0 frame:5000
said: 1 | 0x00000012 ble met predicted:-64 observed:-65
percept: 1 | 0x00000012 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-68
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000010 espnow met predicted:-61 observed:-61
percept: 3 | 0x00000010 | link_stable | espnow | + | -
said: 4 | 0x00000012 espnow met predicted:-53 observed:-54
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON266 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5737027 ±0 frame:5000
said: 1 | 0x00000012 ble met predicted:-65 observed:-65
percept: 1 | 0x00000012 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-61 observed:-61
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-68 observed:-68
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000012 espnow met predicted:-54 observed:-54
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON267 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5797027 ±0 frame:5000
said: 1 | 0x00000012 ble met predicted:-65 observed:-63
percept: 1 | 0x00000012 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-61 observed:-56
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-68 observed:-66
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000012 espnow met predicted:-54 observed:-51
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON268 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5859010 ±0 frame:5000
said: 1 | 0x00000012 ble met predicted:-63 observed:-63
percept: 1 | 0x00000012 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-56 observed:-56
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-66 observed:-66
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000012 espnow met predicted:-51 observed:-50
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON269 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5919018 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-66 observed:-64
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-56 observed:-50
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000012 espnow met predicted:-50 observed:-44
percept: 3 | 0x00000012 | link_stable | espnow | + | -
said: 4 | 0x00000012 ble met predicted:-63 observed:-58
percept: 4 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON270 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5979129 ±0 frame:5000
said: 1 | 0x00000012 ble met predicted:-58 observed:-59
percept: 1 | 0x00000012 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-50 observed:-55
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-64 observed:-65
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000012 espnow met predicted:-44 observed:-43
percept: 4 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON271 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 6039129 ±0 frame:5000
said: 1 | 0x00000012 ble met predicted:-59 observed:-59
percept: 1 | 0x00000012 | link_stable | ble | + | -
said: 2 | 0x00000012 espnow met predicted:-43 observed:-43
percept: 2 | 0x00000012 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-65 observed:-64
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000010 espnow met predicted:-55 observed:-56
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---


---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xee98fca8 wall:0 t_ms:6989045 node:0x300 from:0x10
**REMAP** prev_stream:0x98fbaf08 prev_t_ms:5586 offset_ms:6983459 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT103LON8192 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:7034724 stream:0xee98fca8 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT95LON38 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7034724 stream:0xee98fca8 wall:0 window_ms:60000 n:908
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:23 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---

@LAT103LON8193 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60001 ±0 frame:17500
said: 1 | **ENTWIN** t_ms:7159812 stream:0xee98fca8 wall:0 window_ms:60001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT95LON39 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7159812 stream:0xee98fca8 wall:0 window_ms:60001 n:729
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:36 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT103LON272 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7150398 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-68 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-52 observed:-55
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON273 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7210398 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-68 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-55 observed:-60
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON274 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7270398 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-68 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-60 observed:-60
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON275 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7330398 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-68 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-60 observed:-60
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---


---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:46 last_lon:45 t_ms:7440342 stream:0xee98fca8 wall:0 node:0x00000300

---


---

@LAT95LON40 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7549042 stream:0xee98fca8 wall:0 window_ms:94370 n:2
**MOTION** state:still moving_permille:0 dev_mean_mg:13 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT103LON8194 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7483868 ±0 frame:5000
said: 1 | **ENTWIN** t_ms:7553285 stream:0xee98fca8 wall:0 window_ms:98613 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 12 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 13 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 14 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 15 | **CORE** entities:0
```

---

@LAT103LON276 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7539634 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-59 observed:-60
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-68
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON277 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7599634 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-68 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-60 observed:-59
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON278 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7659634 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-59 observed:-60
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-68
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON279 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7719634 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-60 observed:-60
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-68
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON280 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7779634 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-60 observed:-60
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-68
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON281 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7839634 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-60 observed:-59
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-68
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON282 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7899634 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-59 observed:-59
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-68
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON283 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 7959634 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-68 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-59 observed:-60
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON284 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8019634 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-60 observed:-60
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-68
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON285 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8079634 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-60 observed:-60
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-68
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON286 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8139634 ±0 frame:5000
said: 1 | 0x00000010 espnow violated predicted:-60 observed:-48
percept: 1 | 0x00000010 | link_stable | espnow | - | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-65
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON287 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8199634 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-65 observed:-69
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-48 observed:-53
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON288 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8259634 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-53 observed:-49
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-69 observed:-65
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON289 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8319634 ±0 frame:5000
said: 1 | 0x00000010 espnow violated predicted:-49 observed:-58
percept: 1 | 0x00000010 | link_stable | espnow | - | -
said: 2 | 0x00000010 ble met predicted:-65 observed:-69
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON290 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8379634 ±0 frame:5000
said: 1 | 0x00000010 espnow met predicted:-58 observed:-58
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-69 observed:-68
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON8195 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 62632 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:8548219 stream:0xee98fca8 wall:0 window_ms:62632 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT95LON41 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:8548219 stream:0xee98fca8 wall:0 window_ms:62632 n:535
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:22 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT103LON291 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8539104 ±21 frame:5000
said: 1 | 0x00000010 espnow violated predicted:-49 observed:-62
percept: 1 | 0x00000010 | link_stable | espnow | - | -
said: 2 | 0x00000010 ble met predicted:-66 observed:-68
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT104LON27 | created:0 | updated:0

**carried through @LAT103LON251**

```ttdb-carried
through: 251
carried: 164 0 363 86 | 0x00000200 | link_stable | espnow
carried: 227 2 585 98 | 0x00000200 | link_stable | ble
carried: 236 0 589 104 | 0x00000100 | link_stable | espnow
carried: 171 0 525 38 | 0x00000010 | link_stable | ble
carried: 169 1 523 38 | 0x00000010 | link_stable | espnow
carried: 4 0 4 6 | 0x00000011 | link_stable | ble
carried: 3 1 4 6 | 0x00000011 | link_stable | espnow
carried: 7 1 8 8 | 0x00000012 | link_stable | ble
carried: 7 0 7 7 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON292 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8599114 ±22 frame:5000
said: 1 | 0x00000010 ble met predicted:-68 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-62 observed:-62
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON293 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8659093 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-68 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-62 observed:-62
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON294 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8719093 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-68 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-62 observed:-62
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON295 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8781116 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-68 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-62 observed:-62
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON296 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8841304 ±0 frame:5000
said: 1 | 0x00000010 ble met predicted:-68 observed:-68
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-62 observed:-62
percept: 2 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON297 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8901304 ±0 frame:5000
said: 1 | 0x00000010 espnow violated predicted:-62 observed:-50
percept: 1 | 0x00000010 | link_stable | espnow | - | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-66
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x88023c58 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT103LON8196 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:50583 stream:0x88023c58 wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT95LON42 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:50583 stream:0x88023c58 wall:0 window_ms:60000 n:917
**MOTION** state:still moving_permille:1 dev_mean_mg:12 dev_max_mg:115 moving_ms:60
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT103LON8197 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1213636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:1204219 stream:0x88023c58 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,84a329c78fec,0283cce0e689,e6b32d2cea8b
said: 14 | **COVERED** windows:1 entities:10 window_ms:553636 first_t_ms:604219 last_t_ms:604219 covered_by:@LAT103LON8196
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
```

---

@LAT103LON8198 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1813635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:1804218 stream:0x88023c58 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,c2e94427adcf,84a329c78fec,0283cce0e689
```

---

@LAT95LON43 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1850583 stream:0x88023c58 wall:0 window_ms:60000 n:998
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28979 window_ms:1740000 moving_permille:0 dev_mean_mg:12 dev_max_mg:25 moving_ms:0 first_t_ms:110583 last_t_ms:1790583 covered_by:@LAT95LON42

---

@LAT103LON8199 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2413635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:2404218 stream:0x88023c58 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,5ce28c488e0c,e6b32d2cea8b,c2e94427adcf,0283cce0e689,84a329c78fec
```

---

@LAT103LON8200 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3013636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:3004219 stream:0x88023c58 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,5ce28c488e0c,c2e94427adcf,0283cce0e689
```

---

@LAT103LON8201 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3613636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:3604219 stream:0x88023c58 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689,7236bc441422,c2e94427adcf,5ce28c488e0c
```

---

@LAT95LON44 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3650583 stream:0x88023c58 wall:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:13 dev_max_mg:16 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28984 window_ms:1740000 moving_permille:0 dev_mean_mg:12 dev_max_mg:19 moving_ms:0 first_t_ms:1910583 last_t_ms:3590583 covered_by:@LAT95LON43

---

@LAT103LON8202 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4813635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:4804218 stream:0x88023c58 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,5ce28c488e0c,e6b32d2cea8b,c2e94427adcf,0283cce0e689
said: 13 | **COVERED** windows:1 entities:9 window_ms:600000 first_t_ms:4204219 last_t_ms:4204219 covered_by:@LAT103LON8201
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-92 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93 windows:1
```

---

@LAT103LON8203 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5413636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:5404219 stream:0x88023c58 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,64677217947d,5ce28c488e0c,7236bc441422,0283cce0e689,c2e94427adcf,e6b32d2cea8b
```

---

@LAT95LON45 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5450583 stream:0x88023c58 wall:0 window_ms:60000 n:999
**MOTION** state:still moving_permille:0 dev_mean_mg:13 dev_max_mg:16 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28984 window_ms:1740000 moving_permille:0 dev_mean_mg:13 dev_max_mg:18 moving_ms:0 first_t_ms:3710583 last_t_ms:5390583 covered_by:@LAT95LON44

---

@LAT103LON8204 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6013635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:6004218 stream:0x88023c58 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,0283cce0e689,5ce28c488e0c,c2e94427adcf,e6b32d2cea8b
```

---

@LAT103LON8205 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6613636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:6604219 stream:0x88023c58 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,5ce28c488e0c,aef9ff2626ac,0283cce0e689,c2e94427adcf
```

---

@LAT95LON46 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7250583 stream:0x88023c58 wall:0 window_ms:60000 n:999
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28981 window_ms:1740000 moving_permille:0 dev_mean_mg:13 dev_max_mg:18 moving_ms:0 first_t_ms:5510583 last_t_ms:7190583 covered_by:@LAT95LON45

---

@LAT103LON8206 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7813635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:7804218 stream:0x88023c58 wall:0 window_ms:600000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 13 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,0283cce0e689,7236bc441422,c2e94427adcf,aef9ff2626ac
said: 15 | **COVERED** windows:1 entities:11 window_ms:599999 first_t_ms:7204218 last_t_ms:7204218 covered_by:@LAT103LON8205
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94 windows:1
```

---

@LAT103LON8207 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8413636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:8404219 stream:0x88023c58 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689,c2e94427adcf,aef9ff2626ac
```

---

@LAT103LON8208 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9013635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:9004218 stream:0x88023c58 wall:0 window_ms:599999 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,0283cce0e689,5ce28c488e0c,7236bc441422,c2e94427adcf,aef9ff2626ac
```

---

@LAT95LON47 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:9050583 stream:0x88023c58 wall:0 window_ms:60000 n:999
**MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28979 window_ms:1740000 moving_permille:0 dev_mean_mg:12 dev_max_mg:23 moving_ms:0 first_t_ms:7310583 last_t_ms:8990583 covered_by:@LAT95LON46

---

@LAT103LON8209 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9613636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:9604219 stream:0x88023c58 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,c2e94427adcf,5ce28c488e0c,7236bc441422,0283cce0e689
```

---

@LAT103LON8210 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10213635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:10204218 stream:0x88023c58 wall:0 window_ms:599999 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,7236bc441422,5ce28c488e0c,84a329c78fec,c2e94427adcf,0283cce0e689
```

---

@LAT103LON8211 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11413635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:11404218 stream:0x88023c58 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,5ce28c488e0c,c2e94427adcf,84a329c78fec,7236bc441422
said: 12 | **COVERED** windows:1 entities:10 window_ms:600000 first_t_ms:10804218 last_t_ms:10804218 covered_by:@LAT103LON8210
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
```

---

@LAT103LON8212 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12013636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:12004219 stream:0x88023c58 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,5ce28c488e0c,7236bc441422,c2e94427adcf
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:3417
t_ms:12012992 stream:0x88023c58 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0000 cap_epoch:5
**TRACE** copresence:32 half_life_ms:600000 reinforced:1 last_ms:12022409
t_ms:12012992 stream:0x88023c58 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:12012992 stream:0x88023c58 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:3417
t_ms:12012992 stream:0x88023c58 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:3417
t_ms:12012992 stream:0x88023c58 wall:0

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
