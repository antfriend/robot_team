# The default network — capabilities, testimony, and shape

*Design exploration — 2026-08-09. **Stages 1 and 4 (§6) are BUILT and natively tested;
stages 2, 3 and 5 are not.** Not in PLAN.md. companion.md remains the source of truth for
what is true of the fleet — see its 2026-08-09 entries for the state, including what has
NOT been flashed. This is the exploratory half of a proposal; if it survives, its
normative half is an extension to TTDB-RFC-0010 (lane classes) and TTN-RFC-0005 (trust),
not a new corpus.*

Companion documents: [stigmergy.md](stigmergy.md) (the field discipline this sits inside),
[ttn-semantic-positioning.md](ttn-semantic-positioning.md) (the hypothesis §5 serves).

---

## 0. The ask, restated precisely

Four claims, taken as the brief:

1. A node should follow a **default-network scene**: a record of the beliefs it has come to
   hold about the *other* nodes, read when nothing else is demanding attention.
2. A node **knows its own capabilities** (mic, GPS, ability to know the time and date) and
   knows **whether it has shared them** with a given other.
3. The fleet's understanding of **its own physical shape** should be *what can be inferred
   in the moment from their common information*.
4. **One direct sensory input is enough to form a direct-experience belief.** A
   communication about someone else's direct experience forms a **new direct experience in
   the recipient**, of the form `V4-A believes xyz`.

Claim 4 is the load-bearing one and it is correct as stated. Claims 2 and 3 each contain
one thing that cannot be built as written. §2 is the corrections; §3–§6 is what I would
build instead.

📌 The name is read here as the brain's **default mode network** — the resting-state system
that runs self-referential and social modelling when no task is on. That reading is what
makes it a *scene*: `pulse::Chart` already carries a band-wide `scene_id` that survives
conductor handoff, and the band's idle scene is currently silence. The proposal is that the
fleet's idle behaviour is *modelling each other*.

---

## 1. The reframe that unifies the two halves

Capabilities and positioning look like two features. They are one:

> **Umwelt overlap gives the fleet its SHAPE. Capabilities are what give the shape a POSE.**

A relation between two nodes — do we hear each other, do we see the same access points, did
that deposit get through — is invariant under moving the whole fleet. So *everything*
inferable from common information alone is inferable only up to the symmetry group: in 2D
that is **translation (2), rotation (1), reflection (1) = four degrees of freedom** the
common information cannot touch. This is not a limitation to be engineered away; it is what
"inferred from common information" *means*.

Those four are broken only by a node holding a capability nobody else has:

| Breaks | Needs | Who has it |
|---|---|---|
| translation | one absolute fix | T-Deck GPS |
| rotation | a second fix at a different place | T-Deck GPS, roaming |
| reflection | a third non-collinear fix | T-Deck GPS, roaming (`companion.py anchor`'s "≥3 ties resolve mirror") |
| *nothing* | RSSI amplitude | ⚠ measured broken outdoors: 2–7× over-range, decorrelated |

So the capability table is not metadata about the fleet — **it is the list of who can
collapse which ambiguity**, and a node that knows the fleet's capabilities knows exactly how
much of its own shape is knowable right now. That is a computable quantity, it belongs in
the default-network scene, and it is the most useful single number the scene could hold.

🔬 Falsifier for the whole reframe: if the scene's shape estimate agrees with
`companion.py positions` in every configuration, the distributed version added nothing.
Say so and stop (stigmergy.md §4.C's falsifier, restated).

---

## 2. Corrections

### 2.1 "Knows whether it has shared its capabilities" — cannot be known, and the useful version is cheaper

You cannot know a broadcast was received without an acknowledgement, and an
acknowledgement's absence proves nothing here — this fleet has the receipt twice over
(`--op play` and a prune on a grown TTDB both succeed while no-ACKing;
[[band-play-ack-false-negative]]). Worse, "have I told X" is a **send-side** fact: it is
cheap to store and it answers the wrong question, because it stays true after X reboots and
forgets.

Model the **disagreement**, not the telling:

- Each node carries a `cap_epoch` — one byte, bumped whenever its own capability vector
  changes (a peripheral verified, a GPS fix obtained, LoRa enabled).
- Each node's HELLO carries its own `cap_epoch` **and, for each peer it knows about, the
  epoch it currently holds for that peer**.
- B hears A's beacon, finds itself in A's peer list, and compares the epoch A holds for B
  against B's own. **A lower one means A is out of date about B — and B learned that from a
  direct experience of the beacon, with nobody having asked anybody anything.**

The response is not a reply. B raises its own re-advertisement rate for a cooldown; A's
picture converges within a beacon or two; the elevated rate decays. This is anti-entropy
gossip in its standard form and it is **exactly stigmergic**: the medium carries *who is
stale about whom*, the trace selects the next act, and no node addresses another.

It is also self-healing across reboots, which the send-side flag is not.

### 2.2 "Ability to get the current time and date" already exists — do not re-invent it

That capability is `wall:<0|1>`, live fleet-wide since 2026-08-03, and it is already kept
**separate from `stream:`** precisely because *we agree with each other* and *we know what
day it is* are two different facts that one bit used to conflate. Any capability mask must
**derive** its wall-clock bit from `timestream::Engine::wall()` and never store it
independently, or the fleet acquires a second source of truth for the thing it just spent a
release giving one.

🔬 And `wall` is worth studying because **it is already an instance of claim 4 working.** A
node with no laptop contact holds `wall:1` by having adopted a peer's stream. It did not
sense the date; it received it, attributed to a timeline it can name, with a `REMAP` record
kept so a superseded attribution stays interpretable. That is testimony handled correctly,
in production, on six sketches. Copy its shape.

### 2.3 A capability claim is a falsifiable prediction — so it needs no new belief machinery

"I have a mic" is not a fact about a device tree. It is a **prediction**: *when the fleet
clock says a transient occurred, this node will report one*. That is falsifiable inside one
window against an observable the fleet already produces (`@LAT94` stamps the loudest
transient with the fleet-clock time, explicitly as TDoA groundwork).

Which means capabilities go through `PerceptLearn`'s Rule 1 / Rule 2 **unmodified**: predict
before the world answers, append the verdict to a lane the node never edits, let Rule 3 fold
it. No new epistemics, no new lane discipline, and capability confidence gets earned the
same way link stability does.

Three statuses fall out, and they are earned rather than compiled in:

- **declared** — the build says the peripheral is there.
- **verified** — it answered at boot.
- **exercised** — it produced a percept that reached a lane.

This fleet has been wrong at each of the first two steps: the BMI270 is at `0x69`, not the
published `0x68`; `TFT_BL 45` silenced a speaker that was declared and present; the T-Deck's
battery divider reads **4.71 V**, above the Li-ion ceiling, from constants that were never
metered. ⚠ **A self-declared capability is a claim, and this repo's own history is the
argument for treating it as one** ([[verify-before-believing]]).

⚠ Honest limit: the mic prediction needs a **second** mic to be checkable by anyone but the
node making it, and only the Cardputer has one. Until then a mic claim is self-attested and
must render as such.

### 2.4 "One input forms a belief" — yes, and that is what makes EPS an actuator

Correct, and it is not a weakening. `EPS = sal × (255−conf)/255` means a
single-observation belief is a **high-salience, low-confidence** record — i.e. by
construction the highest-EPS thing the node holds, i.e. the next thing it should go and
check. One-shot belief formation is what *loads* the attention field; refusing to form the
belief until N observations is what leaves it empty.

Two constraints on it:

- ⚠ **A one-shot belief must stay distinguishable from a folded one forever.** Rule 3's
  `+2 / −16` asymmetry encodes "a claim must hold 8 times in 9 to be worth keeping"; a
  belief that enters at a *folded* confidence it never earned gets that guarantee for free.
  The shape already exists — `**RUN** windows_since_last:1 reason:first` — and must be
  written from birth, not retrofitted.
- **Birth confidence must be a stated constant per evidence class, not whatever the fold
  happens to produce.** Direct sensing and testimony must not enter at the same value (§2.5).

### 2.5 Testimony: the wrapper is non-collapsible, and that is the whole safety property

`V4-A believes xyz` is exactly right, and the reason it is right is worth stating as a rule
rather than a preference:

> **A node MUST NOT fold `V4-A believes P` into its own tally for `P`.** They are different
> propositions. The first is an observation of an *utterance* and its subject is V4-A; the
> second is an observation of the *world*.

Collapse them and five nodes echoing one clap become five independent confirmations of it,
and confidence rises with hop count rather than with evidence. This fleet already has that
failure written down in a narrower form — *"the boundary must never contain `**OBSERVED**
peer:0x` … the node re-learns from its own gravestone"* — and it is the same shape as the
`prev_stream:` and `**COVERED-SPAN**` needle collisions: **a matcher that cannot tell a
quotation from an assertion.** Generalise it once, here, rather than a fourth time.

Two consequences:

1. **Two confidences, never one.** *That the utterance happened* is near-certain — the toot
   is HMAC-signed and we received it, which is as direct as any sensing this fleet does.
   *That the content is true* is an inference from the speaker's track record. Storing one
   number for both is what makes rumour indistinguishable from observation.
2. **Cycles become harmless by construction.** If A tells B "P", and B tells A "B believes
   P", A records `V4-B believes (V4-A believes P)` — a distinct proposition about B, not a
   second vote for P. No hop counters, no seen-sets, no TTL. The nesting terminates in
   practice because the wire form carries a depth cap (§4).

---

## 3. Where it lives: three layers, two of them already built

| Layer | Lane | Class | Bounded by | Prune |
|---|---|---|---|---|
| **What was said** | `@LAT102` ATTRIBUTED | EVIDENCE | peers × claim-slots | **none needed** |
| **What speakers are worth** | `@LAT91`-shaped belief per speaker | EVIDENCE | peers | none |
| **What the fleet looks like now** | `@LAT101` SOCIAL | **FIELD** | decayed reclamation | none, by design |

⚠ **`@LAT102` must be bounded by CARDINALITY, not by time.** A log of every utterance is a
lane that fills with uptime — the disease `@LAT95` and `@LAT92` already caught — and worse,
it re-enters the prune treadmill whose budget is the Cardputer's **28 of 32** remaining
`@LAT100` markers. Make it one tally record per `(speaker, claim-slot)` with run-length
counts from birth, like `@LAT91` is one belief per `(peer, proto)`: ~5 peers × ~8 claim
slots = **40 slots, a working set that never grows with uptime and therefore never needs a
boundary.** This is the single most important structural decision in the proposal, and it
is only available because the design is being made now rather than retrofitted.

`@LAT101` is the fleet's first FIELD lane, which RFC-0010 §3 requires be a **new** lane at
101+ (never a conversion — reclassifying a lane retroactively reclassifies the archives in
`master/` too). ✅ **BUILT 2026-08-09 (RFC-0010 §7.2 stage 3).** One record per known
peer, in the shipped form (three masks, like the wire; the draft's two-mask `caps/status`
could not express three levels — same correction §4 records):

```
@LAT101LON0 | sid:1c68e2a4 | created:… | updated:… |
**PEER** node:0x00000200 spoke:1 declared:0x7f93 verified:0x7793 exercised:0x1011 cap_epoch:7
**TRACE** copresence:180 half_life_ms:600000 reinforced:9 last_ms:8260961
t_ms:3710811 stream:0xe334a7e1 wall:1
```

The `shape:` line from the draft is deliberately absent — it belongs to stage 5 (the
relaxation), and a record field written before anything computes it would be a fabricated
pose. The natural key is **`node:0x%08lx`** (§7's question 4, answered): full width,
because every 1-byte squeeze of this fleet's ids collides.

**Acceptance test (RFC-0010 §6.3), and it passes:** a node that just booted has an empty
`@LAT101`, plays nothing, believes nothing about anyone — and that is a correct state, not a
degraded one, because HELLO refills it within one 2 s beacon. Emptying it costs a latency,
not an answer. ⚠ Which is exactly why capabilities must **not** be stored only there: the
durable record of what was claimed is `@LAT102`, EVIDENCE; the field is the current picture,
disposable on purpose.

---

## 4. The wire: 10–22 bytes, inside a budget with room

✅ **BUILT 2026-08-09 — `firmware/libraries/Social`, both handhelds, native suite 89 checks.**
The layout below is the shipped one. It differs from this document's first draft in one
way, and the change was worth its bytes: the draft sent **two** masks (`caps` + `status`)
which can only express two levels, and §2.3 needs **three**. Three `u16` masks it is.

HELLO is 250 bytes and carries **39** today (21-byte time-stream anchor + 18-byte trace
digest). The social digest follows the same construction rules that made both of those
backward-compatible: fixed offset after the previous block, magic + version checked before a
single byte is trusted, an un-reflashed node contributing zero bytes and being a
**non-participant rather than a parse error**.

```
[0]      magic 0xFC
[1]      version
[2..3]   declared   u16 LE
[4..5]   verified   u16 LE
[6..7]   exercised  u16 LE
[8]      cap_epoch  u8    bumped only on a real change to the three masks above
[9]      n_peers    u8
[10..]   n_peers × { peer u16 LE, cap_epoch_we_hold u8 }
```

Header 10 B + 3 B/peer; four peers → **22 bytes**, and HELLO goes 39 → **61 of 250**.
⚠ Price it against **LoRa** framing (TTN-RFC-0006), not ESP-NOW, because that is the budget
that will actually bind in Phase 4.

Three details the implementation forced, each of which is a trap avoided:

- **The peer id is 2 bytes, not 1.** Every `RobotTeamNodeId` is ≤ `0x300`, so the low 16
  bits are unique — but every 1-byte squeeze of them collides on this fleet (`0x001`/`0x011`
  under a low-nibble fold, `0x100`/`0x200` under a low-byte truncation). A collision merges
  two nodes into one table row, each overwriting the other every beacon. `test_social.cpp`
  pins the uniqueness invariant against the id list, so allocating a colliding id fails the
  build instead of silently merging two robots.
- **The sender's id is deliberately absent** — it is already in the signed toot header, and
  a second copy is a second thing that can disagree with the first.
- **The block chains on the trace digest, not on the anchor.** Its position is defined as
  *after the field*, so appending it in a beacon where the field was skipped would put
  capability masks exactly where a receiver reads trace strengths.

Nesting depth for testimony rides on the record, not the beacon: `V4-A believes …` is depth
1, and **depth is capped at 1 on the wire**. A node relays what it observed, never what it
was told someone else was told. Second-hand testimony is not evidence about the world *or*
about the speaker — it is evidence about the relayer, and nothing in §1 needs it.

---

## 5. The scene itself

Scene 0 — the band's idle scene, currently silence — becomes the default network. Per idle
bar, each node independently:

1. **Voices the social field.** One cell per peer on the 16-step grid `TraceField` already
   uses, amplitude = decayed co-presence. You *hear* who is present and how strongly. This
   is the working `TraceField` extended, not a new instrument.
2. **Takes one damped relaxation step** on its own `(x, y, σ)` — pull toward peers with high
   umwelt overlap, push from peers with none. ⚠ Damping and a stated iteration budget are
   mandatory: a distributed relaxation can oscillate where a central one converges.
3. **Checks for staleness** (§2.1) and adjusts its own re-advertisement rate. No reply.

All three are local reads of a shared medium. Nothing addresses anybody, which is the test
that this is stigmergy and not a protocol with extra steps.

⚠ **The scene must render decay as decay** (RFC-0010 §6.4): a peer whose co-presence has
faded must show as *faded*, never as *absent*. "Nobody has reinforced this for an hour" and
"there is no such node" are different claims, and on this fleet the second one has already
been fabricated once by a shell loop that rebooted the bridge
([[looping-companion-py-resets-bridge]]).

⚠ **And the pose must render its own ambiguity.** If no GPS-capable node has taken a fix,
the shape is correct and the map is one of four; drawing it as a map is the same class of
lie as drawing a faded trace as an absent one. Show the shape; show which of the four
degrees of freedom are currently pinned and by whom.

---

## 6. Build order, and what each stage costs

Each stage is independently abandonable, per RFC-0010 §7.2's staging.

- ✅ **Stage 1 — capability advertisement only. BUILT 2026-08-09, NOT YET FLASHED.**
  `firmware/libraries/Social` (portable core + `SocialNode.h` glue, the shape
  `TimeStreamNode`/`LaneGenNode`/`TraceFieldNode` established), wired into both handhelds'
  HELLO, `w` prints the fleet table on either. No lane, no belief, no field — RAM only, so
  RFC-0010 §6.3's acceptance test holds trivially: a node that just booted knows nothing
  about anybody, and a HELLO refills the table in one 2 s beacon.
  **Cost, measured against a HEAD worktree: T-Deck +3220 B flash (+0.10 %), +520 B RAM;
  Cardputer +3300 B (+0.10 %), +520 B.** Both sketches read one percentage point higher
  than before (40→41, 41→42) purely from rounding. Native suite **89 checks, 0 failures.**

  🔬 **THE FALSIFIER IS ALREADY HALF-ANSWERED, AND BY ARGUMENT RATHER THAN BY RUNNING IT.**
  Writing the code exposed why: a node's whole capability vector is in its every beacon, so
  **at one radio hop a peer's view cannot lag** — it converges next beacon regardless of
  what anyone reports. The staleness detector is therefore an **instrument, not a
  mechanism**, and it is expected to read **zero**. It was built anyway, and only as a
  counter, because zero is the finding: it is the cheap, dated evidence that §2.1's
  machinery can be deleted rather than kept "just in case". Three places it could still
  fire, all of which stage 1 can now watch for: a peer heard over multiple hops, a digest
  whose peer list has rotated past the node in question (5 nodes, 4 slots — live today),
  and a LoRa budget too small to carry the vector every time.
  ⚠ **Building the response would have been the mistake.** A rate-control loop that cannot
  matter is worse than none: it would have looked like a working mechanism forever.
- **Stage 2 — capability claims through Rule 1/2** (§2.3). Reuses `PerceptLearn` whole. This
  is where `verified` and `exercised` start being earned rather than asserted.
- **Stage 3 — `@LAT102` attributed testimony**, cardinality-bounded, depth-capped at 1,
  with the two confidences kept separate.
- ✅ **Stage 4 — `@LAT101` as the fleet's first FIELD lane. BUILT 2026-08-09** (this is
  RFC-0010 §7.2's **stage 3** — the two documents number their stages differently; the
  RFC's staging entry is the fuller account). The key is `node:0x%08lx` (KEY-identified,
  as the measurement required); deposits are receptions of the HELLO blocks stage 1
  already ships (no new wire bytes); the lane is the RAM table's durable shadow,
  change-triggered + heartbeat, born with **no prune path** — which is the RFC's stage-3
  falsifier, pre-committed structurally.
  ⚠ Note this stage landed BEFORE stages 2 and 3 above: the field needed no Rule-1/2
  epistemics and no testimony lane, only the sid decision, and building it first is what
  §7.2's "each stage independently abandonable" is for. Stages 2/3 remain open.
- **Stage 5 — the scene.** Voicing and relaxation.

**Where it lands:** the two handhelds (Cardputer 41%, T-Deck 40%). ⚠ The three V4s are at
**94%** and need `huge_app` before they carry any of this — which means stage 1's capability
table is *incomplete by construction* until they are repartitioned, and the table must say
so rather than reporting a V4 as capability-less.

**Interlocks, both already established:**
- ⚠ No stage during a measurement run. A firmware flash is fine; `Upload-*-FS.ps1` wipes the
  lanes.
- ⚠ No measured constant may come from `@LAT101` (RFC-0010 §6.1). The staleness cooldown,
  the co-presence half-life and the relaxation damping are all **field** parameters; if one
  of them ever needs to be a *published* number, it must be measured off `@LAT102`.

---

## 7. Open questions

1. **What is a claim-slot?** §3's bound is `peers × claim-slots` and the whole no-prune
   property rests on that second factor being small and fixed. Capability bits are an
   obvious slot set; positions and link verdicts are not obviously bounded. If the slot set
   grows with the world, `@LAT102` is a log again.
2. **Does speaker reliability actually differentiate on a five-node fleet?** All five are
   honest and none is adversarial. If every speaker's reliability saturates at the ceiling
   and stays there, §3's middle layer is dead weight — that is TTN-RFC-0005's whole subject
   and it may simply have no work to do here until a node is faulty. Worth pre-registering
   as a falsifier rather than discovering after building it.
3. ~~**Whether `@LAT101` should be shared as deposits at all**, or held per-node and
   merged only on pull.~~ ✅ **Answered by building it (2026-08-09): per-node, merged only
   on pull.** Its deposits are receptions of blocks HELLO already carries, so sharing
   them again would be a second copy that can disagree with the first. RFC-0010 §9 keeps
   the question open only for a field whose deposits are not already on the air.
4. ~~**`sid` naming remains the gate for stage 4**, unchanged and unpriced.~~ ✅ **Closed
   2026-08-09** (TTDB-RFC-0010 v0.2 §4). ~~The replacement question: **what is
   `@LAT101`'s natural key?**~~ ✅ Also closed the same day: **`node:0x%08lx`**, full
   width (§3's record form).
