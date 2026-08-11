# TTN Semantic Positioning

**Inferring Relative Physical Position of ESP32 Nodes from TTDB Semantic Relationships**

*Draft 0.3 — Toot Toot Engineering — August 2026*

**Status: PRIMARY HYPOTHESIS of robot_team (adopted 2026-07-07).** This is the
claim the fleet now exists to prove. The build order is PLAN.md **Act II**;
companion.md §6 tracks its live state. Everything verified so far — toots,
HMAC, sync, Dream Cycle, pulse — is the floor this proof stands on.

**What changed in 0.3 (2026-08-11), and why.** Between 0.2 and 0.3 the fleet built
a great deal of infrastructure that was filed as "off the hypothesis path" —
stigmergic fields and lane discipline (`TTDB-RFC-0010`), the team time stream, lane
generations, stable record identity, change-triggered lanes, and the default network
(`default-network.md`). Read together, that work does not sit beside this document;
it **corrects** it in six places and **strengthens** it in two. Every change below is
tagged with the measurement or RFC that forced it, so this revision reads as evidence
rather than as opinion:

| § | Change | Driven by |
|---|---|---|
| 0.1 | Shape vs pose: the ambiguity is **4 DoF**, not just flip | `default-network.md` §1 |
| 0.2 | Proof leg 1 reports `(sigma, pose_ceiling)`, not `sigma` alone | the above, made honest |
| 0.3 | **The falsifier can fire falsely at bench scale** | cross-node overlap, 2026-08-11 |
| 1.1 | The entity tier's resolving power is bounded by AP alphabet | night 1/3 baselines |
| 1.2 | Anchoring on V4-A is **circular** — its coordinate is configured | this revision |
| 2.3–2.4 | Lane register + identity kinds for positioning records | `TTDB-RFC-0010` §3, §4.2 |
| 3.2b | **Distributed embedding** — the fleet shapes itself, no laptop | `default-network.md` §5 |
| 3.3 | TDoA must use the **pulse**, never the time stream | `TimeStream` is a ratchet |
| 4.3 | The ablation needs a stated geometry or it proves nothing | cross-node overlap |
| A | Phase 0's risk is retired; the mitigation was the wrong one | run-length, 2026-08-04 |

---

## 0. The Hypothesis — and the three proofs

> **A mesh of ESP32 nodes can infer its own physical arrangement from the
> semantic structure of what it perceives** — umwelt overlap implies spatial
> proximity — **accurately enough to be useful.**

### 0.1 Shape and pose — what "its own physical arrangement" can and cannot mean

**(New in 0.3. Source: `default-network.md` §1, which reached this by a different
road and got there first.)**

A relation between two nodes — do we hear each other, do we see the same access
points, did that deposit arrive — is **invariant under moving the whole fleet**.
So everything inferable from common information alone is inferable only up to the
symmetry group of the plane: **translation (2) + rotation (1) + reflection (1) =
four degrees of freedom** that no amount of umwelt overlap can touch. This is not
a defect to engineer away; it is what "inferred from common information" *means*.

> **Umwelt overlap gives the fleet its SHAPE. Capabilities are what give the shape
> a POSE.**

Those four fall only to a node holding a capability nobody else has:

| Breaks | Needs | Who has it |
|---|---|---|
| translation | one absolute fix | T-Deck GPS |
| rotation | a second fix at a different place | T-Deck GPS, roaming |
| reflection | a third non-collinear fix | T-Deck GPS, roaming (`anchor`'s "≥3 ties resolve mirror") |
| *nothing* | RSSI amplitude | ⚠ measured broken outdoors: 2–7× over-range, decorrelated |

**Consequence, and it supersedes §1.3:** flip ambiguity is not *the* limitation, it
is *one of four*, and the other three were previously treated as solved by anchoring
(§1.2) when they are not — see §1.2's correction.

### 0.2 The proof legs

"Useful" is pinned to three concrete, falsifiable proof legs:

1. **Verified.** Position beliefs land within their own stated uncertainty of
   ground truth, measured against the **T-Deck's GPS** used as a roaming
   verification instrument (§4). The map must be *honest*, not just pretty.
   ⚠ **Revised in 0.3: the stated uncertainty is `(sigma, pose_ceiling)`, a PAIR,
   and reporting `sigma` alone fails this leg by its own standard.** Position error
   has two components with different shapes: shape uncertainty, which `sigma`
   covers and which is roughly Gaussian, and **pose ambiguity, which `sigma` does
   not cover at all** — it is a discrete 4-DoF freedom, not a spread. A fleet with
   perfect shape knowledge and no GPS fix has `sigma → 0` and **unbounded** position
   error. `pose_ceiling` states how many of the four degrees of freedom are
   currently pinned, and by whom.
2. **Actuated.** The inferred pairwise proximity **drives the transport ladder
   automatically**: each node pair selects **ESP-NOW when the belief says
   in-range and falls back to LoRa when it doesn't**, with hysteresis, without
   configuration (§3, Phase 5). Position belief becomes behavior.
3. **Rendered.** The emergent map is *visible* as **TTCP** — network + node
   status drawn from the master TTDB on the **laptop** (browser viewer, the
   [antfriend.github.io](https://github.com/antfriend/antfriend.github.io)
   pattern) and natively on the **T-Deck's 320×240 screen** (§3, Phase 6).
   The fleet draws a live map of itself.

### 0.3 Falsifier — and the way it can fire falsely

**Falsifier:** the ablation study (§4.3) compares RSSI-only against
RSSI+semantic evidence (entity co-occurrence, BLE near-range, environmental
TDoA). If the semantic layer adds nothing over plain radio ranging, the
hypothesis fails, and this document records why.

🛑 **NEW IN 0.3 — THE FALSIFIER HAS A FALSE-POSITIVE MODE, AND THE FLEET IS
CURRENTLY SITTING IN IT.** Measured 2026-08-11 from the night-3 archives, two nodes
a few metres apart on the same bench, all night (**corrected same day — see the
box below**):

```
cross-node entity DISTANCE (V4-A vs Cardputer, n=11)  min 0.125  p50 0.250  max 0.250
same-node drift, 10 min apart (night 3, n=31)         p50 0.111  p90 0.222  max 0.375
                                                                 p95 0.250
```

**A typical between-node difference lands on the still node's p95 — margin over p90
is ~1.1x.** So the entity tier *can* barely tell these two nodes apart at bench
separation, but not by enough to attribute anything to distance: an ablation run
here would be reading its own noise. Run §4.3's ablation at this geometry and it
will report — uselessly — that the semantic layer adds nothing.

**That would be a test-geometry artifact, not a result about the tier**, and
recording it as a falsification would lose the hypothesis for the wrong reason.
§4.3 is therefore amended to require a **stated separation** at which the entity
sets measurably differ, established *before* the ablation runs, with a
**pre-registered margin of 2.0x** over the still-node floor (§4.3).

> 📌 **CORRECTION, 2026-08-11, same day: the first draft of this box said the
> between-node signal was *smaller* than the within-node noise (distance ~0.125),
> and blamed an upward overlap bias from V4-A's folding build that it claimed made
> the conclusion safer. Both halves were wrong.** A folded record still itemises
> **its own** window in `**ENTITY**` lines — only the *suppressed* windows are gone
> — so per-window sets were available for V4-A all along. Including the
> `**COVERED**` union inflated the overlap and **halved** the measured distance
> (0.250 → 0.125), and the bias runs toward *understating* separation, i.e. toward
> the "not admissible" verdict rather than away from it. **The verdict is unchanged
> and the reasoning is not.** Rule that falls out, and it is the instrument's design:
> **for CROSS-NODE separation use each record's own window set (valid on a folded
> lane); for WITHIN-NODE drift a folded lane is unusable (the suppressed windows are
> gone).** The two measurements have different input requirements and one command
> must not treat them alike.

---

## 1. The Basic Idea

TTDB normally runs in one direction: physical position (`@LATxLONy` coordinate addressing) organizes knowledge. Semantic positioning inverts this. Nodes infer their physical arrangement *from* the structure of what they know.

The governing principle is **umwelt overlap implies spatial proximity**. Each node's umwelt — the slice of the world it can perceive — is bounded by radio range, sensor reach, and environmental exposure. Two nodes whose percept streams reference the same external entities, at correlated times, with correlated intensities, must occupy overlapping regions of physical space. The degree and character of that overlap is a distance measurement in disguise.

This makes position an *emergent belief* rather than a configured constant. A node's coordinate address becomes an epistemically weighted claim, subject to the same `conf` / `sal` / `rev` / `touched` machinery (TBEW, RFC-0005) as any other node in the graph, consolidated by the Dream Cycle (RFC-0002), and revisable when evidence changes — for example, when a node is physically moved.

### 1.1 Signal Sources

Three families of evidence, all naturally representable as paired `@PERCEPT:before` / `@PERCEPT:after` nodes:

1. **Link-layer percepts.** Every received ESP-NOW or LoRa frame carries RSSI and SNR. Each reception is a percept: *before* = expected link quality (prior belief about the pairwise link), *after* = observed value. RSSI-to-distance conversion is noisy (±3–6 dB swings from multipath, foliage, humidity), but noise is exactly what epistemic weighting handles: individual observations carry low `conf`; consolidated pairwise estimates gain `conf` with sample count and consistency.

2. **Shared-entity co-occurrence.** Nodes log sightings of external entities: WiFi SSIDs/BSSIDs, BLE advertisement MACs, acoustic events, recognized RF beacons. The Jaccard overlap of two nodes' entity sets is a coarse proximity measure. Shared visible WiFi APs alone typically bound two observers to within ~50–100 m of each other; BLE overlap bounds tighter (~10–30 m).

   ⚠ **Measured limit (new in 0.3) — this tier's resolving power scales with the
   AP alphabet, and this bench is at the low end of it.** The entire night-1
   segment is **10 distinct BSSIDs**; night 3 is **9**, and 9 of those 9 are
   shared with night 1's 10 — the same room, twice. With per-window sets of 5–9
   drawn from an alphabet of ~10, one AP appearing or vanishing moves Jaccard by
   0.125–0.200, so the metric takes a **handful of discrete values** and
   "continuous drift" is a misdescription of it. Two consequences the 0.2 text
   did not anticipate:
   - The `~50–100 m` bound is *not wrong*, but it is the tier's **resolution**,
     not merely its reach: below that scale the tier contributes a **cap**, never
     a distance (§3 Phase 1 already says "caps rather than refines" — 0.3 says
     *why*, and that the cap is all there will ever be at this density).
   - A **denser AP environment makes this tier better**, and a sparse one makes it
     nearly blind. Any conclusion about the entity tier must state the alphabet
     size it was measured at, exactly as an RSSI conclusion must state the terrain.

3. **Environmental gradient timing.** Spatially propagating transients — rain fronts, temperature drops, sunrise/sunset light curves, pressure waves — arrive at different nodes at different times. Time-difference-of-arrival between correlated environmental percepts yields directional constraints. Solar charge curves (V4-B) additionally encode shading geometry and panel orientation at zero sensor cost.

4. **BLE near-range approximation.** Every board carries BLE 5.0. Nodes advertise and scan: inter-node BLE advertisement visibility (and its RSSI) bounds a pair to roughly 10–30 m — a short-range proximity tier that tightens `dist_sigma_m` exactly where ESP-NOW RSSI is least informative (near-field flattening: past a few meters of separation, strong ESP-NOW RSSI barely changes). Same percept schema as link observations, `proto: ble`. BLE is an *approximation tool*, never a transport: it contributes evidence, not toots.

### 1.2 Synthesis

Pairwise evidence is fused into a single affinity/distance matrix and embedded into 2D via anchor-free localization (MDS-MAP or spring relaxation). For meshes of 3–20 nodes this is comfortably within ESP32 compute budgets, or can be delegated to the head node / attached host — **and as of 0.3 the fully distributed version is a named goal, not a footnote (§3 Phase 2b).**

🛑 **CORRECTION IN 0.3 — ANCHORING ON V4-A IS CIRCULAR, AND 0.2 SAID OTHERWISE.**
The previous text read: *"Nodes with authoritative known positions (the bridge/head,
V4-A) act as anchors that pin the relative map to absolute `@LATxLONy`
coordinates."* **V4-A's coordinate is configured, not measured.** Pinning the map to
it does not convert shape into pose; it asserts the pose and then reports the
assertion back as a result. Under §0.1 the only things that pin the four degrees of
freedom on this fleet are **GPS fixes and the tape measure** — a configured constant
is neither.

This does not make V4-A useless. It remains the right **origin of the relative
frame** (a labelling choice, free of epistemic content) and the natural place to run
the solver. What it must not be is the *source of absolute position*, and any
`@BELIEF:POSITION` whose `anchor_chain` contains only V4-A is a **shape claim
wearing pose clothing** — it must report `pose_ceiling: 0` (§0.2), not a small
`sigma`.

### 1.3 Known Limitation: Flip Ambiguity — *generalised in 0.3, see §0.1*

Three nodes determine a triangle only up to reflection. Disambiguation requires one of: a fourth node, a second anchor with known coordinates, or a declared directional constraint (e.g., "V4-C is east of V4-B"). The system should represent an unresolved flip as *two candidate embeddings with split confidence* rather than silently choosing one.

⚠ **0.3: this section is correct but was mis-scoped.** Reflection is **one of four**
undetermined degrees of freedom, and it is the only one 0.2 treated as a known
limitation — translation and rotation were silently assumed away by the circular
anchoring §1.2 has now retracted. The general statement lives in **§0.1**; the
dual-candidate representation prescribed here is the right *shape* of answer and
generalises directly: an unpinned degree of freedom is represented, never guessed.

---

## 2. Data Model

### 2.1 New Node Types

All stored as flat Markdown per TTDB conventions; field names follow TBEW (RFC-0005).

**Link observation percept** (high volume, ephemeral, consolidated then pruned):

```markdown
@PERCEPT:LINK @LAT43.6421xLON-116.2834
peer: V4-C
before: { rssi_expected: -87, conf: 0.42 }
after:  { rssi: -84, snr: 7.5, freq_err: 120 }
proto: espnow | lora
ts: 2026-07-05T14:22:31Z
conf: 0.15   # single observation, low confidence
sal: 0.2
rev: 0
```

**Entity sighting percept:**

```markdown
@PERCEPT:ENTITY @LAT43.6421xLON-116.2834
entity: BSSID:a4:2b:b0:xx:xx:xx
kind: wifi_ap | ble_mac | acoustic | rf_beacon
rssi: -71
ts: 2026-07-05T14:20:02Z
conf: 0.6
```

**Environmental transient percept:**

```markdown
@PERCEPT:ENV @LAT43.6421xLON-116.2834
signal: temp_drop | light_rise | pressure_wave | rain_onset
magnitude: -4.2C over 300s
onset_ts: 2026-07-05T13:58:40Z
conf: 0.5
```

**Consolidated pairwise link belief** (Dream Cycle output — the durable object):

```markdown
@BELIEF:PROXIMITY @pair(V4-B, V4-C)
dist_est_m: 214
dist_sigma_m: 60
n_obs: 342
sources: { rssi: 0.71, entity_jaccard: 0.18, env_tdoa: 0.11 }  # evidence mix
conf: 0.78
sal: 0.9
rev: 14
touched: 2026-07-05T15:00:00Z
```

**Position belief** (per node — the payoff object):

```markdown
@BELIEF:POSITION @node(V4-C)
sid: <KEY-kind stable id over node:0x…>   # 0.3, RFC-0010 §4.2 — see §2.4
lat: 43.64312
lon: -116.28067
sigma_m: 45                                # SHAPE uncertainty only
pose_ceiling: 3                            # 0.3 — how many of the 4 DoF are pinned
dof_pinned: { translation: gps@tdeck_1, rotation: gps@tdeck_1, reflection: none }
anchor_chain: [gps@tdeck_1 x2]             # 0.3 — GPS/tape only; NOT a configured node
embedding_rev: 9
flip_resolved: false                       # implied by reflection: none
conf: 0.71
rev: 9
```

⚠ **`sigma_m` and `pose_ceiling` are not substitutes and must both be present**
(§0.2). A record with `pose_ceiling: 0` is a *shape* claim: its `lat`/`lon` are one
of an infinite family related by translation and rotation, and one of two mirror
images, however small `sigma_m` is. Renderers must show this (§3 Phase 6); a
consumer that reads `sigma_m` alone will be confidently wrong.

### 2.2 Key Design Decision

Raw link percepts are **write-heavy, short-lived**. They exist to feed consolidation, then are pruned (or downsampled to periodic summaries) to respect flash wear and flat-file scale on ESP32-class storage. The durable graph objects are the consolidated `@BELIEF:PROXIMITY` and `@BELIEF:POSITION` nodes. This matches the existing Dream Cycle philosophy: experience is cheap, consolidated belief is the asset.

🎯 **REVISED IN 0.3 — COMPRESS THE LANE; DO NOT PRUNE IT. Pruning was the wrong
mitigation and the fleet measured it.** "Then are pruned" was 0.2's answer to
percept volume, and in practice it was a treadmill *and* it consumed a budget 0.2
did not know existed (§4.5). What worked instead is **change-triggered lanes with
run-length**: a window whose verdict matches the run in progress writes nothing, and
the record that closes the run states what it suppressed.

| lane | before | after | mechanism |
|---|---|---|---|
| `@LAT95` motion | fills in 48 min | ~24 h | run-length, 2026-08-04 |
| `@LAT92` outcomes | fills in 24 min | — | run-length, 2026-08-04 |
| `@LAT96` entity | 8 h | 48 h | stable-core trigger, 2026-08-10 |

⚠ **Compression is legitimate only where it is LOSSLESS FOR THE CONSUMER, and that
must be argued per lane, not assumed.** Folding a verdict N times equals folding it
once per window, which is why run-length is safe on a *tally*; dropping unchanged
windows *without* the count would have removed `conf`'s denominator and made every
belief over-confident. For `@LAT96` the consumer computes a **union**, so the record
that closes a run carries the run's union (`**COVERED-ENTITY**`) and loss is zero
**by construction** — a window whose entities would not fit ends the run rather than
being dropped. Verified on hardware 2026-08-11: without that union the fold would
have permanently dropped 2 BSSIDs from exactly the quantity the tier consumes.

**Any new positioning lane must state its consumer and its losslessness argument
before it is written.**

---

### 2.3 Lane register — which positioning records are EVIDENCE and which are FIELD

**(New in 0.3. Source: `TTDB-RFC-0010` §3, which is normative on adoption and which
the positioning lanes are already governed by.)**

0.2 proposed record *types* with no statement of record *class*. That gap is no
longer academic: the fleet now has a live FIELD lane (`@LAT101`, peer co-presence,
decay-on-read, no prune path by design) carrying what is unmistakably positioning
evidence. RFC-0010 draws a hard line, and it lands right across this document:

> **§6.1 — no measured constant may come from a FIELD lane.**

| lane | carries | class | may feed a calibration constant? |
|---|---|---|---|
| `@LAT97` | per-peer RSSI histograms (`LinkPercept`) | **EVIDENCE** | yes |
| `@LAT96` | WiFi BSSID sightings (`EntityPercept`) | **EVIDENCE** | yes |
| `@LAT95` | motion windows (`MotionPercept`) | **EVIDENCE** | yes |
| `@LAT94` | acoustic transients (`AcousticPercept`) | **EVIDENCE** | yes |
| `@LAT101` | peer co-presence trace (`Social`) | **FIELD** | 🛑 **no** |
| `@LAT100` | lane-generation boundaries | PROVENANCE | n/a |

**So: co-presence may inform a belief, but no path-loss exponent, no drift
threshold, and no distance calibration may be derived from it.** `@LAT96` was
deliberately kept EVIDENCE for precisely this reason — the still-node drift
threshold comes from it, and a FIELD lane cannot carry a number anything else is
measured against. A field is an *optimisation*, never the store of record (§6.3).

⚠ **And RFC-0010 §6.2 forbids a `derived_from` edge targeting a FIELD record**, so a
`@BELIEF:PROXIMITY` may not cite `@LAT101` as provenance even when co-presence
contributed to it. If co-presence is to be citable, it needs an EVIDENCE-class
shadow — that decision is deferred, and named as deferred, rather than taken by
accident at the first `derived_from` someone writes.

### 2.4 Identity — a position belief must keep its name across revisions

**(New in 0.3. Source: `TTDB-RFC-0010` §4.2, decided 2026-08-09 by measurement.)**

RFC-0010 distinguishes two identity kinds: **EVENT** (body and time fold into the
id) and **KEY** (both stay out, so a revised record keeps its name). Phase 4 makes
`@BELIEF:POSITION` a *living* belief, revised continuously as evidence accumulates —
which settles the question:

> **`@BELIEF:POSITION` and `@BELIEF:PROXIMITY` MUST be KEY-kind**, natural key
> `node:0x%08lx` and the ordered pair respectively.

Under an EVENT-kind id every revision renames the record, and every typed edge
pointing at it breaks — the map would lose its own history exactly as it started
being worth having. `@LAT91` already writes a KEY-kind sid stable across boots and
rewrites, and the laptop recomputes it from the key alone; copy that.

⚠ On collision, RFC-0010 §4.2.4 is **refuse, do not perturb** — a positioning
record that cannot be named is dropped with a diagnostic, never renamed into a
neighbour's slot.

---

## 3. Implementation Plan — Core Features

### Phase 0: Instrumentation (1–2 weeks)

*Goal: every frame reception becomes a percept.*

- Hook the ESP-NOW receive callback (`esp_now_register_recv_cb`) to capture `rx_ctrl.rssi` per frame; on the LoRa path, read RSSI/SNR from the SX1262 driver after each packet.
- Buffer observations in RAM (ring buffer, ~64 entries) and flush to a rolling percept file every N minutes or on buffer-full. Never write per-packet — flash wear.
- Piggyback: each node appends its own recent RSSI observations of peers into existing beacon/heartbeat frames (a few bytes per peer), so every node learns *both directions* of every link. Asymmetry (A hears B at -80, B hears A at -90) is itself diagnostic of antenna/obstruction differences.
- Add periodic WiFi scan (V4s only; ~2 s scan every 10–15 min, duty-cycled for the solar node) logging visible BSSIDs as entity percepts.

*Deliverable:* nodes accumulating link and entity percepts in TTDB format. Verify with a serial dump — this phase is pure data plumbing, no inference.

### Phase 1: Pairwise Distance Estimation (1–2 weeks)

*Goal: consolidated `@BELIEF:PROXIMITY` per node pair.*

- **RSSI → distance:** log-distance path loss model, `RSSI(d) = RSSI(d₀) − 10·n·log₁₀(d/d₀)`. Calibrate `RSSI(d₀)` and path-loss exponent `n` once with a tape measure and two nodes at known separations (do 5 m, 20 m, 50 m, 100 m). Expect `n ≈ 2.7–3.5` outdoors with vegetation.
- **Robust aggregation:** use the *median* of the top-quartile RSSI values over the consolidation window (the strongest receptions are closest to line-of-sight truth; fading only subtracts). Compute `dist_sigma_m` from observed spread.
- **Entity overlap term:** Jaccard index over BSSIDs seen in the same window, mapped to a coarse distance bound. This term mostly *caps* the RSSI estimate ("they share 6 APs, they cannot be 800 m apart") rather than refining it.
- Run this as a Dream Cycle job: read window of raw percepts → emit/update `@BELIEF:PROXIMITY` → bump `rev`, grow `conf` per TBEW's EPS formula → prune consumed raw percepts.

*Deliverable:* a proximity belief file per pair whose `dist_est_m` is within ~30–50% of tape-measure truth. That's the realistic accuracy class for RSSI ranging; the design absorbs it via `sigma`.

### Phase 2: Embedding and Anchoring (2–3 weeks)

*Goal: `@BELIEF:POSITION` for every node.*

- Build the symmetric distance matrix from proximity beliefs, weighting entries by `conf` (missing/low-conf pairs get large sigma, not zero weight).
- **Solver:** for ≤10 nodes, skip classical MDS eigendecomposition and use weighted spring relaxation (stress majorization): iterate `xᵢ ← xᵢ + η·Σⱼ wᵢⱼ·(‖xᵢ−xⱼ‖ − dᵢⱼ)·(xⱼ−xᵢ)/‖xᵢ−xⱼ‖`. It's ~40 lines of C, converges in hundreds of iterations, handles missing entries natively, and warm-starts from the previous embedding so incremental updates are nearly free.
- **Anchoring — revised in 0.3 (§1.2).** V4-A is the **origin of the relative
  frame**, which is a labelling choice and carries no epistemic content; it is
  **not** an anchor, because its coordinate is configured rather than measured.
  Pose comes only from **GPS fixes and the tape measure**. **The T-Deck is
  therefore the only anchor the fleet has:** its GPS gives it an authoritative
  position wherever it happens to be, and because it *roams* it is effectively
  many anchors over time — each GPS-stamped position it visits pins one more
  degree of freedom (the mobile-node/SLAM-lite mode of §5, promoted to a core
  role). Track this explicitly: **1 fix pins translation, 2 pins rotation, ≥3
  non-collinear pins reflection** (§0.1), and the count *is* `pose_ceiling`.
  ⚠ Until the T-Deck has taken fixes, every position belief carries
  `pose_ceiling: 0` and must render as a shape, not a map (Phase 6).
- **Flip handling:** evaluate stress for both mirror images; if within noise of each other, emit both candidates with split `conf` and mark `flip_resolved: false`.
- Run on the head node (V4-A) or attached host; publish resulting position beliefs back over the mesh so each node stores its own.

*Deliverable:* a self-drawn map of the three-node spine, honest about its uncertainty.

### Phase 2b: Distributed embedding — the fleet shapes itself (NEW IN 0.3)

*Goal: the shape estimate exists with the laptop switched off.*

**(Source: `default-network.md` §5, promoted here from "off the hypothesis path".)**

Phases 1–2 as written permit the embedding to run "on the head node (V4-A) or
attached host" — so the hypothesis as stated in 0.2 is **provable with a laptop
doing the mathematics**. That is a weaker claim than the fleet's own premise, and
the machinery to strengthen it is already built: `TraceField` (decay-on-read,
HELLO-carried, max-merged), the `Social` capability table, and `pulse::Chart`'s
band-wide idle scene, which is currently silence.

Per idle bar, each node independently:

1. **Voices the social field** — one cell per peer on the 16-step grid, amplitude =
   decayed co-presence. The fleet's shape becomes *audible*.
2. **Takes one damped relaxation step** on its own `(x, y, sigma)` — pull toward
   peers with high umwelt overlap, push from peers with none.
3. **Recomputes `pose_ceiling`** from the capability table (§0.1) and adjusts its
   own re-advertisement rate.

All three are local reads of a shared medium; nothing addresses anybody, which is
the test that this is stigmergy rather than a protocol with extra steps.

⚠ **Damping and a stated iteration budget are mandatory** — a distributed
relaxation can oscillate where a central one converges, and this fleet has no
global step counter to appeal to.

🔬 **Falsifier for Phase 2b specifically:** if the distributed shape estimate agrees
with `companion.py positions` in every configuration tested, **the distributed
version added nothing** — say so, record it, and keep the central solver. Phase 2b
is a strengthening of the hypothesis, not a prerequisite for it: **Phases 1–2 alone
still prove or refute §0**, and 2b may be abandoned without touching the primary
proof.

### Phase 3: Environmental TDoA (2–4 weeks, parallelizable)

*Goal: directional constraints from shared transients.*

- Onset detection per sensor channel: CUSUM or simple derivative-threshold on temperature, light, pressure. Log `@PERCEPT:ENV` with onset timestamp.
- **Clock sync is the hard part.** ESP-NOW round-trip timestamp exchange gets nodes to ~1 ms agreement, sufficient for slow fronts (weather: minutes across hundreds of meters) but not acoustic events. Start with slow signals only.

  🛑 **NEW IN 0.3 — USE THE PULSE, NEVER THE TIME STREAM. This is a trap, and the
  time stream is the thing you will reach for.** The fleet now owns a shared
  timeline (`TimeStream`, `stream:`/`wall:`) that looks exactly like TDoA
  infrastructure. It is the wrong instrument: **a stream's clock is a ratchet** —
  elapsed-since-its-own-origin, fastest crystal heard wins — which is what makes
  "older stream wins" and monotonicity one rule, and which makes it *correct for
  ordering and recency and wrong for measuring a duration*. **TDoA is a cross-node
  duration.** A ratcheting counter can move a node's clock forward by seven weeks
  and still be behaving exactly as designed.

  The right reference is the **pulse** — conductor-elected, phase-locked, and
  already counted by every node in the band. Two pieces of it are built and
  hardware-verified:
  - `@LAT94` `AcousticPercept` logs the **fleet-clock timestamp of the loudest
    transient** in each window — a time-of-arrival measurement, not an amplitude
    one, so it is not subject to the shadowing that broke RSSI outdoors.
  - **Beat-scheduled recording** (`CMD_RECORD`) captures a window off the band
    clock so every node records the same instant, and each node **stamps what it
    BELIEVED the time was** — so clock wobble stays correctable rather than baked
    in. That is the right design shape for TDoA and it already exists.

  📊 **Measured resolution floor:** band skew is mostly whole-fleet common mode;
  with the per-run mean removed and the conductor excluded (its 0.0 is true by
  construction), the residual is **~1.9 m**. That is the spatial resolution class
  to expect from acoustic TDoA on this fleet — sufficient for bench-to-garden
  geometry, not for centimetres. State it before running the experiment, not after.

  ⚠ **Only the Cardputer has a microphone**, so multi-node acoustic TDoA is
  unexercised: one clap heard by two nodes needs a second mic-equipped node. This
  is the single largest hardware gap on the hypothesis path.
- Cross-correlate onset times across nodes for the same detected event class within a window; each match yields a "B preceded C by Δt" constraint. Accumulate these as directional priors that (a) break flip ambiguity statistically and (b) add gradient-direction information the distance matrix lacks.
- Solar node bonus: V4-B's charge-current curve shape vs. clear-sky model encodes shading azimuth — a free compass-like hint.

### Phase 4: Closing the Loop (1 week)

*Goal: position as living belief.*

- Node self-address update: when `@BELIEF:POSITION` `conf` exceeds a threshold and disagrees with the node's configured `@LATxLONy` beyond `sigma`, raise a revision event. Policy choice per deployment: auto-adopt (fully emergent addressing) or flag-for-operator (conservative).
- Movement detection falls out for free: a sustained shift in a node's link-RSSI profile drops the `conf` of stale proximity beliefs via `touched` decay, triggering re-embedding. The mesh notices it was rearranged.

  ✅ **NEW IN 0.3 — that detector can now be VALIDATED rather than asserted.** The
  Cardputer's accelerometer writes `@LAT95` `still|moving` windows, which makes "the
  observer held still" a **checkable claim instead of an assumption** — it is
  already load-bearing as gate 3 of the entity-drift baseline. So the RSSI-based
  movement detector has ground truth to be scored against on at least one node:
  run both over the same interval and report agreement, false-positive and
  false-negative rates. **An inferred detector with an available ground truth that
  nobody scored it against is an assertion**, and this document has now made that
  mistake once (§1.2's anchor).
  ⚠ The IMU is Cardputer-only, so this validates the *method* on one node rather
  than the *fleet's* movement detection — say which is claimed.

### Phase 5: Transport Auto-Switch (proof leg 2 — actuation)

*Goal: proximity beliefs drive the range-adaptive ladder without configuration.*

- Each node holds a per-peer transport choice derived from belief, not config:
  **ESP-NOW** if `dist_est_m + k·dist_sigma_m` is inside the calibrated ESP-NOW
  envelope *and* link percepts for that peer are fresh; otherwise **LoRa**
  (`USE_LORA` finally earns its Phase-4 bring-up — the SX1262 path on the V4s
  and the T-Deck).
- **Hysteresis is mandatory:** switch on `k·sigma` margins plus a freshness
  timeout, never on a single observation. A flapping link is worse than a slow
  one. Switch events are rare and logged.
- Each switch decision is itself a percept (*before:* chosen transport +
  expected delivery, *after:* delivery outcome), so the Dream Cycle audits
  whether the belief chose well — **the actuation loop feeds its own evidence.**
- Pass criterion: with one pair walked out of ESP-NOW range (T-Deck roaming, or
  V4-C fielded), traffic falls back to LoRa *before* ESP-NOW delivery dies and
  returns to ESP-NOW when back in range — with zero manual transport config.

### Phase 6: TTCP Rendering (proof leg 3 — the payoff render)

*Goal: the emergent map of network + node status, visible on two very
different screens from the same TTDB.*

- **Laptop:** the master TTDB (`reconcile` output + `@BELIEF:PROXIMITY` /
  `@BELIEF:POSITION` records) rendered in the browser per the TTCP RFCs
  (`RFCs/TTCP-RFC-0001..0003`: record rendering, knowledge globe + cursor
  navigation, toot URIs). The working example is
  **[antfriend.github.io](https://github.com/antfriend/antfriend.github.io)** —
  a dependency-free JS viewer that loads a TTDB via `?ttdb=<file>.md`; the
  companion's job is to keep emitting a master file that viewer can render, so
  the laptop leg is mostly *authoring discipline, not new renderer code*.
  Node status (last-seen, sync skew, transport in use, position `conf`/`sigma`)
  rides on each node's record; proximity beliefs render as typed edges.
- **T-Deck:** a native TTCP mini-renderer on the 320×240 (the console's fleet
  view grown up): the fleet globe drawn from the on-flash TTDB — nodes at
  their believed `@LATxLONy` with `sigma` circles, edges colored by transport
  (ESP-NOW / LoRa) and link health, trackball moves the cursor (TTCP-RFC-0002
  cursor semantics), keyboard keeps its CMD remote role. The T-Deck pulls
  belief updates over the mesh like any Dream-Cycle participant — the map it
  draws is the map it *carries*.
- 🎨 **TWO RENDER RULES, NORMATIVE, NEW IN 0.3.** Both are cases of the same
  principle — *if a view can show less than the whole truth, it must say so on
  screen* — which this fleet has already paid to learn twice.
  1. **A faded trace renders as faded, never as absent** (`TTDB-RFC-0010` §6.4).
     "Nobody has reinforced this for an hour" and "there is no such node" are
     different claims, and this fleet has already **fabricated** the second one
     once. A stale position belief dims; it does not vanish.
  2. **The pose renders its own ambiguity** (`default-network.md` §5). If no
     GPS-capable node has taken a fix, the shape is correct and the map is one of
     four — drawing it as a map is the same class of lie as rule 1. **Show the
     shape; show which of the four degrees of freedom are pinned, and by whom.**
     A globe that draws `pose_ceiling: 0` as a confident map fails Phase 6
     regardless of how good the shape underneath it is.

- Pass criterion: laptop and T-Deck render **the same fleet state from the
  same TTDB lineage**, and a physical rearrangement of the bench shows up on
  both screens within a stated number of Dream Cycles — **with `pose_ceiling` and
  trace decay visible on both.**

---

## 4. Validation Plan

1. **Ground truth: the T-Deck GPS is the verification instrument.** Walk the
   T-Deck to each static node and record a GPS fix beside it (plus tape measure
   for pairs under GPS resolution); the roaming T-Deck also continuously scores
   its *own* position belief against its live fix — an always-on residual for
   proof leg 1. (GPS is the *verifier*, never an input to the inference under
   test — keep the legs separate or the proof is circular.)
2. **Metrics:** pairwise distance error (%), embedded position error (m) after anchoring vs. GPS truth, flip-resolution correctness, time-to-converge after a node move, and transport-switch correctness (Phase 5 pass criterion).
3. **Ablation:** RSSI-only vs. RSSI+entity vs. RSSI+entity+BLE vs. all four sources — quantifies what the semantic layer adds over plain radio ranging. This comparison is the interesting result: it's the difference between "we did RSSI localization" and "umwelt overlap measurably improves spatial self-knowledge," which is the Locus-flavored claim — and it is the hypothesis's falsifier (§0).

   🛑 **AMENDED IN 0.3 — THE ABLATION HAS A PRECONDITION, AND RUNNING IT WITHOUT
   THAT PRECONDITION FALSIFIES THE HYPOTHESIS FOR THE WRONG REASON.** Per §0.3, two
   nodes metres apart show a cross-node Jaccard distance of **p50 0.250** against
   the same node's own ten-minute drift of **p90 0.222 / p95 0.250** — a margin of
   **~1.1x**, on n=11. At bench separation the tier's contribution is inside a
   factor of two of its own noise, so the ablation would be measuring the geometry
   rather than the tier.

   **Preconditions, all four required before an ablation result is admissible:**
   - **a stated separation** at which the nodes' entity sets measurably differ,
     established by measurement *before* the ablation runs — the entity tier's
     resolution is ~50–100 m (§1.1), so bench scale and probably garden scale are
     both inside its blind spot;
   - **a margin of ≥ 2.0x** of cross-node p50 over the still-node p90. Pre-registered
     here, before the geometry that will satisfy it exists. Below 2x, a difference
     cannot be attributed to distance rather than to the tier's own restlessness;
   - **the alphabet size stated** with the result (this bench: ~10 BSSIDs), exactly
     as an RSSI result must state its terrain;
   - **the right input for each half**, which is *not* the same input:
     **cross-node separation** may use a folded lane (each record still itemises its
     own window in `**ENTITY**`), but the **within-node floor** may not (the
     suppressed windows are gone, and the `**COVERED**` union is a different
     quantity). ⚠ Mixing the covered union into a cross-node set **halves the
     measured distance** — measured, not estimated (§0.3's correction box).

   ⚠ **A null result that does not meet all four is a statement about the test,
   not about the hypothesis, and must be recorded as such.**
4. **Stress test:** move V4-C 50 m and measure how many Dream Cycles until the map catches up — on both TTCP renders.

5. **🛑 EXPERIMENTS ARE NOT FREE TO REPEAT — NEW IN 0.3, AND IT CONSTRAINS EVERY
   ITEM ABOVE.** 0.2's validation plan tacitly assumed a run could be re-taken at
   will. Measured, it cannot:
   - **Prune markers.** A run needing a clean lane costs `@LAT100` boundary
     records, and there is **no prune path for `@LAT100` itself**. The Cardputer —
     the only node with an IMU, hence the only stillness witness — stands at
     **30/32**: two clean-lane experiments remain **for the life of that firmware**.
   - **Wall-clock.** An 8 h lane cap plus a ≥5.2 h gate floor means one usable
     measurement per night, and three of the first three attempts were lost or
     fragmented by resets.
   - **The witness lanes.** `@LAT90` caps at 16 and refuses when full; a fleet with
     every timeline witness full is a fleet whose failed runs **cannot be
     diagnosed**. Prune the witness before the run, not after.

   **Consequences for the plan:** state the pre-committed stop rule *before* each
   run; bank a failed run rather than re-timing it; and treat lane **compression**
   (§2.2) as the enabler of this validation plan rather than as an optimisation.

---

## 5. Future Directions (Summary)

📎 **Promoted out of this section in 0.3** (they are core now, not future): the
**mobile-node / SLAM-lite** mode, which became the T-Deck's anchoring role in Phase
2 once §1.2's circular anchor was retracted and the roaming GPS became the fleet's
*only* source of pose; and the **stigmergic/distributed** direction, which became
Phase 2b. `default-network.md` is the design note behind both.

**Denser evidence, same framework.**
- BLE scanning as a second entity class (tighter distance bounds than WiFi, ~10–30 m).
- Acoustic TDoA with better clock sync (μs-class sync via ESP-NOW timestamping is achievable) for meter-scale precision on impulsive events.
- LoRa time-of-flight ranging if future hardware supports it (SX1280-class 2.4 GHz parts do native ranging; a compelling V5-era upgrade).

**Richer spatial semantics.**
- From points to *regions*: represent each node's position as a probability field over the coordinate grid rather than a point + sigma — a natural fit for coordinate-addressed flat files (one weight per grid cell the node might occupy).
- Obstruction inference: persistent asymmetric RSSI between pairs implies intervening obstacles; the mesh sketches not just where nodes are, but what's *between* them. This is the beginning of a shared spatial umwelt — a map of the environment, not just the network.
- Mobile-node mode: a node carried on a walk becomes a measuring instrument, its moving link profile sharpening the positions of all static nodes it passes (SLAM-lite).

**Deeper Locus integration.**
- Position confidence as CHC input (RFC-0006): spatial uncertainty modulates which cognitive domain the agent selects — a lost node should prioritize orientation behaviors, an active-inference framing where positional uncertainty is expected free energy to be resolved by action.
- Narrative Metamorphosis tie-in: a node's progression from configured address → provisional self-estimate → high-confidence emergent address is a concrete instance of the larva-to-eclosion archetype; worth writing up as the RFC's running example.
- ARC relevance: the general pattern — *infer latent geometry from co-occurrence structure in percepts* — is exactly the class of relational inference ARC-AGI-3 interactive tasks reward. The mesh becomes a physical testbed for the abstract capability.

**Toward an RFC.**
- Once Phases 0–2 are validated, distill into TTDB-RFC-000x "Emergent Spatial Addressing": percept schemas, consolidation rules, embedding contract, flip-ambiguity semantics, and the auto-adopt vs. flag-for-operator address-revision policy. Conformance test: a simulated mesh with known geometry must recover positions within stated bounds.

---

## Appendix A: Effort & Risk Summary

*Revised in 0.3: statuses reflect what is on hardware, and two risk lines were
wrong — Phase 0's mitigation and Phase 2's scope.*

| Phase | Effort | Status | Primary risk | Mitigation |
|---|---|---|---|---|
| 0 Instrumentation | 1–2 wk | ✅ **on hardware** (RSSI, entity, motion, acoustic) | ~~Flash wear from percept volume~~ **retired by measurement** | 🛑 **was "aggressive pruning" — WRONG.** Pruning is a treadmill *and* spends a finite marker budget (§4.5). Correct mitigation: **change-triggered lanes with run-length** (§2.2), 6–48× lane life, lossless per consumer |
| 1 Pairwise distance | 1–2 wk | ✅ calibrated, consolidating | RSSI noise → bad estimates; **⚠ measured shadowing-limited outdoors (2–7× over-range)** | Median-of-top-quartile, calibration walk, sigma honesty; **non-amplitude tiers are the real answer** (Phase 3) |
| 2 Embedding | 2–3 wk | ✅ solver + first fleet self-map | ~~Flip ambiguity, single anchor~~ → **4 unpinned DoF, and 0.2's anchor was circular** (§1.2) | Dual-candidate beliefs generalised to per-DoF; T-Deck GPS is the **only** anchor; report `pose_ceiling` |
| **2b Distributed embedding** | 2–3 wk | 🆕 **new in 0.3**, unbuilt | Distributed relaxation oscillates where a central one converges | Mandatory damping + stated iteration budget; **abandonable without touching the primary proof** |
| 3 Env TDoA | 2–4 wk | 🔬 instrumented (`@LAT94`), consolidator unwritten | Clock sync precision; **⚠ the obvious clock is the wrong one** (§3 Phase 3) | Use the **pulse**, never the time stream; ~1.9 m measured floor; ⚠ **only one node has a mic** |
| 4 Address loop | 1 wk | unbuilt | Runaway self-revision | Conf threshold + operator flag mode default; **score the RSSI mover against `@LAT95` ground truth** |
| 5 Transport auto-switch | 1–2 wk | unbuilt (needs `USE_LORA`) | Link flapping | k·sigma hysteresis + freshness timeout; switch events logged |
| 6 TTCP rendering | 2–3 wk | ✅ T-Deck render live; laptop leg open | Two renderers drifting apart; **a confident map drawn from `pose_ceiling: 0`** | One TTDB lineage; the two normative render rules (Phase 6) |

## Appendix B: Calibration Procedure (Phase 1)

1. Place two V4 nodes at exactly 5 m, line of sight. Log 200+ frames each direction. Record median RSSI → this is `RSSI(d₀)` at `d₀ = 5 m`.
2. Repeat at 20 m, 50 m, 100 m in representative terrain (with the actual vegetation/obstructions of the deployment site, not a parking lot).
3. Fit `n` by least squares over the four points, per protocol (ESP-NOW and LoRa will differ; LoRa's `n` is typically lower and its usable range far longer).
4. Store as a `@BELIEF:CALIBRATION` node with `conf` reflecting fit quality; recalibrate seasonally (foliage matters).
