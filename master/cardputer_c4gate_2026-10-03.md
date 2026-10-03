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

@LAT103LON16415 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 124031 ±0 frame:5500
said: 1 | **MOTIONWIN** t_ms:115881 stream:0x9afbb748 wall:0 window_ms:89508 n:2
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:3 dev_max_mg:4 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8268 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 134380 ±0 frame:5500
said: 1 | **ENTWIN** t_ms:126230 stream:0x9afbb748 wall:0 window_ms:99857 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:923badc7ab14 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON8269 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1330379 ±0 frame:5500
said: 1 | **ENTWIN** t_ms:1322229 stream:0x9afbb748 wall:0 window_ms:600004 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 8 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 9 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,0283cce0e689
said: 10 | **COVERED** windows:1 entities:8 window_ms:595995 first_t_ms:722225 last_t_ms:722225 covered_by:@LAT103LON8268
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
```

---

@LAT103LON8270 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1932370 ±0 frame:5500
said: 1 | **ENTWIN** t_ms:1924220 stream:0x9afbb748 wall:0 window_ms:601991 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,84a329c78fec,0283cce0e689,5ce28c488e0c
```

---

@LAT103LON16416 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 1940660 ±0 frame:5500
said: 1 | **MOTIONWIN** t_ms:1932510 stream:0x9afbb748 wall:0 window_ms:60000 n:463
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:5 dev_max_mg:7 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:13033 window_ms:1756629 moving_permille:0 dev_mean_mg:4 dev_max_mg:497 moving_ms:60 first_t_ms:177458 last_t_ms:1872510 covered_by:@LAT103LON16415
```

---

@LAT103LON8271 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2532370 ±0 frame:5500
said: 1 | **ENTWIN** t_ms:2524220 stream:0x9afbb748 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,aef9ff2626ac,84a329c78fec,0283cce0e689,5ce28c488e0c
```

---

@LAT103LON8272 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3184037 ±0 frame:5500
seq: 2
said: 1 | **ENTWIN** t_ms:3183036 stream:0x9afbb748 wall:0 window_ms:60000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON16417 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3184037 ±0 frame:5500
seq: 3
said: 1 | **MOTIONWIN** t_ms:3183036 stream:0x9afbb748 wall:0 window_ms:60000 n:919
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:5 dev_max_mg:9 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON16418 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3434941 ±214768 frame:5500
seq: 10
said: 1 | **MOTIONWIN** t_ms:3434465 stream:0x9afbb748 wall:0 window_ms:62306 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:7 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8273 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3475187 ±0 frame:5500
seq: 12
said: 1 | **ENTWIN** t_ms:3474488 stream:0x9afbb748 wall:0 window_ms:102552 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON16419 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3926951 ±0 frame:5500
seq: 28
said: 1 | **MOTIONWIN** t_ms:3925983 stream:0x9afbb748 wall:0 window_ms:60001 n:996
said: 2 | **MOTION** state:moving moving_permille:119 dev_mean_mg:53 dev_max_mg:4618 moving_ms:7140
said: 3 | **RUN** windows_since_last:8 reason:changed max_run:30
said: 4 | **COVERED** state:still windows:7 n:4027 window_ms:432009 moving_permille:0 dev_mean_mg:6 dev_max_mg:155 moving_ms:126 first_t_ms:3493973 last_t_ms:3865982 covered_by:@LAT103LON16418
```

---

@LAT103LON16420 | created:0 | updated:0

**motion transition**

```ttdb-episode
source: motionpercept
at: 3926951 ±0 frame:5500
seq: 29
said: 1 | **TRANSITION** t_ms:3925983 stream:0x9afbb748 wall:0 node:0x300 from:still to:moving dt_ms:60001 dt_across_merge:0
said: 2 | @PERCEPT:before state:still t_ms:3865982 window_ms:60001 n:996 moving_permille:2 dev_mean_mg:6 dev_max_mg:155 moving_ms:126 lane:@LAT103LON16418+7
said: 3 | @PERCEPT:after state:moving t_ms:3925983 window_ms:60001 n:996 moving_permille:119 dev_mean_mg:53 dev_max_mg:4618 moving_ms:7140 lane:@LAT103LON16419+0
said: 4 | **DELTA** edge:became d_permille:117 d_dev_mean_mg:47 d_dev_max_mg:4463
```

---

@LAT103LON16421 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3986951 ±0 frame:5500
seq: 32
said: 1 | **MOTIONWIN** t_ms:3985983 stream:0x9afbb748 wall:0 window_ms:60000 n:996
said: 2 | **MOTION** state:still moving_permille:24 dev_mean_mg:11 dev_max_mg:493 moving_ms:1440
said: 3 | **RUN** windows_since_last:1 reason:changed max_run:30
```

---

@LAT103LON16422 | created:0 | updated:0

**motion transition**

```ttdb-episode
source: motionpercept
at: 3986951 ±0 frame:5500
seq: 33
said: 1 | **TRANSITION** t_ms:3985983 stream:0x9afbb748 wall:0 node:0x300 from:moving to:still dt_ms:60000 dt_across_merge:0
said: 2 | @PERCEPT:before state:moving t_ms:3925983 window_ms:60001 n:996 moving_permille:119 dev_mean_mg:53 dev_max_mg:4618 moving_ms:7140 lane:@LAT103LON16419+0
said: 3 | @PERCEPT:after state:still t_ms:3985983 window_ms:60000 n:996 moving_permille:24 dev_mean_mg:11 dev_max_mg:493 moving_ms:1440 lane:@LAT103LON16421+0
said: 4 | **DELTA** edge:became d_permille:-95 d_dev_mean_mg:-42 d_dev_max_mg:-4125
```

---

@LAT103LON8274 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4673790 ±0 frame:5500
seq: 57
follows: 0x00000010:2
said: 1 | **ENTWIN** t_ms:4672822 stream:0x9afbb748 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,84a329c78fec
said: 14 | **COVERED** windows:1 entities:8 window_ms:598602 first_t_ms:4072821 last_t_ms:4072821 covered_by:@LAT103LON8273
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-29 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92 windows:1
```

---

@LAT103LON8275 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5273789 ±0 frame:5500
seq: 78
follows: 0x00000010:12
said: 1 | **ENTWIN** t_ms:5272821 stream:0x9afbb748 wall:0 window_ms:599999 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 13 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,84a329c78fec,64677217947d,0283cce0e689
```

---

@LAT103LON16423 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5786953 ±0 frame:5500
seq: 96
follows: 0x00000010:22
said: 1 | **MOTIONWIN** t_ms:5785985 stream:0x9afbb748 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:10 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28763 window_ms:1740002 moving_permille:2 dev_mean_mg:7 dev_max_mg:281 moving_ms:3606 first_t_ms:4045983 last_t_ms:5725985 covered_by:@LAT103LON16421
```

---

@LAT103LON8276 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5873788 ±0 frame:5500
seq: 100
follows: 0x00000010:23
said: 1 | **ENTWIN** t_ms:5872820 stream:0x9afbb748 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,bc102f237ace,e6b32d2cea8b,aef9ff2626ac,84a329c78fec,0283cce0e689
```

---

@LAT103LON8277 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6473790 ±0 frame:5500
seq: 121
follows: 0x00000010:34
said: 1 | **ENTWIN** t_ms:6472822 stream:0x9afbb748 wall:0 window_ms:600002 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-97
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,84a329c78fec,aef9ff2626ac
```

---

@LAT103LON864 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6566958 ±0 frame:5500
seq: 124
follows: 0x00000010:36
said: 1 | **LINKWIN** t_ms:6565990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-52 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON865 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6626958 ±0 frame:5500
seq: 126
follows: 0x00000010:37
said: 1 | **LINKWIN** t_ms:6625990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-67 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON866 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6686958 ±0 frame:5500
seq: 128
follows: 0x00000010:38
said: 1 | **LINKWIN** t_ms:6685990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:69 rssi_min:-81 rssi_med:-64 rssi_max:-59
said: 3 | **LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON867 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6746958 ±0 frame:5500
seq: 130
follows: 0x00000010:39
said: 1 | **LINKWIN** t_ms:6745990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:30 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 3 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-67 rssi_med:-64 rssi_max:-60
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON868 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6806958 ±0 frame:5500
seq: 132
follows: 0x00000010:40
said: 1 | **LINKWIN** t_ms:6805990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-67 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble met predicted:-64 observed:-64
percept: 5 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON869 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6866958 ±0 frame:5500
seq: 134
follows: 0x00000010:41
said: 1 | **LINKWIN** t_ms:6865990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 3 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-79 rssi_med:-64 rssi_max:-60
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON870 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6926958 ±0 frame:5500
seq: 136
follows: 0x00000010:41
said: 1 | **LINKWIN** t_ms:6925990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-52 rssi_med:-51 rssi_max:-50
said: 3 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-67 rssi_med:-64 rssi_max:-60
said: 4 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble met predicted:-64 observed:-64
percept: 5 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON871 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 6986958 ±0 frame:5500
seq: 138
follows: 0x00000010:42
said: 1 | **LINKWIN** t_ms:6985990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble met predicted:-64 observed:-64
percept: 5 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON872 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7046958 ±0 frame:5500
seq: 140
follows: 0x00000010:44
said: 1 | **LINKWIN** t_ms:7045990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-67 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON8278 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7073790 ±0 frame:5500
seq: 142
follows: 0x00000010:44
said: 1 | **ENTWIN** t_ms:7072822 stream:0x9afbb748 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,bc102f237ace,e6b32d2cea8b,84a329c78fec,aef9ff2626ac,02c57d2f9717
```

---

@LAT103LON873 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7106958 ±0 frame:5500
seq: 143
follows: 0x00000010:45
said: 1 | **LINKWIN** t_ms:7105990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-79 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON874 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7166958 ±0 frame:5500
seq: 145
follows: 0x00000010:46
said: 1 | **LINKWIN** t_ms:7165990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:32 rssi_min:-52 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON875 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7226958 ±0 frame:5500
seq: 147
follows: 0x00000010:47
said: 1 | **LINKWIN** t_ms:7225990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-52 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON876 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7286958 ±0 frame:5500
seq: 149
follows: 0x00000010:48
said: 1 | **LINKWIN** t_ms:7285990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-81 rssi_med:-64 rssi_max:-59
said: 3 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON877 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7346958 ±0 frame:5500
seq: 151
follows: 0x00000010:49
said: 1 | **LINKWIN** t_ms:7345990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-79 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON878 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7406958 ±0 frame:5500
seq: 153
follows: 0x00000010:50
said: 1 | **LINKWIN** t_ms:7405990 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-52 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON879 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7466959 ±0 frame:5500
seq: 155
follows: 0x00000010:51
said: 1 | **LINKWIN** t_ms:7465991 stream:0x9afbb748 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-67 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON880 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7526959 ±0 frame:5500
seq: 157
follows: 0x00000010:52
said: 1 | **LINKWIN** t_ms:7525991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 3 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-67 rssi_med:-64 rssi_max:-60
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON881 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7586959 ±0 frame:5500
seq: 159
follows: 0x00000010:53
said: 1 | **LINKWIN** t_ms:7585991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-79 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:14 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble met predicted:-64 observed:-64
percept: 5 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON16424 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 7586959 ±0 frame:5500
seq: 160
follows: 0x00000010:53
said: 1 | **MOTIONWIN** t_ms:7585991 stream:0x9afbb748 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28747 window_ms:1740006 moving_permille:0 dev_mean_mg:7 dev_max_mg:15 moving_ms:0 first_t_ms:5845986 last_t_ms:7525991 covered_by:@LAT103LON16423
```

---

@LAT103LON25260 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 7586959 ±0 frame:5500
seq: 161
follows: 0x00000010:53
said: 1 | **ACOUSTICWIN** t_ms:7585991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:112 rms_max:406 peak:730 transients:0
```

---

@LAT103LON882 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7646959 ±0 frame:5500
seq: 162
follows: 0x00000010:53
said: 1 | **LINKWIN** t_ms:7645991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-67 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-52 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25261 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 7646959 ±0 frame:5500
seq: 163
follows: 0x00000010:53
said: 1 | **ACOUSTICWIN** t_ms:7645991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3735 rate:8000
said: 2 | **ACOUSTIC** rms_mean:104 rms_max:247 peak:584 transients:0
```

---

@LAT103LON883 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7706959 ±0 frame:5500
seq: 164
follows: 0x00000010:55
said: 1 | **LINKWIN** t_ms:7705991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-66 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25262 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 7706959 ±0 frame:5500
seq: 165
follows: 0x00000010:55
said: 1 | **ACOUSTICWIN** t_ms:7705991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3742 rate:8000
said: 2 | **ACOUSTIC** rms_mean:105 rms_max:1270 peak:3154 transients:2
said: 3 | **TRANSIENT** t_ms:7666229 stream:0x9afbb748 wall:0 rms:1270
```

---

@LAT103LON884 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7766959 ±0 frame:5500
seq: 166
follows: 0x00000010:56
said: 1 | **LINKWIN** t_ms:7765991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-79 rssi_med:-64 rssi_max:-59
said: 3 | **LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25263 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 7766959 ±0 frame:5500
seq: 167
follows: 0x00000010:56
said: 1 | **ACOUSTICWIN** t_ms:7765991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3734 rate:8000
said: 2 | **ACOUSTIC** rms_mean:100 rms_max:225 peak:514 transients:0
```

---

@LAT103LON885 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7826959 ±0 frame:5500
seq: 168
follows: 0x00000010:57
said: 1 | **LINKWIN** t_ms:7825991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-52 rssi_med:-51 rssi_max:-50
said: 3 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-66 rssi_med:-64 rssi_max:-60
said: 4 | 0x00000010 ble met predicted:-64 observed:-64
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25264 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 7826959 ±0 frame:5500
seq: 169
follows: 0x00000010:57
said: 1 | **ACOUSTICWIN** t_ms:7825991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3742 rate:8000
said: 2 | **ACOUSTIC** rms_mean:98 rms_max:247 peak:733 transients:0
```

---

@LAT103LON886 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7886959 ±0 frame:5500
seq: 170
follows: 0x00000010:58
said: 1 | **LINKWIN** t_ms:7885991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-79 rssi_med:-64 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 4 | 0x00000010 espnow met predicted:-51 observed:-51
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble met predicted:-64 observed:-64
percept: 5 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON25265 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 7886959 ±0 frame:5500
seq: 171
follows: 0x00000010:58
said: 1 | **ACOUSTICWIN** t_ms:7885991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3615 rate:8000
said: 2 | **ACOUSTIC** rms_mean:99 rms_max:231 peak:553 transients:0
```

---

@LAT103LON887 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 7946959 ±0 frame:5500
seq: 172
follows: 0x00000010:59
said: 1 | **LINKWIN** t_ms:7945991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-67 rssi_med:-60 rssi_max:-55
said: 3 | **LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-51 rssi_med:-50 rssi_max:-41
said: 4 | 0x00000010 ble met predicted:-64 observed:-60
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-51 observed:-50
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25266 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 7946959 ±0 frame:5500
seq: 173
follows: 0x00000010:59
said: 1 | **ACOUSTICWIN** t_ms:7945991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3741 rate:8000
said: 2 | **ACOUSTIC** rms_mean:128 rms_max:1607 peak:5603 transients:1
said: 3 | **TRANSIENT** t_ms:7919008 stream:0x9afbb748 wall:0 rms:1607
```

---

@LAT103LON888 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8006959 ±0 frame:5500
seq: 174
follows: 0x00000010:60
said: 1 | **LINKWIN** t_ms:8005991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-64 rssi_med:-61 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000010 ble met predicted:-60 observed:-61
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-50 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25267 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8006959 ±0 frame:5500
seq: 175
follows: 0x00000010:60
said: 1 | **ACOUSTICWIN** t_ms:8005991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3725 rate:8000
said: 2 | **ACOUSTIC** rms_mean:114 rms_max:376 peak:1014 transients:0
```

---

@LAT103LON889 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8066959 ±0 frame:5500
seq: 176
follows: 0x00000010:61
said: 1 | **LINKWIN** t_ms:8065991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-64 rssi_med:-61 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000010 ble met predicted:-61 observed:-61
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25268 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8066959 ±0 frame:5500
seq: 177
follows: 0x00000010:61
said: 1 | **ACOUSTICWIN** t_ms:8065991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3741 rate:8000
said: 2 | **ACOUSTIC** rms_mean:108 rms_max:351 peak:662 transients:0
```

---

@LAT103LON890 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8126959 ±0 frame:5500
seq: 178
follows: 0x00000010:62
said: 1 | **LINKWIN** t_ms:8125991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-61 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000010 ble met predicted:-61 observed:-61
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25269 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8126959 ±0 frame:5500
seq: 179
follows: 0x00000010:62
said: 1 | **ACOUSTICWIN** t_ms:8125991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3735 rate:8000
said: 2 | **ACOUSTIC** rms_mean:104 rms_max:275 peak:566 transients:0
```

---

@LAT103LON891 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8186959 ±0 frame:5500
seq: 180
follows: 0x00000010:63
said: 1 | **LINKWIN** t_ms:8185991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 3 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-64 rssi_med:-61 rssi_max:-56
said: 4 | 0x00000010 ble met predicted:-61 observed:-61
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25270 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8186959 ±0 frame:5500
seq: 181
follows: 0x00000010:63
said: 1 | **ACOUSTICWIN** t_ms:8185991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3739 rate:8000
said: 2 | **ACOUSTIC** rms_mean:103 rms_max:290 peak:546 transients:0
```

---

@LAT103LON892 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8246959 ±0 frame:5500
seq: 182
follows: 0x00000010:64
said: 1 | **LINKWIN** t_ms:8245991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 3 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-80 rssi_med:-61 rssi_max:-56
said: 4 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble met predicted:-61 observed:-61
percept: 5 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON25271 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8246959 ±0 frame:5500
seq: 183
follows: 0x00000010:64
said: 1 | **ACOUSTICWIN** t_ms:8245991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3742 rate:8000
said: 2 | **ACOUSTIC** rms_mean:176 rms_max:1258 peak:2063 transients:0
```

---

@LAT103LON8279 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8273788 ±0 frame:5500
seq: 184
follows: 0x00000010:64
said: 1 | **ENTWIN** t_ms:8272820 stream:0x9afbb748 wall:0 window_ms:599999 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,e6b32d2cea8b,bc102f237ace,84a329c78fec,02c57d2f9719,02c57d2f9717,aef9ff2626ac
said: 14 | **COVERED** windows:1 entities:9 window_ms:599999 first_t_ms:7672821 last_t_ms:7672821 covered_by:@LAT103LON8278
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-94 windows:1
```

---

@LAT103LON893 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8306959 ±0 frame:5500
seq: 185
follows: 0x00000010:65
said: 1 | **LINKWIN** t_ms:8305991 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-61 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble met predicted:-61 observed:-61
percept: 5 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON25272 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8306959 ±0 frame:5500
seq: 186
follows: 0x00000010:65
said: 1 | **ACOUSTICWIN** t_ms:8305991 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3739 rate:8000
said: 2 | **ACOUSTIC** rms_mean:102 rms_max:244 peak:511 transients:0
```

---

@LAT103LON894 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8366961 ±0 frame:5500
seq: 187
follows: 0x00000010:65
said: 1 | **LINKWIN** t_ms:8365993 stream:0x9afbb748 wall:0 window_ms:60002
said: 2 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-64 rssi_med:-61 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:6 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000010 ble met predicted:-61 observed:-61
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25273 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8366961 ±0 frame:5500
seq: 188
follows: 0x00000010:65
said: 1 | **ACOUSTICWIN** t_ms:8365993 stream:0x9afbb748 wall:0 window_ms:60002 blocks:3739 rate:8000
said: 2 | **ACOUSTIC** rms_mean:111 rms_max:338 peak:696 transients:0
```

---

@LAT103LON895 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8426961 ±0 frame:5500
seq: 189
follows: 0x00000010:65
said: 1 | **LINKWIN** t_ms:8425993 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:51 rssi_min:-80 rssi_med:-61 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000010 ble met predicted:-61 observed:-61
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25274 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8426961 ±0 frame:5500
seq: 190
follows: 0x00000010:65
said: 1 | **ACOUSTICWIN** t_ms:8425993 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3602 rate:8000
said: 2 | **ACOUSTIC** rms_mean:105 rms_max:292 peak:580 transients:0
```

---

@LAT103LON896 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8486961 ±0 frame:5500
seq: 191
follows: 0x00000010:67
said: 1 | **LINKWIN** t_ms:8485993 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-64 rssi_med:-61 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000010 ble met predicted:-61 observed:-61
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25275 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8486961 ±0 frame:5500
seq: 192
follows: 0x00000010:67
said: 1 | **ACOUSTICWIN** t_ms:8485993 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3742 rate:8000
said: 2 | **ACOUSTIC** rms_mean:103 rms_max:222 peak:503 transients:0
```

---

@LAT103LON897 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8546961 ±0 frame:5500
seq: 193
follows: 0x00000010:68
said: 1 | **LINKWIN** t_ms:8545993 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:51 rssi_min:-78 rssi_med:-60 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000010 ble met predicted:-61 observed:-60
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25276 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8546961 ±0 frame:5500
seq: 194
follows: 0x00000010:68
said: 1 | **ACOUSTICWIN** t_ms:8545993 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3733 rate:8000
said: 2 | **ACOUSTIC** rms_mean:107 rms_max:296 peak:541 transients:0
```

---

@LAT103LON898 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8606961 ±0 frame:5500
seq: 195
follows: 0x00000010:69
said: 1 | **LINKWIN** t_ms:8605993 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 3 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-78 rssi_med:-60 rssi_max:-56
said: 4 | 0x00000010 ble met predicted:-60 observed:-60
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25277 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8606961 ±0 frame:5500
seq: 196
follows: 0x00000010:69
said: 1 | **ACOUSTICWIN** t_ms:8605993 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3741 rate:8000
said: 2 | **ACOUSTIC** rms_mean:100 rms_max:231 peak:516 transients:0
```

---

@LAT103LON899 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8666961 ±0 frame:5500
seq: 197
follows: 0x00000010:70
said: 1 | **LINKWIN** t_ms:8665993 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-83 rssi_med:-61 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble met predicted:-60 observed:-61
percept: 5 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON25278 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8666961 ±0 frame:5500
seq: 198
follows: 0x00000010:70
said: 1 | **ACOUSTICWIN** t_ms:8665993 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3739 rate:8000
said: 2 | **ACOUSTIC** rms_mean:93 rms_max:200 peak:509 transients:0
```

---

@LAT103LON900 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8726961 ±0 frame:5500
seq: 199
follows: 0x00000010:71
said: 1 | **LINKWIN** t_ms:8725993 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:71 rssi_min:-64 rssi_med:-60 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000010 ble met predicted:-61 observed:-60
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25279 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8726961 ±0 frame:5500
seq: 200
follows: 0x00000010:71
said: 1 | **ACOUSTICWIN** t_ms:8725993 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3742 rate:8000
said: 2 | **ACOUSTIC** rms_mean:96 rms_max:216 peak:449 transients:0
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:36063
t_ms:8771667 stream:0x9afbb748 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:36063
t_ms:8771667 stream:0x9afbb748 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:559 last_ms:5399088
t_ms:8771667 stream:0x9afbb748 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:36063
t_ms:8771667 stream:0x9afbb748 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:36063
t_ms:8771667 stream:0x9afbb748 wall:0

---

@LAT103LON901 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8786961 ±0 frame:5500
seq: 201
follows: 0x00000010:71
said: 1 | **LINKWIN** t_ms:8785993 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-80 rssi_med:-60 rssi_max:-55
said: 3 | **LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | 0x00000010 ble met predicted:-60 observed:-60
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25280 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8786961 ±0 frame:5500
seq: 202
follows: 0x00000010:71
said: 1 | **ACOUSTICWIN** t_ms:8785993 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3594 rate:8000
said: 2 | **ACOUSTIC** rms_mean:95 rms_max:217 peak:528 transients:0
```

---

@LAT103LON902 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8846961 ±0 frame:5500
seq: 203
follows: 0x00000010:73
said: 1 | **LINKWIN** t_ms:8845993 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 3 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-61 rssi_max:-56
said: 4 | 0x00000010 ble met predicted:-60 observed:-61
percept: 4 | 0x00000010 | link_stable | ble | + | -
said: 5 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 5 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON25281 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8846961 ±0 frame:5500
seq: 204
follows: 0x00000010:73
said: 1 | **ACOUSTICWIN** t_ms:8845993 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:112 rms_max:556 peak:1054 transients:0
```

---

@LAT103LON903 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8906961 ±0 frame:5500
seq: 205
follows: 0x00000010:74
said: 1 | **LINKWIN** t_ms:8905993 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-48 rssi_med:-46 rssi_max:-29
said: 3 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-68 rssi_med:-59 rssi_max:-44
said: 4 | 0x00000010 espnow met predicted:-46 observed:-46
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble met predicted:-61 observed:-59
percept: 5 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT104LON178 | created:0 | updated:0

**carried through @LAT103LON863**

```ttdb-carried
through: 863
through: 8236
through: 16401
through: 25259
carried: 495 5 699 425 | 0x00000200 | link_stable | espnow
carried: 560 7 923 438 | 0x00000200 | link_stable | ble
carried: 276 3 632 149 | 0x00000100 | link_stable | espnow
carried: 483 11 848 364 | 0x00000010 | link_stable | ble
carried: 473 18 844 362 | 0x00000010 | link_stable | espnow
carried: 28 0 28 33 | 0x00000011 | link_stable | ble
carried: 25 3 28 33 | 0x00000011 | link_stable | espnow
carried: 51 2 53 55 | 0x00000012 | link_stable | ble
carried: 49 2 51 52 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON25282 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 8906961 ±0 frame:5500
seq: 206
follows: 0x00000010:74
said: 1 | **ACOUSTICWIN** t_ms:8905993 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3735 rate:8000
said: 2 | **ACOUSTIC** rms_mean:250 rms_max:10129 peak:32768 transients:26
said: 3 | **TRANSIENT** t_ms:8904906 stream:0x9afbb748 wall:0 rms:10129
```
