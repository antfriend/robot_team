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

@LAT103LON16485 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 653636 ±214767 frame:20500
seq: 2945
follows: 0x00000010:532 0x00000011:461 0x00000012:379 0x00000100:732 0x00000200:1155
said: 1 | **MOTIONWIN** t_ms:0 stream:0x8ac5ef22 wall:0 window_ms:69515 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:3 dev_max_mg:3 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8357 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 702054 ±0 frame:20500
seq: 2947
follows: 0x00000010:540 0x00000011:469 0x00000012:385 0x00000100:732 0x00000200:1159
said: 1 | **ENTWIN** t_ms:687636 stream:0xa0be1a79 wall:0 window_ms:117933 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8358 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1900492 ±0 frame:20500
seq: 2988
follows: 0x00000010:563 0x00000011:491 0x00000012:407 0x00000100:732 0x00000200:1181
said: 1 | **ENTWIN** t_ms:1884323 stream:0xa0be1a79 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-92
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 12 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,980d67f79619,0283cce0e689
said: 13 | **COVERED** windows:1 entities:10 window_ms:598438 first_t_ms:1284323 last_t_ms:1284323 covered_by:@LAT103LON8357
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-63 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-81 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91 windows:1
```

---

@LAT103LON16486 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 2454444 ±0 frame:20500
seq: 3008
follows: 0x00000010:573 0x00000011:501 0x00000012:416 0x00000100:732 0x00000200:1191
said: 1 | **MOTIONWIN** t_ms:2438275 stream:0xa0be1a79 wall:0 window_ms:60000 n:989
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:25757 window_ms:1740808 moving_permille:0 dev_mean_mg:7 dev_max_mg:249 moving_ms:551 first_t_ms:698275 last_t_ms:2378275 covered_by:@LAT103LON16485
```

---

@LAT103LON8359 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2500496 ±0 frame:20500
seq: 3010
follows: 0x00000010:573 0x00000011:502 0x00000012:417 0x00000100:732 0x00000200:1191
said: 1 | **ENTWIN** t_ms:2484327 stream:0xa0be1a79 wall:0 window_ms:600004 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-81
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 10 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,0283cce0e689,980d67f79619,c2e94427adcf
```

---

@LAT103LON16487 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 4254445 ±0 frame:20500
seq: 3070
follows: 0x00000010:605 0x00000011:534 0x00000012:447 0x00000100:732 0x00000200:1223
said: 1 | **MOTIONWIN** t_ms:4238276 stream:0xa0be1a79 wall:0 window_ms:60000 n:927
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26873 window_ms:1740001 moving_permille:0 dev_mean_mg:8 dev_max_mg:14 moving_ms:0 first_t_ms:2498275 last_t_ms:4178276 covered_by:@LAT103LON16486
```

---

@LAT103LON16488 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 6054445 ±0 frame:20500
seq: 3131
follows: 0x00000010:635 0x00000011:564 0x00000012:478 0x00000100:732 0x00000200:1254
said: 1 | **MOTIONWIN** t_ms:6038276 stream:0xa0be1a79 wall:0 window_ms:60000 n:921
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26935 window_ms:1740000 moving_permille:0 dev_mean_mg:9 dev_max_mg:20 moving_ms:0 first_t_ms:4298276 last_t_ms:5978276 covered_by:@LAT103LON16487
```

---

@LAT103LON8360 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6100565 ±0 frame:20500
seq: 3133
follows: 0x00000010:636 0x00000011:565 0x00000012:479 0x00000100:732 0x00000200:1254
said: 1 | **ENTWIN** t_ms:6084396 stream:0xa0be1a79 wall:0 window_ms:600001 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-81
said: 8 | **RUN** windows_since_last:6 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,e6b32d2cea8b,bc102f237ace,64677217947d,0283cce0e689,980d67f79619,c2e94427adcf
said: 10 | **COVERED** windows:5 entities:11 window_ms:3000068 first_t_ms:3084325 last_t_ms:5484395 covered_by:@LAT103LON8359
said: 11 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-39 windows:5
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-63 windows:5
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-71 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-75 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-74 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-80 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:3 rssi:-87 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:5 rssi:-88 windows:5
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:5 rssi:-89 windows:5
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:3 rssi:-92 windows:3
```

---

@LAT103LON16489 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 7856012 ±0 frame:20500
seq: 3193
follows: 0x00000010:666 0x00000011:597 0x00000012:511 0x00000100:732 0x00000200:1286
said: 1 | **MOTIONWIN** t_ms:7839843 stream:0xa0be1a79 wall:0 window_ms:60000 n:992
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27008 window_ms:1741567 moving_permille:0 dev_mean_mg:10 dev_max_mg:30 moving_ms:0 first_t_ms:6098276 last_t_ms:7779843 covered_by:@LAT103LON16488
```

---

@LAT103LON16490 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 9656210 ±0 frame:20500
seq: 3254
follows: 0x00000010:696 0x00000011:630 0x00000012:542 0x00000100:732 0x00000200:1317
said: 1 | **MOTIONWIN** t_ms:9640041 stream:0xa0be1a79 wall:0 window_ms:60000 n:923
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27076 window_ms:1740198 moving_permille:0 dev_mean_mg:11 dev_max_mg:22 moving_ms:0 first_t_ms:7899843 last_t_ms:9580041 covered_by:@LAT103LON16489
```

---

@LAT103LON8361 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9700564 ±0 frame:20500
seq: 3256
follows: 0x00000010:697 0x00000011:631 0x00000012:542 0x00000100:732 0x00000200:1317
said: 1 | **ENTWIN** t_ms:9684395 stream:0xa0be1a79 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-81
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 12 | **RUN** windows_since_last:6 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,5203cfd1b904,64677217947d,980d67f79619,84a329c78fec,0283cce0e689,c2e94427adcf
said: 14 | **COVERED** windows:5 entities:11 window_ms:2999999 first_t_ms:6684395 last_t_ms:9084395 covered_by:@LAT103LON8360
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-41 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-63 windows:5
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-69 windows:5
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-76 windows:5
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-77 windows:5
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:5 rssi:-80 windows:5
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:4 rssi:-89 windows:4
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:5 rssi:-88 windows:5
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:5 rssi:-90 windows:5
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-91 windows:2
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-92 windows:2
```

---

@LAT103LON16491 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 11456213 ±0 frame:20500
seq: 3316
follows: 0x00000010:727 0x00000011:661 0x00000012:573 0x00000100:732 0x00000200:1348
said: 1 | **MOTIONWIN** t_ms:11440044 stream:0xa0be1a79 wall:0 window_ms:60000 n:926
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27096 window_ms:1740003 moving_permille:0 dev_mean_mg:11 dev_max_mg:40 moving_ms:0 first_t_ms:9700041 last_t_ms:11380044 covered_by:@LAT103LON16490
```

---

@LAT103LON8362 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11500566 ±0 frame:20500
seq: 3318
follows: 0x00000010:728 0x00000011:662 0x00000012:573 0x00000100:732 0x00000200:1348
said: 1 | **ENTWIN** t_ms:11484397 stream:0xa0be1a79 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-79
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,980d67f79619,c2e94427adcf
said: 12 | **COVERED** windows:2 entities:11 window_ms:1200003 first_t_ms:10284395 last_t_ms:10884398 covered_by:@LAT103LON8361
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-43 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-63 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-77 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-78 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-71 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-81 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-87 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-93 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:003044ca577f n:1 rssi:-91 windows:1
```

---

@LAT103LON8363 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12100566 ±0 frame:20500
seq: 3339
follows: 0x00000010:739 0x00000011:672 0x00000012:583 0x00000100:732 0x00000200:1358
said: 1 | **ENTWIN** t_ms:12084397 stream:0xa0be1a79 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,980d67f79619,84a329c78fec,c2e94427adcf
```

---

@LAT103LON8364 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12700565 ±0 frame:20500
seq: 3360
follows: 0x00000010:750 0x00000011:682 0x00000012:593 0x00000100:732 0x00000200:1368
said: 1 | **ENTWIN** t_ms:12684396 stream:0xa0be1a79 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-79
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-81
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,bc102f237ace,5203cfd1b904,64677217947d,0283cce0e689,980d67f79619,84a329c78fec
```

---

@LAT103LON16492 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 13256221 ±0 frame:20500
seq: 3380
follows: 0x00000010:759 0x00000011:692 0x00000012:602 0x00000100:732 0x00000200:1378
said: 1 | **MOTIONWIN** t_ms:13240052 stream:0xa0be1a79 wall:0 window_ms:60000 n:989
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26670 window_ms:1740008 moving_permille:0 dev_mean_mg:12 dev_max_mg:22 moving_ms:0 first_t_ms:11500044 last_t_ms:13180052 covered_by:@LAT103LON16491
```

---

@LAT103LON8365 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 13300565 ±0 frame:20500
seq: 3382
follows: 0x00000010:760 0x00000011:693 0x00000012:603 0x00000100:732 0x00000200:1378
said: 1 | **ENTWIN** t_ms:13284396 stream:0xa0be1a79 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,980d67f79619
```

---

@LAT103LON8366 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 14500566 ±0 frame:20500
seq: 3423
follows: 0x00000010:782 0x00000011:714 0x00000012:624 0x00000100:732 0x00000200:1399
said: 1 | **ENTWIN** t_ms:14484397 stream:0xa0be1a79 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-78
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,e6b32d2cea8b,980d67f79619,84a329c78fec,0283cce0e689,c2e94427adcf
said: 14 | **COVERED** windows:1 entities:9 window_ms:600001 first_t_ms:13884397 last_t_ms:13884397 covered_by:@LAT103LON8365
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-63 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-78 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
```

---

@LAT103LON16493 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 15056275 ±0 frame:20500
seq: 3443
follows: 0x00000010:791 0x00000011:724 0x00000012:634 0x00000100:732 0x00000200:1409
said: 1 | **MOTIONWIN** t_ms:15040106 stream:0xa0be1a79 wall:0 window_ms:60000 n:931
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26733 window_ms:1740054 moving_permille:0 dev_mean_mg:12 dev_max_mg:24 moving_ms:0 first_t_ms:13300052 last_t_ms:14980106 covered_by:@LAT103LON16492
```

---

@LAT103LON16494 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 16856277 ±0 frame:20500
seq: 3504
follows: 0x00000010:821 0x00000011:756 0x00000012:665 0x00000100:732 0x00000200:1438
said: 1 | **MOTIONWIN** t_ms:16840108 stream:0xa0be1a79 wall:0 window_ms:60000 n:921
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26971 window_ms:1740002 moving_permille:0 dev_mean_mg:12 dev_max_mg:17 moving_ms:0 first_t_ms:15100106 last_t_ms:16780108 covered_by:@LAT103LON16493
```

---

@LAT103LON8367 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 18100565 ±0 frame:20500
seq: 3546
follows: 0x00000010:843 0x00000011:777 0x00000012:686 0x00000100:732 0x00000200:1460
said: 1 | **ENTWIN** t_ms:18084396 stream:0xa0be1a79 wall:0 window_ms:599998 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 11 | **RUN** windows_since_last:6 reason:heartbeat max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,64677217947d,e6b32d2cea8b,84a329c78fec,0283cce0e689,c2e94427adcf,980d67f79619
said: 13 | **COVERED** windows:5 entities:11 window_ms:3000001 first_t_ms:15084397 last_t_ms:17484398 covered_by:@LAT103LON8366
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-38 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-64 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-75 windows:5
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-73 windows:5
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-81 windows:5
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-89 windows:4
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:3 rssi:-90 windows:3
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:5 rssi:-91 windows:5
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:4 rssi:-92 windows:4
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:4 rssi:-81 windows:4
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
```

---

@LAT103LON16495 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 18656281 ±0 frame:20500
seq: 3566
follows: 0x00000010:852 0x00000011:787 0x00000012:695 0x00000100:732 0x00000200:1469
said: 1 | **MOTIONWIN** t_ms:18640112 stream:0xa0be1a79 wall:0 window_ms:60000 n:989
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27054 window_ms:1740004 moving_permille:0 dev_mean_mg:12 dev_max_mg:31 moving_ms:0 first_t_ms:16900108 last_t_ms:18580112 covered_by:@LAT103LON16494
```

---

@LAT103LON8368 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 18700565 ±0 frame:20500
seq: 3568
follows: 0x00000010:853 0x00000011:788 0x00000012:696 0x00000100:732 0x00000200:1470
said: 1 | **ENTWIN** t_ms:18684396 stream:0xa0be1a79 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,5203cfd1b904,e6b32d2cea8b,64677217947d,980d67f79619,c2e94427adcf,0283cce0e689
```

---

@LAT103LON16496 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 20456284 ±0 frame:20500
seq: 3628
follows: 0x00000010:883 0x00000011:820 0x00000012:726 0x00000100:732 0x00000200:1500
said: 1 | **MOTIONWIN** t_ms:20440115 stream:0xa0be1a79 wall:0 window_ms:60000 n:989
said: 2 | **MOTION** state:still moving_permille:36 dev_mean_mg:17 dev_max_mg:458 moving_ms:2160
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26592 window_ms:1740003 moving_permille:0 dev_mean_mg:11 dev_max_mg:20 moving_ms:0 first_t_ms:18700112 last_t_ms:20380115 covered_by:@LAT103LON16495
```

---

@LAT103LON8369 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 20500566 ±0 frame:20500
seq: 3630
follows: 0x00000010:884 0x00000011:820 0x00000012:727 0x00000100:732 0x00000200:1501
said: 1 | **ENTWIN** t_ms:20484397 stream:0xa0be1a79 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 10 | **RUN** windows_since_last:3 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:10 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d,c2e94427adcf,980d67f79619,0283cce0e689
said: 12 | **COVERED** windows:2 entities:11 window_ms:1200001 first_t_ms:19284397 last_t_ms:19884397 covered_by:@LAT103LON8368
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:2 rssi:-42 windows:2
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:2 rssi:-65 windows:2
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:2 rssi:-76 windows:2
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:2 rssi:-75 windows:2
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:2 rssi:-82 windows:2
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-82 windows:2
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-91 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:2 rssi:-89 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-91 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93 windows:1
```

---

@LAT103LON8370 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21100565 ±0 frame:20500
seq: 3651
follows: 0x00000010:894 0x00000011:830 0x00000012:737 0x00000100:732 0x00000200:1511
said: 1 | **ENTWIN** t_ms:21084396 stream:0xa0be1a79 wall:0 window_ms:599999 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,c2e94427adcf,64677217947d,980d67f79619
```

---

@LAT103LON8371 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 21700566 ±0 frame:20500
seq: 3672
follows: 0x00000010:904 0x00000011:841 0x00000012:748 0x00000100:732 0x00000200:1521
said: 1 | **ENTWIN** t_ms:21684397 stream:0xa0be1a79 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,84a329c78fec,c2e94427adcf
```

---

@LAT103LON16497 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 22256296 ±0 frame:20500
seq: 3692
follows: 0x00000010:914 0x00000011:852 0x00000012:758 0x00000100:732 0x00000200:1530
said: 1 | **MOTIONWIN** t_ms:22240127 stream:0xa0be1a79 wall:0 window_ms:60000 n:926
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:13 dev_max_mg:17 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26681 window_ms:1740012 moving_permille:0 dev_mean_mg:12 dev_max_mg:25 moving_ms:0 first_t_ms:20500115 last_t_ms:22180127 covered_by:@LAT103LON16496
```

---

@LAT103LON8372 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 22300566 ±0 frame:20500
seq: 3694
follows: 0x00000010:915 0x00000011:852 0x00000012:759 0x00000100:732 0x00000200:1531
said: 1 | **ENTWIN** t_ms:22284397 stream:0xa0be1a79 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,84a329c78fec,c2e94427adcf
```

---

@LAT103LON8373 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 23500566 ±0 frame:20500
seq: 3735
follows: 0x00000010:935 0x00000011:873 0x00000012:779 0x00000100:732 0x00000200:1553
said: 1 | **ENTWIN** t_ms:23484397 stream:0xa0be1a79 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-96
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,c2e94427adcf,84a329c78fec
said: 14 | **COVERED** windows:1 entities:9 window_ms:600000 first_t_ms:22884397 last_t_ms:22884397 covered_by:@LAT103LON8372
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-65 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
```

---

@LAT103LON16498 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 24056304 ±0 frame:20500
seq: 3755
follows: 0x00000010:945 0x00000011:883 0x00000012:789 0x00000100:732 0x00000200:1563
said: 1 | **MOTIONWIN** t_ms:24040135 stream:0xa0be1a79 wall:0 window_ms:60000 n:919
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:13 dev_max_mg:16 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26858 window_ms:1740008 moving_permille:0 dev_mean_mg:13 dev_max_mg:23 moving_ms:0 first_t_ms:22300127 last_t_ms:23980135 covered_by:@LAT103LON16497
```

---

@LAT103LON8374 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 24700565 ±0 frame:20500
seq: 3777
follows: 0x00000010:956 0x00000011:894 0x00000012:800 0x00000100:732 0x00000200:1574
said: 1 | **ENTWIN** t_ms:24684396 stream:0xa0be1a79 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-50
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 9 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,5ce28c488e0c,0283cce0e689,64677217947d,c2e94427adcf
said: 11 | **COVERED** windows:1 entities:8 window_ms:600000 first_t_ms:24084397 last_t_ms:24084397 covered_by:@LAT103LON8373
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46 windows:1
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-65 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95 windows:1
```

---

@LAT103LON8375 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 25300565 ±0 frame:20500
seq: 3798
follows: 0x00000010:966 0x00000011:905 0x00000012:810 0x00000100:732 0x00000200:1584
said: 1 | **ENTWIN** t_ms:25284396 stream:0xa0be1a79 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689,c2e94427adcf
```

---

@LAT103LON16499 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 25856304 ±0 frame:20500
seq: 3818
follows: 0x00000010:976 0x00000011:915 0x00000012:819 0x00000100:732 0x00000200:1593
said: 1 | **MOTIONWIN** t_ms:25840135 stream:0xa0be1a79 wall:0 window_ms:60000 n:989
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26754 window_ms:1740000 moving_permille:0 dev_mean_mg:12 dev_max_mg:43 moving_ms:0 first_t_ms:24100135 last_t_ms:25780135 covered_by:@LAT103LON16498
```

---

@LAT103LON8376 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 25900566 ±0 frame:20500
seq: 3820
follows: 0x00000010:977 0x00000011:915 0x00000012:820 0x00000100:732 0x00000200:1594
said: 1 | **ENTWIN** t_ms:25884397 stream:0xa0be1a79 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,0283cce0e689
```

---

@LAT106LON141 | created:0 | updated:0

**BAR** frame:20500 bar:45 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:987 hi:996 sum:9915
**HOLDS** agent:0x00000011 n:10 lo:925 hi:934 sum:9295
**HOLDS** agent:0x00000012 n:10 lo:830 hi:839 sum:8345
**HOLDS** agent:0x00000200 n:10 lo:1604 hi:1614 sum:16087
**HOLDS** agent:0x00000300 n:10 lo:3839 hi:3857 sum:38480

---

@LAT103LON16500 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 27656304 ±0 frame:20500
seq: 3880
follows: 0x00000010:1007 0x00000011:947 0x00000012:850 0x00000100:732 0x00000200:1625
said: 1 | **MOTIONWIN** t_ms:27640135 stream:0xa0be1a79 wall:0 window_ms:60000 n:926
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26881 window_ms:1740000 moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0 first_t_ms:25900135 last_t_ms:27580135 covered_by:@LAT103LON16499
```

---

@LAT106LON142 | created:0 | updated:0

**BAR** frame:20500 bar:46 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:997 hi:1007 sum:10020
**HOLDS** agent:0x00000011 n:10 lo:936 hi:945 sum:9405
**HOLDS** agent:0x00000012 n:10 lo:840 hi:850 sum:8449
**HOLDS** agent:0x00000200 n:10 lo:1615 hi:1625 sum:16197
**HOLDS** agent:0x00000300 n:10 lo:3859 hi:3877 sum:38680

---

@LAT106LON143 | created:0 | updated:0

**BAR** frame:20500 bar:47 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1008 hi:1017 sum:10125
**HOLDS** agent:0x00000011 n:10 lo:947 hi:956 sum:9515
**HOLDS** agent:0x00000012 n:10 lo:851 hi:860 sum:8555
**HOLDS** agent:0x00000200 n:10 lo:1626 hi:1635 sum:16305
**HOLDS** agent:0x00000300 n:10 lo:3879 hi:3898 sum:38889

---

@LAT106LON144 | created:0 | updated:0

**BAR** frame:20500 bar:48 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1018 hi:1027 sum:10225
**HOLDS** agent:0x00000011 n:10 lo:958 hi:967 sum:9625
**HOLDS** agent:0x00000012 n:10 lo:861 hi:871 sum:8659
**HOLDS** agent:0x00000200 n:10 lo:1636 hi:1646 sum:16407
**HOLDS** agent:0x00000300 n:10 lo:3900 hi:3918 sum:39090

---

@LAT103LON16501 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 29456308 ±0 frame:20500
seq: 3941
follows: 0x00000010:1037 0x00000011:979 0x00000012:881 0x00000100:732 0x00000200:1657
said: 1 | **MOTIONWIN** t_ms:29440139 stream:0xa0be1a79 wall:0 window_ms:60000 n:922
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26970 window_ms:1740004 moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0 first_t_ms:27700135 last_t_ms:29380139 covered_by:@LAT103LON16500
```

---

@LAT103LON8377 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 29500566 ±0 frame:20500
seq: 3943
follows: 0x00000010:1038 0x00000011:979 0x00000012:882 0x00000100:732 0x00000200:1658
said: 1 | **ENTWIN** t_ms:29484397 stream:0xa0be1a79 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 9 | **RUN** windows_since_last:6 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,0283cce0e689,64677217947d
said: 11 | **COVERED** windows:5 entities:11 window_ms:3000000 first_t_ms:26484397 last_t_ms:28884397 covered_by:@LAT103LON8376
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:5 rssi:-46 windows:5
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:5 rssi:-64 windows:5
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:5 rssi:-71 windows:5
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:5 rssi:-77 windows:5
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:5 rssi:-83 windows:5
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-93 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-91 windows:4
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:3 rssi:-86 windows:3
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-87 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1
```

---

@LAT106LON145 | created:0 | updated:0

**BAR** frame:20500 bar:49 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1028 hi:1037 sum:10325
**HOLDS** agent:0x00000011 n:10 lo:969 hi:978 sum:9735
**HOLDS** agent:0x00000012 n:10 lo:872 hi:881 sum:8765
**HOLDS** agent:0x00000200 n:10 lo:1647 hi:1657 sum:16517
**HOLDS** agent:0x00000300 n:10 lo:3920 hi:3938 sum:39290

---

@LAT106LON146 | created:0 | updated:0

**BAR** frame:20500 bar:50 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1038 hi:1048 sum:10430
**HOLDS** agent:0x00000011 n:10 lo:979 hi:988 sum:9835
**HOLDS** agent:0x00000012 n:10 lo:882 hi:891 sum:8865
**HOLDS** agent:0x00000200 n:10 lo:1658 hi:1668 sum:16627
**HOLDS** agent:0x00000300 n:10 lo:3940 hi:3960 sum:39508

---

@LAT106LON147 | created:0 | updated:0

**BAR** frame:20500 bar:51 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1049 hi:1058 sum:10535
**HOLDS** agent:0x00000011 n:10 lo:990 hi:999 sum:9945
**HOLDS** agent:0x00000012 n:10 lo:892 hi:901 sum:8965
**HOLDS** agent:0x00000200 n:10 lo:1669 hi:1678 sum:16735
**HOLDS** agent:0x00000300 n:10 lo:3962 hi:3980 sum:39710

---

@LAT103LON16502 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 31256309 ±0 frame:20500
seq: 4003
follows: 0x00000010:1069 0x00000011:1012 0x00000012:912 0x00000100:732 0x00000200:1689
said: 1 | **MOTIONWIN** t_ms:31240140 stream:0xa0be1a79 wall:0 window_ms:60000 n:990
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26925 window_ms:1740001 moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0 first_t_ms:29500139 last_t_ms:31180140 covered_by:@LAT103LON16501
```

---

@LAT106LON148 | created:0 | updated:0

**BAR** frame:20500 bar:52 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1059 hi:1069 sum:10640
**HOLDS** agent:0x00000011 n:10 lo:1001 hi:1010 sum:10055
**HOLDS** agent:0x00000012 n:10 lo:902 hi:912 sum:9069
**HOLDS** agent:0x00000200 n:10 lo:1679 hi:1689 sum:16837
**HOLDS** agent:0x00000300 n:10 lo:3982 hi:4000 sum:39910

---

@LAT103LON8378 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 31900566 ±0 frame:20500
seq: 4025
follows: 0x00000010:1081 0x00000011:1023 0x00000012:923 0x00000100:732 0x00000200:1701
said: 1 | **ENTWIN** t_ms:31884397 stream:0xa0be1a79 wall:0 window_ms:600001 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 9 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,e45e1b9f675a,0283cce0e689,64677217947d
said: 11 | **COVERED** windows:3 entities:9 window_ms:1799999 first_t_ms:30084397 last_t_ms:31284396 covered_by:@LAT103LON8377
said: 12 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-46 windows:3
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-64 windows:3
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-75 windows:3
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-76 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-85 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:3 rssi:-86 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:3 rssi:-91 windows:3
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e45e1b9f675a n:2 rssi:-93 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
```

---

@LAT106LON149 | created:0 | updated:0

**BAR** frame:20500 bar:53 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1070 hi:1080 sum:10750
**HOLDS** agent:0x00000011 n:10 lo:1012 hi:1021 sum:10165
**HOLDS** agent:0x00000012 n:10 lo:913 hi:922 sum:9175
**HOLDS** agent:0x00000200 n:10 lo:1690 hi:1700 sum:16947
**HOLDS** agent:0x00000300 n:10 lo:4002 hi:4021 sum:40119

---

@LAT106LON150 | created:0 | updated:0

**BAR** frame:20500 bar:54 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1081 hi:1090 sum:10855
**HOLDS** agent:0x00000011 n:10 lo:1023 hi:1032 sum:10275
**HOLDS** agent:0x00000012 n:10 lo:923 hi:932 sum:9275
**HOLDS** agent:0x00000200 n:10 lo:1701 hi:1711 sum:17057
**HOLDS** agent:0x00000300 n:10 lo:4023 hi:4042 sum:40329

---

@LAT103LON16503 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 33056310 ±0 frame:20500
seq: 4065
follows: 0x00000010:1101 0x00000011:1045 0x00000012:942 0x00000100:732 0x00000200:1722
said: 1 | **MOTIONWIN** t_ms:33040141 stream:0xa0be1a79 wall:0 window_ms:60000 n:924
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:15 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26873 window_ms:1740001 moving_permille:0 dev_mean_mg:11 dev_max_mg:16 moving_ms:0 first_t_ms:31300140 last_t_ms:32980141 covered_by:@LAT103LON16502
```

---

@LAT103LON8379 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 33100565 ±0 frame:20500
seq: 4067
follows: 0x00000010:1102 0x00000011:1045 0x00000012:943 0x00000100:732 0x00000200:1723
said: 1 | **ENTWIN** t_ms:33084396 stream:0xa0be1a79 wall:0 window_ms:599998 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,e6b32d2cea8b,64677217947d,0283cce0e689
said: 12 | **COVERED** windows:1 entities:8 window_ms:600001 first_t_ms:32484398 last_t_ms:32484398 covered_by:@LAT103LON8378
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-46 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95 windows:1
```

---

@LAT106LON151 | created:0 | updated:0

**BAR** frame:20500 bar:55 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1091 hi:1101 sum:10960
**HOLDS** agent:0x00000011 n:10 lo:1034 hi:1043 sum:10385
**HOLDS** agent:0x00000012 n:10 lo:933 hi:942 sum:9375
**HOLDS** agent:0x00000200 n:10 lo:1712 hi:1722 sum:17167
**HOLDS** agent:0x00000300 n:10 lo:4044 hi:4062 sum:40530

---

@LAT103LON2754 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33296310 ±0 frame:20500
seq: 4074
follows: 0x00000010:1105 0x00000011:1049 0x00000012:946 0x00000100:732 0x00000200:1726
said: 1 | **LINKWIN** t_ms:33280141 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-63 rssi_med:-56 rssi_max:-55
said: 3 | **LINK** peer:0x00000012 proto:ble n:68 rssi_min:-80 rssi_med:-60 rssi_max:-56
said: 4 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 5 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-53 rssi_med:-50 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:espnow n:93 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000011 proto:espnow n:118 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 8 | **LINK** peer:0x00000012 proto:espnow n:107 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 9 | **LINK** peer:0x00000200 proto:espnow n:97 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 10 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000010 ble met predicted:-49 observed:-49
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-56 observed:-56
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-59 observed:-60
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-50 observed:-50
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2755 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33356310 ±0 frame:20500
seq: 4076
follows: 0x00000010:1106 0x00000011:1050 0x00000012:947 0x00000100:732 0x00000200:1727
said: 1 | **LINKWIN** t_ms:33340141 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:78 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 4 | **LINK** peer:0x00000010 proto:ble n:69 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 5 | **LINK** peer:0x00000200 proto:espnow n:74 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 6 | **LINK** peer:0x00000012 proto:espnow n:146 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 7 | **LINK** peer:0x00000010 proto:espnow n:89 rssi_min:-32 rssi_med:-29 rssi_max:-29
said: 8 | **LINK** peer:0x00000200 proto:ble n:70 rssi_min:-82 rssi_med:-56 rssi_max:-55
said: 9 | **LINK** peer:0x00000011 proto:ble n:52 rssi_min:-81 rssi_med:-50 rssi_max:-49
said: 10 | 0x00000200 ble met predicted:-56 observed:-56
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-60 observed:-59
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-49 observed:-49
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000011 ble met predicted:-50 observed:-50
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON2756 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33416318 ±0 frame:20500
seq: 4078
follows: 0x00000010:1107 0x00000011:1051 0x00000012:948 0x00000100:732 0x00000200:1728
said: 1 | **LINKWIN** t_ms:33400149 stream:0xa0be1a79 wall:0 window_ms:60008
said: 2 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-59 rssi_max:-56
said: 3 | **LINK** peer:0x00000010 proto:espnow n:159 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 4 | **LINK** peer:0x00000011 proto:espnow n:95 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 5 | **LINK** peer:0x00000200 proto:espnow n:106 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 6 | **LINK** peer:0x00000012 proto:espnow n:91 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 8 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-63 rssi_med:-56 rssi_max:-55
said: 9 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-53 rssi_med:-50 rssi_max:-49
said: 10 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000012 ble met predicted:-59 observed:-59
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-49 observed:-49
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-56 observed:-56
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-50 observed:-50
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2757 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33476318 ±0 frame:20500
seq: 4080
follows: 0x00000010:1108 0x00000011:1052 0x00000012:949 0x00000100:732 0x00000200:1729
said: 1 | **LINKWIN** t_ms:33460149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:85 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 3 | **LINK** peer:0x00000012 proto:espnow n:66 rssi_min:-44 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000011 proto:espnow n:134 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 5 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-53 rssi_med:-50 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 7 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 8 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-63 rssi_med:-56 rssi_max:-55
said: 9 | **LINK** peer:0x00000010 proto:espnow n:141 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 10 | 0x00000012 ble met predicted:-59 observed:-59
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-44 observed:-43
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-49 observed:-49
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-56 observed:-56
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-50 observed:-50
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2758 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33536318 ±0 frame:20500
seq: 4082
follows: 0x00000010:1109 0x00000011:1053 0x00000012:950 0x00000100:732 0x00000200:1730
said: 1 | **LINKWIN** t_ms:33520149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-63 rssi_med:-56 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 4 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 5 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 6 | **LINK** peer:0x00000012 proto:espnow n:77 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 7 | **LINK** peer:0x00000200 proto:espnow n:57 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000011 proto:espnow n:114 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 9 | **LINK** peer:0x00000011 proto:ble n:68 rssi_min:-52 rssi_med:-50 rssi_max:-48
said: 10 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-43 observed:-44
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000011 ble met predicted:-50 observed:-50
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-49 observed:-49
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-59 observed:-59
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-56 observed:-56
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON2759 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33596318 ±0 frame:20500
seq: 4084
follows: 0x00000010:1110 0x00000011:1054 0x00000012:951 0x00000100:732 0x00000200:1731
said: 1 | **LINKWIN** t_ms:33580149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:115 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:espnow n:152 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 4 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-52 rssi_med:-50 rssi_max:-49
said: 5 | **LINK** peer:0x00000011 proto:espnow n:96 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 6 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 7 | **LINK** peer:0x00000012 proto:ble n:70 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 8 | **LINK** peer:0x00000200 proto:ble n:71 rssi_min:-63 rssi_med:-56 rssi_max:-55
said: 9 | **LINK** peer:0x00000010 proto:espnow n:125 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 10 | 0x00000200 ble met predicted:-56 observed:-56
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000012 ble met predicted:-59 observed:-59
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000010 ble met predicted:-49 observed:-49
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-50 observed:-50
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2760 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33656318 ±0 frame:20500
seq: 4086
follows: 0x00000010:1111 0x00000011:1056 0x00000012:952 0x00000100:732 0x00000200:1732
said: 1 | **LINKWIN** t_ms:33640149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-79 rssi_med:-49 rssi_max:-45
said: 3 | **LINK** peer:0x00000012 proto:espnow n:74 rssi_min:-44 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000200 proto:espnow n:71 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 6 | **LINK** peer:0x00000010 proto:espnow n:80 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-52 rssi_med:-50 rssi_max:-49
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 9 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-63 rssi_med:-56 rssi_max:-55
said: 10 | 0x00000012 espnow met predicted:-44 observed:-43
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000011 ble met predicted:-50 observed:-50
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 ble met predicted:-49 observed:-49
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-59 observed:-59
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-56 observed:-56
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON2761 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33716318 ±0 frame:20500
seq: 4088
follows: 0x00000010:1112 0x00000011:1057 0x00000012:953 0x00000100:732 0x00000200:1733
said: 1 | **LINKWIN** t_ms:33700149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-53 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000012 proto:espnow n:73 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 6 | **LINK** peer:0x00000010 proto:espnow n:93 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-56 rssi_max:-55
said: 8 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 9 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 10 | 0x00000010 ble met predicted:-49 observed:-49
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000012 espnow met predicted:-43 observed:-44
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-50 observed:-50
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-59 observed:-59
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-56 observed:-56
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT106LON152 | created:0 | updated:0

**BAR** frame:20500 bar:56 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1102 hi:1111 sum:11065
**HOLDS** agent:0x00000011 n:10 lo:1045 hi:1054 sum:10495
**HOLDS** agent:0x00000012 n:10 lo:943 hi:952 sum:9475
**HOLDS** agent:0x00000200 n:10 lo:1723 hi:1732 sum:17275
**HOLDS** agent:0x00000300 n:10 lo:4064 hi:4084 sum:40748

---

@LAT103LON2762 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33776318 ±0 frame:20500
seq: 4090
follows: 0x00000010:1113 0x00000011:1058 0x00000012:954 0x00000100:732 0x00000200:1734
said: 1 | **LINKWIN** t_ms:33760149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:76 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 3 | **LINK** peer:0x00000010 proto:espnow n:85 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 4 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-82 rssi_med:-56 rssi_max:-55
said: 5 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 6 | **LINK** peer:0x00000011 proto:espnow n:88 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 7 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 8 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-53 rssi_med:-50 rssi_max:-49
said: 9 | **LINK** peer:0x00000012 proto:espnow n:66 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 10 | 0x00000011 ble met predicted:-50 observed:-50
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-56 observed:-56
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-59 observed:-59
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-49 observed:-49
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON2763 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33836318 ±0 frame:20500
seq: 4092
follows: 0x00000010:1114 0x00000011:1059 0x00000012:955 0x00000100:732 0x00000200:1735
said: 1 | **LINKWIN** t_ms:33820149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:100 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-63 rssi_med:-56 rssi_max:-54
said: 4 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 5 | **LINK** peer:0x00000010 proto:espnow n:96 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 6 | **LINK** peer:0x00000200 proto:espnow n:126 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-79 rssi_med:-49 rssi_max:-45
said: 8 | **LINK** peer:0x00000011 proto:espnow n:113 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 9 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-50 rssi_max:-49
said: 10 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-56 observed:-56
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000010 ble met predicted:-49 observed:-49
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-59 observed:-59
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-50 observed:-50
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON2764 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33896318 ±0 frame:20500
seq: 4094
follows: 0x00000010:1115 0x00000011:1060 0x00000012:956 0x00000100:732 0x00000200:1736
said: 1 | **LINKWIN** t_ms:33880149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-81 rssi_med:-56 rssi_max:-55
said: 3 | **LINK** peer:0x00000011 proto:espnow n:79 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-83 rssi_med:-49 rssi_max:-45
said: 5 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 6 | **LINK** peer:0x00000010 proto:espnow n:71 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 8 | **LINK** peer:0x00000012 proto:espnow n:95 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 9 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-53 rssi_med:-50 rssi_max:-49
said: 10 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-56 observed:-56
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000012 ble met predicted:-59 observed:-59
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-49 observed:-49
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-50 observed:-50
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2765 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 33956318 ±0 frame:20500
seq: 4096
follows: 0x00000010:1116 0x00000011:1061 0x00000012:957 0x00000100:732 0x00000200:1737
said: 1 | **LINKWIN** t_ms:33940149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:espnow n:84 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 5 | **LINK** peer:0x00000200 proto:espnow n:118 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 6 | **LINK** peer:0x00000012 proto:espnow n:71 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 7 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-63 rssi_med:-56 rssi_max:-55
said: 8 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 9 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 10 | 0x00000200 ble met predicted:-56 observed:-56
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000010 ble met predicted:-49 observed:-49
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000012 ble met predicted:-59 observed:-59
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-50 observed:-50
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2766 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34016318 ±0 frame:20500
seq: 4098
follows: 0x00000010:1117 0x00000011:1062 0x00000012:958 0x00000100:732 0x00000200:1738
said: 1 | **LINKWIN** t_ms:34000149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-53 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:espnow n:108 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-44 rssi_med:-43 rssi_max:-42
said: 5 | **LINK** peer:0x00000200 proto:espnow n:120 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 6 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-32 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-82 rssi_med:-49 rssi_max:-45
said: 8 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-63 rssi_med:-56 rssi_max:-55
said: 10 | 0x00000011 ble met predicted:-50 observed:-50
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-44 observed:-43
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-56 observed:-56
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-59 observed:-59
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-49 observed:-49
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON2767 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34076318 ±0 frame:20500
seq: 4100
follows: 0x00000010:1118 0x00000011:1063 0x00000012:959 0x00000100:732 0x00000200:1739
said: 1 | **LINKWIN** t_ms:34060149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 4 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:espnow n:119 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 6 | **LINK** peer:0x00000010 proto:espnow n:150 rssi_min:-32 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-50 rssi_max:-49
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-62 rssi_med:-56 rssi_max:-55
said: 9 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-79 rssi_med:-59 rssi_max:-56
said: 10 | 0x00000011 ble met predicted:-50 observed:-50
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-43 observed:-44
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-49 observed:-49
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-59 observed:-59
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-56 observed:-56
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON2768 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34136318 ±0 frame:20500
seq: 4102
follows: 0x00000010:1119 0x00000011:1064 0x00000012:960 0x00000100:732 0x00000200:1740
said: 1 | **LINKWIN** t_ms:34120149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-80 rssi_med:-56 rssi_max:-55
said: 3 | **LINK** peer:0x00000011 proto:espnow n:129 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 4 | **LINK** peer:0x00000010 proto:espnow n:85 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 5 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 6 | **LINK** peer:0x00000010 proto:ble n:69 rssi_min:-79 rssi_med:-49 rssi_max:-45
said: 7 | **LINK** peer:0x00000011 proto:ble n:72 rssi_min:-53 rssi_med:-50 rssi_max:-49
said: 8 | **LINK** peer:0x00000012 proto:espnow n:118 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 9 | **LINK** peer:0x00000200 proto:espnow n:123 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 10 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000010 ble met predicted:-49 observed:-49
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-50 observed:-50
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-56 observed:-56
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-59 observed:-59
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON2769 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34196318 ±0 frame:20500
seq: 4104
follows: 0x00000010:1120 0x00000011:1065 0x00000012:961 0x00000100:732 0x00000200:1741
said: 1 | **LINKWIN** t_ms:34180149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:98 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 3 | **LINK** peer:0x00000011 proto:espnow n:77 rssi_min:-38 rssi_med:-35 rssi_max:-32
said: 4 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 5 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-53 rssi_med:-50 rssi_max:-49
said: 6 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 7 | **LINK** peer:0x00000012 proto:espnow n:95 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 9 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-63 rssi_med:-56 rssi_max:-55
said: 10 | 0x00000200 ble met predicted:-56 observed:-56
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-59 observed:-59
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-49 observed:-49
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000011 ble met predicted:-50 observed:-50
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON2770 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34256318 ±0 frame:20500
seq: 4106
follows: 0x00000010:1121 0x00000011:1066 0x00000012:962 0x00000100:732 0x00000200:1742
said: 1 | **LINKWIN** t_ms:34240149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-53 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-55 rssi_med:-49 rssi_max:-45
said: 4 | **LINK** peer:0x00000011 proto:espnow n:113 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 5 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000010 proto:espnow n:78 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000200 proto:espnow n:89 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-66 rssi_med:-59 rssi_max:-56
said: 9 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-80 rssi_med:-56 rssi_max:-55
said: 10 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000010 ble met predicted:-49 observed:-49
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000011 ble met predicted:-50 observed:-50
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000012 ble met predicted:-59 observed:-59
percept: 14 | 0x00000012 | link_stable | ble | + | -
said: 15 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-56 observed:-56
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON8380 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34300565 ±0 frame:20500
seq: 4108
follows: 0x00000010:1122 0x00000011:1066 0x00000012:963 0x00000100:732 0x00000200:1743
said: 1 | **ENTWIN** t_ms:34284396 stream:0xa0be1a79 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,e45e1b9f675a,84a329c78fec,0283cce0e689
said: 12 | **COVERED** windows:1 entities:8 window_ms:600001 first_t_ms:33684397 last_t_ms:33684397 covered_by:@LAT103LON8379
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-49 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-64 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-92 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1
```

---

@LAT103LON2771 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34316318 ±0 frame:20500
seq: 4109
follows: 0x00000010:1122 0x00000011:1067 0x00000012:963 0x00000100:732 0x00000200:1743
said: 1 | **LINKWIN** t_ms:34300149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:134 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 3 | **LINK** peer:0x00000010 proto:espnow n:70 rssi_min:-32 rssi_med:-29 rssi_max:-29
said: 4 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-38 rssi_med:-35 rssi_max:-34
said: 5 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-63 rssi_med:-56 rssi_max:-55
said: 7 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-53 rssi_med:-50 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-49 rssi_max:-45
said: 9 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-80 rssi_med:-59 rssi_max:-56
said: 10 | 0x00000011 ble met predicted:-50 observed:-50
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-49 observed:-49
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-59 observed:-59
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-56 observed:-56
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT106LON153 | created:0 | updated:0

**BAR** frame:20500 bar:57 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1112 hi:1121 sum:11165
**HOLDS** agent:0x00000011 n:10 lo:1056 hi:1065 sum:10605
**HOLDS** agent:0x00000012 n:10 lo:953 hi:962 sum:9575
**HOLDS** agent:0x00000200 n:10 lo:1733 hi:1742 sum:17375
**HOLDS** agent:0x00000300 n:10 lo:4086 hi:4104 sum:40950

---

@LAT103LON2772 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34376318 ±0 frame:20500
seq: 4111
follows: 0x00000010:1123 0x00000011:1068 0x00000012:964 0x00000100:732 0x00000200:1744
said: 1 | **LINKWIN** t_ms:34360149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-53 rssi_med:-50 rssi_max:-47
said: 3 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-80 rssi_med:-59 rssi_max:-55
said: 4 | **LINK** peer:0x00000011 proto:espnow n:92 rssi_min:-38 rssi_med:-35 rssi_max:-33
said: 5 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-80 rssi_med:-49 rssi_max:-44
said: 6 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 7 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-56 rssi_max:-53
said: 8 | **LINK** peer:0x00000012 proto:espnow n:132 rssi_min:-49 rssi_med:-44 rssi_max:-42
said: 9 | **LINK** peer:0x00000200 proto:espnow n:70 rssi_min:-46 rssi_med:-44 rssi_max:-42
said: 10 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-35 observed:-35
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-56 observed:-56
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000011 ble met predicted:-50 observed:-50
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-49 observed:-49
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-59 observed:-59
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON2773 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34436318 ±0 frame:20500
seq: 4113
follows: 0x00000010:1124 0x00000011:1068 0x00000012:965 0x00000100:732 0x00000200:1745
said: 1 | **LINKWIN** t_ms:34420149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-50 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-83 rssi_med:-56 rssi_max:-54
said: 4 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-81 rssi_med:-59 rssi_max:-56
said: 5 | **LINK** peer:0x00000012 proto:espnow n:74 rssi_min:-49 rssi_med:-44 rssi_max:-42
said: 6 | **LINK** peer:0x00000010 proto:espnow n:105 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 7 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-49 rssi_max:-45
said: 8 | **LINK** peer:0x00000011 proto:espnow n:69 rssi_min:-38 rssi_med:-33 rssi_max:-32
said: 9 | **LINK** peer:0x00000011 proto:ble n:48 rssi_min:-53 rssi_med:-50 rssi_max:-47
said: 10 | 0x00000011 ble met predicted:-50 observed:-50
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-59 observed:-59
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000011 espnow met predicted:-35 observed:-33
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-49 observed:-49
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-56 observed:-56
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow met predicted:-44 observed:-44
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON2774 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34496318 ±0 frame:20500
seq: 4115
follows: 0x00000010:1125 0x00000011:1070 0x00000012:966 0x00000100:732 0x00000200:1746
said: 1 | **LINKWIN** t_ms:34480149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-69 rssi_med:-47 rssi_max:-44
said: 3 | **LINK** peer:0x00000200 proto:espnow n:104 rssi_min:-50 rssi_med:-45 rssi_max:-43
said: 4 | **LINK** peer:0x00000010 proto:espnow n:116 rssi_min:-55 rssi_med:-28 rssi_max:-27
said: 5 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-64 rssi_med:-50 rssi_max:-47
said: 6 | **LINK** peer:0x00000012 proto:espnow n:123 rssi_min:-49 rssi_med:-46 rssi_max:-44
said: 7 | **LINK** peer:0x00000012 proto:ble n:70 rssi_min:-63 rssi_med:-59 rssi_max:-55
said: 8 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-80 rssi_med:-57 rssi_max:-55
said: 9 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-62 rssi_med:-41 rssi_max:-32
said: 10 | 0x00000200 espnow met predicted:-44 observed:-45
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-56 observed:-57
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000012 ble met predicted:-59 observed:-59
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000012 espnow met predicted:-44 observed:-46
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-29 observed:-28
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-49 observed:-47
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000011 espnow violated predicted:-33 observed:-41
percept: 16 | 0x00000011 | link_stable | espnow | - | -
said: 17 | 0x00000011 ble met predicted:-50 observed:-50
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2775 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34556318 ±0 frame:20500
seq: 4117
follows: 0x00000010:1125 0x00000011:1071 0x00000012:967 0x00000100:732 0x00000200:1747
said: 1 | **LINKWIN** t_ms:34540149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-42 rssi_max:-37
said: 3 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-56 rssi_med:-46 rssi_max:-43
said: 4 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-68 rssi_med:-58 rssi_max:-54
said: 5 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-82 rssi_med:-61 rssi_max:-55
said: 6 | **LINK** peer:0x00000011 proto:espnow n:86 rssi_min:-50 rssi_med:-24 rssi_max:-22
said: 7 | **LINK** peer:0x00000012 proto:espnow n:85 rssi_min:-56 rssi_med:-48 rssi_max:-42
said: 8 | **LINK** peer:0x00000010 proto:ble n:39 rssi_min:-67 rssi_med:-56 rssi_max:-53
said: 9 | **LINK** peer:0x00000010 proto:espnow n:12 rssi_min:-44 rssi_med:-42 rssi_max:-39
said: 10 | 0x00000010 ble violated predicted:-47 observed:-56
percept: 10 | 0x00000010 | link_stable | ble | - | -
said: 11 | 0x00000200 espnow met predicted:-45 observed:-46
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow violated predicted:-28 observed:-42
percept: 12 | 0x00000010 | link_stable | espnow | - | -
said: 13 | 0x00000011 ble violated predicted:-50 observed:-42
percept: 13 | 0x00000011 | link_stable | ble | - | -
said: 14 | 0x00000012 espnow met predicted:-46 observed:-48
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-59 observed:-61
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-57 observed:-58
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow violated predicted:-41 observed:-24
percept: 17 | 0x00000011 | link_stable | espnow | - | -
```

---

@LAT103LON2776 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34616318 ±0 frame:20500
seq: 4119
follows: 0x00000010:1127 0x00000011:1072 0x00000012:969 0x00000100:732 0x00000200:1748
said: 1 | **LINKWIN** t_ms:34600149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-61 rssi_med:-56 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-57 rssi_max:-55
said: 4 | **LINK** peer:0x00000011 proto:espnow n:108 rssi_min:-24 rssi_med:-24 rssi_max:-23
said: 5 | **LINK** peer:0x00000012 proto:espnow n:74 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 6 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-39 rssi_max:-38
said: 7 | **LINK** peer:0x00000012 proto:ble n:46 rssi_min:-83 rssi_med:-61 rssi_max:-58
said: 8 | **LINK** peer:0x00000010 proto:espnow n:42 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 9 | **LINK** peer:0x00000200 proto:espnow n:91 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 10 | 0x00000011 ble met predicted:-42 observed:-39
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-46 observed:-45
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-58 observed:-57
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000012 ble met predicted:-61 observed:-61
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-24 observed:-24
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-48 observed:-47
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-56 observed:-56
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-42 observed:-40
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON2777 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34676318 ±0 frame:20500
seq: 4121
follows: 0x00000010:1128 0x00000011:1073 0x00000012:970 0x00000100:732 0x00000200:1749
said: 1 | **LINKWIN** t_ms:34660149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-43 rssi_med:-39 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-57 rssi_max:-55
said: 4 | **LINK** peer:0x00000012 proto:espnow n:112 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000200 proto:espnow n:70 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 6 | **LINK** peer:0x00000011 proto:espnow n:147 rssi_min:-24 rssi_med:-24 rssi_max:-23
said: 7 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-83 rssi_med:-61 rssi_max:-58
said: 8 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-61 rssi_med:-56 rssi_max:-53
said: 9 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-43 rssi_med:-39 rssi_max:-38
said: 10 | 0x00000010 ble met predicted:-56 observed:-56
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-57 observed:-57
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000011 espnow met predicted:-24 observed:-24
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-39 observed:-39
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-61 observed:-61
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-40 observed:-39
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON2778 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34736318 ±0 frame:20500
seq: 4123
follows: 0x00000010:1129 0x00000011:1074 0x00000012:971 0x00000100:732 0x00000200:1751
said: 1 | **LINKWIN** t_ms:34720149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-61 rssi_max:-58
said: 3 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-82 rssi_med:-39 rssi_max:-38
said: 4 | **LINK** peer:0x00000012 proto:espnow n:111 rssi_min:-48 rssi_med:-47 rssi_max:-44
said: 5 | **LINK** peer:0x00000200 proto:espnow n:98 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 6 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-24 rssi_med:-24 rssi_max:-23
said: 7 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-79 rssi_med:-57 rssi_max:-55
said: 8 | **LINK** peer:0x00000010 proto:espnow n:91 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 9 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-56 rssi_max:-53
said: 10 | 0x00000011 ble met predicted:-39 observed:-39
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-57 observed:-57
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-24 observed:-24
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-61 observed:-61
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-56 observed:-56
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:41262
t_ms:34768026 stream:0xa0be1a79 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:625 last_ms:34199086
t_ms:34768026 stream:0xa0be1a79 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:253 half_life_ms:600000 reinforced:565 last_ms:34190188
t_ms:34768026 stream:0xa0be1a79 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:648 last_ms:34199053
t_ms:34768026 stream:0xa0be1a79 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:605 last_ms:34198670
t_ms:34768026 stream:0xa0be1a79 wall:0

---

@LAT101LON5 | sid:499db878 | created:0 | updated:0 |
**PEER** node:0x00000001 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:34768026 stream:0xa0be1a79 wall:0

---

@LAT103LON2779 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34796318 ±0 frame:20500
seq: 4125
follows: 0x00000010:1130 0x00000011:1075 0x00000012:972 0x00000100:732 0x00000200:1752
said: 1 | **LINKWIN** t_ms:34780149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-39 rssi_max:-38
said: 3 | **LINK** peer:0x00000011 proto:espnow n:77 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 4 | **LINK** peer:0x00000012 proto:espnow n:113 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000200 proto:espnow n:99 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000010 proto:espnow n:131 rssi_min:-43 rssi_med:-39 rssi_max:-38
said: 7 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-82 rssi_med:-61 rssi_max:-58
said: 8 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-57 rssi_max:-55
said: 9 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-61 rssi_med:-56 rssi_max:-54
said: 10 | 0x00000012 ble met predicted:-61 observed:-61
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-39 observed:-39
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-24 observed:-23
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-57 observed:-57
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000010 ble met predicted:-56 observed:-56
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON2780 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34856318 ±0 frame:20500
seq: 4127
follows: 0x00000010:1130 0x00000011:1076 0x00000012:973 0x00000100:732 0x00000200:1753
said: 1 | **LINKWIN** t_ms:34840149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:105 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 3 | **LINK** peer:0x00000010 proto:espnow n:107 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-64 rssi_med:-56 rssi_max:-55
said: 5 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-39 rssi_max:-38
said: 6 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-61 rssi_max:-58
said: 7 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-61 rssi_med:-56 rssi_max:-53
said: 8 | **LINK** peer:0x00000011 proto:espnow n:88 rssi_min:-24 rssi_med:-23 rssi_max:-23
said: 9 | **LINK** peer:0x00000200 proto:espnow n:188 rssi_min:-47 rssi_med:-45 rssi_max:-43
said: 10 | 0x00000011 ble met predicted:-39 observed:-39
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-61 observed:-61
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-57 observed:-56
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-56 observed:-56
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON16504 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 34856318 ±0 frame:20500
seq: 4128
follows: 0x00000010:1130 0x00000011:1076 0x00000012:973 0x00000100:732 0x00000200:1753
said: 1 | **MOTIONWIN** t_ms:34840149 stream:0xa0be1a79 wall:0 window_ms:60000 n:993
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:12 dev_max_mg:16 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26894 window_ms:1740008 moving_permille:0 dev_mean_mg:12 dev_max_mg:170 moving_ms:180 first_t_ms:33100141 last_t_ms:34780149 covered_by:@LAT103LON16503
```

---

@LAT103LON8381 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 34903031 ±0 frame:20500
seq: 4130
follows: 0x00000010:1131 0x00000011:1076 0x00000012:974 0x00000100:732 0x00000200:1754
said: 1 | **ENTWIN** t_ms:34886862 stream:0xa0be1a79 wall:0 window_ms:602466 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-62
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,64677217947d,e6b32d2cea8b,0283cce0e689
```

---

@LAT103LON2781 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34916318 ±0 frame:20500
seq: 4131
follows: 0x00000010:1132 0x00000011:1077 0x00000012:974 0x00000100:732 0x00000200:1754
said: 1 | **LINKWIN** t_ms:34900149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:87 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 3 | **LINK** peer:0x00000012 proto:espnow n:100 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 4 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-83 rssi_med:-61 rssi_max:-58
said: 5 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-61 rssi_med:-56 rssi_max:-51
said: 6 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-80 rssi_med:-39 rssi_max:-38
said: 7 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-56 rssi_max:-55
said: 8 | **LINK** peer:0x00000011 proto:espnow n:93 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 9 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-42 rssi_med:-40 rssi_max:-38
said: 10 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-39 observed:-40
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-56 observed:-56
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000011 ble met predicted:-39 observed:-39
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000012 ble met predicted:-61 observed:-61
percept: 14 | 0x00000012 | link_stable | ble | + | -
said: 15 | 0x00000010 ble met predicted:-56 observed:-56
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT106LON154 | created:0 | updated:0

**BAR** frame:20500 bar:58 own:10 held:36 terms:8 digest:0x27fc0e6b settled_ms:120000
**HOLDS** agent:0x00000010 n:7 lo:1122 hi:1129 sum:7877
**HOLDS** agent:0x00000011 n:9 lo:1066 hi:1075 sum:9635
**HOLDS** agent:0x00000012 n:10 lo:963 hi:973 sum:9679
**HOLDS** agent:0x00000200 n:10 lo:1743 hi:1753 sum:17477
**HOLDS** agent:0x00000300 n:10 lo:4106 hi:4125 sum:41159

---

@LAT103LON2782 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 34976318 ±0 frame:20500
seq: 4133
follows: 0x00000010:1133 0x00000011:1078 0x00000012:975 0x00000100:732 0x00000200:1755
said: 1 | **LINKWIN** t_ms:34960149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:91 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-64 rssi_med:-57 rssi_max:-56
said: 4 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-57 rssi_max:-53
said: 5 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-61 rssi_max:-58
said: 6 | **LINK** peer:0x00000011 proto:espnow n:88 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 7 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-39 rssi_max:-38
said: 8 | **LINK** peer:0x00000012 proto:espnow n:92 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000200 proto:espnow n:60 rssi_min:-47 rssi_med:-46 rssi_max:-45
said: 10 | 0x00000200 espnow met predicted:-45 observed:-46
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000012 ble met predicted:-61 observed:-61
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000010 ble met predicted:-56 observed:-57
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 ble met predicted:-39 observed:-39
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000200 ble met predicted:-56 observed:-57
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000010 espnow met predicted:-40 observed:-39
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON2783 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35036318 ±0 frame:20500
seq: 4135
follows: 0x00000010:1134 0x00000011:1079 0x00000012:976 0x00000100:732 0x00000200:1756
said: 1 | **LINKWIN** t_ms:35020149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-80 rssi_med:-57 rssi_max:-55
said: 3 | **LINK** peer:0x00000012 proto:espnow n:89 rssi_min:-48 rssi_med:-47 rssi_max:-45
said: 4 | **LINK** peer:0x00000200 proto:espnow n:127 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 6 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 7 | **LINK** peer:0x00000011 proto:espnow n:119 rssi_min:-24 rssi_med:-23 rssi_max:-23
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-61 rssi_med:-56 rssi_max:-53
said: 9 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-82 rssi_med:-61 rssi_max:-58
said: 10 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 10 | 0x00000010 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-57 observed:-57
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-57 observed:-56
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000012 ble met predicted:-61 observed:-61
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-39 observed:-39
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000200 espnow met predicted:-46 observed:-45
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON27150 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35036318 ±0 frame:20500
seq: 4136
follows: 0x00000010:1134 0x00000011:1079 0x00000012:976 0x00000100:732 0x00000200:1756
said: 1 | **ACOUSTICWIN** t_ms:35020149 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3456 rate:8000
said: 2 | **ACOUSTIC** rms_mean:84 rms_max:552 peak:1055 transients:0
```

---

@LAT103LON2784 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35096318 ±0 frame:20500
seq: 4137
follows: 0x00000010:1135 0x00000011:1080 0x00000012:977 0x00000100:732 0x00000200:1757
said: 1 | **LINKWIN** t_ms:35080149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:94 rssi_min:-47 rssi_med:-46 rssi_max:-45
said: 3 | **LINK** peer:0x00000011 proto:espnow n:101 rssi_min:-24 rssi_med:-23 rssi_max:-23
said: 4 | **LINK** peer:0x00000012 proto:espnow n:113 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-61 rssi_med:-56 rssi_max:-53
said: 6 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-42 rssi_med:-38 rssi_max:-38
said: 7 | **LINK** peer:0x00000010 proto:espnow n:94 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 8 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-82 rssi_med:-61 rssi_max:-58
said: 9 | **LINK** peer:0x00000200 proto:ble n:71 rssi_min:-79 rssi_med:-57 rssi_max:-55
said: 10 | 0x00000200 ble met predicted:-57 observed:-57
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-46
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-39 observed:-38
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-56 observed:-56
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-61 observed:-61
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON27151 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35096318 ±0 frame:20500
seq: 4138
follows: 0x00000010:1135 0x00000011:1080 0x00000012:977 0x00000100:732 0x00000200:1757
said: 1 | **ACOUSTICWIN** t_ms:35080149 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3692 rate:8000
said: 2 | **ACOUSTIC** rms_mean:82 rms_max:3514 peak:5995 transients:4
said: 3 | **TRANSIENT** t_ms:35073769 stream:0xa0be1a79 wall:0 rms:3514
```

---

@LAT103LON2785 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35156318 ±0 frame:20500
seq: 4139
follows: 0x00000010:1136 0x00000011:1081 0x00000012:978 0x00000100:732 0x00000200:1758
said: 1 | **LINKWIN** t_ms:35140149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-80 rssi_med:-56 rssi_max:-55
said: 3 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-61 rssi_med:-39 rssi_max:-38
said: 4 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:64 rssi_min:-43 rssi_med:-39 rssi_max:-38
said: 6 | **LINK** peer:0x00000200 proto:espnow n:101 rssi_min:-48 rssi_med:-45 rssi_max:-45
said: 7 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-56 rssi_max:-53
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 9 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 10 | 0x00000200 espnow met predicted:-46 observed:-45
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-56 observed:-56
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 ble met predicted:-38 observed:-39
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-61 observed:-61
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-57 observed:-56
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON27152 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35156318 ±0 frame:20500
seq: 4140
follows: 0x00000010:1136 0x00000011:1081 0x00000012:978 0x00000100:732 0x00000200:1758
said: 1 | **ACOUSTICWIN** t_ms:35140149 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3654 rate:8000
said: 2 | **ACOUSTIC** rms_mean:107 rms_max:5035 peak:8680 transients:8
said: 3 | **TRANSIENT** t_ms:35100730 stream:0xa0be1a79 wall:0 rms:5035
```

---

@LAT103LON2786 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35216318 ±0 frame:20500
seq: 4141
follows: 0x00000010:1137 0x00000011:1082 0x00000012:979 0x00000100:732 0x00000200:1759
said: 1 | **LINKWIN** t_ms:35200149 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 4 | **LINK** peer:0x00000012 proto:espnow n:112 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000200 proto:espnow n:72 rssi_min:-47 rssi_med:-46 rssi_max:-45
said: 6 | **LINK** peer:0x00000011 proto:espnow n:122 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 7 | **LINK** peer:0x00000010 proto:espnow n:68 rssi_min:-42 rssi_med:-40 rssi_max:-38
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-57 rssi_max:-55
said: 9 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 10 | 0x00000200 ble met predicted:-56 observed:-57
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-39 observed:-39
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-39 observed:-40
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-46
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-56 observed:-57
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-61 observed:-61
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON27153 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35216318 ±0 frame:20500
seq: 4142
follows: 0x00000010:1137 0x00000011:1082 0x00000012:979 0x00000100:732 0x00000200:1759
said: 1 | **ACOUSTICWIN** t_ms:35200149 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3450 rate:8000
said: 2 | **ACOUSTIC** rms_mean:74 rms_max:480 peak:991 transients:0
```

---

@LAT103LON2787 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35278467 ±0 frame:20500
seq: 4143
follows: 0x00000010:1137 0x00000011:1083 0x00000012:980 0x00000100:732 0x00000200:1760
said: 1 | **LINKWIN** t_ms:35262298 stream:0xa0be1a79 wall:0 window_ms:62149
said: 2 | **LINK** peer:0x00000011 proto:espnow n:82 rssi_min:-24 rssi_med:-23 rssi_max:-23
said: 3 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 4 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-61 rssi_med:-57 rssi_max:-53
said: 5 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-81 rssi_med:-56 rssi_max:-55
said: 6 | **LINK** peer:0x00000010 proto:espnow n:154 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 7 | **LINK** peer:0x00000012 proto:espnow n:91 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-61 rssi_max:-58
said: 9 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-39 rssi_max:-38
said: 10 | 0x00000010 ble met predicted:-57 observed:-57
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-61 observed:-61
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-46 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-40 observed:-39
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-57 observed:-56
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-39 observed:-39
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON27154 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35278467 ±0 frame:20500
seq: 4144
follows: 0x00000010:1137 0x00000011:1083 0x00000012:980 0x00000100:732 0x00000200:1760
said: 1 | **ACOUSTICWIN** t_ms:35262298 stream:0xa0be1a79 wall:0 window_ms:62149 blocks:3551 rate:8000
said: 2 | **ACOUSTIC** rms_mean:75 rms_max:359 peak:751 transients:0
```

---

@LAT103LON2788 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35338467 ±0 frame:20500
seq: 4145
follows: 0x00000010:1139 0x00000011:1084 0x00000012:981 0x00000100:732 0x00000200:1762
said: 1 | **LINKWIN** t_ms:35322298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:75 rssi_min:-47 rssi_med:-46 rssi_max:-45
said: 3 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-61 rssi_med:-56 rssi_max:-53
said: 4 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-64 rssi_med:-56 rssi_max:-55
said: 5 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 6 | **LINK** peer:0x00000010 proto:espnow n:171 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 7 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-83 rssi_med:-61 rssi_max:-58
said: 8 | **LINK** peer:0x00000011 proto:espnow n:87 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 9 | **LINK** peer:0x00000012 proto:espnow n:118 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 10 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-45 observed:-46
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 ble met predicted:-57 observed:-56
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000200 ble met predicted:-56 observed:-56
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-61 observed:-61
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-39 observed:-39
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON27155 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35338467 ±0 frame:20500
seq: 4146
follows: 0x00000010:1139 0x00000011:1084 0x00000012:981 0x00000100:732 0x00000200:1762
said: 1 | **ACOUSTICWIN** t_ms:35322298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3707 rate:8000
said: 2 | **ACOUSTIC** rms_mean:77 rms_max:765 peak:1678 transients:0
```

---

@LAT103LON2789 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35398467 ±0 frame:20500
seq: 4147
follows: 0x00000010:1140 0x00000011:1085 0x00000012:982 0x00000100:732 0x00000200:1763
said: 1 | **LINKWIN** t_ms:35382298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-42 rssi_med:-38 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:ble n:75 rssi_min:-65 rssi_med:-57 rssi_max:-55
said: 4 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-56 rssi_max:-53
said: 5 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-47 rssi_med:-46 rssi_max:-45
said: 6 | **LINK** peer:0x00000012 proto:espnow n:77 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000011 proto:espnow n:89 rssi_min:-24 rssi_med:-23 rssi_max:-23
said: 8 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 9 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 10 | 0x00000200 espnow met predicted:-46 observed:-46
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000010 ble met predicted:-56 observed:-56
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 ble met predicted:-56 observed:-57
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000011 ble met predicted:-39 observed:-38
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-61 observed:-61
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON27156 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35398467 ±0 frame:20500
seq: 4148
follows: 0x00000010:1140 0x00000011:1085 0x00000012:982 0x00000100:732 0x00000200:1763
said: 1 | **ACOUSTICWIN** t_ms:35382298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3429 rate:8000
said: 2 | **ACOUSTIC** rms_mean:74 rms_max:512 peak:1195 transients:0
```

---

@LAT103LON2790 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35458467 ±0 frame:20500
seq: 4149
follows: 0x00000010:1141 0x00000011:1086 0x00000012:983 0x00000100:732 0x00000200:1764
said: 1 | **LINKWIN** t_ms:35442298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:71 rssi_min:-42 rssi_med:-38 rssi_max:-38
said: 3 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:espnow n:76 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 5 | **LINK** peer:0x00000011 proto:espnow n:88 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 6 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-57 rssi_max:-55
said: 7 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-61 rssi_med:-56 rssi_max:-53
said: 8 | **LINK** peer:0x00000010 proto:espnow n:105 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 9 | **LINK** peer:0x00000012 proto:espnow n:151 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 10 | 0x00000011 ble met predicted:-38 observed:-38
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-57 observed:-57
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-56 observed:-56
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000200 espnow met predicted:-46 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-61 observed:-61
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON27157 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35458467 ±0 frame:20500
seq: 4150
follows: 0x00000010:1141 0x00000011:1086 0x00000012:983 0x00000100:732 0x00000200:1764
said: 1 | **ACOUSTICWIN** t_ms:35442298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3430 rate:8000
said: 2 | **ACOUSTIC** rms_mean:110 rms_max:5586 peak:6036 transients:4
said: 3 | **TRANSIENT** t_ms:35416575 stream:0xa0be1a79 wall:0 rms:5586
```

---

@LAT103LON8382 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 35503029 ±0 frame:20500
seq: 4151
follows: 0x00000010:1141 0x00000011:1086 0x00000012:984 0x00000100:732 0x00000200:1765
said: 1 | **ENTWIN** t_ms:35486860 stream:0xa0be1a79 wall:0 window_ms:599998 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-47
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-63
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 8 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 9 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,64677217947d
```

---

@LAT103LON2791 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35518467 ±0 frame:20500
seq: 4152
follows: 0x00000010:1142 0x00000011:1087 0x00000012:984 0x00000100:732 0x00000200:1765
said: 1 | **LINKWIN** t_ms:35502298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:76 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 3 | **LINK** peer:0x00000012 proto:espnow n:137 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 4 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-61 rssi_med:-56 rssi_max:-53
said: 5 | **LINK** peer:0x00000010 proto:espnow n:134 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 6 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-42 rssi_med:-38 rssi_max:-38
said: 7 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-82 rssi_med:-61 rssi_max:-58
said: 8 | **LINK** peer:0x00000200 proto:espnow n:108 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 9 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-64 rssi_med:-57 rssi_max:-55
said: 10 | 0x00000011 ble met predicted:-38 observed:-38
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-61 observed:-61
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-57 observed:-57
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000010 ble met predicted:-56 observed:-56
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON27158 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35518467 ±0 frame:20500
seq: 4153
follows: 0x00000010:1142 0x00000011:1087 0x00000012:984 0x00000100:732 0x00000200:1765
said: 1 | **ACOUSTICWIN** t_ms:35502298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3688 rate:8000
said: 2 | **ACOUSTIC** rms_mean:72 rms_max:325 peak:834 transients:0
```

---

@LAT106LON155 | created:0 | updated:0

**BAR** frame:20500 bar:59 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1131 hi:1140 sum:11355
**HOLDS** agent:0x00000011 n:10 lo:1076 hi:1085 sum:10805
**HOLDS** agent:0x00000012 n:10 lo:974 hi:983 sum:9785
**HOLDS** agent:0x00000200 n:10 lo:1754 hi:1764 sum:17587
**HOLDS** agent:0x00000300 n:10 lo:4127 hi:4147 sum:41378

---

@LAT103LON2792 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35578467 ±0 frame:20500
seq: 4154
follows: 0x00000010:1142 0x00000011:1088 0x00000012:985 0x00000100:732 0x00000200:1766
said: 1 | **LINKWIN** t_ms:35562298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-42 rssi_med:-38 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-47 rssi_med:-46 rssi_max:-45
said: 4 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-61 rssi_med:-56 rssi_max:-54
said: 5 | **LINK** peer:0x00000011 proto:espnow n:74 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 6 | **LINK** peer:0x00000012 proto:espnow n:86 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 8 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-61 rssi_max:-58
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-57 rssi_max:-56
said: 10 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000010 ble met predicted:-56 observed:-56
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-38 observed:-38
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-61 observed:-61
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000200 espnow met predicted:-45 observed:-46
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-57 observed:-57
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON27159 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35578467 ±0 frame:20500
seq: 4155
follows: 0x00000010:1142 0x00000011:1088 0x00000012:985 0x00000100:732 0x00000200:1766
said: 1 | **ACOUSTICWIN** t_ms:35562298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:2578 rate:8000
said: 2 | **ACOUSTIC** rms_mean:84 rms_max:337 peak:848 transients:0
```

---

@LAT103LON2793 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35638467 ±0 frame:20500
seq: 4156
follows: 0x00000010:1144 0x00000011:1089 0x00000012:986 0x00000100:732 0x00000200:1767
said: 1 | **LINKWIN** t_ms:35622298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-79 rssi_med:-56 rssi_max:-55
said: 3 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-42 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-79 rssi_med:-56 rssi_max:-54
said: 5 | **LINK** peer:0x00000011 proto:espnow n:109 rssi_min:-24 rssi_med:-23 rssi_max:-23
said: 6 | **LINK** peer:0x00000200 proto:espnow n:154 rssi_min:-47 rssi_med:-46 rssi_max:-44
said: 7 | **LINK** peer:0x00000012 proto:espnow n:90 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-42 rssi_med:-40 rssi_max:-38
said: 9 | **LINK** peer:0x00000012 proto:ble n:51 rssi_min:-82 rssi_med:-61 rssi_max:-58
said: 10 | 0x00000011 ble met predicted:-38 observed:-38
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-46 observed:-46
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 ble met predicted:-56 observed:-56
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-39 observed:-40
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-61 observed:-61
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-57 observed:-56
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON27160 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35638467 ±0 frame:20500
seq: 4157
follows: 0x00000010:1144 0x00000011:1089 0x00000012:986 0x00000100:732 0x00000200:1767
said: 1 | **ACOUSTICWIN** t_ms:35622298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3675 rate:8000
said: 2 | **ACOUSTIC** rms_mean:99 rms_max:360 peak:784 transients:0
```

---

@LAT105LON4547 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 35643017 ±21 frame:20500
seq: 1768
follows: 0x00000010:1144 0x00000011:1089 0x00000012:986 0x00000100:732 0x00000300:4157
said: 1 | **LINKWIN** t_ms:35626803 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:195 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000011 proto:espnow n:118 rssi_min:-48 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000011 proto:ble n:72 rssi_min:-65 rssi_med:-61 rssi_max:-58
said: 5 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-71 rssi_med:-61 rssi_max:-59
said: 6 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-57 rssi_med:-54 rssi_max:-53
said: 7 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-50 rssi_med:-47 rssi_max:-47
said: 8 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-48 rssi_med:-45 rssi_max:-44
said: 9 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-61 rssi_med:-59 rssi_max:-53
```

---

@LAT105LON4548 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 35648535 ±21 frame:20500
seq: 987
follows: 0x00000010:1144 0x00000011:1089 0x00000100:732 0x00000200:1768 0x00000300:4157
said: 1 | **LINKWIN** t_ms:35632368 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 3 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-80 rssi_med:-66 rssi_max:-59
said: 5 | **LINK** peer:0x00000010 proto:espnow n:89 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 6 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-60 rssi_max:-54
said: 7 | **LINK** peer:0x00000200 proto:espnow n:97 rssi_min:-53 rssi_med:-52 rssi_max:-48
said: 8 | **LINK** peer:0x00000300 proto:espnow n:148 rssi_min:-44 rssi_med:-43 rssi_max:-40
said: 9 | **LINK** peer:0x00000011 proto:espnow n:109 rssi_min:-54 rssi_med:-52 rssi_max:-51
```

---

@LAT105LON4549 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 35691062 ±21 frame:20500
seq: 1145
follows: 0x00000011:1091 0x00000012:987 0x00000100:732 0x00000200:1768 0x00000300:4157
said: 1 | **LINKWIN** t_ms:35674877 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:63 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 3 | **LINK** peer:0x00000012 proto:espnow n:95 rssi_min:-52 rssi_med:-50 rssi_max:-48
said: 4 | **LINK** peer:0x00000300 proto:espnow n:139 rssi_min:-38 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000200 proto:espnow n:75 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 6 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-63 rssi_max:-55
said: 7 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-62 rssi_med:-60 rssi_max:-58
said: 8 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-56 rssi_med:-51 rssi_max:-49
said: 9 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-61 rssi_max:-60
```

---

@LAT105LON4550 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 35682958 ±21 frame:20500
seq: 1091
follows: 0x00000010:1144 0x00000012:987 0x00000100:732 0x00000200:1768 0x00000300:4157
said: 1 | **LINKWIN** t_ms:35666784 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000012 proto:espnow n:83 rssi_min:-55 rssi_med:-54 rssi_max:-54
said: 4 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-52 rssi_med:-51 rssi_max:-49
said: 5 | **LINK** peer:0x00000300 proto:espnow n:146 rssi_min:-17 rssi_med:-16 rssi_max:-15
said: 6 | **LINK** peer:0x00000012 proto:ble n:68 rssi_min:-82 rssi_med:-67 rssi_max:-63
said: 7 | **LINK** peer:0x00000010 proto:espnow n:73 rssi_min:-47 rssi_med:-44 rssi_max:-40
said: 8 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-30 rssi_max:-30
said: 9 | **LINK** peer:0x00000200 proto:ble n:50 rssi_min:-82 rssi_med:-65 rssi_max:-56
```

---

@LAT103LON2794 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35698467 ±0 frame:20500
seq: 4158
follows: 0x00000010:1145 0x00000011:1091 0x00000012:987 0x00000100:732 0x00000200:1768
said: 1 | **LINKWIN** t_ms:35682298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 3 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-61 rssi_med:-56 rssi_max:-53
said: 4 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-56 rssi_max:-55
said: 5 | **LINK** peer:0x00000012 proto:espnow n:83 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 6 | **LINK** peer:0x00000011 proto:espnow n:67 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 7 | **LINK** peer:0x00000200 proto:espnow n:68 rssi_min:-47 rssi_med:-46 rssi_max:-45
said: 8 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-43 rssi_med:-39 rssi_max:-38
said: 9 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-39 rssi_max:-38
said: 10 | 0x00000200 ble met predicted:-56 observed:-56
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-38 observed:-39
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-56 observed:-56
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-46 observed:-46
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-40 observed:-39
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-61 observed:-61
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON27161 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35698467 ±0 frame:20500
seq: 4159
follows: 0x00000010:1145 0x00000011:1091 0x00000012:987 0x00000100:732 0x00000200:1768
said: 1 | **ACOUSTICWIN** t_ms:35682298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3401 rate:8000
said: 2 | **ACOUSTIC** rms_mean:99 rms_max:472 peak:868 transients:0
```

---

@LAT105LON4551 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 35708538 ±21 frame:20500
seq: 988
follows: 0x00000010:1145 0x00000011:1091 0x00000100:732 0x00000200:1769 0x00000300:4159
said: 1 | **LINKWIN** t_ms:35692368 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 4 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-60 rssi_max:-54
said: 5 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-64 rssi_max:-59
said: 6 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-51 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000300 proto:espnow n:148 rssi_min:-44 rssi_med:-43 rssi_max:-42
said: 8 | **LINK** peer:0x00000200 proto:espnow n:108 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 9 | **LINK** peer:0x00000011 proto:espnow n:57 rssi_min:-53 rssi_med:-52 rssi_max:-51
```

---

@LAT105LON4552 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 35703016 ±21 frame:20500
seq: 1769
follows: 0x00000010:1145 0x00000011:1091 0x00000012:987 0x00000100:732 0x00000300:4159
said: 1 | **LINKWIN** t_ms:35686804 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:162 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000011 proto:espnow n:70 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-59 rssi_max:-53
said: 5 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-57 rssi_med:-54 rssi_max:-53
said: 6 | **LINK** peer:0x00000010 proto:espnow n:105 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-65 rssi_med:-61 rssi_max:-59
said: 8 | **LINK** peer:0x00000012 proto:espnow n:68 rssi_min:-50 rssi_med:-47 rssi_max:-47
said: 9 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-65 rssi_med:-61 rssi_max:-58
```

---

@LAT105LON4553 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 35742959 ±21 frame:20500
seq: 1092
follows: 0x00000010:1145 0x00000012:988 0x00000100:732 0x00000200:1769 0x00000300:4159
said: 1 | **LINKWIN** t_ms:35726784 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:167 rssi_min:-17 rssi_med:-16 rssi_max:-15
said: 3 | **LINK** peer:0x00000200 proto:espnow n:124 rssi_min:-52 rssi_med:-51 rssi_max:-49
said: 4 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-62 rssi_max:-60
said: 5 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-47 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-82 rssi_med:-67 rssi_max:-63
said: 7 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-64 rssi_max:-56
said: 8 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-55 rssi_med:-54 rssi_max:-54
said: 9 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-30 rssi_max:-30
```

---

@LAT105LON4554 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 35751061 ±21 frame:20500
seq: 1146
follows: 0x00000011:1092 0x00000012:988 0x00000100:732 0x00000200:1769 0x00000300:4159
said: 1 | **LINKWIN** t_ms:35734877 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:66 rssi_min:-52 rssi_med:-50 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:156 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | **LINK** peer:0x00000300 proto:espnow n:146 rssi_min:-38 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-56 rssi_med:-51 rssi_max:-48
said: 7 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-64 rssi_med:-63 rssi_max:-55
said: 8 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-81 rssi_med:-59 rssi_max:-58
said: 9 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-61 rssi_max:-60
```

---

@LAT103LON2795 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35758467 ±0 frame:20500
seq: 4160
follows: 0x00000010:1146 0x00000011:1092 0x00000012:988 0x00000100:732 0x00000200:1769
said: 1 | **LINKWIN** t_ms:35742298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-56 rssi_max:-53
said: 3 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 4 | **LINK** peer:0x00000012 proto:espnow n:86 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000200 proto:espnow n:144 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 6 | **LINK** peer:0x00000010 proto:espnow n:88 rssi_min:-43 rssi_med:-40 rssi_max:-39
said: 7 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 8 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-57 rssi_max:-55
said: 9 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 10 | 0x00000012 ble met predicted:-61 observed:-61
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-56 observed:-56
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 ble met predicted:-56 observed:-57
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-46 observed:-45
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-39 observed:-40
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-39 observed:-39
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON27162 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35758467 ±0 frame:20500
seq: 4161
follows: 0x00000010:1146 0x00000011:1092 0x00000012:988 0x00000100:732 0x00000200:1769
said: 1 | **ACOUSTICWIN** t_ms:35742298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3703 rate:8000
said: 2 | **ACOUSTIC** rms_mean:97 rms_max:351 peak:874 transients:0
```

---

@LAT105LON4555 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 35763018 ±21 frame:20500
seq: 1770
follows: 0x00000010:1146 0x00000011:1092 0x00000012:988 0x00000100:732 0x00000300:4161
said: 1 | **LINKWIN** t_ms:35746804 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:78 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:176 rssi_min:-42 rssi_med:-42 rssi_max:-40
said: 4 | **LINK** peer:0x00000011 proto:espnow n:101 rssi_min:-49 rssi_med:-48 rssi_max:-45
said: 5 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-60 rssi_max:-59
said: 6 | **LINK** peer:0x00000010 proto:espnow n:83 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-65 rssi_med:-61 rssi_max:-58
said: 8 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-62 rssi_med:-59 rssi_max:-53
said: 9 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-57 rssi_med:-54 rssi_max:-53
```

---

@LAT105LON4556 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 35768538 ±21 frame:20500
seq: 989
follows: 0x00000010:1146 0x00000011:1092 0x00000100:732 0x00000200:1770 0x00000300:4161
said: 1 | **LINKWIN** t_ms:35752368 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-54 rssi_med:-52 rssi_max:-51
said: 3 | **LINK** peer:0x00000200 proto:espnow n:147 rssi_min:-53 rssi_med:-52 rssi_max:-50
said: 4 | **LINK** peer:0x00000300 proto:espnow n:156 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 5 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-82 rssi_med:-60 rssi_max:-54
said: 6 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-61 rssi_max:-58
said: 7 | **LINK** peer:0x00000010 proto:espnow n:79 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 8 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 9 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-80 rssi_med:-64 rssi_max:-60
```

---

@LAT105LON4557 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 35802960 ±21 frame:20500
seq: 1093
follows: 0x00000010:1147 0x00000012:990 0x00000100:732 0x00000200:1770 0x00000300:4161
said: 1 | **LINKWIN** t_ms:35786784 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:70 rssi_min:-82 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000200 proto:espnow n:110 rssi_min:-52 rssi_med:-51 rssi_max:-49
said: 4 | **LINK** peer:0x00000300 proto:espnow n:147 rssi_min:-17 rssi_med:-16 rssi_max:-15
said: 5 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-55 rssi_med:-54 rssi_max:-54
said: 6 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-47 rssi_med:-45 rssi_max:-43
said: 7 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-81 rssi_med:-30 rssi_max:-30
said: 8 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-67 rssi_max:-62
said: 9 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-66 rssi_max:-56
```

---

@LAT105LON4558 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 35811063 ±21 frame:20500
seq: 1148
follows: 0x00000011:1093 0x00000012:990 0x00000100:732 0x00000200:1770 0x00000300:4161
said: 1 | **LINKWIN** t_ms:35794876 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-59 rssi_max:-57
said: 3 | **LINK** peer:0x00000011 proto:espnow n:85 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:espnow n:146 rssi_min:-38 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000012 proto:espnow n:108 rssi_min:-52 rssi_med:-51 rssi_max:-48
said: 6 | **LINK** peer:0x00000200 proto:espnow n:118 rssi_min:-48 rssi_med:-46 rssi_max:-45
said: 7 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-51 rssi_max:-49
said: 8 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-64 rssi_med:-63 rssi_max:-56
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-76 rssi_med:-61 rssi_max:-59
```

---

@LAT103LON2796 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35818467 ±0 frame:20500
seq: 4162
follows: 0x00000010:1148 0x00000011:1093 0x00000012:990 0x00000100:732 0x00000200:1770
said: 1 | **LINKWIN** t_ms:35802298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-79 rssi_med:-38 rssi_max:-38
said: 3 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 4 | **LINK** peer:0x00000010 proto:espnow n:69 rssi_min:-42 rssi_med:-40 rssi_max:-38
said: 5 | **LINK** peer:0x00000011 proto:espnow n:93 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 6 | **LINK** peer:0x00000012 proto:espnow n:114 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-64 rssi_med:-57 rssi_max:-55
said: 8 | **LINK** peer:0x00000200 proto:espnow n:115 rssi_min:-47 rssi_med:-46 rssi_max:-43
said: 9 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-61 rssi_med:-56 rssi_max:-53
said: 10 | 0x00000010 ble met predicted:-56 observed:-56
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-61 observed:-61
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-46
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-57 observed:-57
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-39 observed:-38
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON27163 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35818467 ±0 frame:20500
seq: 4163
follows: 0x00000010:1148 0x00000011:1093 0x00000012:990 0x00000100:732 0x00000200:1770
said: 1 | **ACOUSTICWIN** t_ms:35802298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3435 rate:8000
said: 2 | **ACOUSTIC** rms_mean:100 rms_max:460 peak:1378 transients:0
```

---

@LAT105LON4559 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 35823020 ±21 frame:20500
seq: 1771
follows: 0x00000010:1148 0x00000011:1093 0x00000012:990 0x00000100:732 0x00000300:4163
said: 1 | **LINKWIN** t_ms:35806804 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:126 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 3 | **LINK** peer:0x00000011 proto:espnow n:110 rssi_min:-48 rssi_med:-48 rssi_max:-45
said: 4 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-65 rssi_med:-61 rssi_max:-59
said: 5 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-62 rssi_med:-59 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 7 | **LINK** peer:0x00000010 proto:espnow n:55 rssi_min:-48 rssi_med:-46 rssi_max:-44
said: 8 | **LINK** peer:0x00000011 proto:ble n:51 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 9 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-50 rssi_med:-48 rssi_max:-46
```

---

@LAT105LON4560 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 35828538 ±21 frame:20500
seq: 991
follows: 0x00000010:1148 0x00000011:1093 0x00000100:732 0x00000200:1771 0x00000300:4163
said: 1 | **LINKWIN** t_ms:35812367 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:113 rssi_min:-44 rssi_med:-43 rssi_max:-42
said: 3 | **LINK** peer:0x00000010 proto:espnow n:60 rssi_min:-51 rssi_med:-50 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 5 | **LINK** peer:0x00000011 proto:espnow n:93 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 6 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-81 rssi_med:-61 rssi_max:-57
said: 7 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-80 rssi_med:-63 rssi_max:-60
said: 8 | **LINK** peer:0x00000300 proto:ble n:49 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-59 rssi_max:-54
```

---

@LAT105LON4561 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 35862959 ±21 frame:20500
seq: 1094
follows: 0x00000010:1148 0x00000012:991 0x00000100:732 0x00000200:1771 0x00000300:4163
said: 1 | **LINKWIN** t_ms:35846784 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-67 rssi_max:-63
said: 3 | **LINK** peer:0x00000012 proto:espnow n:113 rssi_min:-55 rssi_med:-54 rssi_max:-53
said: 4 | **LINK** peer:0x00000300 proto:espnow n:177 rssi_min:-17 rssi_med:-16 rssi_max:-15
said: 5 | **LINK** peer:0x00000200 proto:espnow n:89 rssi_min:-51 rssi_med:-51 rssi_max:-50
said: 6 | **LINK** peer:0x00000010 proto:espnow n:72 rssi_min:-47 rssi_med:-45 rssi_max:-43
said: 7 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-81 rssi_med:-64 rssi_max:-56
said: 8 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-62 rssi_max:-60
said: 9 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-79 rssi_med:-30 rssi_max:-29
```

---

@LAT103LON2797 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35878467 ±0 frame:20500
seq: 4164
follows: 0x00000010:1149 0x00000011:1094 0x00000012:991 0x00000100:732 0x00000200:1771
said: 1 | **LINKWIN** t_ms:35862298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-71 rssi_med:-57 rssi_max:-55
said: 3 | **LINK** peer:0x00000012 proto:espnow n:98 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 4 | **LINK** peer:0x00000011 proto:espnow n:87 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 5 | **LINK** peer:0x00000200 proto:espnow n:96 rssi_min:-47 rssi_med:-46 rssi_max:-45
said: 6 | **LINK** peer:0x00000010 proto:espnow n:87 rssi_min:-43 rssi_med:-40 rssi_max:-38
said: 7 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-56 rssi_max:-53
said: 8 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-42 rssi_med:-38 rssi_max:-37
said: 9 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-80 rssi_med:-61 rssi_max:-58
said: 10 | 0x00000011 ble met predicted:-38 observed:-38
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-61 observed:-61
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000010 espnow met predicted:-40 observed:-40
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-57 observed:-57
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000200 espnow met predicted:-46 observed:-46
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000010 ble met predicted:-56 observed:-56
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON27164 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35878467 ±0 frame:20500
seq: 4165
follows: 0x00000010:1149 0x00000011:1094 0x00000012:991 0x00000100:732 0x00000200:1771
said: 1 | **ACOUSTICWIN** t_ms:35862298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3689 rate:8000
said: 2 | **ACOUSTIC** rms_mean:167 rms_max:4636 peak:5035 transients:14
said: 3 | **TRANSIENT** t_ms:35841813 stream:0xa0be1a79 wall:0 rms:4424
```

---

@LAT105LON4562 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 35883038 ±21 frame:20500
seq: 1772
follows: 0x00000010:1149 0x00000011:1094 0x00000012:991 0x00000100:732 0x00000300:4165
said: 1 | **LINKWIN** t_ms:35866821 stream:0xa0be1a79 wall:0 window_ms:60017
said: 2 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-79 rssi_med:-59 rssi_max:-53
said: 3 | **LINK** peer:0x00000012 proto:espnow n:92 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 4 | **LINK** peer:0x00000011 proto:espnow n:103 rssi_min:-48 rssi_med:-48 rssi_max:-45
said: 5 | **LINK** peer:0x00000300 proto:espnow n:169 rssi_min:-42 rssi_med:-42 rssi_max:-41
said: 6 | **LINK** peer:0x00000010 proto:espnow n:92 rssi_min:-47 rssi_med:-46 rssi_max:-44
said: 7 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-57 rssi_med:-54 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 9 | **LINK** peer:0x00000011 proto:ble n:49 rssi_min:-80 rssi_med:-61 rssi_max:-58
```

---

@LAT105LON4563 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 35888537 ±21 frame:20500
seq: 992
follows: 0x00000010:1149 0x00000011:1094 0x00000100:732 0x00000200:1772 0x00000300:4165
said: 1 | **LINKWIN** t_ms:35872368 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-63 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-61 rssi_max:-58
said: 4 | **LINK** peer:0x00000011 proto:espnow n:79 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 5 | **LINK** peer:0x00000200 proto:espnow n:75 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 6 | **LINK** peer:0x00000010 proto:espnow n:105 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000300 proto:espnow n:180 rssi_min:-44 rssi_med:-43 rssi_max:-40
said: 8 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-60 rssi_max:-54
said: 9 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-82 rssi_med:-54 rssi_max:-53
```

---

@LAT105LON4564 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 35871063 ±21 frame:20500
seq: 1149
follows: 0x00000011:1094 0x00000012:991 0x00000100:732 0x00000200:1771 0x00000300:4163
said: 1 | **LINKWIN** t_ms:35854876 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:92 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000012 proto:espnow n:80 rssi_min:-52 rssi_med:-50 rssi_max:-48
said: 4 | **LINK** peer:0x00000300 proto:espnow n:176 rssi_min:-38 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-59 rssi_max:-58
said: 6 | **LINK** peer:0x00000200 proto:espnow n:94 rssi_min:-48 rssi_med:-46 rssi_max:-45
said: 7 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-79 rssi_med:-61 rssi_max:-60
said: 8 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-63 rssi_max:-55
said: 9 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-56 rssi_med:-51 rssi_max:-49
```

---

@LAT105LON4565 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 35922981 ±21 frame:20500
seq: 1095
follows: 0x00000010:1149 0x00000012:992 0x00000100:732 0x00000200:1772 0x00000300:4165
said: 1 | **LINKWIN** t_ms:35906805 stream:0xa0be1a79 wall:0 window_ms:60021
said: 2 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-82 rssi_med:-67 rssi_max:-63
said: 3 | **LINK** peer:0x00000300 proto:ble n:70 rssi_min:-82 rssi_med:-30 rssi_max:-29
said: 4 | **LINK** peer:0x00000200 proto:espnow n:73 rssi_min:-54 rssi_med:-51 rssi_max:-49
said: 5 | **LINK** peer:0x00000012 proto:espnow n:95 rssi_min:-55 rssi_med:-54 rssi_max:-54
said: 6 | **LINK** peer:0x00000300 proto:espnow n:105 rssi_min:-17 rssi_med:-16 rssi_max:-15
said: 7 | **LINK** peer:0x00000010 proto:espnow n:139 rssi_min:-47 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-81 rssi_med:-65 rssi_max:-56
said: 9 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-62 rssi_max:-60
```

---

@LAT103LON2798 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35938467 ±0 frame:20500
seq: 4166
follows: 0x00000010:1150 0x00000011:1095 0x00000012:992 0x00000100:732 0x00000200:1772
said: 1 | **LINKWIN** t_ms:35922298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:70 rssi_min:-61 rssi_med:-57 rssi_max:-53
said: 3 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-79 rssi_med:-56 rssi_max:-55
said: 4 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-42 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000012 proto:espnow n:97 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 6 | **LINK** peer:0x00000200 proto:espnow n:88 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 7 | **LINK** peer:0x00000011 proto:espnow n:69 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 8 | **LINK** peer:0x00000010 proto:espnow n:139 rssi_min:-43 rssi_med:-39 rssi_max:-39
said: 9 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-80 rssi_med:-61 rssi_max:-58
said: 10 | 0x00000200 ble met predicted:-57 observed:-56
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-46 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-40 observed:-39
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-56 observed:-57
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-38 observed:-38
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-61 observed:-61
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON27165 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35938467 ±0 frame:20500
seq: 4167
follows: 0x00000010:1150 0x00000011:1095 0x00000012:992 0x00000100:732 0x00000200:1772
said: 1 | **ACOUSTICWIN** t_ms:35922298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3457 rate:8000
said: 2 | **ACOUSTIC** rms_mean:100 rms_max:637 peak:1781 transients:0
```

---

@LAT104LON618 | created:0 | updated:0

**carried through @LAT103LON2753**

```ttdb-carried
through: 2753
through: 8335
through: 16482
through: 27149
carried: 2011 34 2244 2000 | 0x00000200 | link_stable | espnow
carried: 2141 24 2521 2048 | 0x00000200 | link_stable | ble
carried: 925 13 1291 817 | 0x00000100 | link_stable | espnow
carried: 1465 15 1834 1364 | 0x00000010 | link_stable | ble
carried: 1401 27 1781 1326 | 0x00000010 | link_stable | espnow
carried: 977 7 984 1009 | 0x00000011 | link_stable | ble
carried: 876 17 893 911 | 0x00000011 | link_stable | espnow
carried: 918 9 927 942 | 0x00000012 | link_stable | ble
carried: 897 7 904 926 | 0x00000012 | link_stable | espnow
```

---

@LAT105LON4566 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 35938792 ±21 frame:20500
seq: 1773
follows: 0x00000010:1150 0x00000011:1095 0x00000012:992 0x00000100:732 0x00000300:4167
said: 1 | **LINKWIN** t_ms:35926843 stream:0xa0be1a79 wall:0 window_ms:60022
said: 2 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-62 rssi_med:-59 rssi_max:-53
said: 3 | **LINK** peer:0x00000011 proto:espnow n:67 rssi_min:-48 rssi_med:-48 rssi_max:-45
said: 4 | **LINK** peer:0x00000012 proto:espnow n:77 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 5 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-65 rssi_med:-61 rssi_max:-59
said: 6 | **LINK** peer:0x00000300 proto:espnow n:102 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 7 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-54 rssi_max:-53
said: 8 | **LINK** peer:0x00000010 proto:espnow n:142 rssi_min:-49 rssi_med:-45 rssi_max:-44
said: 9 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-65 rssi_med:-61 rssi_max:-58
```

---

@LAT105LON4567 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 35931063 ±21 frame:20500
seq: 1150
follows: 0x00000011:1095 0x00000012:992 0x00000100:732 0x00000200:1772 0x00000300:4165
said: 1 | **LINKWIN** t_ms:35914877 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-64 rssi_med:-63 rssi_max:-55
said: 3 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-47 rssi_med:-46 rssi_max:-45
said: 4 | **LINK** peer:0x00000011 proto:espnow n:71 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000300 proto:espnow n:95 rssi_min:-38 rssi_med:-34 rssi_max:-33
said: 6 | **LINK** peer:0x00000012 proto:espnow n:92 rssi_min:-52 rssi_med:-51 rssi_max:-49
said: 7 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-81 rssi_med:-51 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-80 rssi_med:-62 rssi_max:-60
said: 9 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-80 rssi_med:-59 rssi_max:-58
```

---

@LAT105LON4568 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 35948539 ±21 frame:20500
seq: 993
follows: 0x00000010:1150 0x00000011:1095 0x00000100:732 0x00000200:1773 0x00000300:4167
said: 1 | **LINKWIN** t_ms:35932367 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:137 rssi_min:-44 rssi_med:-43 rssi_max:-40
said: 3 | **LINK** peer:0x00000010 proto:espnow n:142 rssi_min:-51 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:67 rssi_min:-54 rssi_med:-52 rssi_max:-51
said: 5 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-53
said: 6 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-60 rssi_max:-53
said: 7 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-80 rssi_med:-61 rssi_max:-58
said: 8 | **LINK** peer:0x00000200 proto:espnow n:94 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 9 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-64 rssi_max:-60
```

---

@LAT105LON4569 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 35983002 ±21 frame:20500
seq: 1096
follows: 0x00000010:1150 0x00000012:993 0x00000100:732 0x00000200:1773 0x00000300:4167
said: 1 | **LINKWIN** t_ms:35966825 stream:0xa0be1a79 wall:0 window_ms:60020
said: 2 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-82 rssi_med:-64 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-52 rssi_med:-51 rssi_max:-49
said: 4 | **LINK** peer:0x00000300 proto:espnow n:189 rssi_min:-17 rssi_med:-16 rssi_max:-15
said: 5 | **LINK** peer:0x00000010 proto:espnow n:135 rssi_min:-47 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-67 rssi_max:-63
said: 7 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-30 rssi_max:-29
said: 8 | **LINK** peer:0x00000012 proto:espnow n:100 rssi_min:-55 rssi_med:-54 rssi_max:-54
said: 9 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-80 rssi_med:-62 rssi_max:-60
```

---

@LAT103LON2799 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 35998467 ±0 frame:20500
seq: 4168
follows: 0x00000010:1151 0x00000011:1096 0x00000012:993 0x00000100:732 0x00000200:1773
said: 1 | **LINKWIN** t_ms:35982298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:128 rssi_min:-42 rssi_med:-39 rssi_max:-38
said: 3 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-47 rssi_med:-47 rssi_max:-46
said: 4 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-63 rssi_med:-57 rssi_max:-55
said: 5 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-61 rssi_med:-56 rssi_max:-54
said: 6 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-38 rssi_max:-38
said: 7 | **LINK** peer:0x00000011 proto:espnow n:143 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 8 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-61 rssi_max:-58
said: 10 | 0x00000010 ble met predicted:-57 observed:-56
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-56 observed:-57
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000011 ble met predicted:-38 observed:-38
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-61 observed:-61
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON27166 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 35998467 ±0 frame:20500
seq: 4169
follows: 0x00000010:1151 0x00000011:1096 0x00000012:993 0x00000100:732 0x00000200:1773
said: 1 | **ACOUSTICWIN** t_ms:35982298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3416 rate:8000
said: 2 | **ACOUSTIC** rms_mean:130 rms_max:4914 peak:5391 transients:7
said: 3 | **TRANSIENT** t_ms:35961718 stream:0xa0be1a79 wall:0 rms:4914
```

---

@LAT105LON4570 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 36008614 ±21 frame:20500
seq: 994
follows: 0x00000010:1151 0x00000011:1096 0x00000100:732 0x00000200:1774 0x00000300:4169
said: 1 | **LINKWIN** t_ms:35992443 stream:0xa0be1a79 wall:0 window_ms:60075
said: 2 | **LINK** peer:0x00000300 proto:espnow n:192 rssi_min:-54 rssi_med:-43 rssi_max:-40
said: 3 | **LINK** peer:0x00000010 proto:espnow n:122 rssi_min:-52 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:espnow n:94 rssi_min:-60 rssi_med:-52 rssi_max:-47
said: 5 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-80 rssi_med:-64 rssi_max:-59
said: 6 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-61 rssi_max:-58
said: 7 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-54 rssi_max:-53
said: 8 | **LINK** peer:0x00000011 proto:espnow n:157 rssi_min:-60 rssi_med:-52 rssi_max:-51
said: 9 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-81 rssi_med:-60 rssi_max:-54
```

---

@LAT105LON4571 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 36003063 ±21 frame:20500
seq: 1774
follows: 0x00000010:1151 0x00000011:1096 0x00000012:993 0x00000100:732 0x00000300:4169
said: 1 | **LINKWIN** t_ms:35986843 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-65 rssi_med:-61 rssi_max:-58
said: 3 | **LINK** peer:0x00000300 proto:espnow n:236 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-66 rssi_med:-61 rssi_max:-58
said: 5 | **LINK** peer:0x00000011 proto:espnow n:145 rssi_min:-49 rssi_med:-48 rssi_max:-45
said: 6 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 7 | **LINK** peer:0x00000010 proto:espnow n:117 rssi_min:-48 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-59 rssi_max:-53
said: 9 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-57 rssi_med:-54 rssi_max:-53
```

---

@LAT105LON4572 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 35991065 ±21 frame:20500
seq: 1151
follows: 0x00000011:1096 0x00000012:993 0x00000100:732 0x00000200:1773 0x00000300:4167
said: 1 | **LINKWIN** t_ms:35974876 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:127 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000300 proto:espnow n:200 rssi_min:-38 rssi_med:-34 rssi_max:-31
said: 4 | **LINK** peer:0x00000200 proto:espnow n:90 rssi_min:-48 rssi_med:-46 rssi_max:-45
said: 5 | **LINK** peer:0x00000012 proto:espnow n:109 rssi_min:-52 rssi_med:-50 rssi_max:-49
said: 6 | **LINK** peer:0x00000300 proto:ble n:72 rssi_min:-74 rssi_med:-51 rssi_max:-49
said: 7 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-61 rssi_max:-60
said: 8 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-64 rssi_med:-63 rssi_max:-55
said: 9 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-59 rssi_max:-57
```

---

@LAT105LON4573 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 36043002 ±21 frame:20500
seq: 1097
follows: 0x00000010:1151 0x00000012:994 0x00000100:732 0x00000200:1774 0x00000300:4169
said: 1 | **LINKWIN** t_ms:36026825 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:102 rssi_min:-61 rssi_med:-52 rssi_max:-32
said: 3 | **LINK** peer:0x00000300 proto:espnow n:202 rssi_min:-17 rssi_med:-16 rssi_max:-14
said: 4 | **LINK** peer:0x00000010 proto:espnow n:121 rssi_min:-61 rssi_med:-44 rssi_max:-36
said: 5 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-30 rssi_max:-29
said: 6 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-81 rssi_med:-64 rssi_max:-45
said: 7 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-55 rssi_max:-50
said: 8 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-66 rssi_max:-56
said: 9 | **LINK** peer:0x00000200 proto:espnow n:121 rssi_min:-64 rssi_med:-55 rssi_max:-49
```

---

@LAT103LON2800 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 36058467 ±0 frame:20500
seq: 4170
follows: 0x00000010:1151 0x00000011:1097 0x00000012:994 0x00000100:732 0x00000200:1774
said: 1 | **LINKWIN** t_ms:36042298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-68 rssi_med:-58 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-58 rssi_med:-47 rssi_max:-44
said: 4 | **LINK** peer:0x00000010 proto:espnow n:80 rssi_min:-67 rssi_med:-44 rssi_max:-37
said: 5 | **LINK** peer:0x00000012 proto:espnow n:84 rssi_min:-61 rssi_med:-47 rssi_max:-37
said: 6 | **LINK** peer:0x00000011 proto:espnow n:90 rssi_min:-25 rssi_med:-23 rssi_max:-22
said: 7 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-80 rssi_med:-38 rssi_max:-37
said: 8 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-60 rssi_max:-53
said: 9 | **LINK** peer:0x00000012 proto:ble n:45 rssi_min:-82 rssi_med:-59 rssi_max:-51
said: 10 | 0x00000010 espnow met predicted:-39 observed:-44
percept: 10 | 0x00000010 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-57 observed:-58
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000010 ble met predicted:-56 observed:-60
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 ble met predicted:-38 observed:-38
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000200 espnow met predicted:-45 observed:-47
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-61 observed:-59
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON27167 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 36058467 ±0 frame:20500
seq: 4171
follows: 0x00000010:1151 0x00000011:1097 0x00000012:994 0x00000100:732 0x00000200:1774
said: 1 | **ACOUSTICWIN** t_ms:36042298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3696 rate:8000
said: 2 | **ACOUSTIC** rms_mean:124 rms_max:6003 peak:23180 transients:7
said: 3 | **TRANSIENT** t_ms:35990046 stream:0xa0be1a79 wall:0 rms:6003
```

---

@LAT105LON4574 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 36051065 ±21 frame:20500
seq: 1152
follows: 0x00000011:1097 0x00000012:994 0x00000100:732 0x00000200:1774 0x00000300:4169
said: 1 | **LINKWIN** t_ms:36034877 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-72 rssi_med:-53 rssi_max:-47
said: 3 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-82 rssi_med:-52 rssi_max:-41
said: 4 | **LINK** peer:0x00000011 proto:espnow n:92 rssi_min:-52 rssi_med:-41 rssi_max:-34
said: 5 | **LINK** peer:0x00000300 proto:espnow n:166 rssi_min:-53 rssi_med:-36 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-79 rssi_med:-52 rssi_max:-46
said: 7 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-77 rssi_med:-63 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-62 rssi_med:-49 rssi_max:-45
said: 9 | **LINK** peer:0x00000012 proto:espnow n:100 rssi_min:-59 rssi_med:-50 rssi_max:-26
```

---

@LAT105LON4575 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 36063063 ±21 frame:20500
seq: 1775
follows: 0x00000010:1152 0x00000011:1097 0x00000012:994 0x00000100:732 0x00000300:4171
said: 1 | **LINKWIN** t_ms:36046894 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:97 rssi_min:-63 rssi_med:-50 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-62 rssi_med:-55 rssi_max:-53
said: 4 | **LINK** peer:0x00000012 proto:ble n:50 rssi_min:-81 rssi_med:-60 rssi_max:-50
said: 5 | **LINK** peer:0x00000011 proto:espnow n:77 rssi_min:-57 rssi_med:-52 rssi_max:-48
said: 6 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-70 rssi_med:-64 rssi_max:-56
said: 7 | **LINK** peer:0x00000012 proto:espnow n:78 rssi_min:-70 rssi_med:-47 rssi_max:-32
said: 8 | **LINK** peer:0x00000300 proto:espnow n:187 rssi_min:-56 rssi_med:-44 rssi_max:-39
said: 9 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-62 rssi_max:-52
```

---

@LAT103LON8383 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36103029 ±0 frame:20500
seq: 4172
follows: 0x00000010:1152 0x00000011:1097 0x00000012:994 0x00000100:732 0x00000200:1775
said: 1 | **ENTWIN** t_ms:36086860 stream:0xa0be1a79 wall:0 window_ms:600000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-48
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-61
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,84a329c78fec,e6b32d2cea8b
```

---

@LAT105LON4576 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 36103003 ±21 frame:20500
seq: 1098
follows: 0x00000010:1152 0x00000012:994 0x00000100:732 0x00000200:1775 0x00000300:4171
said: 1 | **LINKWIN** t_ms:36086825 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:65 rssi_min:-63 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000300 proto:espnow n:158 rssi_min:-17 rssi_med:-16 rssi_max:-15
said: 4 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-47 rssi_med:-43 rssi_max:-41
said: 5 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-67 rssi_max:-59
said: 6 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-30 rssi_max:-29
said: 7 | **LINK** peer:0x00000012 proto:ble n:49 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 8 | **LINK** peer:0x00000012 proto:espnow n:31 rssi_min:-45 rssi_med:-33 rssi_max:-31
said: 9 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-53 rssi_max:-51
```

---

@LAT103LON2801 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 36118467 ±0 frame:20500
seq: 4173
follows: 0x00000010:1153 0x00000011:1098 0x00000012:996 0x00000100:732 0x00000200:1775
said: 1 | **LINKWIN** t_ms:36102298 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-68 rssi_med:-59 rssi_max:-54
said: 3 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-74 rssi_med:-62 rssi_max:-53
said: 4 | **LINK** peer:0x00000011 proto:espnow n:74 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 5 | **LINK** peer:0x00000200 proto:espnow n:72 rssi_min:-51 rssi_med:-47 rssi_max:-41
said: 6 | **LINK** peer:0x00000010 proto:espnow n:79 rssi_min:-63 rssi_med:-46 rssi_max:-41
said: 7 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-48 rssi_med:-38 rssi_max:-37
said: 8 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-64 rssi_med:-55 rssi_max:-51
said: 9 | **LINK** peer:0x00000012 proto:espnow n:58 rssi_min:-52 rssi_med:-42 rssi_max:-37
said: 10 | 0x00000200 ble met predicted:-58 observed:-59
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-47 observed:-47
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-44 observed:-46
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-47 observed:-42
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-23 observed:-23
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-38 observed:-38
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-60 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-59 observed:-55
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON27168 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 36118467 ±0 frame:20500
seq: 4174
follows: 0x00000010:1153 0x00000011:1098 0x00000012:996 0x00000100:732 0x00000200:1775
said: 1 | **ACOUSTICWIN** t_ms:36102298 stream:0xa0be1a79 wall:0 window_ms:60000 blocks:3688 rate:8000
said: 2 | **ACOUSTIC** rms_mean:114 rms_max:14794 peak:32768 transients:18
said: 3 | **TRANSIENT** t_ms:36064078 stream:0xa0be1a79 wall:0 rms:14794
```

---

@LAT105LON4577 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 36105463 ±21 frame:20500
seq: 995
follows: 0x00000010:1152 0x00000011:1098 0x00000100:732 0x00000200:1775 0x00000300:4172
said: 1 | **LINKWIN** t_ms:36089294 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:96 rssi_min:-41 rssi_med:-33 rssi_max:-31
said: 3 | **LINK** peer:0x00000011 proto:espnow n:35 rssi_min:-45 rssi_med:-33 rssi_max:-31
said: 4 | **LINK** peer:0x00000200 proto:espnow n:61 rssi_min:-54 rssi_med:-43 rssi_max:-31
said: 5 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-34 rssi_med:-28 rssi_max:-27
said: 6 | **LINK** peer:0x00000010 proto:ble n:43 rssi_min:-82 rssi_med:-45 rssi_max:-41
said: 7 | **LINK** peer:0x00000200 proto:ble n:45 rssi_min:-81 rssi_med:-56 rssi_max:-44
said: 8 | **LINK** peer:0x00000300 proto:ble n:49 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000011 proto:ble n:48 rssi_min:-81 rssi_med:-51 rssi_max:-45
```

---

@LAT105LON4578 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 36111065 ±21 frame:20500
seq: 1153
follows: 0x00000011:1098 0x00000012:996 0x00000100:732 0x00000200:1775 0x00000300:4172
said: 1 | **LINKWIN** t_ms:36094876 stream:0xa0be1a79 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-80 rssi_med:-58 rssi_max:-39
said: 3 | **LINK** peer:0x00000011 proto:espnow n:64 rssi_min:-49 rssi_med:-42 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-60 rssi_med:-51 rssi_max:-29
said: 5 | **LINK** peer:0x00000300 proto:espnow n:144 rssi_min:-57 rssi_med:-40 rssi_max:-35
said: 6 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-60 rssi_med:-52 rssi_max:-49
said: 7 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-81 rssi_med:-57 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:ble n:46 rssi_min:-51 rssi_med:-46 rssi_max:-38
said: 9 | **LINK** peer:0x00000012 proto:espnow n:54 rssi_min:-41 rssi_med:-30 rssi_max:-29
```
@LAT106LON156 | created:0 | updated:0

**BAR** frame:20500 bar:60 own:10 held:40 terms:8 digest:0xdf43adec settled_ms:120000
**HOLDS** agent:0x00000010 n:10 lo:1141 hi:1151 sum:11459
**HOLDS** agent:0x00000011 n:10 lo:1086 hi:1096 sum:10911
**HOLDS** agent:0x00000012 n:10 lo:984 hi:994 sum:9889
**HOLDS** agent:0x00000200 n:10 lo:1765 hi:1774 sum:17695
**HOLDS** agent:0x00000300 n:10 lo:4149 hi:4168 sum:41589
