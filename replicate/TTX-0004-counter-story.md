# TTX-0004 — The Counter-Story Experiment

**Status:** Draft 02 — proposed
**Series:** Toot Toot Experiments (TTX)
**Depends on:** TTDB-RFC-0001 (file format), TTDB-RFC-0005 (TBEW / EPS), TTDB-RFC-0006
(umwelt frame, paired-percept primary datum), TTDB-RFC-0007 (Dream Cycle), TTDB-RFC-0008
(Narrative Metamorphosis), Draft 05 golden conformance store
**Formal half:** [RFCs/TTDB-RFC-0009-Counter-Story-and-Narrative-Morphospace.md](RFCs/TTDB-RFC-0009-Counter-Story-and-Narrative-Morphospace.md)
— the normative version of §3–§5 (definitions, MUST/SHOULD requirements, the metric
contract). This document is the discursive half: the chain of reasoning that produced it,
kept because the *reasoning* is what the RFC cannot carry.
**Open gap it touches:** `@LAT20LON3` (Learning from Action, in
[agent-memory-system_ttdb.md](agent-memory-system_ttdb.md))

> **Draft 02 changes.** The heterogeneous triad and the raw-material source moved from the
> **UNIHIKER K10** to the **M5Stack Cardputer ADV** (`0x300`): the K10 left the fleet on
> 2026-07-29 (v1 firmware, off the band roster, removed from the T-Deck's mesh map). This
> is not a like-for-like swap — the K10's contribution here was an *ambient thermometer*
> (AHT20) and the Cardputer has none. See §4.1 for what replaces it and why the experiment
> is better off. Cross-references were also reconciled to the `replicate/RFCs/` numbering
> (Dream Cycle = TTDB-RFC-0007, Narrative Metamorphosis = TTDB-RFC-0008).

---

## 0. Front matter

### 0.1 Plain-language preface

*No background required. Skip to §1 if you already know the framework.*

Some problems only need one smart thinker. Others cannot be solved by *any* single
thinker, no matter how smart — because the answer is not hidden in the thinking, it is
hidden in the gap between two different points of view. One ear cannot tell you where
a sound came from; two ears can. That is not a matter of trying harder.

This document explores what that means for groups. Groups turn out to do a few
recognizable jobs: keeping something steady (like body temperature), rebuilding
something back into its proper shape (like healing a wound), deciding where to put
effort, and remembering things longer than any one member lives.

The catch is that adding more members only helps if they are *different* from each
other. A hundred people watching the same news channel are not a hundred viewpoints —
they are one viewpoint that feels much more certain. The group's blind spot does not
shrink; it just becomes harder to notice.

The experiment described here tests that idea on a small network of homemade sensors.
Feed it a second opinion that *agrees*, and it should simply get more confident. Feed
it one that genuinely *disagrees* — coming from a different kind of sensor — and it
should discover things it did not know it did not know.

It also tests a stranger idea: that groups may store their sense of "what we are
supposed to look like" in the form of stories, and that a story's ending is what tells
a repair when to stop.

### 0.2 Purpose

This document records a line of reasoning about when a *collection* of intelligent
nodes can do something no single node can, follows that reasoning up the scale
ladder to society, and converts the one place where the reasoning **failed** into a
testable experiment for the mesh.

The failure is the interesting part. The rest is context for it.

---

## 1. The chain of reasoning

### 1.1 The dividing line is rank, not compute

A node can be arbitrarily intelligent and still be unable to compute a quantity that
is not present in its sensor stream at any level of processing.

**Single node suffices** when the answer is a transformation of one vantage point:
puzzle grids, route planning on a known map, proofs, classification. Adding nodes
here buys throughput, not capability — and can cost coherence, since a world model
split across a bandwidth-limited mesh *creates* fragmentation rather than resolving
it. (This is ARC-AGI-3 failure mode FM-1 in mesh clothing.)

**A collection is required** when the answer lives in the *relationship between*
observations:

| Class | Why one node cannot | Example |
|---|---|---|
| Geometric | Rank deficiency, not reasoning deficiency | TDoA, parallax, triangulation |
| Simultaneity | Cannot separate change-in-time from change-in-space | "warmer" vs. "a front moved east" |
| Self-calibration | Bias is invisible from inside the umwelt containing it | disagreeing peer as instrument |
| Continuity | Node dies, knowledge dies | corpus persistence |

### 1.2 The governing rule

> **More nodes only add capability when the nodes are different.**

N identical sensors co-located are one node with √N better confidence. The *volume*
of ignorance shrinks; its *shape* does not change. Only a node with a different
umwelt changes the topology of what can be unknown.

This is the operational reading of the Alexander duality framing: the shape of an
agent's ignorance is determined by the shape of its knowledge, so to change the
former you must change the latter's *form*, not its *quantity*.

**Standing test before adding any node:**
*Does this change what can be known, or only how confidently?*

### 1.3 Roles of collective intelligence, by state space

Thermoregulation and wound healing are the same role at different dimensionality.
Once seen that way, the taxonomy falls out of one question: **what space does the
setpoint live in?**

- **Scalar** — temperature, pH, hive humidity. Negative feedback, bidirectional effectors.
- **Pattern / morphospace** — healing, regeneration, development. Target is a
  high-dimensional configuration stored distributedly. *The stopping condition is the
  hard part, not the growing.*
- **Allocation** — foraging, task switching, immune recruitment, price discovery.
  Effort matched to yield across a space no member can survey.
- **Identity boundary** — self/non-self, continuously re-verified. Cancer is a cell
  reverting its boundary to the single-cell scale.
- **Commitment** — quorum sensing, bee house-hunting, neural decision. Distributed
  evidence collapsed to one irreversible choice; the quorum threshold is an explicit
  speed/accuracy dial.
- **Information across time** — genome, culture, institution. Setpoint is the
  persistence of a pattern past any node's lifespan.

### 1.4 Cross-cutting axes

**Scale nests.** Molecule → cell → tissue → organism → society. The same regulatory
logic recurs; what looks like an agent from above looks like a swarm from below.

**Timescales nest, and slower loops set the setpoints of faster ones.** Reflex (ms) →
homeostasis (min) → healing (days) → development (months) → culture (generations).
Healing is the slow loop telling individual cells which local gradient to chase.

**Coupling mechanism.** Stigmergic (via modified environment, no messaging) →
field/diffusive → discrete message-passing → mechanical. Stigmergy is cheapest and
scales furthest; message-passing is the only one that can address a specific peer.

### 1.5 The James criterion

**Same ends, variable means.** Block the normal route and see whether the target is
still reached by a novel path.

Planaria regenerate through pathways they have never used. A termite mound damaged
in an unprecedented way still gets ventilated. A thermostat has exactly one move.

> A collection that can reach its setpoint by only one route is a distributed
> **machine**, not a distributed **mind**.

### 1.6 Running the taxonomy against society

**Strong:** *Information across time* (writing, law, science — the most successful
setpoint-persistence machines ever built) and *allocation* (markets as ant-foraging
at larger radius).

**Weak:** the *identity boundary* is permanently contested rather than cheaply
verified, and is the source of most of society's violence.

**Distinctive:** society is the only collective whose nodes can model the collective
and argue about its target. Cells do not debate morphospace. This buys deliberate
redesign and costs Goodhart, self-fulfilling expectation, and the ability to entrench
a bad setpoint long past where feedback would have corrected a dumber collective.

**Timescale pathology:** the slow loops that set setpoints (culture, constitutions,
norms) have not accelerated; the fast loops (markets, media) have gone up orders of
magnitude. A slow loop that can no longer keep pace stops functioning as a setpoint
and becomes noise.

**The homogenization inference.** Society's characteristic modern failure is not too
few nodes or too little communication. Dense high-bandwidth coupling *homogenizes
umwelten*. N people converging on the same inputs behave as one node with √N
confidence: certainty rises, the shape of the ignorance is unchanged — and now
invisible, because it has been averaged. Hence the least-recognized societal role:
**preserving the conditions for heterogeneous observation**, which no member wants
(everyone would rather be agreed with) and no member can supply alone.

### 1.7 On accelerating setpoints

A target that moves at media speed is not a target, it is a price; a servo referenced
to a moving reference is an oscillator with extra steps.

**Setpoints should not accelerate. Error signals should.** Biology already does this:
healing is a slow morphogenetic target with fast local error signals. The gradient
updates in seconds; the target anatomy does not.

Corollary constraint on any divergence instrument: **it cannot be a dashboard.** A
scalar summary is simultaneously a Goodhart target and a homogenizing high-bandwidth
channel. Shape has dimensionality; collapsing it to one number destroys the quantity
being measured. The needed readout is the societal analogue of *residual EPS topology*
— which coordinates stay unresolved — not mean `conf`.

---

## 2. The correction (the reason this document exists)

The claim in §1.6 that society lacks a morphospace setpoint appears to be **wrong**,
and wrong in a way that matters for TTDB.

Kevin Ashton's *The Story of Stories* (2026) argues that narrative is not merely a
carrier of lessons but the thing that constituted us. Read structurally, that says:

> **A society's morphospace setpoint is stored as narrative.**
> A myth is a target shape encoded as a traversal order.

If true, society is not missing the pattern-regulation role — it stores that role in a
format not recognizable as a store when you go looking for a table of setpoints.

This is already the architecture of TTDB-RFC-0008. Scene-as-instar *is* a
morphogenetic sequence. It would be strange for narrative-as-morphospace to hold at
agent scale and not at collective scale.

Ashton's own arc lands on the homogenization problem historically rather than
structurally — firelight to smartphone glare, from few-telling-few to
everyone-telling-everyone — and his central warning is that story technologies have
become powerful enough to destroy *counter-stories*.

**Counter-stories are alternate routes.** Losing them is losing route plurality under
ablation, which by §1.5 is exactly the transition from mind to machine.

Where his prescription is weaker than the framework: he prescribes *critical
thinking*, a property of individual nodes. Asking every node to independently resist
a shared input stream is the √N situation with extra effort. Skepticism does not
change the shape of ignorance. **A different sensor does.**

---

## 3. Claims registered for falsification

| ID | Claim |
|---|---|
| C-1 | Coupling bandwidth raises `conf` faster than it changes the *identity* of the unresolved set. |
| C-2 | Intelligence = target reached by a route not designed for, after normal route ablation. |
| C-3 | A regenerating store without a stopping condition is a tumor, not a healing. |
| C-4 | **Morphospace targets are stored as traversal order (narrative), not as state tables.** |
| C-5 | **A counter-story changes ignorance topology; a corroborating story only raises `conf`.** |

C-1 through C-3 are covered by the existing experiment set (§4). C-4 and C-5 are new
and are the subject of TTX-0004.

---

## 4. Existing experiment set, and the rig it runs on

- **EXP-01 — Homogenization.** Identical-sensor triad (three Heltec V4s, same firmware,
  same modality set) vs. the heterogeneous Cardputer/Heltec-V4/T-Deck triad (§4.1),
  sweeping ESP-NOW sync interval. Measure *residual EPS topology*, not accuracy.
  Falsifier: homogeneous mesh's unresolved set changes composition as coupling rises.
- **EXP-02 — James Test.** Ablate a *sensor class* (not a node) mid-fix; see whether an
  equivalent-quality position is re-derived through an unused modality. On this fleet the
  classes are `acoustic` · `motion` · `entity` · `link` · `gnss` · `interoceptive` (§4.1).
  Ablate a class across the whole rig — pulling a *node* pulls several classes at once and
  confounds rank with reachability. Falsifier: recovery only via restoration or a pre-coded
  fallback.
- **EXP-03 — Planaria Test.** Excise a coherent region of the Draft 05 golden store,
  run consolidation. Two criteria: does it pass conformance again by a *different*
  path, and **does it stop**. Falsifier: confabulation, or unbounded growth.

Run order remains EXP-01 first: it establishes whether the mesh is heterogeneous
enough for the others to mean anything.

### 4.1 The heterogeneous triad, as the fleet actually stands

| Node | Distinctive modalities | Percept lanes | Absent — and that is the point |
|---|---|---|---|
| **Cardputer ADV** `0x300` | BMI270 accel **+ gyro** (tilt, shake, set-down); ES8311 MEMS mic, incl. the fleet-clock timestamp of the loudest transient | `@LAT95` motion, `@LAT94` acoustic, `@LAT96` entity, `@LAT97` link | no GPS, no LoRa, **no ambient thermometer** |
| **Heltec V4** (spine) | long-haul radio; ESP-NOW *and* LoRa link evidence from one node | `@LAT97` link, `@LAT96` entity | no mic, no IMU, no GPS |
| **LilyGo T-Deck** | u-blox GNSS — the fleet's only externally-referenced position | `@LAT97` link, `@LAT96` entity, GPS percept | no mic, no IMU |

All three also carry **interoception** (battery, die temperature, worst loop pass), which
is a fourth class and ablatable like any other.

**What the K10 used to supply, and what does not replace it.** The K10's contribution to
this rig was an AHT20 **ambient thermometer** — a real instrument pointed at the room. The
Cardputer's only thermal channel is `temperatureRead()`, the ESP32-S3 **die** temperature:
45–48 °C at idle, and as much a measure of how hard the radios are working as of the room.
That is an *interoceptive* signal and belongs beside battery voltage. Substituting it for
ambient temperature would inject a node-internal confound into exactly the comparison this
document exists to make, while looking like a faithful port of the original design — which
is why TTDB-RFC-0009 §5.5 states the prohibition normatively rather than as advice.

**Why the fleet is better off anyway.** C-5 needs a counter-story that genuinely disagrees.
Thermal-vs-outdoor-RSSI disagreement had to be manufactured. The current triad's
disagreement is a **standing field result**: amplitude ranging (RSSI, BLE) is
shadowing-limited outdoors and observed to decorrelate from true distance — the finding
that motivated the non-amplitude tiers in the first place (TTN-RFC-0011 §9; the 2026-07-10
and 2026-07-13 garden runs). The Cardputer's acoustic transient timestamp is a
*time-of-arrival* quantity; the spine's RSSI proximity is an *amplitude* quantity. They are
decorrelated as a matter of physics, not of rig construction, which is the difference
between an injection and a stunt.

---

## 5. TTX-0004 — The Counter-Story Experiment

**Tests:** C-4 and C-5.
**Prerequisite:** EXP-01 complete (heterogeneity established).
**Normative version:** [TTDB-RFC-0009](RFCs/TTDB-RFC-0009-Counter-Story-and-Narrative-Morphospace.md)
§5–§6. Where this section and the RFC differ in detail, the RFC governs; it carries the
MUST/SHOULD requirements (equal toot-bits, the fixed-before-the-run EPS threshold `θ`, the
separate-sessions rule, and the ban on reporting a scalar as the headline).

### 5.1 Hypotheses

- **H1 (narrative morphospace).** A store whose target region is encoded as an
  ordered traversal (scene-as-instar, TTDB-RFC-0008) regenerates that region after excision
  more correctly and with less overshoot than a store encoding the same content as
  unordered assertions with equivalent total toot-bits.
- **H2 (counter-story asymmetry).** Injecting a *divergent-umwelt* account of the same
  events changes the composition of the residual high-EPS set. Injecting a
  *corroborating* account of equal size raises mean `conf` and leaves composition
  unchanged.

H2 is the mesh-scale statement of the whole societal argument, which is why it is
worth running even though H1 is the more tractable one.

### 5.2 Construction

Build two isomorphic stores over identical subject matter. A **Cardputer
acoustic + motion session run alongside a Heltec V4 outdoor RSSI/entity session** is a
good source, because it produces genuinely heterogeneous raw material — a
time-of-arrival account and an amplitude account of the same events (§4.1).

- **Store N (narrative).** Content laid out as a sequence with explicit ordering
  edges. Each stage's precondition is the prior stage's post-state. Paired
  `@PERCEPT:before` / `@PERCEPT:after` used as the primary datum throughout.
- **Store A (assertional).** Same facts, same TBEW fields, same total toot-bit count,
  no ordering edges. Typed edges permitted but acyclic-order information removed.

Equalize toot-bits, not node count. Ordering edges are content; that is the point of
the comparison, so the budget must be matched on the shared substrate.

### 5.3 Procedure

**Phase 1 — Regeneration (H1).**
Excise a coherent region from each store. Run the Dream Cycle (Replay → Projection)
with no backup reachable by the agent. Repeat across ≥5 excision sites per store to
avoid single-site luck.

**Phase 2 — Injection (H2).**
Restore both stores. Then, in separate runs:
- **2a. Corroborating injection** — an account from a *duplicate* sensor modality: a
  **second V4's RSSI** account of the same session. Same sensor class, different node.
- **2b. Counter-story injection** — an account from a *different* modality that
  disagrees on at least one derived belief, matched to 2a in toot-bits: the **Cardputer's
  `@LAT94` acoustic transient timestamp** against the spine's **`@LAT97` RSSI proximity**,
  disagreeing on a derived proximity belief.

Consolidate. Compare residual EPS sets before and after each injection.

2a and 2b must be *separate sessions*. Combined, nothing can attribute a topology change
to the divergent account, which is the only thing the experiment is for.

### 5.4 Metrics

**For H1:**
- *Conformance pass rate* after regeneration.
- *Path divergence* — fraction of regenerated nodes whose derivation edges differ from
  the originals. Byte-identical restoration is a backup, not regeneration; low
  divergence is a **negative** result.
- *Overshoot* — nodes synthesized beyond the excised region. The stopping condition
  is the finding.
- *Halt latency* — consolidation cycles until no new nodes are proposed. Failure to
  halt is reported as `∞`, not as a large number.

**For H2:**
- Δ mean `conf` across the store.
- **Jaccard distance between the residual high-EPS coordinate sets, pre- and
  post-injection.** This is the primary metric of the whole document. It is the mesh
  instrument corresponding to the societal thing that must not be a dashboard. The
  high-EPS threshold `θ` is fixed *before* the run and reported with the result — a `θ`
  chosen after seeing the sets is a free parameter fitted to the hypothesis.
- Count of coordinates *newly* high-EPS — ignorance the store did not previously know
  it had.

### 5.5 Predictions (registered in advance)

1. Store N halts; Store A either under-regenerates or fails to halt. Traversal order
   carries the stopping condition — the ending is where the target shape is stored.
2. Corroborating injection: Δ`conf` positive, Jaccard distance ≈ 0.
3. Counter-story injection: Δ`conf` near zero or *negative*, Jaccard distance well
   above 0, and non-empty newly-high-EPS set.

Prediction 3 is the load-bearing one. A useful contribution that **lowers** average
confidence while revealing new unknowns is the operational signature of a node that
changed the shape of ignorance rather than its volume.

### 5.6 Falsifiers

- **C-4 fails** if Store A regenerates and halts as well as Store N at matched
  toot-bits. Narrative would then be a presentation convenience, not a storage format
  for target shape.
- **C-5 fails** if the corroborating injection also moves the Jaccard distance, or if
  the counter-story does not. Either result collapses the distinction the entire
  societal argument rests on, and §1.6 should be retracted rather than patched.

### 5.7 Why this one touches `@LAT20LON3`

Regeneration is not a query. Choosing an excision-repair path, committing to it, and
deciding to stop are all *actions*, and the store currently has no way to learn from
having taken them. EXP-03 brushes this gap; TTX-0004 sits on it, because Phase 1
requires a halt decision and Phase 2 requires committing to a revision the store's
own prior beliefs contradict.

Expect the experiment to be partly blocked by the gap. That is diagnostic
information about the gap, and worth logging as such rather than engineering around.

### 5.8 Coordinate allocation

`@LAT/LON` assignments for TTX-0004 nodes are **to be assigned** against the live
Draft 05 store; this document deliberately does not squat coordinates it has not
checked. Suggested namespaces on allocation (the required fields per namespace are
tabulated in [TTDB-RFC-0009](RFCs/TTDB-RFC-0009-Counter-Story-and-Narrative-Morphospace.md)
§7):

- `@EXPERIMENT:ttx0004:*` — rig configuration and run metadata
- `@PERCEPT:before` / `@PERCEPT:after` — per §5.2, primary datum in both stores
- `@BELIEF:*` — Dream Cycle output; tag regenerated beliefs distinctly from original

---

## 6. What is not technical

Whose divergence, and who authors the setpoint, is the identity-boundary problem plus
legitimacy. At mesh scale it is a configuration choice made by the operator. At
societal scale it is a political position, and any implementation that presents it as
an engineering choice is concealing the substantive claim inside it.

The structure of the problem is analyzable. The answer is not, and the document
should not imply otherwise.

---

## 7. Standing criteria (keep these on one card)

1. **Adding a node:** does this change what can be known, or only how confidently?
2. **Mind vs. machine:** is the target reachable by a route not designed for, after
   ablation of the normal one?
3. **Healing vs. tumor:** does it stop?
4. **Instrument design:** does the readout preserve shape, or collapse it to a scalar?

---

## 8. References

- Ashton, K. (2026). *The Story of Stories: The Million-Year History of a Uniquely
  Human Art.* — narrative as constitutive; counter-stories as the thing at risk.
- Levin, M. — bioelectric morphospace storage; multiscale competency architecture.
- Friston, K. (2010). — active inference; precision-weighting ↔ TBEW.
- von Uexküll, J. — umwelt; the frame for §1.2.
- James, W. — same ends by variable means; §1.5.
- TTDB-RFC-0001 (file format), -0005 (TBEW/EPS), -0006 (umwelt frame), -0007 (Dream
  Cycle), -0008 (Narrative Metamorphosis); TTN-RFC-0011 (Semantic Positioning — the
  field results that make §4.1's counter-story available);
  [agent-memory-system_ttdb.md](agent-memory-system_ttdb.md) — the Draft 05 golden
  conformance store, whose `@LAT20LON5` carries C-4 and C-5 in compressed form.
- [TTDB-RFC-0009](RFCs/TTDB-RFC-0009-Counter-Story-and-Narrative-Morphospace.md) — the
  normative half of this document.

---

*Draft 02. Predictions in §5.5 are registered before running; amend by appending a
results section rather than by editing them. Nothing here has been run on hardware, and
the EXP-01 gate (§4) is itself unrun — so no §5 result is admissible yet.*
