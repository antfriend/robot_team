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

@LAT103LON3123 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2603209 ±0 frame:11000
seq: 4908
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2120
said: 1 | **LINKWIN** t_ms:2589653 stream:0xed9951d6 wall:0 window_ms:62515
said: 2 | **LINK** peer:0x00000100 proto:espnow n:12 rssi_min:-42 rssi_med:-39 rssi_max:-35
said: 3 | 0x00000100 espnow met predicted:-37 observed:-39
percept: 3 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON3124 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 146547 ±0 frame:10000
seq: 4928
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2120
said: 1 | **LINKWIN** t_ms:134040 stream:0x678473b9 wall:0 window_ms:146547
said: 2 | **LINK** peer:0x00000200 proto:ble n:1 rssi_min:-58 rssi_med:-58 rssi_max:-58
```

---

@LAT105LON5839 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 59993 ±21 frame:8500
seq: 2121
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4929
said: 1 | **LINKWIN** t_ms:187868 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:90 rssi_min:-46 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-73 rssi_med:-52 rssi_max:-46
```

---

@LAT103LON3125 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 66165 ±0 frame:8500
seq: 4930
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2122
said: 1 | **LINKWIN** t_ms:194040 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-73 rssi_med:-56 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:86 rssi_min:-49 rssi_med:-40 rssi_max:-38
said: 4 | 0x00000200 ble met predicted:-58 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON3126 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 126602 ±0 frame:8500
seq: 4932
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2123
said: 1 | **LINKWIN** t_ms:254477 stream:0x678473b9 wall:0 window_ms:60437
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-62 rssi_med:-55 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:espnow n:69 rssi_min:-45 rssi_med:-42 rssi_max:-39
said: 4 | 0x00000200 ble met predicted:-56 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-40 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON5840 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 117996 ±21 frame:8500
seq: 2123
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4930
said: 1 | **LINKWIN** t_ms:247868 stream:0x678473b9 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000300 proto:espnow n:97 rssi_min:-42 rssi_med:-37 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-49
```

---

@LAT103LON3127 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 188544 ±0 frame:8500
seq: 4934
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2123
said: 1 | **LINKWIN** t_ms:316419 stream:0x678473b9 wall:0 window_ms:61942
said: 2 | **LINK** peer:0x00000200 proto:espnow n:54 rssi_min:-42 rssi_med:-41 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-63 rssi_med:-56 rssi_max:-51
said: 4 | 0x00000200 ble met predicted:-55 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-42 observed:-41
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON3128 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 269381 ±0 frame:8500
seq: 4936
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2125
said: 1 | **LINKWIN** t_ms:397256 stream:0x678473b9 wall:0 window_ms:80837
said: 2 | **LINK** peer:0x00000200 proto:espnow n:68 rssi_min:-45 rssi_med:-42 rssi_max:-40
said: 3 | **LINK** peer:0x00000200 proto:ble n:79 rssi_min:-68 rssi_med:-56 rssi_max:-53
said: 4 | 0x00000200 espnow met predicted:-41 observed:-42
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-56 observed:-56
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5841 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 175992 ±21 frame:8500
seq: 2124
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4933
said: 1 | **LINKWIN** t_ms:307869 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-61 rssi_med:-52 rssi_max:-46
said: 3 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-40 rssi_med:-36 rssi_max:-33
```

---

@LAT105LON5842 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 235995 ±21 frame:8500
seq: 2125
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4935
said: 1 | **LINKWIN** t_ms:367869 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-38 rssi_med:-36 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-60 rssi_med:-53 rssi_max:-48
```

---

@LAT105LON5843 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 297998 ±21 frame:8500
seq: 2126
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4936
said: 1 | **LINKWIN** t_ms:427868 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:31 rssi_min:-39 rssi_med:-36 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-80 rssi_med:-54 rssi_max:-48
```

---

@LAT105LON5844 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 351998 ±23 frame:8500
seq: 2127
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4937
said: 1 | **LINKWIN** t_ms:487869 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:29 rssi_min:-58 rssi_med:-54 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:25 rssi_min:-37 rssi_med:-35 rssi_max:-35
```

---

@LAT103LON3129 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 405430 ±21 frame:8500
seq: 4938
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2127
said: 1 | **LINKWIN** t_ms:541301 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-54 rssi_med:-46 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:49 rssi_min:-80 rssi_med:-58 rssi_max:-53
```

---

@LAT103LON3130 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 467942 ±23 frame:8500
seq: 4942
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2128
said: 1 | **LINKWIN** t_ms:603813 stream:0x678473b9 wall:0 window_ms:62512
said: 2 | **LINK** peer:0x00000200 proto:ble n:44 rssi_min:-74 rssi_med:-56 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-57 rssi_med:-43 rssi_max:-39
said: 4 | 0x00000200 espnow met predicted:-46 observed:-43
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-58 observed:-56
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5845 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 411998 ±0 frame:8500
seq: 2128
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4941
said: 1 | **LINKWIN** t_ms:547869 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:79 rssi_min:-51 rssi_med:-40 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-81 rssi_med:-55 rssi_max:-49
```

---

@LAT105LON5846 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 60000 ±0 frame:9500
seq: 2129
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:4943
said: 1 | **LINKWIN** t_ms:643355 stream:0x678473b9 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:40 rssi_min:-38 rssi_med:-36 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-81 rssi_med:-54 rssi_max:-47
```

---

@LAT103LON3131 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 536058 ±0 frame:8500
seq: 4944
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2130
said: 1 | **LINKWIN** t_ms:671929 stream:0x678473b9 wall:0 window_ms:68116
said: 2 | **LINK** peer:0x00000200 proto:espnow n:82 rssi_min:-51 rssi_med:-40 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:ble n:74 rssi_min:-67 rssi_med:-56 rssi_max:-49
said: 4 | 0x00000200 ble met predicted:-56 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-43 observed:-40
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON3132 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 596565 ±0 frame:8500
seq: 4946
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2130
said: 1 | **LINKWIN** t_ms:732436 stream:0x678473b9 wall:0 window_ms:60507
said: 2 | **LINK** peer:0x00000200 proto:espnow n:9 rssi_min:-53 rssi_med:-50 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:ble n:19 rssi_min:-65 rssi_med:-61 rssi_max:-50
said: 4 | 0x00000200 espnow violated predicted:-40 observed:-50
percept: 4 | 0x00000200 | link_stable | espnow | - | -
said: 5 | 0x00000200 ble met predicted:-56 observed:-61
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON3133 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3174837 ±0 frame:12000
seq: 5028
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2130
said: 1 | **LINKWIN** t_ms:3160130 stream:0xf569ab0e wall:0 window_ms:3174837
said: 2 | **LINK** peer:0x00000200 proto:espnow n:9 rssi_min:-38 rssi_med:-36 rssi_max:-35
said: 3 | **LINK** peer:0x00000200 proto:ble n:19 rssi_min:-56 rssi_med:-52 rssi_max:-49
```

---

@LAT103LON3134 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 70272 ±0 frame:8500
seq: 5030
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2132
said: 1 | **LINKWIN** t_ms:3223780 stream:0xf569ab0e wall:0 window_ms:63650
said: 2 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-42 rssi_med:-36 rssi_max:-33
said: 3 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-63 rssi_med:-52 rssi_max:-47
said: 4 | 0x00000200 espnow met predicted:-36 observed:-36
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-52 observed:-52
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5847 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 51993 ±21 frame:8500
seq: 2131
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5029
said: 1 | **LINKWIN** t_ms:3213502 stream:0xf569ab0e wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-47 rssi_max:-44
said: 3 | **LINK** peer:0x00000300 proto:espnow n:7 rssi_min:-34 rssi_med:-30 rssi_max:-30
```

---

@LAT103LON3135 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 133747 ±0 frame:8500
seq: 5031
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2132
said: 1 | **LINKWIN** t_ms:3287255 stream:0xf569ab0e wall:0 window_ms:63475
said: 2 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-62 rssi_med:-51 rssi_max:-46
said: 3 | **LINK** peer:0x00000200 proto:espnow n:33 rssi_min:-45 rssi_med:-34 rssi_max:-34
```

---

@LAT103LON3136 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 200489 ±0 frame:8500
seq: 5033
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2132
said: 1 | **LINKWIN** t_ms:3353997 stream:0xf569ab0e wall:0 window_ms:66742
said: 2 | **LINK** peer:0x00000200 proto:ble n:70 rssi_min:-55 rssi_med:-50 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:espnow n:41 rssi_min:-36 rssi_med:-34 rssi_max:-34
said: 4 | 0x00000200 ble met predicted:-51 observed:-50
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-34 observed:-34
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON5848 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 141212 ±21 frame:8500
seq: 2133
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5032
said: 1 | **LINKWIN** t_ms:3324773 stream:0xf569ab0e wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-46 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:9 rssi_min:-30 rssi_med:-30 rssi_max:-29
```

---

@LAT103LON3137 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 75538 ±0 frame:9500
seq: 5035
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2136
said: 1 | **LINKWIN** t_ms:63418 stream:0xdfce8729 wall:0 window_ms:60038
said: 2 | **LINK** peer:0x00000200 proto:espnow n:46 rssi_min:-48 rssi_med:-39 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:50 rssi_min:-80 rssi_med:-55 rssi_max:-50
```

---

@LAT105LON5849 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 61903 ±21 frame:9500
seq: 2135
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5034
said: 1 | **LINKWIN** t_ms:47884 stream:0xdfce8729 wall:0 window_ms:61911
said: 2 | **LINK** peer:0x00000300 proto:espnow n:35 rssi_min:-43 rssi_med:-34 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:ble n:39 rssi_min:-81 rssi_med:-52 rssi_max:-46
```

---

@LAT105LON5850 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 122306 ±21 frame:9500
seq: 2137
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5038
said: 1 | **LINKWIN** t_ms:107884 stream:0xdfce8729 wall:0 window_ms:60401
said: 2 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-39 rssi_med:-36 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-52 rssi_max:-49
```

---

@LAT103LON3138 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 135538 ±0 frame:9500
seq: 5039
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2137
said: 1 | **LINKWIN** t_ms:123418 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-55 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:57 rssi_min:-43 rssi_med:-41 rssi_max:-39
said: 4 | 0x00000200 espnow met predicted:-39 observed:-41
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-55 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5851 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 182310 ±21 frame:9500
seq: 2138
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5040
said: 1 | **LINKWIN** t_ms:170196 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-56 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:141 rssi_min:-40 rssi_med:-37 rssi_max:-34
```

---

@LAT103LON3139 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 195546 ±0 frame:9500
seq: 5041
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2138
said: 1 | **LINKWIN** t_ms:183426 stream:0xdfce8729 wall:0 window_ms:60008
said: 2 | **LINK** peer:0x00000200 proto:espnow n:67 rssi_min:-46 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-79 rssi_med:-56 rssi_max:-54
said: 4 | 0x00000200 ble met predicted:-55 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-41 observed:-42
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON5852 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 242306 ±22 frame:9500
seq: 2139
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5042
said: 1 | **LINKWIN** t_ms:230196 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:60 rssi_min:-39 rssi_med:-38 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:49 rssi_min:-59 rssi_med:-53 rssi_max:-47
```

---

@LAT103LON3140 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 60000 ±0 frame:9500
seq: 5043
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2139
said: 1 | **LINKWIN** t_ms:286568 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-80 rssi_med:-55 rssi_max:-45
said: 3 | **LINK** peer:0x00000200 proto:espnow n:40 rssi_min:-49 rssi_med:-37 rssi_max:-32
```

---

@LAT105LON5853 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 302306 ±25 frame:9500
seq: 2140
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5046
said: 1 | **LINKWIN** t_ms:290196 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-54 rssi_max:-42
said: 3 | **LINK** peer:0x00000300 proto:espnow n:61 rssi_min:-45 rssi_med:-35 rssi_max:-29
```

---

@LAT103LON3141 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 120000 ±0 frame:9500
seq: 5047
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2140
said: 1 | **LINKWIN** t_ms:346568 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:32 rssi_min:-42 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 4 | 0x00000200 ble met predicted:-55 observed:-53
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-37 observed:-37
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON5854 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 133458 ±21 frame:9500
seq: 2141
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5048
said: 1 | **LINKWIN** t_ms:358618 stream:0xdfce8729 wall:0 window_ms:61409
said: 2 | **LINK** peer:0x00000300 proto:espnow n:47 rssi_min:-37 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-80 rssi_med:-50 rssi_max:-47
```

---

@LAT103LON3142 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 180000 ±0 frame:9500
seq: 5049
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2142
said: 1 | **LINKWIN** t_ms:406568 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:61 rssi_min:-55 rssi_med:-41 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-56 rssi_max:-51
said: 4 | 0x00000200 espnow met predicted:-37 observed:-41
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-53 observed:-56
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5855 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 193459 ±21 frame:9500
seq: 2143
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5050
said: 1 | **LINKWIN** t_ms:420027 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-69 rssi_med:-52 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:69 rssi_min:-53 rssi_med:-37 rssi_max:-34
```

---

@LAT103LON3143 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 240001 ±0 frame:9500
seq: 5051
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2143
said: 1 | **LINKWIN** t_ms:466569 stream:0xdfce8729 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000200 proto:espnow n:53 rssi_min:-48 rssi_med:-38 rssi_max:-36
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-62 rssi_med:-55 rssi_max:-50
said: 4 | 0x00000200 espnow met predicted:-41 observed:-38
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-56 observed:-55
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5856 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 253460 ±21 frame:9500
seq: 2144
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:480027 stream:0xdfce8729 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:67 rssi_min:-52 rssi_med:-38 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-79 rssi_med:-54 rssi_max:-46
```

---

@LAT105LON5857 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1073202 ±0 frame:8500
seq: 2146
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:1061712 stream:0xb8b08067 wall:0 window_ms:1073202
said: 2 | **LINK** peer:0x00000300 proto:espnow n:3 rssi_min:-47 rssi_med:-47 rssi_max:-47
```

---

@LAT103LON3144 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1123505 ±22 frame:8500
seq: 5053
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2146
said: 1 | **LINKWIN** t_ms:1112020 stream:0xb8b08067 wall:0 window_ms:60074
said: 2 | **LINK** peer:0x00000200 proto:espnow n:35 rssi_min:-53 rssi_med:-51 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:ble n:44 rssi_min:-69 rssi_med:-64 rssi_max:-62
```

---

@LAT105LON5858 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 1133193 ±21 frame:8500
seq: 2147
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5052
said: 1 | **LINKWIN** t_ms:1121715 stream:0xb8b08067 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:69 rssi_min:-75 rssi_med:-61 rssi_max:-58
said: 3 | **LINK** peer:0x00000300 proto:espnow n:34 rssi_min:-91 rssi_med:-49 rssi_max:-47
```

---

@LAT103LON3145 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 60040 ±0 frame:7500
seq: 5057
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2147
said: 1 | **LINKWIN** t_ms:49855 stream:0x1f824110 wall:0 window_ms:60040
said: 2 | **LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-43 rssi_med:-42 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:ble n:48 rssi_min:-80 rssi_med:-56 rssi_max:-51
```

---

@LAT103LON3146 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 85818 ±0 frame:7500
seq: 5064
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2147
said: 1 | **LINKWIN** t_ms:75809 stream:0xad373985 wall:0 window_ms:85818
said: 2 | **LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-46 rssi_med:-46 rssi_max:-46
```

---

@LAT105LON5859 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 68995 ±21 frame:7500
seq: 2148
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5060
said: 1 | **LINKWIN** t_ms:57427 stream:0x1f824110 wall:0 window_ms:61386
said: 2 | **LINK** peer:0x00000300 proto:espnow n:39 rssi_min:-40 rssi_med:-37 rssi_max:-32
said: 3 | **LINK** peer:0x00000300 proto:ble n:50 rssi_min:-82 rssi_med:-54 rssi_max:-48
```

---

@LAT103LON3147 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 145818 ±0 frame:7500
seq: 5068
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2151
said: 1 | **LINKWIN** t_ms:135809 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:56 rssi_min:-51 rssi_med:-44 rssi_max:-33
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-67 rssi_med:-56 rssi_max:-47
said: 4 | 0x00000200 espnow met predicted:-46 observed:-44
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON5860 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 139634 ±21 frame:7500
seq: 2150
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5067
said: 1 | **LINKWIN** t_ms:129626 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:57 rssi_min:-53 rssi_med:-37 rssi_max:-29
said: 3 | **LINK** peer:0x00000300 proto:ble n:46 rssi_min:-75 rssi_med:-53 rssi_max:-44
```

---

@LAT103LON3148 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 205818 ±0 frame:7500
seq: 5070
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2151
said: 1 | **LINKWIN** t_ms:195809 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:70 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-51 rssi_med:-34 rssi_max:-27
said: 4 | 0x00000200 espnow violated predicted:-44 observed:-34
percept: 4 | 0x00000200 | link_stable | espnow | - | -
said: 5 | 0x00000200 ble met predicted:-56 observed:-50
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5861 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 199636 ±21 frame:7500
seq: 2152
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5069
said: 1 | **LINKWIN** t_ms:189626 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:73 rssi_min:-47 rssi_med:-35 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-67 rssi_med:-45 rssi_max:-37
```

---

@LAT105LON5862 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 259638 ±21 frame:7500
seq: 2153
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5071
said: 1 | **LINKWIN** t_ms:249627 stream:0xad373985 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-42 rssi_max:-39
said: 3 | **LINK** peer:0x00000300 proto:espnow n:83 rssi_min:-44 rssi_med:-27 rssi_max:-25
```

---

@LAT103LON3149 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 60000 ±0 frame:7500
seq: 5072
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2153
said: 1 | **LINKWIN** t_ms:49501 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:25 rssi_min:-80 rssi_med:-44 rssi_max:-40
said: 3 | **LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-34 rssi_med:-29 rssi_max:-28
```

---

@LAT103LON3150 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 120000 ±0 frame:7500
seq: 5076
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2155
said: 1 | **LINKWIN** t_ms:109501 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:39 rssi_min:-30 rssi_med:-28 rssi_max:-27
said: 3 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-44 rssi_max:-41
said: 4 | 0x00000200 ble met predicted:-44 observed:-44
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000200 espnow met predicted:-29 observed:-28
percept: 5 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON5863 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 95985 ±21 frame:7500
seq: 2154
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5075
said: 1 | **LINKWIN** t_ms:84171 stream:0xb4b25252 wall:0 window_ms:61315
said: 2 | **LINK** peer:0x00000300 proto:espnow n:41 rssi_min:-29 rssi_med:-24 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-40 rssi_max:-37
```

---

@LAT105LON5864 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 155984 ±21 frame:7500
seq: 2156
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5077
said: 1 | **LINKWIN** t_ms:145486 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:64 rssi_min:-28 rssi_med:-25 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-70 rssi_med:-40 rssi_max:-36
```

---

@LAT103LON3151 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 180039 ±0 frame:7500
seq: 5078
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2156
said: 1 | **LINKWIN** t_ms:169540 stream:0xb4b25252 wall:0 window_ms:60039
said: 2 | **LINK** peer:0x00000200 proto:espnow n:59 rssi_min:-31 rssi_med:-29 rssi_max:-27
said: 3 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-45 rssi_max:-41
said: 4 | 0x00000200 espnow met predicted:-28 observed:-29
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-44 observed:-45
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5865 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 215985 ±21 frame:7500
seq: 2157
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5079
said: 1 | **LINKWIN** t_ms:205486 stream:0xb4b25252 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:64 rssi_min:-26 rssi_med:-25 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-47 rssi_med:-41 rssi_max:-37
```

---

@LAT103LON3152 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 86407 ±0 frame:10500
seq: 5083
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2156
said: 1 | **LINKWIN** t_ms:73043 stream:0x3bead35c wall:0 window_ms:86407
said: 2 | **LINK** peer:0x00000200 proto:espnow n:1 rssi_min:-32 rssi_med:-32 rssi_max:-32
```

---

@LAT103LON3153 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 146407 ±0 frame:10500
seq: 5087
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2157
said: 1 | **LINKWIN** t_ms:133043 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-79 rssi_med:-51 rssi_max:-43
said: 4 | 0x00000200 espnow met predicted:-32 observed:-32
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON5866 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 141238 ±21 frame:10500
seq: 2158
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5086
said: 1 | **LINKWIN** t_ms:127872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-29 rssi_med:-27 rssi_max:-25
said: 3 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-47 rssi_med:-43 rssi_max:-39
```

---

@LAT105LON5867 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 201238 ±21 frame:10500
seq: 2160
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5088
said: 1 | **LINKWIN** t_ms:187872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:65 rssi_min:-30 rssi_med:-28 rssi_max:-24
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-50 rssi_med:-43 rssi_max:-40
```

---

@LAT103LON3154 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 207718 ±0 frame:10500
seq: 5089
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2160
said: 1 | **LINKWIN** t_ms:194354 stream:0x3bead35c wall:0 window_ms:61311
said: 2 | **LINK** peer:0x00000200 proto:espnow n:65 rssi_min:-38 rssi_med:-33 rssi_max:-30
said: 3 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-79 rssi_med:-49 rssi_max:-44
said: 4 | 0x00000200 espnow met predicted:-32 observed:-33
percept: 4 | 0x00000200 | link_stable | espnow | + | -
said: 5 | 0x00000200 ble met predicted:-51 observed:-49
percept: 5 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5868 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4380985 ±21 frame:7500
seq: 1428
follows: 0x00000010:1482 0x00000012:1341 0x00000100:1081 0x00000200:2118 0x00000300:4789
said: 1 | **LINKWIN** t_ms:4702717 stream:0xc9e0e898 wall:0 window_ms:60005
said: 2 | **LINK** peer:0x00000010 proto:espnow n:200 rssi_min:-23 rssi_med:-21 rssi_max:-20
said: 3 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-55 rssi_med:-45 rssi_max:-41
said: 4 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-60 rssi_max:-50
said: 5 | **LINK** peer:0x00000200 proto:espnow n:134 rssi_min:-70 rssi_med:-61 rssi_max:-50
said: 6 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-34 rssi_max:-31
said: 7 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-82 rssi_med:-44 rssi_max:-40
said: 8 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-66 rssi_max:-55
said: 9 | **LINK** peer:0x00000300 proto:espnow n:111 rssi_min:-31 rssi_med:-29 rssi_max:-25
```

---

@LAT105LON5869 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4431631 ±21 frame:7500
seq: 1342
follows: 0x00000010:1483 0x00000011:1428 0x00000100:1082 0x00000200:2119 0x00000300:4791
said: 1 | **LINKWIN** t_ms:4753366 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-37 rssi_max:-37
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-84 rssi_med:-65 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-41 rssi_max:-38
said: 5 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-19 rssi_med:-17 rssi_max:-16
said: 6 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-48 rssi_med:-45 rssi_max:-41
said: 7 | **LINK** peer:0x00000200 proto:espnow n:100 rssi_min:-27 rssi_med:-24 rssi_max:-23
said: 8 | **LINK** peer:0x00000300 proto:espnow n:134 rssi_min:-29 rssi_med:-26 rssi_max:-24
said: 9 | **LINK** peer:0x00000010 proto:espnow n:124 rssi_min:-66 rssi_med:-52 rssi_max:-43
```

---

@LAT105LON5870 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4440985 ±21 frame:7500
seq: 1429
follows: 0x00000010:1483 0x00000012:1342 0x00000100:1082 0x00000200:2119 0x00000300:4791
said: 1 | **LINKWIN** t_ms:4762717 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-71 rssi_max:-60
said: 3 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-61 rssi_max:-49
said: 4 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-83 rssi_med:-37 rssi_max:-32
said: 5 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-83 rssi_med:-44 rssi_max:-41
said: 6 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-44 rssi_med:-41 rssi_max:-40
said: 7 | **LINK** peer:0x00000200 proto:espnow n:71 rssi_min:-68 rssi_med:-63 rssi_max:-59
said: 8 | **LINK** peer:0x00000300 proto:espnow n:132 rssi_min:-31 rssi_med:-28 rssi_max:-27
said: 9 | **LINK** peer:0x00000012 proto:espnow n:93 rssi_min:-49 rssi_med:-45 rssi_max:-43
```

---

@LAT105LON5871 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4288400 ±24 frame:7500
seq: 1481
follows: 0x00000011:1426 0x00000012:1339 0x00000100:1078 0x00000200:2117 0x00000300:4785
said: 1 | **LINKWIN** t_ms:4610125 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:99 rssi_min:-57 rssi_med:-48 rssi_max:-44
said: 3 | **LINK** peer:0x00000300 proto:ble n:35 rssi_min:-81 rssi_med:-44 rssi_max:-38
said: 4 | **LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-54 rssi_med:-47 rssi_max:-41
said: 5 | **LINK** peer:0x00000300 proto:espnow n:44 rssi_min:-58 rssi_med:-31 rssi_max:-25
said: 6 | **LINK** peer:0x00000012 proto:espnow n:75 rssi_min:-55 rssi_med:-43 rssi_max:-35
said: 7 | **LINK** peer:0x00000011 proto:espnow n:134 rssi_min:-23 rssi_med:-21 rssi_max:-20
said: 8 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-70 rssi_med:-59 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-38 rssi_med:-34 rssi_max:-29
```

---

@LAT103LON3155 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 267790 ±0 frame:10500
seq: 5091
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2161
said: 1 | **LINKWIN** t_ms:254426 stream:0x3bead35c wall:0 window_ms:60072
said: 2 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-56 rssi_med:-36 rssi_max:-31
said: 3 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-52 rssi_max:-44
said: 4 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-52 rssi_med:-32 rssi_max:-29
said: 5 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 6 | **LINK** peer:0x00000011 proto:espnow n:87 rssi_min:-36 rssi_med:-29 rssi_max:-26
said: 7 | **LINK** peer:0x00000011 proto:ble n:38 rssi_min:-55 rssi_med:-45 rssi_max:-42
said: 8 | **LINK** peer:0x00000012 proto:espnow n:45 rssi_min:-21 rssi_med:-19 rssi_max:-18
said: 9 | **LINK** peer:0x00000012 proto:ble n:26 rssi_min:-37 rssi_med:-35 rssi_max:-33
said: 10 | 0x00000200 espnow met predicted:-33 observed:-36
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-49 observed:-52
percept: 11 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5872 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 261239 ±21 frame:10500
seq: 2161
follows: 0x00000010:1484 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5090
said: 1 | **LINKWIN** t_ms:247872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:79 rssi_min:-46 rssi_med:-32 rssi_max:-26
said: 3 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-66 rssi_med:-47 rssi_max:-40
said: 4 | **LINK** peer:0x00000010 proto:ble n:43 rssi_min:-51 rssi_med:-47 rssi_max:-43
said: 5 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-33 rssi_med:-31 rssi_max:-27
said: 6 | **LINK** peer:0x00000011 proto:ble n:36 rssi_min:-51 rssi_med:-49 rssi_max:-45
said: 7 | **LINK** peer:0x00000011 proto:espnow n:72 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:27 rssi_min:-56 rssi_med:-50 rssi_max:-46
said: 9 | **LINK** peer:0x00000012 proto:espnow n:37 rssi_min:-38 rssi_med:-34 rssi_max:-33
```

---

@LAT105LON5873 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4348395 ±21 frame:7500
seq: 1482
follows: 0x00000011:1427 0x00000012:1340 0x00000100:1078 0x00000200:2118 0x00000300:4789
said: 1 | **LINKWIN** t_ms:4670125 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:170 rssi_min:-54 rssi_med:-43 rssi_max:-40
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-62 rssi_max:-54
said: 4 | **LINK** peer:0x00000200 proto:espnow n:158 rssi_min:-63 rssi_med:-52 rssi_max:-46
said: 5 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-34 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:126 rssi_min:-22 rssi_med:-21 rssi_max:-20
said: 7 | **LINK** peer:0x00000300 proto:espnow n:176 rssi_min:-39 rssi_med:-31 rssi_max:-29
said: 8 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-77 rssi_med:-60 rssi_max:-46
said: 9 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-79 rssi_med:-45 rssi_max:-42
```

---

@LAT103LON3156 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 327830 ±0 frame:10500
seq: 5093
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2161
said: 1 | **LINKWIN** t_ms:314466 stream:0x3bead35c wall:0 window_ms:60040
said: 2 | **LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-21 rssi_med:-20 rssi_max:-18
said: 3 | **LINK** peer:0x00000010 proto:espnow n:53 rssi_min:-47 rssi_med:-33 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:ble n:15 rssi_min:-81 rssi_med:-45 rssi_max:-41
said: 5 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-51 rssi_max:-46
said: 6 | **LINK** peer:0x00000010 proto:ble n:15 rssi_min:-54 rssi_med:-50 rssi_max:-46
said: 7 | **LINK** peer:0x00000200 proto:espnow n:50 rssi_min:-48 rssi_med:-35 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:13 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 9 | **LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-33 rssi_med:-29 rssi_max:-28
said: 10 | 0x00000200 espnow met predicted:-36 observed:-35
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-52 observed:-51
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000010 espnow met predicted:-32 observed:-33
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-49 observed:-50
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-45 observed:-45
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow met predicted:-19 observed:-20
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-35 observed:-35
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT105LON5874 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 321240 ±23 frame:10500
seq: 2162
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000300:5092
said: 1 | **LINKWIN** t_ms:307872 stream:0x3bead35c wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:61 rssi_min:-44 rssi_med:-31 rssi_max:-28
said: 3 | **LINK** peer:0x00000011 proto:espnow n:48 rssi_min:-35 rssi_med:-33 rssi_max:-28
said: 4 | **LINK** peer:0x00000010 proto:espnow n:78 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 5 | **LINK** peer:0x00000012 proto:espnow n:40 rssi_min:-36 rssi_med:-35 rssi_max:-33
said: 6 | **LINK** peer:0x00000011 proto:ble n:15 rssi_min:-63 rssi_med:-50 rssi_max:-46
said: 7 | **LINK** peer:0x00000012 proto:ble n:22 rssi_min:-56 rssi_med:-52 rssi_max:-47
said: 8 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-67 rssi_med:-47 rssi_max:-44
said: 9 | **LINK** peer:0x00000010 proto:ble n:26 rssi_min:-54 rssi_med:-47 rssi_max:-44
```

---

@LAT103LON3157 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 60000 ±0 frame:12000
seq: 5094
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2162
said: 1 | **LINKWIN** t_ms:45024 stream:0x5d34e552 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:10 rssi_min:-30 rssi_med:-30 rssi_max:-29
said: 3 | **LINK** peer:0x00000200 proto:ble n:11 rssi_min:-54 rssi_med:-45 rssi_max:-43
```

---

@LAT105LON5875 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 107656 ±22 frame:12000
seq: 2163
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000300:5097
said: 1 | **LINKWIN** t_ms:90717 stream:0x5d34e552 wall:0 window_ms:61963
said: 2 | **LINK** peer:0x00000300 proto:espnow n:65 rssi_min:-27 rssi_med:-23 rssi_max:-22
said: 3 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-45 rssi_med:-41 rssi_max:-35
```

---

@LAT103LON3158 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 120074 ±0 frame:12000
seq: 5098
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2164
said: 1 | **LINKWIN** t_ms:105098 stream:0x5d34e552 wall:0 window_ms:60074
said: 2 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-80 rssi_med:-45 rssi_max:-41
said: 3 | **LINK** peer:0x00000200 proto:espnow n:66 rssi_min:-33 rssi_med:-29 rssi_max:-27
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:1 half_life_ms:600000 reinforced:0 last_ms:8976
t_ms:108273 stream:0x5d34e552 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:39 last_ms:122205
t_ms:108273 stream:0x5d34e552 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:108273 stream:0x5d34e552 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:108273 stream:0x5d34e552 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:108273 stream:0x5d34e552 wall:0

---

@LAT101LON5 | sid:499db878 | created:0 | updated:0 |
**PEER** node:0x00000001 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:1 half_life_ms:600000 reinforced:0 last_ms:8976
t_ms:108273 stream:0x5d34e552 wall:0

---

@LAT105LON5876 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 167627 ±21 frame:12000
seq: 2165
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000300:5101
said: 1 | **LINKWIN** t_ms:152680 stream:0x5d34e552 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-80 rssi_med:-38 rssi_max:-35
said: 3 | **LINK** peer:0x00000300 proto:espnow n:79 rssi_min:-31 rssi_med:-23 rssi_max:-22
said: 4 | **LINK** peer:0x00000010 proto:ble n:3 rssi_min:-54 rssi_med:-52 rssi_max:-48
```

---

@LAT103LON3159 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 180074 ±0 frame:12000
seq: 5102
follows: 0x00000010:1486 0x00000011:1429 0x00000012:1342 0x00000100:1356 0x00000200:2165
said: 1 | **LINKWIN** t_ms:165098 stream:0x5d34e552 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:79 rssi_min:-34 rssi_med:-29 rssi_max:-26
said: 3 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-44 rssi_max:-41
said: 4 | **LINK** peer:0x00000010 proto:espnow n:9 rssi_min:-28 rssi_med:-27 rssi_max:-25
said: 5 | **LINK** peer:0x00000010 proto:ble n:16 rssi_min:-44 rssi_med:-43 rssi_max:-41
said: 6 | **LINK** peer:0x00000100 proto:espnow n:17 rssi_min:-30 rssi_med:-25 rssi_max:-24
said: 7 | **LINK** peer:0x00000011 proto:espnow n:3 rssi_min:-24 rssi_med:-24 rssi_max:-24
said: 8 | **LINK** peer:0x00000011 proto:ble n:9 rssi_min:-44 rssi_med:-39 rssi_max:-38
said: 9 | **LINK** peer:0x00000012 proto:espnow n:5 rssi_min:-18 rssi_med:-16 rssi_max:-16
said: 10 | 0x00000200 ble met predicted:-45 observed:-44
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT105LON5877 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4408386 ±21 frame:7500
seq: 1483
follows: 0x00000011:1428 0x00000012:1341 0x00000100:1081 0x00000200:2119 0x00000300:4791
said: 1 | **LINKWIN** t_ms:4730125 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-58 rssi_med:-46 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-80 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-34 rssi_max:-30
said: 5 | **LINK** peer:0x00000200 proto:espnow n:84 rssi_min:-54 rssi_med:-46 rssi_max:-43
said: 6 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-58 rssi_med:-41 rssi_max:-35
said: 7 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-64 rssi_med:-47 rssi_max:-39
said: 8 | **LINK** peer:0x00000300 proto:espnow n:86 rssi_min:-39 rssi_med:-31 rssi_max:-28
said: 9 | **LINK** peer:0x00000011 proto:espnow n:108 rssi_min:-21 rssi_med:-21 rssi_max:-20
```

---

@LAT105LON5878 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4468395 ±21 frame:7500
seq: 1484
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1082 0x00000200:2120 0x00000300:4793
said: 1 | **LINKWIN** t_ms:4790126 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-43 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:espnow n:97 rssi_min:-58 rssi_med:-46 rssi_max:-45
said: 4 | **LINK** peer:0x00000300 proto:espnow n:129 rssi_min:-50 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000012 proto:espnow n:109 rssi_min:-65 rssi_med:-50 rssi_max:-39
said: 6 | **LINK** peer:0x00000300 proto:ble n:71 rssi_min:-81 rssi_med:-46 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:espnow n:81 rssi_min:-21 rssi_med:-21 rssi_max:-20
said: 8 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-39 rssi_med:-33 rssi_max:-30
said: 9 | **LINK** peer:0x00000200 proto:ble n:47 rssi_min:-77 rssi_med:-58 rssi_max:-55
```

---

@LAT105LON5879 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 273054 ±21 frame:10500
seq: 1486
follows: 0x00000011:1429 0x00000012:1342 0x00000100:1110 0x00000200:2161 0x00000300:5091
said: 1 | **LINKWIN** t_ms:259691 stream:0x3bead35c wall:0 window_ms:60072
said: 2 | **LINK** peer:0x00000300 proto:espnow n:81 rssi_min:-52 rssi_med:-23 rssi_max:-20
said: 3 | **LINK** peer:0x00000200 proto:espnow n:130 rssi_min:-29 rssi_med:-26 rssi_max:-23
said: 4 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-72 rssi_med:-39 rssi_max:-35
said: 5 | **LINK** peer:0x00000200 proto:ble n:49 rssi_min:-44 rssi_med:-40 rssi_max:-37
said: 6 | **LINK** peer:0x00000011 proto:espnow n:116 rssi_min:-21 rssi_med:-20 rssi_max:-18
said: 7 | **LINK** peer:0x00000011 proto:ble n:43 rssi_min:-81 rssi_med:-34 rssi_max:-30
said: 8 | **LINK** peer:0x00000012 proto:espnow n:62 rssi_min:-33 rssi_med:-30 rssi_max:-28
said: 9 | **LINK** peer:0x00000012 proto:ble n:40 rssi_min:-79 rssi_med:-47 rssi_max:-40
```

---

@LAT105LON5880 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 60001 ±0 frame:9500
seq: 2166
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1467 0x00000300:5103
said: 1 | **LINKWIN** t_ms:47860 stream:0x69cc95ce wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-40 rssi_med:-37 rssi_max:-33
```

---

@LAT105LON5881 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 120001 ±0 frame:9500
seq: 2168
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1470 0x00000300:5103
said: 1 | **LINKWIN** t_ms:107861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-42 rssi_med:-39 rssi_max:-33
```

---

@LAT105LON5882 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 180001 ±0 frame:9500
seq: 2169
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1471 0x00000300:5103
said: 1 | **LINKWIN** t_ms:167861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-41 rssi_med:-39 rssi_max:-36
```

---

@LAT105LON5883 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 240001 ±0 frame:9500
seq: 2170
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1472 0x00000300:5103
said: 1 | **LINKWIN** t_ms:227861 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-40 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON5884 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 300030 ±0 frame:9500
seq: 2171
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1473 0x00000300:5103
said: 1 | **LINKWIN** t_ms:287890 stream:0x69cc95ce wall:0 window_ms:60029
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON5885 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 360030 ±0 frame:9500
seq: 2172
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1474 0x00000300:5103
said: 1 | **LINKWIN** t_ms:347890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-40 rssi_med:-39 rssi_max:-39
```

---

@LAT105LON5886 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 420030 ±0 frame:9500
seq: 2173
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1475 0x00000300:5103
said: 1 | **LINKWIN** t_ms:407890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON5887 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 480030 ±0 frame:9500
seq: 2174
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1476 0x00000300:5103
said: 1 | **LINKWIN** t_ms:467890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-40 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON5888 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 540030 ±0 frame:9500
seq: 2175
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1477 0x00000300:5103
said: 1 | **LINKWIN** t_ms:527890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-39 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON5889 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 600030 ±0 frame:9500
seq: 2176
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1478 0x00000300:5103
said: 1 | **LINKWIN** t_ms:587890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-39 rssi_med:-39 rssi_max:-39
```

---

@LAT103LON3160 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 778538 ±0 frame:9500
seq: 5104
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1481 0x00000200:2178
said: 1 | **LINKWIN** t_ms:766400 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-65 rssi_med:-51 rssi_max:-25
said: 3 | **LINK** peer:0x00000200 proto:espnow n:85 rssi_min:-78 rssi_med:-54 rssi_max:-31
said: 4 | **LINK** peer:0x00000200 proto:ble n:47 rssi_min:-90 rssi_med:-64 rssi_max:-46
```

---

@LAT105LON5890 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 660030 ±0 frame:9500
seq: 2177
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1479 0x00000300:5103
said: 1 | **LINKWIN** t_ms:647890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-43 rssi_med:-39 rssi_max:-38
```

---

@LAT105LON5891 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 720030 ±0 frame:9500
seq: 2178
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1480 0x00000300:5103
said: 1 | **LINKWIN** t_ms:707890 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-41 rssi_med:-39 rssi_max:-37
```

---

@LAT105LON5892 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 780080 ±21 frame:9500
seq: 2179
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1481 0x00000300:5107
said: 1 | **LINKWIN** t_ms:767945 stream:0x69cc95ce wall:0 window_ms:60055
said: 2 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-43 rssi_med:-39 rssi_max:-37
said: 3 | **LINK** peer:0x00000300 proto:espnow n:130 rssi_min:-84 rssi_med:-46 rssi_max:-28
said: 4 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-62 rssi_max:-44
```

---

@LAT103LON3161 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 838538 ±0 frame:9500
seq: 5108
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2179
said: 1 | **LINKWIN** t_ms:826400 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-76 rssi_med:-66 rssi_max:-60
said: 3 | **LINK** peer:0x00000100 proto:espnow n:25 rssi_min:-54 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:espnow n:65 rssi_min:-66 rssi_med:-50 rssi_max:-47
said: 5 | 0x00000100 espnow met predicted:-51 observed:-49
percept: 5 | 0x00000100 | link_stable | espnow | + | -
said: 6 | 0x00000200 espnow met predicted:-54 observed:-50
percept: 6 | 0x00000200 | link_stable | espnow | + | -
said: 7 | 0x00000200 ble met predicted:-64 observed:-66
percept: 7 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT105LON5893 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 840079 ±21 frame:9500
seq: 2180
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000300:5109
said: 1 | **LINKWIN** t_ms:827945 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:74 rssi_min:-61 rssi_med:-47 rssi_max:-42
said: 3 | **LINK** peer:0x00000100 proto:espnow n:16 rssi_min:-48 rssi_med:-39 rssi_max:-38
said: 4 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-79 rssi_med:-62 rssi_max:-53
```

---

@LAT103LON3162 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 898538 ±0 frame:9500
seq: 5110
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **LINKWIN** t_ms:886400 stream:0x69cc95ce wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:51 rssi_min:-74 rssi_med:-61 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-69 rssi_max:-51
said: 4 | 0x00000200 ble met predicted:-66 observed:-69
percept: 4 | 0x00000200 | link_stable | ble | + | -
said: 5 | 0x00000100 espnow unobserved predicted:-49 observed:-49
percept: 5 | 0x00000100 | link_stable | espnow | ? | -
said: 6 | 0x00000200 espnow violated predicted:-50 observed:-61
percept: 6 | 0x00000200 | link_stable | espnow | - | -
```

---

@LAT108LON0 | sid:0c396446 | created:0 | updated:0 | relates:derived_from@LAT103LON3162
[ew]
conf:80
rev:0
sal:0
touched:0
[/ew]

**PRECISION** sid:0c396446 node:0x00000300 chan:link prec:252 var:91 n:62 prec_scale:8192
**FOLD** pe_span:90 alpha:4 mode:expanded predictor:previous_window from:@LAT103LON3123 through:@LAT103LON3162 episodes:40 excluded:0 segments:11 peers_absent:15 skipped:0
**STAMP** t_ms:0 stream:0x00000000 wall:0

---

@LAT103LON8507 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1813377 ±0 frame:7500
seq: 6720
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:1803050 stream:0xd486c598 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e89f6dad2951,aef9ff2626ac,e6b32d2cea8b,0283cce0e689,84a329c78fec
```

---

@LAT103LON8508 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3613377 ±0 frame:7500
seq: 6752
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:3603050 stream:0xd486c598 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-92
said: 12 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e89f6dad2951,e6b32d2cea8b,64677217947d,aef9ff2626ac,5203cfd1b904,84a329c78fec
said: 14 | **COVERED** windows:2 entities:12 window_ms:1200000 first_t_ms:2403050 last_t_ms:3003050 covered_by:@LAT103LON8507
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-39 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-68 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-73 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-79 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:2 rssi:-85 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:2 rssi:-89 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-87 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-89 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-87 windows:2
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90 windows:1
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93 windows:1
```

---

@LAT103LON8509 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:8000
seq: 6764
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:49080 stream:0x4dd69a39 wall:0 window_ms:60000 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 12 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 13 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 14 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 15 | **CORE** entities:0
```

---

@LAT103LON8510 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1213964 ±0 frame:8000
seq: 6786
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:1203044 stream:0x4dd69a39 wall:0 window_ms:600000 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 13 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 14 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 15 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,aef9ff2626ac,bc102f237ace,c2e94427adcf,84a329c78fec,64677217947d,e89f6dad2951,e6b32d2cea8b
said: 16 | **COVERED** windows:1 entities:12 window_ms:553964 first_t_ms:603044 last_t_ms:603044 covered_by:@LAT103LON8509
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-85 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-89 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:7c0cf6082a49 n:1 rssi:-89 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90 windows:1
said: 27 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93 windows:1
said: 28 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93 windows:1
```

---

@LAT103LON8511 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1813966 ±0 frame:8000
seq: 6797
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:1803046 stream:0x4dd69a39 wall:0 window_ms:600002 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 13 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 15 | **CORE** entities:11 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,aef9ff2626ac,e89f6dad2951,c2e94427adcf,64677217947d,84a329c78fec,e6b32d2cea8b,5ce28c488e0c
```

---

@LAT103LON8512 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2413966 ±0 frame:8000
seq: 6809
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:2403046 stream:0x4dd69a39 wall:0 window_ms:600000 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 12 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 13 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:12 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,aef9ff2626ac,84a329c78fec,bc102f237ace,64677217947d,e89f6dad2951,c2e94427adcf,e6b32d2cea8b,5ce28c488e0c,7236bc441422
```

---

@LAT103LON8513 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5413979 ±0 frame:8000
seq: 6861
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:5403059 stream:0x4dd69a39 wall:0 window_ms:600010 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-88
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 12 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 13 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 14 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:12 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,e89f6dad2951,aef9ff2626ac,84a329c78fec,c2e94427adcf,7236bc441422,e6b32d2cea8b,0283cce0e689
said: 16 | **COVERED** windows:4 entities:13 window_ms:2400003 first_t_ms:3003047 last_t_ms:4803049 covered_by:@LAT103LON8512
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-37 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-70 windows:4
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-73 windows:4
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:4 rssi:-85 windows:4
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:4 rssi:-86 windows:4
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-85 windows:4
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:4 rssi:-87 windows:4
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:4 rssi:-88 windows:4
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-86 windows:4
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:4 rssi:-87 windows:4
said: 27 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:4 rssi:-88 windows:4
said: 28 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-91 windows:2
said: 29 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-90 windows:2
```

---

@LAT103LON8514 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:13000
seq: 6905
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:44387 stream:0x800a6cd3 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-85
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8515 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1218669 ±0 frame:13000
seq: 6927
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:1203056 stream:0x800a6cd3 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 5 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:4 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,e6b32d2cea8b
said: 12 | **COVERED** windows:1 entities:8 window_ms:558668 first_t_ms:603055 last_t_ms:603055 covered_by:@LAT103LON8514
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-83 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-90 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
```

---

@LAT103LON8516 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1818680 ±0 frame:13000
seq: 6938
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:1803067 stream:0x800a6cd3 wall:0 window_ms:600011 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 13 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-95
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 15 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e89f6dad2951,e6b32d2cea8b,64677217947d
```

---

@LAT103LON8517 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2418683 ±0 frame:13000
seq: 6950
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:2403070 stream:0x800a6cd3 wall:0 window_ms:600003 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-89
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 12 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 13 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e89f6dad2951,64677217947d,84a329c78fec,e6b32d2cea8b,aef9ff2626ac,0283cce0e689
```

---

@LAT103LON8518 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3018681 ±0 frame:13000
seq: 6961
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:3003068 stream:0x800a6cd3 wall:0 window_ms:599998 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:a063913cf026 n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e89f6dad2951,84a329c78fec,64677217947d,c2e94427adcf,0283cce0e689,e6b32d2cea8b,aef9ff2626ac
```

---

@LAT103LON8519 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4818687 ±0 frame:13000
seq: 6993
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:4803074 stream:0x800a6cd3 wall:0 window_ms:600001 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 12 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 13 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:12 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e89f6dad2951,64677217947d,84a329c78fec,c2e94427adcf,5ce28c488e0c,0283cce0e689,e6b32d2cea8b,aef9ff2626ac
said: 15 | **COVERED** windows:2 entities:12 window_ms:1200005 first_t_ms:3603073 last_t_ms:4203073 covered_by:@LAT103LON8518
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-32 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-70 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-68 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-79 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:2 rssi:-80 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-88 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-87 windows:2
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-92 windows:2
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:2 rssi:-93 windows:2
said: 27 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94 windows:1
```

---

@LAT103LON8520 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5418688 ±0 frame:13000
seq: 7004
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:5403075 stream:0x800a6cd3 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e89f6dad2951,bc102f237ace,84a329c78fec,c2e94427adcf,e6b32d2cea8b,aef9ff2626ac,64677217947d,0283cce0e689
```

---

@LAT103LON8521 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6618687 ±0 frame:13000
seq: 7026
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:6603074 stream:0x800a6cd3 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e89f6dad2951,bc102f237ace,e6b32d2cea8b,c2e94427adcf,64677217947d,84a329c78fec,0283cce0e689
said: 14 | **COVERED** windows:1 entities:8 window_ms:599999 first_t_ms:6003074 last_t_ms:6003074 covered_by:@LAT103LON8520
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-84 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-88 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91 windows:1
```

---

@LAT103LON8522 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8418689 ±0 frame:13000
seq: 7058
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:8403076 stream:0x800a6cd3 wall:0 window_ms:599998 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 11 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e89f6dad2951,c2e94427adcf,e6b32d2cea8b,64677217947d,0283cce0e689
said: 13 | **COVERED** windows:2 entities:12 window_ms:1200004 first_t_ms:7203076 last_t_ms:7803078 covered_by:@LAT103LON8521
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-34 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-69 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-74 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-78 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:2 rssi:-81 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-86 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-90 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-93 windows:2
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
```

---

@LAT103LON8523 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9018700 ±0 frame:13000
seq: 7069
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:9003087 stream:0x800a6cd3 wall:0 window_ms:600011 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:18a5ffc36c02 n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 13 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e89f6dad2951,84a329c78fec,c2e94427adcf,e6b32d2cea8b,0283cce0e689,64677217947d
```

---

@LAT103LON8524 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9618698 ±0 frame:13000
seq: 7081
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:9603085 stream:0x800a6cd3 wall:0 window_ms:599998 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 11 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 12 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 13 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e89f6dad2951,c2e94427adcf,bc102f237ace,84a329c78fec,e6b32d2cea8b,64677217947d,5ce28c488e0c,0283cce0e689
```

---

@LAT103LON8525 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:10500
seq: 7091
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:46589 stream:0x079f2298 wall:0 window_ms:60000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 14 | **CORE** entities:0
```

---

@LAT103LON8526 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1216454 ±0 frame:10500
seq: 7113
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:1203043 stream:0x079f2298 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-96
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,e89f6dad2951,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,aef9ff2626ac
said: 12 | **COVERED** windows:1 entities:9 window_ms:556454 first_t_ms:603043 last_t_ms:603043 covered_by:@LAT103LON8525
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-82 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94 windows:1
```

---

@LAT103LON8527 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1816460 ±0 frame:10500
seq: 7124
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:1803049 stream:0x079f2298 wall:0 window_ms:600006 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e89f6dad2951,bc102f237ace,64677217947d,84a329c78fec,e6b32d2cea8b,aef9ff2626ac
```

---

@LAT103LON8528 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3016461 ±0 frame:10500
seq: 7146
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:3003050 stream:0x079f2298 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e89f6dad2951,64677217947d,e6b32d2cea8b,aef9ff2626ac
said: 12 | **COVERED** windows:1 entities:3 window_ms:600001 first_t_ms:2403050 last_t_ms:2403050 covered_by:@LAT103LON8527
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-82 windows:1
```

---

@LAT103LON16636 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3660001 ±0 frame:10500
seq: 7157
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:3646590 stream:0x079f2298 wall:0 window_ms:60000 n:1000
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:10 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28364 window_ms:1740000 moving_permille:0 dev_mean_mg:7 dev_max_mg:656 moving_ms:120 first_t_ms:1906590 last_t_ms:3586590 covered_by:@LAT103LON16635
```

---

@LAT103LON8529 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4216467 ±0 frame:10500
seq: 7168
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:4203056 stream:0x079f2298 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e89f6dad2951,64677217947d,e6b32d2cea8b,84a329c78fec,aef9ff2626ac
said: 14 | **COVERED** windows:1 entities:10 window_ms:600006 first_t_ms:3603056 last_t_ms:3603056 covered_by:@LAT103LON8528
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-84 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:e0c25086ede3 n:1 rssi:-91 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
```

---

@LAT103LON8530 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4816467 ±0 frame:10500
seq: 7179
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:4803056 stream:0x079f2298 wall:0 window_ms:600000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:e0c25086ede3 n:1 rssi:-91
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,84a329c78fec,aef9ff2626ac,5ce28c488e0c,e89f6dad2951
```

---

@LAT103LON8531 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:7500
seq: 7185
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:49879 stream:0x4257488f wall:0 window_ms:60000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON16637 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:7500
seq: 7186
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:49879 stream:0x4257488f wall:0 window_ms:60000 n:928
said: 2 | **MOTION** state:still moving_permille:11 dev_mean_mg:9 dev_max_mg:154 moving_ms:660
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8532 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1213162 ±0 frame:7500
seq: 7207
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:1203041 stream:0x4257488f wall:0 window_ms:600000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 13 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 14 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,e89f6dad2951,bc102f237ace,64677217947d,0283cce0e689
said: 15 | **COVERED** windows:1 entities:10 window_ms:553162 first_t_ms:603041 last_t_ms:603041 covered_by:@LAT103LON8531
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-84 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
```

---

@LAT103LON8533 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1813167 ±0 frame:7500
seq: 7218
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:1803046 stream:0x4257488f wall:0 window_ms:600005 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,e89f6dad2951,bc102f237ace,64677217947d,aef9ff2626ac,7236bc441422,0283cce0e689
```

---

@LAT103LON16638 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 1860000 ±0 frame:7500
seq: 7219
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:1849879 stream:0x4257488f wall:0 window_ms:60000 n:942
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28708 window_ms:1740000 moving_permille:0 dev_mean_mg:8 dev_max_mg:17 moving_ms:0 first_t_ms:109879 last_t_ms:1789879 covered_by:@LAT103LON16637
```

---

@LAT103LON8534 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2413167 ±0 frame:7500
seq: 7230
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:2403046 stream:0x4257488f wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:12 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,e89f6dad2951,64677217947d,84a329c78fec,5ce28c488e0c,7236bc441422,aef9ff2626ac,0283cce0e689
```

---

@LAT103LON8535 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3013167 ±0 frame:7500
seq: 7241
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:3003046 stream:0x4257488f wall:0 window_ms:600000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:11 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e89f6dad2951,e6b32d2cea8b,64677217947d,5ce28c488e0c,84a329c78fec,7236bc441422,aef9ff2626ac
```

---

@LAT103LON16639 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3660001 ±0 frame:7500
seq: 7252
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:3649880 stream:0x4257488f wall:0 window_ms:60000 n:999
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28398 window_ms:1740001 moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0 first_t_ms:1909879 last_t_ms:3589880 covered_by:@LAT103LON16638
```

---

@LAT103LON8536 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4813174 ±0 frame:7500
seq: 7273
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:4803053 stream:0x4257488f wall:0 window_ms:600006 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 12 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e89f6dad2951,bc102f237ace,e6b32d2cea8b,64677217947d,7236bc441422,aef9ff2626ac,84a329c78fec
said: 14 | **COVERED** windows:2 entities:10 window_ms:1200001 first_t_ms:3603048 last_t_ms:4203047 covered_by:@LAT103LON8535
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-33 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-69 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-72 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-82 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-83 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:2 rssi:-82 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-85 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:2 rssi:-89 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:2 rssi:-88 windows:2
```

---

@LAT103LON8537 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5413174 ±0 frame:7500
seq: 7284
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:5403053 stream:0x4257488f wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-87
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e89f6dad2951,bc102f237ace,64677217947d,e6b32d2cea8b,7236bc441422,aef9ff2626ac
```

---

@LAT103LON16640 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5460003 ±0 frame:7500
seq: 7285
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:5449882 stream:0x4257488f wall:0 window_ms:60000 n:994
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28334 window_ms:1740002 moving_permille:0 dev_mean_mg:9 dev_max_mg:18 moving_ms:0 first_t_ms:3709880 last_t_ms:5389882 covered_by:@LAT103LON16639
```

---

@LAT103LON16641 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 7260003 ±0 frame:7500
seq: 7316
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:7249882 stream:0x4257488f wall:0 window_ms:60000 n:995
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28457 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0 first_t_ms:5509882 last_t_ms:7189882 covered_by:@LAT103LON16640
```

---

@LAT103LON8538 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7813184 ±0 frame:7500
seq: 7327
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:7803063 stream:0x4257488f wall:0 window_ms:599999 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 13 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e89f6dad2951,e6b32d2cea8b,64677217947d,84a329c78fec,7236bc441422,aef9ff2626ac
said: 15 | **COVERED** windows:3 entities:10 window_ms:1800011 first_t_ms:6003053 last_t_ms:7203064 covered_by:@LAT103LON8537
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-34 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-68 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-72 windows:3
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:3 rssi:-81 windows:3
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-84 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-84 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-86 windows:2
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:3 rssi:-89 windows:3
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:3 rssi:-89 windows:3
```

---

@LAT103LON16642 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 9060012 ±0 frame:7500
seq: 7348
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:9049891 stream:0x4257488f wall:0 window_ms:60000 n:998
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28313 window_ms:1740009 moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0 first_t_ms:7309882 last_t_ms:8989891 covered_by:@LAT103LON16641
```

---

@LAT103LON8539 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9613190 ±0 frame:7500
seq: 7359
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:9603069 stream:0x4257488f wall:0 window_ms:600000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 13 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:11 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e89f6dad2951,e6b32d2cea8b,84a329c78fec,64677217947d,7236bc441422,aef9ff2626ac,0283cce0e689
said: 15 | **COVERED** windows:2 entities:11 window_ms:1200006 first_t_ms:8403064 last_t_ms:9003069 covered_by:@LAT103LON8538
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-32 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-70 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-73 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-84 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-84 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-85 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-86 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:2 rssi:-90 windows:2
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-81 windows:1
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94 windows:1
```

---

@LAT103LON8540 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:9000
seq: 7380
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:48289 stream:0x987928e4 wall:0 window_ms:60000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 13 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 14 | **CORE** entities:0
```

---

@LAT103LON16643 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:9000
seq: 7381
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:48289 stream:0x987928e4 wall:0 window_ms:60000 n:901
said: 2 | **MOTION** state:still moving_permille:36 dev_mean_mg:16 dev_max_mg:319 moving_ms:1989
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8541 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1214763 ±0 frame:9000
seq: 7402
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:1203052 stream:0x987928e4 wall:0 window_ms:599998 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 13 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 14 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,e89f6dad2951,64677217947d,bc102f237ace,e6b32d2cea8b,84a329c78fec,5ce28c488e0c,0283cce0e689
said: 15 | **COVERED** windows:1 entities:12 window_ms:554765 first_t_ms:603054 last_t_ms:603054 covered_by:@LAT103LON8540
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-82 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5a32b52ccf44 n:1 rssi:-84 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89 windows:1
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90 windows:1
said: 27 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
```

---

@LAT103LON8542 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1814775 ±0 frame:9000
seq: 7413
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:1803064 stream:0x987928e4 wall:0 window_ms:600012 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 14 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e89f6dad2951,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,5ce28c488e0c,7236bc441422,0283cce0e689
```

---

@LAT103LON16644 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 1860018 ±0 frame:9000
seq: 7414
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:1848307 stream:0x987928e4 wall:0 window_ms:60000 n:947
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28793 window_ms:1740018 moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0 first_t_ms:108289 last_t_ms:1788307 covered_by:@LAT103LON16643
```

---

@LAT106LON376 | created:0 | updated:0

**BAR** frame:9000 bar:3 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:2111 heap:13896 fetched:0 unanswered:16 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT106LON377 | created:0 | updated:0

**BAR** frame:9000 bar:4 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:2714 heap:13136 fetched:0 unanswered:16 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT106LON378 | created:0 | updated:0

**BAR** frame:9000 bar:5 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:3310 heap:13896 fetched:0 unanswered:18 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON16645 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3660018 ±0 frame:9000
seq: 7445
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:3648307 stream:0x987928e4 wall:0 window_ms:60000 n:999
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28495 window_ms:1740000 moving_permille:0 dev_mean_mg:10 dev_max_mg:22 moving_ms:0 first_t_ms:1908307 last_t_ms:3588307 covered_by:@LAT103LON16644
```

---

@LAT106LON379 | created:0 | updated:0

**BAR** frame:9000 bar:6 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:3914 heap:13932 fetched:0 unanswered:20 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON8543 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4214777 ±0 frame:9000
seq: 7456
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:4203066 stream:0x987928e4 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e89f6dad2951,64677217947d,e6b32d2cea8b,7236bc441422,0283cce0e689,84a329c78fec
said: 13 | **COVERED** windows:3 entities:11 window_ms:1800001 first_t_ms:2403065 last_t_ms:3603065 covered_by:@LAT103LON8542
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-34 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-68 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-68 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:3 rssi:-82 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-81 windows:3
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-83 windows:3
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:3 rssi:-86 windows:3
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:2 rssi:-91 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-91 windows:2
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1
```

---

@LAT106LON380 | created:0 | updated:0

**BAR** frame:9000 bar:7 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:4514 heap:13404 fetched:0 unanswered:20 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT106LON381 | created:0 | updated:0

**BAR** frame:9000 bar:8 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:5112 heap:13084 fetched:0 unanswered:22 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON8544 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5414778 ±0 frame:9000
seq: 7477
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:5403067 stream:0x987928e4 wall:0 window_ms:600002 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 13 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,e89f6dad2951,bc102f237ace,e6b32d2cea8b,84a329c78fec,7236bc441422,0283cce0e689
said: 15 | **COVERED** windows:1 entities:9 window_ms:599999 first_t_ms:4803065 last_t_ms:4803065 covered_by:@LAT103LON8543
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-80 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
```

---

@LAT103LON16646 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5460024 ±0 frame:9000
seq: 7478
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:5448313 stream:0x987928e4 wall:0 window_ms:60000 n:997
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28385 window_ms:1740006 moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0 first_t_ms:3708307 last_t_ms:5388313 covered_by:@LAT103LON16645
```

---

@LAT106LON382 | created:0 | updated:0

**BAR** frame:9000 bar:9 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:5710 heap:12544 fetched:0 unanswered:22 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON8545 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6014777 ±0 frame:9000
seq: 7489
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:6003066 stream:0x987928e4 wall:0 window_ms:599999 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88
said: 11 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-88
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e89f6dad2951,64677217947d,e6b32d2cea8b,84a329c78fec,7236bc441422,0283cce0e689
```

---

@LAT106LON383 | created:0 | updated:0

**BAR** frame:9000 bar:10 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:6310 heap:13648 fetched:0 unanswered:24 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON8546 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6614779 ±0 frame:9000
seq: 7500
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:6603068 stream:0x987928e4 wall:0 window_ms:600002 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-88
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 12 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:11 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e89f6dad2951,e6b32d2cea8b,64677217947d,84a329c78fec,aef9ff2626ac,7236bc441422,0283cce0e689
```

---

@LAT106LON384 | created:0 | updated:0

**BAR** frame:9000 bar:11 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:6911 heap:13652 fetched:0 unanswered:26 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON16647 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 7260045 ±0 frame:9000
seq: 7511
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:7248334 stream:0x987928e4 wall:0 window_ms:60000 n:994
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28583 window_ms:1740021 moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0 first_t_ms:5508313 last_t_ms:7188334 covered_by:@LAT103LON16646
```

---

@LAT106LON385 | created:0 | updated:0

**BAR** frame:9000 bar:12 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:7511 heap:13160 fetched:0 unanswered:26 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT106LON386 | created:0 | updated:0

**BAR** frame:9000 bar:13 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:8111 heap:13908 fetched:0 unanswered:28 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT106LON387 | created:0 | updated:0

**BAR** frame:9000 bar:14 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:8714 heap:13420 fetched:0 unanswered:30 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON16648 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 9060047 ±0 frame:9000
seq: 7542
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:9048336 stream:0x987928e4 wall:0 window_ms:60000 n:999
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28501 window_ms:1740002 moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0 first_t_ms:7308334 last_t_ms:8988336 covered_by:@LAT103LON16647
```

---

@LAT106LON388 | created:0 | updated:0

**BAR** frame:9000 bar:15 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:9310 heap:14160 fetched:0 unanswered:30 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT106LON389 | created:0 | updated:0

**BAR** frame:9000 bar:16 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:9911 heap:13880 fetched:0 unanswered:32 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON8547 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10214794 ±0 frame:9000
seq: 7563
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:10203083 stream:0x987928e4 wall:0 window_ms:600000 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 13 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 14 | **RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
said: 15 | **CORE** entities:11 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e89f6dad2951,e6b32d2cea8b,64677217947d,84a329c78fec,aef9ff2626ac,0283cce0e689,7236bc441422
said: 16 | **COVERED** windows:5 entities:12 window_ms:3000015 first_t_ms:7203075 last_t_ms:9603083 covered_by:@LAT103LON8546
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-34 windows:5
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-67 windows:5
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-69 windows:5
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-81 windows:5
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e89f6dad2951 n:5 rssi:-81 windows:5
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:5 rssi:-83 windows:5
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-82 windows:5
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:3 rssi:-87 windows:3
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:5 rssi:-89 windows:5
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:4 rssi:-88 windows:4
said: 27 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-92 windows:4
said: 28 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1
```

---

@LAT106LON390 | created:0 | updated:0

**BAR** frame:9000 bar:17 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:10510 heap:13600 fetched:0 unanswered:32 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON29895 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10620050 ±0 frame:9000
seq: 7570
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:10608339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3741 rate:8000
said: 2 | **ACOUSTIC** rms_mean:92 rms_max:282 peak:516 transients:0 self_blocks:0
```

---

@LAT103LON29896 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10680050 ±0 frame:9000
seq: 7571
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:10668339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3742 rate:8000
said: 2 | **ACOUSTIC** rms_mean:86 rms_max:343 peak:662 transients:0 self_blocks:0
```

---

@LAT103LON29897 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10740050 ±0 frame:9000
seq: 7572
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:10728339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3744 rate:8000
said: 2 | **ACOUSTIC** rms_mean:87 rms_max:332 peak:683 transients:0 self_blocks:0
```

---

@LAT103LON29898 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10800050 ±0 frame:9000
seq: 7573
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:10788339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3745 rate:8000
said: 2 | **ACOUSTIC** rms_mean:79 rms_max:419 peak:633 transients:0 self_blocks:0
```

---

@LAT103LON16649 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 10860050 ±0 frame:9000
seq: 7574
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:10848339 stream:0x987928e4 wall:0 window_ms:60000 n:999
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:28640 window_ms:1740003 moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0 first_t_ms:9108336 last_t_ms:10788339 covered_by:@LAT103LON16648
```

---

@LAT103LON29899 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10860050 ±0 frame:9000
seq: 7575
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:10848339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3740 rate:8000
said: 2 | **ACOUSTIC** rms_mean:82 rms_max:425 peak:664 transients:0 self_blocks:0
```

---

@LAT103LON29900 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10920050 ±0 frame:9000
seq: 7576
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:10908339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:81 rms_max:175 peak:432 transients:0 self_blocks:0
```

---

@LAT103LON29901 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10980050 ±0 frame:9000
seq: 7577
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:10968339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3744 rate:8000
said: 2 | **ACOUSTIC** rms_mean:83 rms_max:294 peak:538 transients:0 self_blocks:0
```

---

@LAT108LON1 | sid:1a33cd4d | created:0 | updated:0 | relates:derived_from@LAT103LON8547
[ew]
conf:96
rev:25
sal:0
touched:0
[/ew]

**PRECISION** sid:1a33cd4d node:0x00000300 chan:entity prec:222 var:1180 n:69 prec_scale:8192
**FOLD** pe_span:jaccard alpha:4 mode:expanded predictor:previous_window from:@LAT103LON8507 through:@LAT103LON8547 episodes:41 excluded:0 segments:6 peers_absent:0 skipped:0
**STAMP** t_ms:10971862 stream:0x987928e4 wall:0

---

@LAT103LON29902 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11040050 ±0 frame:9000
seq: 7578
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:11028339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3529 rate:8000
said: 2 | **ACOUSTIC** rms_mean:76 rms_max:186 peak:356 transients:0 self_blocks:0
```

---

@LAT103LON29903 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11100050 ±0 frame:9000
seq: 7579
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:11088339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3743 rate:8000
said: 2 | **ACOUSTIC** rms_mean:165 rms_max:7353 peak:9594 transients:15 self_blocks:0
said: 3 | **TRANSIENT** t_ms:11068360 stream:0x987928e4 wall:0 rms:5750
```
@LAT106LON391 | created:0 | updated:0

**BAR** frame:9000 bar:18 own:0 held:0 terms:0 digest:0x00000000 settled_ms:300000
**DELIVER** up_s:11111 heap:13884 fetched:0 unanswered:34 broken:0 resumed:0 empty:0 served:0 wants:0 early:0 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:0 split:0

---

@LAT103LON29904 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11160050 ±0 frame:9000
seq: 7580
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:11148339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3371 rate:8000
said: 2 | **ACOUSTIC** rms_mean:156 rms_max:7727 peak:9677 transients:10 self_blocks:0
said: 3 | **TRANSIENT** t_ms:11094267 stream:0x987928e4 wall:0 rms:7727
```

---

@LAT103LON29905 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11220050 ±0 frame:9000
seq: 7581
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:11208339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3744 rate:8000
said: 2 | **ACOUSTIC** rms_mean:192 rms_max:9753 peak:11338 transients:35 self_blocks:0
said: 3 | **TRANSIENT** t_ms:11160268 stream:0x987928e4 wall:0 rms:9753
```

---

@LAT103LON29906 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11280050 ±0 frame:9000
seq: 7582
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:11268339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3746 rate:8000
said: 2 | **ACOUSTIC** rms_mean:149 rms_max:11714 peak:27387 transients:10 self_blocks:0
said: 3 | **TRANSIENT** t_ms:11250873 stream:0x987928e4 wall:0 rms:11714
```

---

@LAT103LON29907 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11340050 ±0 frame:9000
seq: 7583
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:11328339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3747 rate:8000
said: 2 | **ACOUSTIC** rms_mean:109 rms_max:821 peak:1668 transients:0 self_blocks:0
```

---

@LAT103LON29908 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11400050 ±0 frame:9000
seq: 7584
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:11388339 stream:0x987928e4 wall:0 window_ms:60000 blocks:3744 rate:8000
said: 2 | **ACOUSTIC** rms_mean:202 rms_max:14049 peak:32768 transients:25 self_blocks:0
said: 3 | **TRANSIENT** t_ms:11387326 stream:0x987928e4 wall:0 rms:14049
```

---

@LAT103LON16650 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 67923
seq: 7585
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:0 stream:0xc80d52b0 wall:0 window_ms:67923 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:4 dev_max_mg:4 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON29909 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 67923
seq: 7586
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:0 stream:0xc80d52b0 wall:0 window_ms:67923 blocks:1 rate:8000
said: 2 | **ACOUSTIC** rms_mean:79 rms_max:79 peak:214 transients:0 self_blocks:0
```

---

@LAT103LON8548 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:9500
seq: 7587
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ENTWIN** t_ms:47579 stream:0x2107fa15 wall:0 window_ms:60000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:e89f6dad2951 n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 6 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON16651 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:9500
seq: 7588
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **MOTIONWIN** t_ms:47579 stream:0x2107fa15 wall:0 window_ms:60000 n:888
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:4 dev_max_mg:10 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON29910 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 60000 ±0 frame:9500
seq: 7589
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:47579 stream:0x2107fa15 wall:0 window_ms:60000 blocks:3322 rate:8000
said: 2 | **ACOUSTIC** rms_mean:98 rms_max:413 peak:2192 transients:0 self_blocks:0
```

---

@LAT104LON1000 | created:0 | updated:0

**carried through @LAT103LON3122**

```ttdb-carried
through: 3122
through: 8506
through: 16635
through: 29894
carried: 2305 38 2542 2315 | 0x00000300 | link_stable_espnow | 0x00000200
carried: 2408 27 2791 2348 | 0x00000300 | link_stable_ble | 0x00000200
carried: 1199 15 1567 1103 | 0x00000300 | link_stable_espnow | 0x00000100
carried: 1718 16 2088 1655 | 0x00000300 | link_stable_ble | 0x00000010
carried: 1687 31 2071 1639 | 0x00000300 | link_stable_espnow | 0x00000010
carried: 1253 8 1261 1313 | 0x00000300 | link_stable_ble | 0x00000011
carried: 1179 27 1206 1235 | 0x00000300 | link_stable_espnow | 0x00000011
carried: 1170 9 1179 1231 | 0x00000300 | link_stable_ble | 0x00000012
carried: 1155 9 1164 1210 | 0x00000300 | link_stable_espnow | 0x00000012
```

---

@LAT108LON2 | sid:d9b3eb9c | created:0 | updated:0 | relates:derived_from@LAT103LON16651
[ew]
conf:128
rev:10
sal:0
touched:0
[/ew]

**PRECISION** sid:d9b3eb9c node:0x00000300 chan:motion prec:255 var:0 n:330 prec_scale:8192
**FOLD** pe_span:60 alpha:4 mode:expanded predictor:previous_window from:@LAT103LON16636 through:@LAT103LON16651 episodes:16 excluded:0 segments:5 peers_absent:0 skipped:0
**STAMP** t_ms:50971 stream:0x2107fa15 wall:0

---

@LAT108LON3 | sid:582b2759 | created:0 | updated:0 | relates:derived_from@LAT103LON29910
[ew]
conf:48
rev:119
sal:0
touched:0
[/ew]

**PRECISION** sid:582b2759 node:0x00000300 chan:acoustic prec:252 var:89 n:13 prec_scale:8192
**FOLD** pe_span:900 alpha:4 mode:expanded predictor:previous_window from:@LAT103LON29895 through:@LAT103LON29910 episodes:16 excluded:0 segments:3 peers_absent:0 skipped:0
**STAMP** t_ms:51129 stream:0x2107fa15 wall:0

---

@LAT103LON29911 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 120000 ±0 frame:9500
seq: 7590
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:107579 stream:0x2107fa15 wall:0 window_ms:60000 blocks:3527 rate:8000
said: 2 | **ACOUSTIC** rms_mean:108 rms_max:2503 peak:9962 transients:1 self_blocks:0
said: 3 | **TRANSIENT** t_ms:70793 stream:0x2107fa15 wall:0 rms:2503
```

---

@LAT103LON29912 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 180000 ±0 frame:9500
seq: 7591
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:167579 stream:0x2107fa15 wall:0 window_ms:60000 blocks:3720 rate:8000
said: 2 | **ACOUSTIC** rms_mean:114 rms_max:3728 peak:13579 transients:8 self_blocks:0
said: 3 | **TRANSIENT** t_ms:147464 stream:0x2107fa15 wall:0 rms:3728
```

---

@LAT103LON29913 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 240000 ±0 frame:9500
seq: 7592
follows: 0x00000010:1488 0x00000011:1429 0x00000012:1342 0x00000100:1482 0x00000200:2180
said: 1 | **ACOUSTICWIN** t_ms:227579 stream:0x2107fa15 wall:0 window_ms:60000 blocks:3737 rate:8000
said: 2 | **ACOUSTIC** rms_mean:99 rms_max:681 peak:2018 transients:0 self_blocks:0
```
