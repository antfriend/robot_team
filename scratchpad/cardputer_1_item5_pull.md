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

@LAT106LON173 | created:0 | updated:0

**BAR** frame:8000 bar:14 own:10 held:40 terms:9 digest:0x4b93e0ea settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1333 hi:1342 sum:13375
**HOLDS** agent:0x00000011 n:10 lo:1276 hi:1285 sum:12805
**HOLDS** agent:0x00000012 n:10 lo:1183 hi:1193 sum:11884
**HOLDS** agent:0x00000200 n:10 lo:1975 hi:1984 sum:19795
**HOLDS** agent:0x00000300 n:10 lo:4501 hi:4520 sum:45109
**DELIVER** up_s:8701 heap:11060 fetched:618 unanswered:333 broken:108 resumed:1798 empty:164 served:2547 wants:3157 early:127 wantq_drop:1 superseded:2

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

@LAT106LON174 | created:0 | updated:0

**BAR** frame:8000 bar:15 own:10 held:40 terms:9 digest:0x033334fc settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1343 hi:1353 sum:13484
**HOLDS** agent:0x00000011 n:10 lo:1286 hi:1295 sum:12905
**HOLDS** agent:0x00000012 n:10 lo:1194 hi:1204 sum:11994
**HOLDS** agent:0x00000200 n:10 lo:1985 hi:1994 sum:19895
**HOLDS** agent:0x00000300 n:10 lo:4522 hi:4541 sum:45319
**DELIVER** up_s:9305 heap:11324 fetched:657 unanswered:351 broken:116 resumed:1930 empty:176 served:2701 wants:3350 early:127 wantq_drop:1 superseded:2

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

@LAT106LON176 | created:0 | updated:0

**BAR** frame:8000 bar:17 own:10 held:40 terms:9 digest:0x5345e039 settled_ms:300004
**HOLDS** agent:0x00000010 n:10 lo:1365 hi:1374 sum:13695
**HOLDS** agent:0x00000011 n:10 lo:1307 hi:1316 sum:13115
**HOLDS** agent:0x00000012 n:10 lo:1216 hi:1226 sum:12214
**HOLDS** agent:0x00000200 n:10 lo:2005 hi:2014 sum:20095
**HOLDS** agent:0x00000300 n:10 lo:4564 hi:4582 sum:45730
**DELIVER** up_s:10501 heap:13732 fetched:739 unanswered:385 broken:130 resumed:2174 empty:198 served:3060 wants:3789 early:127 wantq_drop:1 superseded:2

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

@LAT106LON177 | created:0 | updated:0

**BAR** frame:8000 bar:18 own:10 held:40 terms:9 digest:0xabc37525 settled_ms:301165
**HOLDS** agent:0x00000010 n:10 lo:1375 hi:1384 sum:13795
**HOLDS** agent:0x00000011 n:10 lo:1317 hi:1326 sum:13215
**HOLDS** agent:0x00000012 n:10 lo:1227 hi:1237 sum:12324
**HOLDS** agent:0x00000200 n:10 lo:2015 hi:2024 sum:20195
**HOLDS** agent:0x00000300 n:10 lo:4584 hi:4602 sum:45930
**DELIVER** up_s:11109 heap:14008 fetched:779 unanswered:398 broken:135 resumed:2262 empty:209 served:3226 wants:4000 early:127 wantq_drop:1 superseded:2

---

@LAT103LON16515 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 11224991 ±214767 frame:8000
seq: 4618
follows: 0x00000010:1390 0x00000011:1332 0x00000012:1243 0x00000100:955 0x00000200:2029
said: 1 | **MOTIONWIN** t_ms:11215307 stream:0x732acba3 wall:0 window_ms:71040 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:7 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8394 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11287131 ±0 frame:8000
seq: 4621
follows: 0x00000010:1392 0x00000011:1334 0x00000012:1245 0x00000100:957 0x00000200:2030
said: 1 | **ENTWIN** t_ms:11278276 stream:0x732acba3 wall:0 window_ms:133180 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT106LON178 | created:0 | updated:0

**BAR** frame:8000 bar:19 own:8 held:38 terms:9 digest:0xb5144cb4 settled_ms:300000
**HOLDS** agent:0x00000010 n:8 lo:1385 hi:1393 sum:11115
**HOLDS** agent:0x00000011 n:10 lo:1327 hi:1337 sum:13324
**HOLDS** agent:0x00000012 n:10 lo:1238 hi:1248 sum:12434
**HOLDS** agent:0x00000200 n:10 lo:2025 hi:2034 sum:20295
**HOLDS** agent:0x00000300 n:8 lo:4604 hi:4623 sum:36901
**DELIVER** up_s:561 heap:10632 fetched:22 unanswered:9 broken:0 resumed:69 empty:6 served:149 wants:159 early:0 wantq_drop:18 superseded:15

---

@LAT103LON8395 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 62000 ±0 frame:10500
seq: 4639
follows: 0x00000010:1402 0x00000011:1345 0x00000012:1256 0x00000100:967 0x00000200:2041
said: 1 | **ENTWIN** t_ms:48956 stream:0xcfc15fd4 wall:0 window_ms:62000 entities:6
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 8 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 9 | **CORE** entities:0
```

---

@LAT103LON16516 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 62000 ±0 frame:10500
seq: 4640
follows: 0x00000010:1402 0x00000011:1345 0x00000012:1256 0x00000100:967 0x00000200:2041
said: 1 | **MOTIONWIN** t_ms:48956 stream:0xcfc15fd4 wall:0 window_ms:62000 n:880
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:5 dev_max_mg:9 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8396 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 103991 ±0 frame:7500
seq: 4643
follows: 0x00000010:1408 0x00000011:1353 0x00000012:1268 0x00000100:1001 0x00000200:2044
said: 1 | **ENTWIN** t_ms:425735 stream:0xc9e0e898 wall:0 window_ms:60000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON16517 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 103991 ±0 frame:7500
seq: 4644
follows: 0x00000010:1408 0x00000011:1353 0x00000012:1268 0x00000100:1001 0x00000200:2044
said: 1 | **MOTIONWIN** t_ms:425735 stream:0xc9e0e898 wall:0 window_ms:60000 n:907
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:5 dev_max_mg:18 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT106LON179 | created:0 | updated:0

**BAR** frame:7500 bar:1 own:9 held:38 terms:9 digest:0xd2c5d402 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1407 hi:1417 sum:14124
**HOLDS** agent:0x00000011 n:10 lo:1351 hi:1361 sum:13564
**HOLDS** agent:0x00000012 n:10 lo:1267 hi:1276 sum:12715
**HOLDS** agent:0x00000200 n:8 lo:2047 hi:2054 sum:16404
**HOLDS** agent:0x00000300 n:9 lo:4642 hi:4660 sum:41866
**DELIVER** up_s:870 heap:14220 fetched:93 unanswered:48 broken:10 resumed:252 empty:16 served:282 wants:348 early:34 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:4 split:1
**SPLIT** agent:0x00000012 grammar:0xaf98ac36

---

@LAT103LON3042 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1244177 ±0 frame:7500
seq: 4682
follows: 0x00000010:1428 0x00000011:1373 0x00000012:1288 0x00000100:1020 0x00000200:2064
said: 1 | **LINKWIN** t_ms:1565921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:101 rssi_min:-46 rssi_med:-45 rssi_max:-45
said: 3 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-79 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-56 rssi_max:-53
said: 5 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 6 | **LINK** peer:0x00000010 proto:espnow n:121 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000200 proto:espnow n:140 rssi_min:-42 rssi_med:-41 rssi_max:-41
said: 8 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-63 rssi_max:-49
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-67 rssi_max:-60
said: 10 | 0x00000011 espnow unobserved predicted:-60 observed:-60
percept: 10 | 0x00000011 | link_stable | espnow | ? | -
said: 11 | 0x00000012 espnow met predicted:-45 observed:-45
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000200 ble met predicted:-59 observed:-59
percept: 15 | 0x00000200 | link_stable | ble | + | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-62 observed:-63
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON8397 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1257832 ±0 frame:7500
seq: 4684
follows: 0x00000010:1428 0x00000011:1373 0x00000012:1288 0x00000100:1021 0x00000200:2065
said: 1 | **ENTWIN** t_ms:1579576 stream:0xc9e0e898 wall:0 window_ms:600001 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 11 | **CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689,7236bc441422
said: 12 | **COVERED** windows:1 entities:8 window_ms:553840 first_t_ms:979575 last_t_ms:979575 covered_by:@LAT103LON8396
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91 windows:1
```

---

@LAT103LON3043 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1304177 ±0 frame:7500
seq: 4685
follows: 0x00000010:1429 0x00000011:1374 0x00000012:1288 0x00000100:1022 0x00000200:2066
said: 1 | **LINKWIN** t_ms:1625921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:73 rssi_min:-46 rssi_med:-45 rssi_max:-43
said: 3 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-64 rssi_med:-59 rssi_max:-53
said: 4 | **LINK** peer:0x00000011 proto:espnow n:153 rssi_min:-64 rssi_med:-59 rssi_max:-48
said: 5 | **LINK** peer:0x00000010 proto:ble n:52 rssi_min:-66 rssi_med:-62 rssi_max:-50
said: 6 | **LINK** peer:0x00000200 proto:espnow n:81 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 7 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-79 rssi_med:-56 rssi_max:-53
said: 8 | **LINK** peer:0x00000010 proto:espnow n:72 rssi_min:-52 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-77 rssi_med:-67 rssi_max:-60
said: 10 | 0x00000012 espnow met predicted:-45 observed:-45
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-59 observed:-59
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000012 ble met predicted:-56 observed:-56
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow unobserved predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | ? | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-63 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-67 observed:-67
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON3044 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1364177 ±0 frame:7500
seq: 4687
follows: 0x00000010:1430 0x00000011:1375 0x00000012:1290 0x00000100:1023 0x00000200:2067
said: 1 | **LINKWIN** t_ms:1685921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:138 rssi_min:-62 rssi_med:-58 rssi_max:-55
said: 3 | **LINK** peer:0x00000012 proto:espnow n:102 rssi_min:-48 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 5 | **LINK** peer:0x00000010 proto:espnow n:87 rssi_min:-50 rssi_med:-49 rssi_max:-47
said: 6 | **LINK** peer:0x00000200 proto:espnow n:140 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 7 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-79 rssi_med:-66 rssi_max:-59
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-79 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-80 rssi_med:-56 rssi_max:-53
said: 10 | 0x00000012 espnow met predicted:-45 observed:-45
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-59 observed:-59
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000011 espnow met predicted:-59 observed:-58
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble unobserved predicted:-62 observed:-62
percept: 13 | 0x00000010 | link_stable | ble | ? | -
said: 14 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-56 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-49
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-67 observed:-66
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON3045 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1424177 ±0 frame:7500
seq: 4689
follows: 0x00000010:1431 0x00000011:1376 0x00000012:1291 0x00000100:1024 0x00000200:2068
said: 1 | **LINKWIN** t_ms:1745921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-80 rssi_med:-58 rssi_max:-53
said: 3 | **LINK** peer:0x00000012 proto:espnow n:101 rssi_min:-47 rssi_med:-45 rssi_max:-39
said: 4 | **LINK** peer:0x00000011 proto:espnow n:102 rssi_min:-67 rssi_med:-58 rssi_max:-47
said: 5 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-74 rssi_med:-62 rssi_max:-50
said: 6 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-83 rssi_med:-58 rssi_max:-51
said: 7 | **LINK** peer:0x00000200 proto:espnow n:130 rssi_min:-45 rssi_med:-41 rssi_max:-35
said: 8 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-83 rssi_med:-67 rssi_max:-59
said: 9 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-31 rssi_med:-29 rssi_max:-27
said: 10 | 0x00000011 espnow met predicted:-58 observed:-58
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000012 espnow met predicted:-45 observed:-45
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow unobserved predicted:-49 observed:-49
percept: 13 | 0x00000010 | link_stable | espnow | ? | -
said: 14 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-66 observed:-67
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-59 observed:-58
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-56 observed:-58
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON3046 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1484177 ±0 frame:7500
seq: 4691
follows: 0x00000010:1432 0x00000011:1377 0x00000012:1292 0x00000100:1025 0x00000200:2069
said: 1 | **LINKWIN** t_ms:1805921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:92 rssi_min:-50 rssi_med:-44 rssi_max:-39
said: 3 | **LINK** peer:0x00000010 proto:espnow n:112 rssi_min:-54 rssi_med:-48 rssi_max:-43
said: 4 | **LINK** peer:0x00000011 proto:espnow n:124 rssi_min:-67 rssi_med:-57 rssi_max:-48
said: 5 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-68 rssi_med:-60 rssi_max:-49
said: 6 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 7 | **LINK** peer:0x00000200 proto:espnow n:87 rssi_min:-49 rssi_med:-42 rssi_max:-40
said: 8 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-82 rssi_med:-59 rssi_max:-53
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-83 rssi_med:-66 rssi_max:-59
said: 10 | 0x00000012 ble met predicted:-58 observed:-59
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000012 espnow met predicted:-45 observed:-44
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-58 observed:-57
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-62 observed:-60
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000200 ble unobserved predicted:-58 observed:-58
percept: 14 | 0x00000200 | link_stable | ble | ? | -
said: 15 | 0x00000200 espnow met predicted:-41 observed:-42
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-67 observed:-66
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 17 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT106LON180 | created:0 | updated:0

**BAR** frame:7500 bar:2 own:10 held:40 terms:9 digest:0x4d262fda settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1418 hi:1427 sum:14225
**HOLDS** agent:0x00000011 n:10 lo:1362 hi:1371 sum:13665
**HOLDS** agent:0x00000012 n:10 lo:1277 hi:1287 sum:12821
**HOLDS** agent:0x00000200 n:10 lo:2055 hi:2064 sum:20595
**HOLDS** agent:0x00000300 n:10 lo:4662 hi:4680 sum:46710
**DELIVER** up_s:1466 heap:11780 fetched:131 unanswered:64 broken:21 resumed:375 empty:30 served:433 wants:541 early:42 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:4 split:1
**SPLIT** agent:0x00000012 grammar:0xaf98ac36

---

@LAT103LON3047 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1544177 ±0 frame:7500
seq: 4693
follows: 0x00000010:1433 0x00000011:1378 0x00000012:1294 0x00000100:1026 0x00000200:2070
said: 1 | **LINKWIN** t_ms:1865921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-62 rssi_max:-49
said: 3 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-53 rssi_med:-47 rssi_max:-43
said: 4 | **LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-50 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000011 proto:espnow n:78 rssi_min:-69 rssi_med:-63 rssi_max:-50
said: 7 | **LINK** peer:0x00000011 proto:ble n:52 rssi_min:-83 rssi_med:-63 rssi_max:-58
said: 8 | **LINK** peer:0x00000200 proto:espnow n:109 rssi_min:-48 rssi_med:-45 rssi_max:-41
said: 9 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-80 rssi_med:-58 rssi_max:-55
said: 10 | 0x00000012 espnow met predicted:-44 observed:-47
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-48 observed:-47
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-57 observed:-63
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000010 ble met predicted:-60 observed:-62
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-42 observed:-45
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-59 observed:-58
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-66 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON3048 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1604177 ±0 frame:7500
seq: 4695
follows: 0x00000010:1434 0x00000011:1379 0x00000012:1295 0x00000100:1027 0x00000200:2071
said: 1 | **LINKWIN** t_ms:1925921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-48 rssi_med:-47 rssi_max:-45
said: 3 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-60 rssi_max:-54
said: 4 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-81 rssi_med:-58 rssi_max:-55
said: 5 | **LINK** peer:0x00000011 proto:espnow n:117 rssi_min:-68 rssi_med:-64 rssi_max:-60
said: 6 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000200 proto:espnow n:73 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-62 rssi_max:-50
said: 9 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-81 rssi_med:-63 rssi_max:-58
said: 10 | 0x00000010 ble met predicted:-62 observed:-62
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 11 | 0x00000012 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow unobserved predicted:-47 observed:-47
percept: 13 | 0x00000010 | link_stable | espnow | ? | -
said: 14 | 0x00000011 espnow met predicted:-63 observed:-64
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-63 observed:-63
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 16 | 0x00000200 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-58 observed:-58
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON3049 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1664177 ±0 frame:7500
seq: 4697
follows: 0x00000010:1435 0x00000011:1380 0x00000012:1296 0x00000100:1028 0x00000200:2072
said: 1 | **LINKWIN** t_ms:1985921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:91 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 3 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-83 rssi_med:-62 rssi_max:-50
said: 5 | **LINK** peer:0x00000011 proto:espnow n:60 rssi_min:-68 rssi_med:-63 rssi_max:-61
said: 6 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000010 proto:espnow n:169 rssi_min:-50 rssi_med:-48 rssi_max:-47
said: 8 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-60 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-64 rssi_med:-58 rssi_max:-56
said: 10 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-60 observed:-60
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000012 ble met predicted:-58 observed:-58
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000011 espnow met predicted:-64 observed:-63
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-62 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000011 ble unobserved predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | ? | -
```

---

@LAT103LON3050 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1724177 ±0 frame:7500
seq: 4699
follows: 0x00000010:1436 0x00000011:1381 0x00000012:1296 0x00000100:1029 0x00000200:2073
said: 1 | **LINKWIN** t_ms:2045921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-47 rssi_med:-47 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-29 rssi_med:-29 rssi_max:-29
said: 4 | **LINK** peer:0x00000011 proto:espnow n:136 rssi_min:-68 rssi_med:-63 rssi_max:-61
said: 5 | **LINK** peer:0x00000200 proto:espnow n:94 rssi_min:-46 rssi_med:-45 rssi_max:-42
said: 6 | **LINK** peer:0x00000200 proto:ble n:73 rssi_min:-64 rssi_med:-60 rssi_max:-54
said: 7 | **LINK** peer:0x00000010 proto:espnow n:78 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:ble n:45 rssi_min:-64 rssi_med:-58 rssi_max:-51
said: 9 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-66 rssi_med:-62 rssi_max:-50
said: 10 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 10 | 0x00000012 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 ble met predicted:-62 observed:-62
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000011 espnow met predicted:-63 observed:-63
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-48 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-60 observed:-60
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-58 observed:-58
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON3051 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1784177 ±0 frame:7500
seq: 4701
follows: 0x00000010:1437 0x00000011:1382 0x00000012:1298 0x00000100:1030 0x00000200:2074
said: 1 | **LINKWIN** t_ms:2105921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 3 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-64 rssi_max:-57
said: 4 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-64 rssi_med:-60 rssi_max:-54
said: 5 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-69 rssi_med:-61 rssi_max:-50
said: 6 | **LINK** peer:0x00000200 proto:espnow n:82 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000011 proto:espnow n:158 rssi_min:-68 rssi_med:-63 rssi_max:-61
said: 9 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-80 rssi_med:-57 rssi_max:-53
said: 10 | 0x00000012 espnow unobserved predicted:-47 observed:-47
percept: 10 | 0x00000012 | link_stable | espnow | ? | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-63 observed:-63
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-60 observed:-60
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-58 observed:-57
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-62 observed:-61
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON3052 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1844177 ±0 frame:7500
seq: 4703
follows: 0x00000010:1439 0x00000011:1383 0x00000012:1299 0x00000100:1031 0x00000200:2075
said: 1 | **LINKWIN** t_ms:2165921 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 3 | **LINK** peer:0x00000200 proto:espnow n:126 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000010 proto:espnow n:129 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000012 proto:espnow n:120 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 6 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-62 rssi_med:-57 rssi_max:-53
said: 7 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-62 rssi_max:-49
said: 8 | **LINK** peer:0x00000011 proto:ble n:49 rssi_min:-78 rssi_med:-63 rssi_max:-58
said: 9 | **LINK** peer:0x00000200 proto:ble n:52 rssi_min:-82 rssi_med:-60 rssi_max:-54
said: 10 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000011 ble met predicted:-64 observed:-63
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000200 ble met predicted:-60 observed:-60
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000010 ble met predicted:-61 observed:-62
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000011 espnow unobserved predicted:-63 observed:-63
percept: 16 | 0x00000011 | link_stable | espnow | ? | -
said: 17 | 0x00000012 ble met predicted:-57 observed:-57
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON8398 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1857831 ±0 frame:7500
seq: 4705
follows: 0x00000010:1439 0x00000011:1383 0x00000012:1299 0x00000100:1032 0x00000200:2076
said: 1 | **ENTWIN** t_ms:2179575 stream:0xc9e0e898 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-79
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-89
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,5203cfd1b904,bc102f237ace,e6b32d2cea8b,0283cce0e689,5ce28c488e0c,7236bc441422
```

---

@LAT103LON3053 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1908250 ±0 frame:7500
seq: 4706
follows: 0x00000010:1440 0x00000011:1384 0x00000012:1300 0x00000100:1034 0x00000200:2076
said: 1 | **LINKWIN** t_ms:2229994 stream:0xc9e0e898 wall:0 window_ms:64073
said: 2 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-62 rssi_max:-50
said: 3 | **LINK** peer:0x00000011 proto:espnow n:115 rssi_min:-68 rssi_med:-63 rssi_max:-61
said: 4 | **LINK** peer:0x00000010 proto:espnow n:96 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 5 | **LINK** peer:0x00000200 proto:espnow n:113 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000012 proto:espnow n:59 rssi_min:-47 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-64 rssi_max:-58
said: 8 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-79 rssi_med:-60 rssi_max:-54
said: 9 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 10 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-47 observed:-48
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000012 espnow met predicted:-46 observed:-47
percept: 13 | 0x00000012 | link_stable | espnow | + | -
said: 14 | 0x00000012 ble unobserved predicted:-57 observed:-57
percept: 14 | 0x00000012 | link_stable | ble | ? | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-62
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-64
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-60 observed:-60
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON16518 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 1908250 ±0 frame:7500
seq: 4707
follows: 0x00000010:1440 0x00000011:1384 0x00000012:1300 0x00000100:1034 0x00000200:2076
said: 1 | **MOTIONWIN** t_ms:2229994 stream:0xc9e0e898 wall:0 window_ms:64073 n:983
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:6 dev_max_mg:10 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27525 window_ms:1740186 moving_permille:0 dev_mean_mg:6 dev_max_mg:13 moving_ms:0 first_t_ms:485735 last_t_ms:2165921 covered_by:@LAT103LON16517
```

---

@LAT103LON3054 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 1968250 ±0 frame:7500
seq: 4709
follows: 0x00000010:1441 0x00000011:1385 0x00000012:1300 0x00000100:1035 0x00000200:2077
said: 1 | **LINKWIN** t_ms:2289994 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 3 | **LINK** peer:0x00000200 proto:espnow n:85 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-78 rssi_med:-60 rssi_max:-54
said: 5 | **LINK** peer:0x00000011 proto:espnow n:119 rssi_min:-68 rssi_med:-63 rssi_max:-61
said: 6 | **LINK** peer:0x00000010 proto:espnow n:107 rssi_min:-51 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-62 rssi_max:-49
said: 8 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-77 rssi_med:-63 rssi_max:-58
said: 9 | **LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 10 | 0x00000010 ble met predicted:-62 observed:-62
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000011 espnow met predicted:-63 observed:-63
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-48 observed:-47
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-64 observed:-63
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-60 observed:-60
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 17 | 0x00000100 | link_stable | espnow | + | -
```

---

@LAT103LON3055 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2028250 ±0 frame:7500
seq: 4711
follows: 0x00000010:1442 0x00000011:1386 0x00000012:1300 0x00000100:1036 0x00000200:2078
said: 1 | **LINKWIN** t_ms:2349994 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-64 rssi_med:-60 rssi_max:-54
said: 3 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 4 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-78 rssi_med:-63 rssi_max:-58
said: 5 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000010 proto:espnow n:75 rssi_min:-50 rssi_med:-47 rssi_max:-47
said: 7 | **LINK** peer:0x00000011 proto:espnow n:163 rssi_min:-67 rssi_med:-62 rssi_max:-60
said: 8 | **LINK** peer:0x00000010 proto:ble n:53 rssi_min:-66 rssi_med:-62 rssi_max:-50
said: 9 | **LINK** peer:0x00000012 proto:espnow n:35 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 10 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-60 observed:-60
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000011 espnow met predicted:-63 observed:-62
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-62
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-63
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000012 espnow met predicted:-47 observed:-46
percept: 17 | 0x00000012 | link_stable | espnow | + | -
```

---

@LAT103LON3056 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2088250 ±0 frame:7500
seq: 4713
follows: 0x00000010:1443 0x00000011:1387 0x00000012:1302 0x00000100:1037 0x00000200:2079
said: 1 | **LINKWIN** t_ms:2409994 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:99 rssi_min:-54 rssi_med:-47 rssi_max:-44
said: 3 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000011 proto:espnow n:111 rssi_min:-70 rssi_med:-62 rssi_max:-51
said: 5 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-50 rssi_med:-45 rssi_max:-41
said: 6 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-60 rssi_max:-54
said: 7 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-67 rssi_med:-59 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-62 rssi_max:-50
said: 9 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-63 rssi_max:-58
said: 10 | 0x00000200 ble met predicted:-60 observed:-60
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000011 ble met predicted:-63 observed:-63
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-62 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000012 espnow unobserved predicted:-46 observed:-46
percept: 17 | 0x00000012 | link_stable | espnow | ? | -
```

---

@LAT106LON181 | created:0 | updated:0

**BAR** frame:7500 bar:3 own:10 held:39 terms:9 digest:0xcd88d703 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1429 hi:1438 sum:14335
**HOLDS** agent:0x00000011 n:10 lo:1373 hi:1382 sum:13775
**HOLDS** agent:0x00000012 n:9 lo:1288 hi:1297 sum:11633
**HOLDS** agent:0x00000200 n:10 lo:2065 hi:2075 sum:20704
**HOLDS** agent:0x00000300 n:10 lo:4682 hi:4701 sum:46919
**DELIVER** up_s:2068 heap:11280 fetched:168 unanswered:87 broken:26 resumed:488 empty:43 served:580 wants:729 early:42 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON3057 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2148250 ±0 frame:7500
seq: 4715
follows: 0x00000010:1444 0x00000011:1388 0x00000012:1302 0x00000100:1038 0x00000200:2080
said: 1 | **LINKWIN** t_ms:2469994 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-31 rssi_med:-29 rssi_max:-28
said: 3 | **LINK** peer:0x00000200 proto:espnow n:96 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000012 proto:espnow n:71 rssi_min:-48 rssi_med:-47 rssi_max:-45
said: 5 | **LINK** peer:0x00000011 proto:espnow n:78 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 6 | **LINK** peer:0x00000010 proto:espnow n:91 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-82 rssi_med:-61 rssi_max:-52
said: 8 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-63 rssi_max:-58
said: 9 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-81 rssi_med:-60 rssi_max:-54
said: 10 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 10 | 0x00000010 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-60 observed:-60
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-59 observed:-61
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 ble unobserved predicted:-62 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | ? | -
said: 17 | 0x00000011 ble met predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON3058 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2208250 ±0 frame:7500
seq: 4717
follows: 0x00000010:1445 0x00000011:1389 0x00000012:1303 0x00000100:1039 0x00000200:2081
said: 1 | **LINKWIN** t_ms:2529994 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:73 rssi_min:-81 rssi_med:-60 rssi_max:-54
said: 3 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-81 rssi_med:-64 rssi_max:-58
said: 4 | **LINK** peer:0x00000100 proto:espnow n:62 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000011 proto:espnow n:101 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 6 | **LINK** peer:0x00000200 proto:espnow n:159 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:espnow n:114 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:espnow n:63 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-61 rssi_max:-52
said: 10 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000012 espnow met predicted:-47 observed:-47
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-61 observed:-61
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-64
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-60 observed:-60
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON3059 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2268250 ±0 frame:7500
seq: 4719
follows: 0x00000010:1446 0x00000011:1390 0x00000012:1304 0x00000100:1040 0x00000200:2082
said: 1 | **LINKWIN** t_ms:2589994 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 3 | **LINK** peer:0x00000012 proto:ble n:68 rssi_min:-62 rssi_med:-56 rssi_max:-52
said: 4 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-81 rssi_med:-62 rssi_max:-50
said: 5 | **LINK** peer:0x00000011 proto:ble n:68 rssi_min:-81 rssi_med:-63 rssi_max:-58
said: 6 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 8 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-65 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000011 proto:espnow n:102 rssi_min:-65 rssi_med:-62 rssi_max:-59
said: 10 | 0x00000200 ble met predicted:-60 observed:-59
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-64 observed:-63
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 espnow unobserved predicted:-47 observed:-47
percept: 16 | 0x00000012 | link_stable | espnow | ? | -
said: 17 | 0x00000012 ble met predicted:-61 observed:-56
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON3060 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2328250 ±0 frame:7500
seq: 4721
follows: 0x00000010:1447 0x00000011:1391 0x00000012:1305 0x00000100:1041 0x00000200:2083
said: 1 | **LINKWIN** t_ms:2649994 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:128 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-29 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-80 rssi_med:-61 rssi_max:-52
said: 6 | **LINK** peer:0x00000010 proto:espnow n:107 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-66 rssi_med:-62 rssi_max:-50
said: 8 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-80 rssi_med:-64 rssi_max:-58
said: 9 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-59 rssi_max:-54
said: 10 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 10 | 0x00000010 | link_stable | espnow | + | -
said: 11 | 0x00000012 ble met predicted:-56 observed:-61
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-62 observed:-62
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000011 ble met predicted:-63 observed:-64
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 15 | 0x00000100 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-59 observed:-59
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON3061 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2388250 ±0 frame:7500
seq: 4723
follows: 0x00000010:1448 0x00000011:1393 0x00000012:1306 0x00000100:1042 0x00000200:2084
said: 1 | **LINKWIN** t_ms:2709994 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-65 rssi_med:-61 rssi_max:-59
said: 3 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-29 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:espnow n:126 rssi_min:-46 rssi_med:-45 rssi_max:-42
said: 5 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 6 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-49 rssi_med:-47 rssi_max:-45
said: 7 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-61 rssi_med:-56 rssi_max:-52
said: 8 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-82 rssi_med:-63 rssi_max:-58
said: 9 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-82 rssi_med:-62 rssi_max:-50
said: 10 | 0x00000011 espnow met predicted:-62 observed:-61
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-61 observed:-56
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-62
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-64 observed:-63
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-59 observed:-59
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON3062 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2448250 ±0 frame:7500
seq: 4725
follows: 0x00000010:1449 0x00000011:1394 0x00000012:1307 0x00000100:1044 0x00000200:2085
said: 1 | **LINKWIN** t_ms:2769994 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:150 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-62 rssi_max:-49
said: 4 | **LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-29 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000200 proto:espnow n:112 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-65 rssi_med:-60 rssi_max:-54
said: 7 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-81 rssi_med:-63 rssi_max:-58
said: 8 | **LINK** peer:0x00000010 proto:espnow n:70 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000012 proto:ble n:51 rssi_min:-81 rssi_med:-56 rssi_max:-52
said: 10 | 0x00000011 espnow met predicted:-61 observed:-62
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-59 observed:-60
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-56 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-63
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-62 observed:-62
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON3063 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2508250 ±0 frame:7500
seq: 4727
follows: 0x00000010:1450 0x00000011:1395 0x00000012:1308 0x00000100:1045 0x00000200:2086
said: 1 | **LINKWIN** t_ms:2829994 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-62 rssi_max:-50
said: 3 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000200 proto:ble n:53 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 6 | **LINK** peer:0x00000011 proto:espnow n:74 rssi_min:-64 rssi_med:-61 rssi_max:-59
said: 7 | **LINK** peer:0x00000010 proto:espnow n:104 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 9 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-80 rssi_med:-60 rssi_max:-52
said: 10 | 0x00000011 espnow met predicted:-62 observed:-61
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000010 ble met predicted:-62 observed:-62
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-60 observed:-59
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000011 ble met predicted:-63 observed:-63
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000012 ble met predicted:-56 observed:-60
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON3064 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2568251 ±0 frame:7500
seq: 4729
follows: 0x00000010:1451 0x00000011:1396 0x00000012:1309 0x00000100:1046 0x00000200:2087
said: 1 | **LINKWIN** t_ms:2889995 stream:0xc9e0e898 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-65 rssi_med:-59 rssi_max:-54
said: 3 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-61 rssi_med:-56 rssi_max:-52
said: 4 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-61 rssi_max:-50
said: 5 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 6 | **LINK** peer:0x00000200 proto:espnow n:112 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:espnow n:111 rssi_min:-49 rssi_med:-47 rssi_max:-44
said: 8 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 9 | **LINK** peer:0x00000011 proto:ble n:56 rssi_min:-79 rssi_med:-63 rssi_max:-58
said: 10 | 0x00000010 ble met predicted:-62 observed:-61
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-59 observed:-59
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-61 observed:-62
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-63
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-60 observed:-56
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON3065 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2628251 ±0 frame:7500
seq: 4731
follows: 0x00000010:1452 0x00000011:1397 0x00000012:1310 0x00000100:1047 0x00000200:2088
said: 1 | **LINKWIN** t_ms:2949995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:70 rssi_min:-78 rssi_med:-56 rssi_max:-52
said: 3 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-63 rssi_max:-58
said: 4 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000200 proto:espnow n:107 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 7 | **LINK** peer:0x00000010 proto:espnow n:118 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-66 rssi_med:-61 rssi_max:-50
said: 9 | **LINK** peer:0x00000200 proto:ble n:74 rssi_min:-80 rssi_med:-59 rssi_max:-54
said: 10 | 0x00000200 ble met predicted:-59 observed:-59
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000012 ble met predicted:-56 observed:-56
percept: 11 | 0x00000012 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-61 observed:-61
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON3066 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2688251 ±0 frame:7500
seq: 4733
follows: 0x00000010:1453 0x00000011:1398 0x00000012:1311 0x00000100:1048 0x00000200:2089
said: 1 | **LINKWIN** t_ms:3009995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-29 rssi_med:-28 rssi_max:-28
said: 3 | **LINK** peer:0x00000200 proto:espnow n:131 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-64 rssi_med:-59 rssi_max:-54
said: 5 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 6 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-61 rssi_max:-50
said: 7 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-80 rssi_med:-56 rssi_max:-51
said: 8 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-50 rssi_med:-47 rssi_max:-45
said: 9 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-65 rssi_med:-61 rssi_max:-59
said: 10 | 0x00000012 ble met predicted:-56 observed:-56
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-63 observed:-63
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-28
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-62 observed:-61
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-61 observed:-61
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-59 observed:-59
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT106LON182 | created:0 | updated:0

**BAR** frame:7500 bar:4 own:10 held:38 terms:9 digest:0xc9a9ac56 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1440 hi:1449 sum:14445
**HOLDS** agent:0x00000011 n:10 lo:1383 hi:1392 sum:13875
**HOLDS** agent:0x00000012 n:8 lo:1299 hi:1307 sum:10425
**HOLDS** agent:0x00000200 n:10 lo:2076 hi:2085 sum:20805
**HOLDS** agent:0x00000300 n:10 lo:4703 hi:4723 sum:47137
**DELIVER** up_s:2672 heap:12020 fetched:208 unanswered:105 broken:35 resumed:624 empty:54 served:750 wants:937 early:42 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON3067 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2748251 ±0 frame:7500
seq: 4735
follows: 0x00000010:1454 0x00000011:1399 0x00000012:1312 0x00000100:1049 0x00000200:2090
said: 1 | **LINKWIN** t_ms:3069995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-29 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000011 proto:espnow n:81 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 5 | **LINK** peer:0x00000200 proto:espnow n:83 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-79 rssi_med:-63 rssi_max:-58
said: 7 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-56 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-66 rssi_med:-61 rssi_max:-50
said: 9 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 10 | 0x00000100 espnow met predicted:-28 observed:-29
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000200 ble met predicted:-59 observed:-59
percept: 12 | 0x00000200 | link_stable | ble | + | -
said: 13 | 0x00000011 ble met predicted:-63 observed:-63
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-61 observed:-61
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-56 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000011 espnow met predicted:-61 observed:-62
percept: 17 | 0x00000011 | link_stable | espnow | + | -
```

---

@LAT103LON3068 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2808251 ±0 frame:7500
seq: 4737
follows: 0x00000010:1455 0x00000011:1400 0x00000012:1313 0x00000100:1050 0x00000200:2091
said: 1 | **LINKWIN** t_ms:3129995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:112 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000011 proto:espnow n:131 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 5 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-29 rssi_med:-29 rssi_max:-28
said: 6 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-62 rssi_max:-50
said: 7 | **LINK** peer:0x00000010 proto:espnow n:77 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:51 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 10 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 10 | 0x00000010 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 ble met predicted:-63 observed:-63
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-56 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-61 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-59 observed:-59
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON3069 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2868251 ±0 frame:7500
seq: 4739
follows: 0x00000010:1456 0x00000011:1401 0x00000012:1314 0x00000100:1051 0x00000200:2092
said: 1 | **LINKWIN** t_ms:3189995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:104 rssi_min:-46 rssi_med:-45 rssi_max:-45
said: 3 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-29 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000011 proto:espnow n:87 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 5 | **LINK** peer:0x00000200 proto:ble n:67 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 6 | **LINK** peer:0x00000011 proto:ble n:64 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 7 | **LINK** peer:0x00000010 proto:espnow n:107 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-61 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-61 rssi_max:-50
said: 10 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-59 observed:-59
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000010 ble met predicted:-62 observed:-61
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-61
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON3070 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2928251 ±0 frame:7500
seq: 4741
follows: 0x00000010:1457 0x00000011:1402 0x00000012:1315 0x00000100:1052 0x00000200:2093
said: 1 | **LINKWIN** t_ms:3249995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-65 rssi_med:-59 rssi_max:-54
said: 3 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-79 rssi_med:-63 rssi_max:-58
said: 4 | **LINK** peer:0x00000011 proto:espnow n:90 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 5 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 6 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-80 rssi_med:-60 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:espnow n:97 rssi_min:-48 rssi_med:-47 rssi_max:-46
said: 10 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-59 observed:-59
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000011 ble met predicted:-63 observed:-63
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-61 observed:-60
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble unobserved predicted:-61 observed:-61
percept: 17 | 0x00000010 | link_stable | ble | ? | -
```

---

@LAT103LON27438 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 2928251 ±0 frame:7500
seq: 4742
follows: 0x00000010:1457 0x00000011:1402 0x00000012:1315 0x00000100:1052 0x00000200:2093
said: 1 | **ACOUSTICWIN** t_ms:3249995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3681 rate:8000
said: 2 | **ACOUSTIC** rms_mean:111 rms_max:935 peak:1921 transients:1
said: 3 | **TRANSIENT** t_ms:3248680 stream:0xc9e0e898 wall:0 rms:935
```

---

@LAT103LON3071 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 2988251 ±0 frame:7500
seq: 4743
follows: 0x00000010:1458 0x00000011:1403 0x00000012:1316 0x00000100:1053 0x00000200:2094
said: 1 | **LINKWIN** t_ms:3309995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:113 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:espnow n:119 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 4 | **LINK** peer:0x00000200 proto:espnow n:102 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-29 rssi_med:-29 rssi_max:-28
said: 6 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-61 rssi_max:-50
said: 7 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-81 rssi_med:-56 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-79 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-63 rssi_max:-58
said: 10 | 0x00000200 ble met predicted:-59 observed:-59
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-63 observed:-63
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-60 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000012 espnow unobserved predicted:-47 observed:-47
percept: 17 | 0x00000012 | link_stable | espnow | ? | -
```

---

@LAT103LON27439 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 2988251 ±0 frame:7500
seq: 4744
follows: 0x00000010:1458 0x00000011:1403 0x00000012:1316 0x00000100:1053 0x00000200:2094
said: 1 | **ACOUSTICWIN** t_ms:3309995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3439 rate:8000
said: 2 | **ACOUSTIC** rms_mean:116 rms_max:940 peak:1466 transients:1
said: 3 | **TRANSIENT** t_ms:3304603 stream:0xc9e0e898 wall:0 rms:940
```

---

@LAT103LON3072 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3048251 ±0 frame:7500
seq: 4745
follows: 0x00000010:1459 0x00000011:1404 0x00000012:1317 0x00000100:1055 0x00000200:2095
said: 1 | **LINKWIN** t_ms:3369995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-29 rssi_med:-29 rssi_max:-28
said: 3 | **LINK** peer:0x00000011 proto:espnow n:143 rssi_min:-65 rssi_med:-62 rssi_max:-59
said: 4 | **LINK** peer:0x00000200 proto:espnow n:135 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-79 rssi_med:-63 rssi_max:-58
said: 6 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-50 rssi_med:-47 rssi_max:-45
said: 7 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-61 rssi_med:-56 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-80 rssi_med:-62 rssi_max:-49
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-65 rssi_med:-59 rssi_max:-54
said: 10 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000010 ble met predicted:-61 observed:-62
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-56 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-59 observed:-59
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON27440 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3048251 ±0 frame:7500
seq: 4746
follows: 0x00000010:1459 0x00000011:1404 0x00000012:1317 0x00000100:1055 0x00000200:2095
said: 1 | **ACOUSTICWIN** t_ms:3369995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3686 rate:8000
said: 2 | **ACOUSTIC** rms_mean:109 rms_max:357 peak:605 transients:0
```

---

@LAT103LON3073 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3108251 ±0 frame:7500
seq: 4747
follows: 0x00000010:1460 0x00000011:1405 0x00000012:1318 0x00000100:1056 0x00000200:2096
said: 1 | **LINKWIN** t_ms:3429995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-82 rssi_med:-56 rssi_max:-52
said: 3 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-65 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-62 rssi_max:-50
said: 5 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 6 | **LINK** peer:0x00000200 proto:espnow n:65 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:espnow n:81 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000011 proto:espnow n:101 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 9 | **LINK** peer:0x00000011 proto:ble n:45 rssi_min:-79 rssi_med:-63 rssi_max:-58
said: 10 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 ble met predicted:-63 observed:-63
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-56 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-62 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000200 ble met predicted:-59 observed:-59
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON27441 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3108251 ±0 frame:7500
seq: 4748
follows: 0x00000010:1460 0x00000011:1405 0x00000012:1318 0x00000100:1056 0x00000200:2096
said: 1 | **ACOUSTICWIN** t_ms:3429995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3671 rate:8000
said: 2 | **ACOUSTIC** rms_mean:316 rms_max:1304 peak:1920 transients:0
```

---

@LAT103LON3074 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3168251 ±0 frame:7500
seq: 4749
follows: 0x00000010:1461 0x00000011:1406 0x00000012:1319 0x00000100:1057 0x00000200:2097
said: 1 | **LINKWIN** t_ms:3489995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-62 rssi_max:-50
said: 3 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-80 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-61 rssi_max:-52
said: 5 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-78 rssi_med:-63 rssi_max:-58
said: 6 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 7 | **LINK** peer:0x00000011 proto:espnow n:78 rssi_min:-65 rssi_med:-63 rssi_max:-60
said: 8 | **LINK** peer:0x00000010 proto:espnow n:96 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000200 proto:espnow n:60 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 10 | 0x00000012 ble met predicted:-56 observed:-61
percept: 10 | 0x00000012 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-59 observed:-59
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-62 observed:-62
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000011 espnow met predicted:-62 observed:-63
percept: 16 | 0x00000011 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON27442 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3168251 ±0 frame:7500
seq: 4750
follows: 0x00000010:1461 0x00000011:1406 0x00000012:1319 0x00000100:1057 0x00000200:2097
said: 1 | **ACOUSTICWIN** t_ms:3489995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3673 rate:8000
said: 2 | **ACOUSTIC** rms_mean:105 rms_max:416 peak:704 transients:0
```

---

@LAT103LON3075 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3228251 ±0 frame:7500
seq: 4751
follows: 0x00000010:1462 0x00000011:1407 0x00000012:1320 0x00000100:1058 0x00000200:2098
said: 1 | **LINKWIN** t_ms:3549995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-29 rssi_med:-29 rssi_max:-28
said: 3 | **LINK** peer:0x00000010 proto:espnow n:86 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 4 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 5 | **LINK** peer:0x00000012 proto:ble n:65 rssi_min:-79 rssi_med:-56 rssi_max:-52
said: 6 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-62 rssi_max:-50
said: 7 | **LINK** peer:0x00000200 proto:espnow n:168 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-82 rssi_med:-64 rssi_max:-57
said: 10 | 0x00000010 ble met predicted:-62 observed:-62
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-59 observed:-59
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000012 ble met predicted:-61 observed:-56
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000011 ble met predicted:-63 observed:-64
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-63 observed:-62
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON27443 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3228251 ±0 frame:7500
seq: 4752
follows: 0x00000010:1462 0x00000011:1407 0x00000012:1320 0x00000100:1058 0x00000200:2098
said: 1 | **ACOUSTICWIN** t_ms:3549995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3675 rate:8000
said: 2 | **ACOUSTIC** rms_mean:102 rms_max:238 peak:446 transients:0
```

---

@LAT103LON3076 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3288251 ±0 frame:7500
seq: 4753
follows: 0x00000010:1463 0x00000011:1408 0x00000012:1322 0x00000100:1059 0x00000200:2099
said: 1 | **LINKWIN** t_ms:3609995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:109 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000200 proto:espnow n:106 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 4 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-82 rssi_med:-60 rssi_max:-51
said: 6 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-82 rssi_med:-63 rssi_max:-58
said: 7 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-80 rssi_med:-62 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:espnow n:108 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 9 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-64 rssi_med:-59 rssi_max:-54
said: 10 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-47 observed:-48
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 12 | 0x00000011 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-56 observed:-60
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000010 ble met predicted:-62 observed:-62
percept: 14 | 0x00000010 | link_stable | ble | + | -
said: 15 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 15 | 0x00000200 | link_stable | espnow | + | -
said: 16 | 0x00000200 ble met predicted:-59 observed:-59
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-64 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON27444 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3288251 ±0 frame:7500
seq: 4754
follows: 0x00000010:1463 0x00000011:1408 0x00000012:1322 0x00000100:1059 0x00000200:2099
said: 1 | **ACOUSTICWIN** t_ms:3609995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3685 rate:8000
said: 2 | **ACOUSTIC** rms_mean:113 rms_max:252 peak:495 transients:0
```

---

@LAT106LON183 | created:0 | updated:0

**BAR** frame:7500 bar:5 own:10 held:40 terms:9 digest:0xdd4d4ce8 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1450 hi:1459 sum:14545
**HOLDS** agent:0x00000011 n:10 lo:1394 hi:1403 sum:13985
**HOLDS** agent:0x00000012 n:10 lo:1308 hi:1317 sum:13125
**HOLDS** agent:0x00000200 n:10 lo:2086 hi:2095 sum:20905
**HOLDS** agent:0x00000300 n:10 lo:4725 hi:4743 sum:47340
**DELIVER** up_s:3269 heap:11776 fetched:248 unanswered:123 broken:41 resumed:744 empty:66 served:916 wants:1144 early:42 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON3077 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3348251 ±0 frame:7500
seq: 4755
follows: 0x00000010:1464 0x00000011:1409 0x00000012:1323 0x00000100:1060 0x00000200:2100
said: 1 | **LINKWIN** t_ms:3669995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:63 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 3 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-66 rssi_med:-62 rssi_max:-50
said: 5 | **LINK** peer:0x00000012 proto:ble n:64 rssi_min:-82 rssi_med:-60 rssi_max:-52
said: 6 | **LINK** peer:0x00000010 proto:espnow n:80 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000011 proto:espnow n:93 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 8 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-79 rssi_med:-63 rssi_max:-58
said: 9 | **LINK** peer:0x00000200 proto:espnow n:103 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 10 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 11 | 0x00000200 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-60 observed:-60
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000011 ble met predicted:-63 observed:-63
percept: 14 | 0x00000011 | link_stable | ble | + | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-62
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-48 observed:-47
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-59 observed:-59
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON27445 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3348251 ±0 frame:7500
seq: 4756
follows: 0x00000010:1464 0x00000011:1409 0x00000012:1323 0x00000100:1060 0x00000200:2100
said: 1 | **ACOUSTICWIN** t_ms:3669995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:2649 rate:8000
said: 2 | **ACOUSTIC** rms_mean:115 rms_max:300 peak:561 transients:0
```

---

@LAT103LON3078 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3408251 ±0 frame:7500
seq: 4757
follows: 0x00000010:1465 0x00000011:1410 0x00000012:1324 0x00000100:1061 0x00000200:2101
said: 1 | **LINKWIN** t_ms:3729995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-65 rssi_med:-61 rssi_max:-50
said: 3 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-78 rssi_med:-63 rssi_max:-58
said: 4 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-61 rssi_med:-60 rssi_max:-52
said: 5 | **LINK** peer:0x00000100 proto:espnow n:71 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 6 | **LINK** peer:0x00000200 proto:espnow n:87 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:espnow n:62 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 8 | **LINK** peer:0x00000010 proto:espnow n:116 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-65 rssi_med:-59 rssi_max:-54
said: 10 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000200 ble met predicted:-59 observed:-59
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000010 ble met predicted:-62 observed:-61
percept: 12 | 0x00000010 | link_stable | ble | + | -
said: 13 | 0x00000012 ble met predicted:-60 observed:-60
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-63
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON27446 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3408251 ±0 frame:7500
seq: 4758
follows: 0x00000010:1465 0x00000011:1410 0x00000012:1324 0x00000100:1061 0x00000200:2101
said: 1 | **ACOUSTICWIN** t_ms:3729995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3675 rate:8000
said: 2 | **ACOUSTIC** rms_mean:99 rms_max:251 peak:508 transients:0
```

---

@LAT103LON3079 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3468251 ±0 frame:7500
seq: 4759
follows: 0x00000010:1466 0x00000011:1411 0x00000012:1325 0x00000100:1062 0x00000200:2102
said: 1 | **LINKWIN** t_ms:3789995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:93 rssi_min:-47 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 4 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-61 rssi_med:-56 rssi_max:-52
said: 6 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-65 rssi_med:-59 rssi_max:-54
said: 7 | **LINK** peer:0x00000010 proto:espnow n:97 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 8 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-82 rssi_med:-61 rssi_max:-49
said: 9 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-79 rssi_med:-63 rssi_max:-57
said: 10 | 0x00000010 ble met predicted:-61 observed:-61
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000011 ble met predicted:-63 observed:-63
percept: 11 | 0x00000011 | link_stable | ble | + | -
said: 12 | 0x00000012 ble met predicted:-60 observed:-56
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-59 observed:-59
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON27447 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3468251 ±0 frame:7500
seq: 4760
follows: 0x00000010:1466 0x00000011:1411 0x00000012:1325 0x00000100:1062 0x00000200:2102
said: 1 | **ACOUSTICWIN** t_ms:3789995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3460 rate:8000
said: 2 | **ACOUSTIC** rms_mean:88 rms_max:187 peak:429 transients:0
```

---

@LAT103LON3080 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3528251 ±0 frame:7500
seq: 4761
follows: 0x00000010:1467 0x00000011:1412 0x00000012:1326 0x00000100:1063 0x00000200:2103
said: 1 | **LINKWIN** t_ms:3849995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 3 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-50 rssi_med:-47 rssi_max:-45
said: 4 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-57
said: 5 | **LINK** peer:0x00000200 proto:espnow n:119 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000011 proto:espnow n:83 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-62 rssi_max:-50
said: 8 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-83 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 10 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 11 | 0x00000011 | link_stable | espnow | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-56 observed:-56
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000200 ble met predicted:-59 observed:-59
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000010 ble met predicted:-61 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON27448 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3528251 ±0 frame:7500
seq: 4762
follows: 0x00000010:1467 0x00000011:1412 0x00000012:1326 0x00000100:1063 0x00000200:2103
said: 1 | **ACOUSTICWIN** t_ms:3849995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3680 rate:8000
said: 2 | **ACOUSTIC** rms_mean:115 rms_max:328 peak:619 transients:0
```

---

@LAT103LON3081 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3588251 ±0 frame:7500
seq: 4763
follows: 0x00000010:1468 0x00000011:1413 0x00000012:1327 0x00000100:1064 0x00000200:2104
said: 1 | **LINKWIN** t_ms:3909995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 3 | **LINK** peer:0x00000100 proto:espnow n:72 rssi_min:-29 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:espnow n:102 rssi_min:-46 rssi_med:-45 rssi_max:-41
said: 5 | **LINK** peer:0x00000011 proto:espnow n:70 rssi_min:-65 rssi_med:-62 rssi_max:-58
said: 6 | **LINK** peer:0x00000010 proto:espnow n:103 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 7 | **LINK** peer:0x00000012 proto:ble n:74 rssi_min:-82 rssi_med:-56 rssi_max:-52
said: 8 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 9 | **LINK** peer:0x00000010 proto:ble n:63 rssi_min:-66 rssi_med:-61 rssi_max:-50
said: 10 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 10 | 0x00000100 | link_stable | espnow | + | -
said: 11 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 11 | 0x00000010 | link_stable | espnow | + | -
said: 12 | 0x00000011 ble met predicted:-63 observed:-63
percept: 12 | 0x00000011 | link_stable | ble | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-61
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-59 observed:-59
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000012 ble met predicted:-56 observed:-56
percept: 17 | 0x00000012 | link_stable | ble | + | -
```

---

@LAT103LON27449 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3588251 ±0 frame:7500
seq: 4764
follows: 0x00000010:1468 0x00000011:1413 0x00000012:1327 0x00000100:1064 0x00000200:2104
said: 1 | **ACOUSTICWIN** t_ms:3909995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3446 rate:8000
said: 2 | **ACOUSTIC** rms_mean:101 rms_max:227 peak:652 transients:0
```

---

@LAT103LON3082 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3648251 ±0 frame:7500
seq: 4765
follows: 0x00000010:1469 0x00000011:1414 0x00000012:1328 0x00000100:1066 0x00000200:2105
said: 1 | **LINKWIN** t_ms:3969995 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:141 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-65 rssi_med:-61 rssi_max:-49
said: 4 | **LINK** peer:0x00000200 proto:espnow n:86 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000100 proto:espnow n:67 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 6 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-64 rssi_med:-59 rssi_max:-54
said: 7 | **LINK** peer:0x00000010 proto:espnow n:116 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 8 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-79 rssi_med:-63 rssi_max:-57
said: 10 | 0x00000200 ble met predicted:-59 observed:-59
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000010 espnow met predicted:-47 observed:-48
percept: 14 | 0x00000010 | link_stable | espnow | + | -
said: 15 | 0x00000012 ble met predicted:-56 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-63
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-61 observed:-61
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON27450 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3648251 ±0 frame:7500
seq: 4766
follows: 0x00000010:1469 0x00000011:1414 0x00000012:1328 0x00000100:1066 0x00000200:2105
said: 1 | **ACOUSTICWIN** t_ms:3969995 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3655 rate:8000
said: 2 | **ACOUSTIC** rms_mean:110 rms_max:226 peak:573 transients:0
```

---

@LAT103LON3083 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3708457 ±0 frame:7500
seq: 4767
follows: 0x00000010:1470 0x00000011:1415 0x00000012:1329 0x00000100:1068 0x00000200:2106
said: 1 | **LINKWIN** t_ms:4030201 stream:0xc9e0e898 wall:0 window_ms:60206
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 3 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-64 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000010 proto:espnow n:66 rssi_min:-49 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000200 proto:espnow n:63 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 7 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-82 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-82 rssi_med:-62 rssi_max:-49
said: 10 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000010 ble met predicted:-61 observed:-62
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 13 | 0x00000100 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-59 observed:-59
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000010 espnow met predicted:-48 observed:-47
percept: 15 | 0x00000010 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-63 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON16519 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3708457 ±0 frame:7500
seq: 4768
follows: 0x00000010:1470 0x00000011:1415 0x00000012:1329 0x00000100:1068 0x00000200:2106
said: 1 | **MOTIONWIN** t_ms:4030201 stream:0xc9e0e898 wall:0 window_ms:60206 n:923
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:27225 window_ms:1740001 moving_permille:0 dev_mean_mg:7 dev_max_mg:11 moving_ms:0 first_t_ms:2289994 last_t_ms:3969995 covered_by:@LAT103LON16518
```

---

@LAT103LON27451 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3708457 ±0 frame:7500
seq: 4769
follows: 0x00000010:1470 0x00000011:1415 0x00000012:1329 0x00000100:1068 0x00000200:2106
said: 1 | **ACOUSTICWIN** t_ms:4030201 stream:0xc9e0e898 wall:0 window_ms:60206 blocks:3444 rate:8000
said: 2 | **ACOUSTIC** rms_mean:122 rms_max:262 peak:512 transients:0
```

---

@LAT105LON5790 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3651591 ±21 frame:7500
seq: 1329
follows: 0x00000010:1469 0x00000011:1414 0x00000100:1065 0x00000200:2105 0x00000300:4764
said: 1 | **LINKWIN** t_ms:3973324 stream:0xc9e0e898 wall:0 window_ms:60033
said: 2 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 4 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000011 proto:espnow n:140 rssi_min:-43 rssi_med:-41 rssi_max:-36
said: 6 | **LINK** peer:0x00000300 proto:espnow n:180 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 7 | **LINK** peer:0x00000200 proto:espnow n:90 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-81 rssi_med:-51 rssi_max:-43
said: 9 | **LINK** peer:0x00000010 proto:espnow n:100 rssi_min:-36 rssi_med:-32 rssi_max:-31
```

---

@LAT105LON5791 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3650561 ±21 frame:7500
seq: 2106
follows: 0x00000010:1469 0x00000011:1414 0x00000012:1328 0x00000100:1066 0x00000300:4766
said: 1 | **LINKWIN** t_ms:3972300 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:140 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | **LINK** peer:0x00000300 proto:espnow n:185 rssi_min:-42 rssi_med:-40 rssi_max:-39
said: 5 | **LINK** peer:0x00000012 proto:espnow n:119 rssi_min:-33 rssi_med:-32 rssi_max:-32
said: 6 | **LINK** peer:0x00000010 proto:espnow n:90 rssi_min:-50 rssi_med:-47 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-81 rssi_med:-57 rssi_max:-50
```

---

@LAT105LON5792 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3661555 ±21 frame:7500
seq: 1470
follows: 0x00000011:1414 0x00000012:1329 0x00000100:1066 0x00000200:2106 0x00000300:4766
said: 1 | **LINKWIN** t_ms:3983322 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-58 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000200 proto:espnow n:63 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:espnow n:126 rssi_min:-45 rssi_med:-44 rssi_max:-42
said: 5 | **LINK** peer:0x00000012 proto:espnow n:77 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:116 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 7 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-49 rssi_med:-46 rssi_max:-39
said: 8 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-80 rssi_med:-52 rssi_max:-45
said: 9 | **LINK** peer:0x00000200 proto:ble n:59 rssi_min:-81 rssi_med:-58 rssi_max:-54
```

---

@LAT105LON5793 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3633008 ±21 frame:7500
seq: 1414
follows: 0x00000010:1469 0x00000012:1328 0x00000100:1064 0x00000200:2105 0x00000300:4764
said: 1 | **LINKWIN** t_ms:3954731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-63 rssi_max:-60
said: 3 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 4 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-70 rssi_med:-69 rssi_max:-68
said: 5 | **LINK** peer:0x00000300 proto:espnow n:151 rssi_min:-62 rssi_med:-59 rssi_max:-56
said: 6 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 7 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-80 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000012 proto:espnow n:104 rssi_min:-41 rssi_med:-35 rssi_max:-35
```

---

@LAT105LON5794 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3710561 ±21 frame:7500
seq: 2107
follows: 0x00000010:1470 0x00000011:1415 0x00000012:1329 0x00000100:1068 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4032301 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:57 rssi_min:-79 rssi_med:-49 rssi_max:-48
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-39 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000011 proto:espnow n:98 rssi_min:-47 rssi_med:-46 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:61 rssi_min:-48 rssi_med:-47 rssi_max:-47
said: 6 | **LINK** peer:0x00000300 proto:ble n:54 rssi_min:-82 rssi_med:-57 rssi_max:-50
said: 7 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-62
said: 8 | **LINK** peer:0x00000010 proto:ble n:50 rssi_min:-69 rssi_med:-63 rssi_max:-54
said: 9 | **LINK** peer:0x00000012 proto:espnow n:76 rssi_min:-33 rssi_med:-32 rssi_max:-32
```

---

@LAT103LON3084 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3768457 ±0 frame:7500
seq: 4770
follows: 0x00000010:1471 0x00000011:1416 0x00000012:1330 0x00000100:1069 0x00000200:2107
said: 1 | **LINKWIN** t_ms:4090201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:159 rssi_min:-66 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:espnow n:130 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 5 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-80 rssi_med:-63 rssi_max:-58
said: 6 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-81 rssi_med:-56 rssi_max:-52
said: 7 | **LINK** peer:0x00000010 proto:ble n:57 rssi_min:-65 rssi_med:-62 rssi_max:-50
said: 8 | **LINK** peer:0x00000010 proto:espnow n:95 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 9 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 10 | 0x00000011 ble met predicted:-63 observed:-63
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000200 ble met predicted:-59 observed:-59
percept: 11 | 0x00000200 | link_stable | ble | + | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 14 | 0x00000200 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 15 | 0x00000011 | link_stable | espnow | + | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000010 ble met predicted:-62 observed:-62
percept: 17 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON27452 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3768457 ±0 frame:7500
seq: 4771
follows: 0x00000010:1471 0x00000011:1416 0x00000012:1330 0x00000100:1069 0x00000200:2107
said: 1 | **ACOUSTICWIN** t_ms:4090201 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3688 rate:8000
said: 2 | **ACOUSTIC** rms_mean:136 rms_max:407 peak:776 transients:0
```

---

@LAT105LON5795 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3721605 ±21 frame:7500
seq: 1471
follows: 0x00000011:1415 0x00000012:1330 0x00000100:1068 0x00000200:2107 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4043323 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:108 rssi_min:-35 rssi_med:-31 rssi_max:-28
said: 3 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-82 rssi_med:-55 rssi_max:-52
said: 4 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-52 rssi_max:-46
said: 5 | **LINK** peer:0x00000011 proto:espnow n:119 rssi_min:-41 rssi_med:-40 rssi_max:-36
said: 6 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-51 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000300 proto:espnow n:134 rssi_min:-45 rssi_med:-43 rssi_max:-42
said: 8 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-46 rssi_max:-39
said: 9 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-59 rssi_med:-58 rssi_max:-57
```

---

@LAT105LON5796 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3693008 ±21 frame:7500
seq: 1415
follows: 0x00000010:1470 0x00000012:1329 0x00000100:1066 0x00000200:2106 0x00000300:4766
said: 1 | **LINKWIN** t_ms:4014730 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-81 rssi_med:-63 rssi_max:-60
said: 3 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-81 rssi_med:-59 rssi_max:-54
said: 4 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-70 rssi_med:-69 rssi_max:-64
said: 5 | **LINK** peer:0x00000200 proto:espnow n:65 rssi_min:-50 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000300 proto:espnow n:117 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 7 | **LINK** peer:0x00000010 proto:espnow n:48 rssi_min:-40 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000012 proto:espnow n:76 rssi_min:-42 rssi_med:-35 rssi_max:-35
said: 9 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-81 rssi_med:-49 rssi_max:-44
```

---

@LAT105LON5797 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3711596 ±21 frame:7500
seq: 1330
follows: 0x00000010:1470 0x00000011:1415 0x00000100:1068 0x00000200:2106 0x00000300:4766
said: 1 | **LINKWIN** t_ms:4033328 stream:0xc9e0e898 wall:0 window_ms:60004
said: 2 | **LINK** peer:0x00000011 proto:espnow n:112 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 3 | **LINK** peer:0x00000010 proto:espnow n:68 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 4 | **LINK** peer:0x00000011 proto:ble n:70 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 5 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-45 rssi_max:-44
said: 6 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 7 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-53 rssi_max:-51
said: 8 | **LINK** peer:0x00000200 proto:espnow n:90 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 9 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-36 rssi_med:-31 rssi_max:-30
```

---

@LAT105LON5798 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3770592 ±21 frame:7500
seq: 2108
follows: 0x00000010:1471 0x00000011:1416 0x00000012:1330 0x00000100:1069 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4092327 stream:0xc9e0e898 wall:0 window_ms:60029
said: 2 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-80 rssi_med:-57 rssi_max:-50
said: 3 | **LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-38 rssi_med:-35 rssi_max:-35
said: 4 | **LINK** peer:0x00000010 proto:espnow n:119 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000300 proto:espnow n:141 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:espnow n:145 rssi_min:-49 rssi_med:-46 rssi_max:-46
said: 7 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-80 rssi_med:-63 rssi_max:-62
said: 8 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-34 rssi_med:-32 rssi_max:-32
```

---

@LAT105LON5799 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3781605 ±21 frame:7500
seq: 1472
follows: 0x00000011:1416 0x00000012:1331 0x00000100:1069 0x00000200:2108 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4103322 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-79 rssi_med:-46 rssi_max:-39
said: 3 | **LINK** peer:0x00000012 proto:espnow n:105 rssi_min:-35 rssi_med:-31 rssi_max:-31
said: 4 | **LINK** peer:0x00000300 proto:ble n:64 rssi_min:-77 rssi_med:-52 rssi_max:-46
said: 5 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-59 rssi_med:-57 rssi_max:-57
said: 6 | **LINK** peer:0x00000200 proto:espnow n:110 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 7 | **LINK** peer:0x00000300 proto:espnow n:130 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 8 | **LINK** peer:0x00000011 proto:espnow n:141 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 9 | **LINK** peer:0x00000011 proto:ble n:71 rssi_min:-73 rssi_med:-55 rssi_max:-52
```

---

@LAT105LON5800 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3771597 ±21 frame:7500
seq: 1331
follows: 0x00000010:1471 0x00000011:1416 0x00000100:1069 0x00000200:2107 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4093328 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:60 rssi_min:-81 rssi_med:-50 rssi_max:-43
said: 3 | **LINK** peer:0x00000010 proto:espnow n:110 rssi_min:-36 rssi_med:-32 rssi_max:-31
said: 4 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000300 proto:ble n:74 rssi_min:-80 rssi_med:-53 rssi_max:-52
said: 6 | **LINK** peer:0x00000300 proto:espnow n:147 rssi_min:-46 rssi_med:-45 rssi_max:-40
said: 7 | **LINK** peer:0x00000011 proto:espnow n:166 rssi_min:-43 rssi_med:-41 rssi_max:-41
said: 8 | **LINK** peer:0x00000200 proto:ble n:61 rssi_min:-80 rssi_med:-45 rssi_max:-44
said: 9 | **LINK** peer:0x00000200 proto:espnow n:125 rssi_min:-35 rssi_med:-30 rssi_max:-30
```

---

@LAT103LON3085 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3828457 ±0 frame:7500
seq: 4772
follows: 0x00000010:1472 0x00000011:1417 0x00000012:1331 0x00000100:1070 0x00000200:2108
said: 1 | **LINKWIN** t_ms:4150201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:104 rssi_min:-65 rssi_med:-62 rssi_max:-60
said: 3 | **LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-49 rssi_med:-47 rssi_max:-46
said: 5 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-61 rssi_med:-60 rssi_max:-51
said: 6 | **LINK** peer:0x00000200 proto:ble n:65 rssi_min:-64 rssi_med:-59 rssi_max:-54
said: 7 | **LINK** peer:0x00000011 proto:ble n:46 rssi_min:-79 rssi_med:-63 rssi_max:-58
said: 8 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-65 rssi_med:-61 rssi_max:-49
said: 9 | **LINK** peer:0x00000200 proto:espnow n:142 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 10 | 0x00000011 espnow met predicted:-62 observed:-62
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000011 ble met predicted:-63 observed:-63
percept: 13 | 0x00000011 | link_stable | ble | + | -
said: 14 | 0x00000012 ble met predicted:-56 observed:-60
percept: 14 | 0x00000012 | link_stable | ble | + | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-61
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000200 ble met predicted:-59 observed:-59
percept: 17 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON27453 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3828457 ±0 frame:7500
seq: 4773
follows: 0x00000010:1472 0x00000011:1417 0x00000012:1331 0x00000100:1070 0x00000200:2108
said: 1 | **ACOUSTICWIN** t_ms:4150201 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3675 rate:8000
said: 2 | **ACOUSTIC** rms_mean:221 rms_max:2367 peak:5348 transients:27
said: 3 | **TRANSIENT** t_ms:4102092 stream:0xc9e0e898 wall:0 rms:2304
```

---

@LAT104LON686 | created:0 | updated:0

**carried through @LAT103LON3041**

```ttdb-carried
through: 3041
through: 8353
through: 16500
through: 27437
carried: 2255 37 2491 2263 | 0x00000200 | link_stable | espnow
carried: 2358 27 2741 2297 | 0x00000200 | link_stable | ble
carried: 1124 15 1492 1026 | 0x00000100 | link_stable | espnow
carried: 1673 16 2043 1606 | 0x00000010 | link_stable | ble
carried: 1640 31 2024 1589 | 0x00000010 | link_stable | espnow
carried: 1205 8 1213 1264 | 0x00000011 | link_stable | ble
carried: 1132 25 1157 1184 | 0x00000011 | link_stable | espnow
carried: 1124 9 1133 1182 | 0x00000012 | link_stable | ble
carried: 1137 9 1146 1188 | 0x00000012 | link_stable | espnow
```

---

@LAT105LON5801 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3753010 ±21 frame:7500
seq: 1416
follows: 0x00000010:1471 0x00000012:1330 0x00000100:1068 0x00000200:2107 0x00000300:4769
said: 1 | **LINKWIN** t_ms:4074731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 3 | **LINK** peer:0x00000300 proto:espnow n:137 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 4 | **LINK** peer:0x00000010 proto:espnow n:113 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 5 | **LINK** peer:0x00000200 proto:espnow n:137 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 6 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-41 rssi_med:-35 rssi_max:-32
said: 7 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 9 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-82 rssi_med:-54 rssi_max:-51
```

---

@LAT105LON5802 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3841629 ±21 frame:7500
seq: 1473
follows: 0x00000011:1417 0x00000012:1331 0x00000100:1070 0x00000200:2109 0x00000300:4773
said: 1 | **LINKWIN** t_ms:4163344 stream:0xc9e0e898 wall:0 window_ms:60022
said: 2 | **LINK** peer:0x00000200 proto:espnow n:151 rssi_min:-49 rssi_med:-49 rssi_max:-47
said: 3 | **LINK** peer:0x00000300 proto:espnow n:180 rssi_min:-45 rssi_med:-43 rssi_max:-43
said: 4 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-59 rssi_med:-58 rssi_max:-56
said: 5 | **LINK** peer:0x00000012 proto:espnow n:51 rssi_min:-35 rssi_med:-31 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:91 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 7 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-59 rssi_max:-55
said: 8 | **LINK** peer:0x00000011 proto:ble n:55 rssi_min:-77 rssi_med:-55 rssi_max:-51
said: 9 | **LINK** peer:0x00000300 proto:ble n:55 rssi_min:-60 rssi_med:-53 rssi_max:-46
```

---

@LAT105LON5803 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3813010 ±21 frame:7500
seq: 1417
follows: 0x00000010:1472 0x00000012:1331 0x00000100:1069 0x00000200:2108 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4134731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:espnow n:106 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 3 | **LINK** peer:0x00000200 proto:espnow n:141 rssi_min:-49 rssi_med:-48 rssi_max:-46
said: 4 | **LINK** peer:0x00000300 proto:espnow n:159 rssi_min:-62 rssi_med:-58 rssi_max:-57
said: 5 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-70 rssi_med:-69 rssi_max:-65
said: 6 | **LINK** peer:0x00000012 proto:espnow n:107 rssi_min:-42 rssi_med:-35 rssi_max:-35
said: 7 | **LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-49 rssi_max:-44
said: 8 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 9 | **LINK** peer:0x00000200 proto:ble n:66 rssi_min:-81 rssi_med:-63 rssi_max:-60
```

---

@LAT103LON3086 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3888457 ±0 frame:7500
seq: 4774
follows: 0x00000010:1473 0x00000011:1418 0x00000012:1332 0x00000100:1071 0x00000200:2109
said: 1 | **LINKWIN** t_ms:4210201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:espnow n:105 rssi_min:-46 rssi_med:-45 rssi_max:-44
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-56 rssi_max:-52
said: 5 | **LINK** peer:0x00000010 proto:ble n:68 rssi_min:-66 rssi_med:-62 rssi_max:-49
said: 6 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-65 rssi_med:-61 rssi_max:-59
said: 7 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-81 rssi_med:-63 rssi_max:-58
said: 8 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-59 rssi_max:-54
said: 9 | **LINK** peer:0x00000010 proto:espnow n:94 rssi_min:-50 rssi_med:-47 rssi_max:-46
said: 10 | 0x00000011 espnow met predicted:-62 observed:-61
percept: 10 | 0x00000011 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000012 ble met predicted:-60 observed:-56
percept: 13 | 0x00000012 | link_stable | ble | + | -
said: 14 | 0x00000200 ble met predicted:-59 observed:-59
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000011 ble met predicted:-63 observed:-63
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000010 ble met predicted:-61 observed:-62
percept: 16 | 0x00000010 | link_stable | ble | + | -
said: 17 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 17 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON27454 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3888457 ±0 frame:7500
seq: 4775
follows: 0x00000010:1473 0x00000011:1418 0x00000012:1332 0x00000100:1071 0x00000200:2109
said: 1 | **ACOUSTICWIN** t_ms:4210201 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3415 rate:8000
said: 2 | **ACOUSTIC** rms_mean:138 rms_max:1600 peak:1874 transients:2
said: 3 | **TRANSIENT** t_ms:4207367 stream:0xc9e0e898 wall:0 rms:1129
```

---

@LAT105LON5804 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3873010 ±21 frame:7500
seq: 1418
follows: 0x00000010:1473 0x00000012:1332 0x00000100:1070 0x00000200:2109 0x00000300:4773
said: 1 | **LINKWIN** t_ms:4194731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-83 rssi_med:-54 rssi_max:-50
said: 3 | **LINK** peer:0x00000100 proto:espnow n:60 rssi_min:-70 rssi_med:-69 rssi_max:-66
said: 4 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-81 rssi_med:-49 rssi_max:-43
said: 5 | **LINK** peer:0x00000300 proto:ble n:62 rssi_min:-82 rssi_med:-58 rssi_max:-54
said: 6 | **LINK** peer:0x00000200 proto:espnow n:119 rssi_min:-49 rssi_med:-48 rssi_max:-47
said: 7 | **LINK** peer:0x00000010 proto:espnow n:84 rssi_min:-41 rssi_med:-34 rssi_max:-33
said: 8 | **LINK** peer:0x00000300 proto:espnow n:178 rssi_min:-62 rssi_med:-59 rssi_max:-57
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-63 rssi_max:-60
```

---

@LAT105LON5805 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3831596 ±21 frame:7500
seq: 1332
follows: 0x00000010:1472 0x00000011:1417 0x00000100:1070 0x00000200:2108 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4153328 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-53 rssi_max:-49
said: 3 | **LINK** peer:0x00000300 proto:espnow n:155 rssi_min:-46 rssi_med:-45 rssi_max:-41
said: 4 | **LINK** peer:0x00000010 proto:espnow n:112 rssi_min:-38 rssi_med:-32 rssi_max:-31
said: 5 | **LINK** peer:0x00000200 proto:espnow n:186 rssi_min:-36 rssi_med:-30 rssi_max:-30
said: 6 | **LINK** peer:0x00000011 proto:espnow n:113 rssi_min:-43 rssi_med:-41 rssi_max:-38
said: 7 | **LINK** peer:0x00000100 proto:espnow n:66 rssi_min:-32 rssi_med:-31 rssi_max:-30
said: 8 | **LINK** peer:0x00000300 proto:ble n:58 rssi_min:-81 rssi_med:-53 rssi_max:-51
said: 9 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-52 rssi_max:-43
```

---

@LAT105LON5806 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3891610 ±21 frame:7500
seq: 1333
follows: 0x00000010:1473 0x00000011:1418 0x00000100:1071 0x00000200:2109 0x00000300:4773
said: 1 | **LINKWIN** t_ms:4213341 stream:0xc9e0e898 wall:0 window_ms:60013
said: 2 | **LINK** peer:0x00000011 proto:espnow n:105 rssi_min:-43 rssi_med:-41 rssi_max:-40
said: 3 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-52
said: 4 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-36 rssi_med:-31 rssi_max:-30
said: 5 | **LINK** peer:0x00000010 proto:espnow n:82 rssi_min:-37 rssi_med:-32 rssi_max:-31
said: 6 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-83 rssi_med:-53 rssi_max:-49
said: 7 | **LINK** peer:0x00000200 proto:ble n:56 rssi_min:-80 rssi_med:-45 rssi_max:-44
said: 8 | **LINK** peer:0x00000300 proto:espnow n:221 rssi_min:-86 rssi_med:-44 rssi_max:-40
said: 9 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-50 rssi_max:-43
```
@LAT106LON184 | created:0 | updated:0

**BAR** frame:7500 bar:6 own:10 held:40 terms:8 digest:0xe5fee0c4 settled_ms:300000
**HOLDS** agent:0x00000010 n:10 lo:1460 hi:1469 sum:14645
**HOLDS** agent:0x00000011 n:10 lo:1404 hi:1413 sum:14085
**HOLDS** agent:0x00000012 n:10 lo:1318 hi:1328 sum:13231
**HOLDS** agent:0x00000200 n:10 lo:2096 hi:2105 sum:21005
**HOLDS** agent:0x00000300 n:10 lo:4745 hi:4763 sum:47540
**DELIVER** up_s:3867 heap:11776 fetched:287 unanswered:138 broken:49 resumed:859 empty:76 served:1064 wants:1335 early:42 wantq_drop:0 superseded:0
**GRAMMAR** hash:0xfe169cb3 same:5 split:0

---

@LAT103LON3087 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 3948457 ±0 frame:7500
seq: 4776
follows: 0x00000010:1474 0x00000011:1419 0x00000012:1333 0x00000100:1072 0x00000200:2110
said: 1 | **LINKWIN** t_ms:4270201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-62 rssi_max:-49
said: 3 | **LINK** peer:0x00000011 proto:espnow n:106 rssi_min:-65 rssi_med:-60 rssi_max:-45
said: 4 | **LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 5 | **LINK** peer:0x00000200 proto:espnow n:117 rssi_min:-46 rssi_med:-45 rssi_max:-38
said: 6 | **LINK** peer:0x00000200 proto:ble n:69 rssi_min:-65 rssi_med:-59 rssi_max:-53
said: 7 | **LINK** peer:0x00000012 proto:ble n:52 rssi_min:-67 rssi_med:-57 rssi_max:-52
said: 8 | **LINK** peer:0x00000010 proto:espnow n:98 rssi_min:-51 rssi_med:-47 rssi_max:-45
said: 9 | **LINK** peer:0x00000011 proto:ble n:53 rssi_min:-78 rssi_med:-64 rssi_max:-56
said: 10 | 0x00000200 espnow met predicted:-45 observed:-45
percept: 10 | 0x00000200 | link_stable | espnow | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000012 ble met predicted:-56 observed:-57
percept: 12 | 0x00000012 | link_stable | ble | + | -
said: 13 | 0x00000010 ble met predicted:-62 observed:-62
percept: 13 | 0x00000010 | link_stable | ble | + | -
said: 14 | 0x00000011 espnow met predicted:-61 observed:-60
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000011 ble met predicted:-63 observed:-64
percept: 15 | 0x00000011 | link_stable | ble | + | -
said: 16 | 0x00000200 ble met predicted:-59 observed:-59
percept: 16 | 0x00000200 | link_stable | ble | + | -
said: 17 | 0x00000010 espnow met predicted:-47 observed:-47
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON27455 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 3948457 ±0 frame:7500
seq: 4777
follows: 0x00000010:1474 0x00000011:1419 0x00000012:1333 0x00000100:1072 0x00000200:2110
said: 1 | **ACOUSTICWIN** t_ms:4270201 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:2925 rate:8000
said: 2 | **ACOUSTIC** rms_mean:132 rms_max:588 peak:945 transients:0
```

---

@LAT105LON5807 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3901629 ±21 frame:7500
seq: 1474
follows: 0x00000011:1418 0x00000012:1333 0x00000100:1071 0x00000200:2110 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4223344 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-58 rssi_med:-58 rssi_max:-57
said: 3 | **LINK** peer:0x00000300 proto:espnow n:234 rssi_min:-45 rssi_med:-43 rssi_max:-40
said: 4 | **LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-46 rssi_max:-39
said: 5 | **LINK** peer:0x00000200 proto:espnow n:116 rssi_min:-49 rssi_med:-49 rssi_max:-46
said: 6 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-41 rssi_med:-39 rssi_max:-36
said: 7 | **LINK** peer:0x00000011 proto:ble n:62 rssi_min:-70 rssi_med:-56 rssi_max:-52
said: 8 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-66 rssi_med:-58 rssi_max:-55
said: 9 | **LINK** peer:0x00000300 proto:ble n:66 rssi_min:-77 rssi_med:-53 rssi_max:-46
```

---

@LAT105LON5808 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3830592 ±21 frame:7500
seq: 2109
follows: 0x00000010:1472 0x00000011:1417 0x00000012:1331 0x00000100:1070 0x00000300:4771
said: 1 | **LINKWIN** t_ms:4152330 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:68 rssi_min:-37 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000011 proto:espnow n:98 rssi_min:-48 rssi_med:-46 rssi_max:-46
said: 4 | **LINK** peer:0x00000010 proto:espnow n:109 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 5 | **LINK** peer:0x00000300 proto:espnow n:152 rssi_min:-41 rssi_med:-40 rssi_max:-40
said: 6 | **LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 8 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-49 rssi_max:-48
said: 9 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-81 rssi_med:-57 rssi_max:-50
```

---

@LAT105LON5809 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3933010 ±21 frame:7500
seq: 1419
follows: 0x00000010:1474 0x00000012:1333 0x00000100:1071 0x00000200:2110 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4254731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:141 rssi_min:-62 rssi_med:-58 rssi_max:-46
said: 3 | **LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-70 rssi_med:-69 rssi_max:-54
said: 4 | **LINK** peer:0x00000010 proto:espnow n:110 rssi_min:-41 rssi_med:-34 rssi_max:-31
said: 5 | **LINK** peer:0x00000012 proto:espnow n:127 rssi_min:-40 rssi_med:-35 rssi_max:-34
said: 6 | **LINK** peer:0x00000200 proto:ble n:68 rssi_min:-82 rssi_med:-63 rssi_max:-55
said: 7 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-82 rssi_med:-49 rssi_max:-41
said: 8 | **LINK** peer:0x00000010 proto:ble n:59 rssi_min:-82 rssi_med:-54 rssi_max:-47
said: 9 | **LINK** peer:0x00000300 proto:ble n:52 rssi_min:-82 rssi_med:-59 rssi_max:-53
```

---

@LAT105LON5810 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 3951610 ±21 frame:7500
seq: 1334
follows: 0x00000010:1474 0x00000011:1419 0x00000100:1071 0x00000200:2110 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4273341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:81 rssi_min:-44 rssi_med:-42 rssi_max:-36
said: 3 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 4 | **LINK** peer:0x00000011 proto:ble n:61 rssi_min:-81 rssi_med:-53 rssi_max:-46
said: 5 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-38 rssi_med:-33 rssi_max:-30
said: 6 | **LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-37 rssi_med:-32 rssi_max:-30
said: 7 | **LINK** peer:0x00000200 proto:espnow n:131 rssi_min:-38 rssi_med:-31 rssi_max:-28
said: 8 | **LINK** peer:0x00000300 proto:espnow n:140 rssi_min:-54 rssi_med:-52 rssi_max:-35
said: 9 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-81 rssi_med:-51 rssi_max:-43
```

---

@LAT105LON5811 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 3961630 ±21 frame:7500
seq: 1475
follows: 0x00000011:1419 0x00000012:1334 0x00000100:1072 0x00000200:2111 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4283345 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-68 rssi_med:-54 rssi_max:-49
said: 3 | **LINK** peer:0x00000200 proto:espnow n:104 rssi_min:-59 rssi_med:-50 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:76 rssi_min:-42 rssi_med:-38 rssi_max:-33
said: 5 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-83 rssi_med:-46 rssi_max:-38
said: 6 | **LINK** peer:0x00000300 proto:espnow n:138 rssi_min:-51 rssi_med:-44 rssi_max:-40
said: 7 | **LINK** peer:0x00000011 proto:ble n:71 rssi_min:-79 rssi_med:-53 rssi_max:-48
said: 8 | **LINK** peer:0x00000012 proto:espnow n:60 rssi_min:-34 rssi_med:-31 rssi_max:-29
said: 9 | **LINK** peer:0x00000300 proto:ble n:60 rssi_min:-80 rssi_med:-52 rssi_max:-46
```

---

@LAT105LON5812 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 3993012 ±21 frame:7500
seq: 1420
follows: 0x00000010:1475 0x00000012:1334 0x00000100:1072 0x00000200:2111 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4314731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-73 rssi_med:-56 rssi_max:-47
said: 3 | **LINK** peer:0x00000200 proto:espnow n:97 rssi_min:-54 rssi_med:-48 rssi_max:-44
said: 4 | **LINK** peer:0x00000012 proto:espnow n:120 rssi_min:-44 rssi_med:-35 rssi_max:-33
said: 5 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-82 rssi_med:-58 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:espnow n:112 rssi_min:-47 rssi_med:-32 rssi_max:-30
said: 7 | **LINK** peer:0x00000300 proto:espnow n:165 rssi_min:-55 rssi_med:-49 rssi_max:-36
said: 8 | **LINK** peer:0x00000012 proto:ble n:63 rssi_min:-83 rssi_med:-51 rssi_max:-42
said: 9 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-82 rssi_med:-61 rssi_max:-52
```

---

@LAT103LON3088 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4008457 ±0 frame:7500
seq: 4778
follows: 0x00000010:1475 0x00000011:1420 0x00000012:1334 0x00000100:1073 0x00000200:2111
said: 1 | **LINKWIN** t_ms:4330201 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-57 rssi_max:-49
said: 3 | **LINK** peer:0x00000100 proto:espnow n:64 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 4 | **LINK** peer:0x00000200 proto:espnow n:108 rssi_min:-51 rssi_med:-42 rssi_max:-38
said: 5 | **LINK** peer:0x00000010 proto:espnow n:115 rssi_min:-53 rssi_med:-48 rssi_max:-43
said: 6 | **LINK** peer:0x00000011 proto:espnow n:107 rssi_min:-58 rssi_med:-49 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:ble n:62 rssi_min:-82 rssi_med:-62 rssi_max:-50
said: 8 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-81 rssi_med:-63 rssi_max:-55
said: 9 | **LINK** peer:0x00000012 proto:ble n:71 rssi_min:-81 rssi_med:-56 rssi_max:-50
said: 10 | 0x00000010 ble met predicted:-62 observed:-62
percept: 10 | 0x00000010 | link_stable | ble | + | -
said: 11 | 0x00000011 espnow violated predicted:-60 observed:-49
percept: 11 | 0x00000011 | link_stable | espnow | - | -
said: 12 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 12 | 0x00000100 | link_stable | espnow | + | -
said: 13 | 0x00000200 espnow met predicted:-45 observed:-42
percept: 13 | 0x00000200 | link_stable | espnow | + | -
said: 14 | 0x00000200 ble met predicted:-59 observed:-57
percept: 14 | 0x00000200 | link_stable | ble | + | -
said: 15 | 0x00000012 ble met predicted:-57 observed:-56
percept: 15 | 0x00000012 | link_stable | ble | + | -
said: 16 | 0x00000010 espnow met predicted:-47 observed:-48
percept: 16 | 0x00000010 | link_stable | espnow | + | -
said: 17 | 0x00000011 ble met predicted:-64 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON27456 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4008457 ±0 frame:7500
seq: 4779
follows: 0x00000010:1475 0x00000011:1420 0x00000012:1334 0x00000100:1073 0x00000200:2111
said: 1 | **ACOUSTICWIN** t_ms:4330201 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3675 rate:8000
said: 2 | **ACOUSTIC** rms_mean:154 rms_max:4633 peak:22169 transients:8
said: 3 | **TRANSIENT** t_ms:4313432 stream:0xc9e0e898 wall:0 rms:4633
```

---

@LAT105LON5813 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3890593 ±21 frame:7500
seq: 2110
follows: 0x00000010:1473 0x00000011:1418 0x00000012:1332 0x00000100:1071 0x00000300:4775
said: 1 | **LINKWIN** t_ms:4212330 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-38 rssi_med:-35 rssi_max:-35
said: 3 | **LINK** peer:0x00000010 proto:espnow n:93 rssi_min:-49 rssi_med:-47 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:114 rssi_min:-48 rssi_med:-46 rssi_max:-45
said: 5 | **LINK** peer:0x00000300 proto:ble n:68 rssi_min:-81 rssi_med:-57 rssi_max:-49
said: 6 | **LINK** peer:0x00000010 proto:ble n:74 rssi_min:-81 rssi_med:-63 rssi_max:-54
said: 7 | **LINK** peer:0x00000012 proto:ble n:54 rssi_min:-51 rssi_med:-49 rssi_max:-48
said: 8 | **LINK** peer:0x00000011 proto:ble n:65 rssi_min:-63 rssi_med:-63 rssi_max:-62
said: 9 | **LINK** peer:0x00000012 proto:espnow n:64 rssi_min:-33 rssi_med:-32 rssi_max:-32
```

---

@LAT105LON5814 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4011611 ±21 frame:7500
seq: 1335
follows: 0x00000010:1475 0x00000011:1420 0x00000100:1073 0x00000200:2111 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4333341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-45 rssi_med:-31 rssi_max:-27
said: 3 | **LINK** peer:0x00000011 proto:ble n:54 rssi_min:-81 rssi_med:-56 rssi_max:-47
said: 4 | **LINK** peer:0x00000011 proto:espnow n:89 rssi_min:-56 rssi_med:-41 rssi_max:-35
said: 5 | **LINK** peer:0x00000300 proto:espnow n:123 rssi_min:-60 rssi_med:-38 rssi_max:-27
said: 6 | **LINK** peer:0x00000010 proto:ble n:66 rssi_min:-82 rssi_med:-53 rssi_max:-43
said: 7 | **LINK** peer:0x00000010 proto:espnow n:101 rssi_min:-52 rssi_med:-32 rssi_max:-30
said: 8 | **LINK** peer:0x00000200 proto:espnow n:92 rssi_min:-50 rssi_med:-31 rssi_max:-25
said: 9 | **LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-45 rssi_max:-39
```

---

@LAT105LON5815 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4021560 ±21 frame:7500
seq: 1476
follows: 0x00000011:1420 0x00000012:1335 0x00000100:1073 0x00000200:2112 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4343344 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-71 rssi_med:-53 rssi_max:-47
said: 3 | **LINK** peer:0x00000011 proto:espnow n:100 rssi_min:-50 rssi_med:-39 rssi_max:-31
said: 4 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-65 rssi_med:-51 rssi_max:-44
said: 5 | **LINK** peer:0x00000300 proto:espnow n:135 rssi_min:-56 rssi_med:-49 rssi_max:-35
said: 6 | **LINK** peer:0x00000200 proto:espnow n:80 rssi_min:-51 rssi_med:-49 rssi_max:-41
said: 7 | **LINK** peer:0x00000012 proto:espnow n:170 rssi_min:-51 rssi_med:-43 rssi_max:-29
said: 8 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-77 rssi_med:-59 rssi_max:-52
said: 9 | **LINK** peer:0x00000012 proto:ble n:62 rssi_min:-81 rssi_med:-51 rssi_max:-38
```

---

@LAT105LON5816 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4053012 ±21 frame:7500
seq: 1421
follows: 0x00000010:1476 0x00000012:1335 0x00000100:1073 0x00000200:2112 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4374731 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-57 rssi_med:-53 rssi_max:-41
said: 3 | **LINK** peer:0x00000100 proto:espnow n:65 rssi_min:-69 rssi_med:-58 rssi_max:-50
said: 4 | **LINK** peer:0x00000300 proto:espnow n:179 rssi_min:-61 rssi_med:-46 rssi_max:-41
said: 5 | **LINK** peer:0x00000200 proto:espnow n:44 rssi_min:-59 rssi_med:-54 rssi_max:-50
said: 6 | **LINK** peer:0x00000200 proto:ble n:35 rssi_min:-81 rssi_med:-63 rssi_max:-60
said: 7 | **LINK** peer:0x00000012 proto:ble n:67 rssi_min:-80 rssi_med:-59 rssi_max:-49
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-47
said: 9 | **LINK** peer:0x00000010 proto:espnow n:118 rssi_min:-43 rssi_med:-35 rssi_max:-30
```

---

@LAT103LON3089 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4068458 ±0 frame:7500
seq: 4780
follows: 0x00000010:1476 0x00000011:1421 0x00000012:1335 0x00000100:1074 0x00000200:2112
said: 1 | **LINKWIN** t_ms:4390202 stream:0xc9e0e898 wall:0 window_ms:60001
said: 2 | **LINK** peer:0x00000011 proto:ble n:57 rssi_min:-81 rssi_med:-68 rssi_max:-61
said: 3 | **LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-63 rssi_max:-51
said: 4 | **LINK** peer:0x00000012 proto:espnow n:103 rssi_min:-40 rssi_med:-39 rssi_max:-38
said: 5 | **LINK** peer:0x00000200 proto:ble n:33 rssi_min:-80 rssi_med:-58 rssi_max:-55
said: 6 | **LINK** peer:0x00000100 proto:espnow n:59 rssi_min:-31 rssi_med:-29 rssi_max:-29
said: 7 | **LINK** peer:0x00000011 proto:espnow n:99 rssi_min:-56 rssi_med:-54 rssi_max:-46
said: 8 | **LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-42 rssi_med:-41 rssi_max:-40
said: 9 | **LINK** peer:0x00000010 proto:espnow n:102 rssi_min:-56 rssi_med:-51 rssi_max:-46
said: 10 | 0x00000200 ble met predicted:-57 observed:-58
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000200 espnow met predicted:-42 observed:-41
percept: 12 | 0x00000200 | link_stable | espnow | + | -
said: 13 | 0x00000010 espnow met predicted:-48 observed:-51
percept: 13 | 0x00000010 | link_stable | espnow | + | -
said: 14 | 0x00000011 espnow met predicted:-49 observed:-54
percept: 14 | 0x00000011 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble met predicted:-62 observed:-63
percept: 15 | 0x00000010 | link_stable | ble | + | -
said: 16 | 0x00000011 ble met predicted:-63 observed:-68
percept: 16 | 0x00000011 | link_stable | ble | + | -
said: 17 | 0x00000012 ble unobserved predicted:-56 observed:-56
percept: 17 | 0x00000012 | link_stable | ble | ? | -
```

---

@LAT103LON27457 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4068458 ±0 frame:7500
seq: 4781
follows: 0x00000010:1476 0x00000011:1421 0x00000012:1335 0x00000100:1074 0x00000200:2112
said: 1 | **ACOUSTICWIN** t_ms:4390202 stream:0xc9e0e898 wall:0 window_ms:60001 blocks:3448 rate:8000
said: 2 | **ACOUSTIC** rms_mean:150 rms_max:1906 peak:5102 transients:2
said: 3 | **TRANSIENT** t_ms:4363484 stream:0xc9e0e898 wall:0 rms:1906
```

---

@LAT105LON5817 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000010
source: linkpercept
at: 4081629 ±21 frame:7500
seq: 1477
follows: 0x00000011:1421 0x00000012:1336 0x00000100:1074 0x00000200:2112 0x00000300:4781
said: 1 | **LINKWIN** t_ms:4403344 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000011 proto:espnow n:83 rssi_min:-41 rssi_med:-36 rssi_max:-33
said: 3 | **LINK** peer:0x00000300 proto:espnow n:187 rssi_min:-57 rssi_med:-49 rssi_max:-41
said: 4 | **LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-64 rssi_med:-60 rssi_max:-44
said: 5 | **LINK** peer:0x00000300 proto:ble n:51 rssi_min:-79 rssi_med:-55 rssi_max:-49
said: 6 | **LINK** peer:0x00000012 proto:ble n:55 rssi_min:-76 rssi_med:-56 rssi_max:-51
said: 7 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-79 rssi_med:-54 rssi_max:-49
said: 8 | **LINK** peer:0x00000012 proto:espnow n:72 rssi_min:-65 rssi_med:-42 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:ble n:33 rssi_min:-60 rssi_med:-57 rssi_max:-54
```

---

@LAT105LON5818 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4071612 ±21 frame:7500
seq: 1336
follows: 0x00000010:1476 0x00000011:1421 0x00000100:1074 0x00000200:2112 0x00000300:4781
said: 1 | **LINKWIN** t_ms:4393341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-37 rssi_med:-31 rssi_max:-29
said: 3 | **LINK** peer:0x00000300 proto:espnow n:190 rssi_min:-39 rssi_med:-33 rssi_max:-30
said: 4 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-60 rssi_med:-55 rssi_max:-49
said: 5 | **LINK** peer:0x00000200 proto:ble n:38 rssi_min:-55 rssi_med:-42 rssi_max:-40
said: 6 | **LINK** peer:0x00000011 proto:ble n:58 rssi_min:-81 rssi_med:-65 rssi_max:-53
said: 7 | **LINK** peer:0x00000010 proto:espnow n:104 rssi_min:-56 rssi_med:-48 rssi_max:-43
said: 8 | **LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-28 rssi_med:-27 rssi_max:-26
said: 9 | **LINK** peer:0x00000300 proto:ble n:56 rssi_min:-81 rssi_med:-48 rssi_max:-46
```

---

@LAT105LON5819 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000011
source: linkpercept
at: 4113013 ±21 frame:7500
seq: 1422
follows: 0x00000010:1477 0x00000012:1336 0x00000100:1074 0x00000200:2114 0x00000300:4781
said: 1 | **LINKWIN** t_ms:4434730 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:ble n:65 rssi_min:-82 rssi_med:-64 rssi_max:-56
said: 3 | **LINK** peer:0x00000200 proto:ble n:55 rssi_min:-82 rssi_med:-63 rssi_max:-61
said: 4 | **LINK** peer:0x00000100 proto:espnow n:58 rssi_min:-61 rssi_med:-59 rssi_max:-49
said: 5 | **LINK** peer:0x00000300 proto:espnow n:144 rssi_min:-57 rssi_med:-53 rssi_max:-45
said: 6 | **LINK** peer:0x00000012 proto:espnow n:121 rssi_min:-56 rssi_med:-54 rssi_max:-53
said: 7 | **LINK** peer:0x00000012 proto:ble n:53 rssi_min:-83 rssi_med:-62 rssi_max:-53
said: 8 | **LINK** peer:0x00000010 proto:ble n:61 rssi_min:-82 rssi_med:-54 rssi_max:-50
said: 9 | **LINK** peer:0x00000010 proto:espnow n:70 rssi_min:-40 rssi_med:-33 rssi_max:-32
```

---

@LAT105LON5820 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 3950594 ±21 frame:7500
seq: 2111
follows: 0x00000010:1474 0x00000011:1419 0x00000012:1333 0x00000100:1072 0x00000300:4777
said: 1 | **LINKWIN** t_ms:4272329 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000300 proto:espnow n:156 rssi_min:-48 rssi_med:-35 rssi_max:-34
said: 3 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-73 rssi_med:-63 rssi_max:-61
said: 4 | **LINK** peer:0x00000011 proto:espnow n:94 rssi_min:-50 rssi_med:-46 rssi_max:-45
said: 5 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-39 rssi_med:-35 rssi_max:-33
said: 6 | **LINK** peer:0x00000300 proto:ble n:59 rssi_min:-79 rssi_med:-57 rssi_max:-47
said: 7 | **LINK** peer:0x00000012 proto:espnow n:88 rssi_min:-35 rssi_med:-32 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:ble n:58 rssi_min:-54 rssi_med:-49 rssi_max:-47
said: 9 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-70 rssi_med:-63 rssi_max:-53
```

---

@LAT103LON3090 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4128458 ±0 frame:7500
seq: 4782
follows: 0x00000010:1477 0x00000011:1422 0x00000012:1336 0x00000100:1075 0x00000200:2114
said: 1 | **LINKWIN** t_ms:4450202 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000200 proto:ble n:60 rssi_min:-91 rssi_med:-59 rssi_max:-53
said: 3 | **LINK** peer:0x00000100 proto:espnow n:70 rssi_min:-30 rssi_med:-29 rssi_max:-29
said: 4 | **LINK** peer:0x00000010 proto:espnow n:76 rssi_min:-67 rssi_med:-50 rssi_max:-48
said: 5 | **LINK** peer:0x00000011 proto:espnow n:80 rssi_min:-61 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000012 proto:espnow n:118 rssi_min:-42 rssi_med:-38 rssi_max:-35
said: 7 | **LINK** peer:0x00000010 proto:ble n:64 rssi_min:-72 rssi_med:-63 rssi_max:-50
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-79 rssi_med:-56 rssi_max:-52
said: 9 | **LINK** peer:0x00000011 proto:ble n:63 rssi_min:-80 rssi_med:-68 rssi_max:-61
said: 10 | 0x00000011 ble met predicted:-68 observed:-68
percept: 10 | 0x00000011 | link_stable | ble | + | -
said: 11 | 0x00000010 ble met predicted:-63 observed:-63
percept: 11 | 0x00000010 | link_stable | ble | + | -
said: 12 | 0x00000012 espnow met predicted:-39 observed:-38
percept: 12 | 0x00000012 | link_stable | espnow | + | -
said: 13 | 0x00000200 ble met predicted:-58 observed:-59
percept: 13 | 0x00000200 | link_stable | ble | + | -
said: 14 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 14 | 0x00000100 | link_stable | espnow | + | -
said: 15 | 0x00000011 espnow violated predicted:-54 observed:-47
percept: 15 | 0x00000011 | link_stable | espnow | - | -
said: 16 | 0x00000200 espnow unobserved predicted:-41 observed:-41
percept: 16 | 0x00000200 | link_stable | espnow | ? | -
said: 17 | 0x00000010 espnow met predicted:-51 observed:-50
percept: 17 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT104LON687 | created:0 | updated:0

**carried through @LAT103LON3050**

```ttdb-carried
through: 3050
through: 8353
through: 16500
through: 27437
carried: 2264 37 2500 2272 | 0x00000200 | link_stable | espnow
carried: 2364 27 2747 2304 | 0x00000200 | link_stable | ble
carried: 1131 15 1499 1034 | 0x00000100 | link_stable | espnow
carried: 1680 16 2050 1614 | 0x00000010 | link_stable | ble
carried: 1645 31 2029 1596 | 0x00000010 | link_stable | espnow
carried: 1211 8 1219 1271 | 0x00000011 | link_stable | ble
carried: 1139 25 1164 1192 | 0x00000011 | link_stable | espnow
carried: 1133 9 1142 1191 | 0x00000012 | link_stable | ble
carried: 1146 9 1155 1197 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON27458 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4128458 ±0 frame:7500
seq: 4783
follows: 0x00000010:1477 0x00000011:1422 0x00000012:1336 0x00000100:1075 0x00000200:2114
said: 1 | **ACOUSTICWIN** t_ms:4450202 stream:0xc9e0e898 wall:0 window_ms:60000 blocks:3416 rate:8000
said: 2 | **ACOUSTIC** rms_mean:163 rms_max:1371 peak:4221 transients:4
said: 3 | **TRANSIENT** t_ms:4411092 stream:0xc9e0e898 wall:0 rms:1371
```

---

@LAT105LON5821 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4010595 ±21 frame:7500
seq: 2112
follows: 0x00000010:1475 0x00000011:1420 0x00000012:1334 0x00000100:1073 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4332329 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-52 rssi_med:-35 rssi_max:-33
said: 3 | **LINK** peer:0x00000010 proto:espnow n:111 rssi_min:-62 rssi_med:-48 rssi_max:-42
said: 4 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-61 rssi_max:-52
said: 5 | **LINK** peer:0x00000011 proto:ble n:59 rssi_min:-74 rssi_med:-62 rssi_max:-57
said: 6 | **LINK** peer:0x00000012 proto:ble n:70 rssi_min:-56 rssi_med:-49 rssi_max:-42
said: 7 | **LINK** peer:0x00000300 proto:ble n:63 rssi_min:-81 rssi_med:-55 rssi_max:-47
said: 8 | **LINK** peer:0x00000012 proto:espnow n:141 rssi_min:-44 rssi_med:-33 rssi_max:-28
said: 9 | **LINK** peer:0x00000300 proto:espnow n:132 rssi_min:-49 rssi_med:-41 rssi_max:-33
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:49 last_ms:4110400
t_ms:4476863 stream:0xc9e0e898 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:15 last_ms:4110665
t_ms:4476863 stream:0xc9e0e898 wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:21 last_ms:4109906
t_ms:4476863 stream:0xc9e0e898 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:20 last_ms:4107487
t_ms:4476863 stream:0xc9e0e898 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:25 last_ms:4110060
t_ms:4476863 stream:0xc9e0e898 wall:0

---

@LAT101LON5 | sid:499db878 | created:0 | updated:0 |
**PEER** node:0x00000001 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:4476863 stream:0xc9e0e898 wall:0

---

@LAT105LON5822 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4095175 ±21 frame:7500
seq: 2113
follows: 0x00000010:1476 0x00000011:1420 0x00000012:1335 0x00000100:1073 0x00000300:4779
said: 1 | **LINKWIN** t_ms:4417270 stream:0xc9e0e898 wall:0 window_ms:76125
said: 2 | **LINK** peer:0x00000012 proto:espnow n:57 rssi_min:-33 rssi_med:-32 rssi_max:-32
said: 3 | **LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-38 rssi_med:-37 rssi_max:-36
said: 4 | **LINK** peer:0x00000011 proto:espnow n:64 rssi_min:-53 rssi_med:-52 rssi_max:-51
said: 5 | **LINK** peer:0x00000010 proto:espnow n:41 rssi_min:-47 rssi_med:-45 rssi_max:-45
said: 6 | **LINK** peer:0x00000300 proto:espnow n:105 rssi_min:-46 rssi_med:-44 rssi_max:-44
said: 7 | **LINK** peer:0x00000300 proto:ble n:53 rssi_min:-81 rssi_med:-58 rssi_max:-54
said: 8 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-57 rssi_med:-49 rssi_max:-47
said: 9 | **LINK** peer:0x00000011 proto:ble n:50 rssi_min:-80 rssi_med:-65 rssi_max:-62
```

---

@LAT105LON5823 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000012
source: linkpercept
at: 4131611 ±21 frame:7500
seq: 1337
follows: 0x00000010:1477 0x00000011:1422 0x00000100:1075 0x00000200:2114 0x00000300:4783
said: 1 | **LINKWIN** t_ms:4453341 stream:0xc9e0e898 wall:0 window_ms:60000
said: 2 | **LINK** peer:0x00000010 proto:ble n:65 rssi_min:-80 rssi_med:-60 rssi_max:-51
said: 3 | **LINK** peer:0x00000300 proto:espnow n:152 rssi_min:-43 rssi_med:-33 rssi_max:-29
said: 4 | **LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-35 rssi_med:-31 rssi_max:-29
said: 5 | **LINK** peer:0x00000011 proto:espnow n:75 rssi_min:-57 rssi_med:-47 rssi_max:-45
said: 6 | **LINK** peer:0x00000300 proto:ble n:61 rssi_min:-80 rssi_med:-49 rssi_max:-44
said: 7 | **LINK** peer:0x00000010 proto:espnow n:75 rssi_min:-48 rssi_med:-44 rssi_max:-42
said: 8 | **LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-44 rssi_max:-40
said: 9 | **LINK** peer:0x00000011 proto:ble n:51 rssi_min:-80 rssi_med:-64 rssi_max:-55
```

---

@LAT103LON3091 | created:0 | updated:0

**link window**

```ttdb-episode
source: linkpercept
at: 4188561 ±0 frame:7500
seq: 4784
follows: 0x00000010:1478 0x00000011:1424 0x00000012:1337 0x00000100:1076 0x00000200:2115
said: 1 | **LINKWIN** t_ms:4510305 stream:0xc9e0e898 wall:0 window_ms:60103
said: 2 | **LINK** peer:0x00000012 proto:ble n:60 rssi_min:-81 rssi_med:-56 rssi_max:-46
said: 3 | **LINK** peer:0x00000011 proto:espnow n:67 rssi_min:-63 rssi_med:-49 rssi_max:-42
said: 4 | **LINK** peer:0x00000200 proto:espnow n:168 rssi_min:-63 rssi_med:-44 rssi_max:-31
said: 5 | **LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-63 rssi_max:-55
said: 6 | **LINK** peer:0x00000012 proto:espnow n:130 rssi_min:-47 rssi_med:-38 rssi_max:-34
said: 7 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-30 rssi_med:-29 rssi_max:-28
said: 8 | **LINK** peer:0x00000010 proto:espnow n:53 rssi_min:-60 rssi_med:-48 rssi_max:-41
said: 9 | **LINK** peer:0x00000200 proto:ble n:63 rssi_min:-77 rssi_med:-57 rssi_max:-45
said: 10 | 0x00000200 ble met predicted:-59 observed:-57
percept: 10 | 0x00000200 | link_stable | ble | + | -
said: 11 | 0x00000100 espnow met predicted:-29 observed:-29
percept: 11 | 0x00000100 | link_stable | espnow | + | -
said: 12 | 0x00000010 espnow met predicted:-50 observed:-48
percept: 12 | 0x00000010 | link_stable | espnow | + | -
said: 13 | 0x00000011 espnow met predicted:-47 observed:-49
percept: 13 | 0x00000011 | link_stable | espnow | + | -
said: 14 | 0x00000012 espnow met predicted:-38 observed:-38
percept: 14 | 0x00000012 | link_stable | espnow | + | -
said: 15 | 0x00000010 ble unobserved predicted:-63 observed:-63
percept: 15 | 0x00000010 | link_stable | ble | ? | -
said: 16 | 0x00000012 ble met predicted:-56 observed:-56
percept: 16 | 0x00000012 | link_stable | ble | + | -
said: 17 | 0x00000011 ble met predicted:-68 observed:-63
percept: 17 | 0x00000011 | link_stable | ble | + | -
```

---

@LAT103LON27459 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4188561 ±0 frame:7500
seq: 4785
follows: 0x00000010:1478 0x00000011:1424 0x00000012:1337 0x00000100:1076 0x00000200:2115
said: 1 | **ACOUSTICWIN** t_ms:4510305 stream:0xc9e0e898 wall:0 window_ms:60103 blocks:3137 rate:8000
said: 2 | **ACOUSTIC** rms_mean:199 rms_max:5585 peak:21869 transients:9
said: 3 | **TRANSIENT** t_ms:4458182 stream:0xc9e0e898 wall:0 rms:5585
```

---

@LAT105LON5824 | created:0 | updated:0

**link window**

```ttdb-episode
held: 0x00000200
source: linkpercept
at: 4155241 ±21 frame:7500
seq: 2115
follows: 0x00000010:1477 0x00000011:1422 0x00000012:1337 0x00000100:1075 0x00000300:4783
said: 1 | **LINKWIN** t_ms:4481341 stream:0xc9e0e898 wall:0 window_ms:60070
said: 2 | **LINK** peer:0x00000010 proto:espnow n:70 rssi_min:-65 rssi_med:-51 rssi_max:-43
said: 3 | **LINK** peer:0x00000012 proto:ble n:66 rssi_min:-81 rssi_med:-52 rssi_max:-47
said: 4 | **LINK** peer:0x00000300 proto:espnow n:202 rssi_min:-53 rssi_med:-37 rssi_max:-26
said: 5 | **LINK** peer:0x00000011 proto:ble n:67 rssi_min:-81 rssi_med:-64 rssi_max:-56
said: 6 | **LINK** peer:0x00000010 proto:ble n:55 rssi_min:-84 rssi_med:-64 rssi_max:-54
said: 7 | **LINK** peer:0x00000100 proto:espnow n:61 rssi_min:-44 rssi_med:-37 rssi_max:-32
said: 8 | **LINK** peer:0x00000012 proto:espnow n:123 rssi_min:-47 rssi_med:-34 rssi_max:-31
said: 9 | **LINK** peer:0x00000011 proto:espnow n:97 rssi_min:-68 rssi_med:-48 rssi_max:-45
```
