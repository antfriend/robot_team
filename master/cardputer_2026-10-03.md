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

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON2,senses@LAT0LON0

**OUTCOME** t_ms:26773469 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON1+0 observed_in:@LAT97LON2 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-46 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-45 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON1 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON22,senses@LAT0LON0

**OUTCOME** t_ms:28030043 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON2+0 observed_in:@LAT97LON22 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-52 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-49 delta:3 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON2 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON37,senses@LAT0LON0

**OUTCOME** t_ms:28932577 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON3+0 observed_in:@LAT97LON37 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-49 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xce6b6750 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x8a1565a4 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x67ea1389 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xfdaf75bf wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x642cef6b wall:0 t_ms:431045 node:0x300 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x9957bc73 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x7ced00dc wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x55e96c91 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xdf12e1d4 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xdcd3edce wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT93LON0 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON27,derived_from@LAT95LON28

**TRANSITION** t_ms:7812748 stream:0xdcd3edce wall:0 node:0x300 from:still to:moving dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:still t_ms:7752748 window_ms:60000 n:998 moving_permille:0 dev_mean_mg:12 dev_max_mg:20 moving_ms:0 lane:@LAT95LON27+9
  @PERCEPT:after state:moving t_ms:7812748 window_ms:60000 n:998 moving_permille:161 dev_mean_mg:60 dev_max_mg:5563 moving_ms:9664 lane:@LAT95LON28+0
**DELTA** edge:became d_permille:161 d_dev_mean_mg:48 d_dev_max_mg:5543

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x1c3a61ee wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x0c76a2a1 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xee98fca8 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xee98fca8 wall:0 t_ms:6989045 node:0x300 from:0x10
**REMAP** prev_stream:0x98fbaf08 prev_t_ms:5586 offset_ms:6983459 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:46 last_lon:45 t_ms:7440342 stream:0xee98fca8 wall:0 node:0x00000300

---


---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x88023c58 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:1 removed:48 last_lon:47 t_ms:15673 stream:0xe1f82632 wall:0 node:0x00000300

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:1 removed:48 last_lon:47 t_ms:4429700 stream:0x92fb56ae wall:0 node:0x00000300

---

@LAT92LON3 | created:0 | updated:0 | relates:testifies_about@LAT103LON16387,derived_from@LAT103LON343,senses@LAT0LON0

**OUTCOME** t_ms:7205408 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16387+0 observed_in:@LAT103LON343 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-60 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-61 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-41 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-44 delta:-2 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT92LON4 | created:0 | updated:0 | relates:testifies_about@LAT103LON16387,derived_from@LAT103LON345,senses@LAT0LON0

**OUTCOME** t_ms:7325408 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16387+2 observed_in:@LAT103LON345 band_dbm:6 met:3 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:2 reason:changed max_run:30
**COVERED-SPAN** windows:1 first_t_ms:7265408 last_t_ms:7265408 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000200 proto:ble verdict:met windows:1 observed_min:-55 observed_max:-55
**COVERED** peer:0x00000010 proto:ble verdict:met windows:1 observed_min:-66 observed_max:-66
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:1 observed_min:-42 observed_max:-42
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:1 observed_min:-47 observed_max:-47
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-66 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-59 delta:7 verdict:violated
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-40 delta:2 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-41 delta:6 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT92LON5 | created:0 | updated:0 | relates:testifies_about@LAT103LON16387,derived_from@LAT103LON346,senses@LAT0LON0

**OUTCOME** t_ms:7385408 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16387+3 observed_in:@LAT103LON346 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-59 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-41 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-42 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-56 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:0 stream:0x00000000 wall:0 node:0x00000300

---


---


---


---


---


---


---


---


---


---


---

@LAT92LON6 | created:0 | updated:0 | relates:testifies_about@LAT103LON16388,derived_from@LAT103LON349,senses@LAT0LON0

**OUTCOME** t_ms:7941919 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16388+0 observed_in:@LAT103LON349 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-59 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-38 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-38 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-42 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT92LON7 | created:0 | updated:0 | relates:testifies_about@LAT103LON16389,derived_from@LAT103LON379,senses@LAT0LON0

**OUTCOME** t_ms:9756012 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16389+0 observed_in:@LAT103LON379 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED-SPAN** windows:29 first_t_ms:8001919 last_t_ms:9696012 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000200 proto:ble verdict:met windows:29 observed_min:-55 observed_max:-54
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:29 observed_min:-42 observed_max:-41
**COVERED** peer:0x00000010 proto:ble verdict:met windows:29 observed_min:-59 observed_max:-59
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:29 observed_min:-38 observed_max:-38
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-59 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-38 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-38 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-42 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT91LON0 | sid:ab8f77ba | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:134
rev:3
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000100 proto:espnow node:0x300
**TOUCHED** t_ms:9816012 stream:0x92fb56ae wall:0 unix_s:0
**TALLY** met:3 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT91LON1 | sid:76dbf602 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:198
rev:3
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:ble node:0x300
**TOUCHED** t_ms:9816012 stream:0x92fb56ae wall:0 unix_s:0
**TALLY** met:35 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT91LON2 | sid:ca9b482d | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:180
rev:3
sal:8
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:9816012 stream:0x92fb56ae wall:0 unix_s:0
**TALLY** met:34 violated:1 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT91LON3 | sid:8a93826d | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:198
rev:3
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:espnow node:0x300
**TOUCHED** t_ms:9816012 stream:0x92fb56ae wall:0 unix_s:0
**TALLY** met:35 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT91LON4 | sid:2b4da8c8 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:198
rev:3
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TOUCHED** t_ms:9816012 stream:0x92fb56ae wall:0 unix_s:0
**TALLY** met:35 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:8 method:sequential_fold_from_baseline

---

@LAT103LON8228 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9308730 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:10242780 stream:0x92fb56ae wall:0 window_ms:606768 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-97
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,c2e94427adcf,5ce28c488e0c,980d67f79619,64677217947d
```

---

@LAT103LON8229 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10502093 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:11436143 stream:0x92fb56ae wall:0 window_ms:593363 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,84a329c78fec,64677217947d,980d67f79619,5ce28c488e0c,c2e94427adcf
said: 14 | **COVERED** windows:1 entities:8 window_ms:600000 first_t_ms:10842780 last_t_ms:10842780 covered_by:@LAT103LON8228
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94 windows:1
```

---

@LAT92LON8 | created:0 | updated:0 | relates:testifies_about@LAT103LON16390,derived_from@LAT103LON409,senses@LAT0LON0

**OUTCOME** t_ms:11556143 stream:0x92fb56ae wall:0 node:0x300 acting:@LAT103LON16390+0 observed_in:@LAT103LON409 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED-SPAN** windows:29 first_t_ms:9816012 last_t_ms:11496143 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000010 proto:ble verdict:met windows:29 observed_min:-61 observed_max:-57
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:29 observed_min:-43 observed_max:-40
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:29 observed_min:-41 observed_max:-38
**COVERED** peer:0x00000200 proto:ble verdict:met windows:29 observed_min:-56 observed_max:-54
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-54 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-59 delta:-2 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-40 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-41 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT103 observable:@LAT103 band_src:p90_of_still_windows

---

@LAT103LON8230 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10795104 ±21 frame:6000
said: 1 | **ENTWIN** t_ms:11729173 stream:0x92fb56ae wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8231 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11518948 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:12455030 stream:0x92fb56ae wall:0 window_ms:62000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON8232 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:7500
said: 1 | **ENTWIN** t_ms:13403057 stream:0x92fb56ae wall:0 window_ms:60000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON16393 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:7500
said: 1 | **MOTIONWIN** t_ms:13403057 stream:0x92fb56ae wall:0 window_ms:60000 n:924
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:20 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8233 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:11000
said: 1 | **ENTWIN** t_ms:46462 stream:0x0947153e wall:0 window_ms:60000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON16394 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:11000
said: 1 | **MOTIONWIN** t_ms:46462 stream:0x0947153e wall:0 window_ms:60000 n:870
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:36 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8234 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:51120 stream:0x2ee5fee1 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON16395 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:6000
said: 1 | **MOTIONWIN** t_ms:51120 stream:0x2ee5fee1 wall:0 window_ms:60000 n:948
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8235 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 62000 ±0 frame:8500
said: 1 | **ENTWIN** t_ms:50566 stream:0xc909d5a8 wall:0 window_ms:62000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON16396 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 62000 ±0 frame:8500
said: 1 | **MOTIONWIN** t_ms:50566 stream:0xc909d5a8 wall:0 window_ms:62000 n:906
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8236 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:7000
said: 1 | **ENTWIN** t_ms:333393 stream:0xc909d5a8 wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON16397 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:7000
said: 1 | **MOTIONWIN** t_ms:333393 stream:0xc909d5a8 wall:0 window_ms:60000 n:931
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:22 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8237 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 364347 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:476952 stream:0xc909d5a8 wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON16398 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 364347 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:476952 stream:0xc909d5a8 wall:0 window_ms:60000 n:931
said: 2 | **MOTION** state:still moving_permille:1 dev_mean_mg:10 dev_max_mg:316 moving_ms:60
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8238 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1517171 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:1629776 stream:0xc909d5a8 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 12 | **COVERED** windows:1 entities:10 window_ms:552823 first_t_ms:1029775 last_t_ms:1029775 covered_by:@LAT103LON8237
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-88 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
```

---

@LAT103LON8239 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2117171 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:2229776 stream:0xc909d5a8 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c,0283cce0e689
```

---

@LAT103LON8240 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2717171 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:2829776 stream:0xc909d5a8 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,7236bc441422,5ce28c488e0c,0283cce0e689
```

---

@LAT103LON8241 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3317171 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:3429776 stream:0xc909d5a8 wall:0 window_ms:600000 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 13 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,64677217947d,e6b32d2cea8b,5ce28c488e0c,0283cce0e689,aef9ff2626ac,7236bc441422
```

---

@LAT103LON16399 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3966515 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:4079120 stream:0xc909d5a8 wall:0 window_ms:60000 n:968
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28788 window_ms:1740063 moving_permille:0 dev_mean_mg:10 dev_max_mg:85 moving_ms:60 first_t_ms:2339057 last_t_ms:4019120 covered_by:@LAT103LON16399
```

---

@LAT103LON8242 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4517259 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:4629864 stream:0xc909d5a8 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-97
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689,64677217947d,7236bc441422,5ce28c488e0c
said: 13 | **COVERED** windows:1 entities:8 window_ms:600089 first_t_ms:4029865 last_t_ms:4029865 covered_by:@LAT103LON8241
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-88 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
```

---

@LAT103LON8243 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5117260 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:5229865 stream:0xc909d5a8 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,c2e94427adcf,5ce28c488e0c
```

---

@LAT103LON8244 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5717260 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:5829865 stream:0xc909d5a8 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,e6b32d2cea8b,5ce28c488e0c,0283cce0e689,980d67f79619,c2e94427adcf
```

---

@LAT103LON16400 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5766517 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:5879122 stream:0xc909d5a8 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:26 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28797 window_ms:1740002 moving_permille:0 dev_mean_mg:10 dev_max_mg:51 moving_ms:0 first_t_ms:4139120 last_t_ms:5819122 covered_by:@LAT103LON16399
```

---

@LAT103LON8245 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6317260 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:6429865 stream:0xc909d5a8 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-93
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,5ce28c488e0c,0283cce0e689,bc102f237ace
```

---

@LAT103LON8246 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9317260 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:9429865 stream:0xc909d5a8 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689,02c57d2f9717,5ce28c488e0c
said: 13 | **COVERED** windows:4 entities:10 window_ms:2400001 first_t_ms:7029865 last_t_ms:8829866 covered_by:@LAT103LON8245
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-39 windows:4
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-69 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-78 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-73 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-87 windows:4
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:3 rssi:-90 windows:3
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-92 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-90 windows:4
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-90 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2f9717 n:2 rssi:-94 windows:2
```

---

@LAT103LON8247 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9917261 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:10029866 stream:0xc909d5a8 wall:0 window_ms:600001 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,84a329c78fec,0283cce0e689,e6b32d2cea8b,02c57d2f9717
```

---

@LAT103LON8248 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10298572 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:10411196 stream:0xc909d5a8 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON16401 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 10298572 ±21 frame:4000
said: 1 | **MOTIONWIN** t_ms:10411196 stream:0xc909d5a8 wall:0 window_ms:60000 n:867
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:17 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON16402 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 10598527 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:10711196 stream:0xc909d5a8 wall:0 window_ms:60000 n:962
said: 2 | **MOTION** state:moving moving_permille:825 dev_mean_mg:310 dev_max_mg:1843 moving_ms:47647
said: 3 | **RUN** windows_since_last:5 reason:changed max_run:30
said: 4 | **COVERED** state:still windows:4 n:3948 window_ms:240000 moving_permille:0 dev_mean_mg:11 dev_max_mg:22 moving_ms:0 first_t_ms:10471196 last_t_ms:10651196 covered_by:@LAT103LON16401
```

---

@LAT103LON16403 | created:0 | updated:0

**motion transition**

```ttdb-episode
source: motionpercept
at: 10598527 ±0 frame:4000
said: 1 | **TRANSITION** t_ms:10711196 stream:0xc909d5a8 wall:0 node:0x300 from:still to:moving dt_ms:60000 dt_across_merge:0
said: 2 | @PERCEPT:before state:still t_ms:10651196 window_ms:60000 n:998 moving_permille:0 dev_mean_mg:10 dev_max_mg:16 moving_ms:0 lane:@LAT103LON16401+4
said: 3 | @PERCEPT:after state:moving t_ms:10711196 window_ms:60000 n:962 moving_permille:825 dev_mean_mg:310 dev_max_mg:1843 moving_ms:47647 lane:@LAT103LON16402+0
said: 4 | **DELTA** edge:became d_permille:825 d_dev_mean_mg:300 d_dev_max_mg:1827
```

---

@LAT103LON16404 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 10718527 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:10831196 stream:0xc909d5a8 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:19 moving_ms:0
said: 3 | **RUN** windows_since_last:2 reason:changed max_run:30
said: 4 | **COVERED** state:moving windows:1 n:995 window_ms:60000 moving_permille:682 dev_mean_mg:164 dev_max_mg:1051 moving_ms:40991 first_t_ms:10771196 last_t_ms:10771196 covered_by:@LAT103LON16402
```

---

@LAT103LON16405 | created:0 | updated:0

**motion transition**

```ttdb-episode
source: motionpercept
at: 10718527 ±0 frame:4000
said: 1 | **TRANSITION** t_ms:10831196 stream:0xc909d5a8 wall:0 node:0x300 from:moving to:still dt_ms:60000 dt_across_merge:0
said: 2 | @PERCEPT:before state:moving t_ms:10771196 window_ms:60000 n:995 moving_permille:682 dev_mean_mg:164 dev_max_mg:1051 moving_ms:40991 lane:@LAT103LON16402+1
said: 3 | @PERCEPT:after state:still t_ms:10831196 window_ms:60000 n:998 moving_permille:0 dev_mean_mg:11 dev_max_mg:19 moving_ms:0 lane:@LAT103LON16404+0
said: 4 | **DELTA** edge:became d_permille:-682 d_dev_mean_mg:-153 d_dev_max_mg:-1032
```

---

@LAT103LON8249 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11069050 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:11181716 stream:0xc909d5a8 wall:0 window_ms:61999 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON16406 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 11069050 ±21 frame:4000
said: 1 | **MOTIONWIN** t_ms:11181716 stream:0xc909d5a8 wall:0 window_ms:61999 n:899
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8250 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12141708 ±21 frame:4000
said: 1 | **ENTWIN** t_ms:12254416 stream:0xc909d5a8 wall:0 window_ms:60000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON16407 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 12141708 ±21 frame:4000
said: 1 | **MOTIONWIN** t_ms:12254416 stream:0xc909d5a8 wall:0 window_ms:60000 n:923
said: 2 | **MOTION** state:still moving_permille:18 dev_mean_mg:13 dev_max_mg:354 moving_ms:1020
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8251 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13295138 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:13407819 stream:0xc909d5a8 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,84a329c78fec,e6b32d2cea8b,5ce28c488e0c
said: 12 | **COVERED** windows:1 entities:7 window_ms:553403 first_t_ms:12807819 last_t_ms:12807819 covered_by:@LAT103LON8250
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
```

---

@LAT103LON8252 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13895139 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:14007820 stream:0xc909d5a8 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,5ce28c488e0c,84a329c78fec
```

---

@LAT103LON16408 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 13941735 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:14054416 stream:0xc909d5a8 wall:0 window_ms:60000 n:960
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28826 window_ms:1740000 moving_permille:0 dev_mean_mg:11 dev_max_mg:22 moving_ms:0 first_t_ms:12314416 last_t_ms:13994416 covered_by:@LAT103LON16407
```

---

@LAT103LON8253 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 14495140 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:14607821 stream:0xc909d5a8 wall:0 window_ms:600001 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689,5ce28c488e0c,84a329c78fec
```

---

@LAT103LON8254 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 15095140 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:15207821 stream:0xc909d5a8 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,5ce28c488e0c
```

---

@LAT103LON16409 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 15743728 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:15856409 stream:0xc909d5a8 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28800 window_ms:1741993 moving_permille:0 dev_mean_mg:11 dev_max_mg:16 moving_ms:0 first_t_ms:14114416 last_t_ms:15796409 covered_by:@LAT103LON16408
```

---

@LAT103LON8255 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 16295140 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:16407821 stream:0xc909d5a8 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,5ce28c488e0c,64677217947d,0283cce0e689
said: 12 | **COVERED** windows:1 entities:7 window_ms:600000 first_t_ms:15807821 last_t_ms:15807821 covered_by:@LAT103LON8254
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
```

---

@LAT103LON8256 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 16895140 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:17007821 stream:0xc909d5a8 wall:0 window_ms:600000 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 7 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,0283cce0e689,e6b32d2cea8b
```

---

@LAT103LON16410 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 17544005 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:17656686 stream:0xc909d5a8 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28794 window_ms:1740277 moving_permille:0 dev_mean_mg:11 dev_max_mg:16 moving_ms:0 first_t_ms:15916409 last_t_ms:17596686 covered_by:@LAT103LON16409
```

---

@LAT103LON8257 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 18095139 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:18207820 stream:0xc909d5a8 wall:0 window_ms:599998 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,84a329c78fec,e6b32d2cea8b,0283cce0e689
said: 11 | **COVERED** windows:1 entities:7 window_ms:600001 first_t_ms:17607822 last_t_ms:17607822 covered_by:@LAT103LON8256
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
```

---

@LAT103LON8258 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 18695140 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:18807821 stream:0xc909d5a8 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689
```

---

@LAT103LON8259 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 19295140 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:19407821 stream:0xc909d5a8 wall:0 window_ms:600000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON16411 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 19344005 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:19456686 stream:0xc909d5a8 wall:0 window_ms:60000 n:996
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28757 window_ms:1740000 moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0 first_t_ms:17716686 last_t_ms:19396686 covered_by:@LAT103LON16410
```

---

@LAT103LON8260 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 19895142 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:20007823 stream:0xc909d5a8 wall:0 window_ms:600002 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d
```

---

@LAT103LON8261 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 20495140 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:20607821 stream:0xc909d5a8 wall:0 window_ms:599998 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d,5ce28c488e0c
```

---

@LAT103LON720 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20664006 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:20776687 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-40 rssi_med:-34 rssi_max:-32
said: 3 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-22 rssi_med:-21 rssi_max:-19
said: 4 | 0x00000200 ble met predicted:-35 observed:-34
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-21 observed:-21
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON721 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 20724006 ±0 frame:4000
said: 1 | **LINKWIN** t_ms:20836687 stream:0xc909d5a8 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:22 rssi_min:-53 rssi_med:-39 rssi_max:-31
said: 3 | **LINK** peer:0x00000200 proto:espnow n:11 rssi_min:-36 rssi_med:-21 rssi_max:-18
said: 4 | 0x00000200 ble met predicted:-34 observed:-39
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-21 observed:-21
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON8262 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21095140 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:21207821 stream:0xc909d5a8 wall:0 window_ms:600000 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:7 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,64677217947d,e6b32d2cea8b,02c57d2e0f0d,5ce28c488e0c
```

---

@LAT103LON16412 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 21144006 ±0 frame:4000
said: 1 | **MOTIONWIN** t_ms:21256687 stream:0xc909d5a8 wall:0 window_ms:60000 n:999
said: 2 | **MOTION** state:still moving_permille:3 dev_mean_mg:12 dev_max_mg:211 moving_ms:180
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28803 window_ms:1740001 moving_permille:0 dev_mean_mg:11 dev_max_mg:51 moving_ms:0 first_t_ms:19516686 last_t_ms:21196687 covered_by:@LAT103LON16411
```

---

@LAT103LON8263 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21695139 ±0 frame:4000
said: 1 | **ENTWIN** t_ms:21807820 stream:0xc909d5a8 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,84a329c78fec,64677217947d,0283cce0e689
```

---

@LAT103LON8264 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:8000
said: 1 | **ENTWIN** t_ms:49320 stream:0x40bbc10f wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON16413 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:8000
said: 1 | **MOTIONWIN** t_ms:49320 stream:0x40bbc10f wall:0 window_ms:60000 n:917
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON722 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 197267 ±0 frame:8000
said: 1 | **LINKWIN** t_ms:186587 stream:0x40bbc10f wall:0 window_ms:197267
said: 2 | **LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-40 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000200 proto:ble n:2 rssi_min:-56 rssi_med:-56 rssi_max:-55
```

---

@LAT103LON723 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 36362 ±21 frame:5000
said: 1 | **LINKWIN** t_ms:246587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:34 rssi_min:-72 rssi_med:-63 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:espnow n:8 rssi_min:-53 rssi_med:-51 rssi_max:-44
said: 4 | 0x00000200 espnow violated predicted:-40 observed:-51
percept: 4 | 0x00000200 | link_stable | espnow | - | -
said: 5 | 0x00000200 ble violated predicted:-56 observed:-63
percept: 5 | 0x00000200 | link_stable | ble | - | -
```

---

@LAT103LON724 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 42580 ±22 frame:5000
said: 1 | **LINKWIN** t_ms:306587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:10 rssi_min:-70 rssi_med:-59 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:ble n:38 rssi_min:-81 rssi_med:-59 rssi_max:-55
said: 4 | 0x00000200 ble met predicted:-63 observed:-59
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow violated predicted:-51 observed:-59
percept: 5 | 0x00000200 | link_stable | espnow | - | -
```

---

@LAT103LON725 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 102580 ±25 frame:5000
said: 1 | **LINKWIN** t_ms:366587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:43 rssi_min:-79 rssi_med:-58 rssi_max:-54
said: 3 | **LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-61 rssi_med:-48 rssi_max:-46
said: 4 | 0x00000200 espnow violated predicted:-59 observed:-48
percept: 4 | 0x00000200 | link_stable | espnow | - | -
said: 5 | 0x00000200 ble met predicted:-59 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON726 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 162580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:426587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-58 rssi_med:-43 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-70 rssi_med:-56 rssi_max:-50
said: 4 | 0x00000200 ble met predicted:-58 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-48 observed:-43
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON727 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 222580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:486587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-56 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-46 rssi_med:-42 rssi_max:-39
said: 4 | 0x00000200 espnow met predicted:-43 observed:-42
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-56 observed:-56
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON728 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 282580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:546587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-47 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-72 rssi_med:-55 rssi_max:-51
said: 4 | 0x00000200 ble met predicted:-56 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON729 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 342580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:606587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-64 rssi_med:-47 rssi_max:-43
said: 3 | **LINK** peer:0x00000010 proto:ble n:49 rssi_min:-82 rssi_med:-64 rssi_max:-56
said: 4 | **LINK** peer:0x00000100 proto:espnow n:19 rssi_min:-35 rssi_med:-33 rssi_max:-32
said: 5 | 0x00000200 espnow unobserved predicted:-42 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | ? | -
said: 6 | 0x00000200 ble unobserved predicted:-55 observed:-55
percept: 6 | 0x00000200 | link_stable | ble | ? | -
```

---

@LAT103LON730 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 402580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:666587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-63 rssi_max:-57
said: 3 | **LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-59 rssi_med:-50 rssi_max:-45
said: 4 | **LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-35 rssi_med:-33 rssi_max:-32
said: 5 | 0x00000010 espnow met predicted:-47 observed:-50
percept: 5 | 0x00000010 | link_stable | espnow | + | -
said: 6 | 0x00000010 ble met predicted:-64 observed:-63
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000100 espnow met predicted:-33 observed:-33
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON731 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 462580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:726587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-58 rssi_med:-47 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-62 rssi_max:-55
said: 4 | **LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-37 rssi_med:-33 rssi_max:-32
said: 5 | 0x00000010 ble met predicted:-63 observed:-62
percept: 5 | 0x00000010 | link_stable | ble | + | -
said: 6 | 0x00000010 espnow met predicted:-50 observed:-47
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-33 observed:-33
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON732 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 522580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:786587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-50 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000010 proto:ble n:47 rssi_min:-69 rssi_med:-56 rssi_max:-53
said: 4 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-36 rssi_med:-34 rssi_max:-31
said: 5 | 0x00000010 espnow met predicted:-47 observed:-42
percept: 5 | 0x00000010 | link_stable | espnow | + | -
said: 6 | 0x00000010 ble met predicted:-62 observed:-56
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000100 espnow met predicted:-33 observed:-34
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON733 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 582580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:846587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-43 rssi_med:-34 rssi_max:-31
said: 3 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-56 rssi_med:-47 rssi_max:-43
said: 4 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-63 rssi_max:-53
said: 5 | 0x00000010 espnow met predicted:-42 observed:-47
percept: 5 | 0x00000010 | link_stable | espnow | + | -
said: 6 | 0x00000010 ble violated predicted:-56 observed:-63
percept: 6 | 0x00000010 | link_stable | ble | - | -
said: 7 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON734 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 642580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:906587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-50 rssi_med:-45 rssi_max:-40
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-60 rssi_max:-55
said: 4 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-39 rssi_med:-33 rssi_max:-31
said: 5 | 0x00000100 espnow met predicted:-34 observed:-33
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000010 espnow met predicted:-47 observed:-45
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-63 observed:-60
percept: 7 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON735 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 702580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:966587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:70 rssi_min:-78 rssi_med:-63 rssi_max:-55
said: 3 | **LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-64 rssi_med:-45 rssi_max:-42
said: 4 | **LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-39 rssi_med:-33 rssi_max:-31
said: 5 | 0x00000010 espnow met predicted:-45 observed:-45
percept: 5 | 0x00000010 | link_stable | espnow | + | -
said: 6 | 0x00000010 ble met predicted:-60 observed:-63
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000100 espnow met predicted:-33 observed:-33
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON736 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 762580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1026587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-60 rssi_med:-46 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-36 rssi_med:-34 rssi_max:-31
said: 4 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-63 rssi_max:-55
said: 5 | 0x00000010 ble met predicted:-63 observed:-63
percept: 5 | 0x00000010 | link_stable | ble | + | -
said: 6 | 0x00000010 espnow met predicted:-45 observed:-46
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-33 observed:-34
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON737 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 822580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1086587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-67 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-59 rssi_med:-51 rssi_max:-45
said: 4 | **LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-50 rssi_med:-37 rssi_max:-33
said: 5 | 0x00000010 espnow met predicted:-46 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
said: 6 | 0x00000100 espnow met predicted:-34 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-63 observed:-67
percept: 7 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON25116 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 865314 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1129321 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3739 rate:8000
said: 2 | **ACOUSTIC** rms_mean:219 rms_max:4162 peak:11973 transients:20
said: 3 | **TRANSIENT** t_ms:1117591 stream:0x40bbc10f wall:0 rms:3119
```

---

@LAT103LON738 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 882580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1146587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-72 rssi_med:-57 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-40 rssi_med:-35 rssi_max:-32
said: 4 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-84 rssi_med:-68 rssi_max:-57
said: 5 | 0x00000010 ble met predicted:-67 observed:-68
percept: 5 | 0x00000010 | link_stable | ble | + | -
said: 6 | 0x00000010 espnow met predicted:-51 observed:-57
percept: 6 | 0x00000010 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-35
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON25117 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 925314 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1189321 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:183 rms_max:2729 peak:13297 transients:11
said: 3 | **TRANSIENT** t_ms:1152538 stream:0x40bbc10f wall:0 rms:2729
```

---

@LAT103LON8265 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 939030 ±0 frame:5000
said: 1 | **ENTWIN** t_ms:1203037 stream:0x40bbc10f wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec
said: 11 | **COVERED** windows:1 entities:8 window_ms:553717 first_t_ms:603037 last_t_ms:603037 covered_by:@LAT103LON8264
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
```

---

@LAT103LON739 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 942580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1206587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-62 rssi_med:-48 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-80 rssi_med:-64 rssi_max:-50
said: 4 | **LINK** peer:0x00000100 proto:espnow n:30 rssi_min:-37 rssi_med:-34 rssi_max:-31
said: 5 | 0x00000010 espnow violated predicted:-57 observed:-48
percept: 5 | 0x00000010 | link_stable | espnow | - | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-34
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000010 ble met predicted:-68 observed:-64
percept: 7 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON25118 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 985314 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1249321 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3733 rate:8000
said: 2 | **ACOUSTIC** rms_mean:96 rms_max:597 peak:3170 transients:0
```

---

@LAT103LON740 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1002580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1266587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:29 rssi_min:-83 rssi_med:-57 rssi_max:-47
said: 3 | **LINK** peer:0x00000010 proto:espnow n:10 rssi_min:-54 rssi_med:-48 rssi_max:-38
said: 4 | 0x00000010 espnow met predicted:-48 observed:-48
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble violated predicted:-64 observed:-57
percept: 5 | 0x00000010 | link_stable | ble | - | -
said: 6 | 0x00000100 espnow unobserved predicted:-34 observed:-34
percept: 6 | 0x00000100 | link_stable | espnow | ? | -
```

---

@LAT103LON25119 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1045314 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1309321 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3735 rate:8000
said: 2 | **ACOUSTIC** rms_mean:159 rms_max:3070 peak:7354 transients:13
said: 3 | **TRANSIENT** t_ms:1302963 stream:0x40bbc10f wall:0 rms:3070
```

---

@LAT103LON741 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1062580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1326587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-82 rssi_med:-57 rssi_max:-47
said: 3 | **LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-62 rssi_med:-43 rssi_max:-37
said: 4 | 0x00000010 ble met predicted:-57 observed:-57
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-48 observed:-43
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25120 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1105314 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1369321 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3725 rate:8000
said: 2 | **ACOUSTIC** rms_mean:184 rms_max:1027 peak:2392 transients:3
said: 3 | **TRANSIENT** t_ms:1368267 stream:0x40bbc10f wall:0 rms:1027
```

---

@LAT103LON742 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1122580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1386587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-82 rssi_med:-57 rssi_max:-49
said: 3 | **LINK** peer:0x00000010 proto:espnow n:11 rssi_min:-67 rssi_med:-43 rssi_max:-42
said: 4 | 0x00000010 ble met predicted:-57 observed:-57
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-43 observed:-43
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25121 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1165314 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1429321 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:112 rms_max:1841 peak:5206 transients:5
said: 3 | **TRANSIENT** t_ms:1418129 stream:0x40bbc10f wall:0 rms:1841
```

---

@LAT103LON743 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1182580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1446587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:49 rssi_min:-81 rssi_med:-56 rssi_max:-50
said: 3 | **LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-52 rssi_med:-48 rssi_max:-40
said: 4 | 0x00000010 ble met predicted:-57 observed:-56
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-43 observed:-48
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25122 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1225315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1489322 stream:0x40bbc10f wall:0 window_ms:60001 blocks:3737 rate:8000
said: 2 | **ACOUSTIC** rms_mean:231 rms_max:1250 peak:2542 transients:17
said: 3 | **TRANSIENT** t_ms:1460461 stream:0x40bbc10f wall:0 rms:1076
```

---

@LAT103LON744 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1242580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1506587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-52 rssi_med:-47 rssi_max:-36
said: 3 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-82 rssi_med:-57 rssi_max:-49
said: 4 | 0x00000010 ble met predicted:-56 observed:-57
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-48 observed:-47
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25123 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1285315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1549322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3611 rate:8000
said: 2 | **ACOUSTIC** rms_mean:132 rms_max:3499 peak:24730 transients:10
said: 3 | **TRANSIENT** t_ms:1501164 stream:0x40bbc10f wall:0 rms:1510
```

---

@LAT103LON745 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1302580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1566587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-57 rssi_max:-46
said: 3 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-49 rssi_med:-43 rssi_max:-37
said: 4 | 0x00000010 espnow met predicted:-47 observed:-43
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble met predicted:-57 observed:-57
percept: 5 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON25124 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1345315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1609322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3737 rate:8000
said: 2 | **ACOUSTIC** rms_mean:190 rms_max:10579 peak:32768 transients:27
said: 3 | **TRANSIENT** t_ms:1588995 stream:0x40bbc10f wall:0 rms:10579
```

---

@LAT103LON746 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1362580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1626587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:14 rssi_min:-70 rssi_med:-58 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:3 rssi_min:-45 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000011 proto:espnow n:13 rssi_min:-45 rssi_med:-37 rssi_max:-36
said: 5 | **LINK** peer:0x00000011 proto:ble n:45 rssi_min:-73 rssi_med:-54 rssi_max:-48
said: 6 | 0x00000010 ble met predicted:-57 observed:-58
percept: 6 | 0x00000010 | link_stable | ble | + | -
said: 7 | 0x00000010 espnow met predicted:-43 observed:-40
percept: 7 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25125 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1405315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1669322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3733 rate:8000
said: 2 | **ACOUSTIC** rms_mean:182 rms_max:1747 peak:2952 transients:6
said: 3 | **TRANSIENT** t_ms:1611197 stream:0x40bbc10f wall:0 rms:1747
```

---

@LAT103LON747 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1422580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1686587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-82 rssi_med:-54 rssi_max:-47
said: 3 | **LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-42 rssi_med:-36 rssi_max:-34
said: 4 | 0x00000010 ble unobserved predicted:-58 observed:-58
percept: 4 | 0x00000010 | link_stable | ble | ? | -
said: 5 | 0x00000010 espnow unobserved predicted:-40 observed:-40
percept: 5 | 0x00000010 | link_stable | espnow | ? | -
said: 6 | 0x00000011 espnow met predicted:-37 observed:-36
percept: 6 | 0x00000011 | link_stable | espnow | + | -
said: 7 | 0x00000011 ble met predicted:-54 observed:-54
percept: 7 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON25126 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1465315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1729322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:301 rms_max:1464 peak:4339 transients:1
said: 3 | **TRANSIENT** t_ms:1689349 stream:0x40bbc10f wall:0 rms:1111
```

---

@LAT103LON748 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1482580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1746587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:9 rssi_min:-47 rssi_med:-39 rssi_max:-38
said: 3 | **LINK** peer:0x00000011 proto:ble n:30 rssi_min:-58 rssi_med:-53 rssi_max:-49
said: 4 | 0x00000011 ble met predicted:-54 observed:-53
percept: 4 | 0x00000011 | link_stable | ble | + | -
said: 5 | 0x00000011 espnow met predicted:-36 observed:-39
percept: 5 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON25127 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1525315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1789322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3744 rate:8000
said: 2 | **ACOUSTIC** rms_mean:114 rms_max:1116 peak:2364 transients:3
said: 3 | **TRANSIENT** t_ms:1733879 stream:0x40bbc10f wall:0 rms:1116
```

---

@LAT103LON8266 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1539030 ±0 frame:5000
said: 1 | **ENTWIN** t_ms:1803037 stream:0x40bbc10f wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 12 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,84a329c78fec,7236bc441422
```

---

@LAT103LON749 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1542580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1806587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-43 rssi_med:-39 rssi_max:-36
said: 3 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-80 rssi_med:-56 rssi_max:-48
said: 4 | 0x00000011 espnow met predicted:-39 observed:-39
percept: 4 | 0x00000011 | link_stable | espnow | + | -
said: 5 | 0x00000011 ble met predicted:-53 observed:-56
percept: 5 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON16414 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 1585315 ±0 frame:5000
said: 1 | **MOTIONWIN** t_ms:1849322 stream:0x40bbc10f wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:16 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28764 window_ms:1740002 moving_permille:1 dev_mean_mg:11 dev_max_mg:276 moving_ms:2220 first_t_ms:109320 last_t_ms:1789322 covered_by:@LAT103LON16413
```

---

@LAT103LON25128 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1585315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1849322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3737 rate:8000
said: 2 | **ACOUSTIC** rms_mean:352 rms_max:1550 peak:2527 transients:56
said: 3 | **TRANSIENT** t_ms:1813765 stream:0x40bbc10f wall:0 rms:1550
```

---

@LAT103LON750 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1602580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1866587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-61 rssi_med:-55 rssi_max:-46
said: 3 | **LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-43 rssi_med:-39 rssi_max:-36
said: 4 | 0x00000011 espnow met predicted:-39 observed:-39
percept: 4 | 0x00000011 | link_stable | espnow | + | -
said: 5 | 0x00000011 ble met predicted:-56 observed:-55
percept: 5 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON25129 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1645315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1909322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3720 rate:8000
said: 2 | **ACOUSTIC** rms_mean:171 rms_max:801 peak:1355 transients:0
```

---

@LAT103LON751 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1662580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1926587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-80 rssi_med:-53 rssi_max:-47
said: 3 | **LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-40 rssi_med:-36 rssi_max:-33
said: 4 | 0x00000011 ble met predicted:-55 observed:-53
percept: 4 | 0x00000011 | link_stable | ble | + | -
said: 5 | 0x00000011 espnow met predicted:-39 observed:-36
percept: 5 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON25130 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1705315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:1969322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3740 rate:8000
said: 2 | **ACOUSTIC** rms_mean:159 rms_max:1104 peak:2454 transients:1
said: 3 | **TRANSIENT** t_ms:1947985 stream:0x40bbc10f wall:0 rms:1104
```

---

@LAT103LON752 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1722580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:1986587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:50 rssi_min:-81 rssi_med:-53 rssi_max:-46
said: 3 | **LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-46 rssi_med:-37 rssi_max:-34
said: 4 | **LINK** peer:0x00000012 proto:ble n:3 rssi_min:-63 rssi_med:-63 rssi_max:-53
said: 5 | 0x00000011 ble met predicted:-53 observed:-53
percept: 5 | 0x00000011 | link_stable | ble | + | -
said: 6 | 0x00000011 espnow met predicted:-36 observed:-37
percept: 6 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON25131 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1765315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:2029322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3732 rate:8000
said: 2 | **ACOUSTIC** rms_mean:156 rms_max:11584 peak:32768 transients:19
said: 3 | **TRANSIENT** t_ms:1977753 stream:0x40bbc10f wall:0 rms:11584
```

---

@LAT103LON753 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1782580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:2046587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-82 rssi_med:-54 rssi_max:-47
said: 3 | **LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-42 rssi_med:-36 rssi_max:-33
said: 4 | 0x00000011 ble unobserved predicted:-53 observed:-53
percept: 4 | 0x00000011 | link_stable | ble | ? | -
said: 5 | 0x00000011 espnow unobserved predicted:-37 observed:-37
percept: 5 | 0x00000011 | link_stable | espnow | ? | -
said: 6 | 0x00000012 ble violated predicted:-63 observed:-54
percept: 6 | 0x00000012 | link_stable | ble | - | -
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:96 half_life_ms:600000 reinforced:257 last_ms:1190998
t_ms:2078531 stream:0x40bbc10f wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:46 half_life_ms:600000 reinforced:36 last_ms:551886
t_ms:2078531 stream:0x40bbc10f wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:149 half_life_ms:600000 reinforced:267 last_ms:1587261
t_ms:2078531 stream:0x40bbc10f wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:233 half_life_ms:600000 reinforced:64 last_ms:1983964
t_ms:2078531 stream:0x40bbc10f wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:249 half_life_ms:600000 reinforced:17 last_ms:2056754
t_ms:2078531 stream:0x40bbc10f wall:0

---

@LAT103LON25132 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1825315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:2089322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3491 rate:8000
said: 2 | **ACOUSTIC** rms_mean:168 rms_max:15622 peak:32768 transients:17
said: 3 | **TRANSIENT** t_ms:2087889 stream:0x40bbc10f wall:0 rms:15622
```

---

@LAT103LON754 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1842580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:2106587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:41 rssi_min:-77 rssi_med:-52 rssi_max:-47
said: 3 | **LINK** peer:0x00000012 proto:espnow n:8 rssi_min:-44 rssi_med:-36 rssi_max:-35
said: 4 | 0x00000012 ble met predicted:-54 observed:-52
percept: 4 | 0x00000012 | link_stable | ble | + | -
said: 5 | 0x00000012 espnow met predicted:-36 observed:-36
percept: 5 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON25133 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1885315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:2149322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3742 rate:8000
said: 2 | **ACOUSTIC** rms_mean:206 rms_max:7256 peak:8123 transients:10
said: 3 | **TRANSIENT** t_ms:2131294 stream:0x40bbc10f wall:0 rms:7256
```

---

@LAT103LON755 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1902580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:2166587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:13 rssi_min:-38 rssi_med:-37 rssi_max:-34
said: 3 | **LINK** peer:0x00000012 proto:ble n:48 rssi_min:-57 rssi_med:-52 rssi_max:-46
said: 4 | 0x00000012 ble met predicted:-52 observed:-52
percept: 4 | 0x00000012 | link_stable | ble | + | -
said: 5 | 0x00000012 espnow met predicted:-36 observed:-37
percept: 5 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON25134 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 1945315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:2209322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3735 rate:8000
said: 2 | **ACOUSTIC** rms_mean:234 rms_max:5047 peak:9852 transients:10
said: 3 | **TRANSIENT** t_ms:2149868 stream:0x40bbc10f wall:0 rms:5047
```

---

@LAT103LON756 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1962580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:2226587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-58 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-40 rssi_med:-39 rssi_max:-39
said: 4 | 0x00000012 espnow met predicted:-37 observed:-39
percept: 4 | 0x00000012 | link_stable | espnow | + | -
said: 5 | 0x00000012 ble met predicted:-52 observed:-51
percept: 5 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON25135 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 2005315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:2269322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:256 rms_max:17353 peak:32768 transients:32
said: 3 | **TRANSIENT** t_ms:2229241 stream:0x40bbc10f wall:0 rms:17353
```

---

@LAT103LON757 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2022580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:2286587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-57 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 4 | 0x00000012 ble met predicted:-51 observed:-55
percept: 4 | 0x00000012 | link_stable | ble | + | -
said: 5 | 0x00000012 espnow met predicted:-39 observed:-39
percept: 5 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON25136 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 2065315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:2329322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3739 rate:8000
said: 2 | **ACOUSTIC** rms_mean:134 rms_max:1884 peak:2424 transients:2
said: 3 | **TRANSIENT** t_ms:2300353 stream:0x40bbc10f wall:0 rms:1884
```

---

@LAT103LON758 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2082580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:2346587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-80 rssi_med:-54 rssi_max:-50
said: 3 | **LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-42 rssi_med:-38 rssi_max:-37
said: 4 | 0x00000012 ble met predicted:-55 observed:-54
percept: 4 | 0x00000012 | link_stable | ble | + | -
said: 5 | 0x00000012 espnow met predicted:-39 observed:-38
percept: 5 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON25137 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 2125315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:2389322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3737 rate:8000
said: 2 | **ACOUSTIC** rms_mean:165 rms_max:3527 peak:8221 transients:15
said: 3 | **TRANSIENT** t_ms:2358732 stream:0x40bbc10f wall:0 rms:3046
```

---

@LAT103LON8267 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2139031 ±0 frame:5000
said: 1 | **ENTWIN** t_ms:2403038 stream:0x40bbc10f wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:bc3e073874d8 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,7236bc441422,84a329c78fec,0283cce0e689,5ce28c488e0c
```

---

@LAT103LON759 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2142580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:2406587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-82 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-41 rssi_med:-39 rssi_max:-38
said: 4 | 0x00000012 ble met predicted:-54 observed:-55
percept: 4 | 0x00000012 | link_stable | ble | + | -
said: 5 | 0x00000012 espnow met predicted:-38 observed:-39
percept: 5 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT104LON144 | created:0 | updated:0

**carried through @LAT103LON719**

```ttdb-carried
through: 719
through: 8227
through: 16392
through: 25115
carried: 479 2 680 404 | 0x00000200 | link_stable | espnow
carried: 542 6 904 417 | 0x00000200 | link_stable | ble
carried: 266 3 622 138 | 0x00000100 | link_stable | espnow
carried: 382 6 742 257 | 0x00000010 | link_stable | ble
carried: 373 13 739 256 | 0x00000010 | link_stable | espnow
carried: 22 0 22 26 | 0x00000011 | link_stable | ble
carried: 19 3 22 26 | 0x00000011 | link_stable | espnow
carried: 44 1 45 47 | 0x00000012 | link_stable | ble
carried: 42 2 44 45 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON25138 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 2185315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:2449322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3586 rate:8000
said: 2 | **ACOUSTIC** rms_mean:181 rms_max:5831 peak:6343 transients:17
said: 3 | **TRANSIENT** t_ms:2398644 stream:0x40bbc10f wall:0 rms:5831
```

---

@LAT103LON760 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2202580 ±0 frame:5000
said: 1 | **LINKWIN** t_ms:2466587 stream:0x40bbc10f wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-57 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-44 rssi_med:-39 rssi_max:-39
said: 4 | 0x00000012 ble met predicted:-55 observed:-53
percept: 4 | 0x00000012 | link_stable | ble | + | -
said: 5 | 0x00000012 espnow met predicted:-39 observed:-39
percept: 5 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON25139 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 2245315 ±0 frame:5000
said: 1 | **ACOUSTICWIN** t_ms:2509322 stream:0x40bbc10f wall:0 window_ms:60000 blocks:3732 rate:8000
said: 2 | **ACOUSTIC** rms_mean:139 rms_max:6514 peak:32768 transients:10
said: 3 | **TRANSIENT** t_ms:2462286 stream:0x40bbc10f wall:0 rms:6514
```
