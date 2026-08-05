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

@LAT99LON0 | created:1785774270 | updated:1785774270 | relates:logs@LAT0LON0

**SYNC** id:8 t_ms:1785774270662 recv_ms:4040166 offset_ms:1785770230496

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:418673 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:1 removed:48 last_lon:47 t_ms:1683303 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:1 removed:48 last_lon:47 t_ms:1688500 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:1 removed:16 last_lon:15 t_ms:1438863 stream:0xe7384824 wall:0 node:0x00000300
**STREAMS-EXPLAINED** n:12 0x0ad62c42 0xfc36a38c 0x10578c80 0x26a1b82d 0x44574814 0x59fb8ce8 0x450f0e1c 0x2434b81f 0xbdc62024 0x1428c702 0xa315ec7d 0x9c462b30

---

@LAT90LON0 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xe7384824 wall:0 t_ms:1447466 node:0x300 from:0x12
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---


---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xaf869fce wall:0 t_ms:7185 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x161e88ac wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON3 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x5f6eb232 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON4 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x41ba1242 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON5 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x67ec2883 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT90LON6 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x3ab84e5a wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---


---


---

@LAT90LON7 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xbe6d9616 wall:0 t_ms:4001 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---


---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbe6d9616 wall:0 t_ms:5743568 node:0x300 from:0x10
**REMAP** prev_stream:0x9feeb581 prev_t_ms:7042 offset_ms:5736526 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---

@LAT100LON4 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:2 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON5 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:2 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON6 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---

@LAT100LON7 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:2 removed:48 last_lon:47 t_ms:6837755 stream:0xbe6d9616 wall:0 node:0x00000300

---


---


---

@LAT90LON9 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbe6d9616 wall:0 t_ms:6944002 node:0x300 from:0x10
**REMAP** prev_stream:0x36d6dcee prev_t_ms:5710 offset_ms:6938292 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled

---


---

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7084422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-64 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000100 proto:espnow n:29 rssi_min:-36 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000010 proto:espnow n:15 rssi_min:-42 rssi_med:-40 rssi_max:-39

---

@LAT96LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7084422 stream:0xbe6d9616 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:7084422 stream:0xbe6d9616 wall:0 window_ms:60000 n:280
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:11 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7084422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:1044 rate:8000
**ACOUSTIC** rms_mean:131 rms_max:305 peak:652 transients:0

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7144422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-60 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-41 rssi_med:-40 rssi_max:-40

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7144422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2844 rate:8000
**ACOUSTIC** rms_mean:123 rms_max:361 peak:852 transients:0

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7204422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-41 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-79 rssi_med:-56 rssi_max:-55

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7204422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2991 rate:8000
**ACOUSTIC** rms_mean:203 rms_max:20902 peak:32768 transients:7
**TRANSIENT** t_ms:7181840 stream:0xbe6d9616 wall:0 rms:20902

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7264422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-36 rssi_med:-35 rssi_max:-35
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-60 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-41 rssi_med:-40 rssi_max:-40

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7264422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:2859 rate:8000
**ACOUSTIC** rms_mean:122 rms_max:1181 peak:1892 transients:1
**TRANSIENT** t_ms:7242525 stream:0xbe6d9616 wall:0 rms:1181

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7324422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-60 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:29 rssi_min:-41 rssi_med:-40 rssi_max:-39

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7324422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3115 rate:8000
**ACOUSTIC** rms_mean:124 rms_max:611 peak:1063 transients:0

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:7384422 stream:0xbe6d9616 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-79 rssi_med:-56 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-36 rssi_med:-35 rssi_max:-34
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-41 rssi_med:-40 rssi_max:-40

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:7384422 stream:0xbe6d9616 wall:0 window_ms:60000 blocks:3114 rate:8000
**ACOUSTIC** rms_mean:149 rms_max:1546 peak:1857 transients:3
**TRANSIENT** t_ms:7376333 stream:0xbe6d9616 wall:0 rms:1261

---

@LAT91LON0 | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:176
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000010 proto:ble node:0x300
**TOUCHED** t_ms:7460670 stream:0xbe6d9616 wall:0 unix_s:0
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
**TOUCHED** t_ms:7460670 stream:0xbe6d9616 wall:0 unix_s:0
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
**TOUCHED** t_ms:7460670 stream:0xbe6d9616 wall:0 unix_s:0
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
**TOUCHED** t_ms:7460670 stream:0xbe6d9616 wall:0 unix_s:0
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
**TOUCHED** t_ms:7460670 stream:0xbe6d9616 wall:0 unix_s:0
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
**TOUCHED** t_ms:7460670 stream:0xbe6d9616 wall:0 unix_s:0
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
**TOUCHED** t_ms:7460670 stream:0xbe6d9616 wall:0 unix_s:0
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
**TOUCHED** t_ms:7460670 stream:0xbe6d9616 wall:0 unix_s:0
**TALLY** met:23 violated:1 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:24 method:sequential_fold_from_baseline
