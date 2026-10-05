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

@LAT103LON16475 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 26670284 ±214767 frame:7000
seq: 2436
follows: 0x00000010:272 0x00000011:205 0x00000012:121 0x00000100:474 0x00000200:902
said: 1 | **MOTIONWIN** t_ms:26743222 stream:0x3c4214c9 wall:0 window_ms:71649 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8342 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 26734059 ±0 frame:7000
seq: 2439
follows: 0x00000010:274 0x00000011:207 0x00000012:122 0x00000100:476 0x00000200:905
said: 1 | **ENTWIN** t_ms:26806530 stream:0x3c4214c9 wall:0 window_ms:135424 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8343 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 27974675 ±214769 frame:7000
seq: 2474
follows: 0x00000010:298 0x00000011:232 0x00000012:146 0x00000100:500 0x00000200:928
said: 1 | **ENTWIN** t_ms:28090017 stream:0x3c4214c9 wall:0 window_ms:63066 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON16476 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 27974675 ±214769 frame:7000
seq: 2475
follows: 0x00000010:298 0x00000011:232 0x00000012:146 0x00000100:500 0x00000200:928
said: 1 | **MOTIONWIN** t_ms:28090017 stream:0x3c4214c9 wall:0 window_ms:63066 n:454
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8344 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 29126283 ±0 frame:7000
seq: 2515
follows: 0x00000010:318 0x00000011:252 0x00000012:167 0x00000100:518 0x00000200:946
said: 1 | **ENTWIN** t_ms:29241625 stream:0x3c4214c9 wall:0 window_ms:599999 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 12 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-94
said: 13 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 14 | **CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d
said: 15 | **COVERED** windows:1 entities:8 window_ms:551609 first_t_ms:28641626 last_t_ms:28641626 covered_by:@LAT103LON8343
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-82 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-94 windows:1
```

---

@LAT103LON8345 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 29726283 ±0 frame:7000
seq: 2534
follows: 0x00000010:326 0x00000011:258 0x00000012:178 0x00000100:524 0x00000200:957
said: 1 | **ENTWIN** t_ms:29841625 stream:0x3c4214c9 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,e45e1b9f675a,5ce28c488e0c,64677217947d
```

---

@LAT103LON16477 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 29787192 ±0 frame:7000
seq: 2538
follows: 0x00000010:327 0x00000011:261 0x00000012:179 0x00000100:525 0x00000200:958
said: 1 | **MOTIONWIN** t_ms:29902534 stream:0x3c4214c9 wall:0 window_ms:60000 n:993
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:27 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:22686 window_ms:1752517 moving_permille:0 dev_mean_mg:11 dev_max_mg:368 moving_ms:1290 first_t_ms:28150495 last_t_ms:29842534 covered_by:@LAT103LON16476
```

---

@LAT103LON8346 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 30326283 ±0 frame:7000
seq: 2556
follows: 0x00000010:336 0x00000011:269 0x00000012:188 0x00000100:534 0x00000200:968
said: 1 | **ENTWIN** t_ms:30441625 stream:0x3c4214c9 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-51
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,e6b32d2cea8b,84a329c78fec,e45e1b9f675a,5ce28c488e0c
```

---

@LAT103LON8347 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 30926283 ±0 frame:7000
seq: 2577
follows: 0x00000010:347 0x00000011:280 0x00000012:197 0x00000100:545 0x00000200:979
said: 1 | **ENTWIN** t_ms:31041625 stream:0x3c4214c9 wall:0 window_ms:600000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-52
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 12 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-96
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,64677217947d,0283cce0e689,e45e1b9f675a,5ce28c488e0c,84a329c78fec
```

---

@LAT103LON16478 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 31595882 ±0 frame:7000
seq: 2601
follows: 0x00000010:359 0x00000011:292 0x00000012:210 0x00000100:558 0x00000200:990
said: 1 | **MOTIONWIN** t_ms:31711224 stream:0x3c4214c9 wall:0 window_ms:60000 n:989
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26883 window_ms:1748690 moving_permille:0 dev_mean_mg:11 dev_max_mg:50 moving_ms:0 first_t_ms:29962534 last_t_ms:31651224 covered_by:@LAT103LON16477
```

---

@LAT106LON81 | created:0 | updated:0

**BAR** frame:7000 bar:53 own:10 held:20 terms:9 digest:0xdcd835d4 settled_ms:120000
**HOLDS** agent:0x00000011 n:10 lo:286 hi:295 sum:2905
**HOLDS** agent:0x00000012 n:10 lo:204 hi:214 sum:2086
**HOLDS** agent:0x00000300 n:10 lo:2588 hi:2607 sum:25973

---

@LAT106LON82 | created:0 | updated:0

**BAR** frame:7000 bar:54 own:10 held:20 terms:9 digest:0xbef2590a settled_ms:120000
**HOLDS** agent:0x00000011 n:10 lo:296 hi:305 sum:3005
**HOLDS** agent:0x00000012 n:10 lo:215 hi:225 sum:2196
**HOLDS** agent:0x00000300 n:10 lo:2609 hi:2627 sum:26180

---

@LAT106LON83 | created:0 | updated:0

**BAR** frame:7000 bar:55 own:10 held:26 terms:9 digest:0x76530f7c settled_ms:120000
**HOLDS** agent:0x00000010 n:6 lo:376 hi:381 sum:2271
**HOLDS** agent:0x00000011 n:10 lo:306 hi:316 sum:3110
**HOLDS** agent:0x00000012 n:10 lo:226 hi:235 sum:2305
**HOLDS** agent:0x00000300 n:10 lo:2629 hi:2647 sum:26380

---

@LAT103LON16479 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 33395891 ±0 frame:7000
seq: 2662
follows: 0x00000010:392 0x00000011:323 0x00000012:242 0x00000100:590 0x00000200:1021
said: 1 | **MOTIONWIN** t_ms:33511233 stream:0x3c4214c9 wall:0 window_ms:60000 n:932
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26703 window_ms:1740009 moving_permille:0 dev_mean_mg:11 dev_max_mg:21 moving_ms:0 first_t_ms:31771224 last_t_ms:33451233 covered_by:@LAT103LON16478
```

---

@LAT106LON84 | created:0 | updated:0

**BAR** frame:7000 bar:56 own:10 held:22 terms:9 digest:0x9a5db3d8 settled_ms:120000
**HOLDS** agent:0x00000010 n:6 lo:391 hi:396 sum:2361
**HOLDS** agent:0x00000011 n:3 lo:324 hi:326 sum:975
**HOLDS** agent:0x00000012 n:5 lo:242 hi:246 sum:1220
**HOLDS** agent:0x00000200 n:8 lo:1015 hi:1023 sum:8153
**HOLDS** agent:0x00000300 n:10 lo:2649 hi:2668 sum:26583

---

@LAT103LON8348 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 33926286 ±0 frame:7000
seq: 2680
follows: 0x00000010:402 0x00000011:332 0x00000012:251 0x00000100:600 0x00000200:1030
said: 1 | **ENTWIN** t_ms:34041628 stream:0x3c4214c9 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-91
said: 10 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,bc102f237ace,0283cce0e689,e45e1b9f675a,5ce28c488e0c
said: 12 | **COVERED** windows:4 entities:12 window_ms:2400002 first_t_ms:31641626 last_t_ms:33441627 covered_by:@LAT103LON8347
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-50 windows:4
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-76 windows:4
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-78 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-80 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:4 rssi:-87 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-82 windows:4
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-88 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-86 windows:4
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-88 windows:4
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:e45e1b9f675a n:2 rssi:-90 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93 windows:1
```

---

@LAT106LON85 | created:0 | updated:0

**BAR** frame:7000 bar:57 own:10 held:39 terms:9 digest:0xfe7a10c4 settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:397 hi:407 sum:4023
**HOLDS** agent:0x00000011 n:9 lo:327 hi:337 sum:2984
**HOLDS** agent:0x00000012 n:10 lo:247 hi:256 sum:2515
**HOLDS** agent:0x00000200 n:10 lo:1026 hi:1035 sum:10305
**HOLDS** agent:0x00000300 n:10 lo:2670 hi:2689 sum:26795

---

@LAT106LON86 | created:0 | updated:0

**BAR** frame:7000 bar:58 own:10 held:32 terms:8 digest:0x687075bf settled_ms:120000
**HOLDS** agent:0x00000010 n:4 lo:408 hi:411 sum:1638
**HOLDS** agent:0x00000011 n:8 lo:338 hi:345 sum:2732
**HOLDS** agent:0x00000012 n:10 lo:257 hi:267 sum:2623
**HOLDS** agent:0x00000200 n:10 lo:1036 hi:1045 sum:10405
**HOLDS** agent:0x00000300 n:10 lo:2691 hi:2709 sum:27000

---

@LAT103LON8349 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 35126285 ±0 frame:7000
seq: 2721
follows: 0x00000010:423 0x00000011:352 0x00000012:273 0x00000100:622 0x00000200:1051
said: 1 | **ENTWIN** t_ms:35241627 stream:0x3c4214c9 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,e6b32d2cea8b,84a329c78fec,bc102f237ace,0283cce0e689,e45e1b9f675a
said: 13 | **COVERED** windows:1 entities:9 window_ms:599998 first_t_ms:34641626 last_t_ms:34641626 covered_by:@LAT103LON8348
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-94 windows:1
```

---

@LAT103LON16480 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 35197418 ±0 frame:7000
seq: 2725
follows: 0x00000010:424 0x00000011:354 0x00000012:274 0x00000100:623 0x00000200:1052
said: 1 | **MOTIONWIN** t_ms:35312760 stream:0x3c4214c9 wall:0 window_ms:60000 n:928
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27074 window_ms:1741527 moving_permille:0 dev_mean_mg:11 dev_max_mg:30 moving_ms:0 first_t_ms:33571233 last_t_ms:35252760 covered_by:@LAT103LON16479
```

---

@LAT106LON87 | created:0 | updated:0

**BAR** frame:7000 bar:59 own:10 held:30 terms:8 digest:0x687075bf settled_ms:120000
**HOLDS** agent:0x00000011 n:10 lo:348 hi:358 sum:3527
**HOLDS** agent:0x00000012 n:10 lo:268 hi:278 sum:2733
**HOLDS** agent:0x00000200 n:10 lo:1046 hi:1056 sum:10512
**HOLDS** agent:0x00000300 n:10 lo:2711 hi:2731 sum:27208

---

@LAT106LON88 | created:0 | updated:0

**BAR** frame:7000 bar:60 own:10 held:30 terms:8 digest:0x687075bf settled_ms:120000
**HOLDS** agent:0x00000011 n:10 lo:359 hi:369 sum:3637
**HOLDS** agent:0x00000012 n:10 lo:279 hi:289 sum:2843
**HOLDS** agent:0x00000200 n:10 lo:1057 hi:1066 sum:10615
**HOLDS** agent:0x00000300 n:10 lo:2733 hi:2751 sum:27420

---

@LAT103LON8350 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36326285 ±0 frame:7000
seq: 2763
follows: 0x00000010:444 0x00000011:374 0x00000012:294 0x00000100:644 0x00000200:1071
said: 1 | **ENTWIN** t_ms:36441627 stream:0x3c4214c9 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689,bc102f237ace,aef9ff2626ac,64677217947d,84a329c78fec,e45e1b9f675a
said: 12 | **COVERED** windows:1 entities:11 window_ms:599999 first_t_ms:35841626 last_t_ms:35841626 covered_by:@LAT103LON8349
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-91 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:dc4ba1e08b09 n:1 rssi:-95 windows:1
```

---

@LAT106LON89 | created:0 | updated:0

**BAR** frame:7000 bar:61 own:10 held:29 terms:8 digest:0x687075bf settled_ms:120000
**HOLDS** agent:0x00000011 n:9 lo:370 hi:378 sum:3366
**HOLDS** agent:0x00000012 n:10 lo:290 hi:299 sum:2945
**HOLDS** agent:0x00000200 n:10 lo:1067 hi:1076 sum:10715
**HOLDS** agent:0x00000300 n:10 lo:2753 hi:2772 sum:27625

---

@LAT103LON8351 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36926284 ±0 frame:7000
seq: 2784
follows: 0x00000010:455 0x00000011:384 0x00000012:305 0x00000100:655 0x00000200:1081
said: 1 | **ENTWIN** t_ms:37041626 stream:0x3c4214c9 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,e6b32d2cea8b,0283cce0e689,bc102f237ace,5ce28c488e0c,aef9ff2626ac,84a329c78fec
```

---

@LAT103LON16481 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 36997430 ±0 frame:7000
seq: 2788
follows: 0x00000010:456 0x00000011:386 0x00000012:306 0x00000100:656 0x00000200:1082
said: 1 | **MOTIONWIN** t_ms:37112772 stream:0x3c4214c9 wall:0 window_ms:60000 n:994
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27057 window_ms:1740012 moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0 first_t_ms:35372760 last_t_ms:37052772 covered_by:@LAT103LON16480
```

---

@LAT106LON90 | created:0 | updated:0

**BAR** frame:7000 bar:62 own:10 held:30 terms:9 digest:0x73c68450 settled_ms:121864
**HOLDS** agent:0x00000011 n:10 lo:380 hi:389 sum:3845
**HOLDS** agent:0x00000012 n:10 lo:300 hi:310 sum:3053
**HOLDS** agent:0x00000200 n:10 lo:1077 hi:1086 sum:10815
**HOLDS** agent:0x00000300 n:10 lo:2774 hi:2794 sum:27838

---

@LAT103LON8352 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 37526285 ±0 frame:7000
seq: 2806
follows: 0x00000010:465 0x00000011:394 0x00000012:316 0x00000100:665 0x00000200:1091
said: 1 | **ENTWIN** t_ms:37641627 stream:0x3c4214c9 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,64677217947d,84a329c78fec,e6b32d2cea8b,0283cce0e689,bc102f237ace,5ce28c488e0c
```

---

@LAT106LON91 | created:0 | updated:0

**BAR** frame:7000 bar:63 own:10 held:30 terms:9 digest:0x73c68450 settled_ms:120000
**HOLDS** agent:0x00000011 n:10 lo:390 hi:399 sum:3945
**HOLDS** agent:0x00000012 n:10 lo:311 hi:321 sum:3163
**HOLDS** agent:0x00000200 n:10 lo:1087 hi:1096 sum:10915
**HOLDS** agent:0x00000300 n:10 lo:2796 hi:2815 sum:28055

---

@LAT106LON92 | created:0 | updated:0

**BAR** frame:7000 bar:64 own:10 held:30 terms:9 digest:0x73c68450 settled_ms:120000
**HOLDS** agent:0x00000011 n:10 lo:400 hi:410 sum:4047
**HOLDS** agent:0x00000012 n:10 lo:322 hi:331 sum:3265
**HOLDS** agent:0x00000200 n:10 lo:1097 hi:1107 sum:11022
**HOLDS** agent:0x00000300 n:10 lo:2817 hi:2835 sum:28260

---

@LAT103LON8353 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 38726285 ±0 frame:7000
seq: 2847
follows: 0x00000010:486 0x00000011:415 0x00000012:336 0x00000100:686 0x00000200:1112
said: 1 | **ENTWIN** t_ms:38841627 stream:0x3c4214c9 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,5ce28c488e0c,bc102f237ace,0283cce0e689
said: 13 | **COVERED** windows:1 entities:7 window_ms:600000 first_t_ms:38241627 last_t_ms:38241627 covered_by:@LAT103LON8352
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
```

---

@LAT103LON16482 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 38798067 ±0 frame:7000
seq: 2851
follows: 0x00000010:487 0x00000011:417 0x00000012:337 0x00000100:687 0x00000200:1113
said: 1 | **MOTIONWIN** t_ms:38913409 stream:0x3c4214c9 wall:0 window_ms:60000 n:934
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27223 window_ms:1740637 moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0 first_t_ms:37172772 last_t_ms:38853409 covered_by:@LAT103LON16481
```

---

@LAT103LON2169 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 38978070 ±0 frame:7000
seq: 2857
follows: 0x00000010:489 0x00000011:420 0x00000012:340 0x00000100:690 0x00000200:1116
said: 1 | **LINKWIN** t_ms:39093412 stream:0x3c4214c9 wall:0 window_ms:60003
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-54 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 4 | **LINK** peer:0x00000010 proto:espnow n:91 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 5 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 6 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 7 | **LINK** peer:0x00000012 proto:espnow n:115 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 8 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-59 rssi_med:-52 rssi_max:-49
said: 10 | 0x00000200 ble met predicted:-44 observed:-44
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-52 observed:-52
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000011 ble met predicted:-52 observed:-54
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-39 observed:-38
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000010 ble met predicted:-54 observed:-54
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON2170 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39038070 ±0 frame:7000
seq: 2859
follows: 0x00000010:491 0x00000011:422 0x00000012:341 0x00000100:691 0x00000200:1117
said: 1 | **LINKWIN** t_ms:39153412 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:73 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:125 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000012 proto:espnow n:122 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 5 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 6 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-60 rssi_med:-52 rssi_max:-51
said: 7 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-52 rssi_med:-44 rssi_max:-42
said: 8 | **LINK** peer:0x00000010 proto:espnow n:151 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-59 rssi_med:-52 rssi_max:-49
said: 10 | 0x00000011 ble met predicted:-54 observed:-52
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-44 observed:-44
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-54 observed:-54
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-52 observed:-52
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON2171 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39098070 ±0 frame:7000
seq: 2861
follows: 0x00000010:492 0x00000011:423 0x00000012:342 0x00000100:692 0x00000200:1118
said: 1 | **LINKWIN** t_ms:39213412 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-80 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 4 | **LINK** peer:0x00000200 proto:espnow n:94 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000012 proto:espnow n:81 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 6 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 7 | **LINK** peer:0x00000100 proto:espnow n:76 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 8 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-79 rssi_med:-52 rssi_max:-51
said: 9 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-59 rssi_med:-52 rssi_max:-49
said: 10 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-54 observed:-54
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 ble met predicted:-52 observed:-52
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000200 ble met predicted:-44 observed:-44
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-52 observed:-52
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT106LON93 | created:0 | updated:0

**BAR** frame:7000 bar:65 own:10 held:30 terms:8 digest:0x687075bf settled_ms:120000
**HOLDS** agent:0x00000011 n:10 lo:411 hi:421 sum:4157
**HOLDS** agent:0x00000012 n:10 lo:332 hi:341 sum:3365
**HOLDS** agent:0x00000200 n:10 lo:1108 hi:1117 sum:11125
**HOLDS** agent:0x00000300 n:10 lo:2837 hi:2857 sum:28468

---

@LAT103LON2172 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39158070 ±0 frame:7000
seq: 2863
follows: 0x00000010:493 0x00000011:424 0x00000012:343 0x00000100:693 0x00000200:1119
said: 1 | **LINKWIN** t_ms:39273412 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-52 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 4 | **LINK** peer:0x00000200 proto:espnow n:70 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000012 proto:espnow n:62 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 6 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-36 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000010 proto:espnow n:74 rssi_min:-42 rssi_med:-39 rssi_max:-37
said: 8 | **LINK** peer:0x00000012 proto:ble n:68 rssi_min:-80 rssi_med:-55 rssi_max:-49
said: 9 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-82 rssi_med:-52 rssi_max:-51
said: 10 | 0x00000200 ble met predicted:-44 observed:-44
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-54 observed:-54
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-38 observed:-39
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 15 | 0x00000100 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-52 observed:-52
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-52 observed:-55
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON2173 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39218075 ±0 frame:7000
seq: 2865
follows: 0x00000010:494 0x00000011:425 0x00000012:344 0x00000100:694 0x00000200:1120
said: 1 | **LINKWIN** t_ms:39333417 stream:0x3c4214c9 wall:0 window_ms:60005
said: 2 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-55 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-82 rssi_med:-54 rssi_max:-51
said: 4 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-54 rssi_max:-52
said: 5 | **LINK** peer:0x00000100 proto:espnow n:80 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000200 proto:espnow n:136 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 7 | **LINK** peer:0x00000012 proto:espnow n:134 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 8 | **LINK** peer:0x00000010 proto:espnow n:150 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 9 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-52 rssi_med:-44 rssi_max:-42
said: 10 | 0x00000200 ble met predicted:-44 observed:-44
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-54 observed:-54
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-39 observed:-38
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-55 observed:-55
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-52 observed:-54
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2174 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39278076 ±0 frame:7000
seq: 2867
follows: 0x00000010:495 0x00000011:426 0x00000012:345 0x00000100:695 0x00000200:1121
said: 1 | **LINKWIN** t_ms:39393418 stream:0x3c4214c9 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000010 proto:espnow n:89 rssi_min:-42 rssi_med:-39 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-52 rssi_med:-44 rssi_max:-42
said: 4 | **LINK** peer:0x00000100 proto:espnow n:83 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 5 | **LINK** peer:0x00000200 proto:espnow n:96 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 6 | **LINK** peer:0x00000012 proto:espnow n:119 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 7 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-63 rssi_med:-54 rssi_max:-52
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-59 rssi_med:-52 rssi_max:-49
said: 9 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-52 rssi_max:-51
said: 10 | 0x00000012 ble met predicted:-55 observed:-52
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-54 observed:-52
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-54 observed:-54
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-38 observed:-39
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-44 observed:-44
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON8354 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 39326286 ±0 frame:7000
seq: 2869
follows: 0x00000010:496 0x00000011:426 0x00000012:346 0x00000100:696 0x00000200:1122
said: 1 | **ENTWIN** t_ms:39441628 stream:0x3c4214c9 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,64677217947d,84a329c78fec,bc102f237ace,0283cce0e689
```

---

@LAT103LON2175 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39338076 ±0 frame:7000
seq: 2870
follows: 0x00000010:496 0x00000011:427 0x00000012:346 0x00000100:696 0x00000200:1122
said: 1 | **LINKWIN** t_ms:39453418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-59 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:66 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 5 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 6 | **LINK** peer:0x00000010 proto:espnow n:75 rssi_min:-42 rssi_med:-38 rssi_max:-37
said: 7 | **LINK** peer:0x00000100 proto:espnow n:74 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-52 rssi_med:-44 rssi_max:-42
said: 9 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-59 rssi_med:-55 rssi_max:-49
said: 10 | 0x00000010 espnow met predicted:-39 observed:-38
percept: 10 | 0x00000010 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-44 observed:-44
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-54 observed:-54
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-52 observed:-55
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-52 observed:-52
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2176 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39398076 ±0 frame:7000
seq: 2872
follows: 0x00000010:497 0x00000011:428 0x00000012:347 0x00000100:697 0x00000200:1123
said: 1 | **LINKWIN** t_ms:39513418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:77 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 3 | **LINK** peer:0x00000012 proto:espnow n:70 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 4 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-79 rssi_med:-52 rssi_max:-49
said: 5 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-52 rssi_max:-51
said: 6 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-79 rssi_med:-54 rssi_max:-52
said: 7 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-52 rssi_med:-44 rssi_max:-42
said: 9 | **LINK** peer:0x00000010 proto:espnow n:72 rssi_min:-41 rssi_med:-39 rssi_max:-37
said: 10 | 0x00000011 ble met predicted:-52 observed:-52
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 ble met predicted:-54 observed:-54
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-38 observed:-39
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 15 | 0x00000100 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-44 observed:-44
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-55 observed:-52
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON2177 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39458076 ±0 frame:7000
seq: 2874
follows: 0x00000010:498 0x00000011:429 0x00000012:348 0x00000100:698 0x00000200:1124
said: 1 | **LINKWIN** t_ms:39573418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-59 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000010 proto:espnow n:85 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 4 | **LINK** peer:0x00000200 proto:espnow n:114 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 5 | **LINK** peer:0x00000100 proto:espnow n:78 rssi_min:-40 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-52 rssi_med:-44 rssi_max:-42
said: 7 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 8 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-73 rssi_med:-52 rssi_max:-48
said: 9 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 10 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000012 ble met predicted:-52 observed:-52
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000011 ble met predicted:-52 observed:-52
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-54 observed:-54
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 15 | 0x00000100 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-44 observed:-44
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-39 observed:-38
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON2178 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39518076 ±0 frame:7000
seq: 2876
follows: 0x00000010:499 0x00000011:430 0x00000012:349 0x00000100:699 0x00000200:1125
said: 1 | **LINKWIN** t_ms:39633418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-52 rssi_med:-44 rssi_max:-42
said: 4 | **LINK** peer:0x00000100 proto:espnow n:74 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 5 | **LINK** peer:0x00000012 proto:espnow n:85 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 6 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000012 proto:ble n:69 rssi_min:-59 rssi_med:-54 rssi_max:-49
said: 8 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-81 rssi_med:-52 rssi_max:-50
said: 9 | **LINK** peer:0x00000010 proto:espnow n:99 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 10 | 0x00000011 ble met predicted:-52 observed:-52
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-44 observed:-44
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000010 ble met predicted:-54 observed:-54
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-52 observed:-54
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON2179 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39578076 ±0 frame:7000
seq: 2878
follows: 0x00000010:500 0x00000011:431 0x00000012:350 0x00000100:700 0x00000200:1126
said: 1 | **LINKWIN** t_ms:39693418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:77 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 3 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 4 | **LINK** peer:0x00000200 proto:espnow n:159 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 5 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-60 rssi_med:-52 rssi_max:-51
said: 6 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 7 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-52 rssi_med:-44 rssi_max:-40
said: 8 | **LINK** peer:0x00000012 proto:ble n:68 rssi_min:-80 rssi_med:-52 rssi_max:-49
said: 9 | **LINK** peer:0x00000010 proto:espnow n:59 rssi_min:-41 rssi_med:-40 rssi_max:-37
said: 10 | 0x00000010 ble met predicted:-54 observed:-54
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-44 observed:-44
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-54 observed:-52
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-52 observed:-52
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-38 observed:-40
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON2180 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39638076 ±0 frame:7000
seq: 2880
follows: 0x00000010:500 0x00000011:432 0x00000012:351 0x00000100:701 0x00000200:1127
said: 1 | **LINKWIN** t_ms:39753418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-58 rssi_med:-55 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-59 rssi_med:-52 rssi_max:-51
said: 4 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 5 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-52 rssi_med:-44 rssi_max:-42
said: 6 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 7 | **LINK** peer:0x00000012 proto:espnow n:150 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 8 | **LINK** peer:0x00000200 proto:espnow n:70 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 9 | **LINK** peer:0x00000010 proto:espnow n:79 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 10 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 ble met predicted:-52 observed:-52
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-54 observed:-54
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000200 ble met predicted:-44 observed:-44
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-52 observed:-55
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-40 observed:-38
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON2181 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39698076 ±0 frame:7000
seq: 2882
follows: 0x00000010:502 0x00000011:433 0x00000012:352 0x00000100:702 0x00000200:1128
said: 1 | **LINKWIN** t_ms:39813418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:75 rssi_min:-37 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 4 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-52 rssi_med:-44 rssi_max:-41
said: 5 | **LINK** peer:0x00000010 proto:espnow n:99 rssi_min:-84 rssi_med:-38 rssi_max:-36
said: 6 | **LINK** peer:0x00000012 proto:espnow n:66 rssi_min:-40 rssi_med:-38 rssi_max:-35
said: 7 | **LINK** peer:0x00000200 proto:espnow n:69 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 8 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-60 rssi_med:-52 rssi_max:-50
said: 9 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-58 rssi_med:-52 rssi_max:-49
said: 10 | 0x00000012 ble met predicted:-55 observed:-52
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-52 observed:-52
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-54 observed:-54
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000200 ble met predicted:-44 observed:-44
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT106LON94 | created:0 | updated:0

**BAR** frame:7000 bar:66 own:10 held:29 terms:8 digest:0x687075bf settled_ms:120000
**HOLDS** agent:0x00000011 n:9 lo:422 hi:430 sum:3834
**HOLDS** agent:0x00000012 n:10 lo:342 hi:351 sum:3465
**HOLDS** agent:0x00000200 n:10 lo:1118 hi:1127 sum:11225
**HOLDS** agent:0x00000300 n:10 lo:2859 hi:2878 sum:28685

---

@LAT103LON2182 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39758076 ±0 frame:7000
seq: 2884
follows: 0x00000010:503 0x00000011:434 0x00000012:353 0x00000100:703 0x00000200:1129
said: 1 | **LINKWIN** t_ms:39873418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-58 rssi_med:-52 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:98 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-61 rssi_med:-52 rssi_max:-51
said: 5 | **LINK** peer:0x00000012 proto:espnow n:112 rssi_min:-41 rssi_med:-38 rssi_max:-33
said: 6 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-44 rssi_max:-41
said: 7 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-37 rssi_med:-35 rssi_max:-34
said: 8 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-63 rssi_med:-54 rssi_max:-51
said: 9 | **LINK** peer:0x00000010 proto:espnow n:70 rssi_min:-43 rssi_med:-39 rssi_max:-37
said: 10 | 0x00000100 espnow met predicted:-34 observed:-35
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000010 ble met predicted:-54 observed:-54
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 ble met predicted:-44 observed:-44
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000010 espnow met predicted:-38 observed:-39
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-52 observed:-52
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-52 observed:-52
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON2183 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39818076 ±0 frame:7000
seq: 2886
follows: 0x00000010:504 0x00000011:435 0x00000012:354 0x00000100:705 0x00000200:1130
said: 1 | **LINKWIN** t_ms:39933418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-60 rssi_med:-52 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-70 rssi_med:-44 rssi_max:-42
said: 4 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 5 | **LINK** peer:0x00000010 proto:espnow n:74 rssi_min:-42 rssi_med:-39 rssi_max:-37
said: 6 | **LINK** peer:0x00000012 proto:espnow n:86 rssi_min:-41 rssi_med:-38 rssi_max:-34
said: 7 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-37 rssi_med:-34 rssi_max:-34
said: 8 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-48
said: 10 | 0x00000012 ble met predicted:-52 observed:-54
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000011 ble met predicted:-52 observed:-52
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-44 observed:-44
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000100 espnow met predicted:-35 observed:-34
percept: 15 | 0x00000100 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-54 observed:-54
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON2184 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39878076 ±0 frame:7000
seq: 2888
follows: 0x00000010:505 0x00000011:436 0x00000012:355 0x00000100:706 0x00000200:1132
said: 1 | **LINKWIN** t_ms:39993418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-80 rssi_med:-52 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:81 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000010 proto:espnow n:112 rssi_min:-43 rssi_med:-39 rssi_max:-35
said: 5 | **LINK** peer:0x00000200 proto:ble n:71 rssi_min:-81 rssi_med:-44 rssi_max:-41
said: 6 | **LINK** peer:0x00000100 proto:espnow n:75 rssi_min:-38 rssi_med:-34 rssi_max:-34
said: 7 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-56 rssi_med:-51 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:espnow n:89 rssi_min:-41 rssi_med:-38 rssi_max:-34
said: 9 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 10 | 0x00000011 ble met predicted:-52 observed:-52
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-44 observed:-44
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-54 observed:-54
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 15 | 0x00000100 | link_stable | espnow | + | -
said: 16 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-54 observed:-51
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON2185 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39938076 ±0 frame:7000
seq: 2890
follows: 0x00000010:506 0x00000011:437 0x00000012:356 0x00000100:707 0x00000200:1133
said: 1 | **LINKWIN** t_ms:40053418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:99 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 3 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 4 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 5 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 6 | **LINK** peer:0x00000200 proto:espnow n:147 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 7 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-80 rssi_med:-52 rssi_max:-49
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 9 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-52 rssi_max:-51
said: 10 | 0x00000011 ble met predicted:-52 observed:-52
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-44 observed:-44
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-51 observed:-52
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000010 ble met predicted:-54 observed:-54
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON2186 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 39998076 ±0 frame:7000
seq: 2892
follows: 0x00000010:507 0x00000011:438 0x00000012:357 0x00000100:708 0x00000200:1134
said: 1 | **LINKWIN** t_ms:40113418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:74 rssi_min:-36 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-51 rssi_max:-49
said: 4 | **LINK** peer:0x00000200 proto:espnow n:138 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000012 proto:espnow n:97 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 6 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 7 | **LINK** peer:0x00000010 proto:espnow n:43 rssi_min:-42 rssi_med:-40 rssi_max:-38
said: 8 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-80 rssi_med:-52 rssi_max:-51
said: 10 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-39 observed:-40
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-54 observed:-54
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-52 observed:-51
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-44 observed:-44
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-52 observed:-52
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2187 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40058076 ±0 frame:7000
seq: 2894
follows: 0x00000010:507 0x00000011:439 0x00000012:358 0x00000100:709 0x00000200:1135
said: 1 | **LINKWIN** t_ms:40173418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-51 rssi_max:-49
said: 4 | **LINK** peer:0x00000012 proto:espnow n:117 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 5 | **LINK** peer:0x00000100 proto:espnow n:81 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000010 proto:espnow n:129 rssi_min:-42 rssi_med:-39 rssi_max:-37
said: 7 | **LINK** peer:0x00000200 proto:espnow n:78 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 8 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-60 rssi_med:-52 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-52 rssi_med:-44 rssi_max:-42
said: 10 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000012 ble met predicted:-51 observed:-51
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-44 observed:-44
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-40 observed:-39
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-54 observed:-54
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-52 observed:-52
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2188 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40118076 ±0 frame:7000
seq: 2896
follows: 0x00000010:509 0x00000011:441 0x00000012:359 0x00000100:710 0x00000200:1136
said: 1 | **LINKWIN** t_ms:40233418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 3 | **LINK** peer:0x00000010 proto:espnow n:121 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 4 | **LINK** peer:0x00000100 proto:espnow n:93 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 5 | **LINK** peer:0x00000200 proto:espnow n:135 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 6 | **LINK** peer:0x00000012 proto:espnow n:114 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 7 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-59 rssi_med:-51 rssi_max:-49
said: 8 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-60 rssi_med:-54 rssi_max:-50
said: 9 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 10 | 0x00000010 ble met predicted:-54 observed:-54
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-51 observed:-51
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-52 observed:-54
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-44 observed:-44
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON2189 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40178076 ±0 frame:7000
seq: 2898
follows: 0x00000010:510 0x00000011:442 0x00000012:360 0x00000100:711 0x00000200:1137
said: 1 | **LINKWIN** t_ms:40293418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-58 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000100 proto:espnow n:77 rssi_min:-35 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 6 | **LINK** peer:0x00000010 proto:espnow n:80 rssi_min:-42 rssi_med:-40 rssi_max:-38
said: 7 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-79 rssi_med:-54 rssi_max:-52
said: 8 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-52 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 10 | 0x00000010 ble met predicted:-54 observed:-54
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000010 espnow met predicted:-39 observed:-40
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-51 observed:-51
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-54 observed:-52
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-44 observed:-44
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON26556 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40178076 ±0 frame:7000
seq: 2899
follows: 0x00000010:510 0x00000011:442 0x00000012:360 0x00000100:711 0x00000200:1137
said: 1 | **ACOUSTICWIN** t_ms:40293418 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3697 rate:8000
said: 2 | **ACOUSTIC** rms_mean:141 rms_max:1220 peak:2095 transients:11
said: 3 | **TRANSIENT** t_ms:40261471 stream:0x3c4214c9 wall:0 rms:1220
```

---

@LAT103LON2190 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40238076 ±0 frame:7000
seq: 2900
follows: 0x00000010:511 0x00000011:443 0x00000012:361 0x00000100:712 0x00000200:1138
said: 1 | **LINKWIN** t_ms:40353418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:112 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 3 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-79 rssi_med:-51 rssi_max:-49
said: 4 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-44 rssi_max:-42
said: 5 | **LINK** peer:0x00000100 proto:espnow n:91 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000010 proto:ble n:71 rssi_min:-81 rssi_med:-54 rssi_max:-52
said: 7 | **LINK** peer:0x00000200 proto:espnow n:79 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 8 | **LINK** peer:0x00000010 proto:espnow n:126 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-77 rssi_med:-52 rssi_max:-51
said: 10 | 0x00000012 ble met predicted:-51 observed:-51
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-40 observed:-39
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-54 observed:-54
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-52 observed:-52
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-44 observed:-44
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON26557 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40238076 ±0 frame:7000
seq: 2901
follows: 0x00000010:511 0x00000011:443 0x00000012:361 0x00000100:712 0x00000200:1138
said: 1 | **ACOUSTICWIN** t_ms:40353418 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3437 rate:8000
said: 2 | **ACOUSTIC** rms_mean:115 rms_max:1598 peak:2675 transients:4
said: 3 | **TRANSIENT** t_ms:40295131 stream:0x3c4214c9 wall:0 rms:1598
```

---

@LAT103LON2191 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40298076 ±0 frame:7000
seq: 2902
follows: 0x00000010:511 0x00000011:444 0x00000012:362 0x00000100:713 0x00000200:1139
said: 1 | **LINKWIN** t_ms:40413418 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-58 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 4 | **LINK** peer:0x00000200 proto:espnow n:132 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-36 rssi_med:-34 rssi_max:-33
said: 6 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-60 rssi_med:-54 rssi_max:-51
said: 7 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-52 rssi_med:-44 rssi_max:-42
said: 8 | **LINK** peer:0x00000010 proto:espnow n:49 rssi_min:-42 rssi_med:-39 rssi_max:-37
said: 9 | **LINK** peer:0x00000012 proto:espnow n:135 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 10 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000012 ble met predicted:-51 observed:-51
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000200 ble met predicted:-44 observed:-44
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000010 ble met predicted:-54 observed:-54
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-52 observed:-54
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON26558 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40298076 ±0 frame:7000
seq: 2903
follows: 0x00000010:511 0x00000011:444 0x00000012:362 0x00000100:713 0x00000200:1139
said: 1 | **ACOUSTICWIN** t_ms:40413418 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3435 rate:8000
said: 2 | **ACOUSTIC** rms_mean:82 rms_max:619 peak:1110 transients:0
```

---

@LAT106LON95 | created:0 | updated:0

**BAR** frame:7000 bar:67 own:10 held:27 terms:8 digest:0x687075bf settled_ms:120000
**HOLDS** agent:0x00000011 n:7 lo:432 hi:439 sum:3047
**HOLDS** agent:0x00000012 n:10 lo:352 hi:361 sum:3565
**HOLDS** agent:0x00000200 n:10 lo:1128 hi:1138 sum:11332
**HOLDS** agent:0x00000300 n:10 lo:2880 hi:2898 sum:28890

---

@LAT103LON2192 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40359409 ±0 frame:7000
seq: 2904
follows: 0x00000010:513 0x00000011:445 0x00000012:363 0x00000100:714 0x00000200:1140
said: 1 | **LINKWIN** t_ms:40474751 stream:0x3c4214c9 wall:0 window_ms:61333
said: 2 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-81 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000012 proto:ble n:68 rssi_min:-59 rssi_med:-51 rssi_max:-48
said: 4 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-64 rssi_med:-54 rssi_max:-52
said: 5 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000200 proto:espnow n:86 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 7 | **LINK** peer:0x00000012 proto:espnow n:83 rssi_min:-41 rssi_med:-38 rssi_max:-37
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-44 rssi_max:-42
said: 9 | **LINK** peer:0x00000010 proto:espnow n:57 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 10 | 0x00000012 ble met predicted:-51 observed:-51
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-54 observed:-54
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-34 observed:-34
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-54 observed:-52
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000200 ble met predicted:-44 observed:-44
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON26559 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40359409 ±0 frame:7000
seq: 2905
follows: 0x00000010:513 0x00000011:445 0x00000012:363 0x00000100:714 0x00000200:1140
said: 1 | **ACOUSTICWIN** t_ms:40474751 stream:0x3c4214c9 wall:0 window_ms:61333 blocks:2743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:97 rms_max:925 peak:1548 transients:1
said: 3 | **TRANSIENT** t_ms:40459023 stream:0x3c4214c9 wall:0 rms:925
```

---

@LAT103LON2193 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40419409 ±0 frame:7000
seq: 2906
follows: 0x00000010:514 0x00000011:446 0x00000012:364 0x00000100:715 0x00000200:1141
said: 1 | **LINKWIN** t_ms:40534751 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-38 rssi_med:-36 rssi_max:-34
said: 3 | **LINK** peer:0x00000012 proto:espnow n:74 rssi_min:-47 rssi_med:-38 rssi_max:-33
said: 4 | **LINK** peer:0x00000200 proto:espnow n:111 rssi_min:-41 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-58 rssi_med:-55 rssi_max:-48
said: 6 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 7 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-60 rssi_med:-53 rssi_max:-50
said: 8 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-62 rssi_med:-43 rssi_max:-42
said: 9 | **LINK** peer:0x00000010 proto:espnow n:91 rssi_min:-45 rssi_med:-39 rssi_max:-37
said: 10 | 0x00000011 ble met predicted:-52 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-51 observed:-55
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-54 observed:-55
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-34 observed:-36
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-44 observed:-43
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON26560 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40419409 ±0 frame:7000
seq: 2907
follows: 0x00000010:514 0x00000011:446 0x00000012:364 0x00000100:715 0x00000200:1141
said: 1 | **ACOUSTICWIN** t_ms:40534751 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3694 rate:8000
said: 2 | **ACOUSTIC** rms_mean:169 rms_max:12840 peak:32768 transients:14
said: 3 | **TRANSIENT** t_ms:40493586 stream:0x3c4214c9 wall:0 rms:12840
```

---

@LAT103LON2194 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40479409 ±0 frame:7000
seq: 2908
follows: 0x00000010:515 0x00000011:447 0x00000012:365 0x00000100:717 0x00000200:1142
said: 1 | **LINKWIN** t_ms:40594751 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:125 rssi_min:-48 rssi_med:-34 rssi_max:-28
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-79 rssi_med:-56 rssi_max:-43
said: 4 | **LINK** peer:0x00000200 proto:espnow n:95 rssi_min:-49 rssi_med:-46 rssi_max:-28
said: 5 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-70 rssi_med:-56 rssi_max:-52
said: 6 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-47 rssi_med:-44 rssi_max:-36
said: 7 | **LINK** peer:0x00000100 proto:espnow n:77 rssi_min:-46 rssi_med:-35 rssi_max:-30
said: 8 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-58 rssi_med:-53 rssi_max:-45
said: 9 | **LINK** peer:0x00000010 proto:ble n:73 rssi_min:-67 rssi_med:-57 rssi_max:-51
said: 10 | 0x00000100 espnow met predicted:-36 observed:-35
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-38 observed:-34
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow violated predicted:-29 observed:-46
percept: 12 | 0x00000200 | link_stable | espnow | - | -
said: 13 | 0x00000012 ble met predicted:-55 observed:-53
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-55 observed:-57
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000011 ble met predicted:-53 observed:-56
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000200 ble violated predicted:-43 observed:-56
percept: 16 | 0x00000200 | link_stable | ble | - | -
said: 17 | 0x00000010 espnow met predicted:-39 observed:-44
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON26561 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40479409 ±0 frame:7000
seq: 2909
follows: 0x00000010:515 0x00000011:447 0x00000012:365 0x00000100:717 0x00000200:1142
said: 1 | **ACOUSTICWIN** t_ms:40594751 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3665 rate:8000
said: 2 | **ACOUSTIC** rms_mean:218 rms_max:22149 peak:32768 transients:20
said: 3 | **TRANSIENT** t_ms:40578490 stream:0x3c4214c9 wall:0 rms:22149
```

---

@LAT103LON2195 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40539409 ±0 frame:7000
seq: 2910
follows: 0x00000010:516 0x00000011:448 0x00000012:366 0x00000100:718 0x00000200:1143
said: 1 | **LINKWIN** t_ms:40654751 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-80 rssi_med:-48 rssi_max:-47
said: 3 | **LINK** peer:0x00000100 proto:espnow n:75 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 4 | **LINK** peer:0x00000200 proto:espnow n:77 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 5 | **LINK** peer:0x00000012 proto:espnow n:66 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-56 rssi_max:-53
said: 7 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-46 rssi_max:-43
said: 8 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-74 rssi_med:-59 rssi_max:-56
said: 9 | **LINK** peer:0x00000010 proto:espnow n:134 rssi_min:-46 rssi_med:-42 rssi_max:-41
said: 10 | 0x00000012 espnow met predicted:-34 observed:-31
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble violated predicted:-56 observed:-46
percept: 11 | 0x00000200 | link_stable | ble | - | -
said: 12 | 0x00000200 espnow violated predicted:-46 observed:-30
percept: 12 | 0x00000200 | link_stable | espnow | - | -
said: 13 | 0x00000011 ble met predicted:-56 observed:-56
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-44 observed:-42
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000100 espnow met predicted:-35 observed:-30
percept: 15 | 0x00000100 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-53 observed:-48
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-57 observed:-59
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON26562 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40539409 ±0 frame:7000
seq: 2911
follows: 0x00000010:516 0x00000011:448 0x00000012:366 0x00000100:718 0x00000200:1143
said: 1 | **ACOUSTICWIN** t_ms:40654751 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3482 rate:8000
said: 2 | **ACOUSTIC** rms_mean:179 rms_max:8245 peak:8659 transients:11
said: 3 | **TRANSIENT** t_ms:40611766 stream:0x3c4214c9 wall:0 rms:8245
```

---

@LAT103LON2196 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40599409 ±0 frame:7000
seq: 2912
follows: 0x00000010:517 0x00000011:449 0x00000012:367 0x00000100:719 0x00000200:1144
said: 1 | **LINKWIN** t_ms:40714751 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 3 | **LINK** peer:0x00000100 proto:espnow n:80 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 4 | **LINK** peer:0x00000012 proto:espnow n:82 rssi_min:-33 rssi_med:-31 rssi_max:-29
said: 5 | **LINK** peer:0x00000200 proto:espnow n:108 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-68 rssi_med:-55 rssi_max:-55
said: 7 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-80 rssi_med:-46 rssi_max:-43
said: 8 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-59 rssi_max:-55
said: 9 | **LINK** peer:0x00000010 proto:espnow n:83 rssi_min:-46 rssi_med:-42 rssi_max:-40
said: 10 | 0x00000012 ble met predicted:-48 observed:-48
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-30 observed:-31
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-56 observed:-55
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000200 ble met predicted:-46 observed:-46
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-59 observed:-59
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON16483 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 40599409 ±0 frame:7000
seq: 2913
follows: 0x00000010:517 0x00000011:449 0x00000012:367 0x00000100:719 0x00000200:1144
said: 1 | **MOTIONWIN** t_ms:40714751 stream:0x3c4214c9 wall:0 window_ms:60000 n:926
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:17 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27191 window_ms:1741342 moving_permille:0 dev_mean_mg:11 dev_max_mg:54 moving_ms:0 first_t_ms:38973409 last_t_ms:40654751 covered_by:@LAT103LON16482
```

---

@LAT103LON26563 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40599409 ±0 frame:7000
seq: 2914
follows: 0x00000010:517 0x00000011:449 0x00000012:367 0x00000100:719 0x00000200:1144
said: 1 | **ACOUSTICWIN** t_ms:40714751 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3433 rate:8000
said: 2 | **ACOUSTIC** rms_mean:188 rms_max:1992 peak:5903 transients:12
said: 3 | **TRANSIENT** t_ms:40687114 stream:0x3c4214c9 wall:0 rms:1992
```

---

@LAT103LON2197 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40659409 ±0 frame:7000
seq: 2915
follows: 0x00000010:518 0x00000011:450 0x00000012:368 0x00000100:720 0x00000200:1145
said: 1 | **LINKWIN** t_ms:40774751 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-80 rssi_med:-56 rssi_max:-53
said: 3 | **LINK** peer:0x00000012 proto:espnow n:109 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 4 | **LINK** peer:0x00000100 proto:espnow n:89 rssi_min:-32 rssi_med:-30 rssi_max:-28
said: 5 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000200 proto:espnow n:154 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-80 rssi_med:-46 rssi_max:-43
said: 9 | **LINK** peer:0x00000011 proto:espnow n:118 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 10 | 0x00000012 ble met predicted:-48 observed:-48
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-31 observed:-31
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-55 observed:-56
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000200 ble met predicted:-46 observed:-46
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-59 observed:-59
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow unobserved predicted:-42 observed:-42
percept: 17 | 0x00000010 | link_stable | espnow | ? | -
```

---

@LAT103LON26564 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40659409 ±0 frame:7000
seq: 2916
follows: 0x00000010:518 0x00000011:450 0x00000012:368 0x00000100:720 0x00000200:1145
said: 1 | **ACOUSTICWIN** t_ms:40774751 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3683 rate:8000
said: 2 | **ACOUSTIC** rms_mean:114 rms_max:1243 peak:2248 transients:4
said: 3 | **TRANSIENT** t_ms:40721921 stream:0x3c4214c9 wall:0 rms:1243
```

---

@LAT105LON2135 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 40681624 ±21 frame:7000
seq: 1146
follows: 0x00000010:518 0x00000011:451 0x00000012:369 0x00000100:721 0x00000300:2916
said: 1 | **LINKWIN** t_ms:40796961 stream:0x3c4214c9 wall:0 window_ms:60030
said: 2 | **LINK** peer:0x00000011 proto:espnow n:72 rssi_min:-61 rssi_med:-57 rssi_max:-55
said: 3 | **LINK** peer:0x00000300 proto:espnow n:180 rssi_min:-29 rssi_med:-28 rssi_max:-27
said: 4 | **LINK** peer:0x00000100 proto:espnow n:95 rssi_min:-31 rssi_med:-29 rssi_max:-27
said: 5 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-51 rssi_med:-44 rssi_max:-42
said: 6 | **LINK** peer:0x00000012 proto:espnow n:116 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-80 rssi_med:-70 rssi_max:-66
said: 8 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-61 rssi_med:-56 rssi_max:-55
said: 9 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-48 rssi_med:-47 rssi_max:-46
```

---

@LAT103LON2198 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40719409 ±0 frame:7000
seq: 2917
follows: 0x00000010:519 0x00000011:452 0x00000012:369 0x00000100:721 0x00000200:1146
said: 1 | **LINKWIN** t_ms:40834751 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 3 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-56 rssi_max:-52
said: 4 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-30 rssi_med:-30 rssi_max:-29
said: 5 | **LINK** peer:0x00000200 proto:espnow n:91 rssi_min:-32 rssi_med:-31 rssi_max:-31
said: 6 | **LINK** peer:0x00000010 proto:espnow n:88 rssi_min:-44 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-59 rssi_max:-55
said: 8 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-56 rssi_med:-46 rssi_max:-43
said: 9 | **LINK** peer:0x00000012 proto:espnow n:86 rssi_min:-33 rssi_med:-31 rssi_max:-30
said: 10 | 0x00000011 ble met predicted:-56 observed:-56
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-48 observed:-48
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000200 espnow met predicted:-31 observed:-31
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-59 observed:-59
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-46 observed:-46
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow unobserved predicted:-40 observed:-40
percept: 17 | 0x00000011 | link_stable | espnow | ? | -
```

---

@LAT103LON26565 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40719409 ±0 frame:7000
seq: 2918
follows: 0x00000010:519 0x00000011:452 0x00000012:369 0x00000100:721 0x00000200:1146
said: 1 | **ACOUSTICWIN** t_ms:40834751 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3694 rate:8000
said: 2 | **ACOUSTIC** rms_mean:137 rms_max:2058 peak:4923 transients:3
said: 3 | **TRANSIENT** t_ms:40832369 stream:0x3c4214c9 wall:0 rms:2058
```

---

@LAT105LON2136 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 40645628 ±21 frame:7000
seq: 450
follows: 0x00000010:518 0x00000012:368 0x00000100:720 0x00000200:1145 0x00000300:2914
said: 1 | **LINKWIN** t_ms:40760921 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:80 rssi_min:-31 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-55 rssi_max:-49
said: 4 | **LINK** peer:0x00000012 proto:espnow n:113 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 5 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-74 rssi_max:-71
said: 6 | **LINK** peer:0x00000300 proto:espnow n:137 rssi_min:-39 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000200 proto:espnow n:146 rssi_min:-64 rssi_med:-61 rssi_max:-58
said: 8 | **LINK** peer:0x00000010 proto:espnow n:75 rssi_min:-31 rssi_med:-28 rssi_max:-27
said: 9 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-82 rssi_med:-43 rssi_max:-40
```

---

@LAT105LON2137 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 40735678 ±21 frame:7000
seq: 370
follows: 0x00000010:519 0x00000011:452 0x00000100:722 0x00000200:1146 0x00000300:2918
said: 1 | **LINKWIN** t_ms:40850994 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:179 rssi_min:-26 rssi_med:-25 rssi_max:-24
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-39 rssi_max:-37
said: 4 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-50 rssi_max:-46
said: 5 | **LINK** peer:0x00000200 proto:espnow n:112 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 6 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-80 rssi_med:-42 rssi_max:-41
said: 7 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-53 rssi_max:-50
said: 8 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-26 rssi_med:-24 rssi_max:-24
said: 9 | **LINK** peer:0x00000010 proto:espnow n:75 rssi_min:-42 rssi_med:-39 rssi_max:-34
```

---

@LAT105LON2138 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 40741665 ±21 frame:7000
seq: 1147
follows: 0x00000010:519 0x00000011:452 0x00000012:370 0x00000100:722 0x00000300:2918
said: 1 | **LINKWIN** t_ms:40857001 stream:0x3c4214c9 wall:0 window_ms:60041
said: 2 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-48 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000100 proto:espnow n:71 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 4 | **LINK** peer:0x00000012 proto:espnow n:62 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:espnow n:92 rssi_min:-60 rssi_med:-57 rssi_max:-55
said: 6 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-51 rssi_med:-44 rssi_max:-41
said: 7 | **LINK** peer:0x00000011 proto:ble n:49 rssi_min:-76 rssi_med:-69 rssi_max:-65
said: 8 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-47 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-61 rssi_med:-56 rssi_max:-55
```

---

@LAT103LON2199 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40779409 ±0 frame:7000
seq: 2919
follows: 0x00000010:520 0x00000011:453 0x00000012:370 0x00000100:722 0x00000200:1147
said: 1 | **LINKWIN** t_ms:40894751 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:57 rssi_min:-44 rssi_med:-42 rssi_max:-40
said: 3 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 4 | **LINK** peer:0x00000200 proto:espnow n:101 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-31 rssi_med:-31 rssi_max:-29
said: 6 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-64 rssi_med:-56 rssi_max:-54
said: 7 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-78 rssi_med:-59 rssi_max:-55
said: 8 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-56 rssi_med:-47 rssi_max:-43
said: 9 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-79 rssi_med:-48 rssi_max:-46
said: 10 | 0x00000012 ble met predicted:-48 observed:-48
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-56 observed:-56
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-31 observed:-31
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-41 observed:-42
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-59 observed:-59
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-46 observed:-47
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON26566 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40779409 ±0 frame:7000
seq: 2920
follows: 0x00000010:520 0x00000011:453 0x00000012:370 0x00000100:722 0x00000200:1147
said: 1 | **ACOUSTICWIN** t_ms:40894751 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3461 rate:8000
said: 2 | **ACOUSTIC** rms_mean:146 rms_max:770 peak:2164 transients:0
```

---

@LAT105LON2139 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 40705629 ±21 frame:7000
seq: 452
follows: 0x00000010:519 0x00000012:369 0x00000100:721 0x00000200:1146 0x00000300:2916
said: 1 | **LINKWIN** t_ms:40820922 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:76 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 3 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-81 rssi_med:-55 rssi_max:-50
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-80 rssi_med:-73 rssi_max:-70
said: 5 | **LINK** peer:0x00000300 proto:espnow n:136 rssi_min:-39 rssi_med:-34 rssi_max:-34
said: 6 | **LINK** peer:0x00000200 proto:espnow n:70 rssi_min:-64 rssi_med:-61 rssi_max:-60
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-43 rssi_max:-40
said: 8 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-82 rssi_med:-50 rssi_max:-48
said: 9 | **LINK** peer:0x00000012 proto:espnow n:79 rssi_min:-41 rssi_med:-40 rssi_max:-36
```

---

@LAT105LON2140 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 40795678 ±21 frame:7000
seq: 371
follows: 0x00000010:520 0x00000011:453 0x00000100:723 0x00000200:1147 0x00000300:2920
said: 1 | **LINKWIN** t_ms:40910994 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:80 rssi_min:-42 rssi_med:-40 rssi_max:-36
said: 3 | **LINK** peer:0x00000010 proto:espnow n:67 rssi_min:-43 rssi_med:-40 rssi_max:-35
said: 4 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-81 rssi_med:-50 rssi_max:-46
said: 5 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-54 rssi_max:-49
said: 6 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-42 rssi_max:-41
said: 7 | **LINK** peer:0x00000300 proto:espnow n:139 rssi_min:-26 rssi_med:-25 rssi_max:-24
said: 8 | **LINK** peer:0x00000100 proto:espnow n:73 rssi_min:-26 rssi_med:-24 rssi_max:-23
said: 9 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON2141 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 40765630 ±21 frame:7000
seq: 453
follows: 0x00000010:520 0x00000012:370 0x00000100:722 0x00000200:1147 0x00000300:2918
said: 1 | **LINKWIN** t_ms:40880922 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:espnow n:130 rssi_min:-65 rssi_med:-60 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-73 rssi_max:-69
said: 5 | **LINK** peer:0x00000100 proto:espnow n:85 rssi_min:-35 rssi_med:-31 rssi_max:-29
said: 6 | **LINK** peer:0x00000300 proto:espnow n:128 rssi_min:-39 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-43 rssi_max:-40
said: 8 | **LINK** peer:0x00000010 proto:espnow n:59 rssi_min:-31 rssi_med:-29 rssi_max:-27
said: 9 | **LINK** peer:0x00000012 proto:espnow n:92 rssi_min:-41 rssi_med:-40 rssi_max:-35
```

---

@LAT105LON2142 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 40801689 ±21 frame:7000
seq: 1148
follows: 0x00000010:521 0x00000011:453 0x00000012:371 0x00000100:723 0x00000300:2920
said: 1 | **LINKWIN** t_ms:40917022 stream:0x3c4214c9 wall:0 window_ms:60022
said: 2 | **LINK** peer:0x00000011 proto:espnow n:83 rssi_min:-59 rssi_med:-57 rssi_max:-54
said: 3 | **LINK** peer:0x00000300 proto:espnow n:139 rssi_min:-30 rssi_med:-28 rssi_max:-27
said: 4 | **LINK** peer:0x00000012 proto:espnow n:99 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-48 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-83 rssi_med:-69 rssi_max:-65
said: 7 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-61 rssi_med:-56 rssi_max:-54
said: 9 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-44 rssi_max:-42
```

---

@LAT103LON2200 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40839409 ±0 frame:7000
seq: 2921
follows: 0x00000010:521 0x00000011:454 0x00000012:371 0x00000100:723 0x00000200:1148
said: 1 | **LINKWIN** t_ms:40954751 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:123 rssi_min:-33 rssi_med:-31 rssi_max:-31
said: 3 | **LINK** peer:0x00000100 proto:espnow n:71 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:ble n:72 rssi_min:-66 rssi_med:-56 rssi_max:-52
said: 5 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-47 rssi_max:-44
said: 6 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-81 rssi_med:-59 rssi_max:-55
said: 7 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-48 rssi_max:-47
said: 8 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-44 rssi_med:-41 rssi_max:-40
said: 9 | **LINK** peer:0x00000200 proto:espnow n:89 rssi_min:-33 rssi_med:-31 rssi_max:-31
said: 10 | 0x00000010 espnow met predicted:-42 observed:-41
percept: 10 | 0x00000010 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-31 observed:-31
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-56 observed:-56
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000010 ble met predicted:-59 observed:-59
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-47 observed:-47
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-48 observed:-48
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON26567 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40839409 ±0 frame:7000
seq: 2922
follows: 0x00000010:521 0x00000011:454 0x00000012:371 0x00000100:723 0x00000200:1148
said: 1 | **ACOUSTICWIN** t_ms:40954751 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3454 rate:8000
said: 2 | **ACOUSTIC** rms_mean:136 rms_max:1238 peak:1620 transients:0
```

---

@LAT105LON2143 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 40825631 ±21 frame:7000
seq: 454
follows: 0x00000010:521 0x00000012:371 0x00000100:723 0x00000200:1148 0x00000300:2920
said: 1 | **LINKWIN** t_ms:40940973 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-55 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-89 rssi_med:-72 rssi_max:-69
said: 4 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-82 rssi_med:-50 rssi_max:-47
said: 5 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-43 rssi_max:-39
said: 6 | **LINK** peer:0x00000100 proto:espnow n:81 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000010 proto:espnow n:89 rssi_min:-35 rssi_med:-28 rssi_max:-27
said: 8 | **LINK** peer:0x00000012 proto:espnow n:92 rssi_min:-42 rssi_med:-40 rssi_max:-36
said: 9 | **LINK** peer:0x00000200 proto:espnow n:107 rssi_min:-63 rssi_med:-60 rssi_max:-57
```

---

@LAT105LON2144 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 40855674 ±21 frame:7000
seq: 372
follows: 0x00000010:521 0x00000011:454 0x00000100:724 0x00000200:1148 0x00000300:2922
said: 1 | **LINKWIN** t_ms:40970994 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:148 rssi_min:-26 rssi_med:-25 rssi_max:-24
said: 3 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-42 rssi_med:-40 rssi_max:-35
said: 4 | **LINK** peer:0x00000100 proto:espnow n:80 rssi_min:-26 rssi_med:-24 rssi_max:-24
said: 5 | **LINK** peer:0x00000011 proto:espnow n:137 rssi_min:-46 rssi_med:-40 rssi_max:-36
said: 6 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-42 rssi_max:-41
said: 7 | **LINK** peer:0x00000200 proto:espnow n:118 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 8 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-54 rssi_max:-50
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-39 rssi_max:-37
```

---

@LAT105LON2145 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 40861713 ±21 frame:7000
seq: 1149
follows: 0x00000010:522 0x00000011:454 0x00000012:372 0x00000100:724 0x00000300:2922
said: 1 | **LINKWIN** t_ms:40977045 stream:0x3c4214c9 wall:0 window_ms:60023
said: 2 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-82 rssi_med:-69 rssi_max:-65
said: 3 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-82 rssi_med:-47 rssi_max:-46
said: 4 | **LINK** peer:0x00000300 proto:ble n:71 rssi_min:-51 rssi_med:-44 rssi_max:-42
said: 5 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-48 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000100 proto:espnow n:97 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000012 proto:espnow n:116 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000300 proto:espnow n:174 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 9 | **LINK** peer:0x00000011 proto:espnow n:130 rssi_min:-58 rssi_med:-56 rssi_max:-55
```

---

@LAT103LON2201 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40899409 ±0 frame:7000
seq: 2923
follows: 0x00000010:523 0x00000011:455 0x00000012:372 0x00000100:724 0x00000200:1149
said: 1 | **LINKWIN** t_ms:41014751 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 3 | **LINK** peer:0x00000011 proto:ble n:52 rssi_min:-83 rssi_med:-56 rssi_max:-54
said: 4 | **LINK** peer:0x00000100 proto:espnow n:74 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 5 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-33 rssi_med:-31 rssi_max:-31
said: 6 | **LINK** peer:0x00000012 proto:espnow n:92 rssi_min:-33 rssi_med:-31 rssi_max:-31
said: 7 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-79 rssi_med:-46 rssi_max:-44
said: 8 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-80 rssi_med:-59 rssi_max:-55
said: 9 | **LINK** peer:0x00000010 proto:espnow n:70 rssi_min:-84 rssi_med:-42 rssi_max:-40
said: 10 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000011 ble met predicted:-56 observed:-56
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000200 ble met predicted:-47 observed:-46
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-59 observed:-59
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-48 observed:-48
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-41 observed:-42
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 espnow met predicted:-31 observed:-31
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON26568 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40899409 ±0 frame:7000
seq: 2924
follows: 0x00000010:523 0x00000011:455 0x00000012:372 0x00000100:724 0x00000200:1149
said: 1 | **ACOUSTICWIN** t_ms:41014751 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3450 rate:8000
said: 2 | **ACOUSTIC** rms_mean:114 rms_max:437 peak:822 transients:0
```
@LAT106LON96 | created:0 | updated:0

**BAR** frame:7000 bar:68 own:10 held:30 terms:9 digest:0xad560d26 settled_ms:120000
**HOLDS** agent:0x00000011 n:10 lo:443 hi:453 sum:4477
**HOLDS** agent:0x00000012 n:10 lo:362 hi:371 sum:3665
**HOLDS** agent:0x00000200 n:10 lo:1139 hi:1148 sum:11435
**HOLDS** agent:0x00000300 n:10 lo:2900 hi:2919 sum:29093

---

@LAT103LON2202 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 40959409 ±0 frame:7000
seq: 2925
follows: 0x00000010:524 0x00000011:456 0x00000012:374 0x00000100:725 0x00000200:1150
said: 1 | **LINKWIN** t_ms:41074751 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-56 rssi_med:-47 rssi_max:-44
said: 3 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-30 rssi_med:-30 rssi_max:-30
said: 4 | **LINK** peer:0x00000200 proto:espnow n:63 rssi_min:-33 rssi_med:-31 rssi_max:-31
said: 5 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 6 | **LINK** peer:0x00000010 proto:espnow n:89 rssi_min:-44 rssi_med:-42 rssi_max:-40
said: 7 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 8 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-84 rssi_med:-59 rssi_max:-55
said: 9 | **LINK** peer:0x00000012 proto:espnow n:60 rssi_min:-33 rssi_med:-31 rssi_max:-31
said: 10 | 0x00000012 ble met predicted:-48 observed:-48
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-56 observed:-56
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-31 observed:-31
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-46 observed:-47
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-59 observed:-59
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON26569 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 40959409 ±0 frame:7000
seq: 2926
follows: 0x00000010:524 0x00000011:456 0x00000012:374 0x00000100:725 0x00000200:1150
said: 1 | **ACOUSTICWIN** t_ms:41074751 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3167 rate:8000
said: 2 | **ACOUSTIC** rms_mean:133 rms_max:3311 peak:3550 transients:6
said: 3 | **TRANSIENT** t_ms:41066538 stream:0x3c4214c9 wall:0 rms:2858
```

---

@LAT105LON2146 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 40915680 ±21 frame:7000
seq: 373
follows: 0x00000010:523 0x00000011:455 0x00000100:725 0x00000200:1149 0x00000300:2924
said: 1 | **LINKWIN** t_ms:41030994 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-50 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-26 rssi_med:-24 rssi_max:-24
said: 4 | **LINK** peer:0x00000300 proto:espnow n:160 rssi_min:-26 rssi_med:-25 rssi_max:-24
said: 5 | **LINK** peer:0x00000200 proto:espnow n:97 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 6 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-80 rssi_med:-39 rssi_max:-38
said: 7 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-81 rssi_med:-41 rssi_max:-41
said: 8 | **LINK** peer:0x00000011 proto:espnow n:92 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 9 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-54 rssi_max:-50
```

---

@LAT105LON2147 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 40885631 ±21 frame:7000
seq: 455
follows: 0x00000010:522 0x00000012:372 0x00000100:724 0x00000200:1149 0x00000300:2922
said: 1 | **LINKWIN** t_ms:41000973 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-81 rssi_med:-72 rssi_max:-69
said: 3 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-81 rssi_med:-43 rssi_max:-39
said: 4 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-31 rssi_med:-28 rssi_max:-27
said: 5 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-62 rssi_med:-60 rssi_max:-58
said: 6 | **LINK** peer:0x00000100 proto:espnow n:87 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000300 proto:espnow n:195 rssi_min:-38 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-49 rssi_max:-48
```

---

@LAT105LON2148 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 40975679 ±21 frame:7000
seq: 375
follows: 0x00000010:524 0x00000011:456 0x00000100:726 0x00000200:1150 0x00000300:2926
said: 1 | **LINKWIN** t_ms:41090993 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:68 rssi_min:-43 rssi_med:-40 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:117 rssi_min:-26 rssi_med:-25 rssi_max:-24
said: 4 | **LINK** peer:0x00000010 proto:espnow n:53 rssi_min:-42 rssi_med:-40 rssi_max:-35
said: 5 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-26 rssi_med:-24 rssi_max:-24
said: 6 | **LINK** peer:0x00000200 proto:espnow n:45 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 7 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-80 rssi_med:-54 rssi_max:-50
said: 8 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-51 rssi_max:-46
said: 9 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-80 rssi_med:-42 rssi_max:-41
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:1250 last_ms:13105774
t_ms:41134360 stream:0x3c4214c9 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:590 last_ms:13105214
t_ms:41134360 stream:0x3c4214c9 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:254 half_life_ms:600000 reinforced:327 last_ms:13100476
t_ms:41134360 stream:0x3c4214c9 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:253 half_life_ms:600000 reinforced:463 last_ms:13094032
t_ms:41134360 stream:0x3c4214c9 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:654 last_ms:13107104
t_ms:41134360 stream:0x3c4214c9 wall:0

---

@LAT101LON5 | sid:499db878 | created:0 | updated:0 |
**PEER** node:0x00000001 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:41134360 stream:0x3c4214c9 wall:0

---

@LAT103LON2203 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41023118 ±0 frame:7000
seq: 2927
follows: 0x00000010:525 0x00000011:457 0x00000012:375 0x00000100:727 0x00000200:1151
said: 1 | **LINKWIN** t_ms:41138460 stream:0x3c4214c9 wall:0 window_ms:63709
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-47 rssi_max:-44
said: 3 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-64 rssi_med:-56 rssi_max:-54
said: 4 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-48 rssi_max:-47
said: 5 | **LINK** peer:0x00000012 proto:espnow n:155 rssi_min:-33 rssi_med:-31 rssi_max:-31
said: 6 | **LINK** peer:0x00000100 proto:espnow n:80 rssi_min:-31 rssi_med:-30 rssi_max:-28
said: 7 | **LINK** peer:0x00000010 proto:espnow n:97 rssi_min:-44 rssi_med:-41 rssi_max:-40
said: 8 | **LINK** peer:0x00000200 proto:espnow n:73 rssi_min:-32 rssi_med:-31 rssi_max:-31
said: 9 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-85 rssi_med:-59 rssi_max:-55
said: 10 | 0x00000200 ble met predicted:-47 observed:-47
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-31 observed:-31
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 ble met predicted:-56 observed:-56
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-42 observed:-41
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-48 observed:-48
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-59 observed:-59
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON26570 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41023118 ±0 frame:7000
seq: 2928
follows: 0x00000010:525 0x00000011:457 0x00000012:375 0x00000100:727 0x00000200:1151
said: 1 | **ACOUSTICWIN** t_ms:41138460 stream:0x3c4214c9 wall:0 window_ms:63709 blocks:3440 rate:8000
said: 2 | **ACOUSTIC** rms_mean:176 rms_max:5373 peak:5709 transients:10
said: 3 | **TRANSIENT** t_ms:41112398 stream:0x3c4214c9 wall:0 rms:3618
```

---

@LAT105LON2149 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 40945654 ±21 frame:7000
seq: 456
follows: 0x00000010:524 0x00000012:374 0x00000100:725 0x00000200:1150 0x00000300:2924
said: 1 | **LINKWIN** t_ms:41060995 stream:0x3c4214c9 wall:0 window_ms:60022
said: 2 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-57 rssi_med:-55 rssi_max:-49
said: 3 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-43 rssi_max:-40
said: 4 | **LINK** peer:0x00000300 proto:espnow n:115 rssi_min:-39 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-81 rssi_med:-73 rssi_max:-69
said: 6 | **LINK** peer:0x00000012 proto:espnow n:61 rssi_min:-42 rssi_med:-40 rssi_max:-36
said: 7 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-81 rssi_med:-50 rssi_max:-48
said: 8 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000200 proto:espnow n:69 rssi_min:-62 rssi_med:-60 rssi_max:-59
```

---

@LAT103LON2204 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41083118 ±0 frame:7000
seq: 2929
follows: 0x00000010:526 0x00000011:458 0x00000012:376 0x00000100:728 0x00000200:1152
said: 1 | **LINKWIN** t_ms:41198460 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 3 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-53 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000012 proto:espnow n:84 rssi_min:-33 rssi_med:-31 rssi_max:-28
said: 5 | **LINK** peer:0x00000100 proto:espnow n:104 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 6 | **LINK** peer:0x00000010 proto:espnow n:92 rssi_min:-44 rssi_med:-42 rssi_max:-40
said: 7 | **LINK** peer:0x00000200 proto:espnow n:52 rssi_min:-32 rssi_med:-31 rssi_max:-31
said: 8 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-56 rssi_med:-47 rssi_max:-43
said: 9 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-84 rssi_med:-59 rssi_max:-55
said: 10 | 0x00000200 ble met predicted:-47 observed:-47
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-56 observed:-56
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000012 ble met predicted:-48 observed:-48
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-41 observed:-42
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000200 espnow met predicted:-31 observed:-31
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000010 ble met predicted:-59 observed:-59
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON26571 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41083118 ±0 frame:7000
seq: 2930
follows: 0x00000010:526 0x00000011:458 0x00000012:376 0x00000100:728 0x00000200:1152
said: 1 | **ACOUSTICWIN** t_ms:41198460 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3711 rate:8000
said: 2 | **ACOUSTIC** rms_mean:108 rms_max:302 peak:674 transients:0
```

---

@LAT105LON2150 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 41005652 ±21 frame:7000
seq: 457
follows: 0x00000010:525 0x00000012:375 0x00000100:727 0x00000200:1151 0x00000300:2926
said: 1 | **LINKWIN** t_ms:41120994 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-43 rssi_max:-39
said: 4 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-38 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-73 rssi_max:-69
said: 6 | **LINK** peer:0x00000012 proto:espnow n:125 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 7 | **LINK** peer:0x00000200 proto:espnow n:64 rssi_min:-61 rssi_med:-60 rssi_max:-59
said: 8 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-32 rssi_med:-31 rssi_max:-30
```

---

@LAT105LON2151 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 41035679 ±21 frame:7000
seq: 376
follows: 0x00000010:525 0x00000011:457 0x00000100:728 0x00000200:1151 0x00000300:2928
said: 1 | **LINKWIN** t_ms:41150994 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:113 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 3 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-26 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000300 proto:espnow n:138 rssi_min:-26 rssi_med:-25 rssi_max:-22
said: 5 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-80 rssi_med:-50 rssi_max:-46
said: 6 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-39 rssi_max:-37
said: 7 | **LINK** peer:0x00000010 proto:espnow n:97 rssi_min:-42 rssi_med:-39 rssi_max:-35
said: 8 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-42 rssi_max:-41
said: 9 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-50
```

---

@LAT105LON2152 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 40921714 ±21 frame:7000
seq: 1150
follows: 0x00000010:523 0x00000011:455 0x00000012:373 0x00000100:725 0x00000300:2924
said: 1 | **LINKWIN** t_ms:41037048 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 3 | **LINK** peer:0x00000300 proto:espnow n:122 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 4 | **LINK** peer:0x00000100 proto:espnow n:76 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 5 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-58 rssi_med:-56 rssi_max:-55
said: 6 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 7 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-69 rssi_max:-65
said: 8 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-79 rssi_med:-44 rssi_max:-42
said: 9 | **LINK** peer:0x00000010 proto:ble n:70 rssi_min:-79 rssi_med:-59 rssi_max:-55
```

---

@LAT105LON2153 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 41065655 ±21 frame:7000
seq: 458
follows: 0x00000010:526 0x00000012:376 0x00000100:728 0x00000200:1152 0x00000300:2928
said: 1 | **LINKWIN** t_ms:41180995 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:98 rssi_min:-61 rssi_med:-60 rssi_max:-59
said: 3 | **LINK** peer:0x00000300 proto:espnow n:102 rssi_min:-38 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-55 rssi_max:-50
said: 5 | **LINK** peer:0x00000100 proto:espnow n:95 rssi_min:-32 rssi_med:-31 rssi_max:-29
said: 6 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-72 rssi_max:-69
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-43 rssi_max:-40
said: 8 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-83 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000010 proto:espnow n:66 rssi_min:-30 rssi_med:-29 rssi_max:-27
```

---

@LAT103LON8355 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 41126297 ±0 frame:7000
seq: 2931
follows: 0x00000010:527 0x00000011:458 0x00000012:377 0x00000100:729 0x00000200:1153
said: 1 | **ENTWIN** t_ms:41241639 stream:0x3c4214c9 wall:0 window_ms:600000 entities:5
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 7 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 8 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,84a329c78fec,e6b32d2cea8b,64677217947d
said: 9 | **COVERED** windows:2 entities:8 window_ms:1200011 first_t_ms:40041627 last_t_ms:40641639 covered_by:@LAT103LON8354
said: 10 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-42 windows:2
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-70 windows:2
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-76 windows:2
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-83 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-85 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-87 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87 windows:1
```

---

@LAT105LON2154 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 41095698 ±21 frame:7000
seq: 377
follows: 0x00000010:526 0x00000011:458 0x00000100:729 0x00000200:1152 0x00000300:2930
said: 1 | **LINKWIN** t_ms:41211011 stream:0x3c4214c9 wall:0 window_ms:60017
said: 2 | **LINK** peer:0x00000011 proto:espnow n:95 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:103 rssi_min:-26 rssi_med:-25 rssi_max:-24
said: 4 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-39 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-42 rssi_max:-41
said: 6 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 7 | **LINK** peer:0x00000100 proto:espnow n:79 rssi_min:-26 rssi_med:-24 rssi_max:-24
said: 8 | **LINK** peer:0x00000010 proto:espnow n:75 rssi_min:-42 rssi_med:-39 rssi_max:-35
said: 9 | **LINK** peer:0x00000200 proto:espnow n:34 rssi_min:-29 rssi_med:-28 rssi_max:-28
```

---

@LAT103LON2205 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41143118 ±0 frame:7000
seq: 2932
follows: 0x00000010:527 0x00000011:459 0x00000012:377 0x00000100:729 0x00000200:1153
said: 1 | **LINKWIN** t_ms:41258460 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:71 rssi_min:-31 rssi_med:-30 rssi_max:-30
said: 3 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-81 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:ble n:50 rssi_min:-56 rssi_med:-47 rssi_max:-44
said: 5 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-33 rssi_med:-31 rssi_max:-31
said: 6 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-64 rssi_med:-56 rssi_max:-52
said: 7 | **LINK** peer:0x00000010 proto:espnow n:44 rssi_min:-44 rssi_med:-42 rssi_max:-40
said: 8 | **LINK** peer:0x00000010 proto:ble n:41 rssi_min:-83 rssi_med:-58 rssi_max:-55
said: 9 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 10 | 0x00000011 ble met predicted:-56 observed:-56
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-48 observed:-48
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow unobserved predicted:-31 observed:-31
percept: 15 | 0x00000200 | link_stable | espnow | ? | -
said: 16 | 0x00000200 ble met predicted:-47 observed:-47
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-59 observed:-58
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON26572 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41143118 ±0 frame:7000
seq: 2933
follows: 0x00000010:527 0x00000011:459 0x00000012:377 0x00000100:729 0x00000200:1153
said: 1 | **ACOUSTICWIN** t_ms:41258460 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3662 rate:8000
said: 2 | **ACOUSTIC** rms_mean:109 rms_max:326 peak:557 transients:0
```

---

@LAT105LON2155 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 41125655 ±21 frame:7000
seq: 459
follows: 0x00000010:527 0x00000012:377 0x00000100:729 0x00000200:1153 0x00000300:2930
said: 1 | **LINKWIN** t_ms:41240994 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-72 rssi_max:-69
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-82 rssi_med:-50 rssi_max:-48
said: 4 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-43 rssi_max:-39
said: 5 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-55 rssi_max:-50
said: 6 | **LINK** peer:0x00000012 proto:espnow n:123 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 7 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-30 rssi_med:-28 rssi_max:-27
said: 8 | **LINK** peer:0x00000100 proto:espnow n:74 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000300 proto:espnow n:114 rssi_min:-39 rssi_med:-34 rssi_max:-33
```

---

@LAT103LON2206 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41203118 ±0 frame:7000
seq: 2934
follows: 0x00000010:528 0x00000011:460 0x00000012:378 0x00000100:730 0x00000200:1154
said: 1 | **LINKWIN** t_ms:41318460 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:69 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-57 rssi_med:-47 rssi_max:-44
said: 4 | **LINK** peer:0x00000010 proto:ble n:46 rssi_min:-83 rssi_med:-58 rssi_max:-55
said: 5 | **LINK** peer:0x00000100 proto:espnow n:74 rssi_min:-31 rssi_med:-30 rssi_max:-30
said: 6 | **LINK** peer:0x00000012 proto:espnow n:70 rssi_min:-34 rssi_med:-31 rssi_max:-31
said: 7 | **LINK** peer:0x00000010 proto:espnow n:108 rssi_min:-44 rssi_med:-41 rssi_max:-40
said: 8 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-79 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-41 rssi_med:-40 rssi_max:-39
said: 10 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000012 ble met predicted:-48 observed:-48
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000200 ble met predicted:-47 observed:-47
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-56 observed:-56
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-42 observed:-41
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-58 observed:-58
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow met predicted:-40 observed:-40
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON26573 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41203118 ±0 frame:7000
seq: 2935
follows: 0x00000010:528 0x00000011:460 0x00000012:378 0x00000100:730 0x00000200:1154
said: 1 | **ACOUSTICWIN** t_ms:41318460 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3468 rate:8000
said: 2 | **ACOUSTIC** rms_mean:121 rms_max:532 peak:940 transients:0
```

---

@LAT105LON2156 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 41185655 ±21 frame:7000
seq: 460
follows: 0x00000010:528 0x00000012:378 0x00000100:730 0x00000200:1154 0x00000300:2933
said: 1 | **LINKWIN** t_ms:41300995 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-72 rssi_max:-69
said: 3 | **LINK** peer:0x00000100 proto:espnow n:78 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 4 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 5 | **LINK** peer:0x00000010 proto:espnow n:82 rssi_min:-30 rssi_med:-28 rssi_max:-27
said: 6 | **LINK** peer:0x00000300 proto:espnow n:143 rssi_min:-39 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-61 rssi_med:-60 rssi_max:-59
said: 8 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-43 rssi_max:-40
```

---

@LAT105LON2157 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 41155697 ±21 frame:7000
seq: 378
follows: 0x00000010:527 0x00000011:459 0x00000100:730 0x00000200:1153 0x00000300:2933
said: 1 | **LINKWIN** t_ms:41271011 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-80 rssi_med:-54 rssi_max:-50
said: 3 | **LINK** peer:0x00000011 proto:espnow n:101 rssi_min:-43 rssi_med:-40 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-39 rssi_max:-37
said: 5 | **LINK** peer:0x00000300 proto:espnow n:149 rssi_min:-27 rssi_med:-25 rssi_max:-24
said: 6 | **LINK** peer:0x00000010 proto:espnow n:61 rssi_min:-42 rssi_med:-40 rssi_max:-35
said: 7 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-42 rssi_max:-41
said: 8 | **LINK** peer:0x00000100 proto:espnow n:81 rssi_min:-26 rssi_med:-24 rssi_max:-24
said: 9 | **LINK** peer:0x00000200 proto:espnow n:82 rssi_min:-30 rssi_med:-28 rssi_max:-28
```

---

@LAT105LON2158 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 40981715 ±21 frame:7000
seq: 1151
follows: 0x00000010:524 0x00000011:456 0x00000012:375 0x00000100:726 0x00000300:2926
said: 1 | **LINKWIN** t_ms:41097048 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 3 | **LINK** peer:0x00000012 proto:espnow n:101 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 4 | **LINK** peer:0x00000010 proto:espnow n:67 rssi_min:-48 rssi_med:-46 rssi_max:-44
said: 5 | **LINK** peer:0x00000300 proto:espnow n:132 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 6 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-61 rssi_med:-56 rssi_max:-55
said: 7 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-79 rssi_med:-69 rssi_max:-66
said: 8 | **LINK** peer:0x00000011 proto:espnow n:80 rssi_min:-58 rssi_med:-57 rssi_max:-55
said: 9 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-51 rssi_med:-44 rssi_max:-42
```

---

@LAT105LON2159 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 41215698 ±21 frame:7000
seq: 379
follows: 0x00000010:528 0x00000011:460 0x00000100:731 0x00000200:1154 0x00000300:2935
said: 1 | **LINKWIN** t_ms:41331011 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-54 rssi_max:-50
said: 3 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 4 | **LINK** peer:0x00000300 proto:espnow n:177 rssi_min:-26 rssi_med:-25 rssi_max:-24
said: 5 | **LINK** peer:0x00000100 proto:espnow n:75 rssi_min:-25 rssi_med:-24 rssi_max:-24
said: 6 | **LINK** peer:0x00000010 proto:ble n:72 rssi_min:-81 rssi_med:-50 rssi_max:-46
said: 7 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-42 rssi_max:-41
said: 8 | **LINK** peer:0x00000010 proto:espnow n:108 rssi_min:-42 rssi_med:-39 rssi_max:-35
said: 9 | **LINK** peer:0x00000200 proto:espnow n:62 rssi_min:-30 rssi_med:-28 rssi_max:-28
```

---

@LAT103LON2207 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 41263118 ±0 frame:7000
seq: 2936
follows: 0x00000010:528 0x00000011:461 0x00000012:379 0x00000100:731 0x00000200:1155
said: 1 | **LINKWIN** t_ms:41378460 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-64 rssi_med:-56 rssi_max:-52
said: 3 | **LINK** peer:0x00000100 proto:espnow n:90 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 4 | **LINK** peer:0x00000200 proto:espnow n:96 rssi_min:-33 rssi_med:-31 rssi_max:-31
said: 5 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-45 rssi_med:-41 rssi_max:-40
said: 6 | **LINK** peer:0x00000010 proto:ble n:36 rssi_min:-86 rssi_med:-58 rssi_max:-54
said: 7 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-56 rssi_med:-47 rssi_max:-44
said: 8 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-52 rssi_med:-48 rssi_max:-47
said: 9 | **LINK** peer:0x00000012 proto:espnow n:116 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 10 | 0x00000012 ble met predicted:-48 observed:-48
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-47 observed:-47
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-58 observed:-58
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-30 observed:-30
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-31 observed:-31
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-41 observed:-41
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-56 observed:-56
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow unobserved predicted:-40 observed:-40
percept: 17 | 0x00000011 | link_stable | espnow | ? | -
```

---

@LAT103LON26574 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 41263118 ±0 frame:7000
seq: 2937
follows: 0x00000010:528 0x00000011:461 0x00000012:379 0x00000100:731 0x00000200:1155
said: 1 | **ACOUSTICWIN** t_ms:41378460 stream:0x3c4214c9 wall:0 window_ms:60000 blocks:3675 rate:8000
said: 2 | **ACOUSTIC** rms_mean:154 rms_max:5760 peak:9356 transients:7
said: 3 | **TRANSIENT** t_ms:41368839 stream:0x3c4214c9 wall:0 rms:5084
```

---

@LAT105LON2160 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 41041715 ±21 frame:7000
seq: 1152
follows: 0x00000010:526 0x00000011:457 0x00000012:376 0x00000100:728 0x00000300:2928
said: 1 | **LINKWIN** t_ms:41157048 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-80 rssi_med:-69 rssi_max:-65
said: 3 | **LINK** peer:0x00000012 proto:espnow n:87 rssi_min:-33 rssi_med:-31 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:espnow n:81 rssi_min:-58 rssi_med:-56 rssi_max:-55
said: 5 | **LINK** peer:0x00000300 proto:espnow n:144 rssi_min:-30 rssi_med:-28 rssi_max:-28
said: 6 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-56 rssi_max:-55
said: 7 | **LINK** peer:0x00000010 proto:espnow n:58 rssi_min:-48 rssi_med:-46 rssi_max:-44
said: 8 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000100 proto:espnow n:75 rssi_min:-31 rssi_med:-29 rssi_max:-29
```

---

@LAT105LON2161 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 39358682 ±21 frame:7000
seq: 497
follows: 0x00000011:427 0x00000012:347 0x00000100:697 0x00000200:1122 0x00000300:2871
said: 1 | **LINKWIN** t_ms:39474023 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-38 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:133 rssi_min:-35 rssi_med:-33 rssi_max:-32
said: 4 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 5 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 6 | **LINK** peer:0x00000011 proto:espnow n:56 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 7 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-53 rssi_med:-48 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-79 rssi_med:-52 rssi_max:-43
said: 9 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-44 rssi_med:-41 rssi_max:-40
```

---

@LAT103LON2208 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 72807 ±0 frame:20500
seq: 2938
follows: 0x00000010:530 0x00000011:461 0x00000012:379 0x00000100:732 0x00000200:1155
said: 1 | **LINKWIN** t_ms:56641 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:31 rssi_min:-49 rssi_med:-43 rssi_max:-38
said: 3 | **LINK** peer:0x00000010 proto:ble n:45 rssi_min:-81 rssi_med:-60 rssi_max:-55
```

---

@LAT104LON482 | created:0 | updated:0

**carried through @LAT103LON2168**

```ttdb-carried
through: 2168
through: 8308
through: 16464
through: 26555
carried: 1439 27 1665 1420 | 0x00000200 | link_stable | espnow
carried: 1565 18 1939 1466 | 0x00000200 | link_stable | ble
carried: 886 13 1252 778 | 0x00000100 | link_stable | espnow
carried: 884 13 1251 781 | 0x00000010 | link_stable | ble
carried: 823 24 1200 744 | 0x00000010 | link_stable | espnow
carried: 395 7 402 427 | 0x00000011 | link_stable | ble
carried: 333 16 349 365 | 0x00000011 | link_stable | espnow
carried: 340 5 345 360 | 0x00000012 | link_stable | ble
carried: 315 7 322 344 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON8356 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 72807 ±0 frame:20500
seq: 2939
follows: 0x00000010:530 0x00000011:461 0x00000012:379 0x00000100:732 0x00000200:1155
said: 1 | **ENTWIN** t_ms:56641 stream:0xa0be1a79 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON16484 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 72807 ±0 frame:20500
seq: 2940
follows: 0x00000010:530 0x00000011:461 0x00000012:379 0x00000100:732 0x00000200:1155
said: 1 | **MOTIONWIN** t_ms:56641 stream:0xa0be1a79 wall:0 window_ms:60000 n:879
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:5 dev_max_mg:9 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON26575 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 72807 ±0 frame:20500
seq: 2941
follows: 0x00000010:530 0x00000011:461 0x00000012:379 0x00000100:732 0x00000200:1155
said: 1 | **ACOUSTICWIN** t_ms:56641 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3292 rate:8000
said: 2 | **ACOUSTIC** rms_mean:82 rms_max:1212 peak:3924 transients:2
said: 3 | **TRANSIENT** t_ms:11211 stream:0xa0be1a79 wall:0 rms:1212
```

---

@LAT105LON2162 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 39418714 ±21 frame:7000
seq: 498
follows: 0x00000011:428 0x00000012:348 0x00000100:698 0x00000200:1123 0x00000300:2873
said: 1 | **LINKWIN** t_ms:39534056 stream:0x3c4214c9 wall:0 window_ms:60032
said: 2 | **LINK** peer:0x00000200 proto:espnow n:81 rssi_min:-44 rssi_med:-44 rssi_max:-44
said: 3 | **LINK** peer:0x00000300 proto:espnow n:162 rssi_min:-36 rssi_med:-33 rssi_max:-32
said: 4 | **LINK** peer:0x00000100 proto:espnow n:73 rssi_min:-38 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000012 proto:espnow n:86 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-72 rssi_med:-52 rssi_max:-43
said: 8 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-79 rssi_med:-48 rssi_max:-47
said: 9 | **LINK** peer:0x00000011 proto:espnow n:139 rssi_min:-30 rssi_med:-28 rssi_max:-28
```

---

@LAT105LON2163 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 39478715 ±21 frame:7000
seq: 499
follows: 0x00000011:429 0x00000012:348 0x00000100:698 0x00000200:1124 0x00000300:2875
said: 1 | **LINKWIN** t_ms:39594056 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-38 rssi_med:-34 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:123 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:espnow n:197 rssi_min:-35 rssi_med:-33 rssi_max:-31
said: 5 | **LINK** peer:0x00000011 proto:espnow n:69 rssi_min:-28 rssi_med:-28 rssi_max:-28
said: 6 | **LINK** peer:0x00000012 proto:espnow n:87 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-79 rssi_med:-52 rssi_max:-43
said: 8 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-52 rssi_med:-48 rssi_max:-47
said: 9 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-45 rssi_med:-41 rssi_max:-39
```

---

@LAT105LON2164 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 39538715 ±21 frame:7000
seq: 500
follows: 0x00000011:430 0x00000012:350 0x00000100:700 0x00000200:1125 0x00000300:2877
said: 1 | **LINKWIN** t_ms:39654056 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-73 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-39 rssi_med:-34 rssi_max:-33
said: 4 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-48 rssi_max:-47
said: 5 | **LINK** peer:0x00000200 proto:espnow n:124 rssi_min:-44 rssi_med:-44 rssi_max:-44
said: 6 | **LINK** peer:0x00000300 proto:espnow n:137 rssi_min:-36 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-56 rssi_med:-52 rssi_max:-43
said: 8 | **LINK** peer:0x00000012 proto:espnow n:95 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-58 rssi_med:-55 rssi_max:-52
```

---

@LAT105LON2165 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 39598778 ±21 frame:7000
seq: 501
follows: 0x00000011:431 0x00000012:351 0x00000100:701 0x00000200:1126 0x00000300:2879
said: 1 | **LINKWIN** t_ms:39714069 stream:0x3c4214c9 wall:0 window_ms:60062
said: 2 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-44 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000012 proto:espnow n:81 rssi_min:-42 rssi_med:-41 rssi_max:-38
said: 4 | **LINK** peer:0x00000100 proto:espnow n:76 rssi_min:-39 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000011 proto:espnow n:88 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 6 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-81 rssi_med:-52 rssi_max:-43
said: 7 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:espnow n:136 rssi_min:-44 rssi_med:-44 rssi_max:-44
said: 9 | **LINK** peer:0x00000300 proto:espnow n:178 rssi_min:-36 rssi_med:-33 rssi_max:-32
```

---

@LAT103LON2209 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 132807 ±0 frame:20500
seq: 2942
follows: 0x00000010:532 0x00000011:461 0x00000012:379 0x00000100:732 0x00000200:1155
said: 1 | **LINKWIN** t_ms:116641 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:75 rssi_min:-49 rssi_med:-47 rssi_max:-45
said: 3 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-61 rssi_max:-57
said: 4 | 0x00000010 espnow met predicted:-43 observed:-47
percept: 4 | 0x00000010 | link_stable | espnow | + | -
said: 5 | 0x00000010 ble met predicted:-60 observed:-61
percept: 5 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON26576 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 132807 ±0 frame:20500
seq: 2943
follows: 0x00000010:532 0x00000011:461 0x00000012:379 0x00000100:732 0x00000200:1155
said: 1 | **ACOUSTICWIN** t_ms:116641 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3668 rate:8000
said: 2 | **ACOUSTIC** rms_mean:84 rms_max:445 peak:2042 transients:0
```

---

@LAT105LON2166 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 39658779 ±21 frame:7000
seq: 502
follows: 0x00000011:432 0x00000012:352 0x00000100:702 0x00000200:1127 0x00000300:2881
said: 1 | **LINKWIN** t_ms:39774117 stream:0x3c4214c9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:105 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:espnow n:154 rssi_min:-35 rssi_med:-33 rssi_max:-30
said: 4 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-38 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-52 rssi_med:-48 rssi_max:-47
said: 6 | **LINK** peer:0x00000200 proto:espnow n:71 rssi_min:-44 rssi_med:-44 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:espnow n:67 rssi_min:-29 rssi_med:-28 rssi_max:-27
said: 8 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-56 rssi_med:-52 rssi_max:-43
said: 9 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-44 rssi_med:-41 rssi_max:-40
```
