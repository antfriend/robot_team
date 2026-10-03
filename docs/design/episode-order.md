# Episode order across the fleet — `seq`, `follows`, and the vector that carries them

*Draft 2026-10-03; §8's three decisions taken by the operator the same day (all as
recommended). Not built. ACT-III §5 C4's last open item. Implements TTG-RFC-0004 §4.4
rule 2 (and with it §4.8 items 1–3 on hardware data); stage 2 (§7) is the
path to item 4.*

---

## 0. The short version

Every episode gets a **per-agent sequence number** (`seq:`) and a **vector**
(`follows:`): the highest `seq` this node knows of from every other node at the moment
the episode is written. Nodes learn each other's numbers from a small, frequent
**`EPISODE` toot (type 14, sub-op `VECTOR`)**. They do not exchange episode content at
this stage.

That is enough for RFC-0004 §4.4 rule 2. A number received over the air proves that
the episode it names had already been written: **B written after receiving A's `seq` is
after A, whatever the clocks say.** `semantic::order()` already decides exactly this
from `(agent, seq)` pairs and is native-tested (`tests/test_fleettime.cpp`). What is
missing is everything around it: assigning the number, carrying it over the air,
writing it into the episode and reading it back.

Episode **delivery**, meaning the content of other nodes' episodes held locally, is
stage 2 (§7). Stage 2 is what RFC-0004 §4.5's bar view needs (item 4: *same episodes,
same answers*). It is deliberately not a prerequisite for ordering, because ordering
does not need it.

---

## 1. What already exists, and what this has to fit

| fact | where | consequence here |
|---|---|---|
| `EpisodeRef{agent, seq, at, follows[]}` and `order()`: `a` BEFORE `b` iff `b.follows[a.agent] >= a.seq` | `Semantic/src/FleetTime.*`, `FLEETTIME_MAX_AGENTS 8` | the order relation is done; it compares **directly**, with no edge walk, so the vector must be **transitive** (§3.2) |
| episodes carry `at: <pulse> ±<bound> frame:<downbeat>` but **no `seq`, no `follows`, no sid** | `Episode.cpp` `EPISODE_HEADER_FMT` | two new block lines; old readers skip lines they don't know (§4) |
| ordinals are LONs in an 8192-wide tier band and **wrap** in ~5.7 days; every node mints the same ordinals | `Episode.h` "ORDINALS WRAP" | an ordinal can't name an episode across the fleet; `seq` can (§2) |
| HELLO = anchor 21 + trace 19 + capability ≤ 22 = **≤ 62 of 208 B**, but the blocks are **positional** and only the two handhelds send all three; **V4-A/B/C and the K10 send the anchor alone** | each sketch's HELLO emit | a fourth HELLO block on an anchor-only board would be read as a trace digest by both consoles, so the vector gets **its own toot type** (§3.1) |
| unknown toot types fall to `default:` and are dropped | every `handleToot` | type 14 rolls out board by board; an un-reflashed node is a non-participant, never a parse error |
| the recv callback must never touch an engine | CLAUDE.md, TimeStream section | vectors are queued in the callback and merged in `loop()`, the `TimeStreamNode` shape (§3.3) |
| one shared render scratch buffer; worst link episode measured **1194 / 1280 B** | `EpisodeNode::scratch()`, `SEMANTIC_LINK_EPISODE_BUF` | the new lines **do not fit the worst case**; the buffer grows and is pinned both ways (§4.2) |
| V4s at 96% flash, ~47–49 KB free; Cardputer loop heap 16–24 KB | FLEET.md §6, log 2026-10-03 | stage 1 is sized to fit everywhere without `huge_app` (§6) |

---

## 2. `seq` — the per-agent number

- **One counter per node, across all four tiers.** Within one agent, `seq` is a total
  order (RFC-0004 §4.4 rule 1). Today that order is ambiguous, because the tiers write
  into separate LON bands and file order is the only tiebreak.
- **`u32`, starting at 1, never wraps in practice** (one episode a minute is 8,000 years).
  That removes the reason FLEET.md §6 gave for citing a sid: ordinals wrap and collide,
  `(agent, seq)` does neither. Unlike a sid, `seq` is **ordered**, and a vector clock needs
  that.
- **Dense: incremented only when the append succeeds.** `next_seq` is assigned when the
  episode is rendered and committed only on a successful `appendRecord`; a refused append
  reuses it. A gap therefore means an episode that existed and is no longer held, never
  one that was never written. Stage 2's catch-up relies on this (§7).
- **Recovered at boot from flash, no new record.** `seq` = max over the live episodes
  replayed at boot. The newest episode is never folded (a fold takes the oldest past a
  tier's quota), so the maximum is always on flash once any episode carries a `seq`.
  The `@LAT104` checkpoint needs no change.
- **And from the fleet: a peer's view of you is a floor.** Whenever a received vector
  says this node's `seq` is higher than its own, the node jumps past it and counts a
  `seq_regression`. This covers the one case flash can't: a node whose filesystem was
  re-imaged. Its peers still remember its last number, and its next episode resumes above
  it instead of reusing `seq`s that copies elsewhere already carry. A node's first link
  window flushes about 60 s after boot, and vectors arrive every ≤ 10 s (§3.1), so in a
  powered fleet this happens before the first write. ⚠ A re-imaged node with **no** peer
  in range restarts at 1, and no rule can repair that. The regression counter makes it
  **visible** afterwards, and `fleet.py order` (§5) reports any agent whose `seq` runs
  backward against its `at:` within one frame.
- **Pre-C4 episodes have no `seq`.** They parse with `seq = 0`, meaning *unsequenced*.
  They still count as beliefs; they take no part in edge order.
  ⚠ **`order()` does not handle this today, and has to before anything writes a
  `seq`.** `knows()` tests `follows.seq >= earlier.seq`, which is always true for
  `seq = 0`. So *every* pre-C4 episode would read as BEFORE any episode that names its
  agent, and two unsequenced episodes from one agent compare `SAME`. The fix is two
  guards in `FleetTime.cpp`: no edge reaches `seq == 0`, and a same-agent pair with
  either `seq == 0` falls through to the stamp rule. Native test 8 pins it.

---

## 3. The vector, and how it travels

### 3.1 Wire: `EPISODE` (toot type 14), sub-op `VECTOR`

```
[0]        sub-op         0 = VECTOR   (1 = WANT, 2 = DATA reserved for stage 2, §7)
[1]        n              entries, ≤ FLEETTIME_MAX_AGENTS (8)
[2..]      n × { agent u32 LE, seq u32 LE }     — the sender's OWN entry included
```

That is `2 + 8n` bytes, **66 B** at the maximum: one unchunked frame, broadcast, with no
`want_ack`. A lost vector is harmless in the same way RFC-0004 §4.7 says a lost beacon
is: the next one supersedes it, and the only cost of missing one is that order is
*under-claimed*, never wrongly claimed (§3.2).

**Cadence: change-triggered, with a heartbeat.** Send when the vector changes (this node
wrote an episode, or merged a higher entry), rate-limited to one per second, plus a
heartbeat every **10 s**. At about one episode a minute per node, that is ~0.1–1 frame/s
per node. The lesson from `CMD_DUET` applies: *repeating idempotent state beats
`want_ack`*, so a node that missed one simply converges on the next.

**Why a new type rather than a fourth HELLO block** (operator decision, §8.2): HELLO's
blocks are positional. Two consoles read anything past the anchor as a trace digest
once `len ≥ 40`, and four of the six boards send only the anchor. Putting the vector on
HELLO would mean either adding placeholder trace and capability blocks to four sketches
(the V4s are at 96% flash, and an empty capability digest *asserts* "no capabilities",
which is a semantic change), or adding a length-tagged trailer that the existing parsers
would misread. Type 14 costs one more beacon frame, needs nothing from any other block,
and is ignored by old builds.

### 3.2 Merge: element-wise max, so the vector is transitive

On receipt, `V[a] = max(V[a], received[a])` for every entry. The node's own entry is
always `seq` (with the floor rule from §2). Because each node forwards everything it has
merged, knowledge of A reaches C through B even if A and C never hear each other. The
vector is a true vector clock, which is what lets `order()` compare two episodes
directly, without walking a chain of edges.

**Every entry is a lower bound on what the node knew, so it can only under-claim.** A
lost frame, a reboot that forgets the vector, or a node that hasn't heard a peer yet all
make fewer pairs ordered; none of them can make a pair wrongly ordered. Over-claiming
would need a forged or corrupt entry, and every toot is HMAC-signed.

**The vector is recovered at boot** from the newest episode's `follows:` line, which is
already replayed. Without this, a reboot would only lose order, not correctness, but
recovering it is free.

**Table size:** `FLEETTIME_MAX_AGENTS` = 8, so 7 other agents (six boards today). A full
table **drops the newcomer** and counts it (`overflow()`). Different agents' `seq`s are not
comparable, so "evict the lowest" would be arbitrary; dropping is deterministic, and either
way the result only under-claims.

### 3.3 Where it runs

A new header, `Semantic/src/EpisodeOrderNode.h` (Arduino glue, the `TimeStreamNode`
shape), plus the portable part in `Semantic/src/EpisodeOrder.*`, native-tested:

- `onEpisodeToot(t)` **from the recv callback:** validate the length, copy into a
  4-deep ring, bump the index. Nothing else.
- `service(now)` **first thing in `loop()`:** drain the ring, merge, apply the
  `seq` floor, and emit `VECTOR` if it changed or the heartbeat is due.
- `stamp(EpisodeBuilder&)` **at every episode render:** write `seq:` and `follows:`.
- `committed()` **after a successful append:** advance `seq`.

---

## 4. In the record

```ttdb-episode
source: perceptlearn
at: 4890438 ±0 frame:5000
seq: 1412
follows: 0x00000010:388 0x00000011:57 0x00000200:77 0x00000012:212
said: 1 | ...
```

- **Two block lines, after `at:`, inside the fence.** `follows:` lists only *other*
  agents with `seq > 0`, sorted by agent id, so that two renders of the same vector are
  byte-identical. With no entries the line is omitted, not written empty.
- **Old readers are unaffected:** the firmware's `EpisodeReader` reads only `percept:`
  lines (`Episode.cpp:229`), and `fleet.py`'s `tier_records` returns only `said:`. Both
  are proven by the existing suites still passing, and pinned by a new fixture.

### 4.1 Why block lines, not `relates:` edges

TTDB-RFC-0003 typed edges target a **coordinate** (`derived_from@LAT97LON3`). A
`follows` target is `(agent, seq)`, an episode that is usually held **nowhere** on this
node, and whose local coordinate (if stage 2 ever stores a copy) would be this node's
ordinal, which says nothing about the original. Writing it as `follows@LATxLONy` would
fabricate an address. The block line is honest about what it is: a vector clock. If
the RFC wants an edge form later, `follows@<agent>:<seq>` is the natural one to propose
upstream, alongside C2d's divergence note, not invented here.

### 4.2 The buffer

✅ **Measured 2026-10-03, and the draft's estimate was wrong in the cheap direction.** A
maximal block is **179 B** (`EPISODEORDER_BLOCK_MAX` 184). The worst link episode becomes
**1373 B**, so `SEMANTIC_LINK_EPISODE_BUF` went 1280 → **1408**, pinned both ways (fits
1408, would not have fitted 1280). But **no firmware allocates that constant**: every
render goes into the one shared scratch, `SEMANTIC_ENTITY_EPISODE_BUF` = **3072 B**, and the
worst episode any tier writes still fits it with a maximal block: entity 2727 + 179 = 2906,
link window 2064 + 179 = 2243 against its 2560 budget (both pinned in `test_episode`). **So
the order lines cost 0 B of `.bss`**, not the +128 B the draft said.

---

## 5. The laptop side

- `fleet.py`: `parse_episode_order(text, node)` returns `EpisodeRef`-shaped dicts
  (`agent, seq, at, follows`) per episode, with a Python port of `order()` and
  `maximal()` held byte-compatible with `FleetTime.cpp` by a shared fixture.
- **`fleet.py order <pull> <pull> …`**, the instrument. It merges N pulls and reports,
  for every cross-agent pair of episodes: ordered **by edge**, ordered **by stamps
  only**, **concurrent**, and **`clock_contradiction`** (an edge decided against what the
  stamps alone said). It also reports per-agent `seq` density (gaps = folded or lost)
  and any `seq` that runs backward against `at:` within one frame (§2's re-image case).

The laptop is still the only place where two stores *meet* until stage 2. That is the
CLAUDE.md caveat applied honestly: **the edges are written by the fleet with no cable
attached**, and only *reading them across stores* needs the laptop. Stage 2 is where
the fleet reads them itself.

---

## 6. Cost (estimates, to be measured)

| | flash | RAM |
|---|---|---|
| `EpisodeOrder` + glue | ~2–3 KB | vector 8 × 8 = 64 B, ring 4 × 66 ≈ 270 B, counters |
| render buffer | — | **0 B** (fits the existing 3072 B scratch, §4.2) |
| airtime | — | ≤ 66 B frame, ~0.1–1 /s per node |

The V4s have ~47–49 KB free, so **stage 1 does not need `huge_app`**. Stage 2 probably
does (§7).

---

## 7. Stage 2 — delivery (sketch, not part of this build)

Stage 2 is what RFC-0004 §4.5 / §4.8 item 4 needs: two nodes holding the *same
episodes* compute the *same view as of bar N*.

- **`WANT {agent, from_seq, to_seq}`**, addressed. A receiver whose vector says it knows
  `V[a]` but holds less asks for the difference, so the vector **is** the anti-entropy
  digest and stage 1 is its prerequisite. Because `seq` is dense (§2), "what am I
  missing" is a range, not a set.
- **`DATA`**: one episode per logical toot, chunked under RFC-0007 (8 × 208 = 1664 B cap,
  which fits 1408 + 16 B header), streamed **from `loop()` and paced** (the ESP-NOW burst-pacing
  rule), `want_ack` per chunk. The author answers first; any holder may answer later
  (gossip), keyed on `(agent, seq)`.
- **Stored in a new lane, `@LAT105` HELD**, with a per-source quota (say 8 each,
  ~40 index slots for five peers; the Cardputer is at 173/288) and oldest-first eviction
  per source, the same ring as the tiers. **Never fed to this node's consolidator.**
  Another agent's episode is testimony (TTG-0002 §5.1; default-network.md: *testimony
  must never fold into the world's tally*). The bar view reads own + held; beliefs read
  own only.
- **Integrity:** an EVENT sid (`Sid.h`) on each episode lets a receiver verify that the
  copy it holds is the episode the author wrote, and gives `follows` the `#sid` suffix
  FLEET.md §6 asked for. It is useful in stage 2, not needed in stage 1.
- **Not `@LAT102`.** That lane was reserved for *attributed testimony as tallies*, one
  record per `(speaker, claim-slot)`, bounded by cardinality (default-network.md §3).
  Whole foreign episodes are a different kind of record, and putting them there would
  undo the design decision that lane exists to protect.

---

## 8. Decisions — ✅ all three taken 2026-10-03, as recommended

1. **Ordering from a received number, not from held content.** RFC-0004 §4.4 says
   *"the latest episode it **holds** from each other agent"*. This design reads "holds" as
   "knows was written", the Lamport reading: rule 2's own justification is *"B was said
   already knowing A"*, and a received `seq` is exactly that knowledge. The consequence
   is that order arrives in stage 1, with no delivery. **Recommended**, and recorded as a
   second divergence to offer upstream next to C2d.
2. **Toot type 14 instead of a fourth HELLO block** (§3.1). **Recommended.**
3. **`@LAT105` for held episodes in stage 2**, keeping `@LAT102` for tallies (§7).
   **Recommended**; nothing in stage 1 depends on it.

---

## 9. Test plan

**Native** (`tests/test_episode_order.cpp`, plus the laptop suite):

1. `seq` is dense: a refused append reuses the number, and boot recovers max+1 from a
   fixture lane spanning all four tiers.
2. Merge is element-wise max; the own entry follows the floor rule; a higher own entry
   from a peer jumps `seq` and counts one regression.
3. Transitivity: A → B → C fixture vectors give C an entry for A it never heard directly.
4. Render ↔ parse round-trip of `seq:`/`follows:` (sorted, omitted when empty); the
   firmware `EpisodeReader` and `fleet.py` `tier_records` produce **identical** output
   with and without the new lines.
5. Buffer pinned both ways: a maximal episode with a full vector fits 1408 and does not
   fit 1280.
6. `order()` over episodes **rendered and re-parsed** from two fixture stores satisfies
   RFC-0004 §4.8 items 1–3 (today's test builds `EpisodeRef` by hand). The Python port
   agrees with C++ on a shared fixture.
7. The callback only enqueues: an Engine-mutation guard, the same shape as the
   TimeStream test.
8. `seq = 0` (unsequenced): no `follows` entry reaches it, and two such episodes from one
   agent are ordered by stamps or are concurrent, never `SAME` (§2). This test must fail
   against today's `FleetTime.cpp` before the guard goes in.

**Hardware gate, pre-registered.** The Cardputer and one V4, side by side, both on the
new build, for ≥ 1 h, then both pulled by their own cables:

- (a) every new episode on both carries `seq`, dense apart from folds; after the first
  vector exchange every episode carries a non-empty `follows:`.
- (b) **of the cross-node episode pairs written > 20 s apart, ≥ 95% are ordered by an
  edge.** Vectors travel at ≤ 10 s, so a pair farther apart than two heartbeats that
  stays concurrent means delivery or merge is broken, not the clocks.
- (c) `clock_contradiction` is reported, not gated. **A non-zero count is a finding about
  `±bound` (too tight), not about edges.** The edge is right by construction; the stamp
  is the estimate.
- (d) Reboot the V4 five times (boot-counted as usual): `seq` resumes at max+1 each time
  and never reuses a number; `seq_regression` stays 0.

**What would falsify the design, not just the build:** (b) failing while vectors
demonstrably arrive (serial shows merges). That would mean the order relation is wrong
for this fleet, not the radio, and the RFC's rule 2 would need revisiting before stage 2
builds on it.

---

## 10. Order of work

> ✅ **Steps 1–2 done 2026-10-03** (no hardware): the `seq 0` guard in `order()` (test 8,
> red first: 4 of 4 failed, then green); `Semantic/src/EpisodeOrder.*` (VectorClock,
> VectorInbox, block render/parse, OrderRecovery) + `tests/test_episode_order.cpp`
> (**66 checks**); the optional `order` block threaded through every episode renderer
> (default off, so existing output is byte-identical); `fleet.py order` + its Python port,
> mirrored case-for-case in `tests/test_episode_order_py.py`. Toot type 14 reserved.
> The Cardputer builds at 42% / 40% (nothing calls the new code yet).
>
> ✅ **Step 3 done 2026-10-03:** Cardputer glue (`EpisodeNode::attachOrder`, `BootTee` →
> `OrderRecovery`, commit-on-append via `pending_seq_`; sketch: inbox push in the recv
> callback, drain + send in `loop()`). +2992 B flash / +368 B RAM vs HEAD. 5/5 clean boots;
> 8 appends → `seq 1..8` dense on a pull (link and entity interleaved under one counter);
> reboot after a fold recovers `seq 8` → next 9. `follows:` empty, as it must be until a
> second board runs this build.
>
> ✅ **Step 4 + the hardware gate, 2026-10-03: PASS.** V4-A on the build; 62 min side by side.
> **(b) 4178 / 4182 = 99.9 %** of cross-agent pairs > 20 s apart ordered by an edge (≥ 95 %
> pre-registered); 4187 pairs, 0 concurrent, **0 clock contradictions**. The 5 non-edge pairs
> are lost vectors (one side wrote > 20 s after the other without having heard it): still
> ordered, by stamps, as §3.2 predicts. **(d)** 5 V4-A reboots, `seq 65` → 66 each time.
> **(a)** every episode after the first exchange carries `follows`; gaps are folds (each tier's
> LONs contiguous, `seq` rising with LON). Pulls: `master/{cardputer,v4a}_c4gate_2026-10-03.md`.
> **Next: step 5**, the other four boards one at a time.

1. The `order()` guard for `seq = 0` (test 8 first, red), then `EpisodeOrder.*`
   portable core + native tests 1–7 (no hardware).
2. `fleet.py` parser + `order` command against fixtures.
3. Cardputer: glue + flash + boot-count; check that its episodes carry `seq` and an
   empty `follows:` (no peer on the new build yet).
4. One V4: same. Run the hardware gate.
5. The remaining four boards, one at a time, each boot-counted.
6. Record the result in `docs/log/`, and mark ACT-III §5 C4 rule 2 done. Stage 2 is
   then its own decision.

