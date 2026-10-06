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

@LAT103LON16505 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 36259598 ±214767 frame:20500
seq: 4176
follows: 0x00000010:1153 0x00000011:1098 0x00000012:996 0x00000100:732 0x00000200:1775
said: 1 | **MOTIONWIN** t_ms:36244246 stream:0xa0be1a79 wall:0 window_ms:70177 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8384 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 36327483 ±0 frame:20500
seq: 4179
follows: 0x00000010:1155 0x00000011:1100 0x00000012:998 0x00000100:732 0x00000200:1778
said: 1 | **ENTWIN** t_ms:36313188 stream:0xa0be1a79 wall:0 window_ms:138062 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-65
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8385 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 37484585 ±0 frame:20500
seq: 4212
follows: 0x00000010:1177 0x00000011:1122 0x00000012:1019 0x00000100:732 0x00000200:1799
said: 1 | **ENTWIN** t_ms:37468391 stream:0xa0be1a79 wall:0 window_ms:64778 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 6 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON16506 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 37484585 ±0 frame:20500
seq: 4213
follows: 0x00000010:1177 0x00000011:1122 0x00000012:1019 0x00000100:732 0x00000200:1799
said: 1 | **MOTIONWIN** t_ms:37468391 stream:0xa0be1a79 wall:0 window_ms:64778 n:300
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:17 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8386 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 634327 ±0 frame:10000
seq: 4216
follows: 0x00000010:1185 0x00000011:1133 0x00000012:1036 0x00000100:742 0x00000200:1830
said: 1 | **ENTWIN** t_ms:950284 stream:0x364dd329 wall:0 window_ms:60000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON16507 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 634327 ±0 frame:10000
seq: 4217
follows: 0x00000010:1185 0x00000011:1133 0x00000012:1036 0x00000100:742 0x00000200:1830
said: 1 | **MOTIONWIN** t_ms:950284 stream:0x364dd329 wall:0 window_ms:60000 n:748
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8387 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 70162 ±0 frame:8000
seq: 4234
follows: 0x00000010:1192 0x00000011:1141 0x00000012:1044 0x00000100:751 0x00000200:1840
said: 1 | **ENTWIN** t_ms:59494 stream:0x732acba3 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON16508 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 70162 ±0 frame:8000
seq: 4235
follows: 0x00000010:1192 0x00000011:1141 0x00000012:1044 0x00000100:751 0x00000200:1840
said: 1 | **MOTIONWIN** t_ms:59494 stream:0x732acba3 wall:0 window_ms:60000 n:773
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:2 dev_max_mg:20 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT106LON160 | created:0 | updated:0

**BAR** frame:8000 bar:1 own:9 held:14 terms:9 digest:0x66684c5a settled_ms:300000
**HOLDS** agent:0x00000010 n:3 lo:1200 hi:1202 sum:3603
**HOLDS** agent:0x00000011 n:4 lo:1148 hi:1151 sum:4598
**HOLDS** agent:0x00000012 n:4 lo:1051 hi:1054 sum:4210
**HOLDS** agent:0x00000200 n:3 lo:1839 hi:1842 sum:5522
**HOLDS** agent:0x00000300 n:9 lo:4233 hi:4251 sum:38185
**DELIVER** up_s:905 heap:10804 fetched:87 unanswered:59 broken:6 resumed:232 empty:15 served:279 wants:339 early:101 wantq_drop:0 superseded:0

---

@LAT103LON8388 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1232299 ±0 frame:8000
seq: 4275
follows: 0x00000010:1212 0x00000011:1161 0x00000012:1064 0x00000100:772 0x00000200:1860
said: 1 | **ENTWIN** t_ms:1221631 stream:0x732acba3 wall:0 window_ms:599999 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-87
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:5 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b
said: 14 | **COVERED** windows:1 entities:8 window_ms:562138 first_t_ms:621632 last_t_ms:621632 covered_by:@LAT103LON8387
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-84 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-88 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
```

---

@LAT106LON161 | created:0 | updated:0

**BAR** frame:8000 bar:2 own:10 held:22 terms:9 digest:0x220c70f5 settled_ms:300000
**HOLDS** agent:0x00000010 n:4 lo:1209 hi:1212 sum:4842
**HOLDS** agent:0x00000011 n:4 lo:1158 hi:1161 sum:4638
**HOLDS** agent:0x00000012 n:4 lo:1061 hi:1064 sum:4250
**HOLDS** agent:0x00000200 n:10 lo:1850 hi:1859 sum:18545
**HOLDS** agent:0x00000300 n:10 lo:4253 hi:4271 sum:42620
**DELIVER** up_s:1503 heap:11056 fetched:137 unanswered:96 broken:13 resumed:358 empty:26 served:449 wants:555 early:127 wantq_drop:1 superseded:0

---

@LAT103LON8389 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1832301 ±0 frame:8000
seq: 4296
follows: 0x00000010:1223 0x00000011:1172 0x00000012:1075 0x00000100:783 0x00000200:1871
said: 1 | **ENTWIN** t_ms:1821633 stream:0x732acba3 wall:0 window_ms:600002 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,5ce28c488e0c,64677217947d,c2e94427adcf,0283cce0e689
```

---

@LAT103LON16509 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 1879876 ±0 frame:8000
seq: 4298
follows: 0x00000010:1225 0x00000011:1174 0x00000012:1077 0x00000100:785 0x00000200:1872
said: 1 | **MOTIONWIN** t_ms:1869208 stream:0x732acba3 wall:0 window_ms:60000 n:991
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:4 dev_max_mg:8 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27438 window_ms:1749714 moving_permille:0 dev_mean_mg:3 dev_max_mg:103 moving_ms:60 first_t_ms:119494 last_t_ms:1809208 covered_by:@LAT103LON16508
```

---

@LAT106LON162 | created:0 | updated:0

**BAR** frame:8000 bar:3 own:10 held:40 terms:9 digest:0xec649483 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1213 hi:1223 sum:12184
**HOLDS** agent:0x00000011 n:10 lo:1162 hi:1172 sum:11674
**HOLDS** agent:0x00000012 n:10 lo:1065 hi:1075 sum:10704
**HOLDS** agent:0x00000200 n:10 lo:1861 hi:1870 sum:18655
**HOLDS** agent:0x00000300 n:10 lo:4273 hi:4292 sum:42829
**DELIVER** up_s:2102 heap:10804 fetched:178 unanswered:111 broken:23 resumed:470 empty:40 served:625 wants:779 early:127 wantq_drop:1 superseded:0

---

@LAT106LON163 | created:0 | updated:0

**BAR** frame:8000 bar:4 own:10 held:40 terms:9 digest:0x161a9dd7 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1224 hi:1234 sum:12294
**HOLDS** agent:0x00000011 n:10 lo:1173 hi:1183 sum:11784
**HOLDS** agent:0x00000012 n:10 lo:1076 hi:1086 sum:10814
**HOLDS** agent:0x00000200 n:10 lo:1872 hi:1881 sum:18765
**HOLDS** agent:0x00000300 n:10 lo:4294 hi:4314 sum:43047
**DELIVER** up_s:2704 heap:14052 fetched:217 unanswered:147 broken:27 resumed:567 empty:51 served:794 wants:981 early:127 wantq_drop:1 superseded:0

---

@LAT106LON164 | created:0 | updated:0

**BAR** frame:8000 bar:5 own:10 held:40 terms:9 digest:0x14f3b7aa settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1235 hi:1245 sum:12404
**HOLDS** agent:0x00000011 n:10 lo:1184 hi:1193 sum:11885
**HOLDS** agent:0x00000012 n:10 lo:1087 hi:1096 sum:10915
**HOLDS** agent:0x00000200 n:10 lo:1882 hi:1891 sum:18865
**HOLDS** agent:0x00000300 n:10 lo:4316 hi:4334 sum:43250
**DELIVER** up_s:3303 heap:11120 fetched:258 unanswered:168 broken:35 resumed:696 empty:63 served:982 wants:1219 early:127 wantq_drop:1 superseded:0

---

@LAT103LON16510 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3685717 ±0 frame:8000
seq: 4359
follows: 0x00000010:1258 0x00000011:1204 0x00000012:1108 0x00000100:818 0x00000200:1902
said: 1 | **MOTIONWIN** t_ms:3675049 stream:0x732acba3 wall:0 window_ms:60000 n:991
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:5 dev_max_mg:19 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27232 window_ms:1745841 moving_permille:0 dev_mean_mg:5 dev_max_mg:14 moving_ms:0 first_t_ms:1929208 last_t_ms:3615049 covered_by:@LAT103LON16509
```

---

@LAT106LON165 | created:0 | updated:0

**BAR** frame:8000 bar:6 own:10 held:40 terms:9 digest:0x604cc9d2 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1246 hi:1256 sum:12514
**HOLDS** agent:0x00000011 n:10 lo:1194 hi:1203 sum:11985
**HOLDS** agent:0x00000012 n:10 lo:1097 hi:1106 sum:11015
**HOLDS** agent:0x00000200 n:10 lo:1892 hi:1901 sum:18965
**HOLDS** agent:0x00000300 n:10 lo:4336 hi:4354 sum:43450
**DELIVER** up_s:3901 heap:14048 fetched:298 unanswered:181 broken:38 resumed:781 empty:76 served:1137 wants:1418 early:127 wantq_drop:1 superseded:0

---

@LAT106LON166 | created:0 | updated:0

**BAR** frame:8000 bar:7 own:10 held:40 terms:9 digest:0x8f8983eb settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1257 hi:1267 sum:12624
**HOLDS** agent:0x00000011 n:10 lo:1204 hi:1213 sum:12085
**HOLDS** agent:0x00000012 n:10 lo:1107 hi:1117 sum:11124
**HOLDS** agent:0x00000200 n:10 lo:1902 hi:1911 sum:19065
**HOLDS** agent:0x00000300 n:10 lo:4356 hi:4375 sum:43658
**DELIVER** up_s:4504 heap:13484 fetched:339 unanswered:202 broken:46 resumed:876 empty:87 served:1307 wants:1636 early:127 wantq_drop:1 superseded:0

---

@LAT103LON8390 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4832302 ±0 frame:8000
seq: 4399
follows: 0x00000010:1278 0x00000011:1223 0x00000012:1128 0x00000100:838 0x00000200:1923
said: 1 | **ENTWIN** t_ms:4821634 stream:0x732acba3 wall:0 window_ms:599883 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:5 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,c2e94427adcf,5ce28c488e0c,0283cce0e689
said: 13 | **COVERED** windows:4 entities:10 window_ms:2400118 first_t_ms:2421634 last_t_ms:4221751 covered_by:@LAT103LON8389
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:4 rssi:-36 windows:4
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:4 rssi:-67 windows:4
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:4 rssi:-70 windows:4
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:4 rssi:-74 windows:4
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:3 rssi:-86 windows:3
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-86 windows:2
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-84 windows:3
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:4 rssi:-93 windows:4
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:3 rssi:-85 windows:3
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-89 windows:2
```

---

@LAT106LON167 | created:0 | updated:0

**BAR** frame:8000 bar:8 own:10 held:40 terms:9 digest:0x6cf5f785 settled_ms:300017
**HOLDS** agent:0x00000010 n:10 lo:1268 hi:1278 sum:12734
**HOLDS** agent:0x00000011 n:10 lo:1214 hi:1223 sum:12185
**HOLDS** agent:0x00000012 n:10 lo:1118 hi:1128 sum:11234
**HOLDS** agent:0x00000200 n:10 lo:1913 hi:1922 sum:19175
**HOLDS** agent:0x00000300 n:10 lo:4377 hi:4395 sum:43860
**DELIVER** up_s:5101 heap:14300 fetched:378 unanswered:215 broken:53 resumed:977 empty:97 served:1469 wants:1849 early:127 wantq_drop:1 superseded:0

---

@LAT103LON16511 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5486124 ±0 frame:8000
seq: 4421
follows: 0x00000010:1291 0x00000011:1235 0x00000012:1141 0x00000100:851 0x00000200:1934
said: 1 | **MOTIONWIN** t_ms:5475456 stream:0x732acba3 wall:0 window_ms:60000 n:975
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:6 dev_max_mg:18 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26065 window_ms:1740407 moving_permille:0 dev_mean_mg:5 dev_max_mg:69 moving_ms:121 first_t_ms:3735049 last_t_ms:5415456 covered_by:@LAT103LON16510
```

---

@LAT106LON168 | created:0 | updated:0

**BAR** frame:8000 bar:9 own:10 held:40 terms:9 digest:0x30d90ae0 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1279 hi:1289 sum:12844
**HOLDS** agent:0x00000011 n:10 lo:1224 hi:1233 sum:12285
**HOLDS** agent:0x00000012 n:10 lo:1129 hi:1139 sum:11344
**HOLDS** agent:0x00000200 n:10 lo:1924 hi:1933 sum:19285
**HOLDS** agent:0x00000300 n:10 lo:4397 hi:4416 sum:44069
**DELIVER** up_s:5707 heap:10556 fetched:417 unanswered:240 broken:64 resumed:1095 empty:110 served:1634 wants:2049 early:127 wantq_drop:1 superseded:0

---

@LAT106LON169 | created:0 | updated:0

**BAR** frame:8000 bar:10 own:10 held:40 terms:9 digest:0x40588064 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1290 hi:1300 sum:12954
**HOLDS** agent:0x00000011 n:10 lo:1234 hi:1244 sum:12394
**HOLDS** agent:0x00000012 n:10 lo:1140 hi:1150 sum:11454
**HOLDS** agent:0x00000200 n:10 lo:1934 hi:1943 sum:19385
**HOLDS** agent:0x00000300 n:10 lo:4418 hi:4437 sum:44278
**DELIVER** up_s:6301 heap:10776 fetched:458 unanswered:256 broken:72 resumed:1197 empty:120 served:1803 wants:2260 early:127 wantq_drop:1 superseded:2

---

@LAT106LON170 | created:0 | updated:0

**BAR** frame:8000 bar:11 own:10 held:40 terms:9 digest:0xa1cf7219 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1301 hi:1311 sum:13064
**HOLDS** agent:0x00000011 n:10 lo:1245 hi:1255 sum:12504
**HOLDS** agent:0x00000012 n:10 lo:1151 hi:1161 sum:11564
**HOLDS** agent:0x00000200 n:10 lo:1944 hi:1953 sum:19485
**HOLDS** agent:0x00000300 n:10 lo:4439 hi:4457 sum:44480
**DELIVER** up_s:6906 heap:10812 fetched:497 unanswered:274 broken:79 resumed:1354 empty:130 served:1990 wants:2494 early:127 wantq_drop:1 superseded:2

---

@LAT103LON8391 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7232327 ±0 frame:8000
seq: 4481
follows: 0x00000010:1322 0x00000011:1265 0x00000012:1171 0x00000100:883 0x00000200:1963
said: 1 | **ENTWIN** t_ms:7221659 stream:0x732acba3 wall:0 window_ms:600010 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-87
said: 10 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 12 | **RUN** windows_since_last:4 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,84a329c78fec,e6b32d2cea8b,c2e94427adcf,0283cce0e689,5ce28c488e0c
said: 14 | **COVERED** windows:3 entities:10 window_ms:1800015 first_t_ms:5421635 last_t_ms:6621649 covered_by:@LAT103LON8390
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:3 rssi:-34 windows:3
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:3 rssi:-65 windows:3
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:3 rssi:-73 windows:3
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:3 rssi:-70 windows:3
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:3 rssi:-84 windows:3
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:2 rssi:-84 windows:2
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:2 rssi:-86 windows:2
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:2 rssi:-86 windows:2
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:2 rssi:-90 windows:2
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:2 rssi:-94 windows:2
```

---

@LAT103LON16512 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 7289743 ±0 frame:8000
seq: 4483
follows: 0x00000010:1323 0x00000011:1267 0x00000012:1174 0x00000100:885 0x00000200:1964
said: 1 | **MOTIONWIN** t_ms:7279075 stream:0x732acba3 wall:0 window_ms:60000 n:977
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:6 dev_max_mg:10 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26771 window_ms:1743619 moving_permille:0 dev_mean_mg:6 dev_max_mg:33 moving_ms:0 first_t_ms:5535456 last_t_ms:7219075 covered_by:@LAT103LON16511
```

---

@LAT106LON171 | created:0 | updated:0

**BAR** frame:8000 bar:12 own:10 held:40 terms:9 digest:0x9c7c5137 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1312 hi:1322 sum:13174
**HOLDS** agent:0x00000011 n:10 lo:1256 hi:1265 sum:12605
**HOLDS** agent:0x00000012 n:10 lo:1162 hi:1171 sum:11665
**HOLDS** agent:0x00000200 n:10 lo:1954 hi:1963 sum:19585
**HOLDS** agent:0x00000300 n:10 lo:4459 hi:4477 sum:44680
**DELIVER** up_s:7503 heap:14020 fetched:537 unanswered:287 broken:91 resumed:1503 empty:142 served:2159 wants:2701 early:127 wantq_drop:1 superseded:2

---

@LAT103LON8392 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7832330 ±0 frame:8000
seq: 4503
follows: 0x00000010:1332 0x00000011:1275 0x00000012:1182 0x00000100:895 0x00000200:1974
said: 1 | **ENTWIN** t_ms:7821662 stream:0x732acba3 wall:0 window_ms:600003 entities:4
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 6 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 7 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,84a329c78fec,e6b32d2cea8b,c2e94427adcf,0283cce0e689
```

---

@LAT106LON172 | created:0 | updated:0

**BAR** frame:8000 bar:13 own:10 held:40 terms:9 digest:0x45949f72 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1323 hi:1332 sum:13275
**HOLDS** agent:0x00000011 n:10 lo:1266 hi:1275 sum:12705
**HOLDS** agent:0x00000012 n:10 lo:1172 hi:1182 sum:11774
**HOLDS** agent:0x00000200 n:10 lo:1964 hi:1973 sum:19685
**HOLDS** agent:0x00000300 n:10 lo:4479 hi:4499 sum:44897
**DELIVER** up_s:8102 heap:14588 fetched:579 unanswered:307 broken:101 resumed:1680 empty:152 served:2364 wants:2935 early:127 wantq_drop:1 superseded:2

---

@LAT103LON8393 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8432333 ±0 frame:8000
seq: 4524
follows: 0x00000010:1342 0x00000011:1285 0x00000012:1193 0x00000100:906 0x00000200:1984
said: 1 | **ENTWIN** t_ms:8421665 stream:0x732acba3 wall:0 window_ms:600003 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:e45e1b9f675a n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,5ce28c488e0c,e6b32d2cea8b,0283cce0e689,84a329c78fec,c2e94427adcf
```

---

@LAT103LON2970 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8609771 ±0 frame:8000
seq: 4529
follows: 0x00000010:1346 0x00000011:1289 0x00000012:1198 0x00000100:910 0x00000200:1987
said: 1 | **LINKWIN** t_ms:8599103 stream:0x732acba3 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 3 | **LINK** peer:0x00000200 proto:espnow n:124 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-71 rssi_med:-66 rssi_max:-64
said: 5 | **LINK** peer:0x00000011 proto:espnow n:53 rssi_min:-33 rssi_med:-33 rssi_max:-30
said: 6 | **LINK** peer:0x00000010 proto:espnow n:99 rssi_min:-32 rssi_med:-30 rssi_max:-28
said: 7 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-54 rssi_max:-49
said: 8 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 9 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 10 | 0x00000100 espnow met predicted:-40 observed:-40
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-66 observed:-66
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000012 ble met predicted:-44 observed:-44
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000011 ble met predicted:-54 observed:-54
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON2971 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8669783 ±0 frame:8000
seq: 4531
follows: 0x00000010:1347 0x00000011:1290 0x00000012:1199 0x00000100:911 0x00000200:1988
said: 1 | **LINKWIN** t_ms:8659115 stream:0x732acba3 wall:0 window_ms:60012
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000200 proto:espnow n:140 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000012 proto:espnow n:118 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 5 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-71 rssi_med:-66 rssi_max:-65
said: 6 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-44 rssi_max:-43
said: 7 | **LINK** peer:0x00000010 proto:espnow n:134 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 8 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-56 rssi_med:-54 rssi_max:-49
said: 9 | **LINK** peer:0x00000011 proto:espnow n:143 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 10 | 0x00000100 espnow met predicted:-40 observed:-40
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-66 observed:-66
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-54 observed:-54
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-44 observed:-44
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT106LON173 | created:0 | updated:0

**BAR** frame:8000 bar:14 own:10 held:40 terms:9 digest:0x4b93e0ea settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1333 hi:1342 sum:13375
**HOLDS** agent:0x00000011 n:10 lo:1276 hi:1285 sum:12805
**HOLDS** agent:0x00000012 n:10 lo:1183 hi:1193 sum:11884
**HOLDS** agent:0x00000200 n:10 lo:1975 hi:1984 sum:19795
**HOLDS** agent:0x00000300 n:10 lo:4501 hi:4520 sum:45109
**DELIVER** up_s:8701 heap:11060 fetched:618 unanswered:333 broken:108 resumed:1798 empty:164 served:2547 wants:3157 early:127 wantq_drop:1 superseded:2

---

@LAT103LON2972 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8729797 ±0 frame:8000
seq: 4533
follows: 0x00000010:1348 0x00000011:1291 0x00000012:1200 0x00000100:912 0x00000200:1989
said: 1 | **LINKWIN** t_ms:8719129 stream:0x732acba3 wall:0 window_ms:60014
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-42 rssi_med:-40 rssi_max:-40
said: 3 | **LINK** peer:0x00000011 proto:ble n:68 rssi_min:-81 rssi_med:-54 rssi_max:-49
said: 4 | **LINK** peer:0x00000011 proto:espnow n:52 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 5 | **LINK** peer:0x00000200 proto:espnow n:82 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 6 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:espnow n:67 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 9 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-71 rssi_med:-66 rssi_max:-65
said: 10 | 0x00000100 espnow met predicted:-40 observed:-40
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-66 observed:-66
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000012 ble unobserved predicted:-44 observed:-44
percept: 14 | 0x00000012 | link_stable | ble | ? | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-54 observed:-54
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON2973 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8789797 ±0 frame:8000
seq: 4535
follows: 0x00000010:1349 0x00000011:1292 0x00000012:1201 0x00000100:913 0x00000200:1990
said: 1 | **LINKWIN** t_ms:8779129 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-54 rssi_max:-48
said: 3 | **LINK** peer:0x00000200 proto:espnow n:124 rssi_min:-51 rssi_med:-48 rssi_max:-45
said: 4 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-77 rssi_med:-66 rssi_max:-60
said: 5 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-80 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-43 rssi_med:-39 rssi_max:-36
said: 7 | **LINK** peer:0x00000010 proto:espnow n:79 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 8 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 9 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 10 | 0x00000100 espnow met predicted:-40 observed:-39
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000011 ble met predicted:-54 observed:-54
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000011 espnow unobserved predicted:-33 observed:-33
percept: 12 | 0x00000011 | link_stable | espnow | ? | -
said: 13 | 0x00000200 espnow met predicted:-49 observed:-48
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-49 observed:-49
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-66 observed:-66
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON2974 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8849797 ±0 frame:8000
seq: 4537
follows: 0x00000010:1350 0x00000011:1293 0x00000012:1202 0x00000100:914 0x00000200:1991
said: 1 | **LINKWIN** t_ms:8839129 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:espnow n:95 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-56 rssi_med:-53 rssi_max:-49
said: 5 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 6 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-44 rssi_max:-43
said: 7 | **LINK** peer:0x00000011 proto:espnow n:93 rssi_min:-35 rssi_med:-33 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:espnow n:101 rssi_min:-29 rssi_med:-27 rssi_max:-24
said: 9 | **LINK** peer:0x00000200 proto:ble n:54 rssi_min:-80 rssi_med:-67 rssi_max:-64
said: 10 | 0x00000011 ble met predicted:-54 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-66 observed:-67
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000012 ble met predicted:-44 observed:-44
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-39 observed:-39
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow unobserved predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | ? | -
said: 16 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000010 ble met predicted:-49 observed:-49
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON2975 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8909797 ±0 frame:8000
seq: 4539
follows: 0x00000010:1351 0x00000011:1294 0x00000012:1202 0x00000100:915 0x00000200:1992
said: 1 | **LINKWIN** t_ms:8899129 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 3 | **LINK** peer:0x00000011 proto:espnow n:133 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 4 | **LINK** peer:0x00000200 proto:espnow n:132 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 5 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-80 rssi_med:-54 rssi_max:-49
said: 6 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-44 rssi_max:-43
said: 7 | **LINK** peer:0x00000010 proto:espnow n:71 rssi_min:-31 rssi_med:-30 rssi_max:-30
said: 8 | **LINK** peer:0x00000012 proto:espnow n:86 rssi_min:-29 rssi_med:-27 rssi_max:-26
said: 9 | **LINK** peer:0x00000200 proto:ble n:48 rssi_min:-81 rssi_med:-66 rssi_max:-63
said: 10 | 0x00000100 espnow met predicted:-39 observed:-39
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000011 ble met predicted:-53 observed:-54
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000010 ble unobserved predicted:-49 observed:-49
percept: 13 | 0x00000010 | link_stable | ble | ? | -
said: 14 | 0x00000012 ble met predicted:-44 observed:-44
percept: 14 | 0x00000012 | link_stable | ble | + | -
said: 15 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-67 observed:-66
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON2976 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 8969797 ±0 frame:8000
seq: 4541
follows: 0x00000010:1352 0x00000011:1295 0x00000012:1204 0x00000100:916 0x00000200:1993
said: 1 | **LINKWIN** t_ms:8959129 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:104 rssi_min:-49 rssi_med:-48 rssi_max:-45
said: 3 | **LINK** peer:0x00000012 proto:espnow n:114 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 4 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-33 rssi_med:-30 rssi_max:-29
said: 5 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 6 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 10 | 0x00000100 espnow met predicted:-39 observed:-39
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 ble met predicted:-54 observed:-53
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000012 ble met predicted:-44 observed:-44
percept: 14 | 0x00000012 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble unobserved predicted:-66 observed:-66
percept: 17 | 0x00000200 | link_stable | ble | ? | -
```

---

@LAT103LON2977 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9029798 ±0 frame:8000
seq: 4543
follows: 0x00000010:1353 0x00000011:1295 0x00000012:1204 0x00000100:917 0x00000200:1994
said: 1 | **LINKWIN** t_ms:9019130 stream:0x732acba3 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-56 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:espnow n:73 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 5 | **LINK** peer:0x00000011 proto:espnow n:122 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 6 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-83 rssi_med:-66 rssi_max:-62
said: 7 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000012 proto:espnow n:69 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 9 | **LINK** peer:0x00000010 proto:espnow n:72 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 10 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-39 observed:-39
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-44 observed:-44
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-53 observed:-53
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000010 ble unobserved predicted:-49 observed:-49
percept: 17 | 0x00000010 | link_stable | ble | ? | -
```

---

@LAT103LON2978 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9089798 ±0 frame:8000
seq: 4545
follows: 0x00000010:1355 0x00000011:1298 0x00000012:1207 0x00000100:918 0x00000200:1995
said: 1 | **LINKWIN** t_ms:9079130 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:68 rssi_min:-56 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-80 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-66 rssi_max:-63
said: 5 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000200 proto:espnow n:100 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 7 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-32 rssi_med:-30 rssi_max:-26
said: 8 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 9 | **LINK** peer:0x00000011 proto:espnow n:73 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 10 | 0x00000011 ble met predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-39 observed:-38
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-66 observed:-66
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-44 observed:-44
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow unobserved predicted:-27 observed:-27
percept: 16 | 0x00000012 | link_stable | espnow | ? | -
said: 17 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON16513 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 9089798 ±0 frame:8000
seq: 4546
follows: 0x00000010:1355 0x00000011:1298 0x00000012:1207 0x00000100:918 0x00000200:1995
said: 1 | **MOTIONWIN** t_ms:9079130 stream:0x732acba3 wall:0 window_ms:60000 n:971
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26796 window_ms:1740055 moving_permille:0 dev_mean_mg:7 dev_max_mg:15 moving_ms:0 first_t_ms:7339075 last_t_ms:9019130 covered_by:@LAT103LON16512
```

---

@LAT103LON2979 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9149798 ±0 frame:8000
seq: 4548
follows: 0x00000010:1356 0x00000011:1299 0x00000012:1208 0x00000100:920 0x00000200:1996
said: 1 | **LINKWIN** t_ms:9139130 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:51 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 3 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 4 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-28 rssi_med:-27 rssi_max:-25
said: 5 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000200 proto:espnow n:149 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 7 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 8 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-48
said: 9 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-33 rssi_med:-30 rssi_max:-30
said: 10 | 0x00000011 ble met predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-49 observed:-49
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 ble unobserved predicted:-66 observed:-66
percept: 12 | 0x00000200 | link_stable | ble | ? | -
said: 13 | 0x00000012 ble met predicted:-44 observed:-44
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000100 espnow met predicted:-38 observed:-39
percept: 16 | 0x00000100 | link_stable | espnow | + | -
said: 17 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON2980 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9209798 ±0 frame:8000
seq: 4550
follows: 0x00000010:1357 0x00000011:1300 0x00000012:1209 0x00000100:921 0x00000200:1997
said: 1 | **LINKWIN** t_ms:9199130 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-79 rssi_med:-66 rssi_max:-63
said: 3 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:espnow n:84 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:115 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 6 | **LINK** peer:0x00000012 proto:espnow n:95 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 7 | **LINK** peer:0x00000011 proto:espnow n:98 rssi_min:-35 rssi_med:-33 rssi_max:-32
said: 8 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-79 rssi_med:-54 rssi_max:-49
said: 9 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 10 | 0x00000010 ble unobserved predicted:-49 observed:-49
percept: 10 | 0x00000010 | link_stable | ble | ? | -
said: 11 | 0x00000100 espnow met predicted:-39 observed:-39
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-44 observed:-44
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-53 observed:-54
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON2981 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9269798 ±0 frame:8000
seq: 4552
follows: 0x00000010:1358 0x00000011:1301 0x00000012:1210 0x00000100:922 0x00000200:1998
said: 1 | **LINKWIN** t_ms:9259130 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-80 rssi_med:-66 rssi_max:-63
said: 3 | **LINK** peer:0x00000011 proto:espnow n:162 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 4 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:espnow n:132 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 7 | **LINK** peer:0x00000010 proto:espnow n:94 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 8 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 10 | 0x00000200 ble met predicted:-66 observed:-66
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-39 observed:-39
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow unobserved predicted:-27 observed:-27
percept: 14 | 0x00000012 | link_stable | espnow | ? | -
said: 15 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-54 observed:-53
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-44 observed:-44
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT106LON174 | created:0 | updated:0

**BAR** frame:8000 bar:15 own:10 held:40 terms:9 digest:0x033334fc settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1343 hi:1353 sum:13484
**HOLDS** agent:0x00000011 n:10 lo:1286 hi:1295 sum:12905
**HOLDS** agent:0x00000012 n:10 lo:1194 hi:1204 sum:11994
**HOLDS** agent:0x00000200 n:10 lo:1985 hi:1994 sum:19895
**HOLDS** agent:0x00000300 n:10 lo:4522 hi:4541 sum:45319
**DELIVER** up_s:9305 heap:11324 fetched:657 unanswered:351 broken:116 resumed:1930 empty:176 served:2701 wants:3350 early:127 wantq_drop:1 superseded:2

---

@LAT103LON2982 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9329798 ±0 frame:8000
seq: 4554
follows: 0x00000010:1359 0x00000011:1302 0x00000012:1210 0x00000100:923 0x00000200:1999
said: 1 | **LINKWIN** t_ms:9319130 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:85 rssi_min:-31 rssi_med:-30 rssi_max:-30
said: 3 | **LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:espnow n:64 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 5 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 6 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-35 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-80 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-83 rssi_med:-65 rssi_max:-63
said: 10 | 0x00000200 ble met predicted:-66 observed:-65
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-39 observed:-39
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000010 ble met predicted:-49 observed:-49
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble unobserved predicted:-53 observed:-53
percept: 16 | 0x00000011 | link_stable | ble | ? | -
said: 17 | 0x00000012 ble met predicted:-44 observed:-44
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON2983 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9389798 ±0 frame:8000
seq: 4556
follows: 0x00000010:1360 0x00000011:1303 0x00000012:1212 0x00000100:924 0x00000200:2000
said: 1 | **LINKWIN** t_ms:9379130 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:93 rssi_min:-34 rssi_med:-33 rssi_max:-28
said: 3 | **LINK** peer:0x00000011 proto:ble n:71 rssi_min:-79 rssi_med:-53 rssi_max:-48
said: 4 | **LINK** peer:0x00000200 proto:espnow n:132 rssi_min:-52 rssi_med:-48 rssi_max:-46
said: 5 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-77 rssi_med:-65 rssi_max:-60
said: 7 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-43 rssi_med:-38 rssi_max:-38
said: 8 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 10 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 10 | 0x00000010 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-39 observed:-38
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow unobserved predicted:-27 observed:-27
percept: 13 | 0x00000012 | link_stable | espnow | ? | -
said: 14 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-44 observed:-44
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-49 observed:-49
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-65 observed:-65
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON2984 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9449798 ±0 frame:8000
seq: 4558
follows: 0x00000010:1361 0x00000011:1304 0x00000012:1213 0x00000100:925 0x00000200:2001
said: 1 | **LINKWIN** t_ms:9439130 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-30 rssi_med:-28 rssi_max:-26
said: 3 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-41 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000200 proto:espnow n:77 rssi_min:-57 rssi_med:-47 rssi_max:-43
said: 5 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-79 rssi_med:-53 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:espnow n:112 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 8 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-71 rssi_med:-60 rssi_max:-57
said: 9 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-35 rssi_med:-33 rssi_max:-30
said: 10 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000011 ble met predicted:-53 observed:-53
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-48 observed:-47
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble unobserved predicted:-44 observed:-44
percept: 13 | 0x00000012 | link_stable | ble | ? | -
said: 14 | 0x00000200 ble met predicted:-65 observed:-60
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000100 espnow met predicted:-38 observed:-37
percept: 15 | 0x00000100 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-49 observed:-49
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:1236 last_ms:9465292
t_ms:9465612 stream:0x732acba3 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:579 last_ms:9463328
t_ms:9465612 stream:0x732acba3 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:615 last_ms:9465737
t_ms:9465612 stream:0x732acba3 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:584 last_ms:9465787
t_ms:9465612 stream:0x732acba3 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:617 last_ms:9464852
t_ms:9465612 stream:0x732acba3 wall:0

---

@LAT101LON5 | sid:499db878 | created:0 | updated:0 |
**PEER** node:0x00000001 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:9465612 stream:0x732acba3 wall:0

---

@LAT103LON2985 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9509804 ±0 frame:8000
seq: 4560
follows: 0x00000010:1362 0x00000011:1305 0x00000012:1214 0x00000100:926 0x00000200:2002
said: 1 | **LINKWIN** t_ms:9499136 stream:0x732acba3 wall:0 window_ms:60006
said: 2 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-82 rssi_med:-44 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-83 rssi_med:-65 rssi_max:-60
said: 4 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-40 rssi_med:-38 rssi_max:-36
said: 5 | **LINK** peer:0x00000011 proto:espnow n:89 rssi_min:-38 rssi_med:-33 rssi_max:-32
said: 6 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:espnow n:146 rssi_min:-33 rssi_med:-30 rssi_max:-28
said: 8 | **LINK** peer:0x00000012 proto:espnow n:141 rssi_min:-33 rssi_med:-27 rssi_max:-26
said: 9 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-56 rssi_med:-53 rssi_max:-48
said: 10 | 0x00000012 espnow met predicted:-28 observed:-27
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-37 observed:-38
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow unobserved predicted:-47 observed:-47
percept: 12 | 0x00000200 | link_stable | espnow | ? | -
said: 13 | 0x00000011 ble met predicted:-53 observed:-53
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-49 observed:-49
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-60 observed:-65
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON2986 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9569804 ±0 frame:8000
seq: 4562
follows: 0x00000010:1363 0x00000011:1306 0x00000012:1215 0x00000100:927 0x00000200:2003
said: 1 | **LINKWIN** t_ms:9559136 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:128 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 3 | **LINK** peer:0x00000200 proto:espnow n:135 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 5 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-66 rssi_med:-65 rssi_max:-64
said: 8 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-56 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 10 | 0x00000012 ble met predicted:-44 observed:-44
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-65 observed:-65
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 ble unobserved predicted:-49 observed:-49
percept: 14 | 0x00000010 | link_stable | ble | ? | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 16 | 0x00000012 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-53 observed:-53
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON2987 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9629804 ±0 frame:8000
seq: 4564
follows: 0x00000010:1364 0x00000011:1306 0x00000012:1215 0x00000100:928 0x00000200:2004
said: 1 | **LINKWIN** t_ms:9619136 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 3 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-78 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:espnow n:71 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000011 proto:espnow n:53 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 7 | **LINK** peer:0x00000010 proto:espnow n:120 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 8 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-66 rssi_med:-65 rssi_max:-64
said: 9 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-49 rssi_max:-48
said: 10 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-33 observed:-32
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-65 observed:-65
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000011 ble unobserved predicted:-53 observed:-53
percept: 16 | 0x00000011 | link_stable | ble | ? | -
said: 17 | 0x00000012 ble met predicted:-44 observed:-44
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON2988 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9689804 ±0 frame:8000
seq: 4566
follows: 0x00000010:1365 0x00000011:1308 0x00000012:1218 0x00000100:929 0x00000200:2005
said: 1 | **LINKWIN** t_ms:9679136 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-79 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 5 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 6 | **LINK** peer:0x00000200 proto:espnow n:127 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-80 rssi_med:-65 rssi_max:-64
said: 8 | **LINK** peer:0x00000010 proto:espnow n:79 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 9 | **LINK** peer:0x00000012 proto:espnow n:133 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 10 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000012 ble met predicted:-44 observed:-44
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow unobserved predicted:-32 observed:-32
percept: 14 | 0x00000011 | link_stable | espnow | ? | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-65 observed:-65
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-49 observed:-49
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON2989 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9749804 ±0 frame:8000
seq: 4568
follows: 0x00000010:1366 0x00000011:1309 0x00000012:1219 0x00000100:930 0x00000200:2006
said: 1 | **LINKWIN** t_ms:9739136 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 3 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000200 proto:espnow n:68 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 5 | **LINK** peer:0x00000010 proto:espnow n:129 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 6 | **LINK** peer:0x00000011 proto:espnow n:81 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 7 | **LINK** peer:0x00000012 proto:espnow n:105 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 8 | **LINK** peer:0x00000200 proto:ble n:50 rssi_min:-66 rssi_med:-65 rssi_max:-63
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 10 | 0x00000011 ble met predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000012 ble unobserved predicted:-44 observed:-44
percept: 11 | 0x00000012 | link_stable | ble | ? | -
said: 12 | 0x00000010 ble met predicted:-49 observed:-49
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-65 observed:-65
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON2990 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9809804 ±0 frame:8000
seq: 4570
follows: 0x00000010:1367 0x00000011:1310 0x00000012:1220 0x00000100:931 0x00000200:2007
said: 1 | **LINKWIN** t_ms:9799136 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-56 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-66 rssi_med:-65 rssi_max:-63
said: 4 | **LINK** peer:0x00000200 proto:espnow n:152 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 5 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | **LINK** peer:0x00000011 proto:espnow n:87 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 7 | **LINK** peer:0x00000012 proto:espnow n:100 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 8 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-83 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000010 proto:espnow n:136 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 10 | 0x00000010 ble met predicted:-49 observed:-49
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-32 observed:-32
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-65 observed:-65
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-53 observed:-53
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON27357 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9809804 ±0 frame:8000
seq: 4571
follows: 0x00000010:1367 0x00000011:1310 0x00000012:1220 0x00000100:931 0x00000200:2007
said: 1 | **ACOUSTICWIN** t_ms:9799136 stream:0x732acba3 wall:0 window_ms:60000 blocks:3345 rate:8000
said: 2 | **ACOUSTIC** rms_mean:97 rms_max:457 peak:783 transients:0
```

---

@LAT103LON2991 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9869817 ±0 frame:8000
seq: 4572
follows: 0x00000010:1368 0x00000011:1311 0x00000012:1221 0x00000100:932 0x00000200:2008
said: 1 | **LINKWIN** t_ms:9859149 stream:0x732acba3 wall:0 window_ms:60013
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-66 rssi_med:-65 rssi_max:-64
said: 3 | **LINK** peer:0x00000012 proto:espnow n:100 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 4 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 5 | **LINK** peer:0x00000010 proto:espnow n:94 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 6 | **LINK** peer:0x00000200 proto:espnow n:107 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 10 | 0x00000011 ble unobserved predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | ? | -
said: 11 | 0x00000200 ble met predicted:-65 observed:-65
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-32 observed:-32
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-49 observed:-49
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON27358 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9869817 ±0 frame:8000
seq: 4573
follows: 0x00000010:1368 0x00000011:1311 0x00000012:1221 0x00000100:932 0x00000200:2008
said: 1 | **ACOUSTICWIN** t_ms:9859149 stream:0x732acba3 wall:0 window_ms:60013 blocks:3361 rate:8000
said: 2 | **ACOUSTIC** rms_mean:89 rms_max:958 peak:1844 transients:1
said: 3 | **TRANSIENT** t_ms:9802874 stream:0x732acba3 wall:0 rms:958
```

---

@LAT106LON175 | created:0 | updated:0

**BAR** frame:8000 bar:16 own:10 held:40 terms:9 digest:0x8fff28fa settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1354 hi:1364 sum:13594
**HOLDS** agent:0x00000011 n:10 lo:1296 hi:1306 sum:13014
**HOLDS** agent:0x00000012 n:10 lo:1205 hi:1215 sum:12104
**HOLDS** agent:0x00000200 n:10 lo:1995 hi:2004 sum:19995
**HOLDS** agent:0x00000300 n:10 lo:4543 hi:4562 sum:45528
**DELIVER** up_s:9901 heap:11612 fetched:697 unanswered:370 broken:124 resumed:2059 empty:186 served:2879 wants:3564 early:127 wantq_drop:1 superseded:2

---

@LAT103LON2992 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9929817 ±0 frame:8000
seq: 4574
follows: 0x00000010:1369 0x00000011:1312 0x00000012:1222 0x00000100:933 0x00000200:2009
said: 1 | **LINKWIN** t_ms:9919149 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 3 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-66 rssi_med:-65 rssi_max:-64
said: 4 | **LINK** peer:0x00000010 proto:espnow n:65 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:espnow n:75 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 6 | **LINK** peer:0x00000200 proto:espnow n:57 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000012 proto:espnow n:82 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 8 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-56 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 10 | 0x00000200 ble met predicted:-65 observed:-65
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-32 observed:-33
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-49 observed:-49
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 16 | 0x00000100 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble unobserved predicted:-44 observed:-44
percept: 17 | 0x00000012 | link_stable | ble | ? | -
```

---

@LAT103LON27359 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9929817 ±0 frame:8000
seq: 4575
follows: 0x00000010:1369 0x00000011:1312 0x00000012:1222 0x00000100:933 0x00000200:2009
said: 1 | **ACOUSTICWIN** t_ms:9919149 stream:0x732acba3 wall:0 window_ms:60000 blocks:2190 rate:8000
said: 2 | **ACOUSTIC** rms_mean:81 rms_max:237 peak:520 transients:0
```

---

@LAT103LON2993 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 9989817 ±0 frame:8000
seq: 4576
follows: 0x00000010:1370 0x00000011:1313 0x00000012:1223 0x00000100:934 0x00000200:2010
said: 1 | **LINKWIN** t_ms:9979149 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:146 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-49 rssi_max:-48
said: 4 | **LINK** peer:0x00000012 proto:espnow n:147 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 5 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-79 rssi_med:-65 rssi_max:-64
said: 6 | **LINK** peer:0x00000010 proto:espnow n:91 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 7 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000011 proto:espnow n:157 rssi_min:-34 rssi_med:-33 rssi_max:-30
said: 10 | 0x00000100 espnow unobserved predicted:-38 observed:-38
percept: 10 | 0x00000100 | link_stable | espnow | ? | -
said: 11 | 0x00000200 ble met predicted:-65 observed:-65
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-53 observed:-53
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-49 observed:-49
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON27360 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 9989817 ±0 frame:8000
seq: 4577
follows: 0x00000010:1370 0x00000011:1313 0x00000012:1223 0x00000100:934 0x00000200:2010
said: 1 | **ACOUSTICWIN** t_ms:9979149 stream:0x732acba3 wall:0 window_ms:60000 blocks:3329 rate:8000
said: 2 | **ACOUSTIC** rms_mean:80 rms_max:317 peak:687 transients:0
```

---

@LAT103LON2994 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10049817 ±0 frame:8000
seq: 4578
follows: 0x00000010:1371 0x00000011:1314 0x00000012:1224 0x00000100:935 0x00000200:2011
said: 1 | **LINKWIN** t_ms:10039149 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 3 | **LINK** peer:0x00000010 proto:espnow n:95 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 4 | **LINK** peer:0x00000012 proto:espnow n:61 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 5 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 6 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-66 rssi_med:-65 rssi_max:-64
said: 7 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-56 rssi_med:-53 rssi_max:-49
said: 8 | **LINK** peer:0x00000011 proto:espnow n:95 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 9 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 10 | 0x00000200 espnow unobserved predicted:-48 observed:-48
percept: 10 | 0x00000200 | link_stable | espnow | ? | -
said: 11 | 0x00000010 ble met predicted:-49 observed:-49
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-65 observed:-65
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-44 observed:-44
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-53 observed:-53
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow met predicted:-33 observed:-32
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON27361 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10049817 ±0 frame:8000
seq: 4579
follows: 0x00000010:1371 0x00000011:1314 0x00000012:1224 0x00000100:935 0x00000200:2011
said: 1 | **ACOUSTICWIN** t_ms:10039149 stream:0x732acba3 wall:0 window_ms:60000 blocks:3155 rate:8000
said: 2 | **ACOUSTIC** rms_mean:80 rms_max:599 peak:1501 transients:0
```

---

@LAT103LON2995 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10109817 ±0 frame:8000
seq: 4580
follows: 0x00000010:1372 0x00000011:1315 0x00000012:1225 0x00000100:936 0x00000200:2012
said: 1 | **LINKWIN** t_ms:10099149 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-82 rssi_med:-65 rssi_max:-63
said: 3 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000012 proto:espnow n:100 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 5 | **LINK** peer:0x00000011 proto:espnow n:89 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 6 | **LINK** peer:0x00000200 proto:espnow n:115 rssi_min:-51 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:espnow n:80 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 8 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-56 rssi_med:-53 rssi_max:-49
said: 9 | **LINK** peer:0x00000010 proto:ble n:48 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 10 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-49 observed:-49
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000200 ble met predicted:-65 observed:-65
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000011 ble met predicted:-53 observed:-53
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000011 espnow met predicted:-32 observed:-32
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble unobserved predicted:-44 observed:-44
percept: 17 | 0x00000012 | link_stable | ble | ? | -
```

---

@LAT103LON27362 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10109817 ±0 frame:8000
seq: 4581
follows: 0x00000010:1372 0x00000011:1315 0x00000012:1225 0x00000100:936 0x00000200:2012
said: 1 | **ACOUSTICWIN** t_ms:10099149 stream:0x732acba3 wall:0 window_ms:60000 blocks:3379 rate:8000
said: 2 | **ACOUSTIC** rms_mean:96 rms_max:935 peak:1947 transients:1
said: 3 | **TRANSIENT** t_ms:10079009 stream:0x732acba3 wall:0 rms:935
```

---

@LAT103LON2996 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10169817 ±0 frame:8000
seq: 4582
follows: 0x00000010:1373 0x00000011:1316 0x00000012:1226 0x00000100:937 0x00000200:2013
said: 1 | **LINKWIN** t_ms:10159149 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-82 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 4 | **LINK** peer:0x00000012 proto:espnow n:70 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 5 | **LINK** peer:0x00000200 proto:espnow n:102 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 7 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 8 | **LINK** peer:0x00000011 proto:espnow n:145 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-65 rssi_max:-63
said: 10 | 0x00000200 ble met predicted:-65 observed:-65
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-32 observed:-32
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-53 observed:-53
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-49 observed:-49
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON27363 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10169817 ±0 frame:8000
seq: 4583
follows: 0x00000010:1373 0x00000011:1316 0x00000012:1226 0x00000100:937 0x00000200:2013
said: 1 | **ACOUSTICWIN** t_ms:10159149 stream:0x732acba3 wall:0 window_ms:60000 blocks:3268 rate:8000
said: 2 | **ACOUSTIC** rms_mean:155 rms_max:1927 peak:5360 transients:10
said: 3 | **TRANSIENT** t_ms:10150345 stream:0x732acba3 wall:0 rms:1927
```

---

@LAT103LON2997 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10229817 ±0 frame:8000
seq: 4584
follows: 0x00000010:1374 0x00000011:1316 0x00000012:1226 0x00000100:938 0x00000200:2014
said: 1 | **LINKWIN** t_ms:10219149 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:125 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-39 rssi_med:-38 rssi_max:-37
said: 4 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-67 rssi_med:-65 rssi_max:-62
said: 5 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-79 rssi_med:-49 rssi_max:-47
said: 6 | **LINK** peer:0x00000011 proto:espnow n:62 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 7 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-79 rssi_med:-53 rssi_max:-49
said: 8 | **LINK** peer:0x00000012 proto:espnow n:94 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 9 | **LINK** peer:0x00000010 proto:espnow n:80 rssi_min:-32 rssi_med:-30 rssi_max:-28
said: 10 | 0x00000011 ble met predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-49 observed:-49
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000011 espnow met predicted:-32 observed:-32
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-65 observed:-65
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON27364 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10229817 ±0 frame:8000
seq: 4585
follows: 0x00000010:1374 0x00000011:1316 0x00000012:1226 0x00000100:938 0x00000200:2014
said: 1 | **ACOUSTICWIN** t_ms:10219149 stream:0x732acba3 wall:0 window_ms:60000 blocks:3373 rate:8000
said: 2 | **ACOUSTIC** rms_mean:118 rms_max:4250 peak:11205 transients:4
said: 3 | **TRANSIENT** t_ms:10176141 stream:0x732acba3 wall:0 rms:4250
```

---

@LAT103LON2998 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10289817 ±0 frame:8000
seq: 4586
follows: 0x00000010:1375 0x00000011:1318 0x00000012:1229 0x00000100:940 0x00000200:2015
said: 1 | **LINKWIN** t_ms:10279149 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-82 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-66 rssi_med:-65 rssi_max:-64
said: 6 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 7 | **LINK** peer:0x00000011 proto:espnow n:76 rssi_min:-35 rssi_med:-32 rssi_max:-32
said: 8 | **LINK** peer:0x00000200 proto:espnow n:101 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 9 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 10 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-65 observed:-65
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000010 ble met predicted:-49 observed:-49
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-32 observed:-32
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-53 observed:-53
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000012 espnow unobserved predicted:-27 observed:-27
percept: 16 | 0x00000012 | link_stable | espnow | ? | -
said: 17 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON27365 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10289817 ±0 frame:8000
seq: 4587
follows: 0x00000010:1375 0x00000011:1318 0x00000012:1229 0x00000100:940 0x00000200:2015
said: 1 | **ACOUSTICWIN** t_ms:10279149 stream:0x732acba3 wall:0 window_ms:60000 blocks:3375 rate:8000
said: 2 | **ACOUSTIC** rms_mean:89 rms_max:948 peak:1382 transients:0
```

---

@LAT103LON2999 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10349817 ±0 frame:8000
seq: 4588
follows: 0x00000010:1376 0x00000011:1319 0x00000012:1230 0x00000100:941 0x00000200:2016
said: 1 | **LINKWIN** t_ms:10339149 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:68 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000010 proto:espnow n:111 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 4 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-40 rssi_med:-38 rssi_max:-37
said: 5 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-29 rssi_med:-27 rssi_max:-26
said: 6 | **LINK** peer:0x00000011 proto:espnow n:148 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-66 rssi_med:-65 rssi_max:-64
said: 9 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 10 | 0x00000011 ble met predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000010 ble unobserved predicted:-49 observed:-49
percept: 11 | 0x00000010 | link_stable | ble | ? | -
said: 12 | 0x00000012 ble met predicted:-44 observed:-44
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000200 ble met predicted:-65 observed:-65
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-32 observed:-33
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON27366 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10349817 ±0 frame:8000
seq: 4589
follows: 0x00000010:1376 0x00000011:1319 0x00000012:1230 0x00000100:941 0x00000200:2016
said: 1 | **ACOUSTICWIN** t_ms:10339149 stream:0x732acba3 wall:0 window_ms:60000 blocks:3332 rate:8000
said: 2 | **ACOUSTIC** rms_mean:81 rms_max:354 peak:602 transients:0
```

---

@LAT103LON3000 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10409817 ±0 frame:8000
seq: 4590
follows: 0x00000010:1377 0x00000011:1320 0x00000012:1231 0x00000100:942 0x00000200:2017
said: 1 | **LINKWIN** t_ms:10399149 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-83 rssi_med:-64 rssi_max:-64
said: 4 | **LINK** peer:0x00000010 proto:espnow n:108 rssi_min:-32 rssi_med:-30 rssi_max:-28
said: 5 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-56 rssi_med:-53 rssi_max:-49
said: 7 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-79 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 9 | **LINK** peer:0x00000011 proto:espnow n:113 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 10 | 0x00000011 ble met predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow unobserved predicted:-27 observed:-27
percept: 13 | 0x00000012 | link_stable | espnow | ? | -
said: 14 | 0x00000011 espnow met predicted:-33 observed:-32
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-44 observed:-44
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-65 observed:-64
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON27367 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10409817 ±0 frame:8000
seq: 4591
follows: 0x00000010:1377 0x00000011:1320 0x00000012:1231 0x00000100:942 0x00000200:2017
said: 1 | **ACOUSTICWIN** t_ms:10399149 stream:0x732acba3 wall:0 window_ms:60000 blocks:3332 rate:8000
said: 2 | **ACOUSTIC** rms_mean:81 rms_max:365 peak:749 transients:0
```

---

@LAT103LON3001 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10469824 ±0 frame:8000
seq: 4592
follows: 0x00000010:1378 0x00000011:1321 0x00000012:1232 0x00000100:943 0x00000200:2018
said: 1 | **LINKWIN** t_ms:10459156 stream:0x732acba3 wall:0 window_ms:60007
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:126 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 5 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-65 rssi_max:-64
said: 6 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 7 | **LINK** peer:0x00000012 proto:espnow n:99 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 8 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 9 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 10 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-64 observed:-65
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-44 observed:-44
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000011 ble met predicted:-53 observed:-53
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000010 ble unobserved predicted:-49 observed:-49
percept: 15 | 0x00000010 | link_stable | ble | ? | -
said: 16 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 16 | 0x00000100 | link_stable | espnow | + | -
said: 17 | 0x00000011 espnow met predicted:-32 observed:-33
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON27368 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10469824 ±0 frame:8000
seq: 4593
follows: 0x00000010:1378 0x00000011:1321 0x00000012:1232 0x00000100:943 0x00000200:2018
said: 1 | **ACOUSTICWIN** t_ms:10459156 stream:0x732acba3 wall:0 window_ms:60007 blocks:3116 rate:8000
said: 2 | **ACOUSTIC** rms_mean:83 rms_max:544 peak:1160 transients:0
```

---

@LAT106LON176 | created:0 | updated:0

**BAR** frame:8000 bar:17 own:10 held:40 terms:9 digest:0x5345e039 settled_ms:300004
**HOLDS** agent:0x00000010 n:10 lo:1365 hi:1374 sum:13695
**HOLDS** agent:0x00000011 n:10 lo:1307 hi:1316 sum:13115
**HOLDS** agent:0x00000012 n:10 lo:1216 hi:1226 sum:12214
**HOLDS** agent:0x00000200 n:10 lo:2005 hi:2014 sum:20095
**HOLDS** agent:0x00000300 n:10 lo:4564 hi:4582 sum:45730
**DELIVER** up_s:10501 heap:13732 fetched:739 unanswered:385 broken:130 resumed:2174 empty:198 served:3060 wants:3789 early:127 wantq_drop:1 superseded:2

---

@LAT103LON3002 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10529824 ±0 frame:8000
seq: 4594
follows: 0x00000010:1379 0x00000011:1322 0x00000012:1233 0x00000100:944 0x00000200:2019
said: 1 | **LINKWIN** t_ms:10519156 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:51 rssi_min:-82 rssi_med:-65 rssi_max:-64
said: 3 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 4 | **LINK** peer:0x00000010 proto:espnow n:108 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 5 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | **LINK** peer:0x00000200 proto:espnow n:73 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-79 rssi_med:-44 rssi_max:-43
said: 8 | **LINK** peer:0x00000011 proto:espnow n:63 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 9 | **LINK** peer:0x00000011 proto:ble n:52 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 10 | 0x00000011 ble met predicted:-53 observed:-53
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-65 observed:-65
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-33 observed:-32
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-44 observed:-44
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 17 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON27369 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10529824 ±0 frame:8000
seq: 4595
follows: 0x00000010:1379 0x00000011:1322 0x00000012:1233 0x00000100:944 0x00000200:2019
said: 1 | **ACOUSTICWIN** t_ms:10519156 stream:0x732acba3 wall:0 window_ms:60000 blocks:2659 rate:8000
said: 2 | **ACOUSTIC** rms_mean:78 rms_max:212 peak:397 transients:0
```

---

@LAT103LON3003 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10589828 ±0 frame:8000
seq: 4596
follows: 0x00000010:1380 0x00000011:1323 0x00000012:1234 0x00000100:945 0x00000200:2020
said: 1 | **LINKWIN** t_ms:10579160 stream:0x732acba3 wall:0 window_ms:60004
said: 2 | **LINK** peer:0x00000100 proto:espnow n:71 rssi_min:-39 rssi_med:-38 rssi_max:-38
said: 3 | **LINK** peer:0x00000011 proto:espnow n:83 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 4 | **LINK** peer:0x00000012 proto:espnow n:82 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 5 | **LINK** peer:0x00000010 proto:espnow n:119 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 6 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-50 rssi_med:-49 rssi_max:-49
said: 7 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-66 rssi_med:-65 rssi_max:-64
said: 8 | **LINK** peer:0x00000200 proto:espnow n:71 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 9 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-46 rssi_med:-44 rssi_max:-42
said: 10 | 0x00000200 ble met predicted:-65 observed:-65
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-44 observed:-44
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 espnow met predicted:-32 observed:-32
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble unobserved predicted:-53 observed:-53
percept: 17 | 0x00000011 | link_stable | ble | ? | -
```

---

@LAT103LON27370 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10589828 ±0 frame:8000
seq: 4597
follows: 0x00000010:1380 0x00000011:1323 0x00000012:1234 0x00000100:945 0x00000200:2020
said: 1 | **ACOUSTICWIN** t_ms:10579160 stream:0x732acba3 wall:0 window_ms:60004 blocks:3336 rate:8000
said: 2 | **ACOUSTIC** rms_mean:85 rms_max:246 peak:535 transients:0
```

---

@LAT103LON3004 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10649828 ±0 frame:8000
seq: 4598
follows: 0x00000010:1381 0x00000011:1324 0x00000012:1235 0x00000100:946 0x00000200:2021
said: 1 | **LINKWIN** t_ms:10639160 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 3 | **LINK** peer:0x00000012 proto:espnow n:90 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 4 | **LINK** peer:0x00000010 proto:espnow n:93 rssi_min:-32 rssi_med:-30 rssi_max:-28
said: 5 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 6 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-79 rssi_med:-53 rssi_max:-49
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000200 proto:espnow n:158 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 9 | **LINK** peer:0x00000012 proto:ble n:69 rssi_min:-82 rssi_med:-44 rssi_max:-43
said: 10 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-32 observed:-32
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000010 ble met predicted:-49 observed:-49
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000200 ble unobserved predicted:-65 observed:-65
percept: 15 | 0x00000200 | link_stable | ble | ? | -
said: 16 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-44 observed:-44
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON27371 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10649828 ±0 frame:8000
seq: 4599
follows: 0x00000010:1381 0x00000011:1324 0x00000012:1235 0x00000100:946 0x00000200:2021
said: 1 | **ACOUSTICWIN** t_ms:10639160 stream:0x732acba3 wall:0 window_ms:60000 blocks:3129 rate:8000
said: 2 | **ACOUSTIC** rms_mean:87 rms_max:227 peak:442 transients:0
```

---

@LAT105LON5460 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 10646407 ±21 frame:8000
seq: 1324
follows: 0x00000010:1381 0x00000012:1234 0x00000100:946 0x00000200:2021 0x00000300:4597
said: 1 | **LINKWIN** t_ms:10635696 stream:0x732acba3 wall:0 window_ms:60031
said: 2 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-41 rssi_med:-41 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:153 rssi_min:-28 rssi_med:-25 rssi_max:-25
said: 4 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-82 rssi_med:-51 rssi_max:-49
said: 5 | **LINK** peer:0x00000200 proto:espnow n:149 rssi_min:-54 rssi_med:-53 rssi_max:-48
said: 6 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-40 rssi_max:-36
said: 7 | **LINK** peer:0x00000010 proto:espnow n:92 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 8 | **LINK** peer:0x00000012 proto:espnow n:110 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 9 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-64 rssi_max:-61
```

---

@LAT105LON5461 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 10647483 ±21 frame:8000
seq: 1235
follows: 0x00000010:1381 0x00000011:1324 0x00000100:946 0x00000200:2021 0x00000300:4597
said: 1 | **LINKWIN** t_ms:10636807 stream:0x732acba3 wall:0 window_ms:60017
said: 2 | **LINK** peer:0x00000011 proto:espnow n:126 rssi_min:-39 rssi_med:-37 rssi_max:-34
said: 3 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000010 proto:espnow n:92 rssi_min:-56 rssi_med:-53 rssi_max:-51
said: 5 | **LINK** peer:0x00000200 proto:espnow n:167 rssi_min:-47 rssi_med:-45 rssi_max:-41
said: 6 | **LINK** peer:0x00000300 proto:espnow n:173 rssi_min:-19 rssi_med:-17 rssi_max:-16
said: 7 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-55 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-85 rssi_med:-64 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-50 rssi_max:-47
```

---

@LAT105LON5462 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 10654322 ±21 frame:8000
seq: 1382
follows: 0x00000011:1324 0x00000012:1235 0x00000100:946 0x00000200:2021 0x00000300:4599
said: 1 | **LINKWIN** t_ms:10643611 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:espnow n:154 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000300 proto:espnow n:135 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 5 | **LINK** peer:0x00000012 proto:espnow n:83 rssi_min:-55 rssi_med:-54 rssi_max:-52
said: 6 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-79 rssi_med:-69 rssi_max:-61
said: 7 | **LINK** peer:0x00000012 proto:ble n:46 rssi_min:-86 rssi_med:-62 rssi_max:-51
said: 8 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-76 rssi_med:-38 rssi_max:-33
said: 9 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-40 rssi_med:-37 rssi_max:-36
```

---

@LAT105LON5463 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 10683109 ±21 frame:8000
seq: 2022
follows: 0x00000010:1382 0x00000011:1324 0x00000012:1235 0x00000100:947 0x00000300:4599
said: 1 | **LINKWIN** t_ms:10672431 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:123 rssi_min:-52 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-34 rssi_med:-33 rssi_max:-33
said: 4 | **LINK** peer:0x00000012 proto:espnow n:102 rssi_min:-46 rssi_med:-44 rssi_max:-40
said: 5 | **LINK** peer:0x00000300 proto:espnow n:136 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-58 rssi_med:-56 rssi_max:-56
said: 7 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-64 rssi_max:-59
said: 8 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-60 rssi_max:-59
said: 9 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-82 rssi_med:-59 rssi_max:-54
```

---

@LAT105LON5464 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 10706405 ±21 frame:8000
seq: 1325
follows: 0x00000010:1382 0x00000012:1235 0x00000100:947 0x00000200:2022 0x00000300:4599
said: 1 | **LINKWIN** t_ms:10695696 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:108 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 3 | **LINK** peer:0x00000300 proto:espnow n:139 rssi_min:-27 rssi_med:-25 rssi_max:-25
said: 4 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-41 rssi_med:-41 rssi_max:-40
said: 5 | **LINK** peer:0x00000012 proto:espnow n:105 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 6 | **LINK** peer:0x00000200 proto:espnow n:109 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 7 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-80 rssi_med:-44 rssi_max:-39
said: 8 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-82 rssi_med:-51 rssi_max:-49
said: 9 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-40 rssi_max:-36
```

---

@LAT105LON5465 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 10707510 ±21 frame:8000
seq: 1236
follows: 0x00000010:1382 0x00000011:1325 0x00000100:947 0x00000200:2022 0x00000300:4599
said: 1 | **LINKWIN** t_ms:10696834 stream:0x732acba3 wall:0 window_ms:60027
said: 2 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-50 rssi_max:-47
said: 3 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000200 proto:espnow n:110 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000300 proto:espnow n:137 rssi_min:-18 rssi_med:-17 rssi_max:-16
said: 6 | **LINK** peer:0x00000010 proto:espnow n:105 rssi_min:-55 rssi_med:-53 rssi_max:-52
said: 7 | **LINK** peer:0x00000011 proto:espnow n:134 rssi_min:-39 rssi_med:-37 rssi_max:-34
said: 8 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-80 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-57 rssi_max:-52
```

---

@LAT103LON3005 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10709842 ±0 frame:8000
seq: 4600
follows: 0x00000010:1382 0x00000011:1325 0x00000012:1236 0x00000100:947 0x00000200:2022
said: 1 | **LINKWIN** t_ms:10699174 stream:0x732acba3 wall:0 window_ms:60014
said: 2 | **LINK** peer:0x00000011 proto:espnow n:124 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 3 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 4 | **LINK** peer:0x00000012 proto:espnow n:113 rssi_min:-28 rssi_med:-27 rssi_max:-25
said: 5 | **LINK** peer:0x00000200 proto:espnow n:107 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 6 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-80 rssi_med:-53 rssi_max:-49
said: 7 | **LINK** peer:0x00000010 proto:espnow n:104 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-79 rssi_med:-44 rssi_max:-43
said: 9 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 10 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-32 observed:-33
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-53 observed:-53
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000010 ble met predicted:-49 observed:-49
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-44 observed:-44
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON27372 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10709842 ±0 frame:8000
seq: 4601
follows: 0x00000010:1382 0x00000011:1325 0x00000012:1236 0x00000100:947 0x00000200:2022
said: 1 | **ACOUSTICWIN** t_ms:10699174 stream:0x732acba3 wall:0 window_ms:60014 blocks:3345 rate:8000
said: 2 | **ACOUSTIC** rms_mean:83 rms_max:197 peak:388 transients:0
```

---

@LAT105LON5466 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 10714323 ±21 frame:8000
seq: 1383
follows: 0x00000011:1325 0x00000012:1236 0x00000100:947 0x00000200:2022 0x00000300:4601
said: 1 | **LINKWIN** t_ms:10703611 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-40 rssi_med:-37 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-23 rssi_med:-23 rssi_max:-20
said: 4 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 5 | **LINK** peer:0x00000011 proto:espnow n:121 rssi_min:-23 rssi_med:-22 rssi_max:-22
said: 6 | **LINK** peer:0x00000200 proto:espnow n:134 rssi_min:-59 rssi_med:-58 rssi_max:-55
said: 7 | **LINK** peer:0x00000012 proto:espnow n:93 rssi_min:-55 rssi_med:-54 rssi_max:-51
said: 8 | **LINK** peer:0x00000011 proto:ble n:70 rssi_min:-76 rssi_med:-38 rssi_max:-33
said: 9 | **LINK** peer:0x00000012 proto:ble n:50 rssi_min:-86 rssi_med:-62 rssi_max:-50
```

---

@LAT105LON5467 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 10743110 ±21 frame:8000
seq: 2023
follows: 0x00000010:1383 0x00000011:1325 0x00000012:1236 0x00000100:948 0x00000300:4601
said: 1 | **LINKWIN** t_ms:10732431 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-35 rssi_med:-33 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:espnow n:181 rssi_min:-45 rssi_med:-44 rssi_max:-41
said: 4 | **LINK** peer:0x00000012 proto:espnow n:76 rssi_min:-46 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-58 rssi_med:-57 rssi_max:-55
said: 7 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-80 rssi_med:-64 rssi_max:-59
said: 8 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-81 rssi_med:-71 rssi_max:-60
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-62 rssi_med:-59 rssi_max:-54
```

---

@LAT105LON5468 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 10766408 ±21 frame:8000
seq: 1326
follows: 0x00000010:1383 0x00000012:1236 0x00000100:948 0x00000200:2023 0x00000300:4601
said: 1 | **LINKWIN** t_ms:10755696 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:75 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000300 proto:espnow n:191 rssi_min:-27 rssi_med:-25 rssi_max:-25
said: 5 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-41 rssi_med:-41 rssi_max:-36
said: 6 | **LINK** peer:0x00000200 proto:espnow n:136 rssi_min:-54 rssi_med:-53 rssi_max:-53
said: 7 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-64 rssi_max:-61
said: 8 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-44 rssi_max:-39
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-51 rssi_max:-49
```

---

@LAT103LON3006 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10769842 ±0 frame:8000
seq: 4602
follows: 0x00000010:1383 0x00000011:1326 0x00000012:1237 0x00000100:948 0x00000200:2023
said: 1 | **LINKWIN** t_ms:10759174 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:95 rssi_min:-34 rssi_med:-33 rssi_max:-32
said: 3 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-80 rssi_med:-49 rssi_max:-48
said: 4 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-66 rssi_med:-65 rssi_max:-63
said: 6 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 7 | **LINK** peer:0x00000012 proto:espnow n:98 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 8 | **LINK** peer:0x00000200 proto:espnow n:143 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 9 | **LINK** peer:0x00000010 proto:espnow n:130 rssi_min:-32 rssi_med:-30 rssi_max:-29
said: 10 | 0x00000011 espnow met predicted:-33 observed:-33
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble unobserved predicted:-53 observed:-53
percept: 14 | 0x00000011 | link_stable | ble | ? | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-44 observed:-44
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-49 observed:-49
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON27373 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10769842 ±0 frame:8000
seq: 4603
follows: 0x00000010:1383 0x00000011:1326 0x00000012:1237 0x00000100:948 0x00000200:2023
said: 1 | **ACOUSTICWIN** t_ms:10759174 stream:0x732acba3 wall:0 window_ms:60000 blocks:3127 rate:8000
said: 2 | **ACOUSTIC** rms_mean:86 rms_max:545 peak:1059 transients:0
```

---

@LAT105LON5469 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 10767537 ±21 frame:8000
seq: 1237
follows: 0x00000010:1383 0x00000011:1326 0x00000100:948 0x00000200:2023 0x00000300:4601
said: 1 | **LINKWIN** t_ms:10756863 stream:0x732acba3 wall:0 window_ms:60029
said: 2 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-82 rssi_med:-31 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:espnow n:220 rssi_min:-18 rssi_med:-17 rssi_max:-16
said: 4 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000010 proto:espnow n:99 rssi_min:-56 rssi_med:-53 rssi_max:-51
said: 6 | **LINK** peer:0x00000200 proto:espnow n:162 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-87 rssi_med:-63 rssi_max:-51
said: 8 | **LINK** peer:0x00000011 proto:espnow n:96 rssi_min:-39 rssi_med:-37 rssi_max:-34
said: 9 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-80 rssi_med:-55 rssi_max:-51
```

---

@LAT105LON5470 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 10774278 ±21 frame:8000
seq: 1384
follows: 0x00000011:1326 0x00000012:1237 0x00000100:948 0x00000200:2023 0x00000300:4603
said: 1 | **LINKWIN** t_ms:10763610 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:134 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:90 rssi_min:-23 rssi_med:-22 rssi_max:-22
said: 5 | **LINK** peer:0x00000012 proto:espnow n:111 rssi_min:-55 rssi_med:-53 rssi_max:-51
said: 6 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-41 rssi_med:-38 rssi_max:-33
said: 7 | **LINK** peer:0x00000012 proto:ble n:48 rssi_min:-85 rssi_med:-62 rssi_max:-51
said: 8 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-69 rssi_max:-61
said: 9 | **LINK** peer:0x00000300 proto:espnow n:200 rssi_min:-24 rssi_med:-23 rssi_max:-22
```

---

@LAT105LON5471 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 10803111 ±21 frame:8000
seq: 2024
follows: 0x00000010:1384 0x00000011:1326 0x00000012:1237 0x00000100:949 0x00000300:4603
said: 1 | **LINKWIN** t_ms:10792430 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:82 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 3 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-33 rssi_med:-33 rssi_max:-33
said: 4 | **LINK** peer:0x00000300 proto:espnow n:174 rssi_min:-45 rssi_med:-44 rssi_max:-40
said: 5 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-58 rssi_med:-56 rssi_max:-56
said: 6 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-67 rssi_med:-64 rssi_max:-59
said: 8 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-81 rssi_med:-71 rssi_max:-60
said: 9 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-80 rssi_med:-60 rssi_max:-59
```

---

@LAT103LON3007 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10829842 ±0 frame:8000
seq: 4604
follows: 0x00000010:1384 0x00000011:1326 0x00000012:1237 0x00000100:949 0x00000200:2024
said: 1 | **LINKWIN** t_ms:10819174 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:59 rssi_min:-35 rssi_med:-32 rssi_max:-32
said: 3 | **LINK** peer:0x00000012 proto:espnow n:74 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 4 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 6 | **LINK** peer:0x00000200 proto:espnow n:106 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 8 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 10 | 0x00000011 espnow met predicted:-33 observed:-32
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000010 ble met predicted:-49 observed:-49
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000012 ble met predicted:-44 observed:-44
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000200 ble unobserved predicted:-65 observed:-65
percept: 13 | 0x00000200 | link_stable | ble | ? | -
said: 14 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON27374 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10829842 ±0 frame:8000
seq: 4605
follows: 0x00000010:1384 0x00000011:1326 0x00000012:1237 0x00000100:949 0x00000200:2024
said: 1 | **ACOUSTICWIN** t_ms:10819174 stream:0x732acba3 wall:0 window_ms:60000 blocks:3342 rate:8000
said: 2 | **ACOUSTIC** rms_mean:88 rms_max:261 peak:471 transients:0
```

---

@LAT105LON5472 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 10834324 ±21 frame:8000
seq: 1385
follows: 0x00000011:1327 0x00000012:1238 0x00000100:949 0x00000200:2024 0x00000300:4603
said: 1 | **LINKWIN** t_ms:10823610 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-71 rssi_med:-69 rssi_max:-61
said: 3 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:111 rssi_min:-23 rssi_med:-22 rssi_max:-22
said: 5 | **LINK** peer:0x00000012 proto:espnow n:78 rssi_min:-55 rssi_med:-53 rssi_max:-51
said: 6 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-59 rssi_med:-57 rssi_max:-56
said: 7 | **LINK** peer:0x00000300 proto:espnow n:96 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 8 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-76 rssi_med:-38 rssi_max:-33
said: 9 | **LINK** peer:0x00000012 proto:ble n:50 rssi_min:-86 rssi_med:-62 rssi_max:-51
```

---

@LAT105LON5473 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 10827562 ±21 frame:8000
seq: 1238
follows: 0x00000010:1384 0x00000011:1327 0x00000100:949 0x00000200:2024 0x00000300:4603
said: 1 | **LINKWIN** t_ms:10816891 stream:0x732acba3 wall:0 window_ms:60028
said: 2 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-39 rssi_med:-37 rssi_max:-33
said: 3 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-45 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000300 proto:espnow n:154 rssi_min:-19 rssi_med:-17 rssi_max:-16
said: 5 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-87 rssi_med:-63 rssi_max:-52
said: 6 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-80 rssi_med:-50 rssi_max:-47
said: 7 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-57 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:espnow n:107 rssi_min:-56 rssi_med:-53 rssi_max:-50
```

---

@LAT105LON5474 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 10863113 ±21 frame:8000
seq: 2025
follows: 0x00000010:1386 0x00000011:1328 0x00000012:1239 0x00000100:950 0x00000300:4605
said: 1 | **LINKWIN** t_ms:10852431 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-34 rssi_med:-33 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:espnow n:124 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 4 | **LINK** peer:0x00000011 proto:espnow n:102 rssi_min:-51 rssi_med:-50 rssi_max:-49
said: 5 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-58 rssi_med:-56 rssi_max:-56
said: 6 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-79 rssi_med:-59 rssi_max:-54
said: 7 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-72 rssi_med:-71 rssi_max:-59
said: 8 | **LINK** peer:0x00000011 proto:ble n:51 rssi_min:-82 rssi_med:-64 rssi_max:-58
said: 9 | **LINK** peer:0x00000012 proto:espnow n:86 rssi_min:-46 rssi_med:-44 rssi_max:-44
```

---

@LAT103LON3008 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10889842 ±0 frame:8000
seq: 4606
follows: 0x00000010:1386 0x00000011:1329 0x00000012:1240 0x00000100:950 0x00000200:2025
said: 1 | **LINKWIN** t_ms:10879174 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-65 rssi_med:-65 rssi_max:-64
said: 3 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-81 rssi_med:-44 rssi_max:-43
said: 4 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 5 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-79 rssi_med:-49 rssi_max:-48
said: 6 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 7 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 8 | **LINK** peer:0x00000200 proto:espnow n:119 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 9 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 10 | 0x00000011 espnow unobserved predicted:-32 observed:-32
percept: 10 | 0x00000011 | link_stable | espnow | ? | -
said: 11 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000012 ble met predicted:-44 observed:-44
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-49 observed:-49
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-53 observed:-53
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON16514 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 10889842 ±0 frame:8000
seq: 4607
follows: 0x00000010:1386 0x00000011:1329 0x00000012:1240 0x00000100:950 0x00000200:2025
said: 1 | **MOTIONWIN** t_ms:10879174 stream:0x732acba3 wall:0 window_ms:60000 n:978
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:26985 window_ms:1740044 moving_permille:0 dev_mean_mg:7 dev_max_mg:13 moving_ms:0 first_t_ms:9139130 last_t_ms:10819174 covered_by:@LAT103LON16513
```

---

@LAT103LON27375 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10889842 ±0 frame:8000
seq: 4608
follows: 0x00000010:1386 0x00000011:1329 0x00000012:1240 0x00000100:950 0x00000200:2025
said: 1 | **ACOUSTICWIN** t_ms:10879174 stream:0x732acba3 wall:0 window_ms:60000 blocks:3333 rate:8000
said: 2 | **ACOUSTIC** rms_mean:81 rms_max:269 peak:478 transients:0
```

---

@LAT105LON5475 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 10826409 ±21 frame:8000
seq: 1327
follows: 0x00000010:1384 0x00000012:1237 0x00000100:949 0x00000200:2024 0x00000300:4603
said: 1 | **LINKWIN** t_ms:10815696 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000200 proto:espnow n:107 rssi_min:-54 rssi_med:-53 rssi_max:-53
said: 4 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-42 rssi_med:-41 rssi_max:-37
said: 5 | **LINK** peer:0x00000300 proto:espnow n:163 rssi_min:-27 rssi_med:-25 rssi_max:-25
said: 6 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-51 rssi_max:-49
said: 7 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-44 rssi_max:-39
said: 8 | **LINK** peer:0x00000010 proto:espnow n:81 rssi_min:-24 rssi_med:-24 rssi_max:-23
said: 9 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-43 rssi_max:-36
```

---

@LAT105LON5476 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 10887569 ±21 frame:8000
seq: 1240
follows: 0x00000010:1386 0x00000011:1329 0x00000100:950 0x00000200:2025 0x00000300:4605
said: 1 | **LINKWIN** t_ms:10876890 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:75 rssi_min:-74 rssi_med:-38 rssi_max:-33
said: 3 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-47 rssi_med:-44 rssi_max:-42
said: 4 | **LINK** peer:0x00000200 proto:espnow n:121 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000010 proto:espnow n:133 rssi_min:-55 rssi_med:-53 rssi_max:-51
said: 6 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-80 rssi_med:-55 rssi_max:-52
said: 7 | **LINK** peer:0x00000010 proto:ble n:48 rssi_min:-85 rssi_med:-63 rssi_max:-51
said: 8 | **LINK** peer:0x00000300 proto:ble n:71 rssi_min:-81 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-80 rssi_med:-50 rssi_max:-47
```

---

@LAT105LON5477 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 10894325 ±21 frame:8000
seq: 1387
follows: 0x00000011:1329 0x00000012:1240 0x00000100:950 0x00000200:2025 0x00000300:4605
said: 1 | **LINKWIN** t_ms:10883610 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:183 rssi_min:-69 rssi_med:-23 rssi_max:-20
said: 4 | **LINK** peer:0x00000012 proto:ble n:48 rssi_min:-85 rssi_med:-62 rssi_max:-50
said: 5 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-80 rssi_med:-37 rssi_max:-36
said: 6 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-38 rssi_max:-32
said: 7 | **LINK** peer:0x00000200 proto:espnow n:126 rssi_min:-59 rssi_med:-57 rssi_max:-57
said: 8 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-79 rssi_med:-69 rssi_max:-61
said: 9 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-55 rssi_med:-53 rssi_max:-52
```

---

@LAT105LON5478 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 10886409 ±21 frame:8000
seq: 1329
follows: 0x00000010:1386 0x00000012:1239 0x00000100:950 0x00000200:2025 0x00000300:4605
said: 1 | **LINKWIN** t_ms:10875696 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000010 proto:espnow n:125 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 4 | **LINK** peer:0x00000200 proto:espnow n:119 rssi_min:-55 rssi_med:-53 rssi_max:-53
said: 5 | **LINK** peer:0x00000012 proto:espnow n:100 rssi_min:-41 rssi_med:-35 rssi_max:-34
said: 6 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-81 rssi_med:-51 rssi_max:-49
said: 7 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-82 rssi_med:-44 rssi_max:-39
said: 8 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-64 rssi_max:-61
said: 9 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-83 rssi_med:-43 rssi_max:-35
```

---

@LAT105LON5479 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 10923095 ±21 frame:8000
seq: 2026
follows: 0x00000010:1387 0x00000011:1329 0x00000012:1240 0x00000100:952 0x00000300:4608
said: 1 | **LINKWIN** t_ms:10912431 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-67 rssi_med:-64 rssi_max:-59
said: 3 | **LINK** peer:0x00000012 proto:espnow n:108 rssi_min:-45 rssi_med:-44 rssi_max:-44
said: 4 | **LINK** peer:0x00000100 proto:espnow n:71 rssi_min:-35 rssi_med:-33 rssi_max:-33
said: 5 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-80 rssi_med:-61 rssi_max:-59
said: 6 | **LINK** peer:0x00000300 proto:espnow n:224 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 7 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-60 rssi_max:-54
said: 8 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-76 rssi_med:-71 rssi_max:-60
said: 9 | **LINK** peer:0x00000011 proto:espnow n:147 rssi_min:-51 rssi_med:-50 rssi_max:-49
```

---

@LAT105LON5480 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 10946410 ±21 frame:8000
seq: 1330
follows: 0x00000010:1387 0x00000012:1240 0x00000100:952 0x00000200:2026 0x00000300:4608
said: 1 | **LINKWIN** t_ms:10935696 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:201 rssi_min:-27 rssi_med:-25 rssi_max:-25
said: 3 | **LINK** peer:0x00000200 proto:espnow n:81 rssi_min:-54 rssi_med:-53 rssi_max:-53
said: 4 | **LINK** peer:0x00000012 proto:espnow n:108 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 5 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-41 rssi_med:-41 rssi_max:-36
said: 6 | **LINK** peer:0x00000010 proto:espnow n:111 rssi_min:-25 rssi_med:-24 rssi_max:-23
said: 7 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-40 rssi_max:-36
said: 8 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-83 rssi_med:-44 rssi_max:-39
said: 9 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-82 rssi_med:-65 rssi_max:-61
```

---

@LAT105LON5481 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 10947558 ±21 frame:8000
seq: 1241
follows: 0x00000010:1387 0x00000011:1330 0x00000100:952 0x00000200:2026 0x00000300:4608
said: 1 | **LINKWIN** t_ms:10936890 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-86 rssi_med:-64 rssi_max:-52
said: 3 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-31 rssi_max:-31
said: 4 | **LINK** peer:0x00000011 proto:espnow n:155 rssi_min:-39 rssi_med:-37 rssi_max:-33
said: 5 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-47 rssi_med:-44 rssi_max:-43
said: 6 | **LINK** peer:0x00000300 proto:espnow n:194 rssi_min:-18 rssi_med:-17 rssi_max:-16
said: 7 | **LINK** peer:0x00000010 proto:espnow n:114 rssi_min:-56 rssi_med:-53 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:espnow n:89 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 9 | **LINK** peer:0x00000011 proto:ble n:66 rssi_min:-81 rssi_med:-50 rssi_max:-47
```

---

@LAT103LON3009 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 10949858 ±0 frame:8000
seq: 4609
follows: 0x00000010:1387 0x00000011:1330 0x00000012:1241 0x00000100:952 0x00000200:2026
said: 1 | **LINKWIN** t_ms:10939190 stream:0x732acba3 wall:0 window_ms:60016
said: 2 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-66 rssi_med:-65 rssi_max:-63
said: 3 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 4 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-40 rssi_med:-38 rssi_max:-38
said: 5 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-79 rssi_med:-53 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:ble n:56 rssi_min:-50 rssi_med:-49 rssi_max:-48
said: 7 | **LINK** peer:0x00000012 proto:espnow n:97 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 8 | **LINK** peer:0x00000011 proto:espnow n:141 rssi_min:-34 rssi_med:-32 rssi_max:-32
said: 9 | **LINK** peer:0x00000010 proto:espnow n:99 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 10 | 0x00000200 ble met predicted:-65 observed:-65
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000012 ble unobserved predicted:-44 observed:-44
percept: 11 | 0x00000012 | link_stable | ble | ? | -
said: 12 | 0x00000011 ble met predicted:-53 observed:-53
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000010 ble met predicted:-49 observed:-49
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-38 observed:-38
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-30 observed:-30
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000200 espnow met predicted:-48 observed:-48
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT104LON668 | created:0 | updated:0

**carried through @LAT103LON2969**

```ttdb-carried
through: 2969
through: 8353
through: 16491
through: 27356
carried: 2190 37 2426 2196 | 0x00000200 | link_stable | espnow
carried: 2306 26 2688 2236 | 0x00000200 | link_stable | ble
carried: 1058 15 1426 958 | 0x00000100 | link_stable | espnow
carried: 1626 16 1996 1550 | 0x00000010 | link_stable | ble
carried: 1588 30 1971 1527 | 0x00000010 | link_stable | espnow
carried: 1155 8 1163 1204 | 0x00000011 | link_stable | ble
carried: 1073 24 1097 1119 | 0x00000011 | link_stable | espnow
carried: 1077 9 1086 1125 | 0x00000012 | link_stable | ble
carried: 1079 9 1088 1124 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON27376 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 10949858 ±0 frame:8000
seq: 4610
follows: 0x00000010:1387 0x00000011:1330 0x00000012:1241 0x00000100:952 0x00000200:2026
said: 1 | **ACOUSTICWIN** t_ms:10939190 stream:0x732acba3 wall:0 window_ms:60016 blocks:3345 rate:8000
said: 2 | **ACOUSTIC** rms_mean:77 rms_max:202 peak:418 transients:0
```

---

@LAT105LON5482 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 10954330 ±21 frame:8000
seq: 1388
follows: 0x00000011:1330 0x00000012:1241 0x00000100:952 0x00000200:2026 0x00000300:4608
said: 1 | **LINKWIN** t_ms:10943616 stream:0x732acba3 wall:0 window_ms:60005
said: 2 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:espnow n:90 rssi_min:-59 rssi_med:-58 rssi_max:-57
said: 4 | **LINK** peer:0x00000011 proto:espnow n:132 rssi_min:-24 rssi_med:-22 rssi_max:-22
said: 5 | **LINK** peer:0x00000012 proto:espnow n:96 rssi_min:-55 rssi_med:-53 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:espnow n:180 rssi_min:-24 rssi_med:-23 rssi_max:-22
said: 7 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-85 rssi_med:-62 rssi_max:-51
said: 8 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-70 rssi_med:-69 rssi_max:-61
said: 9 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-40 rssi_med:-37 rssi_max:-36
```

---

@LAT105LON5483 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 10983113 ±21 frame:8000
seq: 2027
follows: 0x00000010:1388 0x00000011:1330 0x00000012:1241 0x00000100:953 0x00000300:4610
said: 1 | **LINKWIN** t_ms:10972431 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-68 rssi_med:-60 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:74 rssi_min:-36 rssi_med:-33 rssi_max:-32
said: 4 | **LINK** peer:0x00000012 proto:espnow n:95 rssi_min:-48 rssi_med:-44 rssi_max:-43
said: 5 | **LINK** peer:0x00000300 proto:espnow n:123 rssi_min:-59 rssi_med:-44 rssi_max:-41
said: 6 | **LINK** peer:0x00000010 proto:espnow n:82 rssi_min:-76 rssi_med:-57 rssi_max:-50
said: 7 | **LINK** peer:0x00000011 proto:espnow n:92 rssi_min:-57 rssi_med:-50 rssi_max:-49
said: 8 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-81 rssi_med:-64 rssi_max:-58
said: 9 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-92 rssi_med:-71 rssi_max:-58
```

---

@LAT103LON3010 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11009858 ±0 frame:8000
seq: 4611
follows: 0x00000010:1388 0x00000011:1331 0x00000012:1242 0x00000100:953 0x00000200:2027
said: 1 | **LINKWIN** t_ms:10999190 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:114 rssi_min:-35 rssi_med:-27 rssi_max:-25
said: 3 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-50 rssi_max:-47
said: 4 | **LINK** peer:0x00000200 proto:espnow n:81 rssi_min:-52 rssi_med:-47 rssi_max:-41
said: 5 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-52 rssi_max:-46
said: 6 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-83 rssi_med:-62 rssi_max:-56
said: 7 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-53 rssi_med:-39 rssi_max:-36
said: 8 | **LINK** peer:0x00000010 proto:espnow n:111 rssi_min:-39 rssi_med:-31 rssi_max:-29
said: 9 | **LINK** peer:0x00000011 proto:espnow n:71 rssi_min:-41 rssi_med:-33 rssi_max:-28
said: 10 | 0x00000200 ble met predicted:-65 observed:-62
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000200 espnow met predicted:-48 observed:-47
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-38 observed:-39
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000011 ble met predicted:-53 observed:-52
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-49 observed:-50
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000012 espnow met predicted:-27 observed:-27
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000011 espnow met predicted:-32 observed:-33
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000010 espnow met predicted:-30 observed:-31
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON27377 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11009858 ±0 frame:8000
seq: 4612
follows: 0x00000010:1388 0x00000011:1331 0x00000012:1242 0x00000100:953 0x00000200:2027
said: 1 | **ACOUSTICWIN** t_ms:10999190 stream:0x732acba3 wall:0 window_ms:60000 blocks:3177 rate:8000
said: 2 | **ACOUSTIC** rms_mean:103 rms_max:1066 peak:4577 transients:3
said: 3 | **TRANSIENT** t_ms:10960883 stream:0x732acba3 wall:0 rms:1066
```

---

@LAT105LON5484 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 11007570 ±21 frame:8000
seq: 1242
follows: 0x00000010:1388 0x00000011:1330 0x00000100:953 0x00000200:2027 0x00000300:4610
said: 1 | **LINKWIN** t_ms:10996891 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-58 rssi_med:-44 rssi_max:-34
said: 3 | **LINK** peer:0x00000300 proto:espnow n:162 rssi_min:-21 rssi_med:-17 rssi_max:-15
said: 4 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-84 rssi_med:-63 rssi_max:-49
said: 5 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-81 rssi_med:-32 rssi_max:-30
said: 6 | **LINK** peer:0x00000200 proto:espnow n:79 rssi_min:-50 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:espnow n:68 rssi_min:-53 rssi_med:-38 rssi_max:-30
said: 8 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-82 rssi_med:-57 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-52 rssi_max:-45
```

---

@LAT105LON5485 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 11006437 ±21 frame:8000
seq: 1331
follows: 0x00000010:1388 0x00000012:1241 0x00000100:953 0x00000200:2027 0x00000300:4610
said: 1 | **LINKWIN** t_ms:10995722 stream:0x732acba3 wall:0 window_ms:60026
said: 2 | **LINK** peer:0x00000012 proto:espnow n:82 rssi_min:-53 rssi_med:-35 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:espnow n:154 rssi_min:-34 rssi_med:-26 rssi_max:-21
said: 4 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-43 rssi_med:-41 rssi_max:-34
said: 5 | **LINK** peer:0x00000010 proto:espnow n:93 rssi_min:-27 rssi_med:-24 rssi_max:-22
said: 6 | **LINK** peer:0x00000200 proto:espnow n:64 rssi_min:-62 rssi_med:-57 rssi_max:-53
said: 7 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-66 rssi_max:-59
said: 8 | **LINK** peer:0x00000300 proto:ble n:57 rssi_min:-82 rssi_med:-44 rssi_max:-36
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-51 rssi_max:-44
```

---

@LAT105LON5486 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 11014361 ±21 frame:8000
seq: 1389
follows: 0x00000011:1331 0x00000012:1242 0x00000100:953 0x00000200:2027 0x00000300:4612
said: 1 | **LINKWIN** t_ms:11003645 stream:0x732acba3 wall:0 window_ms:60030
said: 2 | **LINK** peer:0x00000200 proto:espnow n:84 rssi_min:-73 rssi_med:-56 rssi_max:-50
said: 3 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-26 rssi_med:-22 rssi_max:-21
said: 4 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-54 rssi_med:-48 rssi_max:-43
said: 5 | **LINK** peer:0x00000012 proto:espnow n:135 rssi_min:-66 rssi_med:-53 rssi_max:-40
said: 6 | **LINK** peer:0x00000300 proto:espnow n:216 rssi_min:-50 rssi_med:-23 rssi_max:-21
said: 7 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-89 rssi_med:-65 rssi_max:-58
said: 8 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-81 rssi_med:-40 rssi_max:-36
said: 9 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-43 rssi_med:-37 rssi_max:-32
```

---

@LAT105LON5487 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 11043116 ±21 frame:8000
seq: 2028
follows: 0x00000010:1389 0x00000011:1331 0x00000012:1242 0x00000100:954 0x00000300:4612
said: 1 | **LINKWIN** t_ms:11032431 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-36 rssi_med:-33 rssi_max:-33
said: 3 | **LINK** peer:0x00000012 proto:espnow n:103 rssi_min:-47 rssi_med:-45 rssi_max:-40
said: 4 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-62 rssi_med:-54 rssi_max:-45
said: 5 | **LINK** peer:0x00000300 proto:espnow n:250 rssi_min:-62 rssi_med:-43 rssi_max:-37
said: 6 | **LINK** peer:0x00000010 proto:espnow n:115 rssi_min:-62 rssi_med:-55 rssi_max:-49
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-69 rssi_max:-58
said: 8 | **LINK** peer:0x00000011 proto:ble n:52 rssi_min:-80 rssi_med:-68 rssi_max:-59
said: 9 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-59 rssi_max:-53
```

---

@LAT105LON5488 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 11066437 ±21 frame:8000
seq: 1332
follows: 0x00000010:1389 0x00000012:1242 0x00000100:954 0x00000200:2028 0x00000300:4612
said: 1 | **LINKWIN** t_ms:11055722 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-46 rssi_med:-43 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:espnow n:282 rssi_min:-40 rssi_med:-24 rssi_max:-22
said: 4 | **LINK** peer:0x00000010 proto:espnow n:77 rssi_min:-25 rssi_med:-22 rssi_max:-20
said: 5 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-40 rssi_max:-37
said: 6 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-82 rssi_med:-52 rssi_max:-47
said: 7 | **LINK** peer:0x00000012 proto:espnow n:102 rssi_min:-47 rssi_med:-35 rssi_max:-30
said: 8 | **LINK** peer:0x00000200 proto:espnow n:113 rssi_min:-66 rssi_med:-57 rssi_max:-49
said: 9 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-39 rssi_max:-34
```

---

@LAT105LON5489 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 11067570 ±21 frame:8000
seq: 1243
follows: 0x00000010:1389 0x00000011:1332 0x00000100:954 0x00000200:2028 0x00000300:4612
said: 1 | **LINKWIN** t_ms:11056891 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-48 rssi_med:-35 rssi_max:-31
said: 3 | **LINK** peer:0x00000300 proto:espnow n:262 rssi_min:-22 rssi_med:-17 rssi_max:-14
said: 4 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-48 rssi_med:-43 rssi_max:-42
said: 5 | **LINK** peer:0x00000010 proto:espnow n:88 rssi_min:-65 rssi_med:-52 rssi_max:-45
said: 6 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-31 rssi_max:-28
said: 7 | **LINK** peer:0x00000010 proto:ble n:54 rssi_min:-84 rssi_med:-65 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-55 rssi_max:-50
said: 9 | **LINK** peer:0x00000011 proto:espnow n:118 rssi_min:-42 rssi_med:-38 rssi_max:-30
```

---

@LAT103LON3011 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11069858 ±0 frame:8000
seq: 4613
follows: 0x00000010:1389 0x00000011:1332 0x00000012:1243 0x00000100:954 0x00000200:2028
said: 1 | **LINKWIN** t_ms:11059190 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-79 rssi_med:-43 rssi_max:-40
said: 3 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-46 rssi_med:-36 rssi_max:-34
said: 4 | **LINK** peer:0x00000200 proto:espnow n:120 rssi_min:-65 rssi_med:-49 rssi_max:-43
said: 5 | **LINK** peer:0x00000011 proto:espnow n:95 rssi_min:-41 rssi_med:-31 rssi_max:-29
said: 6 | **LINK** peer:0x00000010 proto:espnow n:67 rssi_min:-41 rssi_med:-39 rssi_max:-34
said: 7 | **LINK** peer:0x00000012 proto:espnow n:86 rssi_min:-28 rssi_med:-26 rssi_max:-23
said: 8 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 9 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-63 rssi_med:-54 rssi_max:-49
said: 10 | 0x00000012 espnow met predicted:-27 observed:-26
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000010 ble met predicted:-50 observed:-54
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-47 observed:-49
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 ble unobserved predicted:-52 observed:-52
percept: 13 | 0x00000011 | link_stable | ble | ? | -
said: 14 | 0x00000200 ble met predicted:-62 observed:-63
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000100 espnow met predicted:-39 observed:-36
percept: 15 | 0x00000100 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow violated predicted:-31 observed:-39
percept: 16 | 0x00000010 | link_stable | espnow | - | -
said: 17 | 0x00000011 espnow met predicted:-33 observed:-31
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON27378 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11069858 ±0 frame:8000
seq: 4614
follows: 0x00000010:1389 0x00000011:1332 0x00000012:1243 0x00000100:954 0x00000200:2028
said: 1 | **ACOUSTICWIN** t_ms:11059190 stream:0x732acba3 wall:0 window_ms:60000 blocks:3305 rate:8000
said: 2 | **ACOUSTIC** rms_mean:136 rms_max:1509 peak:3984 transients:2
said: 3 | **TRANSIENT** t_ms:11018428 stream:0x732acba3 wall:0 rms:1509
```

---

@LAT105LON5490 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 11074362 ±21 frame:8000
seq: 1390
follows: 0x00000011:1332 0x00000012:1243 0x00000100:954 0x00000200:2028 0x00000300:4612
said: 1 | **LINKWIN** t_ms:11063645 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:119 rssi_min:-62 rssi_med:-55 rssi_max:-50
said: 3 | **LINK** peer:0x00000012 proto:espnow n:80 rssi_min:-61 rssi_med:-53 rssi_max:-49
said: 4 | **LINK** peer:0x00000011 proto:espnow n:108 rssi_min:-23 rssi_med:-22 rssi_max:-21
said: 5 | **LINK** peer:0x00000100 proto:espnow n:69 rssi_min:-56 rssi_med:-51 rssi_max:-45
said: 6 | **LINK** peer:0x00000300 proto:espnow n:221 rssi_min:-38 rssi_med:-32 rssi_max:-27
said: 7 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-65 rssi_max:-57
said: 8 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-80 rssi_med:-67 rssi_max:-60
said: 9 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-40 rssi_med:-37 rssi_max:-32
```

---

@LAT105LON5491 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 11103117 ±21 frame:8000
seq: 2029
follows: 0x00000010:1390 0x00000011:1332 0x00000012:1243 0x00000100:955 0x00000300:4614
said: 1 | **LINKWIN** t_ms:11092431 stream:0x732acba3 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-58 rssi_max:-53
said: 3 | **LINK** peer:0x00000012 proto:espnow n:68 rssi_min:-43 rssi_med:-42 rssi_max:-41
said: 4 | **LINK** peer:0x00000300 proto:espnow n:161 rssi_min:-51 rssi_med:-45 rssi_max:-41
said: 5 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-36 rssi_med:-34 rssi_max:-33
said: 6 | **LINK** peer:0x00000011 proto:ble n:52 rssi_min:-77 rssi_med:-69 rssi_max:-63
said: 7 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-70 rssi_max:-63
said: 8 | **LINK** peer:0x00000011 proto:espnow n:80 rssi_min:-59 rssi_med:-56 rssi_max:-48
said: 9 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-63 rssi_med:-59 rssi_max:-56
```
@LAT106LON177 | created:0 | updated:0

**BAR** frame:8000 bar:18 own:10 held:40 terms:9 digest:0xabc37525 settled_ms:301165
**HOLDS** agent:0x00000010 n:10 lo:1375 hi:1384 sum:13795
**HOLDS** agent:0x00000011 n:10 lo:1317 hi:1326 sum:13215
**HOLDS** agent:0x00000012 n:10 lo:1227 hi:1237 sum:12324
**HOLDS** agent:0x00000200 n:10 lo:2015 hi:2024 sum:20195
**HOLDS** agent:0x00000300 n:10 lo:4584 hi:4602 sum:45930
**DELIVER** up_s:11109 heap:14008 fetched:779 unanswered:398 broken:135 resumed:2262 empty:209 served:3226 wants:4000 early:127 wantq_drop:1 superseded:2

---

@LAT103LON3012 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 11130952 ±0 frame:8000
seq: 4615
follows: 0x00000010:1390 0x00000011:1332 0x00000012:1243 0x00000100:955 0x00000200:2029
said: 1 | **LINKWIN** t_ms:11120284 stream:0x732acba3 wall:0 window_ms:61094
said: 2 | **LINK** peer:0x00000011 proto:espnow n:53 rssi_min:-32 rssi_med:-30 rssi_max:-30
said: 3 | **LINK** peer:0x00000010 proto:ble n:71 rssi_min:-61 rssi_med:-54 rssi_max:-50
said: 4 | **LINK** peer:0x00000012 proto:espnow n:65 rssi_min:-26 rssi_med:-26 rssi_max:-25
said: 5 | **LINK** peer:0x00000011 proto:ble n:68 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 6 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-70 rssi_med:-63 rssi_max:-59
said: 7 | **LINK** peer:0x00000200 proto:espnow n:74 rssi_min:-52 rssi_med:-49 rssi_max:-45
said: 8 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-37 rssi_med:-35 rssi_max:-33
said: 9 | **LINK** peer:0x00000010 proto:espnow n:92 rssi_min:-41 rssi_med:-39 rssi_max:-38
said: 10 | 0x00000012 ble unobserved predicted:-43 observed:-43
percept: 10 | 0x00000012 | link_stable | ble | ? | -
said: 11 | 0x00000100 espnow met predicted:-36 observed:-35
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-49 observed:-49
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-31 observed:-30
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-39 observed:-39
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 espnow met predicted:-26 observed:-26
percept: 15 | 0x00000012 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-63 observed:-63
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-54 observed:-54
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON27379 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 11130952 ±0 frame:8000
seq: 4616
follows: 0x00000010:1390 0x00000011:1332 0x00000012:1243 0x00000100:955 0x00000200:2029
said: 1 | **ACOUSTICWIN** t_ms:11120284 stream:0x732acba3 wall:0 window_ms:61094 blocks:1695 rate:8000
said: 2 | **ACOUSTIC** rms_mean:140 rms_max:1016 peak:3367 transients:2
said: 3 | **TRANSIENT** t_ms:11086060 stream:0x732acba3 wall:0 rms:1016
```
