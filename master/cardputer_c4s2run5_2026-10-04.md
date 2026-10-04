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

@LAT103LON8311 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:43500
seq: 1308
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:334
said: 1 | **ENTWIN** t_ms:41611833 stream:0x9afbb748 wall:0 window_ms:60000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON16452 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:43500
seq: 1309
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:334
said: 1 | **MOTIONWIN** t_ms:41611833 stream:0x9afbb748 wall:0 window_ms:60000 n:297
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON16453 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 41896018 ±214768 frame:5500
seq: 1318
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:339
said: 1 | **MOTIONWIN** t_ms:41906425 stream:0x9afbb748 wall:0 window_ms:70513 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8312 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 41952702 ±0 frame:5500
seq: 1320
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:341
said: 1 | **ENTWIN** t_ms:41962657 stream:0x9afbb748 wall:0 window_ms:127197 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8313 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 62538 ±0 frame:8500
seq: 1342
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:358
said: 1 | **ENTWIN** t_ms:42794291 stream:0x9afbb748 wall:0 window_ms:62538 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON16454 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 62538 ±0 frame:8500
seq: 1343
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:358
said: 1 | **MOTIONWIN** t_ms:42794291 stream:0x9afbb748 wall:0 window_ms:62538 n:457
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:34 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT106LON20 | created:0 | updated:0

**BAR** frame:5500 bar:71 own:9 held:7 terms:2 digest:0x8a894ac9 settled_ms:194552
**HOLDS** agent:0x00000200 n:7 lo:344 hi:351 sum:2435
**HOLDS** agent:0x00000300 n:9 lo:1323 hi:1339 sum:11979

---

@LAT106LON21 | created:0 | updated:0

**BAR** frame:5500 bar:72 own:7 held:7 terms:2 digest:0x15b27419 settled_ms:120000
**HOLDS** agent:0x00000200 n:7 lo:355 hi:363 sum:2514
**HOLDS** agent:0x00000300 n:7 lo:1345 hi:1357 sum:9457

---

@LAT106LON22 | created:0 | updated:0

**BAR** frame:5500 bar:73 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:364 hi:373 sum:3685
**HOLDS** agent:0x00000300 n:10 lo:1359 hi:1377 sum:13680

---

@LAT103LON8314 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 43933179 ±0 frame:5500
seq: 1383
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:375
said: 1 | **ENTWIN** t_ms:43945956 stream:0x9afbb748 wall:0 window_ms:599987 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,0283cce0e689,64677217947d
said: 11 | **COVERED** windows:1 entities:9 window_ms:551678 first_t_ms:43345969 last_t_ms:43345969 covered_by:@LAT103LON8313
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:bc3e073874d8 n:1 rssi:-95 windows:1
```

---

@LAT106LON23 | created:0 | updated:0

**BAR** frame:5500 bar:74 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:374 hi:384 sum:3789
**HOLDS** agent:0x00000300 n:10 lo:1379 hi:1398 sum:13888

---

@LAT103LON16455 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 44581714 ±0 frame:5500
seq: 1405
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:387
said: 1 | **MOTIONWIN** t_ms:44594491 stream:0x9afbb748 wall:0 window_ms:60000 n:870
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27998 window_ms:1740200 moving_permille:2 dev_mean_mg:11 dev_max_mg:707 moving_ms:3508 first_t_ms:42854291 last_t_ms:44534491 covered_by:@LAT103LON16454
```

---

@LAT106LON24 | created:0 | updated:0

**BAR** frame:5500 bar:75 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:385 hi:394 sum:3895
**HOLDS** agent:0x00000300 n:10 lo:1400 hi:1419 sum:14097

---

@LAT103LON8315 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 45134591 ±0 frame:5500
seq: 1425
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:395
said: 1 | **ENTWIN** t_ms:45147368 stream:0x9afbb748 wall:0 window_ms:601341 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,0283cce0e689,bc102f237ace,aef9ff2626ac
said: 12 | **COVERED** windows:1 entities:9 window_ms:600071 first_t_ms:44546027 last_t_ms:44546027 covered_by:@LAT103LON8314
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94 windows:1
```

---

@LAT106LON25 | created:0 | updated:0

**BAR** frame:5500 bar:76 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:395 hi:405 sum:3999
**HOLDS** agent:0x00000300 n:10 lo:1421 hi:1440 sum:14308

---

@LAT106LON26 | created:0 | updated:0

**BAR** frame:5500 bar:77 own:10 held:9 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000200 n:9 lo:406 hi:416 sum:3694
**HOLDS** agent:0x00000300 n:10 lo:1442 hi:1460 sum:14510

---

@LAT103LON16456 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 46381714 ±0 frame:5500
seq: 1467
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:419
said: 1 | **MOTIONWIN** t_ms:46394491 stream:0x9afbb748 wall:0 window_ms:60000 n:793
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28279 window_ms:1740000 moving_permille:0 dev_mean_mg:11 dev_max_mg:29 moving_ms:0 first_t_ms:44654491 last_t_ms:46334491 covered_by:@LAT103LON16455
```

---

@LAT106LON27 | created:0 | updated:0

**BAR** frame:5500 bar:78 own:10 held:10 terms:2 digest:0x0938c1d3 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:417 hi:426 sum:4215
**HOLDS** agent:0x00000300 n:10 lo:1462 hi:1481 sum:14717

---

@LAT103LON16457 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 66844
seq: 1492
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:430
said: 1 | **MOTIONWIN** t_ms:47152739 stream:0x9afbb748 wall:0 window_ms:66844 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:10 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8316 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 117213 ±0 frame:67000
seq: 1494
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:432
said: 1 | **ENTWIN** t_ms:47202884 stream:0x9afbb748 wall:0 window_ms:117213 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT106LON28 | created:0 | updated:0

**BAR** frame:5500 bar:79 own:7 held:10 terms:2 digest:0x15b27419 settled_ms:122095
**HOLDS** agent:0x00000200 n:10 lo:427 hi:437 sum:4317
**HOLDS** agent:0x00000300 n:7 lo:1483 hi:1499 sum:10435

---

@LAT103LON8317 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:15500
seq: 1517
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:444
said: 1 | **ENTWIN** t_ms:41878 stream:0x3c4214c9 wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON16458 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:15500
seq: 1518
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:121 0x00000200:444
said: 1 | **MOTIONWIN** t_ms:41878 stream:0x3c4214c9 wall:0 window_ms:60000 n:793
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:2 dev_max_mg:7 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT106LON29 | created:0 | updated:0

**BAR** frame:7000 bar:1 own:10 held:8 terms:3 digest:0xc4cbb2c3 settled_ms:120000
**HOLDS** agent:0x00000200 n:8 lo:447 hi:455 sum:3611
**HOLDS** agent:0x00000300 n:10 lo:1522 hi:1540 sum:15310

---

@LAT103LON8318 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1159644 ±0 frame:7000
seq: 1559
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:144 0x00000200:465
said: 1 | **ENTWIN** t_ms:1203036 stream:0x3c4214c9 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,64677217947d,84a329c78fec,0283cce0e689,e6b32d2cea8b
said: 12 | **COVERED** windows:1 entities:11 window_ms:561158 first_t_ms:603036 last_t_ms:603036 covered_by:@LAT103LON8317
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-81 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93 windows:1
```

---

@LAT106LON30 | created:0 | updated:0

**BAR** frame:7000 bar:2 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:456 hi:465 sum:4605
**HOLDS** agent:0x00000300 n:10 lo:1542 hi:1561 sum:15511

---

@LAT103LON16459 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 1798486 ±0 frame:7000
seq: 1580
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:155 0x00000200:476
said: 1 | **MOTIONWIN** t_ms:1841878 stream:0x3c4214c9 wall:0 window_ms:60000 n:996
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:5 dev_max_mg:8 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28355 window_ms:1740000 moving_permille:0 dev_mean_mg:4 dev_max_mg:50 moving_ms:0 first_t_ms:101878 last_t_ms:1781878 covered_by:@LAT103LON16458
```

---

@LAT106LON31 | created:0 | updated:0

**BAR** frame:7000 bar:3 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:466 hi:476 sum:4713
**HOLDS** agent:0x00000300 n:10 lo:1563 hi:1582 sum:15721

---

@LAT103LON1566 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2164417 ±0 frame:7000
seq: 1594
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:162 0x00000200:483
said: 1 | **LINKWIN** t_ms:2207809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-44 observed:-44
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1567 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2224417 ±0 frame:7000
seq: 1596
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:163 0x00000200:484
said: 1 | **LINKWIN** t_ms:2267809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-29 rssi_med:-28 rssi_max:-27
said: 4 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1568 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2284417 ±0 frame:7000
seq: 1598
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:164 0x00000200:485
said: 1 | **LINKWIN** t_ms:2327809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-40 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1569 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2344417 ±0 frame:7000
seq: 1600
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:165 0x00000200:486
said: 1 | **LINKWIN** t_ms:2387809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-45 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-45
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON8319 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2359643 ±0 frame:7000
seq: 1601
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:165 0x00000200:486
said: 1 | **ENTWIN** t_ms:2403035 stream:0x3c4214c9 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,84a329c78fec,e6b32d2cea8b,5ce28c488e0c,aef9ff2626ac,0283cce0e689
said: 13 | **COVERED** windows:1 entities:9 window_ms:600000 first_t_ms:1803036 last_t_ms:1803036 covered_by:@LAT103LON8318
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-81 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-87 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
```

---

@LAT103LON1570 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2404417 ±0 frame:7000
seq: 1603
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:166 0x00000200:487
said: 1 | **LINKWIN** t_ms:2447809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-48 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000200 proto:espnow n:43 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-45 observed:-48
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1571 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2464417 ±0 frame:7000
seq: 1605
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:167 0x00000200:488
said: 1 | **LINKWIN** t_ms:2507809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000200 ble met predicted:-48 observed:-44
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1572 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2524417 ±0 frame:7000
seq: 1607
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:169 0x00000200:489
said: 1 | **LINKWIN** t_ms:2567809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-82 rssi_med:-45 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-45
percept: 7 | 0x00000200 | link_stable | ble | + | -
```
@LAT106LON32 | created:0 | updated:0

**BAR** frame:7000 bar:4 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:477 hi:487 sum:4823
**HOLDS** agent:0x00000300 n:10 lo:1584 hi:1603 sum:15931

---

@LAT105LON430 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 2542139 ±21 frame:7000
seq: 490
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:169 0x00000300:1607
said: 1 | **LINKWIN** t_ms:2585488 stream:0x3c4214c9 wall:0 window_ms:64617
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-25 rssi_med:-24 rssi_max:-24
```

---

@LAT103LON1573 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2584417 ±0 frame:7000
seq: 1609
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:171 0x00000200:490
said: 1 | **LINKWIN** t_ms:2627809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:32 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-83 rssi_med:-45 rssi_max:-42
said: 5 | 0x00000200 ble met predicted:-45 observed:-45
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT105LON431 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 2602110 ±21 frame:7000
seq: 491
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:171 0x00000300:1609
said: 1 | **LINKWIN** t_ms:2645494 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000100 proto:espnow n:71 rssi_min:-37 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:espnow n:70 rssi_min:-25 rssi_med:-24 rssi_max:-23
```

---

@LAT103LON1574 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2644417 ±0 frame:7000
seq: 1611
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:172 0x00000200:491
said: 1 | **LINKWIN** t_ms:2687809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000200 proto:espnow n:33 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-45 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON432 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 2662142 ±21 frame:7000
seq: 492
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:172 0x00000300:1611
said: 1 | **LINKWIN** t_ms:2705494 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-40 rssi_max:-37
said: 4 | **LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-24 rssi_med:-24 rssi_max:-23
```

---

@LAT103LON1575 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2704417 ±0 frame:7000
seq: 1613
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:173 0x00000200:492
said: 1 | **LINKWIN** t_ms:2747809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:31 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 3 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-83 rssi_med:-44 rssi_max:-42
said: 4 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 5 | 0x00000200 ble met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON433 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 2722104 ±21 frame:7000
seq: 493
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:173 0x00000300:1613
said: 1 | **LINKWIN** t_ms:2765494 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:espnow n:76 rssi_min:-25 rssi_med:-24 rssi_max:-23
```

---

@LAT103LON1576 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2764417 ±0 frame:7000
seq: 1615
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:174 0x00000200:493
said: 1 | **LINKWIN** t_ms:2807809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-39 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:43 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-44 observed:-44
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT105LON434 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 2782143 ±21 frame:7000
seq: 494
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:174 0x00000300:1615
said: 1 | **LINKWIN** t_ms:2825494 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-37 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-40 rssi_max:-37
said: 4 | **LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-25 rssi_med:-24 rssi_max:-23
```

---

@LAT103LON1577 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2824417 ±0 frame:7000
seq: 1617
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:175 0x00000200:494
said: 1 | **LINKWIN** t_ms:2867809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-39 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON435 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 2842145 ±21 frame:7000
seq: 495
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:175 0x00000300:1617
said: 1 | **LINKWIN** t_ms:2885494 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-37 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-40 rssi_max:-37
said: 4 | **LINK** peer:0x00000300 proto:espnow n:58 rssi_min:-25 rssi_med:-24 rssi_max:-23
```

---

@LAT103LON1578 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2884417 ±0 frame:7000
seq: 1619
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:176 0x00000200:495
said: 1 | **LINKWIN** t_ms:2927809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-39 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON436 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 2902095 ±21 frame:7000
seq: 496
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:176 0x00000300:1619
said: 1 | **LINKWIN** t_ms:2945494 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:62 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 3 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-37 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON1579 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2944417 ±0 frame:7000
seq: 1621
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:177 0x00000200:496
said: 1 | **LINKWIN** t_ms:2987809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-80 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1580 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3004417 ±0 frame:7000
seq: 1623
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:178 0x00000200:497
said: 1 | **LINKWIN** t_ms:3047809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-45 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-39 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000200 proto:espnow n:49 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000200 ble met predicted:-44 observed:-45
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON437 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 2962144 ±21 frame:7000
seq: 497
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:177 0x00000300:1621
said: 1 | **LINKWIN** t_ms:3005494 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-40 rssi_max:-37
said: 4 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-25 rssi_med:-24 rssi_max:-23
```

---

@LAT105LON438 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3022148 ±21 frame:7000
seq: 498
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:178 0x00000300:1623
said: 1 | **LINKWIN** t_ms:3065494 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-38 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:69 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON1581 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3064417 ±0 frame:7000
seq: 1625
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:179 0x00000200:498
said: 1 | **LINKWIN** t_ms:3107809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:45 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000200 ble met predicted:-45 observed:-44
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON439 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3082146 ±22 frame:7000
seq: 499
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:179 0x00000300:1625
said: 1 | **LINKWIN** t_ms:3125494 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-39 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON1582 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3124417 ±0 frame:7000
seq: 1627
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:180 0x00000200:499
said: 1 | **LINKWIN** t_ms:3167809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-40 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 4 | **LINK** peer:0x00000200 proto:espnow n:39 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```
@LAT106LON33 | created:0 | updated:0

**BAR** frame:7000 bar:5 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:488 hi:497 sum:4925
**HOLDS** agent:0x00000300 n:10 lo:1605 hi:1623 sum:16140

---

@LAT105LON440 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3142148 ±21 frame:7000
seq: 500
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:180 0x00000300:1627
said: 1 | **LINKWIN** t_ms:3185494 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:43 rssi_min:-25 rssi_med:-24 rssi_max:-24
said: 4 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-38 rssi_med:-37 rssi_max:-37
```

---

@LAT103LON1583 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3184417 ±0 frame:7000
seq: 1629
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:181 0x00000200:500
said: 1 | **LINKWIN** t_ms:3227809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-40 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:espnow n:46 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-45 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-44 observed:-45
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON441 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3199045 ±22 frame:7000
seq: 501
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:181 0x00000300:1629
said: 1 | **LINKWIN** t_ms:3245494 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-37 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:71 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON1584 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3244417 ±0 frame:7000
seq: 1631
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:182 0x00000200:501
said: 1 | **LINKWIN** t_ms:3287809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:38 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-36 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-45 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON442 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3262151 ±21 frame:7000
seq: 502
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:182 0x00000300:1631
said: 1 | **LINKWIN** t_ms:3305545 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 3 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-37 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON1585 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3304417 ±0 frame:7000
seq: 1633
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:183 0x00000200:502
said: 1 | **LINKWIN** t_ms:3347809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON443 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3322153 ±21 frame:7000
seq: 503
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:183 0x00000300:1633
said: 1 | **LINKWIN** t_ms:3365545 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-37 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:68 rssi_min:-25 rssi_med:-24 rssi_max:-24
said: 4 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON25953 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3358487 ±0 frame:7000
seq: 1634
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:184 0x00000200:503
said: 1 | **ACOUSTICWIN** t_ms:3401879 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3562 rate:8000
said: 2 | **ACOUSTIC** rms_mean:89 rms_max:181 peak:418 transients:0
```

---

@LAT103LON1586 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3364417 ±0 frame:7000
seq: 1635
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:184 0x00000200:503
said: 1 | **LINKWIN** t_ms:3407809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON444 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3382154 ±21 frame:7000
seq: 504
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:184 0x00000300:1635
said: 1 | **LINKWIN** t_ms:3425545 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:62 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON25954 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3418487 ±0 frame:7000
seq: 1636
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:185 0x00000200:504
said: 1 | **ACOUSTICWIN** t_ms:3461879 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3718 rate:8000
said: 2 | **ACOUSTIC** rms_mean:96 rms_max:446 peak:973 transients:0
```

---

@LAT103LON1587 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3424417 ±0 frame:7000
seq: 1637
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:185 0x00000200:504
said: 1 | **LINKWIN** t_ms:3467809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON445 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3442152 ±21 frame:7000
seq: 505
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:185 0x00000300:1637
said: 1 | **LINKWIN** t_ms:3485545 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-37 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-40 rssi_max:-37
said: 4 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-26 rssi_med:-24 rssi_max:-24
```

---

@LAT103LON25955 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3478487 ±0 frame:7000
seq: 1638
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:186 0x00000200:505
said: 1 | **ACOUSTICWIN** t_ms:3521879 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3713 rate:8000
said: 2 | **ACOUSTIC** rms_mean:91 rms_max:201 peak:456 transients:0
```

---

@LAT103LON1588 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3484417 ±0 frame:7000
seq: 1639
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:186 0x00000200:505
said: 1 | **LINKWIN** t_ms:3527809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000200 proto:espnow n:38 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON446 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3502156 ±21 frame:7000
seq: 506
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:186 0x00000300:1639
said: 1 | **LINKWIN** t_ms:3545545 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-38 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:63 rssi_min:-25 rssi_med:-24 rssi_max:-24
said: 4 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON25956 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3538487 ±0 frame:7000
seq: 1640
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:187 0x00000200:506
said: 1 | **ACOUSTICWIN** t_ms:3581879 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3727 rate:8000
said: 2 | **ACOUSTIC** rms_mean:100 rms_max:1397 peak:2539 transients:2
said: 3 | **TRANSIENT** t_ms:3550609 stream:0x3c4214c9 wall:0 rms:1397
```

---

@LAT103LON1589 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3544417 ±0 frame:7000
seq: 1641
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:187 0x00000200:506
said: 1 | **LINKWIN** t_ms:3587809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-39 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 4 | **LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000200 ble met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON447 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3562157 ±21 frame:7000
seq: 507
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:187 0x00000300:1641
said: 1 | **LINKWIN** t_ms:3605545 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-25 rssi_med:-24 rssi_max:-24
said: 3 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON16460 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3598487 ±0 frame:7000
seq: 1642
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:188 0x00000200:507
said: 1 | **MOTIONWIN** t_ms:3641879 stream:0x3c4214c9 wall:0 window_ms:60000 n:997
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:6 dev_max_mg:9 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28067 window_ms:1740001 moving_permille:0 dev_mean_mg:5 dev_max_mg:13 moving_ms:0 first_t_ms:1901878 last_t_ms:3581879 covered_by:@LAT103LON16459
```

---

@LAT103LON25957 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3598487 ±0 frame:7000
seq: 1643
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:188 0x00000200:507
said: 1 | **ACOUSTICWIN** t_ms:3641879 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3733 rate:8000
said: 2 | **ACOUSTIC** rms_mean:113 rms_max:1505 peak:4338 transients:11
said: 3 | **TRANSIENT** t_ms:3633651 stream:0x3c4214c9 wall:0 rms:1505
```

---

@LAT103LON1590 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3604417 ±0 frame:7000
seq: 1644
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:188 0x00000200:507
said: 1 | **LINKWIN** t_ms:3647809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-44 observed:-44
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON448 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3622208 ±22 frame:7000
seq: 508
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:188 0x00000300:1644
said: 1 | **LINKWIN** t_ms:3665596 stream:0x3c4214c9 wall:0 window_ms:60051
said: 2 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-37 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:56 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON25958 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3658487 ±0 frame:7000
seq: 1645
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:189 0x00000200:508
said: 1 | **ACOUSTICWIN** t_ms:3701879 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3720 rate:8000
said: 2 | **ACOUSTIC** rms_mean:92 rms_max:530 peak:1490 transients:0
```

---

@LAT103LON1591 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3664417 ±0 frame:7000
seq: 1646
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:189 0x00000200:508
said: 1 | **LINKWIN** t_ms:3707809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-39 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:46 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000200 ble met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON449 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3682210 ±21 frame:7000
seq: 509
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:189 0x00000300:1646
said: 1 | **LINKWIN** t_ms:3725597 stream:0x3c4214c9 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-45 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-38 rssi_med:-37 rssi_max:-36
```

---

@LAT103LON25959 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3718487 ±0 frame:7000
seq: 1647
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:190 0x00000200:509
said: 1 | **ACOUSTICWIN** t_ms:3761879 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3724 rate:8000
said: 2 | **ACOUSTIC** rms_mean:105 rms_max:291 peak:558 transients:0
```

---

@LAT103LON1592 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3724417 ±0 frame:7000
seq: 1648
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:190 0x00000200:509
said: 1 | **LINKWIN** t_ms:3767809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-39 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```
@LAT106LON34 | created:0 | updated:0

**BAR** frame:7000 bar:6 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:498 hi:507 sum:5025
**HOLDS** agent:0x00000300 n:10 lo:1625 hi:1644 sum:16341

---

@LAT103LON25960 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3778487 ±0 frame:7000
seq: 1649
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:191 0x00000200:510
said: 1 | **ACOUSTICWIN** t_ms:3821879 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3169 rate:8000
said: 2 | **ACOUSTIC** rms_mean:107 rms_max:264 peak:611 transients:0
```

---

@LAT103LON1593 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3784417 ±0 frame:7000
seq: 1650
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:191 0x00000200:510
said: 1 | **LINKWIN** t_ms:3827809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000200 ble met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON450 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3742249 ±21 frame:7000
seq: 510
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:190 0x00000300:1648
said: 1 | **LINKWIN** t_ms:3785635 stream:0x3c4214c9 wall:0 window_ms:60038
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:56 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-38 rssi_med:-37 rssi_max:-36
```

---

@LAT105LON451 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3802248 ±21 frame:7000
seq: 511
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:191 0x00000300:1650
said: 1 | **LINKWIN** t_ms:3845634 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-37 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-79 rssi_med:-40 rssi_max:-37
said: 4 | **LINK** peer:0x00000300 proto:espnow n:66 rssi_min:-25 rssi_med:-24 rssi_max:-23
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:1366 last_ms:3888580
t_ms:3874202 stream:0x3c4214c9 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:607 last_ms:3891730
t_ms:3874202 stream:0x3c4214c9 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:3874202 stream:0x3c4214c9 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:3874202 stream:0x3c4214c9 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:3874202 stream:0x3c4214c9 wall:0

---

@LAT103LON25961 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3838487 ±0 frame:7000
seq: 1651
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:191 0x00000200:511
said: 1 | **ACOUSTICWIN** t_ms:3881879 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3379 rate:8000
said: 2 | **ACOUSTIC** rms_mean:103 rms_max:245 peak:515 transients:0
```

---

@LAT103LON1594 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3844417 ±0 frame:7000
seq: 1652
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:191 0x00000200:511
said: 1 | **LINKWIN** t_ms:3887809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-83 rssi_med:-44 rssi_max:-42
said: 4 | **LINK** peer:0x00000200 proto:espnow n:52 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25962 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3898487 ±0 frame:7000
seq: 1653
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:194 0x00000200:512
said: 1 | **ACOUSTICWIN** t_ms:3941879 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3735 rate:8000
said: 2 | **ACOUSTIC** rms_mean:97 rms_max:197 peak:480 transients:0
```

---

@LAT103LON1595 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3904417 ±0 frame:7000
seq: 1654
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:194 0x00000200:512
said: 1 | **LINKWIN** t_ms:3947809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-40 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-80 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-44 observed:-44
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON452 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3862252 ±21 frame:7000
seq: 512
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:191 0x00000300:1652
said: 1 | **LINKWIN** t_ms:3905635 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-37 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:56 rssi_min:-26 rssi_med:-24 rssi_max:-24
said: 4 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT105LON453 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3922249 ±21 frame:7000
seq: 513
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:195 0x00000300:1654
said: 1 | **LINKWIN** t_ms:3965635 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-38 rssi_med:-37 rssi_max:-37
said: 4 | **LINK** peer:0x00000300 proto:espnow n:61 rssi_min:-24 rssi_med:-24 rssi_max:-23
```

---

@LAT103LON25963 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3958487 ±0 frame:7000
seq: 1655
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:195 0x00000200:513
said: 1 | **ACOUSTICWIN** t_ms:4001879 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3714 rate:8000
said: 2 | **ACOUSTIC** rms_mean:100 rms_max:222 peak:555 transients:0
```

---

@LAT103LON1596 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3964417 ±0 frame:7000
seq: 1656
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:195 0x00000200:513
said: 1 | **LINKWIN** t_ms:4007809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000200 proto:espnow n:55 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON454 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3982245 ±21 frame:7000
seq: 514
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:196 0x00000300:1656
said: 1 | **LINKWIN** t_ms:4025635 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-38 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:70 rssi_min:-25 rssi_med:-24 rssi_max:-24
said: 4 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON25964 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4018502 ±0 frame:7000
seq: 1657
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:196 0x00000200:514
said: 1 | **ACOUSTICWIN** t_ms:4061894 stream:0x3c4214c9 wall:0 window_ms:60015 blocks:3701 rate:8000
said: 2 | **ACOUSTIC** rms_mean:96 rms_max:221 peak:542 transients:0
```

---

@LAT103LON1597 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4024417 ±0 frame:7000
seq: 1658
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:196 0x00000200:514
said: 1 | **LINKWIN** t_ms:4067809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:espnow n:33 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-39 rssi_med:-35 rssi_max:-34
said: 5 | 0x00000200 ble met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON455 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4042255 ±21 frame:7000
seq: 515
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:197 0x00000300:1658
said: 1 | **LINKWIN** t_ms:4085635 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-37 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON25965 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4078502 ±0 frame:7000
seq: 1659
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:197 0x00000200:515
said: 1 | **ACOUSTICWIN** t_ms:4121894 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3733 rate:8000
said: 2 | **ACOUSTIC** rms_mean:103 rms_max:684 peak:1220 transients:0
```

---

@LAT103LON1598 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4084417 ±0 frame:7000
seq: 1660
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:197 0x00000200:515
said: 1 | **LINKWIN** t_ms:4127809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 3 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000200 ble met predicted:-44 observed:-44
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON25966 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4138502 ±0 frame:7000
seq: 1661
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:198 0x00000200:516
said: 1 | **ACOUSTICWIN** t_ms:4181894 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3730 rate:8000
said: 2 | **ACOUSTIC** rms_mean:93 rms_max:220 peak:492 transients:0
```

---

@LAT103LON1599 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4144417 ±0 frame:7000
seq: 1662
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:198 0x00000200:516
said: 1 | **LINKWIN** t_ms:4187809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-45 rssi_max:-42
said: 4 | **LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 5 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-45
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25967 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4198502 ±0 frame:7000
seq: 1663
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:199 0x00000200:517
said: 1 | **ACOUSTICWIN** t_ms:4241894 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3731 rate:8000
said: 2 | **ACOUSTIC** rms_mean:94 rms_max:206 peak:508 transients:0
```

---

@LAT103LON1600 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4204417 ±0 frame:7000
seq: 1664
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:199 0x00000200:517
said: 1 | **LINKWIN** t_ms:4247809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:46 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 3 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-40 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-49 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-45 observed:-49
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON456 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4102298 ±21 frame:7000
seq: 516
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:198 0x00000300:1660
said: 1 | **LINKWIN** t_ms:4145677 stream:0x3c4214c9 wall:0 window_ms:60042
said: 2 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-37 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-25 rssi_med:-24 rssi_max:-24
said: 4 | **LINK** peer:0x00000300 proto:ble n:71 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON25968 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4258502 ±0 frame:7000
seq: 1665
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:200 0x00000200:518
said: 1 | **ACOUSTICWIN** t_ms:4301894 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3726 rate:8000
said: 2 | **ACOUSTIC** rms_mean:89 rms_max:197 peak:454 transients:0
```

---

@LAT103LON1601 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4264417 ±0 frame:7000
seq: 1666
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:200 0x00000200:518
said: 1 | **LINKWIN** t_ms:4307809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-49 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON457 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4162299 ±21 frame:7000
seq: 517
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:199 0x00000300:1662
said: 1 | **LINKWIN** t_ms:4205677 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:59 rssi_min:-25 rssi_med:-24 rssi_max:-24
said: 4 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-71 rssi_med:-40 rssi_max:-37
```

---

@LAT105LON458 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4222299 ±21 frame:7000
seq: 518
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:200 0x00000300:1664
said: 1 | **LINKWIN** t_ms:4265677 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-37 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:73 rssi_min:-25 rssi_med:-24 rssi_max:-24
said: 4 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-40 rssi_max:-37
```

---

@LAT103LON25969 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4318502 ±0 frame:7000
seq: 1667
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:201 0x00000200:519
said: 1 | **ACOUSTICWIN** t_ms:4361894 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3538 rate:8000
said: 2 | **ACOUSTIC** rms_mean:89 rms_max:280 peak:561 transients:0
```

---

@LAT103LON1602 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4324417 ±0 frame:7000
seq: 1668
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:201 0x00000200:519
said: 1 | **LINKWIN** t_ms:4367809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-41 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```
@LAT106LON35 | created:0 | updated:0

**BAR** frame:7000 bar:7 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:508 hi:517 sum:5125
**HOLDS** agent:0x00000300 n:10 lo:1646 hi:1664 sum:16550

---

@LAT105LON459 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4282300 ±21 frame:7000
seq: 519
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:201 0x00000300:1666
said: 1 | **LINKWIN** t_ms:4325677 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-38 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-40 rssi_max:-37
said: 4 | **LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-25 rssi_med:-24 rssi_max:-24
```

---

@LAT105LON460 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4342305 ±22 frame:7000
seq: 520
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:202 0x00000300:1668
said: 1 | **LINKWIN** t_ms:4385681 stream:0x3c4214c9 wall:0 window_ms:60004
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-40 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-38 rssi_med:-37 rssi_max:-37
```

---

@LAT103LON25970 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4378502 ±0 frame:7000
seq: 1669
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:202 0x00000200:520
said: 1 | **ACOUSTICWIN** t_ms:4421894 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3107 rate:8000
said: 2 | **ACOUSTIC** rms_mean:137 rms_max:3370 peak:7839 transients:4
said: 3 | **TRANSIENT** t_ms:4382486 stream:0x3c4214c9 wall:0 rms:3370
```

---

@LAT103LON1603 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4384417 ±0 frame:7000
seq: 1670
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:202 0x00000200:520
said: 1 | **LINKWIN** t_ms:4427809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-41 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000200 proto:espnow n:43 rssi_min:-30 rssi_med:-28 rssi_max:-27
said: 4 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-83 rssi_med:-44 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-35 observed:-35
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-44
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON461 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4402370 ±21 frame:7000
seq: 521
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:203 0x00000300:1670
said: 1 | **LINKWIN** t_ms:4445746 stream:0x3c4214c9 wall:0 window_ms:60065
said: 2 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-41 rssi_med:-37 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:69 rssi_min:-26 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-40 rssi_max:-36
```

---

@LAT103LON25971 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4438502 ±0 frame:7000
seq: 1671
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:203 0x00000200:521
said: 1 | **ACOUSTICWIN** t_ms:4481894 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3733 rate:8000
said: 2 | **ACOUSTIC** rms_mean:104 rms_max:1172 peak:3940 transients:1
said: 3 | **TRANSIENT** t_ms:4423737 stream:0x3c4214c9 wall:0 rms:1172
```

---

@LAT103LON1604 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4444417 ±0 frame:7000
seq: 1672
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:203 0x00000200:521
said: 1 | **LINKWIN** t_ms:4487809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-44 rssi_med:-38 rssi_max:-32
said: 3 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-29 rssi_med:-28 rssi_max:-26
said: 4 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-45 rssi_max:-41
said: 5 | 0x00000100 espnow met predicted:-35 observed:-38
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-28 observed:-28
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-44 observed:-45
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON25972 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4498502 ±0 frame:7000
seq: 1673
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:203 0x00000200:521
said: 1 | **ACOUSTICWIN** t_ms:4541894 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3727 rate:8000
said: 2 | **ACOUSTIC** rms_mean:286 rms_max:20736 peak:32768 transients:28
said: 3 | **TRANSIENT** t_ms:4487234 stream:0x3c4214c9 wall:0 rms:20736
```

---

@LAT103LON1605 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4504417 ±0 frame:7000
seq: 1674
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:203 0x00000200:521
said: 1 | **LINKWIN** t_ms:4547809 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:11 rssi_min:-38 rssi_med:-32 rssi_max:-30
said: 3 | **LINK** peer:0x00000200 proto:ble n:43 rssi_min:-80 rssi_med:-50 rssi_max:-45
said: 4 | 0x00000100 espnow unobserved predicted:-38 observed:-38
percept: 4 | 0x00000100 | link_stable | espnow | ? | -
said: 5 | 0x00000200 espnow met predicted:-28 observed:-32
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-45 observed:-50
percept: 6 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT104LON341 | created:0 | updated:0

**carried through @LAT103LON1565**

```ttdb-carried
through: 1565
through: 8272
through: 16437
through: 25952
carried: 926 16 1141 868 | 0x00000200 | link_stable | espnow
carried: 996 13 1365 881 | 0x00000200 | link_stable | ble
carried: 432 3 788 306 | 0x00000100 | link_stable | espnow
carried: 534 11 899 416 | 0x00000010 | link_stable | ble
carried: 524 18 895 414 | 0x00000010 | link_stable | espnow
carried: 91 0 91 97 | 0x00000011 | link_stable | ble
carried: 87 4 91 97 | 0x00000011 | link_stable | espnow
carried: 59 2 61 64 | 0x00000012 | link_stable | ble
carried: 57 2 59 61 | 0x00000012 | link_stable | espnow
```
