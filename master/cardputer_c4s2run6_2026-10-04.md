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

@LAT106LON35 | created:0 | updated:0

**BAR** frame:7000 bar:7 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:508 hi:517 sum:5125
**HOLDS** agent:0x00000300 n:10 lo:1646 hi:1664 sum:16550

---

@LAT103LON16461 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 4634495 ±214768 frame:7000
seq: 1676
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:203 0x00000200:521
said: 1 | **MOTIONWIN** t_ms:0 stream:0xb8263eac wall:0 window_ms:65451 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:5 dev_max_mg:5 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8320 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4694661 ±0 frame:7000
seq: 1679
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:203 0x00000200:525
said: 1 | **ENTWIN** t_ms:4739404 stream:0x3c4214c9 wall:0 window_ms:125617 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8321 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:26500
seq: 1688
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:203 0x00000200:531
said: 1 | **ENTWIN** t_ms:4994224 stream:0x3c4214c9 wall:0 window_ms:60000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON16462 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:26500
seq: 1689
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:203 0x00000200:531
said: 1 | **MOTIONWIN** t_ms:4994224 stream:0x3c4214c9 wall:0 window_ms:60000 n:595
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:6 dev_max_mg:9 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT106LON36 | created:0 | updated:0

**BAR** frame:7000 bar:8 own:8 held:10 terms:3 digest:0x76f44439 settled_ms:171940
**HOLDS** agent:0x00000200 n:10 lo:518 hi:528 sum:5229
**HOLDS** agent:0x00000300 n:8 lo:1666 hi:1681 sum:13384

---

@LAT106LON37 | created:0 | updated:0

**BAR** frame:7000 bar:9 own:9 held:10 terms:2 digest:0x8a894ac9 settled_ms:122075
**HOLDS** agent:0x00000200 n:10 lo:529 hi:538 sum:5335
**HOLDS** agent:0x00000300 n:9 lo:1683 hi:1703 sum:15247

---

@LAT103LON8322 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6123825 ±0 frame:7000
seq: 1729
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:214 0x00000200:551
said: 1 | **ENTWIN** t_ms:6167252 stream:0x3c4214c9 wall:0 window_ms:598767 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,5ce28c488e0c
said: 11 | **COVERED** windows:1 entities:8 window_ms:574261 first_t_ms:5568485 last_t_ms:5568485 covered_by:@LAT103LON8321
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94 windows:1
```
@LAT106LON38 | created:0 | updated:0

**BAR** frame:7000 bar:10 own:10 held:10 terms:3 digest:0xbfc8f19f settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:539 hi:549 sum:5440
**HOLDS** agent:0x00000300 n:10 lo:1705 hi:1723 sum:17140

---

@LAT103LON8323 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6723825 ±0 frame:7000
seq: 1750
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:226 0x00000200:562
said: 1 | **ENTWIN** t_ms:6767252 stream:0x3c4214c9 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c,84a329c78fec
```
@LAT106LON39 | created:0 | updated:0

**BAR** frame:7000 bar:11 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:550 hi:560 sum:5550
**HOLDS** agent:0x00000300 n:10 lo:1725 hi:1744 sum:17348

---

@LAT103LON16463 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 6759104 ±0 frame:7000
seq: 1752
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:227 0x00000200:563
said: 1 | **MOTIONWIN** t_ms:6802531 stream:0x3c4214c9 wall:0 window_ms:60000 n:755
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:6 dev_max_mg:10 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:20890 window_ms:1748307 moving_permille:1 dev_mean_mg:6 dev_max_mg:645 moving_ms:1979 first_t_ms:5054224 last_t_ms:6742531 covered_by:@LAT103LON16462
```

---

@LAT106LON40 | created:0 | updated:0

**BAR** frame:7000 bar:12 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:561 hi:570 sum:5655
**HOLDS** agent:0x00000300 n:10 lo:1746 hi:1766 sum:17565

---

@LAT106LON41 | created:0 | updated:0

**BAR** frame:7000 bar:13 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:571 hi:580 sum:5755
**HOLDS** agent:0x00000300 n:10 lo:1768 hi:1786 sum:17770

---

@LAT106LON42 | created:0 | updated:0

**BAR** frame:7000 bar:14 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:581 hi:591 sum:5860
**HOLDS** agent:0x00000300 n:10 lo:1788 hi:1806 sum:17970

---

@LAT103LON16464 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 8562628 ±0 frame:7000
seq: 1813
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:260 0x00000200:594
said: 1 | **MOTIONWIN** t_ms:8606055 stream:0x3c4214c9 wall:0 window_ms:60000 n:866
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:10 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28398 window_ms:1743524 moving_permille:0 dev_mean_mg:6 dev_max_mg:11 moving_ms:0 first_t_ms:6862531 last_t_ms:8546055 covered_by:@LAT103LON16463
```

---

@LAT106LON43 | created:0 | updated:0

**BAR** frame:7000 bar:15 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:592 hi:601 sum:5965
**HOLDS** agent:0x00000300 n:10 lo:1808 hi:1827 sum:18177

---

@LAT106LON44 | created:0 | updated:0

**BAR** frame:7000 bar:16 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:602 hi:611 sum:6065
**HOLDS** agent:0x00000300 n:10 lo:1829 hi:1847 sum:18380

---

@LAT103LON8324 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10323825 ±0 frame:7000
seq: 1873
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:291 0x00000200:623
said: 1 | **ENTWIN** t_ms:10367252 stream:0x3c4214c9 wall:0 window_ms:600000 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 13 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96
said: 14 | **RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,84a329c78fec,64677217947d,e6b32d2cea8b,5ce28c488e0c
said: 16 | **COVERED** windows:5 entities:11 window_ms:3000000 first_t_ms:7367253 last_t_ms:9767252 covered_by:@LAT103LON8323
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-33 windows:5
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-69 windows:5
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-72 windows:5
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-74 windows:5
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-84 windows:5
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:5 rssi:-85 windows:5
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:5 rssi:-87 windows:5
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:2 rssi:-91 windows:2
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-94 windows:2
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:4 rssi:-81 windows:4
said: 27 | **COVERED-ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93 windows:1
```
@LAT106LON45 | created:0 | updated:0

**BAR** frame:7000 bar:17 own:10 held:10 terms:3 digest:0xbfc8f19f settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:612 hi:621 sum:6165
**HOLDS** agent:0x00000300 n:10 lo:1849 hi:1867 sum:18580

---

@LAT103LON16465 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 10362628 ±0 frame:7000
seq: 1875
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:292 0x00000200:624
said: 1 | **MOTIONWIN** t_ms:10406055 stream:0x3c4214c9 wall:0 window_ms:60000 n:794
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28288 window_ms:1740000 moving_permille:0 dev_mean_mg:7 dev_max_mg:104 moving_ms:120 first_t_ms:8666055 last_t_ms:10346055 covered_by:@LAT103LON16464
```

---

@LAT103LON8325 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10923824 ±0 frame:7000
seq: 1895
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:301 0x00000200:634
said: 1 | **ENTWIN** t_ms:10967251 stream:0x3c4214c9 wall:0 window_ms:599999 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,84a329c78fec,64677217947d,e6b32d2cea8b,9418651af894,0283cce0e689,5ce28c488e0c
```

---

@LAT106LON46 | created:0 | updated:0

**BAR** frame:7000 bar:18 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:622 hi:632 sum:6270
**HOLDS** agent:0x00000300 n:10 lo:1869 hi:1889 sum:18795

---

@LAT106LON47 | created:0 | updated:0

**BAR** frame:7000 bar:19 own:10 held:7 terms:3 digest:0xa4eee16b settled_ms:140323
**HOLDS** agent:0x00000200 n:7 lo:633 hi:640 sum:4455
**HOLDS** agent:0x00000300 n:10 lo:1891 hi:1910 sum:19008

---

@LAT103LON8326 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11592104 ±21 frame:7000
seq: 1913
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:314 0x00000200:643
said: 1 | **ENTWIN** t_ms:11659743 stream:0x3c4214c9 wall:0 window_ms:62000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-94
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON16466 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 11592104 ±21 frame:7000
seq: 1914
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:314 0x00000200:643
said: 1 | **MOTIONWIN** t_ms:11659743 stream:0x3c4214c9 wall:0 window_ms:62000 n:860
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT106LON48 | created:0 | updated:0

**BAR** frame:7000 bar:20 own:7 held:9 terms:3 digest:0x27417f16 settled_ms:120000
**HOLDS** agent:0x00000200 n:9 lo:642 hi:650 sum:5814
**HOLDS** agent:0x00000300 n:7 lo:1912 hi:1926 sum:13438

---

@LAT103LON1728 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12138012 ±0 frame:7000
seq: 1932
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:322 0x00000200:652
said: 1 | **LINKWIN** t_ms:12205651 stream:0x3c4214c9 wall:0 window_ms:63011
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-40 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-58 rssi_max:-57
said: 5 | 0x00000200 ble met predicted:-62 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON1729 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12198012 ±0 frame:7000
seq: 1934
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:325 0x00000200:654
said: 1 | **LINKWIN** t_ms:12265651 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-65 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-41 rssi_med:-37 rssi_max:-36
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1730 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12258012 ±0 frame:7000
seq: 1936
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:325 0x00000200:654
said: 1 | **LINKWIN** t_ms:12325651 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-40 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-66 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 5 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON1731 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12318012 ±0 frame:7000
seq: 1938
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:327 0x00000200:657
said: 1 | **LINKWIN** t_ms:12385651 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-40 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-81 rssi_med:-58 rssi_max:-57
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1732 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12378012 ±0 frame:7000
seq: 1940
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:328 0x00000200:658
said: 1 | **LINKWIN** t_ms:12445651 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-58 rssi_max:-57
said: 5 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON591 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 12372596 ±21 frame:7000
seq: 658
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:328 0x00000300:1939
said: 1 | **LINKWIN** t_ms:12440222 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-39 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-44 rssi_med:-43 rssi_max:-42
said: 4 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON1733 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12438012 ±0 frame:7000
seq: 1942
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:329 0x00000200:659
said: 1 | **LINKWIN** t_ms:12505651 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:48 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-40 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-58 rssi_max:-57
said: 5 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1734 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12498012 ±0 frame:7000
seq: 1944
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:330 0x00000200:660
said: 1 | **LINKWIN** t_ms:12565651 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-41 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-58 rssi_max:-57
said: 5 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON592 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 12432596 ±21 frame:7000
seq: 659
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:329 0x00000300:1941
said: 1 | **LINKWIN** t_ms:12500222 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-48 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-82 rssi_med:-54 rssi_max:-53
```

---

@LAT105LON593 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 12492598 ±21 frame:7000
seq: 660
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:330 0x00000300:1943
said: 1 | **LINKWIN** t_ms:12560222 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-48 rssi_med:-43 rssi_max:-43
said: 3 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON1735 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12558012 ±0 frame:7000
seq: 1946
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:331 0x00000200:661
said: 1 | **LINKWIN** t_ms:12625651 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-40 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:espnow n:52 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON594 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 12552600 ±21 frame:7000
seq: 661
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:331 0x00000300:1945
said: 1 | **LINKWIN** t_ms:12620222 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-47 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON1736 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12618012 ±0 frame:7000
seq: 1948
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:332 0x00000200:661
said: 1 | **LINKWIN** t_ms:12685651 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-40 rssi_med:-37 rssi_max:-37
said: 4 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON595 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 12612600 ±21 frame:7000
seq: 662
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:332 0x00000300:1947
said: 1 | **LINKWIN** t_ms:12680222 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-39 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:56 rssi_min:-44 rssi_med:-43 rssi_max:-42
said: 4 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON1737 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12678013 ±0 frame:7000
seq: 1950
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:333 0x00000200:663
said: 1 | **LINKWIN** t_ms:12745652 stream:0x3c4214c9 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-38 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-63 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:espnow n:45 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 5 | 0x00000200 ble met predicted:-58 observed:-63
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON596 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 12672602 ±21 frame:7000
seq: 663
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:333 0x00000300:1949
said: 1 | **LINKWIN** t_ms:12740221 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:73 rssi_min:-82 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-39 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:espnow n:42 rssi_min:-48 rssi_med:-43 rssi_max:-43
```
@LAT106LON49 | created:0 | updated:0

**BAR** frame:7000 bar:21 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:651 hi:661 sum:6560
**HOLDS** agent:0x00000300 n:10 lo:1928 hi:1946 sum:19370

---

@LAT103LON1738 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12738013 ±0 frame:7000
seq: 1952
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:335 0x00000200:664
said: 1 | **LINKWIN** t_ms:12805652 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-40 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-65 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-63 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON8327 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12752919 ±0 frame:7000
seq: 1954
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:335 0x00000200:664
said: 1 | **ENTWIN** t_ms:12820558 stream:0x3c4214c9 wall:0 window_ms:604060 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b
said: 12 | **COVERED** windows:1 entities:9 window_ms:556755 first_t_ms:12216498 last_t_ms:12216498 covered_by:@LAT103LON8326
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-92 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e0c25086ede3 n:1 rssi:-94 windows:1
```

---

@LAT105LON597 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 12732602 ±21 frame:7000
seq: 664
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:334 0x00000300:1951
said: 1 | **LINKWIN** t_ms:12800222 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-79 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-39 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:espnow n:49 rssi_min:-48 rssi_med:-43 rssi_max:-42
```

---

@LAT103LON1739 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12798013 ±0 frame:7000
seq: 1955
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:337 0x00000200:664
said: 1 | **LINKWIN** t_ms:12865652 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-81 rssi_med:-58 rssi_max:-56
said: 4 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-38 rssi_med:-37 rssi_max:-37
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON598 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 12790600 ±21 frame:7000
seq: 665
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:337 0x00000300:1954
said: 1 | **LINKWIN** t_ms:12860222 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-39 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-49 rssi_med:-43 rssi_max:-42
```

---

@LAT103LON1740 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12859128 ±0 frame:7000
seq: 1957
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:338 0x00000200:666
said: 1 | **LINKWIN** t_ms:12926767 stream:0x3c4214c9 wall:0 window_ms:61115
said: 2 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:espnow n:43 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-58 rssi_max:-57
said: 5 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT105LON599 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 12816603 ±21 frame:7000
seq: 666
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:338 0x00000300:1956
said: 1 | **LINKWIN** t_ms:12920222 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-39 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:19 rssi_min:-48 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-54 rssi_max:-53
```

---

@LAT105LON600 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 12912542 ±21 frame:7000
seq: 667
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:339 0x00000300:1958
said: 1 | **LINKWIN** t_ms:12980222 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-47 rssi_med:-43 rssi_max:-43
```

---

@LAT103LON1741 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12921020 ±0 frame:7000
seq: 1959
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:339 0x00000200:667
said: 1 | **LINKWIN** t_ms:12988659 stream:0x3c4214c9 wall:0 window_ms:61892
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-40 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:espnow n:46 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-65 rssi_med:-58 rssi_max:-56
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1742 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 12981105 ±0 frame:7000
seq: 1961
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:340 0x00000200:667
said: 1 | **LINKWIN** t_ms:13048744 stream:0x3c4214c9 wall:0 window_ms:60085
said: 2 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-41 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-65 rssi_med:-58 rssi_max:-56
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1743 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13041105 ±0 frame:7000
seq: 1963
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:341 0x00000200:669
said: 1 | **LINKWIN** t_ms:13108744 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-66 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON601 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 12972605 ±21 frame:7000
seq: 668
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:340 0x00000300:1960
said: 1 | **LINKWIN** t_ms:13040222 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:55 rssi_min:-48 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-80 rssi_med:-54 rssi_max:-53
```

---

@LAT105LON602 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13032646 ±21 frame:7000
seq: 669
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:341 0x00000300:1962
said: 1 | **LINKWIN** t_ms:13100263 stream:0x3c4214c9 wall:0 window_ms:60041
said: 2 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-38 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-47 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON1744 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13101105 ±0 frame:7000
seq: 1965
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:342 0x00000200:670
said: 1 | **LINKWIN** t_ms:13168744 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-38 rssi_med:-37 rssi_max:-37
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON603 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13092649 ±21 frame:7000
seq: 670
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:342 0x00000300:1964
said: 1 | **LINKWIN** t_ms:13160263 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:62 rssi_min:-44 rssi_med:-43 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-39 rssi_med:-34 rssi_max:-34
```

---

@LAT103LON1745 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13161105 ±0 frame:7000
seq: 1967
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:343 0x00000200:671
said: 1 | **LINKWIN** t_ms:13228744 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-41 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-79 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:espnow n:39 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 5 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT105LON604 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13152651 ±21 frame:7000
seq: 671
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:343 0x00000300:1966
said: 1 | **LINKWIN** t_ms:13220263 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-82 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-44 rssi_med:-43 rssi_max:-43
```

---

@LAT105LON605 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13212649 ±21 frame:7000
seq: 672
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:344 0x00000300:1968
said: 1 | **LINKWIN** t_ms:13280263 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:32 rssi_min:-44 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON1746 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13221105 ±0 frame:7000
seq: 1969
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:344 0x00000200:672
said: 1 | **LINKWIN** t_ms:13288744 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-40 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:espnow n:43 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON1747 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13281105 ±0 frame:7000
seq: 1971
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:345 0x00000200:673
said: 1 | **LINKWIN** t_ms:13348744 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-65 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:33 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-41 rssi_med:-37 rssi_max:-36
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON606 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13272651 ±21 frame:7000
seq: 673
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:345 0x00000300:1970
said: 1 | **LINKWIN** t_ms:13340263 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-48 rssi_med:-43 rssi_max:-43
```
@LAT106LON50 | created:0 | updated:0

**BAR** frame:7000 bar:22 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:121260
**HOLDS** agent:0x00000200 n:10 lo:662 hi:671 sum:6665
**HOLDS** agent:0x00000300 n:10 lo:1948 hi:1967 sum:19577

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:919 last_ms:1811676
t_ms:13409419 stream:0x3c4214c9 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:473 last_ms:1811676
t_ms:13409419 stream:0x3c4214c9 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:13409419 stream:0x3c4214c9 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:13409419 stream:0x3c4214c9 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:13409419 stream:0x3c4214c9 wall:0

---

@LAT101LON5 | sid:499db878 | created:0 | updated:0 |
**PEER** node:0x00000001 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:13409419 stream:0x3c4214c9 wall:0

---

@LAT103LON1748 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13341780 ±0 frame:7000
seq: 1973
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:346 0x00000200:673
said: 1 | **LINKWIN** t_ms:13409419 stream:0x3c4214c9 wall:0 window_ms:60675
said: 2 | **LINK** peer:0x00000200 proto:ble n:80 rssi_min:-81 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-48 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-41 rssi_med:-37 rssi_max:-36
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON26115 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 13341780 ±0 frame:7000
seq: 1974
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:346 0x00000200:673
said: 1 | **ACOUSTICWIN** t_ms:13409419 stream:0x3c4214c9 wall:0 window_ms:60675 blocks:2141 rate:8000
said: 2 | **ACOUSTIC** rms_mean:127 rms_max:214 peak:610 transients:0
```

---

@LAT103LON8328 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13366950 ±0 frame:7000
seq: 1975
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:347 0x00000200:674
said: 1 | **ENTWIN** t_ms:13434589 stream:0x3c4214c9 wall:0 window_ms:614031 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-93
said: 13 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-93
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 15 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,64677217947d,0283cce0e689,980d67f79619,02c57d2f9717
```

---

@LAT103LON1749 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13409070 ±0 frame:7000
seq: 1976
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:348 0x00000200:674
said: 1 | **LINKWIN** t_ms:13476709 stream:0x3c4214c9 wall:0 window_ms:67290
said: 2 | **LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:49 rssi_min:-65 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-48 rssi_med:-48 rssi_max:-46
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON16467 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 13409070 ±0 frame:7000
seq: 1977
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:348 0x00000200:674
said: 1 | **MOTIONWIN** t_ms:13476709 stream:0x3c4214c9 wall:0 window_ms:67290 n:2
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:9 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:15039 window_ms:1749676 moving_permille:0 dev_mean_mg:8 dev_max_mg:15 moving_ms:0 first_t_ms:11719743 last_t_ms:13409419 covered_by:@LAT103LON16466
```

---

@LAT103LON26116 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 13409070 ±0 frame:7000
seq: 1978
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:348 0x00000200:674
said: 1 | **ACOUSTICWIN** t_ms:13476709 stream:0x3c4214c9 wall:0 window_ms:67290 blocks:4 rate:8000
said: 2 | **ACOUSTIC** rms_mean:137 rms_max:173 peak:470 transients:0
```

---

@LAT105LON607 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13333204 ±21 frame:7000
seq: 674
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:346 0x00000300:1972
said: 1 | **LINKWIN** t_ms:13400809 stream:0x3c4214c9 wall:0 window_ms:60551
said: 2 | **LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-44 rssi_med:-43 rssi_max:-43
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-39 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-54 rssi_max:-53
```

---

@LAT105LON608 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13393204 ±24 frame:7000
seq: 675
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:348 0x00000300:1972
said: 1 | **LINKWIN** t_ms:13460814 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-38 rssi_med:-34 rssi_max:-34
```

---

@LAT103LON1750 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13469070 ±0 frame:7000
seq: 1979
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:349 0x00000200:676
said: 1 | **LINKWIN** t_ms:13536709 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-80 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:47 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-40 rssi_med:-37 rssi_max:-36
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON26117 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 13469070 ±0 frame:7000
seq: 1980
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:349 0x00000200:676
said: 1 | **ACOUSTICWIN** t_ms:13536709 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:2945 rate:8000
said: 2 | **ACOUSTIC** rms_mean:120 rms_max:221 peak:605 transients:0
```

---

@LAT105LON609 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13453206 ±21 frame:7000
seq: 676
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:349 0x00000300:1978
said: 1 | **LINKWIN** t_ms:13520814 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-35 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000300 proto:espnow n:53 rssi_min:-48 rssi_med:-43 rssi_max:-43
```

---

@LAT105LON610 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13513204 ±21 frame:7000
seq: 678
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:350 0x00000300:1980
said: 1 | **LINKWIN** t_ms:13580813 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-39 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:56 rssi_min:-49 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON1751 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13529070 ±0 frame:7000
seq: 1981
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:350 0x00000200:678
said: 1 | **LINKWIN** t_ms:13596709 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:47 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-41 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-58 rssi_max:-57
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON26118 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 13529070 ±0 frame:7000
seq: 1982
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:350 0x00000200:678
said: 1 | **ACOUSTICWIN** t_ms:13596709 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3102 rate:8000
said: 2 | **ACOUSTIC** rms_mean:122 rms_max:397 peak:823 transients:0
```

---

@LAT103LON1752 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13589070 ±0 frame:7000
seq: 1983
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:351 0x00000200:679
said: 1 | **LINKWIN** t_ms:13656709 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-40 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-58 rssi_max:-56
said: 4 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 5 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON26119 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 13589070 ±0 frame:7000
seq: 1984
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:351 0x00000200:679
said: 1 | **ACOUSTICWIN** t_ms:13656709 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:984 rate:8000
said: 2 | **ACOUSTIC** rms_mean:148 rms_max:697 peak:2294 transients:0
```

---

@LAT105LON611 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13573206 ±22 frame:7000
seq: 679
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:351 0x00000300:1982
said: 1 | **LINKWIN** t_ms:13640814 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:36 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 4 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-79 rssi_med:-54 rssi_max:-53
```

---

@LAT105LON612 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13633209 ±21 frame:7000
seq: 680
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:352 0x00000300:1984
said: 1 | **LINKWIN** t_ms:13700814 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:71 rssi_min:-39 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-53 rssi_max:-50
said: 4 | **LINK** peer:0x00000300 proto:espnow n:48 rssi_min:-48 rssi_med:-43 rssi_max:-36
```

---

@LAT103LON1753 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13649070 ±0 frame:7000
seq: 1985
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:352 0x00000200:680
said: 1 | **LINKWIN** t_ms:13716709 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-58 rssi_max:-55
said: 3 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-42 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:espnow n:53 rssi_min:-49 rssi_med:-47 rssi_max:-42
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-47
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON26120 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 13649070 ±0 frame:7000
seq: 1986
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:352 0x00000200:680
said: 1 | **ACOUSTICWIN** t_ms:13716709 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3101 rate:8000
said: 2 | **ACOUSTIC** rms_mean:186 rms_max:689 peak:1371 transients:0
```

---

@LAT103LON1754 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13711066 ±0 frame:7000
seq: 1987
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:353 0x00000200:681
said: 1 | **LINKWIN** t_ms:13778705 stream:0x3c4214c9 wall:0 window_ms:61996
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-58 rssi_max:-56
said: 3 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-39 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:espnow n:47 rssi_min:-49 rssi_med:-48 rssi_max:-45
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-47 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON26121 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 13711066 ±0 frame:7000
seq: 1988
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:353 0x00000200:681
said: 1 | **ACOUSTICWIN** t_ms:13778705 stream:0x3c4214c9 wall:0 window_ms:61996 blocks:2241 rate:8000
said: 2 | **ACOUSTIC** rms_mean:197 rms_max:4601 peak:15272 transients:5
said: 3 | **TRANSIENT** t_ms:13764180 stream:0x3c4214c9 wall:0 rms:4601
```

---

@LAT105LON613 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13693210 ±22 frame:7000
seq: 681
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:353 0x00000300:1986
said: 1 | **LINKWIN** t_ms:13760814 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-47 rssi_med:-43 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:ble n:71 rssi_min:-81 rssi_med:-53 rssi_max:-53
```

---

@LAT103LON1755 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13773092 ±0 frame:7000
seq: 1989
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:354 0x00000200:681
said: 1 | **LINKWIN** t_ms:13840731 stream:0x3c4214c9 wall:0 window_ms:62026
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-65 rssi_med:-58 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-49 rssi_med:-48 rssi_max:-45
said: 4 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-41 rssi_med:-37 rssi_max:-37
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON26122 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 13773092 ±0 frame:7000
seq: 1990
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:354 0x00000200:681
said: 1 | **ACOUSTICWIN** t_ms:13840731 stream:0x3c4214c9 wall:0 window_ms:62026 blocks:52 rate:8000
said: 2 | **ACOUSTIC** rms_mean:181 rms_max:411 peak:801 transients:0
```

---

@LAT105LON614 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13751209 ±22 frame:7000
seq: 682
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:354 0x00000300:1988
said: 1 | **LINKWIN** t_ms:13820813 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-39 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 4 | **LINK** peer:0x00000300 proto:espnow n:20 rssi_min:-44 rssi_med:-43 rssi_max:-42
```

---

@LAT103LON1756 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13837032 ±0 frame:7000
seq: 1991
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:355 0x00000200:683
said: 1 | **LINKWIN** t_ms:13904671 stream:0x3c4214c9 wall:0 window_ms:63940
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-66 rssi_med:-58 rssi_max:-55
said: 3 | **LINK** peer:0x00000100 proto:espnow n:74 rssi_min:-41 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON26123 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 13837032 ±0 frame:7000
seq: 1992
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:355 0x00000200:683
said: 1 | **ACOUSTICWIN** t_ms:13904671 stream:0x3c4214c9 wall:0 window_ms:63940 blocks:323 rate:8000
said: 2 | **ACOUSTIC** rms_mean:196 rms_max:1209 peak:2094 transients:2
said: 3 | **TRANSIENT** t_ms:13849297 stream:0x3c4214c9 wall:0 rms:1209
```

---

@LAT105LON615 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13813212 ±21 frame:7000
seq: 683
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:355 0x00000300:1990
said: 1 | **LINKWIN** t_ms:13880813 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-82 rssi_med:-53 rssi_max:-50
said: 3 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-39 rssi_med:-35 rssi_max:-33
said: 4 | **LINK** peer:0x00000300 proto:espnow n:51 rssi_min:-48 rssi_med:-43 rssi_max:-40
```

---

@LAT105LON616 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13873215 ±21 frame:7000
seq: 684
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:356 0x00000300:1992
said: 1 | **LINKWIN** t_ms:13940824 stream:0x3c4214c9 wall:0 window_ms:60013
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-39 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-82 rssi_med:-54 rssi_max:-52
said: 4 | **LINK** peer:0x00000300 proto:espnow n:59 rssi_min:-48 rssi_med:-43 rssi_max:-43
```

---

@LAT103LON1757 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13897141 ±0 frame:7000
seq: 1993
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:356 0x00000200:684
said: 1 | **LINKWIN** t_ms:13964780 stream:0x3c4214c9 wall:0 window_ms:60109
said: 2 | **LINK** peer:0x00000200 proto:espnow n:50 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-43 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-58 rssi_max:-53
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON26124 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 13897141 ±0 frame:7000
seq: 1994
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:356 0x00000200:684
said: 1 | **ACOUSTICWIN** t_ms:13964780 stream:0x3c4214c9 wall:0 window_ms:60109 blocks:371 rate:8000
said: 2 | **ACOUSTIC** rms_mean:122 rms_max:570 peak:1256 transients:0
```
@LAT106LON51 | created:0 | updated:0

**BAR** frame:7000 bar:23 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:142058
**HOLDS** agent:0x00000200 n:10 lo:672 hi:682 sum:6770
**HOLDS** agent:0x00000300 n:10 lo:1969 hi:1989 sum:19793

---

@LAT103LON1758 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 13957205 ±0 frame:7000
seq: 1995
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:357 0x00000200:685
said: 1 | **LINKWIN** t_ms:14024844 stream:0x3c4214c9 wall:0 window_ms:60064
said: 2 | **LINK** peer:0x00000200 proto:ble n:50 rssi_min:-66 rssi_med:-58 rssi_max:-54
said: 3 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-48 rssi_med:-48 rssi_max:-43
said: 4 | **LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-42 rssi_med:-37 rssi_max:-35
said: 5 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 5 | 0x00000200 | link_stable | espnow | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON26125 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 13957205 ±0 frame:7000
seq: 1996
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:357 0x00000200:685
said: 1 | **ACOUSTICWIN** t_ms:14024844 stream:0x3c4214c9 wall:0 window_ms:60064 blocks:100 rate:8000
said: 2 | **ACOUSTIC** rms_mean:138 rms_max:410 peak:1045 transients:0
```

---

@LAT103LON8329 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13972328 ±0 frame:7000
seq: 1997
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:357 0x00000200:685
said: 1 | **ENTWIN** t_ms:14039967 stream:0x3c4214c9 wall:0 window_ms:605378 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,e6b32d2cea8b,02c57d2e0f0d,64677217947d,7236bc441422,0283cce0e689,02c57d2f9717,980d67f79619
```

---

@LAT105LON617 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13933227 ±22 frame:7000
seq: 685
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:357 0x00000300:1994
said: 1 | **LINKWIN** t_ms:14000827 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:espnow n:33 rssi_min:-44 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-56 rssi_max:-50
```

---

@LAT103LON1759 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14017205 ±0 frame:7000
seq: 1998
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:358 0x00000200:686
said: 1 | **LINKWIN** t_ms:14084844 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-80 rssi_med:-58 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:espnow n:36 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-41 rssi_med:-37 rssi_max:-37
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON26126 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 14017205 ±0 frame:7000
seq: 1999
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:358 0x00000200:686
said: 1 | **ACOUSTICWIN** t_ms:14084844 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:2836 rate:8000
said: 2 | **ACOUSTIC** rms_mean:86 rms_max:490 peak:992 transients:0
```

---

@LAT105LON618 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 13993228 ±21 frame:7000
seq: 686
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:358 0x00000300:1997
said: 1 | **LINKWIN** t_ms:14060827 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-41 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-82 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000300 proto:espnow n:52 rssi_min:-47 rssi_med:-43 rssi_max:-43
```

---

@LAT103LON1760 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14077205 ±0 frame:7000
seq: 2000
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:359 0x00000200:687
said: 1 | **LINKWIN** t_ms:14144844 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-66 rssi_med:-58 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-40 rssi_med:-37 rssi_max:-37
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON26127 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 14077205 ±0 frame:7000
seq: 2001
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:359 0x00000200:687
said: 1 | **ACOUSTICWIN** t_ms:14144844 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3109 rate:8000
said: 2 | **ACOUSTIC** rms_mean:90 rms_max:1077 peak:1666 transients:1
said: 3 | **TRANSIENT** t_ms:14139415 stream:0x3c4214c9 wall:0 rms:955
```

---

@LAT105LON619 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 14053229 ±21 frame:7000
seq: 687
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:359 0x00000300:1999
said: 1 | **LINKWIN** t_ms:14120827 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-48 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON1761 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14137205 ±0 frame:7000
seq: 2002
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:360 0x00000200:688
said: 1 | **LINKWIN** t_ms:14204844 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-41 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:espnow n:37 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-58 rssi_max:-56
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 7 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON26128 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 14137205 ±0 frame:7000
seq: 2003
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:360 0x00000200:688
said: 1 | **ACOUSTICWIN** t_ms:14204844 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:979 rate:8000
said: 2 | **ACOUSTIC** rms_mean:92 rms_max:162 peak:400 transients:0
```

---

@LAT105LON620 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 14113230 ±22 frame:7000
seq: 688
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:360 0x00000300:2001
said: 1 | **LINKWIN** t_ms:14180827 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-47 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON1762 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14197205 ±0 frame:7000
seq: 2004
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:361 0x00000200:689
said: 1 | **LINKWIN** t_ms:14264844 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-41 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:espnow n:48 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-58 rssi_max:-56
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON26129 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 14197205 ±0 frame:7000
seq: 2005
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:361 0x00000200:689
said: 1 | **ACOUSTICWIN** t_ms:14264844 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3099 rate:8000
said: 2 | **ACOUSTIC** rms_mean:93 rms_max:664 peak:1575 transients:0
```

---

@LAT105LON621 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 14173231 ±21 frame:7000
seq: 689
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:361 0x00000300:2003
said: 1 | **LINKWIN** t_ms:14240826 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-47 rssi_med:-44 rssi_max:-43
```

---

@LAT105LON622 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 14233232 ±22 frame:7000
seq: 690
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:362 0x00000300:2005
said: 1 | **LINKWIN** t_ms:14300827 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:70 rssi_min:-44 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-54 rssi_max:-53
```

---

@LAT103LON1763 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14257205 ±0 frame:7000
seq: 2006
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:362 0x00000200:690
said: 1 | **LINKWIN** t_ms:14324844 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-41 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-66 rssi_med:-58 rssi_max:-57
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON26130 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 14257205 ±0 frame:7000
seq: 2007
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:362 0x00000200:690
said: 1 | **ACOUSTICWIN** t_ms:14324844 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:2922 rate:8000
said: 2 | **ACOUSTIC** rms_mean:85 rms_max:228 peak:455 transients:0
```

---

@LAT103LON1764 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14317205 ±0 frame:7000
seq: 2008
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:363 0x00000200:691
said: 1 | **LINKWIN** t_ms:14384844 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-41 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:espnow n:47 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-58 observed:-58
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON26131 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 14317205 ±0 frame:7000
seq: 2009
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:363 0x00000200:691
said: 1 | **ACOUSTICWIN** t_ms:14384844 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:804 rate:8000
said: 2 | **ACOUSTIC** rms_mean:81 rms_max:166 peak:481 transients:0
```

---

@LAT105LON623 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 14284274 ±22 frame:7000
seq: 691
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:363 0x00000300:2007
said: 1 | **LINKWIN** t_ms:14360827 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:22 rssi_min:-44 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-38 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-54 rssi_max:-53
```

---

@LAT105LON624 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 14353232 ±21 frame:7000
seq: 692
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:364 0x00000300:2009
said: 1 | **LINKWIN** t_ms:14420827 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-59 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000300 proto:espnow n:50 rssi_min:-47 rssi_med:-44 rssi_max:-43
```

---

@LAT103LON1765 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14377205 ±0 frame:7000
seq: 2010
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:364 0x00000200:692
said: 1 | **LINKWIN** t_ms:14444844 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-41 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON26132 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 14377205 ±0 frame:7000
seq: 2011
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:364 0x00000200:692
said: 1 | **ACOUSTICWIN** t_ms:14444844 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3105 rate:8000
said: 2 | **ACOUSTIC** rms_mean:79 rms_max:282 peak:522 transients:0
```

---

@LAT105LON625 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 14413236 ±21 frame:7000
seq: 693
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:365 0x00000300:2011
said: 1 | **LINKWIN** t_ms:14480827 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-35 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-48 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-54 rssi_max:-52
```

---

@LAT103LON1766 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14437205 ±0 frame:7000
seq: 2012
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:365 0x00000200:693
said: 1 | **LINKWIN** t_ms:14504844 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-41 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-66 rssi_med:-58 rssi_max:-56
said: 4 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON26133 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 14437205 ±0 frame:7000
seq: 2013
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:365 0x00000200:693
said: 1 | **ACOUSTICWIN** t_ms:14504844 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3097 rate:8000
said: 2 | **ACOUSTIC** rms_mean:84 rms_max:386 peak:814 transients:0
```

---

@LAT103LON1767 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14497205 ±0 frame:7000
seq: 2014
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:366 0x00000200:694
said: 1 | **LINKWIN** t_ms:14564844 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-58 rssi_max:-56
said: 3 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-38 rssi_med:-37 rssi_max:-37
said: 4 | **LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON26134 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 14497205 ±0 frame:7000
seq: 2015
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:366 0x00000200:694
said: 1 | **ACOUSTICWIN** t_ms:14564844 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:990 rate:8000
said: 2 | **ACOUSTIC** rms_mean:99 rms_max:925 peak:1631 transients:0
```

---

@LAT105LON626 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 14473236 ±22 frame:7000
seq: 694
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:366 0x00000300:2013
said: 1 | **LINKWIN** t_ms:14540827 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-39 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:37 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-54 rssi_max:-53
```
@LAT106LON52 | created:0 | updated:0

**BAR** frame:7000 bar:24 own:10 held:10 terms:3 digest:0xd25ff5d5 settled_ms:120000
**HOLDS** agent:0x00000200 n:10 lo:683 hi:692 sum:6875
**HOLDS** agent:0x00000300 n:10 lo:1991 hi:2010 sum:20007

---

@LAT105LON627 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 14533237 ±21 frame:7000
seq: 695
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:367 0x00000300:2015
said: 1 | **LINKWIN** t_ms:14600826 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-80 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-48 rssi_med:-44 rssi_max:-43
```

---

@LAT103LON1768 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14557205 ±0 frame:7000
seq: 2016
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:368 0x00000200:695
said: 1 | **LINKWIN** t_ms:14624844 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-41 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-58 rssi_max:-55
said: 4 | **LINK** peer:0x00000200 proto:espnow n:47 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 5 | 0x00000200 ble met predicted:-58 observed:-58
percept: 5 | 0x00000200 | link_stable | ble | + | -
said: 6 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 6 | 0x00000100 | link_stable | espnow | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON26135 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 14557205 ±0 frame:7000
seq: 2017
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:368 0x00000200:695
said: 1 | **ACOUSTICWIN** t_ms:14624844 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:2299 rate:8000
said: 2 | **ACOUSTIC** rms_mean:90 rms_max:853 peak:1424 transients:0
```

---

@LAT103LON8330 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 14572332 ±0 frame:7000
seq: 2018
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:368 0x00000200:695
said: 1 | **ENTWIN** t_ms:14639971 stream:0x3c4214c9 wall:0 window_ms:600004 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,e6b32d2cea8b,02c57d2e0f0d,7236bc441422,02c57d2f9719,64677217947d,0283cce0e689,02c57d2f9717,980d67f79619
```

---

@LAT104LON380 | created:0 | updated:0

**carried through @LAT103LON1727**

```ttdb-carried
through: 1727
through: 8290
through: 16446
through: 26114
carried: 1084 17 1300 1027 | 0x00000200 | link_stable | espnow
carried: 1155 13 1524 1040 | 0x00000200 | link_stable | ble
carried: 576 6 935 454 | 0x00000100 | link_stable | espnow
carried: 534 11 899 416 | 0x00000010 | link_stable | ble
carried: 524 18 895 414 | 0x00000010 | link_stable | espnow
carried: 91 0 91 97 | 0x00000011 | link_stable | ble
carried: 87 4 91 97 | 0x00000011 | link_stable | espnow
carried: 59 2 61 64 | 0x00000012 | link_stable | ble
carried: 57 2 59 61 | 0x00000012 | link_stable | espnow
```

---

@LAT105LON628 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 14593239 ±21 frame:7000
seq: 696
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:370 0x00000300:2018
said: 1 | **LINKWIN** t_ms:14660878 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000300 proto:espnow n:46 rssi_min:-44 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON1769 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 14617205 ±0 frame:7000
seq: 2019
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:370 0x00000200:696
said: 1 | **LINKWIN** t_ms:14684844 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:42 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-66 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-38 rssi_med:-37 rssi_max:-37
said: 5 | 0x00000100 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 ble met predicted:-58 observed:-58
percept: 6 | 0x00000200 | link_stable | ble | + | -
said: 7 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 7 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON26136 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 14617205 ±0 frame:7000
seq: 2020
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:370 0x00000200:696
said: 1 | **ACOUSTICWIN** t_ms:14684844 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:2657 rate:8000
said: 2 | **ACOUSTIC** rms_mean:80 rms_max:187 peak:409 transients:0
```
