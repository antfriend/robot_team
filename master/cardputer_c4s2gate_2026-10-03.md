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

@LAT103LON16425 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 62947
seq: 208
follows: 0x00000010:74
said: 1 | **MOTIONWIN** t_ms:0 stream:0x4bcee13a wall:0 window_ms:62947 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:10 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8280 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 103283 ±0 frame:63000
seq: 210
follows: 0x00000010:75
said: 1 | **ENTWIN** t_ms:9030925 stream:0x9afbb748 wall:0 window_ms:103283 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON8281 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10238743 ±0 frame:5500
seq: 251
follows: 0x00000010:86
said: 1 | **ENTWIN** t_ms:10237759 stream:0x9afbb748 wall:0 window_ms:600007 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,aef9ff2626ac
said: 13 | **COVERED** windows:1 entities:9 window_ms:598623 first_t_ms:9637752 last_t_ms:9637752 covered_by:@LAT103LON8280
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
```

---

@LAT103LON16426 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 10799910 ±0 frame:5500
seq: 271
follows: 0x00000010:86 0x00000200:5
said: 1 | **MOTIONWIN** t_ms:10798926 stream:0x9afbb748 wall:0 window_ms:60000 n:997
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:25375 window_ms:1740133 moving_permille:1 dev_mean_mg:8 dev_max_mg:227 moving_ms:2126 first_t_ms:9058793 last_t_ms:10738926 covered_by:@LAT103LON16425
```

---

@LAT103LON8282 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10838735 ±0 frame:5500
seq: 273
follows: 0x00000010:86 0x00000200:5
said: 1 | **ENTWIN** t_ms:10837751 stream:0x9afbb748 wall:0 window_ms:599992 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 12 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 14 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,bc102f237ace,0283cce0e689,aef9ff2626ac,84a329c78fec
```

---

@LAT103LON16427 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 12599910 ±0 frame:5500
seq: 333
follows: 0x00000010:86 0x00000100:26 0x00000200:5
said: 1 | **MOTIONWIN** t_ms:12598926 stream:0x9afbb748 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28752 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0 first_t_ms:10858926 last_t_ms:12538926 covered_by:@LAT103LON16426
```

---

@LAT103LON8283 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13238736 ±0 frame:5500
seq: 355
follows: 0x00000010:86 0x00000100:39 0x00000200:5
said: 1 | **ENTWIN** t_ms:13237752 stream:0x9afbb748 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 11 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,0283cce0e689,aef9ff2626ac,5ce28c488e0c,84a329c78fec
said: 13 | **COVERED** windows:3 entities:11 window_ms:1800000 first_t_ms:11437752 last_t_ms:12637751 covered_by:@LAT103LON8282
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-34 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-68 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-74 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-79 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-84 windows:3
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:3 rssi:-88 windows:3
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:3 rssi:-88 windows:3
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-90 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-86 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95 windows:1
```

---

@LAT103LON8284 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13838736 ±0 frame:5500
seq: 376
follows: 0x00000010:86 0x00000100:49 0x00000200:5
said: 1 | **ENTWIN** t_ms:13837752 stream:0x9afbb748 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,bc102f237ace,0283cce0e689,aef9ff2626ac,84a329c78fec
```

---

@LAT103LON16428 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 14399910 ±0 frame:5500
seq: 396
follows: 0x00000010:86 0x00000100:59 0x00000200:5
said: 1 | **MOTIONWIN** t_ms:14398926 stream:0x9afbb748 wall:0 window_ms:60000 n:995
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28787 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0 first_t_ms:12658926 last_t_ms:14338926 covered_by:@LAT103LON16427
```

---

@LAT103LON8285 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 14438736 ±0 frame:5500
seq: 398
follows: 0x00000010:86 0x00000100:60 0x00000200:5
said: 1 | **ENTWIN** t_ms:14437752 stream:0x9afbb748 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,84a329c78fec,5ce28c488e0c,0283cce0e689,aef9ff2626ac
```

---

@LAT103LON8286 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 15038736 ±0 frame:5500
seq: 419
follows: 0x00000010:86 0x00000100:72 0x00000200:5
said: 1 | **ENTWIN** t_ms:15037752 stream:0x9afbb748 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,bc102f237ace,84a329c78fec,0283cce0e689,aef9ff2626ac
```

---

@LAT103LON16429 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 16199913 ±0 frame:5500
seq: 459
follows: 0x00000010:86 0x00000100:92 0x00000200:5
said: 1 | **MOTIONWIN** t_ms:16198929 stream:0x9afbb748 wall:0 window_ms:60000 n:999
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28764 window_ms:1740003 moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0 first_t_ms:14458926 last_t_ms:16138929 covered_by:@LAT103LON16428
```

---

@LAT103LON8287 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 16838736 ±0 frame:5500
seq: 481
follows: 0x00000010:86 0x00000100:104 0x00000200:5
said: 1 | **ENTWIN** t_ms:16837752 stream:0x9afbb748 wall:0 window_ms:600000 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 12 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 13 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-96
said: 14 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,bc102f237ace,aef9ff2626ac,5ce28c488e0c,84a329c78fec,0283cce0e689
said: 16 | **COVERED** windows:2 entities:10 window_ms:1200000 first_t_ms:15637752 last_t_ms:16237752 covered_by:@LAT103LON8286
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-35 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-68 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-74 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-81 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-85 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-88 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:2 rssi:-90 windows:2
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87 windows:1
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89 windows:1
```

---

@LAT103LON8288 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 17438737 ±0 frame:5500
seq: 502
follows: 0x00000010:86 0x00000100:114 0x00000200:5
said: 1 | **ENTWIN** t_ms:17437753 stream:0x9afbb748 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,64677217947d,5ce28c488e0c,84a329c78fec,0283cce0e689,7236bc441422,aef9ff2626ac
```

---

@LAT103LON16430 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 17999914 ±0 frame:5500
seq: 522
follows: 0x00000010:86 0x00000100:121 0x00000200:5
said: 1 | **MOTIONWIN** t_ms:17998930 stream:0x9afbb748 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:31 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28798 window_ms:1740001 moving_permille:0 dev_mean_mg:9 dev_max_mg:110 moving_ms:60 first_t_ms:16258929 last_t_ms:17938930 covered_by:@LAT103LON16429
```

---

@LAT103LON8289 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 18038735 ±0 frame:5500
seq: 524
follows: 0x00000010:86 0x00000100:121 0x00000200:5
said: 1 | **ENTWIN** t_ms:18037751 stream:0x9afbb748 wall:0 window_ms:599998 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,5ce28c488e0c,7236bc441422,0283cce0e689,64677217947d,aef9ff2626ac
```

---

@LAT103LON16431 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 19799915 ±0 frame:5500
seq: 584
follows: 0x00000010:86 0x00000011:16 0x00000100:121 0x00000200:5
said: 1 | **MOTIONWIN** t_ms:19798931 stream:0x9afbb748 wall:0 window_ms:60000 n:962
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28790 window_ms:1740001 moving_permille:0 dev_mean_mg:9 dev_max_mg:85 moving_ms:60 first_t_ms:18058930 last_t_ms:19738931 covered_by:@LAT103LON16430
```

---

@LAT103LON8290 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21038736 ±0 frame:5500
seq: 626
follows: 0x00000010:86 0x00000011:38 0x00000100:121 0x00000200:5
said: 1 | **ENTWIN** t_ms:21037752 stream:0x9afbb748 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,aef9ff2626ac,7236bc441422,0283cce0e689,64677217947d
said: 13 | **COVERED** windows:4 entities:11 window_ms:2400001 first_t_ms:18637752 last_t_ms:20437752 covered_by:@LAT103LON8289
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-35 windows:4
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-70 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-73 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-80 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-81 windows:4
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-86 windows:4
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:4 rssi:-88 windows:4
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-88 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:c899b2d3c797 n:2 rssi:-92 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:4 rssi:-90 windows:4
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-88 windows:4
```

---

@LAT103LON16432 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 21599915 ±0 frame:5500
seq: 646
follows: 0x00000010:86 0x00000011:48 0x00000100:121 0x00000200:5
said: 1 | **MOTIONWIN** t_ms:21598931 stream:0x9afbb748 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28774 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0 first_t_ms:19858931 last_t_ms:21538931 covered_by:@LAT103LON16431
```

---

@LAT103LON8291 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 22238736 ±0 frame:5500
seq: 668
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:7
said: 1 | **ENTWIN** t_ms:22237752 stream:0x9afbb748 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,aef9ff2626ac,64677217947d,0283cce0e689,7236bc441422,84a329c78fec
said: 14 | **COVERED** windows:1 entities:11 window_ms:600000 first_t_ms:21637752 last_t_ms:21637752 covered_by:@LAT103LON8290
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
```

---

@LAT103LON16433 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 23399915 ±0 frame:5500
seq: 708
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:27
said: 1 | **MOTIONWIN** t_ms:23398931 stream:0x9afbb748 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28733 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:39 moving_ms:0 first_t_ms:21658931 last_t_ms:23338931 covered_by:@LAT103LON16432
```

---

@LAT103LON8292 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 23438736 ±0 frame:5500
seq: 710
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:27
said: 1 | **ENTWIN** t_ms:23437752 stream:0x9afbb748 wall:0 window_ms:600000 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 13 | **ENTITY** kind:wifi_ap id:bc3e073874d8 n:1 rssi:-94
said: 14 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:11 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,aef9ff2626ac,64677217947d,84a329c78fec,e6b32d2cea8b,7236bc441422,5ce28c488e0c,0283cce0e689
said: 16 | **COVERED** windows:1 entities:10 window_ms:600000 first_t_ms:22837752 last_t_ms:22837752 covered_by:@LAT103LON8291
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89 windows:1
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
```

---

@LAT103LON16434 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 24361649 ±0 frame:5500
seq: 742
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:42
said: 1 | **MOTIONWIN** t_ms:24360665 stream:0x9afbb748 wall:0 window_ms:61734 n:302
said: 2 | **MOTION** state:moving moving_permille:142 dev_mean_mg:30 dev_max_mg:488 moving_ms:2580
said: 3 | **RUN** windows_since_last:16 reason:changed max_run:30
said: 4 | **COVERED** state:still windows:15 n:14797 window_ms:900000 moving_permille:0 dev_mean_mg:10 dev_max_mg:76 moving_ms:60 first_t_ms:23458931 last_t_ms:24298931 covered_by:@LAT103LON16433
```

---

@LAT103LON16435 | created:0 | updated:0

**motion transition**

```ttdb-episode
source: motionpercept
at: 24361649 ±0 frame:5500
seq: 743
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:42
said: 1 | **TRANSITION** t_ms:24360665 stream:0x9afbb748 wall:0 node:0x300 from:still to:moving dt_ms:61734 dt_across_merge:0
said: 2 | @PERCEPT:before state:still t_ms:24298931 window_ms:60000 n:996 moving_permille:1 dev_mean_mg:10 dev_max_mg:76 moving_ms:60 lane:@LAT103LON16433+15
said: 3 | @PERCEPT:after state:moving t_ms:24360665 window_ms:61734 n:302 moving_permille:142 dev_mean_mg:30 dev_max_mg:488 moving_ms:2580 lane:@LAT103LON16434+0
said: 4 | **DELTA** edge:became d_permille:141 d_dev_mean_mg:20 d_dev_max_mg:412
```

---

@LAT103LON16436 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 24425560 ±0 frame:5500
seq: 746
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:43
said: 1 | **MOTIONWIN** t_ms:24424608 stream:0x9afbb748 wall:0 window_ms:63943 n:68
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:changed max_run:30
```

---

@LAT103LON16437 | created:0 | updated:0

**motion transition**

```ttdb-episode
source: motionpercept
at: 24425560 ±0 frame:5500
seq: 747
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:43
said: 1 | **TRANSITION** t_ms:24424608 stream:0x9afbb748 wall:0 node:0x300 from:moving to:still dt_ms:63943 dt_across_merge:0
said: 2 | @PERCEPT:before state:moving t_ms:24360665 window_ms:61734 n:302 moving_permille:142 dev_mean_mg:30 dev_max_mg:488 moving_ms:2580 lane:@LAT103LON16434+0
said: 3 | @PERCEPT:after state:still t_ms:24424608 window_ms:63943 n:68 moving_permille:0 dev_mean_mg:10 dev_max_mg:12 moving_ms:0 lane:@LAT103LON16436+0
said: 4 | **DELTA** edge:became d_permille:-142 d_dev_mean_mg:-20 d_dev_max_mg:-476
```

---

@LAT103LON8293 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 24644182 ±0 frame:5500
seq: 750
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:47
said: 1 | **ENTWIN** t_ms:24643226 stream:0x9afbb748 wall:0 window_ms:60000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-96
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON16438 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 24644182 ±0 frame:5500
seq: 751
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:47
said: 1 | **MOTIONWIN** t_ms:24643226 stream:0x9afbb748 wall:0 window_ms:60000 n:803
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8294 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:13000
seq: 758
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:51
said: 1 | **ENTWIN** t_ms:24866660 stream:0x9afbb748 wall:0 window_ms:60000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON16439 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:13000
seq: 759
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:51
said: 1 | **MOTIONWIN** t_ms:24866660 stream:0x9afbb748 wall:0 window_ms:60000 n:836
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON16440 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 61585
seq: 774
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:57
said: 1 | **MOTIONWIN** t_ms:25297365 stream:0x9afbb748 wall:0 window_ms:61585 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:10 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8295 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 111769 ±0 frame:62000
seq: 775
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:59
said: 1 | **ENTWIN** t_ms:25349512 stream:0x9afbb748 wall:0 window_ms:111769 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON8296 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 26181564 ±21 frame:5500
seq: 788
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:74
said: 1 | **ENTWIN** t_ms:26180718 stream:0x9afbb748 wall:0 window_ms:63123 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-27
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON16441 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 26181564 ±21 frame:5500
seq: 789
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:74
said: 1 | **MOTIONWIN** t_ms:26180718 stream:0x9afbb748 wall:0 window_ms:63123 n:702
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8297 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 27331804 ±0 frame:5500
seq: 829
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:92
said: 1 | **ENTWIN** t_ms:27330958 stream:0x9afbb748 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 12 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,aef9ff2626ac,0283cce0e689
said: 13 | **COVERED** windows:1 entities:7 window_ms:550241 first_t_ms:26730959 last_t_ms:26730959 covered_by:@LAT103LON8296
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
```

---

@LAT103LON1206 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27505526 ±0 frame:5500
seq: 834
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:95
said: 1 | **LINKWIN** t_ms:27504680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-79 rssi_med:-57 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:espnow n:55 rssi_min:-52 rssi_med:-45 rssi_max:-44
said: 4 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-57 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1207 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27565526 ±0 frame:5500
seq: 836
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:96
said: 1 | **LINKWIN** t_ms:27564680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-48 rssi_med:-44 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-65 rssi_med:-57 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-57 observed:-57
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-45 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1208 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27625526 ±0 frame:5500
seq: 838
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:96
said: 1 | **LINKWIN** t_ms:27624680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:60 rssi_min:-50 rssi_med:-44 rssi_max:-42
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-57 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1209 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27685526 ±0 frame:5500
seq: 840
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:98
said: 1 | **LINKWIN** t_ms:27684680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:45 rssi_min:-45 rssi_med:-44 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-57 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-57 observed:-57
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1210 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27745526 ±0 frame:5500
seq: 842
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:99
said: 1 | **LINKWIN** t_ms:27744680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-80 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:54 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-57 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1211 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27805526 ±0 frame:5500
seq: 844
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:100
said: 1 | **LINKWIN** t_ms:27804680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-64 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1212 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27865526 ±0 frame:5500
seq: 846
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:101
said: 1 | **LINKWIN** t_ms:27864680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:57 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1213 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27925526 ±0 frame:5500
seq: 848
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:102
said: 1 | **LINKWIN** t_ms:27924680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON8298 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 27931805 ±0 frame:5500
seq: 850
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:102
said: 1 | **ENTWIN** t_ms:27930959 stream:0x9afbb748 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,64677217947d,0283cce0e689,aef9ff2626ac
```

---

@LAT103LON1214 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 27985526 ±0 frame:5500
seq: 851
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:104
said: 1 | **LINKWIN** t_ms:27984680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:32 rssi_min:-49 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON16442 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 27985526 ±0 frame:5500
seq: 852
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:104
said: 1 | **MOTIONWIN** t_ms:27984680 stream:0x9afbb748 wall:0 window_ms:60000 n:996
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26683 window_ms:1743962 moving_permille:0 dev_mean_mg:10 dev_max_mg:593 moving_ms:1080 first_t_ms:26244680 last_t_ms:27924680 covered_by:@LAT103LON16441
```

---

@LAT103LON1215 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28045526 ±0 frame:5500
seq: 854
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:105
said: 1 | **LINKWIN** t_ms:28044680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-49 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1216 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28105526 ±0 frame:5500
seq: 856
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:106
said: 1 | **LINKWIN** t_ms:28104680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1217 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28165526 ±0 frame:5500
seq: 858
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:107
said: 1 | **LINKWIN** t_ms:28164680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-82 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-49 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 ble met predicted:-57 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON79 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28215326 ±21 frame:5500
seq: 108
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:859
said: 1 | **LINKWIN** t_ms:28214450 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON1218 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28225526 ±0 frame:5500
seq: 860
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:108
said: 1 | **LINKWIN** t_ms:28224680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:46 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-64 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON80 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28275326 ±21 frame:5500
seq: 109
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:861
said: 1 | **LINKWIN** t_ms:28274450 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON1219 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28285526 ±0 frame:5500
seq: 862
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:109
said: 1 | **LINKWIN** t_ms:28284680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-49 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON81 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28335328 ±21 frame:5500
seq: 110
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:863
said: 1 | **LINKWIN** t_ms:28334451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:28 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT103LON1220 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28345526 ±0 frame:5500
seq: 864
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:110
said: 1 | **LINKWIN** t_ms:28344680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON82 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28395329 ±21 frame:5500
seq: 111
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:865
said: 1 | **LINKWIN** t_ms:28394451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-79 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON1221 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28405526 ±0 frame:5500
seq: 866
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:111
said: 1 | **LINKWIN** t_ms:28404680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-64 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON83 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28455330 ±21 frame:5500
seq: 112
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:867
said: 1 | **LINKWIN** t_ms:28454451 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-79 rssi_med:-54 rssi_max:-51
```

---

@LAT103LON1222 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28465526 ±0 frame:5500
seq: 868
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:112
said: 1 | **LINKWIN** t_ms:28464680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-63 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1223 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28525526 ±0 frame:5500
seq: 870
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:112
said: 1 | **LINKWIN** t_ms:28524680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-44 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-57 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON84 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28516237 ±21 frame:5500
seq: 113
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:869
said: 1 | **LINKWIN** t_ms:28514451 stream:0x9afbb748 wall:0 window_ms:60906
said: 2 | **LINK** peer:0x00000300 proto:espnow n:59 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-79 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON1224 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28585526 ±0 frame:5500
seq: 872
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:113
said: 1 | **LINKWIN** t_ms:28584680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-64 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON85 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28576254 ±22 frame:5500
seq: 114
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:871
said: 1 | **LINKWIN** t_ms:28575367 stream:0x9afbb748 wall:0 window_ms:60016
said: 2 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-78 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-56 rssi_med:-53 rssi_max:-50
```

---

@LAT103LON1225 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28645526 ±0 frame:5500
seq: 874
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:114
said: 1 | **LINKWIN** t_ms:28644680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 ble met predicted:-57 observed:-57
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON86 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28636255 ±21 frame:5500
seq: 115
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:873
said: 1 | **LINKWIN** t_ms:28635373 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-56 rssi_med:-54 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT103LON1226 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28705526 ±0 frame:5500
seq: 876
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:116
said: 1 | **LINKWIN** t_ms:28704680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:49 rssi_min:-49 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-57 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1227 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28765526 ±0 frame:5500
seq: 878
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:117
said: 1 | **LINKWIN** t_ms:28764680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-56 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:33 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-56
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON87 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28696257 ±21 frame:5500
seq: 116
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:875
said: 1 | **LINKWIN** t_ms:28695373 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:54 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT105LON88 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28756256 ±23 frame:5500
seq: 117
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:877
said: 1 | **LINKWIN** t_ms:28755373 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-40 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-56 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON1228 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28825526 ±0 frame:5500
seq: 880
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:118
said: 1 | **LINKWIN** t_ms:28824680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-79 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:45 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 4 | 0x00000200 ble met predicted:-56 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON89 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28816251 ±21 frame:5500
seq: 118
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:879
said: 1 | **LINKWIN** t_ms:28815373 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-59 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON1229 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28885526 ±0 frame:5500
seq: 882
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:118
said: 1 | **LINKWIN** t_ms:28884680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:38 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-57 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-57
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON90 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28876260 ±21 frame:5500
seq: 119
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:881
said: 1 | **LINKWIN** t_ms:28875373 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-59 rssi_med:-53 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT105LON91 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28936305 ±21 frame:5500
seq: 120
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:883
said: 1 | **LINKWIN** t_ms:28935413 stream:0x9afbb748 wall:0 window_ms:60045
said: 2 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-79 rssi_med:-54 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-41 rssi_med:-40 rssi_max:-39
```

---

@LAT103LON1230 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 28945526 ±0 frame:5500
seq: 884
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:120
said: 1 | **LINKWIN** t_ms:28944680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-63 rssi_med:-57 rssi_max:-53
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-57 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1231 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29005526 ±0 frame:5500
seq: 886
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:120
said: 1 | **LINKWIN** t_ms:29004680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-57 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON92 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 28996313 ±21 frame:5500
seq: 121
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:885
said: 1 | **LINKWIN** t_ms:28995419 stream:0x9afbb748 wall:0 window_ms:60006
said: 2 | **LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-59 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON1232 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29065526 ±0 frame:5500
seq: 888
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:121
said: 1 | **LINKWIN** t_ms:29064680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON93 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29056380 ±21 frame:5500
seq: 122
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:887
said: 1 | **LINKWIN** t_ms:29055485 stream:0x9afbb748 wall:0 window_ms:60066
said: 2 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-59 rssi_med:-53 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT105LON94 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29116381 ±21 frame:5500
seq: 123
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:889
said: 1 | **LINKWIN** t_ms:29115490 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-40 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON1233 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29125526 ±0 frame:5500
seq: 890
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:123
said: 1 | **LINKWIN** t_ms:29124680 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-64 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON95 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29176382 ±21 frame:5500
seq: 124
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:891
said: 1 | **LINKWIN** t_ms:29175490 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-69 rssi_med:-53 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT103LON1234 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29187575 ±0 frame:5500
seq: 892
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:124
said: 1 | **LINKWIN** t_ms:29186729 stream:0x9afbb748 wall:0 window_ms:62049
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-63 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1235 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29247575 ±0 frame:5500
seq: 894
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:125
said: 1 | **LINKWIN** t_ms:29246729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-55 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25602 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29247575 ±0 frame:5500
seq: 895
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:125
said: 1 | **ACOUSTICWIN** t_ms:29246729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3731 rate:8000
said: 2 | **ACOUSTIC** rms_mean:540 rms_max:943 peak:1487 transients:0
```

---

@LAT105LON96 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29236383 ±21 frame:5500
seq: 125
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:893
said: 1 | **LINKWIN** t_ms:29235490 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-59 rssi_med:-54 rssi_max:-51
```

---

@LAT105LON97 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29296384 ±21 frame:5500
seq: 126
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:895
said: 1 | **LINKWIN** t_ms:29295489 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-79 rssi_med:-53 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-41 rssi_med:-40 rssi_max:-40
```

---

@LAT103LON1236 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29307575 ±0 frame:5500
seq: 896
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:126
said: 1 | **LINKWIN** t_ms:29306729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-49 rssi_med:-44 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 4 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25603 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29307575 ±0 frame:5500
seq: 897
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:126
said: 1 | **ACOUSTICWIN** t_ms:29306729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3726 rate:8000
said: 2 | **ACOUSTIC** rms_mean:554 rms_max:7240 peak:32768 transients:1
said: 3 | **TRANSIENT** t_ms:29305074 stream:0x9afbb748 wall:0 rms:7240
```

---

@LAT103LON1237 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29367575 ±0 frame:5500
seq: 898
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:127
said: 1 | **LINKWIN** t_ms:29366729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-82 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:39 rssi_min:-48 rssi_med:-43 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-44 observed:-43
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25604 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29367575 ±0 frame:5500
seq: 899
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:127
said: 1 | **ACOUSTICWIN** t_ms:29366729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3583 rate:8000
said: 2 | **ACOUSTIC** rms_mean:540 rms_max:1554 peak:4546 transients:0
```

---

@LAT105LON98 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29356385 ±21 frame:5500
seq: 127
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:897
said: 1 | **LINKWIN** t_ms:29355490 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-42 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-79 rssi_med:-54 rssi_max:-50
```

---

@LAT103LON1238 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29427575 ±0 frame:5500
seq: 900
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:128
said: 1 | **LINKWIN** t_ms:29426729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-47 rssi_med:-43 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-57 rssi_max:-51
said: 4 | 0x00000200 ble met predicted:-55 observed:-57
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25605 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29427575 ±0 frame:5500
seq: 901
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:128
said: 1 | **ACOUSTICWIN** t_ms:29426729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3718 rate:8000
said: 2 | **ACOUSTIC** rms_mean:542 rms_max:1533 peak:4253 transients:0
```

---

@LAT105LON99 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29416385 ±21 frame:5500
seq: 128
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:899
said: 1 | **LINKWIN** t_ms:29415490 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-43 rssi_med:-40 rssi_max:-38
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON1239 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29487575 ±0 frame:5500
seq: 902
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:129
said: 1 | **LINKWIN** t_ms:29486729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-63 rssi_med:-45 rssi_max:-42
said: 4 | 0x00000200 espnow met predicted:-43 observed:-45
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-57 observed:-57
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25606 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29487575 ±0 frame:5500
seq: 903
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:129
said: 1 | **ACOUSTICWIN** t_ms:29486729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3737 rate:8000
said: 2 | **ACOUSTIC** rms_mean:529 rms_max:1760 peak:4412 transients:0
```

---

@LAT105LON100 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29476386 ±21 frame:5500
seq: 129
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:901
said: 1 | **LINKWIN** t_ms:29475541 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-73 rssi_med:-55 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-60 rssi_med:-42 rssi_max:-38
```

---

@LAT103LON1240 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29547575 ±0 frame:5500
seq: 904
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:130
said: 1 | **LINKWIN** t_ms:29546729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-50 rssi_med:-43 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 4 | 0x00000200 ble met predicted:-57 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-45 observed:-43
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25607 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29547575 ±0 frame:5500
seq: 905
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:130
said: 1 | **ACOUSTICWIN** t_ms:29546729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3358 rate:8000
said: 2 | **ACOUSTIC** rms_mean:519 rms_max:1509 peak:4530 transients:0
```

---

@LAT103LON1241 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29607575 ±0 frame:5500
seq: 906
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:131
said: 1 | **LINKWIN** t_ms:29606729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-49 rssi_med:-44 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-81 rssi_med:-56 rssi_max:-51
said: 4 | 0x00000200 espnow met predicted:-43 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-56 observed:-56
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25608 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29607575 ±0 frame:5500
seq: 907
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:131
said: 1 | **ACOUSTICWIN** t_ms:29606729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3735 rate:8000
said: 2 | **ACOUSTIC** rms_mean:526 rms_max:2643 peak:5799 transients:1
said: 3 | **TRANSIENT** t_ms:29584442 stream:0x9afbb748 wall:0 rms:2643
```

---

@LAT103LON1242 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29667575 ±0 frame:5500
seq: 908
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:132
said: 1 | **LINKWIN** t_ms:29666729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-61 rssi_med:-58 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-83 rssi_med:-61 rssi_max:-52
said: 4 | 0x00000200 espnow violated predicted:-44 observed:-58
percept: 4 | 0x00000200 | link_stable | espnow | - | -
said: 5 | 0x00000200 ble met predicted:-56 observed:-61
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25609 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29667575 ±0 frame:5500
seq: 909
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:132
said: 1 | **ACOUSTICWIN** t_ms:29666729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3720 rate:8000
said: 2 | **ACOUSTIC** rms_mean:553 rms_max:6889 peak:23899 transients:4
said: 3 | **TRANSIENT** t_ms:29624248 stream:0x9afbb748 wall:0 rms:6889
```

---

@LAT103LON1243 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29727575 ±0 frame:5500
seq: 910
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:133
said: 1 | **LINKWIN** t_ms:29726729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:33 rssi_min:-61 rssi_med:-60 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-83 rssi_med:-61 rssi_max:-56
said: 4 | 0x00000200 espnow met predicted:-58 observed:-60
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-61 observed:-61
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25610 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29727575 ±0 frame:5500
seq: 911
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:133
said: 1 | **ACOUSTICWIN** t_ms:29726729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3730 rate:8000
said: 2 | **ACOUSTIC** rms_mean:519 rms_max:929 peak:1438 transients:0
```

---

@LAT103LON1244 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29787575 ±0 frame:5500
seq: 912
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:133
said: 1 | **LINKWIN** t_ms:29786729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:29 rssi_min:-80 rssi_med:-61 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:espnow n:10 rssi_min:-61 rssi_med:-60 rssi_max:-60
said: 4 | 0x00000200 espnow met predicted:-60 observed:-60
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-61 observed:-61
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON16443 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 29787575 ±0 frame:5500
seq: 913
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:133
said: 1 | **MOTIONWIN** t_ms:29786729 stream:0x9afbb748 wall:0 window_ms:60000 n:997
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28362 window_ms:1742049 moving_permille:0 dev_mean_mg:10 dev_max_mg:18 moving_ms:0 first_t_ms:28044680 last_t_ms:29726729 covered_by:@LAT103LON16442
```

---

@LAT103LON25611 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29787575 ±0 frame:5500
seq: 914
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:133
said: 1 | **ACOUSTICWIN** t_ms:29786729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3736 rate:8000
said: 2 | **ACOUSTIC** rms_mean:498 rms_max:1554 peak:3744 transients:0
```

---

@LAT103LON1245 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29847575 ±0 frame:5500
seq: 915
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:135
said: 1 | **LINKWIN** t_ms:29846729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-83 rssi_med:-61 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:espnow n:5 rssi_min:-60 rssi_med:-60 rssi_max:-60
said: 4 | 0x00000200 ble met predicted:-61 observed:-61
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-60 observed:-60
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25612 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29847575 ±0 frame:5500
seq: 916
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:135
said: 1 | **ACOUSTICWIN** t_ms:29846729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3561 rate:8000
said: 2 | **ACOUSTIC** rms_mean:490 rms_max:726 peak:1208 transients:0
```

---

@LAT105LON101 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29536388 ±21 frame:5500
seq: 130
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:903
said: 1 | **LINKWIN** t_ms:29535541 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-43 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-54 rssi_max:-49
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:29887942 stream:0x9afbb748 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:11 last_ms:3767167
t_ms:29887942 stream:0x9afbb748 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:29887942 stream:0x9afbb748 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:4330
t_ms:29887942 stream:0x9afbb748 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:4330
t_ms:29887942 stream:0x9afbb748 wall:0

---

@LAT103LON1246 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29907575 ±0 frame:5500
seq: 917
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:136
said: 1 | **LINKWIN** t_ms:29906729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-85 rssi_med:-61 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-61 rssi_med:-60 rssi_max:-57
said: 4 | 0x00000200 ble met predicted:-61 observed:-61
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-60 observed:-60
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25613 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29907575 ±0 frame:5500
seq: 918
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:136
said: 1 | **ACOUSTICWIN** t_ms:29906729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3405 rate:8000
said: 2 | **ACOUSTIC** rms_mean:504 rms_max:1804 peak:2425 transients:0
```

---

@LAT105LON102 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29596388 ±21 frame:5500
seq: 131
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:905
said: 1 | **LINKWIN** t_ms:29595541 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-45 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-79 rssi_med:-55 rssi_max:-51
```

---

@LAT105LON103 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29656390 ±21 frame:5500
seq: 132
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:907
said: 1 | **LINKWIN** t_ms:29655541 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-55 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-64 rssi_med:-46 rssi_max:-39
```

---

@LAT103LON1247 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 29967575 ±0 frame:5500
seq: 919
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:136
said: 1 | **LINKWIN** t_ms:29966729 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-84 rssi_med:-61 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-61 rssi_med:-60 rssi_max:-57
said: 4 | 0x00000200 ble met predicted:-61 observed:-61
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-60 observed:-60
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25614 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 29967575 ±0 frame:5500
seq: 920
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:136
said: 1 | **ACOUSTICWIN** t_ms:29966729 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3576 rate:8000
said: 2 | **ACOUSTIC** rms_mean:244 rms_max:4871 peak:6085 transients:8
said: 3 | **TRANSIENT** t_ms:29906999 stream:0x9afbb748 wall:0 rms:4625
```

---

@LAT103LON1248 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 30029510 ±0 frame:5500
seq: 921
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:138
said: 1 | **LINKWIN** t_ms:30028664 stream:0x9afbb748 wall:0 window_ms:61935
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-80 rssi_med:-57 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-51 rssi_med:-47 rssi_max:-26
said: 4 | 0x00000200 ble met predicted:-61 observed:-57
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow violated predicted:-60 observed:-47
percept: 5 | 0x00000200 | link_stable | espnow | - | -
```

---

@LAT103LON25615 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 30029510 ±0 frame:5500
seq: 922
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:138
said: 1 | **ACOUSTICWIN** t_ms:30028664 stream:0x9afbb748 wall:0 window_ms:61935 blocks:3332 rate:8000
said: 2 | **ACOUSTIC** rms_mean:241 rms_max:20656 peak:32768 transients:25
said: 3 | **TRANSIENT** t_ms:30020405 stream:0x9afbb748 wall:0 rms:20656
```

---

@LAT105LON104 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29716389 ±21 frame:5500
seq: 133
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:909
said: 1 | **LINKWIN** t_ms:29715541 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-80 rssi_med:-59 rssi_max:-53
said: 3 | **LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-63 rssi_med:-60 rssi_max:-58
```

---

@LAT105LON105 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29837288 ±21 frame:5500
seq: 134
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:914
said: 1 | **LINKWIN** t_ms:29832435 stream:0x9afbb748 wall:0 window_ms:63875
said: 2 | **LINK** peer:0x00000300 proto:espnow n:26 rssi_min:-96 rssi_med:-60 rssi_max:-58
said: 3 | **LINK** peer:0x00000300 proto:ble n:45 rssi_min:-71 rssi_med:-59 rssi_max:-52
```

---

@LAT105LON106 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29897282 ±21 frame:5500
seq: 136
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:916
said: 1 | **LINKWIN** t_ms:29896440 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-62 rssi_med:-60 rssi_max:-58
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-79 rssi_med:-59 rssi_max:-53
```

---

@LAT105LON107 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 29959581 ±21 frame:5500
seq: 137
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:918
said: 1 | **LINKWIN** t_ms:29956725 stream:0x9afbb748 wall:0 window_ms:62292
said: 2 | **LINK** peer:0x00000300 proto:espnow n:59 rssi_min:-61 rssi_med:-60 rssi_max:-58
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-72 rssi_med:-59 rssi_max:-53
```

---

@LAT105LON108 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 30019584 ±21 frame:5500
seq: 138
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:920
said: 1 | **LINKWIN** t_ms:30018732 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-64 rssi_med:-46 rssi_max:-34
```

---

@LAT103LON1249 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 30089510 ±0 frame:5500
seq: 923
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:139
said: 1 | **LINKWIN** t_ms:30088664 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:56 rssi_min:-31 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-42 rssi_max:-40
said: 4 | 0x00000200 ble violated predicted:-57 observed:-42
percept: 4 | 0x00000200 | link_stable | ble | - | -
said: 5 | 0x00000200 espnow violated predicted:-47 observed:-28
percept: 5 | 0x00000200 | link_stable | espnow | - | -
```

---

@LAT103LON25616 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 30089510 ±0 frame:5500
seq: 924
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:139
said: 1 | **ACOUSTICWIN** t_ms:30088664 stream:0x9afbb748 wall:0 window_ms:60000 blocks:2835 rate:8000
said: 2 | **ACOUSTIC** rms_mean:126 rms_max:688 peak:1893 transients:0
```

---

@LAT105LON109 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 30079584 ±21 frame:5500
seq: 139
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:922
said: 1 | **LINKWIN** t_ms:30078731 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-35 rssi_med:-23 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-80 rssi_med:-39 rssi_max:-37
```

---

@LAT105LON110 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 30139585 ±22 frame:5500
seq: 140
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:924
said: 1 | **LINKWIN** t_ms:30138732 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-39 rssi_max:-38
said: 3 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-27 rssi_med:-23 rssi_max:-23
```

---

@LAT103LON1250 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 30149510 ±0 frame:5500
seq: 925
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:140
said: 1 | **LINKWIN** t_ms:30148664 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-31 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-83 rssi_med:-43 rssi_max:-39
said: 4 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-42 observed:-43
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25617 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 30149510 ±0 frame:5500
seq: 926
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:140
said: 1 | **ACOUSTICWIN** t_ms:30148664 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3232 rate:8000
said: 2 | **ACOUSTIC** rms_mean:151 rms_max:15733 peak:32768 transients:5
said: 3 | **TRANSIENT** t_ms:30145050 stream:0x9afbb748 wall:0 rms:15733
```

---

@LAT104LON258 | created:0 | updated:0

**carried through @LAT103LON1205**

```ttdb-carried
through: 1205
through: 8254
through: 16419
through: 25601
carried: 584 9 792 519 | 0x00000200 | link_stable | espnow
carried: 650 10 1016 532 | 0x00000200 | link_stable | ble
carried: 397 3 753 271 | 0x00000100 | link_stable | espnow
carried: 534 11 899 416 | 0x00000010 | link_stable | ble
carried: 524 18 895 414 | 0x00000010 | link_stable | espnow
carried: 91 0 91 97 | 0x00000011 | link_stable | ble
carried: 87 4 91 97 | 0x00000011 | link_stable | espnow
carried: 59 2 61 64 | 0x00000012 | link_stable | ble
carried: 57 2 59 61 | 0x00000012 | link_stable | espnow
```
