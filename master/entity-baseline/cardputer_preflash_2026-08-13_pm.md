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

**STREAM-ADOPTED** stream:0x0870722b wall:0 t_ms:1708670 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT101LON0 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:22 last_ms:56621
t_ms:1772049 stream:0x0870722b wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:16 last_ms:59341
t_ms:1772049 stream:0x0870722b wall:0

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1772049 stream:0x0870722b wall:0 window_ms:60000 n:972
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:1839496 stream:0x0870722b wall:0 node:0x300 acting:@LAT95LON0+0 observed_in:@LAT97LON1 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-42 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-26 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-25 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-44 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-41 delta:3 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-27 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-27 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON1 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON5,senses@LAT0LON0

**OUTCOME** t_ms:2100671 stream:0x0870722b wall:0 node:0x300 acting:@LAT95LON0+4 observed_in:@LAT97LON5 band_dbm:6 met:3 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:4 reason:changed max_run:30
**COVERED-SPAN** windows:3 first_t_ms:1914926 last_t_ms:2040671 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000200 proto:ble verdict:met windows:3 observed_min:-44 observed_max:-42
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:3 observed_min:-28 observed_max:-27
**COVERED** peer:0x00000010 proto:ble verdict:met windows:3 observed_min:-41 observed_max:-40
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:3 observed_min:-25 observed_max:-25
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-40 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-45 delta:-5 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-43 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-49 delta:-6 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-25 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-29 delta:-4 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-27 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-34 delta:-7 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON2 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON6,senses@LAT0LON0

**OUTCOME** t_ms:2160671 stream:0x0870722b wall:0 node:0x300 acting:@LAT95LON0+5 observed_in:@LAT97LON6 band_dbm:6 met:4 violated:0 unobserved:2 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-29 band:6
**OBSERVED** peer:0x00000010 proto:espnow verdict:unobserved
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-49 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-49 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-45 band:6
**OBSERVED** peer:0x00000010 proto:ble verdict:unobserved
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-34 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-34 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-31 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-31 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-47 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-48 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON3 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON7,senses@LAT0LON0

**OUTCOME** t_ms:2220671 stream:0x0870722b wall:0 node:0x300 acting:@LAT95LON0+6 observed_in:@LAT97LON7 band_dbm:6 met:4 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-48 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-48 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-31 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-31 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-34 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-34 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-49 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-49 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbeb39900 wall:0 t_ms:8947 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:67153 stream:0xbeb39900 wall:0 window_ms:60000 n:964
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT92LON4 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON12,senses@LAT0LON0

**OUTCOME** t_ms:127153 stream:0xbeb39900 wall:0 node:0x300 acting:@LAT95LON1+0 observed_in:@LAT97LON12 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-29 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-31 delta:-2 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-34 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-33 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-32 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-29 delta:3 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-47 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-48 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-60 delta:-2 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-52 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-51 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-50 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-50 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-49 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-49 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x1de72b4d wall:0 t_ms:240617 node:0x300 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:297709 stream:0x1de72b4d wall:0 window_ms:60000 n:744
**MOTION** state:moving moving_permille:190 dev_mean_mg:45 dev_max_mg:597 moving_ms:10073
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:357709 stream:0x1de72b4d wall:0 window_ms:60000 n:496
**MOTION** state:still moving_permille:0 dev_mean_mg:16 dev_max_mg:19 moving_ms:0
**RUN** windows_since_last:1 reason:changed max_run:30

---

@LAT93LON0 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON2,derived_from@LAT95LON3

**TRANSITION** t_ms:357709 stream:0x1de72b4d wall:0 node:0x300 from:moving to:still dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:moving t_ms:297709 window_ms:60000 n:744 moving_permille:190 dev_mean_mg:45 dev_max_mg:597 moving_ms:10073 lane:@LAT95LON2+0
  @PERCEPT:after state:still t_ms:357709 window_ms:60000 n:496 moving_permille:0 dev_mean_mg:16 dev_max_mg:19 moving_ms:0 lane:@LAT95LON3+0
**DELTA** edge:became d_permille:-190 d_dev_mean_mg:-29 d_dev_max_mg:-578

---

@LAT92LON5 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON18,senses@LAT0LON0

**OUTCOME** t_ms:417780 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+0 observed_in:@LAT97LON18 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-78 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-76 delta:2 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-84 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-83 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-65 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-66 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-70 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-69 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-61 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-65 delta:-4 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-48 delta:-6 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-69 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-67 delta:2 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-61 delta:-5 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON6 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON21,senses@LAT0LON0

**OUTCOME** t_ms:597827 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+3 observed_in:@LAT97LON21 band_dbm:6 met:7 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:3 reason:changed max_run:30
**COVERED-SPAN** windows:2 first_t_ms:477827 last_t_ms:537827 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000012 proto:ble verdict:met windows:2 observed_min:-78 observed_max:-77
**COVERED** peer:0x00000200 proto:ble verdict:met windows:2 observed_min:-56 observed_max:-53
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:2 observed_min:-46 observed_max:-40
**COVERED** peer:0x00000012 proto:espnow verdict:met windows:2 observed_min:-65 observed_max:-65
**COVERED** peer:0x00000011 proto:espnow verdict:met windows:2 observed_min:-69 observed_max:-69
**COVERED** peer:0x00000010 proto:ble verdict:met windows:2 observed_min:-69 observed_max:-68
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:2 observed_min:-70 observed_max:-69
**COVERED** peer:0x00000011 proto:ble verdict:met windows:2 observed_min:-84 observed_max:-83
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-83 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-86 delta:-3 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-65 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-62 delta:3 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-55 delta:-2 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-69 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-69 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-69 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-68 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-70 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-66 delta:4 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-78 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-77 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-48 delta:-8 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON7 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON22,senses@LAT0LON0

**OUTCOME** t_ms:657894 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+4 observed_in:@LAT97LON22 band_dbm:6 met:7 violated:1 unobserved:0 streak:2
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-77 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-78 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-68 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-65 delta:3 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-62 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-62 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-69 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-68 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-66 delta:-11 verdict:violated
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-86 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-84 delta:2 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-50 delta:-2 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-66 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-66 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON8 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON23,senses@LAT0LON0

**OUTCOME** t_ms:717898 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+5 observed_in:@LAT97LON23 band_dbm:6 met:7 violated:1 unobserved:0 streak:3
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-78 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-78 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-62 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-67 delta:-5 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-68 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-69 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-84 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-85 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-66 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-70 delta:-4 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-66 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-70 delta:-4 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-65 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-66 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-50 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-61 delta:-11 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON9 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON24,senses@LAT0LON0

**OUTCOME** t_ms:777927 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+6 observed_in:@LAT97LON24 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-78 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-79 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-67 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-62 delta:5 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-85 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-85 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-66 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-67 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-70 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-67 delta:3 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-70 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-69 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-61 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-61 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-69 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-68 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT92LON10 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON26,senses@LAT0LON0

**OUTCOME** t_ms:897927 stream:0x1de72b4d wall:0 node:0x300 acting:@LAT95LON3+8 observed_in:@LAT97LON26 band_dbm:6 met:7 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:2 reason:changed max_run:30
**COVERED-SPAN** windows:1 first_t_ms:837927 last_t_ms:837927 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000010 proto:ble verdict:met windows:1 observed_min:-65 observed_max:-65
**COVERED** peer:0x00000011 proto:espnow verdict:met windows:1 observed_min:-68 observed_max:-68
**COVERED** peer:0x00000012 proto:ble verdict:met windows:1 observed_min:-77 observed_max:-77
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:1 observed_min:-63 observed_max:-63
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:1 observed_min:-55 observed_max:-55
**COVERED** peer:0x00000200 proto:ble verdict:met windows:1 observed_min:-69 observed_max:-69
**COVERED** peer:0x00000011 proto:ble verdict:met windows:1 observed_min:-85 observed_max:-85
**COVERED** peer:0x00000012 proto:espnow verdict:met windows:1 observed_min:-63 observed_max:-63
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-65 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-64 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-63 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-63 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-85 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-85 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-68 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-68 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-77 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-78 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-62 delta:-7 verdict:violated
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-63 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-64 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-69 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-75 delta:-6 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xd9f790b7 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52491 stream:0xd9f790b7 wall:0 window_ms:60026 n:588
**MOTION** state:still moving_permille:79 dev_mean_mg:27 dev_max_mg:506 moving_ms:3601
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xcab73254 wall:0 t_ms:4900 node:0x300 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60451 stream:0xcab73254 wall:0 window_ms:60000 n:945
**MOTION** state:moving moving_permille:265 dev_mean_mg:62 dev_max_mg:745 moving_ms:16014
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbb1177f2 wall:0 t_ms:4006646 node:0x300 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4063152 stream:0xbb1177f2 wall:0 window_ms:60000 n:934
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:39 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT92LON11 | created:0 | updated:0 | relates:testifies_about@LAT95LON6,derived_from@LAT97LON32,senses@LAT0LON0

**OUTCOME** t_ms:4123152 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON6+0 observed_in:@LAT97LON32 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-84 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-83 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-68 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-65 delta:3 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-75 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-76 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-62 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-62 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-55 delta:-2 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-69 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-70 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-58 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-60 delta:-2 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-66 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-66 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5876521 stream:0xbb1177f2 wall:0 window_ms:60000 n:921
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7137217 stream:0xbb1177f2 wall:0 window_ms:60001 n:927
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:8877930 stream:0xbb1177f2 wall:0 window_ms:60000 n:926
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:10318584 stream:0xbb1177f2 wall:0 window_ms:60000 n:934
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:11699263 stream:0xbb1177f2 wall:0 window_ms:60000 n:937
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:13440096 stream:0xbb1177f2 wall:0 window_ms:60000 n:923
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:14880934 stream:0xbb1177f2 wall:0 window_ms:60000 n:923
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:16321671 stream:0xbb1177f2 wall:0 window_ms:60000 n:934
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:17462377 stream:0xbb1177f2 wall:0 window_ms:60000 n:923
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:18940055 stream:0xbb1177f2 wall:0 window_ms:60000 n:924
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:20809384 stream:0xbb1177f2 wall:0 window_ms:60000 n:932
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:22430146 stream:0xbb1177f2 wall:0 window_ms:60000 n:924
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:24230831 stream:0xbb1177f2 wall:0 window_ms:60000 n:930
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:26019689 stream:0xbb1177f2 wall:0 window_ms:60000 n:922
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:27880402 stream:0xbb1177f2 wall:0 window_ms:60000 n:915
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:29694891 stream:0xbb1177f2 wall:0 window_ms:60000 n:922
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:31435588 stream:0xbb1177f2 wall:0 window_ms:60000 n:921
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:33236269 stream:0xbb1177f2 wall:0 window_ms:60000 n:913
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:34137786 stream:0xbb1177f2 wall:0 window_ms:60000 n:920
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:35758498 stream:0xbb1177f2 wall:0 window_ms:60000 n:918
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:37498518 stream:0xbb1177f2 wall:0 window_ms:60000 n:974
**MOTION** state:moving moving_permille:152 dev_mean_mg:31 dev_max_mg:592 moving_ms:9349
**RUN** windows_since_last:29 reason:changed max_run:30
**COVERED** state:still windows:28 n:26529 window_ms:1680020 moving_permille:0 dev_mean_mg:11 dev_max_mg:17 moving_ms:0 first_t_ms:35818498 last_t_ms:37438518 covered_by:@LAT95LON26

---

@LAT93LON1 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON26,derived_from@LAT95LON27

**TRANSITION** t_ms:37498518 stream:0xbb1177f2 wall:0 node:0x300 from:still to:moving dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:still t_ms:37438518 window_ms:60000 n:977 moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0 lane:@LAT95LON26+28
  @PERCEPT:after state:moving t_ms:37498518 window_ms:60000 n:974 moving_permille:152 dev_mean_mg:31 dev_max_mg:592 moving_ms:9349 lane:@LAT95LON27+0
**DELTA** edge:became d_permille:152 d_dev_mean_mg:20 d_dev_max_mg:578

---

@LAT95LON28 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:37620097 stream:0xbb1177f2 wall:0 window_ms:60000 n:920
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---

@LAT95LON29 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:37822788 stream:0xbb1177f2 wall:0 window_ms:62566 n:2
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:11 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON30 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:38269059 stream:0xbb1177f2 wall:0 window_ms:60000 n:915
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---


---


---

@LAT95LON31 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:38761743 stream:0xbb1177f2 wall:0 window_ms:60000 n:7
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---

@LAT95LON32 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:38946302 stream:0xbb1177f2 wall:0 window_ms:60000 n:930
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:18 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON33 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:39163875 stream:0xbb1177f2 wall:0 window_ms:64405 n:2
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:10 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON34 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:39983489 stream:0xbb1177f2 wall:0 window_ms:60000 n:792
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON35 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:40075386 stream:0xbb1177f2 wall:0 window_ms:60000 n:174
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON36 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:41260656 stream:0xbb1177f2 wall:0 window_ms:60000 n:428
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON37 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:42364964 stream:0xbb1177f2 wall:0 window_ms:60000 n:42
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x89af9f2e wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON38 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:42524985 stream:0xbb1177f2 wall:0 window_ms:62829 n:2
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:10 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON39 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:42682834 stream:0xbb1177f2 wall:0 window_ms:60000 n:903
**MOTION** state:still moving_permille:1 dev_mean_mg:9 dev_max_mg:70 moving_ms:60
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON40 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:42914618 stream:0xbb1177f2 wall:0 window_ms:60000 n:918
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:48 last_lon:47 t_ms:0 stream:0x00000000 wall:0 node:0x00000300

---


---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:0 stream:0x00000000 wall:0 node:0x00000300

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:1 removed:48 last_lon:47 t_ms:0 stream:0x00000000 wall:0 node:0x00000300

---


---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:43333073 stream:0xbb1177f2 wall:0 window_ms:63089
**LINK** peer:0x00000100 proto:espnow n:32 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-49 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-35 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-66 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:50 rssi_min:-67 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:35 rssi_min:-89 rssi_med:-83 rssi_max:-83

---

@LAT95LON41 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:43333073 stream:0xbb1177f2 wall:0 window_ms:63089 n:2
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:9 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:43333073 stream:0xbb1177f2 wall:0 window_ms:63089 blocks:3 rate:8000
**ACOUSTIC** rms_mean:95 rms_max:105 peak:235 transients:0

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:43343990 stream:0xbb1177f2 wall:0 window_ms:74006 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-66
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:8470d7633e07 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-95
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:43393073 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-67 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-66 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-92 rssi_med:-87 rssi_max:-83
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-48 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-35 rssi_med:-35 rssi_max:-34

---

@LAT92LON12 | created:0 | updated:0 | relates:testifies_about@LAT95LON41,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:43393073 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON41+0 observed_in:@LAT97LON1 band_dbm:6 met:6 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-35 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-35 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-48 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-35 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-35 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-54 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-54 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-59 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-83 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-87 delta:-4 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:43393073 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:2312 rate:8000
**ACOUSTIC** rms_mean:106 rms_max:241 peak:511 transients:0

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:43453073 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-81 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:75 rssi_min:-67 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-49 rssi_med:-48 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-40 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-91 rssi_med:-88 rssi_max:-83
**LINK** peer:0x00000100 proto:espnow n:31 rssi_min:-37 rssi_med:-35 rssi_max:-34

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:43453073 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:2822 rate:8000
**ACOUSTIC** rms_mean:113 rms_max:207 peak:540 transients:0

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:43554983 stream:0xbb1177f2 wall:0 window_ms:63979
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-35 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-48 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-65 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:45 rssi_min:-80 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000011 proto:ble n:41 rssi_min:-90 rssi_med:-86 rssi_max:-82

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:43554983 stream:0xbb1177f2 wall:0 window_ms:63979 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:8470d7633e07 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:a036bc43f1f0 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON42 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:43554983 stream:0xbb1177f2 wall:0 window_ms:63979 n:2
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:11 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:43554983 stream:0xbb1177f2 wall:0 window_ms:63979 blocks:3 rate:8000
**ACOUSTIC** rms_mean:112 rms_max:131 peak:374 transients:0

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:43614983 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-67 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-48 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-41 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-61 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-90 rssi_med:-83 rssi_max:-82

---

@LAT92LON13 | created:0 | updated:0 | relates:testifies_about@LAT95LON42,derived_from@LAT97LON4,senses@LAT0LON0

**OUTCOME** t_ms:43614983 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON42+0 observed_in:@LAT97LON4 band_dbm:6 met:6 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-35 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-35 delta:0 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-35 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-35 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-48 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-54 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-54 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-59 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-86 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-83 delta:3 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:43614983 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:2320 rate:8000
**ACOUSTIC** rms_mean:159 rms_max:502 peak:926 transients:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:43674983 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-89 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-67 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-40 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-65 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-49 rssi_med:-48 rssi_max:-47

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:43674983 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:2810 rate:8000
**ACOUSTIC** rms_mean:125 rms_max:650 peak:1160 transients:0

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:43734983 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-90 rssi_med:-86 rssi_max:-82
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-79 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-49 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-39 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-82 rssi_med:-61 rssi_max:-55

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:43734983 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:2644 rate:8000
**ACOUSTIC** rms_mean:131 rms_max:361 peak:765 transients:0

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:43796280 stream:0xbb1177f2 wall:0 window_ms:61297
**LINK** peer:0x00000200 proto:ble n:72 rssi_min:-68 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-49 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-40 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-92 rssi_med:-83 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:11 rssi_min:-81 rssi_med:-76 rssi_max:-72

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:43796280 stream:0xbb1177f2 wall:0 window_ms:61297 blocks:1410 rate:8000
**ACOUSTIC** rms_mean:224 rms_max:2498 peak:3920 transients:11
**TRANSIENT** t_ms:43766912 stream:0xbb1177f2 wall:0 rms:2498

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:43856284 stream:0xbb1177f2 wall:0 window_ms:60004
**LINK** peer:0x00000200 proto:ble n:67 rssi_min:-68 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-78 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:71 rssi_min:-67 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000011 proto:ble n:36 rssi_min:-89 rssi_med:-87 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-48 rssi_med:-48 rssi_max:-46
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-40 rssi_med:-35 rssi_max:-34

---

@LAT92LON14 | created:0 | updated:0 | relates:testifies_about@LAT95LON42,derived_from@LAT97LON8,senses@LAT0LON0

**OUTCOME** t_ms:43856284 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON42+4 observed_in:@LAT97LON8 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:4 reason:changed max_run:30
**COVERED-SPAN** windows:3 first_t_ms:43674983 last_t_ms:43796280 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000200 proto:ble verdict:met windows:3 observed_min:-61 observed_max:-59
**COVERED** peer:0x00000100 proto:espnow verdict:met windows:3 observed_min:-35 observed_max:-35
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:3 observed_min:-48 observed_max:-48
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:3 observed_min:-35 observed_max:-35
**COVERED** peer:0x00000010 proto:ble verdict:met windows:3 observed_min:-54 observed_max:-54
**COVERED** peer:0x00000011 proto:ble verdict:met windows:3 observed_min:-86 observed_max:-83
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-58 delta:1 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-35 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-35 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-48 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-35 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-35 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-54 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-54 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-83 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-87 delta:-4 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-76 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-76 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:43856284 stream:0xbb1177f2 wall:0 window_ms:60004 blocks:201 rate:8000
**ACOUSTIC** rms_mean:195 rms_max:853 peak:1421 transients:0

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:43918278 stream:0xbb1177f2 wall:0 window_ms:61994
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-77 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-65 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-68 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-39 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-90 rssi_med:-82 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-49 rssi_med:-48 rssi_max:-47

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:43918278 stream:0xbb1177f2 wall:0 window_ms:61994 blocks:142 rate:8000
**ACOUSTIC** rms_mean:136 rms_max:242 peak:557 transients:0

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:43980234 stream:0xbb1177f2 wall:0 window_ms:61956
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-77 rssi_med:-76 rssi_max:-76
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-62 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:41 rssi_min:-89 rssi_med:-82 rssi_max:-82
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-68 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-40 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-48 rssi_med:-48 rssi_max:-47

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:43980234 stream:0xbb1177f2 wall:0 window_ms:61956 blocks:321 rate:8000
**ACOUSTIC** rms_mean:134 rms_max:235 peak:542 transients:0

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44042154 stream:0xbb1177f2 wall:0 window_ms:61920
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-62 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-77 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-80 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-88 rssi_med:-87 rssi_max:-81
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-48 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-40 rssi_med:-35 rssi_max:-34

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44042154 stream:0xbb1177f2 wall:0 window_ms:61920 blocks:435 rate:8000
**ACOUSTIC** rms_mean:132 rms_max:240 peak:548 transients:0

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44102154 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-77 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-69 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-48 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:32 rssi_min:-89 rssi_med:-82 rssi_max:-82
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-67 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-35 rssi_med:-35 rssi_max:-34

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44102154 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:2370 rate:8000
**ACOUSTIC** rms_mean:146 rms_max:308 peak:813 transients:0

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44163776 stream:0xbb1177f2 wall:0 window_ms:61622
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-90 rssi_med:-82 rssi_max:-81
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-68 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-77 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-39 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-48 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-67 rssi_med:-54 rssi_max:-53

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44163776 stream:0xbb1177f2 wall:0 window_ms:61622 blocks:2760 rate:8000
**ACOUSTIC** rms_mean:129 rms_max:313 peak:652 transients:0

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44223776 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-62 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-49 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-68 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:17 rssi_min:-77 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:44 rssi_min:-89 rssi_med:-87 rssi_max:-81
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-39 rssi_med:-35 rssi_max:-34

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44223776 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:2895 rate:8000
**ACOUSTIC** rms_mean:113 rms_max:255 peak:563 transients:0

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44283776 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-48 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-89 rssi_med:-88 rssi_max:-82
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-66 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-77 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-68 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-35 rssi_med:-35 rssi_max:-34

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44283776 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:2494 rate:8000
**ACOUSTIC** rms_mean:111 rms_max:223 peak:535 transients:0

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44343776 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-38 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-66 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:32 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-68 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-48 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-77 rssi_med:-76 rssi_max:-75
**LINK** peer:0x00000011 proto:ble n:41 rssi_min:-89 rssi_med:-83 rssi_max:-81

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44343776 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:2658 rate:8000
**ACOUSTIC** rms_mean:112 rms_max:250 peak:590 transients:0

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44404157 stream:0xbb1177f2 wall:0 window_ms:60381
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-49 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-80 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-83 rssi_med:-54 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-79 rssi_med:-76 rssi_max:-74
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:31 rssi_min:-92 rssi_med:-88 rssi_max:-79

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44404157 stream:0xbb1177f2 wall:0 window_ms:60381 blocks:1817 rate:8000
**ACOUSTIC** rms_mean:145 rms_max:3260 peak:4692 transients:5
**TRANSIENT** t_ms:44381868 stream:0xbb1177f2 wall:0 rms:3260

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44464271 stream:0xbb1177f2 wall:0 window_ms:60114
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-62 rssi_med:-54 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-78 rssi_med:-77 rssi_max:-75
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-37 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-48 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-68 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:34 rssi_min:-89 rssi_med:-88 rssi_max:-81

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44464271 stream:0xbb1177f2 wall:0 window_ms:60114 blocks:430 rate:8000
**ACOUSTIC** rms_mean:126 rms_max:948 peak:1631 transients:0

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44524275 stream:0xbb1177f2 wall:0 window_ms:60004
**LINK** peer:0x00000010 proto:espnow n:33 rssi_min:-40 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-91 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-83 rssi_med:-80 rssi_max:-73
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-39 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-57 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-48 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-79 rssi_med:-58 rssi_max:-53

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44524275 stream:0xbb1177f2 wall:0 window_ms:60004 blocks:600 rate:8000
**ACOUSTIC** rms_mean:284 rms_max:17659 peak:32768 transients:3
**TRANSIENT** t_ms:44483062 stream:0xbb1177f2 wall:0 rms:17659

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44584275 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:55 rssi_min:-91 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-85 rssi_med:-81 rssi_max:-78
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-37 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-38 rssi_med:-38 rssi_max:-37
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-71 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-57 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-43 rssi_med:-43 rssi_max:-42

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44584275 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:1458 rate:8000
**ACOUSTIC** rms_mean:115 rms_max:931 peak:1159 transients:1
**TRANSIENT** t_ms:44584263 stream:0xbb1177f2 wall:0 rms:931

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44646388 stream:0xbb1177f2 wall:0 window_ms:62113
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-57 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-90 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-35 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-39 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-62 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-45 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-85 rssi_med:-81 rssi_max:-78

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44646388 stream:0xbb1177f2 wall:0 window_ms:62113 blocks:409 rate:8000
**ACOUSTIC** rms_mean:168 rms_max:1928 peak:7151 transients:2
**TRANSIENT** t_ms:44598075 stream:0xbb1177f2 wall:0 rms:1928

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44708156 stream:0xbb1177f2 wall:0 window_ms:61768
**LINK** peer:0x00000200 proto:ble n:68 rssi_min:-79 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-88 rssi_med:-81 rssi_max:-73
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-46 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-92 rssi_med:-84 rssi_max:-81
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-61 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-40 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-64 rssi_med:-53 rssi_max:-47

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44708156 stream:0xbb1177f2 wall:0 window_ms:61768 blocks:1809 rate:8000
**ACOUSTIC** rms_mean:180 rms_max:11894 peak:32768 transients:3
**TRANSIENT** t_ms:44695837 stream:0xbb1177f2 wall:0 rms:11894

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:44762275 stream:0xbb1177f2 wall:0 window_ms:602557 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,64677217947d,5ce28c488e0c,18a5ffbae2d6
**COVERED** windows:1 entities:9 window_ms:604735 first_t_ms:44159718 last_t_ms:44159718 covered_by:@LAT96LON1
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-67 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93 windows:1

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44768156 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-45 rssi_med:-35 rssi_max:-29
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-80 rssi_med:-51 rssi_max:-39
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-73 rssi_med:-61 rssi_max:-49
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-71 rssi_med:-49 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:47 rssi_min:-96 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000011 proto:espnow n:15 rssi_min:-86 rssi_med:-77 rssi_max:-71
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-48 rssi_med:-39 rssi_max:-34

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44768156 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:585 rate:8000
**ACOUSTIC** rms_mean:213 rms_max:3622 peak:17137 transients:4
**TRANSIENT** t_ms:44767655 stream:0xbb1177f2 wall:0 rms:3622

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44828158 stream:0xbb1177f2 wall:0 window_ms:60002
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-56 rssi_med:-46 rssi_max:-40
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-90 rssi_med:-84 rssi_max:-79
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-79 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-31 rssi_med:-30 rssi_max:-27
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-72 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-53 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-31 rssi_med:-30 rssi_max:-28

---

@LAT92LON15 | created:0 | updated:0 | relates:testifies_about@LAT95LON42,derived_from@LAT97LON24,senses@LAT0LON0

**OUTCOME** t_ms:44828158 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON42+20 observed_in:@LAT97LON24 band_dbm:6 met:5 violated:2 unobserved:0 streak:1
**RUN** windows_since_last:16 reason:changed max_run:30
**COVERED-SPAN** windows:15 first_t_ms:43918278 last_t_ms:44768156 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000200 proto:ble verdict:met windows:15 observed_min:-61 observed_max:-58
**COVERED** peer:0x00000011 proto:espnow verdict:met windows:15 observed_min:-81 observed_max:-76
**COVERED** peer:0x00000100 proto:espnow verdict:met windows:15 observed_min:-39 observed_max:-35
**COVERED** peer:0x00000010 proto:ble verdict:met windows:15 observed_min:-54 observed_max:-51
**COVERED** peer:0x00000011 proto:ble verdict:met windows:15 observed_min:-88 observed_max:-82
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:15 observed_min:-49 observed_max:-42
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:15 observed_min:-35 observed_max:-33
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-35 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-30 delta:5 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-51 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-45 delta:6 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-61 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-46 delta:15 verdict:violated
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-49 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-30 delta:19 verdict:violated
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-86 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-84 delta:2 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-77 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-71 delta:6 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-41 delta:-2 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44828158 stream:0xbb1177f2 wall:0 window_ms:60002 blocks:3169 rate:8000
**ACOUSTIC** rms_mean:151 rms_max:1532 peak:4726 transients:1
**TRANSIENT** t_ms:44793712 stream:0xbb1177f2 wall:0 rms:1532

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44888158 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-70 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-79 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-89 rssi_med:-82 rssi_max:-79
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-47 rssi_med:-41 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-31 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-81 rssi_med:-47 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-34 rssi_med:-30 rssi_max:-30

---

@LAT92LON16 | created:0 | updated:0 | relates:testifies_about@LAT95LON42,derived_from@LAT97LON25,senses@LAT0LON0

**OUTCOME** t_ms:44888158 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON42+21 observed_in:@LAT97LON25 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-46 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-47 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-84 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-82 delta:2 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-45 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-45 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-30 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-71 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-69 delta:2 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-41 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-30 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44888158 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3364 rate:8000
**ACOUSTIC** rms_mean:154 rms_max:9021 peak:32768 transients:3
**TRANSIENT** t_ms:44872683 stream:0xbb1177f2 wall:0 rms:9021

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:44948158 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-60 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-29 rssi_med:-29 rssi_max:-29
**LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-46 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:33 rssi_min:-91 rssi_med:-87 rssi_max:-80
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-46 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-73 rssi_med:-70 rssi_max:-69
**LINK** peer:0x00000200 proto:espnow n:11 rssi_min:-33 rssi_med:-33 rssi_max:-32

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:44948158 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3379 rate:8000
**ACOUSTIC** rms_mean:139 rms_max:981 peak:1941 transients:1
**TRANSIENT** t_ms:44891689 stream:0xbb1177f2 wall:0 rms:979

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45068818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-80 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-72 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-47 rssi_med:-42 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-80 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-31 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-32 rssi_med:-30 rssi_max:-28
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-94 rssi_med:-81 rssi_max:-78

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:45068818 stream:0xbb1177f2 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON43 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:45068818 stream:0xbb1177f2 wall:0 window_ms:60000 n:927
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:53 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45068818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3468 rate:8000
**ACOUSTIC** rms_mean:146 rms_max:2260 peak:4611 transients:12
**TRANSIENT** t_ms:45032885 stream:0xbb1177f2 wall:0 rms:2260

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45128818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-92 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000200 proto:espnow n:8 rssi_min:-30 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-43 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-55 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-72 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:8 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT92LON17 | created:0 | updated:0 | relates:testifies_about@LAT95LON43,derived_from@LAT97LON28,senses@LAT0LON0

**OUTCOME** t_ms:45128818 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON43+0 observed_in:@LAT97LON28 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-45 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-46 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-72 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-72 delta:0 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-45 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-46 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-30 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-30 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-81 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-81 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45128818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3653 rate:8000
**ACOUSTIC** rms_mean:113 rms_max:780 peak:1317 transients:0

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45188818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-82 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-47 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-43 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-72 rssi_med:-71 rssi_max:-68
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000011 proto:ble n:36 rssi_min:-93 rssi_med:-90 rssi_max:-80
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-31 rssi_med:-30 rssi_max:-29

---

@LAT92LON18 | created:0 | updated:0 | relates:testifies_about@LAT95LON43,derived_from@LAT97LON29,senses@LAT0LON0

**OUTCOME** t_ms:45188818 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON43+1 observed_in:@LAT97LON29 band_dbm:6 met:6 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-81 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-90 delta:-9 verdict:violated
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-30 delta:0 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-46 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-46 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-72 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-71 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-46 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-45 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-30 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45188818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3665 rate:8000
**ACOUSTIC** rms_mean:120 rms_max:664 peak:1408 transients:0

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45248818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:70 rssi_min:-82 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-42 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:38 rssi_min:-93 rssi_med:-91 rssi_max:-80
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-79 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-72 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT92LON19 | created:0 | updated:0 | relates:testifies_about@LAT95LON43,derived_from@LAT97LON30,senses@LAT0LON0

**OUTCOME** t_ms:45248818 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON43+2 observed_in:@LAT97LON30 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-46 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-46 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-45 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-46 delta:-1 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-71 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-72 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-30 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-90 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-91 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-30 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45248818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3582 rate:8000
**ACOUSTIC** rms_mean:138 rms_max:4885 peak:7196 transients:9
**TRANSIENT** t_ms:45238197 stream:0xbb1177f2 wall:0 rms:4885

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45308818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-55 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-94 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-42 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-73 rssi_med:-71 rssi_max:-71
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-30 rssi_med:-30 rssi_max:-29

---

@LAT92LON20 | created:0 | updated:0 | relates:testifies_about@LAT95LON43,derived_from@LAT97LON31,senses@LAT0LON0

**OUTCOME** t_ms:45308818 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON43+3 observed_in:@LAT97LON31 band_dbm:6 met:6 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-46 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-45 delta:1 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-91 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-81 delta:10 verdict:violated
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-46 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-46 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-30 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-72 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-71 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-30 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45308818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3647 rate:8000
**ACOUSTIC** rms_mean:112 rms_max:392 peak:710 transients:0

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45368818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:70 rssi_min:-55 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:43 rssi_min:-48 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-73 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:37 rssi_min:-92 rssi_med:-81 rssi_max:-79
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-30 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-43 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT92LON21 | created:0 | updated:0 | relates:testifies_about@LAT95LON43,derived_from@LAT97LON32,senses@LAT0LON0

**OUTCOME** t_ms:45368818 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON43+4 observed_in:@LAT97LON32 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-45 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-46 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-81 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-81 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-46 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-46 delta:0 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-71 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-72 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-30 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-30 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45368818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3656 rate:8000
**ACOUSTIC** rms_mean:124 rms_max:518 peak:1168 transients:0

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45428818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-43 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-93 rssi_med:-89 rssi_max:-80
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-80 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-55 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-72 rssi_med:-72 rssi_max:-70
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT92LON22 | created:0 | updated:0 | relates:testifies_about@LAT95LON43,derived_from@LAT97LON33,senses@LAT0LON0

**OUTCOME** t_ms:45428818 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON43+5 observed_in:@LAT97LON33 band_dbm:6 met:6 violated:1 unobserved:0 streak:1
**RUN** windows_since_last:1 reason:changed max_run:30
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-46 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-46 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-46 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-46 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-72 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-72 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-81 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-89 delta:-8 verdict:violated
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-30 delta:0 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-30 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45428818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3559 rate:8000
**ACOUSTIC** rms_mean:127 rms_max:301 peak:778 transients:0

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45488818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-43 rssi_med:-42 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:37 rssi_min:-96 rssi_med:-80 rssi_max:-79
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-73 rssi_med:-71 rssi_max:-65
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-55 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-47 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT94LON34 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45488818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3645 rate:8000
**ACOUSTIC** rms_mean:167 rms_max:5312 peak:18242 transients:6
**TRANSIENT** t_ms:45458129 stream:0xbb1177f2 wall:0 rms:3100

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45548818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-32 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-79 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-48 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-74 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000011 proto:ble n:37 rssi_min:-96 rssi_med:-82 rssi_max:-80
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT92LON23 | created:0 | updated:0 | relates:testifies_about@LAT95LON43,derived_from@LAT97LON35,senses@LAT0LON0

**OUTCOME** t_ms:45548818 stream:0xbb1177f2 wall:0 node:0x300 acting:@LAT95LON43+7 observed_in:@LAT97LON35 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:2 reason:changed max_run:30
**COVERED-SPAN** windows:1 first_t_ms:45488818 last_t_ms:45488818 counts_scored_windows_not_minutes:1
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:1 observed_min:-30 observed_max:-30
**COVERED** peer:0x00000100 proto:espnow verdict:met windows:1 observed_min:-42 observed_max:-42
**COVERED** peer:0x00000011 proto:ble verdict:violated windows:1 observed_min:-80 observed_max:-80
**COVERED** peer:0x00000010 proto:ble verdict:met windows:1 observed_min:-45 observed_max:-45
**COVERED** peer:0x00000200 proto:ble verdict:met windows:1 observed_min:-45 observed_max:-45
**COVERED** peer:0x00000011 proto:espnow verdict:met windows:1 observed_min:-71 observed_max:-71
**COVERED** peer:0x00000010 proto:espnow verdict:met windows:1 observed_min:-30 observed_max:-30
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-30 delta:0 verdict:met
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-80 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-82 delta:-2 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-71 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-71 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-45 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-46 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-45 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-45 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-30 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-30 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT94LON35 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45548818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3656 rate:8000
**ACOUSTIC** rms_mean:149 rms_max:1363 peak:5025 transients:5
**TRANSIENT** t_ms:45512047 stream:0xbb1177f2 wall:0 rms:1363

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45608818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-47 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:36 rssi_min:-92 rssi_med:-88 rssi_max:-80
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-76 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-81 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-30 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT94LON36 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45608818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3551 rate:8000
**ACOUSTIC** rms_mean:131 rms_max:1007 peak:2039 transients:1
**TRANSIENT** t_ms:45558645 stream:0xbb1177f2 wall:0 rms:917

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45668818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-91 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-47 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:30 rssi_min:-80 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:4 rssi_min:-30 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000011 proto:espnow n:14 rssi_min:-73 rssi_med:-71 rssi_max:-71
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT94LON37 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45668818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3638 rate:8000
**ACOUSTIC** rms_mean:140 rms_max:3872 peak:5294 transients:3
**TRANSIENT** t_ms:45666241 stream:0xbb1177f2 wall:0 rms:3872

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45728818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-47 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:48 rssi_min:-56 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:10 rssi_min:-30 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-72 rssi_med:-71 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-91 rssi_med:-89 rssi_max:-80
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-31 rssi_med:-30 rssi_max:-30

---

@LAT94LON38 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45728818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3648 rate:8000
**ACOUSTIC** rms_mean:123 rms_max:353 peak:755 transients:0

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45788818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000011 proto:ble n:44 rssi_min:-91 rssi_med:-89 rssi_max:-80
**LINK** peer:0x00000010 proto:ble n:57 rssi_min:-47 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:5 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT94LON39 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45788818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3552 rate:8000
**ACOUSTIC** rms_mean:140 rms_max:411 peak:853 transients:0

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45848818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-46 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:35 rssi_min:-91 rssi_med:-89 rssi_max:-80
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-55 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:29 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-72 rssi_med:-72 rssi_max:-71
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT94LON40 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45848818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3643 rate:8000
**ACOUSTIC** rms_mean:111 rms_max:248 peak:531 transients:0

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45908818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-46 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:70 rssi_min:-80 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-73 rssi_med:-71 rssi_max:-71
**LINK** peer:0x00000011 proto:ble n:39 rssi_min:-91 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT94LON41 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45908818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3635 rate:8000
**ACOUSTIC** rms_mean:133 rms_max:4256 peak:4776 transients:4
**TRANSIENT** t_ms:45897159 stream:0xbb1177f2 wall:0 rms:3845

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:45968818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-30 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-30 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-44 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:40 rssi_min:-91 rssi_med:-88 rssi_max:-80
**LINK** peer:0x00000010 proto:ble n:70 rssi_min:-47 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-79 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-72 rssi_med:-72 rssi_max:-71

---

@LAT94LON42 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:45968818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3544 rate:8000
**ACOUSTIC** rms_mean:183 rms_max:5317 peak:7176 transients:12
**TRANSIENT** t_ms:45956303 stream:0xbb1177f2 wall:0 rms:5221

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46028818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-55 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-46 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-73 rssi_med:-72 rssi_max:-69
**LINK** peer:0x00000011 proto:ble n:52 rssi_min:-91 rssi_med:-82 rssi_max:-80
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT94LON43 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:46028818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3645 rate:8000
**ACOUSTIC** rms_mean:127 rms_max:864 peak:1705 transients:0

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46088818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-32 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000011 proto:ble n:42 rssi_min:-92 rssi_med:-81 rssi_max:-80
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-47 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-72 rssi_med:-71 rssi_max:-70
**LINK** peer:0x00000200 proto:espnow n:11 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT94LON44 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:46088818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3639 rate:8000
**ACOUSTIC** rms_mean:132 rms_max:5778 peak:6804 transients:3
**TRANSIENT** t_ms:46046007 stream:0xbb1177f2 wall:0 rms:3057

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46148818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-82 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:46 rssi_min:-92 rssi_med:-89 rssi_max:-80
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-30 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-30 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-55 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-72 rssi_med:-71 rssi_max:-70

---

@LAT94LON45 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:46148818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3548 rate:8000
**ACOUSTIC** rms_mean:140 rms_max:4414 peak:5651 transients:3
**TRANSIENT** t_ms:46118411 stream:0xbb1177f2 wall:0 rms:3083

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46208818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-43 rssi_med:-42 rssi_max:-41
**LINK** peer:0x00000200 proto:ble n:69 rssi_min:-55 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:ble n:37 rssi_min:-91 rssi_med:-85 rssi_max:-80
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-72 rssi_med:-71 rssi_max:-71
**LINK** peer:0x00000010 proto:ble n:72 rssi_min:-81 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:14 rssi_min:-30 rssi_med:-30 rssi_max:-29
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-30 rssi_med:-30 rssi_max:-30

---

@LAT94LON46 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:46208818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3639 rate:8000
**ACOUSTIC** rms_mean:109 rms_max:1151 peak:2128 transients:1
**TRANSIENT** t_ms:46198713 stream:0xbb1177f2 wall:0 rms:1136

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:46222076 stream:0xbb1177f2 wall:0 window_ms:600060 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,0283cce0e689,e6b32d2cea8b,64677217947d,18a5ffbae2d6
**COVERED** windows:1 entities:8 window_ms:553198 first_t_ms:45622016 last_t_ms:45622016 covered_by:@LAT96LON3
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92 windows:1

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:46268818 stream:0xbb1177f2 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-82 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-72 rssi_med:-71 rssi_max:-71
**LINK** peer:0x00000010 proto:ble n:54 rssi_min:-46 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:34 rssi_min:-91 rssi_med:-86 rssi_max:-80
**LINK** peer:0x00000200 proto:espnow n:15 rssi_min:-33 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-31 rssi_med:-30 rssi_max:-30
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-43 rssi_med:-42 rssi_max:-42

---

@LAT94LON47 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:46268818 stream:0xbb1177f2 wall:0 window_ms:60000 blocks:3454 rate:8000
**ACOUSTIC** rms_mean:102 rms_max:233 peak:585 transients:0

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:46875524 stream:0xbb1177f2 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON44 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:46875524 stream:0xbb1177f2 wall:0 window_ms:60000 n:914
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:48029410 stream:0xbb1177f2 wall:0 window_ms:600001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:8 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,0283cce0e689,84a329c78fec,64677217947d,18a5ffbae2d6,e6b32d2cea8b
**COVERED** windows:1 entities:9 window_ms:553885 first_t_ms:47429409 last_t_ms:47429409 covered_by:@LAT96LON5
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93 windows:1

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:48690053 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON45 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:48690053 stream:0xbb1177f2 wall:0 window_ms:60000 n:928
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:49843161 stream:0xbb1177f2 wall:0 window_ms:599998 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-94
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,18a5ffbae2d6
**COVERED** windows:1 entities:7 window_ms:553110 first_t_ms:49243163 last_t_ms:49243163 covered_by:@LAT96LON7
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-85 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91 windows:1

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:50443734 stream:0xbb1177f2 wall:0 window_ms:600573 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
**CORE** entities:7 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,0283cce0e689,84a329c78fec,e6b32d2cea8b,18a5ffbae2d6

---

@LAT95LON46 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:50490099 stream:0xbb1177f2 wall:0 window_ms:60000 n:877
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:27628 window_ms:1740046 moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0 first_t_ms:48750053 last_t_ms:50430099 covered_by:@LAT95LON45

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:51090792 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON47 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51090792 stream:0xbb1177f2 wall:0 window_ms:60000 n:912
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52090418 stream:0xbb1177f2 wall:0 window_ms:60001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x427255ed wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52261 stream:0x427255ed wall:0 window_ms:60000 entities:12
**ENTITY** kind:wifi_ap id:c049effec409 n:1 rssi:-55
**ENTITY** kind:wifi_ap id:60f41901f0c6 n:1 rssi:-62
**ENTITY** kind:wifi_ap id:a2902da54f80 n:1 rssi:-63
**ENTITY** kind:wifi_ap id:acdf9f500570 n:1 rssi:-69
**ENTITY** kind:wifi_ap id:acdfbf510570 n:1 rssi:-69
**ENTITY** kind:wifi_ap id:98e7f4fafa31 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:186041a57253 n:1 rssi:-73
**ENTITY** kind:wifi_ap id:266a0e4d7e8c n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc5bd583b912 n:1 rssi:-75
**ENTITY** kind:wifi_ap id:c8d7194f3a7c n:1 rssi:-77
**ENTITY** kind:wifi_ap id:749be8a5a868 n:1 rssi:-78
**ENTITY** kind:wifi_ap id:14cb19b7ab58 n:1 rssi:-79
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x44c6e9e1 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52269 stream:0x44c6e9e1 wall:0 window_ms:60000 entities:12
**ENTITY** kind:wifi_ap id:60f41901f0c6 n:1 rssi:-48
**ENTITY** kind:wifi_ap id:a2902da54f80 n:1 rssi:-49
**ENTITY** kind:wifi_ap id:98e7f4fafa31 n:1 rssi:-54
**ENTITY** kind:wifi_ap id:266a0e4d7e8c n:1 rssi:-60
**ENTITY** kind:wifi_ap id:c049effec409 n:1 rssi:-61
**ENTITY** kind:wifi_ap id:acdfbf510570 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc5bd583b912 n:1 rssi:-70
**ENTITY** kind:wifi_ap id:acdf9f500570 n:1 rssi:-71
**ENTITY** kind:wifi_ap id:c8d7194f3a7c n:1 rssi:-74
**ENTITY** kind:wifi_ap id:749be8a5a868 n:1 rssi:-80
**ENTITY** kind:wifi_ap id:14cb19b7ab58 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:3c6ad297ddc7 n:1 rssi:-86
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:63223205 stream:0xbb1177f2 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:64376196 stream:0xbb1177f2 wall:0 window_ms:600003 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,84a329c78fec,18a5ffbae2d6
**COVERED** windows:1 entities:9 window_ms:552988 first_t_ms:63776193 last_t_ms:63776193 covered_by:@LAT96LON14
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92 windows:1
**COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:65023898 stream:0xbb1177f2 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:66177790 stream:0xbb1177f2 wall:0 window_ms:600027 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,84a329c78fec,e6b32d2cea8b,18a5ffbae2d6
**COVERED** windows:1 entities:8 window_ms:553865 first_t_ms:65577763 last_t_ms:65577763 covered_by:@LAT96LON16
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94 windows:1

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:66644641 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:67798680 stream:0xbb1177f2 wall:0 window_ms:600039 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:8 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,0283cce0e689,84a329c78fec,18a5ffbae2d6,e6b32d2cea8b,64677217947d
**COVERED** windows:1 entities:8 window_ms:554000 first_t_ms:67198641 last_t_ms:67198641 covered_by:@LAT96LON18
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94 windows:1

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:68249677 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:69215357 stream:0xbb1177f2 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-96
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:70369669 stream:0xbb1177f2 wall:0 window_ms:599998 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,84a329c78fec
**COVERED** windows:1 entities:6 window_ms:554314 first_t_ms:69769671 last_t_ms:69769671 covered_by:@LAT96LON21
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:71044762 stream:0xbb1177f2 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:72198901 stream:0xbb1177f2 wall:0 window_ms:600338 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:3 ids:f83eb025d3d2,bc102f237ace,e6b32d2cea8b
**COVERED** windows:1 entities:6 window_ms:553801 first_t_ms:71598563 last_t_ms:71598563 covered_by:@LAT96LON23
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92 windows:1

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:72851021 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:74005295 stream:0xbb1177f2 wall:0 window_ms:600089 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:4 ids:f83eb025d3d2,02c57d2e0f0d,e6b32d2cea8b,18a5ffbae2d6
**COVERED** windows:1 entities:4 window_ms:554185 first_t_ms:73405206 last_t_ms:73405206 covered_by:@LAT96LON25
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-30 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93 windows:1

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:74621633 stream:0xbb1177f2 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---


---

@LAT91LON0 | sid:76dbf602 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:190
rev:1
sal:16
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:47 violated:2 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON1 | sid:2b4da8c8 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:222
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:47 violated:0 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON2 | sid:ca9b482d | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:222
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:47 violated:0 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON3 | sid:8a93826d | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:136
rev:1
sal:40
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:44 violated:5 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON4 | sid:4dd86ced | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:206
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000011 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:39 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON5 | sid:150da582 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:144
rev:1
sal:32
touched:0
[/ew]

**LINK-STABLE** peer:0x00000011 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:40 violated:4 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:2 contradiction:1
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON6 | sid:05e0a4f2 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:150
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000012 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:11 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON7 | sid:7256ea07 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:150
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000012 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:11 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbab5e169 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin
