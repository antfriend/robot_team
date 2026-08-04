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

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60000 synced:0 window_ms:60000 n:777
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:16 moving_ms:0

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60000 synced:0 window_ms:60000 blocks:2911 rate:8000
**ACOUSTIC** rms_mean:138 rms_max:2061 peak:7365 transients:2
**TRANSIENT** t_ms:15016 rms:2061 synced:0

---

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:120000 synced:0 node:0x300 acting:@LAT95LON0 observed_in:@LAT97LON1 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-45 delta:-2 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-44 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:2 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-58 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-45 delta:2 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-38 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-38 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:120000 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:20 moving_ms:0

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:120000 synced:0 window_ms:60000 blocks:3732 rate:8000
**ACOUSTIC** rms_mean:191 rms_max:17259 peak:30154 transients:9
**TRANSIENT** t_ms:111878 rms:16241 synced:0

---

@LAT92LON1 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON2,senses@LAT0LON0

**OUTCOME** t_ms:180000 synced:0 node:0x300 acting:@LAT95LON1 observed_in:@LAT97LON2 band_dbm:6 met:6 violated:2 unobserved:0 streak:1
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-73 delta:-15 verdict:violated
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-53 delta:2 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-45 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-43 delta:2 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-38 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-45 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-66 delta:-21 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:180000 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:180000 synced:0 window_ms:60000 blocks:3738 rate:8000
**ACOUSTIC** rms_mean:117 rms_max:495 peak:899 transients:0

---

@LAT92LON2 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON3,senses@LAT0LON0

**OUTCOME** t_ms:240001 synced:0 node:0x300 acting:@LAT95LON2 observed_in:@LAT97LON3 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-73 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-71 delta:2 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-66 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-63 delta:3 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-40 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:240001 synced:0 window_ms:60001 n:991
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:18 moving_ms:0

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:240001 synced:0 window_ms:60001 blocks:3711 rate:8000
**ACOUSTIC** rms_mean:140 rms_max:4184 peak:4978 transients:2
**TRANSIENT** t_ms:222074 rms:2617 synced:0

---

@LAT92LON3 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON4,senses@LAT0LON0

**OUTCOME** t_ms:300001 synced:0 node:0x300 acting:@LAT95LON3 observed_in:@LAT97LON4 band_dbm:6 met:6 violated:2 unobserved:0 streak:1
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-71 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-96 delta:-25 verdict:violated
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-63 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-91 delta:-28 verdict:violated
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-40 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:300001 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:300001 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:85 rms_max:575 peak:774 transients:0

---

@LAT92LON4 | created:0 | updated:0 | relates:testifies_about@LAT95LON4,derived_from@LAT97LON5,senses@LAT0LON0

**OUTCOME** t_ms:360001 synced:0 node:0x300 acting:@LAT95LON4 observed_in:@LAT97LON5 band_dbm:6 met:7 violated:0 unobserved:1 streak:0
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-91 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-93 delta:-2 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-96 band:6
**OBSERVED** peer:0x00000200 proto:ble verdict:unobserved
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:360001 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:360001 synced:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:117 rms_max:4249 peak:4880 transients:5
**TRANSIENT** t_ms:304231 rms:4249 synced:0

---

@LAT92LON5 | created:0 | updated:0 | relates:testifies_about@LAT95LON5,derived_from@LAT97LON6,senses@LAT0LON0

**OUTCOME** t_ms:420002 synced:0 node:0x300 acting:@LAT95LON5 observed_in:@LAT97LON6 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-93 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-91 delta:2 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:420002 synced:0 window_ms:60001 n:986
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:420002 synced:0 window_ms:60001 blocks:3692 rate:8000
**ACOUSTIC** rms_mean:131 rms_max:2705 peak:5169 transients:6
**TRANSIENT** t_ms:370581 rms:2016 synced:0

---

@LAT92LON6 | created:0 | updated:0 | relates:testifies_about@LAT95LON6,derived_from@LAT97LON7,senses@LAT0LON0

**OUTCOME** t_ms:480002 synced:0 node:0x300 acting:@LAT95LON6 observed_in:@LAT97LON7 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-53 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-91 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-92 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:480002 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:480002 synced:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:145 rms_max:4255 peak:4692 transients:9
**TRANSIENT** t_ms:457344 rms:4255 synced:0

---

@LAT92LON7 | created:0 | updated:0 | relates:testifies_about@LAT95LON7,derived_from@LAT97LON8,senses@LAT0LON0

**OUTCOME** t_ms:540002 synced:0 node:0x300 acting:@LAT95LON7 observed_in:@LAT97LON8 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-41 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-57 delta:-4 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-59 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-92 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-92 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:540002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:540002 synced:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:132 rms_max:7006 peak:7713 transients:9
**TRANSIENT** t_ms:509511 rms:7006 synced:0

---

@LAT92LON8 | created:0 | updated:0 | relates:testifies_about@LAT95LON8,derived_from@LAT97LON9,senses@LAT0LON0

**OUTCOME** t_ms:600002 synced:0 node:0x300 acting:@LAT95LON8 observed_in:@LAT97LON9 band_dbm:6 met:6 violated:2 unobserved:0 streak:1
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-59 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-92 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-55 delta:37 verdict:violated
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-88 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-68 delta:20 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:600002 synced:0 window_ms:60000 n:986
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:600002 synced:0 window_ms:60000 blocks:3692 rate:8000
**ACOUSTIC** rms_mean:142 rms_max:4732 peak:9167 transients:8
**TRANSIENT** t_ms:557675 rms:3638 synced:0

---

@LAT92LON9 | created:0 | updated:0 | relates:testifies_about@LAT95LON9,derived_from@LAT97LON10,senses@LAT0LON0

**OUTCOME** t_ms:660002 synced:0 node:0x300 acting:@LAT95LON9 observed_in:@LAT97LON10 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-68 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-66 delta:2 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-41 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-55 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-59 delta:-4 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-59 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:660002 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:660002 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:180 rms_max:4812 peak:17910 transients:10
**TRANSIENT** t_ms:606187 rms:2231 synced:0

---

@LAT92LON10 | created:0 | updated:0 | relates:testifies_about@LAT95LON10,derived_from@LAT97LON11,senses@LAT0LON0

**OUTCOME** t_ms:720002 synced:0 node:0x300 acting:@LAT95LON10 observed_in:@LAT97LON11 band_dbm:6 met:7 violated:1 unobserved:0 streak:1
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:-2 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-66 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-62 delta:4 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-59 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-47 delta:12 verdict:violated
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-57 delta:2 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-41 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:720002 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:720002 synced:0 window_ms:60000 blocks:3735 rate:8000
**ACOUSTIC** rms_mean:136 rms_max:969 peak:5484 transients:1
**TRANSIENT** t_ms:717078 rms:969 synced:0

---

@LAT92LON11 | created:0 | updated:0 | relates:testifies_about@LAT95LON11,derived_from@LAT97LON12,senses@LAT0LON0

**OUTCOME** t_ms:780002 synced:0 node:0x300 acting:@LAT95LON11 observed_in:@LAT97LON12 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-62 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-64 delta:-2 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-57 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-49 delta:-2 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-57 delta:-2 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:780002 synced:0 window_ms:60000 n:982
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:16 moving_ms:0

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:780002 synced:0 window_ms:60000 blocks:3678 rate:8000
**ACOUSTIC** rms_mean:131 rms_max:609 peak:3743 transients:0

---

@LAT92LON12 | created:0 | updated:0 | relates:testifies_about@LAT95LON12,derived_from@LAT97LON13,senses@LAT0LON0

**OUTCOME** t_ms:840002 synced:0 node:0x300 acting:@LAT95LON12 observed_in:@LAT97LON13 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-57 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-39 delta:3 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-64 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-59 delta:5 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-55 delta:2 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-55 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-49 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-46 delta:3 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-44 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:840002 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:840002 synced:0 window_ms:60000 blocks:3734 rate:8000
**ACOUSTIC** rms_mean:376 rms_max:23411 peak:32768 transients:12
**TRANSIENT** t_ms:839335 rms:23058 synced:0

---

@LAT92LON13 | created:0 | updated:0 | relates:testifies_about@LAT95LON13,derived_from@LAT97LON14,senses@LAT0LON0

**OUTCOME** t_ms:900002 synced:0 node:0x300 acting:@LAT95LON13 observed_in:@LAT97LON14 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-64 delta:-5 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-44 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-46 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-51 delta:-5 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-56 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-38 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:-3 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:900002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:20 moving_ms:0

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:900002 synced:0 window_ms:60000 blocks:3727 rate:8000
**ACOUSTIC** rms_mean:226 rms_max:24518 peak:32768 transients:6
**TRANSIENT** t_ms:851544 rms:24518 synced:0

---

@LAT92LON14 | created:0 | updated:0 | relates:testifies_about@LAT95LON14,derived_from@LAT97LON15,senses@LAT0LON0

**OUTCOME** t_ms:960002 synced:0 node:0x300 acting:@LAT95LON14 observed_in:@LAT97LON15 band_dbm:6 met:6 violated:2 unobserved:0 streak:1
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-59 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-51 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-87 delta:-36 verdict:violated
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-64 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-83 delta:-19 verdict:violated
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-38 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-38 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-43 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-43 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:960002 synced:0 window_ms:60000 n:982
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:30 moving_ms:0

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:960002 synced:0 window_ms:60000 blocks:3671 rate:8000
**ACOUSTIC** rms_mean:189 rms_max:5476 peak:6188 transients:9
**TRANSIENT** t_ms:909575 rms:5476 synced:0

---

@LAT92LON15 | created:0 | updated:0 | relates:testifies_about@LAT95LON15,derived_from@LAT97LON16,senses@LAT0LON0

**OUTCOME** t_ms:1020002 synced:0 node:0x300 acting:@LAT95LON15 observed_in:@LAT97LON16 band_dbm:6 met:7 violated:0 unobserved:1 streak:0
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:-1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-41 delta:2 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-41 delta:2 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-57 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-87 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-93 delta:-6 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-38 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-83 band:6
**OBSERVED** peer:0x00000200 proto:ble verdict:unobserved
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1020002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:26 moving_ms:0

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1020002 synced:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:144 rms_max:3582 peak:12291 transients:2
**TRANSIENT** t_ms:995817 rms:3582 synced:0

---

@LAT92LON16 | created:0 | updated:0 | relates:testifies_about@LAT95LON16,derived_from@LAT97LON17,senses@LAT0LON0

**OUTCOME** t_ms:1080002 synced:0 node:0x300 acting:@LAT95LON16 observed_in:@LAT97LON17 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-57 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-56 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-41 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-55 delta:1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-93 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-92 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1080002 synced:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1080002 synced:0 window_ms:60000 blocks:3734 rate:8000
**ACOUSTIC** rms_mean:135 rms_max:477 peak:1680 transients:0

---

@LAT92LON17 | created:0 | updated:0 | relates:testifies_about@LAT95LON17,derived_from@LAT97LON18,senses@LAT0LON0

**OUTCOME** t_ms:1140002 synced:0 node:0x300 acting:@LAT95LON17 observed_in:@LAT97LON18 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-41 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-42 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-55 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-92 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-93 delta:-1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-38 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1140002 synced:0 window_ms:60000 n:977
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1140002 synced:0 window_ms:60000 blocks:3656 rate:8000
**ACOUSTIC** rms_mean:136 rms_max:1290 peak:4516 transients:1
**TRANSIENT** t_ms:1128983 rms:1290 synced:0

---

@LAT92LON18 | created:0 | updated:0 | relates:testifies_about@LAT95LON18,derived_from@LAT97LON19,senses@LAT0LON0

**OUTCOME** t_ms:1200002 synced:0 node:0x300 acting:@LAT95LON18 observed_in:@LAT97LON19 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-53 delta:3 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-43 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-56 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-42 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-38 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-39 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-93 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-93 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1200002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:32 moving_ms:0

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1200002 synced:0 window_ms:60000 blocks:3731 rate:8000
**ACOUSTIC** rms_mean:140 rms_max:1135 peak:2113 transients:2
**TRANSIENT** t_ms:1149091 rms:1135 synced:0

---

@LAT92LON19 | created:0 | updated:0 | relates:testifies_about@LAT95LON19,derived_from@LAT97LON20,senses@LAT0LON0

**OUTCOME** t_ms:1260002 synced:0 node:0x300 acting:@LAT95LON19 observed_in:@LAT97LON20 band_dbm:6 met:5 violated:2 unobserved:0 streak:1
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-53 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-49 delta:4 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-56 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-59 delta:-3 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-43 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-48 delta:-5 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-63 delta:-5 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-93 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-92 delta:1 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-39 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-31 delta:8 verdict:violated
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-42 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-49 delta:-7 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1260002 synced:0 window_ms:60000 n:994
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1260002 synced:0 window_ms:60000 blocks:3720 rate:8000
**ACOUSTIC** rms_mean:135 rms_max:2603 peak:7462 transients:1
**TRANSIENT** t_ms:1255811 rms:2603 synced:0

---

@LAT92LON20 | created:0 | updated:0 | relates:testifies_about@LAT95LON20,derived_from@LAT97LON21,senses@LAT0LON0

**OUTCOME** t_ms:1320002 synced:0 node:0x300 acting:@LAT95LON20 observed_in:@LAT97LON21 band_dbm:6 met:7 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-49 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-49 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-47 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-49 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-47 delta:2 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-59 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-58 delta:1 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-63 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-64 delta:-1 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-92 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-92 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-31 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-31 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1320002 synced:0 window_ms:60000 n:973
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1320002 synced:0 window_ms:60000 blocks:3643 rate:8000
**ACOUSTIC** rms_mean:132 rms_max:362 peak:1267 transients:0

---

@LAT92LON21 | created:0 | updated:0 | relates:testifies_about@LAT95LON21,derived_from@LAT97LON22,senses@LAT0LON0

**OUTCOME** t_ms:1380002 synced:0 node:0x300 acting:@LAT95LON21 observed_in:@LAT97LON22 band_dbm:6 met:6 violated:1 unobserved:0 streak:1
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-49 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-49 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-64 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-66 delta:-2 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-58 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-92 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-75 delta:17 verdict:violated
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-48 delta:-1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-47 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-31 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-31 delta:0 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1380002 synced:0 window_ms:60000 n:995
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1380002 synced:0 window_ms:60000 blocks:3728 rate:8000
**ACOUSTIC** rms_mean:184 rms_max:4933 peak:5732 transients:8
**TRANSIENT** t_ms:1373861 rms:4933 synced:0

---

@LAT92LON22 | created:0 | updated:0 | relates:testifies_about@LAT95LON22,derived_from@LAT97LON23,senses@LAT0LON0

**OUTCOME** t_ms:1440002 synced:0 node:0x300 acting:@LAT95LON22 observed_in:@LAT97LON23 band_dbm:6 met:6 violated:2 unobserved:0 streak:2
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-66 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-63 delta:3 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-47 delta:1 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-49 delta:-2 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-58 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-60 delta:-2 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-49 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-49 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-31 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-31 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-75 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-49 delta:26 verdict:violated
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-82 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-62 delta:20 verdict:violated
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1440002 synced:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:46 moving_ms:0

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1440002 synced:0 window_ms:60000 blocks:3727 rate:8000
**ACOUSTIC** rms_mean:150 rms_max:1444 peak:4036 transients:2
**TRANSIENT** t_ms:1416085 rms:1444 synced:0

---

@LAT92LON23 | created:0 | updated:0 | relates:testifies_about@LAT95LON23,derived_from@LAT97LON24,senses@LAT0LON0

**OUTCOME** t_ms:1500002 synced:0 node:0x300 acting:@LAT95LON23 observed_in:@LAT97LON24 band_dbm:6 met:8 violated:0 unobserved:0 streak:0
**EXPECTED** peer:0x00000200 proto:ble predicted_med:-62 band:6
**OBSERVED** peer:0x00000200 proto:ble observed_med:-62 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:espnow predicted_med:-47 band:6
**OBSERVED** peer:0x00000011 proto:espnow observed_med:-43 delta:4 verdict:met
**EXPECTED** peer:0x00000012 proto:espnow predicted_med:-49 band:6
**OBSERVED** peer:0x00000012 proto:espnow observed_med:-49 delta:0 verdict:met
**EXPECTED** peer:0x00000010 proto:espnow predicted_med:-31 band:6
**OBSERVED** peer:0x00000010 proto:espnow observed_med:-31 delta:0 verdict:met
**EXPECTED** peer:0x00000011 proto:ble predicted_med:-63 band:6
**OBSERVED** peer:0x00000011 proto:ble observed_med:-61 delta:2 verdict:met
**EXPECTED** peer:0x00000010 proto:ble predicted_med:-49 band:6
**OBSERVED** peer:0x00000010 proto:ble observed_med:-49 delta:0 verdict:met
**EXPECTED** peer:0x00000012 proto:ble predicted_med:-60 band:6
**OBSERVED** peer:0x00000012 proto:ble observed_med:-60 delta:0 verdict:met
**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-49 band:6
**OBSERVED** peer:0x00000200 proto:espnow observed_med:-48 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1500002 synced:0 window_ms:60000 n:967
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1500002 synced:0 window_ms:60000 blocks:3621 rate:8000
**ACOUSTIC** rms_mean:136 rms_max:1023 peak:2818 transients:1
**TRANSIENT** t_ms:1499709 rms:1023 synced:0

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:60000 synced:0 window_ms:60000 n:333
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:120000 synced:0 window_ms:60000 n:798
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:33 moving_ms:0

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:180000 synced:0 window_ms:60000 n:798
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:47 moving_ms:0

---

@LAT95LON28 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:240000 synced:0 window_ms:60000 n:761
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON29 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:300000 synced:0 window_ms:60000 n:798
**MOTION** state:still moving_permille:2 dev_mean_mg:14 dev_max_mg:80 moving_ms:120

---

@LAT95LON30 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:360000 synced:0 window_ms:60000 n:796
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON31 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:420000 synced:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON32 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:480000 synced:0 window_ms:60000 n:798
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:21 moving_ms:0

---

@LAT95LON33 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:540000 synced:0 window_ms:60000 n:798
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:21 moving_ms:0

---

@LAT95LON34 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:600000 synced:0 window_ms:60000 n:763
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:27 moving_ms:0

---

@LAT95LON35 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:660000 synced:0 window_ms:60000 n:731
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON36 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:720000 synced:0 window_ms:60000 n:799
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON37 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:780000 synced:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON38 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:840000 synced:0 window_ms:60000 n:799
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON39 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:900000 synced:0 window_ms:60000 n:799
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:38 moving_ms:0

---

@LAT95LON40 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:960000 synced:0 window_ms:60000 n:765
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON41 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1020000 synced:0 window_ms:60000 n:798
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON42 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1080000 synced:0 window_ms:60000 n:800
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON43 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1140000 synced:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON44 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1200000 synced:0 window_ms:60000 n:798
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON45 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1260000 synced:0 window_ms:60000 n:727
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT95LON46 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1320000 synced:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:44 moving_ms:0

---

@LAT95LON47 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1380000 synced:0 window_ms:60000 n:799
**MOTION** state:still moving_permille:0 dev_mean_mg:14 dev_max_mg:17 moving_ms:0

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60019 synced:0 window_ms:60019 blocks:1027 rate:8000
**ACOUSTIC** rms_mean:294 rms_max:12237 peak:32768 transients:7
**TRANSIENT** t_ms:47765 rms:12237 synced:0

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:120019 synced:0 window_ms:60000 blocks:2293 rate:8000
**ACOUSTIC** rms_mean:306 rms_max:6566 peak:19623 transients:15
**TRANSIENT** t_ms:91010 rms:6566 synced:0

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:180043 synced:0 window_ms:60024 blocks:2794 rate:8000
**ACOUSTIC** rms_mean:189 rms_max:2571 peak:13186 transients:6
**TRANSIENT** t_ms:149210 rms:2571 synced:0

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:240043 synced:0 window_ms:60000 blocks:2160 rate:8000
**ACOUSTIC** rms_mean:309 rms_max:8453 peak:32768 transients:36
**TRANSIENT** t_ms:231022 rms:8453 synced:0

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:300043 synced:0 window_ms:60000 blocks:2974 rate:8000
**ACOUSTIC** rms_mean:323 rms_max:20375 peak:32768 transients:14
**TRANSIENT** t_ms:271358 rms:20375 synced:0

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:360043 synced:0 window_ms:60000 blocks:3369 rate:8000
**ACOUSTIC** rms_mean:238 rms_max:1759 peak:3921 transients:4
**TRANSIENT** t_ms:339345 rms:1580 synced:0

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:420043 synced:0 window_ms:60000 blocks:3111 rate:8000
**ACOUSTIC** rms_mean:230 rms_max:987 peak:4038 transients:0

---

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:480043 synced:0 window_ms:60000 blocks:3369 rate:8000
**ACOUSTIC** rms_mean:264 rms_max:795 peak:2320 transients:0

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:540043 synced:0 window_ms:60000 blocks:3362 rate:8000
**ACOUSTIC** rms_mean:251 rms_max:1656 peak:2846 transients:1
**TRANSIENT** t_ms:514307 rms:932 synced:0

---

@LAT94LON34 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:600043 synced:0 window_ms:60000 blocks:3242 rate:8000
**ACOUSTIC** rms_mean:238 rms_max:1066 peak:3324 transients:3
**TRANSIENT** t_ms:568851 rms:1066 synced:0

---

@LAT94LON35 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:660043 synced:0 window_ms:60000 blocks:3118 rate:8000
**ACOUSTIC** rms_mean:230 rms_max:865 peak:1898 transients:0

---

@LAT94LON36 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:720043 synced:0 window_ms:60000 blocks:3373 rate:8000
**ACOUSTIC** rms_mean:241 rms_max:802 peak:1914 transients:0

---

@LAT94LON37 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:60000 synced:0 window_ms:60000 blocks:3442 rate:8000
**ACOUSTIC** rms_mean:92 rms_max:3263 peak:16640 transients:6
**TRANSIENT** t_ms:24930 rms:3263 synced:0

---

@LAT94LON38 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:120000 synced:0 window_ms:60000 blocks:3741 rate:8000
**ACOUSTIC** rms_mean:140 rms_max:519 peak:2225 transients:0

---

@LAT94LON39 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:180000 synced:0 window_ms:60000 blocks:3746 rate:8000
**ACOUSTIC** rms_mean:90 rms_max:1528 peak:6422 transients:1
**TRANSIENT** t_ms:149037 rms:1528 synced:0

---

@LAT94LON40 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:240000 synced:0 window_ms:60000 blocks:3737 rate:8000
**ACOUSTIC** rms_mean:71 rms_max:681 peak:2055 transients:0

---

@LAT94LON41 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:300000 synced:0 window_ms:60000 blocks:3746 rate:8000
**ACOUSTIC** rms_mean:85 rms_max:1619 peak:4612 transients:3
**TRANSIENT** t_ms:247211 rms:1619 synced:0

---

@LAT94LON42 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:360000 synced:0 window_ms:60000 blocks:3746 rate:8000
**ACOUSTIC** rms_mean:105 rms_max:3616 peak:13702 transients:4
**TRANSIENT** t_ms:336105 rms:3616 synced:0

---

@LAT94LON43 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:420000 synced:0 window_ms:60000 blocks:3732 rate:8000
**ACOUSTIC** rms_mean:96 rms_max:1074 peak:5149 transients:5
**TRANSIENT** t_ms:401407 rms:1074 synced:0

---

@LAT94LON44 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:480000 synced:0 window_ms:60000 blocks:3746 rate:8000
**ACOUSTIC** rms_mean:145 rms_max:2239 peak:4941 transients:14
**TRANSIENT** t_ms:449178 rms:2239 synced:0

---

@LAT94LON45 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:542000 synced:0 window_ms:62000 blocks:3748 rate:8000
**ACOUSTIC** rms_mean:173 rms_max:17436 peak:32768 transients:26
**TRANSIENT** t_ms:508203 rms:17436 synced:0

---

@LAT94LON46 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:602000 synced:0 window_ms:60000 blocks:3236 rate:8000
**ACOUSTIC** rms_mean:74 rms_max:424 peak:1429 transients:0

---

@LAT94LON47 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:662000 synced:0 window_ms:60000 blocks:3122 rate:8000
**ACOUSTIC** rms_mean:79 rms_max:526 peak:1476 transients:0

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x0ad62c42 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0xfc36a38c wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x10578c80 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT99LON0 | created:1785774270 | updated:1785774270 | relates:logs@LAT0LON0

**SYNC** id:8 t_ms:1785774270662 recv_ms:4040166 offset_ms:1785770230496

---

@LAT90LON3 | created:1785774270 | updated:1785774270 | relates:describes@LAT0LON0

**STREAM-ANCHORED** stream:0x10578c80 wall:1 t_ms:4028054 node:0x300 from:0x1
**WALL** unix_ms:1785774270662 wall_conflict_ms:0
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:anchored

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x26a1b82d wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x26a1b82d wall:0 t_ms:1835081 node:0x300 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0x26a1b82d wall:0 t_ms:2148099 node:0x300 from:0x200
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x44574814 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0x26a1b82d wall:0 t_ms:3970101 node:0x300 from:0x200
**REMAP** prev_stream:0x44574814 prev_t_ms:13283 offset_ms:3956818 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x59fb8ce8 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---


---


---


---


---


---


---


---


---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6611291 stream:0x59fb8ce8 wall:0 window_ms:60000 entities:11
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT90LON10 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x450f0e1c wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6691199 stream:0x59fb8ce8 wall:0 window_ms:60000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT96LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7275589 stream:0x59fb8ce8 wall:0 window_ms:584390 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-95

---

@LAT96LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7875592 stream:0x59fb8ce8 wall:0 window_ms:600003 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-95

---

@LAT96LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8475591 stream:0x59fb8ce8 wall:0 window_ms:599999 entities:4
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT96LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9075590 stream:0x59fb8ce8 wall:0 window_ms:599999 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91

---

@LAT96LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:9675590 stream:0x59fb8ce8 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92

---

@LAT96LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10087528 stream:0x59fb8ce8 wall:0 window_ms:60000 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---

@LAT96LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:10640509 stream:0x59fb8ce8 wall:0 window_ms:552981 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:11240508 stream:0x59fb8ce8 wall:0 window_ms:599999 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-93

---

@LAT90LON11 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x2434b81f wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON12 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbdc62024 wall:0 t_ms:37253 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:94367 stream:0xbdc62024 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92

---


---

@LAT96LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:401976 stream:0xbdc62024 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:418673 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT91LON0 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:176
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:24 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON1 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:176
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000012 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:24 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON2 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:176
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000011 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:24 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON3 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:176
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000011 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:24 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON4 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:158
rev:1
sal:8
touched:0
[/ew]

**LINK-STABLE** peer:0x00000012 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:23 violated:1 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON5 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:64
rev:1
sal:40
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:ble node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:8 violated:5 unobserved:2 baseline_conf:128 rule:+2/-16 max_streak:2 contradiction:1
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON6 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:50
rev:1
sal:56
touched:0
[/ew]

**LINK-STABLE** peer:0x00000200 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:17 violated:7 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:2 contradiction:1
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline

---

@LAT91LON7 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:158
rev:1
sal:8
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:espnow node:0x300
**TOUCHED** t_ms:0 stream:0x00000000 wall:0 unix_s:0
**TALLY** met:23 violated:1 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline
