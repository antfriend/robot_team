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

@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26647619 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-51 rssi_med:-46 rssi_max:-42

---

@LAT97LON1 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26713469 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:34 rssi_min:-48 rssi_med:-46 rssi_max:-40

---

@LAT97LON2 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26773469 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-49 rssi_med:-45 rssi_max:-43

---

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON1,derived_from@LAT97LON2,senses@LAT0LON0

**OUTCOME** t_ms:26773469 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON1+0 observed_in:@LAT97LON2 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-46 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-45 delta:1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT97LON3 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26833469 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-46 rssi_med:-44 rssi_max:-43

---

@LAT97LON4 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26893469 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-45 rssi_med:-44 rssi_max:-43

---

@LAT97LON5 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:26953469 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-50 rssi_med:-45 rssi_max:-43

---

@LAT97LON6 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27013541 stream:0x4a194eda wall:0 window_ms:60072
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-48 rssi_med:-44 rssi_max:-42

---

@LAT97LON7 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27075506 stream:0x4a194eda wall:0 window_ms:61965
**LINK** peer:0x00000100 proto:espnow n:50 rssi_min:-47 rssi_med:-45 rssi_max:-43

---

@LAT97LON8 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27135506 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-50 rssi_med:-47 rssi_max:-44

---

@LAT97LON9 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27195506 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:57 rssi_min:-48 rssi_med:-47 rssi_max:-43

---

@LAT97LON10 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27255506 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-49 rssi_med:-46 rssi_max:-41

---

@LAT97LON11 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27315506 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-49 rssi_med:-44 rssi_max:-41

---

@LAT97LON12 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27375506 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:39 rssi_min:-48 rssi_med:-44 rssi_max:-43

---

@LAT97LON13 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27435593 stream:0x4a194eda wall:0 window_ms:60087
**LINK** peer:0x00000100 proto:espnow n:56 rssi_min:-49 rssi_med:-47 rssi_max:-46

---

@LAT97LON14 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27495594 stream:0x4a194eda wall:0 window_ms:60001
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-48 rssi_med:-47 rssi_max:-46

---

@LAT97LON15 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27557534 stream:0x4a194eda wall:0 window_ms:61940
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-51 rssi_med:-47 rssi_max:-46

---

@LAT97LON16 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27617534 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-52 rssi_med:-50 rssi_max:-47

---

@LAT97LON17 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27677592 stream:0x4a194eda wall:0 window_ms:60058
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-59 rssi_med:-47 rssi_max:-42

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27739597 stream:0x4a194eda wall:0 window_ms:62005
**LINK** peer:0x00000100 proto:espnow n:41 rssi_min:-66 rssi_med:-48 rssi_max:-46

---

@LAT97LON19 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27801474 stream:0x4a194eda wall:0 window_ms:61877
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-55 rssi_med:-47 rssi_max:-46

---

@LAT97LON20 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27861474 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-52 rssi_med:-47 rssi_max:-44

---

@LAT97LON21 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:27970043 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:48 rssi_min:-69 rssi_med:-52 rssi_max:-48

---

@LAT97LON22 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28030043 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-51 rssi_med:-49 rssi_max:-46

---

@LAT92LON1 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON22,senses@LAT0LON0

**OUTCOME** t_ms:28030043 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON2+0 observed_in:@LAT97LON22 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-52 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-49 delta:3 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT97LON23 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28090044 stream:0x4a194eda wall:0 window_ms:60001
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-69 rssi_med:-48 rssi_max:-45

---

@LAT97LON24 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28150044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:43 rssi_min:-62 rssi_med:-49 rssi_max:-44

---

@LAT97LON25 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28210044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-56 rssi_med:-49 rssi_max:-44

---

@LAT97LON26 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28270044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-61 rssi_med:-49 rssi_max:-47

---

@LAT97LON27 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28330044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-62 rssi_med:-49 rssi_max:-47

---

@LAT97LON28 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28390044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:38 rssi_min:-59 rssi_med:-50 rssi_max:-47

---

@LAT97LON29 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28450044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:53 rssi_min:-53 rssi_med:-48 rssi_max:-46

---

@LAT97LON30 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28510044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-55 rssi_med:-47 rssi_max:-44

---

@LAT97LON31 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28570044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:46 rssi_min:-50 rssi_med:-45 rssi_max:-43

---

@LAT97LON32 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28630044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-56 rssi_med:-46 rssi_max:-43

---

@LAT97LON33 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28690044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:55 rssi_min:-47 rssi_med:-46 rssi_max:-46

---

@LAT97LON34 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28750044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:51 rssi_min:-47 rssi_med:-46 rssi_max:-45

---

@LAT97LON35 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28810044 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:36 rssi_min:-52 rssi_med:-47 rssi_max:-45

---

@LAT97LON36 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28872577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:49 rssi_min:-51 rssi_med:-48 rssi_max:-44

---

@LAT97LON37 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28932577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-53 rssi_med:-49 rssi_max:-45

---

@LAT92LON2 | created:0 | updated:0 | relates:testifies_about@LAT95LON3,derived_from@LAT97LON37,senses@LAT0LON0

**OUTCOME** t_ms:28932577 stream:0x4a194eda wall:0 node:0x300 acting:@LAT95LON3+0 observed_in:@LAT97LON37 band_dbm:6 met:1 violated:0 unobserved:0 streak:0
**RUN** windows_since_last:1 reason:first max_run:30
**EXPECTED** peer:0x00000100 proto:espnow predicted_med:-48 band:6
**OBSERVED** peer:0x00000100 proto:espnow observed_med:-49 delta:-1 verdict:met
**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still tier:@LAT95 observable:@LAT97 band_src:p90_of_still_windows

---

@LAT97LON38 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:28992577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:44 rssi_min:-60 rssi_med:-48 rssi_max:-44

---

@LAT97LON39 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29052577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:54 rssi_min:-63 rssi_med:-49 rssi_max:-45

---

@LAT97LON40 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29112577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-56 rssi_med:-49 rssi_max:-44

---

@LAT97LON41 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29172577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-54 rssi_med:-47 rssi_max:-44

---

@LAT97LON42 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29232577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:52 rssi_min:-50 rssi_med:-47 rssi_max:-44

---

@LAT97LON43 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29292577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:40 rssi_min:-48 rssi_med:-47 rssi_max:-45

---

@LAT97LON44 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29352577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:47 rssi_min:-47 rssi_med:-46 rssi_max:-45

---

@LAT97LON45 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29412577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-50 rssi_med:-46 rssi_max:-45

---

@LAT97LON46 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29472577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:45 rssi_min:-64 rssi_med:-51 rssi_max:-47

---

@LAT97LON47 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:29532577 stream:0x4a194eda wall:0 window_ms:60000
**LINK** peer:0x00000100 proto:espnow n:37 rssi_min:-62 rssi_med:-49 rssi_max:-46

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

@LAT103LON8192 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:7034724 stream:0xee98fca8 wall:0 window_ms:60000 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 9 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 10 | **CORE** entities:0
```

---

@LAT103LON8193 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60001 ±0 frame:17500
said: 1 | **ENTWIN** t_ms:7159812 stream:0xee98fca8 wall:0 window_ms:60001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-40
said: 3 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:96 gen:1 removed:46 last_lon:45 t_ms:7440342 stream:0xee98fca8 wall:0 node:0x00000300

---


---

@LAT103LON8194 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7483868 ±0 frame:5000
said: 1 | **ENTWIN** t_ms:7553285 stream:0xee98fca8 wall:0 window_ms:98613 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-41
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 12 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 13 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 14 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 15 | **CORE** entities:0
```

---

@LAT103LON8195 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 62632 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:8548219 stream:0xee98fca8 wall:0 window_ms:62632 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-71
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 13 | **CORE** entities:0
```

---

@LAT103LON297 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 8901304 ±0 frame:5000
said: 1 | 0x00000010 espnow violated predicted:-62 observed:-50
percept: 1 | 0x00000010 | link_stable | espnow | - | -
said: 2 | 0x00000010 ble met predicted:-68 observed:-66
percept: 2 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT90LON15 | created:0 | updated:0 | relates:describes@LAT0LON0

**STREAM-ORIGIN** stream:0x88023c58 wall:0 t_ms:0 node:0x300 from:0x300
**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 basis:elapsed_since_stream_origin event:origin

---

@LAT103LON8196 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:50583 stream:0x88023c58 wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8197 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1213636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:1204219 stream:0x88023c58 wall:0 window_ms:600000 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:c899b2d3c797 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:7 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,84a329c78fec,0283cce0e689,e6b32d2cea8b
said: 14 | **COVERED** windows:1 entities:10 window_ms:553636 first_t_ms:604219 last_t_ms:604219 covered_by:@LAT103LON8196
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93 windows:1
```

---

@LAT103LON8198 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 1813635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:1804218 stream:0x88023c58 wall:0 window_ms:599999 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93
said: 10 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 11 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,e6b32d2cea8b,c2e94427adcf,84a329c78fec,0283cce0e689
```

---

@LAT103LON8199 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2413635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:2404218 stream:0x88023c58 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-85
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,5ce28c488e0c,e6b32d2cea8b,c2e94427adcf,0283cce0e689,84a329c78fec
```

---

@LAT103LON8200 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3013636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:3004219 stream:0x88023c58 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,5ce28c488e0c,c2e94427adcf,0283cce0e689
```

---

@LAT103LON8201 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3613636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:3604219 stream:0x88023c58 wall:0 window_ms:600000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,e6b32d2cea8b,0283cce0e689,7236bc441422,c2e94427adcf,5ce28c488e0c
```

---

@LAT103LON8202 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4813635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:4804218 stream:0x88023c58 wall:0 window_ms:599999 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 11 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,5ce28c488e0c,e6b32d2cea8b,c2e94427adcf,0283cce0e689
said: 13 | **COVERED** windows:1 entities:9 window_ms:600000 first_t_ms:4204219 last_t_ms:4204219 covered_by:@LAT103LON8201
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-68 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-92 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93 windows:1
```

---

@LAT103LON8203 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5413636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:5404219 stream:0x88023c58 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-38
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:10 ids:f83eb025d3d2,bc102f237ace,5203cfd1b904,02c57d2e0f0d,64677217947d,5ce28c488e0c,7236bc441422,0283cce0e689,c2e94427adcf,e6b32d2cea8b
```

---

@LAT103LON8204 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6013635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:6004218 stream:0x88023c58 wall:0 window_ms:599999 entities:7
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 9 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 10 | **CORE** entities:8 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,0283cce0e689,5ce28c488e0c,c2e94427adcf,e6b32d2cea8b
```

---

@LAT103LON8205 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 6613636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:6604219 stream:0x88023c58 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-69
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,5ce28c488e0c,aef9ff2626ac,0283cce0e689,c2e94427adcf
```

---

@LAT103LON8206 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 7813635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:7804218 stream:0x88023c58 wall:0 window_ms:600000 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 13 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,0283cce0e689,7236bc441422,c2e94427adcf,aef9ff2626ac
said: 15 | **COVERED** windows:1 entities:11 window_ms:599999 first_t_ms:7204218 last_t_ms:7204218 covered_by:@LAT103LON8205
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-70 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:2cfb0f0f0696 n:1 rssi:-90 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-90 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-91 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-93 windows:1
said: 26 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94 windows:1
```

---

@LAT103LON8207 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 8413636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:8404219 stream:0x88023c58 wall:0 window_ms:600001 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 10 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 12 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,0283cce0e689,c2e94427adcf,aef9ff2626ac
```

---

@LAT103LON8208 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9013635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:9004218 stream:0x88023c58 wall:0 window_ms:599999 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 12 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,0283cce0e689,5ce28c488e0c,7236bc441422,c2e94427adcf,aef9ff2626ac
```

---

@LAT103LON8209 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 9613636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:9604219 stream:0x88023c58 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,c2e94427adcf,5ce28c488e0c,7236bc441422,0283cce0e689
```

---

@LAT103LON8210 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 10213635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:10204218 stream:0x88023c58 wall:0 window_ms:599999 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-68
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-72
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 10 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-91
said: 11 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 12 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 13 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 14 | **CORE** entities:11 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,7236bc441422,5ce28c488e0c,84a329c78fec,c2e94427adcf,0283cce0e689
```

---

@LAT103LON8211 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 11413635 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:11404218 stream:0x88023c58 wall:0 window_ms:600000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-86
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-91
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91
said: 10 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 11 | **CORE** entities:10 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,5ce28c488e0c,c2e94427adcf,84a329c78fec,7236bc441422
said: 12 | **COVERED** windows:1 entities:10 window_ms:600000 first_t_ms:10804218 last_t_ms:10804218 covered_by:@LAT103LON8210
said: 13 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 14 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-67 windows:1
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-83 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-89 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-91 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-93 windows:1
```

---

@LAT103LON8212 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 12013636 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:12004219 stream:0x88023c58 wall:0 window_ms:600001 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-69
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-70
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-84
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-87
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-89
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-90
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-92
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 12 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:5
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,bc102f237ace,02c57d2e0f0d,64677217947d,e6b32d2cea8b,5ce28c488e0c,7236bc441422,c2e94427adcf
```

---

@LAT103LON8213 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 604978 ±22 frame:4000
said: 1 | **ENTWIN** t_ms:12651644 stream:0x88023c58 wall:0 window_ms:60000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-81
said: 7 | **ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-85
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-87
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-92
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8214 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 104518 ±0 frame:59000
said: 1 | **ENTWIN** t_ms:45800 stream:0x4d8b207e wall:0 window_ms:104518 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-73
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-73
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9717 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-95
said: 12 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-95
said: 13 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 14 | **CORE** entities:0
```

---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:94 gen:1 removed:48 last_lon:47 t_ms:15673 stream:0xe1f82632 wall:0 node:0x00000300

---

@LAT103LON8215 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 105949 ±0 frame:60000
said: 1 | **ENTWIN** t_ms:46031 stream:0x4e654405 wall:0 window_ms:105949 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-36
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-66
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-71
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 6 | **ENTITY** kind:wifi_ap id:60f41900f1c6 n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:02c57d2f9719 n:1 rssi:-95
said: 10 | **ENTITY** kind:wifi_ap id:7236bc441422 n:1 rssi:-96
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8216 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:6500
said: 1 | **ENTWIN** t_ms:50533 stream:0x01e9f962 wall:0 window_ms:60000 entities:9
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-31
said: 3 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-75
said: 4 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-82
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-93
said: 11 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 12 | **CORE** entities:0
```

---

@LAT103LON8217 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 61053 ±0 frame:7000
said: 1 | **ENTWIN** t_ms:51142 stream:0x92fb56ae wall:0 window_ms:61053 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-42
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-76
said: 6 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-80
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-91
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON8218 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 102060 ±0 frame:60500
said: 1 | **ENTWIN** t_ms:1961892 stream:0x92fb56ae wall:0 window_ms:102060 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-80
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 7 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:000800d3c8ea n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-96
said: 12 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-96
said: 13 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-97
said: 14 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 15 | **CORE** entities:0
```

---

@LAT103LON8219 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 2244248 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:3173909 stream:0x92fb56ae wall:0 window_ms:604629 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-37
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-79
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-83
said: 6 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-89
said: 7 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-93
said: 9 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,5ce28c488e0c,e6b32d2cea8b,c2e94427adcf,aef9ff2626ac,980d67f79619
said: 14 | **COVERED** windows:1 entities:11 window_ms:600676 first_t_ms:2569280 last_t_ms:2569280 covered_by:@LAT103LON8218
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-72 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-81 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-84 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-90 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-91 windows:1
said: 22 | **COVERED-ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92 windows:1
said: 23 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-92 windows:1
said: 24 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94 windows:1
said: 25 | **COVERED-ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95 windows:1
```

---

@LAT103LON8220 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 60000 ±0 frame:17000
said: 1 | **ENTWIN** t_ms:4126557 stream:0x92fb56ae wall:0 window_ms:60000 entities:8
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-33
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 5 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-80
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-95
said: 10 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 11 | **CORE** entities:0
```

---

@LAT103LON16384 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 60000 ±0 frame:17000
said: 1 | **MOTIONWIN** t_ms:4126557 stream:0x92fb56ae wall:0 window_ms:60000 n:738
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:7 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON298 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 3254482 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-55 observed:-55
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000200 ble met predicted:-56 observed:-56
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON299 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 3314482 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-55 observed:-55
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000200 ble met predicted:-56 observed:-56
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-44 observed:-44
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON300 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 3374482 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-56 observed:-55
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-55 observed:-56
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-44 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON301 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 3434482 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-55 observed:-55
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-56 observed:-56
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT100LON2 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:95 gen:1 removed:48 last_lon:47 t_ms:4429700 stream:0x92fb56ae wall:0 node:0x00000300

---

@LAT91LON0 | sid:ab8f77ba | created:0 | updated:0 | relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0
[ew]
conf:134
rev:1
sal:0
touched:0
[/ew]

**LINK-STABLE** peer:0x00000100 proto:espnow node:0x300
**TOUCHED** t_ms:4498196 stream:0x92fb56ae wall:0 unix_s:0
**TALLY** met:3 violated:0 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:0 contradiction:0
**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92 lane_records:3 method:sequential_fold_from_baseline

---

@LAT103LON16385 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 3566077 ±214768 frame:6000
said: 1 | **MOTIONWIN** t_ms:4498196 stream:0x92fb56ae wall:0 window_ms:60081 n:1
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:9 dev_max_mg:9 moving_ms:0
said: 3 | **RUN** windows_since_last:1 reason:first max_run:30
```

---

@LAT103LON8221 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 3612115 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:4546043 stream:0x92fb56ae wall:0 window_ms:106119 entities:11
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-74
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-77
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-86
said: 7 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 8 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 9 | **ENTITY** kind:wifi_ap id:aef9ff2626ac n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-95
said: 11 | **ENTITY** kind:wifi_ap id:acdf9f4ca21c n:1 rssi:-95
said: 12 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95
said: 13 | **RUN** windows_since_last:1 reason:first max_run:6 core_n:3 core_m:5 core_windows:1
said: 14 | **CORE** entities:0
```

---

@LAT103LON302 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 3626077 ±0 frame:6000
said: 1 | 0x00000200 espnow met predicted:-42 observed:-43
percept: 1 | 0x00000200 | link_stable | espnow | + | -
said: 2 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-56 observed:-56
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON303 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 3686077 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-55 observed:-55
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-56 observed:-56
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON304 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 3746077 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-56 observed:-56
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000200 ble met predicted:-55 observed:-55
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON305 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 3806234 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-55 observed:-55
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-56 observed:-56
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON306 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 3866234 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-56 observed:-56
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000200 ble met predicted:-55 observed:-55
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON307 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 3926234 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-56 observed:-56
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000200 ble met predicted:-55 observed:-55
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON308 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 3986523 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-56 observed:-56
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000200 espnow met predicted:-43 observed:-42
percept: 2 | 0x00000200 | link_stable | espnow | + | -
said: 3 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 3 | 0x00000010 | link_stable | espnow | + | -
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON309 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4046523 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-55 observed:-55
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-56 observed:-56
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-42 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON310 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4106523 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-55 observed:-55
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 2 | 0x00000200 | link_stable | espnow | + | -
said: 3 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 3 | 0x00000010 | link_stable | espnow | + | -
said: 4 | 0x00000010 ble met predicted:-56 observed:-56
percept: 4 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON311 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4166892 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-56 observed:-56
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000200 ble met predicted:-55 observed:-55
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON312 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4226892 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-56 observed:-56
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 2 | 0x00000200 | link_stable | espnow | + | -
said: 3 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 3 | 0x00000010 | link_stable | espnow | + | -
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON313 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4288087 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-55 observed:-55
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-56 observed:-55
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON24648 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4288087 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5220192 stream:0x92fb56ae wall:0 window_ms:61195 blocks:195 rate:8000
said: 2 | **ACOUSTIC** rms_mean:83 rms_max:149 peak:392 transients:0
```

---

@LAT103LON314 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4350001 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-55 observed:-55
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000200 espnow met predicted:-43 observed:-42
percept: 2 | 0x00000200 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-55 observed:-55
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON24649 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4350001 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5282106 stream:0x92fb56ae wall:0 window_ms:61914 blocks:243 rate:8000
said: 2 | **ACOUSTIC** rms_mean:95 rms_max:197 peak:444 transients:0
```

---

@LAT103LON315 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4410130 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-55 observed:-55
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 2 | 0x00000200 | link_stable | espnow | + | -
said: 3 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 3 | 0x00000010 | link_stable | espnow | + | -
said: 4 | 0x00000010 ble met predicted:-55 observed:-56
percept: 4 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON24650 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4410130 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5342235 stream:0x92fb56ae wall:0 window_ms:60129 blocks:265 rate:8000
said: 2 | **ACOUSTIC** rms_mean:88 rms_max:161 peak:383 transients:0
```

---

@LAT103LON316 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4492110 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-56 observed:-56
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000200 ble met predicted:-55 observed:-55
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-42 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON24651 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4492110 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5424215 stream:0x92fb56ae wall:0 window_ms:81980 blocks:2492 rate:8000
said: 2 | **ACOUSTIC** rms_mean:90 rms_max:345 peak:734 transients:0
```

---

@LAT103LON317 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4552110 ±0 frame:6000
said: 1 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-56 observed:-56
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 ble met predicted:-55 observed:-55
percept: 3 | 0x00000200 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24652 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4552110 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5484215 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3114 rate:8000
said: 2 | **ACOUSTIC** rms_mean:91 rms_max:218 peak:517 transients:0
```

---

@LAT103LON318 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4612110 ±0 frame:6000
said: 1 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000200 ble met predicted:-55 observed:-55
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000010 ble met predicted:-56 observed:-55
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24653 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4612110 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5544215 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3112 rate:8000
said: 2 | **ACOUSTIC** rms_mean:103 rms_max:396 peak:727 transients:0
```

---

@LAT103LON319 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4672123 ±0 frame:6000
said: 1 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000200 ble met predicted:-55 observed:-55
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000010 ble met predicted:-55 observed:-55
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24654 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4672123 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5604228 stream:0x92fb56ae wall:0 window_ms:60013 blocks:1510 rate:8000
said: 2 | **ACOUSTIC** rms_mean:98 rms_max:243 peak:542 transients:0
```

---

@LAT103LON320 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4732123 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-55 observed:-55
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-55 observed:-56
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 3 | 0x00000010 | link_stable | espnow | + | -
said: 4 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24655 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4732123 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5664228 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3110 rate:8000
said: 2 | **ACOUSTIC** rms_mean:104 rms_max:781 peak:2031 transients:0
```

---

@LAT103LON321 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4792123 ±0 frame:6000
said: 1 | 0x00000010 espnow met predicted:-38 observed:-38
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-56 observed:-56
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 ble met predicted:-55 observed:-55
percept: 3 | 0x00000200 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-43 observed:-43
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24656 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4792123 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5724228 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3111 rate:8000
said: 2 | **ACOUSTIC** rms_mean:103 rms_max:652 peak:1579 transients:0
```

---

@LAT103LON8222 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 4810506 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:5742611 stream:0x92fb56ae wall:0 window_ms:598434 entities:10
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-34
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-76
said: 5 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-82
said: 6 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-90
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-92
said: 9 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-93
said: 10 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-93
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 12 | **RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 core_m:5 core_windows:3
said: 13 | **CORE** entities:6 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,980d67f79619
said: 14 | **COVERED** windows:1 entities:7 window_ms:599957 first_t_ms:5144177 last_t_ms:5144177 covered_by:@LAT103LON8221
said: 15 | **COVERED-ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35 windows:1
said: 16 | **COVERED-ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-74 windows:1
said: 17 | **COVERED-ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-76 windows:1
said: 18 | **COVERED-ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-78 windows:1
said: 19 | **COVERED-ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-87 windows:1
said: 20 | **COVERED-ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94 windows:1
said: 21 | **COVERED-ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-95 windows:1
```

---

@LAT103LON322 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4852147 ±0 frame:6000
said: 1 | 0x00000010 espnow met predicted:-38 observed:-40
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000200 ble met predicted:-55 observed:-55
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000010 ble met predicted:-56 observed:-56
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-43 observed:-42
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24657 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4852147 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5784252 stream:0x92fb56ae wall:0 window_ms:60024 blocks:1481 rate:8000
said: 2 | **ACOUSTIC** rms_mean:142 rms_max:2037 peak:5509 transients:2
said: 3 | **TRANSIENT** t_ms:5751149 stream:0x92fb56ae wall:0 rms:2037
```

---

@LAT103LON323 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4912147 ±0 frame:6000
said: 1 | 0x00000010 espnow met predicted:-40 observed:-41
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000200 ble met predicted:-55 observed:-54
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000010 ble met predicted:-56 observed:-58
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-42 observed:-40
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24658 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4912147 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5844252 stream:0x92fb56ae wall:0 window_ms:60000 blocks:3115 rate:8000
said: 2 | **ACOUSTIC** rms_mean:106 rms_max:1784 peak:5859 transients:1
said: 3 | **TRANSIENT** t_ms:5794735 stream:0x92fb56ae wall:0 rms:1784
```

---

@LAT103LON324 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 4978055 ±0 frame:6000
said: 1 | 0x00000010 espnow met predicted:-41 observed:-41
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-58 observed:-59
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 ble met predicted:-54 observed:-55
percept: 3 | 0x00000200 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-40 observed:-39
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24659 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 4978055 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5910160 stream:0x92fb56ae wall:0 window_ms:65908 blocks:498 rate:8000
said: 2 | **ACOUSTIC** rms_mean:170 rms_max:4327 peak:11896 transients:3
said: 3 | **TRANSIENT** t_ms:5856723 stream:0x92fb56ae wall:0 rms:4327
```

---

@LAT103LON325 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5040146 ±0 frame:6000
said: 1 | 0x00000010 espnow met predicted:-41 observed:-42
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000200 ble met predicted:-55 observed:-55
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000010 ble met predicted:-59 observed:-60
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-39 observed:-42
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24660 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5040146 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:5972251 stream:0x92fb56ae wall:0 window_ms:62091 blocks:122 rate:8000
said: 2 | **ACOUSTIC** rms_mean:331 rms_max:885 peak:2777 transients:0
```

---

@LAT103LON326 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5102124 ±0 frame:6000
said: 1 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-60 observed:-60
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24661 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5102124 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6034229 stream:0x92fb56ae wall:0 window_ms:61978 blocks:379 rate:8000
said: 2 | **ACOUSTIC** rms_mean:136 rms_max:616 peak:1070 transients:0
```

---

@LAT103LON327 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5164011 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-55 observed:-56
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-60 observed:-59
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-42 observed:-41
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON24662 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5164011 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6096116 stream:0x92fb56ae wall:0 window_ms:61887 blocks:373 rate:8000
said: 2 | **ACOUSTIC** rms_mean:89 rms_max:216 peak:393 transients:0
```

---

@LAT103LON328 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5224011 ±0 frame:6000
said: 1 | 0x00000010 espnow met predicted:-41 observed:-42
percept: 1 | 0x00000010 | link_stable | espnow | + | -
said: 2 | 0x00000200 ble met predicted:-56 observed:-56
percept: 2 | 0x00000200 | link_stable | ble | + | -
said: 3 | 0x00000010 ble met predicted:-59 observed:-59
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24663 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5224011 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6156116 stream:0x92fb56ae wall:0 window_ms:60000 blocks:527 rate:8000
said: 2 | **ACOUSTIC** rms_mean:158 rms_max:745 peak:1248 transients:0
```

---

@LAT103LON329 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5284011 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-56 observed:-55
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-59 observed:-59
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-42 observed:-42
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24664 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5284011 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6216116 stream:0x92fb56ae wall:0 window_ms:60000 blocks:2981 rate:8000
said: 2 | **ACOUSTIC** rms_mean:183 rms_max:1491 peak:4223 transients:0
```

---

@LAT101LON0 | sid:cc0653e0 | created:0 | updated:0 |
**PEER** node:0x00000100 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:6238210 stream:0x92fb56ae wall:0

---

@LAT101LON1 | sid:27cc5401 | created:0 | updated:0 |
**PEER** node:0x00000200 spoke:1 declared:0x3ffa verified:0x2faa exercised:0x0008 cap_epoch:6
**TRACE** copresence:255 half_life_ms:600000 reinforced:493 last_ms:1800109
t_ms:6238210 stream:0x92fb56ae wall:0

---

@LAT101LON2 | sid:449b7202 | created:0 | updated:0 |
**PEER** node:0x00000010 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:255 half_life_ms:600000 reinforced:524 last_ms:1800109
t_ms:6238210 stream:0x92fb56ae wall:0

---

@LAT101LON3 | sid:459b7395 | created:0 | updated:0 |
**PEER** node:0x00000011 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:6238210 stream:0x92fb56ae wall:0

---

@LAT101LON4 | sid:429b6edc | created:0 | updated:0 |
**PEER** node:0x00000012 spoke:0 declared:0x0000 verified:0x0000 exercised:0x0000 cap_epoch:0
**TRACE** copresence:0 half_life_ms:600000 reinforced:0 last_ms:0
t_ms:6238210 stream:0x92fb56ae wall:0

---

@LAT103LON330 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5344011 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-59 observed:-59
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000200 ble met predicted:-55 observed:-56
percept: 3 | 0x00000200 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-42 observed:-41
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON24665 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5344011 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6276116 stream:0x92fb56ae wall:0 window_ms:60000 blocks:2254 rate:8000
said: 2 | **ACOUSTIC** rms_mean:122 rms_max:530 peak:1340 transients:0
```

---

@LAT103LON331 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5406034 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-56 observed:-56
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-59 observed:-59
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 4 | 0x00000200 | link_stable | espnow | + | -
```

---

@LAT103LON16386 | created:0 | updated:0

**motion window**

```ttdb-episode
source: motionpercept
at: 5406034 ±0 frame:6000
said: 1 | **MOTIONWIN** t_ms:6338139 stream:0x92fb56ae wall:0 window_ms:62023 n:335
said: 2 | **MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0
said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30
said: 4 | **COVERED** state:still windows:29 n:14653 window_ms:1777934 moving_permille:0 dev_mean_mg:8 dev_max_mg:33 moving_ms:0 first_t_ms:4558182 last_t_ms:6276116 covered_by:@LAT103LON16385
```

---

@LAT103LON24666 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5406034 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6338139 stream:0x92fb56ae wall:0 window_ms:62023 blocks:1251 rate:8000
said: 2 | **ACOUSTIC** rms_mean:127 rms_max:2581 peak:3439 transients:5
said: 3 | **TRANSIENT** t_ms:6324369 stream:0x92fb56ae wall:0 rms:2581
```

---

@LAT103LON8223 | created:0 | updated:0

**entity window**

```ttdb-episode
source: entitypercept
at: 5416297 ±0 frame:6000
said: 1 | **ENTWIN** t_ms:6348402 stream:0x92fb56ae wall:0 window_ms:605791 entities:12
said: 2 | **ENTITY** kind:wifi_ap id:f83eb025d3d2 n:1 rssi:-35
said: 3 | **ENTITY** kind:wifi_ap id:5203cfd1b904 n:1 rssi:-73
said: 4 | **ENTITY** kind:wifi_ap id:02c57d2e0f0d n:1 rssi:-75
said: 5 | **ENTITY** kind:wifi_ap id:84a329c78fec n:1 rssi:-86
said: 6 | **ENTITY** kind:wifi_ap id:bc102f237ace n:1 rssi:-87
said: 7 | **ENTITY** kind:wifi_ap id:64677217947d n:1 rssi:-88
said: 8 | **ENTITY** kind:wifi_ap id:e6b32d2cea8b n:1 rssi:-90
said: 9 | **ENTITY** kind:wifi_ap id:5ce28c488e0c n:1 rssi:-94
said: 10 | **ENTITY** kind:wifi_ap id:9418651af894 n:1 rssi:-94
said: 11 | **ENTITY** kind:wifi_ap id:c2e94427adcf n:1 rssi:-94
said: 12 | **ENTITY** kind:wifi_ap id:980d67f79619 n:1 rssi:-94
said: 13 | **ENTITY** kind:wifi_ap id:0283cce0e689 n:1 rssi:-97
said: 14 | **RUN** windows_since_last:1 reason:changed max_run:6 core_n:3 core_m:5 core_windows:4
said: 15 | **CORE** entities:9 ids:f83eb025d3d2,5203cfd1b904,02c57d2e0f0d,bc102f237ace,64677217947d,e6b32d2cea8b,c2e94427adcf,980d67f79619,0283cce0e689
```

---

@LAT103LON332 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5468081 ±0 frame:6000
said: 1 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 1 | 0x00000200 | link_stable | espnow | + | -
said: 2 | 0x00000010 ble met predicted:-59 observed:-59
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000010 espnow met predicted:-42 observed:-41
percept: 3 | 0x00000010 | link_stable | espnow | + | -
said: 4 | 0x00000200 ble met predicted:-56 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24667 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5468081 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6400186 stream:0x92fb56ae wall:0 window_ms:62047 blocks:243 rate:8000
said: 2 | **ACOUSTIC** rms_mean:96 rms_max:204 peak:502 transients:0
```

---

@LAT103LON333 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5528129 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-56 observed:-56
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-59 observed:-59
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-41 observed:-41
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON24668 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5528129 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6460234 stream:0x92fb56ae wall:0 window_ms:60048 blocks:255 rate:8000
said: 2 | **ACOUSTIC** rms_mean:109 rms_max:256 peak:467 transients:0
```

---

@LAT103LON334 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5592017 ±0 frame:6000
said: 1 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 1 | 0x00000200 | link_stable | espnow | + | -
said: 2 | 0x00000010 espnow met predicted:-41 observed:-41
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-59 observed:-59
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 ble met predicted:-56 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24669 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5592017 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6524122 stream:0x92fb56ae wall:0 window_ms:63888 blocks:239 rate:8000
said: 2 | **ACOUSTIC** rms_mean:106 rms_max:169 peak:502 transients:0
```

---

@LAT103LON335 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5654002 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-59 observed:-59
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-41 observed:-41
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000200 espnow met predicted:-41 observed:-42
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000200 ble met predicted:-56 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24670 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5654002 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6586107 stream:0x92fb56ae wall:0 window_ms:61985 blocks:361 rate:8000
said: 2 | **ACOUSTIC** rms_mean:139 rms_max:1647 peak:2117 transients:2
said: 3 | **TRANSIENT** t_ms:6554237 stream:0x92fb56ae wall:0 rms:1647
```

---

@LAT103LON336 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5715628 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-59 observed:-59
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000010 espnow met predicted:-41 observed:-42
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000200 espnow met predicted:-42 observed:-41
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000200 ble met predicted:-56 observed:-56
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT104LON40 | created:0 | updated:0

**carried through @LAT103LON296**

```ttdb-carried
through: 296
through: 24647
carried: 164 0 363 86 | 0x00000200 | link_stable | espnow
carried: 227 2 585 98 | 0x00000200 | link_stable | ble
carried: 236 0 589 104 | 0x00000100 | link_stable | espnow
carried: 216 0 570 83 | 0x00000010 | link_stable | ble
carried: 210 5 568 83 | 0x00000010 | link_stable | espnow
carried: 4 0 4 6 | 0x00000011 | link_stable | ble
carried: 3 1 4 6 | 0x00000011 | link_stable | espnow
carried: 27 1 28 28 | 0x00000012 | link_stable | ble
carried: 26 1 27 27 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON24671 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5715628 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6647733 stream:0x92fb56ae wall:0 window_ms:61626 blocks:233 rate:8000
said: 2 | **ACOUSTIC** rms_mean:165 rms_max:1558 peak:3761 transients:2
said: 3 | **TRANSIENT** t_ms:6643662 stream:0x92fb56ae wall:0 rms:1558
```

---

@LAT103LON337 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5778131 ±0 frame:6000
said: 1 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 1 | 0x00000200 | link_stable | espnow | + | -
said: 2 | 0x00000010 espnow met predicted:-42 observed:-41
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000200 ble met predicted:-56 observed:-55
percept: 3 | 0x00000200 | link_stable | ble | + | -
said: 4 | 0x00000010 ble met predicted:-59 observed:-59
percept: 4 | 0x00000010 | link_stable | ble | + | -
```

---

@LAT103LON24672 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5778131 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6710236 stream:0x92fb56ae wall:0 window_ms:62503 blocks:58 rate:8000
said: 2 | **ACOUSTIC** rms_mean:113 rms_max:235 peak:522 transients:0
```

---

@LAT104LON41 | created:0 | updated:0

**carried through @LAT103LON296**

```ttdb-carried
through: 296
through: 24656
carried: 164 0 363 86 | 0x00000200 | link_stable | espnow
carried: 227 2 585 98 | 0x00000200 | link_stable | ble
carried: 236 0 589 104 | 0x00000100 | link_stable | espnow
carried: 216 0 570 83 | 0x00000010 | link_stable | ble
carried: 210 5 568 83 | 0x00000010 | link_stable | espnow
carried: 4 0 4 6 | 0x00000011 | link_stable | ble
carried: 3 1 4 6 | 0x00000011 | link_stable | espnow
carried: 27 1 28 28 | 0x00000012 | link_stable | ble
carried: 26 1 27 27 | 0x00000012 | link_stable | espnow
```

---

@LAT103LON338 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5840011 ±0 frame:6000
said: 1 | 0x00000010 ble met predicted:-59 observed:-59
percept: 1 | 0x00000010 | link_stable | ble | + | -
said: 2 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 2 | 0x00000200 | link_stable | espnow | + | -
said: 3 | 0x00000010 espnow met predicted:-41 observed:-42
percept: 3 | 0x00000010 | link_stable | espnow | + | -
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24673 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5840011 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6772116 stream:0x92fb56ae wall:0 window_ms:61880 blocks:238 rate:8000
said: 2 | **ACOUSTIC** rms_mean:97 rms_max:194 peak:385 transients:0
```

---

@LAT103LON339 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5902001 ±0 frame:6000
said: 1 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 1 | 0x00000200 | link_stable | espnow | + | -
said: 2 | 0x00000010 espnow met predicted:-42 observed:-42
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-59 observed:-59
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 ble met predicted:-55 observed:-55
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24674 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5902001 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6834106 stream:0x92fb56ae wall:0 window_ms:61990 blocks:383 rate:8000
said: 2 | **ACOUSTIC** rms_mean:106 rms_max:465 peak:1319 transients:0
```

---

@LAT103LON340 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 5962001 ±0 frame:6000
said: 1 | 0x00000200 espnow met predicted:-41 observed:-41
percept: 1 | 0x00000200 | link_stable | espnow | + | -
said: 2 | 0x00000010 espnow met predicted:-42 observed:-45
percept: 2 | 0x00000010 | link_stable | espnow | + | -
said: 3 | 0x00000010 ble met predicted:-59 observed:-61
percept: 3 | 0x00000010 | link_stable | ble | + | -
said: 4 | 0x00000200 ble met predicted:-55 observed:-54
percept: 4 | 0x00000200 | link_stable | ble | + | -
```

---

@LAT103LON24675 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 5962001 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6894106 stream:0x92fb56ae wall:0 window_ms:60000 blocks:1700 rate:8000
said: 2 | **ACOUSTIC** rms_mean:120 rms_max:547 peak:1546 transients:0
```

---

@LAT103LON341 | created:0 | updated:0

**link window**

```ttdb-episode
source: perceptlearn
at: 6022001 ±0 frame:6000
said: 1 | 0x00000200 ble met predicted:-54 observed:-56
percept: 1 | 0x00000200 | link_stable | ble | + | -
said: 2 | 0x00000010 ble met predicted:-61 observed:-61
percept: 2 | 0x00000010 | link_stable | ble | + | -
said: 3 | 0x00000200 espnow met predicted:-41 observed:-43
percept: 3 | 0x00000200 | link_stable | espnow | + | -
said: 4 | 0x00000010 espnow met predicted:-45 observed:-43
percept: 4 | 0x00000010 | link_stable | espnow | + | -
```

---

@LAT103LON24676 | created:0 | updated:0

**acoustic window**

```ttdb-episode
source: acousticpercept
at: 6022001 ±0 frame:6000
said: 1 | **ACOUSTICWIN** t_ms:6954106 stream:0x92fb56ae wall:0 window_ms:60000 blocks:2850 rate:8000
said: 2 | **ACOUSTIC** rms_mean:132 rms_max:777 peak:3058 transients:0
```
