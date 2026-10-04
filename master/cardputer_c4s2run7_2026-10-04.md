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

@LAT103LON16468 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 71691
seq: 2022
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:370 0x00000200:696
said: 1 | **MOTIONWIN** t_ms:14767135 stream:0x3c4214c9 wall:0 window_ms:71691 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:9 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8331 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 119924 ±0 frame:72000
seq: 2024
follows: 0x00000010:86 0x00000011:48 0x00000012:5 0x00000100:371 0x00000200:697
said: 1 | **ENTWIN** t_ms:14814705 stream:0x3c4214c9 wall:0 window_ms:119924 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-80
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95
said: 12 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-95
said: 13 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 14 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 15 | **CORE** entities:0
```

---

@LAT103LON8332 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 15942100 ±0 frame:7000
seq: 2065
follows: 0x00000010:89 0x00000011:48 0x00000012:5 0x00000100:390 0x00000200:719
said: 1 | **ENTWIN** t_ms:16013312 stream:0x3c4214c9 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,5203cfd1b904,0283cce0e689,980d67f79619
said: 14 | **COVERED** windows:1 entities:10 window_ms:598607 first_t_ms:15413312 last_t_ms:15413312 covered_by:@LAT103LON8331
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-83 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96 windows:1
```

---

@LAT103LON16469 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 16531268 ±0 frame:7000
seq: 2085
follows: 0x00000010:97 0x00000011:48 0x00000012:5 0x00000100:390 0x00000200:730
said: 1 | **MOTIONWIN** t_ms:16602480 stream:0x3c4214c9 wall:0 window_ms:60000 n:943
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:25611 window_ms:1776008 moving_permille:1 dev_mean_mg:9 dev_max_mg:406 moving_ms:2920 first_t_ms:14834679 last_t_ms:16542480 covered_by:@LAT103LON16468
```

---

@LAT103LON8333 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 16542099 ±0 frame:7000
seq: 2087
follows: 0x00000010:97 0x00000011:48 0x00000012:5 0x00000100:390 0x00000200:730
said: 1 | **ENTWIN** t_ms:16613311 stream:0x3c4214c9 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,84a329c78fec,64677217947d,5ce28c488e0c,0283cce0e689,980d67f79619
```

---

@LAT106LON57 | created:0 | updated:0

**BAR** frame:7000 bar:29 own:10 held:20 terms:4 digest:0x53bf6f20 settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:103 hi:112 sum:1075
**HOLDS** agent:0x00000200 n:10 lo:735 hi:745 sum:7402
**HOLDS** agent:0x00000300 n:10 lo:2096 hi:2114 sum:21050

---

@LAT106LON58 | created:0 | updated:0

**BAR** frame:7000 bar:30 own:10 held:23 terms:6 digest:0x6ec5a451 settled_ms:120001
**HOLDS** agent:0x00000010 n:10 lo:113 hi:123 sum:1181
**HOLDS** agent:0x00000011 n:3 lo:49 hi:52 sum:152
**HOLDS** agent:0x00000200 n:10 lo:746 hi:756 sum:7512
**HOLDS** agent:0x00000300 n:10 lo:2116 hi:2134 sum:21250

---

@LAT103LON16470 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 18331268 ±0 frame:7000
seq: 2147
follows: 0x00000010:129 0x00000011:59 0x00000012:5 0x00000100:390 0x00000200:761
said: 1 | **MOTIONWIN** t_ms:18402480 stream:0x3c4214c9 wall:0 window_ms:60000 n:941
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27291 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:23 moving_ms:0 first_t_ms:16662480 last_t_ms:18342480 covered_by:@LAT103LON16469
```

---

@LAT103LON8334 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 18343396 ±0 frame:7000
seq: 2149
follows: 0x00000010:129 0x00000011:59 0x00000012:5 0x00000100:390 0x00000200:761
said: 1 | **ENTWIN** t_ms:18414608 stream:0x3c4214c9 wall:0 window_ms:601296 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:9 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,84a329c78fec,0283cce0e689,64677217947d,5ce28c488e0c
said: 11 | **COVERED** windows:2 entities:10 window_ms:1200001 first_t_ms:17213312 last_t_ms:17813312 covered_by:@LAT103LON8333
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-34 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-71 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-73 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-73 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-84 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-85 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-90 windows:2
```

---

@LAT106LON59 | created:0 | updated:0

**BAR** frame:7000 bar:31 own:10 held:29 terms:6 digest:0x374c50f3 settled_ms:120000
**HOLDS** agent:0x00000010 n:9 lo:125 hi:134 sum:1167
**HOLDS** agent:0x00000011 n:10 lo:55 hi:64 sum:595
**HOLDS** agent:0x00000200 n:10 lo:757 hi:766 sum:7615
**HOLDS** agent:0x00000300 n:10 lo:2136 hi:2156 sum:21458

---

@LAT106LON60 | created:0 | updated:0

**BAR** frame:7000 bar:32 own:10 held:30 terms:6 digest:0x374c50f3 settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:135 hi:144 sum:1395
**HOLDS** agent:0x00000011 n:10 lo:65 hi:75 sum:700
**HOLDS** agent:0x00000200 n:10 lo:767 hi:777 sum:7723
**HOLDS** agent:0x00000300 n:10 lo:2158 hi:2176 sum:21670

---

@LAT103LON8335 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 19543394 ±0 frame:7000
seq: 2190
follows: 0x00000010:150 0x00000011:81 0x00000012:5 0x00000100:390 0x00000200:783
said: 1 | **ENTWIN** t_ms:19614606 stream:0x3c4214c9 wall:0 window_ms:599999 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 13 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:8 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,84a329c78fec,64677217947d,0283cce0e689
said: 15 | **COVERED** windows:1 entities:10 window_ms:599999 first_t_ms:19014607 last_t_ms:19014607 covered_by:@LAT103LON8334
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
```

---

@LAT106LON61 | created:0 | updated:0

**BAR** frame:7000 bar:33 own:10 held:30 terms:6 digest:0x374c50f3 settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:145 hi:155 sum:1501
**HOLDS** agent:0x00000011 n:10 lo:76 hi:86 sum:810
**HOLDS** agent:0x00000200 n:10 lo:778 hi:788 sum:7833
**HOLDS** agent:0x00000300 n:10 lo:2178 hi:2197 sum:21874

---

@LAT103LON16471 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 20133812 ±0 frame:7000
seq: 2210
follows: 0x00000010:160 0x00000011:91 0x00000012:6 0x00000100:390 0x00000200:794
said: 1 | **MOTIONWIN** t_ms:20205024 stream:0x3c4214c9 wall:0 window_ms:60000 n:991
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:27 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27464 window_ms:1742544 moving_permille:0 dev_mean_mg:9 dev_max_mg:31 moving_ms:0 first_t_ms:18462480 last_t_ms:20145024 covered_by:@LAT103LON16470
```

---

@LAT103LON8336 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 20143394 ±0 frame:7000
seq: 2212
follows: 0x00000010:160 0x00000011:91 0x00000012:6 0x00000100:390 0x00000200:794
said: 1 | **ENTWIN** t_ms:20214606 stream:0x3c4214c9 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,84a329c78fec,e6b32d2cea8b,0283cce0e689
```

---

@LAT106LON62 | created:0 | updated:0

**BAR** frame:7000 bar:34 own:10 held:34 terms:8 digest:0x1022a2b2 settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:156 hi:165 sum:1605
**HOLDS** agent:0x00000011 n:10 lo:87 hi:96 sum:915
**HOLDS** agent:0x00000012 n:4 lo:7 hi:11 sum:37
**HOLDS** agent:0x00000200 n:10 lo:789 hi:799 sum:7943
**HOLDS** agent:0x00000300 n:10 lo:2199 hi:2219 sum:22088

---

@LAT103LON8337 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 20743394 ±0 frame:7000
seq: 2233
follows: 0x00000010:171 0x00000011:101 0x00000012:17 0x00000100:390 0x00000200:804
said: 1 | **ENTWIN** t_ms:20814606 stream:0x3c4214c9 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:22ad5628d593 n:1 rssi:-92
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,84a329c78fec,64677217947d,5ce28c488e0c,0283cce0e689
```

---

@LAT106LON63 | created:0 | updated:0

**BAR** frame:7000 bar:35 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:166 hi:176 sum:1711
**HOLDS** agent:0x00000011 n:10 lo:97 hi:106 sum:1015
**HOLDS** agent:0x00000012 n:10 lo:12 hi:21 sum:165
**HOLDS** agent:0x00000200 n:10 lo:800 hi:809 sum:8045
**HOLDS** agent:0x00000300 n:10 lo:2221 hi:2240 sum:22304

---

@LAT106LON64 | created:0 | updated:0

**BAR** frame:7000 bar:36 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:177 hi:186 sum:1815
**HOLDS** agent:0x00000011 n:10 lo:107 hi:117 sum:1120
**HOLDS** agent:0x00000012 n:10 lo:22 hi:32 sum:269
**HOLDS** agent:0x00000200 n:10 lo:810 hi:819 sum:8145
**HOLDS** agent:0x00000300 n:10 lo:2242 hi:2260 sum:22510

---

@LAT103LON16472 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 21933838 ±0 frame:7000
seq: 2273
follows: 0x00000010:192 0x00000011:122 0x00000012:38 0x00000100:390 0x00000200:824
said: 1 | **MOTIONWIN** t_ms:22005050 stream:0x3c4214c9 wall:0 window_ms:60000 n:870
said: 2 | **MOTION** state:still moving_permille:83 dev_mean_mg:25 dev_max_mg:567 moving_ms:4431
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27168 window_ms:1740026 moving_permille:0 dev_mean_mg:9 dev_max_mg:132 moving_ms:245 first_t_ms:20265024 last_t_ms:21945050 covered_by:@LAT103LON16471
```

---

@LAT106LON65 | created:0 | updated:0

**BAR** frame:7000 bar:37 own:10 held:40 terms:9 digest:0xb4e03f56 settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:187 hi:197 sum:1921
**HOLDS** agent:0x00000011 n:10 lo:118 hi:127 sum:1225
**HOLDS** agent:0x00000012 n:10 lo:33 hi:43 sum:379
**HOLDS** agent:0x00000200 n:10 lo:820 hi:829 sum:8245
**HOLDS** agent:0x00000300 n:10 lo:2262 hi:2281 sum:22714

---

@LAT103LON8338 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 22546277 ±0 frame:7000
seq: 2295
follows: 0x00000010:202 0x00000011:133 0x00000012:50 0x00000100:402 0x00000200:835
said: 1 | **ENTWIN** t_ms:22617489 stream:0x3c4214c9 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,84a329c78fec,0283cce0e689
said: 12 | **COVERED** windows:2 entities:10 window_ms:1202882 first_t_ms:21417489 last_t_ms:22017488 covered_by:@LAT103LON8337
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-35 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-71 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-72 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-69 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-83 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-91 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1
```

---

@LAT106LON66 | created:0 | updated:0

**BAR** frame:7000 bar:38 own:10 held:40 terms:9 digest:0x33428584 settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:198 hi:207 sum:2025
**HOLDS** agent:0x00000011 n:10 lo:128 hi:138 sum:1330
**HOLDS** agent:0x00000012 n:10 lo:44 hi:54 sum:489
**HOLDS** agent:0x00000200 n:10 lo:830 hi:840 sum:8353
**HOLDS** agent:0x00000300 n:10 lo:2283 hi:2302 sum:22924

---

@LAT103LON8339 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 23146276 ±0 frame:7000
seq: 2316
follows: 0x00000010:213 0x00000011:144 0x00000012:61 0x00000100:413 0x00000200:845
said: 1 | **ENTWIN** t_ms:23217488 stream:0x3c4214c9 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,5ce28c488e0c,0283cce0e689
```

---

@LAT106LON67 | created:0 | updated:0

**BAR** frame:7000 bar:39 own:10 held:38 terms:9 digest:0x0c80140a settled_ms:120000
**HOLDS** agent:0x00000010 n:8 lo:208 hi:216 sum:1696
**HOLDS** agent:0x00000011 n:10 lo:139 hi:149 sum:1440
**HOLDS** agent:0x00000012 n:10 lo:55 hi:65 sum:599
**HOLDS** agent:0x00000200 n:10 lo:841 hi:850 sum:8455
**HOLDS** agent:0x00000300 n:10 lo:2304 hi:2323 sum:23134

---

@LAT103LON16473 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 23733838 ±0 frame:7000
seq: 2336
follows: 0x00000010:223 0x00000011:155 0x00000012:71 0x00000100:423 0x00000200:856
said: 1 | **MOTIONWIN** t_ms:23805050 stream:0x3c4214c9 wall:0 window_ms:60000 n:993
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26973 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0 first_t_ms:22065050 last_t_ms:23745050 covered_by:@LAT103LON16472
```

---

@LAT103LON1926 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24093838 ±0 frame:7000
seq: 2348
follows: 0x00000010:229 0x00000011:161 0x00000012:78 0x00000100:430 0x00000200:862
said: 1 | **LINKWIN** t_ms:24165050 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-55 rssi_med:-52 rssi_max:-45
said: 4 | **LINK** peer:0x00000100 proto:espnow n:73 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 5 | **LINK** peer:0x00000012 proto:espnow n:117 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000011 proto:espnow n:88 rssi_min:-35 rssi_med:-34 rssi_max:-34
said: 7 | **LINK** peer:0x00000200 proto:espnow n:108 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 8 | **LINK** peer:0x00000012 proto:ble n:72 rssi_min:-61 rssi_med:-54 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 10 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000010 ble met predicted:-52 observed:-52
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000200 ble met predicted:-55 observed:-55
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-54 observed:-54
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-53 observed:-53
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT106LON68 | created:0 | updated:0

**BAR** frame:7000 bar:40 own:10 held:38 terms:9 digest:0x5a7ad8bc settled_ms:120000
**HOLDS** agent:0x00000010 n:8 lo:219 hi:226 sum:1780
**HOLDS** agent:0x00000011 n:10 lo:150 hi:160 sum:1550
**HOLDS** agent:0x00000012 n:10 lo:66 hi:76 sum:709
**HOLDS** agent:0x00000200 n:10 lo:851 hi:861 sum:8563
**HOLDS** agent:0x00000300 n:10 lo:2325 hi:2344 sum:23344

---

@LAT103LON1927 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24153838 ±0 frame:7000
seq: 2350
follows: 0x00000010:230 0x00000011:162 0x00000012:79 0x00000100:431 0x00000200:863
said: 1 | **LINKWIN** t_ms:24225050 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:111 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:76 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 5 | **LINK** peer:0x00000200 proto:espnow n:59 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 7 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-79 rssi_med:-52 rssi_max:-45
said: 8 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-63 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-61 rssi_med:-54 rssi_max:-52
said: 10 | 0x00000200 ble met predicted:-55 observed:-55
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-52 observed:-52
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-54 observed:-54
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-53 observed:-53
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON1928 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24213838 ±0 frame:7000
seq: 2352
follows: 0x00000010:231 0x00000011:163 0x00000012:80 0x00000100:432 0x00000200:864
said: 1 | **LINKWIN** t_ms:24285050 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-57 rssi_med:-52 rssi_max:-49
said: 4 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-21 rssi_med:-21 rssi_max:-20
said: 5 | **LINK** peer:0x00000200 proto:espnow n:132 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000012 proto:espnow n:157 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000011 proto:espnow n:122 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000010 proto:espnow n:136 rssi_min:-34 rssi_med:-33 rssi_max:-31
said: 9 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-61 rssi_med:-55 rssi_max:-52
said: 10 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-41 observed:-40
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-53 observed:-52
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000010 ble unobserved predicted:-52 observed:-52
percept: 15 | 0x00000010 | link_stable | ble | ? | -
said: 16 | 0x00000200 ble met predicted:-55 observed:-55
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-54 observed:-54
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON1929 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24273838 ±0 frame:7000
seq: 2354
follows: 0x00000010:232 0x00000011:164 0x00000012:80 0x00000100:433 0x00000200:865
said: 1 | **LINKWIN** t_ms:24345050 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-21 rssi_med:-21 rssi_max:-20
said: 3 | **LINK** peer:0x00000010 proto:espnow n:78 rssi_min:-33 rssi_med:-33 rssi_max:-32
said: 4 | **LINK** peer:0x00000011 proto:espnow n:83 rssi_min:-37 rssi_med:-34 rssi_max:-34
said: 5 | **LINK** peer:0x00000012 proto:espnow n:140 rssi_min:-37 rssi_med:-35 rssi_max:-34
said: 6 | **LINK** peer:0x00000200 proto:espnow n:124 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000200 proto:ble n:73 rssi_min:-65 rssi_med:-55 rssi_max:-52
said: 8 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-55 rssi_med:-52 rssi_max:-45
said: 10 | 0x00000012 ble met predicted:-54 observed:-54
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000011 ble unobserved predicted:-52 observed:-52
percept: 11 | 0x00000011 | link_stable | ble | ? | -
said: 12 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-40 observed:-41
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-33 observed:-33
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-55 observed:-55
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1930 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24333838 ±0 frame:7000
seq: 2356
follows: 0x00000010:233 0x00000011:166 0x00000012:82 0x00000100:435 0x00000200:866
said: 1 | **LINKWIN** t_ms:24405050 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 3 | **LINK** peer:0x00000011 proto:espnow n:86 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000012 proto:espnow n:130 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 5 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-56 rssi_med:-54 rssi_max:-52
said: 6 | **LINK** peer:0x00000010 proto:espnow n:89 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:espnow n:113 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 9 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-52 rssi_max:-45
said: 10 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-33 observed:-33
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-55 observed:-55
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-54 observed:-54
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-52 observed:-52
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON1931 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24393838 ±0 frame:7000
seq: 2358
follows: 0x00000010:234 0x00000011:167 0x00000012:83 0x00000100:436 0x00000200:867
said: 1 | **LINKWIN** t_ms:24465050 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 4 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000010 proto:espnow n:59 rssi_min:-33 rssi_med:-33 rssi_max:-32
said: 6 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 7 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:espnow n:89 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 9 | **LINK** peer:0x00000012 proto:espnow n:117 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 10 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-54 observed:-54
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-33 observed:-33
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-55 observed:-55
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000200 espnow met predicted:-41 observed:-40
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000010 ble unobserved predicted:-52 observed:-52
percept: 17 | 0x00000010 | link_stable | ble | ? | -
```

---

@LAT103LON1932 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24453838 ±0 frame:7000
seq: 2360
follows: 0x00000010:235 0x00000011:168 0x00000012:84 0x00000100:437 0x00000200:868
said: 1 | **LINKWIN** t_ms:24525050 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:150 rssi_min:-37 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 4 | **LINK** peer:0x00000200 proto:espnow n:179 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 5 | **LINK** peer:0x00000012 proto:espnow n:117 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 7 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-57 rssi_med:-53 rssi_max:-49
said: 8 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-55 rssi_med:-54 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-83 rssi_med:-52 rssi_max:-45
said: 10 | 0x00000011 ble met predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow unobserved predicted:-33 observed:-33
percept: 13 | 0x00000010 | link_stable | espnow | ? | -
said: 14 | 0x00000012 ble met predicted:-54 observed:-54
percept: 14 | 0x00000012 | link_stable | ble | + | -
said: 15 | 0x00000200 ble met predicted:-55 observed:-55
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000200 espnow met predicted:-40 observed:-41
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON1933 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24513838 ±0 frame:7000
seq: 2362
follows: 0x00000010:236 0x00000011:169 0x00000012:85 0x00000100:438 0x00000200:869
said: 1 | **LINKWIN** t_ms:24585050 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 3 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 4 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-82 rssi_med:-54 rssi_max:-52
said: 5 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-82 rssi_med:-52 rssi_max:-49
said: 6 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-55 rssi_med:-52 rssi_max:-45
said: 8 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:espnow n:89 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 10 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-55 observed:-55
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000011 ble met predicted:-53 observed:-52
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-54 observed:-54
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-52 observed:-52
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON1934 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24573838 ±0 frame:7000
seq: 2364
follows: 0x00000010:237 0x00000011:170 0x00000012:86 0x00000100:439 0x00000200:870
said: 1 | **LINKWIN** t_ms:24645050 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-79 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:espnow n:92 rssi_min:-35 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 5 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 6 | **LINK** peer:0x00000200 proto:espnow n:139 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-60 rssi_med:-54 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:espnow n:94 rssi_min:-33 rssi_med:-33 rssi_max:-32
said: 9 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 10 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000012 ble met predicted:-54 observed:-54
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000011 ble met predicted:-52 observed:-53
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble unobserved predicted:-52 observed:-52
percept: 15 | 0x00000010 | link_stable | ble | ? | -
said: 16 | 0x00000200 ble met predicted:-55 observed:-55
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON1935 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24633838 ±0 frame:7000
seq: 2366
follows: 0x00000010:238 0x00000011:171 0x00000012:87 0x00000100:440 0x00000200:871
said: 1 | **LINKWIN** t_ms:24705050 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:125 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 4 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-80 rssi_med:-55 rssi_max:-52
said: 5 | **LINK** peer:0x00000011 proto:espnow n:141 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000012 proto:espnow n:148 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-55 rssi_med:-52 rssi_max:-45
said: 9 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-57 rssi_med:-53 rssi_max:-49
said: 10 | 0x00000011 ble met predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-54 observed:-54
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow unobserved predicted:-33 observed:-33
percept: 16 | 0x00000010 | link_stable | espnow | ? | -
said: 17 | 0x00000200 ble met predicted:-55 observed:-55
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1936 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24693839 ±0 frame:7000
seq: 2368
follows: 0x00000010:239 0x00000011:172 0x00000012:88 0x00000100:441 0x00000200:872
said: 1 | **LINKWIN** t_ms:24765051 stream:0x3c4214c9 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 3 | **LINK** peer:0x00000200 proto:espnow n:100 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 4 | **LINK** peer:0x00000011 proto:espnow n:123 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 5 | **LINK** peer:0x00000012 proto:espnow n:169 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 7 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-57 rssi_med:-53 rssi_max:-49
said: 8 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-61 rssi_med:-54 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-80 rssi_med:-52 rssi_max:-45
said: 10 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-55 observed:-55
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-54 observed:-54
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-52 observed:-52
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-53 observed:-53
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT106LON69 | created:0 | updated:0

**BAR** frame:7000 bar:41 own:10 held:36 terms:9 digest:0x1a384774 settled_ms:120000
**HOLDS** agent:0x00000010 n:6 lo:229 hi:234 sum:1389
**HOLDS** agent:0x00000011 n:10 lo:161 hi:171 sum:1660
**HOLDS** agent:0x00000012 n:10 lo:77 hi:86 sum:815
**HOLDS** agent:0x00000200 n:10 lo:862 hi:871 sum:8665
**HOLDS** agent:0x00000300 n:10 lo:2346 hi:2364 sum:23550

---

@LAT103LON1937 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24753839 ±0 frame:7000
seq: 2370
follows: 0x00000010:240 0x00000011:173 0x00000012:89 0x00000100:442 0x00000200:873
said: 1 | **LINKWIN** t_ms:24825051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-79 rssi_med:-52 rssi_max:-45
said: 3 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-33 rssi_med:-33 rssi_max:-32
said: 4 | **LINK** peer:0x00000011 proto:espnow n:118 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 5 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-80 rssi_med:-54 rssi_max:-53
said: 6 | **LINK** peer:0x00000012 proto:espnow n:125 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 7 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 8 | **LINK** peer:0x00000200 proto:espnow n:53 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-55 rssi_max:-52
said: 10 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-55 observed:-55
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000011 ble unobserved predicted:-53 observed:-53
percept: 15 | 0x00000011 | link_stable | ble | ? | -
said: 16 | 0x00000012 ble met predicted:-54 observed:-54
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-52 observed:-52
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON1938 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24813839 ±0 frame:7000
seq: 2372
follows: 0x00000010:241 0x00000011:174 0x00000012:90 0x00000100:443 0x00000200:874
said: 1 | **LINKWIN** t_ms:24885051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:96 rssi_min:-33 rssi_med:-32 rssi_max:-32
said: 3 | **LINK** peer:0x00000012 proto:espnow n:120 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000011 proto:espnow n:142 rssi_min:-36 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 6 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-21 rssi_med:-21 rssi_max:-21
said: 7 | **LINK** peer:0x00000200 proto:espnow n:147 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 8 | **LINK** peer:0x00000011 proto:ble n:68 rssi_min:-79 rssi_med:-52 rssi_max:-49
said: 9 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 10 | 0x00000010 ble unobserved predicted:-52 observed:-52
percept: 10 | 0x00000010 | link_stable | ble | ? | -
said: 11 | 0x00000010 espnow met predicted:-33 observed:-32
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-54 observed:-54
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 15 | 0x00000100 | link_stable | espnow | + | -
said: 16 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-55 observed:-55
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1939 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24873839 ±0 frame:7000
seq: 2374
follows: 0x00000010:243 0x00000011:175 0x00000012:91 0x00000100:444 0x00000200:875
said: 1 | **LINKWIN** t_ms:24945051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-52 rssi_max:-45
said: 3 | **LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 4 | **LINK** peer:0x00000012 proto:espnow n:110 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 5 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-21 rssi_med:-21 rssi_max:-21
said: 6 | **LINK** peer:0x00000200 proto:espnow n:120 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-60 rssi_med:-54 rssi_max:-52
said: 8 | **LINK** peer:0x00000011 proto:ble n:72 rssi_min:-57 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000011 proto:espnow n:109 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 10 | 0x00000010 espnow met predicted:-32 observed:-33
percept: 10 | 0x00000010 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble unobserved predicted:-55 observed:-55
percept: 13 | 0x00000200 | link_stable | ble | ? | -
said: 14 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-52 observed:-53
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-54 observed:-54
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON1940 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24933839 ±0 frame:7000
seq: 2376
follows: 0x00000010:244 0x00000011:177 0x00000012:92 0x00000100:445 0x00000200:876
said: 1 | **LINKWIN** t_ms:25005051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-57 rssi_med:-52 rssi_max:-49
said: 3 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-52 rssi_max:-45
said: 4 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 5 | **LINK** peer:0x00000200 proto:espnow n:148 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 7 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-57 rssi_med:-53 rssi_max:-52
said: 8 | **LINK** peer:0x00000012 proto:espnow n:114 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 9 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 10 | 0x00000010 ble met predicted:-52 observed:-52
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000010 espnow unobserved predicted:-33 observed:-33
percept: 11 | 0x00000010 | link_stable | espnow | ? | -
said: 12 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-54 observed:-53
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-53 observed:-52
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON8340 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 24946441 ±0 frame:7000
seq: 2378
follows: 0x00000010:244 0x00000011:177 0x00000012:93 0x00000100:445 0x00000200:876
said: 1 | **ENTWIN** t_ms:25017653 stream:0x3c4214c9 wall:0 window_ms:600011 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-94
said: 9 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d,0283cce0e689
said: 11 | **COVERED** windows:2 entities:9 window_ms:1200154 first_t_ms:23817640 last_t_ms:24417642 covered_by:@LAT103LON8339
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-42 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-72 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-73 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-79 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-82 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-85 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-90 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1
```

---

@LAT103LON1941 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 24993839 ±0 frame:7000
seq: 2379
follows: 0x00000010:245 0x00000011:178 0x00000012:94 0x00000100:446 0x00000200:877
said: 1 | **LINKWIN** t_ms:25065051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-79 rssi_med:-53 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:100 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-22 rssi_med:-21 rssi_max:-18
said: 5 | **LINK** peer:0x00000011 proto:espnow n:112 rssi_min:-35 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-55 rssi_med:-52 rssi_max:-48
said: 7 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-60 rssi_med:-54 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-66 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:espnow n:109 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 10 | 0x00000011 ble met predicted:-52 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-52 observed:-52
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-41 observed:-40
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-53 observed:-54
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-55 observed:-55
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON1942 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25053839 ±0 frame:7000
seq: 2381
follows: 0x00000010:245 0x00000011:179 0x00000012:95 0x00000100:447 0x00000200:878
said: 1 | **LINKWIN** t_ms:25125051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:109 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:espnow n:120 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 4 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 5 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-57 rssi_med:-54 rssi_max:-52
said: 6 | **LINK** peer:0x00000010 proto:espnow n:83 rssi_min:-36 rssi_med:-32 rssi_max:-32
said: 7 | **LINK** peer:0x00000011 proto:espnow n:87 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 8 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-79 rssi_med:-50 rssi_max:-44
said: 9 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 10 | 0x00000011 ble unobserved predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | ? | -
said: 11 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 ble met predicted:-52 observed:-50
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-54 observed:-54
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-55 observed:-55
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON1943 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25113839 ±0 frame:7000
seq: 2383
follows: 0x00000010:247 0x00000011:180 0x00000012:96 0x00000100:448 0x00000200:879
said: 1 | **LINKWIN** t_ms:25185051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:69 rssi_min:-79 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000010 proto:espnow n:79 rssi_min:-35 rssi_med:-32 rssi_max:-32
said: 4 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 5 | **LINK** peer:0x00000011 proto:espnow n:70 rssi_min:-37 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000200 proto:espnow n:108 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 7 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 8 | **LINK** peer:0x00000010 proto:ble n:45 rssi_min:-55 rssi_med:-50 rssi_max:-48
said: 9 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-54 rssi_max:-52
said: 10 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-54 observed:-54
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-32 observed:-32
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-50 observed:-50
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000200 ble unobserved predicted:-55 observed:-55
percept: 17 | 0x00000200 | link_stable | ble | ? | -
```

---

@LAT103LON1944 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25173839 ±0 frame:7000
seq: 2385
follows: 0x00000010:249 0x00000011:181 0x00000012:97 0x00000100:449 0x00000200:880
said: 1 | **LINKWIN** t_ms:25245051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:106 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 4 | **LINK** peer:0x00000200 proto:ble n:70 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 5 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-80 rssi_med:-54 rssi_max:-52
said: 6 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-57 rssi_med:-53 rssi_max:-49
said: 7 | **LINK** peer:0x00000012 proto:espnow n:165 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 8 | **LINK** peer:0x00000011 proto:espnow n:125 rssi_min:-35 rssi_med:-34 rssi_max:-34
said: 9 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-51 rssi_max:-45
said: 10 | 0x00000011 ble met predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000010 espnow unobserved predicted:-32 observed:-32
percept: 11 | 0x00000010 | link_stable | espnow | ? | -
said: 12 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-50 observed:-51
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-54 observed:-54
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON1945 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25233839 ±0 frame:7000
seq: 2387
follows: 0x00000010:249 0x00000011:182 0x00000012:98 0x00000100:450 0x00000200:881
said: 1 | **LINKWIN** t_ms:25305051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-21 rssi_med:-21 rssi_max:-20
said: 3 | **LINK** peer:0x00000200 proto:espnow n:100 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:espnow n:88 rssi_min:-35 rssi_med:-32 rssi_max:-32
said: 5 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-80 rssi_med:-54 rssi_max:-52
said: 6 | **LINK** peer:0x00000011 proto:espnow n:80 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 7 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-55 rssi_med:-50 rssi_max:-44
said: 8 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-53 rssi_max:-49
said: 10 | 0x00000200 espnow met predicted:-40 observed:-41
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-55 observed:-55
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000012 ble met predicted:-54 observed:-54
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000011 ble met predicted:-53 observed:-53
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000012 espnow unobserved predicted:-35 observed:-35
percept: 15 | 0x00000012 | link_stable | espnow | ? | -
said: 16 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000010 ble met predicted:-51 observed:-50
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON1946 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25293839 ±0 frame:7000
seq: 2389
follows: 0x00000010:250 0x00000011:183 0x00000012:99 0x00000100:451 0x00000200:882
said: 1 | **LINKWIN** t_ms:25365051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 3 | **LINK** peer:0x00000011 proto:espnow n:71 rssi_min:-35 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000012 proto:espnow n:67 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 5 | **LINK** peer:0x00000200 proto:espnow n:108 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 7 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-79 rssi_med:-54 rssi_max:-52
said: 8 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000010 proto:espnow n:89 rssi_min:-35 rssi_med:-32 rssi_max:-32
said: 10 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-41 observed:-40
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-32 observed:-32
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-54 observed:-54
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble unobserved predicted:-50 observed:-50
percept: 15 | 0x00000010 | link_stable | ble | ? | -
said: 16 | 0x00000200 ble met predicted:-55 observed:-55
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-53 observed:-53
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON26313 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25293839 ±0 frame:7000
seq: 2390
follows: 0x00000010:250 0x00000011:183 0x00000012:99 0x00000100:451 0x00000200:882
said: 1 | **ACOUSTICWIN** t_ms:25365051 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3714 rate:8000
said: 2 | **ACOUSTIC** rms_mean:80 rms_max:304 peak:580 transients:0
```

---

@LAT106LON70 | created:0 | updated:0

**BAR** frame:7000 bar:42 own:10 held:33 terms:9 digest:0xe0bc5b95 settled_ms:120000
**HOLDS** agent:0x00000010 n:3 lo:239 hi:241 sum:720
**HOLDS** agent:0x00000011 n:10 lo:172 hi:182 sum:1770
**HOLDS** agent:0x00000012 n:10 lo:87 hi:97 sum:919
**HOLDS** agent:0x00000200 n:10 lo:872 hi:881 sum:8765
**HOLDS** agent:0x00000300 n:10 lo:2366 hi:2385 sum:23754

---

@LAT103LON1947 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25353839 ±0 frame:7000
seq: 2391
follows: 0x00000010:251 0x00000011:184 0x00000012:100 0x00000100:452 0x00000200:883
said: 1 | **LINKWIN** t_ms:25425051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-55 rssi_med:-50 rssi_max:-45
said: 3 | **LINK** peer:0x00000012 proto:ble n:68 rssi_min:-82 rssi_med:-54 rssi_max:-52
said: 4 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 5 | **LINK** peer:0x00000200 proto:espnow n:68 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000012 proto:espnow n:120 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:espnow n:68 rssi_min:-35 rssi_med:-32 rssi_max:-32
said: 10 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-40 observed:-40
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-55 observed:-55
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-54 observed:-54
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble unobserved predicted:-53 observed:-53
percept: 16 | 0x00000011 | link_stable | ble | ? | -
said: 17 | 0x00000010 espnow met predicted:-32 observed:-32
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON26314 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25353839 ±0 frame:7000
seq: 2392
follows: 0x00000010:251 0x00000011:184 0x00000012:100 0x00000100:452 0x00000200:883
said: 1 | **ACOUSTICWIN** t_ms:25425051 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:2681 rate:8000
said: 2 | **ACOUSTIC** rms_mean:78 rms_max:400 peak:836 transients:0
```

---

@LAT103LON1948 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25413839 ±0 frame:7000
seq: 2393
follows: 0x00000010:252 0x00000011:185 0x00000012:101 0x00000100:453 0x00000200:884
said: 1 | **LINKWIN** t_ms:25485051 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-50 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:156 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 4 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-82 rssi_med:-52 rssi_max:-49
said: 5 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-21 rssi_med:-21 rssi_max:-21
said: 6 | **LINK** peer:0x00000012 proto:espnow n:135 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-55 rssi_max:-52
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-35 rssi_med:-34 rssi_max:-34
said: 10 | 0x00000010 ble met predicted:-50 observed:-50
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-54 observed:-54
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-40 observed:-41
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-55 observed:-55
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow unobserved predicted:-32 observed:-32
percept: 17 | 0x00000010 | link_stable | espnow | ? | -
```

---

@LAT103LON26315 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25413839 ±0 frame:7000
seq: 2394
follows: 0x00000010:252 0x00000011:185 0x00000012:101 0x00000100:453 0x00000200:884
said: 1 | **ACOUSTICWIN** t_ms:25485051 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3431 rate:8000
said: 2 | **ACOUSTIC** rms_mean:107 rms_max:668 peak:971 transients:0
```

---

@LAT103LON1949 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25477211 ±0 frame:7000
seq: 2395
follows: 0x00000010:253 0x00000011:186 0x00000012:102 0x00000100:454 0x00000200:885
said: 1 | **LINKWIN** t_ms:25548423 stream:0x3c4214c9 wall:0 window_ms:63372
said: 2 | **LINK** peer:0x00000200 proto:espnow n:156 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 4 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-57 rssi_med:-53 rssi_max:-49
said: 5 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000012 proto:espnow n:123 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000012 proto:ble n:71 rssi_min:-55 rssi_med:-54 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-63 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-55 rssi_med:-50 rssi_max:-48
said: 10 | 0x00000010 ble met predicted:-50 observed:-50
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-41 observed:-40
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000011 ble met predicted:-52 observed:-53
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-55 observed:-55
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-54 observed:-54
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON26316 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25477211 ±0 frame:7000
seq: 2396
follows: 0x00000010:253 0x00000011:186 0x00000012:102 0x00000100:454 0x00000200:885
said: 1 | **ACOUSTICWIN** t_ms:25548423 stream:0x3c4214c9 wall:0 window_ms:63372 blocks:3666 rate:8000
said: 2 | **ACOUSTIC** rms_mean:116 rms_max:687 peak:1056 transients:0
```

---

@LAT103LON1950 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25537211 ±0 frame:7000
seq: 2397
follows: 0x00000010:254 0x00000011:188 0x00000012:103 0x00000100:456 0x00000200:886
said: 1 | **LINKWIN** t_ms:25608423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 3 | **LINK** peer:0x00000012 proto:espnow n:66 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-78 rssi_med:-55 rssi_max:-52
said: 5 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:ble n:50 rssi_min:-57 rssi_med:-53 rssi_max:-49
said: 7 | **LINK** peer:0x00000011 proto:espnow n:69 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 8 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-81 rssi_med:-50 rssi_max:-45
said: 9 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-60 rssi_med:-54 rssi_max:-52
said: 10 | 0x00000200 espnow met predicted:-40 observed:-41
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000011 ble met predicted:-53 observed:-53
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-54 observed:-54
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-55 observed:-55
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-50 observed:-50
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON16474 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 25537211 ±0 frame:7000
seq: 2398
follows: 0x00000010:254 0x00000011:188 0x00000012:103 0x00000100:456 0x00000200:886
said: 1 | **MOTIONWIN** t_ms:25608423 stream:0x3c4214c9 wall:0 window_ms:60000 n:991
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26990 window_ms:1743373 moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0 first_t_ms:23865050 last_t_ms:25548423 covered_by:@LAT103LON16473
```

---

@LAT103LON26317 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25537211 ±0 frame:7000
seq: 2399
follows: 0x00000010:254 0x00000011:188 0x00000012:103 0x00000100:456 0x00000200:886
said: 1 | **ACOUSTICWIN** t_ms:25608423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3699 rate:8000
said: 2 | **ACOUSTIC** rms_mean:146 rms_max:624 peak:1058 transients:0
```

---

@LAT103LON1951 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25597211 ±0 frame:7000
seq: 2400
follows: 0x00000010:255 0x00000011:189 0x00000012:104 0x00000100:458 0x00000200:887
said: 1 | **LINKWIN** t_ms:25668423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-80 rssi_med:-52 rssi_max:-49
said: 3 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 4 | **LINK** peer:0x00000200 proto:espnow n:118 rssi_min:-42 rssi_med:-41 rssi_max:-38
said: 5 | **LINK** peer:0x00000011 proto:espnow n:108 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000012 proto:espnow n:73 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-80 rssi_med:-54 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-55 rssi_med:-51 rssi_max:-44
said: 10 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-55 observed:-55
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-53 observed:-52
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-50 observed:-51
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-54 observed:-54
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON26318 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25597211 ±0 frame:7000
seq: 2401
follows: 0x00000010:255 0x00000011:189 0x00000012:104 0x00000100:458 0x00000200:887
said: 1 | **ACOUSTICWIN** t_ms:25668423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3452 rate:8000
said: 2 | **ACOUSTIC** rms_mean:119 rms_max:614 peak:840 transients:0
```

---

@LAT103LON1952 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25657211 ±0 frame:7000
seq: 2402
follows: 0x00000010:256 0x00000011:190 0x00000012:105 0x00000100:459 0x00000200:888
said: 1 | **LINKWIN** t_ms:25728423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:144 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-79 rssi_med:-54 rssi_max:-52
said: 4 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-21 rssi_med:-21 rssi_max:-20
said: 5 | **LINK** peer:0x00000011 proto:espnow n:122 rssi_min:-35 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000012 proto:espnow n:116 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-55 rssi_med:-50 rssi_max:-48
said: 8 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-57 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 10 | 0x00000011 ble met predicted:-52 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-54 observed:-54
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-55 observed:-55
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-51 observed:-50
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON26319 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25657211 ±0 frame:7000
seq: 2403
follows: 0x00000010:256 0x00000011:190 0x00000012:105 0x00000100:459 0x00000200:888
said: 1 | **ACOUSTICWIN** t_ms:25728423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3688 rate:8000
said: 2 | **ACOUSTIC** rms_mean:79 rms_max:176 peak:395 transients:0
```

---

@LAT103LON1953 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25717211 ±0 frame:7000
seq: 2404
follows: 0x00000010:257 0x00000011:191 0x00000012:106 0x00000100:460 0x00000200:889
said: 1 | **LINKWIN** t_ms:25788423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:124 rssi_min:-36 rssi_med:-34 rssi_max:-32
said: 3 | **LINK** peer:0x00000011 proto:ble n:71 rssi_min:-57 rssi_med:-53 rssi_max:-49
said: 4 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 5 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-21 rssi_med:-21 rssi_max:-20
said: 6 | **LINK** peer:0x00000200 proto:espnow n:164 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000012 proto:espnow n:81 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 8 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-56 rssi_med:-54 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:espnow n:68 rssi_min:-35 rssi_med:-32 rssi_max:-32
said: 10 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000012 ble met predicted:-54 observed:-54
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble unobserved predicted:-50 observed:-50
percept: 15 | 0x00000010 | link_stable | ble | ? | -
said: 16 | 0x00000011 ble met predicted:-53 observed:-53
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-55 observed:-55
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON26320 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25717211 ±0 frame:7000
seq: 2405
follows: 0x00000010:257 0x00000011:191 0x00000012:106 0x00000100:460 0x00000200:889
said: 1 | **ACOUSTICWIN** t_ms:25788423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3424 rate:8000
said: 2 | **ACOUSTIC** rms_mean:84 rms_max:252 peak:570 transients:0
```

---

@LAT103LON1954 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25777211 ±0 frame:7000
seq: 2406
follows: 0x00000010:258 0x00000011:192 0x00000012:107 0x00000100:461 0x00000200:890
said: 1 | **LINKWIN** t_ms:25848423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-79 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-55 rssi_med:-50 rssi_max:-45
said: 4 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 5 | **LINK** peer:0x00000012 proto:espnow n:65 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 6 | **LINK** peer:0x00000200 proto:espnow n:96 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 8 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-57 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 10 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000011 ble met predicted:-53 observed:-53
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000200 ble met predicted:-55 observed:-55
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-54 observed:-54
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow unobserved predicted:-32 observed:-32
percept: 17 | 0x00000010 | link_stable | espnow | ? | -
```

---

@LAT103LON26321 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25777211 ±0 frame:7000
seq: 2407
follows: 0x00000010:258 0x00000011:192 0x00000012:107 0x00000100:461 0x00000200:890
said: 1 | **ACOUSTICWIN** t_ms:25848423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3700 rate:8000
said: 2 | **ACOUSTIC** rms_mean:77 rms_max:150 peak:360 transients:0
```

---

@LAT103LON1955 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25837211 ±0 frame:7000
seq: 2408
follows: 0x00000010:259 0x00000011:193 0x00000012:108 0x00000100:462 0x00000200:891
said: 1 | **LINKWIN** t_ms:25908423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:109 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000012 proto:espnow n:102 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-21 rssi_med:-21 rssi_max:-20
said: 5 | **LINK** peer:0x00000011 proto:espnow n:82 rssi_min:-35 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-57 rssi_med:-52 rssi_max:-49
said: 7 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-64 rssi_med:-55 rssi_max:-52
said: 8 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-61 rssi_med:-54 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-83 rssi_med:-51 rssi_max:-47
said: 10 | 0x00000012 ble met predicted:-54 observed:-54
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-50 observed:-51
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-53 observed:-52
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-55 observed:-55
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON26322 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25837211 ±0 frame:7000
seq: 2409
follows: 0x00000010:259 0x00000011:193 0x00000012:108 0x00000100:462 0x00000200:891
said: 1 | **ACOUSTICWIN** t_ms:25908423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3459 rate:8000
said: 2 | **ACOUSTIC** rms_mean:92 rms_max:2103 peak:2413 transients:2
said: 3 | **TRANSIENT** t_ms:25889938 stream:0x3c4214c9 wall:0 rms:1310
```

---

@LAT103LON1956 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25897211 ±0 frame:7000
seq: 2410
follows: 0x00000010:260 0x00000011:194 0x00000012:109 0x00000100:463 0x00000200:892
said: 1 | **LINKWIN** t_ms:25968423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 3 | **LINK** peer:0x00000012 proto:espnow n:106 rssi_min:-38 rssi_med:-35 rssi_max:-33
said: 4 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-34 rssi_med:-32 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-52 rssi_max:-49
said: 6 | **LINK** peer:0x00000011 proto:espnow n:101 rssi_min:-37 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-79 rssi_med:-50 rssi_max:-43
said: 8 | **LINK** peer:0x00000200 proto:espnow n:150 rssi_min:-42 rssi_med:-41 rssi_max:-39
said: 9 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-63 rssi_med:-55 rssi_max:-51
said: 10 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-35 observed:-35
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-21 observed:-21
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-52 observed:-52
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000200 ble met predicted:-55 observed:-55
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000012 ble unobserved predicted:-54 observed:-54
percept: 16 | 0x00000012 | link_stable | ble | ? | -
said: 17 | 0x00000010 ble met predicted:-51 observed:-50
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON26323 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25897211 ±0 frame:7000
seq: 2411
follows: 0x00000010:260 0x00000011:194 0x00000012:109 0x00000100:463 0x00000200:892
said: 1 | **ACOUSTICWIN** t_ms:25968423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3694 rate:8000
said: 2 | **ACOUSTIC** rms_mean:129 rms_max:18719 peak:32768 transients:7
said: 3 | **TRANSIENT** t_ms:25958759 stream:0x3c4214c9 wall:0 rms:18719
```

---

@LAT106LON71 | created:0 | updated:0

**BAR** frame:7000 bar:43 own:10 held:33 terms:9 digest:0x388f0ade settled_ms:120046
**HOLDS** agent:0x00000010 n:3 lo:250 hi:252 sum:753
**HOLDS** agent:0x00000011 n:10 lo:183 hi:193 sum:1880
**HOLDS** agent:0x00000012 n:10 lo:98 hi:107 sum:1025
**HOLDS** agent:0x00000200 n:10 lo:882 hi:891 sum:8865
**HOLDS** agent:0x00000300 n:10 lo:2387 hi:2406 sum:23964

---

@LAT103LON1957 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 25957211 ±0 frame:7000
seq: 2412
follows: 0x00000010:261 0x00000011:195 0x00000012:110 0x00000100:464 0x00000200:893
said: 1 | **LINKWIN** t_ms:26028423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:64 rssi_min:-68 rssi_med:-43 rssi_max:-34
said: 3 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-69 rssi_med:-56 rssi_max:-47
said: 4 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-79 rssi_med:-61 rssi_max:-42
said: 5 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-82 rssi_med:-58 rssi_max:-49
said: 6 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-80 rssi_med:-48 rssi_max:-43
said: 7 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-55 rssi_med:-28 rssi_max:-26
said: 8 | **LINK** peer:0x00000011 proto:espnow n:75 rssi_min:-57 rssi_med:-39 rssi_max:-30
said: 9 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-57 rssi_med:-44 rssi_max:-32
said: 10 | 0x00000100 espnow violated predicted:-21 observed:-44
percept: 10 | 0x00000100 | link_stable | espnow | - | -
said: 11 | 0x00000012 espnow violated predicted:-35 observed:-28
percept: 11 | 0x00000012 | link_stable | espnow | - | -
said: 12 | 0x00000010 espnow unobserved predicted:-32 observed:-32
percept: 12 | 0x00000010 | link_stable | espnow | ? | -
said: 13 | 0x00000011 ble met predicted:-52 observed:-56
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-34 observed:-39
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble violated predicted:-50 observed:-61
percept: 15 | 0x00000010 | link_stable | ble | - | -
said: 16 | 0x00000200 espnow met predicted:-41 observed:-43
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-55 observed:-58
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON26324 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 25957211 ±0 frame:7000
seq: 2413
follows: 0x00000010:261 0x00000011:195 0x00000012:110 0x00000100:464 0x00000200:893
said: 1 | **ACOUSTICWIN** t_ms:26028423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:2673 rate:8000
said: 2 | **ACOUSTIC** rms_mean:232 rms_max:17940 peak:32768 transients:26
said: 3 | **TRANSIENT** t_ms:25983774 stream:0x3c4214c9 wall:0 rms:17940
```

---

@LAT105LON1263 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 25914579 ±21 frame:7000
seq: 893
follows: 0x00000010:261 0x00000011:194 0x00000012:109 0x00000100:463 0x00000300:2411
said: 1 | **LINKWIN** t_ms:25985767 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:69 rssi_min:-54 rssi_med:-48 rssi_max:-44
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-34 rssi_med:-33 rssi_max:-31
said: 4 | **LINK** peer:0x00000011 proto:espnow n:93 rssi_min:-65 rssi_med:-53 rssi_max:-44
said: 5 | **LINK** peer:0x00000010 proto:espnow n:142 rssi_min:-52 rssi_med:-47 rssi_max:-43
said: 6 | **LINK** peer:0x00000300 proto:espnow n:186 rssi_min:-61 rssi_med:-35 rssi_max:-31
said: 7 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-63 rssi_max:-57
said: 8 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-81 rssi_med:-68 rssi_max:-53
said: 9 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-52 rssi_max:-45
```

---

@LAT105LON1264 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 25920835 ±21 frame:7000
seq: 195
follows: 0x00000010:261 0x00000012:109 0x00000100:464 0x00000200:893 0x00000300:2411
said: 1 | **LINKWIN** t_ms:25992028 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:145 rssi_min:-65 rssi_med:-56 rssi_max:-46
said: 3 | **LINK** peer:0x00000300 proto:espnow n:203 rssi_min:-59 rssi_med:-27 rssi_max:-23
said: 4 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-54 rssi_max:-29
said: 5 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-45 rssi_max:-37
said: 6 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-52 rssi_med:-20 rssi_max:-19
said: 7 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-67 rssi_med:-43 rssi_max:-26
said: 8 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-65 rssi_max:-51
said: 9 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-82 rssi_med:-37 rssi_max:-33
```

---

@LAT105LON1265 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 25480737 ±21 frame:7000
seq: 254
follows: 0x00000011:186 0x00000012:101 0x00000100:454 0x00000200:885 0x00000300:2394
said: 1 | **LINKWIN** t_ms:25551918 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:100 rssi_min:-24 rssi_med:-24 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:83 rssi_min:-42 rssi_med:-38 rssi_max:-37
said: 4 | **LINK** peer:0x00000011 proto:ble n:87 rssi_min:-81 rssi_med:-55 rssi_max:-45
said: 5 | **LINK** peer:0x00000012 proto:espnow n:42 rssi_min:-61 rssi_med:-60 rssi_max:-59
said: 6 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-54 rssi_med:-52 rssi_max:-51
said: 7 | **LINK** peer:0x00000012 proto:ble n:88 rssi_min:-82 rssi_med:-68 rssi_max:-59
said: 8 | **LINK** peer:0x00000200 proto:ble n:84 rssi_min:-82 rssi_med:-64 rssi_max:-62
said: 9 | **LINK** peer:0x00000100 proto:espnow n:32 rssi_min:-49 rssi_med:-49 rssi_max:-47
```

---

@LAT105LON1266 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 25974600 ±21 frame:7000
seq: 894
follows: 0x00000010:262 0x00000011:195 0x00000012:110 0x00000100:464 0x00000300:2413
said: 1 | **LINKWIN** t_ms:26045787 stream:0x3c4214c9 wall:0 window_ms:60020
said: 2 | **LINK** peer:0x00000012 proto:espnow n:81 rssi_min:-52 rssi_med:-45 rssi_max:-43
said: 3 | **LINK** peer:0x00000011 proto:espnow n:73 rssi_min:-90 rssi_med:-44 rssi_max:-42
said: 4 | **LINK** peer:0x00000010 proto:espnow n:125 rssi_min:-51 rssi_med:-47 rssi_max:-43
said: 5 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 6 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-59 rssi_max:-50
said: 7 | **LINK** peer:0x00000010 proto:ble n:51 rssi_min:-82 rssi_med:-60 rssi_max:-54
said: 8 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-79 rssi_med:-56 rssi_max:-51
said: 9 | **LINK** peer:0x00000300 proto:espnow n:172 rssi_min:-51 rssi_med:-39 rssi_max:-35
```

---

@LAT103LON1958 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26017211 ±0 frame:7000
seq: 2414
follows: 0x00000010:262 0x00000011:196 0x00000012:111 0x00000100:465 0x00000200:894
said: 1 | **LINKWIN** t_ms:26088423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:158 rssi_min:-52 rssi_med:-46 rssi_max:-38
said: 3 | **LINK** peer:0x00000012 proto:espnow n:77 rssi_min:-32 rssi_med:-28 rssi_max:-25
said: 4 | **LINK** peer:0x00000011 proto:espnow n:138 rssi_min:-48 rssi_med:-41 rssi_max:-33
said: 5 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-62 rssi_med:-44 rssi_max:-41
said: 6 | **LINK** peer:0x00000200 proto:espnow n:133 rssi_min:-50 rssi_med:-43 rssi_max:-41
said: 7 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-56 rssi_med:-47 rssi_max:-42
said: 8 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-67 rssi_med:-54 rssi_max:-50
said: 9 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-59 rssi_max:-51
said: 10 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000011 ble met predicted:-56 observed:-54
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-61 observed:-59
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000200 ble unobserved predicted:-58 observed:-58
percept: 13 | 0x00000200 | link_stable | ble | ? | -
said: 14 | 0x00000012 ble met predicted:-48 observed:-47
percept: 14 | 0x00000012 | link_stable | ble | + | -
said: 15 | 0x00000012 espnow met predicted:-28 observed:-28
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000011 espnow met predicted:-39 observed:-41
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000100 espnow met predicted:-44 observed:-44
percept: 17 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON26325 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 26017211 ±0 frame:7000
seq: 2415
follows: 0x00000010:262 0x00000011:196 0x00000012:111 0x00000100:465 0x00000200:894
said: 1 | **ACOUSTICWIN** t_ms:26088423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3679 rate:8000
said: 2 | **ACOUSTIC** rms_mean:164 rms_max:5564 peak:14884 transients:11
said: 3 | **TRANSIENT** t_ms:26067554 stream:0x3c4214c9 wall:0 rms:5564
```

---

@LAT105LON1267 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 26005561 ±21 frame:7000
seq: 111
follows: 0x00000010:262 0x00000011:196 0x00000100:465 0x00000200:894 0x00000300:2413
said: 1 | **LINKWIN** t_ms:26076772 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:142 rssi_min:-67 rssi_med:-55 rssi_max:-46
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-38 rssi_max:-33
said: 4 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-62 rssi_med:-45 rssi_max:-43
said: 5 | **LINK** peer:0x00000010 proto:espnow n:147 rssi_min:-55 rssi_med:-48 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:espnow n:111 rssi_min:-43 rssi_med:-39 rssi_max:-31
said: 7 | **LINK** peer:0x00000300 proto:espnow n:191 rssi_min:-25 rssi_med:-22 rssi_max:-19
said: 8 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-61 rssi_max:-54
said: 9 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-55 rssi_max:-49
```

---

@LAT105LON1268 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 26034601 ±21 frame:7000
seq: 895
follows: 0x00000010:262 0x00000011:196 0x00000012:111 0x00000100:465 0x00000300:2415
said: 1 | **LINKWIN** t_ms:26105787 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:95 rssi_min:-73 rssi_med:-52 rssi_max:-48
said: 3 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-35 rssi_med:-34 rssi_max:-31
said: 4 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-58 rssi_max:-55
said: 5 | **LINK** peer:0x00000011 proto:ble n:41 rssi_min:-67 rssi_med:-58 rssi_max:-51
said: 6 | **LINK** peer:0x00000010 proto:espnow n:87 rssi_min:-51 rssi_med:-46 rssi_max:-41
said: 7 | **LINK** peer:0x00000300 proto:espnow n:168 rssi_min:-49 rssi_med:-40 rssi_max:-36
said: 8 | **LINK** peer:0x00000011 proto:espnow n:77 rssi_min:-51 rssi_med:-44 rssi_max:-35
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-63 rssi_med:-57 rssi_max:-51
```

---

@LAT105LON1269 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 25540740 ±21 frame:7000
seq: 255
follows: 0x00000011:187 0x00000012:102 0x00000100:456 0x00000200:886 0x00000300:2396
said: 1 | **LINKWIN** t_ms:25595918 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:78 rssi_min:-42 rssi_med:-38 rssi_max:-37
said: 3 | **LINK** peer:0x00000011 proto:ble n:80 rssi_min:-80 rssi_med:-55 rssi_max:-45
said: 4 | **LINK** peer:0x00000012 proto:ble n:80 rssi_min:-74 rssi_med:-68 rssi_max:-58
said: 5 | **LINK** peer:0x00000200 proto:ble n:86 rssi_min:-81 rssi_med:-64 rssi_max:-62
said: 6 | **LINK** peer:0x00000012 proto:espnow n:43 rssi_min:-60 rssi_med:-59 rssi_max:-58
said: 7 | **LINK** peer:0x00000300 proto:espnow n:83 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 8 | **LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 9 | **LINK** peer:0x00000011 proto:espnow n:34 rssi_min:-48 rssi_med:-47 rssi_max:-46
```

---

@LAT103LON1959 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26077211 ±0 frame:7000
seq: 2416
follows: 0x00000010:263 0x00000011:196 0x00000012:112 0x00000100:466 0x00000200:895
said: 1 | **LINKWIN** t_ms:26148423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-79 rssi_med:-65 rssi_max:-61
said: 3 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-55 rssi_med:-52 rssi_max:-51
said: 4 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-28 rssi_med:-28 rssi_max:-27
said: 5 | **LINK** peer:0x00000200 proto:espnow n:131 rssi_min:-53 rssi_med:-50 rssi_max:-48
said: 6 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-79 rssi_med:-59 rssi_max:-55
said: 7 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-50 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000010 proto:espnow n:122 rssi_min:-44 rssi_med:-42 rssi_max:-41
said: 9 | **LINK** peer:0x00000011 proto:ble n:45 rssi_min:-59 rssi_med:-56 rssi_max:-51
said: 10 | 0x00000010 espnow met predicted:-46 observed:-42
percept: 10 | 0x00000010 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-28 observed:-28
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow unobserved predicted:-41 observed:-41
percept: 12 | 0x00000011 | link_stable | espnow | ? | -
said: 13 | 0x00000100 espnow violated predicted:-44 observed:-52
percept: 13 | 0x00000100 | link_stable | espnow | - | -
said: 14 | 0x00000200 espnow violated predicted:-43 observed:-50
percept: 14 | 0x00000200 | link_stable | espnow | - | -
said: 15 | 0x00000012 ble met predicted:-47 observed:-45
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-54 observed:-56
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-59 observed:-59
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON26326 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 26077211 ±0 frame:7000
seq: 2417
follows: 0x00000010:263 0x00000011:196 0x00000012:112 0x00000100:466 0x00000200:895
said: 1 | **ACOUSTICWIN** t_ms:26148423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3499 rate:8000
said: 2 | **ACOUSTIC** rms_mean:105 rms_max:6472 peak:19160 transients:3
said: 3 | **TRANSIENT** t_ms:26091489 stream:0x3c4214c9 wall:0 rms:6472
```

---

@LAT105LON1270 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 26094602 ±21 frame:7000
seq: 896
follows: 0x00000010:264 0x00000011:198 0x00000012:112 0x00000100:466 0x00000300:2417
said: 1 | **LINKWIN** t_ms:26165787 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:58 rssi_min:-57 rssi_med:-50 rssi_max:-48
said: 3 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000010 proto:espnow n:189 rssi_min:-47 rssi_med:-44 rssi_max:-42
said: 5 | **LINK** peer:0x00000300 proto:espnow n:143 rssi_min:-50 rssi_med:-48 rssi_max:-39
said: 6 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-65 rssi_med:-56 rssi_max:-54
said: 7 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-79 rssi_med:-65 rssi_max:-58
said: 8 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-60 rssi_max:-54
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-83 rssi_med:-56 rssi_max:-49
```

---

@LAT105LON1271 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 25980837 ±21 frame:7000
seq: 196
follows: 0x00000010:262 0x00000012:110 0x00000100:465 0x00000200:894 0x00000300:2413
said: 1 | **LINKWIN** t_ms:26052027 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-53 rssi_med:-42 rssi_max:-30
said: 3 | **LINK** peer:0x00000300 proto:espnow n:217 rssi_min:-45 rssi_med:-41 rssi_max:-28
said: 4 | **LINK** peer:0x00000012 proto:espnow n:81 rssi_min:-44 rssi_med:-41 rssi_max:-32
said: 5 | **LINK** peer:0x00000010 proto:espnow n:128 rssi_min:-23 rssi_med:-19 rssi_max:-17
said: 6 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-50 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-82 rssi_med:-33 rssi_max:-29
said: 8 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-54 rssi_max:-49
said: 9 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-82 rssi_med:-58 rssi_max:-51
```

---

@LAT103LON1960 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26137211 ±0 frame:7000
seq: 2418
follows: 0x00000010:264 0x00000011:198 0x00000012:114 0x00000100:467 0x00000200:896
said: 1 | **LINKWIN** t_ms:26208423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:74 rssi_min:-60 rssi_med:-36 rssi_max:-27
said: 3 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-73 rssi_med:-60 rssi_max:-52
said: 4 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-61 rssi_med:-49 rssi_max:-41
said: 5 | **LINK** peer:0x00000011 proto:espnow n:70 rssi_min:-43 rssi_med:-32 rssi_max:-23
said: 6 | **LINK** peer:0x00000200 proto:espnow n:140 rssi_min:-62 rssi_med:-45 rssi_max:-42
said: 7 | **LINK** peer:0x00000010 proto:espnow n:146 rssi_min:-65 rssi_med:-45 rssi_max:-39
said: 8 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-81 rssi_med:-61 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-66 rssi_med:-53 rssi_max:-43
said: 10 | 0x00000200 ble met predicted:-65 observed:-61
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-52 observed:-49
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow violated predicted:-28 observed:-36
percept: 12 | 0x00000012 | link_stable | espnow | - | -
said: 13 | 0x00000200 espnow met predicted:-50 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000010 ble met predicted:-59 observed:-60
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000012 ble violated predicted:-45 observed:-53
percept: 15 | 0x00000012 | link_stable | ble | - | -
said: 16 | 0x00000010 espnow met predicted:-42 observed:-45
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble unobserved predicted:-56 observed:-56
percept: 17 | 0x00000011 | link_stable | ble | ? | -
```

---

@LAT103LON26327 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 26137211 ±0 frame:7000
seq: 2419
follows: 0x00000010:264 0x00000011:198 0x00000012:114 0x00000100:467 0x00000200:896
said: 1 | **ACOUSTICWIN** t_ms:26208423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3699 rate:8000
said: 2 | **ACOUSTIC** rms_mean:111 rms_max:1744 peak:7539 transients:4
said: 3 | **TRANSIENT** t_ms:26155534 stream:0x3c4214c9 wall:0 rms:1744
```

---

@LAT103LON8341 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 26146442 ±0 frame:7000
seq: 2420
follows: 0x00000010:264 0x00000011:198 0x00000012:114 0x00000100:467 0x00000200:896
said: 1 | **ENTWIN** t_ms:26217654 stream:0x3c4214c9 wall:0 window_ms:599999 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689
said: 9 | **COVERED** windows:1 entities:7 window_ms:600002 first_t_ms:25617655 last_t_ms:25617655 covered_by:@LAT103LON8340
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41 windows:1
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
```

---

@LAT105LON1272 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 25600740 ±21 frame:7000
seq: 256
follows: 0x00000011:189 0x00000012:103 0x00000100:458 0x00000200:887 0x00000300:2399
said: 1 | **LINKWIN** t_ms:25655918 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:85 rssi_min:-76 rssi_med:-68 rssi_max:-59
said: 3 | **LINK** peer:0x00000100 proto:espnow n:25 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:77 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000012 proto:espnow n:81 rssi_min:-61 rssi_med:-59 rssi_max:-58
said: 6 | **LINK** peer:0x00000300 proto:ble n:86 rssi_min:-80 rssi_med:-38 rssi_max:-37
said: 7 | **LINK** peer:0x00000011 proto:ble n:78 rssi_min:-79 rssi_med:-55 rssi_max:-45
said: 8 | **LINK** peer:0x00000200 proto:ble n:87 rssi_min:-64 rssi_med:-64 rssi_max:-62
said: 9 | **LINK** peer:0x00000200 proto:espnow n:67 rssi_min:-53 rssi_med:-52 rssi_max:-52
```

---

@LAT105LON1273 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 26065561 ±21 frame:7000
seq: 112
follows: 0x00000010:263 0x00000011:196 0x00000100:466 0x00000200:895 0x00000300:2415
said: 1 | **LINKWIN** t_ms:26136772 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-36 rssi_max:-32
said: 3 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-51 rssi_max:-49
said: 4 | **LINK** peer:0x00000200 proto:espnow n:124 rssi_min:-72 rssi_med:-53 rssi_max:-51
said: 5 | **LINK** peer:0x00000300 proto:espnow n:138 rssi_min:-24 rssi_med:-21 rssi_max:-21
said: 6 | **LINK** peer:0x00000011 proto:ble n:47 rssi_min:-60 rssi_med:-51 rssi_max:-49
said: 7 | **LINK** peer:0x00000100 proto:espnow n:71 rssi_min:-58 rssi_med:-39 rssi_max:-35
said: 8 | **LINK** peer:0x00000011 proto:espnow n:56 rssi_min:-42 rssi_med:-40 rssi_max:-34
said: 9 | **LINK** peer:0x00000010 proto:espnow n:126 rssi_min:-44 rssi_med:-39 rssi_max:-34
```

---

@LAT105LON1274 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 26154603 ±21 frame:7000
seq: 897
follows: 0x00000010:265 0x00000011:199 0x00000012:114 0x00000100:467 0x00000300:2420
said: 1 | **LINKWIN** t_ms:26225787 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:espnow n:140 rssi_min:-54 rssi_med:-42 rssi_max:-38
said: 4 | **LINK** peer:0x00000012 proto:espnow n:78 rssi_min:-61 rssi_med:-44 rssi_max:-37
said: 5 | **LINK** peer:0x00000010 proto:espnow n:125 rssi_min:-51 rssi_med:-44 rssi_max:-41
said: 6 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-86 rssi_med:-58 rssi_max:-50
said: 7 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-58 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-79 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-87 rssi_med:-67 rssi_max:-52
```

---

@LAT103LON1961 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26197211 ±0 frame:7000
seq: 2421
follows: 0x00000010:265 0x00000011:199 0x00000012:115 0x00000100:468 0x00000200:897
said: 1 | **LINKWIN** t_ms:26268423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:91 rssi_min:-58 rssi_med:-48 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:espnow n:140 rssi_min:-52 rssi_med:-48 rssi_max:-45
said: 4 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-42 rssi_max:-37
said: 5 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-63 rssi_max:-51
said: 6 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-79 rssi_med:-62 rssi_max:-58
said: 7 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-66 rssi_med:-50 rssi_max:-41
said: 8 | **LINK** peer:0x00000011 proto:espnow n:96 rssi_min:-27 rssi_med:-24 rssi_max:-23
said: 9 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-62 rssi_med:-52 rssi_max:-41
said: 10 | 0x00000012 espnow violated predicted:-36 observed:-48
percept: 10 | 0x00000012 | link_stable | espnow | - | -
said: 11 | 0x00000010 ble met predicted:-60 observed:-63
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-49 observed:-50
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow violated predicted:-32 observed:-24
percept: 13 | 0x00000011 | link_stable | espnow | - | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-48
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow violated predicted:-45 observed:-52
percept: 15 | 0x00000010 | link_stable | espnow | - | -
said: 16 | 0x00000200 ble met predicted:-61 observed:-62
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 ble unobserved predicted:-53 observed:-53
percept: 17 | 0x00000012 | link_stable | ble | ? | -
```

---

@LAT103LON26328 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 26197211 ±0 frame:7000
seq: 2422
follows: 0x00000010:265 0x00000011:199 0x00000012:115 0x00000100:468 0x00000200:897
said: 1 | **ACOUSTICWIN** t_ms:26268423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3668 rate:8000
said: 2 | **ACOUSTIC** rms_mean:75 rms_max:2546 peak:7505 transients:3
said: 3 | **TRANSIENT** t_ms:26232562 stream:0x3c4214c9 wall:0 rms:2546
```

---

@LAT105LON1275 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 26082869 ±21 frame:7000
seq: 197
follows: 0x00000010:264 0x00000012:112 0x00000100:466 0x00000200:895 0x00000300:2417
said: 1 | **LINKWIN** t_ms:26154052 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-61 rssi_med:-59 rssi_max:-58
said: 3 | **LINK** peer:0x00000200 proto:ble n:47 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000012 proto:ble n:49 rssi_min:-81 rssi_med:-52 rssi_max:-51
said: 6 | **LINK** peer:0x00000300 proto:espnow n:84 rssi_min:-40 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000010 proto:espnow n:124 rssi_min:-22 rssi_med:-19 rssi_max:-18
said: 8 | **LINK** peer:0x00000012 proto:espnow n:46 rssi_min:-87 rssi_med:-41 rssi_max:-41
said: 9 | **LINK** peer:0x00000010 proto:ble n:46 rssi_min:-81 rssi_med:-33 rssi_max:-29
```

---

@LAT105LON1276 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 26214604 ±21 frame:7000
seq: 898
follows: 0x00000010:266 0x00000011:200 0x00000012:115 0x00000100:468 0x00000300:2422
said: 1 | **LINKWIN** t_ms:26285787 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-46 rssi_med:-41 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:espnow n:181 rssi_min:-49 rssi_med:-44 rssi_max:-42
said: 5 | **LINK** peer:0x00000011 proto:espnow n:148 rssi_min:-61 rssi_med:-51 rssi_max:-46
said: 6 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-58 rssi_max:-54
said: 7 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-85 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000010 proto:espnow n:138 rssi_min:-51 rssi_med:-46 rssi_max:-41
said: 9 | **LINK** peer:0x00000012 proto:ble n:51 rssi_min:-79 rssi_med:-56 rssi_max:-51
```

---

@LAT103LON1962 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26257211 ±0 frame:7000
seq: 2423
follows: 0x00000010:266 0x00000011:200 0x00000012:115 0x00000100:469 0x00000200:898
said: 1 | **LINKWIN** t_ms:26328423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:68 rssi_min:-60 rssi_med:-47 rssi_max:-38
said: 3 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-67 rssi_med:-61 rssi_max:-56
said: 4 | **LINK** peer:0x00000200 proto:espnow n:146 rssi_min:-53 rssi_med:-49 rssi_max:-47
said: 5 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-71 rssi_med:-61 rssi_max:-58
said: 6 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-60 rssi_med:-52 rssi_max:-49
said: 7 | **LINK** peer:0x00000011 proto:espnow n:139 rssi_min:-27 rssi_med:-27 rssi_max:-24
said: 8 | **LINK** peer:0x00000012 proto:ble n:47 rssi_min:-67 rssi_med:-59 rssi_max:-51
said: 9 | **LINK** peer:0x00000010 proto:espnow n:104 rssi_min:-60 rssi_med:-50 rssi_max:-43
said: 10 | 0x00000012 espnow met predicted:-48 observed:-47
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-48 observed:-49
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000011 ble unobserved predicted:-42 observed:-42
percept: 12 | 0x00000011 | link_stable | ble | ? | -
said: 13 | 0x00000010 ble met predicted:-63 observed:-61
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000200 ble met predicted:-62 observed:-61
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000100 espnow met predicted:-50 observed:-52
percept: 15 | 0x00000100 | link_stable | espnow | + | -
said: 16 | 0x00000011 espnow met predicted:-24 observed:-27
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000010 espnow met predicted:-52 observed:-50
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON26329 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 26257211 ±0 frame:7000
seq: 2424
follows: 0x00000010:266 0x00000011:200 0x00000012:115 0x00000100:469 0x00000200:898
said: 1 | **ACOUSTICWIN** t_ms:26328423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3463 rate:8000
said: 2 | **ACOUSTIC** rms_mean:67 rms_max:386 peak:898 transients:0
```

---

@LAT105LON1277 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 26142768 ±21 frame:7000
seq: 199
follows: 0x00000010:264 0x00000012:114 0x00000100:467 0x00000200:896 0x00000300:2419
said: 1 | **LINKWIN** t_ms:26214072 stream:0x3c4214c9 wall:0 window_ms:60020
said: 2 | **LINK** peer:0x00000300 proto:espnow n:119 rssi_min:-45 rssi_med:-25 rssi_max:-16
said: 3 | **LINK** peer:0x00000010 proto:espnow n:96 rssi_min:-52 rssi_med:-42 rssi_max:-18
said: 4 | **LINK** peer:0x00000200 proto:espnow n:107 rssi_min:-66 rssi_med:-55 rssi_max:-42
said: 5 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-82 rssi_med:-58 rssi_max:-34
said: 6 | **LINK** peer:0x00000300 proto:ble n:67 rssi_min:-81 rssi_med:-40 rssi_max:-30
said: 7 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-55 rssi_med:-42 rssi_max:-20
said: 8 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-60 rssi_med:-45 rssi_max:-35
said: 9 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-88 rssi_med:-65 rssi_max:-51
```

---

@LAT105LON1278 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 26202890 ±21 frame:7000
seq: 200
follows: 0x00000010:266 0x00000012:115 0x00000100:468 0x00000200:897 0x00000300:2422
said: 1 | **LINKWIN** t_ms:26274072 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-57 rssi_max:-49
said: 3 | **LINK** peer:0x00000012 proto:espnow n:116 rssi_min:-48 rssi_med:-39 rssi_max:-34
said: 4 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-45 rssi_med:-41 rssi_max:-35
said: 5 | **LINK** peer:0x00000200 proto:espnow n:119 rssi_min:-64 rssi_med:-58 rssi_max:-50
said: 6 | **LINK** peer:0x00000010 proto:espnow n:129 rssi_min:-52 rssi_med:-46 rssi_max:-43
said: 7 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-82 rssi_med:-56 rssi_max:-49
said: 8 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-81 rssi_med:-34 rssi_max:-30
said: 9 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-81 rssi_med:-69 rssi_max:-62
```

---

@LAT105LON1279 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 26274605 ±21 frame:7000
seq: 899
follows: 0x00000010:267 0x00000011:201 0x00000012:115 0x00000100:469 0x00000300:2424
said: 1 | **LINKWIN** t_ms:26345787 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-76 rssi_med:-65 rssi_max:-61
said: 3 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-36 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000300 proto:espnow n:191 rssi_min:-60 rssi_med:-45 rssi_max:-43
said: 5 | **LINK** peer:0x00000011 proto:espnow n:162 rssi_min:-58 rssi_med:-51 rssi_max:-48
said: 6 | **LINK** peer:0x00000010 proto:espnow n:122 rssi_min:-50 rssi_med:-44 rssi_max:-41
said: 7 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-59 rssi_max:-56
said: 8 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-59 rssi_max:-55
said: 9 | **LINK** peer:0x00000012 proto:ble n:50 rssi_min:-82 rssi_med:-55 rssi_max:-52
```

---

@LAT103LON1963 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26317211 ±0 frame:7000
seq: 2425
follows: 0x00000010:267 0x00000011:201 0x00000012:117 0x00000100:470 0x00000200:899
said: 1 | **LINKWIN** t_ms:26388423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:78 rssi_min:-55 rssi_med:-45 rssi_max:-43
said: 3 | **LINK** peer:0x00000011 proto:espnow n:152 rssi_min:-27 rssi_med:-25 rssi_max:-24
said: 4 | **LINK** peer:0x00000200 proto:espnow n:101 rssi_min:-64 rssi_med:-51 rssi_max:-47
said: 5 | **LINK** peer:0x00000010 proto:espnow n:139 rssi_min:-59 rssi_med:-46 rssi_max:-41
said: 6 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-50 rssi_med:-40 rssi_max:-38
said: 7 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-49 rssi_med:-41 rssi_max:-37
said: 8 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-67 rssi_max:-60
said: 9 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-57 rssi_med:-55 rssi_max:-51
said: 10 | 0x00000012 espnow met predicted:-47 observed:-41
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000010 ble unobserved predicted:-61 observed:-61
percept: 11 | 0x00000010 | link_stable | ble | ? | -
said: 12 | 0x00000200 espnow met predicted:-49 observed:-51
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-61 observed:-67
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow violated predicted:-52 observed:-45
percept: 14 | 0x00000100 | link_stable | espnow | - | -
said: 15 | 0x00000011 espnow met predicted:-27 observed:-25
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-59 observed:-55
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-50 observed:-46
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON26330 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 26317211 ±0 frame:7000
seq: 2426
follows: 0x00000010:267 0x00000011:201 0x00000012:117 0x00000100:470 0x00000200:899
said: 1 | **ACOUSTICWIN** t_ms:26388423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3673 rate:8000
said: 2 | **ACOUSTIC** rms_mean:70 rms_max:294 peak:1055 transients:0
```

---

@LAT105LON1280 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 26262912 ±21 frame:7000
seq: 201
follows: 0x00000010:267 0x00000012:115 0x00000100:469 0x00000200:898 0x00000300:2424
said: 1 | **LINKWIN** t_ms:26334093 stream:0x3c4214c9 wall:0 window_ms:60021
said: 2 | **LINK** peer:0x00000012 proto:espnow n:60 rssi_min:-46 rssi_med:-36 rssi_max:-32
said: 3 | **LINK** peer:0x00000010 proto:espnow n:83 rssi_min:-50 rssi_med:-45 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:espnow n:174 rssi_min:-21 rssi_med:-20 rssi_max:-16
said: 5 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-52 rssi_med:-43 rssi_max:-35
said: 6 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-34 rssi_max:-30
said: 7 | **LINK** peer:0x00000200 proto:espnow n:184 rssi_min:-62 rssi_med:-55 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-50
said: 9 | **LINK** peer:0x00000012 proto:ble n:47 rssi_min:-82 rssi_med:-54 rssi_max:-47
```

---

@LAT105LON1281 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 25660740 ±21 frame:7000
seq: 257
follows: 0x00000011:190 0x00000012:104 0x00000100:459 0x00000200:888 0x00000300:2401
said: 1 | **LINKWIN** t_ms:25731917 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:27 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:ble n:94 rssi_min:-42 rssi_med:-38 rssi_max:-37
said: 4 | **LINK** peer:0x00000011 proto:ble n:84 rssi_min:-82 rssi_med:-55 rssi_max:-45
said: 5 | **LINK** peer:0x00000200 proto:espnow n:94 rssi_min:-54 rssi_med:-52 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:espnow n:129 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 7 | **LINK** peer:0x00000200 proto:ble n:86 rssi_min:-81 rssi_med:-64 rssi_max:-62
said: 8 | **LINK** peer:0x00000012 proto:ble n:87 rssi_min:-73 rssi_med:-68 rssi_max:-59
said: 9 | **LINK** peer:0x00000011 proto:espnow n:47 rssi_min:-48 rssi_med:-47 rssi_max:-46
```

---

@LAT105LON1282 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 26322928 ±21 frame:7000
seq: 202
follows: 0x00000010:268 0x00000012:117 0x00000100:470 0x00000200:899 0x00000300:2426
said: 1 | **LINKWIN** t_ms:26394109 stream:0x3c4214c9 wall:0 window_ms:60016
said: 2 | **LINK** peer:0x00000200 proto:espnow n:89 rssi_min:-59 rssi_med:-56 rssi_max:-54
said: 3 | **LINK** peer:0x00000100 proto:espnow n:83 rssi_min:-52 rssi_med:-49 rssi_max:-45
said: 4 | **LINK** peer:0x00000300 proto:espnow n:197 rssi_min:-21 rssi_med:-17 rssi_max:-16
said: 5 | **LINK** peer:0x00000012 proto:espnow n:74 rssi_min:-43 rssi_med:-42 rssi_max:-34
said: 6 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-54 rssi_max:-50
said: 7 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-32 rssi_max:-30
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-71 rssi_max:-67
said: 9 | **LINK** peer:0x00000010 proto:espnow n:151 rssi_min:-47 rssi_med:-42 rssi_max:-35
```

---

@LAT105LON1283 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 26125596 ±21 frame:7000
seq: 113
follows: 0x00000010:264 0x00000011:198 0x00000100:467 0x00000200:896 0x00000300:2417
said: 1 | **LINKWIN** t_ms:26196807 stream:0x3c4214c9 wall:0 window_ms:60035
said: 2 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-80 rssi_med:-55 rssi_max:-34
said: 3 | **LINK** peer:0x00000011 proto:espnow n:86 rssi_min:-69 rssi_med:-41 rssi_max:-20
said: 4 | **LINK** peer:0x00000300 proto:espnow n:157 rssi_min:-50 rssi_med:-22 rssi_max:-19
said: 5 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-54 rssi_med:-39 rssi_max:-32
said: 6 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-41 rssi_max:-34
said: 7 | **LINK** peer:0x00000200 proto:espnow n:144 rssi_min:-69 rssi_med:-52 rssi_max:-35
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-79 rssi_med:-51 rssi_max:-30
said: 9 | **LINK** peer:0x00000010 proto:espnow n:176 rssi_min:-70 rssi_med:-39 rssi_max:-17
```

---

@LAT105LON1284 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 26185597 ±21 frame:7000
seq: 115
follows: 0x00000010:265 0x00000011:199 0x00000100:468 0x00000200:897 0x00000300:2420
said: 1 | **LINKWIN** t_ms:26256807 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-56 rssi_max:-49
said: 3 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-50 rssi_med:-41 rssi_max:-33
said: 4 | **LINK** peer:0x00000200 proto:espnow n:125 rssi_min:-48 rssi_med:-43 rssi_max:-34
said: 5 | **LINK** peer:0x00000011 proto:espnow n:92 rssi_min:-50 rssi_med:-41 rssi_max:-34
said: 6 | **LINK** peer:0x00000300 proto:espnow n:172 rssi_min:-57 rssi_med:-46 rssi_max:-30
said: 7 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-80 rssi_med:-54 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-32 rssi_max:-29
said: 9 | **LINK** peer:0x00000010 proto:espnow n:83 rssi_min:-22 rssi_med:-19 rssi_max:-17
```

---

@LAT103LON1964 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26377211 ±0 frame:7000
seq: 2427
follows: 0x00000010:269 0x00000011:202 0x00000012:118 0x00000100:471 0x00000200:900
said: 1 | **LINKWIN** t_ms:26448423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-49 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-54 rssi_med:-49 rssi_max:-46
said: 4 | **LINK** peer:0x00000011 proto:espnow n:117 rssi_min:-26 rssi_med:-24 rssi_max:-23
said: 5 | **LINK** peer:0x00000012 proto:espnow n:73 rssi_min:-49 rssi_med:-40 rssi_max:-36
said: 6 | **LINK** peer:0x00000010 proto:ble n:48 rssi_min:-70 rssi_med:-61 rssi_max:-54
said: 7 | **LINK** peer:0x00000010 proto:espnow n:105 rssi_min:-52 rssi_med:-49 rssi_max:-44
said: 8 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-80 rssi_med:-39 rssi_max:-38
said: 9 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-63 rssi_max:-57
said: 10 | 0x00000100 espnow met predicted:-45 observed:-44
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-25 observed:-24
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-51 observed:-49
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-46 observed:-49
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-40 observed:-39
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000012 espnow met predicted:-41 observed:-40
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-67 observed:-63
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 ble unobserved predicted:-55 observed:-55
percept: 17 | 0x00000012 | link_stable | ble | ? | -
```

---

@LAT103LON26331 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 26377211 ±0 frame:7000
seq: 2428
follows: 0x00000010:269 0x00000011:202 0x00000012:118 0x00000100:471 0x00000200:900
said: 1 | **ACOUSTICWIN** t_ms:26448423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3452 rate:8000
said: 2 | **ACOUSTIC** rms_mean:74 rms_max:2786 peak:5850 transients:4
said: 3 | **TRANSIENT** t_ms:26413780 stream:0x3c4214c9 wall:0 rms:2786
```

---

@LAT105LON1285 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 26334606 ±21 frame:7000
seq: 900
follows: 0x00000010:268 0x00000011:202 0x00000012:117 0x00000100:470 0x00000300:2426
said: 1 | **LINKWIN** t_ms:26405787 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-86 rssi_med:-59 rssi_max:-58
said: 3 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 4 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 5 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-48 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-63 rssi_max:-57
said: 7 | **LINK** peer:0x00000100 proto:espnow n:76 rssi_min:-34 rssi_med:-33 rssi_max:-33
said: 8 | **LINK** peer:0x00000300 proto:espnow n:209 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 9 | **LINK** peer:0x00000011 proto:espnow n:118 rssi_min:-54 rssi_med:-52 rssi_max:-50
```

---

@LAT105LON1286 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 26382927 ±21 frame:7000
seq: 203
follows: 0x00000010:270 0x00000012:118 0x00000100:471 0x00000200:900 0x00000300:2428
said: 1 | **LINKWIN** t_ms:26454108 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:129 rssi_min:-60 rssi_med:-56 rssi_max:-53
said: 3 | **LINK** peer:0x00000012 proto:espnow n:63 rssi_min:-55 rssi_med:-43 rssi_max:-38
said: 4 | **LINK** peer:0x00000010 proto:espnow n:72 rssi_min:-49 rssi_med:-45 rssi_max:-42
said: 5 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-82 rssi_med:-57 rssi_max:-50
said: 6 | **LINK** peer:0x00000300 proto:espnow n:226 rssi_min:-20 rssi_med:-17 rssi_max:-16
said: 7 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-32 rssi_max:-30
said: 8 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-55 rssi_med:-49 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-71 rssi_max:-63
```

---

@LAT103LON1965 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26437211 ±0 frame:7000
seq: 2429
follows: 0x00000010:270 0x00000011:203 0x00000012:119 0x00000100:472 0x00000200:901
said: 1 | **LINKWIN** t_ms:26508423 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-68 rssi_med:-59 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:espnow n:87 rssi_min:-56 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000011 proto:espnow n:86 rssi_min:-27 rssi_med:-24 rssi_max:-24
said: 5 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-58 rssi_med:-46 rssi_max:-44
said: 6 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-72 rssi_med:-63 rssi_max:-57
said: 7 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-47 rssi_med:-41 rssi_max:-38
said: 8 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:espnow n:69 rssi_min:-51 rssi_med:-42 rssi_max:-37
said: 10 | 0x00000100 espnow met predicted:-44 observed:-46
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-49 observed:-48
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-24 observed:-24
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-40 observed:-42
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000010 ble met predicted:-61 observed:-59
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow unobserved predicted:-49 observed:-49
percept: 15 | 0x00000010 | link_stable | espnow | ? | -
said: 16 | 0x00000011 ble met predicted:-39 observed:-41
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-63 observed:-63
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT104LON426 | created:0 | updated:0

**carried through @LAT103LON1925**

```ttdb-carried
through: 1925
through: 8299
through: 16455
through: 26312
carried: 1276 20 1495 1223 | 0x00000200 | link_stable | espnow
carried: 1341 15 1712 1232 | 0x00000200 | link_stable | ble
carried: 668 6 1027 548 | 0x00000100 | link_stable | espnow
carried: 671 11 1036 553 | 0x00000010 | link_stable | ble
carried: 631 19 1003 531 | 0x00000010 | link_stable | espnow
carried: 193 2 195 204 | 0x00000011 | link_stable | ble
carried: 194 7 201 207 | 0x00000011 | link_stable | espnow
carried: 126 2 128 132 | 0x00000012 | link_stable | ble
carried: 120 2 122 127 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON26332 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 26437211 ±0 frame:7000
seq: 2430
follows: 0x00000010:270 0x00000011:203 0x00000012:119 0x00000100:472 0x00000200:901
said: 1 | **ACOUSTICWIN** t_ms:26508423 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3701 rate:8000
said: 2 | **ACOUSTIC** rms_mean:124 rms_max:7027 peak:18398 transients:18
said: 3 | **TRANSIENT** t_ms:26504664 stream:0x3c4214c9 wall:0 rms:7027
```

---

@LAT105LON1287 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 26286723 ±21 frame:7000
seq: 116
follows: 0x00000010:267 0x00000011:201 0x00000100:469 0x00000200:898 0x00000300:2424
said: 1 | **LINKWIN** t_ms:26357893 stream:0x3c4214c9 wall:0 window_ms:72040
said: 2 | **LINK** peer:0x00000200 proto:espnow n:145 rssi_min:-45 rssi_med:-40 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:150 rssi_min:-46 rssi_med:-39 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:espnow n:146 rssi_min:-47 rssi_med:-40 rssi_max:-33
said: 5 | **LINK** peer:0x00000100 proto:espnow n:79 rssi_min:-54 rssi_med:-41 rssi_max:-30
said: 6 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-80 rssi_med:-50 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-33 rssi_max:-29
said: 8 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-80 rssi_med:-52 rssi_max:-48
said: 9 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-80 rssi_med:-52 rssi_max:-48
```

---

@LAT105LON1288 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 26394620 ±21 frame:7000
seq: 901
follows: 0x00000010:270 0x00000011:203 0x00000012:118 0x00000100:471 0x00000300:2428
said: 1 | **LINKWIN** t_ms:26465800 stream:0x3c4214c9 wall:0 window_ms:60013
said: 2 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-36 rssi_med:-34 rssi_max:-32
said: 3 | **LINK** peer:0x00000300 proto:espnow n:206 rssi_min:-52 rssi_med:-45 rssi_max:-43
said: 4 | **LINK** peer:0x00000012 proto:espnow n:67 rssi_min:-49 rssi_med:-40 rssi_max:-38
said: 5 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-62 rssi_med:-55 rssi_max:-51
said: 6 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-68 rssi_max:-63
said: 7 | **LINK** peer:0x00000011 proto:espnow n:111 rssi_min:-55 rssi_med:-51 rssi_max:-49
said: 8 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-60 rssi_max:-54
said: 9 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-60 rssi_max:-53
```

---

@LAT105LON1289 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 26442930 ±21 frame:7000
seq: 204
follows: 0x00000010:270 0x00000012:119 0x00000100:472 0x00000200:901 0x00000300:2430
said: 1 | **LINKWIN** t_ms:26514109 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-60 rssi_med:-53 rssi_max:-41
said: 3 | **LINK** peer:0x00000300 proto:espnow n:159 rssi_min:-24 rssi_med:-17 rssi_max:-16
said: 4 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-33 rssi_max:-22
said: 5 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-55 rssi_max:-48
said: 6 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-67 rssi_max:-57
said: 7 | **LINK** peer:0x00000010 proto:espnow n:77 rssi_min:-78 rssi_med:-45 rssi_max:-40
said: 8 | **LINK** peer:0x00000200 proto:espnow n:78 rssi_min:-62 rssi_med:-55 rssi_max:-44
said: 9 | **LINK** peer:0x00000012 proto:espnow n:61 rssi_min:-61 rssi_med:-43 rssi_max:-40
```

---

@LAT105LON1290 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 26348750 ±21 frame:7000
seq: 118
follows: 0x00000010:268 0x00000011:202 0x00000100:470 0x00000200:900 0x00000300:2426
said: 1 | **LINKWIN** t_ms:26419921 stream:0x3c4214c9 wall:0 window_ms:62027
said: 2 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 3 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-33 rssi_max:-28
said: 4 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-39 rssi_med:-34 rssi_max:-31
said: 5 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-52 rssi_max:-49
said: 6 | **LINK** peer:0x00000011 proto:espnow n:114 rssi_min:-44 rssi_med:-42 rssi_max:-35
said: 7 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-47 rssi_max:-47
said: 8 | **LINK** peer:0x00000300 proto:espnow n:250 rssi_min:-46 rssi_med:-38 rssi_max:-31
said: 9 | **LINK** peer:0x00000200 proto:espnow n:98 rssi_min:-42 rssi_med:-40 rssi_max:-34
```

---

@LAT105LON1291 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 26408774 ±21 frame:7000
seq: 119
follows: 0x00000010:270 0x00000011:203 0x00000100:471 0x00000200:901 0x00000300:2428
said: 1 | **LINKWIN** t_ms:26479945 stream:0x3c4214c9 wall:0 window_ms:60025
said: 2 | **LINK** peer:0x00000200 proto:espnow n:111 rssi_min:-53 rssi_med:-41 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-49
said: 4 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-53 rssi_max:-43
said: 5 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-60 rssi_max:-53
said: 6 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-52 rssi_med:-42 rssi_max:-30
said: 7 | **LINK** peer:0x00000010 proto:espnow n:99 rssi_min:-22 rssi_med:-19 rssi_max:-17
said: 8 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-79 rssi_med:-32 rssi_max:-29
said: 9 | **LINK** peer:0x00000300 proto:espnow n:168 rssi_min:-51 rssi_med:-45 rssi_max:-29
```

---

@LAT105LON1292 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 26468802 ±21 frame:7000
seq: 120
follows: 0x00000010:271 0x00000011:204 0x00000100:472 0x00000200:901 0x00000300:2430
said: 1 | **LINKWIN** t_ms:26539972 stream:0x3c4214c9 wall:0 window_ms:60026
said: 2 | **LINK** peer:0x00000010 proto:espnow n:82 rssi_min:-21 rssi_med:-19 rssi_max:-17
said: 3 | **LINK** peer:0x00000300 proto:espnow n:158 rssi_min:-61 rssi_med:-41 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-54 rssi_max:-48
said: 5 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-55 rssi_max:-51
said: 6 | **LINK** peer:0x00000100 proto:espnow n:75 rssi_min:-53 rssi_med:-43 rssi_max:-32
said: 7 | **LINK** peer:0x00000011 proto:espnow n:132 rssi_min:-53 rssi_med:-41 rssi_max:-36
said: 8 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-52 rssi_max:-44
said: 9 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-32 rssi_max:-29
```

---

@LAT103LON1966 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26499468 ±0 frame:7000
seq: 2431
follows: 0x00000010:271 0x00000011:204 0x00000012:120 0x00000100:473 0x00000200:902
said: 1 | **LINKWIN** t_ms:26570680 stream:0x3c4214c9 wall:0 window_ms:62257
said: 2 | **LINK** peer:0x00000100 proto:espnow n:86 rssi_min:-56 rssi_med:-47 rssi_max:-40
said: 3 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-72 rssi_med:-40 rssi_max:-31
said: 4 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-67 rssi_max:-55
said: 5 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-70 rssi_med:-55 rssi_max:-51
said: 6 | **LINK** peer:0x00000011 proto:espnow n:119 rssi_min:-63 rssi_med:-24 rssi_max:-15
said: 7 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-73 rssi_med:-59 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:espnow n:97 rssi_min:-59 rssi_med:-42 rssi_max:-38
said: 9 | **LINK** peer:0x00000200 proto:espnow n:121 rssi_min:-75 rssi_med:-55 rssi_max:-38
said: 10 | 0x00000010 ble met predicted:-59 observed:-55
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow violated predicted:-48 observed:-55
percept: 11 | 0x00000200 | link_stable | espnow | - | -
said: 12 | 0x00000011 espnow met predicted:-24 observed:-24
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-46 observed:-47
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-63 observed:-67
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000011 ble met predicted:-41 observed:-40
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-59
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000012 espnow unobserved predicted:-42 observed:-42
percept: 17 | 0x00000012 | link_stable | espnow | ? | -
```

---

@LAT103LON26333 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 26499468 ±0 frame:7000
seq: 2432
follows: 0x00000010:271 0x00000011:204 0x00000012:120 0x00000100:473 0x00000200:902
said: 1 | **ACOUSTICWIN** t_ms:26570680 stream:0x3c4214c9 wall:0 window_ms:62257 blocks:3092 rate:8000
said: 2 | **ACOUSTIC** rms_mean:194 rms_max:14073 peak:32768 transients:30
said: 3 | **TRANSIENT** t_ms:26513577 stream:0x3c4214c9 wall:0 rms:14073
```

---

@LAT105LON1293 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 26502930 ±21 frame:7000
seq: 205
follows: 0x00000010:271 0x00000012:120 0x00000100:473 0x00000200:902 0x00000300:2432
said: 1 | **LINKWIN** t_ms:26574109 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:70 rssi_min:-81 rssi_med:-56 rssi_max:-51
said: 3 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-62 rssi_med:-51 rssi_max:-43
said: 4 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-81 rssi_med:-67 rssi_max:-59
said: 5 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-72 rssi_med:-32 rssi_max:-28
said: 6 | **LINK** peer:0x00000300 proto:espnow n:146 rssi_min:-60 rssi_med:-16 rssi_max:-14
said: 7 | **LINK** peer:0x00000012 proto:espnow n:97 rssi_min:-53 rssi_med:-42 rssi_max:-35
said: 8 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-55 rssi_med:-42 rssi_max:-35
said: 9 | **LINK** peer:0x00000200 proto:espnow n:113 rssi_min:-73 rssi_med:-55 rssi_max:-46
```

---

@LAT105LON1294 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 26454622 ±21 frame:7000
seq: 902
follows: 0x00000010:271 0x00000011:204 0x00000012:119 0x00000100:472 0x00000300:2430
said: 1 | **LINKWIN** t_ms:26525801 stream:0x3c4214c9 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000010 proto:espnow n:71 rssi_min:-48 rssi_med:-45 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-36 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000300 proto:espnow n:154 rssi_min:-63 rssi_med:-47 rssi_max:-40
said: 5 | **LINK** peer:0x00000012 proto:espnow n:58 rssi_min:-45 rssi_med:-41 rssi_max:-39
said: 6 | **LINK** peer:0x00000011 proto:espnow n:89 rssi_min:-61 rssi_med:-50 rssi_max:-45
said: 7 | **LINK** peer:0x00000010 proto:ble n:71 rssi_min:-67 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-83 rssi_med:-60 rssi_max:-53
said: 9 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-79 rssi_med:-55 rssi_max:-52
```
@LAT106LON72 | created:0 | updated:0

**BAR** frame:7000 bar:44 own:10 held:28 terms:9 digest:0x38a9a1d3 settled_ms:120000
**HOLDS** agent:0x00000011 n:9 lo:194 hi:203 sum:1787
**HOLDS** agent:0x00000012 n:9 lo:108 hi:118 sum:1012
**HOLDS** agent:0x00000200 n:10 lo:892 hi:901 sum:8965
**HOLDS** agent:0x00000300 n:10 lo:2408 hi:2427 sum:24174

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:39 last_ms:11931693
t_ms:26626791 stream:0x3c4214c9 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:249 half_life_ms:600000 reinforced:5 last_ms:11901074
t_ms:26626791 stream:0x3c4214c9 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:254 half_life_ms:600000 reinforced:10 last_ms:11926067
t_ms:26626791 stream:0x3c4214c9 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:22 last_ms:11930270
t_ms:26626791 stream:0x3c4214c9 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:21 last_ms:11931977
t_ms:26626791 stream:0x3c4214c9 wall:0

---

@LAT101LON5 | sid:499db878 | created:0 | updated:0 |
**PEER** node:0x00000001 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:26626791 stream:0x3c4214c9 wall:0

---

@LAT103LON1967 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 26559468 ±0 frame:7000
seq: 2433
follows: 0x00000010:272 0x00000011:205 0x00000012:121 0x00000100:474 0x00000200:902
said: 1 | **LINKWIN** t_ms:26630680 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-46 rssi_med:-37 rssi_max:-33
said: 3 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-65 rssi_med:-57 rssi_max:-53
said: 4 | **LINK** peer:0x00000011 proto:espnow n:102 rssi_min:-51 rssi_med:-42 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:espnow n:89 rssi_min:-52 rssi_med:-41 rssi_max:-37
said: 6 | **LINK** peer:0x00000012 proto:espnow n:71 rssi_min:-60 rssi_med:-37 rssi_max:-32
said: 7 | **LINK** peer:0x00000012 proto:ble n:71 rssi_min:-69 rssi_med:-54 rssi_max:-45
said: 8 | **LINK** peer:0x00000200 proto:ble n:38 rssi_min:-67 rssi_med:-55 rssi_max:-43
said: 9 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-79 rssi_med:-57 rssi_max:-52
said: 10 | 0x00000100 espnow violated predicted:-47 observed:-37
percept: 10 | 0x00000100 | link_stable | espnow | - | -
said: 11 | 0x00000011 ble violated predicted:-40 observed:-57
percept: 11 | 0x00000011 | link_stable | ble | - | -
said: 12 | 0x00000200 ble violated predicted:-67 observed:-55
percept: 12 | 0x00000200 | link_stable | ble | - | -
said: 13 | 0x00000010 ble met predicted:-55 observed:-57
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow violated predicted:-24 observed:-42
percept: 14 | 0x00000011 | link_stable | espnow | - | -
said: 15 | 0x00000012 ble met predicted:-59 observed:-54
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-42 observed:-41
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 espnow unobserved predicted:-55 observed:-55
percept: 17 | 0x00000200 | link_stable | espnow | ? | -
```

---

@LAT103LON26334 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 26559468 ±0 frame:7000
seq: 2434
follows: 0x00000010:272 0x00000011:205 0x00000012:121 0x00000100:474 0x00000200:902
said: 1 | **ACOUSTICWIN** t_ms:26630680 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:2582 rate:8000
said: 2 | **ACOUSTIC** rms_mean:239 rms_max:13350 peak:32768 transients:20
said: 3 | **TRANSIENT** t_ms:26625523 stream:0x3c4214c9 wall:0 rms:13350
```

---

@LAT105LON1295 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 26559088 ±21 frame:7000
seq: 206
follows: 0x00000010:273 0x00000012:121 0x00000100:474 0x00000200:902 0x00000300:2434
said: 1 | **LINKWIN** t_ms:26634109 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:69 rssi_min:-52 rssi_med:-20 rssi_max:-19
said: 3 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-48 rssi_med:-42 rssi_max:-34
said: 4 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-68 rssi_med:-56 rssi_max:-49
said: 5 | **LINK** peer:0x00000300 proto:espnow n:113 rssi_min:-62 rssi_med:-38 rssi_max:-32
said: 6 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-54 rssi_max:-45
said: 7 | **LINK** peer:0x00000200 proto:ble n:34 rssi_min:-81 rssi_med:-64 rssi_max:-55
said: 8 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-82 rssi_med:-44 rssi_max:-32
said: 9 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-54 rssi_max:-47
```
