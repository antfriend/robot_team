# FLEET.md — the robot_team fleet brain

**This file is the single source of truth for the robot_team project.** Read it
first, every session. When something here is wrong or stale, fix *this file*.

> **Renamed from `companion.md` on 2026-09-30 (ACT-III.md Phase B1), and the name
> mattered.** "Companion" named the laptop, and the fleet's hypothesis is now
> *autonomous fleet* (§1) — under which **the laptop is an observer that can be
> unplugged.** A file describing a laptop-centred fleet was the wrong front door
> for a fleet that has to work without one.

> **Source-of-truth rule (2026-07-13, amended 2026-09-30):** project knowledge —
> state, decisions, milestones, field findings — lives **here** (§6, the fleet
> table, the §7 knowledge map). The cross-session memory store
> (`~/.claude/projects/c--git-robot-team/memory/`) holds only **thin one-line
> pointers back to this file**, never divergent full-text copies, so the two can
> never disagree. Build/hardware gotchas belong in `CLAUDE.md` (also
> repo-canonical). Record a project fact here first; leave at most a pointer in
> memory.
>
> ⚠ **Amendment: this file is not the logbook, and treating it as one is what
> broke it.** "Record a project fact here first" was read as "append here
> forever", and §6 reached **6,524 lines — 92 per cent of a 585 KB file that
> every session is told to read first.** A dated *finding* now goes in
> [docs/log/](docs/log/) (one file per month); §6 holds only what is true now and
> what to do next. This file is the brain; `docs/log/` is the logbook.

## Where things stand — 2026-09-30

**Act III is underway** ([ACT-III.md](ACT-III.md) is the plan of record). The hypothesis
is now **autonomous fleet** (§1). Phase A (RFC sync) is done **bar one board**; Phase B
(this reorganization) is in progress.

**Next:** flash the Cardputer's filesystem — pull it first — then Phase C, the memory that
never refuses a write.

→ Detail, caveats and the banked evidence: **§6**. Dated findings: [docs/log/](docs/log/).
This box is a pointer, not a copy; when it disagrees with §6, §6 wins.

---

> Modeled on the `companion-arc` pattern from the ARC Prize project: one
> orchestrator that holds the whole picture and dispatches simpler, focused
> agents. There, the simpler agents were per-instance solvers. Here they are
> **A32 agents** — the ESP32 robots and the build-time subagents that own them.

---

## 1. What this project is

`robot_team` is **a team of ESP32 robots** that sense, reason, and act
*without* cloud LLMs or neural inference. Each robot is an **A32 agent**: a
deterministic device whose entire mind is a Toot-Toot Database (TTDB) markdown
file (see `replicate/RFCs/A32-RFC-0001-Architecture.md`). The robots form a
range-adaptive mesh (ESP-NOW in range, LoRa long-haul). A laptop runs the Locus
reasoning loop and Dream Cycle **when it is attached** — see the second bullet.

- **The robots are dumb-but-deterministic.** Intelligence lives in their TTDB.
- **The laptop is smart, and must become optional.** It authors TTDB, reconciles
  beliefs, and dispatches commands; it is the only LLM in the system. ⚠ But under
  the hypothesis below it is an **observer that can be unplugged** — anything the
  fleet can only do while a laptop is attached is, by that fact, not yet done.
  The team time stream exists because someone saw this coming: *a fleet-owned
  timeline that survives the laptop's absence.*
- **One protocol, the "toot."** Every message is a 250-byte toot frame, HMAC
  signed, dedup-keyed on `(src_node_id, toot_seq)`. See
  `docs/design/toot_network_architecture.md`.
- **The hypothesis is an AUTONOMOUS FLEET** (adopted 2026-09-30, plan:
  [ACT-III.md](ACT-III.md) §2). A fleet of embedded agents, with no cloud model
  and no laptop present, that **keeps** a memory which never refuses a write,
  **discovers** its own arrangement cooperatively by acting to resolve what it
  does not know, **agrees** without coordinating, and **displays** what it knows
  and how well it knows it, unprompted. Each of those four is a falsifiable
  clause, not an aspiration; ACT-III §2.1 gives the falsifier for each.
- **Semantic positioning is how that hypothesis gets tested, not the claim
  itself** (adopted 2026-07-07, spec:
  [ttn-semantic-positioning.md](ttn-semantic-positioning.md)). It keeps every
  measurement and every falsifier it has earned — *none of that evidence is
  touched* — but it is now the **exercise**: the fleet infers its own physical
  arrangement from umwelt overlap, and the three proofs stand as before,
  **verified** (position beliefs within their stated `sigma` of the T-Deck's GPS
  ground truth), **actuated** (proximity beliefs auto-switch each link between
  ESP-NOW and LoRa), and **rendered** (network + node status drawn as TTCP).
  What changed: the proof must run **fleet-side**, `poseCeiling()` becomes a thing
  the fleet *acts to raise* rather than a gauge it reports, and anchoring on V4-A
  is retired as circular (configured ≠ measured). Build order: PLAN.md **Act II**,
  then ACT-III **Phase F**.
  ⚠ Its field re-run is **gated** on a separation measurement — the falsifier has
  a false-positive mode and the fleet is in it (1.1× against a pre-registered
  2.0×). Act III does not un-gate that, and must not be used to launder it.

---

## 2. The fleet — the A32 agents it orchestrates

Each row is one A32 agent. The companion owns the contract; the agent owns its
firmware + TTDB. (Specs: `docs/hardware/hardware_specs.md`; mesh roles:
`docs/design/toot_network_architecture.md`.)

| Agent | Board | Role | Spine pos | Links | Power | Sketch | Status |
|-------|-------|------|-----------|-------|-------|--------|--------|
| **V4-A** | Heltec V4 | Bridge / head — laptop ↔ mesh gateway | head | USB-CDC + LoRa + ESP-NOW | mains, never sleeps | `firmware/v4a_bridge` | ✅ on-device verified (boots, ESP-NOW up, byte-exact pull + HMAC auth; OLED status; **`want_ack` ACK + time-sync: adopts `TIME_SYNC`, answers `TIME_REQ`, appends its own sync log**; LoRa gated off). **2026-07-30: answers `CMD_GET_INTERO` (21 B body, die temp now in STATUS too) and `CMD_DUET` — it led a verified double-time duet with V4-B.** **reads its own pack: 4.096 V / 89% / rising** (GPIO1 behind an ACTIVE-HIGH GPIO37, measured); ⚠ pull it over its own cable, the bridged path is broken |
| **V4-B** | Heltec V4 | Relay / mid — store-and-forward long hops | mid | LoRa + ESP-NOW | solar + battery | `firmware/v4b_relay` | ✅ on-device verified as the **3rd mesh node + Dream-Cycle participant** (2026-06-25): standalone byte-exact pull + self-heal + `negchecks` (COM9); then through the V4-A bridge over ESP-NOW — adopts `TIME_SYNC` (`@LAT99` self-write), folds into 3-node `reconcile` (id:3/4 `agree:yes`), and adopts a pushed belief byte-exact (`@LAT98`, 1373 B/crc match). Stores+attests beliefs (no DIRECTIVE action — no agent cadence). relay-forward + LoRa gated off. **2026-07-30: answers `CMD_GET_INTERO` and `CMD_DUET` — harmonised a double-time duet after being invited entirely over the air.** **reads its own pack: 3.831 V / 52% / rising** — the solar+battery node can finally report its state of charge; ⚠ its 54 KB TTDB no longer pulls through the bridge — use COM9 direct |
| **V4-C** | Heltec V4 | Edge / tail — remote cluster gateway, GNSS stamp | tail | LoRa + ESP-NOW | solar, off-grid | `firmware/v4c_edge` | 🟨 firmware at **full Dream-Cycle parity** (built from the verified V4-B: deferred+paced TTDB serve, `want_ack`/re-ACK, `TIME_SYNC`+`@LAT99`, belief `TTDB_PUT`+`@LAT98`, SP0 link/entity/BLE percepts, remote lane-clear, OLED, MAX98357A amp + band **offbeat hi-hat**), **2026-07-30: answers `CMD_GET_INTERO` and `CMD_DUET` too — the whole LoRa spine is now at parity, and its pack read 3.841 V / 54% on the FIRST flash because it was built with the measured GPIO37 polarity instead of the published one**; compile-verified 94% flash — ✅ **built + flashed + on-device verified (2026-07-16, COM13)**: `ping` ACK on attempt 1, `pull` byte-exact + self-appended `@LAT96` WiFi entity windows on first boot, adopted conductor 0x10 over ESP-NOW, band-tight ±6.5 ms, **hi-hat AUDIBLE by ear** (hand-wired amp confirmed); LoRa/GNSS gated off |
| **K10-1** | UNIHIKER K10 | Percept node — the fleet's SECOND ear + second stillness witness; the eye that is always on | leaf | ESP-NOW / WiFi | USB (no battery sense) | `firmware/k10_percept` | 🟨 **UNPARKED 2026-08-12 — back on the roster, compile-verified, NOT YET FLASHED.** Parked 2026-07-31, off the band roster since 2026-07-29. Returns with: **`heroarc::kPercept`** (its private Ode-to-Joy loop deleted — silent until the FINALE harmony, as scored); **`CMD_GET_INTERO`** (no battery sense, so bat 0 mV / pct 255 — honest, not silent) and **`CMD_DUET`**; **`CMD_CLEAR_PERCEPTS` + `@LAT100` lane generations** (it had NO prune path at all, which was survivable with one growing lane and is not with four); **`@LAT95`/`@LAT93` motion** off its SC7A20H accelerometer and **`@LAT94` acoustic** off its I2S mic — the two organs that had been on the board unread since it arrived; and a **screen-filling eyeball** as its default face, gazed by the tilt and dilated by the mic. It has **no reachable button**, so **`CMD_SET_VIEW` (op 14) is the only thing that can change its screen** — the T-Deck's `v` key is its hands. Still ✅ on-device verified for everything it had before (TTDB-share over ESP-NOW & USB, `want_ack`/re-ACK, chunk reassembly, `TIME_SYNC` + `@LAT99` self-write, `@LAT96` WiFi entity tier) |
| **T-DECK-1** | LilyGo T-Deck | Handheld console — keyboard injects CMD, screen shows fleet; roams | roaming leaf | ESP-NOW + LoRa (gated) + USB-CDC | battery | `firmware/tdeck_console` | ✅ on-device verified network floor (2026-07-06, COM10): boots from TTDB, **byte-exact pull (1351 B, sha `fd95360b…`)** + **HMAC reject** (`negchecks` wrong-key/tampered → 0). Full participant (pull/HMAC/dedup, `TIME_SYNC`+`@LAT99`, belief `TTDB_PUT`+`@LAT98`, STATUS, PULSE follower). **Console UI live (`USE_TDECK_HW 1`): "toot toot" on boot (I²S sine on the MAX98357A amp) + 320×240 fleet view (Adafruit_ST7789, rotation 3) — both confirmed on-device.** Keyboard (I²C 0x55) → CMD. LoRa gated. **GPS (Plus): NMEA read + `CMD_GET_GPS` GPS PERCEPT built (SP2 roaming anchor); compiles, not yet flashed/skied.** |
| **CARD-1** | M5Stack Cardputer ADV | 2nd handheld console + the fleet's **sense organ** — motion (BMI270) and sound (ES8311 mic); roams | roaming leaf | ESP-NOW + BLE + USB-CDC | battery (1750 mAh) | `firmware/cardputer_console` | ✅ on-device verified (2026-07-27, COM14): boots from TTDB (3 globes), **byte-exact pull 4166 B (sha `c764ae3b…`)**, `negchecks` wrong-key/tampered → 0 (HMAC reject), `CMD_BEEP` ACK attempt 1, hears V4-A over ESP-NOW (`@LAT97` −32 dBm), and logs **four** percept tiers — the first fleet node with @LAT95 motion + @LAT94 acoustic. No LoRa, no GPS (the T-Deck stays the GPS anchor). **2026-08-02: the Learning-from-Action stack (@LAT93 transitions · @LAT92 outcomes · @LAT91 TBEW beliefs) passed its verification gate on this node** — Dream Cycle flash cost measured (150 ms→1757 ms, O(file)), the shape claim confirmed against operator labels with a **23× roamer-vs-stationary separation**, `unobserved` fired for real, beliefs moved to `rev:9`, and a laptop re-fold matched the device on 8 pairs × 7 fields. Also answers `CMD_PING` with a `[mark] FIELD MARK` line so a walk can be labelled from across the house |
| **orchestrator** | laptop | The companion itself — Locus loop, Dream Cycle, master TTDB | — | USB-CDC + WiFi | mains | `orchestrator/companion.py` | 🟨 scaffold (`pull` reassembles a node's TTDB) |

Legend: ⬜ not started · 🟨 scaffold (compiles/ports, not on-device verified) · ✅ on-device verified

> **Hardware on hand: one K10 + two Heltec V4 (V4-A bridge + a 2nd V4 for V4-B) + one
> LilyGo T-Deck.** K10 = FQBN `UNIHIKER:esp32:k10` (COM3); the V4s + the T-Deck = FQBN
> `esp32:esp32:esp32s3` (V4-A on COM6). All use the ESP32-S3 native USB, so all need the
> **`CDCOnBoot=cdc`** flag (see build note). The 2nd V4 is the **V4-B relay** — ✅
> on-device verified as the 3rd mesh node + Dream-Cycle participant (flashed COM9;
> sync/reconcile/push, §6). The **T-Deck** is the handheld console (`firmware/tdeck_console`,
> node id `0x200`) — ✅ on-device verified end-to-end: network floor (COM10: byte-exact pull
> + HMAC reject), console UI (`USE_TDECK_HW 1`: boot "toot toot" + 320×240 fleet view),
> keyboard fleet remote, live on the mesh via the bridge, and the harmony voice of the
> 120 BPM duet (§6).
> **T-Deck flashing needs manual bootloader entry** (native-USB auto-reset is flaky): hold
> the trackball-click (GPIO0/BOOT) + tap RST to enter download mode (port re-enumerates,
> e.g. COM11→COM10), then tap RST *without* the trackball to boot the app. V4-C is built and flashed
> (COM13 as of 2026-07-16) — the whole fleet is now real hardware.
> **The M5Stack Cardputer ADV** (`firmware/cardputer_console`, node id `0x300`) joined
> 2026-07-27 as the 6th node and second handheld — same FQBN family as the V4s/T-Deck
> (`esp32:esp32:esp32s3:CDCOnBoot=cdc`) but on **`PartitionScheme=huge_app,FlashSize=8M`**,
> FS via `scripts/Upload-Cardputer-FS.ps1` (huge_app spiffs @0x310000, **not** the V4 script's
> 0x290000). Its auto-reset works — **no BOOT/RST dance needed**, unlike the T-Deck. It is the
> only node with an accelerometer and a microphone, hence the fleet's motion (`@LAT95`) and
> acoustic (`@LAT94`) percept tiers. **Its BMI270 is at I2C 0x69**, not the 0x68 the published
> pin map implies. Since 2026-07-29 it is also the **first node another console can look
> INSIDE** — it answers `CMD_GET_INTERO` with a 21-byte INTERO PERCEPT that the T-Deck's record
> pane draws as a live body view — and it took the K10's place on the T-Deck's mesh map.
> ⚠ **It stopped being the ONLY node with an accelerometer and a microphone on 2026-08-12**,
> when the K10 came back reading the two it had always had. That is worth stating as a fact
> about the FLEET rather than about the K10: "one ear" was the reason Phase 3 TDoA was
> unexercis*able*, and "one accelerometer" was the reason authoring a belief was structurally
> Cardputer-only. Both sentences now need rewriting, not just re-dating. The Cardputer keeps
> the better instruments (a 6-axis BMI270 with a gyro, a codec-fed mic); the K10 brings a
> SECOND vantage point, which for a time difference of arrival is the whole thing.
> **Flashing is one-cable-at-a-time** (the bench has one USB lead); all nodes run
> powered simultaneously for ESP-NOW — the deploy model is already per-node, so this
> fits: V4-A holds the USB as the bridge during operation, move the lead to flash another.

**Build & deploy:** command-line **arduino-cli** (not PlatformIO — a project
decision overriding the A32-RFC default). Each node is a proper Arduino sketch;
shared code is in `firmware/libraries/`, supplied with `--libraries`. See
`CLAUDE.md` and `firmware/README.md`. The `.sh` scripts are the Unix path; **on
the Windows K10 machine the live path is `.vscode/tasks.json`** (Compile/Upload
K10, Upload K10 Filesystem via `scripts/Upload-K10-FS.ps1`).

---

## 3. The A32 agent contract

Every A32 agent the companion dispatches MUST satisfy this contract. This is what
makes the swarm composable — the companion can reason about any node uniformly.

1. **Boots from TTDB.** Mounts LittleFS, parses the `mmpdb` header, validates
   `db_id` + `umwelt`, seats the cursor. No TTDB → no behavior.
   (`A32-RFC-0002`, `A32-RFC-0003`.)
2. **Runs the sense → reason → act loop.** Quantize sensors to TTDB
   coordinates → nearest node → follow typed edges → act. No inference.
3. **Speaks toots.** Emits/accepts the 250-byte frame; HMAC-signs; dedups on
   `(src, seq)`; honors `ttl`. Transport per the range-adaptive ladder.
4. **Streams, never slurps.** TTDB is read via file-offset index; never loaded
   whole. Feeds the watchdog (`yield()` ~every 100 iters).
5. **Is auditable.** TTDB is human-readable markdown. Firmware is a generic
   interpreter; the TTDB gives it purpose.
6. **Has a native-test build.** Parser + loop logic compile and pass on the
   `native` PlatformIO env with mock sensors (`A32-RFC-0004 §6`).

---

## 4. How the laptop orchestrates — while it is attached

The laptop wears two hats. Both dispatch "A32 agents," at different times.

⚠ **Read this section as a description of the present, not the target.** Under §1's
hypothesis the run-time half (§4b) is what has to migrate into the fleet: a capability
that only works with a cable in is not yet a fleet capability. ACT-III Phase C4 moves
ordering off the laptop, and Phase F moves the positioning loop off it.

### 4a. Build-time — Claude Code subagents
When building/maintaining a node, the companion spawns a focused subagent that
owns exactly one row of the fleet table: its firmware (`src/`, `lib/`), its TTDB
(`data/<node>.md`), and its native tests. The companion hands it:
- the **A32 agent contract** (§3),
- the node's **role + hardware constraints** (§2 row, `docs/hardware/hardware_specs.md`),
- the relevant **RFCs**.

The subagent returns when its node passes native tests and (where possible)
on-device serial assertions. The companion updates the fleet status column.

> Spawn one subagent per node only when the user asks for parallel/agentic
> builds. Otherwise the companion builds nodes itself, in dependency order.

### 4b. Run-time — physical robots
Once deployed, the same A32 agents run autonomously. The companion (laptop)
orchestrates them live:
- Injects **CMD** toots through V4-A (bridge) over USB-CDC.
- Collects **PERCEPT** / **BELIEF** toots back across the A→B→C spine.
- Runs the **Dream Cycle** to consolidate gossiped beliefs into the master TTDB.
- Re-authors node TTDBs and reflashes when behavior must change.

---

## 5. Sources of truth (this file reads these; it does not duplicate them)

| Topic | File |
|-------|------|
| A32 framework, layers, design principles | `replicate/RFCs/A32-RFC-0001-Architecture.md` |
| TTDB storage, streaming parser, index | `replicate/RFCs/A32-RFC-0002-TTDB-Storage.md` |
| Sense-reason-act loop, HAL registries | `replicate/RFCs/A32-RFC-0003-Agent-Loop.md` |
| Claude Code project layout, CLAUDE.md, PlatformIO | `replicate/RFCs/A32-RFC-0004-Claude-Code-Setup.md` |
| TBEW parser extension ([ew] blocks) | `replicate/RFCs/A32-RFC-0002-Amendment-A-TBEW.md` |
| TTDB file format / edges / weights | `replicate/RFCs/TTDB-RFC-000{1..8}` |
| Mesh transport, toot frame, bring-up order | `docs/design/toot_network_architecture.md` |
| **Semantic positioning — the Act II exercise (§1)** | `ttn-semantic-positioning.md` (build plan) + `replicate/RFCs/TTN-RFC-0011-Semantic-Positioning.md` (normative half, Experimental) |
| Cardputer sensory-representor mode (proposal) | `docs/design/cardputer-sensorium.md` |
| TTCP rendering (records, globe, URIs) | `replicate/RFCs/TTCP-RFC-000{1..3}`; live reference viewer: [antfriend.github.io](https://github.com/antfriend/antfriend.github.io) |
| Board specs, GPIO maps, gotchas | `docs/hardware/hardware_specs.md` |
| Build plan & milestones | `PLAN.md` |
| RFC catalog | `replicate/RFCs/INDEX.md` |

| **Act III — the plan of record (hypothesis, memory, viz, snake)** | [ACT-III.md](ACT-III.md) |
| **Dated findings, by month — the logbook** | [docs/log/](docs/log/) |
| Spent handoff documents (history, not guidance) | [docs/handoffs/](docs/handoffs/) |
| Design docs: sensorium, network, default network, stigmergy | [docs/design/](docs/design/) |
| Board specs, wiring, solar | [docs/hardware/](docs/hardware/) |
| Toot Toot Grammar — what Act III consolidates toward | `replicate/RFCs/TTG-RFC-000{1..5}` |

If a fact lives in one of these, link to it from here — don't copy it.

---
## 6. Current state & next action

**State (2026-09-30): Act III is underway.** The fleet's direction changed — see
[ACT-III.md](ACT-III.md), which is the plan of record and supersedes the old
"next action" that used to live at the bottom of this section.

- **The hypothesis is now `autonomous fleet`**: a fleet that keeps a memory which never
  refuses a write, cooperatively discovers its own arrangement by acting to resolve what
  it does not know, agrees without coordinating, and displays what it knows unprompted.
  Semantic positioning ([ttn-semantic-positioning.md](ttn-semantic-positioning.md)) keeps
  every measurement it has earned but is no longer the terminal claim — it is the
  *exercise* through which the new claim is tested. **Consequence: this laptop must become
  an observer that can be unplugged.**
- ✅ **Phase A (RFC sync) is COMPLETE on every board.** Five `TTG-RFC-*` imported; the
  compressed corpus is 38 → 44 records; all three checkouts consistent; native
  `test_rfc_ttdb` green. **Both handhelds report the identical `RFC globe loaded: 52692
  bytes, 44 records`** — the Cardputer flashed 2026-09-30, `rfc.ttdb.md` byte-identical
  in both `data/` dirs.
- ✅ **Phase B (this reorganization) is COMPLETE** — this file's rename, the log split,
  root down to 6 files, and one test entry point. `orchestrator/companion.py` →
  `fleet.py` is deliberately held for Phase C (B2).
- ✅ **Repo health, current:** **0 broken links across 222 markdown files**;
  `bash tests/run-all` is **35/35** (18 native + 16 laptop + the Makefile guard).
- ◐ **Phase C is underway. The TERM/BELIEF tier is built and gated**:
  `firmware/libraries/Semantic/` implements TTG-RFC-0003 §2 counting as a *stream*, which
  makes fold-before-forget a **move** (live → carried) and so lossless arithmetically
  rather than by argument. Both of C3's pre-registered gates are green — belief lines
  byte-identical under **reordered** episodes, and byte-identical after **evicting** the
  oldest with the fold. `tests/test_semantic.cpp` 88 checks / 0 failures; suite **34/34**.
  Still to do in C: the EPISODE lane writer, C4 time, and the deletion that is C0's gate.
- 📐 **Phase C's premise is MEASURED, not argued.** The Cardputer's pre-flash pull
  found **six of six capped lanes at cap** and the whole-file index at **257/288**,
  failing in two distinct ways: `@LAT94`–`97` **treadmilling** through whole-lane wipes
  (six `**LANE-PRUNED**` markers, `removed:48` each — 288 windows destroyed) and
  `@LAT90`/`@LAT92` **refusing writes** outright, which froze all eight `@LAT91` beliefs
  at `met:11 violated:0`. The only lanes with room were the two with no cap. Full
  measurement: [docs/log/2026-09.md](docs/log/2026-09.md).
- ⚠ **… and then a THIRD refusal mode, which cost the fleet a real belief.** Found after
  the census, by the consolidator comparison rather than by the lane census. The evidence holds
  **nine** claims; the node held **eight** beliefs (`PERCEPTLEARN_MAX_CLAIMS 8`). The
  missing one is the **K10**, with 31 confirmations and 0 violations — the fleet had the
  evidence and could not hold the conclusion. Unlike a treadmill (which writes a
  `**LANE-PRUNED**` boundary) or a refusing lane (which writes nothing), a dropped belief
  announces itself only on a serial cable that was not attached. `Semantic` answers it with
  **reclaim-lowest-EPS** plus a countable `reclaimed()`.

### Next action

1. **Phase C, continued** (ACT-III §5 and its ◐ status block). The consolidator **and the
   EPISODE lane library** are done (`Semantic/src/Episode.*`, `@LAT103` episodes +
   `@LAT104` fold checkpoint, 2026-10-01 — [docs/log/2026-10.md](docs/log/2026-10.md)).
   ✅ **RUNNING ON THE CARDPUTER** (2026-10-01): every scored link window → one `@LAT103`
   episode, beside the untouched `@LAT92`/`@LAT91` path. **On hardware: fold + commit at
   49, boot cut, and reboot agreement — including THROUGH a checkpoint and an unplanned
   crash — all pass**, and so does the **runtime (radios-up) cut** (58 → 40 records, 1.7 s pass). C4's portable core (`FleetTime.*`, §4.8 items
   1–4) is built and the episodes now carry `at: <pulse> ±<bound>`.
   ✅ **The Cardputer's ~20-min reset was the BLE SCANNER leaking ≈500 B/min** (not Phase
   C — A/B'd; it overturns the 2026-08 "ceiling, not a leak" note). A **60 s scan restart**
   (`blelink::loop()`, Cardputer only) holds free heap flat at ~26 KB **with peers OFF (~9–11 KB with peers on)**. BLE also costs
   ~92 KB of heap just by being on. ✅ With peers on: BLE claims still heard every window, heap flat. ✅ **V4-A had the same leak (−517 B/min) and the restart bounds it exactly**; the fix is now in every BLE sketch — **All five BLE boards now run it** (Cardputer + V4-A measured; T-Deck, V4-B, V4-C flashed, unmeasured). ✅ The `seen`/EPS drift and C4's chart-frame question are both fixed in source (stamps now carry `frame:<downbeat>`) — ✅ **flashed and verified on the Cardputer** (`frame:` held across a takeover; first new-format checkpoint carries `seen`). Next: **C0's
   deletion is not yet honest** (census 2026-10-01: seven capped lanes still treadmill or refuse). ✅ **Per-tier quotas built** (one LON
   band per tier, GATE 7) and flashed. ✅ **ENTITY tier moved into `@LAT103`** (2026-10-01) with
   `parse_entity_percepts` reading both containers in the same commit; Cardputer `@LAT96` released
   once (index 257 → 212/288). 🛑 Its first flash **boot-looped on heap** (+5.6 KB `.bss`) — every
   episode render now shares **one** scratch buffer (`EpisodeNode::scratch()`), net −768 B vs before.
   ⚠ **With peers on, loop free heap is ~9–11 KB** (measured twice) — that is the margin, so a
   moved tier adds **no** static buffer; diff `.bss` against HEAD before flashing.
   ✅ **ACOUSTIC tier moved** too (2026-10-01; no laptop reader existed; `@LAT94` released, index → 208/288).
   ⚠ **The Cardputer's boot abort is intermittent** (BLE scanner `operator new`, boot burst; pre-existing —
   `2912c11` too): 4/19 boots on 10-01, **0/36 on 10-02**. Not the battery (it crashed at the HIGHER
   reading); cause of the change untested (room BLE traffic is the lead). Boot-count after every flash.
   ✅ **MOTION tier moved** (2026-10-02) — and a full `@LAT95` had been silencing the LINK tier too
   (Rule 1 disarmed → nothing scored → no link episode); both run again, first link fold since.
   Index → 178/288. Boot adverts now printed (`[ble] N advert(s)…`): 101–140 in 5 s, 0/12 crashed.
   ✅ **LINK tier moved** (2026-10-02), the last: one link-band episode per window (RSSI as `said:`, scored
   claims as said/percept), `parse_link_percepts` reads both containers, and **`@LAT92` outcomes flow again**
   citing `@LAT103` (first since `@LAT97` filled; `@LAT91` beliefs 1 → 5). `@LAT97` released: index → 139/288.
   ✅ **C3 WIRED** (2026-10-02): the node's beliefs ARE the episode consolidator (TTG-0003 counting) —
   no `@LAT92` written, no `@LAT91` rewritten; FACE_BELIEF reads RAM with Rule 3 beside it (retained window
   only). `companion.py beliefs` recomputes them from a pull, **9/9 byte-identical** to the node. Heap
   dividend: `.bss` −6.3 KB, loop heap 9–11 → **16–18 KB**. ⚠ The panel itself is not yet eyeballed.
   **Next:** C0 on the Cardputer is now blocked only by `@LAT90` (16/16) — C4's `follows@` order replacing
   the stream lane; the other boards still need an episode tier at all (V4s at 95% flash).
   ⚠ C4's `follows@` edges must cite a **sid**, not a bare ordinal: episode ordinals are
   serial numbers inside an 8192-wide tier band and wrap in ~5.7 days at link's rate.
   📌 Reproduce the consolidator comparison any time with
   `python scratchpad/consolidator_compare.py`.
2. ⚠ **The laptop currently holds the fleet's ONLY copy of its only beliefs** — 257
   records banked in `master/`, gone from the board. That is the flash's intended
   consequence and the pull was its mitigation, but it is exactly the shape this
   hypothesis distrusts, and Phase C is where it stops being true.

⚠ **The `@LAT90` saturation question is no longer the next focus, and acting on it
would be wasted work.** ACT-III §C2 dissolves it rather than deciding it: under
TTG-RFC-0004 §4 order comes from pulse-derived stamps plus `follows@` edges, so there is
no stream-identity lane to saturate. ✅ What survives is the *evidence that the lane was
mis-shaped* — fleet-coupled (43 stream ids cost 73 slots), 60 per cent of ids never shared
with anyone, the K10 naming the mechanism (13 of 16 `STREAM-ORIGIN`). That **detailed
survey** exists only in six banked pre-prune pulls named in the last 2026-08 log entry;
re-pulling the boards will not reproduce it. 📎 **Amended 2026-09-30:** the *saturation
itself* was reproduced — the Cardputer came back at `@LAT90` 16/16 with **no prune
marker**, i.e. refusing writes ([docs/log/2026-09.md](docs/log/2026-09.md)). What a
re-pull cannot recover is the per-id breakdown, not the fact.

### The log — where this section's 6,524 lines went

This section was a flat chronological log: 197 entries, 296 dates, **no subheadings**, and
92 per cent of a 585 KB file that every session is told to read first. It is now
[docs/log/](docs/log/), one file per month, every entry's text unchanged and each one
carrying a heading so it can be cited by anchor instead of by line number:

| month | entries | |
|---|---|---|
| [2026-06](docs/log/2026-06.md) | 21 | first light → the mesh, reliability, time-sync, the pulse |
| [2026-07](docs/log/2026-07.md) | 88 | the band, the handhelds, semantic positioning's field runs |
| [2026-08](docs/log/2026-08.md) | 88 | stigmergy, lane discipline, the `appendRecord` defect, the fleet-wide reflash |
| [2026-09](docs/log/2026-09.md) | — | **not split out — authored directly**, which is the practice from now on. Act III: the RFC sync, this reorganization, the Cardputer census |

Month attribution is from `git blame` — the commit that introduced each entry — not from
dates in the prose, which name when the *work* happened and often predate the writing.

⚠ **Keep this section SHORT.** It is the first thing the next session reads, and the
reason it needed splitting is that "keep this current" was read as "append here forever".
A finding goes in `docs/log/<this month>.md`; only *what is true now* and *what to do
next* belong here.

---

## 7. Fleet knowledge map (TTDB)

The companion **dogfoods the TTDB format**: below is its own knowledge of the
fleet, encoded the way the A32 nodes encode theirs (`TTDB-RFC-0001` file format,
`TTDB-RFC-0003` typed edges, `TTN-RFC-0002` edge taxonomy). It is the master map
§6 narrates. Globe: `lon` = spine position (**0** laptop · **10** head · **20**
mid · **30** tail), `lat 10` = leaf/cluster depth, `lat 90` = engineering
decisions & lessons. Keep both this map and §6 in sync.

**Epistemic weights (`TTDB-RFC-0005`).** Each record carries an `[ew]` block —
`conf` (settledness: 240 proven-on-hardware · 210 stable/exercised · 195 first
instance live · 120 proposed/unbuilt), `sal` (how load-bearing), `rev`, `touched`
— and a derived attention signal **`EPS = sal × (255 − conf) / 255`**. High EPS =
load-bearing *and* unproven → the next thing to verify/build; proven work
(high `conf`) goes quiet. **When reading this file to choose the next move,
compute EPS across these records and let the maximum guide you.** As of
2026-07-16 the ranking points, correctly, at the open crux: **@LAT90LON50 —
Semantic Positioning (EPS 125)**, then **@LAT90LON60 — the SP6-T render leg /
TTN-RFC-0011 (EPS 19)**; everything else sits below EPS 20. **@LAT0LON30 (V4-C
edge) fell from EPS 74 → 8** when it was built + verified on hardware
(2026-07-16), retiring the #2 item and leaving **Semantic Positioning alone at
the top by a factor of ~6** — the hypothesis is now the *only* load-bearing
unproven thing left, and no hardware gap hides behind it. Update the weights when
a record's status changes (a weight-only write does not bump `rev`).

```mmpdb
db_id: orchestrator-master-001
db_name: Orchestrator Master Knowledge Map
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: orchestrator
  role: companion-orchestrator
  perspective: whole-fleet
  scope: master
  constraints:
    - only-llm-in-system
    - authors-and-reconciles-ttdb
  globe:
    frame: fleet-topology
    origin: "@LAT0LON0"
    mapping: "laptop at origin; lon = spine position (0 laptop, 10 head, 20 mid, 30 tail), lat = cluster/leaf depth, lat 90 = engineering decisions"
    note: "what the companion knows about each A32 agent and the build state"
cursor_policy:
  max_preview_chars: 256
  max_nodes: 64
typed_edges:
  enabled: true
  syntax: "type@LATxLONy"
  note: "TTN-RFC-0002 taxonomy: knows, connected_over, routes_via, navigates_to, commands, acknowledges, reports_sensor, supports, refines, derived_from"
librarian:
  enabled: false
  primitive_queries: []
```

```cursor
lat: 0
lon: 0
```

---

@LAT0LON0 | created:1750000000 | updated:1781913600 | relates:connected_over@LAT0LON10,routes_via@LAT10LON10,commands@LAT0LON10,knows@LAT0LON20,knows@LAT0LON30,refines@LAT90LON0
[ew]
conf:240
rev:0
sal:180
touched:1783983861
[/ew]

**Orchestrator** — the laptop companion, the only LLM in the system. Holds the
master TTDB and drives the fleet. `orchestrator/companion.py pull` reassembles any
node's TTDB over the link (whole-file or byte-range, HMAC-verified), directly over
USB-CDC or through the V4-A bridge into the mesh. Verified: byte-exact pulls of
both built nodes (K10 1114 B, V4-A 976 B). Auth/replay floor checked with
`orchestrator/negchecks.py`. Also `cmd`/`monitor` (drive + observe nodes),
`reconcile` (fold node `@LAT99` sync logs → `master/consolidated.md`, Dream-Cycle
seed), `push` (re-author + distribute a belief → `master/belief.md`, see
`@LAT90LON30`), and `band` (measured band-tightness verifier, see `@LAT90LON40`).

---

@LAT0LON10 | created:1750000000 | updated:1781913600 | relates:connected_over@LAT0LON0,routes_via@LAT10LON10,navigates_to@LAT0LON20,acknowledges@LAT0LON0
[ew]
conf:240
rev:0
sal:150
touched:1783983861
[/ew]

**V4-A bridge** (Heltec WiFi LoRa 32 V4, spine head) — ✅ on-device verified
2026-06-20. FQBN `esp32:esp32:esp32s3:CDCOnBoot=cdc`, on COM6. Boots, ESP-NOW up
(ch 1), serves its TTDB over USB-CDC (byte-exact 976 B), rejects wrong-key /
tampered toots (HMAC). **OLED status display** (SSD1306 128×64; SDA 17 / SCL 18 /
RST 21; Vext GPIO36 LOW; U8g2 on the generic esp32 core) shows id, TTDB size,
ESP-NOW channel, live counters (serial-in / injected / served / rx / bridged) and
uptime. TTDB image flashed via `scripts/Upload-V4-FS.ps1` (spiffs @0x290000). LoRa
gated (`USE_LORA 0`).

---

@LAT10LON10 | created:1750000000 | updated:1781913600 | relates:connected_over@LAT0LON10,refines@LAT90LON0,derived_from@LAT90LON10
[ew]
conf:240
rev:0
sal:120
touched:1783983861
[/ew]

**K10-1 percept** (UNIHIKER K10, leaf in the head's ESP-NOW cluster) — ✅ on-device
verified. FQBN `UNIHIKER:esp32:k10:CDCOnBoot=cdc`, on COM3. Agent32 sense→reason→act
loop runs; LCD shows both TTDB records + cursor/WARM; startup "toot toot". Byte-exact
pull (1114 B) + HMAC reject + dedup. Reaches the laptop over ESP-NOW via the V4-A
bridge. Reflashed 2026-06-20 to radio-only dedup (see `@LAT90LON0`) and re-verified
with `negchecks.py` — now consistent with the V4-A. Self-writes its TTDB at runtime:
`@LAT99` time-sync logs (`sync`), and on a pushed belief adopts `/belief.md` and
appends a `BELIEF-ADOPTED` record in its `@LAT98` lane (`push`, `@LAT90LON30`).

---

@LAT10LON0 | created:1782259200 | updated:1783382400 | relates:commands@LAT0LON10,connected_over@LAT0LON10,knows@LAT0LON0
[ew]
conf:240
rev:0
sal:170
touched:1783983861
[/ew]

**T-DECK-1 console** (LilyGo T-Deck, roaming handheld operator) — ✅ on-device verified
end-to-end 2026-07-06. FQBN `esp32:esp32:esp32s3:CDCOnBoot=cdc`, node id `0x200`,
sketch `firmware/tdeck_console`. A mobile mini-orchestrator: the BlackBerry keyboard
(I²C `0x55`) is a **fleet remote** (`t` cycle target V4-B→K10→V4-A, `s` status, `p`
ping, `b` beep, `g` play, `x` stop) and the 320×240 screen renders the live fleet view,
so an operator drives the swarm without the laptop. Full ESP-NOW Dream-Cycle
participant, verified on the floor (**byte-exact pull 1351 B, sha `fd95360b…`** + HMAC
reject) *and* over the air through the V4-A bridge (bridged pull, STATUS, `sync` id=5
adopt + `@LAT99` self-write). Console UI live (`USE_TDECK_HW 1`): boot "toot toot"
(I²S sine on the MAX98357A) + fleet view on **Adafruit_ST7789 (runtime pins, rotation
3 — deliberately not TFT_eSPI)**. Plays the **harmony part of the 120 BPM Ode-to-Joy
duet** with the K10, song state persisted in NVS so it rejoins after a power-cycle.
Carries an SX1262, so it can join the LoRa spine directly (`USE_LORA`) — the only
screen+keyboard node that reaches long-haul. `GPIO10` gates the peripheral rail (drive
HIGH first); native-USB flashing needs manual BOOT/RST (see §6) — though it took a plain
`--upload` three times running on 2026-07-29, so try without the dance first.
**Interoception ✅ on-device verified (2026-07-29):** selecting a node on the mesh map draws
that node's BODY in the record pane — its own from a local sampler (`PIN_BAT_ADC` 4, die
temp, `maxalloc`, worst loop pass), anyone else's from a polled 21-byte INTERO PERCEPT
(`CMD_GET_INTERO`). Both confirmed on the glass by the user, incl. the Cardputer's body
drawn live over ESP-NOW. Its own battery divider is **unconfirmed** (reads 4.71 V, above the
Li-ion ceiling), so it withholds the percentage rather than invent one.
**SP6-T (2026-07-11):** repartitioned to **huge_app** (3 MB APP; FS at 0x310000, flashed
with `scripts/Upload-Tdeck-FS.ps1`) and grown into a native **TTCP mini-renderer** — a
trackball-navigable globe (nodes at believed `@LATxLONy`, sigma rings, transport-coloured
edges, graticule, 3 zooms) + record view + console pane, fed by `companion.py fleetmap`
(`positions.md`+`proximity.md` → its `data/ttdb.md`, one TTDB lineage with the laptop
viewer). A **second globe view** (`n` toggles) browses the RFC corpus (`rfc.ttdb.md`,
view-only, off the mesh). See `@LAT90LON60`.

---

@LAT0LON20 | created:1750000000 | updated:1750000000 | relates:routes_via@LAT0LON10,navigates_to@LAT0LON30
[ew]
conf:240
rev:0
sal:120
touched:1783983861
[/ew]

**V4-B relay** (Heltec V4, spine mid) — ✅ on-device verified 2026-06-25 (COM9 flash).
A 2nd Heltec V4 fills this row as the fleet's **3rd mesh node**. Firmware
(`firmware/v4b_relay`) is a full **ESP-NOW Dream-Cycle participant** — deferred TTDB
serve + paced burst, want_ack ACK/re-ACK, TIME_SYNC adopt + `@LAT99` append, belief
`TTDB_PUT` adopt + `@LAT98` attestation (stores+attests, no DIRECTIVE action — no agent
cadence), OLED status — built blind from the verified K10 + V4-A patterns and worked
first try. Verified through the V4-A bridge: 3-node `sync`/`verify` (within ±50 ms),
`reconcile` (4 sources `agree:yes`), `push` (belief id=9 byte-exact). Pure LoRa
store-and-forward (decrement `ttl`, dedup, re-sign, forward) stays gated behind
`USE_RELAY_FORWARD` / `USE_LORA` until Phase 4 + range separation.

---

@LAT0LON30 | created:1750000000 | updated:1784160000 | relates:connected_over@LAT0LON20,supports@LAT90LON50,derived_from@LAT90LON70
[ew]
conf:240
rev:1
sal:140
touched:1784160000
[/ew]

**V4-C edge** (Heltec V4, spine tail) — ✅ **built + on-device verified end-to-end
2026-07-16** (was an unbuilt scaffold; `conf` 120→240, EPS 74→8). FQBN
`esp32:esp32:esp32s3:CDCOnBoot=cdc`, node id `0x12`, sketch `firmware/v4c_edge`,
flashed on **COM13** (identify by USB `VID_303A&PID_1001` — COM numbers drift; the
historical fleet ports were all absent that session). TTDB image via
`scripts/Upload-V4-FS.ps1` (default 4 MB spiffs @0x290000 — *not* the T-Deck script).
**Needed zero source changes**: the fleet-wide square-wave/8 kHz audio and quarter-amp
`STARTUP_TOOT_AMP` 2750 had already landed. Verified: `ping` ACK attempt 1; `pull`
byte-exact (842 B flashed → **1840 B returned**, the surplus being **two `@LAT96`
ENTWIN windows the node appended itself on first boot** — 8 + 6 WiFi BSSIDs, so the
LittleFS mount, TTDB serve *and* the SP0 entity tier all came up unprompted →
`supports@LAT90LON50`); **adopted conductor `0x10` over ESP-NOW rather than
self-appointing** (era 1, 120 BPM); band-tight **±6.5 ms** against the ±50 ms bound;
**offbeat hi-hat AUDIBLE by ear** — the hand-wired MAX98357A moves air (an ACK only
proves `toneI2S` ran). Off-grid remote-cluster gateway; GNSS `@LATxLONy` stamping;
summarizes PERCEPT before the LoRa hop. **Still gated:** `USE_LORA 0` / `USE_GNSS 0`
(Phases 3–4). **Still unexercised:** bridged `pull --node v4c_edge` over the mesh
(the known inline-serve caveat; direct USB pull works).

---

@LAT90LON0 | created:1781913600 | updated:1781913600 | relates:supports@LAT0LON10,supports@LAT10LON10
[ew]
conf:240
rev:0
sal:70
touched:1783983861
[/ew]

**Decision — dedup is radio-only** (2026-06-20). `(src,seq)` dedup applies on the
ESP-NOW/LoRa receive path only (replay + mesh forwarding-loop guard); the trusted
USB-CDC command link is intentionally NOT deduped, so the laptop can retry a lost
request. Gate dedup in the radio recv callback, never in the shared `handleToot`
dispatch. The K10 was reflashed to match the V4-A (2026-06-20) and re-verified.

---

@LAT90LON10 | created:1781913600 | updated:1781913600 | relates:supports@LAT0LON10,supports@LAT10LON10
[ew]
conf:240
rev:0
sal:70
touched:1783983861
[/ew]

**Lesson — native-USB `CDCOnBoot`**. Both S3 boards expose the ESP32-S3 built-in
USB (no UART bridge chip), so `Serial` — and the `TootSerialLink` the companion
pulls over — only reaches the COM port when built with the FQBN suffix
`CDCOnBoot=cdc`; otherwise it binds to UART0 and pulls return zero bytes. Opening
the port resets the board, so `companion.py` waits ~2.5 s before sending the request.

---

@LAT90LON20 | created:1781913600 | updated:1781913600 | relates:derived_from@LAT0LON10,derived_from@LAT10LON10
[ew]
conf:240
rev:0
sal:85
touched:1783983861
[/ew]

**Milestone — bridged ESP-NOW pull (Phase 1b) ✅ achieved 2026-06-20.**
`companion.py pull --node k10_1 --port COM6` reassembles the K10's TTDB byte-exact
through the V4-A bridge over the air (laptop→USB→V4-A→ESP-NOW→K10 and back),
repeatably; `radio_replay.py` confirms an over-the-air duplicate `(src,seq)` is
dropped. Firmware lessons baked in: serve replies from `loop()` (not the recv
callback), pace ESP-NOW bursts, fresh `toot_seq` per request. **Now → Phase 2**
(`want_ack` + chunking) so every bridged pull is byte-exact under loss; ~1/6 still
drops a frame today. **Update (2026-06-25):** the pull stream is now self-healing —
`request_ttdb` detects gaps against the EOF total length and selectively re-requests
the missing byte ranges (`TTDB_REQ_RANGE`) until byte-complete, no firmware change
(see §6). ✅ On-device verified over COM3 *and bridged over COM6* with `pull --drop`
(induced loss recovers byte-exact; firmware RANGE branch ran live, incl. over the air).

---

@LAT90LON30 | created:1782170835 | updated:1782170835 | relates:derived_from@LAT0LON0,derived_from@LAT10LON10,refines@LAT90LON20
[ew]
conf:240
rev:0
sal:100
touched:1783983861
[/ew]

**Milestone — Dream Cycle, both halves (Phase 6 seed) ✅ achieved 2026-06-24.** The
consolidation half: `companion.py reconcile` folds each node's self-authored `@LAT99`
sync records into `master/consolidated.md` (per-source `recv_ms`/`offset_ms`
provenance) and exits non-zero on any `t_ms` disagreement — K10 `id:1`/`id:2` both
`agree:yes`. The propagation half (`TTN-RFC-0009`): `companion.py push` re-authors
`master/belief.md` from that consolidated knowledge and streams it as offset-addressed
`want_ack TTDB_PUT` slices with CRC-32 whole-object integrity; the K10 writes it to a
separate `/belief.md`, CRC-verifies, and appends a `BELIEF-ADOPTED` record to its own
TTDB (`@LAT98` lane). Verified K10/COM3 — `978 B` / `crc 65118C32`, 6/6 slices ACKed
first try, round-trip MATCH; monotonic `belief_id` → exactly-once adoption (no
duplicate on re-ACK). Push log: `master/belief-log.md`. **Bridge-relayed push ✅
(2026-06-24):** the same `push` now reaches the K10 *over ESP-NOW through the V4-A
bridge* (`--port COM6`, belief `id:4`), once the K10 was taught to defer a radio
`TTDB_PUT`'s flash write to `loop()` (Phase 1b lesson) and the in-`push` verify pull was
moved to a fresh link session (re-opening resets the bridge clean; reusing the burst
session came back empty). The exactly-once gate is RAM-only — a re-push of a reused
`belief_id` after a node reset re-adopts, which is why `belief_id` is monotonic and never
reused. **Dream Cycle CLOSED ✅ (2026-06-24):** the belief carries a `**DIRECTIVE**
sense_interval_ms:<N>` the K10 acts on — its loop cadence retuned **1000→300→700 ms**
across pushes (TTN-RFC-0009 §5.2, PLAN.md Phase 6 "Done when"). **Next:** serve
`/belief.md` back for a byte-diff; add further directives (warm threshold, LED policy).

---

@LAT90LON40 | created:1783382400 | updated:1783382400 | relates:derived_from@LAT0LON10,derived_from@LAT10LON10,derived_from@LAT10LON0,refines@LAT90LON30
[ew]
conf:240
rev:0
sal:95
touched:1783983861
[/ew]

**Milestone — Fleet Pulse & the band (TTN-RFC-0010) ✅ end-to-end on hardware
(2026-06-26 → 2026-07-06).** The band time-base: a shared pulse clock (`millis()` +
adopted offset), first-up-conducts election with `era`-numbered handoff, and
drift-paced `PULSE` beacons (~1 per 15–30 s — zero per-beat traffic; 51 beats on one
beacon measured). Verified: **3-node ensemble locked to one chart, skew ≤ ±10.4 ms**
(`companion.py band` PASS, well inside the ±50 ms swing budget); conductor reboot +
era-latch handoff exercised live. On top of it, `Score.h` note tables give each node a
**data-driven part**: K10 = lead melody (Ode to Joy), T-Deck = harmony a third below,
V4-A = timekeeper, V4-B = backbeat. **120 BPM two-part duet confirmed by the user**;
both voices boot silent and start/stop via `CMD_PLAY`/`CMD_STOP` (keyboard `g`/`x`).
Gotchas baked into CLAUDE.md/memory: tempo lives in `Pulse.h` (a sketch `#define`
never reaches `Pulse.cpp`), the era latch keeps an old tempo across a reflash
(cold-start the fleet), and K10 GPIO45 is the speaker, not the backlight.

---

@LAT90LON50 | created:1783382400 | updated:1783382400 | relates:refines@LAT0LON0,supports@LAT10LON0,derived_from@LAT90LON40
[ew]
conf:130
rev:0
sal:255
touched:1783983861
[/ew]

**Decision — SEMANTIC POSITIONING is the primary hypothesis (2026-07-07).** The
project's governing claim (`ttn-semantic-positioning.md`): nodes infer their
physical arrangement from umwelt overlap — link RSSI percepts, shared-entity
co-occurrence, **BLE near-range approximation**, environmental TDoA — fused by
the Dream Cycle into `@BELIEF:PROXIMITY` / `@BELIEF:POSITION`. Proof legs:
**verified** against the **T-Deck GPS** (roaming ground-truth instrument,
never an inference input), **actuated** (beliefs auto-switch each link
**ESP-NOW ↔ LoRa** with hysteresis — the reason `USE_LORA` finally comes up),
and **rendered** (the end goal: network + node status as **TTCP on the laptop
and the T-Deck** — laptop via the existing
[antfriend.github.io](https://github.com/antfriend/antfriend.github.io) viewer
over the master TTDB, T-Deck via a native mini-renderer grown from the console
fleet view). Build order: PLAN.md Act II (SP0 instrumentation → SP1 calibration
→ SP2 embedding/anchoring → SP3 env TDoA → SP4 address loop → SP5 transport
auto-switch → SP6 TTCP render).

---

@LAT90LON60 | created:1784073600 | updated:1784073600 | relates:derived_from@LAT10LON0,refines@LAT90LON50,supports@LAT0LON0
[ew]
conf:225
rev:0
sal:165
touched:1783983861
[/ew]

**Milestone — SP6-T render leg live + Semantic Positioning made normative
(2026-07-11 → 07-12).** The proof's **rendered** leg reached hardware: the T-Deck
became a native **TTCP mini-renderer** (repartitioned to huge_app, 3 MB APP; FS at
0x310000 via `scripts/Upload-Tdeck-FS.ps1`) — a trackball-navigable globe (believed
`@LATxLONy`, sigma rings, transport-coloured edges, graticule, 3 zooms) + record view
+ console pane, fed by **`companion.py fleetmap`** so laptop and handheld draw one TTDB
lineage (the SP6 "Done when"). A **second globe view** browses the RFC corpus on-device
(`rfc.ttdb.md`, view-only). Verified first try: huge_app boots, PSRAM canvas renders,
byte-exact pull (1351 B) confirms the repartition left the floor intact. The hypothesis
itself was promoted to a normative spec, **`TTN-RFC-0011`** (Experimental) — the
mechanisms are proven, the central claim (Ω ↓ distance, semantic overlap beats
RSSI-only) is **not yet confirmed** (2026-07-10 garden run = partial negative on the
RSSI leg; §8.1 spacetime entanglement is the open blocker). `ttn-semantic-positioning.md`
stays the build plan; the RFC is its formal half.

---

@LAT90LON70 | created:1784160000 | updated:1784160000 | relates:derived_from@LAT0LON30,derived_from@LAT10LON0,supports@LAT0LON0,refines@LAT90LON20
[ew]
conf:240
rev:0
sal:90
touched:1784160000
[/ew]

**Lesson — the fleet's own telemetry produces FALSE NEGATIVES; confirm with ears or
`ping`, never one sample (2026-07-16, V4-C bring-up).** Two independent traps, both
observed on hardware, both of which drew a confident-but-wrong diagnosis out of the
companion before the physical system corrected it. Cost: a chase after a nonexistent
V4-C fault while it was audibly playing.

**(1) `cmd --op play` reports "NOT applied" on nodes that ARE playing.** Per-node
`companion.py cmd --op play --node v4c_edge|tdeck_1` printed **"no ACK after 4
attempts → NOT applied"** — yet both had applied it and were sounding. **`toneI2S`
blocks**, so a node that starts its part misses the ACK retry window (RTO ~4 s max)
though the CMD landed fine. The ACK path fails, not the command path: **`ping` still
ACKs from the same node mid-episode**, so "NOT applied" says *nothing* about
reachability. **Never chase a node's health on a play/beep no-ACK.** An ACK only
proves `toneI2S` ran — **only ears prove the speaker moved air**.

**(2) Band phase needs a settle window; early samples lie.** The first three `band`
runs after nodes were engaged FAILed (±72.0 / ±50.2 / ±48.6) and framed V4-B as
defective (−72.0, then −50.2, then `(no reply)`). **Wrong.** Three runs later V4-B
read **−7.7 / −3.7 / −7.6** and the whole band passed at **±8.5 / ±6.5 / ±7.6 ms**.
The tell: one bad run had V4-C *and* the T-Deck both swinging to ≈−45 **together** —
**a single-node fault cannot move two other nodes in lockstep**, so skews that track
each other are the shared reference settling, not per-node drift. **Take ≥3 runs with
`--probes 5`; trust only a bias that persists and that neighbours don't share.**

**Corollaries.** Start/stop the band with the **T-Deck's `g`/`x`** — it broadcasts to
`NODE_BROADCAST`, every member starts on the same toot, **no per-node ACK needed**
(user-confirmed working). The **bridge does not rebroadcast** (`v4a_bridge` sets only
its own `gPlayEnabled`), so driving play from the laptop is one unreliable CMD per
member — the awkward path. And **`stop` to the conductor re-elects**: V4-A (era 1) →
**V4-B `0x11` (era 2)**, after which `band` showed nodes `(no reply)` to status probes
while `ping` still ACKed — cosmetic here, undiagnosed; cold-start if the era latch
looks stuck (`@LAT90LON20`).
