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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:486789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-45 rssi_med:-44 rssi_max:-40
**LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-56 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000200 proto:ble n:50 rssi_min:-82 rssi_med:-58 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:47 rssi_min:-67 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:9 rssi_min:-41 rssi_med:-39 rssi_max:-38

---

@LAT96LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:486789 stream:0xbdc62024 wall:0 window_ms:60000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-96
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-97

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:546789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-61 rssi_med:-53 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:33 rssi_min:-49 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000010 proto:ble n:58 rssi_min:-80 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-40 rssi_med:-37 rssi_max:-36
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-59 rssi_med:-44 rssi_max:-41

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:606789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-81 rssi_med:-61 rssi_max:-53
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-66 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-47 rssi_med:-40 rssi_max:-36
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-56 rssi_med:-46 rssi_max:-36
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-62 rssi_med:-50 rssi_max:-44

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:666789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-81 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-55 rssi_med:-45 rssi_max:-39
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-42 rssi_med:-39 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-52 rssi_med:-39 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-81 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-37 rssi_med:-34 rssi_max:-21
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-82 rssi_med:-52 rssi_max:-37
**LINK** peer:0x00000011 proto:ble n:31 rssi_min:-82 rssi_med:-53 rssi_max:-46

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:726789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-63 rssi_med:-52 rssi_max:-51
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:13 rssi_min:-41 rssi_med:-38 rssi_max:-35
**LINK** peer:0x00000012 proto:ble n:23 rssi_min:-57 rssi_med:-53 rssi_max:-47
**LINK** peer:0x00000012 proto:espnow n:10 rssi_min:-40 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-49 rssi_med:-46 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-80 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000011 proto:ble n:44 rssi_min:-66 rssi_med:-57 rssi_max:-48

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:786789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:62 rssi_min:-61 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-67 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000011 proto:ble n:45 rssi_min:-79 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-48 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-41 rssi_med:-40 rssi_max:-37
**LINK** peer:0x00000011 proto:espnow n:12 rssi_min:-43 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-79 rssi_med:-55 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-35 rssi_med:-34 rssi_max:-33

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:846789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:44 rssi_min:-60 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-68 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-35 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-42 rssi_med:-40 rssi_max:-37
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-46 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-55 rssi_max:-52
**LINK** peer:0x00000011 proto:espnow n:12 rssi_min:-40 rssi_med:-38 rssi_max:-34
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-58 rssi_med:-54 rssi_max:-48

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:906789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-79 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:42 rssi_min:-46 rssi_med:-44 rssi_max:-39
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-66 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-42 rssi_med:-40 rssi_max:-38
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-82 rssi_med:-56 rssi_max:-52
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-35 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-80 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-43 rssi_med:-37 rssi_max:-34

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:966789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-64 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-81 rssi_med:-55 rssi_max:-51
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-49 rssi_med:-35 rssi_max:-33
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-58 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-45 rssi_med:-44 rssi_max:-40
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-42 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-41 rssi_med:-37 rssi_max:-34
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-63 rssi_med:-53 rssi_max:-48

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1026789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-83 rssi_med:-55 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:75 rssi_min:-57 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-81 rssi_med:-52 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-48 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-41 rssi_med:-39 rssi_max:-36
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-80 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-49 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-42 rssi_med:-37 rssi_max:-34

---

@LAT96LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1072007 stream:0xbdc62024 wall:0 window_ms:585218 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1086789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-63 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:52 rssi_min:-69 rssi_med:-51 rssi_max:-48
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-70 rssi_med:-54 rssi_max:-50
**LINK** peer:0x00000100 proto:espnow n:33 rssi_min:-45 rssi_med:-43 rssi_max:-40
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-34 rssi_med:-33 rssi_max:-32
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-38 rssi_med:-36 rssi_max:-35
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-36 rssi_med:-33 rssi_max:-31
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-48 rssi_med:-37 rssi_max:-34

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1146789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:68 rssi_min:-79 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-57 rssi_med:-54 rssi_max:-46
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-81 rssi_med:-62 rssi_max:-49
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-44 rssi_med:-41 rssi_max:-39
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-34 rssi_med:-34 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:20 rssi_min:-53 rssi_med:-49 rssi_max:-36
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-79 rssi_med:-58 rssi_max:-51
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-62 rssi_med:-46 rssi_max:-39

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1206789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:70 rssi_min:-72 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-82 rssi_med:-51 rssi_max:-49
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-62 rssi_med:-44 rssi_max:-39
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-79 rssi_med:-54 rssi_max:-47
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-43 rssi_med:-34 rssi_max:-32
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-81 rssi_med:-57 rssi_max:-50
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-43 rssi_med:-33 rssi_max:-33
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-49 rssi_med:-35 rssi_max:-34

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1266789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-82 rssi_med:-58 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:71 rssi_min:-79 rssi_med:-56 rssi_max:-53
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-77 rssi_med:-60 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-61 rssi_med:-43 rssi_max:-36
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-81 rssi_med:-63 rssi_max:-57
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-62 rssi_med:-51 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-56 rssi_med:-46 rssi_max:-39
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-54 rssi_med:-44 rssi_max:-36

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1326789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-82 rssi_med:-64 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-78 rssi_med:-65 rssi_max:-55
**LINK** peer:0x00000100 proto:espnow n:2 rssi_min:-61 rssi_med:-61 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-65 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-84 rssi_med:-67 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-75 rssi_med:-55 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-64 rssi_med:-49 rssi_max:-42
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-54 rssi_med:-47 rssi_max:-44

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1386789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-68 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-80 rssi_med:-64 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-80 rssi_med:-65 rssi_max:-59
**LINK** peer:0x00000010 proto:espnow n:28 rssi_min:-51 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:29 rssi_min:-54 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-71 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-50 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-54 rssi_med:-49 rssi_max:-43

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1446789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-67 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-70 rssi_med:-68 rssi_max:-63
**LINK** peer:0x00000011 proto:ble n:61 rssi_min:-70 rssi_med:-64 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-70 rssi_med:-53 rssi_max:-52
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-47 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:19 rssi_min:-49 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000012 proto:ble n:64 rssi_min:-69 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:17 rssi_min:-48 rssi_med:-47 rssi_max:-46

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1506789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-79 rssi_med:-65 rssi_max:-60
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-81 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-52 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-56 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-69 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:16 rssi_min:-50 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-79 rssi_med:-64 rssi_max:-58
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-51 rssi_med:-47 rssi_max:-45

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1566789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-70 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000012 proto:ble n:58 rssi_min:-87 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000012 proto:espnow n:29 rssi_min:-52 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-50 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000200 proto:ble n:72 rssi_min:-79 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:67 rssi_min:-66 rssi_med:-60 rssi_max:-57
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-48 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:16 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1626789 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:30 rssi_min:-68 rssi_med:-60 rssi_max:-58
**LINK** peer:0x00000011 proto:ble n:60 rssi_min:-77 rssi_med:-64 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-61 rssi_max:-56
**LINK** peer:0x00000010 proto:espnow n:13 rssi_min:-49 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-59 rssi_med:-53 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-80 rssi_med:-66 rssi_max:-59
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-50 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-52 rssi_med:-49 rssi_max:-43

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:1 removed:48 last_lon:47 t_ms:1683303 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:1 removed:48 last_lon:47 t_ms:1688500 stream:0xbdc62024 wall:0 node:0x00000300

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1761607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-45 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-53 rssi_med:-52 rssi_max:-52
**LINK** peer:0x00000012 proto:ble n:46 rssi_min:-80 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-50 rssi_med:-48 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-79 rssi_med:-66 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-50 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:49 rssi_min:-68 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000010 proto:ble n:50 rssi_min:-65 rssi_med:-58 rssi_max:-57

---

@LAT96LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1761607 stream:0xbdc62024 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1761607 stream:0xbdc62024 wall:0 window_ms:60000 n:298
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON0 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1761607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:1113 rate:8000
**ACOUSTIC** rms_mean:487 rms_max:1423 peak:2903 transients:17
**TRANSIENT** t_ms:1752723 stream:0xbdc62024 wall:0 rms:1286

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1821607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:53 rssi_min:-72 rssi_med:-66 rssi_max:-61
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-78 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-47 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-55 rssi_med:-53 rssi_max:-51
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-81 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-50 rssi_med:-48 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-52 rssi_med:-49 rssi_max:-43
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-79 rssi_med:-60 rssi_max:-55

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1821607 stream:0xbdc62024 wall:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON1 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1821607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2858 rate:8000
**ACOUSTIC** rms_mean:254 rms_max:9751 peak:32768 transients:12
**TRANSIENT** t_ms:1782052 stream:0xbdc62024 wall:0 rms:9751

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1881607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-48 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-53 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-80 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-87 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-50 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-74 rssi_med:-65 rssi_max:-59
**LINK** peer:0x00000011 proto:ble n:50 rssi_min:-83 rssi_med:-65 rssi_max:-57
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-50 rssi_med:-48 rssi_max:-47

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1881607 stream:0xbdc62024 wall:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON2 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1881607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2859 rate:8000
**ACOUSTIC** rms_mean:270 rms_max:4766 peak:15501 transients:11
**TRANSIENT** t_ms:1834142 stream:0xbdc62024 wall:0 rms:4766

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1941607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-47 rssi_med:-45 rssi_max:-42
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-64 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-73 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-68 rssi_med:-63 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-53 rssi_med:-52 rssi_max:-49
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-75 rssi_med:-65 rssi_max:-60
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-50 rssi_med:-47 rssi_max:-42
**LINK** peer:0x00000012 proto:espnow n:20 rssi_min:-52 rssi_med:-48 rssi_max:-46

---

@LAT95LON3 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1941607 stream:0xbdc62024 wall:0 window_ms:60000 n:728
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON3 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:1941607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2725 rate:8000
**ACOUSTIC** rms_mean:301 rms_max:1901 peak:6939 transients:12
**TRANSIENT** t_ms:1906570 stream:0xbdc62024 wall:0 rms:1901

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2001607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-47 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-80 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:21 rssi_min:-55 rssi_med:-51 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:29 rssi_min:-50 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000011 proto:ble n:65 rssi_min:-79 rssi_med:-61 rssi_max:-57
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-74 rssi_med:-66 rssi_max:-60
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-53 rssi_med:-51 rssi_max:-48

---

@LAT95LON4 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2001607 stream:0xbdc62024 wall:0 window_ms:60000 n:763
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON4 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2001607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2850 rate:8000
**ACOUSTIC** rms_mean:285 rms_max:998 peak:1957 transients:3
**TRANSIENT** t_ms:1962577 stream:0xbdc62024 wall:0 rms:998

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2061607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-82 rssi_med:-64 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-74 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:55 rssi_min:-71 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-63 rssi_med:-53 rssi_max:-46
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-49 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:69 rssi_min:-64 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-46 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-52 rssi_med:-50 rssi_max:-48

---

@LAT95LON5 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2061607 stream:0xbdc62024 wall:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON5 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2061607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2857 rate:8000
**ACOUSTIC** rms_mean:251 rms_max:3193 peak:12356 transients:4
**TRANSIENT** t_ms:2051645 stream:0xbdc62024 wall:0 rms:3193

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2121607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-47 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000200 proto:espnow n:23 rssi_min:-53 rssi_med:-51 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:57 rssi_min:-85 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-53 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-52 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-70 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000010 proto:ble n:66 rssi_min:-65 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:57 rssi_min:-75 rssi_med:-62 rssi_max:-58

---

@LAT95LON6 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2121607 stream:0xbdc62024 wall:0 window_ms:60000 n:729
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON6 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2121607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2728 rate:8000
**ACOUSTIC** rms_mean:380 rms_max:1372 peak:2377 transients:28
**TRANSIENT** t_ms:2081941 stream:0xbdc62024 wall:0 rms:1263

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2181607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-48 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000012 proto:ble n:70 rssi_min:-86 rssi_med:-61 rssi_max:-56
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-84 rssi_med:-65 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-79 rssi_med:-64 rssi_max:-59
**LINK** peer:0x00000200 proto:espnow n:28 rssi_min:-55 rssi_med:-50 rssi_max:-48
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-52 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-55 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:62 rssi_min:-64 rssi_med:-58 rssi_max:-54

---

@LAT95LON7 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2181607 stream:0xbdc62024 wall:0 window_ms:60000 n:765
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON7 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2181607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2865 rate:8000
**ACOUSTIC** rms_mean:363 rms_max:1303 peak:2465 transients:17
**TRANSIENT** t_ms:2180136 stream:0xbdc62024 wall:0 rms:1290

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2241607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-47 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-80 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-75 rssi_med:-66 rssi_max:-58
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-78 rssi_med:-64 rssi_max:-59
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-62 rssi_med:-53 rssi_max:-49
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-54 rssi_med:-50 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:27 rssi_min:-57 rssi_med:-48 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-64 rssi_med:-58 rssi_max:-55

---

@LAT95LON8 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2241607 stream:0xbdc62024 wall:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:12 moving_ms:0

---

@LAT94LON8 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2241607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2861 rate:8000
**ACOUSTIC** rms_mean:435 rms_max:5002 peak:9583 transients:26
**TRANSIENT** t_ms:2230643 stream:0xbdc62024 wall:0 rms:5002

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2301607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-67 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-80 rssi_med:-64 rssi_max:-54
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-51 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-55 rssi_med:-49 rssi_max:-44
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-64 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000012 proto:ble n:53 rssi_min:-92 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:65 rssi_min:-83 rssi_med:-70 rssi_max:-65
**LINK** peer:0x00000010 proto:espnow n:16 rssi_min:-46 rssi_med:-45 rssi_max:-44

---

@LAT95LON9 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2301607 stream:0xbdc62024 wall:0 window_ms:60000 n:729
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON9 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2301607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2723 rate:8000
**ACOUSTIC** rms_mean:429 rms_max:4668 peak:16275 transients:27
**TRANSIENT** t_ms:2270488 stream:0xbdc62024 wall:0 rms:4668

---

@LAT96LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2346536 stream:0xbdc62024 wall:0 window_ms:584929 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2361607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-81 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-64 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-79 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-66 rssi_med:-65 rssi_max:-64
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-49 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-49 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-46 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-74 rssi_med:-69 rssi_max:-67

---

@LAT95LON10 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2361607 stream:0xbdc62024 wall:0 window_ms:60000 n:698
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON10 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2361607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2608 rate:8000
**ACOUSTIC** rms_mean:350 rms_max:2307 peak:3792 transients:33
**TRANSIENT** t_ms:2346423 stream:0xbdc62024 wall:0 rms:2307

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2421607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-64 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-79 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-63 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-66 rssi_med:-65 rssi_max:-64
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-49 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-46 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-72 rssi_med:-61 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-49 rssi_med:-49 rssi_max:-47

---

@LAT95LON11 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2421607 stream:0xbdc62024 wall:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON11 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2421607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2858 rate:8000
**ACOUSTIC** rms_mean:462 rms_max:1871 peak:3075 transients:46
**TRANSIENT** t_ms:2377245 stream:0xbdc62024 wall:0 rms:1639

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2481607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-77 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000011 proto:ble n:56 rssi_min:-64 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-71 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-63 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-49 rssi_med:-49 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-49 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-46 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000200 proto:espnow n:17 rssi_min:-66 rssi_med:-66 rssi_max:-65

---

@LAT95LON12 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2481607 stream:0xbdc62024 wall:0 window_ms:60000 n:729
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON12 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2481607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2726 rate:8000
**ACOUSTIC** rms_mean:468 rms_max:1855 peak:2787 transients:41
**TRANSIENT** t_ms:2471917 stream:0xbdc62024 wall:0 rms:1704

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2541607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-79 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000200 proto:espnow n:24 rssi_min:-66 rssi_med:-65 rssi_max:-65
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-64 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000010 proto:ble n:75 rssi_min:-81 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-49 rssi_med:-49 rssi_max:-49
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-49 rssi_med:-48 rssi_max:-48
**LINK** peer:0x00000200 proto:ble n:60 rssi_min:-78 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-45 rssi_med:-45 rssi_max:-44

---

@LAT95LON13 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2541607 stream:0xbdc62024 wall:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON13 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2541607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2861 rate:8000
**ACOUSTIC** rms_mean:319 rms_max:2390 peak:3818 transients:16
**TRANSIENT** t_ms:2503916 stream:0xbdc62024 wall:0 rms:1921

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2601607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-64 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:57 rssi_min:-75 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-79 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:19 rssi_min:-66 rssi_med:-66 rssi_max:-64
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-50 rssi_med:-49 rssi_max:-49
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-71 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000011 proto:espnow n:16 rssi_min:-49 rssi_med:-48 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-46 rssi_med:-45 rssi_max:-44

---

@LAT95LON14 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2601607 stream:0xbdc62024 wall:0 window_ms:60000 n:761
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON14 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2601607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2846 rate:8000
**ACOUSTIC** rms_mean:258 rms_max:1226 peak:2174 transients:13
**TRANSIENT** t_ms:2578921 stream:0xbdc62024 wall:0 rms:1226

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2661607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-64 rssi_med:-63 rssi_max:-57
**LINK** peer:0x00000200 proto:ble n:63 rssi_min:-73 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000012 proto:ble n:56 rssi_min:-72 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000010 proto:ble n:61 rssi_min:-63 rssi_med:-59 rssi_max:-56
**LINK** peer:0x00000200 proto:espnow n:30 rssi_min:-66 rssi_med:-66 rssi_max:-65
**LINK** peer:0x00000012 proto:espnow n:18 rssi_min:-49 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-49 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-46 rssi_med:-45 rssi_max:-44

---

@LAT95LON15 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2661607 stream:0xbdc62024 wall:0 window_ms:60000 n:731
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON15 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2661607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2734 rate:8000
**ACOUSTIC** rms_mean:347 rms_max:7348 peak:8273 transients:16
**TRANSIENT** t_ms:2658408 stream:0xbdc62024 wall:0 rms:7348

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2721607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:61 rssi_min:-75 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000012 proto:ble n:65 rssi_min:-79 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-63 rssi_med:-58 rssi_max:-56
**LINK** peer:0x00000012 proto:espnow n:28 rssi_min:-50 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-50 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-47 rssi_med:-45 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-64 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000200 proto:espnow n:22 rssi_min:-65 rssi_med:-65 rssi_max:-64

---

@LAT95LON16 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2721607 stream:0xbdc62024 wall:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON16 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2721607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2859 rate:8000
**ACOUSTIC** rms_mean:326 rms_max:11841 peak:14435 transients:17
**TRANSIENT** t_ms:2693690 stream:0xbdc62024 wall:0 rms:11841

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2781607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-79 rssi_med:-60 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:19 rssi_min:-49 rssi_med:-49 rssi_max:-48
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-63 rssi_med:-57 rssi_max:-56
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-51 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-79 rssi_med:-63 rssi_max:-58
**LINK** peer:0x00000200 proto:ble n:59 rssi_min:-74 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000200 proto:espnow n:26 rssi_min:-66 rssi_med:-65 rssi_max:-63
**LINK** peer:0x00000010 proto:espnow n:27 rssi_min:-46 rssi_med:-45 rssi_max:-44

---

@LAT95LON17 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2781607 stream:0xbdc62024 wall:0 window_ms:60000 n:763
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON17 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2781607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2860 rate:8000
**ACOUSTIC** rms_mean:259 rms_max:5521 peak:6997 transients:20
**TRANSIENT** t_ms:2736996 stream:0xbdc62024 wall:0 rms:5521

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2841607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-62 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000200 proto:ble n:66 rssi_min:-79 rssi_med:-70 rssi_max:-64
**LINK** peer:0x00000012 proto:ble n:60 rssi_min:-71 rssi_med:-58 rssi_max:-52
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-67 rssi_med:-60 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:64 rssi_min:-73 rssi_med:-62 rssi_max:-58
**LINK** peer:0x00000012 proto:espnow n:26 rssi_min:-48 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-48 rssi_med:-44 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:24 rssi_min:-52 rssi_med:-46 rssi_max:-43

---

@LAT95LON18 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2841607 stream:0xbdc62024 wall:0 window_ms:60000 n:728
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON18 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2841607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2724 rate:8000
**ACOUSTIC** rms_mean:235 rms_max:1279 peak:2458 transients:17
**TRANSIENT** t_ms:2791854 stream:0xbdc62024 wall:0 rms:1279

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2901607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-78 rssi_med:-62 rssi_max:-57
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-64 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-67 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:21 rssi_min:-69 rssi_med:-62 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:23 rssi_min:-48 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-61 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-81 rssi_med:-70 rssi_max:-66
**LINK** peer:0x00000010 proto:espnow n:20 rssi_min:-47 rssi_med:-45 rssi_max:-42

---

@LAT95LON19 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2901607 stream:0xbdc62024 wall:0 window_ms:60000 n:763
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON19 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2901607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2854 rate:8000
**ACOUSTIC** rms_mean:348 rms_max:2104 peak:3431 transients:14
**TRANSIENT** t_ms:2864164 stream:0xbdc62024 wall:0 rms:2104

---

@LAT96LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2946536 stream:0xbdc62024 wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-86
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:2961607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:49 rssi_min:-71 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000200 proto:espnow n:18 rssi_min:-67 rssi_med:-62 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:59 rssi_min:-79 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-50 rssi_med:-46 rssi_max:-43
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-50 rssi_med:-47 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:54 rssi_min:-70 rssi_med:-63 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:23 rssi_min:-46 rssi_med:-43 rssi_max:-42
**LINK** peer:0x00000200 proto:ble n:51 rssi_min:-79 rssi_med:-69 rssi_max:-64

---

@LAT95LON20 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:2961607 stream:0xbdc62024 wall:0 window_ms:60000 n:697
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON20 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:2961607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2608 rate:8000
**ACOUSTIC** rms_mean:260 rms_max:1180 peak:2437 transients:1
**TRANSIENT** t_ms:2950738 stream:0xbdc62024 wall:0 rms:1180

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3021607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-71 rssi_med:-62 rssi_max:-53
**LINK** peer:0x00000011 proto:ble n:58 rssi_min:-71 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-71 rssi_med:-66 rssi_max:-61
**LINK** peer:0x00000012 proto:espnow n:27 rssi_min:-52 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000010 proto:ble n:55 rssi_min:-81 rssi_med:-57 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:26 rssi_min:-47 rssi_med:-44 rssi_max:-42
**LINK** peer:0x00000200 proto:espnow n:27 rssi_min:-63 rssi_med:-57 rssi_max:-50
**LINK** peer:0x00000011 proto:espnow n:21 rssi_min:-49 rssi_med:-46 rssi_max:-45

---

@LAT95LON21 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3021607 stream:0xbdc62024 wall:0 window_ms:60000 n:730
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON21 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3021607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2732 rate:8000
**ACOUSTIC** rms_mean:305 rms_max:5070 peak:6120 transients:5
**TRANSIENT** t_ms:3019066 stream:0xbdc62024 wall:0 rms:5070

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3081607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:55 rssi_min:-70 rssi_med:-61 rssi_max:-54
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-76 rssi_med:-67 rssi_max:-63
**LINK** peer:0x00000200 proto:espnow n:25 rssi_min:-65 rssi_med:-58 rssi_max:-53
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-50 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000011 proto:espnow n:26 rssi_min:-50 rssi_med:-46 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-79 rssi_med:-64 rssi_max:-61
**LINK** peer:0x00000010 proto:ble n:60 rssi_min:-79 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000010 proto:espnow n:18 rssi_min:-45 rssi_med:-43 rssi_max:-42

---

@LAT95LON22 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3081607 stream:0xbdc62024 wall:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON22 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3081607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2863 rate:8000
**ACOUSTIC** rms_mean:338 rms_max:1744 peak:3131 transients:5
**TRANSIENT** t_ms:3072521 stream:0xbdc62024 wall:0 rms:1744

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3141607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000012 proto:ble n:66 rssi_min:-69 rssi_med:-60 rssi_max:-54
**LINK** peer:0x00000010 proto:ble n:64 rssi_min:-80 rssi_med:-57 rssi_max:-54
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-76 rssi_med:-69 rssi_max:-65
**LINK** peer:0x00000012 proto:espnow n:22 rssi_min:-50 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-70 rssi_med:-63 rssi_max:-61
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-45 rssi_med:-43 rssi_max:-41
**LINK** peer:0x00000011 proto:espnow n:25 rssi_min:-52 rssi_med:-48 rssi_max:-46

---

@LAT95LON23 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3141607 stream:0xbdc62024 wall:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:13 moving_ms:0

---

@LAT94LON23 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3141607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2859 rate:8000
**ACOUSTIC** rms_mean:584 rms_max:1872 peak:3162 transients:10
**TRANSIENT** t_ms:3138507 stream:0xbdc62024 wall:0 rms:1872

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3201607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:63 rssi_min:-68 rssi_med:-65 rssi_max:-60
**LINK** peer:0x00000012 proto:ble n:61 rssi_min:-66 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000010 proto:ble n:65 rssi_min:-62 rssi_med:-58 rssi_max:-54
**LINK** peer:0x00000012 proto:espnow n:15 rssi_min:-47 rssi_med:-47 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:21 rssi_min:-46 rssi_med:-45 rssi_max:-43
**LINK** peer:0x00000200 proto:ble n:64 rssi_min:-74 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-55 rssi_med:-49 rssi_max:-48

---

@LAT95LON24 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3201607 stream:0xbdc62024 wall:0 window_ms:60000 n:729
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON24 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3201607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2721 rate:8000
**ACOUSTIC** rms_mean:610 rms_max:1839 peak:3311 transients:8
**TRANSIENT** t_ms:3168380 stream:0xbdc62024 wall:0 rms:1531

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3261607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:ble n:66 rssi_min:-69 rssi_med:-65 rssi_max:-62
**LINK** peer:0x00000200 proto:ble n:56 rssi_min:-74 rssi_med:-70 rssi_max:-67
**LINK** peer:0x00000012 proto:espnow n:25 rssi_min:-47 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000012 proto:ble n:59 rssi_min:-79 rssi_med:-57 rssi_max:-53
**LINK** peer:0x00000011 proto:espnow n:18 rssi_min:-50 rssi_med:-49 rssi_max:-47
**LINK** peer:0x00000010 proto:ble n:63 rssi_min:-65 rssi_med:-59 rssi_max:-54
**LINK** peer:0x00000010 proto:espnow n:24 rssi_min:-46 rssi_med:-45 rssi_max:-44

---

@LAT95LON25 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3261607 stream:0xbdc62024 wall:0 window_ms:60000 n:765
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON25 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3261607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2865 rate:8000
**ACOUSTIC** rms_mean:682 rms_max:2051 peak:3089 transients:5
**TRANSIENT** t_ms:3241345 stream:0xbdc62024 wall:0 rms:1898

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3321607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:62 rssi_min:-82 rssi_med:-69 rssi_max:-67
**LINK** peer:0x00000012 proto:ble n:52 rssi_min:-70 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000011 proto:ble n:59 rssi_min:-69 rssi_med:-64 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:56 rssi_min:-64 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:17 rssi_min:-48 rssi_med:-45 rssi_max:-44
**LINK** peer:0x00000011 proto:espnow n:22 rssi_min:-57 rssi_med:-49 rssi_max:-45
**LINK** peer:0x00000010 proto:espnow n:22 rssi_min:-47 rssi_med:-44 rssi_max:-43

---

@LAT95LON26 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3321607 stream:0xbdc62024 wall:0 window_ms:60000 n:764
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON26 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3321607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2861 rate:8000
**ACOUSTIC** rms_mean:263 rms_max:1811 peak:3376 transients:10
**TRANSIENT** t_ms:3311050 stream:0xbdc62024 wall:0 rms:1811

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:3381607 stream:0xbdc62024 wall:0 window_ms:60000
**LINK** peer:0x00000200 proto:ble n:58 rssi_min:-73 rssi_med:-69 rssi_max:-63
**LINK** peer:0x00000011 proto:espnow n:23 rssi_min:-48 rssi_med:-46 rssi_max:-44
**LINK** peer:0x00000011 proto:ble n:62 rssi_min:-79 rssi_med:-63 rssi_max:-60
**LINK** peer:0x00000010 proto:ble n:52 rssi_min:-65 rssi_med:-58 rssi_max:-55
**LINK** peer:0x00000010 proto:espnow n:19 rssi_min:-47 rssi_med:-44 rssi_max:-41
**LINK** peer:0x00000012 proto:ble n:63 rssi_min:-67 rssi_med:-59 rssi_max:-55
**LINK** peer:0x00000012 proto:espnow n:24 rssi_min:-47 rssi_med:-46 rssi_max:-45

---

@LAT95LON27 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3381607 stream:0xbdc62024 wall:0 window_ms:60000 n:729
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON27 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3381607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2725 rate:8000
**ACOUSTIC** rms_mean:315 rms_max:1548 peak:4136 transients:19
**TRANSIENT** t_ms:3377708 stream:0xbdc62024 wall:0 rms:1548

---

@LAT95LON28 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3441607 stream:0xbdc62024 wall:0 window_ms:60000 n:765
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON28 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3441607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2861 rate:8000
**ACOUSTIC** rms_mean:371 rms_max:4999 peak:5576 transients:38
**TRANSIENT** t_ms:3403514 stream:0xbdc62024 wall:0 rms:4999

---

@LAT95LON29 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3501607 stream:0xbdc62024 wall:0 window_ms:60000 n:866
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON29 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3501607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3240 rate:8000
**ACOUSTIC** rms_mean:331 rms_max:4500 peak:5540 transients:44
**TRANSIENT** t_ms:3484364 stream:0xbdc62024 wall:0 rms:2404

---

@LAT96LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3546535 stream:0xbdc62024 wall:0 window_ms:599999 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-83
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-85
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93

---

@LAT95LON30 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3561607 stream:0xbdc62024 wall:0 window_ms:60000 n:761
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON30 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3561607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2846 rate:8000
**ACOUSTIC** rms_mean:360 rms_max:1588 peak:3094 transients:25
**TRANSIENT** t_ms:3537534 stream:0xbdc62024 wall:0 rms:1502

---

@LAT95LON31 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3621607 stream:0xbdc62024 wall:0 window_ms:60000 n:866
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:15 moving_ms:0

---

@LAT94LON31 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3621607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3238 rate:8000
**ACOUSTIC** rms_mean:512 rms_max:1723 peak:3568 transients:16
**TRANSIENT** t_ms:3599933 stream:0xbdc62024 wall:0 rms:1674

---

@LAT95LON32 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3681607 stream:0xbdc62024 wall:0 window_ms:60000 n:866
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON32 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3681607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3242 rate:8000
**ACOUSTIC** rms_mean:524 rms_max:1628 peak:3160 transients:17
**TRANSIENT** t_ms:3654895 stream:0xbdc62024 wall:0 rms:1589

---

@LAT95LON33 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3741607 stream:0xbdc62024 wall:0 window_ms:60000 n:830
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON33 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3741607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3098 rate:8000
**ACOUSTIC** rms_mean:296 rms_max:4195 peak:8275 transients:4
**TRANSIENT** t_ms:3717587 stream:0xbdc62024 wall:0 rms:4195

---

@LAT95LON34 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3801607 stream:0xbdc62024 wall:0 window_ms:60000 n:838
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON34 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3801607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3101 rate:8000
**ACOUSTIC** rms_mean:313 rms_max:1619 peak:3245 transients:0

---

@LAT95LON35 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3861607 stream:0xbdc62024 wall:0 window_ms:60000 n:849
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:13 moving_ms:0

---

@LAT94LON35 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3861607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3127 rate:8000
**ACOUSTIC** rms_mean:286 rms_max:1394 peak:3111 transients:1
**TRANSIENT** t_ms:3809085 stream:0xbdc62024 wall:0 rms:1394

---

@LAT95LON36 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3921607 stream:0xbdc62024 wall:0 window_ms:60000 n:791
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON36 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3921607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2882 rate:8000
**ACOUSTIC** rms_mean:286 rms_max:1164 peak:3172 transients:0

---

@LAT95LON37 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3981607 stream:0xbdc62024 wall:0 window_ms:60000 n:837
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON37 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:3981607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3060 rate:8000
**ACOUSTIC** rms_mean:301 rms_max:4544 peak:9435 transients:12
**TRANSIENT** t_ms:3935476 stream:0xbdc62024 wall:0 rms:4544

---

@LAT95LON38 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4041607 stream:0xbdc62024 wall:0 window_ms:60000 n:836
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON38 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4041607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3036 rate:8000
**ACOUSTIC** rms_mean:287 rms_max:1133 peak:2381 transients:0

---

@LAT95LON39 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4101607 stream:0xbdc62024 wall:0 window_ms:60000 n:777
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON39 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4101607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2869 rate:8000
**ACOUSTIC** rms_mean:271 rms_max:1086 peak:2102 transients:1
**TRANSIENT** t_ms:4070712 stream:0xbdc62024 wall:0 rms:925

---

@LAT96LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4146535 stream:0xbdc62024 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-95

---

@LAT95LON40 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4161607 stream:0xbdc62024 wall:0 window_ms:60000 n:780
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON40 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4161607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:2852 rate:8000
**ACOUSTIC** rms_mean:261 rms_max:1171 peak:2033 transients:2
**TRANSIENT** t_ms:4127390 stream:0xbdc62024 wall:0 rms:1115

---

@LAT95LON41 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4221607 stream:0xbdc62024 wall:0 window_ms:60000 n:840
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON41 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4221607 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3048 rate:8000
**ACOUSTIC** rms_mean:270 rms_max:2152 peak:2547 transients:9
**TRANSIENT** t_ms:4212533 stream:0xbdc62024 wall:0 rms:1264

---

@LAT96LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4390069 stream:0xbdc62024 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-81
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93

---

@LAT95LON42 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4390069 stream:0xbdc62024 wall:0 window_ms:60000 n:924
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0

---

@LAT94LON42 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4390069 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3451 rate:8000
**ACOUSTIC** rms_mean:307 rms_max:1943 peak:4434 transients:4
**TRANSIENT** t_ms:4383176 stream:0xbdc62024 wall:0 rms:1943

---

@LAT95LON43 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4450069 stream:0xbdc62024 wall:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:20 moving_ms:0

---

@LAT94LON43 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4450069 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3734 rate:8000
**ACOUSTIC** rms_mean:514 rms_max:4319 peak:10223 transients:5
**TRANSIENT** t_ms:4439377 stream:0xbdc62024 wall:0 rms:2398

---

@LAT95LON44 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4510069 stream:0xbdc62024 wall:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0

---

@LAT94LON44 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4510069 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3736 rate:8000
**ACOUSTIC** rms_mean:573 rms_max:7129 peak:13629 transients:23
**TRANSIENT** t_ms:4473633 stream:0xbdc62024 wall:0 rms:7129

---

@LAT95LON45 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4570069 stream:0xbdc62024 wall:0 window_ms:60000 n:994
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON45 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4570069 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3726 rate:8000
**ACOUSTIC** rms_mean:592 rms_max:19181 peak:32768 transients:17
**TRANSIENT** t_ms:4520767 stream:0xbdc62024 wall:0 rms:19181

---

@LAT95LON46 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4630069 stream:0xbdc62024 wall:0 window_ms:60000 n:997
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON46 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4630069 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3739 rate:8000
**ACOUSTIC** rms_mean:414 rms_max:10578 peak:12020 transients:10
**TRANSIENT** t_ms:4620955 stream:0xbdc62024 wall:0 rms:7210

---

@LAT95LON47 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:4690069 stream:0xbdc62024 wall:0 window_ms:60000 n:996
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT94LON47 | created:0 | updated:0 | relates:hears@LAT0LON0

**ACOUSTICWIN** t_ms:4690069 stream:0xbdc62024 wall:0 window_ms:60000 blocks:3733 rate:8000
**ACOUSTIC** rms_mean:227 rms_max:9073 peak:9821 transients:7
**TRANSIENT** t_ms:4666389 stream:0xbdc62024 wall:0 rms:6569

---

@LAT96LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4831074 stream:0xbdc62024 wall:0 window_ms:60000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-95

---

@LAT96LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5418011 stream:0xbdc62024 wall:0 window_ms:586937 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT96LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6018011 stream:0xbdc62024 wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-87
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-95

---

@LAT96LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:112232 stream:0xe7384824 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:66c6d284568a n:1 rssi:-89
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90

---

@LAT96LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:289448 stream:0xe7384824 wall:0 window_ms:60000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-70
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-92
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ff9038cc n:1 rssi:-95

---

@LAT96LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:564915 stream:0xe7384824 wall:0 window_ms:60000 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-93
**ENTITY** kind:wifi_ap id:e45e1beaab37 n:1 rssi:-93

---

@LAT96LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:744490 stream:0xe7384824 wall:0 window_ms:60000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-95

---

@LAT96LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1331641 stream:0xe7384824 wall:0 window_ms:587151 entities:11
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-87
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ff9038cc n:1 rssi:-94

---

@LAT96LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1436626 stream:0xe7384824 wall:0 window_ms:60000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-94

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

@LAT96LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1517023 stream:0xe7384824 wall:0 window_ms:60000 entities:12
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-67
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-78
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:08bfb88eddd0 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ff9038cc n:1 rssi:-93
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93

---

@LAT96LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2104609 stream:0xe7384824 wall:0 window_ms:587586 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-52
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-69
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:18a5ff9038cc n:1 rssi:-96

---

@LAT96LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2704609 stream:0xe7384824 wall:0 window_ms:600000 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-72
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:e45e1beaab37 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93

---

@LAT96LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3304609 stream:0xe7384824 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-90
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-96

---

@LAT96LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:3904607 stream:0xe7384824 wall:0 window_ms:599998 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94

---

@LAT96LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4410515 stream:0xe7384824 wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-95

---

@LAT96LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:4964151 stream:0xe7384824 wall:0 window_ms:553636 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94

---

@LAT96LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:5564152 stream:0xe7384824 wall:0 window_ms:600001 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-71
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-93
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-95

---

@LAT96LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6164152 stream:0xe7384824 wall:0 window_ms:600000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-70
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-82
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93

---

@LAT96LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:6764149 stream:0xe7384824 wall:0 window_ms:599997 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-69
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-84
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93

---

@LAT96LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7277492 stream:0xe7384824 wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-72
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-85
**ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:7831164 stream:0xe7384824 wall:0 window_ms:553672 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:f83eb00f094a n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-92
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93

---

@LAT96LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:8431165 stream:0xe7384824 wall:0 window_ms:600001 entities:5
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-83
**ENTITY** kind:wifi_ap id:22ad5628d593 n:1 rssi:-91

---

@LAT90LON1 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ADOPTED** stream:0xaf869fce wall:0 t_ms:7185 node:0x300 from:0x10
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:adopted

---

@LAT96LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:61930 stream:0xaf869fce wall:0 window_ms:60000 entities:6
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-32
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91

---

@LAT90LON2 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x161e88ac wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT96LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:52088 stream:0x161e88ac wall:0 window_ms:60000 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-43
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90

---

@LAT96LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:605516 stream:0x161e88ac wall:0 window_ms:553428 entities:7
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91

---

@LAT96LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1205516 stream:0x161e88ac wall:0 window_ms:600000 entities:8
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-79
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-92
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94

---

@LAT96LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1805515 stream:0x161e88ac wall:0 window_ms:599999 entities:9
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-95

---

@LAT96LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**ENTWIN** t_ms:2405513 stream:0x161e88ac wall:0 window_ms:599998 entities:10
**ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
**ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
**ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78
**ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
**ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
**ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-89
**ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:18a5ffbae2d6 n:1 rssi:-91
**ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-93
**ENTITY** kind:wifi_ap id:003044724bc7 n:1 rssi:-94

---


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

---

@LAT90LON8 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-RECONCILED** stream:0xbe6d9616 wall:0 t_ms:5743568 node:0x300 from:0x10
**REMAP** prev_stream:0x9feeb581 prev_t_ms:7042 offset_ms:5736526 rule:older_stream_wins
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:reconciled
