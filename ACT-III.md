# Act III — one grammar, one loop, one lane triple

**A plan for a comprehensive reorganization, consolidation, and new focus.**
Authored 2026-09-30 against `robot_team` @ `79b3967`; direction settled the same
day (§8). Amends [PLAN.md](PLAN.md) (Act I floor → Act II hypothesis) with a
third act, and is written to be read *after* [FLEET.md](FLEET.md) §1–5 —
renamed `FLEET.md` by Phase B — but *instead of* its §6, which Phase B retires.

Every number below was measured during the survey that produced this plan, not
recalled. Where a claim is an argument rather than a measurement it says so.

---

## 0. The shape of the thing

Four asks, in the order they were given:

| | ask | phase |
|---|---|---|
| 1 | Sync the RFCs with the newer/additional ones in the website and engineering repos | **A** |
| 2 | Reorganize + consolidate. **Replace every logging-style write with one memory that never fills up** — less data logger, more dynamic agent with a memory | **B**, **C** |
| 3 | A more unified approach to all visualizations | **D** |
| 4 | A snake game: the eyeball is the head, episodic memory lanes are the body, the snake is live attention | **E** |

They are not four projects. **A supplies the spec that C is a refactor toward,
C supplies the data contract that E renders, and D is the layer E needs to
exist on more than one board.** B is what makes the other four legible enough
to execute. The dependency is real and the ordering is not negotiable except
where §10 says so.

⚠ **§8's answers changed two things in this plan, and both are recorded rather
than smoothed over.** The hypothesis is now *autonomous fleet* (§2), which
demotes semantic positioning from "the thing being proven" to "a thing the fleet
cooperatively does" — a reframe, not a deletion. And "never fills up" removed the
snake's **wall** and its **death** (§7.2), because a memory that cannot refuse a
write has no cap to crash into. The replacement is better and is stated there.

---

## 1. What the survey found

### 1.1 The RFC sync surface is small, precise, and bidirectional

Three copies of the corpus exist: `robot_team/replicate/RFCs/` (32 files),
`toot-toot-engineering/RFCs/` (37), and `antfriend.github.io/RFCs/` (36 — the
website repo, plus `replicate/RFCs/index.html` + `js/rfc-reader.js` + `css/rfc-reader.css`,
a reader UI that renders the corpus as a walkable globe).

Compared with line endings normalised, **every file is byte-identical across all
three except six**:

| file | robot_team | toot-toot | website | verdict |
|---|---|---|---|---|
| `TTG-RFC-0001-Grammar-in-the-Store.md` | — | ✅ | ✅ | **import** |
| `TTG-RFC-0002-Semantic-Percepts.md` | — | ✅ | ✅ | **import** |
| `TTG-RFC-0003-Beliefs-Reasoning-Response.md` | — | ✅ | ✅ | **import** |
| `TTG-RFC-0004-Time-and-the-Fleet.md` | — | ✅ | ✅ | **import** |
| `TTG-RFC-0005-Shapes-and-Amendments.md` | — | ✅ | ✅ | **import** |
| `TTDB-RFC-0009-Counter-Story…` | ✅ | ✅ | — | **push to website** |
| `TTDB-RFC-0010-Stigmergic-Fields…` | ✅ | — | — | **push to both** (never existed upstream; safe) |
| `INDEX.md` | 10510 B | 10217 | 10217 | **3-way merge** |
| `TTN-RFC-0002-Typed-Edges.md` | 1140 B | 845 | 900 | ✅ **v1.1 is correct** — the upstream 1.0 is a regression, not a retraction; pushed to both (A4) |
| `rfc.ttdb.md` | 38 rec | 39 rec | 39 rec | **union → 44 rec** (43 + 1 belief) |

Two consequences worth stating before anyone starts:

- ⚠ **The website's copies were not newer.** They read uniformly 200–400 B larger,
  which looks like new content and was not: `diff --strip-trailing-cr` was clean on
  every one. *(As surveyed: robot_team's own RFC dir was mixed too — five files CRLF
  in the working tree. A1 has since pinned the whole directory to LF.)*
  **Root cause, and it is not what it looks like:** `core.autocrlf=true`, so the
  committed blobs were **already LF in every repo** — only the checkouts differed.
  The three repositories never diverged on line endings at all. Sizes are not
  evidence in this corpus; diff normalised, or you will "sync" 30 files that were
  already identical and bury the six that matter.
- ⚠ **Neither INDEX is a superset.** robot_team's lists `TTDB-RFC-0009` and
  `-0010` and zero TTG entries; toot-toot's lists all five TTG entries and neither
  TTDB-0009 nor -0010. A merge that takes one side wholesale silently drops the
  other's newest work.

### 1.2 The new RFCs are not adjacent to this fleet — they are a spec *of* it

The five TTG RFCs (Toot Toot Grammar, 2026-09-13 → 09-22, all **1.0 Stable**,
implemented by the `personal_grimoire` reference runtime) describe, in order: a
store that carries its own grammar (0001), how input becomes **percepts** on an
append-only **episode** lane and **terms** on a belief lane (0002), how percepts
**consolidate into beliefs** and how a reply is built only from grounds (0003),
how sayings are **ordered without a clock** and how a later saying **retires** an
earlier one (0004), and how a sentence's **shape** is read and amended (0005).

Three of those land directly on top of work this fleet already has, in a simpler
form:

1. **TTG-RFC-0003 §2 is `PerceptLearn` Rule 3, done differently and better.**
   Consolidation is a deterministic count: per triple, `for` = Σ of the largest
   positive weight per episode, `against` likewise, `conf = 255 × (max(for,against)
   + prior_for) ÷ (for + against + prior_for + prior_against)`, decided when
   polarity ≠ `?` and `conf > belief_conf_threshold`. And then the load-bearing
   sentence: *"Beliefs are derived. A conforming implementation MUST be able to
   recompute every belief line from the episodes."*
   Rule 3 is the opposite: an **asymmetric in-place fold**, `conf +2` on a met
   expectation and `−16` on a violated one
   ([PerceptLearn.h:346](firmware/libraries/PerceptLearn/src/PerceptLearn.h#L346)),
   order-dependent by construction
   ([:372](firmware/libraries/PerceptLearn/src/PerceptLearn.h#L372)), and
   therefore **not recomputable**. That is exactly why emptying `@LAT92` returns
   every `@LAT91` belief to baseline, and why the prune had to grow a
   `**BELIEF-AT-BOUNDARY**` gravestone to survive it. Under TTG-0003 that whole
   hazard evaporates: if beliefs are derived, a pruned tally is a *reason to
   recompute*, not a loss.
2. **TTG-RFC-0004 §4 is a proposed spec for this exact fleet, and it is not
   implemented anywhere.** Its own status line: *"§4 proposed, not implemented…
   This section is the design §2–3 were built to accept: only the meaning of
   'later' changes."* It adopts TTN-RFC-0010 (Fleet Pulse) unchanged as the
   time-base, puts the chart in a `ttdb-pulse` block, stamps each episode
   `at: <pulse time> ±<bound>`, orders sayings across agents by (same-agent file
   order) ∨ (`follows@` vector-clock edges) ∨ (non-overlapping stamp ranges),
   declares everything else **concurrent** → contested, makes the bar the fleet's
   Dream Cycle, and carries a grammar hash as `scene_id` so a split is a
   convergence failure. It ships a five-item test plan (§4.8).
   **robot_team owns the only hardware that can run it.**
3. **TTG-RFC-0005 gives "episodic" a spec.** `docs/handoffs/episodic-sensing-handoff.md`
   (2026-08-15) argued its way to the right primitive — *"the covering record must
   carry whatever the lane's consumer computes, so the fold is lossless for that
   consumer by construction"* — without a record format to put it in. TTG-0002
   §5.1's `ttdb-episode` block (`source:`/`at:`/`said:`/`shape:`/`percept:`) is
   that format, and TTG-0005 §5 says a correction is an **amendment kept beside the
   episode, never in it** — which is `@LAT100`'s lane-generation idea, generalised
   and already specified.

TTG also carries external evidence, which nothing in this repo's learning stack
does: bAbI task 1, 1,000 questions — 19.4% as shipped, **100.0%** after four lines
of *grammar data* (no code), 54.9% with `exclusive` removed, and 0.0% on a
permuted-grammar control (TTG-0004 §3.6).

### 1.3 The repo has outgrown its own front door

- **`FLEET.md` is 7,122 lines / 585 KB, and §6 alone is lines 184–6,707** —
  92% of the file. §6 is titled *"Current state & next action"* and is in fact a
  flat chronological log: **296 date strings, zero subheadings**, oldest entry
  first. CLAUDE.md instructs every session to read this file first. The two facts
  are incompatible, and the cost is paid at every single session start.
- **17 root `.md` files, 13,836 lines.** Eight are spent handoffs
  (`percept-learning-handoff`, `percept-learning-return`, `timestream-handoff`,
  `semantic-logging-handoff`, `part-b-handoff`, `episodic-sensing-handoff`,
  `default-network`, `stigmergy`) — history, not guidance, and indistinguishable
  from guidance by filename.
- **`replicate/README.md` has three broken links** (`LICENSE`,
  `feelings_ttdb.md`, `research/valence/`). It is the publication front door; it
  was copied from toot-toot-engineering without the files it points at.

### 1.4 The eyeball exists five times and the globe three

| primitive | implementations |
|---|---|
| eyeball | [cardputer:2181](firmware/cardputer_console/cardputer_console.ino#L2181) `drawEyeball` + [:2650](firmware/cardputer_console/cardputer_console.ino#L2650) `paintEyeBase`/`paintSclera`/`drawIris`/`renderEye`; [k10:929](firmware/k10_percept/k10_percept.ino#L929) `paintEyeBase`/`paintEyeSolid`/`paintIris`/`renderEye`; [tdeck:1600](firmware/tdeck_console/tdeck_console.ino#L1600) `drawEyeball`; the website's `js/eyeball.js` + `css/eyeball.css` |
| globe | [cardputer:2227](firmware/cardputer_console/cardputer_console.ino#L2227) `renderGlobe`; [tdeck:1651](firmware/tdeck_console/tdeck_console.ino#L1651) `renderGlobe`; the website's `js/index-ttdb.js` (44 KB) |
| record pane | `renderRecord` ×2 (paging fixed twice, 2026-08-02) |
| intero pane | `renderIntero` ×2, different signatures |
| ring / text | `drawRing` ×2, `drawWide` ×2 |
| status | `renderOled` ×3 ([v4a:667](firmware/v4a_bridge/v4a_bridge.ino#L667), [v4b:891](firmware/v4b_relay/v4b_relay.ino#L891), [v4c:875](firmware/v4c_edge/v4c_edge.ino#L875)) |
| fleet view | `orchestrator/fleet_ui.py`, 1,223 lines of tkinter |

Five independent rendering stacks: two Adafruit_ST7789 sketches, one TFT_eSPI
sketch, three U8g2-class OLEDs, one tkinter app, one browser. `CMD_SET_VIEW`
(op 14) is the symptom made explicit — its view ids are **node-local**, so the op
had to be made addressed-only and grow a `VIEW_NEXT` sentinel, because no shared
view vocabulary exists to name a view with.

And the piece that would make the views mean something is designed and unbuilt:
the **EPS arbiter**, `docs/design/cardputer-sensorium.md` §7 Phase S1 — *"Per-modality
`(sal, conf)`, EPS ranking, hysteresis. No new rendering."* Both call sites still
say so in the source
([:2494](firmware/cardputer_console/cardputer_console.ino#L2494),
[:3597](firmware/cardputer_console/cardputer_console.ino#L3597)). The project's
attention math is already chosen and already written down —
`EPS = sal × (255 − conf) / 255`, TTDB-RFC-0005 §3.3 — and nothing displays it.

### 1.5 Twelve lanes, and the caps sum past the budget

`@LAT90`–`@LAT101` are live (plus `@LAT88`/`@LAT89`). Caps: 90→16, 92→24,
94/95/96/97→48 each, 100→32, 101→reclaim-lowest. The whole-**file** budget is
`TTDB_MAX_RECORDS 288` ([TTDB.h:22](firmware/libraries/TTDB/src/TTDB.h#L22)),
which every lane shares, and the per-lane caps **sum past it** — the Cardputer
sits at 265/288. Four percept tiers (`LinkPercept` 216 loc, `EntityPercept` 636,
`MotionPercept` 756, `AcousticPercept` 233) write four similar-but-distinct record
grammars, each with its own run-length/covering convention, each with its own
prune path, each needing its own reader in `companion.py` (5,296 lines).

---

## 2. The new hypothesis: an autonomous fleet

### 2.1 The claim

> **A fleet of embedded agents, with no cloud model and no laptop present, can
> keep a shared memory that never refuses a write, cooperatively discover its own
> arrangement by acting to resolve what it does not know, and display what it
> knows and how well it knows it — on its own screens, without being asked.**

Four verbs, and each is a falsifiable clause rather than an aspiration:

| clause | falsified by | already have |
|---|---|---|
| **keeps** a memory that never refuses | any operating procedure needing a `clear` op (§5.2) | `@LAT101`, one lane |
| **discovers** its arrangement cooperatively | the fleet being unable to raise `poseCeiling()` by acting | passive evidence only |
| **agrees** without coordinating | two nodes with the same episodes answering differently (TTG-0004 §4.8 item 4) | nothing — never run |
| **displays** it unprompted | a node that knows its pose ambiguity and cannot show it | five renderers, no shared scene |

### 2.2 What changed, and what did not

**Semantic positioning is no longer the thing being proven; it is the thing the
fleet cooperatively does.** [ttn-semantic-positioning.md](ttn-semantic-positioning.md)
keeps every measurement, every falsifier and every ⚠ it has earned — none of that
evidence is touched or restated. What changes is its *role*: it stops being the
terminal claim and becomes the **exercise** through which the autonomous-fleet
claim is tested. Concretely, three demotions and one promotion:

- **The laptop stops being load-bearing.** Today the proof leg runs
  laptop-side: `companion.py` pulls, reconciles, and verifies against the T-Deck's
  GPS. Under the new hypothesis the *fleet* must reach the belief and the laptop
  must be an **observer that can be unplugged**. Act I built the laptop path
  because it was the only path; the time stream already exists because someone saw
  this coming — *"a fleet-owned timeline that survives the laptop's absence."*
- **GPS verification becomes an audit, not the mechanism.** It stays exactly as
  valuable and exactly as external.
- **Anchoring on V4-A is retired, not patched.** It is already recorded as
  **circular** (configured ≠ measured). A cooperative fleet has no configured
  anchor; it has the node whose current capability makes it *temporarily* the best
  reference, which is a thing `Social`'s capability tiers can already state.
- **Promotion: `poseCeiling()` becomes the fleet's objective.** Today it is a
  read-out — the fleet stating how much of its own shape it can currently know.
  Under §2.3 it becomes the **thing the fleet acts to raise**.

### 2.3 Active discovery — the part that is new work

Every positioning tier this fleet has is **passive**: it logs what happened to
arrive. Active discovery means the fleet **takes an action chosen to reduce its
own positional ambiguity**, and the machinery to choose that action is already
specified and already unbuilt:

- **What to reduce** is already computed. `Social`'s capability tiers record that
  common information gives **SHAPE but never POSE**, and that the remaining
  **4 DoF fall only to a node with a *unique* capability**. So the ambiguity is
  named, quantified, and attributable to a specific missing observation.
- **Which action to take** is already the project's own attention math.
  `EPS = sal × (255 − conf) / 255` is exactly *"what I rely on but have not
  verified"* — a ranked list of what to go and check. The **EPS arbiter**
  (`docs/design/cardputer-sensorium.md` §7 S1) is specified and unbuilt, and it is the same
  object.
- **How to act** already exists as toots. `CMD_DUET` is the precedent: two nodes
  coordinating an action, re-asserted every 2 s because a single invitation gets
  dropped. A "you are the only one who can collapse this ambiguity — take a
  reading" exchange is the same shape.

So active discovery is: **rank ambiguity by EPS, identify which node holds the
unique capability that would collapse the top one, ask it, fold the result, and
re-rank.** That is a cooperative loop, it needs no cloud, and it turns
`poseCeiling()` from a gauge into a controller.

⚠ **This does not un-gate the field re-run.** The falsifier has a false-positive
mode and the fleet is in it — 1.1× against a pre-registered 2.0× — and that gate
stands on its own terms. Active discovery is a new capability to be built and
measured; it is **not** a reason to re-run a blocked test, and it must not be
allowed to launder one.

### 2.4 The engineering slogan underneath it

> **One grammar, one loop, one memory.**

The fleet's percepts, beliefs and fields collapse onto the three record kinds TTG
already specifies — **episode**, **term/belief**, **field** — under one
consolidator, one memory discipline that never refuses a write (§5.2), and one
scene model every screen renders (§6). Time stops being an identity log and
becomes what TTG-RFC-0004 §4 asks for: a pulse-derived stamp with an error bound
plus `follows@` edges, so "later" is a partial order and everything inside the
tolerance is honestly reported as concurrent.

**Act III's own documents change too**, and this is Phase B work rather than a
footnote: `CLAUDE.md`, `README.md` and `PLAN.md` all currently open by naming
semantic positioning as *the primary hypothesis the fleet exists to prove*. All
three need the new framing, and `FLEET.md` §1–5 need it most, since they
describe a fleet organised around a laptop that is now explicitly optional.

---

## 3. Phase A — sync the RFCs

**Goal:** one corpus, three checkouts, no divergence, and the handhelds carrying
it.

> ### ✅ Phase A status — 2026-09-30
>
> | step | state |
> |---|---|
> | A1 normalise | ✅ all 37 files pure LF; `replicate/RFCs/*.md eol=lf` added |
> | A2 import TTG | ✅ 5 files, byte-identical to the donor |
> | A3 INDEX union | ✅ TTG section + per-entry hardware status; all links resolve; every file listed |
> | A4 `TTN-RFC-0002` | ✅ **resolved: v1.1 correct**; upstream 1.0 traced to a stale-baseline regression, pushed to both with the corpus record repaired |
> | A5 corpus union | ✅ 38 → **44 records**; native `test_rfc_ttdb` **passes 10/10** |
> | A5 handhelds | ✅ **BOTH done** — T-Deck (COM10) and Cardputer (COM14) each read back `RFC globe loaded: 52692 bytes, 44 records`, byte- and record-exact, and `rfc.ttdb.md` is byte-identical in both `data/` dirs |
> | A5 pre-flash bank | ✅ both boards pulled and verified first — `master/tdeck_pre_actIII_2026-09-30.md` (54,672 B / 115 records), `master/cardputer_pre_actIII_2026-09-30.md` (**137,958 B / 257 records**). The Cardputer's turned out to be Phase C's before-picture — see §5 C0b |
> | A6 push out | ✅ **both done** — toot-toot and `~/Documents/GitHub/antfriend.github.io`, each verified; uncommitted for review |
> | A7 reader | ✅ note only, no code (by design) |
>
> **Full native suite: 11/11 green, exit 0** — after fixing a pre-existing
> `BUILD FAILED: perceptlearn` link error the run exposed (see B5).
>
> 📎 **One finding worth carrying forward: `core.autocrlf=true` means the CRLF was
> working-tree-only — the three repositories never diverged on line endings at all.**
> The trap was real (five files read as "newer" in every size comparison) but its
> cause was local checkout, not content. That is why `eol=lf` matters here
> specifically: `mklittlefs` images the **working tree**, so without a rule the
> flashed bytes differ from the committed bytes.

### A1. Normalise before comparing

Add to `.gitattributes` (the existing rules cover `firmware/**/data/*.md` and
`master/*.md`, not the canonical source they are copied from):

```
replicate/RFCs/*.md   eol=lf
```

`replicate/RFCs/rfc.ttdb.md` is the corpus **flashed byte-exact** to both
handhelds; a CRLF slip there changes the bytes the HMAC and the belief readback
diff are computed over. Re-normalise the currently-CRLF files in the same commit
so the tree is uniform.

### A2. Import the five TTG RFCs

Source of truth is `toot-toot-engineering/RFCs/` (LF, and the repo whose
changelogs end at 1.0 Stable on 2026-09-22). Copy `TTG-RFC-0001` …
`TTG-RFC-0005` into `replicate/RFCs/`.

### A3. Merge `INDEX.md` as a union, not a copy

Take robot_team's `TTDB-RFC-0009`/`-0010` entries **and** toot-toot's five TTG
entries. Then extend the index with what only this repo can say: each RFC's
**implementation status on real hardware**, which is the one axis the other two
checkouts have no evidence for.

### A4. Reconcile `TTN-RFC-0002-Typed-Edges.md` — ✅ resolved: v1.1 is correct

**Done 2026-09-30, after two wrong readings, and the second one is the instructive
one.** Three lengths (1140 / 845 / 900) resolved to two contents: the two smaller
copies are 1.0 and identical (CRLF explains their gap); robot_team's is 1.1, a
strict superset adding §Semantic Polarity / `opposes`.

- **First wrong reading:** *superset ⇒ newer ⇒ push it.* Refuted by `git log -S`:
  the section was added in **both** repos on 2026-08-01 and then vanished upstream
  on 2026-09-22.
- **Second wrong reading** (this plan's previous text): *therefore upstream
  retracted it, so we are behind a decision.* Also wrong.

**It was a stale-baseline regression, and it happened twice in 45 seconds.**
Upstream `24cea1d "TTG Grammar"` (11:01:35) added the five TTG RFCs and **also
rewrote `rfc.ttdb.md`, reverting its TTN-RFC-0002 record from "seven groups" to
"six"** — regenerated from a base predating the feature. `796f633` (11:02:20) then
edited the RFC itself down to 1.0, making the regression self-consistent and so
invisible. Default web-edit messages, no rationale.

What settles it is that **everything the feature rests on survived both commits
untouched**: `TTDB-RFC-0003` §7 (which *defines* `opposes`) is still v1.1;
`feelings_ttdb.md` still carries **22 `opposes` edges** across 11 antonym pairs;
`research/valence/` still has 17 references. And those edges are **in production** —
`feelings.ttdb.md` is flashed to both handhelds. A taxonomy omitting a type its own
canonical store uses 22 times is exactly the inconsistency §7's rationale names.

**Action taken:** v1.1 stands here, and is pushed to both checkouts *with the
upstream corpus record repaired*. The website's 1.0 was merely **stale** (last
touched 2026-05-09, before the section existed) — a fast-forward, not a conflict.

📎 Two lessons, both now in `.gitattributes` and memory: *a byte count is not a
direction, and neither is a superset.* The thing that actually decided it was
**reading the target's `git log`, and then checking whether the dependent artifacts
moved with it.** A real retraction takes its dependents along; a regression leaves
them behind.

### A5. Rebuild `rfc.ttdb.md` as the union

38 records (robot_team: has TTDB-0009 + TTDB-0010) ∪ 39 (toot-toot: has the five
TTG) = **43 records, ≈60 KB** (from 44,499 B). Well inside the 288-record
whole-file budget, and ≈101 KB for all three globes against the 917 KB LittleFS
partition — no budget risk, but **both handhelds must be re-flashed**, because
both currently carry the 44,499 B copy byte-identically:

```powershell
scripts/Upload-Tdeck-FS.ps1     -Node tdeck_console     -Port <COMx>   # spiffs @0x310000
scripts/Upload-Cardputer-FS.ps1 -Node cardputer_console -Port <COMx>   # spiffs @0x310000
```

*Done when:* the T-Deck's trackball-click reaches the RFC globe and a TTG record
opens on it, and `companion.py pull` of that globe is byte-exact against
`replicate/RFCs/rfc.ttdb.md`.

### A6. Push back what only this repo has

`TTDB-RFC-0010-Stigmergic-Fields-and-Record-Identity.md` → both other repos
(verified safe: `git log --all --diff-filter=D` shows it never existed upstream and
was never deleted, so this is a genuine absence and not a retraction like A4's).
`TTDB-RFC-0009-Counter-Story…` → the website only; toot-toot already has it,
byte-identical. Plus the INDEX entries, and **`TTN-RFC-0002` v1.1 after all** — see A4.

⚠ **The website needs a fifth change the other repo does not, and without it the push
is invisible.** Its reader builds its contents panel from a hand-maintained list in
`index_ttdb.md` (`@LAT-32LON90`), not from the directory — so a new RFC file lands on
disk and never appears on the site. Both new RFCs were added there, along with its
ASCII summary card (33 → 35 documents, and the `lat 10` bar 8 → 10 filled).

This is the half of "sync" that is easy to forget, because the ask was phrased as
an import; robot_team is the sole holder of 0010, which is the RFC the `@LAT101`
field lane and the sid work implement — and the one whose §8.1 falsifier Phase C
inherits.

⚠ **Check the target's history before pushing any file, not just its presence.** A4
is the worked example of why: an absent-or-older file upstream may be a *decision*
rather than a gap, and the only thing that distinguishes them is the commit log.

### A7. Fold the website's reader into the plan; don't re-solve it

`antfriend.github.io` already renders this corpus as a walkable globe
(`js/index-ttdb.js`, `js/rfc-reader.js`, `js/eyeball.js`). **That is the sixth
renderer, and it is the most capable one.** Phase D treats it as the reference
TTCP renderer to converge *toward*, not as a thing to reimplement. No code moves
in Phase A; the note is here so D does not start from a blank page.

---

## 4. Phase B — reorganize, so the rest is executable

Low risk, no firmware, and it pays for itself at every subsequent session start.

> ### ✅ Phase B status — 2026-09-30
>
> | step | state |
> |---|---|
> | B1 `FLEET.md` + log split | ✅ 7,122 → **715 lines**; §6 6,524 → **62**. 197 entries → `docs/log/{2026-06,07,08}.md`, dated by `git blame`. **Losslessness proven: 6,391 non-blank lines in, 6,391 out, 0 missing, 0 extra.** §1/§4/§5 reframed for the new hypothesis |
> | B2 `companion.py` → `fleet.py` | ⏳ deliberately deferred to Phase C, as planned |
> | B3 `docs/` | ✅ root is **6 files** (was 17). 47 files' references rewritten; **0 broken links across 179 markdown files** |
> | B4 `replicate/` pointer | ✅ prose points upstream, `RFCs/` stays local as a build input; all links resolve |
> | B5 one test entry point | ✅ **`tests/run-all`**: 16 native + 16 laptop suites + the Makefile guard, **33/33 green** (was 11 targets). Exit codes negative-controlled |
>
> **Gate met:** `README.md` → `FLEET.md` reaches current state at **line 28** (target <200).
>
> 📎 **On history across the rename — a claim this plan first overstated.** `git mv`
> does not *make* history follow; rename detection is a diff-time **similarity** heuristic,
> and `FLEET.md` keeps only ~10 per cent of `companion.md` (715 of 7,122 lines). Git in fact
> pairs the old path with `docs/log/2026-08.md`, which inherited the bulk. Nothing is lost —
> git stores snapshots, and all **129** commits stay reachable via `git log -- companion.md`
> — but `git log --follow FLEET.md` needs a lowered threshold (`-M10%`) to cross the rename.
> Worth knowing before someone concludes the file has no past.
>
> ⚠ **Two self-inflicted defects worth recording, because both were caught only by a
> check that did not share the buggy code's logic.**
> **(1)** The reference rewriter skipped `companion.md` → `FLEET.md` for every root-level
> file, because its "already a sibling" shortcut compared *directories* and a **rename
> changes the basename, not the directory**. My verification reproduced the same flaw and
> therefore reported 0 stale references. An independent link-resolver found 23.
> **(2)** A blanket `RFCs/` → `replicate/RFCs/` rewrite corrupted **historical** prose in
> `docs/log/`, turning a 2026-07-31 entry into the tautology *"`replicate/RFCs/` now lives
> at `replicate/RFCs/`"*. Fixed by regenerating the log from `git HEAD` and re-applying
> **only link-target** repointing. → *Rule: never blanket-rewrite an archive; and a
> verification that shares the implementation's assumptions verifies nothing.*

### B1. `FLEET.md` → `FLEET.md`, and split it

**The rename is not cosmetic — "companion" names the laptop, and §2 just made the
laptop optional.** The file is the *fleet's* brain, not its companion's, so it
becomes `FLEET.md`, matching the root's existing caps convention (`README.md`,
`CLAUDE.md`, `PLAN.md`).

It keeps §1–5 (rewritten per §2.4 — they currently describe a laptop-centred
fleet) and §7, and its §6 becomes a **short, current** state section: fleet table,
what is true now, next action. The 6,524-line log moves to `docs/log/YYYY-MM.md`,
chronological, one file per month, with §6 linking to the current month.

⚠ **The log is not dead weight — it is the project's evidence.** Nearly every
⚠-marked rule in CLAUDE.md is a compressed citation of a §6 entry. So the split
commit must leave the moved text **byte-identical** and add a stable heading per
entry, so future citations can be anchors rather than line numbers. External
citations are explicitly not a constraint (§8.3), so the move itself is free; what
is *not* free is losing the ability to cite an entry at all.

### B2. Rename the orchestrator too — but in Phase C, not now

`orchestrator/companion.py` (5,296 lines) has the same misnaming problem and
should become `orchestrator/fleet.py`. **Do it in Phase C, when the file is being
rewritten anyway** (C5 expects it to shrink as four per-lane readers collapse into
one episode parser). Renaming it now churns every runbook line in CLAUDE.md and
every `docs/log/` entry for zero benefit, twice.

Two sub-decisions to make when it happens, not before: whether the command surface
keeps its verb names (`pull`/`sync`/`verify`/`band`/`intero`) — it should, they are
in muscle memory — and whether `fleet_ui.py` folds into it as `fleet.py ui`.

### B3. `docs/` for everything that is not the front door

```
docs/handoffs/    the 8 spent handoff docs, moved verbatim
docs/hardware/    docs/hardware/hardware_specs.md, docs/hardware/heltec-v4-solar-charging.md, docs/hardware/max98357a-v4-wiring.html
docs/design/      docs/design/cardputer-sensorium.md, docs/design/toot_network_architecture.md,
                  docs/design/default-network.md, docs/design/stigmergy.md
docs/log/         FLEET.md §6, by month
```

Root keeps: `README.md`, `CLAUDE.md`, `FLEET.md`, `PLAN.md`, `ACT-III.md`,
`ttn-semantic-positioning.md`.

### B4. `replicate/` becomes a pointer

Settled (§8.4). Two halves, and they are different, so be precise:

- **The prose front door points upstream.** `replicate/README.md`'s links to
  `feelings_ttdb.md` and `research/valence/` repoint at
  `antfriend/toot-toot-engineering`, and the README says in one line that this
  directory is robot_team's *slice* of that project, not a mirror of it. Add
  `LICENSE` (or link the root one) so the third broken link goes too.
- **`replicate/RFCs/` stays a real local copy**, because it is a **build input**:
  `rfc.ttdb.md` is flashed byte-exact to both handhelds and `INDEX.md` carries the
  hardware-status column only this repo can write (A3). A pointer cannot be
  flashed.

### B5. One test entry point

*(was B4)* There is no `make` and no host `g++`; the working runner is
**`scratchpad/t.sh`**, driving the persistent `zig c++` at
`c:/tmp/toolchain/zig-windows-x86_64-0.13.0/zig.exe`. It should move into `tests/`
and grow to cover everything.

✅ **Done 2026-09-30: `tests/run-all` covers 16 native targets, all 16 `*_py.py`
suites and `check_makefile.py` — 33/33 green.** The five previously *unobserved*
native tests (`citation`, `sid`, `social`, `tracefield`, `ttdb_index`) all pass; that
is now known rather than assumed. `scratchpad/t.sh` is a shim that `exec`s the new
runner, kept because runbooks and log entries name it.

📐 **Its three guards are negative-controlled, not just written:** a bogus target
exits 1 with *ZERO NATIVE TARGETS BUILT*, a bad toolchain path exits 2 with a message
saying not to re-download, and a good target exits 0.

⚠ **A missing source in that list is invisible unless the stale `.exe` is deleted
first, and it bit again on 2026-09-30.** `test_perceptlearn` had been failing to
**link** — `t.sh` (written Aug 3) never gained `Sid.cpp`/`TtdbParse.cpp` when the sid
work landed Aug 9 — and it surfaced as `BUILD FAILED` only because that run began
with `rm -f tests/test_*.exe`. Fixed in `t.sh`. This is the second instance of the
same hole (the first was `TimeStream.cpp` missing from four tests, 2026-08-07), which
is the argument for B5 being a real task and not tidying: **the runner must delete
binaries before building, fail on zero targets, and treat a build error as a failed
test.** `tests/Makefile` has the older form of the same defect — three undefined
variables meant `make` compiled nothing and `make test` re-ran stale binaries and
passed.

*Done when:* a fresh session reading `README.md` → `FLEET.md` reaches "what is
true now and what is next" in under 200 lines, and `tests/run-all` reports a
target count.

---

## 5. Phase C — the memory that never refuses

This is the substance of ask 2, and §8.2's answer made it both bigger and
sharper than the first draft of this plan had it. The goal is not "tidier lanes".
It is:

> **No lane has a cap. No operator ever clears anything. A write is never
> refused. Forgetting is continuous, principled, and visible.**

> ### ◐ Phase C status — 2026-09-30
>
> | step | state |
> |---|---|
> | C0 the gate | ✅ stated, and inherited verbatim from RFC-0010 §8.1 rather than invented |
> | C0b before-picture | ✅ **measured on hardware**: six of six capped lanes at cap, index 257/288, and **three** distinct refusal modes, not two |
> | C1 what works | ✅ written down; the five findings constrain the design below |
> | C2 three tiers | ◐ TERM/BELIEF **built**; EPISODE lane **built as a library** 2026-10-01 (`Semantic/src/Episode.*`: `@LAT103` episodes, `@LAT104` fold checkpoint, `Ttdb::removeCuts`) — not yet wired into a sketch. FIELD unchanged by design |
> | C2c fold-before-forget | ✅ **built and gated** — and it fell out of the streaming shape as a *move*, so losslessness is arithmetic rather than argued. On flash: **fold → append checkpoint (commit) → cut**, so a refused rewrite is garbage left over, never a double count — gated by a reboot-from-store after every episode with faults injected ([log](docs/log/2026-10.md)) |
> | C3 consolidator | ◐ **built, both gates green**; Rule 3 kept beside it and **measured** on the fleet's own 24 outcome records. Not yet wired into a sketch |
> | C4 time (TTG-0004 §4) | ⏳ not started — the headline, and still unimplemented in any checkout |
> | C0 the deletion | ⏳ the `clear` verbs are still in `orchestrator/` |
>
> `tests/test_semantic.cpp`: **88 checks, 0 failures**; `tests/test_episode.cpp`: **82, 0**. Suite **35/35**.
>
> 📐 **The measurement C3 asked for, on real data** (`scratchpad/consolidator_compare.py`
> over the banked `@LAT92` lane, run-length expanded back to windows and cross-checked
> against the node's own `**TALLY**` on 8/8 claims): counting is higher than Rule 3 on
> **8 of 8**, mean 177.5 → 238.9, largest gap **+89**. ⚠ But the *ordering* agrees — I
> predicted an inversion and there is none. What differs is magnitude, which still matters
> because EPS is a magnitude: `0x200/espnow` attracts 4× the attention under Rule 3
> (255−136) as under counting (255−225).
>
> ⚠ **A THIRD refusal mode, found by that comparison and worse than either in C0b.** The
> evidence lane holds **nine** claims; the node held **eight** beliefs
> (`PERCEPTLEARN_MAX_CLAIMS 8`). The missing one is the **K10**, with 31 confirmations and
> zero violations. A treadmill writes a `**LANE-PRUNED**` boundary; a refusing lane writes
> nothing; a **dropped belief** announces itself on a serial cable that is not attached and
> leaves the store looking complete. The sketch's own comment says why that is the worst of
> the three: *"a dropped claim biases conf from a subset of the lane while looking like a
> complete fold."* ✅ This is exactly the case `Semantic`'s **reclaim-lowest-EPS** answers —
> principled where "whoever arrived ninth" is arbitrary, and `reclaimed()` makes it
> countable from outside the process instead of printable to nobody.

### C0. The ask already has a pre-registered falsifier, written by an RFC

The fleet has exactly one lane built this way — `@LAT101`, the social field — and
its header states the terms
([Social.h:174](firmware/libraries/Social/src/Social.h#L174)):

> ⚠ *THE LANE HAS NO PRUNE PATH, AND THAT IS THE STAGE-3 FALSIFIER (RFC-0010
> §8.1). Reclamation is §5.3's reclaim-lowest, in RAM, when the table is full…
> **If operating this lane ever requires adding a `--lane 101` clear op, the RFC
> says to abandon it**: the treadmill was not the cost that mattered.*

So ask 2 is precisely **"generalise the stage-3 falsifier from one lane to the
whole store"**, and it inherits that falsifier verbatim. The pass condition is
therefore not a benchmark, it is a **deletion**:

> ✅ **Act III's memory work passes when `cmd --op clear-percepts`,
> `--op clear-timeline` and every other clear verb are gone from
> `orchestrator/` and nothing has replaced them.** If any operating procedure
> still needs one, the design failed on terms it set for itself.

That is a much better gate than "it feels cleaner", and it was already on the
shelf.

### C0b. The before-picture, measured on hardware 2026-09-30

C0's gate is a deletion, which makes it easy to state and hard to feel. The Cardputer
supplied the feeling on the way to its Phase A flash: pulled before `mklittlefs` could
overwrite it, its runtime store came back at **137,958 B / 257 records** with **six of six
capped lanes exactly at cap** and the whole-file index at **257 of `TTDB_MAX_RECORDS` 288**.

| lane | records | cap | state |
|---|---|---|---|
| `@LAT90` timeline | 16 | 16 | **refusing** — no prune path, no marker |
| `@LAT92` outcomes | 24 | 24 | **refusing** — froze all eight beliefs |
| `@LAT94`–`@LAT97` percepts | 48 each | 48 | **treadmilling** — six wipes, 288 windows gone |
| `@LAT100` lanegen | 6 | 32 | room |
| `@LAT101` field | 5 | **none, by design** | room |

Three things this establishes that the argument from shape could not:

1. **The two failure modes are different, and only one of them is visible.** A treadmill
   announces itself — `@LAT100` carries six `**LANE-PRUNED**` markers, `removed:48` each,
   so the boundary is written down. A refusal announces nothing at all: `@LAT90` and
   `@LAT92` have no marker and no log line. They simply stopped accepting records.
2. **Refusal corrupts belief silently.** `Reconciler` is a *pure function* of `@LAT92`.
   With that lane stuck at 24/24, the eight `@LAT91` beliefs were recomputed every Dream
   Cycle from a tally that had stopped accepting evidence — frozen at
   `met:11 violated:0`. A belief that new experience cannot move is a constant wearing a
   belief's provenance.
3. ✅ **C0's falsifier already passed once, unprompted.** The only two lanes with room were
   the two with no cap, and `@LAT101` *is* the stage-3 lane whose header states the
   falsifier. The one lane built to the discipline this phase generalises was the one lane
   still accepting writes. That is not proof the discipline scales — it is the strongest
   available evidence that it is the right thing to scale.

⚠ **The refusal reading is inference from a single census** — both lanes exactly at cap,
neither with a marker, both with a documented refuse-on-full policy — not an observed
refused write. Confirm it *inside* Phase C (watch one lane across a boot with the node
untouched), not before it: C2's mechanisms replace the policy either way, so the
confirmation is worth its cost only as a regression baseline.

The measurement is written up in [docs/log/2026-09.md](docs/log/2026-09.md). The store
itself is `master/cardputer_pre_actIII_2026-09-30.md`, whose 24-record `@LAT92` lane is the
natural fixture for **C3's order-independence test**: shuffle the outcomes, recompute,
expect the same eight beliefs. `master/cardputer_postflash_2026-09-30.md` (10 records) is
the matching after-picture — an empty store with known caps, which is Phase C's baseline.

### C1. Write down what works, because it constrains the design

Five things this fleet measured and should not lose:

1. **Change-triggered lanes with run-length.** Measured: `@LAT95` 48 min → ~24 h
   (**15.5×**), `@LAT92` **6.0×**, `@LAT96` **4.56×** (simulated). The mechanism
   that makes it lossless is the heartbeat, not the folding — raising `MAX_RUN`
   without also going 2-of-3 breaks it.
2. **The covering record carries what the consumer computes.** Not *"same value ⇒
   fold"*. `@LAT96` ends a run rather than dropping a window that will not fit:
   **the record's capacity bounds the run, not the other way round.**
3. **The edge is the datum.** `@LAT93` transitions are still the only instance in
   the corpus of TTDB-RFC-0006 §5 — the difference materialised instead of
   overwritten. Keep it; it is what prediction error can be computed over.
4. **FIELD lanes with decay-on-read** (`@LAT101`, `TraceField`): the RAM table is
   the live medium, the lane its change-triggered durable shadow, no prune path by
   design. A field lane must stay correct when **empty**.
5. **Separating "we agree with each other" from "we know what day it is"**
   (`stream:`/`wall:` replacing one `synced:` bit). TTG-0004 §4.3 keeps this
   distinction and sharpens it into a measured bound.

### C2. Collapse twelve lanes onto three kinds

Target, per TTG-RFC-0002 §5 and TTDB-RFC-0010's EVIDENCE / FIELD / PROVENANCE
declaration:

| kind | lane | replaces | contract |
|---|---|---|---|
| **EPISODE** (evidence) | one lane, `ttdb-episode` blocks | `@LAT93`–`@LAT97` percept tiers | one record per closed window-run; `percept:` lines per tier; `shape:`/`said:` per TTG-0002 §5.1 |
| **TERM/BELIEF** (derived) | one lane, `ttdb-term` blocks | `@LAT91` beliefs, `@LAT92` outcome tally | one record per distinct triple, revised in place; `[ew]` conf/sal/rev/touched |
| **FIELD** (decay-on-read) | one lane | `@LAT101`, `TraceField` | unchanged in kind — this tier is already right |
| **PROVENANCE** | TTG-0005 §5 amendments | `@LAT90` stream identity, `@LAT100` lane generations | an amendment sits *beside* the episode, never in it |

The four percept tiers keep their **samplers** — `LinkPercept`, `EntityPercept`,
`MotionPercept`, `AcousticPercept` stay, because each embodies a hard-won
threshold argument. What they stop owning is a record grammar, a prune path and a
reader. Each emits `percept:` lines; one writer appends episodes; one reader
parses them.

⚠ **This is where the `@LAT90` saturation question gets answered by being
dissolved, not decided.** It is currently the next session's focus: four of five
boards at 16/16 in ~2 days, `@LAT90` is fleet-coupled (43 stream ids cost 73
slots), 60% of ids never shared with anyone, and the trap is raising the cap
before knowing whether those 60% are churn. Under TTG-0004 §4 there is **no stream
identity lane at all**: order comes from stamps + `follows@` edges, so there is
nothing to saturate. Do not spend a session choosing a refusal-on-full policy for
a lane this phase removes — but **do** record the measurement in `docs/log/`,
because it is the evidence that the lane was the wrong shape.

### C2b. Three tiers, three reasons they cannot fill — and they are different

"Never fills up" cannot mean unbounded: flash is finite and
`TTDB_MAX_RECORDS 288` is a real whole-file index budget. It means **bounded
capacity that always accepts a write, by forgetting something else in a
principled way.** Each tier gets there differently, and the difference is decided
by the identity decision this repo already made — **EVENT naming vs KEY naming**
(a revised belief keeps its name; every FIELD lane is necessarily KEY):

| tier | identity | why it cannot fill |
|---|---|---|
| **TERM/BELIEF** | **KEY** | bounded by the number of distinct `(subject, vector, object)` triples the node can form. A revision **rewrites its own record**; the lane never appends. It does not need an eviction rule — it structurally cannot grow past its own vocabulary. |
| **FIELD** | **KEY** | decay-on-read + **reclaim-lowest** in a fixed RAM table; the lane is a change-triggered durable shadow. Already built, already measured, unchanged. |
| **EPISODE** | **EVENT** | the only genuinely append-only tier, so the only one that must truly evict. A **fixed ring** with **fold-before-forget** (C2c). |

📎 That asymmetry is the load-bearing insight and it is worth stating plainly:
**ordinal/EVENT naming is what forces prune boundaries, and KEY naming is what
makes reclamation free.** `Social.h` says exactly this — a reclamation *"writes NO
`@LAT100` boundary because under KEY naming there is nothing to re-point."* Two of
three tiers therefore stop needing `@LAT100` at all, and the third needs C2c
instead of a prune.

### C2c. Fold before forget — the one new mechanism

When the episode ring is full and a new episode arrives, the oldest episode is
**folded into the beliefs it supports before its record is dropped**: its
`for`/`against` contribution lands in the term record's carried tally, and only
then does the slot get reused. The write is never refused, and the belief is
unchanged by the forgetting.

This is not a new invention — it is the repo's own primitive, promoted from
exception to rule. `LaneGen`'s boundary already carries
`**OUTCOMES-CARRIED**` (the tally) and one `**BELIEF-AT-BOUNDARY**` line per
belief, precisely so a prune does not reset what was learned; `EntityPercept`'s
`**COVERED-ENTITY**` already carries the union its consumer computes. The
governing rule was already written down in
[docs/handoffs/episodic-sensing-handoff.md](docs/handoffs/episodic-sensing-handoff.md) (which Phase B moves to
`docs/handoffs/`):

> **The covering record must carry whatever the lane's consumer computes, so that
> the fold is lossless *for that consumer* by construction.**

Fold-before-forget is that rule applied to eviction instead of to run-length. Two
traps it inherits and must not re-learn:

- ⚠ **A carried record must never contain the consolidator's own needles.** The
  `@LAT92` boundary rule already says a boundary carrying `**OBSERVED** peer:0x`
  or `**COVERED** peer:0x` gets **folded as testimony next time the lane is
  read** — *the node re-learns from its own gravestone*, double-counting forever.
  A carried tally is data about evidence, never evidence.
- ⚠ **The eviction order must not be recency.** Dropping the oldest is correct for
  a *ring*, but the store should prefer to forget what it neither relies on nor is
  uncertain about — which is **lowest `EPS = sal × (255 − conf) / 255`**, the same
  key `Social`'s reclaim-lowest already uses and the same one the EPS arbiter
  (§6.4) and the snake (§7) read. One value function, three consumers.

### C2d. State the divergence from TTG-0003 upstream, and offer the amendment

⚠ **This breaks strict conformance with TTG-RFC-0003 §2, and it must be declared,
not quietly done.** That RFC says beliefs are derived and *"a conforming
implementation MUST be able to recompute every belief line from the episodes"*. A
store that evicts episodes cannot: it can recompute from *the episodes it still
holds plus the carried tallies*, which is weaker.

That is a legitimate move made in the legitimate way — TTG-RFC-0002 §4 already
sets the precedent with its own heading, *"Divergence from TTDB-RFC-0006,
stated."* So: state it, and then **propose it upstream as a bounded-store profile
for TTG**, because robot_team is the embedded end of that project and is the only
checkout with the hardware to motivate it. Pairs naturally with A6, which is
already pushing `TTDB-RFC-0010` outward.

The honest formulation of what the profile claims:

> Recomputability is preserved **over the retained window**, and beyond it the
> carried tally is a lossless summary *for the consolidator* — which is the only
> consumer that reads it. What is genuinely lost is **provenance**: the fleet can
> still say what it believes and how strongly, but not always which sentence
> taught it. That is the price of a memory instead of a log, and it should be
> visible in a reply (a ground that says *"carried, original episode forgotten"*)
> rather than silently absent.

### C3. Replace the consolidator

Implement TTG-0003 §2 as a pure function `consolidate(episodes) → beliefs`, in
`firmware/libraries/` so a native test can pin it (a native test cannot call into
a sketch, which is why a fixed-buffer builder never belongs in a `.ino`).
Constants come from a `numbers` block, not `#define`s: `prior_for 1`,
`prior_against 1`, `weight_partial 0.5`, `belief_conf_threshold 128`,
`inherit_decay 0.85`, `max_hops 4`.

Keep `PerceptLearn`'s asymmetric Rule 3 as a **second, selectable consolidator**
rather than deleting it. Its `+2`/`−16` and `K = 3` are described in its own
header as guesses that *"are still unrun"*, and the 1:8 ratio putting break-even
at p = 1/9 ≈ 11.1% *is* the experiment. Deleting it ends the experiment with no
result; keeping it beside a deterministic baseline turns it into a measurement —
*does an asymmetric in-place fold beat counting, on this fleet's real episodes?*
That is a better outcome than either deleting it or leaving it as the default.

**Gate:** a native test that reads a fixture episode lane, consolidates, and
reproduces the belief lines byte-for-byte; then the same test run with the
episodes in a **different order** producing the identical result.
Order-independence is the property Rule 3 cannot have and the one TTG-0003 exists
to give.

**Second gate, from C2c:** consolidate a fixture; evict its oldest N episodes with
fold-before-forget; consolidate again — the beliefs must be **identical**. This is
the test that makes "never fills up" safe rather than merely convenient, and it is
the one that would catch the gravestone-double-count trap.

⚠ **Rule 3 and eviction interact, and the interaction favours counting.** Rule 3's
`+2`/`−16` fold is sequential and order-dependent, so a folded-then-evicted tally
cannot be replayed to check it; TTG-0003's count can. Keeping Rule 3 as a
selectable consolidator therefore means keeping it **only over the retained
window**, and the comparison in the paragraph above must say so or it will
silently compare an exact number against an approximate one.

### C4. Time: implement TTG-RFC-0004 §4

The headline. `at: <pulse time> ±<bound>` on every episode, bound = delivery delay
+ `DRIFT_PPM` × time since the last adopted beacon; `follows@<id>` edges naming
the latest episode held from each other node (a vector clock as typed edges);
order = same-agent ∨ edge ∨ disjoint stamp ranges, else **concurrent →
contested**; the bar as the fleet's Dream Cycle; `scene_id` = low 16 bits of a
grammar hash.

Its five-item test plan (§4.8) is the acceptance criteria, already written:
non-overlapping stamps retire; overlapping stamps contest; an edge decides; two
agents holding the same episodes agree as of bar N; a two-hash fleet reports the
split. Item 4 is the falsifiable claim of §2.

⚠ **Reuse the pulse clock, not the time stream's — and not the reverse either.**
CLAUDE.md already records both halves of this trap: the pulse clock's election can
move a clock *backward* (fine for a beat, fatal for a log), and the time stream's
clock is a **ratchet** (fine for ordering, wrong for measuring a duration).
TTG-0004 §4.2 wants the pulse as the *tempo* and a per-node offset kept **in
memory, never in a file** — *"a copied store carries the chart but not the offset:
a file is a stale beacon."* And the recv callback must still never touch the
engine.

### C5. The compaction dividend, and what gets deleted

Expected, to be measured not assumed: four record grammars → one; four prune paths
→ zero; `companion.py`'s per-lane readers → one episode parser. The honest
statement of the goal is **fewer kinds of thing, not fewer bytes** — though
`companion.py` at 5,296 lines is where bytes should fall, and this is the phase in
which it becomes `orchestrator/fleet.py` (B2).

Things that should not exist when C is done — and this list *is* the C0 gate:

- every `clear` verb (`clear-percepts`, `clear-timeline`, and the `--lane N`
  argument they take);
- the per-lane cap constants `*_MAX_LANE` (48 / 24 / 16 / 32), and the arithmetic
  hazard that they **sum past** `TTDB_MAX_RECORDS 288`;
- `lanegen::prune`, `pruneOutcomes`, `pruneTimeline` and the NVS
  deferred-prune-on-next-boot machinery — a prune scheduled because the heap
  refused it is a treadmill artefact, and the treadmill is what is being removed;
- the runbook genre itself. *"A runbook naming a lane SLOT COUNT is stale in under
  a day"* stops being a trap because there are no slot counts to name.

---

## 6. Phase D — one way to draw

### D1. A `Ttcp` library: scene descriptions, not pixels

The rule is already the fleet's own and already proven by INTERO PERCEPT:
**transmit the numbers, never the pixels** — a 21-byte reply renders correctly on
two panels with different palettes, and that is what makes it a TTCP render.
Generalise it. A shared `firmware/libraries/Ttcp/` owns:

- **the scene model** — globe, record pane, intero gauges, eyeball, scope, field,
  and (Phase E) snake, each as a panel-agnostic description;
- **a shared view vocabulary**, which is what `CMD_SET_VIEW`'s node-local ids are
  a workaround for. Absolute view ids become meaningful fleet-wide; `VIEW_NEXT`
  stays as the form that needs no table;
- **primitives once**: `drawRing`, `drawWide`, `drawIris`, `paintSclera`, record
  paging with its `pg n/m` rule (*if a view can show less than all of a record, it
  must say so on screen*).

Per-board blitters stay tiny and stay separate: TFT_eSPI on the K10,
Adafruit_ST7789 on the two handhelds, U8g2-class on the V4 OLEDs.
`orchestrator/fleet_ui.py` and the website's `index-ttdb.js` consume the same
scene model, which is what makes "unified" mean something across the laptop and
the browser too.

### D2. The constraint that decides the architecture

⚠ **Damage-tracked partial repaint, not build-a-framebuffer-and-flush.** This is
not a preference. The K10 sketch abandoned the DFRobot LVGL canvas precisely
because one `updateCanvas()` invalidates the whole object — 240×320 = 153,600 B at
20 MHz ≈ **61 ms of SPI** before anything blends. A unified layer that composites
a full frame would regress the K10 to the exact condition it was rescued from, and
would blow the Cardputer's measured budgets (worst render 24 ms against ≤25, worst
loop pass 37 ms against ≤40). So the scene model must express *damage* — "these
cells changed" — and every phase re-checks the loop budget, which is the gate this
node has already failed once.

Also inherited, and non-negotiable: **never add `#include <TFT_eSPI.h>` to the K10
sketch**; it must inherit the board library's relative include, or the sketch and
the board library's own `tft` are compiled against different headers.

### D3. The V4s get repartitioned first

Settled (§8.5): the three V4s move to **`huge_app`**, so the unified layer lands on
all six boards rather than leaving three on a subset. They are at 94–95% of the
default 4 MB app partition with ~63–74 KB left, past the ceiling the T-Deck already
hit, and CLAUDE.md's own conclusion was that the next feature added to them needs
`huge_app` first. So this is a prerequisite, done deliberately and early rather
than discovered mid-phase.

⚠ **`huge_app` moves the LittleFS partition, and flashing the FS at the old offset
fails *silently*.** This exact mistake is already documented on the T-Deck: the
default scheme puts spiffs at **0x290000**, `huge_app` at **0x310000** (size
0xE0000). Writing the image at the wrong offset drops the LittleFS superblock in
the app region and garbage on the real partition, so the **mount fails quietly and
the node boots with an empty globe while the app otherwise looks fine.** So the
repartition is not one change but three, in one commit:

1. build all three V4 sketches with the `huge_app` partition scheme;
2. **`scripts/Upload-V4-FS.ps1` must be updated to 0x310000** — it currently
   hard-codes the default offset, and it is the only thing standing between this
   change and the T-Deck's failure mode reproduced three times;
3. re-flash each V4's filesystem and confirm the mount, not just the boot.

✅ **Verify by reading the board back, not by inferring from the mesh.** The V4s are
indistinguishable from outside and an `intero`/`ping` reply can arrive over the air
from a *different* battery-powered node. Reset out of band and catch the banner:

```bash
python -m esptool --chip esp32s3 --port COMx --after hard-reset chip-id
python scratchpad/catchboot.py COMx 14      # -> "V4-A bridge …" + "TTDB loaded: … records indexed"
```

A `TTDB loaded:` line with a record count is the mount confirmation; its absence is
the silent failure above. Match boards by `SER=` MAC, never by COM number.

### D4. Give the EPS arbiter its display

Build `docs/design/cardputer-sensorium.md` §7 **Phase S1** at last: per-modality
`(sal, conf)`, `EPS = sal × (255 − conf) / 255`, hysteresis, headless, winner
printed to serial. It is specified, it is owed, and it is the data source Phase E
needs. Its own done-condition is already written: *tilting, clapping, and a
neighbour rejoining each print the right winner, and the winner decays back to
`idle` within ~3 s.*

⚠ And finish **Phase S0** first, because it is a live data-quality bug in the tier
the whole acoustic story rests on: the node's own voice is still eligible to be
logged as an `@LAT94` transient. *Done when a `CMD_BEEP` produces no transient
while a clap still does.*

---

## 7. Phase E — the attention snake

📌 **You have more detail coming for §6 and §7.** What follows is therefore
deliberately the *skeleton and the data contract*, not a finished design — enough
to keep C2 from building a model the snake cannot read, and no more. The one thing
below that is a real change rather than a placeholder is §7.2.

### E1. What it is

A view in which **the eyeball is the head of a snake whose body is the fleet's
live attention**. Each body segment is one record currently held in the attention
window; segments are ordered by EPS, so the snake *is* the EPS arbiter's ranking,
drawn. The head gazes where the arbiter is looking — which the eyeball already
does from tilt on the K10 and the IMU on the Cardputer.

Because it consumes its own tail when a lane prunes, the flavour name is
**Ouroboros**; the view is `VIEW_SNAKE`.

### E2. ⚠ Phase C removed the wall and the death — and improved the game

The first draft of this plan had *the wall = the lane cap* and *death = a refused
write*. **§8.2 deleted both**: a memory that never refuses a write has no cap to
crash into and cannot die of being full. The failure mode the snake was going to
dramatise no longer exists, which is the point of Phase C.

What replaces it is better, and it is the thing the user's phrasing was already
reaching for — *less data logger, more dynamic agent with a memory*:

> **There is no game over. The snake is endless, and its length is the size of
> live attention.** It grows as percepts arrive and recedes as low-EPS records are
> reclaimed, so the tail is not punishment — it is **forgetting, drawn**.

That makes Ouroboros the right name rather than a pun: the snake continuously
consumes its own tail, because that is literally what C2c does on every write once
the ring is warm.

### E3. The mapping — every element is a real quantity

| snake | fleet |
|---|---|
| head position & gaze | the EPS arbiter's current winner; existing gaze from `MotionPercept` |
| each body segment | one live record in the attention window |
| segment colour | its tier (acoustic, motion, entity, link, peer field) |
| segment brightness | that record's `EPS = sal × (255 − conf) / 255` |
| food appearing | a percept arriving — a window closing, a peer heard, a transient |
| eating → growing | the episode ring gaining a record |
| **the receding tail** | **fold-before-forget** — the lowest-EPS record reclaimed (C2c) |
| a segment dimming | a belief settling: `conf` rising, so EPS falling |
| a segment flaring | a contested belief, or an expectation violated |
| length holding steady | admit rate = reclaim rate — a node at rest |
| **length collapsing** | **attention narrowing** — the honest signal that replaces "death" |

### E4. Why it is still an instrument, not a toy

The fleet's most persistent failure mode *was* **silent lane saturation**: `@LAT94`
filled its 48-slot cap in 48 minutes and then refused writes, and it *"reads
`48/48` on nearly every pull for months"* — including the entry naming the cost
plainly, *"was 48/48 FULL — the fleet's SECOND EAR was discarding."* Phase C
removes that failure by construction.

But **it replaces it with a quieter one that needs watching just as much**: a store
that always accepts a write can still be forgetting the wrong things, and *nothing
will report an error*. Reclaim rate, and what tier is being reclaimed, is the new
`48/48`. The snake shows exactly that continuously, on the node, without a pull:

- a tail receding faster than the head advances = the node is churning, and
  whichever colour is vanishing names the tier being starved;
- a body that is all one colour = one tier is crowding out the others;
- a body that is uniformly dim = everything is settled and nothing is being
  learned, which is a different problem and should look different.

**That is the instrument the fleet will need after Phase C**, and the argument for
it is stronger than the one it replaces, because the condition it watches for is
invisible by design rather than merely unreported.

### E5. Why a snake is the *cheapest* animation this fleet can run

A snake changes only at its two ends. On a damage-tracked panel (§D2) a tick
repaints two cells — against 153,600 B / ≈61 ms for a full K10 flush. A
screen-filling animated view that costs a handful of cell-blits per frame is not a
compromise for this hardware; it is the shape the hardware wants. This is the
technical reason the snake is the right game and not merely a charming one.

### E6. Steering = directing attention

- **K10** — autonomous. It has no reachable button, so the arbiter drives; the
  snake is an ambient display and `VIEW_SNAKE` is reachable only via
  `CMD_SET_VIEW` (op 14, addressed-only, `VIEW_NEXT` to step). K10 views become
  0 eye, 1 status, 2 senses, **3 snake**.
- **Cardputer / T-Deck** — steerable. Steering overrides the arbiter's choice of
  which tier to attend next, which makes the input meaningful rather than
  decorative: the autopilot is the node's own EPS ranking, and the operator can
  take the wheel.
  ⚠ On the Cardputer, keys are context-sensitive by existing rule (`1`/`2` are
  modality pins with the FACE up and page with the GLOBES up). Steering keys must
  join that table, not fight it.

### E7. Ordering, and the one thing C2 owes it

E depends on D2 (damage tracking), D4 (the arbiter), and C2 (a tier inventory worth
colouring). The **only** thing that must be fixed early — and it must be fixed in
C2, not retrofitted — is the per-tick data contract:

```
head:      gaze (dx, dy), winning tier
segments:  ordered list of (tier, eps, age_ms)   -- EPS-ranked, longest-lived last
events:    admitted (tier)  |  reclaimed (tier, eps)  |  contested (tier)
```

Note `reclaimed` rather than `pruned`: after C2 there are no prune events, and a
contract naming one would bake the old model into the new display.

*Done when:* the K10 shows the snake as a selectable view within budget (worst
render ≤25 ms, worst loop pass ≤40 ms, stated **with the uptime range**, because
`lp` is a 10-second window and sampling it late reads clean); a `CMD_BEEP`-triggered
percept visibly feeds it; and the tail visibly recedes when the episode ring is
warm.

📌 Everything above the data contract is provisional pending your detail.

---

## 8. Decisions taken — 2026-09-30

| | decision | consequence in this plan |
|---|---|---|
| **8.1** | **"Autonomous fleet" is the new hypothesis**, with active discovery *and* display of semantic positioning as a cooperative fleet activity | §2 rewritten. Positioning is demoted from terminal claim to exercise; the laptop becomes an observer that can be unplugged; `poseCeiling()` becomes a controller, not a gauge (§2.3). `CLAUDE.md`, `README.md`, `PLAN.md` and `FLEET.md` §1–5 all need reframing (§2.4) |
| **8.2** | **Replace every logging-style write with one memory that never fills up.** Less data logger, more dynamic agent with a memory | §5 rebuilt around admit-always / reclaim-lowest-EPS / fold-before-forget. Inherits RFC-0010 §8.1's falsifier: **the pass condition is that every `clear` verb is deleted** (C0, C5). Declares a divergence from TTG-0003 §2 and offers it upstream as a bounded-store profile (C2d). **Removed the snake's wall and death** (§7.2) |
| **8.3** | **Outside citations are not a constraint. Rename away from "companion"** | `FLEET.md` → **`FLEET.md`** (B1) — the rename is substantive, since §2 made the laptop optional. `companion.py` → `fleet.py` deferred to Phase C, where the file is rewritten anyway (B2). The external-citation warning is gone |
| **8.4** | **`replicate/` is a pointer** | B4. Prose front door points upstream; **`replicate/RFCs/` stays a real local copy because it is a build input** — `rfc.ttdb.md` is flashed byte-exact |
| **8.5** | **Repartitioning is fine** | D3: all three V4s move to `huge_app` **first**, so the unified layer lands on all six boards. ⚠ Carries a known silent-failure trap — `Upload-V4-FS.ps1` hard-codes 0x290000 and must move to 0x310000 |

**Still open, deliberately:** the detail of §6 (visualization) and §7 (the snake),
which you are supplying when those phases come up. Everything in §7 above the data
contract is provisional; the data contract itself (E7) is what C2 must honour and
is the only part that cannot wait.

**Two sub-decisions that belong to a later phase, noted so they are not made by
accident:** whether `fleet.py` keeps the verb names (`pull`/`sync`/`verify`/`band`/
`intero` — it should, they are in muscle memory), and whether `fleet_ui.py` folds
in as `fleet.py ui`.

---

## 9. Risks, and the ones that have already bitten

| risk | why it is credible here | mitigation |
|---|---|---|
| The RFC "sync" churns 30 identical files and buries the 6 real ones | CRLF made every website file look 200–400 B newer | normalise first (A1); diff with `--strip-trailing-cr`; review the 6 |
| A one-sided INDEX merge drops the other repo's newest work | neither INDEX is a superset — verified | union, then add the hardware-status column (A3) |
| **"Never fills up" quietly becomes "forgets the wrong things"** | a store that always accepts a write **reports no error when it is churning**; this is the new `48/48` and it is invisible by design | fold-before-forget must be gated by a test (C3 second gate); reclaim rate per tier is the thing the snake displays (§7.4) |
| **The node re-learns from its own gravestone** | already happened in kind: a `@LAT92` boundary carrying `**OBSERVED** peer:0x` gets folded as testimony on the next read, double-counting forever | a carried tally is data *about* evidence and must not match the consolidator's needles (C2c) |
| Eviction silently weakens provenance and nobody notices | C2d: beliefs survive, but "which sentence taught me this" may not | a reply must carry a *"carried, original episode forgotten"* ground rather than an absent one (C2d) |
| The unified render layer regresses the K10 | this is exactly why the LVGL canvas was abandoned: ≈61 ms/flush | damage-tracked by construction; re-check the loop budget every phase (D2) |
| **The V4 repartition drops an empty globe on all three boards** | already happened on the T-Deck: `huge_app` moves spiffs 0x290000 → 0x310000, and the wrong offset **mounts nothing while the app looks fine** | update `Upload-V4-FS.ps1` in the same commit; confirm by reading back a `TTDB loaded: … records indexed` banner, not by a successful boot (D3) |
| A green suite that built nothing | already happened: `tests/Makefile`'s undefined vars meant `make` compiled nothing and stale binaries passed | `tests/run-all` reports a target count and fails on zero (B4) |
| "It works" from a re-ACK or an eaten ACK window | already happened both ways: a dedup re-ACK reported a prune that never ran | only an attempt-1 ACK is evidence; only a re-pull is proof |
| A lane's own label used as evidence for a threshold | already happened, wrong by 2.75× | prune, then collect with the node untouched |
| A build flag that is only ever *named* gets omitted | already happened: the walk anchor was silently downgraded | write the full command line; have the board declare its own build at boot |

---

## 10. Sequencing

| phase | depends on | gate |
|---|---|---|
| **A** RFC sync | — | a TTG record opens on the T-Deck's RFC globe; the pulled globe is byte-exact against `replicate/RFCs/rfc.ttdb.md` |
| **B** reorganize + `FLEET.md` | — (parallel with A) | `README.md` → `FLEET.md` reaches current state in <200 lines; `tests/run-all` reports a target count |
| **C1–C2** three tiers | A (the spec), B (legibility) | every tier declares EVIDENCE/FIELD/PROVENANCE **and its non-filling mechanism** (C2b), with a losslessness argument naming its consumer |
| **C2c** fold-before-forget | C2 | a write is never refused with the ring full; the carried tally contains none of the consolidator's needles |
| **C3** consolidator | C2c | belief lines reproduced byte-for-byte; **identical under reordered episodes**; **identical after evicting N oldest** |
| **C4** time | C3 | TTG-0004 §4.8 items 1–5; item 4 (*two nodes, same episodes, same answers, no coordination*) is the headline claim |
| **C0** ✅ the memory gate | C2c + C3 + C4 | **every `clear` verb deleted from `orchestrator/`, and nothing replacing it** — RFC-0010 §8.1's own falsifier |
| **D0** V4 repartition | — (can precede D1) | all three V4s on `huge_app`, each reading back a `TTDB loaded: … records indexed` banner |
| **D1–D3** TTCP layer | C2 (the scene model needs the tier model), D0 | all six boards render from one scene model, each inside its measured render/loop budget |
| **D4** EPS arbiter | D1; S0 first | S1's own done-condition, verbatim from `docs/design/cardputer-sensorium.md` §7 |
| **E** snake | C2 (the E7 contract), D2, D4 | K10 shows `VIEW_SNAKE` in budget; a beep feeds it; **the tail recedes** once the ring is warm |
| **F** active discovery | C4, D4 | the fleet raises its own `poseCeiling()` by asking the node with the unique capability — §2.3, and the first new claim of the new hypothesis |

A, B and D0 are independent and can run together. C is the long pole and now
carries the headline gate (C0). D is the widest. E is small once C and D exist —
which is the argument for not starting with it, and for fixing its data contract in
C2 so it does not become a retrofit. **F is where the new hypothesis stops being a
reframe and starts being new work**; it is listed so it is not forgotten, and it is
last because it needs both the shared clock and the arbiter underneath it.

---

*Written to be superseded. When a phase lands, its result goes in `docs/log/` and
the gate row above gets a date.*
