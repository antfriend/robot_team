# Stigmergy in robot_team

*Design exploration — 2026-08-07. NOT adopted, NOT in PLAN.md, NOT state.*
*companion.md remains the source of truth for what is actually true of the fleet;
nothing here has been built or measured. Read §5 before §3: the discipline rule is
what makes the rest safe.*

---

## 1. The concept, stated precisely

Grassé coined **stigmergy** in 1959 to explain how blind termites build an arch with no
plan, no foreman, and no termite ever addressing another. A termite drops a pellet; the
pellet raises the local probability that the next termite drops one there; the growing
column is both the record of past work and the instruction for the next act. Grassé's
point was not "self-organisation" in general — it was specifically that **the
coordination lives in the medium, not in the agents or in messages between them.**

Three properties, all of which must hold or it is not stigmergy:

1. **The trace persists in a medium both agents can reach.** Not a message: a deposit.
2. **The trace itself selects the next action.** An agent reads its local environment and
   acts; it does not receive an instruction naming it.
3. **No agent addresses another.** Remove any agent and the medium still says what it
   said. Add one with no history and it can still participate.

Two families, worth keeping distinct because they suggest different features here:

- **Marker-based** (*sign-based*): the deposit is a dedicated signal — an ant's
  trail pheromone. It carries no function except to be read. Requires **decay**, or the
  field saturates and stops discriminating.
- **Sematectonic**: the *work itself* is the cue — the half-built wall, the partially
  eaten leaf. No dedicated signal at all; the state of the artefact is the message.

⚠ **Decay is not housekeeping — it is the computation.** An ant trail without
evaporation is a map of everywhere any ant has ever been, which is worthless. Evaporation
is what turns an accumulating log into a *gradient*, and the gradient is what encodes
recency, intensity, and consensus in a single scalar an agent can read locally. Any
proposal below that drops decay is not a stigmergy proposal; it is a logging proposal.

---

## 2. Why this project is an unusually good host for it

Most attempts to add stigmergy to a distributed system have to invent the medium. This
one already has it, in three separate pieces that were built for other reasons:

- **`@LATxLONy` makes a record "a value at a place."** A pheromone field *is* a scalar
  over coordinates. Every other system has to bolt spatial indexing onto its store; TTDB
  is addressed that way natively, so a trail lane is an ordinary TTDB citizen rather than
  a new subsystem.
- **HELLO is a working, proven deposit channel.** Every node beacons every 2 s;
  `timestream::ANCHOR_LEN` uses **21 of the 250-byte frame**, and an un-reflashed node
  sends 0 bytes and is a *non-participant rather than a parse error* (CLAUDE.md). That
  backward-compatible-by-construction property is exactly what a stigmergic field needs,
  and it is already demonstrated on six sketches.
- **`umwelt` is already the project's vocabulary.** Semantic positioning's governing
  principle is *umwelt overlap implies spatial proximity*. Stigmergy is what you get when
  overlapping umwelten share a medium that can be **written** as well as read. The
  hypothesis and this concept are two halves of one idea, and §3.C exploits that.

And the fleet has **already done stigmergy twice without naming it**, which is the best
evidence that the shape fits:

| Stigmergic element | Where it already exists | What's missing |
|---|---|---|
| Reinforcement of a trace | `@LAT95`/`@LAT92` run-length: `windows:9` is literally "this happened nine more times" instead of nine deposits | **decay** — the run only ever grows |
| A scalar field over records | `EPS = sal × (255−conf)/255` (TBEW, RFC-0005) | it is read on the **laptop**, and actuates nothing on-node |
| Fleet-owned medium surviving agent loss | the team time stream — `stream:`/`wall:`, anchors on HELLO, *older stream wins* | it carries **one** quantity (time) |
| Trace that instructs the next act | `@LAT100` boundaries, `@LAT90` REMAP | they instruct a **reader**, not an agent |

⚠ The time stream is worth studying as the template for anything below, because it got
the hard part right: **`mono()` is mutated only from `service()`, never from the recv
callback** (a torn write moves the clock seven weeks). Any field updated from radio
receptions inherits that constraint exactly.

---

## 3. The one place the project is fighting the concept

**Lane caps are cap-and-wipe. Stigmergy is decay-and-reinforce. These are not variants of
each other — they are opposites, and the project is currently paying for the wrong one.**

The pattern today: a lane fills to its cap (`ENTITYPERCEPT_MAX_LANE 48`,
`PERCEPTLEARN_MAX_LANE 24`, `TIMESTREAM_MAX_LANE 16`), the node **goes blind**, an
operator prunes the whole lane, a `@LAT100` boundary is written so the ordinal citations
stay honest, and the lane refills. companion.md's own verdict: *"pruning is a treadmill
until the lane is change-triggered."*

Run-length made the treadmill 10× slower (48 min → 24 h on `@LAT95`) and it did so by
adding **reinforcement**. It did not add decay, so the treadmill still exists — and as of
2026-08-07 it has a hard stop: **the Cardputer's `@LAT100` is at 28/32, `LANEGEN_MAX_LANE`
is 32, and there is no prune path for `@LAT100`.** One 4-lane prune remains, ever.
`LaneGenNode.h` refuses correctly and loudly at the cap rather than clearing silently —
but the refusal arrives as *a node that can no longer sense*.

A decaying field has no cap, no prune, no boundary, and no exhaustible budget. The trace
that stops being reinforced fades and its space returns. That is not a nicety; on this
fleet it is the difference between "one more measurement run" and "arbitrarily many."

⚠ **But evaporation collides head-on with the lesson `@LAT100` exists to record.** A
citation here is an **ordinal** (`derived_from@LAT97LON1`), so reclaiming slot LON1 for a
new deposit re-points every existing citation at a different record — *a live pointer to
the wrong thing, which is worse than a dangling one*. **Decay therefore requires stable
naming: content-addressed or serial ids, not lane positions.** That is the real price of
this section, it is not small, and it should be priced before anything in §4 is built.
The honest framing: `@LAT100` is the cost of pruning *ordinal-addressed* storage, and
stigmergy asks the project to change the addressing rather than keep buying boundaries.

---

## 4. Applications, ranked by (value × buildability)

### A. Transport selection as a pheromone trail — proof leg 2, without the inference chain
**Strongest fit; recommended first.**

Proof leg 2 is *"inferred pairwise proximity drives the transport ladder: ESP-NOW when the
belief says in-range, LoRa when it doesn't."* As specified, that is a five-link inference
chain: RSSI → distance → position → range → protocol. The fleet has **measured the first
link to be broken outdoors** — RSSI proximity ran 2–7× over-range and *decorrelated from
distance*, and through-house calibration did not transfer.

Ant-colony routing solves protocol/route selection with no ranging at all. Per
`(peer, proto)` keep a trail scalar: **reinforced by each delivery that is actually
confirmed, evaporating on a fixed half-life**, choose `argmax` with a small exploration
probability so a recovered link can be rediscovered.

- **Why it is better here than a threshold:** a trail measures *what got through*, which
  is the quantity proof leg 2 actually cares about. It needs **no constant that has to
  transfer between nights** — which is precisely where Part 2 is currently stuck (p50
  0.143 one night, 0.300 another, same node, same room).
- **It is nearly built.** `@LAT91` LINK-STABLE already holds one belief per
  `(peer, proto)`, and `@LAT92` already tallies `met`/`violated`/`streak`. The missing
  element is decay — and `Reconciler` is a **pure function of `@LAT92`**, so a
  half-life is a change to *how the fold weights old records*, not new storage.
- **Exercisable today without Phase 4.** `USE_LORA` is gated, but `PROTO_BLE` already
  exists in `LinkPercept`/`BleLink` — two protocols is enough to have a choice.
  ⚠ BleLink was built 2026-07-10 and **has never been flashed**; that is the first cost.
- **Falsifier:** if the trail's protocol choice matches "pick the one with better RSSI"
  on every pair, it added nothing. Say so before running it.
- ⚠ **Confirmation must not be an ACK-shaped lie.** `--op play` and a prune on a grown
  TTDB both no-ACK while succeeding ([[band-play-ack-false-negative]]); reinforcing on
  ACK alone would evaporate the trail of a link that works.

### B. Evaporating percept lanes — retire the prune treadmill
**Highest value, blocked on §3's naming problem. Do not start it before pricing that.**

Give each deposit a strength that decays with elapsed stream time and is reinforced by
re-observation; reclaim the weakest slot instead of wiping the lane. Consequences: no
prune CMD, no `@LAT100` spend, no operator in the loop, and a lane that holds *what is
currently true of the environment* rather than *the last 48 things that happened*.

⚠ **Measurement lanes must stay append-only regardless.** `entity-drift`'s gates need
`t_ms` monotonic over a contiguous single-stream run and ≥30 surviving pairs. **A decaying
field is not a sample** — you cannot compute a distribution over records that removed
themselves according to a rule correlated with the thing being measured. See §5.

### C. Stigmergic positioning — the map relaxes itself, laptop-absent
**The most interesting scientifically; medium cost.**

Today the embedding is computed centrally (`companion.py positions` → MDS/spring
relaxation on the laptop). The stigmergic version: each node keeps its own `(x, y, σ)`,
broadcasts it in the spare HELLO bytes, and on each beacon applies **one relaxation step**
— pull toward peers with high umwelt overlap, push from peers with none. No node computes
the map; the map is the fixed point of every node nudging itself. V4-A pins the frame as
the anchor (§1.2 already names it).

- Fits the value the time stream already established: **the fleet keeps working when the
  laptop is absent.** Position becomes fleet-owned like time is.
- ⚠ Inherits §1.3's **flip ambiguity**, and a distributed relaxation can oscillate where a
  central one converges — needs damping and a stated iteration budget.
- 🔬 **The comparison is the experiment:** does the in-field fixed point agree with the
  laptop's embedding? Disagreement is a *result*, not a bug — it says the central
  estimator is using information the field cannot see (or vice versa). Both are checkable
  against the T-Deck GPS, so proof leg 1 arbitrates.

### D. The sensing schedule as an attention field — EPS becomes an actuator
**Cheap; immediately useful; must be gated during measurement.**

`EPS = sal × (255−conf)/255` is already the project's "what deserves attention next," and
it is already computed — on the laptop, as a reading aid. On-node it can drive **when to
sense**: a node whose entity beliefs are confident and fresh scans less often; one whose
beliefs are contested or stale scans more. Publish one byte of "curiosity" on HELLO and a
confident neighbour can answer a curious one with a deposit, which is the cheapest
possible form of mutual aid in a stigmergic field.

⚠ **Hard interlock: this must be OFF during a baseline run.** `WIFI_SCAN_PERIOD_MS` is
600 000 and companion.md is explicit that *the quantity is churn over the interval the
tier actually uses* — a threshold measured at one spacing does not apply to a tier that
adapts its spacing. An adaptive duty cycle silently invalidates the Part 2 baseline. If D
is built, the measurement runbook needs a "fixed cadence" mode and the record needs to say
which mode produced it.

### E. Sematectonic music — a score that is grown, not authored
**Creative; genuinely cheap; and it doubles as an instrument panel.**

`HeroArc.h` is an authored six-scene song. The stigmergic counterpart: **the fleet's
sensing writes the score.** Each percept event deposits a note into a step slot of a
shared 16-step phrase; notes decay unless re-struck; the loop you hear is the fleet's
recent experience. Room WiFi churn becomes a bassline; a link going marginal becomes a
motif that thins out.

- `score::Phrase` is already *a sparse note list over a step grid* — exactly a decaying
  deposit field. Making it mutable is a smaller change than adding a scene.
- The pulse already solves the hard problem: every node agrees on the step grid, and the
  chart survives conductor handoff.
- 🔊 **The practical payoff is an ambient network monitor.** You can hear the mesh's state
  across a room with no screen and no operator reading anything — the fleet's condition
  rendered as sound is a real TTCP render, in the project's own sense: transmit the
  numbers, let the receiver voice them on the instrument it has.
- ⚠ `score::noteAt` is an **exact step match** and a duet's `speed` divides the grid, so a
  deposit landing between slots is silently dropped. Quantise on deposit, not on playback.
- ⚠ On the V4s this needs `huge_app` first (94%, ~74.5 KB left). Cardputer 41% and T-Deck
  40% have room; the two handhelds are the natural home.

### F. The operator as a stigmergic agent — deposits, not commands
**Small, and it fixes something that just cost a measurement.**

Every `companion.py cmd` is an *addressed instruction* — the opposite of a deposit. A
handheld key that writes a **mark** into the field instead ("measurement in progress",
"this node is where I left it") makes the human a participant rather than a foreman.

The concrete win: the stillness a baseline assumes is currently asserted **out-of-band by
the operator** and only checked after the fact by `@LAT95`. A *"do not disturb"* deposit
that every node reads would let the fleet suppress heavy flash work for the window —
prunes, pulls, FS writes — which is exactly the class of event that produced a **10 234 ms
worst loop pass** on the Cardputer this morning and that wrecked two overnight runs by
other means.

### G. Inhibitory traces — an anti-pheromone for the prune loop
**Trivially cheap; protects the last `@LAT100` slot.**

`LaneGenNode.h`'s refusal message is *"Something is pruning in a loop; go and look."*
Inhibition is the textbook stigmergic answer: a recent-prune trace that suppresses the
next prune for a cooldown. Nature uses repellent pheromones for exactly this (foraging
ants mark unproductive paths). Given that the Cardputer has **one prune left, ever**, a
trace that refuses a redundant one is cheap insurance.

---

## 5. The discipline rule — where stigmergy is the WRONG tool here

> **Stigmergic fields for control. Append-only lanes for evidence. Never derive a
> threshold from a field that removed its own data.**

This project's most expensive lessons are all about *not silently rewriting history*:
`@LAT90` REMAP so a superseded timeline stays interpretable; `@LAT100` boundaries so a
prune cannot re-point a citation in silence; `@LAT92`'s boundary carrying
`**OUTCOMES-CARRIED**` and `**BELIEF-AT-BOUNDARY**` so emptying a tally does not erase its
conclusions; a `stream:0x00000000` that means *"comparable with nothing but this node's own
records"* rather than a fabricated id.

**A decaying medium silently rewrites history. That is its function.** So:

- **Never** put evidence in a field. `entity-drift`'s four gates — one stream, `t_ms`
  monotonic, `@LAT95` stillness on the same timeline, ≥30 pairs surviving the spacing
  filter — are unprovable over data that evaporated. The gates were written before the
  data existed, which is the only order in which a gate means anything; a field would make
  gate 2 and gate 4 meaningless.
- **Never** let a field feed a `derived_from` edge. An edge must resolve to a record that
  exists (the rule run-length already established: `+k` offsets are for *windows*, edges
  stay plain ordinals).
- **Reproducibility is the tell.** `Reconciler` is a pure function of `@LAT92` — any party
  reading the same records reaches the same number. A field is a function of *arrival
  order and wall time*, so it is reproducible only if you also log the deposits. If you
  find yourself logging the deposits to make the field auditable, you have built an
  append-only lane with extra steps: choose one on purpose.
- ⚠ **A faded trail must render as faded, never as absent.** Generalising the rule that
  cost a gate check on the record pane — *if a view can show less than all of a record, it
  must say so on screen* — a UI showing a decayed field must show the decay, or an
  operator reads "no trail" where the truth is "a trail nobody has reinforced for an hour."

---

## 6. What I would build first

**A (transport trails), restricted to `(espnow, ble)`, with G (prune inhibition) as a
throwaway warm-up.**

Reasoning: A attacks proof leg 2 — a *primary hypothesis* leg — along the one axis the
fleet has measured to be broken (amplitude ranging), needs no new lane, no new op, and no
constant that has to transfer across nights. Its storage already exists as `@LAT91` +
`@LAT92`; the change is a half-life inside a pure function that is already natively
tested. It lands on the Cardputer and the handhelds, which have flash headroom, and it
does not touch the 94%-full V4s.

What it needs before any code: a decision on **what counts as confirmed delivery** that is
not an ACK (see A's last ⚠), and a pre-registered falsifier — *if the trail's choice
matches "higher RSSI wins" on every pair, this added nothing* — written down before the
first run, in the order the entity-drift gates established.

B is the highest-value item and the one that would retire an operational dead end, but it
is gated on the ordinal-naming problem in §3, and that is a corpus-wide decision, not a
feature. It should not be started as a side effect of anything else.
