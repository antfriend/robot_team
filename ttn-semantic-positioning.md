# TTN Semantic Positioning

**Inferring Relative Physical Position of ESP32 Nodes from TTDB Semantic Relationships**

*Draft 0.2 — Toot Toot Engineering — July 2026*

**Status: PRIMARY HYPOTHESIS of robot_team (adopted 2026-07-07).** This is the
claim the fleet now exists to prove. The build order is PLAN.md **Act II**;
companion.md §6 tracks its live state. Everything verified so far — toots,
HMAC, sync, Dream Cycle, pulse — is the floor this proof stands on.

---

## 0. The Hypothesis — and the three proofs

> **A mesh of ESP32 nodes can infer its own physical arrangement from the
> semantic structure of what it perceives** — umwelt overlap implies spatial
> proximity — **accurately enough to be useful.**

"Useful" is pinned to three concrete, falsifiable proof legs:

1. **Verified.** Position beliefs land within their own stated `sigma` of
   ground truth, measured against the **T-Deck's GPS** used as a roaming
   verification instrument (§4). The map must be *honest*, not just pretty.
2. **Actuated.** The inferred pairwise proximity **drives the transport ladder
   automatically**: each node pair selects **ESP-NOW when the belief says
   in-range and falls back to LoRa when it doesn't**, with hysteresis, without
   configuration (§3, Phase 5). Position belief becomes behavior.
3. **Rendered.** The emergent map is *visible* as **TTCP** — network + node
   status drawn from the master TTDB on the **laptop** (browser viewer, the
   [antfriend.github.io](https://github.com/antfriend/antfriend.github.io)
   pattern) and natively on the **T-Deck's 320×240 screen** (§3, Phase 6).
   The fleet draws a live map of itself.

**Falsifier:** the ablation study (§4.3) compares RSSI-only against
RSSI+semantic evidence (entity co-occurrence, BLE near-range, environmental
TDoA). If the semantic layer adds nothing over plain radio ranging, the
hypothesis fails, and this document records why.

---

## 1. The Basic Idea

TTDB normally runs in one direction: physical position (`@LATxLONy` coordinate addressing) organizes knowledge. Semantic positioning inverts this. Nodes infer their physical arrangement *from* the structure of what they know.

The governing principle is **umwelt overlap implies spatial proximity**. Each node's umwelt — the slice of the world it can perceive — is bounded by radio range, sensor reach, and environmental exposure. Two nodes whose percept streams reference the same external entities, at correlated times, with correlated intensities, must occupy overlapping regions of physical space. The degree and character of that overlap is a distance measurement in disguise.

This makes position an *emergent belief* rather than a configured constant. A node's coordinate address becomes an epistemically weighted claim, subject to the same `conf` / `sal` / `rev` / `touched` machinery (TBEW, RFC-0005) as any other node in the graph, consolidated by the Dream Cycle (RFC-0002), and revisable when evidence changes — for example, when a node is physically moved.

### 1.1 Signal Sources

Three families of evidence, all naturally representable as paired `@PERCEPT:before` / `@PERCEPT:after` nodes:

1. **Link-layer percepts.** Every received ESP-NOW or LoRa frame carries RSSI and SNR. Each reception is a percept: *before* = expected link quality (prior belief about the pairwise link), *after* = observed value. RSSI-to-distance conversion is noisy (±3–6 dB swings from multipath, foliage, humidity), but noise is exactly what epistemic weighting handles: individual observations carry low `conf`; consolidated pairwise estimates gain `conf` with sample count and consistency.

2. **Shared-entity co-occurrence.** Nodes log sightings of external entities: WiFi SSIDs/BSSIDs, BLE advertisement MACs, acoustic events, recognized RF beacons. The Jaccard overlap of two nodes' entity sets is a coarse proximity measure. Shared visible WiFi APs alone typically bound two observers to within ~50–100 m of each other; BLE overlap bounds tighter (~10–30 m).

3. **Environmental gradient timing.** Spatially propagating transients — rain fronts, temperature drops, sunrise/sunset light curves, pressure waves — arrive at different nodes at different times. Time-difference-of-arrival between correlated environmental percepts yields directional constraints. Solar charge curves (V4-B) additionally encode shading geometry and panel orientation at zero sensor cost.

4. **BLE near-range approximation.** Every board carries BLE 5.0. Nodes advertise and scan: inter-node BLE advertisement visibility (and its RSSI) bounds a pair to roughly 10–30 m — a short-range proximity tier that tightens `dist_sigma_m` exactly where ESP-NOW RSSI is least informative (near-field flattening: past a few meters of separation, strong ESP-NOW RSSI barely changes). Same percept schema as link observations, `proto: ble`. BLE is an *approximation tool*, never a transport: it contributes evidence, not toots.

### 1.2 Synthesis

Pairwise evidence is fused into a single affinity/distance matrix and embedded into 2D via anchor-free localization (MDS-MAP or spring relaxation). Nodes with authoritative known positions (the bridge/head, V4-A) act as anchors that pin the relative map to absolute `@LATxLONy` coordinates. For meshes of 3–20 nodes this is comfortably within ESP32 compute budgets, or can be delegated to the head node / attached host.

### 1.3 Known Limitation: Flip Ambiguity

Three nodes determine a triangle only up to reflection. Disambiguation requires one of: a fourth node, a second anchor with known coordinates, or a declared directional constraint (e.g., "V4-C is east of V4-B"). The system should represent an unresolved flip as *two candidate embeddings with split confidence* rather than silently choosing one.

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
lat: 43.64312
lon: -116.28067
sigma_m: 45
anchor_chain: [V4-A]
embedding_rev: 9
flip_resolved: true
conf: 0.71
rev: 9
```

### 2.2 Key Design Decision

Raw link percepts are **write-heavy, short-lived**. They exist to feed consolidation, then are pruned (or downsampled to periodic summaries) to respect flash wear and flat-file scale on ESP32-class storage. The durable graph objects are the consolidated `@BELIEF:PROXIMITY` and `@BELIEF:POSITION` nodes. This matches the existing Dream Cycle philosophy: experience is cheap, consolidated belief is the asset.

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
- **Anchoring:** translate/rotate the relative embedding so V4-A lands on its known `@LATxLONy`. With one anchor, orientation remains free — resolve with a declared bearing constraint or a second anchor. **The T-Deck is the second anchor:** its GPS gives it an authoritative position wherever it happens to be, and because it *roams*, it is effectively many anchors over time — each GPS-stamped position it visits pins the relative embedding a little harder and breaks flip ambiguity statistically (the mobile-node/SLAM-lite mode of §5, promoted to a core role).
- **Flip handling:** evaluate stress for both mirror images; if within noise of each other, emit both candidates with split `conf` and mark `flip_resolved: false`.
- Run on the head node (V4-A) or attached host; publish resulting position beliefs back over the mesh so each node stores its own.

*Deliverable:* a self-drawn map of the three-node spine, honest about its uncertainty.

### Phase 3: Environmental TDoA (2–4 weeks, parallelizable)

*Goal: directional constraints from shared transients.*

- Onset detection per sensor channel: CUSUM or simple derivative-threshold on temperature, light, pressure. Log `@PERCEPT:ENV` with onset timestamp.
- **Clock sync is the hard part.** ESP-NOW round-trip timestamp exchange gets nodes to ~1 ms agreement, sufficient for slow fronts (weather: minutes across hundreds of meters) but not acoustic events. Start with slow signals only.
- Cross-correlate onset times across nodes for the same detected event class within a window; each match yields a "B preceded C by Δt" constraint. Accumulate these as directional priors that (a) break flip ambiguity statistically and (b) add gradient-direction information the distance matrix lacks.
- Solar node bonus: V4-B's charge-current curve shape vs. clear-sky model encodes shading azimuth — a free compass-like hint.

### Phase 4: Closing the Loop (1 week)

*Goal: position as living belief.*

- Node self-address update: when `@BELIEF:POSITION` `conf` exceeds a threshold and disagrees with the node's configured `@LATxLONy` beyond `sigma`, raise a revision event. Policy choice per deployment: auto-adopt (fully emergent addressing) or flag-for-operator (conservative).
- Movement detection falls out for free: a sustained shift in a node's link-RSSI profile drops the `conf` of stale proximity beliefs via `touched` decay, triggering re-embedding. The mesh notices it was rearranged.

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
- Pass criterion: laptop and T-Deck render **the same fleet state from the
  same TTDB lineage**, and a physical rearrangement of the bench shows up on
  both screens within a stated number of Dream Cycles.

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
4. **Stress test:** move V4-C 50 m and measure how many Dream Cycles until the map catches up — on both TTCP renders.

---

## 5. Future Directions (Summary)

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

| Phase | Effort | Primary risk | Mitigation |
|---|---|---|---|
| 0 Instrumentation | 1–2 wk | Flash wear from percept volume | RAM buffering, batched writes, aggressive pruning |
| 1 Pairwise distance | 1–2 wk | RSSI noise → bad estimates | Median-of-top-quartile, calibration walk, sigma honesty |
| 2 Embedding | 2–3 wk | Flip ambiguity, single anchor | Dual-candidate beliefs, T-Deck GPS roaming anchor |
| 3 Env TDoA | 2–4 wk | Clock sync precision | Slow signals first; μs sync deferred |
| 4 Address loop | 1 wk | Runaway self-revision | Conf threshold + operator flag mode default |
| 5 Transport auto-switch | 1–2 wk | Link flapping | k·sigma hysteresis + freshness timeout; switch events logged |
| 6 TTCP rendering | 2–3 wk | Two renderers drifting apart | One TTDB lineage; laptop leg reuses the existing viewer (authoring, not renderer code) |

## Appendix B: Calibration Procedure (Phase 1)

1. Place two V4 nodes at exactly 5 m, line of sight. Log 200+ frames each direction. Record median RSSI → this is `RSSI(d₀)` at `d₀ = 5 m`.
2. Repeat at 20 m, 50 m, 100 m in representative terrain (with the actual vegetation/obstructions of the deployment site, not a parking lot).
3. Fit `n` by least squares over the four points, per protocol (ESP-NOW and LoRa will differ; LoRa's `n` is typically lower and its usable range far longer).
4. Store as a `@BELIEF:CALIBRATION` node with `conf` reflecting fit quality; recalibrate seasonally (foliage matters).
