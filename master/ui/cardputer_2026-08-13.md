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

**STREAM-ADOPTED** stream:0x0870722b wall:0 t_ms:1708670 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT101LON0 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:22 last_ms:56621
t_ms:1772049 stream:0x0870722b wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:16 last_ms:59341
t_ms:1772049 stream:0x0870722b wall:0

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1772049 stream:0x0870722b wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:71 rssi_min:-80 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-27 rssi_med:-26 rssi_max:-26
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-79 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-27 rssi_med:-27 rssi_max:-26

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1772049 stream:0x0870722b wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1772049 stream:0x0870722b wall:0 window_ms:60000 n:972
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1772049 stream:0x0870722b wall:0 window_ms:60000 blocks:3641 rate:8000
**ACOUSTIC** rms_mean:107 rms_max:390 peak:672 transients:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1839496 stream:0x0870722b wall:0 window_ms:67447
**LINK** peer:0x00000200 proto:ble n:72 rssi_min:-79 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000200 proto:espnow n:32 rssi_min:-28 rssi_med:-27 rssi_max:-26
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-26 rssi_med:-25 rssi_max:-24

---

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:1839496 stream:0x0870722b wall:0 node:0x300 acting:@LAT95LON0+0 observed_in:@LAT97LON1 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-42 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-26 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-25 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-44 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-41 delta:3 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-27 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-27 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1839496 stream:0x0870722b wall:0 window_ms:67447 blocks:77 rate:8000
**ACOUSTIC** rms_mean:276 rms_max:3897 peak:8094 transients:3
**TRANSIENT** t_ms:1839478 stream:0x0870722b wall:0 rms:3897

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1914926 stream:0x0870722b wall:0 window_ms:75430
**LINK** peer:0x00000200 proto:ble n:80 rssi_min:-50 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-26 rssi_med:-25 rssi_max:-25
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-28 rssi_med:-27 rssi_max:-26
**LINK** peer:0x00000010 proto:ble n:82 rssi_min:-80 rssi_med:-41 rssi_max:-39

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1914926 stream:0x0870722b wall:0 window_ms:75430 blocks:206 rate:8000
**ACOUSTIC** rms_mean:774 rms_max:2634 peak:6840 transients:2
**TRANSIENT** t_ms:1872741 stream:0x0870722b wall:0 rms:1317

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1978731 stream:0x0870722b wall:0 window_ms:63805
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-80 rssi_med:-44 rssi_max:-38
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-26 rssi_med:-25 rssi_max:-23
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-47 rssi_med:-41 rssi_max:-37
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-30 rssi_med:-28 rssi_max:-25

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1978731 stream:0x0870722b wall:0 window_ms:63805 blocks:246 rate:8000
**ACOUSTIC** rms_mean:1229 rms_max:4618 peak:9959 transients:3
**TRANSIENT** t_ms:1927334 stream:0x0870722b wall:0 rms:2554

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2040671 stream:0x0870722b wall:0 window_ms:61940
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-47 rssi_med:-40 rssi_max:-37
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-53 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-25 rssi_med:-25 rssi_max:-23
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-30 rssi_med:-27 rssi_max:-26

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2040671 stream:0x0870722b wall:0 window_ms:61940 blocks:363 rate:8000
**ACOUSTIC** rms_mean:786 rms_max:3669 peak:7356 transients:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2100671 stream:0x0870722b wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:2 rssi_min:-29 rssi_med:-29 rssi_max:-24
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-59 rssi_med:-49 rssi_max:-41
**LINK** peer:0x00000010 proto:ble n:5 rssi_min:-55 rssi_med:-45 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-40 rssi_med:-34 rssi_max:-29
**LINK** peer:0x00000011 proto:espnow n:11 rssi_min:-33 rssi_med:-31 rssi_max:-30
**LINK** peer:0x00000011 proto:ble n:44 rssi_min:-81 rssi_med:-47 rssi_max:-45

---

@LAT92LON1 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON5,senses@LAT0LON0

**OUTCOME** t_ms:2100671 stream:0x0870722b wall:0 node:0x300 acting:@LAT95LON0+4 observed_in:@LAT97LON5 band_dbm:6 met:3 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:4 reason:changed max_run:30
**COVERED-SPAN** windows:3 first_t_ms:1914926 last_t_ms:2040671 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000200 proto:ble verdict:met windows:3 observed_min:-44 observed_max:-42
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:3 observed_min:-28 observed_max:-27
**COVERED** peer:0x00000010 proto:ble verdict:met windows:3 observed_min:-41 observed_max:-40
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:3 observed_min:-25 observed_max:-25
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-40 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-45 delta:-5 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-43 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-49 delta:-6 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-25 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-29 delta:-4 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-27 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-34 delta:-7 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2100671 stream:0x0870722b wall:0 window_ms:60000 blocks:3355 rate:8000
**ACOUSTIC** rms_mean:209 rms_max:13558 peak:32768 transients:16
**TRANSIENT** t_ms:2050034 stream:0x0870722b wall:0 rms:13558

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2160671 stream:0x0870722b wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-52 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-33 rssi_med:-31 rssi_max:-29
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-59 rssi_med:-49 rssi_max:-45

---

@LAT92LON2 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON6,senses@LAT0LON0

**OUTCOME** t_ms:2160671 stream:0x0870722b wall:0 node:0x300 acting:@LAT95LON0+5 observed_in:@LAT97LON6 band_dbm:6 met:4 violated:0 unobserved:2 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-29 band:6
**OBSERVED** peer:0x00000010 proto:espnow verdict:unobserved
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-49 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-49 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-45 band:6
**OBSERVED** peer:0x00000010 proto:ble verdict:unobserved
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-34 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-34 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-31 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-31 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-47 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-48 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2160671 stream:0x0870722b wall:0 window_ms:60000 blocks:3727 rate:8000
**ACOUSTIC** rms_mean:136 rms_max:2263 peak:11863 transients:2
**TRANSIENT** t_ms:2104864 stream:0x0870722b wall:0 rms:2263

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2220671 stream:0x0870722b wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-70 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-37 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:43 rssi_min:-53 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-32 rssi_med:-31 rssi_max:-29

---

@LAT92LON3 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON7,senses@LAT0LON0

**OUTCOME** t_ms:2220671 stream:0x0870722b wall:0 node:0x300 acting:@LAT95LON0+6 observed_in:@LAT97LON7 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-48 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-48 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-31 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-31 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-34 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-34 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-49 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-49 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2220671 stream:0x0870722b wall:0 window_ms:60000 blocks:3726 rate:8000
**ACOUSTIC** rms_mean:143 rms_max:883 peak:1783 transients:0

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2280671 stream:0x0870722b wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-36 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-33 rssi_med:-31 rssi_max:-29

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2280671 stream:0x0870722b wall:0 window_ms:60000 blocks:3710 rate:8000
**ACOUSTIC** rms_mean:137 rms_max:787 peak:3273 transients:0

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2322506 stream:0x0870722b wall:0 window_ms:550457 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2340671 stream:0x0870722b wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-51 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-32 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-50 rssi_max:-46

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2340671 stream:0x0870722b wall:0 window_ms:60000 blocks:3728 rate:8000
**ACOUSTIC** rms_mean:131 rms_max:620 peak:2583 transients:0

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2400671 stream:0x0870722b wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-49 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-50 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-36 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2400671 stream:0x0870722b wall:0 window_ms:60000 blocks:3727 rate:8000
**ACOUSTIC** rms_mean:129 rms_max:449 peak:1154 transients:0

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbeb39900 wall:0 t_ms:8947 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:67153 stream:0xbeb39900 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-31 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-36 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-33 rssi_med:-32 rssi_max:-28
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-80 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-63 rssi_med:-58 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-80 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-81 rssi_med:-50 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:32 rssi_min:-50 rssi_med:-49 rssi_max:-34

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:67153 stream:0xbeb39900 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:67153 stream:0xbeb39900 wall:0 window_ms:60000 n:964
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:67153 stream:0xbeb39900 wall:0 window_ms:60000 blocks:3611 rate:8000
**ACOUSTIC** rms_mean:109 rms_max:450 peak:784 transients:0

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:127153 stream:0xbeb39900 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-80 rssi_med:-50 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-51 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-35 rssi_med:-33 rssi_max:-30
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-32 rssi_med:-31 rssi_max:-28
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-54 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-53 rssi_med:-49 rssi_max:-41
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-32 rssi_med:-29 rssi_max:-29

---

@LAT92LON4 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON12,senses@LAT0LON0

**OUTCOME** t_ms:127153 stream:0xbeb39900 wall:0 node:0x300 acting:@LAT95LON1+0 observed_in:@LAT97LON12 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-29 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-31 delta:-2 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-34 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-33 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-32 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-29 delta:3 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-47 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-48 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-60 delta:-2 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-52 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-51 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-50 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-50 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-49 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-49 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:127153 stream:0xbeb39900 wall:0 window_ms:60000 blocks:3724 rate:8000
**ACOUSTIC** rms_mean:773 rms_max:29348 peak:32768 transients:32
**TRANSIENT** t_ms:126865 stream:0xbeb39900 wall:0 rms:29348

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:187153 stream:0xbeb39900 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-54 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-55 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-51 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-89 rssi_med:-57 rssi_max:-48
**LINK** peer:0x00000200 proto:espnow n:32 rssi_min:-64 rssi_med:-45 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-34 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-31 rssi_med:-29 rssi_max:-28
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-32 rssi_med:-30 rssi_max:-28

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:187153 stream:0xbeb39900 wall:0 window_ms:60000 blocks:3708 rate:8000
**ACOUSTIC** rms_mean:1040 rms_max:28283 peak:32768 transients:38
**TRANSIENT** t_ms:138710 stream:0xbeb39900 wall:0 rms:28283

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:247153 stream:0xbeb39900 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:71 rssi_min:-51 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-56 rssi_med:-48 rssi_max:-37
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-68 rssi_med:-59 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-35 rssi_med:-33 rssi_max:-31
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-55 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-54 rssi_med:-52 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-32 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-33 rssi_med:-29 rssi_max:-29

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:247153 stream:0xbeb39900 wall:0 window_ms:60000 blocks:3709 rate:8000
**ACOUSTIC** rms_mean:538 rms_max:29246 peak:32768 transients:17
**TRANSIENT** t_ms:246736 stream:0xbeb39900 wall:0 rms:29192

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:307153 stream:0xbeb39900 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:33 rssi_min:-49 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-47 rssi_max:-46
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-50 rssi_med:-49 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-65 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-31 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-53 rssi_med:-51 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-35 rssi_med:-33 rssi_max:-32

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:307153 stream:0xbeb39900 wall:0 window_ms:60000 blocks:3722 rate:8000
**ACOUSTIC** rms_mean:340 rms_max:29562 peak:32768 transients:9
**TRANSIENT** t_ms:253002 stream:0xbeb39900 wall:0 rms:29562

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x1de72b4d wall:0 t_ms:240617 node:0x300 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:297709 stream:0x1de72b4d wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:28 rssi_min:-95 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-90 rssi_med:-69 rssi_max:-63
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-74 rssi_med:-66 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-69 rssi_med:-56 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:49 rssi_min:-87 rssi_med:-77 rssi_max:-70
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-86 rssi_med:-78 rssi_max:-69

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:297709 stream:0x1de72b4d wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:297709 stream:0x1de72b4d wall:0 window_ms:60000 n:744
**MOTION** state:moving moving_permille:190 dev_mean_mg:45 dev_max_mg:597 moving_ms:10073
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:297709 stream:0x1de72b4d wall:0 window_ms:60000 blocks:2720 rate:8000
**ACOUSTIC** rms_mean:500 rms_max:21425 peak:32768 transients:64
**TRANSIENT** t_ms:260004 stream:0x1de72b4d wall:0 rms:21425

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:357709 stream:0x1de72b4d wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:68 rssi_min:-83 rssi_med:-78 rssi_max:-70
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-87 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-69 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-72 rssi_med:-70 rssi_max:-68
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-64 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-63 rssi_med:-42 rssi_max:-38
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-75 rssi_med:-69 rssi_max:-63
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-75 rssi_med:-56 rssi_max:-51

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:357709 stream:0x1de72b4d wall:0 window_ms:60000 n:496
**MOTION** state:still moving_permille:0 dev_mean_mg:16 dev_max_mg:19 moving_ms:0
**RUN** windows_since_last:1 reason:changed max_run:30

---

@LAT93LON0 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON2,derived_from@LAT95LON3

**TRANSITION** t_ms:357709 stream:0x1de72b4d wall:0 node:0x300 from:moving to:still dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:moving t_ms:297709 window_ms:60000 n:744 moving_permille:190 dev_mean_mg:45 dev_max_mg:597 moving_ms:10073 lane:@LAT95LON2+0
  @PERCEPT:after state:still t_ms:357709 window_ms:60000 n:496 moving_permille:0 dev_mean_mg:16 dev_max_mg:19 moving_ms:0 lane:@LAT95LON3+0
**DELTA** edge:became d_permille:-190 d_dev_mean_mg:-29 d_dev_max_mg:-578

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:357709 stream:0x1de72b4d wall:0 window_ms:60000 blocks:1856 rate:8000
**ACOUSTIC** rms_mean:185 rms_max:3824 peak:7368 transients:12
**TRANSIENT** t_ms:345449 stream:0x1de72b4d wall:0 rms:3824

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:417780 stream:0x1de72b4d wall:0 window_ms:60071
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-84 rssi_med:-76 rssi_max:-71
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-88 rssi_med:-61 rssi_max:-49
**LINK** peer:0x00000200 proto:espnow n:43 rssi_min:-72 rssi_med:-48 rssi_max:-39
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-72 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-70 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-76 rssi_med:-67 rssi_max:-61
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-74 rssi_med:-65 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-86 rssi_med:-83 rssi_max:-82

---

@LAT92LON5 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON18,senses@LAT0LON0

**OUTCOME** t_ms:417780 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+0 observed_in:@LAT97LON18 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-78 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-76 delta:2 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-84 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-83 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-65 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-66 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-70 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-69 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-61 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-65 delta:-4 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-48 delta:-6 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-69 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-67 delta:2 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-61 delta:-5 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:417780 stream:0x1de72b4d wall:0 window_ms:60071 blocks:1860 rate:8000
**ACOUSTIC** rms_mean:1547 rms_max:17832 peak:30227 transients:85
**TRANSIENT** t_ms:373014 stream:0x1de72b4d wall:0 rms:17802

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:477827 stream:0x1de72b4d wall:0 window_ms:60047
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-51 rssi_med:-46 rssi_max:-34
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-91 rssi_med:-77 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-88 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-73 rssi_med:-56 rssi_max:-46
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-78 rssi_med:-68 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-70 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-73 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-70 rssi_med:-65 rssi_max:-62

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:477827 stream:0x1de72b4d wall:0 window_ms:60047 blocks:1844 rate:8000
**ACOUSTIC** rms_mean:273 rms_max:7188 peak:32767 transients:22
**TRANSIENT** t_ms:468831 stream:0x1de72b4d wall:0 rms:7188

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:537827 stream:0x1de72b4d wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-87 rssi_med:-83 rssi_max:-81
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-68 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-68 rssi_med:-53 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-72 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-78 rssi_med:-69 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-75 rssi_med:-70 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-88 rssi_med:-78 rssi_max:-72
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-50 rssi_med:-40 rssi_max:-33

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:537827 stream:0x1de72b4d wall:0 window_ms:60000 blocks:1953 rate:8000
**ACOUSTIC** rms_mean:1305 rms_max:18270 peak:32768 transients:82
**TRANSIENT** t_ms:528811 stream:0x1de72b4d wall:0 rms:17361

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:597827 stream:0x1de72b4d wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-88 rssi_med:-77 rssi_max:-72
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-87 rssi_med:-68 rssi_max:-60
**LINK** peer:0x00000012 proto:espnow n:35 rssi_min:-78 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-76 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-77 rssi_med:-55 rssi_max:-30
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-91 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-76 rssi_med:-48 rssi_max:-16
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-76 rssi_med:-66 rssi_max:-60

---

@LAT92LON6 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON21,senses@LAT0LON0

**OUTCOME** t_ms:597827 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+3 observed_in:@LAT97LON21 band_dbm:6 met:7 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:3 reason:changed max_run:30
**COVERED-SPAN** windows:2 first_t_ms:477827 last_t_ms:537827 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000012 proto:ble verdict:met windows:2 observed_min:-78 observed_max:-77
**COVERED** peer:0x00000200 proto:ble verdict:met windows:2 observed_min:-56 observed_max:-53
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:2 observed_min:-46 observed_max:-40
**COVERED** peer:0x00000012 proto:espnow verdict:met windows:2 observed_min:-65 observed_max:-65
**COVERED** peer:0x00000011 proto:espnow verdict:met windows:2 observed_min:-69 observed_max:-69
**COVERED** peer:0x00000010 proto:ble verdict:met windows:2 observed_min:-69 observed_max:-68
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:2 observed_min:-70 observed_max:-69
**COVERED** peer:0x00000011 proto:ble verdict:met windows:2 observed_min:-84 observed_max:-83
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-83 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-86 delta:-3 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-65 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-62 delta:3 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:-2 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-69 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-69 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-69 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-68 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-70 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-66 delta:4 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-78 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-77 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-48 delta:-8 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:597827 stream:0x1de72b4d wall:0 window_ms:60000 blocks:1858 rate:8000
**ACOUSTIC** rms_mean:1417 rms_max:24388 peak:32768 transients:47
**TRANSIENT** t_ms:554085 stream:0x1de72b4d wall:0 rms:24258

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:657894 stream:0x1de72b4d wall:0 window_ms:60067
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-81 rssi_med:-78 rssi_max:-75
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-63 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-68 rssi_med:-68 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-89 rssi_med:-84 rssi_max:-82
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-71 rssi_med:-66 rssi_max:-61
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-66 rssi_max:-59
**LINK** peer:0x00000010 proto:ble n:51 rssi_min:-72 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-68 rssi_med:-50 rssi_max:-46

---

@LAT92LON7 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON22,senses@LAT0LON0

**OUTCOME** t_ms:657894 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+4 observed_in:@LAT97LON22 band_dbm:6 met:7 violated:1 unobserved:0 streak:2
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-77 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-78 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-68 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-65 delta:3 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-62 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-62 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-69 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-68 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-66 delta:-11 verdict:violated
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-86 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-84 delta:2 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-50 delta:-2 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-66 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-66 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:657894 stream:0x1de72b4d wall:0 window_ms:60067 blocks:1838 rate:8000
**ACOUSTIC** rms_mean:190 rms_max:3002 peak:7784 transients:10
**TRANSIENT** t_ms:651399 stream:0x1de72b4d wall:0 rms:3002

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:717898 stream:0x1de72b4d wall:0 window_ms:60004
**LINK** peer:0x00000012 proto:ble n:47 rssi_min:-89 rssi_med:-78 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-75 rssi_med:-67 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-90 rssi_med:-85 rssi_max:-80
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-66 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-73 rssi_med:-70 rssi_max:-65
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-73 rssi_med:-70 rssi_max:-64
**LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-64 rssi_med:-61 rssi_max:-56
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-69 rssi_med:-69 rssi_max:-67

---

@LAT92LON8 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON23,senses@LAT0LON0

**OUTCOME** t_ms:717898 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+5 observed_in:@LAT97LON23 band_dbm:6 met:7 violated:1 unobserved:0 streak:3
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-78 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-78 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-62 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-67 delta:-5 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-68 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-69 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-84 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-85 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-66 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-70 delta:-4 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-66 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-70 delta:-4 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-65 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-66 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-50 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-61 delta:-11 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:717898 stream:0x1de72b4d wall:0 window_ms:60004 blocks:1849 rate:8000
**ACOUSTIC** rms_mean:198 rms_max:2191 peak:3944 transients:5
**TRANSIENT** t_ms:670581 stream:0x1de72b4d wall:0 rms:2191

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:777927 stream:0x1de72b4d wall:0 window_ms:60029
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-78 rssi_med:-67 rssi_max:-61
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-70 rssi_med:-68 rssi_max:-67
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-89 rssi_med:-79 rssi_max:-72
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-72 rssi_med:-67 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:39 rssi_min:-70 rssi_med:-61 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-90 rssi_med:-69 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-93 rssi_med:-85 rssi_max:-83
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-67 rssi_med:-62 rssi_max:-62

---

@LAT92LON9 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON24,senses@LAT0LON0

**OUTCOME** t_ms:777927 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+6 observed_in:@LAT97LON24 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-78 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-79 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-67 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-62 delta:5 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-85 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-85 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-66 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-67 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-70 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-67 delta:3 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-70 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-69 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-61 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-61 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-69 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-68 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:777927 stream:0x1de72b4d wall:0 window_ms:60029 blocks:1852 rate:8000
**ACOUSTIC** rms_mean:288 rms_max:3889 peak:9317 transients:21
**TRANSIENT** t_ms:776941 stream:0x1de72b4d wall:0 rms:3889

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:837927 stream:0x1de72b4d wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-81 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-67 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-90 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-71 rssi_med:-68 rssi_max:-67
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-88 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000200 proto:espnow n:38 rssi_min:-66 rssi_med:-55 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-81 rssi_med:-63 rssi_max:-59
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-83 rssi_med:-69 rssi_max:-64

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:837927 stream:0x1de72b4d wall:0 window_ms:60000 blocks:1832 rate:8000
**ACOUSTIC** rms_mean:1246 rms_max:26017 peak:32768 transients:68
**TRANSIENT** t_ms:832241 stream:0x1de72b4d wall:0 rms:25870

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:849779 stream:0x1de72b4d wall:0 window_ms:552070 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:897927 stream:0x1de72b4d wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-69 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-92 rssi_med:-78 rssi_max:-70
**LINK** peer:0x00000011 proto:ble n:41 rssi_min:-91 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000200 proto:ble n:50 rssi_min:-89 rssi_med:-75 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-74 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-77 rssi_med:-62 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-71 rssi_med:-68 rssi_max:-67

---

@LAT92LON10 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON26,senses@LAT0LON0

**OUTCOME** t_ms:897927 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+8 observed_in:@LAT97LON26 band_dbm:6 met:7 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:2 reason:changed max_run:30
**COVERED-SPAN** windows:1 first_t_ms:837927 last_t_ms:837927 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000010 proto:ble verdict:met windows:1 observed_min:-65 observed_max:-65
**COVERED** peer:0x00000011 proto:espnow verdict:met windows:1 observed_min:-68 observed_max:-68
**COVERED** peer:0x00000012 proto:ble verdict:met windows:1 observed_min:-77 observed_max:-77
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:1 observed_min:-63 observed_max:-63
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:1 observed_min:-55 observed_max:-55
**COVERED** peer:0x00000200 proto:ble verdict:met windows:1 observed_min:-69 observed_max:-69
**COVERED** peer:0x00000011 proto:ble verdict:met windows:1 observed_min:-85 observed_max:-85
**COVERED** peer:0x00000012 proto:espnow verdict:met windows:1 observed_min:-63 observed_max:-63
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-65 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-64 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-63 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-63 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-85 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-85 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-68 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-68 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-77 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-78 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-62 delta:-7 verdict:violated
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-63 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-64 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-69 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-75 delta:-6 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:897927 stream:0x1de72b4d wall:0 window_ms:60000 blocks:1853 rate:8000
**ACOUSTIC** rms_mean:7974 rms_max:26598 peak:32768 transients:148
**TRANSIENT** t_ms:850385 stream:0x1de72b4d wall:0 rms:26598

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:957927 stream:0x1de72b4d wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:11 rssi_min:-66 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-77 rssi_med:-65 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-91 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000200 proto:ble n:19 rssi_min:-90 rssi_med:-81 rssi_max:-75
**LINK** peer:0x00000012 proto:ble n:26 rssi_min:-86 rssi_med:-80 rssi_max:-75
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-74 rssi_med:-64 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:8 rssi_min:-80 rssi_med:-71 rssi_max:-66
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-69 rssi_med:-68 rssi_max:-66

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:957927 stream:0x1de72b4d wall:0 window_ms:60000 blocks:1830 rate:8000
**ACOUSTIC** rms_mean:1497 rms_max:25757 peak:32768 transients:39
**TRANSIENT** t_ms:902847 stream:0x1de72b4d wall:0 rms:24607

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xd9f790b7 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52491 stream:0xd9f790b7 wall:0 window_ms:60026 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52491 stream:0xd9f790b7 wall:0 window_ms:60026 n:588
**MOTION** state:still moving_permille:79 dev_mean_mg:27 dev_max_mg:506 moving_ms:3601
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:52491 stream:0xd9f790b7 wall:0 window_ms:60026 blocks:2175 rate:8000
**ACOUSTIC** rms_mean:454 rms_max:10775 peak:31445 transients:62
**TRANSIENT** t_ms:21135 stream:0xd9f790b7 wall:0 rms:10775

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:112503 stream:0xd9f790b7 wall:0 window_ms:60012 blocks:1871 rate:8000
**ACOUSTIC** rms_mean:1067 rms_max:10873 peak:21873 transients:101
**TRANSIENT** t_ms:85371 stream:0xd9f790b7 wall:0 rms:10746

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:172509 stream:0xd9f790b7 wall:0 window_ms:60006 blocks:1871 rate:8000
**ACOUSTIC** rms_mean:929 rms_max:12080 peak:32767 transients:69
**TRANSIENT** t_ms:151272 stream:0xd9f790b7 wall:0 rms:12080

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:232537 stream:0xd9f790b7 wall:0 window_ms:60028 blocks:1877 rate:8000
**ACOUSTIC** rms_mean:1053 rms_max:9173 peak:30606 transients:31
**TRANSIENT** t_ms:187907 stream:0xd9f790b7 wall:0 rms:9173

---

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:292545 stream:0xd9f790b7 wall:0 window_ms:60008 blocks:1875 rate:8000
**ACOUSTIC** rms_mean:2725 rms_max:27444 peak:32768 transients:50
**TRANSIENT** t_ms:286423 stream:0xd9f790b7 wall:0 rms:26297

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xcab73254 wall:0 t_ms:4900 node:0x300 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60451 stream:0xcab73254 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-54 rssi_med:-37 rssi_max:-31
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-80 rssi_med:-52 rssi_max:-46

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:60451 stream:0xcab73254 wall:0 window_ms:60000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-62
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
**ENTITY** kind:wifi_ap id:cc40d01710aa n:1 rssi:-85
**ENTITY** kind:wifi_ap id:923badc7ab14 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:9483c4218a92 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60451 stream:0xcab73254 wall:0 window_ms:60000 n:945
**MOTION** state:moving moving_permille:265 dev_mean_mg:62 dev_max_mg:745 moving_ms:16014
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60451 stream:0xcab73254 wall:0 window_ms:60000 blocks:3483 rate:8000
**ACOUSTIC** rms_mean:1171 rms_max:25394 peak:32768 transients:53
**TRANSIENT** t_ms:27660 stream:0xcab73254 wall:0 rms:25394

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120571 stream:0xcab73254 wall:0 window_ms:60120
**LINK** peer:0x00000200 proto:espnow n:46 rssi_min:-62 rssi_med:-39 rssi_max:-27
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-54 rssi_max:-37

---

@LAT94LON34 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:120571 stream:0xcab73254 wall:0 window_ms:60120 blocks:3548 rate:8000
**ACOUSTIC** rms_mean:1390 rms_max:24775 peak:32768 transients:98
**TRANSIENT** t_ms:76490 stream:0xcab73254 wall:0 rms:24775

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:180573 stream:0xcab73254 wall:0 window_ms:60002
**LINK** peer:0x00000200 proto:ble n:70 rssi_min:-81 rssi_med:-54 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-62 rssi_med:-38 rssi_max:-31

---

@LAT94LON35 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:180573 stream:0xcab73254 wall:0 window_ms:60002 blocks:3274 rate:8000
**ACOUSTIC** rms_mean:1880 rms_max:31283 peak:32768 transients:111
**TRANSIENT** t_ms:177742 stream:0xcab73254 wall:0 rms:31283

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbb1177f2 wall:0 t_ms:4006646 node:0x300 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4063152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-91 rssi_med:-84 rssi_max:-80
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-79 rssi_med:-68 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:48 rssi_min:-85 rssi_med:-75 rssi_max:-72
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-74 rssi_med:-62 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-64 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-72 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:8 rssi_min:-60 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:22 rssi_min:-82 rssi_med:-66 rssi_max:-64

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4063152 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4063152 stream:0xbb1177f2 wall:0 window_ms:60000 n:934
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:39 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON36 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4063152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3493 rate:8000
**ACOUSTIC** rms_mean:186 rms_max:3978 peak:13712 transients:12
**TRANSIENT** t_ms:4017612 stream:0xbb1177f2 wall:0 rms:3978

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4123152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-90 rssi_med:-83 rssi_max:-80
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-80 rssi_med:-76 rssi_max:-73
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-63 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-63 rssi_med:-60 rssi_max:-54
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-81 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-72 rssi_med:-65 rssi_max:-59
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-62 rssi_med:-55 rssi_max:-51

---

@LAT92LON11 | created:0 | updated:0 | relates:testifies_about@LAT95LON6,derived_from@LAT97LON32,senses@LAT0LON0

**OUTCOME** t_ms:4123152 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON6+0 observed_in:@LAT97LON32 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-84 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-83 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-68 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-65 delta:3 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-75 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-76 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-62 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-62 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-55 delta:-2 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-69 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-70 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-58 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-60 delta:-2 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-66 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-66 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON37 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4123152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3665 rate:8000
**ACOUSTIC** rms_mean:219 rms_max:3862 peak:6170 transients:12
**TRANSIENT** t_ms:4094221 stream:0xbb1177f2 wall:0 rms:2249

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4183152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-89 rssi_med:-82 rssi_max:-81
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-71 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-71 rssi_med:-64 rssi_max:-59
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-62 rssi_med:-60 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-60 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000012 proto:espnow n:14 rssi_min:-64 rssi_med:-62 rssi_max:-61

---

@LAT94LON38 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4183152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3685 rate:8000
**ACOUSTIC** rms_mean:133 rms_max:640 peak:1178 transients:0

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4243152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-71 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-71 rssi_med:-65 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-80 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-64 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-70 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-62 rssi_med:-60 rssi_max:-59
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-56 rssi_med:-54 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-89 rssi_med:-84 rssi_max:-80

---

@LAT94LON39 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4243152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3628 rate:8000
**ACOUSTIC** rms_mean:133 rms_max:1181 peak:2124 transients:2
**TRANSIENT** t_ms:4185321 stream:0xbb1177f2 wall:0 rms:1181

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4303152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-64 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-89 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-62 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-57 rssi_med:-55 rssi_max:-55
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-72 rssi_med:-65 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-71 rssi_med:-67 rssi_max:-64
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-78 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-71 rssi_med:-70 rssi_max:-67

---

@LAT94LON40 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4303152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3675 rate:8000
**ACOUSTIC** rms_mean:132 rms_max:713 peak:1605 transients:0

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4363152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-72 rssi_med:-67 rssi_max:-65
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-79 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-64 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-89 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-69 rssi_med:-61 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-63 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-79 rssi_med:-66 rssi_max:-58
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-71 rssi_med:-70 rssi_max:-69

---

@LAT94LON41 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4363152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3673 rate:8000
**ACOUSTIC** rms_mean:150 rms_max:1303 peak:3000 transients:3
**TRANSIENT** t_ms:4337711 stream:0xbb1177f2 wall:0 rms:1303

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4423152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-69 rssi_max:-60
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-82 rssi_med:-77 rssi_max:-74
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-65 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000011 proto:espnow n:28 rssi_min:-71 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-62 rssi_med:-60 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-57 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-71 rssi_max:-66
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-90 rssi_med:-86 rssi_max:-80

---

@LAT94LON42 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4423152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3619 rate:8000
**ACOUSTIC** rms_mean:219 rms_max:11779 peak:32768 transients:10
**TRANSIENT** t_ms:4377800 stream:0xbb1177f2 wall:0 rms:11779

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4483152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-86 rssi_med:-71 rssi_max:-66
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-68 rssi_max:-61
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-64 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-70 rssi_med:-60 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-60 rssi_med:-59 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-80 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-91 rssi_med:-85 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-71 rssi_med:-69 rssi_max:-69

---

@LAT94LON43 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4483152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3678 rate:8000
**ACOUSTIC** rms_mean:168 rms_max:1932 peak:3647 transients:2
**TRANSIENT** t_ms:4446869 stream:0xbb1177f2 wall:0 rms:1932

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4543152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-77 rssi_med:-73 rssi_max:-65
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-63 rssi_med:-63 rssi_max:-62
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-91 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-60 rssi_med:-59 rssi_max:-57
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-79 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-70 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-61 rssi_med:-60 rssi_max:-57

---

@LAT94LON44 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4543152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3662 rate:8000
**ACOUSTIC** rms_mean:144 rms_max:488 peak:959 transients:0

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4603152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-73 rssi_max:-66
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-91 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-64 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-62 rssi_med:-61 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-60 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-79 rssi_med:-70 rssi_max:-66
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-80 rssi_med:-77 rssi_max:-74

---

@LAT94LON45 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4603152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3617 rate:8000
**ACOUSTIC** rms_mean:141 rms_max:699 peak:1738 transients:0

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4615859 stream:0xbb1177f2 wall:0 window_ms:552707 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4663152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-77 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-63 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000012 proto:ble n:49 rssi_min:-81 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-91 rssi_med:-85 rssi_max:-82
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-72 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-75 rssi_med:-73 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-63 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-58 rssi_med:-57 rssi_max:-56

---

@LAT94LON46 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4663152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3664 rate:8000
**ACOUSTIC** rms_mean:141 rms_max:1128 peak:2776 transients:0

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4723152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-79 rssi_med:-69 rssi_max:-66
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-64 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-76 rssi_med:-73 rssi_max:-66
**LINK** peer:0x00000011 proto:ble n:53 rssi_min:-91 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-71 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-62 rssi_med:-61 rssi_max:-60
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-60 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-80 rssi_med:-78 rssi_max:-73

---

@LAT94LON47 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4723152 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3654 rate:8000
**ACOUSTIC** rms_mean:137 rms_max:465 peak:1032 transients:0

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4783152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-64 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000010 proto:ble n:49 rssi_min:-80 rssi_med:-68 rssi_max:-67
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-75 rssi_med:-69 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-61 rssi_med:-60 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-75 rssi_med:-73 rssi_max:-66
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-91 rssi_med:-86 rssi_max:-81
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-79 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-62 rssi_med:-60 rssi_max:-58

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4843152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:67 rssi_min:-79 rssi_med:-77 rssi_max:-73
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-75 rssi_med:-73 rssi_max:-66
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-80 rssi_med:-68 rssi_max:-66
**LINK** peer:0x00000011 proto:ble n:47 rssi_min:-90 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-61 rssi_med:-60 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-63 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-70 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-62 rssi_med:-61 rssi_max:-55

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4903152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:51 rssi_min:-90 rssi_med:-87 rssi_max:-81
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-63 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-68 rssi_max:-66
**LINK** peer:0x00000011 proto:espnow n:31 rssi_min:-70 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-61 rssi_med:-60 rssi_max:-59
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-75 rssi_med:-74 rssi_max:-66
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-62 rssi_med:-60 rssi_max:-58

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4963152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-80 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-68 rssi_max:-66
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-64 rssi_med:-62 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-90 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:40 rssi_min:-71 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-75 rssi_med:-73 rssi_max:-66
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-61 rssi_med:-60 rssi_max:-59
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-61 rssi_med:-60 rssi_max:-60

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5023152 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-68 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-90 rssi_med:-85 rssi_max:-81
**LINK** peer:0x00000012 proto:ble n:54 rssi_min:-80 rssi_med:-78 rssi_max:-73
**LINK** peer:0x00000011 proto:espnow n:40 rssi_min:-70 rssi_med:-69 rssi_max:-68
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-61 rssi_med:-60 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-73 rssi_max:-65
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-61 rssi_med:-60 rssi_max:-59
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-64 rssi_med:-62 rssi_max:-61

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5215858 stream:0xbb1177f2 wall:0 window_ms:599999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5876521 stream:0xbb1177f2 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-97
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5876521 stream:0xbb1177f2 wall:0 window_ms:60000 n:921
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6429943 stream:0xbb1177f2 wall:0 window_ms:553422 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7029942 stream:0xbb1177f2 wall:0 window_ms:599999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7137217 stream:0xbb1177f2 wall:0 window_ms:60001 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7137217 stream:0xbb1177f2 wall:0 window_ms:60001 n:927
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7690158 stream:0xbb1177f2 wall:0 window_ms:552941 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8290157 stream:0xbb1177f2 wall:0 window_ms:599999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,64677217947d,0283cce0e689,e6b32d2cea8b,84a329c78fec

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8877930 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:8877930 stream:0xbb1177f2 wall:0 window_ms:60000 n:926
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9431182 stream:0xbb1177f2 wall:0 window_ms:553252 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10031194 stream:0xbb1177f2 wall:0 window_ms:600012 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10318584 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:10318584 stream:0xbb1177f2 wall:0 window_ms:60000 n:934
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10871246 stream:0xbb1177f2 wall:0 window_ms:552662 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11471244 stream:0xbb1177f2 wall:0 window_ms:599998 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689,5ce28c488e0c

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11699263 stream:0xbb1177f2 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:11699263 stream:0xbb1177f2 wall:0 window_ms:60000 n:937
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12251831 stream:0xbb1177f2 wall:0 window_ms:552568 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12851895 stream:0xbb1177f2 wall:0 window_ms:600064 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,5ce28c488e0c

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13440096 stream:0xbb1177f2 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:13440096 stream:0xbb1177f2 wall:0 window_ms:60000 n:923
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13993438 stream:0xbb1177f2 wall:0 window_ms:553342 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:14593437 stream:0xbb1177f2 wall:0 window_ms:599999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,64677217947d,5ce28c488e0c,e6b32d2cea8b,84a329c78fec

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:14880934 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:14880934 stream:0xbb1177f2 wall:0 window_ms:60000 n:923
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:15434163 stream:0xbb1177f2 wall:0 window_ms:553229 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:16034160 stream:0xbb1177f2 wall:0 window_ms:599997 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689,5ce28c488e0c

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:16321671 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:16321671 stream:0xbb1177f2 wall:0 window_ms:60000 n:934
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:16874366 stream:0xbb1177f2 wall:0 window_ms:552695 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:17462377 stream:0xbb1177f2 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:17462377 stream:0xbb1177f2 wall:0 window_ms:60000 n:923
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:18015771 stream:0xbb1177f2 wall:0 window_ms:553394 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:18615770 stream:0xbb1177f2 wall:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,0283cce0e689

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:18940055 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:18940055 stream:0xbb1177f2 wall:0 window_ms:60000 n:924
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:19493330 stream:0xbb1177f2 wall:0 window_ms:553275 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:20093328 stream:0xbb1177f2 wall:0 window_ms:599998 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,64677217947d,5ce28c488e0c

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:20809384 stream:0xbb1177f2 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:20809384 stream:0xbb1177f2 wall:0 window_ms:60000 n:932
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:21362203 stream:0xbb1177f2 wall:0 window_ms:552819 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:21962517 stream:0xbb1177f2 wall:0 window_ms:600314 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d,5ce28c488e0c

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:22430146 stream:0xbb1177f2 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:22430146 stream:0xbb1177f2 wall:0 window_ms:60000 n:924
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:22983461 stream:0xbb1177f2 wall:0 window_ms:553315 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:23583479 stream:0xbb1177f2 wall:0 window_ms:600018 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,5ce28c488e0c

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:24230831 stream:0xbb1177f2 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**RUN** windows_since_last:1 reason:first max_run:1 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:24230831 stream:0xbb1177f2 wall:0 window_ms:60000 n:930
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:24783805 stream:0xbb1177f2 wall:0 window_ms:552974 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-94
**RUN** windows_since_last:1 reason:heartbeat max_run:1 core_n:3 core_m:5 core_windows:2
**CORE** entities:0

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:25384134 stream:0xbb1177f2 wall:0 window_ms:600329 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
**RUN** windows_since_last:1 reason:changed max_run:1 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689

---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:26019689 stream:0xbb1177f2 wall:0 window_ms:60000 n:922
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:27880402 stream:0xbb1177f2 wall:0 window_ms:60000 n:915
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:29694891 stream:0xbb1177f2 wall:0 window_ms:60000 n:922
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:31435588 stream:0xbb1177f2 wall:0 window_ms:60000 n:921
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:33236269 stream:0xbb1177f2 wall:0 window_ms:60000 n:913
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:34137786 stream:0xbb1177f2 wall:0 window_ms:60000 n:920
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:35758498 stream:0xbb1177f2 wall:0 window_ms:60000 n:918
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:37498518 stream:0xbb1177f2 wall:0 window_ms:60000 n:974
**MOTION** state:moving moving_permille:152 dev_mean_mg:31 dev_max_mg:592 moving_ms:9349
**RUN** windows_since_last:29 reason:changed max_run:30
**COVERED** state:still windows:28 n:26529 window_ms:1680020 moving_permille:0 dev_mean_mg:11 dev_max_mg:17 moving_ms:0 first_t_ms:35818498 last_t_ms:37438518 covered_by:@LAT95LON26

---

@LAT93LON1 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON26,derived_from@LAT95LON27

**TRANSITION** t_ms:37498518 stream:0xbb1177f2 wall:0 node:0x300 from:still to:moving dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:still t_ms:37438518 window_ms:60000 n:977 moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0 lane:@LAT95LON26+28
  @PERCEPT:after state:moving t_ms:37498518 window_ms:60000 n:974 moving_permille:152 dev_mean_mg:31 dev_max_mg:592 moving_ms:9349 lane:@LAT95LON27+0
**DELTA** edge:became d_permille:152 d_dev_mean_mg:20 d_dev_max_mg:578

---

@LAT95LON28 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:37620097 stream:0xbb1177f2 wall:0 window_ms:60000 n:920
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT91LON0 | sid:76dbf602 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:146
rev:1
sal:8
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:17 violated:1 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON1 | sid:2b4da8c8 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:160
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:16 violated:0 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON2 | sid:ca9b482d | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:160
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:16 violated:0 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON3 | sid:8a93826d | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:92
rev:1
sal:32
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:14 violated:4 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON4 | sid:4dd86ced | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:154
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000011 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:13 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON5 | sid:150da582 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:154
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000011 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:13 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON6 | sid:05e0a4f2 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:150
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000012 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:11 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON7 | sid:7256ea07 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:150
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000012 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:11 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline
