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

@LAT103LON8299 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:7000
seq: 928
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:142
said: 1 | **ENTWIN** t_ms:30270899 stream:0x9afbb748 wall:0 window_ms:60000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON16444 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:7000
seq: 929
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:142
said: 1 | **MOTIONWIN** t_ms:30270899 stream:0x9afbb748 wall:0 window_ms:60000 n:933
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT106LON0 | created:0 | updated:0

**BAR** frame:5500 bar:52 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:266403
**HOLDS** agent:0x00000200 n:10 lo:148 hi:158 sum:1528
**HOLDS** agent:0x00000300 n:10 lo:941 hi:959 sum:9500
@LAT106LON1 | created:0 | updated:0

**BAR** frame:5500 bar:51 own:8 held:10 terms:2 digest:0x5e0ec03e settled_ms:866403
**HOLDS** agent:0x00000200 n:10 lo:138 hi:147 sum:1425
**HOLDS** agent:0x00000300 n:8 lo:921 hi:939 sum:7444

---

@LAT103LON8300 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31641581 ±21 frame:5500
seq: 968
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:165
said: 1 | **ENTWIN** t_ms:31640720 stream:0x9afbb748 wall:0 window_ms:62000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON16445 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 31641581 ±21 frame:5500
seq: 969
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:165
said: 1 | **MOTIONWIN** t_ms:31640720 stream:0x9afbb748 wall:0 window_ms:62000 n:838
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT106LON2 | created:0 | updated:0

**BAR** frame:5500 bar:53 own:6 held:10 terms:2 digest:0x07234745 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:159 hi:169 sum:1638
**HOLDS** agent:0x00000300 n:6 lo:961 hi:973 sum:5800

---

@LAT106LON3 | created:0 | updated:0

**BAR** frame:5500 bar:54 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:121273
**HOLDS** agent:0x00000200 n:10 lo:170 hi:180 sum:1748
**HOLDS** agent:0x00000300 n:10 lo:975 hi:993 sum:9840

---

@LAT103LON8301 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 32805503 ±0 frame:5500
seq: 1009
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:187
said: 1 | **ENTWIN** t_ms:32804653 stream:0x9afbb748 wall:0 window_ms:609011 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-93
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689
said: 14 | **COVERED** windows:1 entities:7 window_ms:554922 first_t_ms:32195642 last_t_ms:32195642 covered_by:@LAT103LON8300
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
```

---

@LAT106LON4 | created:0 | updated:0

**BAR** frame:5500 bar:55 own:10 held:10 terms:2 digest:0x2bacbfd9 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:181 hi:191 sum:1858
**HOLDS** agent:0x00000300 n:10 lo:995 hi:1014 sum:10043

---

@LAT103LON8302 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 33402734 ±0 frame:5500
seq: 1030
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:195
said: 1 | **ENTWIN** t_ms:33401884 stream:0x9afbb748 wall:0 window_ms:597231 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,aef9ff2626ac,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON16446 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 33453567 ±0 frame:5500
seq: 1032
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:196
said: 1 | **MOTIONWIN** t_ms:33452717 stream:0x9afbb748 wall:0 window_ms:60000 n:993
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:17 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:17972 window_ms:1751997 moving_permille:0 dev_mean_mg:10 dev_max_mg:411 moving_ms:480 first_t_ms:31700720 last_t_ms:33392717 covered_by:@LAT103LON16445
```

---

@LAT106LON5 | created:0 | updated:0

**BAR** frame:5500 bar:56 own:10 held:6 terms:2 digest:0xee5eb19f settled_ms:120000
**HOLDS** agent:0x00000200 n:6 lo:192 hi:198 sum:1172
**HOLDS** agent:0x00000300 n:10 lo:1016 hi:1036 sum:10255

---

@LAT103LON8303 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34002734 ±0 frame:5500
seq: 1052
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:205
said: 1 | **ENTWIN** t_ms:34001884 stream:0x9afbb748 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,aef9ff2626ac,64677217947d,e6b32d2cea8b,0283cce0e689
```

---

@LAT106LON6 | created:0 | updated:0

**BAR** frame:5500 bar:57 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:200 hi:209 sum:2045
**HOLDS** agent:0x00000300 n:10 lo:1038 hi:1057 sum:10473

---

@LAT103LON8304 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34602734 ±0 frame:5500
seq: 1073
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:216
said: 1 | **ENTWIN** t_ms:34601884 stream:0x9afbb748 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689,980d67f79619,aef9ff2626ac
```

---

@LAT106LON7 | created:0 | updated:0

**BAR** frame:5500 bar:58 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:210 hi:220 sum:2153
**HOLDS** agent:0x00000300 n:10 lo:1059 hi:1078 sum:10683

---

@LAT103LON16447 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 35253567 ±0 frame:5500
seq: 1095
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:227
said: 1 | **MOTIONWIN** t_ms:35252717 stream:0x9afbb748 wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28184 window_ms:1740000 moving_permille:0 dev_mean_mg:11 dev_max_mg:55 moving_ms:0 first_t_ms:33512717 last_t_ms:35192717 covered_by:@LAT103LON16446
```

---

@LAT106LON8 | created:0 | updated:0

**BAR** frame:5500 bar:59 own:10 held:7 terms:2 digest:0xee5eb19f settled_ms:120000
**HOLDS** agent:0x00000200 n:7 lo:221 hi:228 sum:1572
**HOLDS** agent:0x00000300 n:10 lo:1080 hi:1099 sum:10892

---

@LAT106LON9 | created:0 | updated:0

**BAR** frame:5500 bar:60 own:10 held:1 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000200 n:1 lo:231 hi:231 sum:231
**HOLDS** agent:0x00000300 n:10 lo:1101 hi:1119 sum:11100

---

@LAT103LON8305 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36402734 ±0 frame:5500
seq: 1135
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:248
said: 1 | **ENTWIN** t_ms:36401884 stream:0x9afbb748 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,0283cce0e689,e6b32d2cea8b
said: 12 | **COVERED** windows:2 entities:10 window_ms:1200000 first_t_ms:35201884 last_t_ms:35801884 covered_by:@LAT103LON8304
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-40 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-64 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-74 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-76 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-89 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-88 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
```

---

@LAT103LON16448 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 36542570 ±214768 frame:5500
seq: 1139
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:249
said: 1 | **MOTIONWIN** t_ms:36548070 stream:0x9afbb748 wall:0 window_ms:70599 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8306 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36602154 ±0 frame:5500
seq: 1141
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:251
said: 1 | **ENTWIN** t_ms:36608871 stream:0x9afbb748 wall:0 window_ms:130183 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT106LON10 | created:0 | updated:0

**BAR** frame:5500 bar:61 own:8 held:0 terms:2 digest:0xfba47ec1 settled_ms:156392
**HOLDS** agent:0x00000300 n:8 lo:1121 hi:1136 sum:9025

---

@LAT106LON11 | created:0 | updated:0

**BAR** frame:5500 bar:62 own:10 held:6 terms:2 digest:0x0938c1d3 settled_ms:140819
**HOLDS** agent:0x00000200 n:6 lo:253 hi:258 sum:1533
**HOLDS** agent:0x00000300 n:10 lo:1142 hi:1160 sum:11510

---

@LAT103LON8307 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 37419589 ±21 frame:5500
seq: 1163
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:266
said: 1 | **ENTWIN** t_ms:37425106 stream:0x9afbb748 wall:0 window_ms:64910 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON16449 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 37419589 ±21 frame:5500
seq: 1164
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:266
said: 1 | **MOTIONWIN** t_ms:37425106 stream:0x9afbb748 wall:0 window_ms:64910 n:315
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT106LON12 | created:0 | updated:0

**BAR** frame:5500 bar:63 own:7 held:0 terms:2 digest:0xcf46417f settled_ms:120000
**HOLDS** agent:0x00000300 n:7 lo:1162 hi:1176 sum:8188

---

@LAT106LON13 | created:0 | updated:0

**BAR** frame:5500 bar:64 own:10 held:0 terms:2 digest:0xee5eb19f settled_ms:120000
**HOLDS** agent:0x00000300 n:10 lo:1178 hi:1196 sum:11870

---

@LAT103LON8308 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 38567707 ±0 frame:5500
seq: 1204
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:283
said: 1 | **ENTWIN** t_ms:38573224 stream:0x9afbb748 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 12 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,aef9ff2626ac
said: 13 | **COVERED** windows:1 entities:8 window_ms:548118 first_t_ms:37973224 last_t_ms:37973224 covered_by:@LAT103LON8307
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-87 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
```

---

@LAT103LON1386 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 38863530 ±0 frame:5500
seq: 1213
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:288
said: 1 | **LINKWIN** t_ms:38869047 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:70 rssi_min:-82 rssi_med:-55 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-50 rssi_med:-49 rssi_max:-49
said: 4 | 0x00000200 ble met predicted:-57 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1387 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 38923530 ±0 frame:5500
seq: 1215
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:289
said: 1 | **LINKWIN** t_ms:38929047 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-56 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-55 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1388 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 38983530 ±0 frame:5500
seq: 1217
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:290
said: 1 | **LINKWIN** t_ms:38989047 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-56 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-56 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1389 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39043530 ±0 frame:5500
seq: 1219
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:292
said: 1 | **LINKWIN** t_ms:39049047 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:48 rssi_min:-82 rssi_med:-56 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 4 | 0x00000200 ble met predicted:-56 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1390 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39103532 ±0 frame:5500
seq: 1221
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:293
said: 1 | **LINKWIN** t_ms:39109049 stream:0x9afbb748 wall:0 window_ms:60002
said: 2 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-55 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 4 | 0x00000200 ble met predicted:-56 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT106LON14 | created:0 | updated:0

**BAR** frame:5500 bar:65 own:10 held:0 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000300 n:10 lo:1198 hi:1217 sum:12077

---

@LAT103LON1391 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39163532 ±0 frame:5500
seq: 1223
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:294
said: 1 | **LINKWIN** t_ms:39169049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-80 rssi_med:-55 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON8309 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 39167706 ±0 frame:5500
seq: 1225
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:294
said: 1 | **ENTWIN** t_ms:39173223 stream:0x9afbb748 wall:0 window_ms:599999 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 10 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,aef9ff2626ac,0283cce0e689,84a329c78fec,64677217947d,bc102f237ace
```

---

@LAT103LON1392 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39223532 ±0 frame:5500
seq: 1226
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:295
said: 1 | **LINKWIN** t_ms:39229049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-81 rssi_med:-56 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-55 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON16450 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 39223532 ±0 frame:5500
seq: 1227
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:295
said: 1 | **MOTIONWIN** t_ms:39229049 stream:0x9afbb748 wall:0 window_ms:60000 n:996
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26596 window_ms:1743943 moving_permille:0 dev_mean_mg:11 dev_max_mg:247 moving_ms:1505 first_t_ms:37487126 last_t_ms:39169049 covered_by:@LAT103LON16449
```

---

@LAT103LON1393 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39283532 ±0 frame:5500
seq: 1229
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:296
said: 1 | **LINKWIN** t_ms:39289049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-80 rssi_med:-55 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-56 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1394 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39343532 ±0 frame:5500
seq: 1231
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:297
said: 1 | **LINKWIN** t_ms:39349049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-60 rssi_med:-56 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 4 | 0x00000200 ble met predicted:-55 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON220 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 36994071 ±22 frame:5500
seq: 259
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1153
said: 1 | **LINKWIN** t_ms:36999576 stream:0x9afbb748 wall:0 window_ms:60039
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-43 rssi_med:-39 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-27 rssi_med:-25 rssi_max:-24
```

---

@LAT105LON221 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37054071 ±21 frame:5500
seq: 260
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1155
said: 1 | **LINKWIN** t_ms:37059582 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-44 rssi_med:-40 rssi_max:-38
said: 3 | **LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-27 rssi_med:-25 rssi_max:-24
```

---

@LAT103LON1395 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39403532 ±0 frame:5500
seq: 1233
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:298
said: 1 | **LINKWIN** t_ms:39409049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-60 rssi_med:-55 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 4 | 0x00000200 ble met predicted:-56 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON222 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37114071 ±22 frame:5500
seq: 261
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1157
said: 1 | **LINKWIN** t_ms:37119582 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-40 rssi_max:-38
said: 3 | **LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-25 rssi_med:-24 rssi_max:-24
```

---

@LAT103LON1396 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39463532 ±0 frame:5500
seq: 1235
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:299
said: 1 | **LINKWIN** t_ms:39469049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-56 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-55 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON223 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37172073 ±22 frame:5500
seq: 262
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1159
said: 1 | **LINKWIN** t_ms:37179582 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-39 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:30 rssi_min:-25 rssi_med:-24 rssi_max:-23
```

---

@LAT103LON1397 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39523532 ±0 frame:5500
seq: 1237
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:300
said: 1 | **LINKWIN** t_ms:39529049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-56 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-56 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1398 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39583532 ±0 frame:5500
seq: 1239
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:301
said: 1 | **LINKWIN** t_ms:39589049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-56 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-56 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1399 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39643532 ±0 frame:5500
seq: 1241
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:303
said: 1 | **LINKWIN** t_ms:39649049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-57 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-56 observed:-57
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1400 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39703532 ±0 frame:5500
seq: 1243
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:304
said: 1 | **LINKWIN** t_ms:39709049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-60 rssi_med:-55 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-57 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT106LON15 | created:0 | updated:0

**BAR** frame:5500 bar:66 own:10 held:0 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000300 n:10 lo:1219 hi:1239 sum:12293

---

@LAT103LON1401 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39763532 ±0 frame:5500
seq: 1245
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:305
said: 1 | **LINKWIN** t_ms:39769049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-57 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 4 | 0x00000200 ble met predicted:-55 observed:-57
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON8310 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 39767705 ±0 frame:5500
seq: 1247
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:305
said: 1 | **ENTWIN** t_ms:39773222 stream:0x9afbb748 wall:0 window_ms:599999 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 12 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,aef9ff2626ac,84a329c78fec,64677217947d,0283cce0e689,c2e94427adcf
```

---

@LAT103LON1402 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39823532 ±0 frame:5500
seq: 1248
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:306
said: 1 | **LINKWIN** t_ms:39829049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-80 rssi_med:-56 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 4 | 0x00000200 ble met predicted:-57 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1403 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39883532 ±0 frame:5500
seq: 1250
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:307
said: 1 | **LINKWIN** t_ms:39889049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-60 rssi_med:-56 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-56 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1404 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39943532 ±0 frame:5500
seq: 1252
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:308
said: 1 | **LINKWIN** t_ms:39949049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-55 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-56 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON224 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37234066 ±21 frame:5500
seq: 263
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1161
said: 1 | **LINKWIN** t_ms:37239582 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:45 rssi_min:-82 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:38 rssi_min:-27 rssi_med:-25 rssi_max:-24
```

---

@LAT105LON225 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37294066 ±24 frame:5500
seq: 264
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1161
said: 1 | **LINKWIN** t_ms:37299582 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:28 rssi_min:-43 rssi_med:-39 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:17 rssi_min:-26 rssi_med:-25 rssi_max:-24
```

---

@LAT105LON226 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37354066 ±0 frame:5500
seq: 265
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1161
said: 1 | **LINKWIN** t_ms:37359582 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:46 rssi_min:-81 rssi_med:-40 rssi_max:-38
said: 3 | **LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-26 rssi_med:-24 rssi_max:-23
```

---

@LAT105LON227 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37414066 ±0 frame:5500
seq: 266
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1161
said: 1 | **LINKWIN** t_ms:37419582 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-25 rssi_med:-24 rssi_max:-24
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON228 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37474059 ±21 frame:5500
seq: 268
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1165
said: 1 | **LINKWIN** t_ms:37479582 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-39 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-26 rssi_med:-24 rssi_max:-23
```

---

@LAT103LON1405 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40003532 ±0 frame:5500
seq: 1254
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:309
said: 1 | **LINKWIN** t_ms:40009049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-79 rssi_med:-55 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:45 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1406 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40063532 ±0 frame:5500
seq: 1256
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:310
said: 1 | **LINKWIN** t_ms:40069049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-61 rssi_med:-55 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-52 rssi_med:-49 rssi_max:-48
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1407 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40123532 ±0 frame:5500
seq: 1258
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:311
said: 1 | **LINKWIN** t_ms:40129049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-56 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-51 rssi_med:-49 rssi_max:-39
said: 4 | 0x00000200 ble met predicted:-55 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1408 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40183532 ±0 frame:5500
seq: 1260
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:312
said: 1 | **LINKWIN** t_ms:40189049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-42 rssi_med:-41 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-56 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow violated predicted:-49 observed:-41
percept: 5 | 0x00000200 | link_stable | espnow | - | -
```

---

@LAT103LON1409 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40243532 ±0 frame:5500
seq: 1262
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:314
said: 1 | **LINKWIN** t_ms:40249049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-41 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1410 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40303532 ±0 frame:5500
seq: 1264
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:315
said: 1 | **LINKWIN** t_ms:40309049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-79 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-42 rssi_med:-41 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-55 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-42 observed:-41
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT106LON16 | created:0 | updated:0

**BAR** frame:5500 bar:67 own:10 held:0 terms:2 digest:0xee5eb19f settled_ms:120000
**HOLDS** agent:0x00000300 n:10 lo:1241 hi:1260 sum:12507

---

@LAT103LON1411 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40363532 ±0 frame:5500
seq: 1266
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:316
said: 1 | **LINKWIN** t_ms:40369049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-43 rssi_med:-42 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-41 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1412 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40423532 ±0 frame:5500
seq: 1268
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:317
said: 1 | **LINKWIN** t_ms:40429049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-60 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-54 observed:-54
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON229 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37534047 ±21 frame:5500
seq: 269
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1167
said: 1 | **LINKWIN** t_ms:37539582 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-26 rssi_med:-25 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-39 rssi_max:-37
```

---

@LAT103LON1413 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40483532 ±0 frame:5500
seq: 1270
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:318
said: 1 | **LINKWIN** t_ms:40489049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-42 observed:-41
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON230 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37594102 ±21 frame:5500
seq: 270
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1169
said: 1 | **LINKWIN** t_ms:37599616 stream:0x9afbb748 wall:0 window_ms:60039
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-46 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:87 rssi_min:-43 rssi_med:-31 rssi_max:-19
```

---

@LAT105LON231 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37831583 ±21 frame:5500
seq: 271
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1177
said: 1 | **LINKWIN** t_ms:37835092 stream:0x9afbb748 wall:0 window_ms:71346
said: 2 | **LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-39 rssi_med:-31 rssi_max:-28
said: 3 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-46 rssi_max:-42
```

---

@LAT105LON232 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 37899582 ±21 frame:5500
seq: 273
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1179
said: 1 | **LINKWIN** t_ms:37903092 stream:0x9afbb748 wall:0 window_ms:67998
said: 2 | **LINK** peer:0x00000300 proto:espnow n:66 rssi_min:-36 rssi_med:-31 rssi_max:-29
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-46 rssi_max:-43
```

---

@LAT103LON1414 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40543532 ±0 frame:5500
seq: 1272
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:319
said: 1 | **LINKWIN** t_ms:40549049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:46 rssi_min:-43 rssi_med:-41 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-63 rssi_med:-54 rssi_max:-53
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON233 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38207663 ±21 frame:5500
seq: 278
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1189
said: 1 | **LINKWIN** t_ms:38211167 stream:0x9afbb748 wall:0 window_ms:61999
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-79 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:45 rssi_min:-51 rssi_med:-50 rssi_max:-49
```

---

@LAT105LON234 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38265116 ±21 frame:5500
seq: 279
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1191
said: 1 | **LINKWIN** t_ms:38271168 stream:0x9afbb748 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-51 rssi_med:-50 rssi_max:-49
```

---

@LAT103LON1415 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40603532 ±0 frame:5500
seq: 1274
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:320
said: 1 | **LINKWIN** t_ms:40609049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-42 rssi_med:-41 rssi_max:-41
said: 4 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-54 observed:-54
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25782 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40603532 ±0 frame:5500
seq: 1275
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:320
said: 1 | **ACOUSTICWIN** t_ms:40609049 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3727 rate:8000
said: 2 | **ACOUSTIC** rms_mean:135 rms_max:673 peak:1106 transients:0
```

---

@LAT103LON1416 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40663532 ±0 frame:5500
seq: 1276
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:321
said: 1 | **LINKWIN** t_ms:40669049 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-81 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-54 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25783 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40663532 ±0 frame:5500
seq: 1277
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:321
said: 1 | **ACOUSTICWIN** t_ms:40669049 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3730 rate:8000
said: 2 | **ACOUSTIC** rms_mean:81 rms_max:286 peak:525 transients:0
```

---

@LAT105LON235 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38329750 ±21 frame:5500
seq: 280
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1193
said: 1 | **LINKWIN** t_ms:38333251 stream:0x9afbb748 wall:0 window_ms:62084
said: 2 | **LINK** peer:0x00000300 proto:ble n:72 rssi_min:-81 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-56 rssi_med:-50 rssi_max:-50
```

---

@LAT105LON236 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38390254 ±21 frame:5500
seq: 281
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1195
said: 1 | **LINKWIN** t_ms:38393753 stream:0x9afbb748 wall:0 window_ms:60503
said: 2 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-92 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-80 rssi_med:-52 rssi_max:-50
```

---

@LAT105LON237 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38451749 ±22 frame:5500
seq: 282
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1197
said: 1 | **LINKWIN** t_ms:38455249 stream:0x9afbb748 wall:0 window_ms:61495
said: 2 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-81 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-52 rssi_med:-50 rssi_max:-49
```

---

@LAT105LON238 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38511818 ±21 frame:5500
seq: 283
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1199
said: 1 | **LINKWIN** t_ms:38517335 stream:0x9afbb748 wall:0 window_ms:60079
said: 2 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-52 rssi_max:-50
```

---

@LAT103LON1417 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40723534 ±0 frame:5500
seq: 1278
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:322
said: 1 | **LINKWIN** t_ms:40729051 stream:0x9afbb748 wall:0 window_ms:60002
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-80 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:43 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-55 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25784 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40723534 ±0 frame:5500
seq: 1279
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:322
said: 1 | **ACOUSTICWIN** t_ms:40729051 stream:0x9afbb748 wall:0 window_ms:60002 blocks:3562 rate:8000
said: 2 | **ACOUSTIC** rms_mean:113 rms_max:404 peak:879 transients:0
```

---

@LAT105LON239 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38571836 ±21 frame:5500
seq: 284
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1204
said: 1 | **LINKWIN** t_ms:38577340 stream:0x9afbb748 wall:0 window_ms:60005
said: 2 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-79 rssi_med:-52 rssi_max:-50
```

---

@LAT105LON240 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38633698 ±21 frame:5500
seq: 285
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1204
said: 1 | **LINKWIN** t_ms:38637193 stream:0x9afbb748 wall:0 window_ms:61861
said: 2 | **LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-71 rssi_med:-52 rssi_max:-50
```

---

@LAT105LON241 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38693755 ±21 frame:5500
seq: 286
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1206
said: 1 | **LINKWIN** t_ms:38697252 stream:0x9afbb748 wall:0 window_ms:60056
said: 2 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-51 rssi_med:-50 rssi_max:-49
```

---

@LAT105LON242 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38753755 ±22 frame:5500
seq: 287
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1210
said: 1 | **LINKWIN** t_ms:38759257 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-80 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-51 rssi_med:-50 rssi_max:-49
```

---

@LAT105LON243 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38815548 ±21 frame:5500
seq: 288
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1210
said: 1 | **LINKWIN** t_ms:38819075 stream:0x9afbb748 wall:0 window_ms:61825
said: 2 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-54 rssi_med:-50 rssi_max:-45
said: 3 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-82 rssi_med:-52 rssi_max:-47
```

---

@LAT105LON244 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38876176 ±21 frame:5500
seq: 289
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1212
said: 1 | **LINKWIN** t_ms:38879669 stream:0x9afbb748 wall:0 window_ms:60593
said: 2 | **LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-79 rssi_med:-52 rssi_max:-50
```

---

@LAT103LON1418 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40783534 ±0 frame:5500
seq: 1280
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:323
said: 1 | **LINKWIN** t_ms:40789051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-57 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:56 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25785 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40783534 ±0 frame:5500
seq: 1281
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:323
said: 1 | **ACOUSTICWIN** t_ms:40789051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3555 rate:8000
said: 2 | **ACOUSTIC** rms_mean:115 rms_max:410 peak:736 transients:0
```

---

@LAT103LON1419 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40843534 ±0 frame:5500
seq: 1282
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:323
said: 1 | **LINKWIN** t_ms:40849051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:46 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:3 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-41 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25786 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40843534 ±0 frame:5500
seq: 1283
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:323
said: 1 | **ACOUSTICWIN** t_ms:40849051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3737 rate:8000
said: 2 | **ACOUSTIC** rms_mean:134 rms_max:8429 peak:9164 transients:7
said: 3 | **TRANSIENT** t_ms:40831507 stream:0x9afbb748 wall:0 rms:8429
```

---

@LAT103LON1420 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40903534 ±0 frame:5500
seq: 1284
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:325
said: 1 | **LINKWIN** t_ms:40909051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25787 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40903534 ±0 frame:5500
seq: 1285
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:325
said: 1 | **ACOUSTICWIN** t_ms:40909051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3557 rate:8000
said: 2 | **ACOUSTIC** rms_mean:124 rms_max:459 peak:810 transients:0
```
@LAT106LON17 | created:0 | updated:0

**BAR** frame:5500 bar:68 own:10 held:0 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000300 n:10 lo:1262 hi:1280 sum:12710

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:40936053 stream:0x9afbb748 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:251 half_life_ms:600000 reinforced:8 last_ms:3553106
t_ms:40936053 stream:0x9afbb748 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:40936053 stream:0x9afbb748 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:40936053 stream:0x9afbb748 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:40936053 stream:0x9afbb748 wall:0

---

@LAT103LON1421 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40963534 ±0 frame:5500
seq: 1286
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:326
said: 1 | **LINKWIN** t_ms:40969051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:11 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-83 rssi_med:-54 rssi_max:-52
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25788 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40963534 ±0 frame:5500
seq: 1287
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:326
said: 1 | **ACOUSTICWIN** t_ms:40969051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3249 rate:8000
said: 2 | **ACOUSTIC** rms_mean:107 rms_max:721 peak:1142 transients:0
```

---

@LAT105LON245 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38936188 ±21 frame:5500
seq: 290
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1216
said: 1 | **LINKWIN** t_ms:38941686 stream:0x9afbb748 wall:0 window_ms:60012
said: 2 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-51 rssi_med:-50 rssi_max:-49
```

---

@LAT105LON246 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 38996498 ±21 frame:5500
seq: 292
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1216
said: 1 | **LINKWIN** t_ms:39001991 stream:0x9afbb748 wall:0 window_ms:60310
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-52 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-90 rssi_med:-50 rssi_max:-49
```

---

@LAT105LON247 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 39056596 ±21 frame:5500
seq: 293
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1220
said: 1 | **LINKWIN** t_ms:39062094 stream:0x9afbb748 wall:0 window_ms:60097
said: 2 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-52 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-51 rssi_med:-50 rssi_max:-49
```

---

@LAT105LON248 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 39116647 ±21 frame:5500
seq: 294
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1222
said: 1 | **LINKWIN** t_ms:39122143 stream:0x9afbb748 wall:0 window_ms:60049
said: 2 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:73 rssi_min:-81 rssi_med:-53 rssi_max:-50
```

---

@LAT103LON1422 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41023534 ±0 frame:5500
seq: 1288
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:327
said: 1 | **LINKWIN** t_ms:41029051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:49 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-54 observed:-54
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON16451 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 41023534 ±0 frame:5500
seq: 1289
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:327
said: 1 | **MOTIONWIN** t_ms:41029051 stream:0x9afbb748 wall:0 window_ms:60000 n:947
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28150 window_ms:1740002 moving_permille:0 dev_mean_mg:11 dev_max_mg:18 moving_ms:0 first_t_ms:39289049 last_t_ms:40969051 covered_by:@LAT103LON16450
```

---

@LAT103LON25789 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41023534 ±0 frame:5500
seq: 1290
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:327
said: 1 | **ACOUSTICWIN** t_ms:41029051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3546 rate:8000
said: 2 | **ACOUSTIC** rms_mean:98 rms_max:447 peak:754 transients:0
```

---

@LAT105LON249 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 39176657 ±23 frame:5500
seq: 295
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1225
said: 1 | **LINKWIN** t_ms:39182152 stream:0x9afbb748 wall:0 window_ms:60009
said: 2 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-79 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:29 rssi_min:-51 rssi_med:-50 rssi_max:-48
```

---

@LAT105LON250 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 39236725 ±21 frame:5500
seq: 296
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1228
said: 1 | **LINKWIN** t_ms:39242219 stream:0x9afbb748 wall:0 window_ms:60067
said: 2 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-50 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-53 rssi_med:-53 rssi_max:-50
```

---

@LAT105LON251 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 39296727 ±21 frame:5500
seq: 297
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000300:1230
said: 1 | **LINKWIN** t_ms:39302219 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-53 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-51 rssi_med:-50 rssi_max:-49
```

---

@LAT103LON1423 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41083534 ±0 frame:5500
seq: 1291
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:327
said: 1 | **LINKWIN** t_ms:41089051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:55 rssi_min:-43 rssi_med:-42 rssi_max:-40
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-54 rssi_max:-52
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25790 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41083534 ±0 frame:5500
seq: 1292
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:327
said: 1 | **ACOUSTICWIN** t_ms:41089051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3562 rate:8000
said: 2 | **ACOUSTIC** rms_mean:92 rms_max:449 peak:803 transients:0
```

---

@LAT103LON1424 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41143534 ±0 frame:5500
seq: 1293
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:328
said: 1 | **LINKWIN** t_ms:41149051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-54 observed:-54
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25791 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41143534 ±0 frame:5500
seq: 1294
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:328
said: 1 | **ACOUSTICWIN** t_ms:41149051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3726 rate:8000
said: 2 | **ACOUSTIC** rms_mean:86 rms_max:185 peak:428 transients:0
```

---

@LAT103LON1425 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41203534 ±0 frame:5500
seq: 1295
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:329
said: 1 | **LINKWIN** t_ms:41209051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-62 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-42 observed:-41
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25792 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41203534 ±0 frame:5500
seq: 1296
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:329
said: 1 | **ACOUSTICWIN** t_ms:41209051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3737 rate:8000
said: 2 | **ACOUSTIC** rms_mean:86 rms_max:203 peak:639 transients:0
```

---

@LAT103LON1426 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41263534 ±0 frame:5500
seq: 1297
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:331
said: 1 | **LINKWIN** t_ms:41269051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25793 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41263534 ±0 frame:5500
seq: 1298
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:331
said: 1 | **ACOUSTICWIN** t_ms:41269051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3724 rate:8000
said: 2 | **ACOUSTIC** rms_mean:116 rms_max:336 peak:913 transients:0
```

---

@LAT103LON1427 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41323534 ±0 frame:5500
seq: 1299
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:332
said: 1 | **LINKWIN** t_ms:41329051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-82 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-41 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25794 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41323534 ±0 frame:5500
seq: 1300
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:332
said: 1 | **ACOUSTICWIN** t_ms:41329051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3731 rate:8000
said: 2 | **ACOUSTIC** rms_mean:132 rms_max:394 peak:790 transients:0
```

---

@LAT103LON1428 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41383534 ±0 frame:5500
seq: 1301
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:333
said: 1 | **LINKWIN** t_ms:41389051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-44 rssi_med:-42 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25795 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41383534 ±0 frame:5500
seq: 1302
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:333
said: 1 | **ACOUSTICWIN** t_ms:41389051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3724 rate:8000
said: 2 | **ACOUSTIC** rms_mean:119 rms_max:288 peak:765 transients:0
```

---

@LAT103LON1429 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41443534 ±0 frame:5500
seq: 1303
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:334
said: 1 | **LINKWIN** t_ms:41449051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-63 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25796 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41443534 ±0 frame:5500
seq: 1304
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:334
said: 1 | **ACOUSTICWIN** t_ms:41449051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3733 rate:8000
said: 2 | **ACOUSTIC** rms_mean:138 rms_max:2339 peak:3422 transients:4
said: 3 | **TRANSIENT** t_ms:41446335 stream:0x9afbb748 wall:0 rms:2339
```

---

@LAT103LON1430 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41503534 ±0 frame:5500
seq: 1305
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:334
said: 1 | **LINKWIN** t_ms:41509051 stream:0x9afbb748 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-54 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-54 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON25797 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41503534 ±0 frame:5500
seq: 1306
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:334
said: 1 | **ACOUSTICWIN** t_ms:41509051 stream:0x9afbb748 wall:0 window_ms:60000 blocks:3735 rate:8000
said: 2 | **ACOUSTIC** rms_mean:199 rms_max:11296 peak:32767 transients:8
said: 3 | **TRANSIENT** t_ms:41457277 stream:0x9afbb748 wall:0 rms:11296
```

---

@LAT104LON300 | created:0 | updated:0

**carried through @LAT103LON1385**

```ttdb-carried
through: 1385
through: 8263
through: 16428
through: 25781
carried: 754 15 968 695 | 0x00000200 | link_stable | espnow
carried: 823 13 1192 708 | 0x00000200 | link_stable | ble
carried: 397 3 753 271 | 0x00000100 | link_stable | espnow
carried: 534 11 899 416 | 0x00000010 | link_stable | ble
carried: 524 18 895 414 | 0x00000010 | link_stable | espnow
carried: 91 0 91 97 | 0x00000011 | link_stable | ble
carried: 87 4 91 97 | 0x00000011 | link_stable | espnow
carried: 59 2 61 64 | 0x00000012 | link_stable | ble
carried: 57 2 59 61 | 0x00000012 | link_stable | espnow
```
@LAT106LON18 | created:0 | updated:0

**BAR** frame:5500 bar:69 own:10 held:0 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000300 n:10 lo:1282 hi:1301 sum:12916
