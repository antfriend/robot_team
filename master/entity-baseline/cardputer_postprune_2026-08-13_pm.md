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

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xcab73254 wall:0 t_ms:4900 node:0x300 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbb1177f2 wall:0 t_ms:4006646 node:0x300 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

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

@LAT93LON1 | created:0 | updated:0 | relates:senses@LAT0LON0,derived_from@LAT95LON26,derived_from@LAT95LON27

**TRANSITION** t_ms:37498518 stream:0xbb1177f2 wall:0 node:0x300 from:still to:moving dt_ms:60000 dt_across_merge:0
  @PERCEPT:before state:still t_ms:37438518 window_ms:60000 n:977 moving_permille:0 dev_mean_mg:11 dev_max_mg:14 moving_ms:0 lane:@LAT95LON26+28
  @PERCEPT:after state:moving t_ms:37498518 window_ms:60000 n:974 moving_permille:152 dev_mean_mg:31 dev_max_mg:592 moving_ms:9349 lane:@LAT95LON27+0
**DELTA** edge:became d_permille:152 d_dev_mean_mg:20 d_dev_max_mg:578

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x89af9f2e wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

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

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xbab5e169 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xc7038e68 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:39666 stream:0xc7038e68 wall:0 window_ms:70009 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:8470d7633e07 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-98
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x1a8126a3 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52057 stream:0x1a8126a3 wall:0 window_ms:60000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-84
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:2 removed:48 last_lon:47 t_ms:101971 stream:0x1a8126a3 wall:0 node:0x00000300

---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:1 removed:48 last_lon:47 t_ms:0 stream:0x7eeae016 wall:0 node:0x00000300

---

@LAT100LON5 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:2 removed:48 last_lon:47 t_ms:0 stream:0x00000000 wall:0 node:0x00000300

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
