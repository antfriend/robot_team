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


---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x82bca9f3 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:34089 stream:0x82bca9f3 wall:0 window_ms:62528 n:2
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:10 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:38367 stream:0x82bca9f3 wall:0 window_ms:66806 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-45
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT90LON13 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xfde301a1 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:51883 stream:0xfde301a1 wall:0 window_ms:60001 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51883 stream:0xfde301a1 wall:0 window_ms:60001 n:693
**MOTION** state:still moving_permille:5 dev_mean_mg:14 dev_max_mg:109 moving_ms:240
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:51883 stream:0xfde301a1 wall:0 window_ms:60001 blocks:2578 rate:8000
**ACOUSTIC** rms_mean:464 rms_max:24705 peak:32768 transients:41
**TRANSIENT** t_ms:41003 stream:0xfde301a1 wall:0 rms:23915

---

@LAT90LON14 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x7aabf338 wall:0 t_ms:569457 node:0x300 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x8dd93153 wall:0 t_ms:393715 node:0x300 from:0x100
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:449412 stream:0x8dd93153 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-67 rssi_med:-56 rssi_max:-47
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-60 rssi_med:-36 rssi_max:-30
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-51 rssi_med:-41 rssi_max:-35

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:449412 stream:0x8dd93153 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:449412 stream:0x8dd93153 wall:0 window_ms:60000 n:928
**MOTION** state:still moving_permille:53 dev_mean_mg:18 dev_max_mg:341 moving_ms:3006
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:449412 stream:0x8dd93153 wall:0 window_ms:60000 blocks:3371 rate:8000
**ACOUSTIC** rms_mean:244 rms_max:14416 peak:32768 transients:26
**TRANSIENT** t_ms:449306 stream:0x8dd93153 wall:0 rms:14416

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:87026 stream:0xb23c7677 wall:0 window_ms:60038
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-54 rssi_med:-39 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-61 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-83 rssi_med:-61 rssi_max:-53
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-59 rssi_med:-53 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:54 rssi_min:-76 rssi_med:-63 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-52 rssi_med:-41 rssi_max:-34
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-59 rssi_med:-50 rssi_max:-41
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-48 rssi_med:-40 rssi_max:-31

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:87026 stream:0xb23c7677 wall:0 window_ms:60038 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-44
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:87026 stream:0xb23c7677 wall:0 window_ms:60038 n:619
**MOTION** state:still moving_permille:48 dev_mean_mg:20 dev_max_mg:519 moving_ms:1994
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:87026 stream:0xb23c7677 wall:0 window_ms:60038 blocks:2296 rate:8000
**ACOUSTIC** rms_mean:2895 rms_max:26392 peak:32768 transients:120
**TRANSIENT** t_ms:68182 stream:0xb23c7677 wall:0 rms:25987

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:147026 stream:0xb23c7677 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-82 rssi_med:-54 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:53 rssi_min:-79 rssi_med:-54 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-37 rssi_med:-33 rssi_max:-31
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-74 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-57 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-56 rssi_med:-47 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-44 rssi_med:-39 rssi_max:-37
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-50 rssi_med:-45 rssi_max:-39

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:147026 stream:0xb23c7677 wall:0 window_ms:60000 blocks:1817 rate:8000
**ACOUSTIC** rms_mean:5922 rms_max:26630 peak:32768 transients:60
**TRANSIENT** t_ms:110487 stream:0xb23c7677 wall:0 rms:25591

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:207064 stream:0xb23c7677 wall:0 window_ms:60038
**LINK** peer:0x00000011 proto:ble n:68 rssi_min:-83 rssi_med:-57 rssi_max:-52
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-64 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-81 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-48 rssi_med:-43 rssi_max:-35
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-59 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-57 rssi_med:-43 rssi_max:-39
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-42 rssi_med:-39 rssi_max:-36
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-67 rssi_med:-54 rssi_max:-50

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:207064 stream:0xb23c7677 wall:0 window_ms:60038 blocks:1872 rate:8000
**ACOUSTIC** rms_mean:6023 rms_max:26380 peak:32768 transients:66
**TRANSIENT** t_ms:167328 stream:0xb23c7677 wall:0 rms:25791

---


---


---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5087799 stream:0x0a5e91fa wall:0 window_ms:60002
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-60 rssi_med:-49 rssi_max:-44

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5087799 stream:0x0a5e91fa wall:0 window_ms:60002 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:5087799 stream:0x0a5e91fa wall:0 window_ms:60002 n:489
**MOTION** state:still moving_permille:6 dev_mean_mg:15 dev_max_mg:96 moving_ms:180
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5087799 stream:0x0a5e91fa wall:0 window_ms:60002 blocks:1824 rate:8000
**ACOUSTIC** rms_mean:2397 rms_max:27243 peak:32768 transients:76
**TRANSIENT** t_ms:5084681 stream:0x0a5e91fa wall:0 rms:27243

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5147859 stream:0x0a5e91fa wall:0 window_ms:60060
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-64 rssi_med:-53 rssi_max:-44

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5147859 stream:0x0a5e91fa wall:0 window_ms:60060 blocks:1871 rate:8000
**ACOUSTIC** rms_mean:3911 rms_max:27833 peak:32768 transients:114
**TRANSIENT** t_ms:5126868 stream:0x0a5e91fa wall:0 rms:27820

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5207860 stream:0x0a5e91fa wall:0 window_ms:60001
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-59 rssi_med:-49 rssi_max:-42

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5207860 stream:0x0a5e91fa wall:0 window_ms:60001 blocks:1873 rate:8000
**ACOUSTIC** rms_mean:6628 rms_max:27574 peak:32768 transients:190
**TRANSIENT** t_ms:5186684 stream:0x0a5e91fa wall:0 rms:27574

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5267889 stream:0x0a5e91fa wall:0 window_ms:60029
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-53 rssi_med:-40 rssi_max:-38

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5267889 stream:0x0a5e91fa wall:0 window_ms:60029 blocks:1868 rate:8000
**ACOUSTIC** rms_mean:7070 rms_max:27540 peak:32768 transients:183
**TRANSIENT** t_ms:5264756 stream:0x0a5e91fa wall:0 rms:27496

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5327889 stream:0x0a5e91fa wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-59 rssi_med:-41 rssi_max:-37

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5327889 stream:0x0a5e91fa wall:0 window_ms:60000 blocks:1867 rate:8000
**ACOUSTIC** rms_mean:4426 rms_max:29208 peak:32768 transients:164
**TRANSIENT** t_ms:5295960 stream:0x0a5e91fa wall:0 rms:29208

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5387891 stream:0x0a5e91fa wall:0 window_ms:60002
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-50 rssi_med:-45 rssi_max:-41

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5387891 stream:0x0a5e91fa wall:0 window_ms:60002 blocks:1872 rate:8000
**ACOUSTIC** rms_mean:6011 rms_max:26540 peak:32768 transients:211
**TRANSIENT** t_ms:5337256 stream:0x0a5e91fa wall:0 rms:26140

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4412150 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-65 rssi_med:-52 rssi_max:-42

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4412150 stream:0x03316fb0 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4412150 stream:0x03316fb0 wall:0 window_ms:60000 n:512
**MOTION** state:still moving_permille:62 dev_mean_mg:20 dev_max_mg:135 moving_ms:3179
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4412150 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1908 rate:8000
**ACOUSTIC** rms_mean:4623 rms_max:25211 peak:32768 transients:65
**TRANSIENT** t_ms:4390186 stream:0x03316fb0 wall:0 rms:24373

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4915485 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:32 rssi_min:-70 rssi_med:-49 rssi_max:-46

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4915485 stream:0x03316fb0 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4915485 stream:0x03316fb0 wall:0 window_ms:60000 n:486
**MOTION** state:still moving_permille:88 dev_mean_mg:23 dev_max_mg:314 moving_ms:5162
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4915485 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1815 rate:8000
**ACOUSTIC** rms_mean:523 rms_max:27998 peak:32768 transients:73
**TRANSIENT** t_ms:4874914 stream:0x03316fb0 wall:0 rms:27998

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:4975540 stream:0x03316fb0 wall:0 window_ms:60055
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-52 rssi_med:-48 rssi_max:-46

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4975540 stream:0x03316fb0 wall:0 window_ms:60055 blocks:1867 rate:8000
**ACOUSTIC** rms_mean:1754 rms_max:11251 peak:32768 transients:83
**TRANSIENT** t_ms:4971368 stream:0x03316fb0 wall:0 rms:11251

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5035540 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-76 rssi_med:-51 rssi_max:-49

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5035540 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1873 rate:8000
**ACOUSTIC** rms_mean:2301 rms_max:8309 peak:20903 transients:32
**TRANSIENT** t_ms:4999257 stream:0x03316fb0 wall:0 rms:8309

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5095540 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-82 rssi_med:-55 rssi_max:-49

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5095540 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1868 rate:8000
**ACOUSTIC** rms_mean:4098 rms_max:16632 peak:32768 transients:15
**TRANSIENT** t_ms:5088068 stream:0x03316fb0 wall:0 rms:14850

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5155594 stream:0x03316fb0 wall:0 window_ms:60054
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-74 rssi_med:-57 rssi_max:-50

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5155594 stream:0x03316fb0 wall:0 window_ms:60054 blocks:1875 rate:8000
**ACOUSTIC** rms_mean:1489 rms_max:10585 peak:32768 transients:24
**TRANSIENT** t_ms:5107004 stream:0x03316fb0 wall:0 rms:10585

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5215660 stream:0x03316fb0 wall:0 window_ms:60066
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-73 rssi_med:-58 rssi_max:-51

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5215660 stream:0x03316fb0 wall:0 window_ms:60066 blocks:1875 rate:8000
**ACOUSTIC** rms_mean:308 rms_max:13966 peak:32768 transients:37
**TRANSIENT** t_ms:5194910 stream:0x03316fb0 wall:0 rms:13966

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5275695 stream:0x03316fb0 wall:0 window_ms:60035
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-74 rssi_med:-61 rssi_max:-53

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5275695 stream:0x03316fb0 wall:0 window_ms:60035 blocks:1869 rate:8000
**ACOUSTIC** rms_mean:1782 rms_max:16066 peak:28534 transients:131
**TRANSIENT** t_ms:5262959 stream:0x03316fb0 wall:0 rms:15125

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5335695 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-69 rssi_med:-59 rssi_max:-53

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5335695 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1873 rate:8000
**ACOUSTIC** rms_mean:696 rms_max:7134 peak:12851 transients:128
**TRANSIENT** t_ms:5279370 stream:0x03316fb0 wall:0 rms:7134

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5395695 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-70 rssi_med:-60 rssi_max:-54

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5395695 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1870 rate:8000
**ACOUSTIC** rms_mean:684 rms_max:5807 peak:13610 transients:106
**TRANSIENT** t_ms:5359799 stream:0x03316fb0 wall:0 rms:5807

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5455717 stream:0x03316fb0 wall:0 window_ms:60022
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-65 rssi_med:-63 rssi_max:-62

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5455717 stream:0x03316fb0 wall:0 window_ms:60022 blocks:1871 rate:8000
**ACOUSTIC** rms_mean:317 rms_max:2613 peak:6183 transients:84
**TRANSIENT** t_ms:5400157 stream:0x03316fb0 wall:0 rms:2516

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5515717 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-64 rssi_med:-61 rssi_max:-60

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5515717 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1873 rate:8000
**ACOUSTIC** rms_mean:158 rms_max:1484 peak:3493 transients:16
**TRANSIENT** t_ms:5456516 stream:0x03316fb0 wall:0 rms:1484

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5575719 stream:0x03316fb0 wall:0 window_ms:60002
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-64 rssi_med:-60 rssi_max:-53

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5575719 stream:0x03316fb0 wall:0 window_ms:60002 blocks:1871 rate:8000
**ACOUSTIC** rms_mean:637 rms_max:3415 peak:7688 transients:34
**TRANSIENT** t_ms:5534305 stream:0x03316fb0 wall:0 rms:3415

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5635784 stream:0x03316fb0 wall:0 window_ms:60065
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-68 rssi_med:-57 rssi_max:-53

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5635784 stream:0x03316fb0 wall:0 window_ms:60065 blocks:1871 rate:8000
**ACOUSTIC** rms_mean:461 rms_max:1474 peak:3462 transients:2
**TRANSIENT** t_ms:5608178 stream:0x03316fb0 wall:0 rms:1190

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5695846 stream:0x03316fb0 wall:0 window_ms:60062
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-61 rssi_med:-56 rssi_max:-50

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5695846 stream:0x03316fb0 wall:0 window_ms:60062 blocks:1875 rate:8000
**ACOUSTIC** rms_mean:701 rms_max:3894 peak:9004 transients:46
**TRANSIENT** t_ms:5665748 stream:0x03316fb0 wall:0 rms:3894

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5755919 stream:0x03316fb0 wall:0 window_ms:60073
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-63 rssi_med:-56 rssi_max:-53

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5755919 stream:0x03316fb0 wall:0 window_ms:60073 blocks:1875 rate:8000
**ACOUSTIC** rms_mean:672 rms_max:3825 peak:9127 transients:25
**TRANSIENT** t_ms:5709733 stream:0x03316fb0 wall:0 rms:3825

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5815958 stream:0x03316fb0 wall:0 window_ms:60039
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-71 rssi_med:-61 rssi_max:-51

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5815958 stream:0x03316fb0 wall:0 window_ms:60039 blocks:1868 rate:8000
**ACOUSTIC** rms_mean:569 rms_max:4665 peak:10938 transients:28
**TRANSIENT** t_ms:5783792 stream:0x03316fb0 wall:0 rms:4665

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5875958 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-69 rssi_med:-65 rssi_max:-53

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5875958 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1869 rate:8000
**ACOUSTIC** rms_mean:759 rms_max:4636 peak:10012 transients:99
**TRANSIENT** t_ms:5819777 stream:0x03316fb0 wall:0 rms:4636

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5936023 stream:0x03316fb0 wall:0 window_ms:60065
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-68 rssi_med:-62 rssi_max:-54

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5936023 stream:0x03316fb0 wall:0 window_ms:60065 blocks:1875 rate:8000
**ACOUSTIC** rms_mean:744 rms_max:3404 peak:7609 transients:61
**TRANSIENT** t_ms:5881430 stream:0x03316fb0 wall:0 rms:3050

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:5996023 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-68 rssi_med:-62 rssi_max:-51

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:5996023 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1870 rate:8000
**ACOUSTIC** rms_mean:550 rms_max:2844 peak:6636 transients:61
**TRANSIENT** t_ms:5942342 stream:0x03316fb0 wall:0 rms:2835

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6056025 stream:0x03316fb0 wall:0 window_ms:60002
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-69 rssi_med:-59 rssi_max:-53

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6056025 stream:0x03316fb0 wall:0 window_ms:60002 blocks:1871 rate:8000
**ACOUSTIC** rms_mean:617 rms_max:5224 peak:9125 transients:79
**TRANSIENT** t_ms:6043307 stream:0x03316fb0 wall:0 rms:5224

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6068248 stream:0x03316fb0 wall:0 window_ms:599975 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:5 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,84a329c78fec
**COVERED** windows:1 entities:5 window_ms:552788 first_t_ms:5468273 last_t_ms:5468273 covered_by:@LAT96LON36
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6116091 stream:0x03316fb0 wall:0 window_ms:60066
**LINK** peer:0x00000100 proto:espnow n:32 rssi_min:-61 rssi_med:-55 rssi_max:-51

---

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6116091 stream:0x03316fb0 wall:0 window_ms:60066 blocks:1864 rate:8000
**ACOUSTIC** rms_mean:621 rms_max:3263 peak:9252 transients:71
**TRANSIENT** t_ms:6113817 stream:0x03316fb0 wall:0 rms:3140

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6176091 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-63 rssi_med:-59 rssi_max:-51

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6176091 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1850 rate:8000
**ACOUSTIC** rms_mean:556 rms_max:5298 peak:13253 transients:63
**TRANSIENT** t_ms:6119662 stream:0x03316fb0 wall:0 rms:5298

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6236091 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-60 rssi_med:-58 rssi_max:-52

---

@LAT94LON34 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6236091 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1855 rate:8000
**ACOUSTIC** rms_mean:471 rms_max:3006 peak:7358 transients:50
**TRANSIENT** t_ms:6218882 stream:0x03316fb0 wall:0 rms:2808

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6296152 stream:0x03316fb0 wall:0 window_ms:60061
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-59 rssi_med:-55 rssi_max:-51

---

@LAT94LON35 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6296152 stream:0x03316fb0 wall:0 window_ms:60061 blocks:1856 rate:8000
**ACOUSTIC** rms_mean:762 rms_max:6307 peak:14041 transients:85
**TRANSIENT** t_ms:6272419 stream:0x03316fb0 wall:0 rms:6307

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6356178 stream:0x03316fb0 wall:0 window_ms:60026
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-66 rssi_med:-60 rssi_max:-53

---

@LAT94LON36 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6356178 stream:0x03316fb0 wall:0 window_ms:60026 blocks:1845 rate:8000
**ACOUSTIC** rms_mean:620 rms_max:3647 peak:8150 transients:70
**TRANSIENT** t_ms:6354363 stream:0x03316fb0 wall:0 rms:3647

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6416185 stream:0x03316fb0 wall:0 window_ms:60007
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-76 rssi_med:-58 rssi_max:-52

---

@LAT94LON37 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6416185 stream:0x03316fb0 wall:0 window_ms:60007 blocks:1858 rate:8000
**ACOUSTIC** rms_mean:794 rms_max:6397 peak:30721 transients:70
**TRANSIENT** t_ms:6368871 stream:0x03316fb0 wall:0 rms:6397

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6476247 stream:0x03316fb0 wall:0 window_ms:60062
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-71 rssi_med:-61 rssi_max:-53

---

@LAT94LON38 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6476247 stream:0x03316fb0 wall:0 window_ms:60062 blocks:1858 rate:8000
**ACOUSTIC** rms_mean:613 rms_max:3797 peak:7616 transients:67
**TRANSIENT** t_ms:6417339 stream:0x03316fb0 wall:0 rms:3797

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6536247 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-64 rssi_med:-62 rssi_max:-56

---

@LAT94LON39 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6536247 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1847 rate:8000
**ACOUSTIC** rms_mean:497 rms_max:3260 peak:7652 transients:59
**TRANSIENT** t_ms:6534350 stream:0x03316fb0 wall:0 rms:3260

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6596247 stream:0x03316fb0 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-65 rssi_med:-62 rssi_max:-52

---

@LAT94LON40 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6596247 stream:0x03316fb0 wall:0 window_ms:60000 blocks:1856 rate:8000
**ACOUSTIC** rms_mean:415 rms_max:3630 peak:8445 transients:73
**TRANSIENT** t_ms:6595765 stream:0x03316fb0 wall:0 rms:3630

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6663511 stream:0x03316fb0 wall:0 window_ms:67264
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-61 rssi_med:-55 rssi_max:-52

---

@LAT94LON41 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6663511 stream:0x03316fb0 wall:0 window_ms:67264 blocks:1836 rate:8000
**ACOUSTIC** rms_mean:640 rms_max:5648 peak:12565 transients:69
**TRANSIENT** t_ms:6627791 stream:0x03316fb0 wall:0 rms:5648

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6723571 stream:0x03316fb0 wall:0 window_ms:60060
**LINK** peer:0x00000100 proto:espnow n:35 rssi_min:-65 rssi_med:-60 rssi_max:-60

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:6723571 stream:0x03316fb0 wall:0 window_ms:60060 n:524
**MOTION** state:still moving_permille:0 dev_mean_mg:13 dev_max_mg:19 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:14791 window_ms:1748026 moving_permille:8 dev_mean_mg:14 dev_max_mg:437 moving_ms:15364 first_t_ms:4975540 last_t_ms:6663511 covered_by:@LAT95LON6

---

@LAT94LON42 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6723571 stream:0x03316fb0 wall:0 window_ms:60060 blocks:1822 rate:8000
**ACOUSTIC** rms_mean:516 rms_max:3887 peak:9781 transients:32
**TRANSIENT** t_ms:6673780 stream:0x03316fb0 wall:0 rms:3887

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6783576 stream:0x03316fb0 wall:0 window_ms:60005
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-62 rssi_med:-60 rssi_max:-60

---

@LAT94LON43 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6783576 stream:0x03316fb0 wall:0 window_ms:60005 blocks:1855 rate:8000
**ACOUSTIC** rms_mean:370 rms_max:1194 peak:2120 transients:1
**TRANSIENT** t_ms:6772597 stream:0x03316fb0 wall:0 rms:1107

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6843584 stream:0x03316fb0 wall:0 window_ms:60008
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-65 rssi_med:-60 rssi_max:-53

---

@LAT94LON44 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6843584 stream:0x03316fb0 wall:0 window_ms:60008 blocks:1856 rate:8000
**ACOUSTIC** rms_mean:711 rms_max:6291 peak:18613 transients:29
**TRANSIENT** t_ms:6802471 stream:0x03316fb0 wall:0 rms:6291

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6903589 stream:0x03316fb0 wall:0 window_ms:60005
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-71 rssi_med:-64 rssi_max:-54

---

@LAT94LON45 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6903589 stream:0x03316fb0 wall:0 window_ms:60005 blocks:1823 rate:8000
**ACOUSTIC** rms_mean:746 rms_max:3505 peak:8100 transients:63
**TRANSIENT** t_ms:6867536 stream:0x03316fb0 wall:0 rms:3505

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:6963611 stream:0x03316fb0 wall:0 window_ms:60022
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-83 rssi_med:-60 rssi_max:-53

---

@LAT94LON46 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:6963611 stream:0x03316fb0 wall:0 window_ms:60022 blocks:1856 rate:8000
**ACOUSTIC** rms_mean:652 rms_max:3612 peak:8682 transients:40
**TRANSIENT** t_ms:6929806 stream:0x03316fb0 wall:0 rms:3539

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7024604 stream:0x03316fb0 wall:0 window_ms:60993
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-64 rssi_med:-57 rssi_max:-53

---

@LAT94LON47 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7024604 stream:0x03316fb0 wall:0 window_ms:60993 blocks:1854 rate:8000
**ACOUSTIC** rms_mean:820 rms_max:4508 peak:8583 transients:23
**TRANSIENT** t_ms:6998905 stream:0x03316fb0 wall:0 rms:3405

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7084665 stream:0x03316fb0 wall:0 window_ms:60061
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-67 rssi_med:-56 rssi_max:-52

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7444256 stream:0x03316fb0 wall:0 window_ms:60000 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7444256 stream:0x03316fb0 wall:0 window_ms:60000 n:924
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:17 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8597537 stream:0x03316fb0 wall:0 window_ms:600001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-95
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:4 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b
**COVERED** windows:1 entities:7 window_ms:553280 first_t_ms:7997536 last_t_ms:7997536 covered_by:@LAT96LON38
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94 windows:1

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9242548 stream:0x03316fb0 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:9242548 stream:0x03316fb0 wall:0 window_ms:60000 n:927
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10395653 stream:0x03316fb0 wall:0 window_ms:599998 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,02c57d2e0f0d,bc102f237ace,e6b32d2cea8b,84a329c78fec,18a5ffbae2d6
**COVERED** windows:1 entities:6 window_ms:553107 first_t_ms:9795655 last_t_ms:9795655 covered_by:@LAT96LON40
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-39 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89 windows:1

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:11042555 stream:0x03316fb0 wall:0 window_ms:60000 n:828
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:still windows:29 n:28749 window_ms:1740007 moving_permille:0 dev_mean_mg:10 dev_max_mg:16 moving_ms:0 first_t_ms:9302548 last_t_ms:10982555 covered_by:@LAT95LON9

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11246454 stream:0x03316fb0 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:11246454 stream:0x03316fb0 wall:0 window_ms:60000 n:918
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:12400106 stream:0x03316fb0 wall:0 window_ms:599998 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:6 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,64677217947d,18a5ffbae2d6
**COVERED** windows:1 entities:7 window_ms:553654 first_t_ms:11800108 last_t_ms:11800108 covered_by:@LAT96LON42
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86 windows:1
**COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90 windows:1

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:13047149 stream:0x03316fb0 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:13047149 stream:0x03316fb0 wall:0 window_ms:60000 n:919
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:18 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:14200778 stream:0x03316fb0 wall:0 window_ms:599999 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
**CORE** entities:7 ids:f83eb025d3d2,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,84a329c78fec,5ce28c488e0c,18a5ffbae2d6
**COVERED** windows:1 entities:8 window_ms:553630 first_t_ms:13600779 last_t_ms:13600779 covered_by:@LAT96LON44
**COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
**COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73 windows:1
**COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77 windows:1
**COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83 windows:1
**COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
**COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90 windows:1
**COVERED-ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91 windows:1
**COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52155 stream:0x0dad56fd wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52155 stream:0x0dad56fd wall:0 window_ms:60000 n:923
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:89189 stream:0x5b53f35b wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
**CORE** entities:0

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:89189 stream:0x5b53f35b wall:0 window_ms:60000 n:925
**MOTION** state:still moving_permille:10 dev_mean_mg:9 dev_max_mg:815 moving_ms:600
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1580133 stream:0xc48b6525 wall:0 window_ms:60000 n:908
**MOTION** state:still moving_permille:71 dev_mean_mg:21 dev_max_mg:258 moving_ms:3998
**RUN** windows_since_last:1 reason:first max_run:30

---


---


---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52086 stream:0x6223aa03 wall:0 window_ms:60028 n:627
**MOTION** state:still moving_permille:89 dev_mean_mg:28 dev_max_mg:372 moving_ms:5281
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT101LON0 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:61 half_life_ms:600000 reinforced:0 last_ms:1940
t_ms:53670 stream:0x6223aa03 wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0000 cap_epoch:5
**TRACE** copresence:125 half_life_ms:600000 reinforced:2 last_ms:61612
t_ms:53670 stream:0x6223aa03 wall:0

---

@LAT101LON2 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:61 half_life_ms:600000 reinforced:0 last_ms:1940
t_ms:53670 stream:0x6223aa03 wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:61 half_life_ms:600000 reinforced:0 last_ms:1940
t_ms:53670 stream:0x6223aa03 wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:61 half_life_ms:600000 reinforced:0 last_ms:1940
t_ms:53670 stream:0x6223aa03 wall:0

---


---


---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60040 stream:0x40658fbe wall:0 window_ms:60000 n:909
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:19 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51856 stream:0x2bf1375d wall:0 window_ms:60028 n:536
**MOTION** state:still moving_permille:31 dev_mean_mg:14 dev_max_mg:542 moving_ms:1020
**RUN** windows_since_last:1 reason:first max_run:30

---


---


---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51949 stream:0xc4223c17 wall:0 window_ms:60000 n:909
**MOTION** state:still moving_permille:2 dev_mean_mg:12 dev_max_mg:228 moving_ms:1000
**RUN** windows_since_last:1 reason:first max_run:30

---


---


---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51788 stream:0x292b0620 wall:0 window_ms:60000 n:904
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

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


---


---


---


---


---


---


---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52255 stream:0x6dfb3395 wall:0 window_ms:60000 n:917
**MOTION** state:still moving_permille:0 dev_mean_mg:11 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---


---


---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51778 stream:0xefbd2d4f wall:0 window_ms:60000 n:905
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

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


---


---


---


---


---


---


---


---


---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51987 stream:0x1ad97e1e wall:0 window_ms:60000 n:909
**MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52175 stream:0x30ebef97 wall:0 window_ms:60000 n:913
**MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:18 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51695 stream:0x7dc26589 wall:0 window_ms:60000 n:905
**MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:11 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51780 stream:0xd57649e4 wall:0 window_ms:60000 n:908
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51996 stream:0x6fdf7a92 wall:0 window_ms:60000 n:909
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:10 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON28 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52171 stream:0x1fc582d4 wall:0 window_ms:60000 n:914
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:21 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON29 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51693 stream:0x1d8a50cc wall:0 window_ms:60000 n:905
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:15 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON30 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51831 stream:0x183ed39d wall:0 window_ms:60001 n:909
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON31 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51992 stream:0x4eae26e7 wall:0 window_ms:60000 n:908
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:22 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON32 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52169 stream:0xf1d8dd4c wall:0 window_ms:60000 n:912
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---


---


---

@LAT95LON33 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52345 stream:0x54cd5254 wall:0 window_ms:60000 n:916
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---


---

@LAT95LON34 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52259 stream:0x093b299b wall:0 window_ms:60000 n:922
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:14 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON35 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51776 stream:0x2d55a432 wall:0 window_ms:60000 n:904
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON36 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51966 stream:0x8aa779f8 wall:0 window_ms:60000 n:908
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON37 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52143 stream:0xfebe7baf wall:0 window_ms:60000 n:912
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---

@LAT95LON38 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51859 stream:0x8265216d wall:0 window_ms:60000 n:904
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---

@LAT95LON39 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52249 stream:0xc050ca97 wall:0 window_ms:60000 n:922
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON40 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51770 stream:0x2d51fd2d wall:0 window_ms:60000 n:903
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON41 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51958 stream:0xd87c9db5 wall:0 window_ms:60000 n:913
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON42 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52135 stream:0x4c469062 wall:0 window_ms:60000 n:916
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON43 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52329 stream:0xa8434f1a wall:0 window_ms:60000 n:923
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON44 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51787 stream:0xe01b78dc wall:0 window_ms:60000 n:909
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON45 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51977 stream:0xa6135890 wall:0 window_ms:60000 n:915
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON46 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:52159 stream:0x4b608bcc wall:0 window_ms:60001 n:914
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON47 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:51677 stream:0x4529f078 wall:0 window_ms:60000 n:908
**MOTION** state:still moving_permille:0 dev_mean_mg:10 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---


---


---


---


---


---


---


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
**TOUCHED** t_ms:26188454 stream:0x4a194eda wall:0 unix_s:0
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
**TOUCHED** t_ms:26188454 stream:0x4a194eda wall:0 unix_s:0
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
**TOUCHED** t_ms:26188454 stream:0x4a194eda wall:0 unix_s:0
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
**TOUCHED** t_ms:26188454 stream:0x4a194eda wall:0 unix_s:0
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
**TOUCHED** t_ms:26188454 stream:0x4a194eda wall:0 unix_s:0
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
**TOUCHED** t_ms:26188454 stream:0x4a194eda wall:0 unix_s:0
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
**TOUCHED** t_ms:26188454 stream:0x4a194eda wall:0 unix_s:0
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
**TOUCHED** t_ms:26188454 stream:0x4a194eda wall:0 unix_s:0
**TALLY** met:11 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline
