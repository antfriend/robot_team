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

@LAT91LON0 | sid:76dbf602 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:146
rev:1
sal:8
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:ble node:0x300
**TOUCHED** t_ms:43234099 stream:0xbb1177f2 wall:0 unix_s:0
**TALLY** met:17 violated:1 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON1 | sid:2b4da8c8 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:160
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TOUCHED** t_ms:43234099 stream:0xbb1177f2 wall:0 unix_s:0
**TALLY** met:16 violated:0 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON2 | sid:ca9b482d | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:160
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:43234099 stream:0xbb1177f2 wall:0 unix_s:0
**TALLY** met:16 violated:0 unobserved:1 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON3 | sid:8a93826d | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:92
rev:1
sal:32
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:espnow node:0x300
**TOUCHED** t_ms:43234099 stream:0xbb1177f2 wall:0 unix_s:0
**TALLY** met:14 violated:4 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON4 | sid:4dd86ced | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:154
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000011 proto:espnow node:0x300
**TOUCHED** t_ms:43234099 stream:0xbb1177f2 wall:0 unix_s:0
**TALLY** met:13 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON5 | sid:150da582 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:154
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000011 proto:ble node:0x300
**TOUCHED** t_ms:43234099 stream:0xbb1177f2 wall:0 unix_s:0
**TALLY** met:13 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON6 | sid:05e0a4f2 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:150
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000012 proto:espnow node:0x300
**TOUCHED** t_ms:43234099 stream:0xbb1177f2 wall:0 unix_s:0
**TALLY** met:11 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline

---

@LAT91LON7 | sid:7256ea07 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:150
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000012 proto:ble node:0x300
**TOUCHED** t_ms:43234099 stream:0xbb1177f2 wall:0 unix_s:0
**TALLY** met:11 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:12 method:sequential_fold_from_baseline
